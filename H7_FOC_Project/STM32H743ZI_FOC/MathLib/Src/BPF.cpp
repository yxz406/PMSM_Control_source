/*
 * BPF.cpp
 *
 *  Created on: 2020/01/05
 *      Author: watashi
 */

#include <BPF.hpp>

BPF::BPF()
:mInputIntegrate1(1), mInputIntegrate2(1), mMidIntegrate(1), mOutIntegrate(1)
{
	// TODO Auto-generated constructor stub

}

BPF::~BPF() {
	// TODO Auto-generated destructor stub
}

void BPF::Init(float pGainB0, float pGainB2, float pGainA1, float pGainA2) {
	mGainB0 = pGainB0;
	mGainB2 = pGainB2;
	mGainA1 = pGainA1;
	mGainA2 = pGainA2;
}

float BPF::Output(float pTime, float pInput) {

	float buf = mGainB0 * pInput - mGainB2 * mInputIntegrate2.integrate(pTime, mInputIntegrate1.integrate(pTime, pInput) );
	mBuf1 = buf - mGainA2 * mBuf2;

	mOutput = mBuf1 - mGainA1 * mBuf3;

	mBuf3 = mOutIntegrate.integrate(pTime, mOutput);
	mBuf2 = mMidIntegrate.integrate(pTime, mBuf3);
	//TODO コードレビュー
}
