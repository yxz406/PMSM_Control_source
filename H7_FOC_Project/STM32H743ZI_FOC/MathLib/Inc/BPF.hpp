/*
 * BPF.hpp
 *
 *  Created on: 2020/01/05
 *      Author: watashi
 */

#ifndef INC_BPF_HPP_
#define INC_BPF_HPP_

#include "ZIntegrate.hpp"

class BPF {

private:
	float mGainB0;
	float mGainB2;
	float mGainA1;
	float mGainA2;

	Zintegrate1n mInputIntegrate1;
	Zintegrate1n mInputIntegrate2;
	Zintegrate1n mMidIntegrate;
	Zintegrate1n mOutIntegrate;

	float mBuf1 = 0;
	float mBuf2 = 0;
	float mBuf3 = 0;
	float mOutput = 0;

public:
	BPF();
	virtual ~BPF();

	void Init(float pGainB0, float pGainB2, float pGainA1, float pGainA2);
	float Output(float pTime, float pInput);


};

#endif /* INC_BPF_HPP_ */
