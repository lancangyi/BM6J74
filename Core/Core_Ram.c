/*-----------------------------------------------------------------------------
 * Filename: CORE_MEMORY.C     For Chipset: ITE.IT85XX
 *
 * Function: Memory Definition for extern all code base reference
 *
 * [Memory Map Description]
 *
 * =Chip Internal= 0x00-0xFF
 * 0x00-0xFF     For Kernel and Chip Level use
 *
 ***************************************************
 * Chip 8500       : External ram 0x000-0x7FF
 * Chip Other 85XX : External ram 0x000-0xFFF
 ***************************************************
 * Memory Map :
 * 0x000-0x0FF   For Kernel Core/Module
 * 0x100-0x1FF   OEM RAM
 * 0x200-0x2FF   OEM RAM
 * 0x300-0x3FF   OEM RAM
 * 0x400-0x4FF   OEM RAM
 * 0x500-0x5FF   OEM RAM
 * 0x600-0x6FF   For ITE flash utility,EC SPI rom read write function, and ramdebug function.
 * 0x700-0x7FF   For Keil C Complier and Ram Code Space (for SPI programming).
 * 0x800-0x8FF   OEM RAM
 * 0x800-0x9FF   OEM RAM
 * 0xA00-0xAFF   OEM RAM
 * 0xB00-0xBFF   OEM RAM
 * 0xC00-0xCFF   OEM RAM
 * 0xD00-0xDFF   OEM RAM
 * 0xE00-0xEFF   OEM RAM
 * 0xF00-0xFFF   OEM RAM
 *
 * Copyright (c) 2006-2009, ITE Tech. Inc. All Rights Reserved.
 *---------------------------------------------------------------------------*/

//-----------------------------------------------------------------------------
// Common Header Include
//-----------------------------------------------------------------------------
#include "Core_Inc.h"
#include "Oem_Inc.h"

/*****************************************************************************/
/* 8032 BANK REGISTER RAM AREA  (0x00 ~ 0x1F) ********************************/
/*****************************************************************************/
// 0x00 - 0x1F for Chip R0-R7 Bank 0-3


/*****************************************************************************/
/* INTERNAL BIT ADDRESS RAM AREA  (0x20 ~ 0x2F) ******************************/
/*****************************************************************************/

volatile unsigned char bdata Service	_at_ 0x20;
sbit F_Service_000  	= Service^0;
sbit F_Service_001 	= Service^1;
sbit F_Service_002 	= Service^2;
sbit F_Service_003 	= Service^3;
sbit F_Service_004 	= Service^4;
sbit F_Service_005  	= Service^5;
sbit F_Service_006  	= Service^6;
sbit F_Service_007  	= Service^7;

volatile unsigned char bdata Service1 _at_ 0x21;	
sbit F_Service_008 	= Service1^0;
sbit F_Service_009	= Service1^1;
sbit F_Service_00A     = Service1^2;
sbit F_Service_00B     = Service1^3;
sbit F_Service_00C  	= Service1^4;
sbit F_Service_00D	= Service1^5;
sbit F_Service_00E  	= Service1^6; 
sbit F_Service_00F  	= Service1^7;

volatile unsigned char bdata SWKBCFlag _at_ 0x22;
sbit KbdNeedResponseFlag	= SWKBCFlag^0;
sbit ExtendMatrix				= SWKBCFlag^1;
sbit Isr_Int1_Occur         		= SWKBCFlag^2;
sbit FastA20		        		= SWKBCFlag^3;
sbit ChkAUXRespFlag2		= SWKBCFlag^4;
sbit ECCheckBurstMode		= SWKBCFlag^5;
sbit OEM_Isr_Int1_Request   	= SWKBCFlag^6;
sbit FnStickKey             		= SWKBCFlag^7;

volatile unsigned char bdata Ccb42 _at_ 0x23;
sbit Ccb42_INTR_KEY  	= Ccb42^0;
sbit Ccb42_INTR_AUX  	= Ccb42^1;
sbit Ccb42_SYS_FLAG  	= Ccb42^2;
sbit Ccb42_RV1       		= Ccb42^3;
sbit Ccb42_DISAB_KEY 	= Ccb42^4;
sbit Ccb42_DISAB_AUX 	= Ccb42^5;
sbit Ccb42_XLATE_PC  	= Ccb42^6;
sbit Ccb42_RV2       		= Ccb42^7;

