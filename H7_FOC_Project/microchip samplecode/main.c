/**********************************************************************
* © 2011 Microchip Technology Inc.
*
* SOFTWARE LICENSE AGREEMENT:
* Microchip Technology Incorporated ("Microchip") retains all ownership and 
* intellectual property rights in the code accompanying this message and in all 
* derivatives hereto.  You may use this code, and any derivatives created by 
* any person or entity by or on your behalf, exclusively with Microchip's
* proprietary products.  Your acceptance and/or use of this code constitutes 
* agreement to the terms and conditions of this notice.
*
* CODE ACCOMPANYING THIS MESSAGE IS SUPPLIED BY MICROCHIP "AS IS".  NO 
* WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED 
* TO, IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY AND FITNESS FOR A 
* PARTICULAR PURPOSE APPLY TO THIS CODE, ITS INTERACTION WITH MICROCHIP'S 
* PRODUCTS, COMBINATION WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
*
* YOU ACKNOWLEDGE AND AGREE THAT, IN NO EVENT, SHALL MICROCHIP BE LIABLE, WHETHER 
* IN CONTRACT, WARRANTY, TORT (INCLUDING NEGLIGENCE OR BREACH OF STATUTORY DUTY), 
* STRICT LIABILITY, INDEMNITY, CONTRIBUTION, OR OTHERWISE, FOR ANY INDIRECT, SPECIAL, 
* PUNITIVE, EXEMPLARY, INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, FOR COST OR EXPENSE OF 
* ANY KIND WHATSOEVER RELATED TO THE CODE, HOWSOEVER CAUSED, EVEN IF MICROCHIP HAS BEEN 
* ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT 
* ALLOWABLE BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY RELATED TO 
* THIS CODE, SHALL NOT EXCEED THE PRICE YOU PAID DIRECTLY TO MICROCHIP SPECIFICALLY TO 
* HAVE THIS CODE DEVELOPED.
*
* You agree that you are solely responsible for testing the code and 
* determining its suitability.  Microchip has no obligation to modify, test, 
* certify, or support the code.
*
******************************************************************************/

#include "p33Exxxx.h"
#include "svm.h"
#include "pi.h"
#include "userdef.h"
#include "rtdmuser.h"
#include "rtdm.h"



/******************************************************************************/
/* Configuration bits                                                         */
/******************************************************************************/
_FPOR(ALTI2C1_OFF & ALTI2C2_OFF);
_FWDT(PLLKEN_ON & FWDTEN_OFF);
_FOSCSEL(FNOSC_FRC & IESO_OFF & PWMLOCK_OFF);
_FGS(GWRP_OFF & GCP_OFF);

_FICD(ICS_PGD2 & JTAGEN_OFF);	// PGD3 for 28pin 	PGD2 for 44pin
_FOSC(FCKSM_CSECMD & POSCMD_XT);		//XT W/PLL



// These Phase values represent the base Phase value of the sinewave for each
// one of the sectors (each sector is a translation of the hall effect sensors
// reading 
#define PHASE_ZERO 	0
#define PHASE_ONE	((PHASE_ZERO + 65536/6) % 65536)
#define PHASE_TWO	((PHASE_ONE + 65536/6) % 65536)
#define PHASE_THREE	((PHASE_TWO + 65536/6) % 65536)
#define PHASE_FOUR	((PHASE_THREE + 65536/6) % 65536)
#define PHASE_FIVE	((PHASE_FOUR + 65536/6) % 65536)

/* maximum phase advance formula */
#define MAX_PH_ADV 		(int)(((float)MAX_PH_ADV_DEG / 360.0) * 65536.0)

#ifdef RTDM_DEMO

int RecorderBuffer1[DATA_BUFFER_SIZE]; //Buffer to store the data samples for the DMCI data viewer Graph1
int RecorderBuffer2[DATA_BUFFER_SIZE];	//Buffer to store the data samples for the DMCI data viewer Graph2
int RecorderBuffer3[DATA_BUFFER_SIZE];	//Buffer to store the data samples for the DMCI data viewer Graph3
int RecorderBuffer4[DATA_BUFFER_SIZE];	//Buffer to store the data samples for the DMCI data viewer Graph4

int * PtrRecBuffer1 = &RecorderBuffer1[0];	//Tail pointer for the DMCI Graph1
int * PtrRecBuffer2 = &RecorderBuffer2[0];	//Tail pointer for the DMCI Graph2
int * PtrRecBuffer3 = &RecorderBuffer3[0];	//Tail pointer for the DMCI Graph3
int * PtrRecBuffer4 = &RecorderBuffer4[0];	//Tail pointer for the DMCI Graph4
int * RecBuffUpperLimit = RecorderBuffer4 + DATA_BUFFER_SIZE -1;	//Buffer Recorder Upper Limit
typedef struct DMCIFlags{
		    unsigned Recorder : 1;	// Flag needs to be set to start buffering data
			unsigned StartStop : 1;
			unsigned unused : 14;  
} DMCIFLAGS;
DMCIFLAGS DMCIFlags;
int	SnapCount = 0;

int SnapShotDelayCnt = 0;
int SnapShotDelay = SNAPDELAY;
int SpeedReference = 0;

#endif // End of #ifdef RTDM_DEMO
        
               
void InitADC10(void);	// Initialization of ADC used for Speed Command
void InitMCPWM(void);	// Initialization for PWM at 20kHz, Center aligned, 
                        // Complementary mode with 2 us of deadtime
