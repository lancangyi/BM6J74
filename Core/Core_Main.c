/*-----------------------------------------------------------------------------
 * TITLE: CORE_MAIN.C - Main Program for KBC firmware.
 *
 * Main processing loop (interrupt driven) for the keyboard controller/scanner.
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


//==================================================
// Name:	Main
// Descript:
// Input:
// Return:
//==================================================
void main(void)
{

	DisableAllInterrupt() ;
	SP = 0xD0 ; 
    

	#if	COMPARE_CHECKSUM
		ROM_Checksum = Get_Checksum();
		CacheDma(3, CalculateChecksum );
		CalculateChecksum();
		if(ROM_Checksum == Calc_Checksum)
		{
			Checksum_compare = 1;		//compare success
		}
		else
		{
			Checksum_compare = 2;		//compare Fail
		}
		SCAR4H = 0x01;	//Disable CacheDMA
		ClearSRamF();	//Clear 0xF00-0xFFF
	#endif
	

	if(ExitRamCodeCommand == 0xAA)
	{
		CLEAR_MASK(FBCFG,SSMC); // disable scatch ROM
		_nop_();
		MPREFC = 0x01;
		_nop_();
		MPREFC = 0x01;
		_nop_(); 
		MPREFC = 0x01;
		_nop_();
		MPREFC = 0x01;
		_nop_();
		_nop_();
		ExitRamCodeCommand = 0x00;
	}
	else
	{

	
		#if SUPPORT_SHARE_ROM
		    HCTRL2 = 0x80;  //For Share ROM
		    FMSSR = 0x0F;	//For Share ROM
		#endif

		Reset_Initialization();
		
		EnableAllInterrupt();

		//----------------------
		//Enable PMC interrupt
		//PMC1
		Index_07H = 0x11;
		Index_30H = 0x01;
		Index_07H = 0x00;
		SET_MASK(IER3, Int_PMCIBF);
		ISR3 = Int_PMCIBF;
		SET_BIT(PM1CTL, 0);



		//PMC2	
		Index_07H = 0x12;
		Index_30H = 0x01;
		Index_07H = 0x00;
		SET_MASK(IER3, Int_PMC2IBF);
		ISR3 = Int_PMC2IBF;
		SET_BIT(PM2CTL, 0);
		//----------------------
	

		//----------------------
		//init SW KBC
		//----------------------
		#if SUPPORT_SWKBC
		Init_SWKBC();
		#endif
	
	}


	

	//===========================================
	//init CIR
	//===========================================
	#if Support_EC_CIR
	EN_EC_CIR();

		#if CIRRX_mapping_to_Pin84
		//-----------------------------------------------
		//SET CIRRX mapping to Pin84(GP10)
		Index_07H = 0x04;
		SET_BIT(Index_F2H, 0);	// 1 : ping84,  0: ping85(default)
		//------------------------------------------------
		#endif

	#endif
	//===========================================
	


	//===========================================
	//init SMBUS
	//===========================================
	InitSMBus();
	//===========================================
	


	//----------------------
	//Set EC FW version
	//----------------------
	Code_Version = OEM_Version_MSB;		////Main version
	Code_Beta_Version = OEM_Version_LSB;	//Beta 00
	//----------------------
	
	
	//Default standy on G3->S5
	SysPowState = _PowrUp_S5;

	//Set DeepSleepCountDown = 2 * 50ms
	DeepSleepCountDown = 2;


	//----------------------
	//Enable UART (EC side)
	//----------------------
	#if USE_UART2
	Init_UART2();
	#endif

	#if USE_UART1
	Init_UART1();
	#endif
	//----------------------


	//--------------------------------
	//Set EC side PWM (PWMOUT / pin 18)
	//--------------------------------
	#if Support_EC_PWMOUT
	Init_EC_PWM();
	DCR = PWM_Duty_75percent;
	SET_BIT(PWMCTL, PCCE);		//Enable PWMOUT
	#endif
	//--------------------------------

	#if LENOVO_80PORT
	{
		BYTE Original_PLLFreq_Setting;
		//========Change FSPI CLK To 48MHz Start================
		Original_PLLFreq_Setting = EC_1E06;
		//RamDebug(Original_PLLFreq_Setting);

		if(Original_PLLFreq_Setting!=0x05)
		{
			EC_1E06 = 0x05;	//Select 48.XMHz as PLL frequency.
											 //0011b: Select 32.3MHz as PLL frequency. (Default)
											 //0101b: Select 46.0MHz as PLL frequency.
											 //0111b: Select 64.5MHz as PLL frequency.
			EC_1E03 = 0x01;

			EA = 0 ;

			PCON |= 0x02;  // Enter Sleep mode
			_nop_();
			_nop_();
			_nop_();
			_nop_();
			_nop_();
			_nop_();
			_nop_();
			_nop_();
			_nop_();
			_nop_();
			_nop_();

			EnableAllInterrupt();
		}
		//========Change FSPI CLK To 48MHz End================
	}
	#endif
	
	while(1)
	{
				
		#if SUPPORT_MAIN_SERVICE
		main_service();
		#endif

		#if SUPPORT_SWKBC        
		service_send();
		#endif 

		#if SUPPORT_MAIN_SERVICE
		SET_BIT(IER3, 1);
		SET_BIT(IER3, 3);
		EnableAllInterrupt();
		_nop_();
		_nop_();
		_nop_();
		_nop_();

		#endif
		

		//*** for EC Deep sleep mode ***//
		
		#if SMBusServiceCenterFunc
		if((Service==0x00)&&(Service1==0x00)&&( CheckSMBusNeedService()==SMBus_ClearService))
		#else
		if (  (Service==0x00) && (Service1==0x00) )
		#endif
		{
			//if( (!DeepSleepCountDown) && (SysPowState == _SYSTEM_S5) )	//
			if(0)		//do not sleep
			{
				InitEnterDeepSleep();
				EnableAllInterrupt();   // enable global interrupt
				EC_1E03 = 0x01;
				PCON   = 0x02;         /* Enter Deep Sleep mode.  */
				_nop_();                /* Wake-up delay.  */
				_nop_();
				_nop_();
				_nop_();
				_nop_();
				_nop_();
				_nop_();
				_nop_();
				_nop_();
				InitWakeFromDeepSleep();
				_nop_();
                
			}
			else
			{
				PCON=1;      		// enter idle mode
	 			_nop_();
				_nop_();
				_nop_();
				_nop_();
				_nop_();
				_nop_();
				_nop_();
				_nop_();
			}
		}
		//*** END ***//
		
	}// End while(1)


}