volatile unsigned char bdata Led_Data _at_ 0x24;
sbit Led_Data_SCROLL 	= Led_Data^0;
sbit Led_Data_NUM    		= Led_Data^1;
sbit Led_Data_CAPS   		= Led_Data^2;
sbit Led_Data_OVL    		= Led_Data^3;
sbit Led_Data_LED4   		= Led_Data^4;
sbit Led_Data_LED5   		= Led_Data^5;
sbit Led_Data_LED6   		= Led_Data^6;
sbit Led_Data_LED7   		= Led_Data^7;

volatile unsigned char bdata AuxTestFlagS _at_ 0x25;
sbit PS2StartBit            	= AuxTestFlagS^0;
sbit MouseDriverIn          	= AuxTestFlagS^1;
sbit KeyboardDriverIn       = AuxTestFlagS^2;
sbit AUX2ByteCommand	= AuxTestFlagS^3;
sbit AuxTestFlagS_RV1	= AuxTestFlagS^4;
sbit AuxTestFlagS_RV2	= AuxTestFlagS^5;
sbit AuxTestFlagS_RV3	= AuxTestFlagS^6;
sbit AuxTestFlagS_RV4	= AuxTestFlagS^7;

volatile unsigned char bdata MULPX _at_ 0x26;
sbit EnableTP      			= MULPX^0;
sbit MULPX_Mx_state2    	= MULPX^1;
sbit MULPX_Mx_state3    	= MULPX^2;
sbit MULPX_Multiplex    	= MULPX^3;
sbit MULPX_RV1          		= MULPX^4;
sbit MULPX_RV2          		= MULPX^5;
sbit MULPX_RV3          		= MULPX^6;
sbit MULPX_RV4          		= MULPX^7;
/*****************************************************************************/
//      NOTE :
/*****************************************************************************/
// Don't use bit addressble 0x2E and 0x2F.
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
//      BIT ADDRESS END MARK
//                          >>----------->
//                                          DIRECT START MARK
/*****************************************************************************/


/*****************************************************************************/
/* INTERNAL DIRECT RAM AREA       (0x30 ~ 0x7F) ******************************/
/*****************************************************************************/
//-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
IBYTE       _R1                             _at_ 0x30;
IBYTE       _R2                             _at_ 0x31;
IBYTE       _R3                             _at_ 0x32;
IBYTE       _R4                             _at_ 0x33;
IBYTE       _R5                             _at_ 0x34;
IBYTE       _R6                             _at_ 0x35;
IWORD     _W1                             _at_ 0x36;		//0x36-0x37

BITS_8      CORE_PMFLAG                     _at_ 0x38;
IBYTE	_FlashCMD					_at_	0x39;
IBYTE	_SEND						_at_	0x3A;
IBYTE	ExitRamCodeCommand		_at_	0x3B;
IBYTE	Kernel_Code_Version			_at_	0x3C;


//0x60-0x6D  PM1/PM2
//-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
IBYTE       PM1Cmd				_at_ 0x60;
IBYTE       PM1Step				_at_ 0x61;
IBYTE       PM1StepSP				_at_ 0x62;
IBYTE       PM1Data				_at_ 0x63;
IBYTE       PM1Data1				_at_ 0x64;
IBYTE       PM1Data2				_at_ 0x65;
IBYTE       PM2Cmd				_at_ 0x66;
IBYTE       PM2Step				_at_ 0x67;
IBYTE       PM2StepSP				_at_ 0x68;
IBYTE       PM2Data				_at_ 0x69;
IBYTE       PM2Data1				_at_ 0x6A;
IBYTE       PM2Data2				_at_ 0x6B;
IBYTE       ECUnProcessCnt			_at_ 0x6C;
IBYTE       ECUnProcessCnt2		_at_ 0x6D;

//-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
//***GAP***
//0x6E-0x6F
//-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --

