/*
 * ZIntegrate.cpp
 *
 *  Created on: Aug 31, 2019
 *      Author: watashi
 */

#include <ZIntegrate.hpp>

ZIntegrate::ZIntegrate() {
	// TODO Auto-generated constructor stub

}

ZIntegrate::~ZIntegrate() {
	// TODO Auto-generated destructor stub
}



void Zintegrate1n::ZintegrateInit(float pK){
	mInput = 0;
	mInputOld = 0;

	mOutput = 0;
	mOutputOld = 0;
	mK = pK;
}

float Zintegrate1n::integrate(float pTime, float pInput) {

	//現在の状態を更新
	mInput = pInput;
	mOutput = mOutputOld + ( 0.5f * mK * pTime ) * (mInput + mInputOld);

	//次のステップに向けて、過去の状態を更新
	mInputOld = pInput;
	mOutputOld = mOutput;

	return mOutput;
}


void Zintegrate2n::ZintegrateInit(float pK){
	mIntegrate1.ZintegrateInit(pK);
	mIntegrate2.ZintegrateInit(pK);
}

std::array<float, 2> Zintegrate2n::integrate(float pTime, std::array<float, 2> pInput) {
	std::array<float, 2> Output;
	Output.at(0) = mIntegrate1.integrate(pTime, pInput.at(0));
	Output.at(1) = mIntegrate2.integrate(pTime, pInput.at(1));
	return Output;
}
