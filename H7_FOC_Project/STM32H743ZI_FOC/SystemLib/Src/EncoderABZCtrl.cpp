/*
 * EncoderABZCtrl.cpp
 *
 *  Created on: 2019/10/22
 *      Author: watashi
 */

#include "EncoderABZCtrl.hpp"

TIM_HandleTypeDef EncoderABZCtrl::mHandleTIM4;

EncoderABZCtrl::EncoderABZCtrl() {
	// TODO Auto-generated constructor stub

}

EncoderABZCtrl::~EncoderABZCtrl() {
	// TODO Auto-generated destructor stub
}

//Initializer
/* TIM4 init function */
void EncoderABZCtrl::MX_TIM4_Init(void) {
  TIM_Encoder_InitTypeDef sConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  mHandleTIM4.Instance = TIM4;
  mHandleTIM4.Init.Prescaler = 0;
  mHandleTIM4.Init.CounterMode = TIM_COUNTERMODE_UP;
  mHandleTIM4.Init.Period = ENCODER_PERIOD;
  mHandleTIM4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  mHandleTIM4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  sConfig.EncoderMode = TIM_ENCODERMODE_TI1;
  sConfig.IC1Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC1Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC1Filter = 0;
  sConfig.IC2Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC2Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC2Filter = 0;
  if (HAL_TIM_Encoder_Init(&mHandleTIM4, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&mHandleTIM4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }

}


void EncoderABZCtrl::EncoderStart(void) {
	HAL_TIM_Encoder_Start(&mHandleTIM4,TIM_CHANNEL_ALL);
}

void EncoderABZCtrl::EncoderStop(void) {
	HAL_TIM_Encoder_Stop(&mHandleTIM4,TIM_CHANNEL_ALL);
}

int EncoderABZCtrl::GetAngle(void) {
	return TIM4->CNT;
}
