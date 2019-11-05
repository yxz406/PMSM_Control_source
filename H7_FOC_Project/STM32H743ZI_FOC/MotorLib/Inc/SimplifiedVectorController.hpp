/*
 * SimplifiedVectorController.hpp
 *
 *  Created on: 2019/11/05
 *      Author: watashi
 */

#ifndef SRC_SIMPLIFIEDVECTORCONTROLLER_HPP_
#define SRC_SIMPLIFIEDVECTORCONTROLLER_HPP_

class SimplifiedVectorController {
private:
	float mR;
	float mLd;
	float mLq;
	float mKe;
	bool mIsInit=false;
public:
	SimplifiedVectorController(float pR, float pLd, float pLq, float pKe);
	virtual ~SimplifiedVectorController();
	float VoltageRefCalc();
};

#endif /* SRC_SIMPLIFIEDVECTORCONTROLLER_HPP_ */
