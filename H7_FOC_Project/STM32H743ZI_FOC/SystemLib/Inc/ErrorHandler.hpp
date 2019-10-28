/*
 * ErrorHandler.hpp
 *
 *  Created on: Jul 31, 2019
 *      Author: watashi
 */

#ifndef ERRORHANDLER_HPP_
#define ERRORHANDLER_HPP_

//エラーハンドラ関数を格納するClass
//singletonだから複数インスタンスは生成できないよ。
//基本的にGetInstanceして関数をたたくこと。
class ErrorHandler {
private:
	ErrorHandler() = default;
	~ErrorHandler() = default;
public:
    ErrorHandler(const ErrorHandler&) = delete;
    ErrorHandler& operator=(const ErrorHandler&) = delete;
    ErrorHandler(ErrorHandler&&) = delete;
    ErrorHandler& operator=(ErrorHandler&&) = delete;

    static ErrorHandler& get_instance()
    {
        static ErrorHandler instance;
        return instance;
    }
//	ErrorHandler();
//	virtual ~ErrorHandler();
	void ADC_Error_Handler();
	void UART_Error_Handler();
};

#endif /* ERRORHANDLER_HPP_ */
