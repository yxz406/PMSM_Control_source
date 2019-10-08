/*
 * MotorCtrl.cpp
 *
 *  Created on: Aug 5, 2019
 *      Author: watashi
 */

//TODO FOCモードの動作が未定義。そのまま回すと死ぬ。決める事。


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
	mDriveMode = ForceCommutation;//動作をまずは強制転流にする。

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

	if(mDriveMode == ForceCommutation) {
		ForceCommutationMode();
	} else if (mDriveMode == FOC) {
		FOCMode();
	}
}

void MotorCtrl::ForceCommutationMode(void) {
	GPIODebugTask();//GPIOからオシロに波形を出力する

	//開始直後にADC2を読み取って、変換時間を演算処理の中で相殺する。
	ADCCtrl::ADC2Start_Conversion();
	//ADCCtrl::ADC2Conversion_wait(10);
	ReadCurrentTask();
	ReadVoltageTask();
	ForceCommutationTask();

	//Iuvw -> Iab
	clarkTransform();
	//Iab -> Igd
	parkabtogd();

	GPIODebugTask();//GPIOからオシロに波形を出力する

	ObserverTaskforFC();

	//PIDTask();

	//IO入力
	float adc2_input = (float)ADCCtrl::ADC2_Read() / 65535;
	float Vganma_input,Vdelta_input;
	Vganma_input = 0;
	Vdelta_input=0;
	Vdelta_input = adc2_input * VCC_VOLTAGE * 0.866;//連れ回し運転
	std::array<float, 2> inputVgd = {Vganma_input,Vdelta_input};
	setVgd(inputVgd);

	GPIODebugTask();//GPIOからオシロに波形を出力する

	//Vgd->Vab
	invParkgdtoab();
	//Vab -> Vuvw
	invClarkTransform();
	//SVM();

	//PWM出力
	MotorOutputTask();

	//DEBUG
	GPIODebugTask();//GPIOからオシロに波形を出力する

	if(DEBUG_MODE){//デバッグモードで入る処理
		JLinkDebug();
	}
	GPIODebugTask();//GPIOからオシロに波形を出力する

}

void MotorCtrl::FOCMode(void) {
	//座標系をどこで制御するのかわからないから、そのままにしておく。
	//Idqを制御してdq軸を中心に動作させるのか、
	//Igdを制御して、Δθで引き戻すのか。

	GPIODebugTask();//GPIOからオシロに波形を出力する

	//開始直後にADC2を読み取って、変換時間を演算処理の中で相殺する。
	ADCCtrl::ADC2Start_Conversion();
	//ADCCtrl::ADC2Conversion_wait(10);
	ReadCurrentTask();
	ReadVoltageTask();

	//Iuvw -> Iab
	clarkTransform();
	//Iab -> Idq
	parkTransform();

	//Iab -> Igd
	parkabtogd();//オブザーバ用にgd軸データも用意する。


	GPIODebugTask();//GPIOからオシロに波形を出力する

	ObserverTaskforFOC();

	//PIDTask();

	//IO入力
	float adc2_input = (float)ADCCtrl::ADC2_Read() / 65535;


	float Vganma_input,Vdelta_input;
	Vganma_input = 0;
	Vdelta_input = adc2_input * VCC_VOLTAGE * 0.866;//連れ回し運転


	std::array<float, 2> inputVgd = {Vganma_input,Vdelta_input};
	setVgd(inputVgd);

	GPIODebugTask();//GPIOからオシロに波形を出力する


//	//Vgd -> Vdq
//	invParkGanmaDelta();
//	//Vdq -> Vab
//	invParkTransform();

	//Vgd->Vab
	invParkgdtoab();

	//Vab -> Vuvw
	//invClarkTransform();
	SVM();

	//PWM出力
	//MotorOutputTask();
	MotorOutputTaskSVM();

	//DEBUG
	GPIODebugTask();//GPIOからオシロに波形を出力する

	if(DEBUG_MODE){//デバッグモードで入る処理
		JLinkDebug();
	}

	GPIODebugTask();//GPIOからオシロに波形を出力する
}

void MotorCtrl::ReadCurrentTask(void) {
	//ReadCurrent
	//エンコーダ読み取り
	float Iu,Iv,Iw;
	//増幅率のバイアス考慮してない。あとで計算すること。
	Iu = (float)ADCCtrl::ADC3_INJ_Read_ch1() * BOARD_IV_RATIO * ADC_VOLTAGE_RATIO + BOARD_IV_OFFSET;
	Iv = (float)ADCCtrl::ADC3_INJ_Read_ch2() * BOARD_IV_RATIO * ADC_VOLTAGE_RATIO + BOARD_IV_OFFSET;
	Iw = (float)ADCCtrl::ADC3_INJ_Read_ch3() * BOARD_IV_RATIO * ADC_VOLTAGE_RATIO + BOARD_IV_OFFSET;
	setIuvw(Iu, Iv, Iw);
}

