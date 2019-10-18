/*
 * ZIntegrate.hpp
 *
 *  Created on: Aug 31, 2019
 *      Author: watashi
 */

#ifndef INC_ZINTEGRATE_HPP_
#define INC_ZINTEGRATE_HPP_

#include <array>


class Zintegrate1n {
private:
	float mK;
	float mInput;
	float mInputOld;

	float mOutput;
	float mOutputOld;


public:
	Zintegrate1n(float pK);
	virtual ~Zintegrate1n();
	void SetDefault(float pInputOld, float pOutputOld);
	float integrate(float pTime, float pInput);
};

class Zintegrate2n {
private:
	Zintegrate1n mIntegrate1;
	Zintegrate1n mIntegrate2;
public:
	Zintegrate2n(float pK);
	virtual ~Zintegrate2n();
	std::array<float, 2> integrate(float pTime, std::array<float, 2> pInput);
};



#endif /* INC_ZINTEGRATE_HPP_ */
