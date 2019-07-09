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
	bool isONBtnState;
public:
	UiCtrl();
	virtual ~UiCtrl();
	void BtnAct();
	void BtnActOFF();
	void BtnActON();
	bool getState(void);
};

#endif /* UICTRL_HPP_ */
