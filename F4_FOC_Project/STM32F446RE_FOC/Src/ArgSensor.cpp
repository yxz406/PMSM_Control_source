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
	mArg_delta = 0;
	mFCisON = 0;
}

ArgSensor::~ArgSensor() {
	// TODO Auto-generated destructor stub
}

void ArgSensor::Init(void) {
	mArgOld = 0;
	mArg = 0;
	mArg_delta = 0;
	mFCisON = 0;
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

float ArgSensor::getArg_delta(void){
	return mArg_delta;
}

void ArgSensor::FC_Start_Stop(bool pIsON){
		mFCisON = pIsON;
}

bool ArgSensor::GetIsAccelerating(void){
	return mIsAccelerating;
}

void ArgSensor::ForceComArg(void){
	if(mFCisON){
		if(mImArgcount < 25000){
			mImArgcount = mImArgcount + 4;
			mIsAccelerating = true;
		} else {
			mIsAccelerating = false;
		}
		float arg_add;
		arg_add = mImArgcount*0.0000125f*M_PI;//進む差分角
		mArgOld = mArg;
		mArg = mArg + arg_add + (2*M_PI);
		mArg = fmodl(mArg, (2*M_PI));

	} else {
		if(mImArgcount > 0){
			mImArgcount = mImArgcount - 4;
			mIsAccelerating = true;
		} else {
			mIsAccelerating = false;
		}
		float arg_add;
		arg_add = mImArgcount*0.0000125f*M_PI;
		mArgOld = mArg;
		mArg = mArg + arg_add + (2*M_PI);
		mArg = fmodl(mArg, (2*M_PI));
	}
}

void ArgSensor::Observer(void){

}
