/*-----------------------------------------------------------------------------
 * TITLE: CORE_IRQ.C - Interrupt Service Routines (ISR).
 *
 * The Interrupt Service Routines (ISR).  The actual interrupt functions are
 * implemented in the "CHIP_IRQ.C".
 *
 * Copyright (c) 1983-2007, Insyde Software Corporation. All Rights Reserved.
 *
 * You may not reproduce, distribute, publish, display, perform, modify, adapt,
 * transmit, broadcast, present, recite, release, license or otherwise exploit
 * any part of this publication in any form, by any means, without the prior
 * written permission of Insyde Software Corporation.
 *---------------------------------------------------------------------------*/
 
#include "Core_Inc.h"
#include "Oem_Inc.h"

//----------------------------------------------------------------------------
// RomString
//----------------------------------------------------------------------------
const unsigned char code RomString[] =  "IT873X Codebase V1.0 - Copyright ITE Tech. Inc.";

//----------------------------------------------------------------------------
// KBC Input Buffer Full Interrupt
//----------------------------------------------------------------------------
void IRQ_INT24_KBCIBF(void) using 2
{
	#if SUPPORT_SWKBC
	CLEAR_MASK(IER3,Int_KBCIBF);
	ISR3 = Int_KBCIBF;
	F_Service_001 = 1;       
	#endif
}

//----------------------------------------------------------------------------
// Port 62/66, 68/6C input buffer full interrupt routine
//----------------------------------------------------------------------------
void Irq_Ibf2(void) using 2
{

	F_Service_000 = 1;
	
	CLEAR_MASK(IER3,Int_PMCIBF);
	ISR3 = Int_PMCIBF;

}

void Irq_Ibf3(void) using 2
{

	F_Service_003 = 1;

	CLEAR_MASK(IER3,Int_PMC2IBF);
	ISR3 = Int_PMC2IBF;

	
}

//----------------------------------------------------------------------------
// ADC interrupt routine
//----------------------------------------------------------------------------
void Irq_ADC(void)  using 2	 
{

}

//----------------------------------------------------------------------------
// SMBus0 interrupt routine
//----------------------------------------------------------------------------
void Irq_SMB0(void) using 2
{
	CLEAR_MASK(IER1,Int_SMBUS0);
	ISR1 = Int_SMBUS0;
	F_Service_SMBus1=SMBus_NeedService;

	F_Service_007 = 1;

}

//----------------------------------------------------------------------------
// SMBus1 interrupt routine
//----------------------------------------------------------------------------
void Irq_SMB1(void) using 2
{
	CLEAR_MASK(IER1,Int_SMBUS1);
	ISR1 = Int_SMBUS1;
	F_Service_SMBus2=SMBus_NeedService;

	F_Service_007 = 1;
}

//----------------------------------------------------------------------------
// SMBus1 interrupt routine
//----------------------------------------------------------------------------
void Irq_SMB2(void) using 2
{
	CLEAR_MASK(IER2,Int_SMBUS2);
	ISR2 = Int_SMBUS2;
	F_Service_SMBus3=SMBus_NeedService;	

	F_Service_007 = 1;
}

//----------------------------------------------------------------------------
// CIR interrupt routine
//----------------------------------------------------------------------------
void Irq_CIR(void) using 2
{

#if Support_EC_CIR
	CLEAR_MASK(IER1, Int_CIR);		// Disable INT15 CIR Interrupt
	ISR1 = Int_CIR;		// Clear INT15 pending Status
	F_Service_004 = 1;
#endif

}

//----------------------------------------------------------------------------
// Null function
//----------------------------------------------------------------------------
void IrqNull(void) using 2
{

}

/* ----------------------------------------------------------------------------
 * FUNCTION:   IrqUART1
 * ISR for INT38 Interrupt for Serial Port - UART Process
 * ------------------------------------------------------------------------- */

void IrqUART1(void) using 2
{
	#if USE_UART1
	CLEAR_MASK(IER4,Int_UART1);				// Disable INT38
	ISR4 = Int_UART1;				// Clear INT38 interrupt flag
	SET_MASK(IER4,Int_UART1);				// Enable INT38

	F_Service_009 = 1;		//UART1
	#endif

}

/* ----------------------------------------------------------------------------
 * FUNCTION:   IrqUART2
 * ISR for INT39 Interrupt for Serial Port - UART Process
 * ------------------------------------------------------------------------- */

