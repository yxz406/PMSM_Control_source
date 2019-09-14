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


class PWM {
public:
	enum PWMch {
		ch1		=	0x00000000U,
		ch2  		=	0x00000004U,
		ch3  		=	0x00000008U,
		ch4  		=	0x0000000CU,
		ch5 		=	0x00000010U,
		ch6  		=	0x00000014U,
		chALL	=	0x0000003CU,
	};
private:
	TIM_HandleTypeDef *mhtim;
	PWMch mCH;
	int mTimReload = 0;

public:
	void setTIM(TIM_HandleTypeDef* phtim);
	void setCH(PWMch pCH);
	void Init();
	void fInit(int pTimReload);
	void Duty(int pDuty);
	void fDuty(float pfDuty);//入力は0~1までの浮動小数点数
	void f2Duty(float pfDuty);//入力は-1~1までの浮動小数点数
	void Disable(void);//TIMを停止する。
};

#endif /* PWM_HPP_ */
