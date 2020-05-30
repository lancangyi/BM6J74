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





void Initialize_GPIO_Pin_State(void)
{	
	Index_07H = 0x07;

	//Set GP7X output
	Index_CEH = 0xFF;
	GPIO_7x = 0x00;

	Index_07H= 0x00;

}