BYTE code *idata Tmp_code_pointer	_at_ 0x70;  
IBYTE	KBHICmd 			_at_ 0x72;
IBYTE	KBHIStep 			_at_ 0x73;
IBYTE	KBHIData			_at_ 0x74;
IBYTE	KBHIData1			_at_ 0x75;
IBYTE	KBHIData2			_at_ 0x76;
//-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
//***GAP***
//0x77-0x7F
//-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --


/*****************************************************************************/
/*****************************************************************************/
//      DIRECT END MARK
//                          >>----------->
//                                          INDIRECT START MARK
/*****************************************************************************/
/* INTERNAL INDIRECT RAM AREA     (0x80 ~ 0xFF) ******************************/
/*****************************************************************************/
//----------------------------------------------------------------------------
// Internal ram variables (Indirect)[0x80-0xCF]
//----------------------------------------------------------------------------

//For SWKBC
IIBYTE 	KB_Command                 	_at_ 0x80;
IIBYTE 	KB_CodeSet                	_at_ 0x81;
IIBYTE 	PS2KB_Typematic         	_at_ 0x82;
IIBYTE 	Save_Typematic            	_at_ 0x83;
IIBYTE 	Main_KB_CHN               	_at_ 0x84;
IIBYTE 	AuxFlags[3]				_at_ 0x85;	
IIBYTE 	Main_KB_ACK_CUNT		_at_ 0x88;
IIBYTE 	KBHIReponse 			_at_ 0x89;
IIBYTE	Pass_Buff[8]				_at_ 0x8A;
IIBYTE 	Pass_Buff_Idx			_at_ 0x92;
IIBYTE  	Pass_On					_at_ 0x93;
IIBYTE 	Pass_Off				_at_ 0x94;
IIBYTE 	Pass_Make1				_at_ 0x95;
IIBYTE  	Pass_Make2				_at_ 0x96;
FLAGS 	Flag						_at_ 0x97;// 2 bytes

//-----------------------------------------------------------------------------
XBYTE	*idata  Tmp_XPntr			_at_ 0x99;  //  2 bytes
XBYTE	*idata Tmp_XPntr1	 		_at_ 0x9B;	//  2 bytes

IIBYTE  	IVECT_BACKUP				_at_ 0x9D;	//For incorrect IVECT number issue

//--- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- -
//Stack                             0xD0 - 0xFF         // 48 bytes
//
// Don't use Idata (0xD0 ~ 0xFF).
// Idata (0xD0 ~ 0xFF). for stack point.
//--- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- -


/*****************************************************************************/
/*****************************************************************************/
//      INTERNAL END MARK
//                          >>----------->
//                                          EXTERNAL START MARK
/*****************************************************************************/
/* EXTERNAL RAM AREA      (0x0000 ~ 0x00FF) **********************************/
/*****************************************************************************/

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
#define OEMHook_MemBase     0x0000  //-0x001F
XBYTE	 Timer1msCnt				_at_ 0x0000;
XBYTE	Timer5msCnt				_at_ 0x0001;
XBYTE	Timer5msCntB				_at_ 0x0002;
XBYTE	Timer100msCnt				_at_ 0x0003;
XBYTE	Timer100msCntB				_at_ 0x0004;
XBYTE	Timer100msCntC				_at_ 0x0005;
XBYTE	Timer1SecCnt				_at_ 0x0006;
XBYTE	Timer1MinCnt				_at_ 0x0007;
XBYTE	Timer125msCnt				_at_ 0x0008;
XBYTE	Timer250msCnt				_at_ 0x0009;
XBYTE	RSTStatus					_at_ 0x000A;

//-----------------------------------------------------------------------------
//For INPUTDEBOUNCE
//-----------------------------------------------------------------------------
XBYTE   DEBOUNCE_FLAG1				_at_ 0x000B;
XBYTE   DEBOUNCE_FLAG2				_at_ 0x000C;
XBYTE   DEBOUNCE_CONT0				_at_ 0x000D;
XBYTE   DEBOUNCE_CONT1				_at_ 0x000E;
XBYTE   DEBOUNCE_CONT2				_at_ 0x000F;
XBYTE   DEBOUNCE_CONT3				_at_ 0x0010;
XBYTE   DEBOUNCE_CONT4				_at_ 0x0011;
XBYTE   DEBOUNCE_CONT5				_at_ 0x0012;
XBYTE   DEBOUNCE_CONT6				_at_ 0x0013;
XBYTE   DEBOUNCE_CONT7				_at_ 0x0014;
XWORD BtnOverTimer1				_at_ 0x0015;
XWORD BtnOverTimer2				_at_ 0x0017;

