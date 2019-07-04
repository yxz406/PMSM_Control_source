/*
 * DebugInfo.hpp
 *
 *  Created on: Jul 1, 2019
 *      Author: watashi
 */

#ifndef DEBUGINFO_HPP_
#define DEBUGINFO_HPP_

#include <vector>

class SendMotorData{
public:
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

	float mEArg;

	SendMotorData();
	SendMotorData(float pIu, float pIv, float pIw, float pEArg);
	SendMotorData(float pIu, float pIv, float pIw,
					float pIalpha, float pIbeta,
					float pId, float pIq,
					float pVu, float pVv, float pVw,
					float pValpha, float pVbeta,
					float pVd, float pVq,
					float pEArg);
	virtual ~SendMotorData();
};


class DebugInfo {
private:
	std::vector<SendMotorData> mSendDataVect;
public:
	DebugInfo();
	virtual ~DebugInfo();
	void SetData(float pIu, float pIv, float pIw, float pEArg);
	void SetData(float pIu, float pIv, float pIw,
				float pIalpha, float pIbeta,
				float pId, float pIq,
				float pVu, float pVv, float pVw,
				float pValpha, float pVbeta,
				float pVd, float pVq,
				float pEArg);
	void SetVector(void);
	std::vector<SendMotorData> GetVect(void);
};



#endif /* DEBUGINFO_HPP_ */
