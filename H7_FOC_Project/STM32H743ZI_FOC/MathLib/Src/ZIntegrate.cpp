/*
 * ZIntegrate.cpp
 *
 *  Created on: Aug 31, 2019
 *      Author: watashi
 */

#include <ZIntegrate.hpp>

//1n

Zintegrate1n::Zintegrate1n(float pK)
:mK(pK), mInput(0), mInputOld(0), mOutput(0), mOutputOld(0)
{
	//constructor
}

Zintegrate1n::~Zintegrate1n() {
	//destructor
}

void Zintegrate1n::SetDefault(float pInputOld, float pOutputOld) {
	//初期値のSetter
	mInputOld = pInputOld;
	mOutputOld = pOutputOld;
}

float Zintegrate1n::integrate(const float &pTime, const float &pInput) {

	//現在の状態を更新
	mInput = pInput;
	mOutput = mOutputOld + ( 0.5f * mK * pTime ) * (mInput + mInputOld);

	//次のステップに向けて、過去の状態を更新
	mInputOld = pInput;
	mOutputOld = mOutput;

	return mOutput;
}

//1nMOD

Zintegrate1nMod::Zintegrate1nMod(float pK)
	:mK(pK), mInput(0), mInputOld(0), mOutput(0), mOutputOld(0)
{
	//constructor
}

Zintegrate1nMod::~Zintegrate1nMod() {
	//destructor
}

void Zintegrate1nMod::SetDefault(float pInputOld, float pOutputOld) {
	//初期値のSetter
	mInputOld = pInputOld;
	mOutputOld = pOutputOld;
}

float Zintegrate1nMod::integrate(const float &pTime, const float &pInput) {

	//現在の状態を更新
	mInput = pInput;
	mOutput = mOutputOld + ( 0.5f * mK * pTime ) * (mInput + mInputOld);

	mOutput = fmod(mOutput, 2.0f * M_PI);//Modする

	//次のステップに向けて、過去の状態を更新
	mInputOld = pInput;
	mOutputOld = mOutput;

	return mOutput;
}

//2n

Zintegrate2n::Zintegrate2n(float pK)
:mIntegrate1(pK), mIntegrate2(pK)
{
	//constructor
}

Zintegrate2n::~Zintegrate2n() {
	//destructor
}

//std::array<float, 2> Zintegrate2n::integrate(const float &pTime, const std::array<float, 2> &pInput) {
//	return {mIntegrate1.integrate(pTime, pInput.at(0)), mIntegrate2.integrate(pTime, pInput.at(1))};
//}
