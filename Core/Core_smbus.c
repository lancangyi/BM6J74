/*-----------------------------------------------------------------------------
 * Filename: CORE_SMBUS.C
 * Function: System Management SMBus Protocol drivers.
 *
 * Copyright (c) 2006-2009, ITE Tech. Inc. All Rights Reserved.
 *---------------------------------------------------------------------------*/
#include "CORE_INC.H"
#include "OEM_INC.H"

/*-----------------------------------------------------------------------------
 * Local Parameter Definition
 *---------------------------------------------------------------------------*/
#define SUPPORT_SMBUS_EEPROM        0

//=============================================================================
// Channel: [SMBusChA] [SMBusChB] [SMBusChC] [SMBusChD]
// Protocol:[SMBusWQ]  -Write Quick command [SMBusRQ]  -Read Quick command
//          [SMBusSBC] -Send Byte command   [SMBusRBC] -Receive Byte command
//          [SMBusWB]  -Write byte command  [SMBusRB]  -Read byte command
//          [SMBusWW]  -Write word command  [SMBusRW]  -Read word command
//          [SMBusWBK] -Write block command [SMBusRBK] -Read block command
//
//=============================================================================


//=============================================================================
//Port V14.1 SMB
const sSMBus code asSMBus[]=
{
	{ &HOCTL_A, &TRASLA_A, &HOCMD_A, &HOSTA_A, &D0REG_A, &D1REG_A,	&HOBDB_A,	&IER1,	&ISR1,  Int_SMBUS0,   &PECERC_A},
	{ &HOCTL_B, &TRASLA_B, &HOCMD_B, &HOSTA_B, &D0REG_B, &D1REG_B,	&HOBDB_B,	&IER1,	&ISR1,  Int_SMBUS1,   &PECERC_B},
	{ &HOCTL_C, &TRASLA_C, &HOCMD_C, &HOSTA_C, &D0REG_C, &D1REG_C,	&HOBDB_C,	&IER2,	&ISR2,	Int_SMBUS2,   &PECERC_C},
};


const sResetSMBusS code asResetSMBusS[]=
{
	{ &HOSTA_A, &HOCTL2_A, &SMBPCTL_A,  &GPIO_8x,	(BIT5+BIT6),   &SMBus1RecoverCunt },
	{ &HOSTA_B, &HOCTL2_B, &SMBPCTL_B,  &GPIO_1x,	(BIT0+BIT0),   &SMBus2RecoverCunt },	//GPIO Reg, no use
	{ &HOSTA_C, &HOCTL2_C, &SMBPCTL_C,   &GPIO_4x,	(BIT6+BIT7),   &SMBus3RecoverCunt }
}; 

//-----------------------------------------------------------------------------
//*****************************************************************************
// SMBus Read/write byte or word function
//
// Channel: [SMBusChA] [SMBusChB] [SMBusChC] [SMBusChD]
// Protocol:[SMBusWB]0x88-Write byte command [SMBusRB]0x08-Read byte command
//          [SMBusWW]0x8C-Write word command [SMBusRW]0x0C-Read word command
//
// Note: bit7 is set for PEC_ENABLE
// Addr:    device address
// Comd:    access command
// *Var:    Point to data Low Byte and *Var++ is high High Byte
// Return:  A byte in SMBUS_STATUS with [TRUE]:Ok. [FALSE] Failed.
//*****************************************************************************
//-----------------------------------------------------------------------------


//=============================================================
//
//
//V14 core_smbus
//=============================================================
//----------------------------------------------------------------------------
// 	
//----------------------------------------------------------------------------
void DelayInact(void) 
{
    BYTE index;
    BYTE counter;
   for(index=0;index<200;index++)
   {
        counter++;
   }
}

