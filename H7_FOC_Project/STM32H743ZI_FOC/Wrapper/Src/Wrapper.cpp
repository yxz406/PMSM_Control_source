/*
 * Wrapper.cpp
 *
 *  Created on: Sep 8, 2019
 *      Author: Nakamura(Yutaka)
 */
//このClassだけは、C/C++の架け橋なので、
//.hppの#includeがHedder側でできない。
//なのでソース内に記述する。

#include "Wrapper.hpp"
#include "Deus.hpp"
#include "SystemTest.hpp"

#include "ADCCtrl.hpp"

extern ADC_HandleTypeDef hadc3;//動作切り替えの都合で一応入れている

Deus Bosatsu;

void cppWrapper(void){
	//SystemTest::StartTest();
	Bosatsu.Ctrl();

}

void EXTI15_10_IRQHandler(void)
{
	if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_12) != 0x00U) {
	Bosatsu.BtnAct2();
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_12);
	}
	if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_13) != 0x00U) {
	Bosatsu.BtnAct();
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);
	}
}

void ADC3_IRQHandler(void)
{
  /* USER CODE BEGIN ADC3_IRQn 0 */
	//HighFreqTask();
//	uint32_t reg_status = ADC3 -> ISR;
//	uint32_t new_reg = ( ADC3 -> ISR | 0b00000000100 ) ;

	//ADC3 -> ISR = ADC3 -> ISR | LL_ADC_FLAG_EOS;

	if(ADC3 -> ISR & LL_ADC_FLAG_JEOC ) {
		//各インジェクトシーケンスの終了（JEOC）
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_1, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);

		//ここで動作切り替えてる　Debug/Run
		//SystemTest();
		Bosatsu.HFTask();


		int inittype = 2;
		switch(inittype) {
		case 1:
			ADC3 -> ISR &= ~(LL_ADC_FLAG_JEOC);
			ADC3 -> ISR &= ~(LL_ADC_FLAG_JEOS);
			break;
		case 2:
			ADCCtrl::ADC3IRQHandler();
		break;
		case 3:
			break;
			HAL_ADC_IRQHandler(&hadc3);
		default:
			break;
		}


		//end
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_1, GPIO_PIN_RESET);

	}



//	if(LL_ADC_IsActiveFlag_JEOS(ADC3)) {
//		ADC3 -> ISR &= ~(uint32_t)( LL_ADC_FLAG_JEOS | LL_ADC_FLAG_JQOVF );
//		//各インジェクトシーケンスの終了（JEOC）
//
//		//キューのオーバーフローは、キューがフル状態のときにJSQR レジスタに書き込むと発生しま
//		//す。このオーバーフローは、フラグ JQOVF のアサーションによって示されます。オーバーフ
//		//ローが発生すると、オーバーフローを作成した JSQR レジスタの書き込みアクセスは無視され、
//		//コンテキストのキューは変更されません。J
//
//
//		//HighFreqTask();
	//HAL_ADC_IRQHandler(&hadc3);
//
//	} else {
//
//		//各インジェクト変換の終了（JEOC）
//
//	}



}

void SystemTest(void) {
	//開始直後にADC2を読み取って、変換時間を演算処理の中で相殺する。
	ADCCtrl::ADC2Start_Conversion();
	ADCCtrl::ADC2Conversion_wait(100);
	int adc2 = ADCCtrl::ADC2_Read();
			const float multiple_val = (3.3/65535);
			int adc_u = ADCCtrl::ADC3_INJ_Read_ch1();
			int adc_v = ADCCtrl::ADC3_INJ_Read_ch2();
			int adc_w = ADCCtrl::ADC3_INJ_Read_ch3();
			float voltage_u = (float)adc_u * multiple_val;
			float voltage_v = (float)adc_v * multiple_val;
			float voltage_w = (float)adc_w * multiple_val;
			float voltage_adc2 = (float)adc2 * multiple_val;
			printf("adcVal:%+6.5f, %+6.5f, %+6.5f \r\n", voltage_u, voltage_v, voltage_w);
			printf("adcVal:%+6.5f, %+6.5f, %+6.5f, %+6.5f \r\n", voltage_u, voltage_v, voltage_w, voltage_adc2);
}
