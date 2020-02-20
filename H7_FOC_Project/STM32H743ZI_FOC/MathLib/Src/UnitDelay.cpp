/*
 * UnitDelay.cpp
 *
 *  Created on: 2020/01/12
 *      Author: watashi
 */

#include "UnitDelay.hpp"

UnitDelay::UnitDelay() {
	// TODO Auto-generated constructor stub

}

UnitDelay::~UnitDelay() {
	// TODO Auto-generated destructor stub
}

float UnitDelay::PushAndGetVal(float pNewVal) {
	mOldVal = mNewVal; //oldval update
	mNewVal = pNewVal; //newval update

	return mOldVal;
}


void UnitDelay::SetVal(float pNewVal) {
	mOldVal = pNewVal;
}

float UnitDelay::GetOldVal(void) {
	return mOldVal;
}