//----------------------------------------------------------------------------
// The function of reseting SMbus 	
//----------------------------------------------------------------------------
void ResetSMBus(BYTE Channel)
{

	SET_MASK(*asSMBus[Channel].SMBusCTL,HOCTL_KILL);
	CLEAR_MASK(*asSMBus[Channel].SMBusCTL,HOCTL_KILL);
	RSTC3=0x06;					            // Reset all SMBus module
	*asResetSMBusS[Channel].SMBusSTA = 0xFE;	// clear bits

	if( Channel == SMBusChA )
	{
		//Set ChannelA	to GPIO
		Index_07H = 0x19;	// LDN 19h for SMBus configurations
	 	Index_30H = 0x01;	// Activation
	 	CLR_BIT(Index_76H, 1);	//Disable	SMBUS channel A	CLK0/DAT0
	 	
		DelayInact();

		Index_07H = 0x07;
		//GP85
		SET_BIT(GPIO_8x, 5);	//Set GP85	Set High
		SET_BIT(Index_CFH, 5);	//Set GP85	OUTPUT
		//GP86
		SET_BIT(GPIO_8x, 6);	//Set GP86	Set High
		SET_BIT(Index_CFH, 6);	//Set GP86	OUTPUT

		DelayInact();

		Index_07H = 0x19;	// LDN 19h for SMBus configurations
	 	Index_30H = 0x01;	// Activation
	 	SET_BIT(Index_76H, 1);	//Enable	SMBUS channel A	CLK0/DAT0

	}
	else if( Channel == SMBusChC )
	{
		//Set ChannelC	to GPIO
		Index_07H = 0x19;	// LDN 19h for SMBus configurations
	 	Index_30H = 0x01;	// Activation
	 	CLR_BIT(Index_76H, 0);	//Disable	SMBUS channel C	CLK2/DAT2
	 	
		DelayInact();


		Index_07H = 0x07;
		//GP46
		SET_BIT(Index_C3H, 6);	//Set GP46	simple IO function
		SET_BIT(Index_CBH, 6);	//Set GP46	OUTPUT
		SET_BIT(GPIO_4x, 6);	//Set GP46	Set High
		SET_BIT(Index_28H, 6);	//Set GP46	

		//GP47
		SET_BIT(Index_C3H, 7);	//Set GP47	simple IO function
		SET_BIT(Index_CBH, 7);	//Set GP47	OUTPUT
		SET_BIT(GPIO_4x, 7);	//Set GP47	Set High
		SET_BIT(Index_28H, 7);	//Set GP47	
				

		DelayInact();


		Index_07H = 0x07;
		//GP46
		CLR_BIT(Index_C3H, 6);	//Set GP46	simple IO function
		CLR_BIT(Index_28H, 6);	//Set GP46	

		//GP47
		CLR_BIT(Index_C3H, 7);	//Set GP47	simple IO function
		CLR_BIT(Index_28H, 7);	//Set GP47	



		Index_07H = 0x19;	// LDN 19h for SMBus configurations
	 	Index_30H = 0x01;	// Activation
	 	SET_BIT(Index_76H, 1);	//Enable	SMBUS channel A	CLK2/DAT2

	}
 	
	*asResetSMBusS[Channel].SMBusCTL2 = 0x02;
	*asResetSMBusS[Channel].SMBusPinCTL = 0x03;
	DelayInact();
	*asResetSMBusS[Channel].SMBusPinCTL = 0x07;
	*asResetSMBusS[Channel].SMBusCTL2 = 0x01;

	#if SMBusServiceCenterFunc
	*asSSC[Channel].inusing=0x00;
	CLEAR_MASK(*asSMBus[Channel].SMBusIER, asSMBus[Channel].IERFlag);
	*asSMBus[Channel].SMBusISR = asSMBus[Channel].IERFlag;
	*asSSC[Channel].serviceflag=0x00;

	
	if(DB_SMBusAck1==ACK_Start)     // For SMBus utility
	{
		DB_SMBusAddr=0x00;
		if(Channel==0x00)
		{
		    DB_SMBusFlag1=0x00;		
		}
		else if(Channel==0x01)
		{
		    DB_SMBusFlag2=0x00;
		}
		else if(Channel==0x02)
		{
		    DB_SMBusFlag3=0x00;	
		}				
				
		DB_SMBusAck1 = ACK_Error;   // For SMBus utility error ACK.
	}
	#endif
}



