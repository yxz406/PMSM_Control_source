/*
 * Deus.cpp
 *
 *  Created on: Sep 8, 2019
 *      Author: watashi
 */

#include "Deus.hpp"
#include <iostream>


Deus::Deus() {
	// TODO Auto-generated constructor stub
	mMode = OperationMode::Drive;
}

Deus::~Deus() {
	// TODO Auto-generated destructor stub
}


void Deus::HFTask() {
	if(mMode == OperationMode::Drive) {
		M_Ctrl.HighFreqTask();
	} else if (mMode == OperationMode::Measure) {
		M_Measure.HighFreqTask();
	}

}

void Deus::Ctrl() {

	if(mMode == OperationMode::Drive) {
		M_Ctrl.InitMotorControl();
		M_Ctrl.InitObserver();

		M_Ctrl.InitSystem();//ここでTIMとADC起動
	} else if (mMode == OperationMode::Measure) {
		M_Measure.InitMotorControl();
		M_Measure.InitObserver();

		M_Measure.InitSystem();
	}


	while(1){
	}
}

void Deus::BtnAct(){
	M_Ctrl.BtnAct();
}

void Deus::BtnAct2(){
	M_Ctrl.BtnActOFF();
}
