/*
 * SystemInterface.hpp
 *
 *  Created on: Dec 22, 2019
 *      Author: watashi
 */

#ifndef INC_SYSTEMINTERFACE_HPP_
#define INC_SYSTEMINTERFACE_HPP_

class SystemInterface {
public:
	SystemInterface();
	virtual ~SystemInterface() = 0;
	virtual bool SPITransmitReceive() = 0;
	//virtual bool SPITransmitReceive(SPI_HandleTypeDef *hspi, uint8_t *pTxData, uint8_t *pRxData, uint16_t pDataSize, uint32_t pTimeout) = 0;
};

#endif /* INC_SYSTEMINTERFACE_HPP_ */