//----------------------------------------------------------------------------
// V14.1 SMbus read byte/word and write byte/word function	
//----------------------------------------------------------------------------
BYTE bRWSMBus(BYTE Channel,BYTE Protocol,BYTE Addr,BYTE Comd,XBYTE *Var,BYTE PECSupport)
{	
	BYTE counter;
	BYTE error;
	BYTE status;
	BYTE resutl;

	if(CheckSMBusInterfaceCanbeUse(Channel, SMBus_AccessType_Fucn)==SMBus_CanNotUse)
	{
		resutl = FALSE;                             // SMBus interface can't be used.
	}
	else
	{
		error = 0xEE;                               // Pre-set error
		resutl = FALSE;                             // Pre-set result is fail
    
		SMBCRC8_A=0x00;                             // Clear CRC variable

		if (Protocol&0x80)	                        // Write byte function
		{	
			if(PECSupport)    
			{   
				CalcCRC8(Addr);                     // To calculate crc8
			}
			*asSMBus[Channel].SMBusADR = Addr;      // set address with writing bit
			
			if(PECSupport)    
			{   
				CalcCRC8(Comd);                     // To calculate crc8
			}
			*asSMBus[Channel].SMBusCMD=Comd;	    // Set command
			Protocol&=(~0x80);
			if(PECSupport)    
			{   
				CalcCRC8(*Var);                     // To calculate crc8
			}
			*asSMBus[Channel].SMBusData0 = *Var;    // set data1
			
			if(Protocol==SMbusRW)		            // write word function
			{
				if(PECSupport)    
				{   
					CalcCRC8(*(Var+0x01));          // To calculate crc8
				}
				*asSMBus[Channel].SMBusData1 = *(Var+0x01);
			}						                // set data2
		}	
		else 						                // Read function
		{	
			*asSMBus[Channel].SMBusADR=Addr|0x01;	
			*asSMBus[Channel].SMBusCMD=Comd;	    // Set command
		}							                // set address with reading bit

		*asSMBus[Channel].SMBusSTA=0xFE;		    // clear bits
		if(PECSupport)
		{
			*asSMBus[Channel].SMBusPEC=SMBCRC8_A;
			*asSMBus[Channel].SMBusCTL=(Protocol|HOCTL_SRT|HOCTL_PEC_EN);   // Start transaction
		}
		else
		{
			*asSMBus[Channel].SMBusCTL=(Protocol|HOCTL_SRT);	// Start transaction
		}

		TR1 = 0;			                        // disable timer1
		ET1 = 0;                  	                // Disable timer1 interrupt
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		TH1 = T_Timer_26ms>>8;                        // Set timer1 counter 26ms
		TL1 = T_Timer_26ms;                           // Set timer1 counter 26ms
		TF1 = 0;                  	                // Clear overflow flag
		TR1 = 1;                 	                // Enable timer1

		while (!TF1)
		{
			status = *asSMBus[Channel].SMBusSTA;    // Read SMBus Host Status
			if(IS_MASK_SET(status, (HOSTA_FINTR+HOSTA_DVER+HOSTA_BSER+HOSTA_FAIL+HOSTA_NACK+HOSTA_TMOE )))
			{
				TR1=0;
				TF1=0;
				ET1=1;                  	        // Enable timer1 interrupt
				break;
			}
		}
	
		if(TF1)                                     // 26ms time-out and no any status bit is set.
		{
			TR1=0;
			TF1=0;
			ET1=1;                                  // Enable timer1 interrupt
			ResetSMBus(Channel);
			error = 0xEE;
		}
		else
		{
			if(IS_MASK_SET(status, (HOSTA_DVER+HOSTA_BSER+HOSTA_FAIL+HOSTA_NACK+HOSTA_TMOE)))
			{
				if(IS_MASK_SET(status, (HOSTA_BSER+HOSTA_FAIL)))
				{
					ResetSMBus(Channel);
				}
				error = 0xEE;
			}
			else                                    // Only Finish Interrupt bit is set.
			{
				error = 0x00;
			}
		}
	                  	                    
		if(error == 0xEE)                           // Fail
		{
			resutl = FALSE;
		}
		else                                        // OK
		{
			if ((*asSMBus[Channel].SMBusADR & 0x01 != 0x00)) 
			{
				*Var = *asSMBus[Channel].SMBusData0;    // read data1
				if(Protocol==SMbusRW)
				{
					*(Var+0x01) = *asSMBus[Channel].SMBusData1;
				}							            // read data2
			}
			resutl = TRUE;
		}

		*asSMBus[Channel].SMBusSTA=0xFE;	            // clear bits
	}

	return(resutl);
}


//----------------------------------------------------------------------------
// V14.1 Read SMbus block function	
//----------------------------------------------------------------------------
BYTE bRSMBusBlock(BYTE Channel,BYTE Protocol,BYTE Addr,BYTE Comd,XBYTE *Var)
{
	BYTE ack;
	BYTE bcount;
	BYTE status;

	if(CheckSMBusInterfaceCanbeUse(Channel, SMBus_AccessType_Fucn)==SMBus_CanNotUse)
	{
		ack = FALSE;                            // SMBus interface can't be used.
	}
	else
	{
		ack = FALSE;					        // pr-set flag
		bcount = 0x00;			                // clear byte counter
	
		*asSMBus[Channel].SMBusADR=Addr|0x01;   // set address with reading bit	
		*asSMBus[Channel].SMBusCMD=Comd;	    // Set command
		*asSMBus[Channel].SMBusSTA=0xFE;	    // clear bits
		*asSMBus[Channel].SMBusCTL=(Protocol|HOCTL_SRT);    // Start transaction

		TR1 = 0;			                    // disable timer1
		ET1 = 0;                  	            // Disable timer1 interrupt
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		TH1 = T_Timer_26ms>>8;                    // Set timer1 counter 26ms
		TL1 = T_Timer_26ms;                       // Set timer1 counter 26ms
		TF1 = 0;                  	            // Clear overflow flag
		TR1 = 1;                 	            // Enable timer1

		while(!TF1)                             // Not time out
		{
			status = *asSMBus[Channel].SMBusSTA;    // Read SMBus Host Status
			if(IS_MASK_SET(status, (HOSTA_BDS+HOSTA_DVER+HOSTA_BSER+HOSTA_FAIL+HOSTA_NACK+HOSTA_TMOE )))
			{
				if(IS_MASK_SET(status, (HOSTA_DVER+HOSTA_BSER+HOSTA_FAIL+HOSTA_NACK+HOSTA_TMOE)))
				{
					if(IS_MASK_SET(status, (HOSTA_BSER+HOSTA_FAIL)))
					{
						ResetSMBus(Channel);
					}
					TR1 = 0;			        // disable timer1
					TF1 = 0;			        // clear overflow flag
					ET1 = 1;			        // Enable timer1 interrupt
					ack = FALSE;
					break;
				}
				else                            // Only Byte Done Status bit is set.
				{
					*Var = *asSMBus[Channel].SMBusBData;    // get first data
					if(bcount ==0x00)
					{
						bcount = *asSMBus[Channel].SMBusData0; // get the data of byte count 
						Hook_GetSMBusReadBlockByteCount(bcount);
						//SMB_BCNT = bcount;      // For ACPI SMBus EC SMB1 Block Count register
					}	
            
					bcount--;
					Var++;
    
					if(bcount == 0x01)
					{						    // set last byte flag
						SET_MASK(*asSMBus[Channel].SMBusCTL,HOCTL_LABY);
					}
    
					*asSMBus[Channel].SMBusSTA=0xFE;    // clear bits

					if(bcount == 0x00)
					{
						TR1 = 0;			    // disable timer1
						TF1 = 0;			    // clear overflow flag
						ET1 = 1;			    // Enable timer1 interrupt
						ack = TRUE;
						break;                  // SMBus read block done.
					}
				}
			}
		}

		if(TF1)                                 // time-out
		{
			TR1 = 0;			                // disable timer1
			TF1 = 0;			                // clear overflow flag
			ET1 = 1;			                // Enable timer1 interrupt
			ResetSMBus(Channel);
			ack = FALSE;
		}

		CLEAR_MASK(*asSMBus[Channel].SMBusCTL,HOCTL_LABY);    // clear last byte flag
		*asSMBus[Channel].SMBusSTA=0xFE;        // clear bits
	}
    
	return(ack);	
}


