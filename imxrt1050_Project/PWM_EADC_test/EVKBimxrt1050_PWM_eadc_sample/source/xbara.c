/*
 * xbara.c
 *
 *  Created on: 2019/12/01
 *      Author: watashi
 */

#include <xbara.h>
#include "fsl_xbara.h"

void XBARA_Configuration(void)
{
    /* Init xbara module. */
    XBARA_Init(XBARA1);

    /* Configure the XBARA signal connections. */
    //XBARA_SetSignalsConnection(XBARA1, kXBARA1_InputPitTrigger0, kXBARA1_OutputAdcEtcXbar0Trig0);
    //XBARA_SetSignalsConnection(XBARA1, kXBARB3_InputFlexpwm1Pwm3OutTrig01, kXBARA1_OutputAdcEtcXbar0Trig0);
    //XBARA_SetSignalsConnection(XBARA1, kXBARA1_InputFlexpwm1Pwm3OutTrig01, kXBARA1_OutputAdcEtcXbar0Trig0);
    XBARA_SetSignalsConnection(XBARA1, kXBARA1_InputFlexpwm1Pwm4OutTrig01, kXBARA1_OutputAdcEtcXbar0Trig0);

    XBARA_SetSignalsConnection(XBARA1, kXBARA1_InputLogicHigh, kXBARA1_OutputFlexpwm1Fault0);
    XBARA_SetSignalsConnection(XBARA1, kXBARA1_InputLogicHigh, kXBARA1_OutputFlexpwm1Fault1);
    XBARA_SetSignalsConnection(XBARA1, kXBARA1_InputLogicHigh, kXBARA1_OutputFlexpwm1234Fault2);
    XBARA_SetSignalsConnection(XBARA1, kXBARA1_InputLogicHigh, kXBARA1_OutputFlexpwm1234Fault3);

}
