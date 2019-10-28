/*
 * SystemTest.cpp
 *
 *  Created on: Sep 17, 2019
 *      Author: watashi
 *
 *      レジスタ叩いてあそぶばしょ
 */

#include "SystemTest.hpp"
//#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "DSPInc.hpp"
//#include "stm32h7xx.h"
//#include "paramsetting.h"

//#include "stm32h7xx_hal_def.h"
//#include "stm32h7xx_ll_adc.h"

//#include "adc.h"
//#include "tim.h"
#include "ADCInit.hpp"
#include "TIMCtrl.hpp"
#include "ADCCtrl.hpp"
#include "SEGGER_RTT.h"

#include "stm32h7xx_hal.h"

	  extern UART_HandleTypeDef huart3;

void uartstr(char *str)
{
	HAL_UART_Transmit(&huart3, (uint8_t *)str, strlen(str), 1000);
}

SystemTest::SystemTest() {
	// TODO Auto-generated constructor stub

}

SystemTest::~SystemTest() {
	// TODO Auto-generated destructor stub
}

void SystemTest::StartTest() {
	  //debug code
//	  extern ADC_HandleTypeDef hadc3;
//	  extern TIM_HandleTypeDef htim1;


	  int initnum = 2;
	  switch(initnum) {
	  case 1:
		  ADCInit::ADC3Init();
		  ADCInit::ADC3Enable();
		  ADCInit::ADC3EnableIT();
		  break;

	  case 2:
		  TIMCtrl::GetIns().MX_TIM1_Init();
		 // TIMCtrl::get_instance().TIM1SetCOMP_ch1(pCompare)
		  TIMCtrl::GetIns().TIM1SetCOMP_ch1(5000);
		  TIMCtrl::GetIns().TIM1SetCOMP_ch2(2500);
		  TIMCtrl::GetIns().TIM1SetCOMP_ch3(1250);
		  TIMCtrl::GetIns().TIM1SetCOMP_ch4(5000);

		  TIMCtrl::GetIns().MotorDuty_ch1(1);
		  TIMCtrl::GetIns().MotorDuty_ch2(0.5);
		  TIMCtrl::GetIns().MotorDuty_ch3(-1);

		  TIMCtrl::GetIns().TIM1PWMStart();

			//ADC Initialize
			ADCCtrl::ADC2Init_HAL();
			ADCCtrl::ADC2Calibration();


		  ADCCtrl::ADC3Init_HAL();
		  ADCCtrl::ADC3Calibration();
		  ADCCtrl::ADC3InjectedStart_IT();

	  case 3:
//		  MX_ADC3_Init();
//		  HAL_ADCEx_InjectedStart_IT(&hadc3);
		  break;

	  case 255://ここにテストコードを書く

		  break;
	  default:

		  break;
	  }


			while(1){

			}
}
