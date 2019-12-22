/*
 * STM32F303K8Interface.hpp
 *
 *  Created on: Dec 22, 2019
 *      Author: watashi
 */

#ifndef INC_STM32F303K8INTERFACE_HPP_
#define INC_STM32F303K8INTERFACE_HPP_

#include "spi.h"
#include "stm32f3xx_hal.h"
#include "SystemInterface.hpp"

class STM32F303K8Interface : public SystemInterface{
public:
	STM32F303K8Interface();
	virtual ~STM32F303K8Interface();


	//SPI Interface
	bool SPIInit();
	bool SPIDeInit();
	bool SPITransmitReceive(SPI_HandleTypeDef *hspi, uint8_t *pTxData, uint8_t *pRxData, uint16_t pDataSize, uint32_t pTimeout);

};

#endif /* INC_STM32F303K8INTERFACE_HPP_ */
