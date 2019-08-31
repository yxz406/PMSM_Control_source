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

//Setter
void Observer::SetIAlphaBeta(float pIalpha, float pIbeta){
	mIalpha = pIalpha;
	mIbeta = pIbeta;
}
void Observer::SetVAlphaBeta(float pValpha, float pVbeta){
	mValpha = pValpha;
	mVbeta = pVbeta;
}
void Observer::SetCycleTime(float pCycleTime) {
	mCycleTime = pCycleTime;
}

//Initializer
void Observer::AdaptVelEstInit(float pR, float pLd, float pLq, float pCycleTime, float pG1, float pG2, float pKp, float pKi) {
	//サイクルタイムの設定
	mVelocityEst.SetCycleTime(pCycleTime);
	mVelocityEst.MotorParamInit(pR, pLd, pLq);
	mVelocityEst.obsBiasInit(pG1, pG2, pKp, pKi);
}

//Calculator
void Observer::Calc() {

	mVelocityEst.SetIAlphaBeta(mIalpha, mIbeta);
	mVelocityEst.SetVAlphaBeta(mValpha, mVbeta);
	mVelocityEst.AdaptiveVelocityEstimator();
	mEstOmegaE = mVelocityEst.GetEstOmegaE();
}

//Getter
float Observer::GetEstTheta(void) {
	return mEstTheta;
}