void InitTMR1(void);	// Initialization for TIMER1 used for speed control 
                        // and motor stalled protection
void InitTMR3(void);	// Initialization for TIMER3 used as a timebase 
                        // for the two input capture channels
void RunMotor(void);	// This function initializes all variables 
                        // and interrupts used for starting and running 
                        // the motor
void StopMotor(void);	// This function clears all flags, and stops anything
                        // related to motor control, and also disables PWMs
void SpeedControl(void);     // This function contains all ASM and C operations
                             // for doing the PID Control loop for the speed
void ForceCommutation(void); // When motor is to slow to generate interrupts 
                             // on halls, this function forces a commutation
void ChargeBootstraps(void); // At the begining of the motor operation, the 
                             // bootstrap caps are charged with this function
void Delay(unsigned int delay_count);

// In the sinewave generation algorithm we need an offset to be added to the
// pointer when energizing the motor in CCW. This is done to compensate an
// asymetry of the sinewave
int PhaseOffsetCW = PHASE_OFFSET_CW;
int PhaseOffsetCCW = PHASE_OFFSET_CCW;

int PeriodFilter;

// Constants used for properly energizing the motor depending on the 
// rotor's position
const int PhaseValues[6] =
{PHASE_ZERO, PHASE_ONE, PHASE_TWO, PHASE_THREE, PHASE_FOUR, PHASE_FIVE}; 

// Flags used for the application
struct 
{
	unsigned MotorRunning	:1;  // This bit is 1 if motor running
	unsigned unused			:15;
}Flags;
 
/* PI configuration structure */
tPIParm PIparms;
 
unsigned int Phase;	// This variable is incremented by the PWM interrupt
                    // in order to generate a proper sinewave. Its value
                    // is incremented by a value of PhaseInc, which
                    // represents the frequency of the generated sinewave
signed int PhaseInc; // Delta increments of the Phase variable, calculated 
                     // in the TIMER1 interrupt and used in 
                     // the PWM interrupt (each 50 us)
signed int PhaseAdvance; // Used for extending motor speed range. This value
                         // is added directly to the parameters passed to the
                         // SVM function (the sine wave generation subroutine)
unsigned int HallValue;	 // This variable holds the hall sensor input readings
unsigned int Sector;  // This variables holds present sector value, which is 
                      // the rotor position
unsigned int LastSector; // This variable holds the last sector value. This 
                         // is critical to filter slow slew rate on the Hall
                         // effect sensors hardware
unsigned int MotorStalledCounter = 0; // This variable gets incremented each 
                                      // 1 ms, and is cleared everytime a new
                                      // sector is detected. Used for 
                                      // ForceCommutation and MotorStalled 
                                      // protection functions
// This array translates the hall state value read from the digital I/O to the
// proper sector.  Hall values of 0 or 7 represent illegal values and therefore
// return -1.
char SectorTable[] = {-1,4,2,3,0,5,1,-1};
unsigned char Current_Direction;	// Current mechanical motor direction of 
                                    // rotation Calculated in halls interrupts
unsigned char Required_Direction;	// Required mechanical motor direction of 
                                    // rotation, will have the same sign as the
									// ControlOutput variable from the Speed 
                                    // Controller
  
// Variables containing the Period of half an electrical cycle, which is an 
// interrupt each edge of one of the hall sensor input
unsigned int PastCapture, ActualCapture, Period; 

// Used as a temporal variable to perform a fractional divide operation in 
// assembly
int MeasuredSpeed, RefSpeed = 200;	// Actual and Desired speeds for the PID 
                            // controller, that will generate the error
int ControlOutput = 0;	// Controller output, used as a voltage output, 
                            // use its sign for the required direction


// Used as a temporal variable to perform a fractional divide operation in 
// assembly
int _MAX_PH_ADV = MAX_PH_ADV;


void Delay(unsigned int delay_count)
{
	int i;
	while (delay_count-- > 0)
	{
		for (i = 0;i < 3000;i++);
	}
	return;
}


/*********************************************************************************** 
 * Function: IOMap()
 *
 * Preconditions: None.
 *
 * Overview: This executes the necessary process to map the RPn pins to the
 *			 appropriate peripherals on the dsPIC33EP512MU810.
 *
 * Input: None.
 *
 * Output: None.
 *
 *****************************************************************************/
void IOMap()
{

	//	Unlock the Reprogrammable Pin Mechanism
	__builtin_write_OSCCONL(OSCCON & (~(1<<6))); // clear bit 6 
	
    TRISB = 0x03FF;					//Set PWM pins as outputs
    
    TRISFbits.TRISF1 = 0;	// Output - UART TX
    TRISDbits.TRISD6 = 0;	// DBG_LED1 output
    TRISDbits.TRISD5 = 0;	// DBG_LED2 output
    TRISDbits.TRISD8 = 0;	// Test Point
    
	// RP36/RB4 is input for fault1
	TRISBbits.TRISB4 = 1;
	RPINR12 = 0;
	RPINR12bits.FLT1R = 0x24;

	// Push Button connected to pin 48 (RB8)
	LATBbits.LATB8 = 0;
	TRISBbits.TRISB8 = 1;
	ANSELBbits.ANSB8 = 0;

	// POT connected to device pin 28 (AN13/RE13)
	TRISEbits.TRISE13 = 1;
	ANSELEbits.ANSE13 = 1;

	//  Assign IC1(HALLA) to RPI24
	//  Assign IC2(HALLB) to RP54
	TRISAbits.TRISA8 = 1;
	TRISCbits.TRISC6 = 1;
	RPINR7 = 0;
	RPINR7bits.IC1R = 0x18;
	RPINR7bits.IC2R = 0x36;

	//  Assign IC3(HALLC) to RPI96
	TRISFbits.TRISF0 = 1;
	RPINR8 = 0;
	RPINR8bits.IC3R = 0x60;
  
	#ifdef RTDM_DEMO
	RPINR19bits.U2RXR = 0x0035;		// Make Pin RPI53 U2RX
    RPOR7bits.RP97R = 0x0003;		// Make Pin RP97 U2TX 
	#endif

	//	Lock the Reprogrammable Pin Mechanism
	__builtin_write_OSCCONL(OSCCON | (1<<6)); 	 // Set bit 6 
}
 
