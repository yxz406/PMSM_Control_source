/*
 * STM32F303K8Interface.cpp
 *
 *  Created on: Dec 22, 2019
 *      Author: watashi
 */

#include "STM32F303K8Interface.hpp"

STM32F303K8Interface::STM32F303K8Interface() {
	// TODO Auto-generated constructor stub

}

STM32F303K8Interface::~STM32F303K8Interface() {
	// TODO Auto-generated destructor stub
}

bool STM32F303K8Interface::SPIInit() {
	return 0;
}

bool STM32F303K8Interface::SPIDeInit() {
	return 0;
}

bool SPITransmitReceive(SPI_HandleTypeDef *hspi, uint8_t *pTxData, uint8_t *pRxData, uint16_t pDataSize, uint32_t pTimeout) {

	if( HAL_SPI_TransmitReceive(hspi, pTxData, pRxData, pDataSize, pTimeout) == HAL_OK ) {
		return 0;
	} else {
		return 1;
	}

}
