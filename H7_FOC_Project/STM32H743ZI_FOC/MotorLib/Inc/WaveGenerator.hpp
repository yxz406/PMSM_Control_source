/*
 * WaveGenerator.hpp
 *
 *  Created on: Dec 13, 2019
 *      Author: watashi
 */

#ifndef INC_WAVEGENERATOR_HPP_
#define INC_WAVEGENERATOR_HPP_

#include "paramsetting.h"
#include "Trigonometric.hpp"

class WaveGenerator {
private:
	int mTargetHz;
	int mCount;
	float mThetaPerStep;
public:
	WaveGenerator();
	virtual ~WaveGenerator();
	void InitFrequency(int pTargetHz);
	void ResetPhase();
	float OutputWaveform();
};

#endif /* INC_WAVEGENERATOR_HPP_ */
