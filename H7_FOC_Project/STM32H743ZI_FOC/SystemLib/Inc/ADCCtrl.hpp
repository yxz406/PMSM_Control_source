/*
 * ADCCtrl.hpp
 *
 *  Created on: Sep 21, 2019
 *      Author: watashi
 */

#ifndef INC_ADCCTRL_HPP_
#define INC_ADCCTRL_HPP_

#include "STM32SystemPack.h"

class ADCCtrl {
private:
	ADC_HandleTypeDef mHandleADC2;
	ADC_HandleTypeDef mHandleADC3;

	ADCCtrl() = default;
	~ADCCtrl() = default;
public:


	//singleton getter
	ADCCtrl(const ADCCtrl&) = delete;
	ADCCtrl& operator=(const ADCCtrl&) = delete;
	ADCCtrl(ADCCtrl&&) = delete;
	ADCCtrl& operator=(ADCCtrl&&) = delete;

	static ADCCtrl& GetIns() {
	        static ADCCtrl instance;
	        return instance;
	}

	//現状ハンドラを渡さずにできている
//	ADC_HandleTypeDef& GetADC2Handle(void);
//	ADC_HandleTypeDef& GetADC3Handle(void);


	//void ADC2Init();
	void ADC2Enable();
	void ADC2Disable();
	//HAL関数を使った定義
	void ADC2Init_HAL();
	void ADC2Calibration();
	void ADC2Start_Conversion();
	void ADC2Conversion_wait(int pTimeout);
	int ADC2_Read();
	//以下HALのWrapper
	void MX_ADC2_Init(void);


	//void ADC3Init();
	void ADC3Enable();
	void ADC3Disable();


	//HAL関数を使った定義
	void ADC3Init_HAL();
	void ADC3Calibration();
	void ADC3InjectedStart_IT();

	int ADC3_INJ_Read_ch1();
	int ADC3_INJ_Read_ch2();
	int ADC3_INJ_Read_ch3();

	void ADC3IRQHandler();

	//以下HALのWrapper
	void MX_ADC3_Init(void);
	void HAL_ADC_MspInit(ADC_HandleTypeDef* adcHandle);
	void HAL_ADC_MspDeInit(ADC_HandleTypeDef* adcHandle);
};



#endif /* INC_ADCCTRL_HPP_ */
