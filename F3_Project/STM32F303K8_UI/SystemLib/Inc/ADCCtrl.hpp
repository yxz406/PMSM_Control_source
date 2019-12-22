/*
 * ADCCtrl.hpp
 *
 *  Created on: Dec 21, 2019
 *      Author: watashi
 */

#ifndef INC_ADCCTRL_HPP_
#define INC_ADCCTRL_HPP_

class ADCCtrl {
public:
	ADCCtrl();
	virtual ~ADCCtrl();


	void ADC1Start_Conversion();
	void ADC1Conversion_wait(int pTimeout);
	int ADC1_Read();
};

#endif /* INC_ADCCTRL_HPP_ */
