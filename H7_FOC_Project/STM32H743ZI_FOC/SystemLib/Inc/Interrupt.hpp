/*
 * Interrupt.hpp
 *
 *  Created on: Sep 7, 2019
 *      Author: watashi
 */

#ifndef INC_INTERRUPT_HPP_
#define INC_INTERRUPT_HPP_

#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"
#include "wrapper.hpp"


void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
void ADC_IRQHandler(void);
void TIM1_BRK_TIM9_IRQHandler(void);
void TIM1_UP_TIM10_IRQHandler(void);
void EXTI15_10_IRQHandler(void);

#ifdef __cplusplus
}
#endif

#endif /* INC_INTERRUPT_HPP_ */
