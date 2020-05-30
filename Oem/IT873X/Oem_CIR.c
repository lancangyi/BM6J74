/*-----------------------------------------------------------------------------
 * Filename: OEM_CIR.C
 * Function: OEM CIR HANDLE
 *
 * Copyright (c) 2006-2009, ITE Tech. Inc. All Rights Reserved.
 *---------------------------------------------------------------------------*/
#include "CORE_INC.H"
#include "OEM_INC.H"

#define RXEN_MASK		0x20
#define RXACT_MASK		0x08
#define RXFBC_MASK		0x3F

const BYTE code RC6PowerKey[]={	0x95,0x55,0xA5,0xF5 }; 	// RC6 power key

//----------------------------------------------------------------------------
// The function of CIR wake up system 
//----------------------------------------------------------------------------


//;;;BJ	,Start OEM>>> T014
void Hook_CIRWakeUp(void)
{
	BYTE index;
	BYTE cirdata;
	BYTE vector ;
	BYTE bytecount;
	BYTE i_cnt ;

	vector = CIR_IIR ;

	switch (vector) 
	{
		case 0x2 : 	

			CIR_RCR &= ~(RXEN_MASK);
			bClearCirFIFO();
			CIR_RCR |= ( (RXEN_MASK) | (RXACT_MASK) ) ;
			//RamDebug(0xCA);

			break;
			
		case 0x4 :
			
			bytecount = CIR_RSR & (RXFBC_MASK)  ;
			
			for( i_cnt = 0 ; i_cnt < bytecount; i_cnt++ )
			{
				CIR_Buffer[i_cnt] = CIR_DR ;
				//RamDebug(cirdata);
			}
	
			CIR_RCR  &= ~(RXEN_MASK);
			bClearCirFIFO();
			CIR_RCR |= ( (RXEN_MASK) | (RXACT_MASK) ) ;


			RamDebug(0x8E);

			break;			
			
		case 0x6 :	

			CIR_RCR &= ~(RXEN_MASK);
			bClearCirFIFO();
			CIR_RCR |= ( (RXEN_MASK) | (RXACT_MASK) ) ;
			RamDebug(0xCB);

			break;
			
		default :
			break;

	}
	

	SET_MASK(IER1, BIT7);		// Enable INT15 CIR Interrupt	
}

//;;;BJ	,End OEM<<< T014

//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// The function of CIR Initialization
//----------------------------------------------------------------------------
//BJ	,Start OEM+ T014	20111213
void Init_CIR(void)
{ 	

	Index_07H = 0x07 ; 
	if( SysPowState != _SYSTEM_S0 )
	{
		SET_BIT(Index_23H, 0);
	}
	Index_07H = 0x0A ; 
	Index_30H = 0x01 ;

	SET_MASK(IELMR1, BIT7);		// CIR Interrupt must use Edge-Trig
	SET_MASK(IER1, BIT7);		// Enable INT15 CIR Interrupt
	ISR1 = Int_CIR;		// Clear INT15 pending Status

	EX1 = 1 ; 
	EA = 1 ;
	
	SET_BIT(CIR_IER, 5);

	CIR_IER = 0x00 ;
	
	SET_BIT(CIR_IER, 4);
	CIR_BDHR	=	0x00; 
	CIR_BDLR	=	0x33;
	
	CLR_BIT(CIR_IER, 4);

	CIR_RCR = 0x01;

	bClearCirFIFO();		  		// Clear FIFO
	SET_BIT(CIR_RCR, 5);

	CIR_IER |= 0x0A ;

	SET_BIT(CIR_RCR, 1);

	CLR_BIT(CIR_TCR1, 6);
	SET_BIT(CIR_TCR1, 5);


	//CIR_Enable = 0x01 ;
	
}
//BJ	,End OEM+ T014	
//----------------------------------------------------------------------------
// The function of CIR module reset
//----------------------------------------------------------------------------
void Reset_CIR(void)
{
//	SET_MASK(RSTC2, BIT1);		// Reset CIR module
	CLEAR_MASK(IER1, BIT7);		// Disable INT15 CIR Interrupt
	ISR1 = Int_CIR;		// Clear INT15 pending Status		     
}
//BJ	,Start OEM+ T012
void EN_EC_CIR(void)
{
	Init_CIR() ;
	
	SET_MASK(IER1, BIT7);		// Set INT15 pending Status		     
	ISR1 = Int_CIR;		// Clear INT15 pending Status		     
}
//BJ	,End OEM+ T012
//----------------------------------------------------------------------------
// The function of clearing CIR FIFO
//----------------------------------------------------------------------------
void bClearCirFIFO(void)
{
	CIR_TCR1 = BIT7;			// Write 1 for Clearing FIFO data
	_nop_();
	while(IsFlag1(CIR_TCR1, BIT7))	    // Wait FIFO Clear Done
	{
		;					
	}
}


//----------------------------------------------------------------------------
// The function of clearing CIR
//----------------------------------------------------------------------------
void ClearCIR(void) 
{
	CLEAR_MASK(CIR_RCR, BIT7);    // RX Disable   
 	bClearCirFIFO();		  	// Clear FIFO
 	SET_MASK(CIR_RCR, BIT7);		// RX enable 
} 

//----------------------------------------------------------------------------
// The function of CIR Interrupt service routine
//----------------------------------------------------------------------------
void Service_CIR(void)
{

    Hook_CIRWakeUp();

}


void Clear_CIR_Buffer(void)
{
	BYTE i_cnt ;
	//clear CIR buffer
	for( i_cnt = 0 ; i_cnt < 0x11; i_cnt++ )
	{
		CIR_Buffer[i_cnt] = 0x00;
	}

}

//=============================================================================


