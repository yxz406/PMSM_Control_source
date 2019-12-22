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
	virtual ~SystemInterface() = 0;

	//ADC(MotorDrive) Interface
	virtual bool ADCInit() = 0;
	virtual bool ADCDeInit() = 0;
	virtual float ADCReadChU() = 0;
	virtual float ADCReadChV() = 0;
	virtual float ADCReadChW() = 0;

	//PWM(MotorDrive) Interface
	virtual bool PWMInit() = 0;
	virtual bool PWMDeInit() = 0;
	virtual bool PWMStart() = 0;
	virtual bool PWMOutputChU(float pDuty) = 0;
	virtual bool PWMOutputChV(float pDuty) = 0;
	virtual bool PWMOutputChW(float pDuty) = 0;

	//Output-Pin Interface
	virtual bool GPIOInit() = 0;
	virtual bool GPIODeInit() = 0;
	virtual bool GPIOPWMSetting(bool pOutput) = 0;
	virtual bool GPIOOverCurrentSetting(bool pOutput) = 0;
	virtual bool GPIOGateEnable(bool pOutput) = 0;

	//SPI Interface
	virtual bool SPIInit() = 0;
	virtual bool SPIDeInit() = 0;
	virtual bool SPITransmitReceive() = 0;

};

#endif /* INC_SYSTEMINTERFACE_HPP_ */
