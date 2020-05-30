
#include "Core_Inc.h"
#include "Oem_Inc.h"


/********************************************************************************
//For 873x
*********************************************************************************/
#define    SMFI_BASE_ADDR    0x1000
ECReg	FBCFG       	 _at_    (SMFI_BASE_ADDR + 0x00);
ECReg	FPCFG        	_at_    (SMFI_BASE_ADDR + 0x01);
ECReg	FMSSR        	_at_    (SMFI_BASE_ADDR + 0x07);

ECReg	CACHDISR	_at_   (SMFI_BASE_ADDR + 0x33);
ECReg	UCCTRL       	_at_    (SMFI_BASE_ADDR + 0x34);
ECReg	 HCTRL2       	_at_    (SMFI_BASE_ADDR + 0x36);

ECReg	ECINDAR0	_at_	(SMFI_BASE_ADDR + 0x3B);
ECReg	ECINDAR1	_at_	(SMFI_BASE_ADDR + 0x3C);
ECReg	ECINDAR2	_at_	(SMFI_BASE_ADDR + 0x3D);
ECReg	ECINDAR3	_at_	(SMFI_BASE_ADDR + 0x3E);
ECReg	ECINDDR		_at_	(SMFI_BASE_ADDR + 0x3F);
ECReg	SCAR0L		_at_	(SMFI_BASE_ADDR + 0x40);
ECReg	SCAR0M		_at_	(SMFI_BASE_ADDR + 0x41);
ECReg	SCAR0H		_at_	(SMFI_BASE_ADDR + 0x42);
ECReg	SCAR1L		_at_	(SMFI_BASE_ADDR + 0x43);
ECReg	SCAR1M		_at_	(SMFI_BASE_ADDR + 0x44);
ECReg	SCAR1H		_at_	(SMFI_BASE_ADDR + 0x45);
ECReg	SCAR2L		_at_	(SMFI_BASE_ADDR + 0x46);
ECReg	SCAR2M		_at_	(SMFI_BASE_ADDR + 0x47);
ECReg	SCAR2H		_at_	(SMFI_BASE_ADDR + 0x48);
ECReg	SCAR3L		_at_	(SMFI_BASE_ADDR + 0x49);
ECReg	SCAR3M		_at_	(SMFI_BASE_ADDR + 0x4A);
ECReg	SCAR3H		_at_	(SMFI_BASE_ADDR + 0x4B);
ECReg	SCAR4L		_at_	(SMFI_BASE_ADDR + 0x4C);
ECReg	SCAR4M		_at_	(SMFI_BASE_ADDR + 0x4D);
ECReg	SCAR4H		_at_	(SMFI_BASE_ADDR + 0x4E);


ECReg	HINSTC1		_at_	(SMFI_BASE_ADDR + 0x58);

/******************************************************************************
//Define
//Description: Define INTC_BASE_ADDR
//Footnote:
******************************************************************************/
#define	INTC_BASE_ADDR		0x1100
ECReg ISR0    	         _at_    (INTC_BASE_ADDR + 0x00);
ECReg ISR1    	         _at_    (INTC_BASE_ADDR + 0x01);
ECReg ISR2    	         _at_    (INTC_BASE_ADDR + 0x02);
ECReg ISR3    	         _at_    (INTC_BASE_ADDR + 0x03);
ECReg IER0               _at_    (INTC_BASE_ADDR + 0x04);
ECReg IER1			_at_    (INTC_BASE_ADDR + 0x05);
ECReg IER2               _at_    (INTC_BASE_ADDR + 0x06);
ECReg IER3               _at_    (INTC_BASE_ADDR + 0x07);
ECReg IELMR0           _at_    (INTC_BASE_ADDR + 0x08);
ECReg IELMR1         	 _at_    (INTC_BASE_ADDR + 0x09);
ECReg IELMR2         	 _at_    (INTC_BASE_ADDR + 0x0A);
ECReg IELMR3         	 _at_    (INTC_BASE_ADDR + 0x0B);
ECReg IPOLR0         	 _at_    (INTC_BASE_ADDR + 0x0C);
ECReg IPOLR1         	 _at_    (INTC_BASE_ADDR + 0x0D);
ECReg IPOLR2         	 _at_    (INTC_BASE_ADDR + 0x0E);
ECReg IPOLR3         	 _at_    (INTC_BASE_ADDR + 0x0F);
ECReg IVECT         	 _at_    (INTC_BASE_ADDR + 0x10);
ECReg INT0ST         	 _at_    (INTC_BASE_ADDR + 0x11);
ECReg PFAILR         	 _at_    (INTC_BASE_ADDR + 0x12);
ECReg ISR4    	         _at_    (INTC_BASE_ADDR + 0x14);	// 8513 Only
ECReg IER4               _at_    (INTC_BASE_ADDR + 0x15); 	// 8513 Only
ECReg IELMR4         	 _at_    (INTC_BASE_ADDR + 0x16);	// 8513 Only
ECReg IPOLR4         	 _at_    (INTC_BASE_ADDR + 0x17);	// 8513 Only
ECReg ISR6         	 _at_    (INTC_BASE_ADDR + 0x1C);	
ECReg IER6         	 _at_    (INTC_BASE_ADDR + 0x1D);	
ECReg ISR8         	 _at_    (INTC_BASE_ADDR + 0x24);
ECReg IER8         	 _at_    (INTC_BASE_ADDR + 0x25);


