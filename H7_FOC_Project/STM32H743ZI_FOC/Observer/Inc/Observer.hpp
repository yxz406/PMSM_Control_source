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

	float mEstOmegaE;
	float mEstTheta;

public:
	Observer();
	virtual ~Observer();

	//Initializer
	void InitEMFObs(float pCycleTime, float pR, float pLd, float pLq, float pGainAlpha);
	void InitPII2(float pCycleTime, float pK1, float pK2, float pK3);

	//Setter
	void SetIGanmaDelta(std::array<float, 2> pIGanmaDelta);
	void SetVGanmaDelta(std::array<float, 2> pVGanmaDelta);

	//Calculator
	void Calculate();

	//Getter
	float GetEstTheta(void);
	float GetEstOmegaE(void);
};

#endif /* OBSERVER_HPP_ */
