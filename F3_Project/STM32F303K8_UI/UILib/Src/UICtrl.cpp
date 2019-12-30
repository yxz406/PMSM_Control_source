/*
 * UICtrl.cpp
 *
 *  Created on: Dec 21, 2019
 *      Author: watashi
 */

#include "UICtrl.hpp"



UICtrl::UICtrl() {
	// TODO Auto-generated constructor stub
}

UICtrl::~UICtrl() {
	// TODO Auto-generated destructor stub
}

void UICtrl::UITask() {
		mADCCtrl.ADC1Init();
	while(1){

		mADCCtrl.ADC1Start_ConversionDMA();
		//HAL_Delay(10);

		uint16_t* ADCResult = mADCCtrl.GetADC_DMA_Val();
		uint16_t ADCCh1 = *ADCResult;
		uint16_t ADCCh2 = *(ADCResult+1);
		uint16_t ADCCh3 = *(ADCResult+2);

//
		mSPICtrl.PushBackTransmitIntData(ADCCh1);
		mSPICtrl.PushBackTransmitIntData(ADCCh2);

//		mSPICtrl.PushBackTransmitIntData(4095);



//		mSPICtrl.PushBackTransmitIntData(1195);
//
//		mSPICtrl.PushBackTransmitIntData(65500);
//
//		mSPICtrl.PushBackTransmitIntData(-1157480048);

		//mSPICtrl.SetTransmitData();
		mSPICtrl.SPITransmitReceive();

		mSPICtrl.GetReceiveData();
	}
}
