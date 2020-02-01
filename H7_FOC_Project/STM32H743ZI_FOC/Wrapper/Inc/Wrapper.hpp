/*
 * Wrapper.hpp
 *
 *  Created on: Sep 8, 2019
 *      Author: Nakamura(Yutaka)
 */

#ifndef WRAPPER_HPP_
#define WRAPPER_HPP_

#include "stm32h7xx_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

void cppWrapper(void);
void HighFreqTask(void);

void HAL_SPI_TxRxHalfCpltCallback(SPI_HandleTypeDef *hspi);
void HAL_SPI_ErrorCallback(SPI_HandleTypeDef *hspi);
void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi);

void DMA1_Stream0_IRQHandler(void);
void DMA1_Stream1_IRQHandler(void);

void EXTI15_10_IRQHandler(void);
void SPI4_IRQHandler(void);
void ADC3_IRQHandler(void);
#ifdef __cplusplus
};
#endif


#endif /* APPLICATION_USER_WRAPPER_HPP_ */