ECReg ISR5    	         _at_    (INTC_BASE_ADDR + 0x18);	//
ECReg IER5               _at_    (INTC_BASE_ADDR + 0x19); 	//
ECReg IELMR5         	 _at_    (INTC_BASE_ADDR + 0x1A);	// Not Adjustble
ECReg IPOLR5         	 _at_    (INTC_BASE_ADDR + 0x1B);	// Not Adjustble

ECReg ISR6    	         _at_    (INTC_BASE_ADDR + 0x1C);	//
ECReg IER6               _at_    (INTC_BASE_ADDR + 0x1D); 	//
ECReg IELMR6         	 _at_    (INTC_BASE_ADDR + 0x1E);	//
ECReg IPOLR6         	 _at_    (INTC_BASE_ADDR + 0x1F);	//

ECReg ISR7    	         _at_    (INTC_BASE_ADDR + 0x20);	//
ECReg IER7               _at_    (INTC_BASE_ADDR + 0x21); 	//
ECReg IELMR7         	 _at_    (INTC_BASE_ADDR + 0x22);	//
ECReg IPOLR7         	 _at_    (INTC_BASE_ADDR + 0x23);	//

ECReg IELMR8         	 _at_    (INTC_BASE_ADDR + 0x26);	//
ECReg IPOLR8         	 _at_    (INTC_BASE_ADDR + 0x27);	//
/******************************************************************************
Define
Description: Define PMC_BASE_ADDR
Footnote:
******************************************************************************/
#define	PMC_BASE_ADDR		0x1500
ECReg PM1STS		  _at_    (PMC_BASE_ADDR + 0x00);
ECReg PM1DO		  _at_    (PMC_BASE_ADDR + 0x01);
ECReg PM1DOSCI		  _at_    (PMC_BASE_ADDR + 0x02);
ECReg PM1DOSMI		  _at_    (PMC_BASE_ADDR + 0x03);
ECReg PM1DI		  _at_    (PMC_BASE_ADDR + 0x04);
ECReg PM1DISCI		  _at_    (PMC_BASE_ADDR + 0x05);
ECReg PM1CTL		  _at_    (PMC_BASE_ADDR + 0x06);
ECReg PM1IC		  _at_    (PMC_BASE_ADDR + 0x07);
ECReg PM1IE		  _at_    (PMC_BASE_ADDR + 0x08);

ECReg PM2STS		  _at_    (PMC_BASE_ADDR + 0x10);
ECReg PM2DO		  _at_    (PMC_BASE_ADDR + 0x11);
ECReg PM2DOSCI		  _at_    (PMC_BASE_ADDR + 0x12);
ECReg PM2DOSMI		  _at_    (PMC_BASE_ADDR + 0x13);
ECReg PM2DI		  _at_    (PMC_BASE_ADDR + 0x14);
ECReg PM2DISCI		  _at_    (PMC_BASE_ADDR + 0x15);
ECReg PM2CTL		  _at_    (PMC_BASE_ADDR + 0x16);
ECReg PM2IC		  _at_    (PMC_BASE_ADDR + 0x17);
ECReg PM2IE		  _at_    (PMC_BASE_ADDR + 0x18);

ECReg MBXCTRL		  _at_    (PMC_BASE_ADDR + 0x19);
ECReg PMIRQR		  _at_    (PMC_BASE_ADDR + 0x20);
ECReg PMHICR		  _at_    (PMC_BASE_ADDR + 0x21);

/******************************************************************************
Define
Description: Define EC_PWM_BASE_ADDR
Footnote:
******************************************************************************/
#define	EC_PWM_BASE_ADDR 0x1800

ECReg CPRS  			_at_    (EC_PWM_BASE_ADDR + 0x00);
ECReg DCR			_at_    (EC_PWM_BASE_ADDR + 0x01);
ECReg PWMCTL      	_at_    (EC_PWM_BASE_ADDR + 0x02);


/******************************************************************************
Define
Description: Define WUC_BASE_ADDR
Footnote:
******************************************************************************/
#define	WUC_BASE_ADDR		0x1B00
ECReg  WUEMR1 		_at_    (WUC_BASE_ADDR + 0x00);		// Wake-up Edge Mode Reg 1
ECReg  WUEMR2 		_at_    (WUC_BASE_ADDR + 0x01);		// Wake-up Edge Mode Reg 2
ECReg  WUEMR3 		_at_    (WUC_BASE_ADDR + 0x02);		// Wake-up Edge Mode Reg 3
ECReg  WUEMR4 		_at_    (WUC_BASE_ADDR + 0x03);		// Wake-up Edge Mode Reg 4
ECReg  WUEMR5 		_at_    (WUC_BASE_ADDR + 0x0C);		// Wake-up Edge Mode Reg 5 (IT8750)
ECReg  WUEMR6 		_at_    (WUC_BASE_ADDR + 0x10);		// Wake-up Edge Mode Reg 6 (IT8516)

ECReg  WUESR1 		_at_    (WUC_BASE_ADDR + 0x04);		// Wake-up Edge Sense Reg 1
ECReg  WUESR2 		_at_    (WUC_BASE_ADDR + 0x05);		// Wake-up Edge Sense Reg 2
ECReg  WUESR3 		_at_    (WUC_BASE_ADDR + 0x06);		// Wake-up Edge Sense Reg 3
ECReg  WUESR4 		_at_    (WUC_BASE_ADDR + 0x07);		// Wake-up Edge Sense Reg 4
ECReg  WUESR5 		_at_    (WUC_BASE_ADDR + 0x0D);		// Wake-up Edge Sense Reg 5 (IT8750)
ECReg  WUESR6 		_at_    (WUC_BASE_ADDR + 0x11);		// Wake-up Edge Sense Reg 6 (IT8516)

