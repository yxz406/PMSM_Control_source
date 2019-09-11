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
//#define DEBUG_COUNT 720 //デバッグ数のカウント
//#define DEBUG_COUNT 7 //デバッグ数のカウント
#define DEBUG_ADC_TRIG_PWM_OUT 1//ONでTIM1 ch4が出力 モータは動作しない


//ボードの I -> V 倍率
#define BOARD_OPAMP_R1 2200
#define BOARD_OPAMP_R2 6800
#define BOARD_CURRENT_R 0.1

//モータのパラメータ設定
#define M_PARAM_LD 0.5
#define M_PARAM_LQ 0.5
#define M_PARAM_PHY 1

//PWMの設定
//#define PWM_COUNT 4000 //PWMの一周期カウント数
//本当は周期で調整したい。#define PWM_HZ 20000

#define PWM_FREQ_HZ 30000
#define TIM_CLOCK_DIVIDER 1
#define TIM_CLK_MHz 180/TIM_CLOCK_DIVIDER
#define PWM_PERIOD_CYCLES (uint16_t)(TIM_CLK_MHz*(unsigned long long)1000000u/(uint16_t)(PWM_FREQ_HZ))
#define PWM_PERIOD_COUNT PWM_PERIOD_CYCLES/2


//PIDパラメータ設定
#define PID_GAIN_ID_P 0.1
#define PID_GAIN_ID_I 0.1
#define PID_GAIN_ID_D 0.1

#define PID_GAIN_IQ_P 0.1
#define PID_GAIN_IQ_I 0.1
#define PID_GAIN_IQ_D 0.1




#endif /* PARAMSETTING_H_ */
