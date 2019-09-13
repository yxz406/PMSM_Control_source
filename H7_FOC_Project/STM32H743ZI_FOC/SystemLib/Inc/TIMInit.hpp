/*
 * TIMInit.hpp
 *
 *  Created on: Jul 30, 2019
 *      Author: watashi
 */

#ifndef TIMINIT_HPP_
#define TIMINIT_HPP_

#include "STM32SystemPack.h"
#include "paramsetting.h"


class TIMInit {
public:
	TIMInit();
	virtual ~TIMInit();
	static void Init();
};

#endif /* TIMINIT_HPP_ */
