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

void MotorCtrl::SetMotorInfo(MotorInfo pMotorInfo) {
	mMotorInfo = pMotorInfo;
}

void MotorCtrl::SetPWMch1(PWM pPWM) {
	mPWMch1 = pPWM;
}

void MotorCtrl::SetPWMch2(PWM pPWM) {
	mPWMch2 = pPWM;
}

void MotorCtrl::SetPWMch3(PWM pPWM) {
	mPWMch3 = pPWM;
}

void MotorCtrl::SetPWMch4(PWM pPWM) {
	mPWMch4 = pPWM;
}

void MotorCtrl::InitSystem(void) {
	//以下CubeMXに頼らない定義たち
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

	PWM_Object1.fInit(PWM_COUNT);
	PWM_Object2.fInit(PWM_COUNT);
	PWM_Object3.fInit(PWM_COUNT);
	PWM_Object4.fInit(PWM_COUNT);

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

	//ADC Start
    LL_ADC_Enable( ADC1 );
    LL_ADC_Enable( ADC2 );
    LL_ADC_Enable( ADC3 );
    /* ADC1 Injected conversions end interrupt enabling */
    LL_ADC_ClearFlag_JEOS( ADC1 );
    LL_ADC_EnableIT_JEOS( ADC1 );
}

void MotorCtrl::InitMotorInfo(void) {
	{//MathLibの生存時間調整(メモリ空けてくれ!!)
		MathLib mathlibrary;//三角関数を取得
		int mathlib_size = 512;//ライブラリのサイズを指定
		mathlibrary.fInit(mathlib_size);
		mMotorInfo.setMathLib(mathlibrary);//モータクラスに算術ライブラリを渡す
	}
	{
		ArgSensor sensor; //角度を求める機能を持ったclass
		mMotorInfo.setArgSensor(sensor);
	}
	{
		TimInfo Tim_Info;//タイマの経過時間測定Class
		Tim_Info.Init(TIM1);
		mMotorInfo.setTimInfo(Tim_Info);
	}
	{//PIDLibの生存時間調整(代入後メモリを解放する)
		PID IqPID;
		PID IdPID;
		IdPID.SetParam(PID_GAIN_ID_P, PID_GAIN_ID_I, PID_GAIN_ID_D);
		IqPID.SetParam(PID_GAIN_IQ_P, PID_GAIN_IQ_I, PID_GAIN_IQ_D);
		mMotorInfo.setIdqPIDLib(IdPID, IqPID);
		//mMotorInfo.setIganmadeltaPIDLib(IganmaPID, IdeltaPID);
	}
}

void MotorCtrl::HighFreqTask(void) {
	if (LL_ADC_IsActiveFlag_JEOS(ADC1) == 1)
	{
		LL_ADC_ClearFlag_JEOS(ADC1);
		//エンコーダ読み取り
		float Iu,Iv,Iw;
		//増幅率のバイアス考慮してない。あとで計算すること。
		Iu = LL_ADC_INJ_ReadConversionData12(ADC1, LL_ADC_INJ_RANK_1)/4095;
		Iv = LL_ADC_INJ_ReadConversionData12(ADC1, LL_ADC_INJ_RANK_2)/4095;
		Iw = LL_ADC_INJ_ReadConversionData12(ADC1, LL_ADC_INJ_RANK_3)/4095;
		mMotorInfo.setIuvw(Iu, Iv, Iw);

		//推定誤差計算

		//推定位置計算(センサを叩く)
		//Motor.culcArg();

		mMotorInfo.ForceCommutation();

		//Iuvw -> Idqに変換 (Park,Clark変換)
		mMotorInfo.parkTransform();
		mMotorInfo.clarkTransform();

		float Id, Iq;//あとで使う　今は未使用だからエラー吐くはず。
		Id = mMotorInfo.getId();
		Iq = mMotorInfo.getIq();

		//指令値入力
		//float Vd_input = 0;
		//float Vq_input = 0.5f;

		float Vganma_input = 0;
		float Vdelta_input = 0;

		float Id_error;
		float Iq_error;

		Id_error = 0;
		Iq_error = 0;
		//Id,IqのPID制御

		//Motor.PIDdq_control(Id_error, Iq_error, 0.1);
		//Vd_input = Motor.getVd();
		//Vq_input = Motor.getVq();

		//IO入力?
		LL_ADC_REG_StartConversionSWStart(ADC2);
		float adc2_input = (float)LL_ADC_REG_ReadConversionData12(ADC2)/4095;
		//Vq_input = 0;
		//Vd_input = adc_speed;//連れ回し運転

		Vganma_input = adc2_input;//連れ回し運転
		Vdelta_input = 0;

		mMotorInfo.setVganma(Vganma_input);
		mMotorInfo.setVdelta(Vdelta_input);

		//PWM出力
		MotorOutputTask();

		if(DEBUG_MODE){//デバッグモードで入る処理
			if( (UiCtrl::getState()) && (!mMotorInfo.mSensor.GetIsAccelerating()) ){//起動後停止の確認処理
				MotorCtrl::DebugTask(Iu, Iv, Iw, mMotorInfo.getArgRad());
			}
		}

	}
/*	else
 * 	{
 * 			LL_ADC_WriteReg(ADC1,ISR,0);
 * 				}*/
}

