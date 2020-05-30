/*-----------------------------------------------------------------------------
 * Filename: Oem_GPIO.h
 * Function: Oem_GPIO.c Include Definition
 *
 * Copyright (c) 2010, ITE Tech. Inc. All Rights Reserved.
 *---------------------------------------------------------------------------*/
#ifndef OEM_GPIO_H
#define OEM_GPIO_H


#define	G3S5_EUP_Enable	FALSE
//#define	CTRL0_USE_GP25	FALSE

/*-----------------------------------------------------------------------------
 * Parameter Definition
 *---------------------------------------------------------------------------*/
#define SEL			0x01
#define NSEL			0x00

#define IOMODE		0x01
#define ALTFUNC		0x00

#define OUTPUT		0x01
#define INPUT		0x00
#define NONIO		0xFF

#define PULLUP		0x01
#define NPULLUP		0x00

#define INV			0x01
#define NINV			0x00

#define	HIGH		0x01
#define	LOW		0x00

#define	NONE		0xFF

// GPIO selection registers from 25h to 29h which provides the pin selections of the GP1X to GP5X
// Note that the selection configurations are not required for GP6X, 7X and 8X because they only supports the simple I/O function.
//#define GP1X_SEL_REG		Index_25H
#define GP10_SEL_REG		Index_25H
#define GP11_SEL_REG		Index_25H
#define GP12_SEL_REG		Index_25H
#define GP13_SEL_REG		Index_25H
#define GP14_SEL_REG		Index_25H
#define GP15_SEL_REG		Index_25H
#define GP16_SEL_REG		Index_25H
#define GP17_SEL_REG		Index_25H

//#define GP2X_SEL_REG		Index_26H
#define GP20_SEL_REG		Index_26H
#define GP21_SEL_REG		Index_26H
#define GP22_SEL_REG		Index_26H
#define GP23_SEL_REG		Index_26H
#define GP24_SEL_REG		Index_26H
#define GP25_SEL_REG		Index_26H
#define GP26_SEL_REG		Index_26H
#define GP27_SEL_REG		Index_26H

//#define GP3X_SEL_REG		Index_27H
#define GP30_SEL_REG		Index_27H
#define GP31_SEL_REG		Index_27H
#define GP32_SEL_REG		Index_27H
#define GP33_SEL_REG		Index_27H
#define GP34_SEL_REG		Index_27H
#define GP35_SEL_REG		Index_27H
#define GP36_SEL_REG		Index_27H
#define GP37_SEL_REG		Index_27H

//#define GP4X_SEL_REG		Index_28H
#define GP40_SEL_REG		Index_28H
#define GP41_SEL_REG		Index_28H
#define GP42_SEL_REG		Index_28H
#define GP43_SEL_REG		Index_28H
#define GP44_SEL_REG		Index_28H
#define GP45_SEL_REG		Index_28H
#define GP46_SEL_REG		Index_28H
#define GP47_SEL_REG		Index_28H

//#define GP5X_SEL_REG		Index_29H
#define GP50_SEL_REG		Index_29H
#define GP51_SEL_REG		Index_29H
#define GP52_SEL_REG		Index_29H
#define GP53_SEL_REG		Index_29H
#define GP54_SEL_REG		Index_29H
#define GP55_SEL_REG		Index_29H
#define GP56_SEL_REG		Index_29H
#define GP57_SEL_REG		Index_29H


#define GP1X_FUNC_REG		Index_C0H
#define GP10_FUNC_REG		Index_C0H
#define GP11_FUNC_REG		Index_C0H
#define GP12_FUNC_REG		Index_C0H
#define GP13_FUNC_REG		Index_C0H
#define GP14_FUNC_REG		Index_C0H
#define GP15_FUNC_REG		Index_C0H
#define GP16_FUNC_REG		Index_C0H
#define GP17_FUNC_REG		Index_C0H

#define GP2X_FUNC_REG		Index_C1H
#define GP20_FUNC_REG		Index_C1H
#define GP21_FUNC_REG		Index_C1H
#define GP22_FUNC_REG		Index_C1H
#define GP23_FUNC_REG		Index_C1H
#define GP24_FUNC_REG		Index_C1H
#define GP25_FUNC_REG		Index_C1H
#define GP26_FUNC_REG		Index_C1H
#define GP27_FUNC_REG		Index_C1H

