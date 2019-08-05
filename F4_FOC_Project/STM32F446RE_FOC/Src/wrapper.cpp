/*
 * wrapper.cpp
 *
 *  Created on: Jun 17, 2019
 *      Author: watashi
 */

//このClassだけは、C/C++の架け橋なので、
//.hppの#includeがHedder側でできない。
//なのでソース内に記述する。
#include "wrapper.hpp"
#include "MotorCtrl.hpp"


//動作パラメータを設定するファイルを別にする。現在未使用。検討中。
//bool isDebugMode = DEBUG_MODE;
//unsigned int debugCount = DEBUG_COUNT;

MotorCtrl M_Ctrl;



void cppwrapper(void){
	M_Ctrl.InitSystem();
	M_Ctrl.InitMotorInfo();
	M_Ctrl.InitPWM();

	while(1){}
}

void HighFreqTask(){
	M_Ctrl.HighFreqTask();
}


void BtnAct(void) { //割り込みラッパ
	M_Ctrl.BtnAct();
}


