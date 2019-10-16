/*
 * ArgCtrl.hpp
 *
 *  Created on: Sep 3, 2019
 *      Author: watashi
 */

#ifndef INC_ARGCTRL_HPP_
#define INC_ARGCTRL_HPP_


#include "MotorLibDefPack.hpp"
#include "MotorMath.hpp"
#include "paramsetting.h"
#include "math.h"
#include "Observer.hpp"

class ArgCtrl {
public://struct
	class OpenLoopInfo {
		private:
		public:
		fp_rad mtargetRPS;
		fp_rad mtargetAcc;
		fp_rad mAccelSPD;
	};
private:

	fp_rad mArg;
	fp_rad mArgOld;
	fp_rad mOmega;
	fp_rad mArgErr;

	OpenLoopInfo mOpenLoopInfo;

public:
	ArgCtrl();
	virtual ~ArgCtrl();
	void Init(void);
	void increment(fp_rad pArg);
	void decrement(fp_rad pArg);
	fp_rad getArg(void);
	fp_rad getArgErr(void);
	fp_rad getArgOld(void);
	fp_rad getArgOmega(void);

	OpenLoop_Status accelerationForOpenLoop(void);
	OpenLoop_Status decelerationForOpenLoop(void);

};

#endif /* INC_ARGCTRL_HPP_ */
