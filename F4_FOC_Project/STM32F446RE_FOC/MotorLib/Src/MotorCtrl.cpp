/*
 * MotorCtrl.cpp
 *
 *  Created on: Aug 5, 2019
 *      Author: watashi
 */

#include "MotorCtrl.hpp"

MotorCtrl::MotorCtrl() {
	// TODO Auto-generated constructor stub

}

MotorCtrl::~MotorCtrl() {
	// TODO Auto-generated destructor stub
}

void MotorCtrl::InitSystem(void) {
	//以下CubeMXに頼らない定義たち
	//mainで既に定義されているとうまく動かないから、Mainで定義する前に呼び出すこと。
	GPIOInit::Init();
	USARTInit::Init();
	ADCInit::Init();
	TIMInit::Init();
}

void MotorCtrl::InitPWM(void) {
	PWM PWM_Object1; //PWMのHWを叩くClass
	PWM PWM_Object2;
	PWM PWM_Object3;
	PWM PWM_Object4;

	//LL_TIM_DisableBRK(TIM1);//こっちは未検証
	//LL_TIM_DisableIT_BRK(TIM1);//効かない

	PWM_Object1.setTIM(TIM1);
	PWM_Object2.setTIM(TIM1);
	PWM_Object3.setTIM(TIM1);
	PWM_Object4.setTIM(TIM1);

	PWM_Object1.setCH(1);
	PWM_Object2.setCH(2);
	PWM_Object3.setCH(3);
	PWM_Object4.setCH(4);

	PWM_Object1.fInit(PWM_PERIOD_COUNT);
	PWM_Object2.fInit(PWM_PERIOD_COUNT);
	PWM_Object3.fInit(PWM_PERIOD_COUNT);
	PWM_Object4.fInit(PWM_PERIOD_COUNT);

	PWM_Object1.f2Duty(0);//50%duty
	PWM_Object2.f2Duty(0);
	PWM_Object3.f2Duty(0);
	PWM_Object4.f2Duty(0);

	LL_GPIO_SetOutputPin(GPIOC, GPIO_PIN_10);
	LL_GPIO_SetOutputPin(GPIOC, GPIO_PIN_11);
	LL_GPIO_SetOutputPin(GPIOC, GPIO_PIN_12);

	mPWMch1 = PWM_Object1;
	mPWMch2 = PWM_Object2;
	mPWMch3 = PWM_Object3;
	mPWMch4 = PWM_Object4;

    PWM_Object4.f2Duty(0.9);

    //ADC Start
    LL_ADC_Enable( ADC1 );
    LL_ADC_Enable( ADC2 );
    LL_ADC_Enable( ADC3 );
    /* ADC1 Injected conversions end interrupt enabling */
    LL_ADC_ClearFlag_JEOS( ADC1 );
    LL_ADC_EnableIT_JEOS( ADC1 );

}

void MotorCtrl::InitMotorInfo(void) {

	{
		ArgCtrl ArgCtrl; //角度を求める機能を持ったclass
		ArgCtrl.Init();
		mArgCtrl = ArgCtrl;
	}
//	{
//		TimInfo Tim_Info;//タイマの経過時間測定Class
//		Tim_Info.Init(TIM1);
//		mMotorInfo.setTimInfo(Tim_Info);
//	}
	{//PIDLibの生存時間調整(代入後メモリを解放する)
		PID IdPID;
		PID IqPID;
		IdPID.SetParam(PID_GAIN_ID_P, PID_GAIN_ID_I, PID_GAIN_ID_D);
		IqPID.SetParam(PID_GAIN_IQ_P, PID_GAIN_IQ_I, PID_GAIN_IQ_D);
		mIdPID = IdPID;
		mIqPID = IqPID;
		//mMotorInfo.setIdqPIDLib(IdPID, IqPID);
		//mMotorInfo.setIganmadeltaPIDLib(IganmaPID, IdeltaPID);
	}
}

