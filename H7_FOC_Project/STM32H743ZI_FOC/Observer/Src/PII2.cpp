/*
 * PII2.cpp
 *
 *  Created on: Sep 11, 2019
 *      Author: watashi
 */

#include "PII2.hpp"

PII2::PII2() {
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
void PII2::SetValue(float pInputVal) {
	mInputVal = pInputVal;
}

//Calculator
void PII2::Calculate() {
	mBufVal1 = mK1 * mInputVal;
	mBufVal2 = mK2 * mInputVal;
	mBufVal3 = mK3 * mInputVal;

	mBufVal4 = mBufVal4ITG.integrate(mCycleTime, mBufVal3);

	mBufVal5 = mBufVal2 + mBufVal4;

	mBufVal6 = mBufVal6ITG.integrate(mCycleTime, mBufVal5);

	mOutputVal = mBufVal1 + mBufVal6;
}

//Getter
float PII2::GetValue() {
	return mOutputVal;
}

float PII2::GetPIVal() {
	return mBufVal5;
}
