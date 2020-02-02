/*
 * SPICtrl.cpp
 *
 *  Created on: Dec 21, 2019
 *      Author: watashi
 */

#include "SPICtrl.hpp"

void SPICtrl::SetTransmitData(const uint8_t* pTxData) {

	if(sizeof(pTxData) > SPI_DATA_SIZE) {
		return;
	}

	*mTxData = *pTxData;

}

void SPICtrl::PushBackTransmitIntData(int pIntData) {

	if( ( 3 + mArrayPos ) > SPI_DATA_SIZE ) {
		return;
	}

	mTxData[ 3 + mArrayPos ] = pIntData & 0xFF;
	mTxData[ 2 + mArrayPos ] = ( pIntData >> 8 ) & 0xFF;
	mTxData[ 1 + mArrayPos ] = ( pIntData >> 16 ) & 0xFF;
	mTxData[ 0 + mArrayPos ] = ( pIntData >> 24 ) & 0xFF;

	mArrayPos = mArrayPos + 4;
}


uint8_t* SPICtrl::GetReceiveData() {
	return mRxData;
}

std::array<int,(SPI_DATA_SIZE/4)> SPICtrl::GetRxInt() {
	std::array<int,(SPI_DATA_SIZE/4)> rxint = {0};

	for(int pos=0; pos < SPI_DATA_SIZE; pos=pos+4){
		int buf = mRxData[3 + pos]
				| (mRxData[2 + pos] << 8)
				| (mRxData[1 + pos] << 16)
				| (mRxData[pos] << 24);
		rxint.at(pos/4) = buf;
	}
	return rxint;
}


void SPICtrl::SPITransmitReceive() {
	mspiState = TRANSFER_WAIT;
	//rxバッファを読み込み前に0埋めする。
	*mRxData = *m0fillArr;

//	//DMA
//	if( HAL_SPI_TransmitReceive_DMA(&hspi4,(uint8_t*)mTxData,(uint8_t*)mRxData,SPI_DATA_SIZE) != HAL_OK ) {
//	}
//
//	while(mspiState == TRANSFER_WAIT){
//	}

	//NO DMA
	if( HAL_SPI_TransmitReceive(&hspi4,(uint8_t*)mTxData,(uint8_t*)mRxData,SPI_DATA_SIZE, 100) != HAL_OK ) {
	}

	//使い終わったtxバッファを0埋めする。
	*mTxData = *m0fillArr;
	mArrayPos = 0;
}
