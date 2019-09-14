///*
// * Interrupt.cpp
// *
// *  Created on: Sep 7, 2019
// *      Author: watashi
// */
//
#include "Interrupt.hpp"
//
/* External variables --------------------------------------------------------*/
//extern ADC_HandleTypeDef hadc3;
//extern TIM_HandleTypeDef htim1;
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
//void NMI_Handler(void)
//{
//  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */
//
//  /* USER CODE END NonMaskableInt_IRQn 0 */
//  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
//
//  /* USER CODE END NonMaskableInt_IRQn 1 */
//}
//
///**
//  * @brief This function handles Hard fault interrupt.
//  */
//void HardFault_Handler(void)
//{
//  /* USER CODE BEGIN HardFault_IRQn 0 */
//
//  /* USER CODE END HardFault_IRQn 0 */
//  while (1)
//  {
//    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
//    /* USER CODE END W1_HardFault_IRQn 0 */
//  }
//}
//
///**
//  * @brief This function handles Memory management fault.
//  */
//void MemManage_Handler(void)
//{
//  /* USER CODE BEGIN MemoryManagement_IRQn 0 */
//
//  /* USER CODE END MemoryManagement_IRQn 0 */
//  while (1)
//  {
//    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
//    /* USER CODE END W1_MemoryManagement_IRQn 0 */
//  }
//}
//
///**
//  * @brief This function handles Pre-fetch fault, memory access fault.
//  */
//void BusFault_Handler(void)
//{
//  /* USER CODE BEGIN BusFault_IRQn 0 */
//
//  /* USER CODE END BusFault_IRQn 0 */
//  while (1)
//  {
//    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
//    /* USER CODE END W1_BusFault_IRQn 0 */
//  }
//}
//
///**
//  * @brief This function handles Undefined instruction or illegal state.
//  */
//void UsageFault_Handler(void)
//{
//  /* USER CODE BEGIN UsageFault_IRQn 0 */
//
//  /* USER CODE END UsageFault_IRQn 0 */
//  while (1)
//  {
//    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
//    /* USER CODE END W1_UsageFault_IRQn 0 */
//  }
//}
//
///**
//  * @brief This function handles System service call via SWI instruction.
//  */
//void SVC_Handler(void)
//{
//  /* USER CODE BEGIN SVCall_IRQn 0 */
//
//  /* USER CODE END SVCall_IRQn 0 */
//  /* USER CODE BEGIN SVCall_IRQn 1 */
//
//  /* USER CODE END SVCall_IRQn 1 */
//}
//
///**
//  * @brief This function handles Debug monitor.
//  */
//void DebugMon_Handler(void)
//{
//  /* USER CODE BEGIN DebugMonitor_IRQn 0 */
//
//  /* USER CODE END DebugMonitor_IRQn 0 */
//  /* USER CODE BEGIN DebugMonitor_IRQn 1 */
//
//  /* USER CODE END DebugMonitor_IRQn 1 */
//}
//
///**
//  * @brief This function handles Pendable request for system service.
//  */
//void PendSV_Handler(void)
//{
//  /* USER CODE BEGIN PendSV_IRQn 0 */
//
//  /* USER CODE END PendSV_IRQn 0 */
//  /* USER CODE BEGIN PendSV_IRQn 1 */
//
//  /* USER CODE END PendSV_IRQn 1 */
//}
//
///**
//  * @brief This function handles System tick timer.
//  */
//void SysTick_Handler(void)
//{
//  /* USER CODE BEGIN SysTick_IRQn 0 */
//
//  /* USER CODE END SysTick_IRQn 0 */
//  HAL_IncTick();
//  /* USER CODE BEGIN SysTick_IRQn 1 */
//
//  /* USER CODE END SysTick_IRQn 1 */
//}
//
///******************************************************************************/
///* STM32H7xx Peripheral Interrupt Handlers                                    */
///* Add here the Interrupt Handlers for the used peripherals.                  */
///* For the available peripheral interrupt handler names,                      */
///* please refer to the startup file (startup_stm32h7xx.s).                    */
///******************************************************************************/
//
///**
//  * @brief This function handles TIM1 break interrupt.
//  */
//void TIM1_BRK_IRQHandler(void)
//{
//  /* USER CODE BEGIN TIM1_BRK_IRQn 0 */
//
//  /* USER CODE END TIM1_BRK_IRQn 0 */
//  //HAL_TIM_IRQHandler(Deus::mhtim1);
//  /* USER CODE BEGIN TIM1_BRK_IRQn 1 */
//
//  /* USER CODE END TIM1_BRK_IRQn 1 */
//}
//
///**
//  * @brief This function handles TIM1 update interrupt.
//  */
//void TIM1_UP_IRQHandler(void)
//{
//  /* USER CODE BEGIN TIM1_UP_IRQn 0 */
//
//  /* USER CODE END TIM1_UP_IRQn 0 */
//  //HAL_TIM_IRQHandler(Deus::mhtim1);
//  /* USER CODE BEGIN TIM1_UP_IRQn 1 */
//
//  /* USER CODE END TIM1_UP_IRQn 1 */
//}
//
///**
//  * @brief This function handles ADC3 global interrupt.
//  */
//void ADC3_IRQHandler(void)
//{
//  /* USER CODE BEGIN ADC3_IRQn 0 */
//
//  /* USER CODE END ADC3_IRQn 0 */
//  //HAL_ADC_IRQHandler(Deus::madc3);
//  /* USER CODE BEGIN ADC3_IRQn 1 */
//
//  /* USER CODE END ADC3_IRQn 1 */
//}



