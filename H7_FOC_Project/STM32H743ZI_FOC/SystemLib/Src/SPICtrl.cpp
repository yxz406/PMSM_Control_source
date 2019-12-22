/*
 * SPICtrl.cpp
 *
 *  Created on: Dec 21, 2019
 *      Author: watashi
 */

#include "SPICtrl.hpp"
#include "spi.h"


SPICtrl::SPICtrl() {
	// TODO Auto-generated constructor stub
	mTxBuffer.reserve(SPI_DATA_SIZE);
	mRxBuffer.reserve(SPI_DATA_SIZE);

	mTxBuffer.clear();
	mRxBuffer.clear();

	mTxBuffer.shrink_to_fit();
	mRxBuffer.shrink_to_fit();
}

SPICtrl::~SPICtrl() {
	// TODO Auto-generated destructor stub
}


void SPICtrl::SetTransmitData() {

}

void SPICtrl::PushBackTransmitIntData(int pIntData) {

	mTmpData.mInt = pIntData;
	for(unsigned int i=0; i < mTmpData.mByte.size(); i++) {
		mTxBuffer.push_back( mTmpData.mByte.at(3-i) );
	}

}


std::vector<uint8_t> SPICtrl::GetReceiveData() {
	return mRxBuffer;
}

void SPICtrl::SPITransmitReceive() {

	//rxバッファを一旦リセットする
	mRxBuffer.clear();
	mRxBuffer.shrink_to_fit();

	mTxBuffer.resize(SPI_DATA_SIZE, 0);

	uint8_t txBuf[SPI_DATA_SIZE];
	for(unsigned int i=0; i < mTxBuffer.size(); i++) {
		txBuf[i] = mTxBuffer.at(i);
	}

	uint8_t rxBuf[64];
	HAL_SPI_TransmitReceive(&hspi4, (uint8_t*)txBuf, (uint8_t*)rxBuf, SPI_DATA_SIZE, SPI_TIMEOUT);
	//HAL_SPI_TransmitReceive(&hspi4, (uint8_t*)txBuf, (uint8_t*)rxBuf, 64, 2000);
	std::vector<uint8_t> rxBuffer(std::begin(rxBuf), std::end(rxBuf));
	mRxBuffer = rxBuffer;

	//配列のクリア
	mTxBuffer.clear();
	mTxBuffer.shrink_to_fit();

}