#define GP3X_FUNC_REG		Index_C2H
#define GP30_FUNC_REG		Index_C2H
#define GP31_FUNC_REG		Index_C2H
#define GP32_FUNC_REG		Index_C2H
#define GP33_FUNC_REG		Index_C2H
#define GP34_FUNC_REG		Index_C2H
#define GP35_FUNC_REG		Index_C2H
#define GP36_FUNC_REG		Index_C2H
#define GP37_FUNC_REG		Index_C2H

#define GP4X_FUNC_REG		Index_C3H
#define GP40_FUNC_REG		Index_C3H
#define GP41_FUNC_REG		Index_C3H
#define GP42_FUNC_REG		Index_C3H
#define GP43_FUNC_REG		Index_C3H
#define GP44_FUNC_REG		Index_C3H
#define GP45_FUNC_REG		Index_C3H
#define GP46_FUNC_REG		Index_C3H
#define GP47_FUNC_REG		Index_C3H

#define GP5X_FUNC_REG		Index_C4H
#define GP50_FUNC_REG		Index_C4H
#define GP51_FUNC_REG		Index_C4H
#define GP52_FUNC_REG		Index_C4H
#define GP53_FUNC_REG		Index_C4H
#define GP54_FUNC_REG		Index_C4H
#define GP55_FUNC_REG		Index_C4H
#define GP56_FUNC_REG		Index_C4H
#define GP57_FUNC_REG		Index_C4H

#define GP1X_IOMODE_REG	Index_C8H
#define GP10_IOMODE_REG	Index_C8H
#define GP11_IOMODE_REG	Index_C8H
#define GP12_IOMODE_REG	Index_C8H
#define GP13_IOMODE_REG	Index_C8H
#define GP14_IOMODE_REG	Index_C8H
#define GP15_IOMODE_REG	Index_C8H
#define GP16_IOMODE_REG	Index_C8H
#define GP17_IOMODE_REG	Index_C8H

#define GP2X_IOMODE_REG	Index_C9H
#define GP20_IOMODE_REG	Index_C9H
#define GP21_IOMODE_REG	Index_C9H
#define GP22_IOMODE_REG	Index_C9H
#define GP23_IOMODE_REG	Index_C9H
#define GP24_IOMODE_REG	Index_C9H
#define GP25_IOMODE_REG	Index_C9H
#define GP26_IOMODE_REG	Index_C9H
#define GP27_IOMODE_REG	Index_C9H

#define GP3X_IOMODE_REG	Index_CAH
#define GP30_IOMODE_REG	Index_CAH
#define GP31_IOMODE_REG	Index_CAH
#define GP32_IOMODE_REG	Index_CAH
#define GP33_IOMODE_REG	Index_CAH
#define GP34_IOMODE_REG	Index_CAH
#define GP35_IOMODE_REG	Index_CAH
#define GP36_IOMODE_REG	Index_CAH
#define GP37_IOMODE_REG	Index_CAH

#define GP4X_IOMODE_REG	Index_CBH
#define GP40_IOMODE_REG	Index_CBH
#define GP41_IOMODE_REG	Index_CBH
#define GP42_IOMODE_REG	Index_CBH
#define GP43_IOMODE_REG	Index_CBH
#define GP44_IOMODE_REG	Index_CBH
#define GP45_IOMODE_REG	Index_CBH
#define GP46_IOMODE_REG	Index_CBH
#define GP47_IOMODE_REG	Index_CBH

#define GP5X_IOMODE_REG	Index_CCH
#define GP50_IOMODE_REG	Index_CCH
#define GP51_IOMODE_REG	Index_CCH
#define GP52_IOMODE_REG	Index_CCH
#define GP53_IOMODE_REG	Index_CCH
#define GP54_IOMODE_REG	Index_CCH
#define GP55_IOMODE_REG	Index_CCH
#define GP56_IOMODE_REG	Index_CCH
#define GP57_IOMODE_REG	Index_CCH

