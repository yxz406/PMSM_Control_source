/*
 * MotorInfo.hpp
 *
 *  Created on: Jun 18, 2019
 *      Author: watashi
 */

#ifndef MOTORINFO_HPP_
#define MOTORINFO_HPP_


#include "MathLib.hpp"
#include "PID.hpp"

class MotorInfo {
private:
	float mIu;
	float mIv;
	float mIw;
	float mIalpha;
	float mIbeta;
	float mId;
	float mIq;
	float mIganma;
	float mIdelta;

	float mVu;
	float mVv;
	float mVw;
	float mValpha;
	float mVbeta;
	float mVd;
	float mVq;
	float mVganma;
	float mVdelta;

	MathLib mLib;
	int marg;
	int marg_delta;

	PID mIdPID, mIqPID;
	PID mIganmaPID, mIdeltaPID;

public:
	MotorInfo();
	virtual ~MotorInfo();

	void setMathLib(MathLib pLib);
	MathLib getMathLib(void);

	void setIdqPIDLib(PID pdPID, PID pqPID);
	void setIganmadeltaPIDLib(PID pganmaPID, PID pdeltaPID);

	void setIu(float pIu);
	void setIv(float pIv);
	void setIw(float pIw);
	void setIuvw(float pIu, float pIv, float pIw);

	void setVu(float pVu);
	void setVv(float pVv);
	void setVw(float pVw);

	void setArg(int parg);
	void setArgDelta(int parg);

	void parkTransform(void);
	void clarkTransform(void);
	void clarkGanmaDelta(void);

	void PIDdq_control(float pdVal, float pqVal, float pTime);//ここでPID使う？？ライブラリインクルード必要だよね？
	void PIDganmadelta_control(float pganmaVal, float pdeltaVal, float pTime);//どちらかが死にclassになるけど毎回呼ぶ作業でif文使いたくない。

	void setVd(float pVd);//強制転流用
	void setVq(float pVq);
	void setVganma(float pVganma);
	void setVdelta(float pVdelta);

	void invClarkGanmaDelta(void);
	void invClarkTransform(void);
	void invParkTransform(void);

	float getIganma(void);
	float getIdelta(void);
	float getId(void);
	float getIq(void);
	float getVd(void);
	float getVq(void);
	float getValpha(void);
	float getVbeta(void);

	float getVu(void);
	float getVv(void);
	float getVw(void);
};

#endif /* MOTORINFO_HPP_ */
