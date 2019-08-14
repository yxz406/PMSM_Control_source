/*
 * paramsetting.h
 *
 *  Created on: Jul 17, 2019
 *      Author: watashi
 */

#ifndef PARAMSETTING_H_
#define PARAMSETTING_H_

/*
 * パラメータセッティング
 * ここではマクロを利用して、動作モードの一括変更をする。
 *
 */


//デバッグ設定
#define DEBUG_MODE 1 //デバッグモード
#define DEBUG_COUNT 360 //デバッグ数のカウント
//#define DEBUG_COUNT 7 //デバッグ数のカウント

//モータのパラメータ設定
#define M_PARAM_LD 0.5
#define M_PARAM_LQ 0.5
#define M_PARAM_PHY 1

//PWMの設定
#define PWM_COUNT 4000 //PWMの一周期カウント数
//本当は周期で調整したい。#define PWM_HZ 20000

//PIDパラメータ設定
#define PID_GAIN_ID_P 0.1
#define PID_GAIN_ID_I 0.1
#define PID_GAIN_ID_D 0.1

#define PID_GAIN_IQ_P 0.1
#define PID_GAIN_IQ_I 0.1
#define PID_GAIN_IQ_D 0.1


#endif /* PARAMSETTING_H_ */
