/*-----------------------------------------------------------------------------
 * Filename:  CORE_SMBUS.H
 * Function:  CORE_SMBUS.C Function prototype include definition
 *
 * Copyright (c) 2006-2009, ITE Tech. Inc. All Rights Reserved.
 *---------------------------------------------------------------------------*/

#include "Core_Type.h"
#ifndef CORE_SMBUS_H
#define CORE_SMBUS_H

/*-----------------------------------------------------------------------------
 * Data Parameter definition
 *---------------------------------------------------------------------------*/

#define SMBusTOC    200     // SMbus re-try counter

#define SMBusChA    0x00    // SMbus channel A index
#define SMBusChB    0x01    // SMbus channel B index
#define SMBusChC    0x02    // SMbus channel C index
//#define SMBusChD    0x03    // SMbus channel D index

#define SMbusCh1	    0x00	// SMbus channel A index
#define SMbusCh2	    0x01	// SMbus channel B index
#define SMbusCh3	    0x02	// SMbus channel C index


//---------------------------------------------------
//V14.1 define
//---------------------------------------------------
#define	SMbusWQ			0x80	// Write Quick command
#define	SMbusRQ			0x00	// Read Quick command
#define	SMbusSBC			0x84	// Send Byte command
#define	SMbusRBC			0x04	// Receive Byte command
#define	SMbusWB			0x88	// Write byte command
#define	SMbusRB			0x08	// Read byte command
#define	SMbusWW			0x8C	// Write word command
#define	SMbusRW			0x0C	// Read  word command
#define	SMbusWBK			0x94	// Write block command
#define	SMbusRBK			0x14	// Read block command

#define	SMBus_NeedPEC			0x01
#define	SMBus_NoPEC			0x00
//---------------------------------------------------


#define HOCTL_PEC_EN        BIT(7)  // PEC Enable
#define HOCTL_SRT    	    BIT(6)  // Start
#define HOCTL_LABY   	    BIT(5)  // Last Byte
#define HOCTL_SMCD2  	    BIT(4)  // SMBus Command
#define HOCTL_SMCD1    	    BIT(3)  // SMBus Command
#define HOCTL_SMCD0    	    BIT(2)  // SMBus Command
#define HOCTL_KILL   	    BIT(1)  // Kill
#define HOCTL_INTREN  	    BIT(0)  // Host Interrupt Enable


#define SMBus_Busy      0x01    // SMBus clock pin or data pin is low
#define SMBus_Free      0x00    // SMBus clock pin and data pin are both high

#define SMBus_CanUse    0x01    // SMBus interface can be used.
#define SMBus_CanNotUse 0x00    // SMBus interface can't be used.

#define SMBus_AccessType_Fucn   0x01	//for func
#define SMBus_AccessType_Table  0x00	//for Scan center

#define ACK_Done			0x33
#define ACK_Error			0x44
#define ACK_Start           0xFF


/*-----------------------------------------------------------------------------
 * Data Structure definition
 *---------------------------------------------------------------------------*/
typedef struct tI2cControlReg
{
	XBYTE	*bCtrl;
	XBYTE	*bCtrl2;
	XBYTE	*bSlaveAddr;
	XBYTE	*bStatus;
	XBYTE	*bI2cdata;
} tsI2cControlReg;


typedef struct RSmbusStruct
{
    BYTE    address;
    BYTE    cmd;
    XBYTE   *smbdata;
} sRSmbusStruct;



//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
typedef struct WSmbusByteStruct
{
    BYTE    address;
    BYTE    cmd;
    XBYTE   *smbdata01;
    BYTE    data01;
} sWSmbusStruct;
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

typedef struct SMBusStruct
{
	XBYTE	*SMBusCTL	;	 
	XBYTE	*SMBusADR	;
	XBYTE	*SMBusCMD	;
	XBYTE	*SMBusSTA	;
	XBYTE	*SMBusData0	;
	XBYTE	*SMBusData1	;	
	XBYTE	*SMBusBData	;	
	XBYTE	*SMBusIER	;	
	XBYTE	*SMBusISR	;
	BYTE	IERFlag		;	
	XBYTE	*SMBusPEC	;
} sSMBus;

extern sSMBus code asSMBus[];

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
typedef struct ResetSMBusS
{
	XBYTE	*SMBusSTA	;
	XBYTE	*SMBusCTL2	;
	XBYTE	*SMBusPinCTL;
	XBYTE	*GPIOReg	;
	BYTE	GPIOData	;
	XBYTE   *recoverCunt;
} sResetSMBusS;

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -



/*-----------------------------------------------------------------------------
 * External Calling Process
 *---------------------------------------------------------------------------*/
extern bit bI2cMasterWrite(BYTE bChannel, BYTE bSlaveAddress, BYTE bDataLength, XBYTE *Var);

//=============================================================
//Under 
//
//V14 core_smbus
//=============================================================
//----------------------------------------------------------------------------
// 	
//----------------------------------------------------------------------------
extern void DelayInact(void);
extern void ResetSMBus(BYTE Channel);
extern void CalcCRC8(BYTE sourcebyte);
extern BYTE CheckSMBusFree(BYTE channel);
extern BYTE CheckSMBusInterfaceCanbeUse(BYTE channel, BYTE accesstype);
extern void Core_Init_SMBus(void);

extern BYTE bRWSMBus(BYTE Channel,BYTE Protocol,BYTE Addr,BYTE Comd,XBYTE *Var,BYTE PECSupport);
extern BYTE bRSMBusBlock(BYTE Channel,BYTE Protocol,BYTE Addr,BYTE Comd,XBYTE *Var);
extern BYTE bWSMBusBlock(BYTE Channel,BYTE Protocol,BYTE Addr,BYTE Comd,XBYTE *Var,BYTE ByteCont,BYTE PECsupport);
extern BYTE bSMBusSendByte(BYTE Channel,BYTE Addr,BYTE SData);
extern BYTE bSMBusReceiveByte(BYTE Channel,BYTE Addr,XBYTE *Var);
/*-----------------------------------------------------------------------------
 * Internal Process Definition
 *---------------------------------------------------------------------------*/

// TIMERS (CORE_TIMER.CORE_ADC)
//

//#define T_Timer_25ms        (0xFFFF-19165)


//-----------------------------------------------------------------------------
#endif

