#include "stdafx.h"
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

double UnitDelay::PushAndGetVal(double pNewVal) {
	mOldVal = mNewVal; //oldval update
	mNewVal = pNewVal; //newval update
	//mOldVal = pNewVal;

	return mOldVal;
}