ECReg  WUENR1 		_at_    (WUC_BASE_ADDR + 0x08);		// Wake-up Enable Reg 1
ECReg  WUENR2 		_at_    (WUC_BASE_ADDR + 0x09);		// Wake-up Enable Reg 2
ECReg  WUENR3 		_at_    (WUC_BASE_ADDR + 0x0A);		// Wake-up Enable Reg 3
ECReg  WUENR4 		_at_    (WUC_BASE_ADDR + 0x0B);		// Wake-up Enable Reg 4
ECReg  WUENR5 		_at_    (WUC_BASE_ADDR + 0x0E);		// Wake-up Enable Reg 5 (IT8750)
ECReg  WUENR6 		_at_    (WUC_BASE_ADDR + 0x12);		// Wake-up Enable Reg 6 (IT8516)

/******************************************************************************
Define
Description: Define SMB_BASE_ADDR
Footnote:
******************************************************************************/
#define	SMB_BASE_ADDR		0x1C00
ECReg  HOSTA_A		_at_    (SMB_BASE_ADDR + 0x00);		// HOST Status
ECReg  HOCTL_A      	_at_    (SMB_BASE_ADDR + 0x01); 	// HOST Control
ECReg  HOCMD_A      	_at_   	(SMB_BASE_ADDR + 0x02);		// HOST Command
ECReg  TRASLA_A     	_at_    (SMB_BASE_ADDR + 0x03);		// Transmit Slave Address
ECReg  D0REG_A      	_at_    (SMB_BASE_ADDR + 0x04);		// HOST Data0
ECReg  D1REG_A      	_at_   	(SMB_BASE_ADDR + 0x05);		// HOST Data1
ECReg  HOBDB_A      	_at_    (SMB_BASE_ADDR + 0x06);  	// HOST Block Data Byte
ECReg  PECERC_A     	_at_    (SMB_BASE_ADDR + 0x07); 	// Packet Error Check
ECReg  SMBPCTL_A    	_at_   	(SMB_BASE_ADDR + 0x0A);  	// SMBUS Pin Control
ECReg  HOCTL2_A     	_at_    (SMB_BASE_ADDR + 0x10); 	// HOST Control2
ECReg  HOSTA_B     	_at_    (SMB_BASE_ADDR + 0x11);		// HOST Status
ECReg  HOCTL_B      	_at_    (SMB_BASE_ADDR + 0x12);		// HOST Control
ECReg  HOCMD_B      	_at_   	(SMB_BASE_ADDR + 0x13);		// HOST Command
ECReg  TRASLA_B     	_at_    (SMB_BASE_ADDR + 0x14);		// Transmit Slave Address
ECReg  D0REG_B      	_at_    (SMB_BASE_ADDR + 0x15);		// HOST Data0
ECReg  D1REG_B      	_at_   	(SMB_BASE_ADDR + 0x16);		// HOST Data1
ECReg  HOBDB_B      	_at_   	(SMB_BASE_ADDR + 0x17);		// HOST Block Data Byte
ECReg  PECERC_B     	_at_    (SMB_BASE_ADDR + 0x18);	 	// Packet Error Check
ECReg  SMBPCTL_B    	_at_   	(SMB_BASE_ADDR + 0x1B);	  	// SMBUS Pin Control
ECReg  HOCTL2_B     	_at_    (SMB_BASE_ADDR + 0x21);	 	// HOST Control2
ECReg  SMBUS_4P7USREG    _at_    (SMB_BASE_ADDR + 0x22); 	// SMB TIMING SETUP1
ECReg  SMBUS_4P0USREG    _at_    (SMB_BASE_ADDR + 0x23); 	// SMB TIMING SETUP2
ECReg  SMBUS_300NSREG    _at_    (SMB_BASE_ADDR + 0x24); 	// SMB TIMING SETUP3
ECReg  SMBUS_250NSREG    _at_    (SMB_BASE_ADDR + 0x25); 	// SMB TIMING SETUP4
ECReg  SMBUS_25MSREG     _at_    (SMB_BASE_ADDR + 0x26); 	// SMB TIMING SETUP5
ECReg  SMBUS_45P3USLREG  _at_    (SMB_BASE_ADDR + 0x27); 	// SMB TIMING SETUP6
ECReg  SMBUS_45P3USHREG  _at_    (SMB_BASE_ADDR + 0x28);		// SMB TIMING SETUP7
ECReg  HOSTA_C      	_at_    (SMB_BASE_ADDR + 0x29);	  	// HOST Status
ECReg  HOCTL_C      	_at_    (SMB_BASE_ADDR + 0x2A);	  	// HOST Control
ECReg  HOCMD_C      	_at_   	(SMB_BASE_ADDR + 0x2B);	  	// HOST Command
ECReg  TRASLA_C     	_at_    (SMB_BASE_ADDR + 0x2C);	  	// Transmit Slave Address
ECReg  D0REG_C      	_at_    (SMB_BASE_ADDR + 0x2D);	  	// HOST Data0
ECReg  D1REG_C      	_at_    (SMB_BASE_ADDR + 0x2E);	  	// HOST Data1
ECReg  HOBDB_C      	_at_    (SMB_BASE_ADDR + 0x2F);	  	// HOST Block Data Byte
ECReg  PECERC_C     	_at_    (SMB_BASE_ADDR + 0x30);	  	// Packet Error Check
ECReg  SMBPCTL_C    	_at_   	(SMB_BASE_ADDR + 0x31);	  	// SMBUS Pin Control
ECReg  HOCTL2_C     	_at_    (SMB_BASE_ADDR + 0x32);	  	// HOST Control2
ECReg  SMBUS_4P7A4P0H    _at_    (SMB_BASE_ADDR + 0x33); 	// SMB TIMING SETUP8

