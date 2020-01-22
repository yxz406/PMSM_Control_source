#include "stdafx.h"
/*
* WaveGenerator.cpp
*
*  Created on: Dec 13, 2019
*      Author: watashi
*/

#include <math.h>
#include "WaveGenerator.hpp"
#define M_PI 3.141592653589793

WaveGenerator::WaveGenerator() {
	// TODO Auto-generated constructor stub

}

WaveGenerator::~WaveGenerator() {
	// TODO Auto-generated destructor stub
}

void WaveGenerator::InitFrequency(int pTargetHz) {
	mTargetHz = pTargetHz;
	mThetaPerStep = ((2.0f * M_PI)* (float)mTargetHz / (float)CONTROL_FREQ_HZ);
}


void WaveGenerator::ResetPhase() {
	mCount = 0;

}


float WaveGenerator::OutputWaveform() {
	float theta = mThetaPerStep * mCount;
	mCount++;

	if (mCount > CONTROL_FREQ_HZ - 1) {//CONTROL_FREQ‚É“Í‚¢‚½‚ç0‚É‚·‚é
		mCount = 0;
	}

	return sin(theta);
}


std::array<float, 2> WaveGenerator::OutputWaves() {
	float theta = mThetaPerStep * mCount;
	mCount++;

	if (mCount > CONTROL_FREQ_HZ - 1) {//CONTROL_FREQ‚É“Í‚¢‚½‚ç0‚É‚·‚é
		mCount = 0;
	}

	return { sin(theta),cos(theta) };

}

std::array<float, 4> WaveGenerator::OutputWavesSupOffsetPhase(float pOffset) {
	float theta = mThetaPerStep * mCount;
	float thetaDemodulation = theta + pOffset;

	mCount++;

	if (mCount > CONTROL_FREQ_HZ - 1) {//CONTROL_FREQ‚É“Í‚¢‚½‚ç0‚É‚·‚é
		mCount = 0;
	}

	return { sin(theta),cos(theta),
		sin(thetaDemodulation),cos(thetaDemodulation) };

}