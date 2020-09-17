
#include "Core_Inc.h"
#include "Oem_Inc.h"


void Kernel_Initialization(void)
{

//	EA = 0;
//    EA = 1;

	SPCTRL1 = 0x03;  	// I2EC R/W Enable;
	SPCTRL2 = 0x27;  	// Bit4 = 1, 8032 UART1 Enable; Bit 2-1 = 11b, SSPI Enable, Bit 5 = 1 because the LRESET# gating;
						// Bit 0 = 1, Port I2EC Enable;
						
	#if VCC_POWER_ON_TREATED
	RSTS = 0x44;//set 2006h bit3 =0 for LDN change issue 
	#else
	RSTS = 0x84;//set 2006h bit3 =0 for LDN change issue 
	#endif

	PI2ECH = 0x0B;   // I2EC Base address MLB
	PI2ECL = 0x00;   // I2EC Base address LSB

	Disable_DCache();	//Disable DCache

	vDelay1ms(100);
	Index_07H = 0x07;    //LDN=0x07
	Index_30H = 0x01;
	Index_E9H = 0x20;	// Disable BUS Selection

	Index_2CH = 0x8B;	// Disable SMBUS isolation
	
	Index_62H = 0x02;	// IO base assignment
	Index_63H = 0x00;


	SET_BIT(CFG_REG, 7);				
	SET_BIT(PWM_STEP_FREQ_REG, 4);	//Initialize the Thermal Diode At the VSTBY Power

	Kernel_Code_Version = Read_SPI(0xFEFE);
	
}


void Init_ClearRam(void)
{

	IIBYTE *IdataIndex;
	PORT_BYTE_PNTR byte_register_pntr;
	IdataIndex = 0x20;
	byte_register_pntr=0;

	#if INIT_CLEAR_XRAM
	while(byte_register_pntr<0x1000)// Clear external ram (0x000~0xFFF)
	{
	    *byte_register_pntr=0;
	    byte_register_pntr ++;
	}
	#endif

	#if INIT_CLEAR_IRAM
	while(IdataIndex<0xD0)			// Clear internal ram (0x20~0xCF)
	{
		    *IdataIndex=0;
		    IdataIndex ++;
	}
	#endif
		
}



void Enable_SMLink1_Mapping_To_TMPIN2(void)
{
	Index_07H = 0x07 ;	// Secret move for enabling the SMLink1
	Index_2AH = 0x02 ;	// Secret move for enabling the SMLink1

	PCH_AMDTSI_HOST_STS		= 0x00 ;
	PCH_AMDTSI_TARGET_ADDR	= 0x97 ;
	PCH_AMDTSI_HOST_CMD		= 0x40 ;
	PCH_AMDTSI_HOST_CTRL		= 0xC3 ;
}

//-----------------------------------------------------------------------------
// Reset_Initialization - Initialize the registers and data variables.
//
//-----------------------------------------------------------------------------
void Reset_Initialization(void)
{

	Kernel_Initialization();

	AWFCS_EN = 0x01;
	//==================================
	//Init GPIO
	//==================================
	Initialize_GPIO_Pin_State();
	//==================================
	InitADC();

	//==================================
	//Set K8 function (for AMD platform)
	//==================================
	#if K8_Function_Enable
	Enable_K8_Function();
	#endif
	
	LED_S0_Status = 0;
	
	Init_BRAM() ;
	
	Init_Timers();

}

void Init_Timers(void)
{
	TF0 = TR0 = 0;        	// Stop timer0 and clear interrupt
	
	#if SUPPORT_Hook_1ms_Timer
	TL0 = T_Timer_1ms;      	// Reload timer
	TH0 = T_Timer_1ms>>8;	    // 1ms
	#else
	TL0 = T_Timer_5ms;      	// Reload timer
	TH0 = T_Timer_5ms>>8;	    // 5ms
	#endif
	
	TMOD  = 0x11;			// Timer0 and timer1 are 16 bits timer
	TR0 = 1;                // Start timer0 running
	ET0 = 1;				// Enable timer0 interrupt
							
	TF1 = TR1 = 0;       	// Stop timer 1 and clear interrupt
	//TL1 = T_Timer_2ms;      	// Reload timer
	//TH1 = T_Timer_2ms>>8; 	// 2ms
	TR1 = 0;           	// Stop timer1 
	//ET1 = 1;				// Enable timer1 interrupt
}


