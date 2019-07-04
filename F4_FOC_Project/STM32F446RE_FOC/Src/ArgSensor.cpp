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
	mArg = 0;
}

void ArgSensor::increment(float pArg){
	mArg = mArg + pArg + (2*M_PI);
	mArg = fmodl(mArg, (2*M_PI));
}

void ArgSensor::decrement(float pArg){
	mArg = mArg - pArg + (2*M_PI);
	mArg = fmodl(mArg, (2*M_PI));
}

float ArgSensor::getArg(void){
	return mArg;
}

void ArgSensor::Start_Stop(bool pIsONState){
		mIsStart = pIsONState;
}

void ArgSensor::ImArg(void){
	if(mIsStart){
		if(mImArgcount < 25000){
			mImArgcount++;
			//mImArgcount = 25;
		}
		mCalcArg = mImArgcount*0.0000125f*M_PI;//進む差分角
		mArg = mArg + mCalcArg + (2*M_PI);
		mArg = fmodl(mArg, (2*M_PI));

	} else {
		if(mImArgcount > 0){
			mImArgcount--;
		}
		mCalcArg = mImArgcount*0.0000125f*M_PI;
		mArg = mArg + mCalcArg + (2*M_PI);
		mArg = fmodl(mArg, (2*M_PI));
	}
}