/*********************************************************************
  Function:        void __attribute__((__interrupt__)) _T1Interrupt (void)
  PreCondition:    The motor is running and is generating hall effect sensors
                   interrupts. Also, the actual direction of the motor used
                   in this interrupt is assumed to be previously calculated.
 
  Input:           None.
  Output:          None.
  Side Effects:    None.
  Overview:        In this ISR the Period, Phase Increment and MeasuredSpeed
                   are calculated based on the input capture of one of the
                   halls. The speed controller is also called in this ISR
                   to generate a new output voltage (ControlOutput). The 
                   Phase Advance is calculated based on the maximum allowed
                   phase advance (MAX_PH_ADV) and the actual speed of the 
                   motor. The last thing done in this ISR is the forced 
                   commutation, which happens each time the motor doesn't
                   generate a new hall interrupt after a programmed period 
                   of time. If the timeout for generating hall ISR is too much
                   (i.e. 100 ms) the motor is then stopped.
  Note:            The MeasuredSpeed Calculation is made in assembly to take 
                   advantage of the signed fractional division.
********************************************************************/
void __attribute__((interrupt, no_auto_psv)) _T1Interrupt (void)
{

	static int PeriodKFilter = PERIOD_FILTER_CONST;
	

    static long int PeriodStateVar;
	
	IFS0bits.T1IF = 0;
	Period = ActualCapture - PastCapture;  // This is an UNsigned substraction
                                           // to get the Period between one 
                                           // hall effect sensor transition

    // These operations limit the Period value to a range from 60 to 6000 rpm
	if (Period < (unsigned int)MINPERIOD)  // MINPERIOD or 6000 rpm
		Period = MINPERIOD;
	else if (Period > (unsigned int)MAXPERIOD) // MAXPERIOD or 60 rpm
		Period = MAXPERIOD;

    PeriodStateVar+= (((long int)Period - (long int)PeriodFilter)*(int)(PeriodKFilter));
	PeriodFilter = (int)(PeriodStateVar>>15);


    // PhaseInc is a value added to the Phase variable to generate the sine
    // voltages. 1 electrical degree corresponds to a PhaseInc value of 184,
    // since the pointer to the sine table is a 16bit value, where 360 Elec
    // Degrees represents 65535 in the pointer. 
    // __builtin_divud(Long Value, Int Value) is a function of the compiler
    // to do Long over Integer divisions.
    PhaseInc = __builtin_divud((long unsigned int)PHASE_INC_CALC,(unsigned int)PeriodFilter);
    
	MeasuredSpeed = __builtin_divud((long unsigned int)SPEED_RPM_CALC,(unsigned int)PeriodFilter);

    // MeasuredSpeed sign adjustment based on current motor direction of 
    // rotation


	if (Current_Direction == CCW)
		MeasuredSpeed = -MeasuredSpeed;


    // The following values represent the MeasuredSpeed values from the 
    // previous operations:
    //
	// CONDITION        RPM          SFRAC16      SINT      HEX
	// Max Speed CW  -> 6000 RPM  -> 0.996805  -> 32663  -> 0x7F97
	// Min Speed CW  -> 60 RPM    -> 0.009984  -> 327    -> 0x0147
	// Min Speed CCW -> -60 RPM   -> -0.009984 -> -327   -> 0xFEB9
	// Max Speed CCW -> -6000 RPM -> -0.996805 -> -32663 -> 0x8069
	SpeedControl(); // Speed PID controller is called here. It will use 
                    // MeasuredSpeed, RefSpeed, some buffers and will generate
                    // the new ControlOutput, which represents a new amplitude
                    // of the sinewave that will be generated by the SVM 
                    // subroutine.
#ifdef PHASE_ADVANCE
		// Calculate Phase Advance Based on Actual Speed and MAX_PH_ADV define
        // The following assembly instruction perform the following formula
        // using fractional multiplication:
        // 
        // PhaseAdvance = MAX_PH_ADV * MeasuredSpeed
        //

        register int a_reg asm("A");
        a_reg = __builtin_mpy(_MAX_PH_ADV, MeasuredSpeed, 0,0,0,0,0,0);
        PhaseAdvance = __builtin_sac(a_reg,0);

#endif
	MotorStalledCounter++;	// We increment a timeout variable to see if the
                            // motor is too slow (not generating hall effect
                            // sensors interrupts frequently enough) or if
                            // the motor is stalled. This variable is cleared
                            // in halls ISRs
    if ((MotorStalledCounter % _10MILLISEC) == 0)
	{
		ForceCommutation();	// Force Commutation if no hall sensor changes 
                            // have occured in specified timeout.
	}
	else if (MotorStalledCounter >= _1SEC)
	{
		StopMotor(); // Stop motor is no hall changes have occured in 
                     // specified timeout
	}

	return;
}
/*********************************************************************
  Function:        void __attribute__((__interrupt__)) _IC1Interrupt (void)
  PreCondition:    The inputs of the hall effect sensors should have low pass
                   filters. A simple RC network works.
 
  Input:           None.
  Output:          None.
  Side Effects:    None.
  Overview:        This interrupt represent Hall A ISR. Hall A -> RC3 -> IC1.
                   This is generated by the input change notification IC1.
                   The purpose of this ISR is to Calculate the actual 
                   mechanical direction of rotation of the motor, and to adjust
                   the Phase variable depending on the sector the rotor is in.
  Note 1:          The sector is validated in order to avoid any spurious
                   interrupt due to a slow slew rate on the halls inputs due to
                   hardware filtering.
  Note 2:          For Phase adjustment in CCW, an offset is added to 
                   compensate non-symetries in the sine table used.
********************************************************************/
void __attribute__((interrupt, no_auto_psv)) _IC1Interrupt (void)
{

	IFS0bits.IC1IF = 0;	// Cleat interrupt flag
	HallValue = HALLA_BIT+2*HALLB_BIT+4*HALLC_BIT;// Read halls
	Sector = SectorTable[HallValue];	// Get Sector from table

    // This MUST be done for getting around the HW slow rate
	if (Sector != LastSector)	
	{
		// Since a new sector is detected, clear variable that would stop 
        // the motor if stalled.
		MotorStalledCounter = 0;
		// Motor current direction is computed based on Sector
		if ((Sector == 5) || (Sector == 2))	
			Current_Direction = CW;
		else
			Current_Direction = CCW;
        // Motor commutation is actually based on the required direction, not
        // the current dir. This allows driving the motor in four quadrants
	if (Required_Direction == CW)	
		{
			Phase = PhaseValues[(Sector) % 6] + PhaseOffsetCW;
		}
		else
		{
			// For CCW an offset must be added to compensate difference in 
            // symmetry of the sine table used for CW and CCW
			Phase = PhaseValues[(Sector + 3) % 6]+ PhaseOffsetCCW;
		}
		LastSector = Sector; // Update last sector
	}

	return;
}
/*********************************************************************
  Function:        void __attribute__((__interrupt__)) _IC2Interrupt (void)
  PreCondition:    The inputs of the hall effect sensors should have low pass
                   filters. A simple RC network works.
 
  Input:           None.
  Output:          None.
  Side Effects:    None.
  Overview:        This interrupt represent Hall B ISR. Hall B -> RA9 -> IC2.
                   This is generated by the input Capture Channel IC2.
                   The purpose of this ISR is to Calculate the actual Period
                   between hall effect sensor transitions, calculate the actual
                   mechanical direction of rotation of the motor, and also to
                   adjust the Phase variable depending on the sector the rotor
                   is in.
  Note 1:          The sector is validated in order to avoid any spurious
                   interrupt due to a slow slew rate on the halls inputs due to
                   hardware filtering.
  Note 2:          For Phase adjustment in CCW, an offset is added to 
                   compensate non-symetries in the sine table used.
********************************************************************/
void __attribute__((interrupt, no_auto_psv)) _IC2Interrupt (void)
{

	IFS0bits.IC2IF = 0;	// Cleat interrupt flag
	HallValue = HALLA_BIT+2*HALLB_BIT+4*HALLC_BIT;// Read halls	
	Sector = SectorTable[HallValue];	// Get Sector from table

    // This MUST be done for getting around the HW slow rate
	if (Sector != LastSector)
	{
		// Calculate Hall period corresponding to half an electrical cycle
		PastCapture = ActualCapture;
		ActualCapture = IC2BUF;
		IC2BUF;
		IC2BUF;
		IC2BUF;
		// Since a new sector is detected, clear variable that would stop 
        // the motor if stalled.
		MotorStalledCounter = 0;
		// Motor current direction is computed based on Sector
		if ((Sector == 3) || (Sector == 0))
			Current_Direction = CW;
		else
			Current_Direction = CCW;
        // Motor commutation is actually based on the required direction, not
        // the current dir. This allows driving the motor in four quadrants
		if (Required_Direction == CW)
		{
			Phase = PhaseValues[(Sector) % 6] + PhaseOffsetCW;
		}
		else
		{
			// For CCW an offset must be added to compensate difference in 
            // symmetry of the sine table used for CW and CCW
			Phase = PhaseValues[(Sector + 3) % 6] + PhaseOffsetCCW;
		}
		LastSector = Sector; // Update last sector
	}

	return;
}
/*********************************************************************
  Function:        void __attribute__((__interrupt__)) _IC3Interrupt (void)
  PreCondition:    The inputs of the hall effect sensors should have low pass
                   filters. A simple RC network works.
 
  Input:           None.
  Output:          None.
  Side Effects:    None.
  Overview:        This interrupt represent Hall C ISR. Hall C -> RA4 -> IC3.
                   This is generated by the input Capture Channel IC3.
                   The purpose of this ISR is to Calculate the actual 
                   mechanical direction of rotation of the motor, and to adjust
                   the Phase variable depending on the sector the rotor is in.
  Note 1:          The sector is validated in order to avoid any spurious
                   interrupt due to a slow slew rate on the halls inputs due to
                   hardware filtering.
  Note 2:          For Phase adjustment in CCW, an offset is added to 
                   compensate non-symetries in the sine table used.
********************************************************************/
void __attribute__((interrupt, no_auto_psv)) _IC3Interrupt (void)
{	
	IFS2bits.IC3IF = 0;	// Cleat interrupt flag
	HallValue = HALLA_BIT+2*HALLB_BIT+4*HALLC_BIT;// Read halls		
	Sector = SectorTable[HallValue];	// Get Sector from table

    // This MUST be done for getting around the HW slow rate
	if (Sector != LastSector)
	{
		// Since a new sector is detected, clear variable that would stop 
        // the motor if stalled.
		MotorStalledCounter = 0;
		// Motor current direction is computed based on Sector
		if ((Sector == 1) || (Sector == 4))
			Current_Direction = CW;
		else
			Current_Direction = CCW;
		
        // Motor commutation is actually based on the required direction, not
        // the current dir. This allows driving the motor in four quadrants
		if (Required_Direction == CW)
		{
			Phase = PhaseValues[(Sector) % 6] + PhaseOffsetCW;
		}
		else
		{
			// For CCW an offset must be added to compensate difference in 
            // symmetry of the sine table used for CW and CCW
			Phase = PhaseValues[(Sector + 3) % 6]+ PhaseOffsetCCW;
		}
		LastSector = Sector; // Update last sector
	}
	return;
}
/*********************************************************************
  Function:        void __attribute__((__interrupt__)) _PWM1Interrupt (void)
  PreCondition:    None.
 
  Input:           None.
  Output:          None.
  Side Effects:    None.
  Overview:        in this ISR the sinewave is generated. If the current motor
                   direction of rotation is different from the required 
                   direction then the motor is operated	in braking mode and 
                   step commutation is performed. Once both directions are 
                   equal then the sinewave is fed into the motor windings.
                   If PHASE_ADVANCE is defined, a value corresponding to the
                   multiplication of the actual speed * maximum phase advance
                   is added to the sine wave phase to produce the phase shift
  Note:            None.
********************************************************************/
void __attribute__((interrupt, no_auto_psv)) _PWM1Interrupt (void)
{

	IFS5bits.PWM1IF = 0;	// Clear interrupt flag
	
	if (Required_Direction == CW)
	{
		if (Current_Direction == CW)
			Phase-= PhaseInc;    // Increment Phase if CW to generate the 
                                  // sinewave only if both directions are equal
		// If Required_Direction is CW (forward) POSITIVE voltage is applied
		#ifdef PHASE_ADVANCE
		SVM(ControlOutput, Phase + PhaseAdvance);	// PhaseAdvance addition
													// produces the sinewave
													// phase shift
		#else
		SVM(ControlOutput, Phase);
		#endif
	}
	else
	{
		if (Current_Direction == CCW)
			Phase += PhaseInc;      // Decrement Phase if CCW to generate
									// the sinewave only if both 
									// directions are equal
		// If Required_Direction is CCW (reverse) NEGATIVE voltage is applied
		#ifdef PHASE_ADVANCE
		SVM(-(ControlOutput+1), Phase + PhaseAdvance);// PhaseAdvance addition
													  // produces the sinewave
													  // phase shift
		#else
		SVM(-(ControlOutput+1), Phase);
		#endif
	}
		#ifdef RTDM_DEMO
    /********************* DMCI Dynamic Data Views  ***************************/
	/********************** RECORDING MOTOR PHASE VALUES ***************/
	if(DMCIFlags.Recorder)
	{
		if(SnapShotDelayCnt++ == SnapShotDelay)
		{
			SnapShotDelayCnt = 0;
			*PtrRecBuffer1++ 	= SNAP1;
			*PtrRecBuffer2++	= SNAP2;
			*PtrRecBuffer3++	= SNAP3;
			*PtrRecBuffer4++	= SNAP4;
			
			if(PtrRecBuffer4 > RecBuffUpperLimit)
			{
				PtrRecBuffer1 = RecorderBuffer1;
				PtrRecBuffer2 = RecorderBuffer2;
		        PtrRecBuffer3 = RecorderBuffer3;
		        PtrRecBuffer4 = RecorderBuffer4;
		        DMCIFlags.Recorder = 0;
		    }   
		}
	}
	#endif


	return;
}
/*********************************************************************
  Function:        void __attribute__((__interrupt__)) _AD1Interrupt (void)
  PreCondition:    None.
 
  Input:           None.
  Output:          None.
  Side Effects:    None.
  Overview:        The ADC interrupt loads the reference speed (RefSpeed) with
                   the respective value of the POT. The value will be a signed
                   fractional value, so it doesn't need any scaling.
  Note:            None.
********************************************************************/
void __attribute__((interrupt, no_auto_psv)) _AD1Interrupt (void)
{

	IFS0bits.AD1IF = 0;		// Clear interrupt flag
	
	#ifdef RTDM_DEMO
		RefSpeed = SpeedReference;
	#else
		RefSpeed = ADC1BUF0; 	// Read POT value to set Reference Speed
	#endif

	return;
}
/*********************************************************************
  Function:        void ChargeBootstraps(void)
  PreCondition:    None.
 
  Input:           None.
  Output:          None.
  Side Effects:    None.
  Overview:        In the topology used, it is necessary to charge the 
                   bootstrap caps each time the motor is energized for the 
                   first time after an undetermined amount of time. 
                   ChargeBootstraps subroutine turns ON	the lower transistors
                   for 10 ms to ensure voltage on these caps, and then it 
                   transfers the control of the outputs to the PWM module.
  Note:            None.
********************************************************************/
void ChargeBootstraps(void)
{
	PDC1 = PHASE1 / 2;	// Initialize as 0 voltage
	PDC2 = PHASE2 / 2;	// Initialize as 0 voltage
	PDC3 = PHASE3 / 2;	// Initialize as 0 voltage
	
	IOCON1 = 0xC040;
	Delay(20);			// Adding this delay allows enough time for high-ESR-type C61 to recover	
	IOCON2 = 0xC040;
	Delay(20);			// Adding this delay allows enough time for high-ESR-type C61 to recover	
	IOCON3 = 0xC040;

	return;
}
/*********************************************************************

  Function:        void RunMotor(void)

  PreCondition:    None.
 
  Input:           None.
  Output:          None.
  Side Effects:    None.
  Overview:        Call this subroutine when first trying to run the motor and
                   the motor is previously stopped. RunMotor will charge 
                   bootstrap caps, will initialize application variables, and
                   will enable all ISRs.
  Note:            None.
********************************************************************/
void RunMotor(void)
{
	ChargeBootstraps();
	// init variables

	
	TMR1 = 0;			// Reset timer 1 for speed control
	TMR3 = 0;			// Reset timer 3 for speed measurement
	ActualCapture = MAXPERIOD; 	// Initialize captures for minimum speed 
								//(60 RPMs)
	PastCapture = 0;
	// Initialize direction with required direction
	// Remember that ADC is not stopped.
	HallValue = HALLA_BIT+2*HALLB_BIT+4*HALLC_BIT;// Read halls	
	LastSector = Sector = SectorTable[HallValue];	// Initialize Sector 
                                                    // variable

	// RefSpeed's sign will determine if the motor should be run at CW 
    // (+RefSpeed) or CCW (-RefSpeed) ONLY at start up, since when the motor 
    // has started, the required direction will be set by the control output
    // variable to be able to operate in the four quadrants
	if (RefSpeed < 0)
	{
		ControlOutput = 0;	// Initial output voltage
		Current_Direction = Required_Direction = CCW;
		Phase = PhaseValues[(Sector + 3) % 6]+PhaseOffsetCCW;
	}
	else
	{
		ControlOutput = 0;	// Initial output voltage
		Current_Direction = Required_Direction = CW;
		Phase = PhaseValues[(Sector) % 6] + PhaseOffsetCW;
	}
	MotorStalledCounter = 0;	// Reset motor stalled protection counter
	// Set initial Phase increment with minimum value. This will change if a 
    // costing operation is required by the application
	PhaseInc = __builtin_divud(PHASE_INC_CALC, MAXPERIOD);	
	// Clear all interrupts flags
	IFS0bits.T1IF = 0;		// Clear timer 1 flag
	IFS0bits.IC1IF = 0;		// Clear interrupt flag
	IFS0bits.IC2IF = 0;		// Clear interrupt flag
	IFS2bits.IC3IF = 0;		// Clear interrupt flag
	IFS5bits.PWM1IF = 0;	// Clear interrupt flag
	// enable all interrupts
	__asm__ volatile ("DISI #0x3FFF");
	IEC0bits.T1IE = 1;		// Enable interrupts for timer 1
	IEC0bits.IC1IE = 1;		// Enable interrupts on IC1
	IEC0bits.IC2IE = 1;		// Enable interrupts on IC2
	IEC2bits.IC3IE = 1;		// Enable interrupts on IC3
	IEC5bits.PWM1IE = 1;	// Enable PWM interrupts
    DISICNT = 0;
	Flags.MotorRunning = 1;	// Indicate that the motor is running
	return;
}
/*********************************************************************
  Function:        void StopMotor(void)
  PreCondition:    None.
 
  Input:           None.
  Output:          None.
  Side Effects:    None.
  Overview:        Call this subroutine whenever the user want to stop the 
                   motor. This subroutine will clear interrupts properly, and
                   will also turn OFF all PWM channels.
  Note:            None.
********************************************************************/
void StopMotor(void)
{
	IOCON1 = 0xC300;
	IOCON2 = 0xC300;
	IOCON3 = 0xC300;
	
	// disable all interrupts
	__asm__ volatile ("DISI #0x3FFF");
	IEC0bits.T1IE = 0;		// Disable interrupts for timer 1
	IEC0bits.IC1IE = 0;		// Disable interrupts on IC1
	IEC0bits.IC2IE = 0;		// Disable interrupts on IC2
	IEC2bits.IC3IE = 0;		// Disable interrupts on IC3
	IEC5bits.PWM1IE = 0;	// Disable PWM interrupts
    DISICNT = 0;
	Flags.MotorRunning = 0;	// Indicate that the motor has been stopped

	return;
}
/*********************************************************************
  Function:        void SpeedControl(void)
  PreCondition:    None.
 
  Input:           None.
  Output:          None.
  Side Effects:    None.
  Overview:        This subroutine implements a PID
  Note:            None.
********************************************************************/