void MotorCtrl::ReadVoltageTask() {
	//ReadVoltage
	//電圧測定(入力)
	mMotorInfo.mVoltageVCC = VCC_VOLTAGE;
}



void MotorCtrl::MotorOutputTask(void){
	TIMCtrl::MotorDuty_ch1(mMotorInfo.mDutyuvw.at(0));
	TIMCtrl::MotorDuty_ch2(mMotorInfo.mDutyuvw.at(1));
	TIMCtrl::MotorDuty_ch3(mMotorInfo.mDutyuvw.at(2));
}

void MotorCtrl::MotorOutputTaskSVM(void){
	TIMCtrl::floatDuty_ch1(mMotorInfo.mDutyuvw.at(0));
	TIMCtrl::floatDuty_ch2(mMotorInfo.mDutyuvw.at(1));
	TIMCtrl::floatDuty_ch3(mMotorInfo.mDutyuvw.at(2));
}

//Motor
void MotorCtrl::setIuvw(float pIu, float pIv, float pIw){
	mMotorInfo.mIuvw.at(0) = pIu;
	mMotorInfo.mIuvw.at(1) = pIv;
	mMotorInfo.mIuvw.at(2) = pIw;
}

void MotorCtrl::ForceCommutationTask(void) {
	//強制転流では、gd軸を回転させる。
	if(mUIStatus.mStartStopTRG) {
	mArgCtrl.FCacceleration();
	} else {
	mArgCtrl.FCdeceleration();
	}
	mMotorInfo.mgdArg = mArgCtrl.getArg(); //gd軸のみ回す。
	//mMotorInfo.mArgErr = mArgCtrl.getArgErr(); //回転方向より符号は反転する
}

void MotorCtrl::clarkTransform(void) {
	std::array<float, 3> Iuvw = {mMotorInfo.mIuvw.at(0),
											   mMotorInfo.mIuvw.at(1),
											   -mMotorInfo.mIuvw.at(0) - mMotorInfo.mIuvw.at(1)};
	//std::array<float, 3> Vuvw = mMotorInfo.mVuvw;
	std::array<float, 2> Iab = MotorMath::clarkTransform(Iuvw);
	//std::array<float, 2> Vab = MotorMath::clarkTransform(Vuvw);
	mMotorInfo.mIab = Iab;
	//mMotorInfo.mVab = Vab;
}

void MotorCtrl::parkTransform(void) {
	fp_rad dqArg = mMotorInfo.mdqArg;
	std::array<float, 2> Iab = mMotorInfo.mIab;
	//std::array<float, 2> Vab = mMotorInfo.mVab;
	std::array<float, 2> Idq = MotorMath::parkTransform(dqArg, Iab);
	//std::array<float, 2> Vdq = MotorMath::parkTransform(dqArg, Vab);
	mMotorInfo.mIdq = Idq;
	//mMotorInfo.mVdq = Vdq;
}

void MotorCtrl::parkGanmaDelta(void) {
	fp_rad ArgErr = mMotorInfo.mArgErr;
	std::array<float, 2> Idq = mMotorInfo.mIdq;
	//std::array<float, 2> Vdq = mMotorInfo.mVdq;
	fp_rad InvArgErr = -1.0f * ArgErr;
	std::array<float, 2> Igd = MotorMath::parkTransform(InvArgErr, Idq);
	//std::array<float, 2> Vgd = MotorMath::parkTransform(InvArgErr, Vdq);
	mMotorInfo.mIgd = Igd;
	//mMotorInfo.mVgd = Vgd;
}

//optional function
void MotorCtrl::parkabtogd(void) {
	fp_rad gdArg = mMotorInfo.mgdArg;
	std::array<float, 2> Iab = mMotorInfo.mIab;
	//std::array<float, 2> Vab = mMotorInfo.mVab;
	std::array<float, 2> Igd = MotorMath::parkTransform(gdArg, Iab);
	//std::array<float, 2> Vgd = MotorMath::parkTransform(gdArg, Vab);
	mMotorInfo.mIgd = Igd;
	//mMotorInfo.mVgd = Vgd;
}

std::array<float, 2> MotorCtrl::getIdq() {
	return mMotorInfo.mIdq;
}

std::array<float, 2> MotorCtrl::getIgd() {
	return mMotorInfo.mIgd;
}