void MotorCtrl::InitObserver(void) {

	{
		Observer Observer; //オブザーバのInit
		Observer.InitEMFObs(OBSERVER_CYCLE_TIME, M_PARAM_R, M_PARAM_LD, M_PARAM_LQ, OBSERVER_GAIN_G1, OBSERVER_GAIN_ALPHA);
		Observer.InitPII2(OBSERVER_CYCLE_TIME, OBSERVER_GAIN_K1, OBSERVER_GAIN_K2, OBSERVER_GAIN_K3);
		mObserver = Observer;
	}
}



void MotorCtrl::HighFreqTask(void) {
	LL_GPIO_SetOutputPin(GPIOA, GPIO_PIN_5);


	//エンコーダ読み取り
	float Iu,Iv,Iw;
	//増幅率のバイアス考慮してない。あとで計算すること。
	Iu = LL_ADC_INJ_ReadConversionData12(ADC1, LL_ADC_INJ_RANK_1);
	Iv = LL_ADC_INJ_ReadConversionData12(ADC1, LL_ADC_INJ_RANK_2);
	Iw = LL_ADC_INJ_ReadConversionData12(ADC1, LL_ADC_INJ_RANK_3);
//		Iu = LL_ADC_INJ_ReadConversionData12(ADC1, LL_ADC_INJ_RANK_1)/4095;
//		Iv = LL_ADC_INJ_ReadConversionData12(ADC1, LL_ADC_INJ_RANK_2)/4095;
//		Iw = LL_ADC_INJ_ReadConversionData12(ADC1, LL_ADC_INJ_RANK_3)/4095;
	setIuvw(Iu, Iv, Iw);

		//推定誤差計算

		//推定位置計算(センサを叩く)
		//Motor.culcArg();

	ForceCommutation();

	//Iuvw -> Iab
	clarkTransform();
	//Iab -> Idq
	parkTransform();
	//Idq -> Igd
	parkGanmaDelta();

	//オブザーバセット・計算・値取得
	mObserver.SetIGanmaDelta(mMotorInfo.mIgd);
	mObserver.SetVGanmaDelta(mMotorInfo.mVgd);
	mObserver.Calculate();
	float EstArgE = mObserver.GetEstTheta();

	std::array<float, 2> Idq = getIdq();
	float Id, Iq;//あとで使う　今は未使用だからエラー吐くはず。
	Id = Idq.at(0);
	Iq = Idq.at(1);


	//指令値入力
	//本当はここをpIdqTargetにして入力にする
	//float Vd_input = 0;
	//float Vq_input = 0.5f;

	float Vganma_input = 0;
	float Vdelta_input = 0;

	float Id_error;
	float Iq_error;

	float Id_target;
	float Iq_target;

	Id_target = 0;
	Iq_target = 0;//ここに目標値を入れる(外部から入れるからSetter必要かも)

	Id_error = Id_target - Id;
	Iq_error = Iq_target - Iq;

	std::array<float, 2> IdqErr = {Id_error, Iq_error};
	//Id,IqのPID制御

	//第二引数に制御周期を入力する。これも計算で出すか、パラメタとして入力すること
	PIDdq_control(IdqErr, 0.1);

	//IO入力?
	LL_ADC_REG_StartConversionSWStart(ADC2);
	float adc2_input = (float)LL_ADC_REG_ReadConversionData12(ADC2)/4095;

	//Vq_input = 0;
	//Vd_input = adc_speed;//連れ回し運転

	Vganma_input = adc2_input;//連れ回し運転
	Vdelta_input = 0;

	std::array<float, 2> inputVgd = {Vganma_input,Vdelta_input};
	setVgd(inputVgd);

	//Vgd -> Vdq
	invParkGanmaDelta();
	//Vdq -> Vab
	invParkTransform();
	//Vab -> Vuvw
	invClarkTransform();
	//PWM出力
	MotorOutputTask();

	{
		//SEGGER RTT DEBUG
		int adc_u = (int)Iu;
		int adc_v = (int)Iv;
		int adc_w = (int)Iw;

		//
//		char str[8];
//		float val = 2.334563;
//		sprintf(str, "%f", val);
		//SEGGER_RTT_printf(0, "val = %s\n", str);

		char* str2 = "2.334563";
		SEGGER_RTT_printf(0, "adcVal:%d,%d,%d,%s\n" ,adc_u, adc_v, adc_w, str2);
	}
	if(DEBUG_MODE){//デバッグモードで入る処理
		//DebugTask(mMotorInfo.mArg, mMotorInfo.mArgErr, mMotorInfo.mIuvw, mMotorInfo.mIab, mMotorInfo.mIdq, mMotorInfo.mIgd);
	}
	LL_GPIO_ResetOutputPin(GPIOA, GPIO_PIN_5);
}

