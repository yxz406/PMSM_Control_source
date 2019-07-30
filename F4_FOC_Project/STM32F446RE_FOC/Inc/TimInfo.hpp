/*
 * TimInfo.hpp
 *
 *  Created on: Jul 29, 2019
 *      Author: watashi
 */

#ifndef TIMINFO_HPP_
#define TIMINFO_HPP_


#include "stm32f4xx_ll_tim.h"//need

class TimInfo {
private:
	TIM_TypeDef *mTIMx;
	int mReload;
	int mStartTime;
	int mStopTime;

public:
	TimInfo();
	virtual ~TimInfo();

	void Init(TIM_TypeDef *pTIMx);

	int CountToHz(int pCount);
	int HzToCount(int pHz);

	void StartTimMesure(void);
	void StopTimMesure(void);

	int CalcTime(void);
};

#endif /* TIMINFO_HPP_ */
