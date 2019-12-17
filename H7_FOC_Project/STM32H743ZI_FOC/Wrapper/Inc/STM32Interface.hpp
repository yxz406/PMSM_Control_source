/*
 * STM32Interface.hpp
 *
 *  Created on: Dec 16, 2019
 *      Author: watashi
 */

#ifndef SRC_STM32INTERFACE_HPP_
#define SRC_STM32INTERFACE_HPP_

#include "SystemInterface.hpp"

class STM32Interface : SystemInterface{
public:
	STM32Interface();
	virtual ~STM32Interface();

	//ADC Interface
	bool ADCInit();
	bool ADCDeInit();

	float ADCReadChU();
	float ADCReadChV();
	float ADCReadChW();

	//PWM Interface
	bool PWMInit();
	bool PWMDeInit();
	bool PWMStart();
	bool PWMOutputChU(float pDuty);
	bool PWMOutputChV(float pDuty);
	bool PWMOutputChW(float pDuty);

	//Output-Pin Interface
	bool GPIO_Init();
	bool GPIO_DeInit();
	bool GPIO_PWMSetting(bool pOutput);
	bool GPIO_OverCurrentSetting(bool pOutput);
	bool GPIO_GateEnable(bool pOutput);

};

#endif /* SRC_STM32INTERFACE_HPP_ */
