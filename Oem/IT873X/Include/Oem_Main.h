/*-----------------------------------------------------------------------------
 * Filename: OEM_MAIN.H
 * Function: OEM_MAIN.C Include Definition
 *
 * Copyright (c) 2006-2009, ITE Tech. Inc. All Rights Reserved.
 *---------------------------------------------------------------------------*/
#ifndef  OEM_MAIN_H
#define  OEM_MAIN_H

extern code BYTE Fan_Duty[];
extern code WORD Target_RPM_Lenovo[];
extern code WORD Target_RPM_Lenovo2[];
extern code WORD Target_RPM_5000[];
extern code WORD Target_RPM1[];
extern code WORD Target_RPM2[];

/*-----------------------------------------------------------------------------
 * External Calling Process
 *---------------------------------------------------------------------------*/
extern void RamDebug(unsigned char dbgcode);
extern void RamDebugWord(unsigned int dbgword);
extern void RamDebugDword(unsigned long dbgdword);
extern void Oem_Hook_1MS_Event(void);
extern void Oem_Hook_5MS_Event(void) ;
extern void Oem_Hook_10MS_Event(void);
extern void Oem_Hook_50MS_EventA(void);
extern void Oem_Hook_50MS_EventB(void);
extern void Oem_Hook_50MS_EventC(void);
extern void Oem_Hook_100MS_EventA(void);
extern void Oem_Hook_100MS_EventB(void);
extern void Oem_Hook_100MS_EventC(void);
extern void Oem_Hook_125MS_Event(void);
extern void Oem_Hook_250MS_Event(void);
extern void Oem_Hook_500MS_EventA(void);
extern void Oem_Hook_500MS_EventB(void);
extern void Oem_Hook_500MS_EventC(void);
extern void Oem_Hook_1S_EventA(void);
extern void Oem_Hook_1S_EventB(void);
extern void Oem_Hook_1S_EventC(void);
extern void Oem_Hook_1Min_Event(void);
extern void Oem_Main_Test_Func(void);
extern void CheckResetSource(void);

/*-----------------------------------------------------------------------------
 * Internal Process Definition
 *---------------------------------------------------------------------------*/


extern void Delay15US(XWORD dly_count);

#endif	// __OEM_MAIN_H__
