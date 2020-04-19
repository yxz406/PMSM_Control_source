/*
 * SineWaveConvCalculator.cpp
 *
 *  Created on: Feb 18, 2020
 *      Author: watashi
 */

#include "SineWaveConvCalculator.hpp"

SineWaveConvCalculator::SineWaveConvCalculator()
{
	// TODO Auto-generated constructor stub

}

SineWaveConvCalculator::~SineWaveConvCalculator() {
	// TODO Auto-generated destructor stub
}


void SineWaveConvCalculator::LPFInit(float pGainB0, float pGainB1, float pGainA1) {
	mLPFIdc.Init(pGainB0, pGainB1, pGainA1);
	mLPFIqc.Init(pGainB0, pGainB1, pGainA1);
}

void SineWaveConvCalculator::SetKh(float pKh) {
	mKh = pKh;
}

void SineWaveConvCalculator::BPF_LPFInit(float pGainB0, float pGainB1, float pGainA1) {
	mBPF_LPFIdc.Init(pGainB0, pGainB1, pGainA1);
	mBPF_LPFIqc.Init(pGainB0, pGainB1, pGainA1);
}

void SineWaveConvCalculator::BPF_HPFInit(float pGainB0, float pGainB1, float pGainA1) {
	mBPF_HPFIdc.Init(pGainB0, pGainB1, pGainA1);
	mBPF_HPFIqc.Init(pGainB0, pGainB1, pGainA1);
}

//void SineWaveConvCalculator::InitCycleTime(float pCycleTime) {
//	mCycleTime = pCycleTime;
//}

void SineWaveConvCalculator::InitPhaseEstimator(float pCycleTime, float pK1, float pK2, float pK3) {
	mPhaseEstimator.InitCycleTime(pCycleTime);
	mPhaseEstimator.InitGainK1(pK1);
	mPhaseEstimator.InitGainK2(pK2);
	mPhaseEstimator.InitGainK3(pK3);
}


void SineWaveConvCalculator::SetIgdPair(const std::array<float, 2> &pIgd) {
	mIgd = pIgd;
}


void SineWaveConvCalculator::SetSinCosForDemodulation(const std::array<float, 2> &pSinCosForDemodulation) {
	mSinCosForDemodulation = pSinCosForDemodulation;
}

void SineWaveConvCalculator::Demodulation() {
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
}


void SineWaveConvCalculator::AngleCalculate() {
	Demodulation();

	//位相推定器
	mPhaseEstimator.SetValue(mEstAxiErr);
	mPhaseEstimator.Calculate();
	mEstOmegaE = mPhaseEstimator.GetOmega();
	mTheta_c = fmod( ( mPhaseEstimator.GetTheta() + 2 * M_PI ) , ( 2 * M_PI ) );//theta % 2pi

}

float SineWaveConvCalculator::GetEstOmegaE(void) {
	return mEstOmegaE;
}

float SineWaveConvCalculator::GetTheta_c(void) {
	return mTheta_c;
}

//制御器設計Debug用
std::array<float,2> SineWaveConvCalculator::GetConvIdqc(void) {
	return {mConvIdc, mConvIqc};
}

std::array<float,2> SineWaveConvCalculator::GetIdqch(void) {
	return {mIdch, mIqch};
}

