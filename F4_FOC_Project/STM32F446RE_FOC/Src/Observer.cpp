/*
 * Observer.cpp
 *
 *  Created on: Aug 20, 2019
 *      Author: watashi
 */

#include "Observer.hpp"


////////////離散的積分ブロックの演算のためのClass////////////

void Observer::Zintegrate1n::ZintegrateInit(float pK){
	mValue = 0;
	mOldVal = 0;
	mK = pK;
}

float Observer::Zintegrate1n::integrate(float pTime, float pValue) {
	mOldVal = mValue;
	mValue = mOldVal + mK * pTime * pValue;
	return mOldVal;
}


void Observer::Zintegrate2n::ZintegrateInit(float pK){
	mVector = {0};
	mOldVec = {0};
	mK = pK;
}

std::array<float, 2> Observer::Zintegrate2n::integrate(float pTime, std::array<float, 2> pVector) {
	mOldVec.at(0) = mVector.at(0);
	mOldVec.at(1) = mVector.at(1);
	mVector.at(0) = mOldVec.at(0) + mK * pTime * pVector.at(0);
	mVector.at(1) = mOldVec.at(1) + mK * pTime * pVector.at(1);
	return mOldVec;
}
///////////////////////////////////////////////////////

Observer::Observer() {
	// TODO Auto-generated constructor stub

}

Observer::~Observer() {
	// TODO Auto-generated destructor stub
}

void Observer::MotorParamInit(float pR, float pLd, float pLq) {
	mR = pR;
	mLd = pLd;
	mLq = pLq;
}

void Observer::obsBiasInit(float pG1) {
	mG1 = pG1;
}

void Observer::SetIalpha_beta(float pIalpha, float pIbeta){
	mIalpha_beta.at(0) = pIalpha;
	mIalpha_beta.at(1) = pIbeta;
}
void Observer::SetValpha_beta(float pValpha, float pVbeta){
	mValpha_beta.at(0) = pValpha;
	mValpha_beta.at(1) = pVbeta;
}

std::array<float, 2> Observer::MatrixMultiple2n(float pa11, float pa12,
	                    				float pa21, float pa22,
										std::array<float, 2> pVector) {

	std::array<float, 2> vector;
	vector.at(0) = pa11 * pVector.at(0) + pa12 * pVector.at(1);
	vector.at(1) = pa21 * pVector.at(0) + pa22 * pVector.at(1);

	return vector;
}

std::array<float, 2> Observer::VectorMultiple2n(float pGain, std::array<float, 2> pVector) {

	std::array<float, 2> vector;
	vector.at(0) = pGain * pVector.at(0);
	vector.at(1) = pGain * pVector.at(1);

	return vector;
}

std::array<float, 2> Observer::VectorAdd2n(std::array<float, 2> pVector1, std::array<float, 2> pVector2) {

	std::array<float, 2> vector;
	vector.at(0) = pVector1.at(0) + pVector2.at(0);
	vector.at(1) = pVector1.at(1) + pVector2.at(1);

	return vector;
}

float Observer::VectorMultiple12_21(std::array<float, 2>pVector1, std::array<float, 2> pVector2) {

	float sum;
	sum = pVector1.at(0) * pVector2.at(0) + pVector1.at(1) * pVector2.at(1);

	return sum;
}


//std::array<float, 2> Observer::Zintegrate2n(float pTime, std::array<float, 2> pVector) {
//
//	std::array<float, 2> vector;
//	vector.at(0) = pVector1.at(0) + pVector2.at(0);
//	vector.at(1) = pVector1.at(1) + pVector2.at(1);
//
//	return vector;
//}



void Observer::calc(float pTime) {

	mv1 = MatrixMultiple2n(      -1 * mR / mLd * mG1, -1 * (1 - mLq/mLd) * mEstOmegaE,
			              (1 - mLq/mLd) * mEstOmegaE, -1 * mR / mLd * mG1,
				          mIalpha_beta);


	std::array<float, 2> vecbuf1;//可読性向上のためのbuff
	vecbuf1 = VectorMultiple2n((float)-mG1/mLd, mIalpha_beta);

	mv2 = VectorAdd2n(mv1, VectorMultiple2n(-1, mIalpha_beta) );

	std::array<float, 2> vecbuf2;
	//vecbuf2 = VectorAdd2n
	vecbuf2 = VectorAdd2n(VectorMultiple2n(mG1/mLd, mValpha_beta),VectorMultiple2n(mG1,mv2));

	mv3 = VectorAdd2n(vecbuf2, mEta_ab);

	mEta_ab = mEta_abIntegrate.integrate(pTime, mv3);

	mEstEmf_ab = VectorAdd2n(mEta_ab, VectorMultiple2n(-mG1, mIalpha_beta) );

	///////下のブロック

	mErrEmf_ab = VectorAdd2n(mEstEmf_ab, VectorMultiple2n(-1, mv9) );

	mv7 = MatrixMultiple2n( mG1, -1 * mG2,
			              	mG2, mG1,
							mErrEmf_ab);

	mv8 = VectorAdd2n(mv7, mv10);

	mv9 = mv9Integrate.integrate(pTime, mv8);

	////
	mJv9 =  MatrixMultiple2n( 0, -1,
          					  1,  0,
							  mv9);

	mVal11 = VectorMultiple12_21(mErrEmf_ab, mJv9);

	mVal12 = mKi * mVal11;

	mVal13 = mVal13Integrate.integrate(pTime, mVal12);

	mEstOmegaE = mKp * mVal11 + mVal13;
	//////

	mv10 = VectorMultiple2n(mEstOmegaE, mJv9);


	//拡張誘起電圧オブザーバ
	mv15 = VectorMultiple2n(mAlpha, mVganma_delta);

	mv16 = MatrixMultiple2n(       -1 * mR / mLd * mG1, -1 * (1 - mLq/mLd) * mEstOmegaE,
					        (1 - mLq/mLd) * mEstOmegaE, -1 * mR / mLd * mG1,
							mIganma_delta);
	//このA11が正しいか検証すること.

	mv17 = VectorMultiple2n(mAlpha * mLd, mIganma_delta);

	mv18 = VectorMultiple2n(-1 * mAlpha, mIganma_delta);

	mv19 = VectorAdd2n(mv16, VectorMultiple2n(-1, mv18));

	mv20 = VectorAdd2n( VectorMultiple2n(mAlpha * mLd, mv19), VectorAdd2n(mv15, mv22) );

	mEta = mEtaIntegrate.integrate(pTime, mv20);

	mv22 = VectorMultiple2n(-1 * mAlpha, mEta);

	mv23 = VectorAdd2n( mEta, VectorMultiple2n(-1, mv17) );

	float Numerator = mv23.at(0);
	float Denominator = mv23.at(1);

	mVal24 = atan2(Numerator, Denominator);

	mVal26 = mVal26Integrate.integrate( pTime, mK2 * mVal24 );

	mVal28 = mVal28Integrate.integrate( pTime, mK3 * mVal24 );
	mVal29 = mVal29Integrate.integrate( pTime, mVal28 );

	mEstTheta = (mK1 * mVal24) + mVal26 + mVal29;
}
