/*
 * Interrupt.cpp
 *
 *  Created on: Sep 7, 2019
 *      Author: watashi
 */

#include "Interrupt.hpp"

extern ADC_HandleTypeDef hadc3;

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void) {
}


void HardFault_Handler(void) {
  while (1){}
}

void MemManage_Handler(void) {
  while (1){}
}

void BusFault_Handler(void) {
  while (1){}
}

void UsageFault_Handler(void) {
  while (1){}
}

void SVC_Handler(void) {
}

void DebugMon_Handler(void) {
}

void PendSV_Handler(void) {
}

void SysTick_Handler(void) {
  HAL_IncTick();
}

/******************************************************************************/
/* STM32F4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f4xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles ADC1, ADC2 and ADC3 interrupts.
  */
void ADC_IRQHandler(void) {
	if(LL_ADC_IsActiveFlag_JEOS(ADC1)) {
		ADC1 -> SR &= ~(uint32_t)( LL_ADC_FLAG_JEOS | LL_ADC_FLAG_JSTRT );
		HighFreqTask();
		HAL_ADC_IRQHandler(&hadc3);
	} else {
	}
}

/**
  * @brief This function handles TIM1 break interrupt and TIM9 global interrupt.
  */
void TIM1_BRK_TIM9_IRQHandler(void) {
}

/**
  * @brief This function handles TIM1 update interrupt and TIM10 global interrupt.
  */
void TIM1_UP_TIM10_IRQHandler(void) {

}

/**
  * @brief This function handles EXTI line[15:10] interrupts.
  */
void EXTI15_10_IRQHandler(void) {
  if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_13) != RESET) {
	  LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_13);
	  BtnAct();
  }

}

