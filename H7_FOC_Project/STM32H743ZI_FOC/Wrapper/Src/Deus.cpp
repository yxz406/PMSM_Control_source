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
}

Deus::~Deus() {
	// TODO Auto-generated destructor stub
}


void Deus::HFTask() {
	M_Ctrl.HighFreqTask();
}

void Deus::Ctrl() {

	M_Ctrl.InitMotorControl();
	M_Ctrl.InitObserver();

	M_Ctrl.InitSystem();//ここでTIMとADC起動

	while(1){
	}
}

void Deus::BtnAct(){
	M_Ctrl.BtnAct();
}

void Deus::BtnAct2(){
	M_Ctrl.BtnActOFF();
}
