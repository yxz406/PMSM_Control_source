/*
 * EMFObs.hpp
 *
 *  Created on: Aug 29, 2019
 *      Author: watashi
 */

#ifndef INC_EMFOBS_HPP_
#define INC_EMFOBS_HPP_

#include "Matrix.hpp"
#include "ZIntegrate.hpp"
#include "Trigonometric.hpp"

class EMFObs {
private:
	//input value
	float mEstOmegaE;

	//input vector
	std::array<float, 2> mVGanmaDelta;
	std::array<float, 2> mIGanmaDelta;

	//motor param
	float mR;
	float mLd;
	float mLq;

	//Integrate Block Param
	float mCycleTime;

	//Gain
	float mGainAlpha;

	//内部状態変数
	std::array<float, 2> mBufVec1;
	std::array<float, 2> mBufVec2;
	std::array<float, 2> mBufVec3;
	std::array<float, 2> mBufVec4;
	std::array<float, 2> mBufVec5;
	std::array<float, 2> mBufVec6;
	Zintegrate2n mBufVec7ITG;
	std::array<float, 2> mBufVec7;
	std::array<float, 2> mBufVec8;
	std::array<float, 2> mEstEMFgd;

public:
	EMFObs();
	virtual ~EMFObs();

	//Initializer
	void InitMotorParam(float pR,float pLd, float pLq);
	void InitCycleTime(float pCycleTime);
	void InitObsGain(float pGainAlpha);
	void InitModelGain(float pG1);

	//Setter
	void SetIgd(const std::array<float, 2> &pIGanmaDelta);
	void SetVgd(const std::array<float, 2> &pVGanmaDelta);
	void SetEstOmegaE(const float &pEstOmegaE);

	//Calculator
	void EMFObserver();

	//Getter
	std::array<float, 2> GetEstEMFgd(void);

	//Debug Getter
	float GetInputEstOmegaE(void);
};

#endif /* INC_EMFOBS_HPP_ */
