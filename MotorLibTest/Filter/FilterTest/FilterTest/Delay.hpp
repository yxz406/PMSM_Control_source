#pragma once
#include <deque>

class Delay
{
private:
	unsigned int mMaxDelaySize = 0;
	std::deque<float> mDelaydeque;
public:
	Delay();
	~Delay();
	void SetMaxDelaySize(int pMaxSize);
	void SetNewVal(float pValue);
	float GetOldValue(int pDelay);
};

