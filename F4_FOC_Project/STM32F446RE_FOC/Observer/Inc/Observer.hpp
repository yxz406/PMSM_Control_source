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

class Observer {
private:

	AdaptVelEst mVelocityEst;
	EMFObs mEMFObserver;

	float mIalpha;
	float mIbeta;
	float mValpha;
	float mVbeta;

	float mCycleTime;

	float mEstOmegaE;
	float mEstTheta;

public:
	Observer();
	virtual ~Observer();

	//Initializer
	void AdaptVelEstInit(float pR, float pLd, float pLq, float pCycleTime, float pG1, float pG2, float pKp, float pKi);
	void EMFObsInit(float pG1);

	//Setter
	void SetIAlphaBeta(float pIalpha, float pIbeta);
	void SetVAlphaBeta(float pValpha, float pVbeta);
	void SetCycleTime(float pCycleTime);

	//Calculator
	void Calc();

	//Getter
	float GetEstTheta(void);
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
