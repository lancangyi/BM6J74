

#include "Core_Inc.h"
#include "Oem_Inc.h"




#define DebugRamAddr 0x600
#define DebugRamRange 0xFF

void RamDebug(unsigned char dbgcode)
{
  	PORT_BYTE_PNTR ClearIndex;
 	PORT_BYTE_PNTR byte_register_pntr;
	BYTE index;
  	BYTE i;
	
    byte_register_pntr = DebugRamAddr+DebugRamRange;          
    index = *byte_register_pntr;
    *byte_register_pntr +=1;
	
    if ( *byte_register_pntr == DebugRamRange )
   	{
   		*byte_register_pntr = 0;
       	ClearIndex= DebugRamAddr;

		for (i=0x00;i<DebugRamRange;i++)
     	{
         	*ClearIndex=0x00;
           	ClearIndex++;
     	}
  	}

	byte_register_pntr = DebugRamAddr + index;
    *byte_register_pntr = dbgcode;
}


void RamDebugWord(unsigned int dbgword)
{
	BYTE	dgb_H;
	BYTE	dgb_L;

	dgb_H = (BYTE) (dbgword >> 8) ;
	dgb_L = (BYTE) (dbgword & 0x00FF ) ;

	RamDebug(dgb_H);
	RamDebug(dgb_L);
}

void RamDebugDword(unsigned long dbgdword)
{
	BYTE	dgb_4;
	BYTE	dgb_3;
	BYTE	dgb_2;
	BYTE	dgb_1;

	dgb_4 = (BYTE) (dbgdword >> 24) ;
	dgb_3 = (BYTE) (dbgdword >> 16) ;
	dgb_2 = (BYTE) (dbgdword >> 8) ;
	dgb_1 = (BYTE) (dbgdword & 0x00FF ) ;

	RamDebug(dgb_4);
	RamDebug(dgb_3);
	RamDebug(dgb_2);
	RamDebug(dgb_1);
}


//-----------------------------------------------------------------------------
// Oem 1ms Events/Hook Here
//-----------------------------------------------------------------------------
void Oem_Hook_1MS_Event(void)
{
	#if SUPPORT_Hook_1ms_Timer
		#if SMBusServiceCenterFunc
		SMBusCenter();
		#endif
	#endif


}



//-----------------------------------------------------------------------------
// Oem 5ms Events/Hook Here
//-----------------------------------------------------------------------------
void Oem_Hook_5MS_Event(void)
{

	Check_Power_State();
	Service_EventCenter();

}

//-----------------------------------------------------------------------------
// Oem 10ms Events/Hook Here
//-----------------------------------------------------------------------------
void Oem_Hook_10MS_Event(void)
{

}

//-----------------------------------------------------------------------------
// Oem 50ms Events/Hook Here
//-----------------------------------------------------------------------------
void Oem_Hook_50MS_EventA(void)
{


}

void Oem_Hook_50MS_EventB(void)
{	
	
}

void Oem_Hook_50MS_EventC(void)
{

}

//-----------------------------------------------------------------------------
// Oem 100ms Events/Hook Here
//-----------------------------------------------------------------------------
void Oem_Hook_100MS_EventA(void)
{

	if(SystemIsS0)
	{
		if(LED_S0_Status == 0)
		{
			PWR_LED_ON();
			LED_S0_Status = 1;
		}
	}
	else if(SystemIsS3)
	{
		LED_blink_CNT++;
		if(LED_blink_CNT == 1)
			PWR_LED_ON();
		else if (LED_blink_CNT == 11)
			PWR_LED_OFF();	
		else if (LED_blink_CNT > 20)
			LED_blink_CNT=0;
		LED_S0_Status = 0;	
	}
}

void Oem_Hook_100MS_EventB(void)
{

}

void Oem_Hook_100MS_EventC(void)
{

}

//-----------------------------------------------------------------------------
// Oem 125ms Events/Hook Here
//-----------------------------------------------------------------------------
void Oem_Hook_125MS_Event(void)
{

}

//-----------------------------------------------------------------------------
// Oem 250ms Events/Hook Here
//-----------------------------------------------------------------------------
void Oem_Hook_250MS_Event(void)
{


}

//-----------------------------------------------------------------------------
// Oem 500ms Events/Hook Here
//-----------------------------------------------------------------------------
void Oem_Hook_500MS_EventA(void)
{

}

void Oem_Hook_500MS_EventB(void)
{

}

void Oem_Hook_500MS_EventC(void)
{


}

//-----------------------------------------------------------------------------
// Oem 1s Events/Hook Here
//-----------------------------------------------------------------------------
void Oem_Hook_1S_EventA(void)
{
	
}

void Oem_Hook_1S_EventB(void)
{

}

void Oem_Hook_1S_EventC(void)
{

}

//-----------------------------------------------------------------------------
// Oem 1min Events/Hook Here
//-----------------------------------------------------------------------------
void Oem_Hook_1Min_Event(void)
{

}
//-----------------------------------------------------------------------------
// End of Handle Timer Events
//-----------------------------------------------------------------------------

void Oem_Main_Test_Func(void)
{
	// do nothing
}


void CheckResetSource(void)
{

}


void Delay15US(XWORD dly_count)
{
    
    //delay
    while(dly_count > 0)
    {
    	WNCKR = 0;	
    	dly_count--;
    }    
    
}
