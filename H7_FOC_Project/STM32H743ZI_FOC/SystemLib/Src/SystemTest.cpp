/*
 * SystemTest.cpp
 *
 *  Created on: Sep 17, 2019
 *      Author: watashi
 *
 *      レジスタ叩いてあそぶばしょ
 */

#include "SystemTest.hpp"

//#include "stm32h7xx.h"
//#include "paramsetting.h"

//#include "stm32h7xx_hal_def.h"
//#include "stm32h7xx_ll_adc.h"

#include "adc.h"
#include "tim.h"
#include "ADCInit.hpp"
#include "SEGGER_RTT.h"

SystemTest::SystemTest() {
	// TODO Auto-generated constructor stub

}

SystemTest::~SystemTest() {
	// TODO Auto-generated destructor stub
}

void SystemTest::StartTest() {
	  //debug code
	  extern ADC_HandleTypeDef hadc3;
	  extern TIM_HandleTypeDef htim1;
	  //extern TIM_OC_InitTypeDef sConfigOC;

	 // HAL_ADC_Start_IT(&hadc3);

	  //HAL_ADC_Start(&hadc3);
	  ADCInit::ADC3Enable();

	  asm("NOP");

		 __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 5000);
		 __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 2500);
		 __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 1250);
		// __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 5000);

		 asm("NOP");
		  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
		  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
		  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
		  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);


			while(1){
				HAL_Delay(100);
				int adc_u = ADC3 -> JDR1;
				int adc_v = ADC3 -> JDR2;
				int adc_w = ADC3 -> JDR3;
				SEGGER_RTT_printf(0, "adcVal:%d,%d,%d\n" ,adc_u, adc_v, adc_w);
			}
	//	  asm("NOP");
	//  while(1) {
	//
	//
	////		 HAL_Delay(1000);
	////		  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 2000);
	////		 HAL_Delay(1000);
	//
	//		  asm("NOP");
	//
	//	  asm("NOP");
	//  }

}


//enum ADC_REG ADCREG;
//static int ADC_REG;

//
//  {
//	  //ADCInit();
//	  asm("NOP");
//
//	  MX_ADC3_Init();
//	  asm("NOP");
//	  ADCStart();
//
//	  HAL_ADC_Start_IT(&hadc3);
//	  asm("NOP");
//	  //ADC3 -> CFGR |= 0b100000000000000000000;//JDISCEN
//	  //ADC3 -> CFGR |= ADC_REG_CFGR_JDISCEN; // ADC Inject Group Enable
//	  asm("NOP");
//
//	  asm("NOP");
//	  //__HAL_ADC_ENABLE_IT(ADC3, ADC_IT_JEOS);
//      ((ADC3->IER) |= ADC_IT_JEOS);
//	  asm("NOP");
//	  ADC3 -> IER |= 0b01;
//	  asm("NOP");
//	  ADC3 -> IER |= 0b10;
//	  asm("NOP");
//	  ADC3 -> IER |= 0b1000;
//	  asm("NOP");
//      ((ADC3->ISR) |= ADC_IT_JEOS);
//	  WRITE_REG((ADC3 -> ISR), (((ADC3 -> ISR) & (~(LL_ADC_FLAG_EOC))) | (LL_ADC_FLAG_EOS)));
//	  asm("NOP");
//	  //HAL_ADC_Start_IT(&hadc3);
//	  asm("NOP");
//	  ADC3 -> ISR = 0x7FF;
//	  asm("NOP");
//	  asm("NOP");
//	  ADC3 -> ISR = ADC3 -> ISR & ~LL_ADC_FLAG_EOS;
//	  asm("NOP");
//	  ADC3 -> ISR = ADC3 -> ISR | LL_ADC_FLAG_EOS;
//	  asm("NOP");
//  }
//  {
//
//	  //GPIO REG TEST
//	  //MX_GPIO_Init();
//	  RCC->AHB4ENR |= RCC_AHB4ENR_GPIOBEN; // IO portB clock enable
//	  GPIOB->MODER &= ~GPIO_MODER_MODE7_Msk; // initialize pin function
//	  GPIOB->MODER |= (GPIO_MODE_OUTPUT_PP << GPIO_MODER_MODE7_Pos); // set PB7 as GPIO for output
//		for(;;) {
////			asm("NOP");
////			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);
////			asm("NOP");
////			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);
////			for(volatile uint32_t i=0; i<100000; i++); // wait
//			asm("NOP");
//			GPIOB->ODR ^= GPIO_ODR_OD7; // toggle output data
//			asm("NOP");
//			GPIOB->ODR = GPIOB->ODR ^ GPIO_ODR_OD7; // toggle output data
//			asm("NOP");
//			GPIOB->ODR = GPIOB->ODR | GPIO_ODR_OD7; // ON PIN7
//			asm("NOP");
//			GPIOB->ODR = GPIOB->ODR & ~GPIO_ODR_OD7; // OFF PIN7
//
//		}
//  }
