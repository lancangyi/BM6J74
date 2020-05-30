/*-----------------------------------------------------------------------------
 * Filename: CORE_MEMORY.C     For Chipset: ITE.IT87XX
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
#ifndef CORE_RAM_H
#define CORE_RAM_H


//----------------------------------------------------------------------------
// Bit addressing variables [0x20-0x2F]
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
// Events that require service in main. 
//----------------------------------------------------------------------------
extern BBYTE Service;
extern bit F_Service_000;
extern bit F_Service_001;
extern bit F_Service_002;
extern bit F_Service_003;
extern bit F_Service_004;
extern bit F_Service_005;
extern bit F_Service_006;
extern bit F_Service_007;

extern BBYTE Service1;
extern bit F_Service_008;
extern bit F_Service_009;
extern bit F_Service_00A;
extern bit F_Service_00B;
extern bit F_Service_00C;
extern bit F_Service_00D;
extern bit F_Service_00E;
extern bit F_Service_00F;
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
extern BBYTE SWKBCFlag;
extern bit KbdNeedResponseFlag;
extern bit ExtendMatrix;	
extern bit Isr_Int1_Occur;
extern bit FastA20;
extern bit ChkAUXRespFlag2;
extern bit ECCheckBurstMode;
extern bit OEM_Isr_Int1_Request;
extern bit FnStickKey;

extern BBYTE Ccb42;
extern bit Ccb42_INTR_KEY;
extern bit Ccb42_INTR_AUX;
extern bit Ccb42_SYS_FLAG;
extern bit Ccb42_RV1;
extern bit Ccb42_DISAB_KEY;
extern bit Ccb42_DISAB_AUX;
extern bit Ccb42_XLATE_PC;
extern bit Ccb42_RV2;

//----------------------------------------------------------------------------
// tate of local keyboard LEDs. 
//----------------------------------------------------------------------------
extern BBYTE Led_Data; 
extern bit Led_Data_SCROLL;
extern bit Led_Data_NUM;
extern bit Led_Data_CAPS;
extern bit Led_Data_OVL;
extern bit Led_Data_LED4;
extern bit Led_Data_LED5;
extern bit Led_Data_LED6;
extern bit Led_Data_LED7;

//----------------------------------------------------------------------------
// PS2 interface control flag
//----------------------------------------------------------------------------
extern BBYTE AuxTestFlagS;
extern bit PS2StartBit;
extern bit MouseDriverIn;
extern bit KeyboardDriverIn;
extern bit AUX2ByteCommand;
extern bit AuxTestFlagS_RV1;
extern bit AuxTestFlagS_RV2;
extern bit AuxTestFlagS_RV3;
extern bit AuxTestFlagS_RV4;

//----------------------------------------------------------------------------
// MULPX - Active PS/2 Mulplexing control byte
//----------------------------------------------------------------------------
extern BBYTE MULPX;
extern bit EnableTP;
extern bit MULPX_Mx_state2;
extern bit MULPX_Mx_state3;
extern bit MULPX_Multiplex;
extern bit MULPX_RV1;
extern bit MULPX_RV2;
extern bit MULPX_RV3;
extern bit MULPX_RV4;


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

extern  	IBYTE       _R1;    //_at_ 0x30;
extern  	IBYTE       _R2;    //_at_ 0x31;
extern	IBYTE       _R3;//                             _at_ 0x32;
extern	IBYTE       _R4;//                             _at_ 0x33;
extern	IBYTE       _R5;//                             _at_ 0x34;
extern	IBYTE       _R6;//                             _at_ 0x35;
extern	IWORD      _W1;//                             _at_ 0x36;	//0x36-0x37
//--------------------------------------------------------------------------------
extern  BITS_8      CORE_PMFLAG;    //_at_ 0x38;
#define _CORE_PMFLAG		CORE_PMFLAG.byte
#define CORE_PMFLAG_S0		CORE_PMFLAG.fbit.bit0
#define CORE_PMFLAG_S1		CORE_PMFLAG.fbit.bit1
#define CORE_PMFLAG_S3		CORE_PMFLAG.fbit.bit2
#define CORE_PMFLAG_S4		CORE_PMFLAG.fbit.bit3
#define CORE_PMFLAG_S5		CORE_PMFLAG.fbit.bit4
#define OS_PMC2_Mode		CORE_PMFLAG.fbit.bit7
#define WAIT_SCI_CENTER	CORE_PMFLAG.fbit.bit6
#define OS_ACPI_Mode		CORE_PMFLAG.fbit.bit7
//--------------------------------------------------------------------------------
extern IBYTE	_FlashCMD;				//_at_	0x39;
extern IBYTE	_SEND;					//_at_	0x3A;
extern IBYTE	ExitRamCodeCommand;	//_at_	0x3B;
extern IBYTE	Kernel_Code_Version;	//_at_	0x3C;




//-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
extern  IBYTE       PM1Cmd;                             //_at_ 0x60;
extern  IBYTE       PM1Step;                            //_at_ 0x61;
extern  IBYTE       PM1StepSP;                          //_at_ 0x62;
extern  IBYTE       PM1Data;                            //_at_ 0x63;
extern  IBYTE       PM1Data1;                           //_at_ 0x64;
extern  IBYTE       PM1Data2;                           //_at_ 0x65;
extern  IBYTE       PM2Cmd;                             //_at_ 0x66;
extern  IBYTE       PM2Step;                            //_at_ 0x67;
extern  IBYTE       PM2StepSP;				//_at_ 0x68;
extern  IBYTE       PM2Data;                            //_at_ 0x69;
extern  IBYTE       PM2Data1;				//_at_ 0x6A;
extern  IBYTE       PM2Data2;				//_at_ 0x6B;
extern  IBYTE       ECUnProcessCnt;			//_at_ 0x6C;
extern  IBYTE       ECUnProcessCnt2;		//_at_ 0x6D;
//-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --


extern  BYTE code 	*idata Tmp_code_pointer;		//_at_ 0x70
extern IBYTE KBHICmd;// 		_at_ 0x72;
extern IBYTE KBHIStep;// 		_at_ 0x73;
extern IBYTE KBHIData;//		_at_ 0x74;
extern IBYTE KBHIData1;//		_at_ 0x75;
extern IBYTE KBHIData2;//		_at_ 0x76;

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
extern IIBYTE 	KB_Command;//    _at_ 0x80;
extern IIBYTE      	KB_CodeSet;//       _at_ 0x81;
extern IIBYTE      	PS2KB_Typematic;// _at_ 0x82;
extern IIBYTE      	Save_Typematic;//   _at_ 0x83;
extern IIBYTE 	Main_KB_CHN;//     _at_ 0x84;
extern IIBYTE 	AuxFlags[];//     _at_ 0x85~87;          
#define DEVICE_IS_MOUSE                          BIT7
#define DEVICE_IS_KEYBOARD                    BIT6
#define DEVICE_IS_MAIN_MOUSE               BIT5
#define DEVICE_IS_MAIN_KB                       BIT4
#define DEVICE_NEED_CONFIG                    BIT3
#define DEVICE_MS_DRIVER_NO_MATCH   BIT2
#define DEVICE_NEED_INIT                          BIT1
#define DEVICE_IS_ATTACHED                     BIT0

extern IIBYTE 	Main_KB_ACK_CUNT;//   _at_ 0x88
extern IIBYTE 	KBHIReponse;// 		    _at_ 0x89;
extern IIBYTE		Pass_Buff[8];			//_at_ 0x8A;
extern IIBYTE 	Pass_Buff_Idx;		//_at_ 0x92;
extern IIBYTE  	Pass_On;			//_at_ 0x93;
extern IIBYTE 	Pass_Off;			//_at_ 0x94;
extern IIBYTE 	Pass_Make1;		//_at_ 0x95;
extern IIBYTE  	Pass_Make2;		//_at_ 0x96;
extern FLAGS 		Flag	;				//_at_ 0x97;// 2 bytes
//----------------------------------------------------------------------------
// Flag
//----------------------------------------------------------------------------
extern 	FLAGS	Flag;
#define SCAN_INH		 bit0 // 1 = Scanner transmission inhibited. 
#define SENDING_SCAN_RC  bit1 // For diagnostic mode. 
#define PASS_READY       bit2 // Password loaded. 
#define NEW_PRI_K        bit3 // Switch to new primary keyboard. 
#define NEW_PRI_M        bit4 // Switch to new primary mouse. 
#define VALID_SCAN       bit5
#define LED_ON           bit6
#define ENTER_LOW_POWER  bit7 // Go into low power mode. 
#define ACPI_IN_PROGRESS bit8
#define ACPI_SMB_ALARM   bit9
#define LEGACY_SMB_ALARM bit10
#define ALT_PRESSED      bit11// External keyboard ALT key state. 
#define CTRL_PRESSED     bit12// External keyboard CTRL key state. 
#define DETECT_EC_B0     bit13// Used to allow Insyde Software's 
#define DETECT_EC_B1     bit14// embedded controller to be detected.
#define Aux_Not_RESP     bit15



extern  XBYTE *idata    Tmp_XPntr;				//_at_ 0x99
extern  XBYTE	*idata 	Tmp_XPntr1;	 		//_at_ 0x9B;

extern	IIBYTE  	IVECT_BACKUP;				//_at_ 0x9D;	//For incorrect IVECT number issue

/*****************************************************************************/
/*****************************************************************************/
//      INTERNAL END MARK
//                          >>----------->
//                                          EXTERNAL START MARK
/*****************************************************************************/
/* EXTERNAL RAM AREA      (0x0000 ~ 0x00FF) **********************************/
/*****************************************************************************/