//==============================================================================
// Name: vSetTimeout
// Description: When TF1 is 1 mean timeout occur
//==============================================================================
void Set_T1_Timeout(WORD wTimeCnt)
{
	ET1 = 0;					// Disable timer1 interrupt
	TR1 = 0;					// Stop timer1
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	TH1 = wTimeCnt>>8;			// Set timer1 counter MSB
	TL1 = wTimeCnt;				// Set timer1 counter LSB
	TF1 = 0;					// Clear overflow flag
	TR1 = 1;					// Enable timer1
}



void Load_Timer_A(void)
{   						// Assume the 8051 clock source is Ring Oscillator 
	TL0 = T_Timer_5ms;      	// Reload timer
	TH0 = T_Timer_5ms>>8;	    // 5ms
	TF0 = 0;				// Clear overflow flag
}


void Load_Timer_A_1ms(void)
{   						// Assume the 8051 clock source is Ring Oscillator 
	TL0 = T_Timer_1ms;      	// Reload timer
	TH0 = T_Timer_1ms>>8;	    // 1ms
	TF0 = 0;				// Clear overflow flag
}



void InitSMBus(void)
{

	//SMBUS initi
 	Index_07H = 0x19;	// LDN 19h for SMBus configurations
	Index_70H = 0x00;
 	Index_30H = 0x00;	// Disable Host side
 	
 	//SMBUS Disable
	#if Disable_All_SMBUS_Channel
	 	Index_30H = 0x00;	// Activation
	 	Index_70H = 0x00;
	 	Index_76H = 0x00;	// SMBus disable
	 	return;
 	#endif


	//---------------------------------------------
	#if Enable_SMBUS_ChannelA	//SMBUS0
	SET_BIT(Index_76H, 1);
	HOCTL2_A = 0x01;	//Enable SMBUS (SMHEN)
	#else
	CLR_BIT(Index_76H, 1);
	#endif

	#if Enable_SMBUS_ChannelB
	HOCTL2_B = 0x01;	//Enable SMBUS (SMHEN)
	#endif


	#if Enable_SMBUS_ChannelC 	//SMBUS2
 	SET_BIT(Index_76H, 0);	// SMBus enable
 	HOCTL2_C = 0x01;	//Enable SMBUS (SMHEN)
 	#else
	CLR_BIT(Index_76H, 0);
 	#endif
	//---------------------------------------------

	Core_Init_SMBus();
	#if SMBusServiceCenterFunc
		CheckSMBusTableSize();
	#endif


	switch(SMBus_Freq)//400,100,50,20,13,10
	{
		case 400:
			SMBUS_4P7USREG = 0x03;
			SMBUS_4P0USREG = 0x02;
			SMBUS_300NSREG = 0x03;	
			SMBUS_250NSREG = 0x03;	
			SMBUS_25MSREG    = 0x19;	
			SMBUS_45P3USLREG = 0xC9;	
			SMBUS_45P3USHREG = 0x01;
			SMBUS_4P7A4P0H = 0x00;
			break;
			
		case 100:
			//set SMBUS Frequency = 100KHz
			SMBUS_4P7USREG = 0x15;
		 	SMBUS_4P0USREG = 0x25;
			SMBUS_300NSREG = 0x03;	
			SMBUS_250NSREG = 0x15;	
			SMBUS_25MSREG    = 0x19;	
			SMBUS_45P3USLREG = 0xB8;	
			SMBUS_45P3USHREG = 0x01;
			SMBUS_4P7A4P0H = 0x00;
			break;

		case 50:
			//set SMBUS Frequency = 50KHz
			SMBUS_4P7USREG = 0x2C;
			SMBUS_4P0USREG = 0x53;
			SMBUS_300NSREG = 0x03;	
			SMBUS_250NSREG = 0x2C;	
			SMBUS_25MSREG    = 0x19;	
			SMBUS_45P3USLREG = 0xA0;	
			SMBUS_45P3USHREG = 0x01;
			SMBUS_4P7A4P0H = 0x00;	
			break;
	
		case 20:
			//set SMBUS Frequency = 20KHz
			SMBUS_4P7USREG = 0x71;
			SMBUS_4P0USREG = 0xDD;
			SMBUS_300NSREG = 0x03;	
			SMBUS_250NSREG = 0x71;	
			SMBUS_25MSREG    = 0x19;	
			SMBUS_45P3USLREG = 0x5B;	
			SMBUS_45P3USHREG = 0x01;
			SMBUS_4P7A4P0H = 0x00;	
			break;
			
		case 13:
			//set SMBUS Frequency = 13KHz
			SMBUS_4P7USREG = 0xAF;
			SMBUS_4P0USREG = 0x5A;
			SMBUS_300NSREG = 0x03;	
			SMBUS_250NSREG = 0xAF;	
			SMBUS_25MSREG    = 0x19;	
			SMBUS_45P3USLREG = 0x1D;	
			SMBUS_45P3USHREG = 0x01;
			SMBUS_4P7A4P0H = 0x02;
			break;
			
		case 10:
			//set SMBUS Frequency = 10KHz
			SMBUS_4P7USREG = 0xE4;
			SMBUS_4P0USREG = 0xC5;
			SMBUS_300NSREG = 0x03;	
			SMBUS_250NSREG = 0xE4;	
			SMBUS_25MSREG    = 0x19;	
			SMBUS_45P3USLREG = 0xE8;	
			SMBUS_45P3USHREG = 0x00;
			SMBUS_4P7A4P0H = 0x02;	
			break;
	
		default:
			break;
	}

}


