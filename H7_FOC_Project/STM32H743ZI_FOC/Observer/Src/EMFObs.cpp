/*
 * EMFObs.cpp
 *
 *  Created on: Aug 29, 2019
 *      Author: watashi
 */

#include "EMFObs.hpp"

EMFObs::EMFObs() {
	// TODO Auto-generated constructor stub

}

EMFObs::~EMFObs() {
	// TODO Auto-generated destructor stub
}

//Initializer
void EMFObs::InitMotorParam(float pR,float pLd, float pLq) {
	mR = pR;
	mLd = pLd;
	mLq = pLq;
}

void EMFObs::InitCycleTime(float pCycleTime) {
	mCycleTime = pCycleTime;
}

void EMFObs::InitObsGain(float pGainAlpha) {
	mGainAlpha = pGainAlpha;
}

//Setter
void EMFObs::SetIgd(std::array<float, 2> pIGanmaDelta) {
	mIGanmaDelta = pIGanmaDelta;
}
void EMFObs::SetVgd(std::array<float, 2> pVGanmaDelta) {
	mVGanmaDelta = pVGanmaDelta;
}
void EMFObs::SetEstOmegaE(float pEstOmegaE) {
	mEstOmegaE = pEstOmegaE;
}

//Calculator
void EMFObs::EMFObserver() {
	//拡張誘起電圧オブザーバ
	mBufVec1 = Matrix::MatrixMultiple2x2(   	    -1.0f * mR / mLd, mLq/mLd * mEstOmegaE,
										 -1.0f* mLq/mLd * mEstOmegaE, -1.0f * mR / mLd,
										 mIGanmaDelta);
	//このA11が正しいか検証すること.

	mBufVec2 = Matrix::VectorMultiple2x1(mGainAlpha, mIGanmaDelta);

	mBufVec3 = Matrix::VectorAdd2x1(mBufVec1, mBufVec2);

	mBufVec4 = Matrix::VectorMultiple2x1(mGainAlpha * mLd, mBufVec3);

	mBufVec5 = Matrix::VectorMultiple2x1(mGainAlpha, mVGanmaDelta);

	mBufVec6 = Matrix::VectorAdd2x1(mBufVec4, mBufVec5, mBufVec8);

	mBufVec7 = mBufVec7ITG.integrate(mCycleTime, mBufVec6);

	mBufVec8 = Matrix::VectorMultiple2x1(-1.0f * mGainAlpha, mBufVec7);

	mEstEMFgd = Matrix::VectorSubtract2x1(mBufVec7, Matrix::VectorMultiple2x1(mLd, mBufVec2) );
				
}

//Getter
std::array<float, 2> EMFObs::GetEstEMFgd(void) {
	return mEstEMFgd;
}

