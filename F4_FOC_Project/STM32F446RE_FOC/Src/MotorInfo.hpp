/*
 * MotorInfo.hpp
 *
 *  Created on: Jun 18, 2019
 *      Author: watashi
 */

#ifndef MOTORINFO_HPP_
#define MOTORINFO_HPP_

#include "MathLib.hpp"

class MotorInfo {
private:
	float mIu;
	float mIv;
	float mIw;
	float mIalpha;
	float mIbeta;
	float mId;
	float mIq;

	float mVu;
	float mVv;
	float mVw;
	float mValpha;
	float mVbeta;
	float mVd;
	float mVq;

	MathLib mLib;
	int marg;

public:
	MotorInfo();
	virtual ~MotorInfo();

	void setMathLib(MathLib pLib);

	void setIu(float pIu);
	void setIv(float pIv);
	void setIw(float pIw);

	void setVu(float pVu);
	void setVv(float pVv);
	void setVw(float pVw);

	void setArg(int parg);

	void parkTransform(void);
	void clarkTransform(void);

	void PID(void);

	void setVd(float pVd);//強制転流用
	void setVq(float pVq);

	void invClarkTransform(void);
	void invParkTransform(void);

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
