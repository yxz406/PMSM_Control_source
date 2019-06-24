/*
 * UART.hpp
 *
 *  Created on: Jun 23, 2019
 *      Author: watashi
 */

#ifndef UART_HPP_
#define UART_HPP_

#include <string>

class UART {
private:
	std::string mStr;
	int mstrSize;
	int mTimeout;
public:
	UART();
	virtual ~UART();
	void setString(std::string pStr);
	void Transmit(void);
};

#endif /* UART_HPP_ */
