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

float EstimatedAxisError::GetError(std::array<float, 2> pEstEMFgd) {
	float EstEMFg = pEstEMFgd.at(0);
	float EstEMFd = pEstEMFgd.at(1);
	return Trigonometric::atan2(-1.0f * EstEMFg, EstEMFd);
}
