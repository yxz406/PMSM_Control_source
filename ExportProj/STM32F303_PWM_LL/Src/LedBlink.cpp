/*
 * LedBlink.cpp
 *
 *  Created on: Jun 8, 2019
 *      Author: watashi
 */

#include "LedBlink.hpp"
#include "stm32f3xx_hal.h"
#include "gpio.h"

void LedBlink::toggle() {
	  LL_GPIO_SetOutputPin(LD3_GPIO_Port, LD3_Pin);
	  HAL_Delay(100);
	  LL_GPIO_ResetOutputPin(LD3_GPIO_Port, LD3_Pin);
	  HAL_Delay(100);
}
