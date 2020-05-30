/*-----------------------------------------------------------------------------
 * Filename: Core_Init.h
 * Function: Core_Init.c Include Definition
 *
 * Copyright (c) 2010, ITE Tech. Inc. All Rights Reserved.
 *---------------------------------------------------------------------------*/
#ifndef CORE_INIT_H
#define CORE_INIT_H


/*-----------------------------------------------------------------------------
 * Parameter Definition
 *---------------------------------------------------------------------------*/

extern void Kernel_Initialization(void) ;
extern void Init_ClearRam(void);
extern void Enable_SMLink1_Mapping_To_TMPIN2(void);
extern void Init_Timers(void) ;
extern void Set_T1_Timeout(WORD wTimeCnt);
extern void Load_Timer_A(void) ;
extern void Load_Timer_A_1ms(void);
extern void Reset_Initialization(void);
extern void InitSMBus(void);
extern void InitDAC(void);
extern void InitADC(void);
extern void InitFanCTL(void);
extern void InitEnterDeepSleep(void);
extern void InitWakeFromDeepSleep(void);
extern void Init_UART2(void);
extern void Init_UART1(void);
extern void Set_ExtTimer1(void);
extern BYTE Read_SPI(WORD address);
extern void Init_BRAM(void) ;
extern void EnableKBCIBFInt(void);
extern void Disable_DCache(void);
extern void Enable_K8_Function(void);
#endif	// __CORE_INIT_H__
