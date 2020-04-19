/*
 * motorparamsetting.h
 *
 *  Created on: Jul 17, 2019
 *      Author: watashi
 */

#ifndef MOTORPARAMSETTING_H_
#define MOTORPARAMSETTING_H_

/*
 * モータパラメータセッティング
 * ここではマクロを利用して、動作モードの一括変更をする。
 *
 *注意　演算が入るものは（）をつけること。
 */

//#include "PWMSettingParam.h"


//モータのパラメータ設定
//R  = 0.0782;
//Ld = 0.035e-3;
//Lq = 0.07e-3;
//鎖交磁束 = 6.61798e-3
//極対数 = 7
#define M_PARAM_LD 0.000035f
#define M_PARAM_LQ 0.00007f
#define M_PARAM_PHY 0.0008f
#define M_PARAM_R 0.006617f


#endif /* MOTORPARAMSETTING_H_ */
