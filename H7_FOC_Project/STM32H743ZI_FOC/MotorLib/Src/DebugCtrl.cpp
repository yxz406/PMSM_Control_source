/*
 * DebugCtrl.cpp
 *
 *  Created on: Aug 8, 2019
 *      Author: watashi
 */

#include "DebugCtrl.hpp"

DebugCtrl::DebugCtrl() {
	// TODO Auto-generated constructor stub
	mLogcount = 0;
}

DebugCtrl::~DebugCtrl() {
	// TODO Auto-generated destructor stub
}


void DebugCtrl::RTTOutput(const MotorInfo &pMotorInfo, const UIStatus &pUIStatus) {

	int milIu = (int)( pMotorInfo.mIuvw.at(0) * 1000 );
	int milIv = (int)( pMotorInfo.mIuvw.at(1) * 1000 );
	int milIw = (int)( pMotorInfo.mIuvw.at(2) * 1000 );
	int DegArg = (int)(pMotorInfo.mgdArg/M_PI * 180 );//指令値の角度
	int DegAxiErr =(int)( pMotorInfo.mArgErr / M_PI *180 );
	int milEstOmega =(int)( pMotorInfo.mEstOmega );
	int EstTheta =(int)( pMotorInfo.mEstTheta/M_PI * 180 );

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

//	int milEstEMFg = (int)(mObserver.GetEstEMFgd().at(0) * 1000);
//	int milEstEMFd = (int)(mObserver.GetEstEMFgd().at(1) * 1000);

	//encoder
	//int encoder = (int)(EncoderABZCtrl::GetAngle()*(360.0f/(ENCODER_PERIOD+1)));

	int milVh = (int)(pMotorInfo.mVh * 1000 );


	//高周波重畳デバッグ用
	int milSinDemod = pMotorInfo.mSinForDemodulation * 1000;
	int milCosDemod = pMotorInfo.mCosForDemodulation * 1000;

	int milConvIdc = pMotorInfo.mConvIdqc.at(0) * 1000;
	int milConvIqc = pMotorInfo.mConvIdqc.at(1) * 1000;

	int milIdch = pMotorInfo.mIdqch.at(0) * 1000;
	int milIqch = pMotorInfo.mIdqch.at(1) * 1000;

	int milHFOmega = pMotorInfo.mEstOmega_HF * 1000;
	int milObsOmega = pMotorInfo.mEstOmega_Observer * 1000;

	char outputStr[100]={0};//100文字までとりあえず静的確保
	//general
	//sprintf(outputStr,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n" ,mlogcount, milIgTarget, milVg, milVd, milIg, milId, DegArg, DegAxiErr, milEstOmega, EstTheta);//みやゆうさんご希望のデバッグ

	//velocity
	//sprintf(outputStr,"%d,%d,%d,%d,%d,%d,%d\n" ,mLogcount, milVg, milVd, milIg, milId, milEstOmega, EstTheta);

	//encoder
	//sprintf(outputStr,"%d\n",encoder);

	//measure HFcon
	//sprintf(outputStr,"%d,%d,%d,%d,%d,%d\n" ,mLogcount, milVg, milVd, milIg, milId, DegArg);

	//measure hetelo
	//sprintf(outputStr,"%d,%d,%d,%d,%d,%d\n" ,mLogcount, milCosDemod, milSinDemod, milIdch, milIqch, DegArg);

	//obs and HF
	sprintf(outputStr,"%d,%d,%d,%d\n" ,mLogcount, milHFOmega, milObsOmega, DegArg);


	//conv済み
	//sprintf(outputStr,"%d,%d,%d,%d,%d,%d\n" ,mLogcount, milCosDemod, milSinDemod, milConvIdc, milConvIqc, DegArg);

	//Default
	//sprintf(outputStr,"%d,%d,%d,%d,%d,%d\n" ,mLogcount, milVg, milVd, milIg, milId, DegArg);


	//SPIVh
	//sprintf(outputStr,"%d\n",milVh);

//	if( !pUIStatus.mStartStopTRG ) {//加速してるときだけ入る Printf
//		return;
//	}
//	SEGGER_RTT_WriteNoLock(BufferIndex, pBuffer, NumBytes);
//	SEGGER_RTT_ASM_WriteSkipNoLock(BufferIndex, pBuffer, NumBytes);
	SEGGER_RTT_WriteString(0,outputStr);
	//printf("%s" ,outputStr);

	mLogcount++;
	if(	mLogcount > 65535){
		mLogcount=0;
	}

}
