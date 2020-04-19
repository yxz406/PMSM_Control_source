/*
 * MotorCtrl.hpp
 *
 *  Created on: Aug 5, 2019
 *      Author: watashi
 */

#ifndef MOTORCTRL_HPP_
#define MOTORCTRL_HPP_

#include "MotorInterface.hpp"

class MotorCtrl {
public:

	enum ControlMode { //強制転流、FOCなどの動作モード管理
		OpenLoop = 1,
		OpenLoopToFOC,
		FOC,
		FOC_Convolution_Start,
		FOC_Convolution,
		FOC_Convolution_HighSpeed,
		FOC_SqWaveConvolution,
	};

	enum DEBUGorSPI { //重い処理だからそれぞれ交互に出すためのEnum
		SPI = 1,
		Debug,
	};

private:
	MotorInfo mMotorInfo;
	Observer mObserver;
	SineWaveConvCalculator mSineWaveConvCalculator;
	SqWaveConvCalculator mSqWaveConvCalculator;



	PID mIdPID, mIqPID;
	PID mIganmaPID, mIdeltaPID;

	PID mVelocityPID;

	ArgCtrl mArgCtrl;

	ControlMode mControlMode;
	DEBUGorSPI mDEBUGorSPI =SPI;

	UIStatus mUIStatus;
	DebugCtrl mDebugCtrl;

	WaveGenerator mWaveGen;//高周波重畳用
	SqWaveGenerator mSqWaveGen;//矩形波高周波重畳用

public:
	MotorCtrl();
	virtual ~MotorCtrl();

	void InitSystem(void);
	void DeInitSystem(void);
	void InitMotorControl(void);
	void InitObserver(void);

	void HighFreqTask(void);

	//void MotorMeasure(void);
	void MotorDrive(void);
	//MotorDrive内呼び出し関数
	void SPITask(void);
	void SetCurrentTarget();
	void SetVhTask();
	void SetVhTaskForSqWave();
	void WaveGenTask(void);
	void SqWaveGenTask(void);
	void ReadCurrentTask();
	void setIuvw(float pIu, float pIv, float pIw);
	void ReadVoltageTask();

	void ReadAngleTask(void);
	fp_rad GetAngleForOpenLoop();
	fp_rad GetAngleForFOC();
	fp_rad GetAngleForSineWaveConv(void);
	fp_rad GetAngleForSqWaveConv(void);

	void clarkTransform(void);
	void parkTransform(void);
	void parkGanmaDelta(void);
	void parkabtogd(void);

	void ObserverTask();

	void CurrentControlTask();
	std::array<float, 2> GetCurrentTarget();
	void CurrentFeedForwardTask();
	void CurrentPITask();
	void CurrentPITaskForConvolution();
	std::array<float, 2> PIDgd_control(const std::array<float, 2> &pErrIgd);//どちらかが死にclassになるけど毎回呼ぶ作業でif文使いたくない。
	void setVgd(std::array<float, 2> pVgd);

	std::array<float, 2> getIdq(void);
	std::array<float, 2> getIgd(void);

	void invParkgdtoab(void);
	void invParkGanmaDelta(void);
	void invParkTransform(void);
	void invClarkTransform(void);
	void SVM(void);

	void VoltageOutputTask(void);

	void VelocityPIDTask();
	void GPIODebugTask();

	//Handler
	void ControlModeHandler();

	//UI
	void BtnAct(void);
	void BtnActOFF(void);
	void BtnActON(void);

private:
	int mlogcount = 0;
	int mTransitionCountForOpenToFOC = 0;
	int mTransitionCountForOpenToFOC2 = 0;

	int mFOCcount=0;
};

#endif /* MOTORCTRL_HPP_ */
