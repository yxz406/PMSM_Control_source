/*
 * MotorCtrl.cpp
 *
 *  Created on: Aug 5, 2019
 *      Author: watashi
 */

#include "MotorCtrl.hpp"

#define DEBUG_CUT

MotorCtrl::MotorCtrl() {
	// TODO Auto-generated constructor stub

}

MotorCtrl::~MotorCtrl() {
	// TODO Auto-generated destructor stub
}

void MotorCtrl::InitSystem(void) {
	//以下CubeMXに頼らない定義たち
	//mainで既に定義されているとうまく動かないから、Mainで定義する前に呼び出すこと。
//	GPIOInit::Init();//これめんどい
//	USARTInit::Init();//これめんどい


	//Timer Initialize
	TIMCtrl::MX_TIM1_Init();

	TIMCtrl::MotorDuty_ch1(0);//50%duty
	TIMCtrl::MotorDuty_ch2(0);
	TIMCtrl::MotorDuty_ch3(0);
	//TIMCtrl::MotorDuty_ch4(0.9);//9割タイミングで打つ
	TIMCtrl::TIM1SetCOMP_ch4(PWM_PERIOD_COUNT - 1);

	//ENABLE信号
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_SET);

	TIMCtrl::TIM1PWMStart();

	//ADC Initialize
	ADCCtrl::ADC2Init_HAL();
	ADCCtrl::ADC2Calibration();

	ADCCtrl::ADC3Init_HAL();
	ADCCtrl::ADC3Calibration();
	ADCCtrl::ADC3InjectedStart_IT();
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
		IdPID.SetSampleTime(PID_CONTROL_CYCLE);
		IqPID.SetSampleTime(PID_CONTROL_CYCLE);
		mIdPID = IdPID;
		mIqPID = IqPID;
	}
}

void MotorCtrl::InitObserver(void) {

	{
		Observer Observer; //オブザーバのInit
		Observer.InitEMFObs(OBSERVER_CYCLE_TIME, M_PARAM_R, M_PARAM_LD, M_PARAM_LQ, OBSERVER_GAIN_ALPHA);
		Observer.InitPII2(OBSERVER_CYCLE_TIME, OBSERVER_GAIN_K1, OBSERVER_GAIN_K2, OBSERVER_GAIN_K3);
		mObserver = Observer;
	}
}



void MotorCtrl::HighFreqTask(void) {
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);

	//開始直後にADC2を読み取って、変換時間を演算処理の中で相殺する。
	ADCCtrl::ADC2Start_Conversion();
	//ADCCtrl::ADC2Conversion_wait(10);

	//エンコーダ読み取り
	float Iu,Iv,Iw;
	//増幅率のバイアス考慮してない。あとで計算すること。
	Iu = (float)ADCCtrl::ADC3_INJ_Read_ch1() * BOARD_IV_RATIO * ADC_VOLTAGE_RATIO + BOARD_IV_OFFSET;
	Iv = (float)ADCCtrl::ADC3_INJ_Read_ch2() * BOARD_IV_RATIO * ADC_VOLTAGE_RATIO + BOARD_IV_OFFSET;
	Iw = (float)ADCCtrl::ADC3_INJ_Read_ch3() * BOARD_IV_RATIO * ADC_VOLTAGE_RATIO + BOARD_IV_OFFSET;
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


	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
	asm("NOP");
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);

	//オブザーバセット・計算・値取得
	mObserver.SetIGanmaDelta(mMotorInfo.mIgd);
	mObserver.SetVGanmaDelta(mMotorInfo.mVgd);
	//mObserver.Calculate();
	mObserver.CalculateForceCom( mArgCtrl.getArgOmega() );//強制転流中はこっち。


	float EstArgE = mObserver.GetEstTheta();

	//デバッグ用推定加速度取得
	float EstOmegaE = mObserver.GetEstOmegaE();

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
	PIDdq_control(IdqErr);

	//IO入力
	float adc2_input = (float)ADCCtrl::ADC2_Read() / 65535;
	//Vq_input = 0;
	//Vd_input = adc_speed;//連れ回し運転

	Vganma_input = adc2_input;//連れ回し運転
	Vdelta_input = 0;

	//ADC2つないでないから処置
	//Vganma_input = 0.5;


	std::array<float, 2> inputVgd = {Vganma_input,Vdelta_input};
	setVgd(inputVgd);

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
	asm("NOP");
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);


	//Vgd -> Vdq
	invParkGanmaDelta();
	//Vdq -> Vab
	invParkTransform();
	//Vab -> Vuvw
	invClarkTransform();
	//PWM出力

	MotorOutputTask();

	//DEBUG
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);

	if(DEBUG_MODE){//デバッグモードで入る処理
		JLinkDebug();
	}

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);//ループ終了のアレ
	asm("NOP");

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
}