#if SUPPORT_MAIN_SERVICE
/* ----------------------------------------------------------------------------
 * FUNCTION: main_service - Check for new/more service requests.
 *
 * Check for a request flag.  The check is done according to priority.  If a
 * request flag is set, handle the request and loop back to get the flags
 * again.  Do not follow through to check the next flag.  The flags are to be
 * checked in order.
 * ------------------------------------------------------------------------- */
const FUNCT_PTR_V_V code service_table[16] =
{
		service_000,       // Service ACPI
		service_001,    	// Service CIR
		service_002, 	// 1 millisecond timer service
		service_003,       // PMC2 68h/6Ch port pairs
		service_004, 	// reserve
		service_005, 	// 1 millisecond timer service
		service_006,        // reserve
		service_007,	// For SMBUS scan center

		service_008,   	// UART2
		service_009,     	// UART1
		service_00A,    	// reserve
		service_00B,    	// reserve
		service_00C,	// reserve
		service_00D,       // reserve
		service_00E, 	// reserve
		service_00F,      // reserve
};


void main_service(void) 
{
	_W1 = (((WORD)Service1 << 8) | Service);  
	while(_W1 != 0)
	{
		_R6 = 0;
		while((_W1 & 1) == 0) 
		{
			_W1 >>= 1;
			_R6++;
		}

		if (_R6 < 0x08) 
		{
			Service &= Cpl_Byte_Mask(_R6 & 0x07);  /* Clear service request. */
		}
		else 
		{
			Service1 &= Cpl_Byte_Mask(_R6& 0x07);  /* Clear service request. */
		}

		(service_table[_R6])();   /* Dispatch to service handler. */

		if(IsFlag1(PM1STS, IBF1) )			{	F_Service_000 = 1;	}
		else if(IsFlag1(PM2STS, IBF1))		{	F_Service_003 = 1;	}
		else if(IsFlag1(KBHISR, IBF))		{	F_Service_001 = 1;	}
		
		 _W1 = ( ( (WORD)Service1 << 8 ) | Service );    /* Re-Load Service */
		 
	}

	//Reserve (Test&Debug)
	#if SMBusServiceCenterFunc
	if( CheckSMBusNeedService()==SMBus_NeedService )
	{
		ServiceSMBus();
	}
	#endif
}

#endif




void service_000(void) 
{
	// Runtime Service 000 -- ACPI
	Service_PCI2();
	
}

void service_001(void)
{
	// Runtime Service 001	-- KBC
	#if SUPPORT_SWKBC    
	F_Service_001=0;
	service_pci1();
	#endif   
	
}

void service_002(void)
{

	// Runtime Service 002
	#if SUPPORT_Hook_1ms_Timer
	Oem_Hook_1MS_Event();
	Timer1msCnt++;
	if(Timer1msCnt == 5)
	{
		F_Service_005 = 1;
		Timer1msCnt = 0;
	}
	#endif

}


void service_003(void)
{
	// Runtime Service 003 for 68h/6Ch port pairs
	Service_PCI3() ;

}


void service_004(void)
{
	#if Support_EC_CIR
	// Runtime Service 004--CIR
	Service_CIR();
	#endif
}


