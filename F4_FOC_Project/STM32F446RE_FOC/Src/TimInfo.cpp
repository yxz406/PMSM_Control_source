/*
 * TimInfo.cpp
 *
 *  Created on: Jul 29, 2019
 *      Author: watashi
 */

#include "stm32f4xx_hal.h"
#include "stm32f4xx_ll_adc.h"
#include "stm32f4xx_ll_tim.h"
#include "stm32f4xx.h"
#include "stm32f4xx_ll_system.h"
#include "stm32f4xx_ll_gpio.h"
#include "stm32f4xx_ll_exti.h"
#include "stm32f4xx_ll_bus.h"
#include "stm32f4xx_ll_cortex.h"
#include "stm32f4xx_ll_rcc.h"
#include "stm32f4xx_ll_utils.h"
#include "stm32f4xx_ll_pwr.h"
#include "stm32f4xx_ll_dma.h"

#include "TimInfo.hpp"


TimInfo::TimInfo() {
	// TODO Auto-generated constructor stub

}

TimInfo::~TimInfo() {
	// TODO Auto-generated destructor stub
}

void TimInfo::Init(TIM_TypeDef *pTIMx) {

	if(pTIMx == NULL) {
		//null ptr error
		while(1){}
	}

	mReload = 0;
	mStartTime = 0;
	mStopTime = 0;

	mTIMx = pTIMx;
	mReload = LL_TIM_GetAutoReload(pTIMx);

}

void TimInfo::StartTimMesure(void) {
	mStartTime = LL_TIM_GetCounter(mTIMx);
}

void TimInfo::StopTimMesure(void) {
	mStopTime = LL_TIM_GetCounter(mTIMx);
}

int TimInfo::CalcTime(void) {
	int timdelta;
	timdelta = mStartTime - mStopTime;

	mStartTime = 0;
	mStopTime = 0;

	return timdelta;
}
