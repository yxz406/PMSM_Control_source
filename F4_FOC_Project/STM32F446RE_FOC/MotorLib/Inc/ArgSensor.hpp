/*
 * ArgSensor.hpp
 *
 *  Created on: Jun 25, 2019
 *      Author: watashi
 */

#ifndef ARGSENSOR_HPP_
#define ARGSENSOR_HPP_

#include "MotorLibDefPack.hpp"
#include "math.h"
#include "Observer.hpp"


class ArgSensor {
private:
	fp_rad mArg;
	fp_rad mArgOld;

	fp_rad mArg_delta;

	bool mFCisON;
	bool mIsAccelerating;

	int mImArgcount;
	Observer mObserver;

public:
	ArgSensor();
	virtual ~ArgSensor();

	void Init(void);
	void increment(fp_rad pArg);
	void decrement(fp_rad pArg);
	float getArg(void);
	float getArg_delta(void);
	float getArgOld(void);
	void FC_Start_Stop(bool pIsON);
	bool GetIsAccelerating(void);
	bool GetFCisON(void);
	int GetArgCount(void);

	void ForceComArg(void);
	//void Observer(void);

	//void ImArg2(void);//連れ回し運転　名前を変える事
};

#endif /* ARGSENSOR_HPP_ */
