/*
 * DebugCtrl.cpp
 *
 *  Created on: Aug 8, 2019
 *      Author: watashi
 */

#include "DebugCtrl.hpp"

DebugCtrl::DebugCtrl() {
	// TODO Auto-generated constructor stub
	mDebugStatus = 0;
}

DebugCtrl::~DebugCtrl() {
	// TODO Auto-generated destructor stub
}

int DebugCtrl::GetDbgStatus(void) {
	return mDebugStatus;
}

void DebugCtrl::DbgInfoRegister(float pIu, float pIv, float pIw, float pArg){
	//DEBUG_COUNTを超えるまではDebugInfoに情報を登録し続ける
	//超えた瞬間に、DebugStatusを更新することで次の関数に入るようにする。
	mDebugInfo.SetMotorData(new DebugInfo::SendMotorData(pIu,pIv,pIw,pArg));//デバッグの種類増やしたい時はここで変えてね

	if(mDebugInfo.GetVectSize() == DEBUG_COUNT) {
		mDebugStatus = 1;//情報格納完了
	}
//		//モータ停止の動作
//		MotorCtrl::BtnActOFF();
//		//モータ停止を確認する動作
//
////		if(mMotorInfo.mSensor.getArg() == mMotorInfo.mSensor.getArgOld()){
//			//タイマ停止する動作(何回もこれ呼ばれちゃうから)
//
//			mPWMch1.f2Duty(0);//50%duty
//			mPWMch2.f2Duty(0);
//			mPWMch3.f2Duty(0);
//			mPWMch4.f2Duty(0);
//
//			mPWMch1.Disable();
//			mPWMch2.Disable();
//			mPWMch3.Disable();
//			mPWMch4.Disable();
}

void DebugCtrl::SetDebugStatus(int pStatus) {
	mDebugStatus = pStatus;
}

void DebugCtrl::PrintStatus() {
	//UARTで転送する動作

	std::vector<DebugInfo::SendMotorData> vectorbuf = mDebugInfo.GetVect();
	for(const auto& num : vectorbuf){
		std::string strbuf;
		strbuf.append(std::to_string(num.mIu));
		strbuf.append(",");
		strbuf.append(std::to_string(num.mIv));
		strbuf.append(",");
		strbuf.append(std::to_string(num.mIw));
		strbuf.append(",");
		strbuf.append(std::to_string(num.mEArg));
		strbuf.append(",");
		#ifdef Debug_alpha_beta //ifdefじゃなくてパラメタのヘッダを持たせるべきか。
		strbuf.append(std::to_string(num.mIalpha));
		strbuf.append(",");
		strbuf.append(std::to_string(num.mIbeta));
		strbuf.append(",");
		#endif
		strbuf.append(std::to_string(num.mId));
		strbuf.append(",");
		strbuf.append(std::to_string(num.mIq));

		strbuf.append("\r\n");
		UART::Transmit(strbuf);
	}
}