void MotorCtrl::ObserverTaskforFC() {
	//Observer
	//オブザーバセット・計算・値取得
	mObserver.SetIGanmaDelta(mMotorInfo.mIgd);
	mObserver.SetVGanmaDelta(mMotorInfo.mVgd);
	//mObserver.Calculate();//ベクトル制御用
	mObserver.CalculateForceCom( mArgCtrl.getArgOmega() );//強制転流中はこっち。

	float EstAxiErr = mObserver.GetEstAxiErr();//軸誤差。gdとdqの差。
	mMotorInfo.mArgErr = EstAxiErr;
	mMotorInfo.mdqArg = mMotorInfo.mgdArg + mMotorInfo.mArgErr;
}

void MotorCtrl::ObserverTaskforFOC() {
	//Observer
	//オブザーバセット・計算・値取得
	mObserver.SetIGanmaDelta(mMotorInfo.mIgd);
	mObserver.SetVGanmaDelta(mMotorInfo.mVgd);
	mObserver.Calculate();//ベクトル制御用
	mObserver.CalculateForceCom( mArgCtrl.getArgOmega() );//強制転流中はこっち。

	float EstAxiErr = mObserver.GetEstAxiErr();//軸誤差。gdとdqの差。
	mMotorInfo.mArgErr = EstAxiErr;
	mMotorInfo.mdqArg = mMotorInfo.mgdArg + mMotorInfo.mArgErr;
}

