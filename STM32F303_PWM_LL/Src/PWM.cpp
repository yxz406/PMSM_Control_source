/*
 * PWM.cpp
 *
 *  Created on: Jun 9, 2019
 *      Author: watashi
 */

#include "PWM.hpp"
#include "stm32f3xx_hal.h"
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
		mREG=&(mTIMx->CCR3);
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

void PWM::Duty(int pDuty){
	WRITE_REG(*mREG, pDuty);
}
