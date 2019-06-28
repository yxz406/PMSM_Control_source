/*
 * UiCtrl.cpp
 *
 *  Created on: Jun 28, 2019
 *      Author: watashi
 */

#include "UiCtrl.hpp"

UiCtrl::UiCtrl() {
	// TODO Auto-generated constructor stub
	isONBtnState = false;
}

UiCtrl::~UiCtrl() {
	// TODO Auto-generated destructor stub
}

void UiCtrl::BtnAct(){
	if(isONBtnState == true){//ONの時
		isONBtnState = false;

		//offにするタスク
	} else {
		isONBtnState = true;

		//ONにするタスク
	}
}

bool UiCtrl::getState(void){return isONBtnState;}
