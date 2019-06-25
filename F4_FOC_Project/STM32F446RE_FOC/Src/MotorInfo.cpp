/*
 * MotorInfo.cpp
 *
 *  Created on: Jun 18, 2019
 *      Author: watashi
 */

/*
 * せつめい！
 * モータの情報を総合的に管理するClass
 * MathClassは保守性を考慮して別に取り込む形になっているので、
 * 利用する際には、クラスを取り込むこと。
 *
 * 基本的に上から順番に関数を叩いていけばそれらしい回り方する気がする。
 */


#include "MotorInfo.hpp"
#include "Mathlib.hpp"

MotorInfo::MotorInfo() {
	// TODO Auto-generated constructor stub

}

MotorInfo::~MotorInfo() {
	// TODO Auto-generated destructor stub
}

void MotorInfo::setMathLib(MathLib pLib){
	mLib = pLib;
}

MathLib MotorInfo::getMathLib(void){return mLib;}

//void MotorInfo::setVu(float pVu):mVu(pVu){};
//void MotorInfo::setVv(float pVv):mVv(pVv){};
//void MotorInfo::setVw(float pVw):mVw(pVw){};

void MotorInfo::setIu(float pIu){mIu=pIu;};
void MotorInfo::setIv(float pIv){mIv=pIv;};
void MotorInfo::setIw(float pIw){mIw=pIw;};

void MotorInfo::setVu(float pVu){mVu=pVu;};
void MotorInfo::setVv(float pVv){mVv=pVv;};
void MotorInfo::setVw(float pVw){mVw=pVw;};

void MotorInfo::setArg(int parg){
	marg = parg;
}

void MotorInfo::parkTransform(void){
	mIalpha = mIu - (mIv + mIw)/2;
	mIbeta = (mIv - mIw)* 1.7320508f/2;
};

void MotorInfo::clarkTransform(void){
	mId =  mLib.getCosList().at(marg) * mIalpha + mLib.getSinList().at(marg) * mIbeta;
	mIq = -mLib.getSinList().at(marg) * mIalpha + mLib.getCosList().at(marg) * mIbeta;
};

void MotorInfo::PID(void){}

void MotorInfo::setVd(float pVd){mVd = pVd;}
void MotorInfo::setVq(float pVq){mVq = pVq;}

void MotorInfo::invClarkTransform(void){
	mValpha = mLib.getCosList().at(marg) * mVd - mLib.getSinList().at(marg) * mVq;
	mVbeta  = mLib.getSinList().at(marg) * mVd + mLib.getCosList().at(marg) * mVq;
};

void MotorInfo::invParkTransform(void){
	mVu = 0.75f * mValpha;
	mVv = -0.75f * mValpha + mValpha / 3 + mVbeta / 1.7320508f;
	mVw = - mValpha / 3 - mVbeta / 1.7320508f;

//
//	mIalpha = 3/2*(mIu);
//	mIbeta = (mIv - mIw)* 1.7320508f/2;
//
//	mIbeta = (mIv - mIw)* 1.7320508f/2;
//	Iu + Iv + Iw = 0;
//	Iu = -	(Iv + Iw);
//
//	Iu + Iv + Iw = 0;
//	Iu + Iv - Iw = -2*Iw;
//	Ialpha * 2/3 + Ibeta * 2/sqrt(3) = -2 Iw;
//
//
//	Iv = -Iu - Iw;
};

float MotorInfo::getId(void){return mId;};
float MotorInfo::getIq(void){return mIq;};

float MotorInfo::getVd(void){return mVd;};
float MotorInfo::getVq(void){return mVq;};

float MotorInfo::getValpha(void){return mValpha;};
float MotorInfo::getVbeta(void){return mVbeta;};

float MotorInfo::getVu(void){return mVu;};
float MotorInfo::getVv(void){return mVv;};
float MotorInfo::getVw(void){return mVw;};

