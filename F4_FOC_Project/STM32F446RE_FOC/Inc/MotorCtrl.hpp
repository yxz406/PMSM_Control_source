/*
 * MotorCtrl.hpp
 *
 *  Created on: Aug 5, 2019
 *      Author: watashi
 */

#ifndef MOTORCTRL_HPP_
#define MOTORCTRL_HPP_

#include "paramsetting.h" //パラメータのマクロ

#include "../SystemLib/Inc/STM32SystemPack.h"

#include "../SystemLib/Inc/ADCInit.hpp"
#include "../SystemLib/Inc/GPIOInit.hpp"
#include "../SystemLib/Inc/TIMInit.hpp"
#include "../SystemLib/Inc/USARTInit.hpp"

//#include <vector>

#include "MotorInfo.hpp"
#include "PWM.hpp"
#include "UART.hpp"
#include "UiCtrl.hpp"

#include "DebugInfo.hpp"

class MotorCtrl {
private:
	MotorInfo mMotorInfo;

	PWM mPWMch1;
	PWM mPWMch2;
	PWM mPWMch3;
	PWM mPWMch4;

	DebugInfo mDebug;
	UART mUART;

public:
	MotorCtrl();
	virtual ~MotorCtrl();
	void SetMotorInfo(MotorInfo pMotorInfo);
	void SetPWMch1(PWM pPWM);
	void SetPWMch2(PWM pPWM);
	void SetPWMch3(PWM pPWM);
	void SetPWMch4(PWM pPWM);

	void InitSystem(void);
	void InitPWM(void);
	void InitMotorInfo(void);

	void HighFreqTask(void);
	void MotorOutputTask(void);

	void DebugTask(float pIu, float pIv, float pIw, float pArg);

	void BtnAct(void);
	void BtnActOFF(void);
	void BtnActON(void);
};

#endif /* MOTORCTRL_HPP_ */