/******************************************************************************
Define
Description: Define SWKBC_BASE_ADDR
Footnote:
******************************************************************************/
#define SWKBC_BASE_ADDR   0x1D00
ECReg  KSOR          _at_ (SWKBC_BASE_ADDR + 0x00);
ECReg  KSOCTRL    _at_ (SWKBC_BASE_ADDR + 0x01);
ECReg  KSIR            _at_ (SWKBC_BASE_ADDR + 0x02);
ECReg  KSICTRLR    _at_ (SWKBC_BASE_ADDR + 0x03);
ECReg  SCCTRL       _at_ (SWKBC_BASE_ADDR + 0x04);
ECReg  KBHICR       _at_ (SWKBC_BASE_ADDR + 0x07);
ECReg  KBHISR       _at_ (SWKBC_BASE_ADDR + 0x08);
ECReg  KBHIKDOR  _at_ (SWKBC_BASE_ADDR + 0x09);
ECReg  KBHIDIR      _at_ (SWKBC_BASE_ADDR + 0x0A);

/******************************************************************************
Define
Description: Define ECPM_BASE_ADDR
Footnote:
******************************************************************************/
#define	ECPM_BASE_ADDR		0x1E00
ECReg  EC_1E00  		_at_    (ECPM_BASE_ADDR + 0x00);	// Clock Frequency Select(8510,8511 only)
ECReg  ECPM_CGCTRL1R 	_at_    (ECPM_BASE_ADDR + 0x01);	// Clock Gating Control1
ECReg  CGCTRL2R 		_at_    (ECPM_BASE_ADDR + 0x02);	// Clock Gating Control2
ECReg  EC_1E03 		_at_    (ECPM_BASE_ADDR + 0x03);	// PLL Control
ECReg  AUTOCG 		_at_    (ECPM_BASE_ADDR + 0x04);	// Auto Clock Gatting
ECReg  CGCTRL3R 		_at_    (ECPM_BASE_ADDR + 0x05);	// Clock Gating Control3
ECReg  EC_1E06 		_at_    (ECPM_BASE_ADDR + 0x06);
ECReg  PLLCSS 		_at_    (ECPM_BASE_ADDR + 0x08);

/******************************************************************************
Define
Description: Define ETWD_BASE_ADDR
Footnote:
******************************************************************************/
#define	ETWD_BASE_ADDR		0x1F00
ECReg  ETWCFG		_at_    (ETWD_BASE_ADDR + 0x01);	// External Timer/WDT Configuration REG
ECReg  ETPSR		_at_    (ETWD_BASE_ADDR + 0x02);	// External Timer Prescaler REG
ECReg  ETCNTLHR		_at_    (ETWD_BASE_ADDR + 0x03);	// External Timer Counter High Byte
ECReg  ETCNTLLR		_at_    (ETWD_BASE_ADDR + 0x04);	// External Timer Counter Low Byte
ECReg  ETWCTRL		_at_    (ETWD_BASE_ADDR + 0x05);	// External Timer/WDT Control REG
ECReg  EWDCNTLHR		_at_    (ETWD_BASE_ADDR + 0x09);	// External WDT Counter High Byte
ECReg  EWDCNTLLR		_at_    (ETWD_BASE_ADDR + 0x06);	// External WDT Counter Low Byte
ECReg  EWDKEYR		_at_    (ETWD_BASE_ADDR + 0x07);	// External WDT Key REG
ECReg  RSTSCR		_at_    (ETWD_BASE_ADDR + 0x08);	// Reset Scratch REG


/******************************************************************************
Define
Description: Define EC interface base address
Footnote:
******************************************************************************/
#define    GCTRL_BASE_ADDR    0x2000
ECReg    ECHIPID1       _at_    (GCTRL_BASE_ADDR + 0x00);    // CHIP ID BYTE 1
ECReg    ECHIPID2       _at_    (GCTRL_BASE_ADDR + 0x01);    // CHIP ID BYTE 2
ECReg    ECHIPVER       _at_    (GCTRL_BASE_ADDR + 0x02);    // CHIP VERSION
ECReg    RSTS           _at_    (GCTRL_BASE_ADDR + 0x06);    // RESET STATUS
ECReg    RSTC1          _at_    (GCTRL_BASE_ADDR + 0x07);    // RESET CONTROL 1
ECReg    RSTC2          _at_    (GCTRL_BASE_ADDR + 0x08);    // RESET CONTROL 2
ECReg    RSTC3          _at_    (GCTRL_BASE_ADDR + 0x09);    // RESET CONTROL 3
ECReg    WNCKR          _at_    (GCTRL_BASE_ADDR + 0x0B);    // WAIT NEXT CLOCK RISING
ECReg    SPCTRL1        _at_    (GCTRL_BASE_ADDR + 0x0D);    // SPECIAL CONTROL 1
ECReg    GENIRQ         _at_    (GCTRL_BASE_ADDR + 0x0F);    // GENERATE IRQ
ECReg    RSTC4          _at_    (GCTRL_BASE_ADDR + 0x11);    // RESET CONTROL 4
ECReg    SPCTRL2        _at_    (GCTRL_BASE_ADDR + 0x12);    // SPECIAL CONTROL 2
ECReg    PI2ECH         _at_    (GCTRL_BASE_ADDR + 0x14);    // PORT I2EC HIGH-BYTE REGISTER
ECReg    PI2ECL         _at_    (GCTRL_BASE_ADDR + 0x15);    // PORT I2EC LOW-BYTE REGISTER
ECReg    SPCTRL3        _at_    (GCTRL_BASE_ADDR + 0x16);    // SPECIAL CONTROL 3

