/*
 * adc.c
 *
 *  Created on: 2019/12/01
 *      Author: watashi
 */

#include <adc.h>
#include "fsl_adc.h"
#include "fsl_adc_etc.h"
#include "fsl_debug_console.h"

void ADC_Configuration(void)
{
    adc_config_t k_adcConfig;
    adc_channel_config_t adcChannelConfigStruct;

    /* Initialize the ADC module. */
    ADC_GetDefaultConfig(&k_adcConfig);
    ADC_Init(ADC1, &k_adcConfig);
    ADC_EnableHardwareTrigger(ADC1, true);

    adcChannelConfigStruct.channelNumber = 16U; /* External channel selection from ADC_ETC. */
    adcChannelConfigStruct.enableInterruptOnConversionCompleted = false;
    ADC_SetChannelConfig(ADC1, 0U, &adcChannelConfigStruct);
    ADC_SetChannelConfig(ADC1, 1U, &adcChannelConfigStruct);

    /* Do auto hardware calibration. */
    if (kStatus_Success == ADC_DoAutoCalibration(ADC1))
    {
        PRINTF("ADC_DoAntoCalibration() Done.\r\n");
    }
    else
    {
        PRINTF("ADC_DoAutoCalibration() Failed.\r\n");
    }
}

