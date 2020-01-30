/*
 * HFConvolution.hpp
 *
 *  Created on: 2020/01/05
 *      Author: watashi
 */

#ifndef SRC_HFCONVOLUTION_HPP_
#define SRC_HFCONVOLUTION_HPP_

#include <array>
#include "ZIntegrate.hpp"
#include "LPF.hpp"
#include "BPF.hpp"
#include "HPF.hpp"
#include "PII2.hpp"

class HFConvolution {
private:
	std::array<float, 2> mIgd; //単位[A]
	std::array<float, 2> mSinCosForDemodulation;

	float mCycleTime;

	LPF mLPFIdc;
	LPF mLPFIqc;
	BPF mBPFIdc;
	BPF mBPFIqc;

	LPF mBPF_LPFIdc;
	LPF mBPF_LPFIqc;
	HPF mBPF_HPFIdc;
	HPF mBPF_HPFIqc;


	//倍率
	float mKh;

	//計算用
	float mIdch = 0;
	float mIqch = 0;


	float mConvIdc=0;
	float mConvIqc=0;

	float mEstAxiErr=0;

	PII2 mEstThetaPII2;

	float mTheta_c;

public:
	HFConvolution();
	virtual ~HFConvolution();

	void InitCycleTime(float pCycleTime);
	void InitPII2(float pCycleTime, float pK1, float pK2, float pK3);
	void LPFInit(float pGainB0, float pGainB1, float pGainA1);
	void SetKh(float pKh);
	void BPFInit(float pGainB0, float pGainB2, float pGainA1, float pGainA2);

	void BPF_LPFInit(float pGainB0, float pGainB1, float pGainA1);
	void BPF_HPFInit(float pGainB0, float pGainB1, float pGainA1);

	void SetIgdPair(const std::array<float, 2> &pIgd);
	void SetSinCosForDemodulation(const std::array<float, 2> &pSinCosForDemodulation);

	void Calculate();

	float GetTheta_c(void);

	//制御器設計Debug用
	std::array<float,2> GetConvIdqc(void);

	std::array<float,2> GetIdqch(void);


};

#endif /* SRC_HFCONVOLUTION_HPP_ */
