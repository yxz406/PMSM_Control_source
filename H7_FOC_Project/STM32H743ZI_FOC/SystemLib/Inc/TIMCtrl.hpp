/*
 * TIMCtrl.hpp
 *
 *  Created on: 2019/09/22
 *      Author: watashi
 */

#ifndef INC_TIMCTRL_HPP_
#define INC_TIMCTRL_HPP_

#include "paramsetting.h"
#include "STM32SystemPack.h"

class TIMCtrl {
public:
	static TIM_HandleTypeDef mHandleTIM1;


	TIMCtrl();
	virtual ~TIMCtrl();

	static void TIM1Init_HAL(void);
	static void TIM1PWMStart(void);

	static void TIM1SetCOMP_ch1(int pCompare);
	static void TIM1SetCOMP_ch2(int pCompare);
	static void TIM1SetCOMP_ch3(int pCompare);
	static void TIM1SetCOMP_ch4(int pCompare);
	static void TIM1SetCOMP_ch5(int pCompare);
	static void TIM1SetCOMP_ch6(int pCompare);

	static void floatDuty_ch1(float pfDuty);//0~1
	static void floatDuty_ch2(float pfDuty);//0~1
	static void floatDuty_ch3(float pfDuty);//0~1
	static void floatDuty_ch4(float pfDuty);//0~1

	static void MotorDuty_ch1(float pfDuty);//-1~1
	static void MotorDuty_ch2(float pfDuty);
	static void MotorDuty_ch3(float pfDuty);
	static void MotorDuty_ch4(float pfDuty);

	//以下HALのWrapper
	static void MX_TIM1_Init(void);
	static void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* tim_baseHandle);
	static void HAL_TIM_MspPostInit(TIM_HandleTypeDef* timHandle);
	static void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* tim_baseHandle);

};

#endif /* INC_TIMCTRL_HPP_ */