extern XBYTE   Timer1msCnt;			//_at_ 0x0000;
extern  XBYTE   Timer5msCnt;                //_at_ 0x00001;
extern  XBYTE   Timer5msCntB;               //_at_ 0x0002;
extern  XBYTE   Timer100msCnt;              //_at_ 0x0003;
extern  XBYTE   Timer100msCntB;             //_at_ 0x0004;
extern  XBYTE   Timer100msCntC;             //_at_ 0x0005;
extern  XBYTE   Timer1SecCnt;               //_at_ 0x0006;
extern  XBYTE   Timer1MinCnt;               //_at_ 0x0007;
extern  XBYTE   Timer125msCnt;              //_at_ 0x0008;
extern  XBYTE   Timer250msCnt;              //_at_ 0x0009;
extern XBYTE	RSTStatus;				//_at_ 0x000A;

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//For INPUTDEBOUNCE
//-----------------------------------------------------------------------------
extern  XBYTE   DEBOUNCE_FLAG1;				//_at_ OEMHook_MemBase+0x0B;
extern  XBYTE   DEBOUNCE_FLAG2;				//_at_ OEMHook_MemBase+0x0C;
extern  XBYTE   DEBOUNCE_CONT0;				//_at_ OEMHook_MemBase+0x0D;
extern  XBYTE   DEBOUNCE_CONT1;				//_at_ OEMHook_MemBase+0x0E;
extern  XBYTE   DEBOUNCE_CONT2;				//_at_ OEMHook_MemBase+0x0F;
extern  XBYTE   DEBOUNCE_CONT3;				//_at_ OEMHook_MemBase+0x10;
extern  XBYTE   DEBOUNCE_CONT4;				//_at_ OEMHook_MemBase+0x11;
extern  XBYTE   DEBOUNCE_CONT5;				//_at_ OEMHook_MemBase+0x12;
extern  XBYTE   DEBOUNCE_CONT6;				//_at_ OEMHook_MemBase+0x13;
extern  XBYTE   DEBOUNCE_CONT7;				//_at_ OEMHook_MemBase+0x14;
extern  XWORD BtnOverTimer1;				//_at_ OEMHook_MemBase+0x15;
extern  XWORD BtnOverTimer2;				//_at_ OEMHook_MemBase+0x17;
//-----------------------------------------------------------------------------

