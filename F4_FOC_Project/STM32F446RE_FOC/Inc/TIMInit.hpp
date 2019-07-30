/*
 * TIMInit.hpp
 *
 *  Created on: Jul 30, 2019
 *      Author: watashi
 */

#ifndef TIMINIT_HPP_
#define TIMINIT_HPP_

#include "stm32f4xx_hal.h"
#include "stm32f4xx_ll_adc.h"
#include "stm32f4xx_ll_tim.h"
#include "stm32f4xx_ll_usart.h"
#include "stm32f4xx_ll_rcc.h"
#include "stm32f4xx.h"
#include "stm32f4xx_ll_system.h"
#include "stm32f4xx_ll_gpio.h"
#include "stm32f4xx_ll_exti.h"
#include "stm32f4xx_ll_bus.h"
#include "stm32f4xx_ll_cortex.h"
#include "stm32f4xx_ll_utils.h"
#include "stm32f4xx_ll_pwr.h"
#include "stm32f4xx_ll_dma.h"


class TIMInit {
public:
	TIMInit();
	virtual ~TIMInit();
	void Init();
};

#endif /* TIMINIT_HPP_ */
