/*
 * STM32Interface.cpp
 *
 *  Created on: Dec 16, 2019
 *      Author: watashi
 */

#include "STM32Interface.hpp"

#include "ADCCtrl.hpp"

STM32Interface::STM32Interface() {
	// TODO Auto-generated constructor stub

}

STM32Interface::~STM32Interface() {
	// TODO Auto-generated destructor stub
}

//ADC Interface
bool STM32Interface::ADCInit() {
	//ADC Initialize
	ADCCtrl::ADC2Init_HAL();
	ADCCtrl::ADC2Calibration();

	ADCCtrl::ADC3Init_HAL();
	ADCCtrl::ADC3Calibration();
	ADCCtrl::ADC3InjectedStart_IT();
	return 0;
}

bool STM32Interface::ADCDeInit() {
	//以降Initの逆順にDeInitしていくこと
	ADCCtrl::ADC3DeInit_HAL();
	ADCCtrl::ADC2DeInit_HAL();
	return 0;
}

float STM32Interface::ADCReadChU() {
	return (float)ADCCtrl::ADC3_INJ_Read_ch1();
}

float STM32Interface::ADCReadChV() {
	return (float)ADCCtrl::ADC3_INJ_Read_ch2();
}

float STM32Interface::ADCReadChW() {
	return (float)ADCCtrl::ADC3_INJ_Read_ch3();
}

//PWM Interface


