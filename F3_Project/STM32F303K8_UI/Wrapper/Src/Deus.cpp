/*
 * Deus.cpp
 *
 *  Created on: Sep 8, 2019
 *      Author: watashi
 */

#include "Deus.hpp"
//#include <iostream>
#include "UICtrl.hpp"


Deus::Deus() {
	// TODO Auto-generated constructor stub
	//mMode = OperationMode::Drive;
	//mMode =OperationMode::Measure;
}

Deus::~Deus() {
	// TODO Auto-generated destructor stub
}


//void Deus::HFTask() {
//	if(mMode == OperationMode::Drive) {
//		M_Ctrl.HighFreqTask();
//	} else if (mMode == OperationMode::Measure) {
//		M_Measure.HighFreqTask();
//	}
//
//}

void Deus::Ctrl() {

	mUICtrl.UITask();

	while(1){

	}
}

//void Deus::BtnAct(){
//	//M_Ctrl.BtnAct();
//
//	if(mMode == OperationMode::Drive) {
//		M_Ctrl.BtnAct();
//
//	} else if (mMode == OperationMode::Measure) {
//		M_Measure.BtnAct();
//		//M_Measure.DeInitSystem();
//	}
//
//
//}
//
//void Deus::BtnAct2(){
//	M_Ctrl.BtnActOFF();
//}
