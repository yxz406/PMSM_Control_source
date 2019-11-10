/*
 * UIStatus.hpp
 *
 *  Created on: 2019/11/10
 *      Author: watashi
 */

#ifndef INC_UISTATUS_HPP_
#define INC_UISTATUS_HPP_



enum MotorStartStopStatus {//ON OFFのフラグ管理
	MotorStop = 0,
	MotorStart = 1,
};

class UIStatus {
public:
	MotorStartStopStatus mStartStopTRG;
};

#endif /* INC_UISTATUS_HPP_ */
