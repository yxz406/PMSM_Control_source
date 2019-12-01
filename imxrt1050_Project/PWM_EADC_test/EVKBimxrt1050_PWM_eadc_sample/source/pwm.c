/*
 * pwm.c
 *
 *  Created on: 2019/12/01
 *      Author: watashi
 */

#include "fsl_pwm.h"
#include "fsl_debug_console.h"


#include "pwm.h"


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

}

void flexPWMSetup(void) {
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
