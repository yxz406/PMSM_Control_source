#include "stdafx.h"
/*
* LPF.cpp
*
*  Created on: 2020/01/05
*      Author: watashi
*/

#include "LPF.hpp"

LPF::LPF()
//:mInputIntegrate(1), mOutputIntegrate(1)
{
	// TODO Auto-generated constructor stub

}

LPF::~LPF() {
	// TODO Auto-generated destructor stub
}

void LPF::Init(float pGainB0, float pGainB1, float pGainA1) {
	mGainB0 = pGainB0;
	mGainB1 = pGainB1;
	mGainA1 = pGainA1;
}

float LPF::Output(float pTime, float pInput) {
	mBuf1 = (mGainB0 * pInput) + (mGainB1 * mInputUnitDelay.PushAndGetVal(pInput));
	mOutput = mBuf1 - mGainA1 * mBuf2;

	//ˆÈŒão—Í‘¤‚P’x‰„(’@‚©‚ê‚é‚Ì‚ªŸ‰ñ‚¾‚©‚ç’x‰„Ší‚ğg‚í‚È‚¢‚Å—Ç‚¢)
	mBuf2 = mOutput;
	return mOutput;
}
