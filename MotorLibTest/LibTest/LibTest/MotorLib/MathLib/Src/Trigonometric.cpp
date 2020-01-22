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

float Trigonometric::sin(float pVal) {
	return arm_sin_f32(pVal);
}

float Trigonometric::cos(float pVal) {
	return arm_cos_f32(pVal);
}

float Trigonometric::atan2(float pNumerator, float pDenominator) {
	return atan2f(pNumerator, pDenominator);
}
