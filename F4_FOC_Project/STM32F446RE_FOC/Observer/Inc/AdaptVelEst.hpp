/*
 * AdaptVelEst.hpp
 *
 *  Created on: Aug 31, 2019
 *      Author: watashi
 *
 *
 * This Class is "Adaptive Velocity Estimator".
 *
 * そくどをてきおうどうていするよ！！！
 *
 */

#ifndef INC_ADAPTVELEST_HPP_
#define INC_ADAPTVELEST_HPP_

#include <array>
#include "Matrix.hpp"
#include "ZIntegrate.hpp"
#include "Trigonometric.hpp"


class AdaptVelEst {
private:
	//input vector
	std::array<float, 2> mIAlphaBeta;
	std::array<float, 2> mVAlphaBeta;

	//motor param
	float mR;
	float mLd;
	float mLq;

	//Integrate Block Param
	float mCycleTime;

	//AdaptVelEst's Gain
	float mG1;
	float mG2;

	//出力段の謎ゲイン(いい名前教えて)
	float mKp;
	float mKi;

	//上のブロック内部状態変数
	std::array<float, 2> mBufVec1;
	std::array<float, 2> mBufVec2;
	std::array<float, 2> mBufVec3;
	std::array<float, 2> mBufVec4;
	std::array<float, 2> mBufVec5;
	std::array<float, 2> mBufVec6;
	Zintegrate2n mEtaAlphaBetaITG;
	std::array<float, 2> mEtaAlphaBeta;

	std::array<float, 2> mBufVec7;
	std::array<float, 2> mEstEmfAlphaBeta;

	//左下ブロック内部状態変数
	std::array<float, 2> mErrEmfAlphaBeta;
	std::array<float, 2> mBufVec8;
	std::array<float, 2> mBufVec9;
	std::array<float, 2> mBufVec10;
	std::array<float, 2> mBufVec11;
	Zintegrate2n mAdaptEmfAlphaBetaITG;
	std::array<float, 2> mAdaptEmfAlphaBeta;

	//右下ブロック内部状態変数
	std::array<float, 2> mBufVec12;
	float mBufVal1;
	float mBufVal2;
	float mBufVal3;
	Zintegrate1n mBufVal4ITG;
	float mBufVal4;

	//OutputValue
	float mEstOmegaE;

public:
	AdaptVelEst();
	virtual ~AdaptVelEst();

	//Initializer
	void MotorParamInit(float pR, float pLd, float pLq);
	void obsBiasInit(float pG1, float pG2, float pKp, float pKi);

	//Setter
	void SetIAlphaBeta(float pIalpha, float pIbeta);
	void SetVAlphaBeta(float pValpha, float pVbeta);
	void SetCycleTime(float pCycleTime);

	//Calculator
	void AdaptiveVelocityEstimator();//どうせ一回しか叩かないからクソ長くした

	//Getter
	float GetEstOmegaE(void);

};

#endif /* INC_ADAPTVELEST_HPP_ */
