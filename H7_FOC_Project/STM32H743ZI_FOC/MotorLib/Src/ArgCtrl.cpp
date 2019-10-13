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

	//強制転流Init
	mOpenLoopInfo.mtargetRPS = OPENLOOP_TARGET_RPS;
	mOpenLoopInfo.mtargetAcc = OPENLOOP_TARGET_ACCEL;
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

fp_rad ArgCtrl::getArgOmega(void) {
	return (mArg - mArgOld) * CONTROL_FREQ_HZ;
}

OpenLoop_Status ArgCtrl::accelerationForOpenLoop(void) {
	//基本設計がおかしい。作り直してる。
	float TargetSPD = (mOpenLoopInfo.mtargetRPS/(float)CONTROL_FREQ_HZ * 2.0f * M_PI);
	if( mOpenLoopInfo.mAccelSPD < TargetSPD ) { // [rpm]/20000 * 2*M_PI = [arg]
		mOpenLoopInfo.mAccelSPD += mOpenLoopInfo.mtargetAcc;//進む差分角
		increment(mOpenLoopInfo.mAccelSPD);
		return 0;
	} else {
		increment(mOpenLoopInfo.mAccelSPD);
		return 1;
	}
}

OpenLoop_Status ArgCtrl::decelerationForOpenLoop(void) {
	if(mOpenLoopInfo.mAccelSPD > 0){
		mOpenLoopInfo.mAccelSPD -= mOpenLoopInfo.mtargetAcc;
		increment(mOpenLoopInfo.mAccelSPD);
		return 0;
	} else {
		increment(0);
		return 1;
	}
}
