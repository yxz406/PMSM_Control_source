/*
 * USARTInit.hpp
 *
 *  Created on: Jul 31, 2019
 *      Author: watashi
 */

#ifndef USARTINIT_HPP_
#define USARTINIT_HPP_

#include "STM32SystemPack.h"


#define B1_Pin LL_GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define B1_EXTI_IRQn EXTI15_10_IRQn
#define USART_TX_Pin LL_GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin LL_GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define LD2_Pin LL_GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define TMS_Pin LL_GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin LL_GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define SWO_Pin LL_GPIO_PIN_3
#define SWO_GPIO_Port GPIOB


class USARTInit {
public:
	USARTInit();
	virtual ~USARTInit();
	static void Init();
};

#endif /* USARTINIT_HPP_ */
