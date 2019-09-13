/*
 * Observer.cpp
 *
 *  Created on: Aug 20, 2019
 *      Author: watashi
 */

#include "Observer.hpp"

Observer::Observer() {
	// TODO Auto-generated constructor stub
}

Observer::~Observer() {
	// TODO Auto-generated destructor stub
}

//Initializer
void Observer::InitEMFObs(float pCycleTime, float pR, float pLd, float pLq, float pG1, float pGainAlpha) {
	mEMFObserver.InitCycleTime(pCycleTime);
	mEMFObserver.InitMotorParam(pR, pLd, pLq);
	mEMFObserver.InitModelGain(pG1);
	mEMFObserver.InitObsGain(pGainAlpha);
}

void Observer::InitPII2(float pCycleTime, float pK1, float pK2, float pK3) {
	mEstThetaPII2.InitCycleTime(pCycleTime);
	mEstThetaPII2.InitGainK1(pK1);
	mEstThetaPII2.InitGainK2(pK2);
	mEstThetaPII2.InitGainK3(pK3);
}

//Setter
void Observer::SetIGanmaDelta(std::array<float, 2> pIGanmaDelta) {
	mIGanmaDelta = pIGanmaDelta;
}
void Observer::SetVGanmaDelta(std::array<float, 2> pVGanmaDelta) {
	mVGanmaDelta = pVGanmaDelta;
}

//Calculator
void Observer::Calculate() {
	mEMFObserver.SetIgd(mIGanmaDelta);
	mEMFObserver.SetVgd(mVGanmaDelta);
	mEMFObserver.EMFObserver();
	std::array<float, 2> EstEMFgd = mEMFObserver.GetEstEMFgd();
	float EstAxiErr = EstimatedAxisError::GetError(EstEMFgd);
	mEstThetaPII2.SetValue(EstAxiErr);
	mEstThetaPII2.Calculate();
	float EstOmegaE = mEstThetaPII2.GetPIVal();
	mEMFObserver.SetEstOmegaE(EstOmegaE);
	mEstTheta = mEstThetaPII2.GetValue();
}

//Getter
float Observer::GetEstTheta(void) {
	return mEstTheta;
}