void MotorCtrl::MotorOutputTask(void){
	mPWMch1.f2Duty(mMotorInfo.mVuvw.at(0));
	mPWMch2.f2Duty(mMotorInfo.mVuvw.at(1));
	mPWMch3.f2Duty(mMotorInfo.mVuvw.at(2));
}

//Motor
void MotorCtrl::setIuvw(float pIu, float pIv, float pIw){
	mMotorInfo.mIuvw.at(0) = pIu;
	mMotorInfo.mIuvw.at(1) = pIv;
	mMotorInfo.mIuvw.at(2) = pIw;
}

void MotorCtrl::ForceCommutation(void) {
	if(mUIStatus.mStartStopTRG) {
	mArgCtrl.FCacceleration();
	} else {
	mArgCtrl.FCdeceleration();
	}
	mMotorInfo.mArg = mArgCtrl.getArg();
	mMotorInfo.mArgErr = mArgCtrl.getArgErr(); //回転方向より符号は反転する
}

void MotorCtrl::clarkTransform(void) {
	std::array<float, 3> Iuvw = mMotorInfo.mIuvw;
	std::array<float, 3> Vuvw = mMotorInfo.mVuvw;
	std::array<float, 2> Iab = MotorMath::clarkTransform(Iuvw);
	std::array<float, 2> Vab = MotorMath::clarkTransform(Vuvw);
	mMotorInfo.mIab = Iab;
	mMotorInfo.mVab = Vab;
}

void MotorCtrl::parkTransform(void) {
	fp_rad Arg = mMotorInfo.mArg;
	std::array<float, 2> Iab = mMotorInfo.mIab;
	std::array<float, 2> Vab = mMotorInfo.mVab;
	std::array<float, 2> Idq = MotorMath::parkTransform(Arg, Iab);
	std::array<float, 2> Vdq = MotorMath::parkTransform(Arg, Vab);
	mMotorInfo.mIdq = Idq;
	mMotorInfo.mVdq = Vdq;
}

void MotorCtrl::parkGanmaDelta(void) {
	fp_rad ArgErr = mMotorInfo.mArgErr;
	std::array<float, 2> Idq = mMotorInfo.mIdq;
	std::array<float, 2> Vdq = mMotorInfo.mVdq;
	fp_rad InvArgErr = -1.0f * ArgErr;
	std::array<float, 2> Igd = MotorMath::parkTransform(InvArgErr, Idq);
	std::array<float, 2> Vgd = MotorMath::parkTransform(InvArgErr, Vdq);
	mMotorInfo.mIgd = Igd;
	mMotorInfo.mVgd = Vgd;
}

std::array<float, 2> MotorCtrl::getIdq() {
	return mMotorInfo.mIdq;
}

std::array<float, 2> MotorCtrl::getIgd() {
	return mMotorInfo.mIgd;
}

void MotorCtrl::PIDdq_control(std::array<float, 2> pErrIdq, float pTime) {
	float ErrId = pErrIdq.at(0);
	float ErrIq = pErrIdq.at(1);
	mIdPID.ErrorAndTimeUpdate(ErrId, pTime);
	mIqPID.ErrorAndTimeUpdate(ErrIq, pTime);

	float Vd = mMotorInfo.mVdq.at(0);
	float Vq = mMotorInfo.mVdq.at(1);

	Vd = Vd + mIdPID.OutPut();
	Vq = Vq + mIqPID.OutPut();
	mMotorInfo.mVdq = {Vd, Vq};
}

