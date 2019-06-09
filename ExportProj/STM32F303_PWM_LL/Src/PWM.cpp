/*
 * PWM.cpp
 *
 *  Created on: Jun 9, 2019
 *      Author: watashi
 */

#include "PWM.hpp"
#include "stm32f3xx_hal.h"
#include "tim.h"

//#include "stm32f3xx.h"//needless
//#include "stm32f3xx_ll_tim.h"//needless

void PWM::setTIM(TIM_TypeDef* pTIMx){
	mTIMx = pTIMx;
}

void PWM::setCH(__IO uint32_t pCCR){
	mCCR = pCCR;
}

void PWM::Init(){

	if(mTIMx==NULL){//error check
		while(1){}
	}

	LL_TIM_CC_EnableChannel(mTIMx, LL_TIM_CHANNEL_CH1);
	LL_TIM_EnableCounter(mTIMx);
	//LL_TIM_GenerateEvent_UPDATE(TIM1);//
	LL_TIM_EnableAllOutputs(mTIMx);// need

}

void PWM::Duty(int pDuty){
	//P = (D*T)/100;
	//LL_TIM_OC_SetCompareCH1(mTIMx, pDuty);
	WRITE_REG(mTIMx->CCR1, pDuty);
	//WRITE_REG(mTIMx->mCCR, pDuty);
	//LL_TIM_CC_EnableChannel(TIM1, LL_TIM_CHANNEL_CH1);
	//LL_TIM_EnableCounter(TIM1);

	//LL_TIM_EnableAllOutputs(TIM1);

	//TIM_OC_InitStruct.CompareValue = pDuty;
}