void InitDAC(void)
{
	DACPDREG = 0x00;	//Enable DAC0~4
	
	DACDAT0_MSB = 0x30;
	DACDAT0_LSB = 0xFF;
	
	DACDAT1_MSB = 0x02;
	DACDAT1_LSB = 0x00;
	
	DACDAT2_MSB = 0x00;
	DACDAT2_LSB = 0x00;
	
	DACDAT3_MSB = 0x00;
	DACDAT3_LSB = 0xFF;
	
	DACDAT4_MSB = 0x02;
	DACDAT4_LSB = 0xFF;
}

void InitADC(void)
{
	Index_07H = 0x04;
	Index_30H = 0x01;
	ADC_VCEn = 0x3F;
	ADC_channel_enable = 0xFF;
	CFG_REG |= 0x01;
}


void InitFanCTL(void)
{
	FAN_MAIN_CTL = 0x77;//enable TAC1-3
	FAN_CTL = 0xC0;//Set Active high

	FAN_CTL1= 0x00;	//Use Fan1
 	PWM_FAN_CTL1= 0x50;

	FAN_CTL2 = 0x00;	//Use Fan2
 	PWM_FAN_CTL2 = 0x50;
}


//======================================================
// Name:	vDelay1ms
// Input:		bMS
// Output:	bMS delay
// Return:
//
// Module Author: Ethan Lo, ITE Tech. Inc.
// Application Implementation: B.J. Chen, ITE. Tech. Inc.
//======================================================
void vDelay1ms(WORD bMS)
{
    bit SaveEA;
    BYTE i;

    SaveEA = EA;    // save Interrupt
    EA = 0;         // clear global interrupt

    while(bMS)      // delay 1ms
    {
        for( i=0; i<66; i++ )
            WNCKR = 0;  // 15.26 us
        bMS--;
    }
    EA = SaveEA;        // restore Interrupt
}//End vDelayXms

void LED_SEG(BYTE ucByte) 
{

    GPIO_7x = ucByte;	
	
}//END LED_SEG

/*
Hardware Monitor 

		INDEX13 bit 2~0=0
		INDEX14 = C0h


COM 2 
	LDN07  
		INDEX 25 bit 7=1
              INDEX 26 bit7~4=1 : F0h
              INDEX 26 bit1~0=1 : 03h
              INDEX C0 bit7=1
              INDEX C1 bit7~4=1 : F0h
              INDEX C1 bit1~0=1 : 03h
              INDEX C8 bit7=1
              INDEX C9 bit7~4=1 : F0h
              INDEX C9 bit1~0=1 : 03h

 Hardware Monitor EC 

		index 0A bit 5~4= 0
*/


void InitEnterDeepSleep(void)
{
	//Disable Timer0/Timer1 Interrupt
	ET0 = 0;
	ET1 = 0;

	//WKO[34], INT52	GP34 WU34
	IER6 = 0x10;
	WUENR3 = 0x10;
	WUESR3 = 0xFF;
}

void InitWakeFromDeepSleep(void)
{
	//WKO[34], INT52	GP34 WU34
	WUENR3 = 0x00;
	IER6 = 0x00;

	DeepSleepCountDown = 2;

	//Enable Timer0 Interrupt
	ET0 = 1;
	//ET1 = 0;
}