#define GP6X_IOMODE_REG	Index_CDH
#define GP60_IOMODE_REG	Index_CDH
#define GP61_IOMODE_REG	Index_CDH
#define GP62_IOMODE_REG	Index_CDH
#define GP63_IOMODE_REG	Index_CDH
#define GP64_IOMODE_REG	Index_CDH
#define GP65_IOMODE_REG	Index_CDH
#define GP66_IOMODE_REG	Index_CDH
#define GP67_IOMODE_REG	Index_CDH

#define GP7X_IOMODE_REG	Index_CEH
#define GP70_IOMODE_REG	Index_CEH
#define GP71_IOMODE_REG	Index_CEH
#define GP72_IOMODE_REG	Index_CEH
#define GP73_IOMODE_REG	Index_CEH
#define GP74_IOMODE_REG	Index_CEH
#define GP75_IOMODE_REG	Index_CEH
#define GP76_IOMODE_REG	Index_CEH
#define GP77_IOMODE_REG	Index_CEH

#define GP8X_IOMODE_REG	Index_CFH
#define GP80_IOMODE_REG	Index_CFH
#define GP81_IOMODE_REG	Index_CFH
#define GP82_IOMODE_REG	Index_CFH
#define GP83_IOMODE_REG	Index_CFH
#define GP84_IOMODE_REG	Index_CFH
#define GP85_IOMODE_REG	Index_CFH
#define GP86_IOMODE_REG	Index_CFH
#define GP87_IOMODE_REG	Index_CFH
// Note that the GP8X only support GP87 to GP85 for I/O mode change
// The GP84 to GP80 are input only


#define GP1X_PULLUP_REG	Index_B8H
#define GP10_PULLUP_REG	Index_B8H
#define GP11_PULLUP_REG	Index_B8H
#define GP12_PULLUP_REG	Index_B8H
#define GP13_PULLUP_REG	Index_B8H
#define GP14_PULLUP_REG	Index_B8H
#define GP15_PULLUP_REG	Index_B8H
#define GP16_PULLUP_REG	Index_B8H
#define GP17_PULLUP_REG	Index_B8H

#define GP2X_PULLUP_REG	Index_B9H
#define GP20_PULLUP_REG	Index_B9H
#define GP21_PULLUP_REG	Index_B9H
#define GP22_PULLUP_REG	Index_B9H
#define GP23_PULLUP_REG	Index_B9H
#define GP24_PULLUP_REG	Index_B9H
#define GP25_PULLUP_REG	Index_B9H
#define GP26_PULLUP_REG	Index_B9H
#define GP27_PULLUP_REG	Index_B9H

#define GP3X_PULLUP_REG	Index_BAH
#define GP30_PULLUP_REG	Index_BAH
#define GP31_PULLUP_REG	Index_BAH
#define GP32_PULLUP_REG	Index_BAH
#define GP33_PULLUP_REG	Index_BAH
#define GP34_PULLUP_REG	Index_BAH
#define GP35_PULLUP_REG	Index_BAH
#define GP36_PULLUP_REG	Index_BAH
#define GP37_PULLUP_REG	Index_BAH

#define GP4X_PULLUP_REG	Index_BBH
#define GP40_PULLUP_REG	Index_BBH
#define GP41_PULLUP_REG	Index_BBH
#define GP42_PULLUP_REG	Index_BBH
#define GP43_PULLUP_REG	Index_BBH
#define GP44_PULLUP_REG	Index_BBH
#define GP45_PULLUP_REG	Index_BBH
#define GP46_PULLUP_REG	Index_BBH
#define GP47_PULLUP_REG	Index_BBH

#define GP5X_PULLUP_REG	Index_BCH
#define GP50_PULLUP_REG	Index_BCH
#define GP51_PULLUP_REG	Index_BCH
#define GP52_PULLUP_REG	Index_BCH
#define GP53_PULLUP_REG	Index_BCH
#define GP54_PULLUP_REG	Index_BCH
#define GP55_PULLUP_REG	Index_BCH
#define GP56_PULLUP_REG	Index_BCH
#define GP57_PULLUP_REG	Index_BCH