void IrqUART2(void) using 2
{
	#if USE_UART2
	CLEAR_MASK(IER4,Int_UART2);				// Disable INT39
	ISR4 = Int_UART2;				// Clear INT39 interrupt flag
	SET_MASK(IER4,Int_UART2);				// Enable INT39

	F_Service_008 = 1;		//UART2
	#endif

}


//----------------------------------------------------------------------------
// Irq_Anykey - Direct Keyboard Scan key press interrupt handler.
// Disable further key interrupts and post key service request.
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// FUNCTION:   Irq_HPSI
// ISR for INT59 WUC Interrupt  for HSPI Process
//----------------------------------------------------------------------------
#ifdef HSPI
void Irq_HSPI(void) using 2
{
    BackUpTR1 = TR1;            // store TR1 status
    TR1 = 0;                    // Disable timer1
	CLEAR_MASK(IER7,BIT3);      // Disable HSPI interrup
    HSPI_RamCode();
    SET_MASK(IER7,BIT3);        // Enable HSPI interrupt
    TR1 = BackUpTR1;            // Re store TR1 status
}
#endif

//----------------------------------------------------------------------------
// External Timer1 INT30
//----------------------------------------------------------------------------
void Irq_ExtTimer1(void)  using 2	 
{
	CLR_BIT(IER3, 6);	//disable interrupt
	ISR3 = Int_EXTimer;		//clear INT30 ISR
	Set_ExtTimer1();
		
}


//----------------------------------------------------------------------------
// FUNCTION:   Isr_Int0
// ISR for INT0 (Key Scan Interrupt).
//----------------------------------------------------------------------------
void Isr_Int0(void) interrupt 0 using 2
{
	#if USE_LRESET_INT
	BYTE Temp;

	EX0 = 0;
	Temp = INT0ST;
		//Something you want to do
		#if PECI_Busy_Workaround
		IF_SELECT_REG = 0x44; //For IT8738
		#endif
	EX0 = 1;
	#endif
	
}

//----------------------------------------------------------------------------
// Isr_Tmr0
// ISR for TF0 (Timer 0 Interrupt).  Timer 0 is the 1mS Timer (Timer A).
//----------------------------------------------------------------------------
/* ----------------------------------------------------------------------------
 * FUNCTION: Irq_Timer_A - Handle Timer A interrupts.
 *
 * Timer A has a time base of 1 mS.
 *
 * Input: On entry, "TIMER Timer_A" has the event(s) to handle. Valid Events:
 *     TMR_SCAN   -
 *     TMR_GENTMO - This timer is a timer that is used for timeout detection
 *                  of serial data transmissions to/from the auxiliary
 *                  keyboard/pointing devices.
 * ------------------------------------------------------------------------- */
void Isr_Tmr0(void) interrupt 1 using 2
{
	#if SUPPORT_Hook_1ms_Timer
	Load_Timer_A_1ms();	// Request 1 ms timer service.
	F_Service_002 = 1;
	#else
	Load_Timer_A();
	F_Service_005 = 1;   // Request 5 ms timer service.
    	#endif
}


/* ----------------------------------------------------------------------------
 * FUNCTION:   Isr_Int1
 * ISR for INT1 (Interrupt Source A and B Interrupts).
 *
 * Interrupt Source A:  
 * ------------------------------------------------------------------------- */
