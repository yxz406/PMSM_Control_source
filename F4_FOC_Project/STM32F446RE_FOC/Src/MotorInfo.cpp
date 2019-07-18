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

void MotorInfo::setArg(int parg){
	marg = parg;
}

void MotorInfo::setArgDelta(int parg){
	marg_delta = parg;
}

void MotorInfo::parkTransform(void){
	mIalpha = mIu - (mIv + mIw)/2;
	mIbeta = (mIv - mIw)* 1.7320508f/2;
};

void MotorInfo::clarkTransform(void){//反時計回り回転
	mId =  mLib.getCosList().at(marg) * mIalpha + mLib.getSinList().at(marg) * mIbeta;
	mIq = -mLib.getSinList().at(marg) * mIalpha + mLib.getCosList().at(marg) * mIbeta;
};

void MotorInfo::clarkGanmaDelta(void){//時計回り回転
	mIganma = mLib.getCosList().at(marg) * mId - mLib.getSinList().at(marg) * mIq;
	mIdelta = mLib.getSinList().at(marg) * mId + mLib.getCosList().at(marg) * mIq;
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

void MotorInfo::invClarkGanmaDelta(void){
	mIganma =  mLib.getCosList().at(marg) * mId + mLib.getSinList().at(marg) * mIq;
	mIdelta = -mLib.getSinList().at(marg) * mId + mLib.getCosList().at(marg) * mIq;
}

void MotorInfo::invClarkTransform(void){
	mValpha = mLib.getCosList().at(marg_delta) * mVd - mLib.getSinList().at(marg_delta) * mVq;
	mVbeta  = mLib.getSinList().at(marg_delta) * mVd + mLib.getCosList().at(marg_delta) * mVq;
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

