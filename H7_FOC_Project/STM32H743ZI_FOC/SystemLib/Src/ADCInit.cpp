/*
 * ADCInit.cpp
 *
 *  Created on: Jul 31, 2019
 *      Author: watashi
 */


#include "ADCInit.hpp"


void ADCInit::ADC3Init() {
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
	ADC3 -> JSQR |= ( 0x8UL << 2UL ); 	//JEXTSEL
	ADC3 -> JSQR |= ( 0x2UL ); 				//JL

	ADC3 -> PCSEL |= 0x43; //プリチャネル選択レジスタ

	//NVIC -> ISER3 |= 0x80000000;
	//NVIC -> ICER3 |= 0x80000000;
	//NVIC->ISER[(((uint32_t)(int32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)(int32_t)IRQn) & 0x1FUL));
    HAL_NVIC_SetPriority(ADC3_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(ADC3_IRQn);
	NVIC->ISER[(((uint32_t)(int32_t)127) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)(int32_t)127) & 0x1FUL));
	//以下RCCの設定で勝手になる。
	//ADC3 -> LHTR1 |= 0x3ffffff; //ADCウォッチドッグ閾値レジスタ 1
	//ADC3 -> LHTR2 |= 0x3ffffff; //ADCウォッチドッグ閾値レジスタ 2
	//ADC3 -> LHTR3 |= 0x3ffffff; //ADCウォッチドッグ閾値レジスタ 3
	//0915 HAL_ADC_MspInit 107まで再現
}

void ADCInit::ADC3Enable() {
	//	ソフトウェアでの ADC の有効化手順
	//	1. ADC_ISR レジスタの ADRDY ビットに「1」を書き込んでクリアします。
	//	2. ADEN=1 にセットします。
	//	3. ADRDY=1 になるまで待ちます（ADRDY は ADC 起動時間後にセットされます）。これは、対応
	//	する割り込みを使用することで実行できます（ADRDYIE=1 をセットします）。
	//	4. ADC_ISR レジスタの ADRDY ビットに「1」を書き込んでクリアします（オプション）。

	ADC3 -> ISR |= ( 0x1UL ); //ADRDY

	ADC3 -> CR |= ( 0x1UL ); //ADEN

	int i=0;
	while(	!( (ADC3 -> ISR) & 0x1 ) ){
		//ADRDYの立ち上がりを確認する
		asm("NOP");
		i++; //ADC立ち上がりタイミングのデバッグ用カウンタ
	}
	asm("NOP");

	ADC3 -> CR |= ( 0x1UL << 3UL ); //JADSTART
}

void ADCInit::ADC3EnableIT() {
	/*LL_ADC_Enable(ADC3);*/
    ADC3 -> CR &= ~( 0x1UL << 31UL ); //ADCAL
    ADC3 -> CR &= ~( 0x1UL << 5UL ); //JADSTP
    ADC3 -> CR &= ~( 0x1UL << 4UL ); //ADSTP
    ADC3 -> CR &= ~( 0x1UL << 3UL ); //JADSTART
    ADC3 -> CR &= ~( 0x1UL << 2UL ); //ADSTART
    ADC3 -> CR &= ~( 0x1UL << 1UL ); //ADDIS
    ADC3 -> CR &= ~( 0x1UL ); //ADEN

    ADC3 -> CR |= ( 0x1UL ); //ADEN


    if ( (ADC3 -> CFGR & ADC_CFGR_JQM) != 0UL)
    {
      ADC3 -> IER |= ( 0x1UL << 10UL ); //JQOVFIE
    }

    /* Enable ADC end of conversion interrupt */
    /*__HAL_ADC_DISABLE_IT(hadc, ADC_IT_JEOC); */
    //ADC3 -> IER &= ~( 0x1UL << 5UL ); //JEOCIE

    /*__HAL_ADC_ENABLE_IT(hadc, ADC_IT_JEOS);*/
    //ADC3 -> IER &= ~( 0x1UL << 6UL ); //JEOSIE

    /*__HAL_ADC_DISABLE_IT(hadc, ADC_IT_JEOS);*/
    ADC3 -> IER &= ~( 0x1UL << 6UL ); //JEOSIE

    /*__HAL_ADC_ENABLE_IT(hadc, ADC_IT_JEOC);*/
    ADC3 -> IER |= ( 0x1UL << 5UL ); //JEOCIE

    /*LL_ADC_INJ_StartConversion(ADC3);*/
    ADC3 -> CR &= ~( 0x1UL << 31UL ); //ADCAL
    ADC3 -> CR &= ~( 0x1UL << 5UL ); //JADSTP
    ADC3 -> CR &= ~( 0x1UL << 4UL ); //ADSTP
    ADC3 -> CR &= ~( 0x1UL << 3UL ); //JADSTART
    ADC3 -> CR &= ~( 0x1UL << 2UL ); //ADSTART
    ADC3 -> CR &= ~( 0x1UL << 1UL ); //ADDIS
    ADC3 -> CR &= ~( 0x1UL ); //ADEN

    ADC3 -> CR |= ( 0x1UL << 3UL ); //JADSTART
}


void ADCInit::ADC3Disable() {
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



