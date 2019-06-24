/*
 * MathLib.hpp
 *
 *  Created on: Jun 20, 2019
 *      Author: watashi
 */

#ifndef MATHLIB_HPP_
#define MATHLIB_HPP_

#include <vector>

class MathLib {
private:
	std::vector<float> mSinList;
	std::vector<float> mCosList;
	int mSize;
	void fSinVectorInit(std::vector<float> *pVector);
	void fCosVectorInit(std::vector<float> *pVector);
	void setLibSize(int pSize);

public:
	MathLib();
	virtual ~MathLib();
	void fInit(int pSize);
	std::vector<float> getSinList(void);
	std::vector<float> getCosList(void);
};



#endif /* MATHLIB_HPP_ */
