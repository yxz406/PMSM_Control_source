/*
 * SPICtrl.hpp
 *
 *  Created on: Dec 21, 2019
 *      Author: watashi
 */

#ifndef INC_SPICTRL_HPP_
#define INC_SPICTRL_HPP_


#include "paramsetting.h"
#include <array>
#include <vector>



union IntToCharArray {
	int mInt;
	std::array<uint8_t,4> mByte;
};

class SPICtrl {
private:
	char* mData;
	std::vector<uint8_t> mTxBuffer;
	std::vector<uint8_t> mRxBuffer;

	IntToCharArray mTmpData;

public:
	SPICtrl();
	virtual ~SPICtrl();
	void SetTransmitData();
	void PushBackTransmitIntData(int pIntData);
	std::vector<uint8_t> GetReceiveData();
	void SPITransmitReceive();
};






#endif /* INC_SPICTRL_HPP_ */
