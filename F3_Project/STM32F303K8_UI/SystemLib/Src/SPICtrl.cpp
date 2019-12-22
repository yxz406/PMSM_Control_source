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


void SPICtrl::GetReceiveData() {

}

void SPICtrl::SPITransmitReceive() {

	mspiState = TRANSFER_WAIT;

//	//rxバッファを一旦リセットする
//	mRxBuffer.clear();
//	mRxBuffer.shrink_to_fit();
//
	//mTxBuffer.resize(SPI_DATA_SIZE, 0);//これが重くて動かなかった
//
	uint8_t txBuf[SPI_DATA_SIZE];
	for(unsigned int i=0; i < mTxBuffer.size(); i++) {
		txBuf[i] = mTxBuffer.at(i);
	}
//

	//uint8_t txBuf[SPI_DATA_SIZE] = { 0x55, 0xAA };
	uint8_t rxBuf[SPI_DATA_SIZE];




	//HAL_SPI_TransmitReceive(&hspi1,(uint8_t*)txBuf,(uint8_t*)rxBuf,SPI_DATA_SIZE,2000);

	HAL_SPI_TransmitReceive_DMA(&hspi1,(uint8_t*)txBuf,(uint8_t*)rxBuf,SPI_DATA_SIZE);

	while(mspiState == TRANSFER_WAIT){
	}


//	std::vector<uint8_t> rxBuffer(std::begin(rxBuf), std::end(rxBuf));
//	mRxBuffer = rxBuffer;
//
	//配列のクリア
	mTxBuffer.clear();
	mTxBuffer.shrink_to_fit();

}
