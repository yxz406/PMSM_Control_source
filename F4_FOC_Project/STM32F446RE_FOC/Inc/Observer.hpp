/*
 * Observer.hpp
 *
 *  Created on: Aug 20, 2019
 *      Author: watashi
 */

#ifndef OBSERVER_HPP_
#define OBSERVER_HPP_

#include <array>
#include "paramsetting.h"
#include "math.h"

#define ARM_MATH_CM4
#include "arm_math.h"
#include "arm_const_structs.h"


class Observer {
public://pub-class

	class Zintegrate1n{
	private:
		float mK;
		float mValue;
		float mOldVal;
	public:
		void ZintegrateInit(float pK);
		float integrate(float pTime, float pValue);
	};

	class Zintegrate2n{
	private:
		float mK;
		std::array<float, 2> mVector;
		std::array<float, 2> mOldVec;
	public:
		void ZintegrateInit(float pK);
		std::array<float, 2> integrate(float pTime, std::array<float, 2> pVector);
	};

private:
	//motor param
	float mR;
	float mLd;
	float mLq;

	float mG1;
	float mG2;


	float mAlpha;

	//input vector
	std::array<float, 2> mIalpha_beta;
	std::array<float, 2> mValpha_beta;

	std::array<float, 2> mIganma_delta;
	std::array<float, 2> mVganma_delta;


	//vector for calc
	//float eta_ab;
	//float mEst_emf_ab;
	//float error_emf_ab;

	float adapt_emf_ab;
	//float est_omega_ele;

	//float mEstOmegaE;

	float eta;
	float mEst_emf;
	float est_theta;
//////////////////////

	float mEstOmegaE;

	std::array<float, 2> mv1;
	std::array<float, 2> mv2;
	std::array<float, 2> mv3;

	Zintegrate2n mEta_abIntegrate;
	std::array<float, 2> mEta_ab;
	std::array<float, 2> mEstEmf_ab;

	std::array<float, 2> mErrEmf_ab;

	std::array<float, 2> mv7;
	std::array<float, 2> mv8;
	Zintegrate2n mv9Integrate;
	std::array<float, 2> mv9;

	std::array<float, 2> mv10;

	std::array<float, 2> mJv9;
	float mVal11;
	float mVal12;
	float mKi;//一体これはなんのゲインのK?
	float mKp;//これも

	Zintegrate1n mVal13Integrate;
	float mVal13;


	//拡張誘起電圧オブザーバ
	std::array<float, 2> mv15;
	std::array<float, 2> mv16;
	std::array<float, 2> mv17;
	std::array<float, 2> mv18;
	std::array<float, 2> mv19;

	std::array<float, 2> mv20;

	Zintegrate2n mEtaIntegrate;
	std::array<float, 2> mEta;
	std::array<float, 2> mv22;

	std::array<float, 2> mv23;

	float mVal24;

	float mK1;
	float mK2;
	float mK3;

	Zintegrate1n mVal26Integrate;
	float mVal26;
	Zintegrate1n mVal28Integrate;
	float mVal28;
	Zintegrate1n mVal29Integrate;
	float mVal29;

	float mEstTheta;

public:
	Observer();
	virtual ~Observer();
	void func();
	void MotorParamInit(float pR, float pLd, float pLq);
	void obsBiasInit(float pG1);

	void SetIalpha_beta(float pIalpha, float pIbeta);
	void SetValpha_beta(float pValpha, float pVbeta);


	std::array<float, 2> MatrixMultiple2n(float pa11, float pa12,
								  float pa21, float pa22,
								  std::array<float, 2> pVector);
	std::array<float, 2> VectorMultiple2n(float pGain, std::array<float, 2> pVector);
	std::array<float, 2> VectorAdd2n(std::array<float, 2> pVector1, std::array<float, 2> pVector2);
	std::array<float, 2> Zintegrate2n(float pTime, std::array<float, 2> pVector);//これは構造体・Classが必要
	float VectorMultiple12_21(std::array<float, 2> pVector1, std::array<float, 2> pVector2);


	void calc(float pTime);

	float atan2(float pNumerator, float pDenominator);
};

#endif /* OBSERVER_HPP_ */


//miyayu月曜日 20:59
//意味がありそうなのはこんなもんですかね。
//K=1
//v4→eta_ab
//v5→est_emf_ab
//v6→error_emf_ab
//v9→adapt_emf_ab
//v14→est_omega_ele
//
//v21→eta
//v23→est_emf
//v24→est_delTheta
//v30→est_Theta
