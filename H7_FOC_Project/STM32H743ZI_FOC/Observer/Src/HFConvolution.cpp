/*
 * HFConvolution.cpp
 *
 *  Created on: 2020/01/05
 *      Author: watashi
 */

#include "HFConvolution.hpp"

HFConvolution::HFConvolution()
:mIntegOmega(1), mIntegTheta(1)
{
	// TODO Auto-generated constructor stub

}

HFConvolution::~HFConvolution() {
	// TODO Auto-generated destructor stub
}


void HFConvolution::Init(float pCycleTime, float pKi, float pKp) {
	InitCycleTime(pCycleTime);
	InitKi(pKi);
	InitKp(pKp);

	//mLPF.Init(pGainB0, pGainB1, pGainA1);
}

void HFConvolution::LPFInit(float pGainB0, float pGainB1, float pGainA1) {
	mLPFIdc.Init(pGainB0, pGainB1, pGainA1);
	mLPFIqc.Init(pGainB0, pGainB1, pGainA1);
}

void HFConvolution::BPFInit(float pGainB0, float pGainB2, float pGainA1, float pGainA2) {
	mBPFIdc.Init(pGainB0, pGainB2, pGainA1, pGainA2);
	mBPFIqc.Init(pGainB0, pGainB2, pGainA1, pGainA2);
}

void HFConvolution::InitCycleTime(float pCycleTime) {
	mCycleTime = pCycleTime;
}

void HFConvolution::InitKi(float pKi) {
	mKi = pKi;
}


void HFConvolution::InitKp(float pKp) {
	mKp = pKp;
}


void HFConvolution::SetIgdPair(const std::array<float, 2> &pIgd) {
	mIgd = pIgd;
}


void HFConvolution::SetSinCos(const std::array<float, 2> &pSinCos) {
	mSinCos = pSinCos;
}


void HFConvolution::Calculate() {
	float BPFIdc = mBPFIdc.Output(mCycleTime, mIgd.at(0));
	float BPFIqc = mBPFIqc.Output(mCycleTime, mIgd.at(1));
	float convIdc = BPFIdc * mSinCos.at(1);
	float convIqc = BPFIqc * mSinCos.at(0);
	float LPFIdc = mLPFIdc.Output(mCycleTime, convIdc);
	float LPFIqc = mLPFIqc.Output(mCycleTime, convIqc);

	//PII2を使うことも要検討。
	float omega = LPFIqc - LPFIdc;

	float omega_c = mKi * mIntegOmega.integrate(mCycleTime, omega) + mKp * omega;

	mTheta_c = mIntegTheta.integrate(mCycleTime, omega_c);

}


float HFConvolution::GetTheta_c(void) {
	return mTheta_c;
}
