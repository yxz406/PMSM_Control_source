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
//#include "fsl_adc.h"
#include "fsl_adc_etc.h"

//#include "fsl_pwm.h"
//#include "fsl_xbara.h"

#include "pwm.h"
#include "adc.h"
#include "eadc.h"
#include "xbara.h"

/* TODO: insert other definitions and declarations here. */


/*******************************************************************************
 * Global Variables
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

    PRINTF("interrupt!! ADC0\n");
}

void ADC_ETC_IRQ1_IRQHandler(void)
{
    ADC_ETC_ClearInterruptStatusFlags(ADC_ETC, kADC_ETC_Trg0TriggerSource, kADC_ETC_Done1StatusFlagMask);
    g_AdcConversionValue1 = ADC_ETC_GetADCConversionValue(ADC_ETC, 0U, 1U); /* Get trigger0 chain1 result. */
    __DSB();

    PRINTF("interrupt!! ADC1\n");
}


/*
 * @brief   Application entry point.
 */
int main(void) {

  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
  	/* Init FSL debug console. */
    BOARD_InitDebugConsole();

    PRINTF("Hello World\n");
    PRINTF("ADC_ETC_Hardware_Trigger_Conv Example Start!\r\n");


    ADC_Configuration();
    ADC_etc_Configuration();
    XBARA_Configuration();


    PRINTF("ADC Full Range: %d\r\n", g_Adc_12bitFullRange);

    PRINTF("FlexPWM driver example\n");

    flexPWMInit();

    //PWM_OutputTriggerEnable(PWM1, kPWM_Module_3, kPWM_ValueRegister_1, true);
    flexPWMSetup();


    PRINTF("Please press any key to get user channel's ADC value.\r\n");

    while (1)
    {
        //GETCHAR();
        PRINTF("ADC conversion vaule is %d and %d\r\n", g_AdcConversionValue0, g_AdcConversionValue1);
    }


}





