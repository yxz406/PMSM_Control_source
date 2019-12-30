/*
 * ADCCtrl.hpp
 *
 *  Created on: Dec 21, 2019
 *      Author: watashi
 */

#ifndef INC_ADCCTRL_HPP_
#define INC_ADCCTRL_HPP_

#include "main.h"
#include "paramsetting.h"

class ADCCtrl {
private:
	uint16_t mADCBuffer[ADC_BUF_LENGTH];

public:
	ADCCtrl();
	virtual ~ADCCtrl();
	void ADC1Init();

	void ADC1Start_Conversion();
	void ADC1Start_ConversionDMA();
	void ADC1Conversion_wait(int pTimeout);
	int ADC1_Read();

	uint16_t* GetADC_DMA_Val();
};

#endif /* INC_ADCCTRL_HPP_ */
