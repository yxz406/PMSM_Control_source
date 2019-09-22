/*
 * ADCInit.hpp
 *
 *  Created on: Jul 31, 2019
 *      Author: watashi
 */

#ifndef ADCINIT_HPP_
#define ADCINIT_HPP_

#include "STM32SystemPack.h"

class ADCInit {
private:
public:
	ADC_HandleTypeDef mHandleADC3;
public:
	ADCInit();
	virtual ~ADCInit();
	static void ADC3Init();
	static void ADC3Enable();
	static void ADC3EnableIT();
	static void ADC3Disable();

};

#endif /* ADCINIT_HPP_ */