void Init_UART2(void)
{
	if( (SysPowState == _SYSTEM_S5) || (SysPowState == _PowrUp_S5) )
	{
		//Index_23H = 0x01;	//For S5 only
		SET_BIT(Index_23H, 0);	//For S5 only
	}
	
	
	//Set LDN 02 for UART2
	Index_07H = 0x02;
	Index_30H = 0x01;
	SET_BIT(Index_F0H, 3);	//UART2 Pin not gated
	
	Index_07H = 0x07;
	CLR_BIT(Index_26H,7);	//Sin2
	CLR_BIT(Index_26H,6);	//Sout2
	CLR_BIT(Index_C1H,7);
	CLR_BIT(Index_C1H,6);
	UART2_LCR = 0x80;				// DLAB = 1
	UART2_DLM = 0x00;				// Enable read/write Baud Rate
	//UART2_DLL = 0x01;				// Set baud rate = 115200
	//UART2_DLL = 0x0C;				// Set baud rate = 9600
	//UART2_DLL = 0x03;				// Set baud rate = 38400
	UART2_DLL = 0x06;				// Set baud rate = 19200
	
	UART2_LCR = 0x03;				// DLAB = 0, Word length = 8 bit
	
	UART2_FCR |= 0x86;				// Set Rx FIFO to 8 byte and reset FIFO
	SetFlag(UART2_FCR, BIT0);		// Enable FIFO
	SetFlag(UART2_IER, BIT0);		// Enable received data available interrupt
	SetFlag(UART2_MCR, BIT3);		// Enable OUT2
	SET_MASK(IER4, Int_UART2) ;	//UART2 int
	ISR4 = Int_UART2;


}



void Init_UART1(void)
{

	//UART1 test
	if( (SysPowState == _SYSTEM_S5) || (SysPowState == _PowrUp_S5) )
	{
		//Index_23H = 0x01;	//For S5 only
		SET_BIT(Index_23H, 0);	//For S5 only
	}
		
	//Set LDN 01 for UART1
	Index_07H = 0x01;
	Index_30H = 0x01;
	SET_BIT(Index_F0H, 3);	//UART1 Pin not gated
	
	UART1_LCR = 0x80;				// DLAB = 1
	UART1_DLM = 0x00;				// Enable read/write Baud Rate
	//UART2_DLL = 0x01;				// Set baud rate = 115200
	//UART2_DLL = 0x0C;				// Set baud rate = 9600
	UART1_DLL = 0x03;				// Set baud rate = 38400
	
	UART1_LCR = 0x03;				// DLAB = 0, Word length = 8 bit

	UART1_FCR |= 0x86;				// Set Rx FIFO to 8 byte and reset FIFO
	SetFlag(UART1_FCR, BIT0);		// Enable FIFO
	SetFlag(UART1_IER, BIT0);		// Enable received data available interrupt
	SetFlag(UART1_MCR, BIT3);		// Enable OUT2
	SET_MASK(IER4, Int_UART1) ;	//UART1 int
	ISR4 = Int_UART1 ;


}


void Set_ExtTimer1(void)
{

	SET_BIT(ETWCTRL, 0);	//Reset
	ETPSR = 0x00;	//Set Clock	
	
	//ETCNTLHR = 0x3E;
	//ETCNTLLR = 0x80;		//Start
	
	ETCNTLHR = 0x7D;
	ETCNTLLR = 0x00;
	
	ISR3 = BIT6;		//clear INT30 ISR
	IER3 |= BIT6;	//set  INT30 IER
	
}


BYTE Read_SPI(WORD address)
{
	unsigned char code *pt_rom;
	unsigned char tmp;
	
	pt_rom = 0+address;
	tmp = *pt_rom;

	return tmp;
}


void Init_BRAM(void)
{

    PORT_BYTE_PNTR byte_reg_pntr ;

    byte_reg_pntr=0x2200;

	if( (BRAM_CHECK0 == 70) && (BRAM_CHECK1 == 5) && (BRAM_CHECK2 == 2) )
	{
		return;	
	}
	else
	{
		while( byte_reg_pntr < (0x22C0) )
		{   // Clear BRAM range (0x2200~0x22BF)
			*byte_reg_pntr = 0x00;
			byte_reg_pntr++; ;
		}
		BRAM_CHECK0 = 70;
		BRAM_CHECK1 = 5;
		BRAM_CHECK2 = 2;
	}

	

}

//------------------------------------------------------------------------------
// The function of enabling KBC Input Buffer Full (60 64 port)Interrupt 
//------------------------------------------------------------------------------
void EnableKBCIBFInt(void)
{
	SET_MASK(IER3,Int_KBCIBF);
}

//------------------------------------------------------------------------------
//Disable Dynamic Cache
//------------------------------------------------------------------------------
void Disable_DCache(void)
{
	#if Disable_DCache_without_checking

	CACHDISR = 0x03;
	
	#else 
	
	//Disable DCache except IT8738
	if( ECHIPID2 != 0x38 )
	{
		CACHDISR = 0x03;
	}
	#endif
}


//------------------------------------------------------------------------------
//K8 function Enable
//------------------------------------------------------------------------------
void Enable_K8_Function(void)
{
	LDN = 0x07;
	SET_MASK(Index_2DH, BIT0);
}