//For checksum
//----------------------------------------------------------------------------
XWORD Calc_Checksum				_at_ 0x0019;	//For CalculateChecksum 0x0019,0x001A
XWORD ROM_Checksum				_at_ 0x001B;	//For CalculateChecksum 0x001B,0x001C
XBYTE	Checksum_compare			_at_ 0x001D;	//For CalculateChecksum 
//----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
#define SCI_MemBase         0x0020  //-0x002F
//#define EVENT_BUFFER_SIZE   9
XBYTE   SCI_Event_Buffer[10]                _at_ SCI_MemBase+0x00;
XBYTE   SCI_Event_In_Index                  _at_ SCI_MemBase+0x0A;
XBYTE   SCI_Event_Out_Index                 _at_ SCI_MemBase+0x0B;
XBYTE   SCI_StepTimer                       _at_ SCI_MemBase+0x0D;
XBYTE   SCI_LastQueryEvent                  _at_ SCI_MemBase+0x0E;
XBYTE   SCI_QueryEvent                      _at_ SCI_MemBase+0x0F;

//-----------------------------------------------------------------------------
#define SMI_MemBase         0x0030  //-0x003F
//#define EVENT_BUFFER_SIZE   9
XBYTE   SMI_Event_Buffer[10]                _at_ SMI_MemBase+0x00;
XBYTE   SMI_Event_In_Index                  _at_ SMI_MemBase+0x0A;
XBYTE   SMI_Event_Out_Index                 _at_ SMI_MemBase+0x0B;
XBYTE   SMI_StepTimer                       _at_ SMI_MemBase+0x0D;
XBYTE   SMI_LastQueryEvent                  _at_ SMI_MemBase+0x0E;
XBYTE   SMI_QueryEvent                      _at_ SMI_MemBase+0x0F;
//-----------------------------------------------------------------------------

#define Record_MemBase      0x0040  //-0x04F
XBYTE   SCI_SMI_Event_Record[15]			_at_ Record_MemBase+0x00;
XBYTE   SCI_SMI_Index_Record			_at_ Record_MemBase+0x0F; 
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
//0x0050---0x0063
//For PECI use
//-----------------------------------------------------------------------------
#define PECI_FW_Base        0x0050
XBYTE	AWFCS_EN				_at_	PECI_FW_Base+0x00;
XBYTE	PECI_FIFO_LB			_at_	PECI_FW_Base+0x01;
XBYTE	PECI_FIFO_HB			_at_	PECI_FW_Base+0x02;
XBYTE	CPUTcontrol				_at_ 	PECI_FW_Base+0x03;
XBYTE	CPUTjmax				_at_ 	PECI_FW_Base+0x04;
XBYTE	PECI_readBuffer[5]		_at_	PECI_FW_Base+0x05 ;		//0x55-0x59
XBYTE	PECI_readBuffer2[5]		_at_	PECI_FW_Base+0x0A ;		//0x5A-0x5E
XBYTE	PECI_PowerUnit			_at_	PECI_FW_Base+0x0F ;
XBYTE	PECI_EnergyUnit			_at_	PECI_FW_Base+0x10 ;
XBYTE	PECI_TimeUnit			_at_	PECI_FW_Base+0x11 ;
XBYTE	CPUTemperature			_at_ 	PECI_FW_Base+0x12;
XBYTE	CPUTermMargin			_at_ 	PECI_FW_Base+0x13;


//-----------------------------------------------------------------------------
//0x006E---
//For UART_TX_RX buffer
//-----------------------------------------------------------------------------
XBYTE	UART_R_IIR						_at_	0x006C;
XBYTE	UART_R_LSR						_at_	0x006D;
XBYTE	UART_RxIndex					_at_	0x006E;
XBYTE	UART_TxIndex					_at_	0x006F;
XBYTE	UART_TxBuff[8]					_at_	0x0070;
XBYTE	UART_RxBuff[8]					_at_	0x0078;


