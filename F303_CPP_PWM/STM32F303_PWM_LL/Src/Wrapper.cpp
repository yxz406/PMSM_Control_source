/*
 * Wrapper.cpp
 *
 *  Created on: Jun 8, 2019
 *      Author: watashi
 */

//system include
#include "wrapper.hpp"

#include "stm32f3xx.h"

#include "stm32f3xx_hal.h"
#include "stm32f3xx_ll_tim.h"
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

//class include
#include "LedBlink.hpp"
#include "PWM.hpp"

void CPP_Wrapper(void){

	PWM PWM_Object1;
	PWM PWM_Object2;

	PWM_Object1.setTIM(TIM1);
	PWM_Object2.setTIM(TIM1);

	PWM_Object1.setCH(1);
	PWM_Object2.setCH(2);

	PWM_Object1.Init();
	PWM_Object2.Init();


	while(1){
		  for(int i=0;i<60000;i=i+100){
			  HAL_Delay(1);
			  PWM_Object1.Duty(i);
			  PWM_Object2.Duty(60000-i);

		  }
	}
}



