/*
 * UART.hpp
 *
 *  Created on: Jun 23, 2019
 *      Author: watashi
 */

#ifndef UART_HPP_
#define UART_HPP_

#include "STM32SystemPack.h"
#include <string>

class UART {
private:
	std::string mStr;
	int mstrSize;
	int mTimeout;
public:
	UART();
	UART(int pTimeout);
	UART(std::string pStr, int pTimeout);
	virtual ~UART();
	void setString(std::string pStr);
	void Transmit(void);
	void Transmit(std::string pStr);
};

#endif /* UART_HPP_ */
