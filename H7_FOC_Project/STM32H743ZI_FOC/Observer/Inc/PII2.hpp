/*
 * PII2.hpp
 *
 *  Created on: Sep 11, 2019
 *      Author: watashi
 */

#ifndef INC_PII2_HPP_
#define INC_PII2_HPP_

#include "ZIntegrate.hpp"

class PII2 {
private:
	//定義
	float mCycleTime;
	float mK1;
	float mK2;
	float mK3;

	//入力値
	float mInputVal;

	//内部変数
	float mBufVal1;
	float mBufVal2;
	float mBufVal3;
	Zintegrate1n mBufVal4ITG;
	float mBufVal4;
	float mBufVal5;
	Zintegrate1nMod mBufVal6ITG;
	float mBufVal6;

	//出力値
	float mOutputVal;

public:
	PII2();
	virtual ~PII2();

	//Initializer
	void InitCycleTime(float pCycleTime);
	void InitGainK1(float pK1);
	void InitGainK2(float pK2);
	void InitGainK3(float pK3);

	void ThetaResetForOpenLoop(const float &pTheta);

	//Setter
	void SetValue(const float &pInputVal);

	//void Calculator
	void Calculate();

	//Getter
	float GetTheta();
	float GetOmega();
};

#endif /* INC_PII2_HPP_ */
