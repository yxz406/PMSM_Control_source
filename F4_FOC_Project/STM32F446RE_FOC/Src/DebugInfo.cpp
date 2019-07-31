/*
 * DebugInfo.cpp
 *
 *  Created on: Jul 1, 2019
 *      Author: watashi
 */

/*
 * せつめい！
 * 各サイクルのモータの電圧・電流・角度等のデバッグ情報を貯めておくクラス
 * それ以上でもそれ以下でもない。
 *
 * 叩き方の例
 * データの格納
 * Debug.SetData((float)adc_data1, (float)adc_data2, (float)adc_data3, (float)sensor.getArg());
 * データの読み出し
 * std::vector<SendMotorData> DataVect = GetVect();
 *
 * 読み出しがVector型であるのは(float型でないのは)データの個数の変化に対応するため。
 *(配列のfor使って調理してください(にっこり))
 */
#include "DebugInfo.hpp"

DebugInfo::SendMotorData::SendMotorData(float pIu, float pIv, float pIw,
							float pIalpha, float pIbeta,
							float pId, float pIq,
							float pVu, float pVv, float pVw,
							float pValpha, float pVbeta,
							float pVd, float pVq,
							float pEArg)
:mIu(pIu), mIv(pIv), mIw(pIw),
 mIalpha(pIalpha), mIbeta(pIbeta),
 mId(pId), mIq(pIq),
 mVu(pVu), mVv(pVv), mVw(pVw),
 mValpha(pValpha), mVbeta(pVbeta),
 mVd(pVd), mVq(pVq), mEArg(pEArg)
{
	//constructor
}

DebugInfo::SendMotorData::SendMotorData(float pIu, float pIv, float pIw, float pEArg)
:mIu(pIu), mIv(pIv), mIw(pIw), mEArg(pEArg)
{
	//constructor
}

DebugInfo::SendMotorData::~SendMotorData(){
	//destructor
}

DebugInfo::DebugInfo() {
	// TODO Auto-generated constructor stub
}

DebugInfo::~DebugInfo() {
	// TODO Auto-generated destructor stub
}

void DebugInfo::SetMotorData(DebugInfo::SendMotorData* pMotorData){
	mSendDataVect.push_back(*pMotorData);
}

//getter
std::vector<DebugInfo::SendMotorData> DebugInfo::GetVect(void){
	return mSendDataVect;
}

int DebugInfo::GetVectSize(void){
	return mSendDataVect.size();
}
