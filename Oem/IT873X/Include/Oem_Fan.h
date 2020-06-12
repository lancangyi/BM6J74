/*-----------------------------------------------------------------------------
 * TITLE: OEM_FAN.H
 *
 * Author : Dino
 *
 * Note : These functions are reference only.
 *        Please follow your project software specification to do some modification.
 *---------------------------------------------------------------------------*/

#ifndef OEM_FAN_H
#define OEM_FAN_H


//------------------------------------------------------------------------------
// Function prototype
//------------------------------------------------------------------------------
extern WORD GetFanRPM(BYTE FnTMRR,BYTE FnTLRR);

extern void EC_start(void);
extern void EC_stop(void);

#endif

