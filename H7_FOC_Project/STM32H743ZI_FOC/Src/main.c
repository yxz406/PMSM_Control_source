/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Wrapper.hpp"
#include "stm32h7xx.h"
#include "paramsetting.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */

#include "stm32h7xx_hal_def.h"
#include "stm32h7xx_ll_adc.h"

void ADCInit(void) {
	RCC->AHB4ENR |= ( 0x1UL << 24UL );	//ADC3RST

	RCC->AHB4ENR |= ( 0x1UL << 5UL ); //GPIOFEN //RCC_AHB4ENR_GPIOFEN);
	RCC->AHB4ENR |= ( 0x1UL << 2UL ); //GPIOFEN

	ADC3 -> CR &= ~( 0x1UL << 29UL );//DEEPPWD

	ADC3 -> CR |= ( 0x1UL << 28UL ); //ADVREGEN
	ADC3 -> CR |= ( 0x1UL << 8UL ); //BOOST

	ADC3 -> CFGR |= ( 0x1UL << 31UL ); //JQDIS

	ADC3 -> JSQR |= ( 0x0UL << 27UL ); //JSQ4
	ADC3 -> JSQR |= ( 0x6UL << 21UL ); //JSQ3
	ADC3 -> JSQR |= ( 0x0UL << 15UL ); //JSQ2
	ADC3 -> JSQR |= ( 0x1UL << 9UL ); 	//JSQ1
	ADC3 -> JSQR |= ( 0x1UL << 7UL ); 	//JEXTEN
	ADC3 -> JSQR |= ( 0x1UL << 2UL ); 	//JEXTSEL
	ADC3 -> JSQR |= ( 0x2UL ); 				//JL

	ADC3 -> PCSEL |= 0x43; //プリチャネル選択レジスタ（ADCx_PCSEL）

	//以下はRCCの設定で勝手になる
	//ADC3 -> LHTR1 |= 0x3ffffff; //ADCウォッチドッグ閾値レジスタ 1
	//ADC3 -> LHTR2 |= 0x3ffffff; //ADCウォッチドッグ閾値レジスタ 2
	//ADC3 -> LHTR3 |= 0x3ffffff; //ADCウォッチドッグ閾値レジスタ 3
	//0915 HAL_ADC_MspInit 107まで再現
}

void ADCStart() {
	ADC3 -> CR |= ( 0x1UL ); //ADEN

	int i=0;
	while(	!( (ADC3 -> ISR) && 0x1 ) ){
		//ADRDYの立ち上がりを確認する
		asm("NOP");
		i++; //ADC立ち上がりタイミングデバッグ用
	}
	asm("NOP");

	ADC3 -> CR |= ( 0x1UL << 3UL ); //JADSTART

}

void ADCOFF() {
	while( ADC3 -> ISR && 0b100 ) {
		//ADSTART=1のとき待つ
		asm("NOP");
	}

	while( ADC3 -> ISR && 0b1000 ) {
		//JADSTART=1のとき待つ
		asm("NOP");
	}

	ADC3 -> CR |= ( 0x1UL << 1UL ); //ADDIS

	while( ADC3 -> CR && 0b1 ) {
		//ADEN=1のとき待つ
		asm("NOP");
	}
}

int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */
  

  /* Enable I-Cache---------------------------------------------------------*/
  SCB_EnableICache();

  /* Enable D-Cache---------------------------------------------------------*/
  SCB_EnableDCache();

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */



//enum ADC_REG ADCREG;
//static int ADC_REG;

