/*
 * ZIntegrate.cpp
 *
 *  Created on: Aug 31, 2019
 *      Author: watashi
 */

//お　し　ら　せ　ここだけコーダ規約破ります。
//ｐInputとかmOutputOldとか書いてあってもよめねーから！！！！
//x_n =
//y_n
//のがずっとありがたいだろ？
//そういうことだよ。

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
	mVector = {0};
	mOldVec = {0};
	mK = pK;
}

std::array<float, 2> Zintegrate2n::integrate(float pTime, std::array<float, 2> pVector) {
	mOldVec.at(0) = mVector.at(0);
	mOldVec.at(1) = mVector.at(1);
	mVector.at(0) = mOldVec.at(0) + mK * pTime * pVector.at(0);
	mVector.at(1) = mOldVec.at(1) + mK * pTime * pVector.at(1);
	return mOldVec;
}
