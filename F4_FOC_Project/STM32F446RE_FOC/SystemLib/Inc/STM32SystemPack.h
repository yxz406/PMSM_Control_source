/*
 * STM32SystemPack.h
 *
 *  Created on: Jul 31, 2019
 *      Author: watashi
 *
 *
 *  STM32のシステム定義する際に利用するヘッダ集
 *  使う機能によって必要なものが増えたり減ったりするが、
 *  基本的にはSTM32CubeMXのmain.h内部を真似して、
 *
 *  前半のInclude　-> STM32SystemPac.h へ
 *  後半のDefine -> PinDef.h へ
 *
 *  書けば容易に移植ができる。
 *
 *  Q&A
 *  Q.なぜmain.hを使わないのか
 *  A.c++に非対応だから。
 */

#ifndef STM32SYSTEMPACK_H_
#define STM32SYSTEMPACK_H_

//System定義するときによく使うヘッダたち

#include "stm32f4xx_hal.h"
#include "stm32f4xx_ll_adc.h"
#include "stm32f4xx_ll_tim.h"
#include "stm32f4xx_ll_usart.h"
#include "stm32f4xx_ll_rcc.h"
#include "stm32f4xx.h"
#include "stm32f4xx_ll_system.h"
#include "stm32f4xx_ll_gpio.h"
#include "stm32f4xx_ll_exti.h"
#include "stm32f4xx_ll_bus.h"
#include "stm32f4xx_ll_cortex.h"
#include "stm32f4xx_ll_utils.h"
#include "stm32f4xx_ll_pwr.h"
#include "stm32f4xx_ll_dma.h"

//追加でエラーハンドラ
#include "ErrorHandler.hpp"


#endif /* STM32SYSTEMPACK_H_ */
