/*
 * MotorCtrl.hpp
 *
 *  Created on: Aug 5, 2019
 *      Author: watashi
 */

#ifndef MOTORCTRL_HPP_
#define MOTORCTRL_HPP_

#include "paramsetting.h" //パラメータのマクロ
#include "MotorLibDefPack.hpp"

// ../SystemLib/Inc/
#include "STM32SystemPack.h"

#include "ADCCtrl.hpp"
#include "TIMCtrl.hpp"

//#include "GPIOInit.hpp"
//#include "USARTInit.hpp"


#include "ArgCtrl.hpp"
#include "MotorMath.hpp"
#include "PID.hpp"
#include "Observer.hpp"
#include <array>

#include "PWM.hpp"
//#include "UART.hpp"

#include "DebugCtrl.hpp"

#include "SEGGER_RTT.h"

class MotorCtrl {
public:

	class MotorInfo {
	public:
		std::array<float, 3> mIuvw;
		std::array<float, 2> mIab;
		std::array<float, 2> mIdq;
		std::array<float, 2> mIgd; //ganmadelta

		std::array<float, 3> mVuvw;
		std::array<float, 2> mVab;
		std::array<float, 2> mVdq;
		std::array<float, 2> mVgd; //ganmadelta
		fp_rad mArg;
		fp_rad mArgErr;
	};

	int mDebugC=0; //SEGGERおためしでつくった

	enum MotorStartStopStatus {
			MotorStop = 0,
			MotorStart = 1,
		};

	class UIStatus {
	public:
		MotorStartStopStatus mStartStopTRG;
	};

private:
	MotorInfo mMotorInfo;
	Observer mObserver;

	PID mIdPID, mIqPID;
	PID mIganmaPID, mIdeltaPID;

	ArgCtrl mArgCtrl;

	UIStatus mUIStatus;

	DebugCtrl mDebug;

public:
	MotorCtrl();
	virtual ~MotorCtrl();
	void SetMotorInfo(MotorInfo pMotorInfo);

	void InitSystem(void);
	void InitMotorInfo(void);
	void InitObserver(void);

	void HighFreqTask(void);
	void MotorOutputTask(void);

	//MotorControl
	void ForceCommutation(void);

	void setIuvw(float pIu, float pIv, float pIw);
	void clarkTransform(void);
	void parkTransform(void);
	void parkGanmaDelta(void);

	std::array<float, 2> getIdq(void);
	std::array<float, 2> getIgd(void);

	void PIDdq_control(std::array<float, 2> pErrIdq);//ここでPID使う？？ライブラリインクルード必要だよね？
	void PIDgd_control(std::array<float, 2> pErrIgd);//どちらかが死にclassになるけど毎回呼ぶ作業でif文使いたくない。

	void setVdq(std::array<float, 2> pVdq);//強制転流用
	void setVgd(std::array<float, 2> pVgd);

	void invParkGanmaDelta(void);
	void invParkTransform(void);
	void invClarkTransform(void);



	//Debug
	void DebugTask(float pIu, float pIv, float pIw, float pArg);

	//UI
	void BtnAct(void);
	void BtnActOFF(void);
	void BtnActON(void);

	//for debug
	void DbgUart(std::string pStr);

};

#endif /* MOTORCTRL_HPP_ */
