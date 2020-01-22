/*
* UnitDelay.hpp
*
*  Created on: 2020/01/12
*      Author: watashi
*/

#ifndef INC_UNITDELAY_HPP_
#define INC_UNITDELAY_HPP_

class UnitDelay {
private:
	double mOldVal = 0;
	double mNewVal = 0;
public:
	UnitDelay();
	virtual ~UnitDelay();
	double PushAndGetVal(double pNewVal);
};

#endif /* INC_UNITDELAY_HPP_ */
