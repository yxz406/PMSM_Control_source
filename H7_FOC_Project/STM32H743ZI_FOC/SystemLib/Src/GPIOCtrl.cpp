/*
 * GPIOCtrl.cpp
 *
 *  Created on: Sep 8, 2019
 *      Author: Nakamura(Yutaka)
 */

#include "GPIOCtrl.hpp"

GPIOCtrl::GPIOCtrl( GPIO_TypeDef *pGPIOx, uint32_t pPinMask)
:mGPIOx(pGPIOx), mPinMask(pPinMask), mGPIOStatus(GPIO_OFF) {
	OFF();
}

GPIOCtrl::~GPIOCtrl() {
}

void GPIOCtrl::OFF() {
	mGPIOStatus = GPIO_OFF;
	HAL_GPIO_WritePin(mGPIOx, mPinMask, GPIO_PIN_RESET);
	//LL_GPIO_ResetOutputPin(mGPIOx, mPinMask);
}

void GPIOCtrl::ON() {
	mGPIOStatus = GPIO_ON;
	HAL_GPIO_WritePin(mGPIOx, mPinMask, GPIO_PIN_SET);
	//LL_GPIO_SetOutputPin(mGPIOx, mPinMask);
}

void GPIOCtrl::Toggle() {
	if(mGPIOStatus) {
		OFF();
	} else {
		ON();
	}
}