#define GP6X_PULLUP_REG	Index_BDH
#define GP60_PULLUP_REG	Index_BDH
#define GP61_PULLUP_REG	Index_BDH
#define GP62_PULLUP_REG	Index_BDH
#define GP63_PULLUP_REG	Index_BDH
#define GP64_PULLUP_REG	Index_BDH
#define GP65_PULLUP_REG	Index_BDH
#define GP66_PULLUP_REG	Index_BDH
#define GP67_PULLUP_REG	Index_BDH

#define GP1X_POLAR_REG		Index_B0H
#define GP10_POLAR_REG		Index_B0H
#define GP11_POLAR_REG		Index_B0H
#define GP12_POLAR_REG		Index_B0H
#define GP13_POLAR_REG		Index_B0H
#define GP14_POLAR_REG		Index_B0H
#define GP15_POLAR_REG		Index_B0H
#define GP16_POLAR_REG		Index_B0H
#define GP17_POLAR_REG		Index_B0H

#define GP2X_POLAR_REG		Index_B1H
#define GP20_POLAR_REG		Index_B1H
#define GP21_POLAR_REG		Index_B1H
#define GP22_POLAR_REG		Index_B1H
#define GP23_POLAR_REG		Index_B1H
#define GP24_POLAR_REG		Index_B1H
#define GP25_POLAR_REG		Index_B1H
#define GP26_POLAR_REG		Index_B1H
#define GP27_POLAR_REG		Index_B1H

#define GP3X_POLAR_REG		Index_B2H
#define GP30_POLAR_REG		Index_B2H
#define GP31_POLAR_REG		Index_B2H
#define GP32_POLAR_REG		Index_B2H
#define GP33_POLAR_REG		Index_B2H
#define GP34_POLAR_REG		Index_B2H
#define GP35_POLAR_REG		Index_B2H
#define GP36_POLAR_REG		Index_B2H
#define GP37_POLAR_REG		Index_B2H

#define GP4X_POLAR_REG		Index_B3H
#define GP40_POLAR_REG		Index_B3H
#define GP41_POLAR_REG		Index_B3H
#define GP42_POLAR_REG		Index_B3H
#define GP43_POLAR_REG		Index_B3H
#define GP44_POLAR_REG		Index_B3H
#define GP45_POLAR_REG		Index_B3H
#define GP46_POLAR_REG		Index_B3H
#define GP47_POLAR_REG		Index_B3H

#define GP5X_POLAR_REG		Index_B4H
#define GP50_POLAR_REG		Index_B4H
#define GP51_POLAR_REG		Index_B4H
#define GP52_POLAR_REG		Index_B4H
#define GP53_POLAR_REG		Index_B4H
#define GP54_POLAR_REG		Index_B4H
#define GP55_POLAR_REG		Index_B4H
#define GP56_POLAR_REG		Index_B4H
#define GP57_POLAR_REG		Index_B4H


// GP1X-8X pin stat control

#define GP1X_STAT_REG		GPIO_1x
#define GP10_STAT_REG		GPIO_1x
#define GP11_STAT_REG		GPIO_1x
#define GP12_STAT_REG		GPIO_1x
#define GP13_STAT_REG		GPIO_1x
#define GP14_STAT_REG		GPIO_1x
#define GP15_STAT_REG		GPIO_1x
#define GP16_STAT_REG		GPIO_1x
#define GP17_STAT_REG		GPIO_1x

#define GP2X_STAT_REG		GPIO_2x
#define GP20_STAT_REG		GPIO_2x
#define GP21_STAT_REG		GPIO_2x
#define GP22_STAT_REG		GPIO_2x
#define GP23_STAT_REG		GPIO_2x
#define GP24_STAT_REG		GPIO_2x
#define GP25_STAT_REG		GPIO_2x
#define GP26_STAT_REG		GPIO_2x
#define GP27_STAT_REG		GPIO_2x

#define GP3X_STAT_REG		GPIO_3x
#define GP30_STAT_REG		GPIO_3x
#define GP31_STAT_REG		GPIO_3x
#define GP32_STAT_REG		GPIO_3x
#define GP33_STAT_REG		GPIO_3x
#define GP34_STAT_REG		GPIO_3x
#define GP35_STAT_REG		GPIO_3x
#define GP36_STAT_REG		GPIO_3x
#define GP37_STAT_REG		GPIO_3x

