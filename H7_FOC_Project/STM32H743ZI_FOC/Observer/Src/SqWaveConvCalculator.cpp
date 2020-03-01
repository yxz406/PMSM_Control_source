/*
 * SqWaveConvCalculator.cpp
 *
 *  Created on: Feb 18, 2020
 *      Author: watashi
 */

#include "SqWaveConvCalculator.hpp"


SqWaveConvCalculator::SqWaveConvCalculator()
{
	// TODO Auto-generated constructor stub

}

SqWaveConvCalculator::~SqWaveConvCalculator() {
	// TODO Auto-generated destructor stub
}

void SqWaveConvCalculator::SetKh(float pKh) {
	mKh = pKh;
}

void SqWaveConvCalculator::HPFInit(float pGainB0, float pGainB1, float pGainA1) {
	mHPFIqc.Init(pGainB0, pGainB1, pGainA1);
}


void SqWaveConvCalculator::InitPhaseEstimator(float pCycleTime, float pK1, float pK2, float pK3) {
	mPhaseEstimator.InitCycleTime(pCycleTime);
	mPhaseEstimator.InitGainK1(pK1);
	mPhaseEstimator.InitGainK2(pK2);
	mPhaseEstimator.InitGainK3(pK3);
}


void SqWaveConvCalculator::SetIgdPair(const std::array<float, 2> &pIgd) {
	mIgd = pIgd;
}

void SqWaveConvCalculator::SetSqWave(const float &pSqWave) {
	mSqWave = pSqWave;
}

void SqWaveConvCalculator::Demodulation() {

	float DemodulateVal = 0;
	//DemodulateVal = sign(Vdch)
	if(mSqWave > 0) {
		DemodulateVal = mSqWave;
	} else {
		DemodulateVal = -mSqWave;
	}

	float oldSqWave = mSqWaveDelay.GetOldVal();
	mSqWaveDelay.SetVal(DemodulateVal);

	//BPF
	float mIqch = mHPFIqc.Output(mIgd.at(1));

	float IqchOld = mIqchDelay.GetOldVal();
	mIqchDelay.SetVal(mIqch);

	//ヘテロダイン
	float buf = mIqch - IqchOld;
	float output = buf + oldSqWave;

	//モータのパラメタの倍率調整
	mEstAxiErr = mKh * output;

}

void SqWaveConvCalculator::AngleCalculate() {
	Demodulation();
	//位相推定器
	mPhaseEstimator.SetValue(mEstAxiErr);
	mPhaseEstimator.Calculate();
	mEstOmegaE = mPhaseEstimator.GetOmega();
	mTheta_c = fmod( ( mPhaseEstimator.GetTheta() + 2 * M_PI ) , ( 2 * M_PI ) );//theta % 2pi

}

float SqWaveConvCalculator::GetEstOmegaE(void) {
	return mEstOmegaE;
}

float SqWaveConvCalculator::GetTheta_c(void) {
	return mTheta_c;
}

//制御器設計Debug用
std::array<float,2> SqWaveConvCalculator::GetConvIdqc(void) {
	return {mConvIdc, mConvIqc};
}

std::array<float,2> SqWaveConvCalculator::GetIdqch(void) {
	return {mIdch, mIqch};
}



