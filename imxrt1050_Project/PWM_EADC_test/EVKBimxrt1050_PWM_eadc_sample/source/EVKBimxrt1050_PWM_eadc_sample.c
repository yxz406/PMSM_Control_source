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
 * @file    EVKBimxrt1050_PWM_eadc_sample.c
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
#include "fsl_adc.h"
#include "fsl_adc_etc.h"

#include "fsl_pwm.h"
#include "fsl_xbara.h"

#include "pwm.h"
#include "adc.h"

/* TODO: insert other definitions and declarations here. */

void ADC_Configuration(void);
void XBARA_Configuration(void);
//void PIT_Configuration(void);

//void flexPWMInit(void);
//void flexPWMSetup(void);
/*******************************************************************************
 * Variables
 ******************************************************************************/
volatile uint32_t g_AdcConversionValue0;
volatile uint32_t g_AdcConversionValue1;
const uint32_t g_Adc_12bitFullRange = 4096U;

/*******************************************************************************
 * Code
 ******************************************************************************/
void ADC_ETC_IRQ0_IRQHandler(void)
{
    ADC_ETC_ClearInterruptStatusFlags(ADC_ETC, kADC_ETC_Trg0TriggerSource, kADC_ETC_Done0StatusFlagMask);
    g_AdcConversionValue0 = ADC_ETC_GetADCConversionValue(ADC_ETC, 0U, 0U); /* Get trigger0 chain0 result. */
    __DSB();
}

void ADC_ETC_IRQ1_IRQHandler(void)
{
    ADC_ETC_ClearInterruptStatusFlags(ADC_ETC, kADC_ETC_Trg0TriggerSource, kADC_ETC_Done1StatusFlagMask);
    g_AdcConversionValue1 = ADC_ETC_GetADCConversionValue(ADC_ETC, 0U, 1U); /* Get trigger0 chain1 result. */
    __DSB();
}


/*
 * @brief   Application entry point.
 */
int main(void) {

    adc_etc_config_t adcEtcConfig;
    adc_etc_trigger_config_t adcEtcTriggerConfig;
    adc_etc_trigger_chain_config_t adcEtcTriggerChainConfig;

  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
  	/* Init FSL debug console. */
    BOARD_InitDebugConsole();

    PRINTF("Hello World\n");
    PRINTF("ADC_ETC_Hardware_Trigger_Conv Example Start!\r\n");


    ADC_Configuration();
    XBARA_Configuration();

    /* Initialize the ADC_ETC. */
    ADC_ETC_GetDefaultConfig(&adcEtcConfig);
    adcEtcConfig.XBARtriggerMask = 1U; /* Enable the external XBAR trigger0. */
    ADC_ETC_Init(ADC_ETC, &adcEtcConfig);

    /* Set the external XBAR trigger0 configuration. */
    adcEtcTriggerConfig.enableSyncMode      = false;
    adcEtcTriggerConfig.enableSWTriggerMode = false;
    adcEtcTriggerConfig.triggerChainLength  = 1U; /* Chain length is 2. */
    adcEtcTriggerConfig.triggerPriority     = 0U;
    adcEtcTriggerConfig.sampleIntervalDelay = 0U;
    adcEtcTriggerConfig.initialDelay        = 0U;
    ADC_ETC_SetTriggerConfig(ADC_ETC, 0U, &adcEtcTriggerConfig);

    /* Set the external XBAR trigger0 chain configuration. */
    adcEtcTriggerChainConfig.enableB2BMode       = true;
    adcEtcTriggerChainConfig.ADCHCRegisterSelect = 1U << 0U; /* Select ADC_HC0 register to trigger. */
    adcEtcTriggerChainConfig.ADCChannelSelect = 15U; /* ADC_HC0 will be triggered to sample Corresponding channel. */
    adcEtcTriggerChainConfig.InterruptEnable = kADC_ETC_Done0InterruptEnable; /* Enable the Done0 interrupt. */
    ADC_ETC_SetTriggerChainConfig(ADC_ETC, 0U, 0U, &adcEtcTriggerChainConfig); /* Configure the trigger0 chain0. */
    adcEtcTriggerChainConfig.ADCHCRegisterSelect = 1U << 1U; /* Select ADC_HC1 register to trigger. */
    adcEtcTriggerChainConfig.ADCChannelSelect = 0U; /* ADC_HC1 will be triggered to sample Corresponding channel. */
    adcEtcTriggerChainConfig.InterruptEnable = kADC_ETC_Done1InterruptEnable; /* Enable the Done1 interrupt. */
    ADC_ETC_SetTriggerChainConfig(ADC_ETC, 0U, 1U, &adcEtcTriggerChainConfig); /* Configure the trigger0 chain1. */

    /* Enable the NVIC. */
    EnableIRQ(ADC_ETC_IRQ0_IRQn);
    EnableIRQ(ADC_ETC_IRQ1_IRQn);

    /* Start PIT channel0. */
    //PIT_StartTimer(PIT, kPIT_Chnl_0);

    PRINTF("ADC Full Range: %d\r\n", g_Adc_12bitFullRange);

    PRINTF("FlexPWM driver example\n");

    flexPWMInit();
   // PWM_OutputTriggerEnable(PWM1, kPWM_Module_3, kPWM_ValueRegister_5, true);
    PWM_OutputTriggerEnable(PWM1, kPWM_Module_3, kPWM_ValueRegister_1, true);
    flexPWMSetup();


    PRINTF("Please press any key to get user channel's ADC value.\r\n");

    while (1)
    {
        GETCHAR();
        PRINTF("ADC conversion vaule is %d and %d\r\n", g_AdcConversionValue0, g_AdcConversionValue1);
    }


}





