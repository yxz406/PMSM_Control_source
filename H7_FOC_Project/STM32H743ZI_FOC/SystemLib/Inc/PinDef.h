/*
 * PinDef.h
 *
 *  Created on: Jul 31, 2019
 *      Author: watashi
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

#ifndef PINDEF_H_
#define PINDEF_H_


//#define B1_Pin LL_GPIO_PIN_13
//#define B1_GPIO_Port GPIOC
//#define B1_EXTI_IRQn EXTI15_10_IRQn
//#define USART_TX_Pin LL_GPIO_PIN_2
//#define USART_TX_GPIO_Port GPIOA
//#define USART_RX_Pin LL_GPIO_PIN_3
//#define USART_RX_GPIO_Port GPIOA
//#define LD2_Pin LL_GPIO_PIN_5
//#define LD2_GPIO_Port GPIOA
//#define TMS_Pin LL_GPIO_PIN_13
//#define TMS_GPIO_Port GPIOA
//#define TCK_Pin LL_GPIO_PIN_14
//#define TCK_GPIO_Port GPIOA
//#define SWO_Pin LL_GPIO_PIN_3
//#define SWO_GPIO_Port GPIOB


#endif /* PINDEF_H_ */
