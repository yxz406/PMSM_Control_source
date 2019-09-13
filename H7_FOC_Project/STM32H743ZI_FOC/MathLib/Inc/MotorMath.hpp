/*
 * MotorMath.hpp
 *
 *  Created on: Sep 2, 2019
 *      Author: watashi
 */

#ifndef INC_MOTORMATH_HPP_
#define INC_MOTORMATH_HPP_

#include "MotorLibDefPack.hpp"
//#include <array>
#include "Matrix.hpp"
#include "Trigonometric.hpp"

class MotorMath {
public:
	MotorMath();
	virtual ~MotorMath();
	static std::array<float, 2> clarkTransform (std::array<float, 3> pVector);
	static std::array<float, 2> parkTransform( fp_rad pRadian,
												std::array<float, 2> pVector);

	static std::array<float, 2> InvparkTransform( fp_rad pRadian,
												   std::array<float, 2> pVector);
	static std::array<float, 3> InvclarkTransform (std::array<float, 2> pVector);
};

#endif /* INC_MOTORMATH_HPP_ */