void MotorCtrl::PIDTask() {
	std::array<float, 2> Idq = getIdq();
	float Id, Iq;//あとで使う　今は未使用だからエラー吐くはず。
	Id = Idq.at(0);
	Iq = Idq.at(1);


	//指令値入力
	//本当はここをpIdqTargetにして入力にする
	//float Vd_input = 0;
	//float Vq_input = 0.5f;

//	float Vganma_input = 0;
//	float Vdelta_input = 0;

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

	PIDdq_control(IdqErr);
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

//optional function
void MotorCtrl::invParkgdtoab(void) {
	std::array<float, 2> Vgd = mMotorInfo.mVgd;
	fp_rad gdArg = mMotorInfo.mgdArg;
	std::array<float, 2> Vab = MotorMath::InvparkTransform(gdArg, Vgd);
	mMotorInfo.mVab = Vab;
}

void MotorCtrl::invParkGanmaDelta(void) {
	std::array<float, 2> Vgd = mMotorInfo.mVgd;
	fp_rad ArgErr = mMotorInfo.mArgErr;
	fp_rad InvArgErr = -1.0f * ArgErr;
	std::array<float, 2> Vdq = MotorMath::InvparkTransform(InvArgErr, Vgd);
	mMotorInfo.mVdq = Vdq;
}

void MotorCtrl::invParkTransform(void) {
	fp_rad dqArg = mMotorInfo.mdqArg;
	std::array<float, 2> Vdq= mMotorInfo.mVdq;
	std::array<float, 2> Vab = MotorMath::InvparkTransform(dqArg, Vdq);
	mMotorInfo.mVab = Vab;
}

void MotorCtrl::invClarkTransform(void) {
	std::array<float, 2> Vab = {mMotorInfo.mVab.at(0)/mMotorInfo.mVoltageVCC,
											  mMotorInfo.mVab.at(1)/mMotorInfo.mVoltageVCC};
	std::array<float, 3> Vuvw = MotorMath::InvclarkTransform(Vab);
	mMotorInfo.mDutyuvw = Vuvw;
}

void MotorCtrl::SVM(void) {
	float Va = mMotorInfo.mVab.at(0);
	float Vb = mMotorInfo.mVab.at(1);

	bool sector0 = ( (Va*Va)>(Vb*Vb/3) ) && (Va>=0) && (Vb>=0);
	bool sector5 = ( (Va*Va)>(Vb*Vb/3) ) && (Va<0) && (Vb>0);

	bool sector1 = ( (Va*Va)<=(Vb*Vb/3) ) && (Vb>=0);//Va=Vb=0はここに入る
	bool sector4 = ( (Va*Va)<=(Vb*Vb/3) ) && (Vb<0);

	bool sector2 = ( (Va*Va)>(Vb*Vb/3) ) && (Va<0) && (Vb>0);
	bool sector3 = ( (Va*Va)>(Vb*Vb/3) ) && (Va<=0) && (Vb<=0);

	int svmflag = ( sector0 | sector1<<1 | sector2 <<2 | sector3 <<3 | sector4 <<4 | sector5 <<5 );

	float cot60 = 1/sqrt(3);
	float cosec60 = 2/sqrt(3);
	float coefficient = sqrt(3.0f/2.0f);
	float Du, Dv, Dw;
	float D0, D1, D2, D3, D4, D5, D6, D7;
	switch(svmflag) {
	case 1://sector0
		D1 = coefficient * (Va - cot60*Vb ) / mMotorInfo.mVoltageVCC;
		D2 = coefficient * (cosec60 * Vb) / mMotorInfo.mVoltageVCC;
		D0 = (1-( D1 + D2 ))/2;
		D7 = (1-( D1 + D2 ))/2;

		Du = D1 + D2 + D7;
		Dv = D2 + D7;
		Dw = D7;
		break;
	case 2://sector1
		D3 = coefficient * (-Va + cot60*Vb ) / mMotorInfo.mVoltageVCC;
		D2 = coefficient * (Va + cot60*Vb ) / mMotorInfo.mVoltageVCC;
		D0 = (1-( D2 + D3 ))/2;
		D7 = (1-( D2 + D3 ))/2;
		Du = D2 + D7;
		Dv = D2 + D3 + D7;
		Dw = D7;
		break;
	case 4://sector2
		D3 = coefficient * (cosec60 * Vb) / mMotorInfo.mVoltageVCC;
		D4 = coefficient * (-Va - cot60*Vb ) / mMotorInfo.mVoltageVCC;
		D0 = (1-( D3 + D4 ))/2;
		D7 = (1-( D3 + D4 ))/2;
		Du = D7;
		Dv = D3 + D4 + D7;
		Dw = D4 + D7;
		break;
	case 8://sector3
		D5 = coefficient * (cosec60 * Vb) / mMotorInfo.mVoltageVCC;
		D4 = coefficient * (-Va + cot60*Vb ) / mMotorInfo.mVoltageVCC;
		D0 = (1-( D4 + D5 ))/2;
		D7 = (1-( D4 + D5 ))/2;
		Du = D7;
		Dv = D4 + D7;
		Dw = D4 + D5 + D7;
		break;
	case 16://sector4
		D5 = coefficient * (-Va - cot60*Vb ) / mMotorInfo.mVoltageVCC;
		D6 = coefficient * (Va - cot60*Vb ) / mMotorInfo.mVoltageVCC;
		D0 = (1-( D5 + D6 ))/2;
		D7 = (1-( D5 + D6 ))/2;
		Du = D6 + D7;
		Dv = D7;
		Dw = D5 + D6 + D7;
		break;
	case 32://sector5
		D1 = coefficient * (Va + cot60*Vb ) / mMotorInfo.mVoltageVCC;
		D6 = coefficient * (cosec60 * Vb) / mMotorInfo.mVoltageVCC;
		D0 = (1-( D1 + D6 ))/2;
		D7 = (1-( D1 + D6 ))/2;
		Du = D1 + D6 + D7;
		Dv = D7;
		Dw = D6 + D7;
		break;
	default:
		Du = 0.5f;
		Dv = 0.5f;
		Dw = 0.5f;
		break;
	}

	mMotorInfo.mDutyuvw.at(0) = Du;
	mMotorInfo.mDutyuvw.at(1) = Dv;
	mMotorInfo.mDutyuvw.at(2) = Dw;
}

void MotorCtrl::GPIODebugTask() {//Lチカでタイミングをオシロで見る
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
	asm("NOP");
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
}

void MotorCtrl::JLinkDebug() {

	//int milIu = (int)( mMotorInfo.mIuvw.at(0) * 1000 );
	//int milIv = (int)( mMotorInfo.mIuvw.at(1) * 1000 );
	//int milIw = (int)( mMotorInfo.mIuvw.at(2) * 1000 );
	int DegArg = (int)(mMotorInfo.mgdArg/M_PI * 180 );//指令値の角度
	int DegAxiErr =(int)( mObserver.GetEstAxiErr() / M_PI *180 );

	int milIa = (int)( mMotorInfo.mIab.at(0) * 1000 );
	int milIb = (int)( mMotorInfo.mIab.at(1) * 1000 );

	int milIg = (int)( mMotorInfo.mIgd.at(0) * 1000 );
	int milId = (int)( mMotorInfo.mIgd.at(1) * 1000 );

	int milVg = (int)( mMotorInfo.mVgd.at(0) * 1000 );
	int milVd = (int)( mMotorInfo.mVgd.at(1) * 1000 );

	if( !mUIStatus.mStartStopTRG ) {//加速してるときだけ入る ACCEL
		return;
	}
		//SEGGER_RTT_printf(0, "%d,%d,%d,%d,%d,%d\n" ,mlogcount,milIu, milIv, milIw, DegArg,DegAxiErr);　//uvwを観測するバージョン
		SEGGER_RTT_printf(0, "%d,%d,%d,%d,%d,%d,%d,%d,%d\n" ,mlogcount, milIa, milIb, milIg, milId, milVg, milVd, DegArg, DegAxiErr);//gdなどを観測するバージョン
		mlogcount++;
		if(	mlogcount > 65535){
			mlogcount=0;
		}

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


