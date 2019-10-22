/*
 * EncoderABZInit.hpp
 *
 *  Created on: Oct 22, 2019
 *      Author: watashi
 */

#ifndef INC_ENCODERABZINIT_HPP_
#define INC_ENCODERABZINIT_HPP_

#include "STM32SystemPack.h"
#include "paramsetting.h"


class EncoderABZInit {
public:
	EncoderABZInit();
	virtual ~EncoderABZInit();
	static void Init(TIM_HandleTypeDef *phtim);
};

#endif /* INC_ENCODERABZINIT_HPP_ */
