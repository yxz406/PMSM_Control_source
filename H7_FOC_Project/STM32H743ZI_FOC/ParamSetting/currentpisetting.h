/*
 * currentpisetting.h
 *
 *  Created on: Jul 17, 2019
 *      Author: watashi
 */

#ifndef CURRENTPISETTING_H_
#define CURRENTPISETTING_H_

#include "motorparamsetting.h"

/*
 * パラメータセッティング
 * ここではマクロを利用して、動作モードの一括変更をする。
 *
 *注意　演算が入るものは（）をつけること。
 */

//制御用周期
#define PWM_PERIOD_SEC 1.0f/(float)PWM_FREQ_HZ
#define CONTROL_FREQ_HZ PWM_FREQ_HZ


//PID制御器設定

//制御周期[s]
#define PID_CYCLE_TIME PWM_PERIOD_SEC
#define PID_TIME_CONSTANT_G 1.0f/((float)175*2*3.1415926f)
#define PID_TIME_CONSTANT_D 1.0f/((float)175*2*3.1415926f)

//PI電流制御をかけない
#define PI_NOCONTROL_DEBUG 0
////PIdq制御器パラメータ設定
//#define PID_GAIN_ID_P 0.1
//#define PID_GAIN_ID_I 0.1
//#define PID_GAIN_ID_D 0.1
//#define PID_ID_MAX_VOLTAGE 10
//
//#define PID_GAIN_IQ_P 0.1
//#define PID_GAIN_IQ_I 0.1
//#define PID_GAIN_IQ_D 0.1
//#define PID_IQ_MAX_VOLTAGE 10

//PIgd制御器パラメータ設定
#define PID_GAIN_IGANMA_P (M_PARAM_LD)/(PID_TIME_CONSTANT_G)
#define PID_GAIN_IGANMA_I (M_PARAM_LD)/(M_PARAM_R)
#define PID_GAIN_IGANMA_D 0
#define PID_IGANMA_MAX_VOLTAGE 9.0f
#define PID_IGANMA_MIN_VOLTAGE -9.0f

#define PID_GAIN_IDELTA_P (M_PARAM_LQ)/(PID_TIME_CONSTANT_D)
#define PID_GAIN_IDELTA_I (M_PARAM_LQ)/(M_PARAM_R)
#define PID_GAIN_IDELTA_D 0
#define PID_IDELTA_MAX_VOLTAGE 9.0f
#define PID_IDELTA_MIN_VOLTAGE -9.0f


#endif /* CURRENTPISETTING_H_ */
