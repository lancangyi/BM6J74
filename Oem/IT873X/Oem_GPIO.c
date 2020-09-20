/*-----------------------------------------------------------------------------
 * TITLE: OEM_GPIO.C - Main Program for KBC firmware.
 *
 * Main processing loop (interrupt driven) for the keyboard controller/scanner.
 *
 * Copyright (c) 1983-2007, Insyde Software Corporation. All Rights Reserved.
 *
 * You may not reproduce, distribute, publish, display, perform, modify, adapt,
 * transmit, broadcast, present, recite, release, license or otherwise exploit
 * any part of this publication in any form, by any means, without the prior
 * written permission of Insyde Software Corporation.
 *---------------------------------------------------------------------------*/

#include "Core_Inc.h"
#include "Oem_Inc.h"


/*
	Here describes the basic configuration about the IT8731 GPIO
*/


void PWR_LED_ON(void)
{
	GP33_HI();

}
void PWR_LED_OFF(void)
{
    GP33_LO();

}


void Initialize_GPIO_Pin_State(void)
{	
	Index_07H = 0x07;
	Index_30H = 0x01;
	//Set GP7X output
	Index_CEH = 0xFF;
	GPIO_7x = 0x00;

	Index_07H= 0x00;

    Index_07H = 0x07;	//J74_003++
	SET_BIT(GP33_SEL_REG,3);		//Set GP33
	SET_BIT(GP3X_IOMODE_REG,3);		//Set GP33 output
	SET_BIT(GP3X_FUNC_REG,3);		//Set GP33 simple IO function
    Index_07H = 0x00;	//J74_003++
	
	//J74_001++>>
	Index_07H = 0x07;
	SET_BIT(GP36_SEL_REG,6);		//Set GP36
	SET_BIT(GP3X_FUNC_REG,6);		//Set GP36 simple IO function
	SET_BIT(GP3X_IOMODE_REG,6); 	//Set GP36 output
	//J74_001A--	GP36_HI();
	GP36_LO();	//J74_001A++
		
	SET_BIT(GP14_SEL_REG,4);		//Set GP14
	SET_BIT(GP1X_IOMODE_REG,4); 	//Set GP14 output
	SET_BIT(GP1X_FUNC_REG,4);		//Set GP14 simple IO function
	//J74_001A-- 	GP14_HI();
	GP14_LO();	//J74_001A++
	
		
	SET_BIT(GP37_SEL_REG,7);		//Set GP37
	SET_BIT(GP3X_IOMODE_REG,7); 	//Set GP37 output
	SET_BIT(GP3X_FUNC_REG,7);		//Set GP37 simple IO function
	//J74_001A--	GP37_HI();
	GP37_LO();	//J74_001A++
		
	SET_BIT(GP24_SEL_REG,4);		//Set GP24
	SET_BIT(GP2X_IOMODE_REG,4); 	//Set GP24 output
	SET_BIT(GP2X_FUNC_REG,4);		//Set GP24 simple IO function
	//J74_001A--	GP24_HI();
	GP24_LO();	//J74_001A++
	Index_07H = 0x00;

	//Index_07H = 0x06;
	//Index_30H = 0x01;
	//Index_70H = 0x0C;
	//Index_07H = 0x00;		
	//J74_001++<< 
}



