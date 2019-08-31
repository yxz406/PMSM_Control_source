/*
 * EMFObs.cpp
 *
 *  Created on: Aug 29, 2019
 *      Author: watashi
 */

#include <EMFObs.hpp>

EMFObs::EMFObs() {
	// TODO Auto-generated constructor stub

}

EMFObs::~EMFObs() {
	// TODO Auto-generated destructor stub
}

////拡張誘起電圧オブザーバ
//mv15 = VectorMultiple2n(mAlpha, mVganma_delta);
//
//mv16 = MatrixMultiple2n(       -1 * mR / mLd * mG1, -1 * (1 - mLq/mLd) * mEstOmegaE,
//				        (1 - mLq/mLd) * mEstOmegaE, -1 * mR / mLd * mG1,
//						mIganma_delta);
////このA11が正しいか検証すること.
//
//mv17 = VectorMultiple2n(mAlpha * mLd, mIganma_delta);
//
//mv18 = VectorMultiple2n(-1 * mAlpha, mIganma_delta);
//
//mv19 = VectorAdd2n(mv16, VectorMultiple2n(-1, mv18));
//
//mv20 = VectorAdd2n( VectorMultiple2n(mAlpha * mLd, mv19), VectorAdd2n(mv15, mv22) );
//
//mEta = mEtaIntegrate.integrate(pTime, mv20);
//
//mv22 = VectorMultiple2n(-1 * mAlpha, mEta);
//
//mv23 = VectorAdd2n( mEta, VectorMultiple2n(-1, mv17) );
//
//float Numerator = mv23.at(0);
//float Denominator = mv23.at(1);
//
//mVal24 = atan2(Numerator, Denominator);
//
//mVal26 = mVal26Integrate.integrate( pTime, mK2 * mVal24 );
//
//mVal28 = mVal28Integrate.integrate( pTime, mK3 * mVal24 );
//mVal29 = mVal29Integrate.integrate( pTime, mVal28 );
//
//mEstTheta = (mK1 * mVal24) + mVal26 + mVal29;
