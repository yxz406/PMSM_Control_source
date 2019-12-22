/*
 * UICtrl.hpp
 *
 *  Created on: Dec 21, 2019
 *      Author: watashi
 */

#ifndef INC_UICTRL_HPP_
#define INC_UICTRL_HPP_

#include "SPICtrl.hpp"
#include "ADCCtrl.hpp"


class UICtrl {
private:
	ADCCtrl mADCCtrl;
	SPICtrl mSPICtrl;
public:
	UICtrl();
	virtual ~UICtrl();
	void UITask();
};

#endif /* INC_UICTRL_HPP_ */
