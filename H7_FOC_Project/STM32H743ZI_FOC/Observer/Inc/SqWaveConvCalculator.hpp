/*
 * SqWaveConvCalculator.hpp
 *
 *  Created on: Feb 18, 2020
 *      Author: watashi
 */

#ifndef INC_SQWAVECONVCALCULATOR_HPP_
#define INC_SQWAVECONVCALCULATOR_HPP_

#include <array>
#include "ZIntegrate.hpp"
#include "LPF.hpp"
#include "HPF.hpp"
#include "PhaseEstimator.hpp"
#include "UnitDelay.hpp"


class SqWaveConvCalculator {
private:
	std::array<float, 2> mIgd; //単位[A]
	float mSqWave = 0;

	HPF mHPFIqc;

	//計算用
	float mIdch = 0;
	float mIqch = 0;
	UnitDelay mIqchDelay;

	float mConvIdc=0;
	float mConvIqc=0;

	UnitDelay mSqWaveDelay;

	float mEstAxiErr=0;

	float mKh = 0;

	PhaseEstimator mPhaseEstimator;

	float mEstOmegaE = 0;
	float mTheta_c = 0;

public:
	SqWaveConvCalculator();
	virtual ~SqWaveConvCalculator();

//	void InitCycleTime(float pCycleTime);
	void InitPhaseEstimator(float pCycleTime, float pK1, float pK2, float pK3);
//	void LPFInit(float pGainB0, float pGainB1, float pGainA1);
	void SetKh(float pKh);

	//void BPF_LPFInit(float pGainB0, float pGainB1, float pGainA1);
	void HPFInit(float pGainB0, float pGainB1, float pGainA1);

	void SetIgdPair(const std::array<float, 2> &pIgd);
	void SetSqWave(const float &pSqWave);
//	void SetSinCosForDemodulation(const std::array<float, 2> &pSinCosForDemodulation);

	void Demodulation();
	void AngleCalculate();

	float GetEstOmegaE(void);
	float GetTheta_c(void);

	//制御器設計Debug用
	std::array<float,2> GetConvIdqc(void);

	std::array<float,2> GetIdqch(void);


};

#endif /* INC_SQWAVECONVCALCULATOR_HPP_ */
