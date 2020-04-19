/*
 * ZIntegrate.hpp
 *
 *  Created on: Aug 31, 2019
 *      Author: watashi
 */

#ifndef INC_ZINTEGRATE_HPP_
#define INC_ZINTEGRATE_HPP_

#include <array>
#include <math.h>

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
	float integrate(const float &pTime, const float &pInput);
};

class Zintegrate1nMod { //TODO 継承してきれいにするべき
protected:
	float mK;
	float mInput;
	float mInputOld;

	float mOutput;
	float mOutputOld;


public:
	Zintegrate1nMod(float pK);
	virtual ~Zintegrate1nMod();
	void SetDefault(float pInputOld, float pOutputOld);
	float integrate(const float &pTime, const float &pInput);
};

class Zintegrate2n {
private:
	Zintegrate1n mIntegrate1;
	Zintegrate1n mIntegrate2;
public:
	Zintegrate2n(float pK);
	virtual ~Zintegrate2n();
	std::array<float, 2> integrate(const float &pTime, const std::array<float, 2> &pInput);
};

inline std::array<float, 2> Zintegrate2n::integrate(const float &pTime, const std::array<float, 2> &pInput) {
	return {mIntegrate1.integrate(pTime, pInput.at(0)), mIntegrate2.integrate(pTime, pInput.at(1))};
}


#endif /* INC_ZINTEGRATE_HPP_ */
