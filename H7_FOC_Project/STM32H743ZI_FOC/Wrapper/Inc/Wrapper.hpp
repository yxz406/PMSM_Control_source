/*
 * Wrapper.hpp
 *
 *  Created on: Sep 8, 2019
 *      Author: Nakamura(Yutaka)
 */

#ifndef WRAPPER_HPP_
#define WRAPPER_HPP_

#ifdef __cplusplus
extern "C" {
#endif

void cppWrapper(void);
void HighFreqTask(void);

void EXTI15_10_IRQHandler(void);
void ADC3_IRQHandler(void);
#ifdef __cplusplus
};
#endif


#endif /* APPLICATION_USER_WRAPPER_HPP_ */
