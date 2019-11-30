/*
 * Copyright 2016-2019 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/**
 * @file    MIMXRT1052xxxxB_ProjectPWM_C.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MIMXRT1052.h"
#include "fsl_debug_console.h"
/* TODO: insert other include files here. */

#include "fsl_pwm.h"
#include "fsl_xbara.h"
/* TODO: insert other definitions and declarations here. */
void SysInit(void);
void flexPWMInit(void);

/*
 * @brief   Application entry point.
 */
int main(void) {

  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
    BOARD_ConfigMPU();
  	/* Init FSL debug console. */
    BOARD_InitDebugConsole();

    PRINTF("Hello World\n");

    SysInit();


    while(1) {
    }

    return 0 ;
}

void SysInit(void) {


//    CLOCK_SetDiv(kCLOCK_AhbDiv, 0x2); /* Set AHB PODF to 2, divide by 3 */
//    CLOCK_SetDiv(kCLOCK_IpgDiv, 0x3); /* Set IPG PODF to 3, divede by 4 */

    /* Set the PWM Fault inputs to a low value */
    XBARA_Init(XBARA1);
    XBARA_SetSignalsConnection(XBARA1, kXBARA1_InputLogicHigh, kXBARA1_OutputFlexpwm1Fault0);
    XBARA_SetSignalsConnection(XBARA1, kXBARA1_InputLogicHigh, kXBARA1_OutputFlexpwm1Fault1);
    XBARA_SetSignalsConnection(XBARA1, kXBARA1_InputLogicHigh, kXBARA1_OutputFlexpwm1234Fault2);
    XBARA_SetSignalsConnection(XBARA1, kXBARA1_InputLogicHigh, kXBARA1_OutputFlexpwm1234Fault3);

    PRINTF("FlexPWM driver example\n");

    flexPWMInit();
}


void flexPWMInit(void) {

	//PWM_Init
    pwm_config_t pwmConfig;
    PWM_GetDefaultConfig(&pwmConfig);

    pwmConfig.enableDebugMode = true;	/*!< true: PWM continues to run in debug mode;
    										false: PWM is paused in debug mode */
    pwmConfig.enableWait = false;		/*!< true: PWM continues to run in WAIT mode;
											false: PWM is paused in WAIT mode */
    pwmConfig.faultFilterCount = 0;		/*!< Fault filter count */
    pwmConfig.faultFilterPeriod = 0;	/*!< Fault filter period;value of 0 will bypass the filter */
    pwmConfig.initializationControl = kPWM_Initialize_LocalSync;	/*!< Option to initialize the counter */
    pwmConfig.clockSource = kPWM_BusClock;	/*!< Clock source for the counter */
    pwmConfig.prescale = kPWM_Prescale_Divide_128;	/*!< Pre-scaler to divide down the clock */
    pwmConfig.pairOperation   = kPWM_ComplementaryPwmA;	/*!< Channel pair in indepedent or complementary mode */
    pwmConfig.reloadLogic = kPWM_ReloadPwmFullCycle;	/*!< PWM Reload logic setup */
    pwmConfig.reloadSelect = kPWM_LocalReload;	/*!< Reload source select */
    pwmConfig.reloadFrequency = kPWM_LoadEveryOportunity;	/*!< Specifies when to reload, used when user's choice
																is not immediate reload */
    pwmConfig.forceTrigger = kPWM_Force_Local;	/*!< Specify which signal will trigger a FORCE_OUT */


    if (PWM_Init(PWM1, kPWM_Module_3, &pwmConfig) == kStatus_Fail)
    {
        PRINTF("PWM initialization failed\n");
        return;
    }

    //pwm setup
    uint16_t deadTimeVal;
    pwm_signal_param_t pwmSignal[1];
    uint32_t pwmSourceClockInHz;
    uint32_t pwmFrequencyInHz = 4;

    //double ahbclk = CLOCK_GetAhbFreq();//for Debug
    pwmSourceClockInHz = CLOCK_GetFreq(kCLOCK_IpgClk);

    /* Set deadtime count, we set this to about 650ns */
    deadTimeVal = ((uint64_t)pwmSourceClockInHz * 650) / 1000000000;

    pwmSignal[0].pwmChannel       = kPWM_PwmA;
    pwmSignal[0].level            = kPWM_HighTrue;
    pwmSignal[0].dutyCyclePercent = 50; /* 1 percent dutycycle */
    pwmSignal[0].deadtimeValue    = deadTimeVal;

//    pwmSignal[1].pwmChannel = kPWM_PwmB;
//    pwmSignal[1].level      = kPWM_HighTrue;
//    /* Dutycycle field of PWM B does not matter as we are running in PWM A complementary mode */
//    pwmSignal[1].dutyCyclePercent = 50;
//    pwmSignal[1].deadtimeValue    = deadTimeVal;

    PWM_SetupPwm(PWM1, kPWM_Module_3, pwmSignal, 1, kPWM_SignedCenterAligned, pwmFrequencyInHz,
                 pwmSourceClockInHz);


    /* Set the load okay bit for all submodules to load registers from their buffer */
    PWM_SetPwmLdok(PWM1, kPWM_Control_Module_3, true);

    /* Start the PWM generation*/
    PWM_StartTimer(PWM1, kPWM_Control_Module_3);
}














//static void PWM_DRV_Init3PhPwm(void)
//{
//    uint16_t deadTimeVal;
//    pwm_signal_param_t pwmSignal[2];
//    uint32_t pwmSourceClockInHz;
//    uint32_t pwmFrequencyInHz = 1000;
//    //pwmFrequencyInHz = 10000;
//    pwmSourceClockInHz = CLOCK_GetFreq(kCLOCK_IpgClk);
//
//    /* Set deadtime count, we set this to about 650ns */
//    deadTimeVal = ((uint64_t)pwmSourceClockInHz * 650) / 1000000000;
//
//    pwmSignal[0].pwmChannel       = kPWM_PwmA;
//    pwmSignal[0].level            = kPWM_HighTrue;
//    pwmSignal[0].dutyCyclePercent = 50; /* 1 percent dutycycle */
//    pwmSignal[0].deadtimeValue    = deadTimeVal;
//
//    pwmSignal[1].pwmChannel = kPWM_PwmB;
//    pwmSignal[1].level      = kPWM_HighTrue;
//    /* Dutycycle field of PWM B does not matter as we are running in PWM A complementary mode */
//    pwmSignal[1].dutyCyclePercent = 50;
//    pwmSignal[1].deadtimeValue    = deadTimeVal;
//
//    /*********** PWMA_SM0 - phase A, configuration, setup 2 channel as an example ************/
//    PWM_SetupPwm(PWM1, kPWM_Module_0, pwmSignal, 2, kPWM_SignedCenterAligned, pwmFrequencyInHz,
//                 pwmSourceClockInHz);
//
////    /*********** PWMA_SM1 - phase B configuration, setup PWM A channel only ************/
////    PWM_SetupPwm(PWM1, kPWM_Module_1, pwmSignal, 1, kPWM_SignedCenterAligned, pwmFrequencyInHz,
////                 pwmSourceClockInHz);
////
////    /*********** PWMA_SM2 - phase C configuration, setup PWM A channel only ************/
////    PWM_SetupPwm(PWM1, kPWM_Module_2, pwmSignal, 1, kPWM_SignedCenterAligned, pwmFrequencyInHz,
////                 pwmSourceClockInHz);
////
////
////    PWM_SetupPwm(PWM1, kPWM_Module_3, pwmSignal, 1, kPWM_SignedCenterAligned, pwmFrequencyInHz,
////                 pwmSourceClockInHz);
//}