const FUNCT_PTR_V_V code IRQ_Service[] = 
{
    IrqNull,            //   INT0	Reserved
    IrqNull,            //   INT1	WUC interrupt WUI0	
    IrqNull,            //   INT2	KBC output buffer empty interrupt 
    IrqNull,            //   INT3	PMC output buffer empty interrupt 
    IrqNull,            //   INT4	
    IrqNull,            //   INT5	WUC interrupt (WU10 ~ WU15)(WU40 ~ WU47)	
    IrqNull,            //   INT6	WUC interrupt WUI3
    IrqNull,            //   INT7	PWM interrupt 
    
    Irq_ADC,    		//   INT8  	ADC Interrupt 	
    Irq_SMB0,      		//   INT9  	SMB0 Interrupt 
    Irq_SMB1,       	//   INT10 	SMB1 Interrupt
    IrqNull,     	//   INT11 	Key matrix scan Int
    IrqNull,            //   INT12	WUC interrupt SWUC wake up
    IrqNull,            //   INT13	WUC interrupt KSI wake-up (WU30 ~ WU37)
    IrqNull,            //   INT14	WUC interrupt Power switch
//    IrqNull,            //   INT15	WUC interrupt Power switch
    Irq_CIR,         	//   INT15 	CIR interrupt 
    
    Irq_SMB2,       	//   INT16	SMB2 Interrupt
    IrqNull,            //   INT17	WUC Interrupt WUI4
    IrqNull,    	//   INT18 	PS2 P2 Interrupt
    IrqNull,     	//   INT19 	PS2 P1 Interrupt
    IrqNull,   	//   INT20 	PS2 P0 Interrupt
    IrqNull,            //   INT21	WUC Interrupt WUI2
    IrqNull,            //   INT22
    IrqNull,            //   INT23
    
    IRQ_INT24_KBCIBF,       	//   INT24 	KBC input buffer empty interrupt 
    Irq_Ibf2,       	//   INT25 	PMC input buffer empty interrupt 
    IrqNull,            //   INT26
    Irq_Ibf3,            //   INT27
    IrqNull,            //   INT28
    IrqNull,            //   INT29
    //IrqNull,            //   INT30	External timer interrupt 
    Irq_ExtTimer1, //   INT30	External timer interrupt 
    IrqNull,            //   INT31	WUC	interrupt WUI1
    
    IrqNull,       		//   INT32 	
    IrqNull,       		//   INT33 	
    IrqNull,            //   INT34
    IrqNull,            //   INT35
    IrqNull,            //   INT36
    IrqNull,            //   INT37
    IrqUART1,            //   INT38	
    IrqUART2,            //   INT39
    
    IrqNull,       		//   INT40 	
    IrqNull,       		//   INT41 	
    IrqNull,            //   INT42
    IrqNull,            //   INT43
    IrqNull,            //   INT44
    IrqNull,            //   INT45
    IrqNull,            //   INT46	
    IrqNull,            //   INT47	
    IrqNull,       	    //   INT48	 	
    IrqNull,       		//   INT49 	
    IrqNull,            //   INT50
    IrqNull,            //   INT51
    IrqNull,            //   INT52
    IrqNull,            //   INT53
    IrqNull,            //   INT54	
    IrqNull,            //   INT55    

    IrqNull,       		//   INT56 	
    IrqNull,            //   INT57
    IrqNull,            //   INT58
    IrqNull,            //   INT59   
    IrqNull,            //   INT60
    IrqNull,            //   INT61	
    IrqNull,            //   INT62   
    IrqNull,            //   INT63  

    IrqNull,       		//   INT64 	
    IrqNull,       		//   INT65 	
    IrqNull,            //   INT66
    IrqNull,           //   INT67
    IrqNull,            //   INT68
    IrqNull,            //   INT69
    IrqNull,            //   INT70	
    IrqNull,            //   INT71	
    
    IrqNull,       		//   INT72	
    IrqNull,       		//   INT73 	
    IrqNull,            //   INT74
    IrqNull,           //   INT75
    IrqNull,            //   INT76
    IrqNull,            //   INT77
    IrqNull,            //   INT78	
    IrqNull,            //   INT79	

};
							
void Isr_Int1 (void) interrupt 2 using 2
{

	if(IVECT_BACKUP != IVECT )
	{
		IVECT_BACKUP = IVECT;
		return;
	}


	if(IVECT < 0x60 )
	{
		(IRQ_Service[(IVECT-0x10)&0x7F])();   // Dispatch to service handler.
	}
	else
	{
		IrqNull();
	}


	IVECT_BACKUP = 0;

} 
    
/* ----------------------------------------------------------------------------
 * FUNCTION:   Isr_Tmr1
 * ISR for TF1 (Timer 1 Interrupt).  Timer 1 is the 600uS Timer (Timer B).
 * ------------------------------------------------------------------------- */
void Isr_Tmr1(void) interrupt 3 using 2
{

}

/* ----------------------------------------------------------------------------
 * FUNCTION:   Isr_UART
 * ISR for TI or RI (UART Interrupt).
 * ------------------------------------------------------------------------- */
void Isr_UART(void) interrupt 4 using 2
{

}


/* ----------------------------------------------------------------------------
 * FUNCTION:   Isr_Tmr2
 * ISR for TF2 or EXF2 (Timer 2 Interrupt).
 * ------------------------------------------------------------------------- */
void Isr_Tmr2(void) interrupt 5 using 2
{

}

//------------------------------------------------------------------------------
// The function of disable all interrupts
//------------------------------------------------------------------------------
void DisableAllInterrupt(void)
{
  	EA = 0;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
}

//------------------------------------------------------------------------------
// The function of enable all interrupts
//------------------------------------------------------------------------------
void EnableAllInterrupt(void)
{
	EX1 = 1 ;
	#if	USE_LRESET_INT
		IT0 = 1;
		EX0 = 1;
		PFAILR= 0x04;
	#endif
  	EA = 1;
}
