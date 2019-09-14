/*
 * DebugCtrl.hpp
 *
 *  Created on: Aug 8, 2019
 *      Author: watashi
 */

#ifndef DEBUGCTRL_HPP_
#define DEBUGCTRL_HPP_

#include "paramsetting.h"

//#include "UART.hpp"
//#include <vector>
#include "DebugInfo.hpp"
#include "DebugInfoTiny.hpp"


class DebugCtrl {
private:
	DebugInfo mDebugInfo;//動的確保
	DebugInfoTiny mDebugInfoTiny;//静的確保
	int mDebugSize;

	int mDebugStatus;

public:
	DebugCtrl();
	virtual ~DebugCtrl();
	int GetDbgStatus();
	void DbgInfoRegister(float pIu, float pIv, float pIw, float pArg);
	void DbgInfoTinyRegister(float pIu, float pIv, float pIw, float pArg);
	void SetDebugStatus(int pStatus);
	void PrintStatus();
	void PrintStatusTiny();
};

#endif /* DEBUGCTRL_HPP_ */
