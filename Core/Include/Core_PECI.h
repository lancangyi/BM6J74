/*-----------------------------------------------------------------------------
 * TITLE: CORE_PECI.H
 *
 * Copyright (c) 2013, ITE Tech. Inc. All Rights Reserved.
 *---------------------------------------------------------------------------*/
#ifndef CORE_PECI_H
#define CORE_PECI_H

/*-----------------------------------------------------------------------------
 * Code Parameter
 *---------------------------------------------------------------------------*/
#define PECI_Softwave_AWFCS 0
#define PECI_HostID         0x01    // Host ID = PECI_HostID << 1 (bit7 ~ bit0)
#define PECI_CPU_ADDR       	0x30
#define PECI_Domain_0			0x00
#define PECI_Domain_1			0x01

#define _PECI_CPU_Tcontrol      16
#define _PECI_CPU_Tjmax      	100

//-----------------------------------------------------------------------------
// Define PECI command
//-----------------------------------------------------------------------------
#define PECI_CMD_GetDIB             0xF7
#define PECI_CMD_Pin                0x00
#define PECI_CMD_GetTemp            0x01
#define PECI_CMD_RdPkgConfig        0xA1  
#define PECI_CMD_WrPkgConfig        0xA5  
#define PECI_CMD_RdIAMSR            0xB1
#define PECI_CMD_WrIAMSR            0xB5
#define PECI_CMD_RdPCIConfig        0x61
#define PECI_CMD_WrPCIConfig        0x65
#define PECI_CMD_RdPCIConfigLocal   0xE1
#define PECI_CMD_WrPCIConfigLocal   0xE5

//-----------------------------------------------------------------------------
// Define completion code
//-----------------------------------------------------------------------------
#define PECI_CC_Valid           0x40
#define PECI_CC_TimeOut         0x80
#define PECI_CC_Ignored         0x90
// ----------------------------------------------------------------------------
// The index definition of PECI3.0 read/write Pkg command
// ----------------------------------------------------------------------------
#define PECI_Index_PTR		2		// Read the Package Temperature register
#define PECI_Index_AESR		3		 // Accumulated Energy Status Read
#define PECI_Index_TMR		10		// Read the Thermal Margin register
#define PECI_Index_TTR		16		 // Read the Maximum Allowed Processor Temperature
#define PECI_Index_PPL1		26		// Power limit 1
#define PECI_Index_PPL2		27		// Power limit 2
#define PECI_Index_PPSL		28		// PACKAGE_POWER_SKU[LOW]	TDP
#define PECI_Index_PPSH		29		// PACKAGE_POWER_SKU[High]		Max power
#define PECI_Index_PPSU		30		// Power SKU unit
#define PECI_Index_ARTR		31		// Accumulated Run Time Read

/*-----------------------------------------------------------------------------
 * External Calling Process
 *---------------------------------------------------------------------------*/
extern  BYTE PECI_ReadPowerUnit(void);
extern BYTE PECI_RdPkgConfig(BYTE HostTargetAddr, XBYTE *ReadData, BYTE Domain, BYTE Retry,BYTE Index, BYTE LSB, BYTE MSB, BYTE ReadLen, BYTE WriteLen);
extern BYTE PECI_WrPkgConfig(BYTE HostTargetAddr, XBYTE *WriteData, BYTE Domain, BYTE Retry,BYTE Index, BYTE LSB, BYTE MSB, BYTE ReadLen, BYTE WriteLen);
extern BYTE PECI_Host_Access_GetTemp(BYTE HostTargetAddr) ;
extern void Calc_Update_PECI_Temp(void);
extern void PECI_ReadTargetTemp(void);
extern void PECI_ReadThermMargin(void);

/*-----------------------------------------------------------------------------
 * Internal Calling Prototype
 *---------------------------------------------------------------------------*/


//-----------------------------------------------------------------------------
#endif

