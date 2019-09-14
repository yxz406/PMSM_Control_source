/*
 * PWM.cpp
 *
 *  Created on: Jun 9, 2019
 *      Author: watashi
 */


/*
 * せつめい！
 * PWMを生成するclass
 *
 * 使い方
 * 	PWM PWM_Object;
 * 	PWM_Object.setTIM(TIM1);
 * 	PWM_Object.setCH(1);
 *  PWM_Object.Init();
 *  PWM_Object.Duty(60000);
 *
 *
 *  HALに変更
 *  TIM_HandleTypeDef *htim1;
 *  PWM PWM_Object;
 *  PWM_Object.setTIM(htim1);
 *  PWM_Object.setCH(ch1);
 *  ...あとはおなじ
 */


#include "PWM.hpp"


void PWM::setTIM(TIM_HandleTypeDef* phtim) {
	mhtim = phtim;
}

//void PWM::setCH(__IO uint32_t pCCR);

void PWM::setCH(PWMch pCH) {
	mCH = pCH;
}

void PWM::Init(){
	//PWM Channel Init
	if(mhtim){//error check
		//while(1){}//err handle else でとばしてもいいかも。
		HAL_TIM_Base_Start_IT(mhtim);
		HAL_TIM_PWM_Start(mhtim, mCH);

	}
}

void PWM::fInit(int pTimReload){
	mTimReload = pTimReload;
	Init();
}

void PWM::Duty(int pDuty){
	//WRITE_REG(*mREG, pDuty);
	__HAL_TIM_SET_COMPARE(mhtim, mCH, pDuty);
}


void PWM::fDuty(float pfDuty){
	int duty = pfDuty * (float)mTimReload;
	Duty(duty);
}

void PWM::f2Duty(float pfDuty){
	int duty = (pfDuty + 1)/2 * (float)mTimReload;
	Duty(duty);
}

void PWM::Disable(void){
	if(mhtim){//error check
	HAL_TIM_PWM_Stop(mhtim, mCH);
	}
}
