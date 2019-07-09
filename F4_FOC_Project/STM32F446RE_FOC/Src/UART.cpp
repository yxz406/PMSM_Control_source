/*
 * UART.cpp
 *
 *  Created on: Jun 23, 2019
 *      Author: watashi
 */


/*
 * UARTを簡単に叩けるClass
 * 余計な代入が多いからあまり早くはうごかない
 * (そもそもHALを利用したUARTのため、あまり早くならない)
 *
 * 嘘です、LLに対応しました。
 *
 * いろいろな叩き方ができるようには一応してあるつもり。
 */


#include "usart.h"
#include "UART.hpp"

#include "stm32f4xx_hal.h"
#include "stm32f4xx_ll_adc.h"
#include "stm32f4xx_ll_tim.h"
#include "stm32f4xx_ll_usart.h"
#include "stm32f4xx.h"
#include "stm32f4xx_ll_system.h"
#include "stm32f4xx_ll_gpio.h"
#include "stm32f4xx_ll_exti.h"
#include "stm32f4xx_ll_bus.h"
#include "stm32f4xx_ll_cortex.h"
#include "stm32f4xx_ll_rcc.h"
#include "stm32f4xx_ll_utils.h"
#include "stm32f4xx_ll_pwr.h"
#include "stm32f4xx_ll_dma.h"

#include <string>


UART::UART() {
	// TODO Auto-generated constructor stub

	mTimeout = 1000;
}

UART::UART(int pTimeout) : mTimeout(pTimeout) {}

UART::~UART() {
	// TODO Auto-generated destructor stub
}

UART::UART(std::string pStr, int pTimeout)
:mStr(pStr), mTimeout(pTimeout)
{
	const char* str = mStr.c_str();
	for(int i = 0; *(str + i) != '/0'; i++){
		LL_USART_TransmitData8(USART2, *(str + i));
	}
}

void UART::setString(std::string pStr){
	mStr = pStr;
	//mstrSize = mStr.length();
}

void UART::Transmit(void){
	const char* str = mStr.c_str();
	for(int i = 0; *(str + i) != '/0'; i++){
		LL_USART_TransmitData8(USART2, *(str + i));
	}
}

void UART::Transmit(std::string	pStr){
	mStr = pStr;
	const char* str = mStr.c_str();
	for(int i = 0; *(str + i) != '/0'; i++){
		LL_USART_TransmitData8(USART2, *(str + i));
	}
}


//HAL_StatusTypeDef HAL_UART_Transmit(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout)
//{
//  uint16_t *tmp;
//  uint32_t tickstart = 0U;
//
//  /* Check that a Tx process is not already ongoing */
//  if (huart->gState == HAL_UART_STATE_READY)
//  {
//    if ((pData == NULL) || (Size == 0U))
//    {
//      return  HAL_ERROR;
//    }
//
//    /* Process Locked */
//    __HAL_LOCK(huart);
//
//    huart->ErrorCode = HAL_UART_ERROR_NONE;
//    huart->gState = HAL_UART_STATE_BUSY_TX;
//
//    /* Init tickstart for timeout managment */
//    tickstart = HAL_GetTick();
//
//    huart->TxXferSize = Size;
//    huart->TxXferCount = Size;
//    while (huart->TxXferCount > 0U)
//    {
//      huart->TxXferCount--;
//      if (huart->Init.WordLength == UART_WORDLENGTH_9B)
//      {
//        if (UART_WaitOnFlagUntilTimeout(huart, UART_FLAG_TXE, RESET, tickstart, Timeout) != HAL_OK)
//        {
//          return HAL_TIMEOUT;
//        }
//        tmp = (uint16_t *) pData;
//        huart->Instance->DR = (*tmp & (uint16_t)0x01FF);
//        if (huart->Init.Parity == UART_PARITY_NONE)
//        {
//          pData += 2U;
//        }
//        else
//        {
//          pData += 1U;
//        }
//      }
//      else
//      {
//        if (UART_WaitOnFlagUntilTimeout(huart, UART_FLAG_TXE, RESET, tickstart, Timeout) != HAL_OK)
//        {
//          return HAL_TIMEOUT;
//        }
//        huart->Instance->DR = (*pData++ & (uint8_t)0xFF);
//      }
//    }
//
//    if (UART_WaitOnFlagUntilTimeout(huart, UART_FLAG_TC, RESET, tickstart, Timeout) != HAL_OK)
//    {
//      return HAL_TIMEOUT;
//    }
//
//    /* At end of Tx process, restore huart->gState to Ready */
//    huart->gState = HAL_UART_STATE_READY;
//
//    /* Process Unlocked */
//    __HAL_UNLOCK(huart);
//
//    return HAL_OK;
//  }
//  else
//  {
//    return HAL_BUSY;
//  }
//}
