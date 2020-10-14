/*-----------------------------------------------------------------------------
 * Filename: CHIP_DEF.H     For Chipset: ITE.IT85XX
 *
 * Function: Register Definition for all code base reference
 *
 * Copyright (c) 2006-2009, ITE Tech. Inc. All Rights Reserved.
 *---------------------------------------------------------------------------*/
#ifndef		REG_EC_H
#define		REG_EC_H



/********************************************************************************
//For 873x
*********************************************************************************/
#define    SMFI_BASE_ADDR    0x1000
extern ECReg      FBCFG;		//        _at_    (SMFI_BASE_ADDR + 0x00);
extern ECReg      FPCFG;		//        _at_    (SMFI_BASE_ADDR + 0x01);
extern ECReg      FMSSR;		//        _at_    (SMFI_BASE_ADDR + 0x07);

extern ECReg	     CACHDISR;	//	   _at_   (SMFI_BASE_ADDR + 0x33);
extern ECReg      UCCTRL;		//       _at_    (SMFI_BASE_ADDR + 0x34);
extern ECReg      HCTRL2;		//       _at_    (SMFI_BASE_ADDR + 0x36);

/*      FBCFG       */
#define SSMC    BIT(7)

extern ECReg	ECINDAR0;		//		_at_	(SMFI_BASE_ADDR + 0x3B);
extern ECReg	ECINDAR1;		//		_at_	(SMFI_BASE_ADDR + 0x3C);
extern ECReg	ECINDAR2;		//		_at_	(SMFI_BASE_ADDR + 0x3D);
extern ECReg	ECINDAR3;		//		_at_	(SMFI_BASE_ADDR + 0x3E);
extern ECReg	ECINDDR;		//		_at_	(SMFI_BASE_ADDR + 0x3F);
extern ECReg	SCAR0L;			//		_at_	(SMFI_BASE_ADDR + 0x40);
extern ECReg	SCAR0M;		//		_at_	(SMFI_BASE_ADDR + 0x41);
extern ECReg	SCAR0H;			//		_at_	(SMFI_BASE_ADDR + 0x42);
extern ECReg	SCAR1L;			//		_at_	(SMFI_BASE_ADDR + 0x43);
extern ECReg	SCAR1M;		//		_at_	(SMFI_BASE_ADDR + 0x44);
extern ECReg	SCAR1H;			//		_at_	(SMFI_BASE_ADDR + 0x45);
extern ECReg	SCAR2L;			//		_at_	(SMFI_BASE_ADDR + 0x46);
extern ECReg	SCAR2M;		//		_at_	(SMFI_BASE_ADDR + 0x47);
extern ECReg	SCAR2H;			//		_at_	(SMFI_BASE_ADDR + 0x48);
extern ECReg	SCAR3L;			//		_at_	(SMFI_BASE_ADDR + 0x49);
extern ECReg	SCAR3M;		//		_at_	(SMFI_BASE_ADDR + 0x4A);
extern ECReg	SCAR3H;			//		_at_	(SMFI_BASE_ADDR + 0x4B);
extern ECReg	SCAR4L;			//		_at_	(SMFI_BASE_ADDR + 0x4C);
extern ECReg	SCAR4M;		//		_at_	(SMFI_BASE_ADDR + 0x4D);
extern ECReg	SCAR4H;			//		_at_	(SMFI_BASE_ADDR + 0x4E);




extern ECReg	HINSTC1;		//_at_	(SMFI_BASE_ADDR + 0x58);

/******************************************************************************
//Define
//Description: Define INTC_BASE_ADDR
//Footnote:
******************************************************************************/
#define	INTC_BASE_ADDR		0x1100
extern ECReg ISR0;//    	         _at_    (INTC_BASE_ADDR + 0x00);
extern ECReg ISR1;//    	         _at_    (INTC_BASE_ADDR + 0x01);
extern ECReg ISR2;//    	         _at_    (INTC_BASE_ADDR + 0x02);
extern ECReg ISR3;//    	         _at_    (INTC_BASE_ADDR + 0x03);
extern ECReg IER0;//               _at_    (INTC_BASE_ADDR + 0x04);
extern ECReg IER1;//								_at_    (INTC_BASE_ADDR + 0x05);
extern ECReg IER2;//               _at_    (INTC_BASE_ADDR + 0x06);
extern ECReg IER3;//               _at_    (INTC_BASE_ADDR + 0x07);
extern ECReg IELMR0;//             _at_    (INTC_BASE_ADDR + 0x08);
extern ECReg IELMR1;//         	 _at_    (INTC_BASE_ADDR + 0x09);
extern ECReg IELMR2;//         	 _at_    (INTC_BASE_ADDR + 0x0A);
extern ECReg IELMR3;//         	 _at_    (INTC_BASE_ADDR + 0x0B);
extern ECReg IPOLR0;//         	 _at_    (INTC_BASE_ADDR + 0x0C);
extern ECReg IPOLR1;//         	 _at_    (INTC_BASE_ADDR + 0x0D);
extern ECReg IPOLR2;//         	 _at_    (INTC_BASE_ADDR + 0x0E);
extern ECReg IPOLR3;//         	 _at_    (INTC_BASE_ADDR + 0x0F);
extern ECReg IVECT ;//        	 _at_    (INTC_BASE_ADDR + 0x10);
extern ECReg INT0ST;//         	 _at_    (INTC_BASE_ADDR + 0x11);
extern ECReg PFAILR;//         	 _at_    (INTC_BASE_ADDR + 0x12);
extern ECReg ISR4  ;//  	         _at_    (INTC_BASE_ADDR + 0x14);	// 8513 Only
extern ECReg IER4  ;//             _at_    (INTC_BASE_ADDR + 0x15); 	// 8513 Only
extern ECReg IELMR4;//         	 _at_    (INTC_BASE_ADDR + 0x16);	// 8513 Only
extern ECReg IPOLR4;//         	 _at_    (INTC_BASE_ADDR + 0x17);	// 8513 Only
extern ECReg ISR6;//         	 _at_    (INTC_BASE_ADDR + 0x1C);	
extern ECReg IER6;//         	 _at_    (INTC_BASE_ADDR + 0x1D);	
extern ECReg ISR8  ;//       	 _at_    (INTC_BASE_ADDR + 0x24);
extern ECReg IER8  ;//       	 _at_    (INTC_BASE_ADDR + 0x25);


extern ECReg ISR5   ;// 	         _at_    (INTC_BASE_ADDR + 0x18);	//
extern ECReg IER5   ;//            _at_    (INTC_BASE_ADDR + 0x19); 	//
extern ECReg IELMR5 ;//        	 _at_    (INTC_BASE_ADDR + 0x1A);	// Not Adjustble
extern ECReg IPOLR5 ;//        	 _at_    (INTC_BASE_ADDR + 0x1B);	// Not Adjustble

extern ECReg ISR6   ;// 	         _at_    (INTC_BASE_ADDR + 0x1C);	//
extern ECReg IER6   ;//            _at_    (INTC_BASE_ADDR + 0x1D); 	//
extern ECReg IELMR6 ;//        	 _at_    (INTC_BASE_ADDR + 0x1E);	//
extern ECReg IPOLR6 ;//        	 _at_    (INTC_BASE_ADDR + 0x1F);	//