/******************************************************************************
Define
Description: Define CIR_BASE_ADDR
Footnote:
******************************************************************************/
#define	CIR_BASE_ADDR		0x2300
ECReg	CIR_DR				_at_	CIR_BASE_ADDR+0x00;
ECReg	CIR_IER				_at_	CIR_BASE_ADDR+0x01;	//bit: BR
ECReg	CIR_RCR				_at_	CIR_BASE_ADDR+0x02;
ECReg	CIR_TCR1			_at_	CIR_BASE_ADDR+0x03;
ECReg	CIR_TCR2			_at_	CIR_BASE_ADDR+0x04;
ECReg	CIR_TSR				_at_	CIR_BASE_ADDR+0x05;
ECReg	CIR_RSR			_at_	CIR_BASE_ADDR+0x06;
//#define	CIR_BDLR	CIR_TSR			//_at_	CIR_BASE_ADDR+0x05;	//BR = 1
//#define	CIR_BDHR	CIR_RSR		//_at_	CIR_BASE_ADDR+0x06;	//BR = 1
ECReg	CIR_IIR				_at_	CIR_BASE_ADDR+0x07;	


/******************************************************************************
Define
Description: Define SPI_BASE_ADDR
Footnote:
******************************************************************************/
#define	SPI_BASE_ADDR		0x2600
ECReg SPI0_DATA_REG		_at_    (SPI_BASE_ADDR + 0x00);	//
ECReg SPI0_CTRL1_REG		_at_    (SPI_BASE_ADDR + 0x01);	//
ECReg SPI0_CTRL2_REG		_at_    (SPI_BASE_ADDR + 0x02);	//
ECReg SPI0_STATUS_REG		_at_    (SPI_BASE_ADDR + 0x03);	//
ECReg SPI0_CTRL3_REG		_at_    (SPI_BASE_ADDR + 0x04);	//

ECReg SPI1_DATA_REG		_at_    (SPI_BASE_ADDR + 0x10);	//
ECReg SPI1_CTRL1_REG		_at_    (SPI_BASE_ADDR + 0x11);	//
ECReg SPI1_CTRL2_REG		_at_    (SPI_BASE_ADDR + 0x12);	//
ECReg SPI1_STATUS_REG		_at_    (SPI_BASE_ADDR + 0x13);	//
ECReg SPI1_CTRL3_REG		_at_    (SPI_BASE_ADDR + 0x14);	//

/******************************************************************************
Define
Description: Define UART1_BASE_ADDR
Footnote:
******************************************************************************/
#define	UART1_BASE_ADDR		0x2700
ECReg 	UART1_RBR_REG		_at_    (UART1_BASE_ADDR + 0x00);	//
ECReg 	UART1_IER_REG		_at_    (UART1_BASE_ADDR + 0x01);	//
ECReg 	UART1_IIR_REG		_at_    (UART1_BASE_ADDR + 0x02);	//
ECReg 	UART1_LCR_REG		_at_    (UART1_BASE_ADDR + 0x03);	//
ECReg 	UART1_MCR_REG		_at_    (UART1_BASE_ADDR + 0x04);	//
ECReg 	UART1_LSR_REG		_at_    (UART1_BASE_ADDR + 0x05);	//
ECReg 	UART1_MSR_REG		_at_    (UART1_BASE_ADDR + 0x06);	//
ECReg 	UART1_SCR_REG		_at_    (UART1_BASE_ADDR + 0x07);	//

/******************************************************************************
Define
Description: Define UART2_BASE_ADDR
Footnote:
******************************************************************************/
#define	UART2_BASE_ADDR		0x2800
ECReg 	UART2_RBR_REG		_at_    (UART2_BASE_ADDR + 0x00);	//
ECReg 	UART2_IER_REG		_at_    (UART2_BASE_ADDR + 0x01);	//
ECReg 	UART2_IIR_REG		_at_    (UART2_BASE_ADDR + 0x02);	//
ECReg 	UART2_LCR_REG		_at_    (UART2_BASE_ADDR + 0x03);	//
ECReg 	UART2_MCR_REG		_at_    (UART2_BASE_ADDR + 0x04);	//
ECReg 	UART2_LSR_REG		_at_    (UART2_BASE_ADDR + 0x05);	//
ECReg 	UART2_MSR_REG		_at_    (UART2_BASE_ADDR + 0x06);	//
ECReg 	UART2_SCR_REG		_at_    (UART2_BASE_ADDR + 0x07);	//