#define GP4X_STAT_REG		GPIO_4x
#define GP40_STAT_REG		GPIO_4x
#define GP41_STAT_REG		GPIO_4x
#define GP42_STAT_REG		GPIO_4x
#define GP43_STAT_REG		GPIO_4x
#define GP44_STAT_REG		GPIO_4x
#define GP45_STAT_REG		GPIO_4x
#define GP46_STAT_REG		GPIO_4x
#define GP47_STAT_REG		GPIO_4x

#define GP5X_STAT_REG		GPIO_5x
#define GP50_STAT_REG		GPIO_5x
#define GP51_STAT_REG		GPIO_5x
#define GP52_STAT_REG		GPIO_5x
#define GP53_STAT_REG		GPIO_5x
#define GP54_STAT_REG		GPIO_5x
#define GP55_STAT_REG		GPIO_5x
#define GP56_STAT_REG		GPIO_5x
#define GP57_STAT_REG		GPIO_5x

#define GP6X_STAT_REG		GPIO_6x
#define GP60_STAT_REG		GPIO_6x
#define GP61_STAT_REG		GPIO_6x
#define GP62_STAT_REG		GPIO_6x
#define GP63_STAT_REG		GPIO_6x
#define GP64_STAT_REG		GPIO_6x
#define GP65_STAT_REG		GPIO_6x
#define GP66_STAT_REG		GPIO_6x
#define GP67_STAT_REG		GPIO_6x

#define GP7X_STAT_REG		GPIO_7x
#define GP70_STAT_REG		GPIO_7x
#define GP71_STAT_REG		GPIO_7x
#define GP72_STAT_REG		GPIO_7x
#define GP73_STAT_REG		GPIO_7x
#define GP74_STAT_REG		GPIO_7x
#define GP75_STAT_REG		GPIO_7x
#define GP76_STAT_REG		GPIO_7x
#define GP77_STAT_REG		GPIO_7x

#define GP8X_STAT_REG		GPIO_8x
#define GP80_STAT_REG		GPIO_8x
#define GP81_STAT_REG		GPIO_8x
#define GP82_STAT_REG		GPIO_8x
#define GP83_STAT_REG		GPIO_8x
#define GP84_STAT_REG		GPIO_8x
#define GP85_STAT_REG		GPIO_8x
#define GP86_STAT_REG		GPIO_8x
#define GP87_STAT_REG		GPIO_8x




extern void Initialize_GPIO_Pin_State(void) ;
//extern void InitGPIO(BYTE GPIOSet);
//extern void InitGPIO_1x(void);
//extern void InitGPIO_2x(void);

////////////////////////////////////////////////
// 		GPIO 1X Status Control Macros
////////////////////////////////////////////////

#define GP10_HI()	SET_BIT(GPIO_1x, 0)
#define GP10_LO()	CLR_BIT(GPIO_1x, 0)
#define GP10_TG()	INVERSE_REG(GPIO_1x, 0)

#define GP11_HI()	SET_BIT(GPIO_1x, 1)
#define GP11_LO()	CLR_BIT(GPIO_1x, 1)
#define GP11_TG()	INVERSE_REG(GPIO_1x, 1)

#define GP12_HI()	SET_BIT(GPIO_1x, 2)
#define GP12_LO()	CLR_BIT(GPIO_1x, 2)
#define GP12_TG()	INVERSE_REG(GPIO_1x, 2)

#define GP13_HI()	SET_BIT(GPIO_1x, 3)
#define GP13_LO()	CLR_BIT(GPIO_1x, 3)
#define GP13_TG()	INVERSE_REG(GPIO_1x, 3)

#define GP14_HI()	SET_BIT(GPIO_1x, 4)
#define GP14_LO()	CLR_BIT(GPIO_1x, 4)
#define GP14_TG()	INVERSE_REG(GPIO_1x, 4)

#define GP15_HI()	SET_BIT(GPIO_1x, 5)
#define GP15_LO()	CLR_BIT(GPIO_1x, 5)
#define GP15_TG()	INVERSE_REG(GPIO_1x, 5)

