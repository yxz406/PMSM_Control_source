/*
 * Observer.hpp
 *
 *  Created on: Aug 20, 2019
 *      Author: watashi
 */

#ifndef OBSERVER_HPP_
#define OBSERVER_HPP_

#include "AdaptVelEst.hpp"
#include "EMFObs.hpp"
#include "EstimatedAxisError.hpp"
#include "PII2.hpp"

class Observer {
private:
	EMFObs mEMFObserver;
	PII2 mEstThetaPII2;

	std::array<float, 2> mIGanmaDelta;
	std::array<float, 2> mVGanmaDelta;

	float mCycleTime;

	float mEstAxiErr;
	float mEstOmegaE;
	float mEstTheta;


	//for debug;
	std::array<float, 2> mEstEMFgd;

public:
	Observer();
	virtual ~Observer();

	//Initializer
	void InitEMFObs(float pCycleTime, float pR, float pLd, float pLq, float pGainAlpha);
	void InitPII2(float pCycleTime, float pK1, float pK2, float pK3);

	//Setter
	void SetIGanmaDelta(const std::array<float, 2> &pIGanmaDelta);
	void SetVGanmaDelta(const std::array<float, 2> &pVGanmaDelta);

	//Calculator
	void Calculate();
	void CalculateOpenLoop(const float &pOmegaE, const float &pThetaE);

	//Getter
	float GetEstTheta(void);
	float GetEstOmegaE(void);
	float GetEstAxiErr(void);

	//debug Get
	std::array<float, 2> GetIgd(void);
	std::array<float, 2> GetVgd(void);
	std::array<float, 2> GetEstEMFgd(void);
};

#endif /* OBSERVER_HPP_ */