void service_005(void)
{
	// Runtime Service 005
	Oem_Hook_5MS_Event() ;
	Timer5msCnt++;
	Timer125msCnt++;
	if( Timer125msCnt >= 25 )
	{
		Timer125msCnt = 0;
		Oem_Hook_125MS_Event();
	}
	if ( Timer5msCnt & 1 )  // 10ms events
	{
		Oem_Hook_10MS_Event();
		Timer250msCnt++;
		if( Timer250msCnt >= 25 )
		{
			Timer250msCnt = 0;
			Oem_Hook_250MS_Event();
		}
	}
	else
	{
		switch( Timer5msCnt )   // Share Loading Branch Control
		{
			case 2: Oem_Hook_50MS_EventA();
				break;
			case 4: Oem_Hook_50MS_EventB();
				break;
			case 6: Oem_Hook_50MS_EventC();
				break;
			case 8: Timer100msCntB++;
				if ( Timer100msCntB & 1 )
				{
					Oem_Hook_100MS_EventA();
				}
				else
				{
					Oem_Hook_100MS_EventB();
				}
				break;

			default:    Timer5msCnt=0;
				break;
		}

		if ( Timer5msCnt == 0x00 )
		{   // 50msec
			Timer100msCnt ++;
			if ( Timer100msCnt & 1 )
			{
				Oem_Hook_100MS_EventC();
			}
			else
			{   // 100msec
				switch( Timer100msCnt )
				{
					case 2:     Oem_Hook_500MS_EventA();
						break;
					case 4:     Oem_Hook_500MS_EventB();
						break;
					case 6:     Oem_Hook_500MS_EventC();
						break;
					case 8:     Oem_Hook_1S_EventA();
						break;
					case 10:    Oem_Hook_1S_EventB();
						break;
					case 12:    Oem_Hook_500MS_EventA();
						break;
					case 14:    Oem_Hook_500MS_EventB();
						break;
					case 16:    Oem_Hook_500MS_EventC();
						break;
					case 18:    Oem_Hook_1S_EventC();
						break;
					default:    // 1 Sec
							Timer100msCnt = 0;
							Timer1SecCnt ++;
							if ( Timer1SecCnt == 10 )
							{
								Oem_Hook_1Min_Event();
								Timer1SecCnt=0;
							}
							break;

				}
			}
		}
	}
}


void service_006(void)
{
	// Runtime Service 006
}


void service_007(void)
{
	// Runtime Service 007
	 //-----------------------------------
	// process SMBus interface data
	//-----------------------------------
	#if SMBusServiceCenterFunc
	ServiceSMBus();
	
	if( CheckSMBusNeedService()==SMBus_ClearService )
	F_Service_007 = 0;

	#endif

}

void service_008(void)
{
	// Runtime Service 008

	#if USE_UART2

	UART_R_IIR	= UART2_IIR;
	UART_R_LSR = UART2_LSR;

	if( (UART_R_LSR & 0x8C) != 0)	//Error
	{
		//Need reset
		UART2_FCR |= 0x02;				// Reset Rx FIFO
		return;
		
	}

	if( IS_BIT_CLEAR(UART_R_LSR, 0) )	//Data not ready
	{

		return;
	}
	else
	{

		//To Modify RxIndex count as you want
		for (UART_RxIndex=0 ; UART_RxIndex<4 ; UART_RxIndex++) {
			UART_RxBuff[UART_RxIndex] = UART2_RBR;			// Store Rx to buffer array
			}
		
		
			UART2_FCR |= 0x02;				// Reset Rx FIFO
			UART2_Data_Handler();
		
	}


	#endif
}


void service_009(void)
{
	// Runtime Service 009
	#if USE_UART1

	UART_R_IIR	= UART1_IIR;
	UART_R_LSR = UART1_LSR;

	if( (UART_R_LSR & 0x8C) != 0)	//Error
	{
		//Need reset
		UART1_FCR |= 0x02;				// Reset Rx FIFO
		return;
		
	}

	if( IS_BIT_CLEAR(UART_R_LSR, 0) )	//Data not ready
	{

		return;
	}
	else
	{

		//To Modify RxIndex count as you want
		for (UART_RxIndex=0 ; UART_RxIndex<4 ; UART_RxIndex++) {
			UART_RxBuff[UART_RxIndex] = UART1_RBR;			// Store Rx to buffer array
			}
		
		
		UART1_FCR |= 0x02;				// Reset Rx FIFO
		UART1_Data_Handler();
		
	}

	#endif
}

void service_00A(void)
{
	// Runtime Service 00A
}


void service_00B(void)
{
	// Runtime Service 00B
}


void service_00C(void)
{
	//Runtime Service 00C
}


void service_00D(void)
{
	// Runtime Service 00D
}


void service_00E(void)
{
	// Runtime Service 00E
}


void service_00F(void)
{
	// Runtime Service 00F
}



#if SUPPORT_SWKBC
/* ----------------------------------------------------------------------------
 * FUNCTION: service_send
 *
 * 
 * 
 * ------------------------------------------------------------------------- */
void service_send(void)
{
    BYTE bTmp;

    if(IS_MASK_SET(KBHISR,IBF))
    {   
        //RamDebug(0xE0);
    	//bTmp = KBHIDIR;
    	return;
    }
	
    if(IS_MASK_SET(KBHISR,OBF))
    {
        //RamDebug(0xE2);
       	return;
    }

    ///SCCTRL = 0x00;
    //RamDebug(0xE2);
    bTmp = Get_KB_Buffer();

    if(bTmp != 0xFF)
    {	
        Data_To_Host(bTmp);
    }    
}

#endif