/******************************************************************************
Define
Description: Define global configuration registers
Footnote:
******************************************************************************/
#define    GLOBAL_BASE_ADDR    0x2900
//ECReg      LDN_REG          _at_    (GLOBAL_BASE_ADDR + 0x07);    // Change LDN
ECReg      Index_07H      _at_    (GLOBAL_BASE_ADDR + 0x07);    // Change LDN
ECReg      Index_13H      _at_    (GLOBAL_BASE_ADDR + 0x13);    // SCI# Output Enable/Disable
ECReg      Index_23H      _at_    (GLOBAL_BASE_ADDR + 0x23);    //
ECReg      Index_25H      _at_    (GLOBAL_BASE_ADDR + 0x25);    //
ECReg      Index_26H      _at_    (GLOBAL_BASE_ADDR + 0x26);    //
ECReg      Index_27H      _at_    (GLOBAL_BASE_ADDR + 0x27);    //
ECReg      Index_28H      _at_    (GLOBAL_BASE_ADDR + 0x28);    //
ECReg      Index_29H      _at_    (GLOBAL_BASE_ADDR + 0x29);    //
ECReg      Index_2AH      _at_    (GLOBAL_BASE_ADDR + 0x2A);    //
ECReg      Index_2BH      _at_    (GLOBAL_BASE_ADDR + 0x2B);    //
ECReg      Index_2CH      _at_    (GLOBAL_BASE_ADDR + 0x2C);    //
ECReg      Index_2DH      _at_    (GLOBAL_BASE_ADDR + 0x2D);    //


ECReg      Index_60H      _at_    (GLOBAL_BASE_ADDR + 0x60);    //
ECReg      Index_61H      _at_    (GLOBAL_BASE_ADDR + 0x61);    //
ECReg      Index_62H      _at_    (GLOBAL_BASE_ADDR + 0x62);    //
ECReg      Index_63H      _at_    (GLOBAL_BASE_ADDR + 0x63);    //

ECReg      Index_70H      _at_    (GLOBAL_BASE_ADDR + 0x70);    //
ECReg      Index_76H      _at_    (GLOBAL_BASE_ADDR + 0x76);    //

ECReg      Index_E9H      _at_    (GLOBAL_BASE_ADDR + 0xE9);    //
ECReg      Index_A0H      _at_    (GLOBAL_BASE_ADDR + 0xA0);
ECReg      Index_A1H      _at_    (GLOBAL_BASE_ADDR + 0xA1);


ECReg      Index_30H      _at_    (GLOBAL_BASE_ADDR + 0x30);    //
ECReg      Index_B0H      _at_    (GLOBAL_BASE_ADDR + 0xB0);    // (LDN=07)GPIO SET 1 PIN POLARITY REGISTER
ECReg      Index_B1H      _at_    (GLOBAL_BASE_ADDR + 0xB1);    // (LDN=07)GPIO SET 2 PIN POLARITY REGISTER
ECReg      Index_B2H      _at_    (GLOBAL_BASE_ADDR + 0xB2);    // (LDN=07)GPIO SET 3 PIN POLARITY REGISTER
ECReg      Index_B3H      _at_    (GLOBAL_BASE_ADDR + 0xB3);    // (LDN=07)GPIO SET 4 PIN POLARITY REGISTER
ECReg      Index_B4H      _at_    (GLOBAL_BASE_ADDR + 0xB4);    // (LDN=07)GPIO SET 5 PIN POLARITY REGISTER
ECReg      Index_B8H      _at_    (GLOBAL_BASE_ADDR + 0xB8);    // (LDN=07)GPIO SET 1 PIN INTERNAL PULL-UP ENABLE REGISTER
ECReg      Index_B9H      _at_    (GLOBAL_BASE_ADDR + 0xB9);    // (LDN=07)GPIO SET 2 PIN INTERNAL PULL-UP ENABLE REGISTER
ECReg      Index_BAH      _at_    (GLOBAL_BASE_ADDR + 0xBA);    // (LDN=07)GPIO SET 3 PIN INTERNAL PULL-UP ENABLE REGISTER
ECReg      Index_BBH      _at_    (GLOBAL_BASE_ADDR + 0xBB);    // (LDN=07)GPIO SET 4 PIN INTERNAL PULL-UP ENABLE REGISTER
ECReg      Index_BCH      _at_    (GLOBAL_BASE_ADDR + 0xBC);    // (LDN=07)GPIO SET 5 PIN INTERNAL PULL-UP ENABLE REGISTER
ECReg      Index_BDH      _at_    (GLOBAL_BASE_ADDR + 0xBD);    // (LDN=07)GPIO SET 6 PIN INTERNAL PULL-UP ENABLE REGISTER
ECReg      Index_BFH      _at_    (GLOBAL_BASE_ADDR + 0xBF);    // (LDN=07)GPIO SET 8 PIN INTERNAL PULL-UP ENABLE REGISTER
ECReg      Index_C0H      _at_    (GLOBAL_BASE_ADDR + 0xC0);    // (LDN=07)SIMPLE I/O SET 1 ENABLE REGISTER
ECReg      Index_C1H      _at_    (GLOBAL_BASE_ADDR + 0xC1);    // (LDN=07)SIMPLE I/O SET 2 ENABLE REGISTER
ECReg      Index_C2H      _at_    (GLOBAL_BASE_ADDR + 0xC2);    // (LDN=07)SIMPLE I/O SET 3 ENABLE REGISTER
ECReg      Index_C3H      _at_    (GLOBAL_BASE_ADDR + 0xC3);    // (LDN=07)SIMPLE I/O SET 4 ENABLE REGISTER
ECReg      Index_C4H      _at_    (GLOBAL_BASE_ADDR + 0xC4);    // (LDN=07)SIMPLE I/O SET 5 ENABLE REGISTER
ECReg      Index_C8H      _at_    (GLOBAL_BASE_ADDR + 0xC8);    // (LDN=07)SIMPLE I/O SET 1 OUTPUT ENABLE REGISTER
ECReg      Index_C9H      _at_    (GLOBAL_BASE_ADDR + 0xC9);    // (LDN=07)SIMPLE I/O SET 2 OUTPUT ENABLE REGISTER
ECReg      Index_CAH      _at_    (GLOBAL_BASE_ADDR + 0xCA);    // (LDN=07)SIMPLE I/O SET 3 OUTPUT ENABLE REGISTER
ECReg      Index_CBH      _at_    (GLOBAL_BASE_ADDR + 0xCB);    // (LDN=07)SIMPLE I/O SET 4 OUTPUT ENABLE REGISTER
ECReg      Index_CCH      _at_    (GLOBAL_BASE_ADDR + 0xCC);    // (LDN=07)SIMPLE I/O SET 5 OUTPUT ENABLE REGISTER
ECReg      Index_CDH      _at_    (GLOBAL_BASE_ADDR + 0xCD);    // (LDN=07)SIMPLE I/O SET 6 OUTPUT ENABLE REGISTER
ECReg      Index_CEH      _at_    (GLOBAL_BASE_ADDR + 0xCE);    // (LDN=07)SIMPLE I/O SET 7 OUTPUT ENABLE REGISTER
ECReg      Index_CFH      _at_    (GLOBAL_BASE_ADDR + 0xCF);    // (LDN=07)SIMPLE I/O SET 8 OUTPUT ENABLE REGISTER
ECReg      Index_F0H      _at_    (GLOBAL_BASE_ADDR + 0xF0);    //
ECReg      Index_F2H      _at_    (GLOBAL_BASE_ADDR + 0xF2);    //
ECReg      Index_F4H      _at_    (GLOBAL_BASE_ADDR + 0xF4);    //
ECReg      Index_F7H      _at_    (GLOBAL_BASE_ADDR + 0xF7);    //