extern ECReg ISR7   ;// 	         _at_    (INTC_BASE_ADDR + 0x20);	//
extern ECReg IER7   ;//            _at_    (INTC_BASE_ADDR + 0x21); 	//
extern ECReg IELMR7 ;//        	 _at_    (INTC_BASE_ADDR + 0x22);	//
extern ECReg IPOLR7 ;//        	 _at_    (INTC_BASE_ADDR + 0x23);	//

extern ECReg IELMR8 ;//        	 _at_    (INTC_BASE_ADDR + 0x26);	//
extern ECReg IPOLR8 ;//        	 _at_    (INTC_BASE_ADDR + 0x27);	//

//
//-----------------------------------------------------------------------------
// (11xxh) Interrupt controller (INTC) 
//-----------------------------------------------------------------------------
// IR0
//		-					BIT(0)	// -
#define	Int_WKO20			BIT(1)	// WKO[20]
#define	Int_KBCOBFE			BIT(2)	// KBC Output Buffer Empty Interrupt
#define	Int_PMCOBFE			BIT(3)	// PMC Output Buffer Empty Interrupt
#define	Int_SMBUS3			BIT(4)	// SMBUS3 Interrupt	
#define Int_WKINTAD			BIT(5)	// WKINTAD (WKINTA or WKINTD)
#define Int_WKO23			BIT(6)	// WKO[23]
#define Int_PWM				BIT(7)	// PWM Interrupt

// IR1
#define	Int_ADC				BIT(0)	// ADC Interrupt
#define	Int_SMBUS0			BIT(1)	// SMBUS0 Interrupt
#define	Int_SMBUS1			BIT(2)	// SMBUS0 Interrupt
#define	Int_KB				BIT(3)	// KB Matrix Scan Interrupt
#define	Int_WKO26			BIT(4)	// WKO[26]
#define Int_WKINTC			BIT(5)	// WKINTC
#define Int_WKO25			BIT(6)	// WKO[25]
#define Int_CIR				BIT(7)	// CIR Interrupt

// IR2
#define	Int_SMBUS2			BIT(0)	// SMBUS2 Interrupt
#define Int_WKO24			BIT(1)	// WKO[24]
#define	Int_PS2_2			BIT(2)	// PS/2 Interrupt 2
#define	Int_PS2_1			BIT(3)	// PS/2 Interrupt 1
#define	Int_PS2_0			BIT(4)	// PS/2 Interrupt 0
#define	Int_WKO22			BIT(5)	// WKO[22]
#define	SMFIS				BIT(6)	// SMFI Semaphore Interrupt
#define	SMFIL				BIT(7)	// SMFI Lock Error Interrupt

// IR3
#define	Int_KBCIBF			BIT(0)	// KBC Input Buffer Full Interrupt
#define Int_PMCIBF			BIT(1)	// PMC Input Buffer Full Interrupt
#define Int_PMC2OBE         BIT(2)	// PMC2 Output Buffer Empty Intr.
#define Int_PMC2IBF		    BIT(3)	// PMC2 Input Buffer Full Intr.
#define	Int_GINT			BIT(4)	// GINT from function 1 of GPD5
#define	Int_EGPC			BIT(5)	// EGPC Interrupt
#define	Int_EXTimer			BIT(6)	// External Timer Interrupt
#define	Int_WKO21			BIT(7)	// WKO[21]

// IR4
#define	Int_GPINT0			BIT(0)	// GPINT0
#define	Int_GPINT1			BIT(1)	// GPINT1
#define	Int_GPINT2			BIT(2)	// GPINT2
#define	Int_GPINT3			BIT(3)	// GPINT3
#define	Int_CIRGPINT	    BIT(4)	// CIR GPINT
#define	Int_SSPI		    BIT(5)	// SSPI Interrupt
#define	Int_UART1		    BIT(6)	// UART1 Interrupt
#define Int_UART2		    BIT(7)	// UART2 Interrupt

// IR5
//#define   Int_		    BIT(0)	//
//#define	Int_		    BIT(1)	//
//#define	Int_		    BIT(2)	//
//#define	Int_		    BIT(3)	//
//#define	Int_		    BIT(4)	//
//#define	Int_		    BIT(5)	//
//#define	Int_		    BIT(6)	//
//#define	Int_		    BIT(7)	//

// IR6
#define	Int_WKO60			BIT(0)	// WKO[60]
#define	Int_WKO61			BIT(1)	// WKO[61]
#define	Int_WKO62			BIT(2)	// WKO[62]
#define	Int_WKO63			BIT(3)	// WKO[63]
#define	Int_WKO64			BIT(4)	// WKO[64]
#define	Int_WKO65			BIT(5)	// WKO[65]
#define	Int_WKO66			BIT(6)	// WKO[66]
#define	Int_WKO67			BIT(7)	// WKO[67]

// IR7
//#define   Int_		    BIT(0)	//
//#define	Int_		    BIT(1)	//
#define Int_ET2Intr		    BIT(2)	// External Timer 2 Interrupt
#define Int_DeferredSPI     BIT(3)  // Deferred SPI Instruction Interrupt
#define Int_TMRINTA0	    BIT(4)	// TMRINTA0
#define Int_TMRINTA1	    BIT(5)	// TMRINTA1
#define Int_TMRINTB0	    BIT(6)	// TMRINTB0
#define	Int_TMRINTB1	    BIT(7)	// TMRINTB1

// IR8
#define Int_PMC2EXOBE	    BIT(0)	// PMC2EX Output Buffer Empty Intr.
#define	Int_PMC2EXIBF	    BIT(1)	// PMC2EX Input Buffer Full Intr.
#define	Int_PMC3OBE		    BIT(2)	// PMC3 Output Buffer Empty Intr.
#define Int_PMC3IBF			BIT(3)	// PMC3 Input Buffer Full Interrupt
#define Int_PMC4OBE		    BIT(4)	// PMC4 Output Buffer Empty Intr.
#define	Int_PMC4IBF		    BIT(5)	// PMC4 Input Buffer Full Intr.
//#define	Int_		    BIT(6)	//
#define	Int_I2BRAM		    BIT(7)	// I2BRAM Interrupt

// IR9
#define	Int_WKO70			BIT(0)	// WKO[70]
#define	Int_WKO71			BIT(1)	// WKO[71]
#define	Int_WKO72			BIT(2)	// WKO[72]
#define	Int_WKO73			BIT(3)	// WKO[73]
#define	Int_WKO74			BIT(4)	// WKO[74]
#define	Int_WKO75			BIT(5)	// WKO[75]
#define	Int_WKO76			BIT(6)	// WKO[76]
#define	Int_WKO77			BIT(7)	// WKO[77]


