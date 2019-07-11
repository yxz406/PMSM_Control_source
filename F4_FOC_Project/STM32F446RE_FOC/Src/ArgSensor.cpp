/*
 * ArgSensor.cpp
 *
 *  Created on: Jun 25, 2019
 *      Author: watashi
 */

/*
 * せつめい！
 * センサ周りを処理するclass
 * 現状強制転流用の仮想エンコーダのみ実装。
 * ABZエンコーダ等の物理エンコーダもここに実装する。
 */

#include "ArgSensor.hpp"
#include "math.h"

ArgSensor::ArgSensor() {
	// TODO Auto-generated constructor stub
	mArg = 0;
	mImArgcount = 0;
}

ArgSensor::~ArgSensor() {
	// TODO Auto-generated destructor stub
}

void ArgSensor::Init(void) {
	mArgOld = 0;
	mArg = 0;
}

void ArgSensor::increment(float pArg){
	mArgOld = mArg;
	mArg = mArg + pArg + (2*M_PI);
	mArg = fmodl(mArg, (2*M_PI));
}

void ArgSensor::decrement(float pArg){
	mArgOld = mArg;
	mArg = mArg - pArg + (2*M_PI);
	mArg = fmodl(mArg, (2*M_PI));
}

float ArgSensor::getArg(void){
	return mArg;
}

float ArgSensor::getArgOld(void){
	return mArgOld;
}

void ArgSensor::Start_Stop(bool pIsONState){
		mIsStart = pIsONState;
}

bool ArgSensor::GetIsAccelerating(void){
	return mIsAccelerating;
}

void ArgSensor::ImArg(void){
	if(mIsStart){
		if(mImArgcount < 25000){
			mImArgcount++;
			//mImArgcount = 25;
			mIsAccelerating = true;
		} else {
			mIsAccelerating = false;
		}
		mCalcArg = mImArgcount*0.0000125f*M_PI;//進む差分角
		mArgOld = mArg;
		mArg = mArg + mCalcArg + (2*M_PI);
		mArg = fmodl(mArg, (2*M_PI));

	} else {
		if(mImArgcount > 0){
			mImArgcount--;
			mIsAccelerating = true;
		} else {
			mIsAccelerating = false;
		}
		mCalcArg = mImArgcount*0.0000125f*M_PI;
		mArgOld = mArg;
		mArg = mArg + mCalcArg + (2*M_PI);
		mArg = fmodl(mArg, (2*M_PI));
	}
}
