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


//#include <iostream>
#include <vector>
#include "math.h"

//class include
#include "LedBlink.hpp"
#include "PWM.hpp"

void vectorInit(std::vector<int> *pVector);//プロトタイプ宣言

void CPP_Wrapper(void){

	std::vector<int> num;
	vectorInit(&num);

	PWM PWM_Object1;
	PWM PWM_Object2;
	PWM PWM_Object3;

	PWM_Object1.setTIM(TIM1);
	PWM_Object2.setTIM(TIM1);
	PWM_Object3.setTIM(TIM1);

	PWM_Object1.setCH(1);
	PWM_Object2.setCH(2);
	PWM_Object3.setCH(3);

	PWM_Object1.Init();
	PWM_Object2.Init();
	PWM_Object3.Init();

	while(1){
		  for(int i=0;i<600;i++){
			  HAL_Delay(1);
			  PWM_Object1.Duty(num[i]);;
			  PWM_Object2.Duty(num[(i+200)%600]);
			  PWM_Object3.Duty(num[(i+400)%600]);
		  }
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

