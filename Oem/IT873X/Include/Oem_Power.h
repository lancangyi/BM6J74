/*-----------------------------------------------------------------------------
 * Filename: OEM_POWER.H
 * Function: OEM_POWER.C Function prototype include definition
 *
 * Copyright (c) 2006-2009, ITE Tech. Inc. All Rights Reserved.
 *---------------------------------------------------------------------------*/
#ifndef OEM_POWER_H
#define OEM_POWER_H

/*-----------------------------------------------------------------------------
 * Parameter Definition
 *---------------------------------------------------------------------------*/
#define _PowrUp_S5      0
#define _SYSTEM_S0      1
#define _SYSTEM_S1      2
#define _SYSTEM_S3      3
#define _SYSTEM_S4      4
#define _SYSTEM_S5      5
#define _GO_POWER_ON    6
#define _GO_RESUME_ON   7
#define _GO_SUSPNED_OFF 8
#define _GO_POWER_OFF   9

#define	Check_SUSB_Twice
#ifdef Check_SUSB_Twice
#define	_Ready_to_S3	10
#endif

//-----------------------------------------------------------------------------
// Shutdown cause
//-----------------------------------------------------------------------------
#define SC_S0SLPOff		    0x01	// System shutdown by S3/S4/S5 Off
#define SC_S3S4SLPOff		0x02	// System shutdown by S3/S4/S5 fail Off
#define SC_4SEC		        0x03	// System shutdown by power button 4 sec overwrite
#define SC_CPUHOT		    0x04	// System shutdown by CPU too hot to shutdown
#define SC_HWPGSx_S0Off		0x05	// System shutdown by HWPG Fail in Sx_S0 power sequence
#define SC_HWPS0Off		    0x06	// System shutdown by HWPG Fail in S0

#define SC_WatchDog         0xFE    // System shutdown by EC watch-dog
#define SC_ECColdBoot       0xFF    // EC VSTBY reset
//-----------------------------------------------------------------------------
// System status define
//-----------------------------------------------------------------------------
#define SystemIsS0          SysPowState==_SYSTEM_S0
#define SystemIsS3          SysPowState==_SYSTEM_S3
#define SystemIsS4          SysPowState==_SYSTEM_S4
#define SystemIsS5          SysPowState==_SYSTEM_S5

#define SystemNotS0         SysPowState!=_SYSTEM_S0
#define SystemNotS3         SysPowState!=_SYSTEM_S3
#define SystemNotS4         SysPowState!=_SYSTEM_S4
#define SystemNotS5         SysPowState!=_SYSTEM_S5
/*-----------------------------------------------------------------------------
 * External Calling Process
 *---------------------------------------------------------------------------*/
extern void Oem_SysPowerContrl(void);
extern void Oem_ColdBootTester(void);
extern void Oem_ForceSystemOff(void);
extern void Oem_TriggerPowerOn(void);
extern void Oem_TriggerPowerOff(void);
extern void Oem_SysOnInit(void);
extern void Oem_SysOffInit(void);
extern void Oem_CommonInit(void);
extern void InitShareMemory(void);
extern void Oem_ChkS5WakeUp(void);
extern void Check_Power_State(void);
/*-----------------------------------------------------------------------------
 * Internal Process Definition
 *---------------------------------------------------------------------------*/

#define	EUP_Status_On					0x01
#define	EUP_Enable_Flag				0x02
#define	EUP_Status_Off_boot_ready		0x04


#define	Init_AMP_with_Table				1
//-----------------------------------------------------------------------------
#endif
