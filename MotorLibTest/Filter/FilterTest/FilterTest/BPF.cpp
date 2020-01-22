#include "stdafx.h"
/*
* BPF.cpp
*
*  Created on: 2020/01/05
*      Author: watashi
*/

#include "BPF.hpp"

BPF::BPF()
//:mInputIntegrate1(1), mInputIntegrate2(1), mMidIntegrate(1), mOutIntegrate(1)
{
	// TODO Auto-generated constructor stub

}

BPF::~BPF() {
	// TODO Auto-generated destructor stub
}

void BPF::Init(double pGainB0, double pGainB2, double pGainA1, double pGainA2) {
	mGainB0 = pGainB0;
	mGainB2 = pGainB2;
	mGainA1 = pGainA1;
	mGainA2 = pGainA2;
}

bool BPF::Check(void) {
	bool status = true;
	if ( ((mGainA1 * mGainA1)/4.0f) < mGainA2) {
		status = false;
		return status;
	}

	if (mGainA2 < (-1.0f - mGainA1)) {
		status = false;
		return status;
	}

	if (mGainA2 < (-1.0f + mGainA1)) {
		status = false;
		return status;
	}
	return status;
}


double BPF::Output(double pTime, double pInput) {

	//double buf = (mGainB0 * pInput) - (mGainB2 * mInputUnitDelay2.PushAndGetVal( mInputUnitDelay1.PushAndGetVal(pInput) ));

	double inbuf1 = mGainB0 * pInput;
	double integrate = mInputUnitDelay1.PushAndGetVal(pInput);
	double integrate2 = mInputUnitDelay2.PushAndGetVal(integrate);
	double inbuf2 = integrate2 * mGainB2;
	double buf = inbuf1 - inbuf2;

	mBuf1 = buf - mGainA2 * mBuf2;

	mOutput = mBuf1 - mGainA1 * mBuf3;

	mBuf2 = mBuf3;
	mBuf3 = mOutput;
	//mBuf2 = mMidUnitDelay.PushAndGetVal(mBuf3);
	//TODO コードレビュー
	

	//debug


	return mOutput;
}
