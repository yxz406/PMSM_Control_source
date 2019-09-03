/*
 * ArgCtrl.cpp
 *
 *  Created on: Sep 3, 2019
 *      Author: watashi
 */

#include "ArgCtrl.hpp"

ArgCtrl::ArgCtrl() {
	// TODO Auto-generated constructor stub
	mArg = 0;
	mArgOld = 0;
	mOmega = 0;
	mArgErr = 0;
}

ArgCtrl::~ArgCtrl() {
	// TODO Auto-generated destructor stub
	mArg = 0;
	mArgOld = 0;
	mOmega = 0;
	mArgErr = 0;
}

void ArgCtrl::Init(void) {
	mArg = 0;
	mArgOld = 0;
	mOmega = 0;
	mArgErr = 0;
}

void ArgCtrl::increment(fp_rad pArg) {
	mArgOld = mArg;
	mArg = mArg + pArg + (2*M_PI);
	mArg = fmodl(mArg, (2*M_PI));
}

void ArgCtrl::decrement(fp_rad pArg) {
	mArgOld = mArg;
	mArg = mArg - pArg + (2*M_PI);
	mArg = fmodl(mArg, (2*M_PI));
}

fp_rad ArgCtrl::getArg(void) {
	return mArg;
}

fp_rad ArgCtrl::getArgErr(void) {
	return mArgErr;
}

fp_rad ArgCtrl::getArgOld(void) {
	return mArgOld;
}

void ArgCtrl::FCInit(fp_rad pFCtargetSPD){
	ForceCom.mFCtargetSPD = pFCtargetSPD;
}

ForceCom_Status ArgCtrl::FCacceleration(void) {
	if(ArgCtrl::mOmega < ForceCom.mFCtargetSPD){
		ForceCom.mAccelSPD = ForceCom.mAccelSPD + 4;//ここ加速度を制御してる
		fp_rad arg_add;
		arg_add = ForceCom.mAccelSPD*0.00000125f*M_PI;//進む差分角
		increment(arg_add);
		return 0;
	} else {
		fp_rad arg_add;
		arg_add = ForceCom.mAccelSPD*0.00000125f*M_PI;//進む差分角
		increment(arg_add);
		return 1;
	}
}

ForceCom_Status ArgCtrl::FCdeceleration(void) {
	if(ArgCtrl::mOmega >= 0){
		ForceCom.mAccelSPD = ForceCom.mAccelSPD + 4;//ここ加速度を制御してる
		float arg_add;
		arg_add = ForceCom.mAccelSPD*0.00000125f*M_PI;//進む差分角
		increment(arg_add);
		return 0;
	} else {
		ForceCom.mAccelSPD = 0;
		float arg_add;
		arg_add = ForceCom.mAccelSPD*0.00000125f*M_PI;//進む差分角
		increment(arg_add);
		return 1;
	}
}
