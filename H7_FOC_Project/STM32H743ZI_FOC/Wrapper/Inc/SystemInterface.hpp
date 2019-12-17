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

	//ADC(MotorDrive) Interface
	virtual bool ADCInit();
	virtual bool ADCDeInit();
	virtual float ADCReadChU();
	virtual float ADCReadChV();
	virtual float ADCReadChW();

	//PWM(MotorDrive) Interface
	virtual bool PWMInit();
	virtual bool PWMDeInit();
	virtual bool PWMStart();
	virtual bool PWMOutputChU(float pDuty);
	virtual bool PWMOutputChV(float pDuty);
	virtual bool PWMOutputChW(float pDuty);

	//Output-Pin Interface
	virtual bool GPIO_Init();
	virtual bool GPIO_DeInit();
	virtual bool GPIO_PWMSetting(bool pOutput);
	virtual bool GPIO_OverCurrentSetting(bool pOutput);
	virtual bool GPIO_GateEnable(bool pOutput);

};

#endif /* INC_SYSTEMINTERFACE_HPP_ */
