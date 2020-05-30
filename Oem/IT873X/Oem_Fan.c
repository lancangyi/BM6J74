/*-----------------------------------------------------------------------------
 * Filename: OEM_FAN.C
 * Function: OEM FAN Control
 *
 * Copyright (c) 2009-2012, ITE Tech. Inc. All Rights Reserved.
 *---------------------------------------------------------------------------*/
 
#include "CORE_INC.H"
#include "OEM_INC.H"


//-----------------------------------------------------------------------------
/*****************************************************************************/
/* PWM/TACHX MODULE **********************************************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
// Calculation Fan Tachometer to Fan Speed (R.P.M)
// Fan Speed (R.P.M)=60/(1/fs sec * {FnTMRR,FnTLRR) * P )
//-----------------------------------------------------------------------------
WORD GetFanRPM(BYTE FnTMRR,BYTE FnTLRR)
{
	WORD	FanRPMSpd, FanRPMDiv;
	WORD	FnTWRR; 

	if( (FnTMRR == 0xFF)&&(FnTLRR == 0xFF) )
		return 0;


	FnTWRR = FnTMRR*0x100+FnTLRR;
	

	FanRPMSpd = 675000 / FnTWRR;

	return FanRPMSpd;

}

