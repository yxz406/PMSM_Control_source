/*
 * AdaptVelEst.hpp
 *
 *  Created on: 2019/08/29
 *      Author: watashi
 */

#ifndef INC_ADAPTVELEST_HPP_
#define INC_ADAPTVELEST_HPP_

class AdaptVelEst {
public:
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

	float mCycleTime;

	float mG1;
	float mG2;


	//input vector
	std::array<float, 2> mIalpha_beta;
	std::array<float, 2> mValpha_beta;

	//vector for calc
	float adapt_emf_ab; //v9

	//float eta;//v21

	float mEstOmegaE;//out value

	std::array<float, 2> mBufVec1;
	std::array<float, 2> mv2;
	std::array<float, 2> mv3;

	Zintegrate2n mEta_abIntegrate;
	std::array<float, 2> mEta_ab;//v4
	std::array<float, 2> mEstEmf_ab;//v5

	std::array<float, 2> mErrEmf_ab;//v6

	std::array<float, 2> mv7;
	std::array<float, 2> mv8;
	Zintegrate2n mv9Integrate;
	std::array<float, 2> mv9;

	std::array<float, 2> mBufVec10;

	std::array<float, 2> mJv9;
	float mVal11;
	float mVal12;
	float mKi;//一体これはなんのゲインのK?
	float mKp;//これも

	Zintegrate1n mVal13Integrate;
	float mVal13;

public:

	AdaptVelEst();
	virtual ~AdaptVelEst();

	//Init
	void MotorParamInit(float pR, float pLd, float pLq);
	void obsBiasInit(float pG1);

	//Setter
	void SetIalpha_beta(float pIalpha, float pIbeta);
	void SetValpha_beta(float pValpha, float pVbeta);
	void SetCycleTime(float pCycleTime);

	//Getter
	float GetEstTheta(void);

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

#endif /* INC_ADAPTVELEST_HPP_ */
