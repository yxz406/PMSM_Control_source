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
	float convIdc = mIgd.at(0) * mSinCos.at(1);
	float convIqc = mIgd.at(1) * mSinCos.at(0);

	//ここでLPFの処理が必要
	int hoooooooo
	//LPF後の処理

	float omega = convIqc - convIdc;

	float omega_c = mKi * mIntegOmega.integrate(mCycleTime, omega) + mKp * omega;

	mTheta_c = mIntegTheta.integrate(mCycleTime, omega_c);

}


float HFConvolution::GetTheta_c(void) {
	return mTheta_c;
}
