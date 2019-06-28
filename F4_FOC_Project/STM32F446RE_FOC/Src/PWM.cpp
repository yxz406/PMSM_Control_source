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
 */


#include "PWM.hpp"
#include "stm32f4xx_hal.h"
#include "tim.h"

void PWM::setTIM(TIM_TypeDef* pTIMx){
	mTIMx = pTIMx;
}

//void PWM::setCH(__IO uint32_t pCCR);

void PWM::setCH(int pCH){
	mCH = pCH;
}

void PWM::Init(){

	if(mCH==0){//error check
		while(1){}
	}

	//mREG Init
	if (mCH == 1){
		mREG=&(mTIMx->CCR1);
	}
	if (mCH == 2){
		mREG=&(mTIMx->CCR2);
	}
	if (mCH == 3){
		mREG=&(mTIMx->CCR3);
	}
	if (mCH == 4){
		mREG=&(mTIMx->CCR4);
	}

	if(mREG==NULL){//error check
		while(1){}
	}
	//mREG Init end

	//PWM Channel Init
	if(mTIMx==NULL){//error check
		while(1){}
	}
	if (mCH == 1){
		LL_TIM_CC_EnableChannel(mTIMx, LL_TIM_CHANNEL_CH1);
	}
	if (mCH == 2){
		LL_TIM_CC_EnableChannel(mTIMx, LL_TIM_CHANNEL_CH2);
	}
	if (mCH == 3){
		LL_TIM_CC_EnableChannel(mTIMx, LL_TIM_CHANNEL_CH3);
	}
	if (mCH == 4){
		LL_TIM_CC_EnableChannel(mTIMx, LL_TIM_CHANNEL_CH4);
	}
	//PWM Channel Init end

	//PWM TIM Init
	LL_TIM_EnableCounter(mTIMx);
	//LL_TIM_GenerateEvent_UPDATE(TIM1);//
	LL_TIM_EnableAllOutputs(mTIMx);// need
	//PWM TIM Init end

}

void PWM::fInit(int pTimReload){

	mTimReload = pTimReload;

	if(mCH==0){//error check
		while(1){}
	}

	//mREG Init
	if (mCH == 1){
		mREG=&(mTIMx->CCR1);
	}
	if (mCH == 2){
		mREG=&(mTIMx->CCR2);
	}
	if (mCH == 3){
		mREG=&(mTIMx->CCR3);
	}
	if (mCH == 4){
		mREG=&(mTIMx->CCR4);
	}

	if(mREG==NULL){//error check
		while(1){}
	}
	//mREG Init end

	//PWM Channel Init
	if(mTIMx==NULL){//error check
		while(1){}
	}
	if (mCH == 1){
		LL_TIM_CC_EnableChannel(mTIMx, LL_TIM_CHANNEL_CH1);
	}
	if (mCH == 2){
		LL_TIM_CC_EnableChannel(mTIMx, LL_TIM_CHANNEL_CH2);
	}
	if (mCH == 3){
		LL_TIM_CC_EnableChannel(mTIMx, LL_TIM_CHANNEL_CH3);
	}
	if (mCH == 4){
		LL_TIM_CC_EnableChannel(mTIMx, LL_TIM_CHANNEL_CH4);
	}
	//PWM Channel Init end

	//PWM TIM Init
	LL_TIM_EnableCounter(mTIMx);

	//auto reload Init
	LL_TIM_SetAutoReload(mTIMx, pTimReload);

	//LL_TIM_GenerateEvent_UPDATE(TIM1);//
	LL_TIM_EnableAllOutputs(mTIMx);// need
	//PWM TIM Init end

}



void PWM::Duty(int pDuty){
	WRITE_REG(*mREG, pDuty);
}


void PWM::fDuty(float pfDuty){
	int pDuty = pfDuty * (float)mTimReload;
	WRITE_REG(*mREG, pDuty);
}

void PWM::f2Duty(float pfDuty){
	int pDuty = (pfDuty + 1)/2 * (float)mTimReload;
	WRITE_REG(*mREG, pDuty);
}
