/*
 * LedBlink.cpp
 *
 *  Created on: Jun 17, 2019
 *      Author: watashi
 */

//あそびクラス　そのうち消す

#include "LedBlink.hpp"
#include "gpio.h"
//#include "stm32f4xx_hal.h"

void LedBlink::toggle() {
	  LL_GPIO_SetOutputPin(GPIOA, GPIO_PIN_5);
	  HAL_Delay(100);
	  LL_GPIO_ResetOutputPin(GPIOA, GPIO_PIN_5);
	  HAL_Delay(100);
}
