/*
 * MotorInfo.cpp
 *
 *  Created on: Jun 18, 2019
 *      Author: watashi
 */

#include "MotorInfo.hpp"

MotorInfo::MotorInfo() {
	// TODO Auto-generated constructor stub

}

MotorInfo::~MotorInfo() {
	// TODO Auto-generated destructor stub
}

void MotorInfo::setVu(float pVu){};
void MotorInfo::setVv(float pVv){};
void MotorInfo::setVw(float pVw){};

float MotorInfo::getVu(void){};
float MotorInfo::getVv(void){};
float MotorInfo::getVw(void){};

float MotorInfo::getValpha(void){};
float MotorInfo::getVbeta(void){};
float MotorInfo::getVd(void){};
float MotorInfo::getVq(void){};

float MotorInfo::getId(void){};
float MotorInfo::getIq(void){};

void MotorInfo::parkTransform(void){};
void MotorInfo::clarkTransform(void){};

void MotorInfo::invParkTransform(void){};
void MotorInfo::invClarkTransform(void){};
