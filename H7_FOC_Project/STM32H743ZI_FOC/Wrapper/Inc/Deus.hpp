/*
 * Deus.hpp
 *
 *  Created on: Sep 8, 2019
 *      Author: watashi
 */

#ifndef INC_DEUS_HPP_
#define INC_DEUS_HPP_

#include "GPIOCtrl.hpp"
#include "MotorInterface.hpp"
#include "MotorCtrl.hpp"
#include "MotorMeasure.hpp"

//test
#include <math.h>
//#include "tim.h"
//#include "TIMInit.hpp"
#include "STM32SystemPack.h"
#include "PWM.hpp"


#include "ErrorHandler.hpp"

class Deus {
private:

	enum OperationMode { //測定か運転か
		Measure = -1,
		Drive = 1,
	};

	OperationMode mMode;
	MotorCtrl M_Ctrl;
	MotorMeasure M_Measure;



public:
	Deus();
	virtual ~Deus();
	//void ModeInit();
	void Ctrl();
	void HFTask();
	void BtnAct();
	void BtnAct2();

	void (*HighFreqFuncPtr)(void);
};

#endif /* INC_DEUS_HPP_ */
