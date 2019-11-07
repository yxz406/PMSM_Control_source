/*
 * DebugOutput.cpp
 *
 *  Created on: Nov 7, 2019
 *      Author: watashi
 */

#include <DebugOutput.hpp>

DebugOutput::DebugOutput() {
	// TODO Auto-generated constructor stub

}

DebugOutput::~DebugOutput() {
	// TODO Auto-generated destructor stub
}

void DebugOutput::Output(const MotorCtrl::MotorInfo &pMotorInfo){
	//mDebugC++;
//	if(mDebugC >= 2) {
//		mDebugC = 0;
//		return;
//	}


	int milIu = (int)( pMotorInfo.mIuvw.at(0) * 1000 );
	int milIv = (int)( pMotorInfo.mIuvw.at(1) * 1000 );
	int milIw = (int)( pMotorInfo.mIuvw.at(2) * 1000 );
	int DegArg = (int)(pMotorInfo.mgdArg/M_PI * 180 );//指令値の角度
	//int DegAxiErr =(int)( pObserver.GetEstAxiErr() / M_PI *180 );
	//int milEstOmega =(int)( pObserver.GetEstOmegaE());
	//int EstTheta =(int)(pObserver.GetEstTheta()/M_PI * 180 );

	int milIa = (int)( pMotorInfo.mIab.at(0) * 1000 );
	int milIb = (int)( pMotorInfo.mIab.at(1) * 1000 );

	int milIg = (int)( pMotorInfo.mIgd.at(0) * 1000 );
	int milId = (int)( pMotorInfo.mIgd.at(1) * 1000 );

	int milVg = (int)( pMotorInfo.mVgd.at(0) * 1000 );
	int milVd = (int)( pMotorInfo.mVgd.at(1) * 1000 );

	//SVMdebug
	int milVu = (int)(pMotorInfo.mDutyuvw.at(0) * 1000 );
	int milVv = (int)(pMotorInfo.mDutyuvw.at(1) * 1000 );
		int milVw = (int)(pMotorInfo.mDutyuvw.at(2) * 1000 );

		int milIgTarget = (int)(pMotorInfo.mIgdTarget.at(0)*1000);

		//int milEstEMFg = (int)(mObserver.GetEstEMFgd().at(0) * 1000);
		//int milEstEMFd = (int)(mObserver.GetEstEMFgd().at(1) * 1000);

		//encoder
		//int encoder = (int)(EncoderABZCtrl::GetAngle()*(360.0f/(ENCODER_PERIOD+1)));

		char outputStr[100]={0};//100文字までとりあえず静的確保
		//general
		//sprintf(outputStr,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n" ,mlogcount, milIgTarget, milVg, milVd, milIg, milId, DegArg, DegAxiErr, milEstOmega, EstTheta);//みやゆうさんご希望のデバッグ

		//velocity
		//sprintf(outputStr,"%d,%d,%d,%d,%d,%d,%d\n" ,mlogcount, milVg, milVd, milIg, milId, milEstOmega, EstTheta);

		//encoder
		//sprintf(outputStr,"%d\n",encoder);

//		if( !mUIStatus.mStartStopTRG ) {//加速してるときだけ入る Printf
//			return;
//		}
//
//		SEGGER_RTT_WriteString(0,outputStr);
//		//printf("%s" ,outputStr);
//
//		mlogcount++;
//		if(	mlogcount > 65535){
//			mlogcount=0;
//		}

}
