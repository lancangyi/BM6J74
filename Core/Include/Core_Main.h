/*-----------------------------------------------------------------------------
 * Filename: Core_Inc.h
 * Function: OEM_MAIN.C Include Definition
 *
 * Copyright (c) 2006-2009, ITE Tech. Inc. All Rights Reserved.
 *---------------------------------------------------------------------------*/
#ifndef CORE_MAIN_H
#define CORE_MAIN_H

//--------------------------------------------------------------------------
//GPIO define
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
static void main(void);
extern void main_service(void);
extern void vDelay1ms(WORD bMS);
extern void LED_SEG(BYTE ucByte);

/*
		Runtime services prototypes
*/
extern void service_000(void);    	// Host command/data service
extern void service_001(void); 	// service unlock
extern void service_002(void);       // Send byte from KBC
extern void service_003(void); 	// Send PS2 interface data	
extern void service_004(void); 		// process PS2 interface data
extern void service_005(void);        // 1 millisecond elapsed
extern void service_006(void);		// Secondary Host command/data service
extern void service_007(void);       // Keyboard scanner service 

extern void service_008(void);   	// Third Host command/data service 
extern void service_009(void);     	// CIR IRQ.     
extern void service_00A(void);    	// 
extern void service_00B(void);    	// 
extern void service_00C(void);    	// 
extern void service_00D(void);       // fourth command/data service 
extern void service_00E(void); // Low level event 
extern void service_00F(void);      // ADC
extern void service_send(void);

#define False				0
#define false				0

#define True				1
#define true				1

#define	Debug_UART		0
#define	USE_UART1		0
#define	USE_UART2		0

#endif	// __CORE_MAIN_H__
