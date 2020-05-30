/*-----------------------------------------------------------------------------
 * Filename: OEM_CIR.H
 * Function: OEM_CIR.C Function prototype include definition
 *
 * Copyright (c) 2006-2009, ITE Tech. Inc. All Rights Reserved.
 *---------------------------------------------------------------------------*/
#ifndef OEM_CIR_H
#define OEM_CIR_H

#define RXEN_MASK		0x20
#define RXACT_MASK		0x08
#define RXFBC_MASK		0x3F


/*-----------------------------------------------------------------------------
 * External Calling Prototype
 *---------------------------------------------------------------------------*/
extern void Service_CIR(void);
extern void Init_CIR(void);
extern void Reset_CIR(void);
extern void  EN_EC_CIR(void) ;//BJ,OEM+ T012
extern void bClearCirFIFO(void);
extern void Service_CIR(void);
extern void ClearCIR(void);
extern bit  bCIRWakeUp(void);
extern void Clear_CIR_Buffer(void);
extern void Set_CIR_From_Driver_to_EC(void);
extern void Set_CIR_From_EC_to_Driver(void);
/*-----------------------------------------------------------------------------
 * Internal Process Prototype
 *---------------------------------------------------------------------------*/



//-----------------------------------------------------------------------------
#endif  //OEM_CIR_H

