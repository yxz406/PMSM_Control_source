/*
 * sqwaveconvsetting.h
 *
 *  Created on: Jul 17, 2019
 *      Author: watashi
 *
 *      ここでは矩形波重畳用のマクロを記述する。
 *
 *
 */

#ifndef SQWAVECONVSETTING_H_
#define SQWAVECONVSETTING_H_

/*
 * パラメータセッティング
 * ここではマクロを利用して、動作モードの一括変更をする。
 *
 *注意　演算が入るものは（）をつけること。
 */

#include "motorparamsetting.h"

//高周波重畳の推定制御器のパラメータ
#define CONV_SQWAVE_FREQ 10000

//HPFパラメータ
#define SQWAVE_DEMOD_HPF_CUTOFF_FREQ 5000
#define SQWAVE_DEMOD_HPF_SAMPLING_FREQ 20000
#define SQWAVE_DEMOD_HPF_CUTOFF_TIME (1.0f /(2* M_PI * (float)HF_HPF_BPF_CUTOFF_FREQ) )
#define SQWAVE_DEMOD_HPF_SAMPLING_TIME (1.0f/(float)HF_HPF_BPF_SAMPLING_FREQ )
#define SQWAVE_DEMOD_HPF_DENOMINATOR (2*HF_HPF_BPF_CUTOFF_TIME + HF_HPF_BPF_SAMPLING_TIME)

#define SQWAVE_DEMOD_HPF_A1 (HF_HPF_BPF_SAMPLING_TIME-2*HF_HPF_BPF_CUTOFF_TIME)/HF_HPF_BPF_DENOMINATOR
#define SQWAVE_DEMOD_HPF_B0 2*HF_HPF_BPF_CUTOFF_TIME/HF_HPF_BPF_DENOMINATOR
#define SQWAVE_DEMOD_HPF_B1 HF_HPF_BPF_B0



#endif
