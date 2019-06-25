/*
 * MathLib.cpp
 *
 *  Created on: Jun 20, 2019
 *      Author: watashi
 */

/* せつめい！
 * メモリの上に予め計算しておいた浮動小数点数を置いておくclass
 * プログラマ「パワーこそ力」「数の暴力」「32Bitの力を見せてみろ」
 * マイコン「ひええ…」
 *
 *  使い方
 * 	MathLib mathlibrary;//ライブラリ オブジェクトを生成
 *	mathlibrary.fInit(256);//オブジェクトに広げる数量を定義
 *	float val = mathlibrary.getSinList().at(0);//0番目のsinの値を取得
 *	256個の値を生成したならば、0~255の番地となることに注意すること。
 */

#include "MathLib.hpp"
#include <vector>
#include "math.h"

MathLib::MathLib() {
	mSize = 0;
}

MathLib::~MathLib() {
	mSize = 0;
	mSinList.clear();
	mCosList.clear();
}

void MathLib::setLibSize(int pSize){
	mSize = pSize;
}

void MathLib::fInit(int pSize){
	setLibSize(pSize);
	if(mSize == 0){
		while(1){}//error check
	}
	mRadvsSize = mSize / 2*M_PI;//サイズと1radianの比

	fSinVectorInit(&mSinList);
	fCosVectorInit(&mCosList);
}

int MathLib::getLibSize(void){return mSize;}

void MathLib::fSinVectorInit(std::vector<float> *pVector){
	for(int i=0;i<mSize;i++){
		float fsinval = sin(i*2*M_PI/(float)mSize);
		pVector->push_back(fsinval);
	}
}

void MathLib::fCosVectorInit(std::vector<float> *pVector){
	for(int i=0;i<mSize;i++){
		float fcosval = cos(i*2*M_PI/(float)mSize);
		pVector->push_back(fcosval);
	}
}

std::vector<float> MathLib::getSinList(void){
	return mSinList;
}

std::vector<float> MathLib::getCosList(void){
	return mCosList;
}

int MathLib::radToSizeCount(float pradian){
	return pradian * mRadvsSize;
}

