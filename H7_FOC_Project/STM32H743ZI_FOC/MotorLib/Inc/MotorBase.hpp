/*
 * MotorBase.hpp
 *
 *  Created on: 2019/12/15
 *      Author: watashi
 */

#ifndef INC_MOTORBASE_HPP_
#define INC_MOTORBASE_HPP_

#include "MotorInterface.hpp"

class MotorBase : MotorInterface {
private:

public:
	MotorBase();
	virtual ~MotorBase();

	void InitSystem(void);
	void DeInitSystem(void);
	void InitMotorControl(void);
	void InitObserver(void);

	void ReadCurrentTask();
	void setIuvw(float pIu, float pIv, float pIw);
	void ReadVoltageTask();

	void ReadAngleTask(void);
	fp_rad GetAngleForOpenLoop();
	fp_rad GetAngleForFOC();

	void clarkTransform(void);
	void parkTransform(void);
	void parkGanmaDelta(void);
	void parkabtogd(void);

	void ObserverTask();

	void CurrentControlTask();
	std::array<float, 2> GetCurrentTarget();
	//void CurrentFeedForwardTask();
	void CurrentPITask();
	std::array<float, 2> PIDgd_control(std::array<float, 2> pErrIgd);//どちらかが死にclassになるけど毎回呼ぶ作業でif文使いたくない。
	void setVg(float pVg);
	void setVd(float pVd);
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



};

#endif /* INC_MOTORBASE_HPP_ */
