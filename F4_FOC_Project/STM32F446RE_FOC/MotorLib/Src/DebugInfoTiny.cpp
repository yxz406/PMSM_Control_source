/*
 * DebugInfoTiny.cpp
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
#include "DebugInfoTiny.hpp"

DebugInfoTiny::DebugInfoTiny() {
	// TODO Auto-generated constructor stub
	mCNT = 0;
}

DebugInfoTiny::~DebugInfoTiny() {
	// TODO Auto-generated destructor stub
}

//Setter
void DebugInfoTiny::SetMotorData(float pIu, float pIv, float pIw,
		float pIalpha, float pIbeta,
		float pVd, float pVq,
		float pEArg) {
	mIu[mCNT] = pIu;
	mIv[mCNT] = pIv;
	mIw[mCNT] = pIw;
	mIalpha[mCNT] = pIalpha;
	mIbeta[mCNT] = pIbeta;
	mVd[mCNT] = pVd;
	mVq[mCNT] = pVq;
	mEArg[mCNT] = pEArg;
	mCNT++;
}

//Getter
int DebugInfoTiny::GetCNT(void){
	return mCNT;
}
