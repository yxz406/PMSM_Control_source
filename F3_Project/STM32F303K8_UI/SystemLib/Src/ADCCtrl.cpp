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
	MX_ADC1_Init();


	if (HAL_ADC_Init(&hadc1) != HAL_OK)
	{
		Error_Handler();
	}

//	if ( HAL_ADCEx_Calibration_Start(&hadc1, ADC_SINGLE_ENDED) != HAL_OK) {
//		Error_Handler();
//	}


}


ADCCtrl::~ADCCtrl() {
	// TODO Auto-generated destructor stub

}

void ADCCtrl::ADC1Start_Conversion() {
	HAL_ADC_Start(&hadc1);
}

void ADCCtrl::ADC1Conversion_wait(int pTimeout) {
	HAL_ADC_PollForConversion(&hadc1, pTimeout);
}

int ADCCtrl::ADC1_Read(){

	return HAL_ADC_GetValue(&hadc1);
}
