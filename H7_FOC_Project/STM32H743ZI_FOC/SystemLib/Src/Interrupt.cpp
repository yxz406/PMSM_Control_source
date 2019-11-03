///*
// * Interrupt.cpp
// *
// *  Created on: Sep 7, 2019
// *      Author: watashi
// */
//
#include "Interrupt.hpp"

/******************************************************************************/
/*           Cortex Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */

  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32H7xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32h7xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles TIM1 break interrupt.
  */
void TIM1_BRK_IRQHandler(void)
{
  /* USER CODE BEGIN TIM1_BRK_IRQn 0 */

  /* USER CODE END TIM1_BRK_IRQn 0 */
  HAL_TIM_IRQHandler(&TIMCtrl::mHandleTIM1);
  /* USER CODE BEGIN TIM1_BRK_IRQn 1 */

  /* USER CODE END TIM1_BRK_IRQn 1 */
}

/**
  * @brief This function handles TIM1 update interrupt.
  */
void TIM1_UP_IRQHandler(void)
{
  /* USER CODE BEGIN TIM1_UP_IRQn 0 */
//	HighFreqTask();
  /* USER CODE END TIM1_UP_IRQn 0 */
  HAL_TIM_IRQHandler(&TIMCtrl::mHandleTIM1);
  /* USER CODE BEGIN TIM1_UP_IRQn 1 */

  /* USER CODE END TIM1_UP_IRQn 1 */
}

/**
  * @brief This function handles TIM1 trigger and commutation interrupts.
  */
void TIM1_TRG_COM_IRQHandler(void)
{
  /* USER CODE BEGIN TIM1_TRG_COM_IRQn 0 */

  /* USER CODE END TIM1_TRG_COM_IRQn 0 */
  HAL_TIM_IRQHandler(&TIMCtrl::mHandleTIM1);
  /* USER CODE BEGIN TIM1_TRG_COM_IRQn 1 */

  /* USER CODE END TIM1_TRG_COM_IRQn 1 */
}

/**
  * @brief This function handles TIM1 capture compare interrupt.
  */
void TIM1_CC_IRQHandler(void)
{
  /* USER CODE BEGIN TIM1_CC_IRQn 0 */

  /* USER CODE END TIM1_CC_IRQn 0 */
  HAL_TIM_IRQHandler(&TIMCtrl::mHandleTIM1);
  /* USER CODE BEGIN TIM1_CC_IRQn 1 */

  /* USER CODE END TIM1_CC_IRQn 1 */
}

/**
  * @brief This function handles EXTI line[15:10] interrupts.
  */
//void EXTI15_10_IRQHandler(void)
//{
//  /* USER CODE BEGIN EXTI15_10_IRQn 0 */
////////
//  /* USER CODE END EXTI15_10_IRQn 0 */
//  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_12);
//  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);
//  /* USER CODE BEGIN EXTI15_10_IRQn 1 */
////////
//  /* USER CODE END EXTI15_10_IRQn 1 */
//}

/**
  * @brief This function handles ADC3 global interrupt.
  */
//void ADC3_IRQHandler(void)
//{
//  /* USER CODE BEGIN ADC3_IRQn 0 */
//////////	//HighFreqTask();
////////////	uint32_t reg_status = ADC3 -> ISR;
////////////	uint32_t new_reg = ( ADC3 -> ISR | 0b00000000100 ) ;
//////////
//////////	//ADC3 -> ISR = ADC3 -> ISR | LL_ADC_FLAG_EOS;
//////////
//////////	if(ADC3 -> ISR && LL_ADC_FLAG_JEOC ) {
//////////		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
//////////		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_1, GPIO_PIN_SET);
//////////		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
//////////		for(int i=0; i<25000000; i++)asm("NOP");
//////////		//asm("NOP");
//////////		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
//////////		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
//////////		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_1, GPIO_PIN_RESET);
//////////		ADC3 -> ISR &= ~(LL_ADC_FLAG_JEOC);
//////////
//////////	}
//////////
//////////
//////////	if(LL_ADC_IsActiveFlag_JEOS(ADC3)) {
//////////		ADC3 -> ISR &= ~(uint32_t)( LL_ADC_FLAG_JEOS | LL_ADC_FLAG_JQOVF );
//////////		//???��?��??��?��?インジェクトシーケンスの終�?????��?��??��?��?JEOC????��?��??��?��?
//////////
//////////		//キューのオーバ�????��?��??��?��フローは、キューがフル状態�????��?��??��?��ときにJSQR レジスタに書き込???��?��??��?��?と発生しま
//////////		//す�????��?��??��?��こ�???��?��オーバ�????��?��??��?��フローは、フラグ JQOVF のアサーションによって示されます�????��?��??��?��オーバ�????��?��??��?��???��?��??��?��?
//////////		//ローが発生すると、オーバ�????��?��??��?��フローを作�????��?��??��?��し�? JSQR レジスタの書き込みアクセスは無視され�??
//////////		//コン???��?��??��?��?キスト�????��?��??��?��キューは変更されません???��?��??��?��?J
//////////
//////////
//////////		//HighFreqTask();
//////////		//HAL_ADC_IRQHandler(&hadc3);
//////////
//////////	} else {
//////////
//////////		//???��?��??��?��?インジェクト変換の終�?????��?��??��?��?JEOC????��?��??��?��?
//////////
//////////	}
//////////	//HAL_ADC
//  /* USER CODE END ADC3_IRQn 0 */
//  HAL_ADC_IRQHandler(&hadc3);
//  /* USER CODE BEGIN ADC3_IRQn 1 */
//////////  //asm("NOP");
//  /* USER CODE END ADC3_IRQn 1 */
//}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/