void MotorCtrl::MotorOutputTask(void){
	mMotorInfo.invClarkGanmaDelta();
	mMotorInfo.invClarkTransform();
	mMotorInfo.invParkTransform();

	mPWMch1.f2Duty(mMotorInfo.getVu());
	mPWMch2.f2Duty(mMotorInfo.getVv());
	mPWMch3.f2Duty(mMotorInfo.getVw());
}


void MotorCtrl::DebugTask(float pIu, float pIv, float pIw, float pArg){
	//他のclass内に持って行く時には、UARTとかDebugのクラスを渡さないとダメかも。
	//Wrapperが持つ関数にしてしまうのが一番うまく行くと思った。

	mDebug.SetMotorData(new DebugInfo::SendMotorData(pIu,pIv,pIw,pArg));//デバッグの種類増やしたい時はここで変えてね
	unsigned int VectCount = mDebug.GetVectSize();//Debug用にブチ込んだデータの個数
	if(VectCount < DEBUG_COUNT){
		//モータ停止の動作
		MotorCtrl::BtnActOFF();
		//モータ停止を確認する動作
		if(mMotorInfo.mSensor.getArg() == mMotorInfo.mSensor.getArgOld()){
			//タイマ停止する動作(何回もこれ呼ばれちゃうから)

			mPWMch1.f2Duty(0);//50%duty
			mPWMch2.f2Duty(0);
			mPWMch3.f2Duty(0);
			mPWMch4.f2Duty(0);

			mPWMch1.Disable();
			mPWMch2.Disable();
			mPWMch3.Disable();
			mPWMch4.Disable();
			//UARTで転送する動作
			std::vector<DebugInfo::SendMotorData> vectorbuf = mDebug.GetVect();
			for(const auto& num : vectorbuf){
				std::string strbuf;

				strbuf.append(std::to_string(num.mIu));
				strbuf.append(",");
				strbuf.append(std::to_string(num.mIv));
				strbuf.append(",");
				strbuf.append(std::to_string(num.mIw));
				strbuf.append(",");
				strbuf.append(std::to_string(num.mEArg));
				strbuf.append(",");
#ifdef Debug_alpha_beta //ifdefじゃなくてパラメタのヘッダを持たせるべきか。
				strbuf.append(std::to_string(num.mIalpha));
				strbuf.append(",");
				strbuf.append(std::to_string(num.mIbeta));
				strbuf.append(",");
#endif
				strbuf.append(std::to_string(num.mId));
				strbuf.append(",");
				strbuf.append(std::to_string(num.mIq));
				strbuf.append("/n");
				mUART.Transmit(strbuf);
			}
			//while(1){}//ここで止める？要検討
		}
	}
	//暫定で作る
}



void MotorCtrl::BtnAct(void){//強制転流開始へのトリガ 割り込みから叩くためにここでラッパする
	UiCtrl::BtnToggle(); // ON/OFFのトグルスイッチ　BtnActで書き込み、getStateで状態を読む
	if(UiCtrl::getState()){
		mMotorInfo.startForceCommutation();
	} else {
		mMotorInfo.stopForceCommutation();
	}
}

void MotorCtrl::BtnActOFF(void){//強制転流開始へのトリガOFF 割り込みから叩かないから本来UiCtrlで定義するべき
	UiCtrl::BtnActOFF(); // OFFのスイッチ　BtnActOFFで書き込み、getStateで状態を読む
	mMotorInfo.stopForceCommutation();
}

void MotorCtrl::BtnActON(void){//強制転流開始へのトリガON 予備で作ってある。使うかは不明
	UiCtrl::BtnActON(); // ONのトグルスイッチ　BtnActONで書き込み、getStateで状態を読む
	mMotorInfo.startForceCommutation();
}
