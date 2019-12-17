/*
 * STM32Interface.cpp
 *
 *  Created on: Dec 16, 2019
 *      Author: watashi
 */

#include "STM32Interface.hpp"

#include "ADCCtrl.hpp"
#include "TIMCtrl.hpp"

#include "main.h"
#include "stm32h7xx_hal_def.h"

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
bool STM32Interface::PWMInit() {
	//Timer Initialize
	TIMCtrl::MX_TIM1_Init();

	TIMCtrl::MotorDuty_ch1(0);//50%duty
	TIMCtrl::MotorDuty_ch2(0);
	TIMCtrl::MotorDuty_ch3(0);
	//TIMCtrl::MotorDuty_ch4(0.9);//9割タイミングで打つ
	TIMCtrl::TIM1SetCOMP_ch4(PWM_PERIOD_COUNT - 1);
	return 0;
}

bool STM32Interface::PWMDeInit() {
	//TIMをDeIntする前に安全のため、50%Duty,I=0に戻す
	TIMCtrl::MotorDuty_ch1(0);//50%duty
	TIMCtrl::MotorDuty_ch2(0);
	TIMCtrl::MotorDuty_ch3(0);

	//TIMCtrl::MotorDuty_ch4(0.9);//9割タイミングで打つ
	TIMCtrl::TIM1SetCOMP_ch4(PWM_PERIOD_COUNT - 1);

	//Timer Initialize
	TIMCtrl::MX_TIM1_DeInit();
	return 0;
}

bool STM32Interface::PWMStart() {
	TIMCtrl::TIM1PWMStart();
	return 0;
}

bool STM32Interface::PWMOutputChU(float pDuty) {
	TIMCtrl::floatDuty_ch1(pDuty);
	return 0;
}

bool STM32Interface::PWMOutputChV(float pDuty) {
	TIMCtrl::floatDuty_ch2(pDuty);
	return 0;
}

bool STM32Interface::PWMOutputChW(float pDuty) {
	TIMCtrl::floatDuty_ch3(pDuty);
	return 0;
}

bool STM32Interface::GPIO_Init() {
	return 0;
}

bool STM32Interface::GPIO_DeInit() {
	return 0;
}

bool STM32Interface::GPIO_PWMSetting(bool pOutput) {
	HAL_GPIO_WritePin(PWMSet_GPIO_Port, PWMSet_Pin, (GPIO_PinState)pOutput);
	return 0;
}

bool STM32Interface::GPIO_OverCurrentSetting(bool pOutput) {
	HAL_GPIO_WritePin(OCSet_GPIO_Port, OCSet_Pin, (GPIO_PinState)pOutput);
	return 0;
}

bool STM32Interface::GPIO_GateEnable(bool pOutput) {
	HAL_GPIO_WritePin(GateEnable_GPIO_Port, GateEnable_Pin, (GPIO_PinState)pOutput);
	return 0;
}
