/*
 * PhaseEstimator.cpp
 *
 *  Created on: Sep 11, 2019
 *      Author: watashi
 */

#include "PhaseEstimator.hpp"

PhaseEstimator::PhaseEstimator()
:mBufVal4ITG(1), mBufVal6ITG(1)
{
	// TODO Auto-generated constructor stub

}

PhaseEstimator::~PhaseEstimator() {
	// TODO Auto-generated destructor stub
}

//Initializer
void PhaseEstimator::InitCycleTime(float pCycleTime) {
	mCycleTime = pCycleTime;
}
void PhaseEstimator::InitGainK1(float pK1) {
	mK1 = pK1;
}
void PhaseEstimator::InitGainK2(float pK2) {
	mK2 = pK2;
}
void PhaseEstimator::InitGainK3(float pK3) {
	mK3 = pK3;
}

//Setter
void PhaseEstimator::SetValue(const float &pInputVal) {
	mInputVal = pInputVal;
}

//Calculator
void PhaseEstimator::Calculate() {
	mBufVal1 = mK1 * mInputVal;
	mBufVal2 = mK2 * mInputVal;
	mBufVal3 = mK3 * mInputVal;

	mBufVal4 = mBufVal4ITG.integrate(mCycleTime, mBufVal3);

	mBufVal5 = mBufVal2 + mBufVal4;

	mBufVal6 = mBufVal6ITG.integrate(mCycleTime, mBufVal5);//オーバフロー対処

	mOutputVal = mBufVal1 + mBufVal6;
}

//integrate Reset For OpenLoop
void PhaseEstimator::ThetaResetForOpenLoop(const float &pTheta) {
	//内部変数を無理やりリセットすることで、強制転流時の角度を引き継ぐ。
	mBufVal4ITG.SetDefault(0, 0);
	mBufVal6ITG.SetDefault(0, pTheta);
}


//Getter
float PhaseEstimator::GetTheta() {
	return mOutputVal;
}

float PhaseEstimator::GetOmega() {
	return mBufVal5;
}
