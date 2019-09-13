/*
 * ErrorHandler.cpp
 *
 *  Created on: Jul 31, 2019
 *      Author: watashi
 */

#include "ErrorHandler.hpp"

ErrorHandler::ErrorHandler() {
	// TODO Auto-generated constructor stub

}

ErrorHandler::~ErrorHandler() {
	// TODO Auto-generated destructor stub
}

void ErrorHandler::ADC_Error_Handler(){
	//ADC Error Handler
	  /* USER CODE BEGIN Error_Handler_Debug */
	while(1){}
	  /* User can add his own implementation to report the HAL error return state */

	  /* USER CODE END Error_Handler_Debug */
}

void ErrorHandler::UART_Error_Handler(){
	//UART Error Handler
	  /* USER CODE BEGIN Error_Handler_Debug */
	while(1){}
	  /* User can add his own implementation to report the HAL error return state */

	  /* USER CODE END Error_Handler_Debug */
}
