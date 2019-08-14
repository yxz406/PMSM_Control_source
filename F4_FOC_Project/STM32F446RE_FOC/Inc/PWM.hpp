/*
 * PWM.hpp
 *
 *  Created on: Jun 9, 2019
 *      Author: watashi
 */




#ifndef PWM_HPP_
#define PWM_HPP_

#include "STM32SystemPack.h"
#include "paramsetting.h"
//#include "stm32f4xx_ll_tim.h"//need

class PWM {
private:
	TIM_TypeDef *mTIMx;
	int mCH = 0;
	int mTimReload = 0;
	__IO uint32_t *mREG;
public:
	void setTIM(TIM_TypeDef* pTIMx);
	void setCH(int pCH);
	void Init();
	void fInit(int pTimReload);
	void Duty(int pDuty);
	void fDuty(float pfDuty);//入力は0~1までの浮動小数点数
	void f2Duty(float pfDuty);//入力は-1~1までの浮動小数点数
	void Disable(void);//TIMを停止する。
};

#endif /* PWM_HPP_ */
