/*-----------------------------------------------------------------------------
 * Filename: OEM_SMBUS.H
 * Function: OEM_SMBUS.C Function prototype include definition
 *
 * Copyright (c) 2006-2012, ITE Tech. Inc. All Rights Reserved.
 *---------------------------------------------------------------------------*/
#ifndef OEM_SMBUS_H
#define OEM_SMBUS_H

#define TotalSMBusChannel	1

#define DB_S		BIT0
#define DB_R		BIT1
#define DB_RB	BIT2
#define DB_WB	BIT3
#define DB_RW	BIT4
#define DB_WW	BIT5
#define DB_RBB	BIT6
#define DB_WBB	BIT7


#define	SMbusQ		        0x00	// Quick command
#define	SMbusSRB	        0x04	// Send Byte command and Receive Byte command
#define	SMbusRWB	        0x08	// Read byte command Write byte command
#define	SMbusRWW	        0x0C	// Read word command Write word command
#define	SMbusRWBB	        0x14	// Read block command Write block command


#define Cmd_Quick		    0x00
#define Cmd_SendByte	    0x01
#define Cmd_RecvByte	    0x02
#define Cmd_ReadByte	    0x03
#define Cmd_WriteByte	    0x04
#define Cmd_ReadWord	    0x05
#define Cmd_WriteWord	    0x06
#define Cmd_ReadBlock	    0x07
#define Cmd_WriteBlock	    0x08


#define SMBus_NeedService	0x01
#define SMBus_ClearService	0x00

//-----------------------------------------------------------------------------
//Extern Func
//-----------------------------------------------------------------------------
extern void Hook_GetSMBusReadBlockByteCount(BYTE rblk_bc);
extern void PollSMBusReceiveByte(BYTE Channel,BYTE Addr);
extern void PollSMBusSendByte(BYTE Channel,BYTE Addr,BYTE cmd);
extern void PollReadSMBusByte(BYTE Channel,BYTE Addr,BYTE Comd);
extern void PollWriteSMBusByte(BYTE Channel,BYTE Addr,BYTE Comd,BYTE data1);
extern void PollReadSMBusWord(BYTE Channel,BYTE Addr,BYTE Comd);
extern void PollWriteSMBusWord(BYTE Channel,BYTE Addr,BYTE Comd,BYTE data1,BYTE data2);
extern void PollReadSMBusBlock(BYTE Channel,BYTE Addr,BYTE Comd);
extern void PollWriteSMBusBlock(BYTE Channel,BYTE Addr,BYTE Comd,BYTE ByteCunt);

extern void CheckSMBusTableSize(void);
extern void ServiceSMBus(void);
extern void SMBusCenterSelection(BYTE channel);
extern void SMBusCenter(void);
extern void WatiSMBusCHxFree(BYTE channel);
extern void Init_OEM_SMBus(void);

extern void service_smbus1(void);
extern void service_smbus2(void);
extern void service_smbus3(void);

extern BYTE CheckSMBusNeedService(void);
//-----------------------------------------------------------------------------
// SMBus table define
//-----------------------------------------------------------------------------

typedef struct SCS
{
	BYTE	protocol;
	BYTE  	address;
	BYTE  	cmd;
	XBYTE 	*smbdata;	
	BYTE	Conditionflag;
	XBYTE	*ConditionVar;
	FUNCT_PTR_V_V	hookfunc;
	FUNCT_PTR_V_V	errorfunc;
	BYTE	Bcunt;
	//BYTE	data1;
	//BYTE	data2;
} sSCS;

typedef struct SSC
{
    XBYTE 	*index;	
	XBYTE	*timeout;
    XBYTE   *bytecount;
    XBYTE	*inusing;
    XBYTE   *tablesize;
    XBYTE   *serviceflag;
	FUNCT_PTR_V_V	servicefunc;
} sSSC;

extern sSSC code asSSC[];
extern sSCS code asSCS1[];
extern sSCS code asSCS2[];
extern sSCS code asSCS3[];

#endif  //OEM_SMBUS_H