/******************************************************************************
Define
Description: Define PMC_BASE_ADDR
Footnote:
******************************************************************************/
#define	PMC_BASE_ADDR		0x1500
extern ECReg PM1STS	;//	  _at_    (PMC_BASE_ADDR + 0x00);
#define         OBF1    BIT(0x00)
#define         IBF1    BIT(0x01)
#define         Busy    BIT(0x02)
#define         C_D1    BIT(0x03)
#define         BURST   BIT(0x04)
#define         SCIEVT  BIT(0x05)
#define         SMIEVT  BIT(0x06)
extern ECReg PM1DO	;//	  _at_    (PMC_BASE_ADDR + 0x01);
extern ECReg PM1DOSCI	;//	  _at_    (PMC_BASE_ADDR + 0x02);
extern ECReg PM1DOSMI	;//	  _at_    (PMC_BASE_ADDR + 0x03);
extern ECReg PM1DI		;//  _at_    (PMC_BASE_ADDR + 0x04);
extern ECReg PM1DISCI	;//	  _at_    (PMC_BASE_ADDR + 0x05);
extern ECReg PM1CTL		;//  _at_    (PMC_BASE_ADDR + 0x06);
extern ECReg PM1IC		;//  _at_    (PMC_BASE_ADDR + 0x07);
extern ECReg PM1IE		;//  _at_    (PMC_BASE_ADDR + 0x08);

extern ECReg PM2STS		;//  _at_    (PMC_BASE_ADDR + 0x10);
extern ECReg PM2DO		;//  _at_    (PMC_BASE_ADDR + 0x11);
extern ECReg PM2DOSCI	;//	  _at_    (PMC_BASE_ADDR + 0x12);
extern ECReg PM2DOSMI	;//	  _at_    (PMC_BASE_ADDR + 0x13);
extern ECReg PM2DI		;//  _at_    (PMC_BASE_ADDR + 0x14);
extern ECReg PM2DISCI	;//	  _at_    (PMC_BASE_ADDR + 0x15);
extern ECReg PM2CTL		;//  _at_    (PMC_BASE_ADDR + 0x16);
extern ECReg PM2IC		;//  _at_    (PMC_BASE_ADDR + 0x17);
extern ECReg PM2IE		;//  _at_    (PMC_BASE_ADDR + 0x18);

extern ECReg MBXCTRL	;//	  _at_    (PMC_BASE_ADDR + 0x19);
extern ECReg PMIRQR		;//  _at_    (PMC_BASE_ADDR + 0x20);
extern ECReg PMHICR		;//  _at_    (PMC_BASE_ADDR + 0x21);



//-----------------------------------------------------------------------------
// (15xxh) Power Management Channel (PMC) 
//-----------------------------------------------------------------------------
// PM Status Register
#define	P_IBF				BIT(1)	// Input Buffer Full
#define	P_OBF				BIT(0)	// Output Buffer Full
#define	P_SYSF    BIT(0x02)
#define	P_C_D     BIT(0x03)
#define	P_KEYL    BIT(0x04)
#define	P_AOBF    BIT(0x05)
#define	P_GTIM    BIT(0x06)
#define	P_PARE    BIT(0x07)


/******************************************************************************
Define
Description: Define EC_PWM_BASE_ADDR
Footnote:
******************************************************************************/
#define	EC_PWM_BASE_ADDR 0x1800

extern ECReg CPRS;			//_at_    (EC_PWM_BASE_ADDR + 0x00);
extern ECReg DCR;			//_at_    (EC_PWM_BASE_ADDR + 0x01);
extern ECReg PWMCTL;		//_at_    (EC_PWM_BASE_ADDR + 0x02);
//J74_003-- extern ECReg DDRSIGN;      	//_at_    (EC_PWM_BASE_ADDR + 0x03);

#define	PWMODEN	5
#define	PCFS		4
#define	PCCE		3



/******************************************************************************
Define
Description: Define WUC_BASE_ADDR
Footnote:
******************************************************************************/
#define	WUC_BASE_ADDR		0x1B00
extern ECReg  WUEMR1;// 		_at_    (WUC_BASE_ADDR + 0x00);		// Wake-up Edge Mode Reg 1
extern ECReg  WUEMR2;// 		_at_    (WUC_BASE_ADDR + 0x01);		// Wake-up Edge Mode Reg 2
extern ECReg  WUEMR3;// 		_at_    (WUC_BASE_ADDR + 0x02);		// Wake-up Edge Mode Reg 3
extern ECReg  WUEMR4;// 		_at_    (WUC_BASE_ADDR + 0x03);		// Wake-up Edge Mode Reg 4
extern ECReg  WUEMR5;// 		_at_    (WUC_BASE_ADDR + 0x0C);		// Wake-up Edge Mode Reg 5 (IT8750)
extern ECReg  WUEMR6;// 		_at_    (WUC_BASE_ADDR + 0x10);		// Wake-up Edge Mode Reg 6 (IT8516)

extern ECReg  WUESR1;// 		_at_    (WUC_BASE_ADDR + 0x04);		// Wake-up Edge Sense Reg 1
extern ECReg  WUESR2;// 		_at_    (WUC_BASE_ADDR + 0x05);		// Wake-up Edge Sense Reg 2
extern ECReg  WUESR3;// 		_at_    (WUC_BASE_ADDR + 0x06);		// Wake-up Edge Sense Reg 3
extern ECReg  WUESR4;// 		_at_    (WUC_BASE_ADDR + 0x07);		// Wake-up Edge Sense Reg 4
extern ECReg  WUESR5;// 		_at_    (WUC_BASE_ADDR + 0x0D);		// Wake-up Edge Sense Reg 5 (IT8750)
extern ECReg  WUESR6;// 		_at_    (WUC_BASE_ADDR + 0x11);		// Wake-up Edge Sense Reg 6 (IT8516)

extern ECReg  WUENR1;// 		_at_    (WUC_BASE_ADDR + 0x08);		// Wake-up Enable Reg 1
extern ECReg  WUENR2;// 		_at_    (WUC_BASE_ADDR + 0x09);		// Wake-up Enable Reg 2
extern ECReg  WUENR3;// 		_at_    (WUC_BASE_ADDR + 0x0A);		// Wake-up Enable Reg 3
extern ECReg  WUENR4;// 		_at_    (WUC_BASE_ADDR + 0x0B);		// Wake-up Enable Reg 4
extern ECReg  WUENR5;// 		_at_    (WUC_BASE_ADDR + 0x0E);		// Wake-up Enable Reg 5 (IT8750)
extern ECReg  WUENR6;// 		_at_    (WUC_BASE_ADDR + 0x12);		// Wake-up Enable Reg 6 (IT8516)

/******************************************************************************
Define
Description: Define SMB_BASE_ADDR
Footnote:
******************************************************************************/
#define	SMB_BASE_ADDR		0x1C00
extern ECReg  HOSTA_A	;//	_at_    (SMB_BASE_ADDR + 0x00);		// HOST Status
#define HOSTA_BDS           BIT(7)  // Byte Done Status
#define HOSTA_TMOE    	    BIT(6)  // Time-out Error
#define HOSTA_NACK   	    BIT(5)  // Not Response ACK
#define HOSTA_FAIL  	    BIT(4)  // Fail
#define HOSTA_BSER    	    BIT(3)  // Bus Error
#define HOSTA_DVER    	    BIT(2)  // Device Error
#define HOSTA_FINTR   	    BIT(1)  // Finish Interrupt
#define HOSTA_HOBY  	    BIT(0)  // Host Busy

extern ECReg  HOCTL_A    ;//  	_at_    (SMB_BASE_ADDR + 0x01); 	// HOST Control

