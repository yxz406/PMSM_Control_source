/*
 * MathLib.cpp
 *
 *  Created on: Jun 20, 2019
 *      Author: watashi
 */

#include "MathLib.hpp"

#include <vector>
#include "math.h"




MathLib::MathLib() {
	// TODO Auto-generated constructor stub
	std::vector<int> mSinList;
	std::vector<int> mCosList;


}

MathLib::~MathLib() {
	// TODO Auto-generated destructor stub
}


void sinVectorInit(std::vector<int> *pVector){
	int lange;
	lange = 600;
	int count = 65535;
	for(int i=0;i<lange;i++){
		float fsinval = sin(i*2*M_PI/(float)lange);
		int val = count/2 * fsinval + count/2;
		pVector->push_back(val);
	}
}

void cosVectorInit(std::vector<int> *pVector){
	int lange;
	lange = 600;
	int count = 65535;
	for(int i=0;i<lange;i++){
		float fcosval = cos(i*2*M_PI/(float)lange);
		int val = count/2 * fcosval + count/2;
		pVector->push_back(val);
	}
}
