/*
 * Matrix.hpp
 *
 *  Created on: Aug 31, 2019
 *      Author: watashi
 *
 *      宣言無しで使えるクラス。
 *      行列の和・積などは、内部に変数を持たないから、
 *      全てPublic Staticで返せばよいよね。
 */

#ifndef INC_MATRIX_HPP_
#define INC_MATRIX_HPP_

#include "DSPInc.hpp"
#include <array>
#include "math.h"

class Matrix {
public:
	Matrix();
	virtual ~Matrix();

	static std::array<float, 2> MatrixMultiple2x2(float pa11, float pa12,
								  float pa21, float pa22,
								  std::array<float, 2> pVector);
	static std::array<float, 2> VectorMultiple2x1(float pGain, std::array<float, 2> pVector);
	static std::array<float, 2> VectorAdd2x1(std::array<float, 2> pVector1, std::array<float, 2> pVector2);//2個のベクトルの足し算
	static std::array<float, 2> VectorAdd2x1(std::array<float, 2> pVector1, std::array<float, 2> pVector2, std::array<float, 2> pVector3);//3個の足し算
	static std::array<float, 2> VectorSubtract2x1(std::array<float, 2> pVector1, std::array<float, 2> pVector2);//2個のベクトルの引き算,pVec1-pVec2


	static float VectorMultiple1x2_2x1(std::array<float, 2> pVector1, std::array<float, 2> pVector2);



};

#endif /* INC_MATRIX_HPP_ */
