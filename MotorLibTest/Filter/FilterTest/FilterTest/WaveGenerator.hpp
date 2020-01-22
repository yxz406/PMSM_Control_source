/*
* WaveGenerator.hpp
*
*  Created on: Dec 13, 2019
*      Author: watashi
*/

#ifndef INC_WAVEGENERATOR_HPP_
#define INC_WAVEGENERATOR_HPP_

#include "paramsetting.h"
//#include "Trigonometric.hpp"
//#include "MotorLibDefPack.hpp"
#include <array>
class WaveGenerator {
private:
	int mTargetHz;
	int mCount = 0;
	float mThetaPerStep;
public:
	WaveGenerator();
	virtual ~WaveGenerator();
	void InitFrequency(int pTargetHz);
	void ResetPhase();
	float OutputWaveform();
	std::array<float, 2> OutputWaves();
	std::array<float, 4> OutputWavesSupOffsetPhase(float pOffset);
};

#endif /* INC_WAVEGENERATOR_HPP_ */
