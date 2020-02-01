/*
 * Observer.cpp
 *
 *  Created on: Aug 20, 2019
 *      Author: watashi
 */

#include "Observer.hpp"

Observer::Observer() {
	// TODO Auto-generated constructor stub
}

Observer::~Observer() {
	// TODO Auto-generated destructor stub
}

//Initializer
void Observer::InitEMFObs(float pCycleTime, float pR, float pLd, float pLq, float pGainAlpha) {
	mEMFObserver.InitCycleTime(pCycleTime);
	mEMFObserver.InitMotorParam(pR, pLd, pLq);
	mEMFObserver.InitObsGain(pGainAlpha);
}

void Observer::InitPII2(float pCycleTime, float pK1, float pK2, float pK3) {
	mEstThetaPII2.InitCycleTime(pCycleTime);
	mEstThetaPII2.InitGainK1(pK1);
	mEstThetaPII2.InitGainK2(pK2);
	mEstThetaPII2.InitGainK3(pK3);
}

//Setter
void Observer::SetIGanmaDelta(const std::array<float, 2> &pIGanmaDelta) {
	mIGanmaDelta = pIGanmaDelta;
}
void Observer::SetVGanmaDelta(const std::array<float, 2> &pVGanmaDelta) {
	mVGanmaDelta = pVGanmaDelta;
}

//Calculator
void Observer::Calculate() {
	mEMFObserver.SetIgd(mIGanmaDelta);
	mEMFObserver.SetVgd(mVGanmaDelta);
	mEMFObserver.EMFObserver();

	mEstEMFgd = mEMFObserver.GetEstEMFgd();
	mEstAxiErr = EstimatedAxisError::GetError(mEstEMFgd);
	mEstThetaPII2.SetValue(mEstAxiErr);
	mEstThetaPII2.Calculate();
	mEstOmegaE = mEstThetaPII2.GetOmega();//計算した角速度の出力
	mEMFObserver.SetEstOmegaE(mEstOmegaE);
	mEstTheta = fmod( ( mEstThetaPII2.GetTheta() + 2 * M_PI ) , ( 2 * M_PI ) ); //theta % 2pi
}

void Observer::CalculateOpenLoop(const float &pOmegaE, const float &pThetaE) {
	//FOCモードとの違い
	//FOCとは違って、電気角速度ωは強制転流コントローラが勝手に決める。
	//そのため、PII2で推定しないで外から強制転流コントローラのωを代入する。
	mEMFObserver.SetIgd(mIGanmaDelta);
	mEMFObserver.SetVgd(mVGanmaDelta);
	mEMFObserver.EMFObserver();

	mEstEMFgd = mEMFObserver.GetEstEMFgd();
	mEstAxiErr = EstimatedAxisError::GetError(mEstEMFgd);

	//強制転流時には毎回角度のリセットをする
	//ganma axis でなく est d axis を入れる
	mEstThetaPII2.ThetaResetForOpenLoop(pThetaE + mEstAxiErr);

	//本当はここ以降動かしてなかった
	mEstThetaPII2.SetValue(mEstAxiErr);
	mEstThetaPII2.Calculate();
	//ここまで

	mEstOmegaE = mEstThetaPII2.GetOmega();//計算した角速度の出力
	mEstTheta = fmod( ( mEstThetaPII2.GetTheta() + 2 * M_PI ) , ( 2 * M_PI ) );//計算した角度の出力

	//PII2から取得せずに入力したOMEGAを見る。 comment out
	//mEstOmegaE = mEMFObserver.GetInputEstOmegaE();

	mEMFObserver.SetEstOmegaE( pOmegaE );//強制転流コントローラからのωを入力している

	//デバッグはEstAxiErrを見れば良い。

}


//Getter
float Observer::GetEstAxiErr(void) {
	return mEstAxiErr;
}

float Observer::GetEstTheta(void) {
	return mEstTheta;
}

float Observer::GetEstOmegaE(void) {
	return mEstOmegaE;
}

//debug Getter
std::array<float, 2> Observer::GetIgd(void) {
	return mIGanmaDelta;
}

std::array<float, 2> Observer::GetVgd(void) {
	return mVGanmaDelta;
}


std::array<float, 2> Observer::GetEstEMFgd(void) {
	return mEstEMFgd;
}
