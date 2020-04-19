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
#include "MotorLibDefPack.hpp"
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
	std::array<float, 4> OutputWavesSupOffsetPhase(const fp_rad &pOffset);
	std::array<float, 4> OutputWavesSupOffsetPhase_dq(const fp_rad &pOffset_dc, const fp_rad &pOffset_qc);
};

class SqWaveGenerator {
private:
	bool mIsPositive = true;
public:
	float OutputSqWave();
};


#endif /* INC_WAVEGENERATOR_HPP_ */
