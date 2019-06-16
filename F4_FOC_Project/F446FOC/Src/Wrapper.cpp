/*
 * Wrapper.cpp
 *
 *  Created on: Jun 8, 2019
 *      Author: watashi
 */

//system include
#include "Wrapper.hpp"

#include "stm32f3xx.h"

#include "stm32f3xx_hal.h"
#include "stm32f3xx_ll_tim.h"
#include "stm32f3xx_ll_adc.h"
#include "stm32f3xx.h"
#include "stm32f3xx_ll_system.h"
#include "stm32f3xx_ll_gpio.h"
#include "stm32f3xx_ll_exti.h"
#include "stm32f3xx_ll_bus.h"
#include "stm32f3xx_ll_cortex.h"
#include "stm32f3xx_ll_rcc.h"
#include "stm32f3xx_ll_utils.h"
#include "stm32f3xx_ll_pwr.h"
#include "stm32f3xx_ll_dma.h"


//#include <iostream>
#include <vector>
#include "math.h"

//class include
#include "LedBlink.hpp"
#include "PWM.hpp"

void HighFreqTask(void);

void vectorInit(std::vector<int> *pVector);//プロトタイプ宣言
void ADCReInit(void);

void CPP_Wrapper(void){

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
	ADCReInit();


	while(1){
		  for(int i=0;i<600;i++){
			  HAL_Delay(1);
			  PWM_Object1.Duty(num[i]);
			  PWM_Object2.Duty(num[(i+200)%600]);
			  PWM_Object3.Duty(num[(i+400)%600]);
		  }
	}
}

void HighFreqTask(void){
	uint16_t adc_data1 = 0, adc_data2 = 0, adc_data3 = 0, adc_data4 = 0;
	if (LL_ADC_IsActiveFlag_JEOS(ADC1) == 1)
		{
			LL_ADC_ClearFlag_JEOS(ADC1);
			adc_data1 = LL_ADC_INJ_ReadConversionData12(ADC1, LL_ADC_INJ_RANK_1);
			adc_data2 = LL_ADC_INJ_ReadConversionData12(ADC1, LL_ADC_INJ_RANK_2);
			adc_data3 = LL_ADC_INJ_ReadConversionData12(ADC1, LL_ADC_INJ_RANK_3);
		}
	else
		{
			LL_ADC_WriteReg(ADC1,ISR,0);
		}
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

void ADCReInit(void){
	// ADC2 Initialization
	  WRITE_REG(ADC1->DIFSEL,0U); // LL_ADC_SetChannelSingleDiffが未定義動作を起こすので、レジスタに直接書き込む
	  LL_ADC_EnableInternalRegulator(ADC1);
	  HAL_Delay(10);
	  LL_ADC_StartCalibration(ADC1, LL_ADC_SINGLE_ENDED);
	  while (LL_ADC_IsCalibrationOnGoing(ADC1));
	  LL_ADC_Enable(ADC1);
	  while (!LL_ADC_IsActiveFlag_ADRDY(ADC1));
	  // JSQRをクリア
	  LL_ADC_INJ_StopConversion(ADC1);
	  while (LL_ADC_INJ_IsStopConversionOngoing(ADC1));
	  // CubeMXが出力するコードが不適切なため、ADC2のJSQRを改めて設定する
	  LL_ADC_DisableIT_JQOVF(ADC1);
	  LL_ADC_INJ_ConfigQueueContext(ADC1,
	                                LL_ADC_INJ_TRIG_EXT_TIM1_TRGO2,
	                                LL_ADC_INJ_TRIG_EXT_RISING,
	                                LL_ADC_INJ_SEQ_SCAN_ENABLE_3RANKS,
	                                LL_ADC_CHANNEL_1,
	                                LL_ADC_CHANNEL_2,
	                                LL_ADC_CHANNEL_3,
	                                LL_ADC_CHANNEL_4);
	  //(ADCx, TriggerSource, ExternalTriggerEdge, SequencerNbRanks, Rank1_Channel, Rank2_Channel, Rank3_Channel, Rank4_Channel)
	  // Inject変換の外部トリガを許可
	  LL_ADC_INJ_StartConversion(ADC1);

	  // Enable ADC Interrupt
	  LL_ADC_EnableIT_JEOS(ADC1);
	//  LL_TIM_EnableIT_UPDATE(TIM1);

	   // Set ADC Sampling Timing
//	   LL_TIM_OC_SetCompareCH4(TIM1, (uint32_t)(65530 - 90));

	    // Enable PWM Career
	    LL_TIM_EnableCounter(TIM1);
	    LL_TIM_SetRepetitionCounter(TIM1,1);

	    // Enable PWM Channels
	    LL_TIM_CC_EnableChannel(TIM1, LL_TIM_CHANNEL_CH1);
//	    LL_TIM_CC_EnableChannel(TIM1, LL_TIM_CHANNEL_CH1N);
	    LL_TIM_CC_EnableChannel(TIM1, LL_TIM_CHANNEL_CH2);
//	    LL_TIM_CC_EnableChannel(TIM1, LL_TIM_CHANNEL_CH2N);
	    LL_TIM_CC_EnableChannel(TIM1, LL_TIM_CHANNEL_CH3);
//	    LL_TIM_CC_EnableChannel(TIM1, LL_TIM_CHANNEL_CH3N);

	    // Enable SPI Channel
	    //LL_SPI_Enable(SPI1);

	    // Enable EXTI Interrupt
	    //LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_3);
}
