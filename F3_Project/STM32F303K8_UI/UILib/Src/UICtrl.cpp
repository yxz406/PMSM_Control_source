/*
 * UICtrl.cpp
 *
 *  Created on: Dec 21, 2019
 *      Author: watashi
 */

#include "UICtrl.hpp"

#include "spi.h"


UICtrl::UICtrl() {
	// TODO Auto-generated constructor stub
}

UICtrl::~UICtrl() {
	// TODO Auto-generated destructor stub
}

void UICtrl::UITask() {

//	uint8_t txBuf[SPI_DATA_SIZE] = {0x0A, 0x0B, 0x0C, 0x0D};
//	HAL_SPI_Transmit_DMA(&hspi1,(uint8_t *)txBuf,SPI_DATA_SIZE);
//	while(1){
//
//	}
	//HAL_SPI_DMA

//	while(1){
//		uint8_t txBuf[SPI_DATA_SIZE] = {0x0A, 0x0B, 0x0C, 0x0D};
////		for(unsigned int i=0; i < mTxBuffer.size(); i++) {
////			txBuf[i] = mTxBuffer.at(i);
////		}
//
//		uint8_t rxBuf[64];
//		HAL_SPI_TransmitReceive(&hspi1,(uint8_t*)txBuf,(uint8_t*)rxBuf,SPI_DATA_SIZE,2000);
//	}


	while(1){

		mADCCtrl.ADC1Start_Conversion();
		mADCCtrl.ADC1Conversion_wait(10);
		int adcval = mADCCtrl.ADC1_Read();
//
		mSPICtrl.PushBackTransmitIntData(adcval);
//
//		mSPICtrl.PushBackTransmitIntData(4095);



//		mSPICtrl.PushBackTransmitIntData(1195);
//
//		mSPICtrl.PushBackTransmitIntData(65500);
//
//		mSPICtrl.PushBackTransmitIntData(-1157480048);

		//mSPICtrl.SetTransmitData();
		mSPICtrl.SPITransmitReceive();

		//mSPICtrl.GetReceiveData();
	}
}
