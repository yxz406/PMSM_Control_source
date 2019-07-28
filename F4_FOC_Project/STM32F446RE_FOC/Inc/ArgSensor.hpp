/*
 * ArgSensor.hpp
 *
 *  Created on: Jun 25, 2019
 *      Author: watashi
 */

#ifndef ARGSENSOR_HPP_
#define ARGSENSOR_HPP_

class ArgSensor {
private:
	float mArg;
	float mArgOld;

	float mArg_delta;

	bool mFCisON;
	bool mIsAccelerating;

	int mImArgcount;

public:
	ArgSensor();
	virtual ~ArgSensor();

	void Init(void);
	void increment(float pArg);
	void decrement(float pArg);
	float getArg(void);
	float getArg_delta(void);
	float getArgOld(void);
	void FC_Start_Stop(bool pIsON);
	bool GetIsAccelerating(void);

	void ForceComArg(void);

	//void ImArg2(void);//連れ回し運転　名前を変える事
};

#endif /* ARGSENSOR_HPP_ */