//----------------------------------------------------------------------------
// V14.1 Write SMbus block function	
//----------------------------------------------------------------------------
BYTE bWSMBusBlock(BYTE Channel,BYTE Protocol,BYTE Addr,BYTE Comd,XBYTE *Var,BYTE ByteCont,BYTE PECsupport)
{	
	BYTE ack;
	BYTE BCTemp;
	BYTE status;

	if(CheckSMBusInterfaceCanbeUse(Channel, SMBus_AccessType_Fucn)==SMBus_CanNotUse)
	{
		ack = FALSE;                            // SMBus interface can't be used.
	}
	else
	{
		ack = FALSE;					        // pre-set flag
		BCTemp = 0x00;			                // clear byte count

		if(PECsupport)
		{   
			SMBCRC8_A=0x00;
			CalcCRC8(Addr);
			CalcCRC8(Comd);
			CalcCRC8(ByteCont);
			CalcCRC8(*Var);
		}
    
		Protocol&=(~0x80);			
		*asSMBus[Channel].SMBusADR=Addr;	    // set address with writing flag
		*asSMBus[Channel].SMBusCMD=Comd;	    // Set command
		*asSMBus[Channel].SMBusData0=ByteCont;  // set byte count
		BCTemp=ByteCont;	                    // sync byte count 
		*asSMBus[Channel].SMBusBData=*Var;	    // set first data
		*asSMBus[Channel].SMBusSTA=0xFE;	    // clear bits
		if(PECsupport)
		{   
			*asSMBus[Channel].SMBusCTL=(Protocol|HOCTL_SRT|HOCTL_PEC_EN);// Start transaction
		}
		else
		{
			*asSMBus[Channel].SMBusCTL=(Protocol|HOCTL_SRT);// Start transaction
		}

		TR1 = 0;			                    // disable timer1
		ET1 = 0;                  	            // Disable timer1 interrupt
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		TH1 = T_Timer_26ms>>8;                    // Set timer1 counter 26ms
		TL1 = T_Timer_26ms;                       // Set timer1 counter 26ms
		TF1 = 0;                  	            // Clear overflow flag
		TR1 = 1;                 	            // Enable timer1

		while(!TF1)                             // Not time out
		{
			status = *asSMBus[Channel].SMBusSTA;    // Read SMBus Host Status
			if(IS_MASK_SET(status, (HOSTA_BDS+HOSTA_DVER+HOSTA_BSER+HOSTA_FAIL+HOSTA_NACK+HOSTA_TMOE )))
			{
				if(IS_MASK_SET(status, (HOSTA_DVER+HOSTA_BSER+HOSTA_FAIL+HOSTA_NACK+HOSTA_TMOE)))
				{
					if(IS_MASK_SET(status, (HOSTA_BSER+HOSTA_FAIL)))
					{
						ResetSMBus(Channel);
					}
					TR1 = 0;			        // disable timer1
					TF1 = 0;			        // clear overflow flag
					ET1 = 1;			        // Enable timer1 interrupt
					ack = FALSE;
					break;
				}
				else                            // Only Byte Done Status bit is set.
				{
					BCTemp--;
					Var++;					    // point to next address of variable

					if(BCTemp != 0x00)
					{
						if(PECsupport)
						{
							*asSMBus[Channel].SMBusBData=*Var;
							CalcCRC8(*Var);
							if(BCTemp==0x01)    // last byte of byte count
							{
								*asSMBus[Channel].SMBusPEC = SMBCRC8_A;
							}
						}
						else
						{
							*asSMBus[Channel].SMBusBData=*Var;
						}
						*asSMBus[Channel].SMBusSTA=0xFE;    // clear bits
					}
					else                        // write block transaction done
					{
						TR1 = 0;			    // disable timer1
						TF1 = 0;			    // clear overflow flag
						ET1 = 1;			    // Enable timer1 interrupt
						ack = TRUE;
						break;
					}
				}
			}
		}
        
		if(TF1)                                 // time-out
		{
			TR1 = 0;			                // disable timer1
			TF1 = 0;			                // clear overflow flag
			ET1 = 1;			                // Enable timer1 interrupt
			ResetSMBus(Channel);
			ack = FALSE;
		}
        
		*asSMBus[Channel].SMBusSTA=0xFE;        // clear bits
	}
    
	return(ack);
} 

