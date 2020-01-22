/*
 * Matrix.cpp
 *
 *  Created on: Aug 31, 2019
 *      Author: watashi
 */

#include "Matrix.hpp"

Matrix::Matrix() {
	// TODO Auto-generated constructor stub

}

Matrix::~Matrix() {
	// TODO Auto-generated destructor stub
}

//to inline
//std::array<float, 2> Matrix::MatrixMultiple2x2(float pa11, float pa12,
//	                    				float pa21, float pa22,
//										std::array<float, 2> pVector) {
//
//	std::array<float, 2> vector;
//	vector.at(0) = pa11 * pVector.at(0) + pa12 * pVector.at(1);
//	vector.at(1) = pa21 * pVector.at(0) + pa22 * pVector.at(1);
//
//	return vector;
//}

//std::array<float, 2> Matrix::VectorMultiple2x1(float pGain, std::array<float, 2> pVector) {
//
//	std::array<float, 2> vector;
//	vector.at(0) = pGain * pVector.at(0);
//	vector.at(1) = pGain * pVector.at(1);
//
//	return vector;
//}

//std::array<float, 2> Matrix::VectorAdd2x1(std::array<float, 2> pVector1, std::array<float, 2> pVector2) {
//
//	std::array<float, 2> vector;
//	vector.at(0) = pVector1.at(0) + pVector2.at(0);
//	vector.at(1) = pVector1.at(1) + pVector2.at(1);
//
//	return vector;
//}
//std::array<float, 2> Matrix::VectorAdd2x1(std::array<float, 2> pVector1, std::array<float, 2> pVector2, std::array<float, 2> pVector3) {
//
//	std::array<float, 2> vector;
//	vector.at(0) = pVector1.at(0) + pVector2.at(0) + pVector3.at(0);
//	vector.at(1) = pVector1.at(1) + pVector2.at(1) + pVector3.at(1);
//
//	return vector;
//}

//std::array<float, 2> Matrix::VectorSubtract2x1(std::array<float, 2> pVector1, std::array<float, 2> pVector2) {
//
//	std::array<float, 2> vector;
//	vector.at(0) = pVector1.at(0) - pVector2.at(0);
//	vector.at(1) = pVector1.at(1) - pVector2.at(1);
//
//	return vector;
//}


//float Matrix::VectorMultiple1x2_2x1(std::array<float, 2>pVector1, std::array<float, 2> pVector2) {
//
//	float sum;
//	sum = pVector1.at(0) * pVector2.at(0) + pVector1.at(1) * pVector2.at(1);
//
//	return sum;
//}
