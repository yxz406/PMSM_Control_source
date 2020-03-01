/*
 * speedpidsetting.h
 *
 *  Created on: Jul 17, 2019
 *      Author: watashi
 */

#ifndef SPEEDPIDSETTING_H_
#define SPEEDPIDSETTING_H_

#include "motorparamsetting.h"

/*
 * パラメータセッティング
 * ここではマクロを利用して、動作モードの一括変更をする。
 *
 *注意　演算が入るものは（）をつけること。
 */

//速度PID制御器
#define VEL_CONTROL 0
#define PID_GAIN_VEL_P 0.001f
#define PID_GAIN_VEL_I 0.01f
#define PID_GAIN_VEL_D 0.01f
#define PID_CYCLE_TIME_VEL PWM_PERIOD_SEC


#endif /* SPEEDPIDSETTING_H_ */
