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
#ifndef OEM_RAM_H
#define OEM_RAM_H
#include "Oem_Project.h"

//==========================================================================
//	External RAM define
//==========================================================================

//=========================================================================================
//EC SRAM 0x0100
//=========================================================================================
//
//#define	SRAM_100_BASE			0x0100
//For SMB_Scan_Center
extern XBYTE	SMBus1RecoverCunt;				//_at_	(SRAM_100_BASE+0x00);
extern XBYTE	SMBus2RecoverCunt;				//_at_	(SRAM_100_BASE+0x01);
extern XBYTE	SMBus3RecoverCunt;				//_at_	(SRAM_100_BASE+0x02);
extern XBYTE	SMBCRC8_A;						//_at_ 	(SRAM_100_BASE+0x03);
extern XBYTE	SMBus_BusyRecover;				//_at_ 	(SRAM_100_BASE+0x04);

//#define	SMBUS_OEM_ScanCenter_BASE		0x0110
extern XBYTE	SMBus1index;					//_at_ (SMBUS_OEM_ScanCenter_BASE+0x00);
extern XBYTE	SMBus2index;					//_at_ (SMBUS_OEM_ScanCenter_BASE+0x01);
extern XBYTE	SMBus3index;					//_at_ (SMBUS_OEM_ScanCenter_BASE+0x02);
extern XBYTE	SMBus1counter;					//_at_ (SMBUS_OEM_ScanCenter_BASE+0x03);
extern XBYTE	SMBus2counter;					//_at_ (SMBUS_OEM_ScanCenter_BASE+0x04);
extern XBYTE	SMBus3counter;					//_at_ (SMBUS_OEM_ScanCenter_BASE+0x05);
extern XBYTE	SMBus1ByteCunt;				//_at_ (SMBUS_OEM_ScanCenter_BASE+0x06);
extern XBYTE	SMBus2ByteCunt;				//_at_ (SMBUS_OEM_ScanCenter_BASE+0x07);
extern XBYTE	SMBus3ByteCunt;				//_at_ (SMBUS_OEM_ScanCenter_BASE+0x08);

extern XBYTE	F_Service_SMBus1;				//_at_ (SMBUS_OEM_ScanCenter_BASE+0x09);
extern XBYTE	F_Service_SMBus2;				//_at_ (SMBUS_OEM_ScanCenter_BASE+0x0A);
extern XBYTE	F_Service_SMBus3;				//_at_ (SMBUS_OEM_ScanCenter_BASE+0x0B);
extern XBYTE	SMBus1InUsing;					//_at_ (SMBUS_OEM_ScanCenter_BASE+0x0C);
extern XBYTE	SMBus2InUsing;					//_at_ (SMBUS_OEM_ScanCenter_BASE+0x0D);
extern XBYTE	SMBus3InUsing;					//_at_ (SMBUS_OEM_ScanCenter_BASE+0x0E);
extern XBYTE	SMBus1TableSize;				//_at_ (SMBUS_OEM_ScanCenter_BASE+0x0F);
extern XBYTE	SMBus2TableSize;				//_at_ (SMBUS_OEM_ScanCenter_BASE+0x10);
extern XBYTE	SMBus3TableSize;				//_at_ (SMBUS_OEM_ScanCenter_BASE+0x11);
extern XBYTE	*SMBus1BlockPtr;				//_at_ (SMBUS_OEM_ScanCenter_BASE+0x12);	//12~13 2bytes
extern XBYTE	*SMBus2BlockPtr;				//_at_ (SMBUS_OEM_ScanCenter_BASE+0x14);	//14~15 2bytes
extern XBYTE	*SMBus3BlockPtr;				//_at_ (SMBUS_OEM_ScanCenter_BASE+0x16);	//16~17 2bytes
extern XBYTE	SMBusSelection;					//_at_ (SMBUS_OEM_ScanCenter_BASE+0x18);
extern XBYTE	SMBusXStatus;					//_at_ (SMBUS_OEM_ScanCenter_BASE+0x19);
extern XBYTE	SMB_BCNT;						//_at_ (SMBUS_OEM_ScanCenter_BASE+0x1A);

#define SMBus1_OK       BIT0
#define SMBus1_Fail     BIT1
#define SMBus2_OK       BIT2
#define SMBus2_Fail     BIT3
#define SMBus3_OK       BIT4
#define SMBus3_Fail     BIT5
#define SMBus4_OK       BIT6
#define SMBus4_Fail     BIT7

//=========================================================================================
//EC SRAM 0x0200
//=========================================================================================
//
//#define	SRAM_200_BASE			0x0200
extern XBYTE	LED_FLASH_CNT;
extern XBYTE	LED_S0_Status;

//=========================================================================================
//EC SRAM 0x0300
//=========================================================================================
//
//#define	SRAM_300_BASE 		0x300



//=========================================================================================
//EC SRAM 0x0400
//=========================================================================================
//#define	SRAM_400_BASE		0x0400


//-----------------------------------------------------------------------------
/*****************************************************************************/
/* EXTERNAL RAM AREA      (0x0500 ~ 0x05FF) **********************************/
/*****************************************************************************/
////////////////////////////////////////////////////////////////////////////
//#define	ECSpace			0x0500

//==========================================================
extern XBYTE	Code_Version;							//_at_ (ECSpace + 0x00);
extern XBYTE	Code_Beta_Version;						//_at_ (ECSpace + 0x01);




//-----------------------------------------------------------------------------
/*****************************************************************************/
/* EXTERNAL RAM AREA      (0x0600 ~ 0x06FF) **********************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
//RAMDEBUG AREA
//-----------------------------------------------------------------------------
//=========================================================================================
//EC SRAM 0x0700
// For Keil C Complier and Ram Code Space (for SPI programming).
//=========================================================================================
//#define	SRAM_700_BASE		0x0700
//Note: Do not use it
// For Keil C Complier and Ram Code Space (for SPI programming).



//=========================================================================================
//EC SRAM 0x800
//=========================================================================================
//#define	SRAM_800_BASE		0x0800


//=========================================================================================
//EC SRAM 0x0900
//=========================================================================================
//#define	SRAM_900_BASE		0x0900


//=========================================================================================
//EC SRAM 0x0A00
//=========================================================================================
//#define	SRAM_A00_BASE		0x0A00


//=========================================================================================
//EC SRAM 0x0B00
//=========================================================================================
//#define	SRAM_B00_BASE		0x0B00


//=========================================================================================
//EC SRAM 0x0C00
//=========================================================================================
//#define	SRAM_C00_BASE		0x0C00


//=========================================================================================
//EC SRAM 0x0D00
//=========================================================================================
//#define	SRAM_D00_BASE		0x0D00


//=========================================================================================
//EC SRAM 0x0E00
//=========================================================================================
//#define	SRAM_E00_BASE		0x0E00


//=========================================================================================
//EC SRAM 0x0F00
//=========================================================================================
//#define	SRAM_F00_BASE		0x0F00




/******************************************************************************

	Define
	Description: Battery-backed SRAM (BRAM)
	Footnote:		64-byte in IT8731
	
******************************************************************************/
//#define 	BRAM_Basse					0x2280
extern XBYTE	BRAM_CHECK0;				//_at_ (BRAM_Basse + 0x00);
extern XBYTE	BRAM_CHECK1;				//_at_ (BRAM_Basse + 0x01);
extern XBYTE	BRAM_CHECK2;				//_at_ (BRAM_Basse + 0x02);




#endif	//__CORE_RAM_H__
