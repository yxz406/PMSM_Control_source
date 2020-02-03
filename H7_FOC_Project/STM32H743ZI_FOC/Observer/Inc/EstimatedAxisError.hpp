/*
 * EstimatedAxisError.hpp
 *
 *  Created on: Sep 11, 2019
 *      Author: watashi
 */

#ifndef INC_ESTIMATEDAXISERROR_HPP_
#define INC_ESTIMATEDAXISERROR_HPP_

#include <array>
#include "Trigonometric.hpp"

class EstimatedAxisError {
public:
	EstimatedAxisError();
	virtual ~EstimatedAxisError();
	static float GetError(const std::array<float, 2> &pEstEMFgd);
};

#endif /* INC_ESTIMATEDAXISERROR_HPP_ */
