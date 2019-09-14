/*
 * GPIOCtrl.hpp
 *
 *  Created on: Sep 8, 2019
 *      Author: Nakamura(Yutaka)
 */

#ifndef GPIOCTRL_HPP_
#define GPIOCTRL_HPP_


#include "gpio.h"
#include "stm32h7xx_hal.h"
//#include "stm32g4xx_hal.h"

class GPIOCtrl {
public:
	enum GPIOStatus {
		GPIO_OFF = 0,
		GPIO_ON = 1,
	};

private:
	GPIO_TypeDef *mGPIOx;
	uint32_t mPinMask;
	GPIOStatus mGPIOStatus;
public:
	GPIOCtrl( GPIO_TypeDef *pGPIOx, uint32_t pPinMask );
	virtual ~GPIOCtrl();
	void ON();
	void OFF();
	void Toggle();
};

#endif /* GPIOCTRL_HPP_ */
