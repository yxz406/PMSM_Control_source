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
#include "UiCtrl.hpp"

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
MotorInfo Motor; //モータの電圧・電流等を管理、及び座標変換のClass

PWM PWM_Object1; //PWMのHWを叩くClass
PWM PWM_Object2;
PWM PWM_Object3;
PWM PWM_Object4;

ArgSensor sensor; //角度を求める機能を持ったclass

UiCtrl ui_ctrl; //UI入力を処理するclass

void cppwrapper(void){
	MathLib mathlibrary;//三角関数を取得
	int mathlib_size = 512;//ライブラリのサイズを指定
	mathlibrary.fInit(mathlib_size);

	Motor.setMathLib(mathlibrary);//モータクラスに算術ライブラリを渡す

	//LL_TIM_DisableIT_BRK(TIM1);//効かない

	PWM_Object1.setTIM(TIM1);
	PWM_Object2.setTIM(TIM1);
	PWM_Object3.setTIM(TIM1);
	PWM_Object4.setTIM(TIM1);

	PWM_Object1.setCH(1);
	PWM_Object2.setCH(2);
	PWM_Object3.setCH(3);
	PWM_Object4.setCH(4);

	PWM_Object1.fInit(4000);
	PWM_Object2.fInit(4000);
	PWM_Object3.fInit(4000);
	PWM_Object4.fInit(4000);


	PWM_Object1.f2Duty(0);//50%duty
	PWM_Object2.f2Duty(0);
	PWM_Object3.f2Duty(0);
	PWM_Object4.f2Duty(0);

	LL_GPIO_SetOutputPin(GPIOC, GPIO_PIN_10);
	LL_GPIO_SetOutputPin(GPIOC, GPIO_PIN_11);
	LL_GPIO_SetOutputPin(GPIOC, GPIO_PIN_12);

	ADC_Init();

	while(1){
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

void HighFreqTask(void){

	if (LL_ADC_IsActiveFlag_JEOS(ADC1) == 1)
		{
			LL_ADC_ClearFlag_JEOS(ADC1);
			adc_data1 = LL_ADC_INJ_ReadConversionData12(ADC1, LL_ADC_INJ_RANK_1);
			adc_data2 = LL_ADC_INJ_ReadConversionData12(ADC1, LL_ADC_INJ_RANK_2);
			adc_data3 = LL_ADC_INJ_ReadConversionData12(ADC1, LL_ADC_INJ_RANK_3);

			//位置センサを叩くTask
//			LL_ADC_REG_StartConversionSWStart(ADC3);//ADC3を叩くためにはこれ
//			float adc_gain = (float)LL_ADC_REG_ReadConversionData12(ADC3)/4095;

			//float one_step = (float)2*M_PI / Motor.getMathLib().getLibSize();//手動インクリ用
			//sensor.increment(one_step);
			sensor.ImArg();

			float Vd_input = 0;
			float Vq_input = 0.5f;

			LL_ADC_REG_StartConversionSWStart(ADC2);
			float adc_speed = (float)LL_ADC_REG_ReadConversionData12(ADC2)/4095;

			Vq_input = 0;
			Vd_input = adc_speed;//連れ回し運転

			MotorPWMTask(Motor.getMathLib().radToSizeCount(sensor.getArg()), Vd_input, Vq_input);//暫定で作った関数
		}
/*	else
		{
			LL_ADC_WriteReg(ADC1,ISR,0);
		}*/
}

void BtnAct(void){//強制転流開始へのトリガ
	ui_ctrl.BtnAct();
	sensor.Start_Stop(ui_ctrl.getState());
}


void ADC_Init()
{
    LL_ADC_Enable( ADC1 );
    LL_ADC_Enable( ADC2 );
    LL_ADC_Enable( ADC3 );
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
	UART uartob;
	uartob.setString(Str);
	uartob.Transmit();
}