void MotorCtrl::PIDgd_control(std::array<float, 2> pErrIgd, float pTime) {
	{
		float ErrIganma = pErrIgd.at(0);
		float ErrIdelta = pErrIgd.at(1);
		mIganmaPID.ErrorAndTimeUpdate(ErrIganma, pTime);
		mIdeltaPID.ErrorAndTimeUpdate(ErrIdelta, pTime);

		float Vganma = mMotorInfo.mVgd.at(0);
		float Vdelta = mMotorInfo.mVgd.at(1);

		Vganma = Vganma + mIganmaPID.OutPut();
		Vdelta = Vdelta + mIdeltaPID.OutPut();
		mMotorInfo.mVgd = {Vganma, Vdelta};
	}
}

void MotorCtrl::setVdq(std::array<float, 2> pVdq) {
	//強制転流用
	mMotorInfo.mVdq = pVdq;
}

void MotorCtrl::setVgd(std::array<float, 2> pVgd) {
	mMotorInfo.mVgd = pVgd;
}

void MotorCtrl::invParkGanmaDelta(void) {
	std::array<float, 2> Vgd = mMotorInfo.mVgd;
	fp_rad ArgErr = mMotorInfo.mArgErr;
	fp_rad InvArgErr = -1.0f * ArgErr;
	std::array<float, 2> Vdq = MotorMath::InvparkTransform(InvArgErr, Vgd);
	mMotorInfo.mVdq = Vdq;
}
void MotorCtrl::invParkTransform(void) {
	fp_rad Arg = mMotorInfo.mArg;
	std::array<float, 2> Vdq= mMotorInfo.mVdq;
	std::array<float, 2> Vab = MotorMath::InvparkTransform(Arg, Vdq);
	mMotorInfo.mVab = Vab;
}

void MotorCtrl::invClarkTransform(void) {
	std::array<float, 2> Vab = mMotorInfo.mVab;
	std::array<float, 3> Vuvw = MotorMath::InvclarkTransform(Vab);
	mMotorInfo.mVuvw = Vuvw;
}


//Debug
void MotorCtrl::DebugTask(float pIu, float pIv, float pIw, float pArg){
	int sw = mDebug.GetDbgStatus();
	switch(sw){
	case 0:
		//if(mMotorInfo.mSensor.GetArgCount() > 24000){
		mDebug.DbgInfoTinyRegister(pIu, pIv, pIw, pArg);
		//mDebug.DbgInfoRegister(pIu, pIv, pIw, pArg);
		//}
		break;
	case 1:
		//止める動作が必要だと思う
		MotorCtrl::BtnActOFF();
		mDebug.SetDebugStatus(2);
		break;
	case 2:
		//止まるのを確認したら次にすすめる
		//if(mMotorInfo.mSensor.GetArgCount() < 10){
			mDebug.SetDebugStatus(3);
		//}
		break;
	case 3:
		mDebug.PrintStatusTiny();
		//mDebug.PrintStatus();
		HAL_Delay(1);
		mDebug.SetDebugStatus(0);
//		//こんな感じで状態遷移の動作をさせればいいのではないでしょうか。
		break;
	default :
		//例外は何もしない
		break;
	}
}


//UICtrl
void MotorCtrl::BtnAct(void){//強制転流開始へのトリガ 割り込みから叩くためにここでラッパする
	if(mUIStatus.mStartStopTRG){
		BtnActOFF();
	} else {
		BtnActON();
	}
}

void MotorCtrl::BtnActOFF(void){//強制転流開始へのトリガOFF
	mUIStatus.mStartStopTRG = MotorStop;
}

void MotorCtrl::BtnActON(void){//強制転流開始へのトリガON
	mUIStatus.mStartStopTRG = MotorStart;
}


////////////////func of debug ///////////////////
void MotorCtrl::DbgUart(std::string pStr) {
	UART::Transmit(pStr);
}



