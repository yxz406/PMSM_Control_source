/*
 * PII2.cpp
 *
 *  Created on: Sep 11, 2019
 *      Author: watashi
 */

#include "PII2.hpp"

PII2::PII2()
:mBufVal4ITG(1), mBufVal6ITG(1)
{
	// TODO Auto-generated constructor stub

}

PII2::~PII2() {
	// TODO Auto-generated destructor stub
}

//Initializer
void PII2::InitCycleTime(float pCycleTime) {
	mCycleTime = pCycleTime;
}
void PII2::InitGainK1(float pK1) {
	mK1 = pK1;
}
void PII2::InitGainK2(float pK2) {
	mK2 = pK2;
}
void PII2::InitGainK3(float pK3) {
	mK3 = pK3;
}

//Setter
void PII2::SetValue(const float &pInputVal) {
	mInputVal = pInputVal;
}

//Calculator
void PII2::Calculate() {
	mBufVal1 = mK1 * mInputVal;
	mBufVal2 = mK2 * mInputVal;
	mBufVal3 = mK3 * mInputVal;

	mBufVal4 = mBufVal4ITG.integrate(mCycleTime, mBufVal3);

	mBufVal5 = mBufVal2 + mBufVal4;

	mBufVal6 = mBufVal6ITG.integrate(mCycleTime, mBufVal5);//オーバフロー対処

	mOutputVal = mBufVal1 + mBufVal6;
}

//integrate Reset For OpenLoop
void PII2::ThetaResetForOpenLoop(const float &pTheta) {
	//内部変数を無理やりリセットすることで、強制転流時の角度を引き継ぐ。
	mBufVal4ITG.SetDefault(0, 0);
	mBufVal6ITG.SetDefault(0, pTheta);
}


//Getter
float PII2::GetTheta() {
	return mOutputVal;
}

float PII2::GetOmega() {
	return mBufVal5;
}
