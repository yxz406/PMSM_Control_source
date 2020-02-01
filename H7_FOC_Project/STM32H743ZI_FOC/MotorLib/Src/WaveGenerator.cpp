/*
 * WaveGenerator.cpp
 *
 *  Created on: Dec 13, 2019
 *      Author: watashi
 */

#include "WaveGenerator.hpp"

WaveGenerator::WaveGenerator() {
	// TODO Auto-generated constructor stub

}

WaveGenerator::~WaveGenerator() {
	// TODO Auto-generated destructor stub
}

void WaveGenerator::InitFrequency(int pTargetHz) {
	mTargetHz = pTargetHz;
	mThetaPerStep = ( (2.0f * M_PI)* (float)mTargetHz/(float)CONTROL_FREQ_HZ );
}


void WaveGenerator::ResetPhase() {
	mCount = 0;

}


float WaveGenerator::OutputWaveform() {
	float theta = mThetaPerStep * mCount ;
	mCount++;

	if(mCount > CONTROL_FREQ_HZ - 1) {//CONTROL_FREQに届いたら0にする
		mCount = 0;
	}

	return Trigonometric::sin(theta);
}


std::array<float, 2> WaveGenerator::OutputWaves() {
	float theta = mThetaPerStep * mCount ;
	mCount++;

	if(mCount > CONTROL_FREQ_HZ - 1) {//CONTROL_FREQに届いたら0にする
		mCount = 0;
	}

	return {Trigonometric::sin(theta),Trigonometric::cos(theta)};

}

std::array<float, 4> WaveGenerator::OutputWavesSupOffsetPhase(const fp_rad &pOffset) {
	fp_rad theta = mThetaPerStep * mCount;
	fp_rad thetaDemodulation = theta + pOffset;

	mCount++;

	if(mCount > CONTROL_FREQ_HZ - 1) {//CONTROL_FREQに届いたら0にする
		mCount = 0;
	}

	return {Trigonometric::sin(theta),Trigonometric::cos(theta),
				Trigonometric::sin(thetaDemodulation),Trigonometric::cos(thetaDemodulation)};

}


std::array<float, 4> WaveGenerator::OutputWavesSupOffsetPhase_dq(const fp_rad &pOffset_dc, const fp_rad &pOffset_qc) {
	fp_rad theta = mThetaPerStep * mCount;
	fp_rad thetaDemodulation_dc = theta + pOffset_dc;
	fp_rad thetaDemodulation_qc = theta + pOffset_qc;

	mCount++;

	if(mCount > CONTROL_FREQ_HZ - 1) {//CONTROL_FREQに届いたら0にする
		mCount = 0;
	}

	//Idcがcos重畳、Iqcがsin重畳
	return {Trigonometric::sin(theta),Trigonometric::cos(theta),
				Trigonometric::sin(thetaDemodulation_qc),Trigonometric::cos(thetaDemodulation_dc)};

}

