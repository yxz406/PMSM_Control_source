/*
 * Deus.cpp
 *
 *  Created on: Sep 8, 2019
 *      Author: watashi
 */

#include "Deus.hpp"

	//GPIOCtrl myGPIO0(GPIOB, GPIO_PIN_7);
	//GPIOCtrl myGPIO1(GPIOB, GPIO_PIN_0);
	GPIOCtrl myGPIO2(GPIOB, GPIO_PIN_14);

void multipleBench(int roop) {
	int i=0;
	//float fval=2.3f;
	float const floatval = 2.3f;
	int fpval = (int)round(floatval * (1<<8));

	float const  mpval = 0.996f;
	int fpmp = (int)round(mpval * (1<<8));

	for(i=0; i<roop; i++){
		fpval =( fpval * fpmp ) >> 8;
	}
}

void addBench(int roop) {
	int i;
	//float fval=2.3f;
	int val = 1;
	for(i=0; i<roop; i++){
		val = val + 1;
		//fval = fval + 1.25f;
		//fval = fval /1.2f;
	}
}

void Bench(){
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);
	asm("NOP");


	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);
	asm("NOP");
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);


	addBench(70);


	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);
	asm("NOP");
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);

	multipleBench(70);

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);
}


Deus::Deus() {
	// TODO Auto-generated constructor stub
//	HAL_TIM_PeriodElapsedCallback(&htim1) {
//
//		  if((htim->Instance == TIM1) && (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)) {
//		    // タイムアウト処理
//		  }
//	}

}

Deus::~Deus() {
	// TODO Auto-generated destructor stub
}


void Deus::HFTask() {
	//M_Ctrl.HighFreqTask();
	//Bench();
//	myGPIO0.Toggle();
//	myGPIO1.Toggle();
	myGPIO2.Toggle();
}

void Deus::Ctrl() {

	M_Ctrl.InitSystem();

	M_Ctrl.InitMotorInfo();
	M_Ctrl.InitObserver();
	M_Ctrl.InitPWM();
	while(1){
		HAL_Delay(100);
		int adc_u = ADC3 -> JDR1;
		int adc_v = ADC3 -> JDR2;
		int adc_w = ADC3 -> JDR3;
		SEGGER_RTT_printf(0, "adcVal:%d,%d,%d\n" ,adc_u, adc_v, adc_w);
	}




//	GPIOCtrl myGPIO0(GPIOB, GPIO_PIN_7);
//	GPIOCtrl myGPIO1(GPIOB, GPIO_PIN_0);
//	GPIOCtrl myGPIO2(GPIOB, GPIO_PIN_14);
//
//	myGPIO0.ON();
//	myGPIO1.ON();
//	myGPIO2.OFF();
//
//	M_Ctrl.InitSystem();
//	M_Ctrl.InitMotorInfo();
//	M_Ctrl.InitObserver();
//	M_Ctrl.InitPWM();
//
//	//HAL_TIM_
//
////											//	TIMInit::Init(this::mhtim1);
////												HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
////												__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 50000);
////											//	//HAL_Delay(500);
////											//	__HAL_TIM_SET_COMPARE(this::htim1, TIM_CHANNEL_1, 10000);
////												//HAL_Delay(500);
////												while(1){
////
////												}
//	PWM PWMch1;
//	//TIM_HandleTypeDef *htim1;
//	PWMch1.setTIM(&htim1);
//	PWMch1.setCH(PWM::PWMch::ch1);
//	PWMch1.fInit(PWM_PERIOD_COUNT);
//
//	while(1){
//		PWMch1.f2Duty(0);
//		myGPIO0.Toggle();
//		myGPIO1.Toggle();
//		myGPIO2.Toggle();
//		HAL_Delay(1000);
//		//PWMch1.f2Duty(-0.9);
//		myGPIO0.Toggle();
//		myGPIO1.Toggle();
//		myGPIO2.Toggle();
//		HAL_Delay(1000);
//	}
}


