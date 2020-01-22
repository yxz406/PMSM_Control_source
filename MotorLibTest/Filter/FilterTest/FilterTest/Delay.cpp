#include "stdafx.h"
#include "Delay.hpp"


Delay::Delay()
{
}


Delay::~Delay()
{
}

void Delay::SetMaxDelaySize(int pMaxSize) {
	mMaxDelaySize = (unsigned int)pMaxSize;
	mDelaydeque.clear();//èâä˙âª
	for (int i = 0; i < pMaxSize; i++) {
		mDelaydeque.push_front(0);
	}
}

void Delay::SetNewVal(float pValue) {
	mDelaydeque.push_front(pValue);
	if (mMaxDelaySize < mDelaydeque.size()) {
		mDelaydeque.pop_back();
	}
}

float Delay::GetOldValue(int pDelay) {

	if (mMaxDelaySize < pDelay) {
		return -1;//null check
	}

	return mDelaydeque.at(pDelay-1);
}