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

enum spiState{
 TRANSFER_WAIT,
 TRANSFER_COMPLETE,
 TRANSFER_ERROR
};

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
	spiState mspiState;

public:

	SPICtrl();
	virtual ~SPICtrl();
	void SetTransmitData();
	void PushBackTransmitIntData(int pIntData);
	void GetReceiveData();
	void SPITransmitReceive();

	void spiCplt() { mspiState = TRANSFER_COMPLETE; }
	void spiWait() {mspiState = TRANSFER_WAIT; }
	void spiErr() {mspiState = TRANSFER_ERROR; }

};






#endif /* INC_SPICTRL_HPP_ */
