/*-----------------------------------------------------------------------------
 * TITLE: CORE_ACPI.H
 *
 * Copyright (c) 1983-2009, Insyde Software Corporation. All Rights Reserved.
 *
 * You may not reproduce, distribute, publish, display, perform, modify, adapt,
 * transmit, broadcast, present, recite, release, license or otherwise exploit
 * any part of this publication in any form, by any means, without the prior
 * written permission of Insyde Software Corporation.
 *---------------------------------------------------------------------------*/
#ifndef CORE_PMC2_H
#define CORE_PMC2_H

/*-----------------------------------------------------------------------------
 * Code Parameter
 *---------------------------------------------------------------------------*/
#define _PM2_STEP_1         1
#define _PM2_STEP_2         2
#define _PM2_STEP_3         3
#define _PM2_STEP_4         4
#define _PM2_STEP_5         5
#define _PM2_STEP_6         6
#define _PM2_STEP_7         7

/*-----------------------------------------------------------------------------
 * External Calling Process
 *---------------------------------------------------------------------------*/
extern void Service_PCI3(void);
extern void Service_PCI3_Main(void);

extern void EC686C_CMD_80(void);
extern void EC686C_CMD_81(void);
extern void EC686C_CMD_82(void);
extern void EC686C_CMD_83(void);
extern void EC686C_CMD_84(void);
extern void PMC2_Cmd_8X(void);


extern bit  PMC2_CheckBurstMode(void);

extern void PMC2_vSetTotalBurstTime(void);


/*-----------------------------------------------------------------------------
 * Internal Calling Prototype
 *---------------------------------------------------------------------------*/


//-----------------------------------------------------------------------------
#endif

