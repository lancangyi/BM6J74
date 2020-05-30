/*-----------------------------------------------------------------------------
 * TITLE: CORE_PECI.H
 *
 * Copyright (c) 2013, ITE Tech. Inc. All Rights Reserved.
 *---------------------------------------------------------------------------*/
#ifndef CORE_UART_H
#define CORE_UART_H

/*-----------------------------------------------------------------------------
 * Code Parameter
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * External Calling Process
 *---------------------------------------------------------------------------*/
extern void UartSendData(BYTE bTxData);
extern void SendCmd2Scalar(BYTE command);
extern void Clear_UART_Rx_Buffer(void);
extern void Clear_UART_Tx_Buffer(void);
extern void UART1_Data_Handler(void);
extern void UART2_Data_Handler(void);
/*-----------------------------------------------------------------------------
 * Internal Calling Prototype
 *---------------------------------------------------------------------------*/


//-----------------------------------------------------------------------------
#endif

