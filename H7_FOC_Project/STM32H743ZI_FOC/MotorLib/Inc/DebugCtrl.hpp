/*
 * DebugCtrl.hpp
 *
 *  Created on: Aug 8, 2019
 *      Author: watashi
 */

#ifndef DEBUGCTRL_HPP_
#define DEBUGCTRL_HPP_

#include "MotorInfo.hpp"
#include "UIStatus.hpp"
#include "math.h"
#include "SEGGER_RTT.h"


class DebugCtrl {
private:
	int mLogcount;
public:
	DebugCtrl();
	virtual ~DebugCtrl();
	void RTTOutput(const MotorInfo &pMotorInfo, const UIStatus &pUIStatus);

};

#endif /* DEBUGCTRL_HPP_ */
