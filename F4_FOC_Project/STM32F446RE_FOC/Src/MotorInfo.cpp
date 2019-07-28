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


/*
 * 角度の向きについて
 *

β         d
*        *
*       *
*      *
*     *                     γ
*    *                     *
*   * Δθ →           *
*  *           *
* * 　←↑  *      ↑
***  θ(dq)　　　　θ(γδ)
* * * * * * * * * * * * * α

* Define
* αβ軸とdq軸のなす角を、反時計回りを正として、θ(dq)とする。
* dq軸に対するγδ軸の遅れを、時計回りを正として、Δθとする。
* αβ軸とγδ軸のなす角を、反時計回りを正として、θ(γδ)とする。
*
* Theorem
* これより、θ(γδ) = θ(dq) + Δθ
* を得る.
*
* */


#include "MotorInfo.hpp"
#include "Mathlib.hpp"

//Init

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

void MotorInfo::setArgSensor(ArgSensor pSensor){
	mSensor = pSensor;
}

void MotorInfo::setIdqPIDLib(PID pdPID, PID pqPID){
	mIdPID = pdPID;
	mIqPID = pqPID;
}

void MotorInfo::setIganmadeltaPIDLib(PID pganmaPID, PID pdeltaPID){
	mIganmaPID = pganmaPID;
	mIdeltaPID = pdeltaPID;
}

//void MotorInfo::setVu(float pVu):mVu(pVu){};
//void MotorInfo::setVv(float pVv):mVv(pVv){};
//void MotorInfo::setVw(float pVw):mVw(pVw){};

//Start,Stop
void MotorInfo::startForceCommutation(void){
	mSensor.FC_Start_Stop(true);
}

void MotorInfo::stopForceCommutation(void){
	mSensor.FC_Start_Stop(false);
}

//Update

void MotorInfo::setIu(float pIu){mIu=pIu;};
void MotorInfo::setIv(float pIv){mIv=pIv;};
void MotorInfo::setIw(float pIw){mIw=pIw;};
void MotorInfo::setIuvw(float pIu, float pIv, float pIw){
	mIu = pIu;
	mIv = pIv;
	mIw = pIw;
}

void MotorInfo::setVu(float pVu){mVu=pVu;};
void MotorInfo::setVv(float pVv){mVv=pVv;};
void MotorInfo::setVw(float pVw){mVw=pVw;};

void MotorInfo::setArg(int pArg){
	mArg = pArg;
}

void MotorInfo::setArgDelta(int pArg){
	mArg_delta = pArg;
}

float MotorInfo::getArgRad(void){
	return mLib.sizeCountToRad(mArg);
}

float MotorInfo::getArgDeltaRad(void){
	return mLib.sizeCountToRad(mArg_delta);
}


void MotorInfo::culcArg(void){
}

void MotorInfo::ForceCommutation(void){
	mSensor.ForceComArg();
	float ArgOld = mSensor.getArgOld();
	float ArgDlt = mSensor.getArg_delta();
	int arg_count = mLib.radToSizeCount(ArgOld);
	int argdelta_count = mLib.radToSizeCount(-1 * ArgDlt);
	mArg = arg_count;
	mArg_delta = argdelta_count; //回転方向より符号は反転する
	setRPM();
}

void MotorInfo::setRPM(void){
	mRPM = (float)(mSensor.getArg() - mSensor.getArgOld()) / (2*3.14f) * 20 * 1000;//適当なパラメータを入れている
}

void MotorInfo::parkTransform(void){
	mIalpha = mIu - (mIv + mIw)/2;
	mIbeta = (mIv - mIw)* 1.7320508f/2;
};

void MotorInfo::clarkTransform(void){//反時計回り回転
	mId =  mLib.getCosList().at(mArg) * mIalpha + mLib.getSinList().at(mArg) * mIbeta;
	mIq = -mLib.getSinList().at(mArg) * mIalpha + mLib.getCosList().at(mArg) * mIbeta;
};

void MotorInfo::clarkGanmaDelta(void){//時計回り回転
	mIganma = mLib.getCosList().at(mArg_delta) * mId - mLib.getSinList().at(mArg_delta) * mIq;
	mIdelta = mLib.getSinList().at(mArg_delta) * mId + mLib.getCosList().at(mArg_delta) * mIq;
}

void MotorInfo::PIDdq_control(float pdVal, float pqVal, float pTime){
	mIdPID.ErrorAndTimeUpdate(pdVal, pTime);
	mIqPID.ErrorAndTimeUpdate(pqVal, pTime);
	mVd = mVd + mIdPID.OutPut();
	mVq = mVq + mIqPID.OutPut();
}
void MotorInfo::PIDganmadelta_control(float pganmaVal, float pdeltaVal, float pTime){
	mIganmaPID.ErrorAndTimeUpdate(pganmaVal, pTime);
	mIdeltaPID.ErrorAndTimeUpdate(pdeltaVal, pTime);
	mVganma = mVganma + mIganmaPID.OutPut();
	mVdelta = mVdelta + mIdeltaPID.OutPut();
}

void MotorInfo::setVd(float pVd){mVd = pVd;}
void MotorInfo::setVq(float pVq){mVq = pVq;}
void MotorInfo::setVganma(float pVganma){mVganma = pVganma;}
void MotorInfo::setVdelta(float pVdelta){mVdelta = pVdelta;}

void MotorInfo::invClarkGanmaDelta(void){
	mVd =  mLib.getCosList().at(mArg) * mVganma + mLib.getSinList().at(mArg) * mVdelta;
	mVq = -mLib.getSinList().at(mArg) * mVganma + mLib.getCosList().at(mArg) * mVdelta;
}

void MotorInfo::invClarkTransform(void){
	mValpha = mLib.getCosList().at(mArg_delta) * mVd - mLib.getSinList().at(mArg_delta) * mVq;
	mVbeta  = mLib.getSinList().at(mArg_delta) * mVd + mLib.getCosList().at(mArg_delta) * mVq;
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

float MotorInfo::getIganma(void){return mIganma;};
float MotorInfo::getIdelta(void){return mIdelta;};

float MotorInfo::getId(void){return mId;};
float MotorInfo::getIq(void){return mIq;};

float MotorInfo::getVd(void){return mVd;};
float MotorInfo::getVq(void){return mVq;};

float MotorInfo::getValpha(void){return mValpha;};
float MotorInfo::getVbeta(void){return mVbeta;};

float MotorInfo::getVu(void){return mVu;};
float MotorInfo::getVv(void){return mVv;};
float MotorInfo::getVw(void){return mVw;};