ECReg      DACPDREG       _at_    (GLOBAL_BASE_ADDR + 0x90);    // Respective DAC Channel Power Down
ECReg      DACDAT0_LSB    _at_    (GLOBAL_BASE_ADDR + 0x91);    // DAC Channel 0 Low Byte
ECReg      DACDAT0_MSB    _at_    (GLOBAL_BASE_ADDR + 0x92);    // DAC Channel 0 High Byte
ECReg      DACDAT1_LSB    _at_    (GLOBAL_BASE_ADDR + 0x93);    // DAC Channel 1 Low Byte
ECReg      DACDAT1_MSB    _at_    (GLOBAL_BASE_ADDR + 0x94);    // DAC Channel 1 High Byte
ECReg      DACDAT2_LSB    _at_    (GLOBAL_BASE_ADDR + 0x95);    // DAC Channel 2 Low Byte
ECReg      DACDAT2_MSB    _at_    (GLOBAL_BASE_ADDR + 0x96);    // DAC Channel 2 High Byte
ECReg      DACDAT3_LSB    _at_    (GLOBAL_BASE_ADDR + 0x97);    // DAC Channel 3 Low Byte
ECReg      DACDAT3_MSB    _at_    (GLOBAL_BASE_ADDR + 0x98);    // DAC Channel 3 High Byte
ECReg      DACDAT4_LSB    _at_    (GLOBAL_BASE_ADDR + 0x99);    // DAC Channel 4 Low Byte
ECReg      DACDAT4_MSB    _at_    (GLOBAL_BASE_ADDR + 0x9A);    // DAC Channel 4 High Byte




/******************************************************************************
Define
Description: Define Environment Controller output registers
Footnote:
******************************************************************************/
//#define    GEE_BASE_ADDR    0x2A00
ECReg   CFG_REG                        	 _at_ (GEE_BASE_ADDR + 0x00);    //
ECReg   HWM_ISR1				_at_ (GEE_BASE_ADDR + 0x01);    //
ECReg   IF_SELECT_REG                   _at_ (GEE_BASE_ADDR + 0x0A);
ECReg   PWM_STEP_FREQ_REG		_at_ (GEE_BASE_ADDR + 0x0B);
ECReg   PWM_F1TLRR                      _at_ (GEE_BASE_ADDR + 0x0D);
ECReg   PWM_F2TLRR                      _at_ (GEE_BASE_ADDR + 0x0E);
ECReg   PWM_F3TLRR                      _at_ (GEE_BASE_ADDR + 0x0F);
ECReg   FAN0_Limit_LR			_at_ (GEE_BASE_ADDR + 0x10);
ECReg   FAN1_Limit_LR			_at_ (GEE_BASE_ADDR + 0x11);
ECReg   FAN2_Limit_LR			_at_ (GEE_BASE_ADDR + 0x12);
ECReg   FAN_MAIN_CTL                    _at_ (GEE_BASE_ADDR + 0x13);
ECReg   FAN_CTL                                 _at_ (GEE_BASE_ADDR + 0x14);
ECReg   FAN_CTL1                                _at_ (GEE_BASE_ADDR + 0x15);
ECReg   FAN_CTL2                                _at_ (GEE_BASE_ADDR + 0x16);
ECReg   FAN_CTL3                                _at_ (GEE_BASE_ADDR + 0x17);
ECReg   PWM_F1TMRR                      _at_ (GEE_BASE_ADDR + 0x18);
ECReg   PWM_F2TMRR                      _at_ (GEE_BASE_ADDR + 0x19);
ECReg   PWM_F3TMRR                      _at_ (GEE_BASE_ADDR + 0x1A);