#define GP16_HI()	SET_BIT(GPIO_1x, 6)
#define GP16_LO()	CLR_BIT(GPIO_1x, 6)
#define GP16_TG()	INVERSE_REG(GPIO_1x, 6)

#define GP17_HI()	SET_BIT(GPIO_1x, 7)
#define GP17_LO()	CLR_BIT(GPIO_1x, 7)
#define GP17_TG()	INVERSE_REG(GPIO_1x, 7)


///////////////////////////////////////////////////////////////
// 	GPIO 2X Status Control Macros (GP22, GP23 is not available)
///////////////////////////////////////////////////////////////

#define GP20_HI()	SET_BIT(GPIO_2x, 0)
#define GP20_LO()	CLR_BIT(GPIO_2x, 0)
#define GP20_TG()	INVERSE_REG(GPIO_2x, 0)

#define GP21_HI()	SET_BIT(GPIO_2x, 1)
#define GP21_LO()	CLR_BIT(GPIO_2x, 1)
#define GP21_TG()	INVERSE_REG(GPIO_2x, 1)

#define GP24_HI()	SET_BIT(GPIO_2x, 4)
#define GP24_LO()	CLR_BIT(GPIO_2x, 4)
#define GP24_TG()	INVERSE_REG(GPIO_2x, 4)

#define GP25_HI()	SET_BIT(GPIO_2x, 5)
#define GP25_LO()	CLR_BIT(GPIO_2x, 5)
#define GP25_TG()	INVERSE_REG(GPIO_2x, 5)

#define GP26_HI()	SET_BIT(GPIO_2x, 6)
#define GP26_LO()	CLR_BIT(GPIO_2x, 6)
#define GP26_TG()	INVERSE_REG(GPIO_2x, 6)

#define GP27_HI()	SET_BIT(GPIO_2x, 7)
#define GP27_LO()	CLR_BIT(GPIO_2x, 7)
#define GP27_TG()	INVERSE_REG(GPIO_2x, 7)

////////////////////////////////////////////////
// 		GPIO 3X Status Control Macros
////////////////////////////////////////////////

#define GP30_HI()	SET_BIT(GPIO_3x, 0)
#define GP30_LO()	CLR_BIT(GPIO_3x, 0)
#define GP30_TG()	INVERSE_REG(GPIO_3x, 0)

#define GP31_HI()	SET_BIT(GPIO_3x, 1)
#define GP31_LO()	CLR_BIT(GPIO_3x, 1)
#define GP31_TG()	INVERSE_REG(GPIO_3x, 1)

#define GP32_HI()	SET_BIT(GPIO_3x, 2)
#define GP32_LO()	CLR_BIT(GPIO_3x, 2)
#define GP32_TG()	INVERSE_REG(GPIO_3x, 2)

#define GP33_HI()	SET_BIT(GPIO_3x, 3)
#define GP33_LO()	CLR_BIT(GPIO_3x, 3)
#define GP33_TG()	INVERSE_REG(GPIO_3x, 3)

#define GP34_HI()	SET_BIT(GPIO_3x, 4)
#define GP34_LO()	CLR_BIT(GPIO_3x, 4)
#define GP34_TG()	INVERSE_REG(GPIO_3x, 4)

#define GP35_HI()	SET_BIT(GPIO_3x, 5)
#define GP35_LO()	CLR_BIT(GPIO_3x, 5)
#define GP35_TG()	INVERSE_REG(GPIO_3x, 5)

#define GP36_HI()	SET_BIT(GPIO_3x, 6)
#define GP36_LO()	CLR_BIT(GPIO_3x, 6)
#define GP36_TG()	INVERSE_REG(GPIO_3x, 6)

#define GP37_HI()	SET_BIT(GPIO_3x, 7)
#define GP37_LO()	CLR_BIT(GPIO_3x, 7)
#define GP37_TG()	INVERSE_REG(GPIO_3x, 7)


////////////////////////////////////////////////
// 		GPIO 4X Status Control Macros
////////////////////////////////////////////////

#define GP40_HI()	SET_BIT(GPIO_4x, 0)
#define GP40_LO()	CLR_BIT(GPIO_4x, 0)
#define GP40_TG()	INVERSE_REG(GPIO_4x, 0)

