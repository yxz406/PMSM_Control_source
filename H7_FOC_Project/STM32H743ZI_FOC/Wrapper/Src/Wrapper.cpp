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


Deus Bosatsu;


void cppWrapper(void){
	SystemTest::StartTest();
	//Bosatsu.Ctrl();

}

void HighFreqTask(void){
	Bosatsu.HFTask();

}
