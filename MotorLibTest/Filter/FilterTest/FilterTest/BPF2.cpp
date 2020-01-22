#include "stdafx.h"
#include "BPF2.hpp"


BPF2::BPF2()
{
}


BPF2::~BPF2()
{
}

float BPF2::Output(float pInput) {
	
	//Delay‘ã“ü•”ŒvŽZ
	mBuf1 = pInput * mS1
		- mBufDelay1 * mA2
	 	- mBufDelay2 * mA3;


	mOutput = mBuf1
		+ mBufDelay1 * mB2
		+ mBufDelay2;

	//Next DelayŒvŽZ
	mBufDelay2 = mBufDelay1;
	mBufDelay1 = pInput;


	return mOutput;
}