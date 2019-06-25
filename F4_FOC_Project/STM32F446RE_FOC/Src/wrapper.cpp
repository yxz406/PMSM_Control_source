/*
 * wrapper.cpp
 *
 *  Created on: Jun 17, 2019
 *      Author: watashi
 */

#include "stm32f4xx_hal.h"
#include "stm32f4xx_ll_adc.h"
#include "stm32f4xx_ll_tim.h"
#include "stm32f4xx.h"
#include "stm32f4xx_ll_system.h"
#include "stm32f4xx_ll_gpio.h"
#include "stm32f4xx_ll_exti.h"
#include "stm32f4xx_ll_bus.h"
#include "stm32f4xx_ll_cortex.h"
#include "stm32f4xx_ll_rcc.h"
#include "stm32f4xx_ll_utils.h"
#include "stm32f4xx_ll_pwr.h"
#include "stm32f4xx_ll_dma.h"

#include <vector>
#include <string>
#include "math.h"

#include "wrapper.hpp"
#include "LedBlink.hpp"

#include "MathLib.hpp"
#include "PWM.hpp"
#include "UART.hpp"
#include "MotorInfo.hpp"
#include "ArgSensor.hpp"

uint16_t adc_data1 = 0, adc_data2 = 0, adc_data3 = 0, adc_data4 = 0;

void vectorInit(std::vector<int> *pVector);//プロトタイプ宣言
void ADCReInit(void);
void ADC_Init(void);
void UARTTask(std::string pStr);
void MotorPWMTask(void);


void cpploop(void) {//遊びクラス
    LedBlink instance;
    instance.toggle();
}

//割り込み内部からも叩けるように、これらマイコン内臓の機能を叩くClassの
//グローバルオブジェクトを生成する。
MotorInfo Motor;

PWM PWM_Object1;
PWM PWM_Object2;
PWM PWM_Object3;
PWM PWM_Object4;

ArgSensor sensor;

void cppwrapper(void){
	MathLib mathlibrary;//三角関数を取得
	int mathlib_size = 256;//ライブラリのサイズを指定
	mathlibrary.fInit(mathlib_size);

	Motor.setMathLib(mathlibrary);//モータクラスに算術ライブラリを渡す

	PWM_Object1.setTIM(TIM1);
	PWM_Object2.setTIM(TIM1);
	PWM_Object3.setTIM(TIM1);
	PWM_Object4.setTIM(TIM1);

	PWM_Object1.setCH(1);
	PWM_Object2.setCH(2);
	PWM_Object3.setCH(3);
	PWM_Object4.setCH(4);

	PWM_Object1.fInit(65535);
	PWM_Object2.fInit(65535);
	PWM_Object3.fInit(65535);
	PWM_Object4.fInit(65535);

	PWM_Object1.f2Duty(0);//50%duty
	PWM_Object2.f2Duty(0);
	PWM_Object3.f2Duty(0);
	PWM_Object4.f2Duty(0);

	ADC_Init();

	while(1){

//		for (const auto& e : mathlibrary.getSinList()) {
//		  //std::cout << e << std::endl;
//		}
//		for(int i=0;i<mathlib_size;i++){
//			Motor.setArg(i);
//			Motor.setVd(0);
//			Motor.setVq(0.5);
//			Motor.invClarkTransform();
//			Motor.invParkTransform();
//
//			PWM_Object1.f2Duty(Motor.getVu());
//			PWM_Object2.f2Duty(Motor.getVv());
//			PWM_Object3.f2Duty(Motor.getVw());
//			HAL_Delay(10);
//		}
	}
}

void MotorPWMTask(int pArg, float pVd, float pVq){//パラメータの物理量は将来的に変える
	//int mathlib_size = Motor.getMathLib().getLibSize();
	Motor.setArg(pArg);
	Motor.setVd(pVd);
	Motor.setVq(pVq);
	Motor.invClarkTransform();
	Motor.invParkTransform();

	PWM_Object1.f2Duty(Motor.getVu());
	PWM_Object2.f2Duty(Motor.getVv());
	PWM_Object3.f2Duty(Motor.getVw());
}



int argnum = 0;
void HighFreqTask(void){

	if (LL_ADC_IsActiveFlag_JEOS(ADC1) == 1)
		{
			LL_ADC_ClearFlag_JEOS(ADC1);
			adc_data1 = LL_ADC_INJ_ReadConversionData12(ADC1, LL_ADC_INJ_RANK_1);
			adc_data2 = LL_ADC_INJ_ReadConversionData12(ADC1, LL_ADC_INJ_RANK_2);
			adc_data3 = LL_ADC_INJ_ReadConversionData12(ADC1, LL_ADC_INJ_RANK_3);


			//位置センサを叩くTask
			sensor.increment((float)2*M_PI / Motor.getMathLib().getLibSize());
			//float arg = sensor.getArg();

			MotorPWMTask(Motor.getMathLib().radToSizeCount(sensor.getArg()), 0, 0.5f);//暫定で作った関数
			//UARTTask("a");
		}
/*	else
		{
			LL_ADC_WriteReg(ADC1,ISR,0);
		}*/


}


void ADC_Init()
{
    LL_ADC_Enable( ADC1 );
    //LL_ADC_Enable( ADC2 );

    /* ADC1 Injected conversions end interrupt enabling */
    LL_ADC_ClearFlag_JEOS( ADC1 );
    LL_ADC_EnableIT_JEOS( ADC1 );
}


void UARTTask(std::string pStr){
	//以下工事中

	float num = 0.345345f;
	std::string Str;
	Str += "number:";
	Str +=  std::to_string(num);
//	float bnum = mathlibrary.getSinList().at(64);
//	std::string Str;
//	Str += "number:";
//	std::string buf2 = std::to_string(bnum);
//	Str += buf2;
//	Str += "number2:";
//	int ubuf = 25;
//	Str += std::to_string(ubuf);
	//Str.push_back(buf2);
	UART uartob;
	uartob.setString(Str);
	uartob.Transmit();
	//HAL_UART_Transmit(huart, pData, Size, Timeout);
}


