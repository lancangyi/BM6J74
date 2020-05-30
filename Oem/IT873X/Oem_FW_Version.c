/*-----------------------------------------------------------------------------
 * TITLE: CORE_ITESTRING.C
 *
 * Copyright (c) ITE INC. All Rights Reserved.
 *
 *---------------------------------------------------------------------------*/
 
#include "Core_Inc.h"
#include "Oem_Inc.h"

const unsigned char code OEM_FW_Version[] =         //Version in ROM
{
	OEM_Version_MSB, OEM_Version_LSB,	0x00,0x00,	//For OEM version
	0xFF,0xFF,0xFF,0xFF							//For Checksum *******Do not modify*********** // 
};