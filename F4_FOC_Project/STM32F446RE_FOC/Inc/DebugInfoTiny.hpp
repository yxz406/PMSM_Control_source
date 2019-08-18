/*
 * DebugInfo.hpp
 *
 *  Created on: Jul 1, 2019
 *      Author: watashi
 */

/*
 * Debug情報を動的確保すると、RAMが圧迫されて仕方がないから、
 * しょうがないから静的に確保することにした。
 * それがこのDebugInfoTiny.
 *
 * 将来的には外部RAMに情報詰め込みたいけどなぁ
 */

#ifndef DEBUGINFO_HPP_
#define DEBUGINFO_HPP_

#include <vector>
#include <array>
#include "paramsetting.h"


class DebugInfoTiny {
private:
	int mCNT;
public:
	std::array<float, DEBUG_COUNT> mIu;
	std::array<float, DEBUG_COUNT> mIv;
	std::array<float, DEBUG_COUNT> mIw;
	std::array<float, DEBUG_COUNT> mIalpha;
	std::array<float, DEBUG_COUNT> mIbeta;
	std::array<float, DEBUG_COUNT> mVd;
	std::array<float, DEBUG_COUNT> mVq;
	std::array<float, DEBUG_COUNT> mEArg;

	DebugInfoTiny();
	virtual ~DebugInfoTiny();
	void SetMotorData(float pIu, float pIv, float pIw,
			float pIalpha, float pIbeta,
			float pVd, float pVq,
			float pEArg);
	int GetCNT(void);
};



#endif /* DEBUGINFO_HPP_ */