extern  XWORD Calc_Checksum;				//_at_ 0x0019;	//For CalculateChecksum 0x0019,0x001A
extern  XWORD ROM_Checksum;				//_at_ 0x001B;	//For CalculateChecksum 0x001B,0x001C
extern  XBYTE	Checksum_compare;				//_at_ 0x001D;	//For CalculateChecksum 
//-----------------------------------------------------------------------------


//#define SCI_MemBase         0x0020  //-0x002F
#define EVENT_BUFFER_SIZE   9
extern XBYTE   SCI_Event_Buffer[10];                //_at_ SCI_MemBase+0x00;
extern XBYTE   SCI_Event_In_Index;                 // _at_ SCI_MemBase+0x0A;
extern XBYTE   SCI_Event_Out_Index;               //  _at_ SCI_MemBase+0x0B;
extern XBYTE   SCI_StepTimer;                          //_at_ SCI_MemBase+0x0D;
extern XBYTE   SCI_LastQueryEvent;                 // _at_ SCI_MemBase+0x0E;
extern XBYTE   SCI_QueryEvent;                       //_at_ SCI_MemBase+0x0F;

//-----------------------------------------------------------------------------
//#define SMI_MemBase         0x0030  //-0x003F
#define EVENT_BUFFER_SIZE   9
extern XBYTE   SMI_Event_Buffer[10];                //_at_ SMI_MemBase+0x00;
extern XBYTE   SMI_Event_In_Index;                 // _at_ SMI_MemBase+0x0A;
extern XBYTE   SMI_Event_Out_Index;               //  _at_ SMI_MemBase+0x0B;
extern XBYTE   SMI_StepTimer;                          //_at_ SMI_MemBase+0x0D;
extern XBYTE   SMI_LastQueryEvent;                 // _at_ SMI_MemBase+0x0E;
extern XBYTE   SMI_QueryEvent;                        //_at_ SMI_MemBase+0x0F;
//-----------------------------------------------------------------------------
//#define Record_MemBase      0x0040  //-0x04F
extern XBYTE   SCI_SMI_Event_Record[15];		//_at_ Record_MemBase+0x00;
extern XBYTE   SCI_SMI_Index_Record;			//_at_ Record_MemBase+0x0F; 
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
//0x0050---0x0063
//For PECI use
//-----------------------------------------------------------------------------
//#define PECI_FW_Base        0x50
extern XBYTE	AWFCS_EN;				//_at_	PECI_FW_Base+0x00;
extern XBYTE	PECI_FIFO_LB;			//_at_	PECI_FW_Base+0x01;
extern XBYTE	PECI_FIFO_HB;			//_at_	PECI_FW_Base+0x02;
extern XBYTE	CPUTcontrol;			//_at_ 	PECI_FW_Base+0x03;
extern XBYTE	CPUTjmax;				//_at_ 	PECI_FW_Base+0x04;
extern XBYTE	PECI_readBuffer[5];		//_at_	PECI_FW_Base+0x05 ;		//0x55-0x59
extern XBYTE	PECI_readBuffer2[5];		//_at_	PECI_FW_Base+0x0A ;		//0x5A-0x5E
extern XBYTE	PECI_PowerUnit;			//_at_	PECI_FW_Base+0x0F ;
extern XBYTE	PECI_EnergyUnit;		//_at_	PECI_FW_Base+0x10 ;
extern XBYTE	PECI_TimeUnit;			//_at_	PECI_FW_Base+0x11 ;
extern XBYTE	CPUTemperature;		//_at_ 	PECI_FW_Base+0x12;
extern XBYTE	CPUTermMargin;			//_at_ 	PECI_FW_Base+0x13;


