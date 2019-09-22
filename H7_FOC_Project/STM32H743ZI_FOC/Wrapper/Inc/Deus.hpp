/*
 * Deus.hpp
 *
 *  Created on: Sep 8, 2019
 *      Author: watashi
 */

#ifndef INC_DEUS_HPP_
#define INC_DEUS_HPP_

#include "GPIOCtrl.hpp"
#include "MotorCtrl.hpp"

//test
#include <math.h>
//#include "tim.h"
//#include "TIMInit.hpp"
#include "STM32SystemPack.h"
#include "PWM.hpp"



class Deus {
private:

	MotorCtrl M_Ctrl;


public:
	Deus();
	virtual ~Deus();
	void Ctrl();
	void HFTask();
	void BtnAct();
};

#endif /* INC_DEUS_HPP_ */
