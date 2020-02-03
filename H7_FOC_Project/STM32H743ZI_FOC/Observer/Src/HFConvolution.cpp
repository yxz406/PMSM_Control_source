/*
 * HFConvolution.cpp
 *
 *  Created on: 2020/01/05
 *      Author: watashi
 */

#include "HFConvolution.hpp"

HFConvolution::HFConvolution()
{
	// TODO Auto-generated constructor stub

}

HFConvolution::~HFConvolution() {
	// TODO Auto-generated destructor stub
}


void HFConvolution::LPFInit(float pGainB0, float pGainB1, float pGainA1) {
	mLPFIdc.Init(pGainB0, pGainB1, pGainA1);
	mLPFIqc.Init(pGainB0, pGainB1, pGainA1);
}

void HFConvolution::SetKh(float pKh) {
	mKh = pKh;
}

void HFConvolution::BPF_LPFInit(float pGainB0, float pGainB1, float pGainA1) {
	mBPF_LPFIdc.Init(pGainB0, pGainB1, pGainA1);
	mBPF_LPFIqc.Init(pGainB0, pGainB1, pGainA1);
}

void HFConvolution::BPF_HPFInit(float pGainB0, float pGainB1, float pGainA1) {
	mBPF_HPFIdc.Init(pGainB0, pGainB1, pGainA1);
	mBPF_HPFIqc.Init(pGainB0, pGainB1, pGainA1);
}

void HFConvolution::InitCycleTime(float pCycleTime) {
	mCycleTime = pCycleTime;
}

void HFConvolution::InitPII2(float pCycleTime, float pK1, float pK2, float pK3) {
	mEstThetaPII2.InitCycleTime(pCycleTime);
	mEstThetaPII2.InitGainK1(pK1);
	mEstThetaPII2.InitGainK2(pK2);
	mEstThetaPII2.InitGainK3(pK3);
}


void HFConvolution::SetIgdPair(const std::array<float, 2> &pIgd) {
	mIgd = pIgd;
}


void HFConvolution::SetSinCosForDemodulation(const std::array<float, 2> &pSinCosForDemodulation) {
	mSinCosForDemodulation = pSinCosForDemodulation;
}


void HFConvolution::Calculate() {
	//BPF
	//BPFは、BPF_LPF に入れて、出力をBPF_HPFに入れる
	//BPF_LPF
	float BPF_LPFIdc = mBPF_LPFIdc.Output(mIgd.at(0));
	float BPF_LPFIqc = mBPF_LPFIqc.Output(mIgd.at(1));
	//BPF_HPF
	mIdch = mBPF_HPFIdc.Output(BPF_LPFIdc);
	mIqch = mBPF_HPFIqc.Output(BPF_LPFIqc);

	//ヘテロダイン
	mConvIdc = mIdch * mSinCosForDemodulation.at(1);
	mConvIqc = mIqch * mSinCosForDemodulation.at(0);
	float LPFIdc = mLPFIdc.Output(mConvIdc);
	float LPFIqc = mLPFIqc.Output(mConvIqc);

	//モータのパラメタの倍率調整
	mEstAxiErr = mKh*(LPFIqc - LPFIdc);

	//位相推定器
	mEstThetaPII2.SetValue(mEstAxiErr);
	mEstThetaPII2.Calculate();
	mEstOmegaE = mEstThetaPII2.GetOmega();
	mTheta_c = fmod( ( mEstThetaPII2.GetTheta() + 2 * M_PI ) , ( 2 * M_PI ) );//theta % 2pi

}

float HFConvolution::GetEstOmegaE(void) {
	return mEstOmegaE;
}

float HFConvolution::GetTheta_c(void) {
	return mTheta_c;
}

//制御器設計Debug用
std::array<float,2> HFConvolution::GetConvIdqc(void) {
	return {mConvIdc, mConvIqc};
}

std::array<float,2> HFConvolution::GetIdqch(void) {
	return {mIdch, mIqch};
}
