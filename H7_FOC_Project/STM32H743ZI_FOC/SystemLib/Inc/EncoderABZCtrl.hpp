/*
 * EncoderABZCtrl.hpp
 *
 *  Created on: 2019/10/22
 *      Author: watashi
 */

#ifndef INC_ENCODERABZCTRL_HPP_
#define INC_ENCODERABZCTRL_HPP_

#include "paramsetting.h"
#include "STM32SystemPack.h"

class EncoderABZCtrl {
public:
	static TIM_HandleTypeDef mHandleTIM4;

	EncoderABZCtrl();
	virtual ~EncoderABZCtrl();

	//以下HALのWrapper
	static void MX_TIM4_Init(void);
	static void EncoderStart(void);
	static void EncoderStop(void);

	static int GetAngle(void);
};

#endif /* INC_ENCODERABZCTRL_HPP_ */