//
//  {
//	  //ADCInit();
//	  asm("NOP");
//
//	  MX_ADC3_Init();
//	  asm("NOP");
//	  ADCStart();
//
//	  HAL_ADC_Start_IT(&hadc3);
//	  asm("NOP");
//	  //ADC3 -> CFGR |= 0b100000000000000000000;//JDISCEN
//	  //ADC3 -> CFGR |= ADC_REG_CFGR_JDISCEN; // ADC Inject Group Enable
//	  asm("NOP");
//
//	  asm("NOP");
//	  //__HAL_ADC_ENABLE_IT(ADC3, ADC_IT_JEOS);
//      ((ADC3->IER) |= ADC_IT_JEOS);
//	  asm("NOP");
//	  ADC3 -> IER |= 0b01;
//	  asm("NOP");
//	  ADC3 -> IER |= 0b10;
//	  asm("NOP");
//	  ADC3 -> IER |= 0b1000;
//	  asm("NOP");
//      ((ADC3->ISR) |= ADC_IT_JEOS);
//	  WRITE_REG((ADC3 -> ISR), (((ADC3 -> ISR) & (~(LL_ADC_FLAG_EOC))) | (LL_ADC_FLAG_EOS)));
//	  asm("NOP");
//	  //HAL_ADC_Start_IT(&hadc3);
//	  asm("NOP");
//	  ADC3 -> ISR = 0x7FF;
//	  asm("NOP");
//	  asm("NOP");
//	  ADC3 -> ISR = ADC3 -> ISR & ~LL_ADC_FLAG_EOS;
//	  asm("NOP");
//	  ADC3 -> ISR = ADC3 -> ISR | LL_ADC_FLAG_EOS;
//	  asm("NOP");
//  }
//  {
//
//	  //GPIO REG TEST
//	  //MX_GPIO_Init();
//	  RCC->AHB4ENR |= RCC_AHB4ENR_GPIOBEN; // IO portB clock enable
//	  GPIOB->MODER &= ~GPIO_MODER_MODE7_Msk; // initialize pin function
//	  GPIOB->MODER |= (GPIO_MODE_OUTPUT_PP << GPIO_MODER_MODE7_Pos); // set PB7 as GPIO for output
//		for(;;) {
////			asm("NOP");
////			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);
////			asm("NOP");
////			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);
////			for(volatile uint32_t i=0; i<100000; i++); // wait
//			asm("NOP");
//			GPIOB->ODR ^= GPIO_ODR_OD7; // toggle output data
//			asm("NOP");
//			GPIOB->ODR = GPIOB->ODR ^ GPIO_ODR_OD7; // toggle output data
//			asm("NOP");
//			GPIOB->ODR = GPIOB->ODR | GPIO_ODR_OD7; // ON PIN7
//			asm("NOP");
//			GPIOB->ODR = GPIOB->ODR & ~GPIO_ODR_OD7; // OFF PIN7
//
//		}
//  }



  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART3_UART_Init();
 // MX_ADC3_Init();
  ADCInit();
  MX_TIM1_Init();
  ADCStart();
  /* USER CODE BEGIN 2 */
cppWrapper();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Supply configuration update enable 
  */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);
  /** Configure the main internal regulator output voltage 
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}
  /** Macro to configure the PLL clock source 
  */
  __HAL_RCC_PLL_PLLSOURCE_CONFIG(RCC_PLLSOURCE_HSI);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 50;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_3;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART3|RCC_PERIPHCLK_ADC;
  PeriphClkInitStruct.PLL2.PLL2M = 4;
  PeriphClkInitStruct.PLL2.PLL2N = 9;
  PeriphClkInitStruct.PLL2.PLL2P = 1;
  PeriphClkInitStruct.PLL2.PLL2Q = 2;
  PeriphClkInitStruct.PLL2.PLL2R = 2;
  PeriphClkInitStruct.PLL2.PLL2RGE = RCC_PLL2VCIRANGE_3;
  PeriphClkInitStruct.PLL2.PLL2VCOSEL = RCC_PLL2VCOMEDIUM;
  PeriphClkInitStruct.PLL2.PLL2FRACN = 3072;
  PeriphClkInitStruct.Usart234578ClockSelection = RCC_USART234578CLKSOURCE_D2PCLK1;
  PeriphClkInitStruct.AdcClockSelection = RCC_ADCCLKSOURCE_PLL2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
