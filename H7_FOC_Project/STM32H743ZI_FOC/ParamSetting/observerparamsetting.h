/*
 * observerparamsetting.h
 *
 *  Created on: Jul 17, 2019
 *      Author: watashi
 */

#ifndef OBSERVERPARAMSETTING_H_
#define OBSERVERPARAMSETTING_H_

/*
 * モータパラメータセッティング
 * ここではマクロを利用して、動作モードの一括変更をする。
 *
 *注意　演算が入るものは（）をつけること。
 */

//オブザーバ位相推定器セッティング
#define OBSERVER_CYCLE_TIME PWM_PERIOD_SEC
#define OBSERVER_GAIN_ALPHA 200
#define OBSERVER_GAIN_K1 2
#define OBSERVER_GAIN_K2 (3 * OBSERVER_GAIN_ALPHA)
#define OBSERVER_GAIN_K3 (OBSERVER_GAIN_ALPHA * OBSERVER_GAIN_ALPHA)

#endif /* OBSERVERPARAMSETTING_H_ */
