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

	bool ADCInit();
	bool ADCDeInit();

	float ADCReadChU();
	float ADCReadChV();
	float ADCReadChW();
};

#endif /* SRC_STM32INTERFACE_HPP_ */
