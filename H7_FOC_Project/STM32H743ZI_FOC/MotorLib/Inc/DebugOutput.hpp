/*
 * DebugOutput.hpp
 *
 *  Created on: Nov 7, 2019
 *      Author: watashi
 */

#ifndef INC_DEBUGOUTPUT_HPP_
#define INC_DEBUGOUTPUT_HPP_

#include "MotorInfo.hpp"

class DebugOutput {
private:
public:
	DebugOutput();
	virtual ~DebugOutput();

	static void Output(const MotorInfo &pMotorInfo);
};

#endif /* INC_DEBUGOUTPUT_HPP_ */
