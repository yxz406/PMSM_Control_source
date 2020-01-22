#pragma once
class BPF2
{
private:
	float mS1 = 0;
	float mA2 = 0;
	float mA3 = 0;
	float mB2 = 0;


	float mBuf1 = 0;
	float mOutput = 0;
	float mBufDelay1 = 0;
	float mBufDelay2 = 0;

public:
	BPF2();
	~BPF2();
	float Output(float pInput);
};

