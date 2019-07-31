/*
 * GPIOInit.hpp
 *
 *  Created on: Jul 31, 2019
 *      Author: watashi
 */

#ifndef GPIOINIT_HPP_
#define GPIOINIT_HPP_

#include "STM32SystemPack.h"
#include "PinDef.h"

class GPIOInit {
public:
	GPIOInit();
	virtual ~GPIOInit();
	void Init();
};

#endif /* GPIOINIT_HPP_ */
