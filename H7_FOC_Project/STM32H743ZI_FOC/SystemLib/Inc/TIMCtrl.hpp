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
private:
	TIM_HandleTypeDef mHandleTIM1;

	TIMCtrl() = default;
	~TIMCtrl() = default;

public:

	//singleton getter
	TIMCtrl(const TIMCtrl&) = delete;
	TIMCtrl& operator=(const TIMCtrl&) = delete;
	TIMCtrl(TIMCtrl&&) = delete;
	TIMCtrl& operator=(TIMCtrl&&) = delete;

	static TIMCtrl& GetIns() {
	        static TIMCtrl instance;
	        return instance;
	}

	TIM_HandleTypeDef& GetHandle(void);

	void TIM1Init_HAL(void);
	void TIM1PWMStart(void);

	void TIM1SetCOMP_ch1(int pCompare);
	void TIM1SetCOMP_ch2(int pCompare);
	void TIM1SetCOMP_ch3(int pCompare);
	void TIM1SetCOMP_ch4(int pCompare);
	void TIM1SetCOMP_ch5(int pCompare);
	void TIM1SetCOMP_ch6(int pCompare);

	void floatDuty_ch1(float pfDuty);//0~1
	void floatDuty_ch2(float pfDuty);//0~1
	void floatDuty_ch3(float pfDuty);//0~1
	void floatDuty_ch4(float pfDuty);//0~1

	void MotorDuty_ch1(float pfDuty);//-1~1
	void MotorDuty_ch2(float pfDuty);
	void MotorDuty_ch3(float pfDuty);
	void MotorDuty_ch4(float pfDuty);

	//以下HALのWrapper
	void MX_TIM1_Init(void);
	void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* tim_baseHandle);
	void HAL_TIM_MspPostInit(TIM_HandleTypeDef* timHandle);
	void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* tim_baseHandle);

};

#endif /* INC_TIMCTRL_HPP_ */