ECReg   FAN0_Limit_MR                           _at_ (GEE_BASE_ADDR + 0x1B);
ECReg   FAN1_Limit_MR                           _at_ (GEE_BASE_ADDR + 0x1C);
ECReg   FAN2_Limit_MR                           _at_ (GEE_BASE_ADDR + 0x1D);

ECReg	ADC_channel_enable		_at_ (GEE_BASE_ADDR + 0x50);

ECReg	zz2						_at_ (GEE_BASE_ADDR + 0x5C);    //

ECReg	PWM_FAN_CTL1			_at_ (GEE_BASE_ADDR + 0x63);
ECReg	PWM_FAN_CTL2			_at_ (GEE_BASE_ADDR + 0x6B);
ECReg	PWM_FAN_CTL3			_at_ (GEE_BASE_ADDR + 0x73);

ECReg	ADC0_test				_at_ (GEE_BASE_ADDR + 0x20);
ECReg	ADC1_test				_at_ (GEE_BASE_ADDR + 0x21);
ECReg	ADC2_test				_at_ (GEE_BASE_ADDR + 0x22);
ECReg	ADC3_test				_at_ (GEE_BASE_ADDR + 0x23);
ECReg	ADC4_test				_at_ (GEE_BASE_ADDR + 0x24);
ECReg	ADC5_test				_at_ (GEE_BASE_ADDR + 0x25);

ECReg	TMPIN1					_at_ (GEE_BASE_ADDR + 0x29);
ECReg	TMPIN2					_at_ (GEE_BASE_ADDR + 0x2A);
ECReg	TMPIN3					_at_ (GEE_BASE_ADDR + 0x2B);

ECReg	ADC_VCEn				_at_ (GEE_BASE_ADDR + 0xAC);
ECReg	ADC0_VRR				_at_ (GEE_BASE_ADDR + 0xB0);
ECReg	ADC1_VRR				_at_ (GEE_BASE_ADDR + 0xB1);
ECReg	ADC2_VRR				_at_ (GEE_BASE_ADDR + 0xB2);
ECReg	ADC3_VRR				_at_ (GEE_BASE_ADDR + 0xB3);
ECReg	ADC4_VRR				_at_ (GEE_BASE_ADDR + 0xB4);
ECReg	ADC5_VRR				_at_ (GEE_BASE_ADDR + 0xB5);

#define    EC_PECI_BASE_ADDR    0x2A80
ECReg	PECI_HOST_STS			_at_ (EC_PECI_BASE_ADDR + 0x08);
ECReg	PECI_TARGET_ADDR		_at_ (EC_PECI_BASE_ADDR + 0x09);
ECReg	PECI_WR_LENGTH		_at_ (EC_PECI_BASE_ADDR + 0x0A);
ECReg	PECI_RD_LENGTH			_at_ (EC_PECI_BASE_ADDR + 0x0B);
ECReg	PECI_WR_DATA_1		_at_ (EC_PECI_BASE_ADDR + 0x0C);
ECReg	PECI_WR_DATA_2_TO_8	_at_ (EC_PECI_BASE_ADDR + 0x0D);
ECReg	PECI_HOST_CTRL			_at_ (EC_PECI_BASE_ADDR + 0x0E);
ECReg	PECI_FIFO				_at_ (EC_PECI_BASE_ADDR + 0x0F);

#define    EC_SMLINK_BASE_ADDR    0x2A98
ECReg	PCH_AMDTSI_HOST_STS		_at_ (EC_SMLINK_BASE_ADDR + 0x00);
ECReg	PCH_AMDTSI_TARGET_ADDR	_at_ (EC_SMLINK_BASE_ADDR + 0x01);
ECReg	PCH_AMDTSI_HOST_CMD		_at_ (EC_SMLINK_BASE_ADDR + 0x04);
ECReg	PCH_AMDTSI_HOST_CTRL		_at_ (EC_SMLINK_BASE_ADDR + 0x06);
ECReg	PCH_AMDTSI_HOST_FIFO		_at_ (EC_SMLINK_BASE_ADDR + 0x07);


/******************************************************************************
Define
Description: Define GPIO output registers
Footnote:
******************************************************************************/
#define    GPIO_BASE_ADDR    0x2C00
ECReg      GPIO_1x       _at_    (GPIO_BASE_ADDR + 0x00);    //
ECReg      GPIO_2x       _at_    (GPIO_BASE_ADDR + 0x01);    //
ECReg      GPIO_3x       _at_    (GPIO_BASE_ADDR + 0x02);    //
ECReg      GPIO_4x       _at_    (GPIO_BASE_ADDR + 0x03);    //
ECReg      GPIO_5x       _at_    (GPIO_BASE_ADDR + 0x04);    //
ECReg      GPIO_6x       _at_    (GPIO_BASE_ADDR + 0x05);    //
ECReg      GPIO_7x       _at_    (GPIO_BASE_ADDR + 0x06);    //
ECReg      GPIO_8x       _at_    (GPIO_BASE_ADDR + 0x07);    //



