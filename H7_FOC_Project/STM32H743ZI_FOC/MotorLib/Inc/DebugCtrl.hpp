/*
 * DebugCtrl.hpp
 *
 *  Created on: Aug 8, 2019
 *      Author: watashi
 */

#ifndef DEBUGCTRL_HPP_
#define DEBUGCTRL_HPP_

#include "MotorInfo.hpp"
#include "UIStatus.hpp"
//#include "math.h"
#include "SEGGER_RTT.h"

//#include <string>

union ParseFloatToByte {
    float mFloat;      // ここを送りたい型にする
    char mByte[4];     // 送りたい型のbyte数を要素数に指定する
};

union ParseIntToByte {
    int mInt;      // ここを送りたい型にする
    char mByte[4];     // 送りたい型のbyte数を要素数に指定する
};

class ConvertToByte{

private:
	ParseFloatToByte mFloatConverter;
	ParseIntToByte	mIntConverter;

public:
	void ConvertData(float pInput, std::array<char ,4> &pOutput) {
		mFloatConverter.mFloat = pInput;
		char serialData[4];
	    for (int i = 0; i < 4; ++i) {
	        pOutput[i] = mFloatConverter.mByte[3-i];
	    }
	}
	void ConvertData(int pInput, std::array<char ,4> &pOutput) {
		mIntConverter.mInt = pInput;
		char serialData[4];
	    for (int i = 0; i < 4; ++i) {
	        pOutput[i] = mIntConverter.mByte[3-i];
	    }
	}

};


class DebugCtrl {
private:
	int mLogcount;
	std::string mOutputStr;
	char mOutputChar[128] = {};

	ConvertToByte mConverter;

public:
	DebugCtrl();
	virtual ~DebugCtrl();
	void RTTOutput(const MotorInfo &pMotorInfo, const UIStatus &pUIStatus);
	void AddOutputString(const MotorInfo &pMotorInfo);

};



#endif /* DEBUGCTRL_HPP_ */
