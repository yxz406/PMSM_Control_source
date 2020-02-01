/*
 * SPICtrl.hpp
 *
 * Singleton Class
 * どうあがいてもSPIのコントローラは一つしかないから、
 * 複数のクラスに持たせるといろいろヤバい競合起こる。
 *
 *実機ではシングルトンとして運用して、テストではモックを作ること。
 *
 *  Created on: Dec 21, 2019
 *      Author: watashi
 */

#ifndef INC_SPICTRL_HPP_
#define INC_SPICTRL_HPP_

#include "spi.h"
#include "paramsetting.h"
#include <array>
//#include <vector>

enum spiState{
 TRANSFER_WAIT,
 TRANSFER_COMPLETE,
 TRANSFER_ERROR
};

//union IntToCharArray {
//	int mInt;
//	std::array<uint8_t,4> mByte;
//};

class SPICtrl {

	//Singleton element
private:
	SPICtrl() = default;
	~SPICtrl() = default;
public:
	SPICtrl(const SPICtrl&) = delete;
	SPICtrl& operator=(const SPICtrl&) = delete;
	SPICtrl(SPICtrl&&) = delete;
	SPICtrl& operator=(SPICtrl&&) = delete;
    static SPICtrl& GetInstance() {
        static SPICtrl instance;
        return instance;
    }

private:
	int mArrayPos = 0;

	uint8_t m0fillArr[SPI_DATA_SIZE] = {0};
	uint8_t mTxData[SPI_DATA_SIZE] = {0};
	uint8_t mRxData[SPI_DATA_SIZE] = {0};

	std::array<int,(SPI_DATA_SIZE/4)> mRxInt;

	spiState mspiState;

public:


	void SetTransmitData(const uint8_t* pTxData);
	void PushBackTransmitIntData(int pIntData);
	uint8_t* GetReceiveData();

	std::array<int,(SPI_DATA_SIZE/4)> GetRxInt();

	void SPITransmitReceive();

	void SPIComplete() { mspiState = TRANSFER_COMPLETE; }
	void SPIWait() {mspiState = TRANSFER_WAIT; }
	void SPIError() {mspiState = TRANSFER_ERROR; }

};






#endif /* INC_SPICTRL_HPP_ */
