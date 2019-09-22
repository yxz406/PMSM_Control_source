/*
 * USARTCtrl.hpp
 *
 *  Created on: Sep 21, 2019
 *      Author: watashi
 */

#ifndef SRC_USARTCTRL_HPP_
#define SRC_USARTCTRL_HPP_

#include "STM32SystemPack.h"

class USARTCtrl {
public:
	static ADC_HandleTypeDef mHandleADC3;


	USARTCtrl();
	virtual ~USARTCtrl();
	static void USART3Init();



	//HAL関数を使った定義
	static void USART3Init_HAL();

	//以下HALのWrapper
	static void MX_ADC3_Init(void);
	static void HAL_ADC_MspInit(ADC_HandleTypeDef* adcHandle);
	static void HAL_ADC_MspDeInit(ADC_HandleTypeDef* adcHandle);

};

#endif /* SRC_USARTCTRL_HPP_ */
