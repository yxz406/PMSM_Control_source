/*
 * PID.hpp
 *
 *  Created on: Jul 12, 2019
 *      Author: watashi
 */

#ifndef PID_HPP_
#define PID_HPP_

#include <array>

class PID {
private:
	std::array<float, 3> mError;
	float mOutValOfLast;
	float mGain_p;
	float mGain_i;
	float mGain_d;
	float mSampleTime;
	float mDiff;

public:
	PID();
	PID(float pGain_p, float pGain_i, float pGain_d);
	virtual ~PID();
	void SetParam(float pGain_p, float pGain_i, float pGain_d);
	void ErrorUpdate(float pError);
	void ErrorAndTimeUpdate(float pError, float pSampleTime);
	void SetSampleTime(float pSampleTime);
	float OutPut(void);
};

#endif /* PID_HPP_ */