//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
void CalcCRC8(BYTE sourcebyte)
{
    BYTE temp;
	SMBCRC8_A ^=sourcebyte;
    temp = SMBCRC8_A;

    if(IS_MASK_CLEAR(temp, BIT7))
    {
        temp = temp<<1;
        SMBCRC8_A ^= temp;
    }
    else
    {
        temp = temp<<1;
        SMBCRC8_A ^= 0x09;
        SMBCRC8_A ^= temp;
    }
    
    if(IS_MASK_CLEAR(temp, BIT7))
    {
        temp = temp<<1;
        SMBCRC8_A ^= temp;
    }
    else
    {
        temp = temp<<1;
        SMBCRC8_A ^= 0x07;
        SMBCRC8_A ^= temp;
    }
}

//----------------------------------------------------------------------------
// The function of Checking SMbus clock and data pins are both high	
//----------------------------------------------------------------------------
BYTE CheckSMBusFree(BYTE channel)
{
    BYTE pinstatus;

    pinstatus = *asResetSMBusS[channel].SMBusPinCTL;

    if((pinstatus&=0x03)==0x03) // Check BIT0 and BIT1
    {
        return(SMBus_Free);
    }
    else
    {
        return(SMBus_Busy);
    }
}

//----------------------------------------------------------------------------
// The function of Checking SMbus pins are all alt
//----------------------------------------------------------------------------
BYTE CheckSMBusInterfaceCanbeUse(BYTE channel, BYTE accesstype)
{
	BYTE checksmbus;

	checksmbus = SMBus_CanUse;                  // Pre-set smbus interface can be used
    
        if(accesstype==SMBus_AccessType_Fucn)
        {
            #if SMBusServiceCenterFunc
            WatiSMBusCHxFree(channel);          // Check smbus is in used or not.
            #endif
        }

        if(CheckSMBusFree(channel)==SMBus_Busy)
        {
            checksmbus = SMBus_CanNotUse;       // Interface can't be used
            if( (*asResetSMBusS[channel].recoverCunt)++ >SMBus_BusyRecover)
            {
                ResetSMBus(channel);
            }
        }
        else
        {
            *asResetSMBusS[channel].recoverCunt=0x00;
            checksmbus = SMBus_CanUse;          // smbus interface can be used
        }


    return(checksmbus);                         // return result
}

//----------------------------------------------------------------------------
// The function of SMbus send byte	V14.1
//----------------------------------------------------------------------------
BYTE bSMBusSendByte(BYTE Channel,BYTE Addr,BYTE SData)
{
	BYTE error;
	BYTE result;
	BYTE status;

	if(CheckSMBusInterfaceCanbeUse(Channel, SMBus_AccessType_Fucn)==SMBus_CanNotUse)
	{
	    result = FALSE;                             // SMBus interface can't be used.
	}
	else
	{
		error = 0xEE;                               // Pre-set error
		result = FALSE;                             // Pre-set result is fail
        
		*asSMBus[Channel].SMBusADR = Addr;	        // set address with writing bit
		*asSMBus[Channel].SMBusCMD = SData;	        // Set command
		*asSMBus[Channel].SMBusSTA = 0xFE;	        // clear bits
		*asSMBus[Channel].SMBusCTL = (0x04|HOCTL_SRT);  // Start transaction

		TR1 = 0;                                    // Disable timer1
		ET1 = 0;                  	                // Disable timer1 interrupt
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		TH1 = T_Timer_26ms>>8;                        // Set timer1 counter 26ms
		TL1 = T_Timer_26ms;                           // Set timer1 counter 26ms
		TF1 = 0;                  	                // Clear overflow flag
		TR1 = 1;                 	                // Enable timer1

		while (!TF1)
		{ 
			status = *asSMBus[Channel].SMBusSTA;    // Read SMBus Host Status
			if(IS_MASK_SET(status, (HOSTA_FINTR+HOSTA_DVER+HOSTA_BSER+HOSTA_FAIL+HOSTA_NACK+HOSTA_TMOE )))
			{
				TR1=0;                              // Disable timer1
				TF1=0;                              // Clear overflow flag
				ET1=1;                  	        // Enable timer1 interrupt
				break;
			}
		}
	
		if(TF1)                                     // 26ms time-out and no any status bit is set.
		{
			TR1=0;
			TF1=0;
			ET1=1;                                  // Enable timer1 interrupt
			ResetSMBus(Channel);
			error = 0xEE;
		}
		else
		{
			if(IS_MASK_SET(status, (HOSTA_DVER+HOSTA_BSER+HOSTA_FAIL+HOSTA_NACK+HOSTA_TMOE)))
			{
				if(IS_MASK_SET(status, (HOSTA_BSER+HOSTA_FAIL)))
				{
					ResetSMBus(Channel);
				}
				error = 0xEE;
			}
			else                                    // Only Finish Interrupt bit is set.
			{
				error = 0x00;
			}
		}
    
		if(error == 0xEE)
		{
			result = FALSE;
		}
		else
		{
			result = TRUE;
		}
		*asSMBus[Channel].SMBusSTA=0xFE;	// clear bits
	}
    
	return(result);
}


