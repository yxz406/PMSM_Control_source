/*
 * UiCtrl.hpp
 *
 *  Created on: Jun 28, 2019
 *      Author: watashi
 */

#ifndef UICTRL_HPP_
#define UICTRL_HPP_

class UiCtrl {
private:

public:
	static bool isONBtnState;
	UiCtrl();
	virtual ~UiCtrl();
	static void BtnToggle();
	static void BtnActOFF();
	static void BtnActON();
	static bool getState(void);
};


#endif /* UICTRL_HPP_ */
