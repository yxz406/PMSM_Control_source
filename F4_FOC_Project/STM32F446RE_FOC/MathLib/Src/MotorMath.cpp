/*
 * MotorMath.cpp
 *
 *  Created on: Sep 2, 2019
 *      Author: watashi
 */

#include "MotorMath.hpp"

MotorMath::MotorMath() {
	// TODO Auto-generated constructor stub

}

MotorMath::~MotorMath() {
	// TODO Auto-generated destructor stub
}


//input [u,v,w]
//output [a,b]
std::array<float, 2> MotorMath::clarkTransform (std::array<float, 3> pVector) {
	std::array<float ,2> RtnArr;
	//mIalpha = mIu - (mIv + mIw)/2;
	//mIbeta = (mIv - mIw)* 1.7320508f/2;
	RtnArr.at(0) = pVector.at(0) - ((pVector.at(1) + pVector.at(2))/2) ;
	RtnArr.at(1) = (pVector.at(1) - pVector.at(2)) * 1.7320508f/2;

	return RtnArr;
};


std::array<float, 2> MotorMath::parkTransform(fp_rad pRadian, std::array<float, 2> pVector) {
	//mId =  mLib.getCosList().at(mArg) * mIalpha + mLib.getSinList().at(mArg) * mIbeta;
	//mIq = -mLib.getSinList().at(mArg) * mIalpha + mLib.getCosList().at(mArg) * mIbeta;
	float sinVal = Trigonometric::sin(pRadian);
	float cosVal = Trigonometric::cos(pRadian);
	float Invsin = -1.0f * sinVal;

	std::array<float, 2> RtnArr;
	RtnArr.at(0) = cosVal * pVector.at(0) + sinVal * pVector.at(1);
	RtnArr.at(1) = Invsin * pVector.at(0) + cosVal * pVector.at(1);

	return RtnArr;
}

std::array<float, 2> MotorMath::InvparkTransform(fp_rad pRadian, std::array<float, 2> pVector) {
	//mId =  mLib.getCosList().at(mArg) * mIalpha + mLib.getSinList().at(mArg) * mIbeta;
	//mIq = -mLib.getSinList().at(mArg) * mIalpha + mLib.getCosList().at(mArg) * mIbeta;
	float sinVal = Trigonometric::sin(pRadian);
	float cosVal = Trigonometric::cos(pRadian);
	float Invsin = -1.0f * sinVal;

	std::array<float, 2> RtnArr;
	RtnArr.at(0) = cosVal * pVector.at(0) + Invsin * pVector.at(1);
	RtnArr.at(1) = sinVal * pVector.at(0) + cosVal * pVector.at(1);

	return RtnArr;
}

//input [a,b]
//output [u,v,w]
std::array<float, 3> MotorMath::InvclarkTransform (std::array<float, 2> pVector) {
	//mVu = 0.75f * mValpha;
	//mVv = -0.75f * mValpha + mValpha / 3 + mVbeta / 1.7320508f;
	//mVw = - mValpha / 3 - mVbeta / 1.7320508f;
	std::array<float ,3> RtnArr;
	RtnArr.at(0) = 0.75f * pVector.at(0);
	RtnArr.at(1) = -0.75f * pVector.at(0) + pVector.at(0) / 3 + pVector.at(1) / 1.7320508f;
	RtnArr.at(2) = - pVector.at(0) / 3 - pVector.at(1) / 1.7320508f;
	return RtnArr;
};