//----------------------------------------------------------------------------
// The function of SMbus receive byte	
//----------------------------------------------------------------------------
BYTE bSMBusReceiveByte(BYTE Channel,BYTE Addr,XBYTE *Var)
{
	BYTE error;
	BYTE result;
	BYTE status;

	if(CheckSMBusInterfaceCanbeUse(Channel, SMBus_AccessType_Fucn)==SMBus_CanNotUse)
	{
		result = FALSE;                             // SMBus interface can't be used.
	}
	else
	{
		error = 0xEE;                               // Pre-set error
		result = FALSE;                             // Pre-set result is fail

		*asSMBus[Channel].SMBusADR = (Addr|0x01);   // set address with writing bit
		*asSMBus[Channel].SMBusSTA = 0xFE;		    // clear bits
		*asSMBus[Channel].SMBusCTL = (0x04|HOCTL_SRT);  // Start transaction

		TR1 = 0;			                        // disable timer1
		ET1 = 0;                  	                // Disable timer1 interrupt
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		TH1 = T_Timer_26ms>>8;                        // Set timer1 counter 26ms
		TL1 = T_Timer_26ms;                           // Set timer1 counter 26ms
		TF1 = 0;                  	                // Clear overflow flag
		TR1 = 1;                 	                // Enable timer1

		while (!TF1)
		{ 
			status = *asSMBus[Channel].SMBusSTA;    // Read SMBus Host Status
			if(IS_MASK_SET(status, (HOSTA_FINTR+HOSTA_DVER+HOSTA_BSER+HOSTA_FAIL+HOSTA_NACK+HOSTA_TMOE )))
			{
				TR1=0;
				TF1=0;
				ET1=1;                  	        // Enable timer1 interrupt
				break;
			}
		}
	
		if(TF1)                                     // 26ms time-out and no any status bit is set.
		{
			TR1=0;
			TF1=0;
			ET1=1;                                  // Enable timer1 interrupt
			ResetSMBus(Channel);
			error = 0xEE;
		}
		else
		{
			if(IS_MASK_SET(status, (HOSTA_DVER+HOSTA_BSER+HOSTA_FAIL+HOSTA_NACK+HOSTA_TMOE)))
			{
				if(IS_MASK_SET(status, (HOSTA_BSER+HOSTA_FAIL)))
				{
					ResetSMBus(Channel);
				}
				error = 0xEE;
			}
			else                                    // Only Finish Interrupt bit is set.
			{
				error = 0x00;
			}
		}
	 
		if(error == 0xEE)
		{
			result = FALSE; 
		}	
		else
		{
			*Var = *asSMBus[Channel].SMBusData0;    // read data
			result = TRUE; 
		}
		*asSMBus[Channel].SMBusSTA=0xFE;	    // clear bits
	}
    
	return(result);
}


//----------------------------------------------------------------------------
// To init. SMBus setting
//----------------------------------------------------------------------------
void Core_Init_SMBus(void)
{
    SMBus_BusyRecover = 20;         // Reset SMBus interface if bus clock pin or data pin is low greater than SMBus_BusyRecover times.
}



//==============================================================================
//	I2C master control table
//==============================================================================

const tsI2cControlReg code conI2cControlReg[] =
{	// bCtrl , bCtrl2   , bSlaveAddr,bStatus , bI2cdata
	{&HOCTL_A, &HOCTL2_A, &TRASLA_A, &HOSTA_A, &HOBDB_A},
	{&HOCTL_B, &HOCTL2_B, &TRASLA_B, &HOSTA_B, &HOBDB_B},
	{&HOCTL_C, &HOCTL2_C, &TRASLA_C, &HOSTA_C, &HOBDB_C},
};

