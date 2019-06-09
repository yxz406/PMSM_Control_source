/*
 * PWM.hpp
 *
 *  Created on: Jun 9, 2019
 *      Author: watashi
 */

#include "stm32f3xx_ll_tim.h"//need


#ifndef PWM_HPP_
#define PWM_HPP_

class PWM {
private:
	TIM_TypeDef *mTIMx;
	__IO uint32_t mCCR;
public:
	void setTIM(TIM_TypeDef* pTIMx);
	void setCH(__IO uint32_t pCCR);
	void Init();
	void Duty(int pDuty);
};

#endif /* PWM_HPP_ */
