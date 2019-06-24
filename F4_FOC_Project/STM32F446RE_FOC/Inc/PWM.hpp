/*
 * PWM.hpp
 *
 *  Created on: Jun 9, 2019
 *      Author: watashi
 */

#include "stm32f4xx_ll_tim.h"//need


#ifndef PWM_HPP_
#define PWM_HPP_

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
	void Duty(int pDuty);
	void fInit(int pTimReload);
	void fDuty(float pfDuty);//入力は0~1までの浮動小数点数
	void f2Duty(float pfDuty);//入力は-1~1までの浮動小数点数
};

#endif /* PWM_HPP_ */
