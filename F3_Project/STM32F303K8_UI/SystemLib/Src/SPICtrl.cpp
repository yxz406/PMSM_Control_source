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

}

SPICtrl::~SPICtrl() {
	// TODO Auto-generated destructor stub
}


void SPICtrl::SetTransmitData() {

}

void SPICtrl::PushBackTransmitIntData(int pIntData) {

	if( ( 3 + mArrayPos ) < SPI_DATA_SIZE ) {
		return;
	}

	mTxData[ 3 + mArrayPos ] = pIntData & 0xFF;
	mTxData[ 2 + mArrayPos ] = ( pIntData >> 8 ) & 0xFF;
	mTxData[ 1 + mArrayPos ] = ( pIntData >> 16 ) & 0xFF;
	mTxData[ 0 + mArrayPos ] = ( pIntData >> 24 ) & 0xFF;

	mArrayPos = mArrayPos + 4;
}


void SPICtrl::GetReceiveData() {

}

void SPICtrl::SPITransmitReceive() {
	mspiState = TRANSFER_WAIT;
	//rxバッファを読み込み前に0埋めする。
	*mRxData = *m0fillArr;
	HAL_SPI_TransmitReceive_DMA(&hspi1,(uint8_t*)mTxData,(uint8_t*)mRxData,SPI_DATA_SIZE);

	while(mspiState == TRANSFER_WAIT){
	}

	//使い終わったtxバッファを0埋めする。
	*mTxData = *m0fillArr;
	mArrayPos = 0;
}
