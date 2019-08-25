/*
 * Observer.hpp
 *
 *  Created on: Aug 20, 2019
 *      Author: watashi
 */

#ifndef OBSERVER_HPP_
#define OBSERVER_HPP_

#include <array>
#include "paramsetting.h"

class Observer {
public://pub-class
	class Zintegrate2n{
	private:
		float mK;
		std::array<float, 2> mVector;
		std::array<float, 2> mOldVec;
	public:
		void ZintegrateInit(float pK);
		std::array<float, 2> integrate(float pTime, std::array<float, 2> pVector);
	};

private:
	//motor param
	float mR;
	float mLd;
	float mLq;

	float mG1;

	//input vector
	std::array<float, 2> mIalpha_beta;
	std::array<float, 2> mValpha_beta;

	//vector for calc
	float eta_ab;
	float est_emf_ab;
	float error_emf_ab;

	float adapt_emf_ab;
	//float est_omega_ele;
	float mEstOmegaE;

	float eta;
	float est_emf;
	float est_theta;

	std::array<float, 2> mv1;
	std::array<float, 2> mv2;
	std::array<float, 2> mv3;

	Zintegrate2n mv4Integrate;
	std::array<float, 2> mv4;


public:
	Observer();
	virtual ~Observer();
	void func();
	void MotorParamInit(float pR, float pLd, float pLq);
	void obsBiasInit(float pG1);

	void SetIalpha_beta(float pIalpha, float pIbeta);
	void SetValpha_beta(float pValpha, float pVbeta);


	std::array<float, 2> MatrixMultiple2n(float pa11, float pa12,
								  float pa21, float pa22,
								  std::array<float, 2> pVector);
	std::array<float, 2> VectorMultiple2n(float pGain, std::array<float, 2> pVector);
	std::array<float, 2> VectorAdd2n(std::array<float, 2> pVector1, std::array<float, 2> pVector2);
	std::array<float, 2> Zintegrate2n(float pTime, std::array<float, 2> pVector);//これは構造体・Classが必要

	void calc();

};

#endif /* OBSERVER_HPP_ */


//miyayu月曜日 20:59
//意味がありそうなのはこんなもんですかね。
//K=1
//v4→eta_ab
//v5→est_emf_ab
//v6→error_emf_ab
//v9→adapt_emf_ab
//v14→est_omega_ele
//
//v21→eta
//v23→est_emf
//v24→est_delTheta
//v30→est_Theta
