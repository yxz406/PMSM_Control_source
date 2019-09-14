/*
 * MotorMath.hpp
 *
 *  Created on: Sep 2, 2019
 *      Author: watashi
 */

#ifndef INC_MOTORMATH_HPP_
#define INC_MOTORMATH_HPP_

#include "MotorLibDefPack.hpp"
//#include <array>
#include "Matrix.hpp"
#include "Trigonometric.hpp"

class MotorMath {
public:
	MotorMath();
	virtual ~MotorMath();
	static inline std::array<float, 2> clarkTransform (std::array<float, 3> pVector);
	static inline std::array<float, 2> parkTransform( fp_rad pRadian,
												std::array<float, 2> pVector);

	static inline std::array<float, 2> InvparkTransform( fp_rad pRadian,
												   std::array<float, 2> pVector);
	static inline std::array<float, 3> InvclarkTransform (std::array<float, 2> pVector);
};

//input [u,v,w]
//output [a,b]
inline std::array<float, 2> MotorMath::clarkTransform (std::array<float, 3> pVector) {
	//mIalpha = mIu - (mIv + mIw)/2;
	//mIbeta = (mIv - mIw)* 1.7320508f/2;
	return { ( 0.81649658f * ( pVector.at(0) - ((pVector.at(1) + pVector.at(2))/2)  ) ),
				  ( 0.81649658f * ( (pVector.at(1) - pVector.at(2)) * 1.7320508f/2 ) ) };
};

inline std::array<float, 2> MotorMath::parkTransform(fp_rad pRadian, std::array<float, 2> pVector) {
	float sinVal = Trigonometric::sin(pRadian);
	float cosVal = Trigonometric::cos(pRadian);
	float Invsin = -1.0f * sinVal;

	return { ( cosVal * pVector.at(0) + sinVal * pVector.at(1) ),
				  ( Invsin * pVector.at(0) + cosVal * pVector.at(1) ) };

}

inline std::array<float, 2> MotorMath::InvparkTransform(fp_rad pRadian, std::array<float, 2> pVector) {
	//mId =  mLib.getCosList().at(mArg) * mIalpha + mLib.getSinList().at(mArg) * mIbeta;
	//mIq = -mLib.getSinList().at(mArg) * mIalpha + mLib.getCosList().at(mArg) * mIbeta;
	float sinVal = Trigonometric::sin(pRadian);
	float cosVal = Trigonometric::cos(pRadian);
	float Invsin = -1.0f * sinVal;

	return { ( cosVal * pVector.at(0) + Invsin * pVector.at(1) ),
				  ( sinVal * pVector.at(0) + cosVal * pVector.at(1) ) };
}

//input [a,b]
//output [u,v,w]
inline  std::array<float, 3> MotorMath::InvclarkTransform (std::array<float, 2> pVector) {
	//mVu = 0.75f * mValpha;
	//mVv = -0.75f * mValpha + mValpha / 3 + mVbeta / 1.7320508f;
	//mVw = - mValpha / 3 - mVbeta / 1.7320508f;
	std::array<float ,3> RtnArr;
	RtnArr.at(0) = 0.75f * pVector.at(0);
	RtnArr.at(1) = -0.75f * pVector.at(0) + pVector.at(0) / 3 + pVector.at(1) / 1.7320508f;
	RtnArr.at(2) = - pVector.at(0) / 3 - pVector.at(1) / 1.7320508f;
	RtnArr.at(0) = RtnArr.at(0) * 0.81649658f;//√2/3
	RtnArr.at(1) = RtnArr.at(1) * 0.81649658f;//√2/3
	RtnArr.at(2) = RtnArr.at(2) * 0.81649658f;//√2/3
	return RtnArr;
};

#endif /* INC_MOTORMATH_HPP_ */