//==============================================================================
// Name: bI2cMasterRead
// Input:	bChannel = 0-3
//			bSlaveAddress = Slave address
//			bDataLength = Max 256
//			*Var = Data buffer
// Return: 0 = Fail, 1 = Correct Pass
//==============================================================================
BYTE bI2cMasterRead(BYTE bChannel, BYTE bSlaveAddress, BYTE bDataLength, XBYTE *Var)
{
	BYTE	bIndex, bFinishFlag;

	bFinishFlag = 1;
	bIndex = 0;
	*conI2cControlReg[bChannel].bCtrl2 = 0x03;				// Enable SMBus and compatible I2C
	*conI2cControlReg[bChannel].bSlaveAddr = (bSlaveAddress|0x01);	// Set slave address
	*conI2cControlReg[bChannel].bStatus |= 0xFE;					// Clear error flag

	if (bDataLength == 1) {
		*conI2cControlReg[bChannel].bCtrl = 0x7C;					// Set last byte
		
	}
	else
	{
		*conI2cControlReg[bChannel].bCtrl = 0x5C;						// Start send (None interrupt)
	}

	
	do {

		//Set Timer1
		Set_T1_Timeout(T_Timer_26ms);	//Reset TF1
		
		while ( (!(*conI2cControlReg[bChannel].bStatus & 0xFE)) )		// Wait byte done
		{
			if(TF1 == 1)	//Timeout
			{
				bFinishFlag = 0;

				
				//---Reset SMBUS
				SET_MASK(*conI2cControlReg[bChannel].bCtrl,HOCTL_KILL);
				*conI2cControlReg[bChannel].bStatus = 0xFE;	// clear bits
				//---

				return bFinishFlag;
			}
		}
		
		bDataLength--;
		if (*conI2cControlReg[bChannel].bStatus & 0x7C) {
			*conI2cControlReg[bChannel].bCtrl |= 0x02;
			_nop_();
			*conI2cControlReg[bChannel].bCtrl &= ~0x02;
			
			//---Reset SMBUS
			SET_MASK(*conI2cControlReg[bChannel].bCtrl,HOCTL_KILL);
			*conI2cControlReg[bChannel].bStatus = 0xFE;	// clear bits
			//---
			
			bFinishFlag = 0;
			break;
		}

		*(Var+bIndex) = *conI2cControlReg[bChannel].bI2cdata;		// Store data
		bIndex++;

		if (bDataLength == 1) {
			*conI2cControlReg[bChannel].bCtrl |= 0x20;				// Set last byte
		}
		else if (bDataLength == 0) {
			*conI2cControlReg[bChannel].bCtrl2 &= 0xFD;				// Disable I2C_EN for stop
		}
		*conI2cControlReg[bChannel].bStatus |= 0x80;				// Clear byte done
	} while (bDataLength);

	return bFinishFlag;
}

//==============================================================================
// Name: bI2cMasterWrite
// Input:	bChannel = 0-3
//			bSlaveAddress = Slave address
//			bDataLength = Max 256
//			*Var = Data buffer
// Return: 0 = Fail, 1 = Correct Pass
//==============================================================================
bit bI2cMasterWrite(BYTE bChannel, BYTE bSlaveAddress, BYTE bDataLength, XBYTE *Var)
{
	BYTE	bIndex, bFinishFlag;

	bFinishFlag = 1;
	bIndex = 0;
	
	*conI2cControlReg[bChannel].bCtrl2 = 0x03;				// Enable SMBus and compatible I2C	
	*conI2cControlReg[bChannel].bStatus |= 0xFE;					// Clear error flag
	
	*conI2cControlReg[bChannel].bSlaveAddr = (bSlaveAddress&0xFE);	// Set slave address
	*conI2cControlReg[bChannel].bStatus |= 0xFE;					// Clear error flag
	*conI2cControlReg[bChannel].bI2cdata = *Var;					// Set first byte
	*conI2cControlReg[bChannel].bCtrl = 0x5C;						// Start send (None interrupt)

	do {
		//Set Timer1
		Set_T1_Timeout(T_Timer_26ms);	//Reset TF1

		while (!(*conI2cControlReg[bChannel].bStatus & 0xFE))		// Wait byte done
		{

			if(TF1 == 1)	//Timeout
			{
				bFinishFlag = 0;
			
				//---Reset SMBUS
				SET_MASK(*conI2cControlReg[bChannel].bCtrl,HOCTL_KILL);
				*conI2cControlReg[bChannel].bStatus = 0xFE;	// clear bits
				//---

				return bFinishFlag;
			}
		}

		
		bDataLength--;
		if (*conI2cControlReg[bChannel].bStatus & 0x7C) {
			bFinishFlag = 0;
			
			//---Reset SMBUS
			SET_MASK(*conI2cControlReg[bChannel].bCtrl,HOCTL_KILL);
			*conI2cControlReg[bChannel].bStatus = 0xFE;	// clear bits
			//---
			
			break;
		}
		else if (bDataLength) {		//*** Send data ***//
			bIndex++;
			*conI2cControlReg[bChannel].bI2cdata = *(Var+bIndex);	// Next byte
			*conI2cControlReg[bChannel].bStatus |= 0x80;			// Clear byte done
		}
	}
	while ( bDataLength);

	*conI2cControlReg[bChannel].bCtrl2 &= 0xFD;						// Disable I2C_EN for stop
	*conI2cControlReg[bChannel].bStatus |= 0x80;					// Clear byte done
	return (bFinishFlag);


}


