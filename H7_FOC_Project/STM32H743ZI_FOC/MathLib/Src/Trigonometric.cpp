/*
 * Trigonometric.cpp
 *
 *  Created on: Aug 31, 2019
 *      Author: watashi
 */

#include "Trigonometric.hpp"

Trigonometric::Trigonometric() {
	// TODO Auto-generated constructor stub

}

Trigonometric::~Trigonometric() {
	// TODO Auto-generated destructor stub
}

float Trigonometric::sin(const float &pVal) {
	return arm_sin_f32(pVal);
}

float Trigonometric::cos(const float &pVal) {
	return arm_cos_f32(pVal);
}

float Trigonometric::atan2(const float &pNumerator, const float &pDenominator) {
	return atan2f(pNumerator, pDenominator);
}