extern ECReg  HOCMD_A    ;//  	_at_   	(SMB_BASE_ADDR + 0x02);		// HOST Command
extern ECReg  TRASLA_A   ;//  	_at_    (SMB_BASE_ADDR + 0x03);		// Transmit Slave Address
extern ECReg  D0REG_A    ;//  	_at_    (SMB_BASE_ADDR + 0x04);		// HOST Data0
extern ECReg  D1REG_A    ;//  	_at_   	(SMB_BASE_ADDR + 0x05);		// HOST Data1
extern ECReg  HOBDB_A    ;//  	_at_    (SMB_BASE_ADDR + 0x06);  	// HOST Block Data Byte
extern ECReg  PECERC_A   ;//  	_at_    (SMB_BASE_ADDR + 0x07); 	// Packet Error Check
extern ECReg  SMBPCTL_A  ;//  	_at_   	(SMB_BASE_ADDR + 0x0A);  	// SMBUS Pin Control
extern ECReg  HOCTL2_A   ;//  	_at_    (SMB_BASE_ADDR + 0x10); 	// HOST Control2
extern ECReg  HOSTA_B    ;// 	_at_    (SMB_BASE_ADDR + 0x11);		// HOST Status
extern ECReg  HOCTL_B    ;//  	_at_    (SMB_BASE_ADDR + 0x12);		// HOST Control
extern ECReg  HOCMD_B    ;//  	_at_   	(SMB_BASE_ADDR + 0x13);		// HOST Command
extern ECReg  TRASLA_B   ;//  	_at_    (SMB_BASE_ADDR + 0x14);		// Transmit Slave Address
extern ECReg  D0REG_B    ;//  	_at_    (SMB_BASE_ADDR + 0x15);		// HOST Data0
extern ECReg  D1REG_B    ;//  	_at_   	(SMB_BASE_ADDR + 0x16);		// HOST Data1
extern ECReg  HOBDB_B    ;//  	_at_   	(SMB_BASE_ADDR + 0x17);		// HOST Block Data Byte
extern ECReg  PECERC_B   ;//  	_at_    (SMB_BASE_ADDR + 0x18);	 	// Packet Error Check
extern ECReg  SMBPCTL_B  ;//  	_at_   	(SMB_BASE_ADDR + 0x1B);	  	// SMBUS Pin Control
extern ECReg  HOCTL2_B   ;//  	_at_    (SMB_BASE_ADDR + 0x21);	 	// HOST Control2
extern ECReg  SMBUS_4P7USREG;//    _at_    (SMB_BASE_ADDR + 0x22); 	// SMB TIMING SETUP1
extern ECReg  SMBUS_4P0USREG;//    _at_    (SMB_BASE_ADDR + 0x23); 	// SMB TIMING SETUP2
extern ECReg  SMBUS_300NSREG;//    _at_    (SMB_BASE_ADDR + 0x24); 	// SMB TIMING SETUP3
extern ECReg  SMBUS_250NSREG;//    _at_    (SMB_BASE_ADDR + 0x25); 	// SMB TIMING SETUP4
extern ECReg  SMBUS_25MSREG ;//    _at_    (SMB_BASE_ADDR + 0x26); 	// SMB TIMING SETUP5
extern ECReg  SMBUS_45P3USLREG;//  _at_    (SMB_BASE_ADDR + 0x27); 	// SMB TIMING SETUP6
extern ECReg  SMBUS_45P3USHREG;//  _at_    (SMB_BASE_ADDR + 0x28);		// SMB TIMING SETUP7
extern ECReg  HOSTA_C ;//     	_at_    (SMB_BASE_ADDR + 0x29);	  	// HOST Status
extern ECReg  HOCTL_C ;//     	_at_    (SMB_BASE_ADDR + 0x2A);	  	// HOST Control
extern ECReg  HOCMD_C ;//     	_at_   	(SMB_BASE_ADDR + 0x2B);	  	// HOST Command
extern ECReg  TRASLA_C;//     	_at_    (SMB_BASE_ADDR + 0x2C);	  	// Transmit Slave Address
extern ECReg  D0REG_C ;//     	_at_    (SMB_BASE_ADDR + 0x2D);	  	// HOST Data0
extern ECReg  D1REG_C ;//     	_at_    (SMB_BASE_ADDR + 0x2E);	  	// HOST Data1
extern ECReg  HOBDB_C ;//     	_at_    (SMB_BASE_ADDR + 0x2F);	  	// HOST Block Data Byte
extern ECReg  PECERC_C;//     	_at_    (SMB_BASE_ADDR + 0x30);	  	// Packet Error Check
extern ECReg  SMBPCTL_C;//    	_at_   	(SMB_BASE_ADDR + 0x31);	  	// SMBUS Pin Control
extern ECReg  HOCTL2_C ;//    	_at_    (SMB_BASE_ADDR + 0x32);	  	// HOST Control2
extern ECReg  SMBUS_4P7A4P0H;//    _at_    (SMB_BASE_ADDR + 0x33); 	// SMB TIMING SETUP8

/******************************************************************************
Define
Description: Define SWKBC_BASE_ADDR
Footnote:
******************************************************************************/
#define SWKBC_BASE_ADDR   0x1D00
extern ECReg  KSOR;//          _at_ (SWKBC_BASE_ADDR + 0x00);
extern ECReg  KSOCTRL;//    _at_ (SWKBC_BASE_ADDR + 0x01);
extern ECReg  KSIR;//            _at_ (SWKBC_BASE_ADDR + 0x02);
extern ECReg  KSICTRLR;//    _at_ (SWKBC_BASE_ADDR + 0x03);
extern ECReg  SCCTRL;//       _at_ (SWKBC_BASE_ADDR + 0x04);
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~`
#define SCEN        BIT(0)
#define SCSTART  BIT(1)

extern ECReg  KBHICR;//       _at_ (SWKBC_BASE_ADDR + 0x07);
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~`
#define PM1ICIE	BIT(6)	// PM Channel 1 Input Buffer Full 8032 Interrupt Enable
#define PM1OCIE	BIT(5)	// PM Channel 1 Output Buffer Empty 8032 Interrupt Enable
#define PM1HIE	BIT(4)	// PM Channel 1 Host Interface Interrupt Enable
#define IBFCIE		BIT(3)	// Input Buffer Full 8032 Interrupt Enable
#define OBECIE	BIT(2)	// Output Buffer Empty 8032 Interrupt Enable
#define OBFMIE	BIT(1)	// Output Buffer Full Mouse Interrupt Enable
#define OBFKIE 	BIT(0)	// Output Buffer Full Keyboard Interrupt Enable

