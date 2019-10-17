/*
 * AdaptVelEst.cpp
 *
 *  Created on: Aug 31, 2019
 *      Author: watashi
 */

#include <AdaptVelEst.hpp>

AdaptVelEst::AdaptVelEst()
:mEtaAlphaBetaITG(1), mAdaptEmfAlphaBetaITG(1), mBufVal4ITG(1)
{
	// TODO Auto-generated constructor stub
	//オブジェクト生成時に必ず0埋めすること.
	mBufVec1 = {0};
	mBufVec2 = {0};
	mBufVec3 = {0};
	mBufVec4 = {0};
	mBufVec5 = {0};
	mBufVec6 = {0};
	mEtaAlphaBeta = {0};
	mBufVec7 = {0};
	mEstEmfAlphaBeta = {0};
	mErrEmfAlphaBeta = {0};
	mBufVec8 = {0};
	mBufVec9 = {0};
	mBufVec10 = {0};
	mBufVec11 = {0};
	mAdaptEmfAlphaBeta = {0};
	mBufVec12 = {0};

	mBufVal1 = 0;
	mBufVal2 = 0;
	mBufVal3 = 0;
	mBufVal4 = 0;
	mEstOmegaE = 0;
}
AdaptVelEst::~AdaptVelEst() {
	// TODO Auto-generated destructor stub
}

//Initializer
void AdaptVelEst::MotorParamInit(float pR, float pLd, float pLq) {
	mR = pR;
	mLd = pLd;
	mLq = pLq;
}
void AdaptVelEst::obsBiasInit(float pG1, float pG2, float pKp, float pKi) {
	mG1 = pG1;
	mG2 = pG2;
	mKp = pKp;
	mKi = pKi;
}

//Setter
void AdaptVelEst::SetIAlphaBeta(float pIalpha, float pIbeta){
	mIAlphaBeta.at(0) = pIalpha;
	mIAlphaBeta.at(1) = pIbeta;
}
void AdaptVelEst::SetVAlphaBeta(float pValpha, float pVbeta){
	mVAlphaBeta.at(0) = pValpha;
	mVAlphaBeta.at(1) = pVbeta;
}
void AdaptVelEst::SetCycleTime(float pCycleTime) {
	mCycleTime = pCycleTime;
}

//Calculator
void AdaptVelEst::AdaptiveVelocityEstimator () {

	//上のブロック
	mBufVec1 = Matrix::MatrixMultiple2x2(       -1 * mR / mLd * mG1, -1 * (1 - mLq/mLd) * mEstOmegaE,
									     (1 - mLq/mLd) * mEstOmegaE, -1 * mR / mLd * mG1,
										 mIAlphaBeta);
	mBufVec2 = Matrix::VectorMultiple2x1((float)-mG1/mLd, mIAlphaBeta);
	mBufVec3 = Matrix::VectorAdd2x1(mBufVec1, Matrix::VectorMultiple2x1(-1, mBufVec2) );
	mBufVec4 = Matrix::VectorMultiple2x1(mG1/mLd, mVAlphaBeta);
	mBufVec5 = Matrix::VectorMultiple2x1(-1 * mG1/mLd, mEtaAlphaBeta);
	mBufVec6 = Matrix::VectorAdd2x1(mBufVec3, mBufVec4, mBufVec5);
	mEtaAlphaBeta = mEtaAlphaBetaITG.integrate(mCycleTime, mBufVec6);

	mBufVec7 = Matrix::VectorMultiple2x1(mG1, mIAlphaBeta);
	mEstEmfAlphaBeta = Matrix::VectorSubtract2x1(mEtaAlphaBeta, mBufVec7);

	//下のブロック
	//左下スタート
	mErrEmfAlphaBeta = Matrix::VectorSubtract2x1(mEstEmfAlphaBeta, mAdaptEmfAlphaBeta);
	mBufVec8 = Matrix::MatrixMultiple2x2( mG1, -1 * mG2,
          								  mG2, mG1,
										  mErrEmfAlphaBeta);

	mBufVec9 = Matrix::MatrixMultiple2x2( 0, -1,
			  	  	  	  	  	  	  	  1,  0,
										  mAdaptEmfAlphaBeta);
	mBufVec10 = Matrix::VectorMultiple2x1(mEstOmegaE, mBufVec9);
	mBufVec11 = Matrix::VectorAdd2x1(mBufVec8, mBufVec10);
	mAdaptEmfAlphaBeta = mAdaptEmfAlphaBetaITG.integrate(mCycleTime, mBufVec11);

	//左下終わり
	//右下スタート
	mBufVec12 = Matrix::MatrixMultiple2x2( 0, -1,
			  	  	  	  	  	  	  	  1,  0,
										  mAdaptEmfAlphaBeta);
	mBufVal1 = Matrix::VectorMultiple1x2_2x1(mErrEmfAlphaBeta, mBufVec12);
	mBufVal2 = mBufVal1 * mKp;
	mBufVal3 = mBufVal1 * mKi;
	mBufVal4 = mBufVal4ITG.integrate(mCycleTime, mBufVal3);
	mEstOmegaE = mBufVal2 + mBufVal4;
}

//Getter
float AdaptVelEst::GetEstOmegaE(void) {
	return mEstOmegaE;
}