void MotorCtrl::MotorOutputTask(void){
	TIMCtrl::MotorDuty_ch1(mMotorInfo.mVuvw.at(0));
	TIMCtrl::MotorDuty_ch2(mMotorInfo.mVuvw.at(1));
	TIMCtrl::MotorDuty_ch3(mMotorInfo.mVuvw.at(2));
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

void MotorCtrl::PIDdq_control(std::array<float, 2> pErrIdq) {
	float ErrId = pErrIdq.at(0);
	float ErrIq = pErrIdq.at(1);
	mIdPID.ErrorUpdate(ErrId);
	mIqPID.ErrorUpdate(ErrIq);

	float Vd = mMotorInfo.mVdq.at(0);
	float Vq = mMotorInfo.mVdq.at(1);

	Vd = Vd + mIdPID.OutPut();
	Vq = Vq + mIqPID.OutPut();
	mMotorInfo.mVdq = {Vd, Vq};
}

void MotorCtrl::PIDgd_control(std::array<float, 2> pErrIgd) {
	{
		float ErrIganma = pErrIgd.at(0);
		float ErrIdelta = pErrIgd.at(1);
		mIganmaPID.ErrorUpdate(ErrIganma);
		mIdeltaPID.ErrorUpdate(ErrIdelta);

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


void MotorCtrl::JLinkDebug() {

//		char str1[10];
//		char str2[10];
//		char str3[10];

//		sprintf(str1, "%f", val1);
//		sprintf(str2, "%f", val2);
//		sprintf(str3, "%f", val3);

	int milIu = (int)( mMotorInfo.mIuvw.at(0) * 1000 );
	int milIv = (int)( mMotorInfo.mIuvw.at(1) * 1000 );
	int milIw = (int)( mMotorInfo.mIuvw.at(2) * 1000 );

	int DegArg = (int)(mMotorInfo.mArg/M_PI * 180 );//指令値の角度

	int DeggdArg = (int)(mMotorInfo.mArgErr/M_PI * 180 ); //現在使ってない

	int DegEstArg = (int)(mObserver.GetEstTheta() /M_PI * 180 );//オブザーバ
	int DegEstOmega = (int)( mObserver.GetEstOmegaE() /M_PI * 180 );

	int DegOmega = (int)( mArgCtrl.getArgOmega() /M_PI *180 );

	if( !mUIStatus.mStartStopTRG ) {//加速してるときだけ入る ACCEL
		return;
	}

#ifdef DEBUG_CUT
		//回数を絞る
		if(mDebugC > 10) {
			SEGGER_RTT_printf(0, "%d,%d,%d,%d,%d,%d,%d\n" ,milIu, milIv, milIw, DegArg, DegEstArg, DegEstOmega, DegOmega);
			mDebugC =0;
		}
		mDebugC++;
#else
		SEGGER_RTT_printf(0, "%d,%d,%d,%d,%d,%d\n" ,milIu, milIv, milIw, milArgdeg, milArggddeg, milIEstArg);
#endif

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
	//UART::Transmit(pStr);
}


