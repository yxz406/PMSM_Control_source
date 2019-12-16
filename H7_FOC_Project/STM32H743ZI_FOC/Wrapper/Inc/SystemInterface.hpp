/*
 * SystemInterface.hpp
 *
 *  Created on: Dec 16, 2019
 *      Author: watashi
 */

#ifndef INC_SYSTEMINTERFACE_HPP_
#define INC_SYSTEMINTERFACE_HPP_

class SystemInterface {
public:
	SystemInterface();
	virtual ~SystemInterface();

	//ADC Interface
	virtual bool ADCInit();
	virtual bool ADCDeInit();
	virtual float ADCReadChU();
	virtual float ADCReadChV();
	virtual float ADCReadChW();

	//PWM Interface
	virtual bool PWMInit();
	virtual bool PWMDeInit();


};

#endif /* INC_SYSTEMINTERFACE_HPP_ */
