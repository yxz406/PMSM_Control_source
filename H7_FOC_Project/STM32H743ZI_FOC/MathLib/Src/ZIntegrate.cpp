/*
 * ZIntegrate.cpp
 *
 *  Created on: Aug 31, 2019
 *      Author: watashi
 */

#include <ZIntegrate.hpp>

ZIntegrate::ZIntegrate() {
	// TODO Auto-generated constructor stub

}

ZIntegrate::~ZIntegrate() {
	// TODO Auto-generated destructor stub
}



void Zintegrate1n::ZintegrateInit(float pK){
	mValue = 0;
	mOldVal = 0;
	mK = pK;
}

float Zintegrate1n::integrate(float pTime, float pValue) {
	mOldVal = mValue;
	mValue = mOldVal + mK * pTime * pValue;
	return mOldVal;
}


void Zintegrate2n::ZintegrateInit(float pK){
	mVector = {0};
	mOldVec = {0};
	mK = pK;
}

std::array<float, 2> Zintegrate2n::integrate(float pTime, std::array<float, 2> pVector) {
	mOldVec.at(0) = mVector.at(0);
	mOldVec.at(1) = mVector.at(1);
	mVector.at(0) = mOldVec.at(0) + mK * pTime * pVector.at(0);
	mVector.at(1) = mOldVec.at(1) + mK * pTime * pVector.at(1);
	return mOldVec;
}
