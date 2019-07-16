/*
 * PID.cpp
 *
 *  Created on: Jul 12, 2019
 *      Author: watashi
 */

/*
 * せつめい！
 * 速度型PID制御をするためのClass
 *
 * コンストラクタでパラメータをセットして、
 * あとはErrorAndTimeUpdateを叩いた後に、
 * OutPut()でFloatを取り出せば速度型のPID制御が簡単にできるはず。
 */

#include "PID.hpp"

PID::PID(){

}

PID::PID(float pGain_p, float pGain_i, float pGain_d)
:mGain_p(pGain_p), mGain_i(pGain_i), mGain_d(pGain_d)
{
	// TODO Auto-generated constructor stub

	mError.fill(0);
}

PID::~PID() {
	// TODO Auto-generated destructor stub
}

void PID::SetParam(float pGain_p, float pGain_i, float pGain_d){
	mGain_p = pGain_p;
	mGain_i = pGain_i;
	mGain_d = pGain_d;
}

void PID::ErrorUpdate(float pError){
	mError[1] = pError;
	mError[2] = mError[1];
	mError[3] = mError[2];
}

void PID::ErrorAndTimeUpdate(float pError, float pSampleTime){
//	mError[1] = pError;
//	mError[2] = mError[1];
//	mError[3] = mError[2];//下のがはやそうだから。
	mError = {pError,mError[1],mError[2]};
	mSampleTime = pSampleTime;
}

void PID::SetSampleTime(float pSampleTime){
	mSampleTime = pSampleTime;
}

float PID::OutPut(void){
	mDiff = mGain_p*(mError[1]-mError[2]+(mGain_i/mSampleTime)*mError[1]+(mGain_d/mSampleTime)*(mError[1]-2*mError[2]+mError[3]));
	return mOutValOfLast + mDiff;
}
