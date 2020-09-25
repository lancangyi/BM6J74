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
 	//J74_001++>>
 	//J74_001A-->>
    /*
    Index_07H = 0x07;
	SET_BIT(GP36_SEL_REG,6);		//Set GP36
	SET_BIT(GP3X_FUNC_REG,6);		//Set GP36 simple IO function
	SET_BIT(GP3X_IOMODE_REG,6); 	//Set GP36 output
	SET_BIT(GP45_PULLUP_REG,5);		// Set GP44 PULL-UP (GPIO Pin Set 4 Pin Internal Pull-up Enable Registers)
		
	SET_BIT(GP14_SEL_REG,4);		//Set GP14
	SET_BIT(GP1X_IOMODE_REG,4); 	//Set GP14 output
	SET_BIT(GP1X_FUNC_REG,4);		//Set GP14 simple IO function	
		
	SET_BIT(GP37_SEL_REG,7);		//Set GP37
	SET_BIT(GP3X_IOMODE_REG,7); 	//Set GP37 output
	SET_BIT(GP3X_FUNC_REG,7);		//Set GP37 simple IO function
		
	SET_BIT(GP24_SEL_REG,4);		//Set GP24
	SET_BIT(GP2X_IOMODE_REG,4); 	//Set GP24 output
	SET_BIT(GP2X_FUNC_REG,4);		//Set GP24 simple IO function
	Index_07H = 0x00;
   /* if(STATE_PM_SLP_S3()&&(DDRSIGN==0))
    {
	    GP36_HI();	
		GP14_HI();
	    GP37_HI();
		GP24_HI(); 
    }
	else if((!STATE_PM_SLP_S3())&&(STATE_PM_SLP_S4()))
	{
 	    DDRSIGN=1;
		GP36_LO();	
		GP14_LO();
		GP37_LO();
	    GP24_LO();
	}
	else if((!STATE_PM_SLP_S3())&&(!STATE_PM_SLP_S4()))
	{
	    DDRSIGN=0;
		GP36_LO();	
		GP14_LO();
	    GP37_LO();
	    GP24_LO();
	}
	*/
   //J74_001A--<<
   //J74_001A++>>
   //J74_001B-->>
   /*
	if(!STATE_PM_SLP_S4())
    {
	    GP36_HI();	
		GP14_HI();
	    GP37_HI();
		GP24_HI(); 
    }
	else if(!STATE_PM_SLP_S3())
	{
		GP36_LO();	
		GP14_LO();
		GP37_LO();
	    GP24_LO();
	}
	
	if(IS_PM_SLP_S4())
    {
		if(IS_PANSHW())
		{
		  GP36_HI();	
		  GP14_HI();
	      GP37_HI();
		  GP24_HI();
		  S3_FLAG = 1;
		}
		else if(S3_FLAG == 0)
		{
		  GP36_LO();	
		  GP14_LO();
		  GP37_LO();
	      GP24_LO();
		}
    }
	else if(IS_PM_SLP_S3())
	{
		GP36_LO();	
		GP14_LO();
		GP37_LO();
	    GP24_LO();
		S3_FLAG = 2;
	}
	else if(S3_FLAG == 1)
	{
		GP36_HI();	
		GP14_HI();
	    GP37_HI();
		GP24_HI();
		S3_FLAG = 0;
	}
   //J74_001A++<<
   */
   //J74_001B--<<
   //J74_001++<<
    //J74_001B++>>
	if(SystemIsS0 && !S3_FLAG) 
	{
		GP36_HI();	
		GP14_HI();
	    GP37_HI();
		GP24_HI();
	}
	else if(SystemNotS0)
	{
		GP36_LO();	
		GP14_LO();
		GP37_LO();
	    GP24_LO();
	}	
	//J74_001B++<<

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
       //EC_start();
    }
	else
	{
		EC_stop();
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
	ProcessLED();
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
