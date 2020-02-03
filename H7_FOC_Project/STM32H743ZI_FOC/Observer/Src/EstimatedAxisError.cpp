/*
 * EstimatedAxisError.cpp
 *
 *  Created on: Sep 11, 2019
 *      Author: watashi
 */


#include "EstimatedAxisError.hpp"

EstimatedAxisError::EstimatedAxisError() {
	// TODO Auto-generated constructor stub

}

EstimatedAxisError::~EstimatedAxisError() {
	// TODO Auto-generated destructor stub
}

float EstimatedAxisError::GetError(const std::array<float, 2> &pEstEMFgd) {
	return Trigonometric::atan2(-1.0f * pEstEMFgd.at(0), pEstEMFgd.at(1));
}