#define GP41_HI()	SET_BIT(GPIO_4x, 1)
#define GP41_LO()	CLR_BIT(GPIO_4x, 1)
#define GP41_TG()	INVERSE_REG(GPIO_4x, 1)

#define GP42_HI()	SET_BIT(GPIO_4x, 2)
#define GP42_LO()	CLR_BIT(GPIO_4x, 2)
#define GP42_TG()	INVERSE_REG(GPIO_4x, 2)

#define GP43_HI()	SET_BIT(GPIO_4x, 3)
#define GP43_LO()	CLR_BIT(GPIO_4x, 3)
#define GP43_TG()	INVERSE_REG(GPIO_4x, 3)

#define GP44_HI()	SET_BIT(GPIO_4x, 4)
#define GP44_LO()	CLR_BIT(GPIO_4x, 4)
#define GP44_TG()	INVERSE_REG(GPIO_4x, 4)

#define GP45_HI()	SET_BIT(GPIO_4x, 5)
#define GP45_LO()	CLR_BIT(GPIO_4x, 5)
#define GP45_TG()	INVERSE_REG(GPIO_4x, 5)

#define GP46_HI()	SET_BIT(GPIO_4x, 6)
#define GP46_LO()	CLR_BIT(GPIO_4x, 6)
#define GP46_TG()	INVERSE_REG(GPIO_4x, 6)

#define GP47_HI()	SET_BIT(GPIO_4x, 7)
#define GP47_LO()	CLR_BIT(GPIO_4x, 7)
#define GP47_TG()	INVERSE_REG(GPIO_4x, 7)


///////////////////////////////////////////////////////////
// 	GPIO 5X Status Control Macros (GP50 is not available)
///////////////////////////////////////////////////////////

#define GP51_HI()	SET_BIT(GPIO_5x, 1)
#define GP51_LO()	CLR_BIT(GPIO_5x, 1)
#define GP51_TG()	INVERSE_REG(GPIO_5x, 1)

#define GP52_HI()	SET_BIT(GPIO_5x, 2)
#define GP52_LO()	CLR_BIT(GPIO_5x, 2)
#define GP52_TG()	INVERSE_REG(GPIO_5x, 2)

#define GP53_HI()	SET_BIT(GPIO_5x, 3)
#define GP53_LO()	CLR_BIT(GPIO_5x, 3)
#define GP53_TG()	INVERSE_REG(GPIO_5x, 3)

#define GP54_HI()	SET_BIT(GPIO_5x, 4)
#define GP54_LO()	CLR_BIT(GPIO_5x, 4)
#define GP54_TG()	INVERSE_REG(GPIO_5x, 4)

#define GP55_HI()	SET_BIT(GPIO_5x, 5)
#define GP55_LO()	CLR_BIT(GPIO_5x, 5)
#define GP55_TG()	INVERSE_REG(GPIO_5x, 5)

#define GP56_HI()	SET_BIT(GPIO_5x, 6)
#define GP56_LO()	CLR_BIT(GPIO_5x, 6)
#define GP56_TG()	INVERSE_REG(GPIO_5x, 6)

#define GP57_HI()	SET_BIT(GPIO_5x, 7)
#define GP57_LO()	CLR_BIT(GPIO_5x, 7)
#define GP57_TG()	INVERSE_REG(GPIO_5x, 7)


///////////////////////////////////////////////////////////
// 	GPIO 7X Status Control Macros (GPIO mode only for 7X)
///////////////////////////////////////////////////////////

#define GP70_HI()	SET_BIT(GPIO_7x, 0)
#define GP70_LO()	CLR_BIT(GPIO_7x, 0)
#define GP70_TG()	INVERSE_REG(GPIO_7x, 0)

#define GP71_HI()	SET_BIT(GPIO_7x, 1)
#define GP71_LO()	CLR_BIT(GPIO_7x, 1)
#define GP71_TG()	INVERSE_REG(GPIO_7x, 1)

#define GP72_HI()	SET_BIT(GPIO_7x, 2)
#define GP72_LO()	CLR_BIT(GPIO_7x, 2)
#define GP72_TG()	INVERSE_REG(GPIO_7x, 2)

