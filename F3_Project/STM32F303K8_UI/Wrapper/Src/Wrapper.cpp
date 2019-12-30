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


//#include "SystemTest.hpp"
//
//#include "ADCCtrl.hpp"

//extern ADC_HandleTypeDef hadc3;//動作切り替えの都合で一応入れている

Deus Bosatsu;

void cppWrapper(void){
	//SystemTest::StartTest();
	Bosatsu.Ctrl();

}


void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
{
	Bosatsu.SPICplt();
}

void HAL_SPI_ErrorCallback(SPI_HandleTypeDef *hspi)
{
	Bosatsu.SPIErr();
}
