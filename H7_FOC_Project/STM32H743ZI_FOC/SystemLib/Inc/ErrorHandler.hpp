/*
 * ErrorHandler.hpp
 *
 *  Created on: Jul 31, 2019
 *      Author: watashi
 */

#ifndef ERRORHANDLER_HPP_
#define ERRORHANDLER_HPP_

//エラーハンドラ関数を格納するClass
//基本的にPublic Static宣言で、オブジェクトを生成せずに関数を直接叩くこと。
class ErrorHandler {
public:
	ErrorHandler();
	virtual ~ErrorHandler();
	static void ADC_Error_Handler();
	static void UART_Error_Handler();
};

#endif /* ERRORHANDLER_HPP_ */