void SpeedControl(void) {

        PIparms.qKp = P_SPEED_PI;
        PIparms.qKi = I_SPEED_PI;
        PIparms.qKc = C_SPEED_PI;
        PIparms.qOutMax = MAX_SPEED_PI;
        PIparms.qOutMin = - PIparms.qOutMax;
        
        PIparms.qInRef = RefSpeed/SPEED_REF_DIV;
        PIparms.qInMeas = MeasuredSpeed;
        
        
        CalcPI(&PIparms);
        ControlOutput = PIparms.qOut;

        #ifndef CLOSED_LOOP
                ControlOutput = RefSpeed;
        #endif
        // ControlOutput will determine the motor required direction
        if (ControlOutput < 0)
                Required_Direction = CCW;
        else
                Required_Direction = CW;
        return;
}
/*********************************************************************
  Function:        void ForceCommutation(void)
  PreCondition:    None.
 
  Input:           None.
  Output:          None.
  Side Effects:    None.
  Overview:        This function is called each time the motor doesn't 
                   generate	hall change interrupt, which means that the motor
                   running too slow or is stalled. If it is stalled, the motor
                   is stopped, but if it is only slow, this function is called
                   and forces a commutation based on the actual hall sensor 
                   position and the required direction of rotation.
  Note:            None.
********************************************************************/
void ForceCommutation(void)
{
	HallValue = HALLA_BIT+2*HALLB_BIT+4*HALLC_BIT;// Read halls		
	Sector = SectorTable[HallValue];	// Read sector based on halls
	if (Sector != -1)	// If the sector is invalid don't do anything
	{
		// Depending on the required direction, a new phase is fetched
		if (Required_Direction == CW)
		{
			// Motor is required to run forward, so read directly the table
			Phase = PhaseValues[(Sector) % 6] + PhaseOffsetCW;
		}
		else
		{
			// Motor is required to run reverse, so calculate new phase and 
            // add offset to compensate asymmetries
			Phase = PhaseValues[(Sector + 3) % 6]+ PhaseOffsetCCW;
		}
	}
	return;
}
/*---------------------------------------------------------------------
  Function Name: InitADC
  Description:   Initialize ADC module
  Inputs:        None
  Returns:       None
-----------------------------------------------------------------------*/
void InitADC( void )
{

	/* Signed Fractional */
	AD1CON1bits.FORM = 3;
	/* Internal Counter Ends Sampling and Starts Conversion */
	AD1CON1bits.SSRC = 0;
	AD1CON1bits.SSRCG = 1;
	/* Sampling begins immediately after last conversion */
	AD1CON1bits.ASAM = 1;
	/* Select 12-bit, 1 channel ADC operation */
	AD1CON1bits.AD12B = 1;
	
	/* No channel scan for CH0+, Use MUX A, SMPI = 1 per interrupt, Vref = AVdd/AVss */ 
	AD1CON2 = 0x0000;
	
	/* Set Samples and bit conversion time */
	AD1CON3 = 0x0304; 

	/* Disable DMA */
	AD1CON4 = 0x0000;

	/* No Channels to Scan */
	AD1CSSL = 0x0000;
	
	/* Channel select AN13 */
	AD1CHS0 = 13;
	
	/* Reset ADC interrupt flag */
	IFS0bits.AD1IF = 0;           

	/* Enable ADC interrupts, disable this interrupt if the DMA is enabled */	  
	IEC0bits.AD1IE = 1;       

	/* Turn on ADC module */
	AD1CON1bits.ADON = 1;          	
}
/*********************************************************************
  Function:        void InitMCPWM(void)
  PreCondition:    None.
 
  Input:           None.
  Output:          None.
  Side Effects:    None.
  Overview:        InitMCPWM, intializes the PWM as follows:
                   1. FPWM = 20000 hz
                   2. Complementary PWMs with center aligned
                   3. Set Duty Cycle to 0 for complementary, which is half 
                      the period
                   4. Set ADC to be triggered by PWM special trigger
                   5. Configure deadtime to be 2 us	
  Note:            None.
********************************************************************/
void InitMCPWM(void)
{

	PHASE1 = (FCY/FPWM - 1);
	PHASE2 = (FCY/FPWM - 1);
	PHASE3 = (FCY/FPWM - 1);

	IOCON1 = 0;
	IOCON2 = 0;
	IOCON3 = 0;

	DTR1 = 0x0000;	// 2 us of dead time
	DTR2 = 0x0000;	// 2 us of dead time
	DTR3 = 0x0000;	// 2 us of dead time

	ALTDTR1 = 2*ALTDTR_DIV2;	// 2 us of dead time		
	ALTDTR2 = 2*ALTDTR_DIV2;	// 2 us of dead time
	ALTDTR3 = 2*ALTDTR_DIV2;	// 2 us of dead time
	//Note: ALTDTR_DIV2 define in svm.c should be half of ALTDTRx


	PTCON2 = 0x0000;	// Divide by 1 to generate PWM

	PWMCON1 = 0x0604;	// Enable PWM output pins and configure them as 
	PWMCON2 = 0x0204;	// complementary mode
	PWMCON3 = 0x0204;

	PDC1 = PHASE1 / 2;	// Initialize as 0 voltage
	PDC2 = PHASE2 / 2;	// Initialize as 0 voltage
	PDC3 = PHASE3 / 2;	// Initialize as 0 voltage

	SEVTCMP = 1;	    // Enable triggering for ADC
	
	//fault enabled	
	FCLCON1 = 0x0005;
	FCLCON2 = 0x0005;
	FCLCON3 = 0x0005;
	
	PTCON = 0x8000;		// start PWM

	return;				 
}
/*********************************************************************
  Function:        void InitIC(void)
  PreCondition:    None.
 
  Input:           None.
  Output:          None.
  Side Effects:    None.
  Overview:        Configure Hall sensor inputs, on IC1,IC2,IC3 input captuers.
				   On IC2 the actual capture value is used for further period 
                   calculation
  Note:            None.
********************************************************************/
void InitIC(void)
{
	//Hall A -> IC1. Hall A is only used for commutation.
	//Hall B -> IC2. Hall B is used for Speed measurement and commutation.
	//Hall C -> IC3. Hall C is only used for commutation.

	// Init Input Capture 1
	IC1CON1 = 0x0001;	// Input capture every edge with interrupts and TMR3
	IC1CON2 = 0x0000;
	IFS0bits.IC1IF = 0;	// Clear interrupt flag
	// Init Input Capture 2
	IC2CON1 = 0x0001;	// Input capture every edge with interrupts and TMR3
    IC2CON2 = 0x0000;
	IFS0bits.IC2IF = 0;	// Clear interrupt flag
	// Init Input Capture 7
	IC3CON1 = 0x0001;	// Input capture every edge with interrupts and TMR3
	IC3CON2 = 0x0000;
	IFS2bits.IC3IF = 0;	// Clear interrupt flag
	return;
}
/*********************************************************************
  Function:        void InitTMR1(void)
  PreCondition:    None.
 
  Input:           None.
  Output:          None.
  Side Effects:    None.
  Overview:        Initialization of Timer 1 as a periodic interrupt each 1 ms
                   for speed control, motor stalled protection which includes:
                   forced commutation if the motor is too slow, or motor 
                   stopped if the motor is stalled.
  Note:            None.
********************************************************************/
void InitTMR1(void)
{
	T1CON = 0x0030;			// internal Tcy/256 clock
	TMR1 = 0;
	PR1 = 234;				// 1 ms interrupts for 60 MIPS
	T1CONbits.TON = 1;		// turn on timer 1 
	return;
}
/*********************************************************************
  Function:        void InitTMR3(void)
  PreCondition:    None.
 
  Input:           None.
  Output:          None.
  Side Effects:    None.
  Overview:        Initialization of Timer 3 as the timebase for the capture 
                   channels for calculating the period of the halls.
  Note:            None.
********************************************************************/
void InitTMR3(void)
{
	T3CON = 0x0030;			// internal Tcy/256 clock
	TMR3 = 0;
	PR3 = 0xFFFF;
	T3CONbits.TON = 1;		// turn on timer 3 
	return;
}
/*********************************************************************
  Function:        int main(void)
  PreCondition:    None.
 
  Input:           None.
  Output:          None.
  Side Effects:    None.
  Overview:        main function of the application. Peripherals are 
                   initialized, and then, depending on the motor status 
                   (running or stopped) and	if the push button is pressed, 
                   the motor is started or stopped.	All other operations and
                   state machines are performed with interrupts.
  Note:            None.
********************************************************************/
int main(void)
{
    //The settings below set up the oscillator and PLL for 70 MIPS as
    //follows:
    //            Crystal Frequency  * (DIVISOR+2)
    // Fcy =     ---------------------------------
    //              PLLPOST * (PRESCLR+2) * 4	
	// Crystal  = 8 MHz
	// Fosc		= 140 MHz
	// Fcy		= 70 MIPS

	PLLFBD =  68;		        // M=70
	CLKDIVbits.PLLPOST = 0;		// N1=2
	CLKDIVbits.PLLPRE = 0;		// N2=2
	__builtin_write_OSCCONH(0x03);
	__builtin_write_OSCCONL(0x01);

	while(OSCCONbits.COSC != 0b011);
	// Wait for PLL to lock
	while(OSCCONbits.LOCK != 1);

	CNPDBbits.CNPDB4 = 1;	// Weak pull up for FLT32
	
	CORCONbits.SATA = 1;
	CORCONbits.SATB = 1;
	CORCONbits.ACCSAT = 1;

	IOMap();		// Map the Peripheral Pin Select Functions
	InitADC();		// Initialize ADC to be signed fractional
	InitIC();		// Initialize Hall sensor inputs ISRs	
	InitTMR1();		// Initialize TMR1 for 1 ms periodic ISR
	InitTMR3();		// Initialize TMR3 for timebase of capture
	InitMCPWM();	// Initialize PWM @ 20 kHz, center aligned, 2 us of deadtime


	#ifdef RTDM_DEMO
    	RTDM_Start();  	// Configure the UART module used by RTDM
				   		// it also initializes the RTDM variables
	#endif

	for(;;)
	{
		#ifdef RTDM_DEMO

			RTDM_ProcessMsgs();
	
			if ((DMCIFlags.StartStop == 1) && (!Flags.MotorRunning))
			{
				RunMotor();	
			}
			else if ((DMCIFlags.StartStop == 0) && (Flags.MotorRunning))
			{
				StopMotor();
			}

		#else
			if ((SWITCH_S2) && (!Flags.MotorRunning))
			{
				Delay(200);
				if(SWITCH_S2)
				{
					RunMotor();	    // Run motor if button is pressed and motor is stopped
					while(SWITCH_S2);
				}
			}
			else if ((SWITCH_S2) && (Flags.MotorRunning))
			{
				Delay(200);
				if(SWITCH_S2)
				{
					StopMotor();    // Stop motor if button is pressed and motor is running 
					while(SWITCH_S2);
				}
			}
		#endif
	}
	return 0;
}


