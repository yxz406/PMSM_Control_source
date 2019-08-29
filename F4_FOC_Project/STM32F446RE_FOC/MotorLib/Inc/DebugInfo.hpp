/*
 * DebugInfo.hpp
 *
 *  Created on: Jul 1, 2019
 *      Author: watashi
 */

#ifndef DEBUGINFO_HPP_
#define DEBUGINFO_HPP_

#include <vector>




class DebugInfo {
public:
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
private:
	std::vector<SendMotorData> mSendDataVect;
public:
	DebugInfo();
	virtual ~DebugInfo();
	void SetMotorData(SendMotorData* pMotorData);
	std::vector<SendMotorData> GetVect(void);
	int GetVectSize(void);
};



#endif /* DEBUGINFO_HPP_ */
