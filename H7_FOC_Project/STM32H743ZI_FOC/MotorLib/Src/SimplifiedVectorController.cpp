/*
 * SimplifiedVectorController.cpp
 *
 *  Created on: 2019/11/05
 *      Author: watashi
 */

#include "SimplifiedVectorController.hpp"

SimplifiedVectorController::SimplifiedVectorController(float pR, float pLd, float pLq, float pKe)
:mR(pR), mLd(pLd), mLq(pLq), mKe(pKe)
{
	// TODO Auto-generated constructor stub
	if(mR == 0 | mLd == 0 | mLq == 0 | mKe == 0) {
		//faltHandler();
	}
	mIsInit = true;

}

SimplifiedVectorController::~SimplifiedVectorController() {
	// TODO Auto-generated destructor stub
}

float SimplifiedVectorController::VoltageRefCalc() {

}