//==============================================================================
// Name: bI2cMasterWriteToRead
// Input:	bChannel = 0-3
//			bSlaveAddress = Slave address
//			Offset = Offset
//			bDataLength = Max 256
//			*Var = Data buffer
// Return: 0 = Fail, 1 = Correct Pass
// Descript: Start - Slave address - Offset - Restart - Slave address - Data0 ... DataN - Stop
//==============================================================================
BYTE bI2cMasterWriteToRead(BYTE bChannel, BYTE bSlaveAddress, BYTE Offset, BYTE bDataLength, XBYTE *Var)
{
	BYTE	bIndex, bFinishFlag;

	bFinishFlag = 1;
	bIndex = 0;
	*conI2cControlReg[bChannel].bCtrl2 = 0x03;				// Enable SMBus and compatible I2C
	*conI2cControlReg[bChannel].bSlaveAddr = (bSlaveAddress&0xFE);	// Set slave address
	*conI2cControlReg[bChannel].bStatus |= 0xFE;					// Clear error flag

	//*** Write offset ***//
	*conI2cControlReg[bChannel].bI2cdata = Offset;					// Set first byte
	*conI2cControlReg[bChannel].bCtrl = 0x5C;						// Start send (None interrupt)
	Set_T1_Timeout(T_Timer_26ms);	//Reset TF1
	while (!(*conI2cControlReg[bChannel].bStatus & 0xFE))		// Wait byte done
	{
		if(TF1 == 1)	//Timeout
		{
			bFinishFlag = 0;
			
			//---Reset SMBUS
			SET_MASK(*conI2cControlReg[bChannel].bCtrl,HOCTL_KILL);
			*conI2cControlReg[bChannel].bStatus = 0xFE;	// clear bits
			//---
				return bFinishFlag;
		}
	}
	if (*conI2cControlReg[bChannel].bStatus & 0x7C) {
		*conI2cControlReg[bChannel].bCtrl |= 0x02;
		_nop_();
		*conI2cControlReg[bChannel].bCtrl &= ~0x02;
		bFinishFlag = 0;
		*conI2cControlReg[bChannel].bCtrl2 &= 0xFD;						// Disable I2C_EN for stop
		*conI2cControlReg[bChannel].bStatus |= 0x80;					// Clear byte done
		return bFinishFlag;
	}

	//*** Wait direction switch ***//
	*conI2cControlReg[bChannel].bCtrl2 |= 0x0C;				// Set I2C direction switch wait
	*conI2cControlReg[bChannel].bStatus |= 0x80;					// Clear byte done
	*conI2cControlReg[bChannel].bCtrl2 &= 0xFB;						// Release I2C switch wait

	//*** Read data ***//
	do {
		Set_T1_Timeout(T_Timer_26ms);	//Reset TF1
		while (!(*conI2cControlReg[bChannel].bStatus & 0xFE))		// Wait byte done
		{
			if(TF1 == 1)	//Timeout
			{
				bFinishFlag = 0;
			
				//---Reset SMBUS
				SET_MASK(*conI2cControlReg[bChannel].bCtrl,HOCTL_KILL);
				*conI2cControlReg[bChannel].bStatus = 0xFE;	// clear bits
				//---

				return bFinishFlag;
			}
		}
		bDataLength--;
		if (*conI2cControlReg[bChannel].bStatus & 0x7C) {
			*conI2cControlReg[bChannel].bCtrl |= 0x02;
			_nop_();
			*conI2cControlReg[bChannel].bCtrl &= ~0x02;
			bFinishFlag = 0;

			//---Reset SMBUS
			SET_MASK(*conI2cControlReg[bChannel].bCtrl,HOCTL_KILL);
			*conI2cControlReg[bChannel].bStatus = 0xFE;	// clear bits
			//---
			
			break;
		}

		*(Var+bIndex) = *conI2cControlReg[bChannel].bI2cdata;		// Store data
		bIndex++;

		if (bDataLength == 1) {
			*conI2cControlReg[bChannel].bCtrl |= 0x20;				// Set last byte
		}
		else if (bDataLength == 0) {
			*conI2cControlReg[bChannel].bCtrl2 &= 0xFD;				// Disable I2C_EN for stop
		}
		*conI2cControlReg[bChannel].bStatus |= 0x80;				// Clear byte done
	} while ( bDataLength);

	*conI2cControlReg[bChannel].bCtrl2 &= 0xFD;						// Disable I2C_EN for stop
	*conI2cControlReg[bChannel].bStatus |= 0x80;					// Clear byte done
	return bFinishFlag;
}
/*-----------------------------------------------------------------------------
 * End
 *---------------------------------------------------------------------------*/

