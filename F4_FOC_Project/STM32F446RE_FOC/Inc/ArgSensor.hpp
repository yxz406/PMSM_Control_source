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

	bool mIsStart;
	int mImArgcount;
	float mCalcArg;
public:
	ArgSensor();
	virtual ~ArgSensor();

	void Init(void);
	void increment(float pArg);
	void decrement(float pArg);
	float getArg(void);
	void Start_Stop(bool pIsONState);
	void ImArg(void);
};

#endif /* ARGSENSOR_HPP_ */