//-----------------------------------------------------------------------------
//0x0080---0x00
//PowerCtrl
//-----------------------------------------------------------------------------
#define	Power_Ctrl_Base		0x0080
XBYTE	SysPowState				_at_		Power_Ctrl_Base+0x00;
XBYTE	CtrlPowStep				_at_		Power_Ctrl_Base+0x01;
XWORD	PowSeqDelay			_at_		Power_Ctrl_Base+0x02;
XBYTE	AutoColdBootTimer		_at_		Power_Ctrl_Base+0x04;
XBYTE	ColdBootTimer			_at_		Power_Ctrl_Base+0x05;
XWORD	LockSwitchPowerOn		_at_		Power_Ctrl_Base+0x06;
XWORD	PowSwOverTimer		_at_		Power_Ctrl_Base+0x08;
XBYTE	DeepSleepCountDown	_at_		Power_Ctrl_Base+0x0A;


XBYTE	Read_SMLink1_Step			_at_ 0x008E;
XBYTE	SMLink1_Temp				_at_ 0x008F;
//-----------------------------------------------------------------------------
//For Core_Flash.c
//=========================================================================================
XBYTE	SPIIDBuf[4]							_at_ 0x90;	
XBYTE	SPIIndex							_at_ 0x94;	
XBYTE	SPIAddrCycle[3]						_at_ 0x95;	
XBYTE	SPIAEraseCmd						_at_ 0x98;	
XBYTE	SPIReadStatus						_at_ 0x99;	
XBYTE	SPIWriteStatus						_at_ 0x9A;	
XBYTE	*SPIDataPointer						_at_ 0x9B;	
XBYTE	SPIID								_at_ 0x9D;	
XBYTE	SSTDeviceID  						_at_ 0x9E;


//-----------------------------------------------------------------------------
// SMBUS_Debug_Ram 0xA0-0xC6
//-----------------------------------------------------------------------------
#define	SMBUS_Debug_Ram	0x00A0

XBYTE	DB_SMBusFlag1					_at_ (SMBUS_Debug_Ram + 0x00);
XBYTE	DB_SMBusFlag2					_at_ (SMBUS_Debug_Ram + 0x01);
XBYTE	DB_SMBusFlag3					_at_ (SMBUS_Debug_Ram + 0x02);
XBYTE	DB_SMBusAck1					_at_ (SMBUS_Debug_Ram + 0x03);
XBYTE	DB_SMBusAddr					_at_ (SMBUS_Debug_Ram + 0x04);
XBYTE	DB_SMBusCmd					_at_ (SMBUS_Debug_Ram + 0x05);
XBYTE	DB_SMBusBCunt					_at_ (SMBUS_Debug_Ram + 0x06);
XBYTE	DB_SMBusData[32]				_at_ (SMBUS_Debug_Ram + 0x07);	//0xA7~0xC6


//-----------------------------------------------------------------------------
// SWKBC 0x00D0 --
//-----------------------------------------------------------------------------
#define	SWKBC_RAMBASE	0x00D0
XBYTE	xbKEY_BUFF[KBF_SIZE]			_at_ (SWKBC_RAMBASE+0x00); //Scan code buffer storage
XBYTE	xbKbf_Head						_at_ (SWKBC_RAMBASE+0x10); //Scan code buffer head
XBYTE	xbKbf_Tail						_at_ (SWKBC_RAMBASE+0x11); //Scan code buffer tail
XBYTE	bTMrepeat						_at_ (SWKBC_RAMBASE+0x12);
XBYTE	bTMdelay						_at_ (SWKBC_RAMBASE+0x13);
XBYTE	KBDataPending[4]      				_at_ (SWKBC_RAMBASE + 0x14);
XBYTE	KBPendingRXCount    				_at_ (SWKBC_RAMBASE + 0x18);
XBYTE	KBPendingTXCount    				_at_ (SWKBC_RAMBASE + 0x19);

//-----------------------------------------------------------------------------
// CIR Buffer 0xF0
//-----------------------------------------------------------------------------
XBYTE	CIR_Buffer[16]					_at_	0x00F0;
