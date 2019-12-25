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

	while(1){

		mADCCtrl.ADC1Start_Conversion();
		mADCCtrl.ADC1Conversion_wait(10);
		int adcval = mADCCtrl.ADC1_Read();
//
		mSPICtrl.PushBackTransmitIntData(adcval);

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
