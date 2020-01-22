/*
 * LPF.hpp
 *
 *  Created on: 2020/01/05
 *      Author: watashi
 */

#ifndef INC_LPF_HPP_
#define INC_LPF_HPP_

//#include "ZIntegrate.hpp"
#include "UnitDelay.hpp"

class LPF {
private:
	float mGainB0;
	float mGainB1;
	float mGainA1;

	UnitDelay mInputUnitDelay;
	UnitDelay mOutputUnitDelay;
	//Zintegrate1n mInputIntegrate;
	//Zintegrate1n mOutputIntegrate;

	float mBuf1 = 0;
	float mBuf2 = 0;
	float mOutput = 0;


public:
	LPF();
	virtual ~LPF();
	void Init(float pGainB0, float pGainB1, float pGainA1);
	float Output(float pTime, float pInput);

};

#endif /* INC_LPF_HPP_ */
