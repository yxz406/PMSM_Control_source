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
	float mOldVal = 0;
	float mNewVal =0;
public:
	UnitDelay();
	virtual ~UnitDelay();
	float PushAndGetVal(float pNewVal);//ところてん方式FIRに使える

	void SetVal(float pNewVal);
	float GetOldVal(void);

};

#endif /* INC_UNITDELAY_HPP_ */
