/*
 * pwmparamsetting.h
 *
 *  Created on: Jul 17, 2019
 *      Author: watashi
 */

#ifndef PWMPARAMSETTING_H_
#define PWMPARAMSETTING_H_

/*
 * モータパラメータセッティング
 * ここではマクロを利用して、動作モードの一括変更をする。
 *
 *注意　演算が入るものは（）をつけること。
 */

/*
 * ハードウェアセッティング
 */
//PWMの設定
#define PWM_FREQ_HZ 20000
#define TIM_CLOCK_DIVIDER 1
#define TIM_CLK_MHz (480/TIM_CLOCK_DIVIDER)
#define PWM_PERIOD_CYCLES (uint16_t)(TIM_CLK_MHz*(unsigned long long)1000000u/(uint16_t)(PWM_FREQ_HZ))
//#define PWM_PERIOD_COUNT PWM_PERIOD_CYCLES/2　//片側のPWMだとこれ
#define PWM_PERIOD_COUNT (PWM_PERIOD_CYCLES/4) //両端のPWMだとこれ
#define PWM_DEADTIME_COUNT 20


#endif /* PWMPARAMSETTING_H_ */
