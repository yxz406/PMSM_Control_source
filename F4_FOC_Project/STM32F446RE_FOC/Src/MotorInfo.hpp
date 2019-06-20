/*
 * MotorInfo.hpp
 *
 *  Created on: Jun 18, 2019
 *      Author: watashi
 */

#ifndef MOTORINFO_HPP_
#define MOTORINFO_HPP_

class MotorInfo {
private:
	float mVu;
	float mVv;
	float mVw;
	float mValpha;
	float mVbeta;
	float mVd;
	float mVq;
	float mId;
	float mIq;
public:
	MotorInfo();
	virtual ~MotorInfo();

	void setVu(float pVu);
	void setVv(float pVv);
	void setVw(float pVw);
	float getVu(void);
	float getVv(void);
	float getVw(void);

	float getValpha(void);
	float getVbeta(void);
	float getVd(void);
	float getVq(void);

	float getId(void);
	float getIq(void);

	void parkTransform(void);
	void clarkTransform(void);

	void invParkTransform(void);
	void invClarkTransform(void);
};

#endif /* MOTORINFO_HPP_ */