//-----------------------------------------------------------------------------
//0x006E---
//For UART_TX_RX buffer
//-----------------------------------------------------------------------------
extern XBYTE	UART_R_IIR;						//_at_	0x006C;
extern XBYTE	UART_R_LSR;					//_at_	0x006D;
extern XBYTE	UART_RxIndex;					//_at_	0x006E;
extern XBYTE	UART_TxIndex;					//_at_	0x006F;
extern XBYTE	UART_TxBuff[8];					//_at_	0x0070;
extern XBYTE	UART_RxBuff[8];					//_at_	0x0078;


//-----------------------------------------------------------------------------
//0x0080---0x00
//PowerCtrl
//-----------------------------------------------------------------------------
//#define	Power_Ctrl_Base		0x0080
extern XBYTE	SysPowState;				//_at_		Power_Ctrl_Base+0x00;
extern XBYTE	CtrlPowStep;					//_at_		Power_Ctrl_Base+0x01;
extern XWORD	PowSeqDelay;			//_at_		Power_Ctrl_Base+0x02;
extern XBYTE	AutoColdBootTimer;			//_at_		Power_Ctrl_Base+0x04;
extern XBYTE	ColdBootTimer;				//_at_		Power_Ctrl_Base+0x05;
extern XWORD	LockSwitchPowerOn;		//_at_		Power_Ctrl_Base+0x06;
extern XWORD	PowSwOverTimer;		//_at_		Power_Ctrl_Base+0x08;
extern XBYTE	DeepSleepCountDown;		//_at_		Power_Ctrl_Base+0x0A;


