/*
 * wrapper.cpp
 *
 *  Created on: Jun 17, 2019
 *      Author: watashi
 */

#include "stm32f4xx_hal.h"
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

#include <vector>
#include "math.h"

#include "wrapper.hpp"
#include "LedBlink.hpp"
#include "PWM.hpp"

void vectorInit(std::vector<int> *pVector);//プロトタイプ宣言
void ADCReInit(void);

void cpploop(void) {
    LedBlink instance;
    instance.toggle();
}

void cppwrapper(void){
	std::vector<int> num;
	vectorInit(&num);

	PWM PWM_Object1;
	PWM PWM_Object2;
	PWM PWM_Object3;
	PWM PWM_Object4;

	PWM_Object1.setTIM(TIM1);
	PWM_Object2.setTIM(TIM1);
	PWM_Object3.setTIM(TIM1);
	PWM_Object4.setTIM(TIM1);

	PWM_Object1.setCH(1);
	PWM_Object2.setCH(2);
	PWM_Object3.setCH(3);
	PWM_Object4.setCH(4);

	PWM_Object1.Init();
	PWM_Object2.Init();
	PWM_Object3.Init();
	PWM_Object4.Init();


	PWM_Object1.Duty(60000);
	PWM_Object2.Duty(60000);
	PWM_Object3.Duty(60000);
	PWM_Object4.Duty(60000);
}

void HighFreqTask(void){
//	uint16_t adc_data1 = 0, adc_data2 = 0, adc_data3 = 0, adc_data4 = 0;
//	if (LL_ADC_IsActiveFlag_JEOS(ADC1) == 1)
//		{
//			LL_ADC_ClearFlag_JEOS(ADC1);
//			adc_data1 = LL_ADC_INJ_ReadConversionData12(ADC1, LL_ADC_INJ_RANK_1);
//			adc_data2 = LL_ADC_INJ_ReadConversionData12(ADC1, LL_ADC_INJ_RANK_2);
//			adc_data3 = LL_ADC_INJ_ReadConversionData12(ADC1, LL_ADC_INJ_RANK_3);
//		}
//	else
//		{
//			LL_ADC_WriteReg(ADC1,ISR,0);
//		}
}


void vectorInit(std::vector<int> *pVector){
	int lange;
	lange = 600;
	int count = 65535;
	for(int i=0;i<lange;i++){
		float fsinval = sin(i*2*M_PI/(float)lange);
		int val = count/2 * fsinval + count/2;
		pVector->push_back(val);
	}
}


