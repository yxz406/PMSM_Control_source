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

float MotorInfo::getVu(void){return mVu;};
float MotorInfo::getVv(void){return mVv;};
float MotorInfo::getVw(void){return mVw;};

float MotorInfo::getValpha(void){return mValpha;};
float MotorInfo::getVbeta(void){return mVbeta;};

float MotorInfo::getVd(void){return mVd;};
float MotorInfo::getVq(void){return mVq;};

float MotorInfo::getId(void){return mId;};
float MotorInfo::getIq(void){return mIq;};

void MotorInfo::parkTransform(void){};
void MotorInfo::clarkTransform(void){};

void MotorInfo::invParkTransform(void){};
void MotorInfo::invClarkTransform(void){};
