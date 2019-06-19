/*
 * wrapper.cpp
 *
 *  Created on: Jun 17, 2019
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

#include <vector>
#include "math.h"

#include "wrapper.hpp"
#include "LedBlink.hpp"
#include "PWM.hpp"



uint16_t adc_data1 = 0, adc_data2 = 0, adc_data3 = 0, adc_data4 = 0;

void vectorInit(std::vector<int> *pVector);//プロトタイプ宣言
void ADCReInit(void);
void ADC_Init(void);

void cpploop(void) {
    LedBlink instance;
    instance.toggle();
}

void cppwrapper(void){
	std::vector<int> num;
	vectorInit(&num);

    ADC_Init();

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

	while(1){
		  for(int i=0;i<600;i++){
			  HAL_Delay(1);
			  PWM_Object1.Duty(num[i]);
			  PWM_Object2.Duty(num[(i+200)%600]);
			  PWM_Object3.Duty(num[(i+400)%600]);

			  HAL_Delay(1);//ここにブレークポイント打ってADCの値が見える
/*			  if (LL_ADC_IsEnabled(ADC1) == 1)
			  {
			    LL_ADC_REG_StartConversionExtTrig(ADC1, LL_ADC_REG_TRIG_EXT_RISING);
			  }
			  else
			  {
			     Error: ADC conversion start could not be performed
				  LL_GPIO_SetOutputPin(GPIOA, GPIO_PIN_5);
			  }*/
		  }
	}
}

void HighFreqTask(void){

	if (LL_ADC_IsActiveFlag_JEOS(ADC1) == 1)
		{
			LL_ADC_ClearFlag_JEOS(ADC1);
			adc_data1 = LL_ADC_INJ_ReadConversionData12(ADC1, LL_ADC_INJ_RANK_1);
			adc_data2 = LL_ADC_INJ_ReadConversionData12(ADC1, LL_ADC_INJ_RANK_2);
			adc_data3 = LL_ADC_INJ_ReadConversionData12(ADC1, LL_ADC_INJ_RANK_3);
		}
/*	else
		{
			LL_ADC_WriteReg(ADC1,ISR,0);
		}*/
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


void ADC_Init()
{
    LL_ADC_Enable( ADC1 );
    //LL_ADC_Enable( ADC2 );

    /* ADC1 Injected conversions end interrupt enabling */
    LL_ADC_ClearFlag_JEOS( ADC1 );
    LL_ADC_EnableIT_JEOS( ADC1 );
}



