/*
* BPF.hpp
*
*  Created on: 2020/01/05
*      Author: watashi
*/

#ifndef INC_BPF_HPP_
#define INC_BPF_HPP_

//#include "ZIntegrate.hpp"
#include "UnitDelay.hpp"

class BPF {

private:
	double mGainB0;
	double mGainB2;
	double mGainA1;
	double mGainA2;

	UnitDelay mInputUnitDelay1;
	UnitDelay mInputUnitDelay2;
	UnitDelay mMidUnitDelay;
	UnitDelay mOutputUnitDelay;

	//Zintegrate1n mInputIntegrate1;
	//Zintegrate1n mInputIntegrate2;
	//Zintegrate1n mMidIntegrate;
	//Zintegrate1n mOutIntegrate;


	double mBuf1 = 0;
	double mBuf2 = 0;
	double mBuf3 = 0;
	double mOutput = 0;

public:
	BPF();
	virtual ~BPF();

	void Init(double pGainB0, double pGainB2, double pGainA1, double pGainA2);
	double Output(double pTime, double pInput);
	bool Check();

};

#endif /* INC_BPF_HPP_ */
