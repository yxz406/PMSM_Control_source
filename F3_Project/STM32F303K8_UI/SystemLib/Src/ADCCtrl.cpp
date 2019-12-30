/*
 * ADCCtrl.cpp
 *
 *  Created on: Dec 21, 2019
 *      Author: watashi
 */

#include "ADCCtrl.hpp"
#include "adc.h"

ADCCtrl::ADCCtrl() {
	// TODO Auto-generated constructor stub
	//Initをここに書くとステップ実行で切り分けできなくなるので非推奨

}


ADCCtrl::~ADCCtrl() {
	// TODO Auto-generated destructor stub

}

void ADCCtrl::ADC1Init() {
	MX_ADC1_Init();
	if ( HAL_ADCEx_Calibration_Start(&hadc1, ADC_SINGLE_ENDED) != HAL_OK) {
		Error_Handler();
	}
}

void ADCCtrl::ADC1Start_Conversion() {
	HAL_ADC_Start(&hadc1);
}

void ADCCtrl::ADC1Start_ConversionDMA() {

	  if (HAL_ADC_Start_DMA(&hadc1, (uint32_t *)mADCBuffer, ADC_BUF_LENGTH) != HAL_OK) {
		  Error_Handler();
	  }
}

void ADCCtrl::ADC1Conversion_wait(int pTimeout) {
	HAL_ADC_PollForConversion(&hadc1, pTimeout);
}

int ADCCtrl::ADC1_Read(){
	return HAL_ADC_GetValue(&hadc1);
}


uint16_t* ADCCtrl::GetADC_DMA_Val() {
	return mADCBuffer;
}
