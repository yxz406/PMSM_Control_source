/*
 * Deus.hpp
 *
 *  Created on: Sep 8, 2019
 *      Author: watashi
 */

#ifndef INC_DEUS_HPP_
#define INC_DEUS_HPP_

#include "UICtrl.hpp"
//#include "GPIOCtrl.hpp"
//#include "MotorInterface.hpp"
//#include "MotorCtrl.hpp"
//#include "MotorMeasure.hpp"
//
////test
//#include <math.h>
////#include "tim.h"
////#include "TIMInit.hpp"
//#include "STM32SystemPack.h"
//#include "PWM.hpp"
//
//
//#include "ErrorHandler.hpp"

class Deus {
private:
	UICtrl mUICtrl;
public:
	Deus();
	virtual ~Deus();
	//void ModeInit();
	void Ctrl();
	void HFTask();
	void BtnAct();
	void BtnAct2();


	void SPICplt();
	void SPIErr();
};

#endif /* INC_DEUS_HPP_ */