#define GP73_HI()	SET_BIT(GPIO_7x, 3)
#define GP73_LO()	CLR_BIT(GPIO_7x, 3)
#define GP73_TG()	INVERSE_REG(GPIO_7x, 3)

#define GP74_HI()	SET_BIT(GPIO_7x, 4)
#define GP74_LO()	CLR_BIT(GPIO_7x, 4)
#define GP74_TG()	INVERSE_REG(GPIO_7x, 4)

#define GP75_HI()	SET_BIT(GPIO_7x, 5)
#define GP75_LO()	CLR_BIT(GPIO_7x, 5)
#define GP75_TG()	INVERSE_REG(GPIO_7x, 5)

#define GP76_HI()	SET_BIT(GPIO_7x, 6)
#define GP76_LO()	CLR_BIT(GPIO_7x, 6)
#define GP76_TG()	INVERSE_REG(GPIO_7x, 6)

#define GP77_HI()	SET_BIT(GPIO_7x, 7)
#define GP77_LO()	CLR_BIT(GPIO_7x, 7)
#define GP77_TG()	INVERSE_REG(GPIO_7x, 7)


///////////////////////////////////////////////////////////////////////
// 	GPIO 8X Status Control Macros (only GP87, GP86, GP85 can be outputs)
///////////////////////////////////////////////////////////////////////

#define GP85_HI()	SET_BIT(GPIO_8x, 5)
#define GP85_LO()	CLR_BIT(GPIO_8x, 5)
#define GP85_TG()	INVERSE_REG(GPIO_8x, 5)

#define GP86_HI()	SET_BIT(GPIO_8x, 6)
#define GP86_LO()	CLR_BIT(GPIO_8x, 6)
#define GP86_TG()	INVERSE_REG(GPIO_8x, 6)

#define GP87_HI()	SET_BIT(GPIO_8x, 7)
#define GP87_LO()	CLR_BIT(GPIO_8x, 7)
#define GP87_TG()	INVERSE_REG(GPIO_8x, 7)

///////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------
// INPUT Function
//-----------------------------------------------------------------
///////////////////////////////////////////////////////////////////
//#define STATE_PowerSW()     IS_BIT_SET(GPIOE,4)
#define PowerSW_Active      0           //1:HighActive 0:LowActive

//#define STATE_PCIRST()      IS_BIT_SET(GPIOD,2) //PCIRST

///////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------
// Host Bus Control
//-----------------------------------------------------------------
///////////////////////////////////////////////////////////////////
//Set GP52=> SCI
#define Alert_SCI_ON()            CLR_BIT(GPIO_5x, 2)
#define Alert_SCI_OFF()           SET_BIT(GPIO_5x, 2)

#define SCI_ON()            CLR_BIT(GPIO_8x, 5)
#define SCI_OFF()           SET_BIT(GPIO_8x, 5)
#define STATE_SCI()         IS_BIT_SET(GPIO_5x, 2)


#define SMI_ON()            CLR_BIT(GPIO_7x,1)
#define SMI_OFF()           SET_BIT(GPIO_7x,1)
#define STATE_SMI()         IS_BIT_SET(GPIO_7x,1)

//-----------------------------------------------------------------------------
// define I/O control
//-----------------------------------------------------------------------------
//#define Fan_volt		PWM_DCR0



/****************************************************************************/
/*					example	Power Pins										*/
/****************************************************************************/

#define	STATE_PANSHW()		IS_BIT_SET(GPIO_4x, 3)



#define	EN_1P2_HI()				SET_BIT(GPIO_7x,1)
#define	EN_1P2_LO()				CLR_BIT(GPIO_7x,1)

#define	PWRBTN_HI()			SET_BIT(GPIO_4x,4)
#define	PWRBTN_LO()			CLR_BIT(GPIO_4x,4)

#define	STATE_PM_SLP_S3()		IS_BIT_SET(GPIO_4x, 5)
#define	STATE_PM_SLP_S4()		IS_BIT_SET(GPIO_5x, 3)


extern void PWR_LED_ON(void);
extern void PWR_LED_OFF(void);
//-----------------------------------------------------------------------------




#endif

