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

	static inline fp_rad AngleDiff(fp_rad pAnglePlus, fp_rad pAngleMinus);
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

//input
//+10が出力の時
//Nominal 30 20
//Carry    5 355
//が存在する。
//Nominal:diff=10, diff_carry=390-20=370,diff_borrow=30-(380)=-350
//Carry  :diff=-350,diff_carry=365-355=10,diff_borrow=5-(715)=-710
//min(diff^2,diff_carry^2)が答えとなる。
//
//-20が出力の時
//Nominal 20 40
//Borrow 350 10
//Nominal:diff_carry=380-40=340 ,diff=-20,diff_borrow=20-(400)=-380
//Borrow:diff_carry=710-10=700 ,diff=340, diff_borrow=350-(370)=-20
inline fp_rad MotorMath::AngleDiff(fp_rad pAnglePlus, fp_rad pAngleMinus) {
	fp_rad diff = pAnglePlus - pAngleMinus;
	fp_rad diff_carry = pAnglePlus + 2*PI - pAngleMinus;
	fp_rad diff_borrow = pAnglePlus - (pAngleMinus + 2*PI);

	float diff2 = diff * diff;
	float diff_carry2 = diff_carry * diff_carry;
	float diff_borrow2 = diff_borrow * diff_borrow;

	if(diff2 < diff_carry2) {//diffかborrow
		if(diff2 < diff_borrow2){
			return diff;
		}else{
			return diff_borrow;
		}
	}else{//carryかborrow
		if(diff_carry2 < diff_borrow2){
			return diff_carry;
		}else{
			return diff_borrow;
		}
	}

}

#endif /* INC_MOTORMATH_HPP_ */
