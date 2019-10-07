/*
 * ZIntegrate.hpp
 *
 *  Created on: Aug 31, 2019
 *      Author: watashi
 */

#ifndef INC_ZINTEGRATE_HPP_
#define INC_ZINTEGRATE_HPP_

#include <array>

class ZIntegrate {
public:
	ZIntegrate();
	virtual ~ZIntegrate();
};

class Zintegrate1n{
private:
	float mK;
	float mInput = 0;
	float mInputOld = 0;

	float mOutput = 0;
	float mOutputOld = 0;


public:
	void ZintegrateInit(float pK);
	float integrate(float pTime, float pValue);
};

class Zintegrate2n{
private:
	float mK;
	std::array<float, 2> mVector;
	std::array<float, 2> mOldVec;
public:
	void ZintegrateInit(float pK);
	std::array<float, 2> integrate(float pTime, std::array<float, 2> pVector);
};



#endif /* INC_ZINTEGRATE_HPP_ */
