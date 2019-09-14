///*
// * USARTInit.cpp
// *
// *  Created on: Jul 31, 2019
// *      Author: watashi
// */
//
//#include "USARTInit.hpp"
//
//USARTInit::USARTInit() {
//	// TODO Auto-generated constructor stub
//
//}
//
//USARTInit::~USARTInit() {
//	// TODO Auto-generated destructor stub
//}
//
//void MX_USART2_LL_UART_Init(void);
//
////UART_HandleTypeDef huart2;
////void MX_USART2_HAL_UART_Init(void);
////void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle);
//
//
//void USARTInit::Init() {
//	MX_USART2_LL_UART_Init();
//	//MX_USART2_HAL_UART_Init();
//}
//
//void MX_USART2_LL_UART_Init(void)
//{
//  LL_USART_InitTypeDef USART_InitStruct = {0};
//
//  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
//  /* Peripheral clock enable */
//  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2);
//
//  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
//  /**USART2 GPIO Configuration
//  PA2   ------> USART2_TX
//  PA3   ------> USART2_RX
//  */
//  GPIO_InitStruct.Pin = USART_TX_Pin|USART_RX_Pin;
//  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
//  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
//  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
//  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
//  GPIO_InitStruct.Alternate = LL_GPIO_AF_7;
//  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
//
//  USART_InitStruct.BaudRate = 115200;
//  USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
//  USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
//  USART_InitStruct.Parity = LL_USART_PARITY_NONE;
//  USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
//  USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
//  USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;
//  LL_USART_Init(USART2, &USART_InitStruct);
//  LL_USART_ConfigAsyncMode(USART2);
//  LL_USART_Enable(USART2);
//
//}


//void MX_USART2_HAL_UART_Init(void)
//{
//
//  huart2.Instance = USART2;
//  huart2.Init.BaudRate = 115200;
//  huart2.Init.WordLength = UART_WORDLENGTH_8B;
//  huart2.Init.StopBits = UART_STOPBITS_1;
//  huart2.Init.Parity = UART_PARITY_NONE;
//  huart2.Init.Mode = UART_MODE_TX_RX;
//  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
//  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
//  if (HAL_UART_Init(&huart2) != HAL_OK)
//  {
//	  ErrorHandler::UART_Error_Handler();
//  }
//
//}

//void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
//{
//
//  GPIO_InitTypeDef GPIO_InitStruct = {0};
//  if(uartHandle->Instance==USART2)
//  {
//  /* USER CODE BEGIN USART2_MspInit 0 */
//
//  /* USER CODE END USART2_MspInit 0 */
//    /* USART2 clock enable */
//    __HAL_RCC_USART2_CLK_ENABLE();
//
//    __HAL_RCC_GPIOA_CLK_ENABLE();
//    /**USART2 GPIO Configuration
//    PA2     ------> USART2_TX
//    PA3     ------> USART2_RX
//    */
//    GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
//    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
//    GPIO_InitStruct.Pull = GPIO_PULLUP;
//    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
//    GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
//    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
//
//  /* USER CODE BEGIN USART2_MspInit 1 */
//
//  /* USER CODE END USART2_MspInit 1 */
//  }
//}
//
//void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
//{
//
//  if(uartHandle->Instance==USART2)
//  {
//  /* USER CODE BEGIN USART2_MspDeInit 0 */
//
//  /* USER CODE END USART2_MspDeInit 0 */
//    /* Peripheral clock disable */
//    __HAL_RCC_USART2_CLK_DISABLE();
//
//    /**USART2 GPIO Configuration
//    PA2     ------> USART2_TX
//    PA3     ------> USART2_RX
//    */
//    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2|GPIO_PIN_3);
//
//  /* USER CODE BEGIN USART2_MspDeInit 1 */
//
//  /* USER CODE END USART2_MspDeInit 1 */
//  }
//}