extern XBYTE	Read_SMLink1_Step;			//_at_ 0x008E;
extern XBYTE	SMLink1_Temp;				//_at_ 0x008F;


extern 	XBYTE	SPIIDBuf[];				// 	_at_ 0x90
extern 	XBYTE	SPIIndex;				// 	_at_ 0x94	
extern	XBYTE	SPIAddrCycle[];			//	_at_ 0x95
extern	XBYTE	SPIAEraseCmd;			//	_at_ 0x98
extern	XBYTE	SPIReadStatus;			//	_at_ 0x99	
extern	XBYTE	SPIWriteStatus;			//	_at_ 0x9A	
extern	XBYTE	*SPIDataPointer;		//	_at_ 0x9B
#define SPIDataPointerLowByte (*(XBYTE*)( 0x09C))	//	_at_ 0x9C	overlay SPIDataPointer low byte
extern 	XBYTE	SPIID;					// 	_at_ 0x9D
extern	XBYTE   SSTDeviceID;			//	_at_ 0x9E

//-----------------------------------------------------------------------------
//#define	SMBUS_Debug_Ram	0x00A0

extern XBYTE	DB_SMBusFlag1;					//_at_ (SMBUS_Debug_Ram + 0x00);
extern XBYTE	DB_SMBusFlag2;					//_at_ (SMBUS_Debug_Ram + 0x01);
extern XBYTE	DB_SMBusFlag3;					//_at_ (SMBUS_Debug_Ram + 0x02);
extern XBYTE	DB_SMBusAck1;					//_at_ (SMBUS_Debug_Ram + 0x03);
extern XBYTE	DB_SMBusAddr;					//_at_ (SMBUS_Debug_Ram + 0x04);
extern XBYTE	DB_SMBusCmd;					//_at_ (SMBUS_Debug_Ram + 0x05);
extern XBYTE	DB_SMBusBCunt;					//_at_ (SMBUS_Debug_Ram + 0x06);
extern XBYTE	DB_SMBusData[];					//_at_ (SMBUS_Debug_Ram + 0x07);	//32byte

//-----------------------------------------------------------------------------
// SWKBC 0x00D0 --
//-----------------------------------------------------------------------------
//#define	SWKBC_RAMBASE	0x00D0
extern XBYTE xbKEY_BUFF[];		//_at_ (SWKBC_RAMBASE+0x00); //Scan code buffer storage
extern XBYTE xbKbf_Head;					//_at_ (SWKBC_RAMBASE+0x10); //Scan code buffer head
extern XBYTE xbKbf_Tail;					//_at_ (SWKBC_RAMBASE+0x11); //Scan code buffer tail
extern XBYTE bTMrepeat;						//_at_ (SWKBC_RAMBASE+0x12);
extern XBYTE bTMdelay;						//_at_ (SWKBC_RAMBASE+0x13);
extern XBYTE KBDataPending[];      			//_at_ (SWKBC_RAMBASE + 0x14);
extern XBYTE KBPendingRXCount;    			//_at_ (SWKBC_RAMBASE + 0x18);
extern XBYTE KBPendingTXCount;    			//_at_ (SWKBC_RAMBASE + 0x19);


//-----------------------------------------------------------------------------
// CIR Buffer 0xF0
//-----------------------------------------------------------------------------
extern XBYTE	CIR_Buffer[16];					//_at_	0x00F0;

#endif	//__CORE_RAM_H__