extern ECReg  KBHISR;//       _at_ (SWKBC_BASE_ADDR + 0x08);
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~`
#define PARE    BIT(7)	// Programming Data
#define GTIM    BIT(6)	// Programming Data
#define AOBF    BIT(5)	// Programming Data
#define KEYL     BIT(4)	// Programming Data
#define C_D      BIT(3)	// Command or data port
#define SYSF     BIT(2)	// Programming Data (System flag)
#define IBF	 BIT(1)	// Input Buffer Full
#define OBF	 BIT(0)	// Output Buffer Full

extern ECReg  KBHIKDOR;//  _at_ (SWKBC_BASE_ADDR + 0x09);
extern ECReg  KBHIDIR;//      _at_ (SWKBC_BASE_ADDR + 0x0A);

/******************************************************************************
Define
Description: Define ECPM_BASE_ADDR
Footnote:
******************************************************************************/
#define	ECPM_BASE_ADDR		0x1E00
extern ECReg  EC_1E00;//  		_at_    (ECPM_BASE_ADDR + 0x00);	// Clock Frequency Select(8510,8511 only)
extern ECReg  ECPM_CGCTRL1R;// 	_at_    (ECPM_BASE_ADDR + 0x01);	// Clock Gating Control1
extern ECReg  CGCTRL2R;// 		_at_    (ECPM_BASE_ADDR + 0x02);	// Clock Gating Control2
extern ECReg  EC_1E03 ;//		_at_    (ECPM_BASE_ADDR + 0x03);	// PLL Control
extern ECReg  AUTOCG ;//		_at_    (ECPM_BASE_ADDR + 0x04);	// Auto Clock Gatting
extern ECReg  CGCTRL3R;// 		_at_    (ECPM_BASE_ADDR + 0x05);	// Clock Gating Control3
extern ECReg  EC_1E06 ;//		_at_    (ECPM_BASE_ADDR + 0x06);

extern ECReg  PLLCSS; 		//_at_    (ECPM_BASE_ADDR + 0x08);
/******************************************************************************
Define
Description: Define ETWD_BASE_ADDR
Footnote:
******************************************************************************/
#define	ETWD_BASE_ADDR		0x1F00
extern ECReg  ETWCFG	;//	_at_    (ETWD_BASE_ADDR + 0x01);	// External Timer/WDT Configuration REG
extern ECReg  ETPSR	;//	_at_    (ETWD_BASE_ADDR + 0x02);	// External Timer Prescaler REG
extern ECReg  ETCNTLHR;//		_at_    (ETWD_BASE_ADDR + 0x03);	// External Timer Counter High Byte
extern ECReg  ETCNTLLR;//		_at_    (ETWD_BASE_ADDR + 0x04);	// External Timer Counter Low Byte
extern ECReg  ETWCTRL;//		_at_    (ETWD_BASE_ADDR + 0x05);	// External Timer/WDT Control REG
extern ECReg  EWDCNTLHR;//		_at_    (ETWD_BASE_ADDR + 0x09);	// External WDT Counter High Byte
extern ECReg  EWDCNTLLR;//		_at_    (ETWD_BASE_ADDR + 0x06);	// External WDT Counter Low Byte
extern ECReg  EWDKEYR;//		_at_    (ETWD_BASE_ADDR + 0x07);	// External WDT Key REG
extern ECReg  RSTSCR;//		_at_    (ETWD_BASE_ADDR + 0x08);	// Reset Scratch REG


/******************************************************************************
Define
Description: Define EC interface base address
Footnote:
******************************************************************************/
#define    GCTRL_BASE_ADDR    0x2000
extern ECReg    ECHIPID1 ;//      _at_    (GCTRL_BASE_ADDR + 0x00);    // CHIP ID BYTE 1
extern ECReg    ECHIPID2 ;//      _at_    (GCTRL_BASE_ADDR + 0x01);    // CHIP ID BYTE 2
extern ECReg    ECHIPVER ;//      _at_    (GCTRL_BASE_ADDR + 0x02);    // CHIP VERSION
extern ECReg    RSTS     ;//      _at_    (GCTRL_BASE_ADDR + 0x06);    // RESET STATUS
extern ECReg    RSTC1    ;//      _at_    (GCTRL_BASE_ADDR + 0x07);    // RESET CONTROL 1
extern ECReg    RSTC2    ;//      _at_    (GCTRL_BASE_ADDR + 0x08);    // RESET CONTROL 2
extern ECReg    RSTC3    ;//      _at_    (GCTRL_BASE_ADDR + 0x09);    // RESET CONTROL 3
extern ECReg    WNCKR    ;//      _at_    (GCTRL_BASE_ADDR + 0x0B);    // WAIT NEXT CLOCK RISING
extern ECReg    SPCTRL1  ;//      _at_    (GCTRL_BASE_ADDR + 0x0D);    // SPECIAL CONTROL 1
extern ECReg    GENIRQ   ;//      _at_    (GCTRL_BASE_ADDR + 0x0F);    // GENERATE IRQ
extern ECReg    RSTC4    ;//      _at_    (GCTRL_BASE_ADDR + 0x11);    // RESET CONTROL 4
extern ECReg    SPCTRL2  ;//      _at_    (GCTRL_BASE_ADDR + 0x12);    // SPECIAL CONTROL 2
extern ECReg    PI2ECH   ;//      _at_    (GCTRL_BASE_ADDR + 0x14);    // PORT I2EC HIGH-BYTE REGISTER
extern ECReg    PI2ECL   ;//      _at_    (GCTRL_BASE_ADDR + 0x15);    // PORT I2EC LOW-BYTE REGISTER
extern ECReg    SPCTRL3  ;//      _at_    (GCTRL_BASE_ADDR + 0x16);    // SPECIAL CONTROL 3


/******************************************************************************
Define
Description: Define CIR_BASE_ADDR
Footnote:
******************************************************************************/
//#define	CIR_BASE_ADDR		0x2300
extern	ECReg	CIR_DR;				//_at_	CIR_BASE_ADDR+0x00;
extern	ECReg	CIR_IER;			//_at_	CIR_BASE_ADDR+0x01;	//bit: BR
extern	ECReg	CIR_RCR;			//_at_	CIR_BASE_ADDR+0x02;
extern	ECReg	CIR_TCR1;			//_at_	CIR_BASE_ADDR+0x03;
extern	ECReg	CIR_TCR2;			//_at_	CIR_BASE_ADDR+0x04;
extern	ECReg	CIR_TSR;			//_at_	CIR_BASE_ADDR+0x05;
extern	ECReg	CIR_RSR;			//_at_	CIR_BASE_ADDR+0x06;
#define	CIR_BDLR	CIR_TSR			//_at_	CIR_BASE_ADDR+0x05;	//BR = 1
#define	CIR_BDHR	CIR_RSR		//_at_	CIR_BASE_ADDR+0x06;	//BR = 1
extern	ECReg	CIR_IIR;				//_at_	CIR_BASE_ADDR+0x07;	


/******************************************************************************
Define
Description: Define SPI_BASE_ADDR
Footnote:
******************************************************************************/
#define	SPI_BASE_ADDR		0x2600
extern ECReg SPI0_DATA_REG	;//	_at_    (SPI_BASE_ADDR + 0x00);	//
extern ECReg SPI0_CTRL1_REG	;//	_at_    (SPI_BASE_ADDR + 0x01);	//
extern ECReg SPI0_CTRL2_REG	;//	_at_    (SPI_BASE_ADDR + 0x02);	//
extern ECReg SPI0_STATUS_REG;//		_at_    (SPI_BASE_ADDR + 0x03);	//
extern ECReg SPI0_CTRL3_REG	;//	_at_    (SPI_BASE_ADDR + 0x04);	//

extern ECReg SPI1_DATA_REG	;//	_at_    (SPI_BASE_ADDR + 0x10);	//
extern ECReg SPI1_CTRL1_REG	;//	_at_    (SPI_BASE_ADDR + 0x11);	//
extern ECReg SPI1_CTRL2_REG	;//	_at_    (SPI_BASE_ADDR + 0x12);	//
extern ECReg SPI1_STATUS_REG;//		_at_    (SPI_BASE_ADDR + 0x13);	//
extern ECReg SPI1_CTRL3_REG	;//	_at_    (SPI_BASE_ADDR + 0x14);	//

/******************************************************************************
Define
Description: Define UART1_BASE_ADDR
Footnote:
******************************************************************************/
#define	UART1_BASE_ADDR		0x2700
extern ECReg 	UART1_RBR_REG;//		_at_    (UART1_BASE_ADDR + 0x00);	//
extern ECReg 	UART1_IER_REG;//		_at_    (UART1_BASE_ADDR + 0x01);	//
extern ECReg 	UART1_IIR_REG;//		_at_    (UART1_BASE_ADDR + 0x02);	//
extern ECReg 	UART1_LCR_REG;//		_at_    (UART1_BASE_ADDR + 0x03);	//
extern ECReg 	UART1_MCR_REG;//		_at_    (UART1_BASE_ADDR + 0x04);	//
extern ECReg 	UART1_LSR_REG;//		_at_    (UART1_BASE_ADDR + 0x05);	//
extern ECReg 	UART1_MSR_REG;//		_at_    (UART1_BASE_ADDR + 0x06);	//
extern ECReg 	UART1_SCR_REG;//		_at_    (UART1_BASE_ADDR + 0x07);	//

/* Spec.7.21.4 Serial Port (UART2) */
#define UART1_RBR        (*(XBYTE *)0x2700)
#define UART1_IER        (*(XBYTE *)0x2701)
#define UART1_IIR        (*(XBYTE *)0x2702)
#define UART1_LCR        (*(XBYTE *)0x2703)
#define UART1_MCR        (*(XBYTE *)0x2704)
#define UART1_DLL        (*(XBYTE *)0x2700)
#define UART1_DLM        (*(XBYTE *)0x2701)
#define UART1_LSR        (*(XBYTE *)0x2705)
#define UART1_MSR        (*(XBYTE *)0x2706)
#define UART1_SCR        (*(XBYTE *)0x2707)
#define UART1_THR        (*(XBYTE *)0x2700)
#define UART1_FCR        (*(XBYTE *)0x2702)
#define UART1_ECSPMR     (*(XBYTE *)0x2708)


/******************************************************************************
Define
Description: Define UART2_BASE_ADDR
Footnote:
******************************************************************************/
#define	UART2_BASE_ADDR		0x2800
extern ECReg 	UART2_RBR_REG;//		_at_    (UART2_BASE_ADDR + 0x00);	//
extern ECReg 	UART2_IER_REG;//		_at_    (UART2_BASE_ADDR + 0x01);	//
extern ECReg 	UART2_IIR_REG;//		_at_    (UART2_BASE_ADDR + 0x02);	//
extern ECReg 	UART2_LCR_REG;//		_at_    (UART2_BASE_ADDR + 0x03);	//
extern ECReg 	UART2_MCR_REG;//		_at_    (UART2_BASE_ADDR + 0x04);	//
extern ECReg 	UART2_LSR_REG;//		_at_    (UART2_BASE_ADDR + 0x05);	//
extern ECReg 	UART2_MSR_REG;//		_at_    (UART2_BASE_ADDR + 0x06);	//
extern ECReg 	UART2_SCR_REG;//		_at_    (UART2_BASE_ADDR + 0x07);	//

/* Spec.7.21.4 Serial Port (UART2) */
#define UART2_RBR        (*(XBYTE *)0x2800)
#define UART2_IER        (*(XBYTE *)0x2801)
#define UART2_IIR        (*(XBYTE *)0x2802)
#define UART2_LCR        (*(XBYTE *)0x2803)
#define UART2_MCR        (*(XBYTE *)0x2804)
#define UART2_DLL        (*(XBYTE *)0x2800)
#define UART2_DLM        (*(XBYTE *)0x2801)
#define UART2_LSR        (*(XBYTE *)0x2805)
#define UART2_MSR        (*(XBYTE *)0x2806)
#define UART2_SCR        (*(XBYTE *)0x2807)
#define UART2_THR        (*(XBYTE *)0x2800)
#define UART2_FCR        (*(XBYTE *)0x2802)
#define UART2_ECSPMR     (*(XBYTE *)0x2808)


/******************************************************************************
Define
Description: Define global configuration registers
Footnote:
******************************************************************************/
#define    GLOBAL_BASE_ADDR    0x2900
//extern ECReg      LDN_REG;	//      	_at_    (GLOBAL_BASE_ADDR + 0x07);    // Change LDN
extern ECReg      Index_07H;//      _at_    (GLOBAL_BASE_ADDR + 0x07);    // Change LDN
#define LDN 			(*(XBYTE *)0x2907)

extern ECReg      Index_13H;//      _at_    (GLOBAL_BASE_ADDR + 0x13);    // SCI# Output Enable/Disable
extern ECReg      Index_23H;//      _at_    (GLOBAL_BASE_ADDR + 0x23);    //
extern ECReg      Index_25H;//      _at_    (GLOBAL_BASE_ADDR + 0x25);    //
extern ECReg      Index_26H;//      _at_    (GLOBAL_BASE_ADDR + 0x25);    //
extern ECReg      Index_27H;//      _at_    (GLOBAL_BASE_ADDR + 0x27);    //
extern ECReg      Index_28H;//      _at_    (GLOBAL_BASE_ADDR + 0x28);    //
extern ECReg      Index_29H;//      _at_    (GLOBAL_BASE_ADDR + 0x29);    //
extern ECReg      Index_2AH;//      _at_    (GLOBAL_BASE_ADDR + 0x2A);    //
extern ECReg      Index_2BH;//      _at_    (GLOBAL_BASE_ADDR + 0x2B);    //
extern ECReg      Index_2CH;//      _at_    (GLOBAL_BASE_ADDR + 0x2C);    //
extern ECReg      Index_2DH;//      _at_    (GLOBAL_BASE_ADDR + 0x2D);    //

extern ECReg      Index_60H;//      _at_    (GLOBAL_BASE_ADDR + 0x60);    //
extern ECReg      Index_61H;//      _at_    (GLOBAL_BASE_ADDR + 0x61);    //
extern ECReg      Index_62H;//      _at_    (GLOBAL_BASE_ADDR + 0x62);    //
extern ECReg      Index_63H;//      _at_    (GLOBAL_BASE_ADDR + 0x63);    //

extern ECReg      Index_70H;//      _at_    (GLOBAL_BASE_ADDR + 0x70);    //
extern ECReg      Index_76H;//      _at_    (GLOBAL_BASE_ADDR + 0x76);    //

extern ECReg      Index_E9H;//      _at_    (GLOBAL_BASE_ADDR + 0xE9);    //
extern ECReg      Index_A0H;//      _at_    (GLOBAL_BASE_ADDR + 0xA0);
extern ECReg      Index_A1H;//      _at_    (GLOBAL_BASE_ADDR + 0xA1);


extern ECReg      Index_30H;//      _at_    (GLOBAL_BASE_ADDR + 0x30);    //
extern ECReg      Index_B0H;//      _at_    (GLOBAL_BASE_ADDR + 0xB0);    // (LDN=07)GPIO SET 1 PIN POLARITY REGISTER
extern ECReg      Index_B1H;//      _at_    (GLOBAL_BASE_ADDR + 0xB1);    // (LDN=07)GPIO SET 2 PIN POLARITY REGISTER
extern ECReg      Index_B2H;//      _at_    (GLOBAL_BASE_ADDR + 0xB2);    // (LDN=07)GPIO SET 3 PIN POLARITY REGISTER
extern ECReg      Index_B3H;//      _at_    (GLOBAL_BASE_ADDR + 0xB3);    // (LDN=07)GPIO SET 4 PIN POLARITY REGISTER
extern ECReg      Index_B4H;//      _at_    (GLOBAL_BASE_ADDR + 0xB4);    // (LDN=07)GPIO SET 5 PIN POLARITY REGISTER
extern ECReg      Index_B8H;//      _at_    (GLOBAL_BASE_ADDR + 0xB8);    // (LDN=07)GPIO SET 1 PIN INTERNAL PULL-UP ENABLE REGISTER
extern ECReg      Index_B9H;//      _at_    (GLOBAL_BASE_ADDR + 0xB9);    // (LDN=07)GPIO SET 2 PIN INTERNAL PULL-UP ENABLE REGISTER
extern ECReg      Index_BAH;//      _at_    (GLOBAL_BASE_ADDR + 0xBA);    // (LDN=07)GPIO SET 3 PIN INTERNAL PULL-UP ENABLE REGISTER
extern ECReg      Index_BBH;//      _at_    (GLOBAL_BASE_ADDR + 0xBB);    // (LDN=07)GPIO SET 4 PIN INTERNAL PULL-UP ENABLE REGISTER
extern ECReg      Index_BCH;//      _at_    (GLOBAL_BASE_ADDR + 0xBC);    // (LDN=07)GPIO SET 5 PIN INTERNAL PULL-UP ENABLE REGISTER
extern ECReg      Index_BDH;//      _at_    (GLOBAL_BASE_ADDR + 0xBD);    // (LDN=07)GPIO SET 6 PIN INTERNAL PULL-UP ENABLE REGISTER
extern ECReg      Index_BFH;//      _at_    (GLOBAL_BASE_ADDR + 0xBF);    // (LDN=07)GPIO SET 8 PIN INTERNAL PULL-UP ENABLE REGISTER
extern ECReg      Index_C0H;//      _at_    (GLOBAL_BASE_ADDR + 0xC0);    // (LDN=07)SIMPLE I/O SET 1 ENABLE REGISTER
extern ECReg      Index_C1H;//      _at_    (GLOBAL_BASE_ADDR + 0xC1);    // (LDN=07)SIMPLE I/O SET 2 ENABLE REGISTER
extern ECReg      Index_C2H;//      _at_    (GLOBAL_BASE_ADDR + 0xC2);    // (LDN=07)SIMPLE I/O SET 3 ENABLE REGISTER
extern ECReg      Index_C3H;//      _at_    (GLOBAL_BASE_ADDR + 0xC3);    // (LDN=07)SIMPLE I/O SET 4 ENABLE REGISTER
extern ECReg      Index_C4H;//      _at_    (GLOBAL_BASE_ADDR + 0xC4);    // (LDN=07)SIMPLE I/O SET 5 ENABLE REGISTER
extern ECReg      Index_C8H;//      _at_    (GLOBAL_BASE_ADDR + 0xC8);    // (LDN=07)SIMPLE I/O SET 1 OUTPUT ENABLE REGISTER
extern ECReg      Index_C9H;//      _at_    (GLOBAL_BASE_ADDR + 0xC9);    // (LDN=07)SIMPLE I/O SET 2 OUTPUT ENABLE REGISTER
extern ECReg      Index_CAH;//      _at_    (GLOBAL_BASE_ADDR + 0xCA);    // (LDN=07)SIMPLE I/O SET 3 OUTPUT ENABLE REGISTER
extern ECReg      Index_CBH;//      _at_    (GLOBAL_BASE_ADDR + 0xCB);    // (LDN=07)SIMPLE I/O SET 4 OUTPUT ENABLE REGISTER
extern ECReg      Index_CCH;//      _at_    (GLOBAL_BASE_ADDR + 0xCC);    // (LDN=07)SIMPLE I/O SET 5 OUTPUT ENABLE REGISTER
extern ECReg      Index_CDH;//      _at_    (GLOBAL_BASE_ADDR + 0xCD);    // (LDN=07)SIMPLE I/O SET 6 OUTPUT ENABLE REGISTER
extern ECReg      Index_CEH;//      _at_    (GLOBAL_BASE_ADDR + 0xCE);    // (LDN=07)SIMPLE I/O SET 7 OUTPUT ENABLE REGISTER
extern ECReg      Index_CFH;//      _at_    (GLOBAL_BASE_ADDR + 0xCF);    // (LDN=07)SIMPLE I/O SET 8 OUTPUT ENABLE REGISTER
extern ECReg      Index_F0H;//      _at_    (GLOBAL_BASE_ADDR + 0xF0);    //
extern ECReg      Index_F2H;//      _at_    (GLOBAL_BASE_ADDR + 0xF2);    //
extern ECReg      Index_F4H;//      _at_    (GLOBAL_BASE_ADDR + 0xF4);    //
extern ECReg      Index_F7H;//      _at_    (GLOBAL_BASE_ADDR + 0xF7);    //

extern ECReg      DACPDREG;//       _at_    (GLOBAL_BASE_ADDR + 0x90);    // Respective DAC Channel Power Down
extern ECReg      DACDAT0_LSB;//    _at_    (GLOBAL_BASE_ADDR + 0x91);    // DAC Channel 0 Low Byte
extern ECReg      DACDAT0_MSB;//    _at_    (GLOBAL_BASE_ADDR + 0x92);    // DAC Channel 0 High Byte
extern ECReg      DACDAT1_LSB;//    _at_    (GLOBAL_BASE_ADDR + 0x93);    // DAC Channel 1 Low Byte
extern ECReg      DACDAT1_MSB;//    _at_    (GLOBAL_BASE_ADDR + 0x94);    // DAC Channel 1 High Byte
extern ECReg      DACDAT2_LSB;//    _at_    (GLOBAL_BASE_ADDR + 0x95);    // DAC Channel 2 Low Byte
extern ECReg      DACDAT2_MSB;//    _at_    (GLOBAL_BASE_ADDR + 0x96);    // DAC Channel 2 High Byte
extern ECReg      DACDAT3_LSB;//    _at_    (GLOBAL_BASE_ADDR + 0x97);    // DAC Channel 3 Low Byte
extern ECReg      DACDAT3_MSB;//    _at_    (GLOBAL_BASE_ADDR + 0x98);    // DAC Channel 3 High Byte
extern ECReg      DACDAT4_LSB;//    _at_    (GLOBAL_BASE_ADDR + 0x99);    // DAC Channel 4 Low Byte
extern ECReg      DACDAT4_MSB;//    _at_    (GLOBAL_BASE_ADDR + 0x9A);    // DAC Channel 4 High Byte


/******************************************************************************
Define
Description: Define GPIO output registers
Footnote:
******************************************************************************/
#define    GEE_BASE_ADDR    0x2A00
extern ECReg            CFG_REG;                        //_at_ (GEE_BASE_ADDR + 0x00);  //
extern ECReg            HWM_ISR1;                               //_at_ (GEE_BASE_ADDR + 0x01);    //
extern ECReg            PWM_STEP_FREQ_REG;		//_at_ (GEE_BASE_ADDR + 0x0B);
extern ECReg            IF_SELECT_REG ;         //_at_ (GEE_BASE_ADDR + 0x0A);
extern ECReg            PWM_F1TLRR; //                  _at_ (GEE_BASE_ADDR + 0x0D);
extern ECReg            PWM_F2TLRR; //                  _at_ (GEE_BASE_ADDR + 0x0E);
extern ECReg            PWM_F3TLRR; //                  _at_ (GEE_BASE_ADDR + 0x0F);

extern ECReg            FAN0_Limit_LR;//                                _at_ (GEE_BASE_ADDR + 0x10);
extern ECReg            FAN1_Limit_LR;//                                _at_ (GEE_BASE_ADDR + 0x11);
extern ECReg            FAN2_Limit_LR;//                                _at_ (GEE_BASE_ADDR + 0x12);

extern ECReg            FAN_MAIN_CTL;//         _at_ (GEE_BASE_ADDR + 0x13);
extern ECReg            FAN_CTL;//                              _at_ (GEE_BASE_ADDR + 0x14);
extern ECReg            FAN_CTL1;                       //_at_ (GEE_BASE_ADDR + 0x15);  //
extern ECReg            FAN_CTL2;                       //_at_ (GEE_BASE_ADDR + 0x16);  //
extern ECReg            FAN_CTL3;                       //_at_ (GEE_BASE_ADDR + 0x17);  //
extern ECReg            PWM_F1TMRR; //                  _at_ (GEE_BASE_ADDR + 0x18);
extern ECReg            PWM_F2TMRR; //                  _at_ (GEE_BASE_ADDR + 0x19);
extern ECReg            PWM_F3TMRR; //                  _at_ (GEE_BASE_ADDR + 0x1A);

extern ECReg            FAN0_Limit_MR;//                                _at_ (GEE_BASE_ADDR + 0x1B);
extern ECReg            FAN1_Limit_MR;//                                _at_ (GEE_BASE_ADDR + 0x1C);
extern ECReg            FAN2_Limit_MR;//                                _at_ (GEE_BASE_ADDR + 0x1D);

extern ECReg		ADC_channel_enable;//				_at_ (GEE_BASE_ADDR + 0x50);


extern ECReg       zz2;					//_at_(GEE_BASE_ADDR + 0x5C);	//

extern ECReg		PWM_FAN_CTL1; 	//_at_(GEE_BASE_ADDR + 0x63);	//
extern ECReg		PWM_FAN_CTL2; 	//_at_(GEE_BASE_ADDR + 0x6B);	//
extern ECReg		PWM_FAN_CTL3; 	//_at_(GEE_BASE_ADDR + 0x73);	//

extern ECReg		ADC0_test;//				_at_ (GEE_BASE_ADDR + 0x20);

extern ECReg		ADC1_test;//				_at_ (GEE_BASE_ADDR + 0x21);
extern ECReg		ADC2_test;//				_at_ (GEE_BASE_ADDR + 0x22);
extern ECReg		ADC3_test;//				_at_ (GEE_BASE_ADDR + 0x23);
extern ECReg		ADC4_test;//				_at_ (GEE_BASE_ADDR + 0x24);
extern ECReg		ADC5_test;//				_at_ (GEE_BASE_ADDR + 0x25);

extern ECReg		TMPIN1;					//_at_ (GEE_BASE_ADDR + 0x29);
extern ECReg		TMPIN2;					//_at_ (GEE_BASE_ADDR + 0x2A);
extern ECReg		TMPIN3;					//_at_ (GEE_BASE_ADDR + 0x2B);

extern ECReg		ADC_VCEn;//				_at_ (GEE_BASE_ADDR + 0xAC);
extern ECReg		ADC0_VRR;//				_at_ (GEE_BASE_ADDR + 0xB0);
extern ECReg		ADC1_VRR;//				_at_ (GEE_BASE_ADDR + 0xB1);
extern ECReg		ADC2_VRR;//				_at_ (GEE_BASE_ADDR + 0xB2);
extern ECReg		ADC3_VRR;//				_at_ (GEE_BASE_ADDR + 0xB3);
extern ECReg		ADC4_VRR;//				_at_ (GEE_BASE_ADDR + 0xB4);
extern ECReg		ADC5_VRR;//				_at_ (GEE_BASE_ADDR + 0xB5);

extern ECReg	PECI_HOST_STS	;			//_at_ (EC_PECI_BASE_ADDR + 0x08);
extern ECReg	PECI_TARGET_ADDR;			//_at_ (EC_PECI_BASE_ADDR + 0x09);
extern ECReg	PECI_WR_LENGTH	;		//_at_ (EC_PECI_BASE_ADDR + 0x0A);
extern ECReg	PECI_RD_LENGTH	;		//_at_ (EC_PECI_BASE_ADDR + 0x0B);
extern ECReg	PECI_WR_DATA_1	;		//_at_ (EC_PECI_BASE_ADDR + 0x0C);
extern ECReg	PECI_WR_DATA_2_TO_8;		//_at_ (EC_PECI_BASE_ADDR + 0x0D);
extern ECReg	PECI_HOST_CTRL	;			//_at_ (EC_PECI_BASE_ADDR + 0x0E);
extern ECReg	PECI_FIFO	;				//_at_ (EC_PECI_BASE_ADDR + 0x0F);

//#define    EC_SMLINK_BASE_ADDR    0x2A98
extern ECReg	PCH_AMDTSI_HOST_STS;			//_at_ (EC_SMLINK_BASE_ADDR + 0x00);
extern ECReg	PCH_AMDTSI_TARGET_ADDR;		//_at_ (EC_SMLINK_BASE_ADDR + 0x01);
extern ECReg	PCH_AMDTSI_HOST_CMD;				//_at_ (EC_SMLINK_BASE_ADDR + 0x04);
extern ECReg	PCH_AMDTSI_HOST_CTRL;		//_at_ (EC_SMLINK_BASE_ADDR + 0x06);
extern ECReg	PCH_AMDTSI_HOST_FIFO;		//_at_ (EC_SMLINK_BASE_ADDR + 0x07);

/******************************************************************************
Define
Description: Define GPIO output registers
Footnote:
******************************************************************************/
#define    GPIO_BASE_ADDR    0x2C00
extern ECReg      GPIO_1x;//       _at_    (GPIO_BASE_ADDR + 0x00);    //
extern ECReg      GPIO_2x;//       _at_    (GPIO_BASE_ADDR + 0x01);    //
extern ECReg      GPIO_3x;//       _at_    (GPIO_BASE_ADDR + 0x02);    //
extern ECReg      GPIO_4x;//       _at_    (GPIO_BASE_ADDR + 0x03);    //
extern ECReg      GPIO_5x;//       _at_    (GPIO_BASE_ADDR + 0x04);    //
extern ECReg      GPIO_6x;//       _at_    (GPIO_BASE_ADDR + 0x05);    //
extern ECReg      GPIO_7x;//       _at_    (GPIO_BASE_ADDR + 0x06);    //
extern ECReg      GPIO_8x;//       _at_    (GPIO_BASE_ADDR + 0x07);    //


/*****************************************************************************/
// END DEFINITION
/*****************************************************************************/

#endif	// __REG_EC_H__