//extern ADC_HandleTypeDef hadc3;
//
///******************************************************************************/
///*           Cortex-M4 Processor Interruption and Exception Handlers          */
///******************************************************************************/
///**
//  * @brief This function handles Non maskable interrupt.
//  */
//void NMI_Handler(void) {
//}
//
//
//void HardFault_Handler(void) {
//  while (1){}
//}
//
//void MemManage_Handler(void) {
//  while (1){}
//}
//
//void BusFault_Handler(void) {
//  while (1){}
//}
//
//void UsageFault_Handler(void) {
//  while (1){}
//}
//
//void SVC_Handler(void) {
//}
//
//void DebugMon_Handler(void) {
//}
//
//void PendSV_Handler(void) {
//}
//
//void SysTick_Handler(void) {
//  HAL_IncTick();
//}
//
///******************************************************************************/
///* STM32F4xx Peripheral Interrupt Handlers                                    */
///* Add here the Interrupt Handlers for the used peripherals.                  */
///* For the available peripheral interrupt handler names,                      */
///* please refer to the startup file (startup_stm32f4xx.s).                    */
///******************************************************************************/
//
///**
//  * @brief This function handles ADC1, ADC2 and ADC3 interrupts.
//  */
//void ADC_IRQHandler(void) {
//	if(LL_ADC_IsActiveFlag_JEOS(ADC1)) {
//		ADC1 -> SR &= ~(uint32_t)( LL_ADC_FLAG_JEOS | LL_ADC_FLAG_JSTRT );
//		HighFreqTask();
//		HAL_ADC_IRQHandler(&hadc3);
//	} else {
//	}
//}
//
///**
//  * @brief This function handles TIM1 break interrupt and TIM9 global interrupt.
//  */
//void TIM1_BRK_TIM9_IRQHandler(void) {
//}
//
///**
//  * @brief This function handles TIM1 update interrupt and TIM10 global interrupt.
//  */
//void TIM1_UP_TIM10_IRQHandler(void) {
//
//}
//
///**
//  * @brief This function handles EXTI line[15:10] interrupts.
//  */
//void EXTI15_10_IRQHandler(void) {
//  if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_13) != RESET) {
//	  LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_13);
//	  BtnAct();
//  }
//
//}

