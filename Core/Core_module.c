/*-----------------------------------------------------------------------------
 * Filename: CORE_MODULE.C
 * Function: System Management SMBus Protocol drivers.
 *
 * Copyright (c) 2006-2009, ITE Tech. Inc. All Rights Reserved.
 *---------------------------------------------------------------------------*/
#include "CORE_INC.H"
#include "OEM_INC.H"







//-----------------------------------------------------------------------------
/*****************************************************************************/
/* GPIO MODULE ***************************************************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// Input Signal Debounce function
// Input Parameter: PIN_STATUS,_ACTIVE,Counter_ID,ReloadCnt
// Return:  ioStatus
//      0x00: No Acitve
//      0x01: Active
//      0x02: Active and Debounced
//      0x03: Repeat Active
// ----------------------------------------------------------------------------
struct inDebounce
{   XBYTE   *REG;
    XBYTE   *Counter;
    BYTE    FLAG_0;
    BYTE    FLAG_1;
};

//-----------------------------------------------------------------------------

const struct inDebounce code inDebounce_TBL[] =
    {
        {&DEBOUNCE_FLAG1    ,&DEBOUNCE_CONT0    ,BIT0   ,BIT1   },
        {&DEBOUNCE_FLAG1    ,&DEBOUNCE_CONT1    ,BIT2   ,BIT3   },
        {&DEBOUNCE_FLAG1    ,&DEBOUNCE_CONT2    ,BIT4   ,BIT5   },
        {&DEBOUNCE_FLAG1    ,&DEBOUNCE_CONT3    ,BIT6   ,BIT7   },
        {&DEBOUNCE_FLAG2    ,&DEBOUNCE_CONT4    ,BIT0   ,BIT1   },
        {&DEBOUNCE_FLAG2    ,&DEBOUNCE_CONT5    ,BIT2   ,BIT3   },
        {&DEBOUNCE_FLAG2    ,&DEBOUNCE_CONT6    ,BIT4   ,BIT5   },
        {&DEBOUNCE_FLAG2    ,&DEBOUNCE_CONT7    ,BIT6   ,BIT7   }
    };

//-----------------------------------------------------------------------------
// Return:  ioStatus
//      0x00: No Acitve
//      0x01: Active
//      0x02: Active and Debounced
//      0x03: Repeat Active
//-----------------------------------------------------------------------------

BYTE InputDebounce(FLAG PIN_STATUS,FLAG _ACTIVE,BYTE Counter_ID,BYTE ReloadCnt)
{
    BYTE    ioStatus = 0x00;
    XBYTE   *in_FlagREG;
    XBYTE   *in_Counter;
    BYTE    in_FLAG_0,in_FLAG_1;
    Counter_ID &= 0x07;
    in_FlagREG = inDebounce_TBL[Counter_ID].REG;
    in_Counter = inDebounce_TBL[Counter_ID].Counter;
    in_FLAG_0  = inDebounce_TBL[Counter_ID].FLAG_0;
    in_FLAG_1  = inDebounce_TBL[Counter_ID].FLAG_1;
    //Check Pin Status
    if( PIN_STATUS == _ACTIVE )
    {   if ( ( (*in_FlagREG) & (in_FLAG_1) ) == 0 )
        {
            if ( ( (*in_FlagREG) & (in_FLAG_0) ) == 0 )
            {   (*in_Counter) = ReloadCnt;
                (*in_FlagREG) |= in_FLAG_0;
                ioStatus = 0x01;
            }
            else
            {   ioStatus = 0x01;
                (*in_Counter)--;

                if( (*in_Counter) == 0 )
                {
                    (*in_FlagREG) |= in_FLAG_1;
                    (*in_FlagREG) &= (~in_FLAG_0);
                    ioStatus = 0x02;
                }
            }
        }
        else
        {
            (*in_FlagREG) |= in_FLAG_0;
            ioStatus = 0x03;
        }

    }
    else
    {
        (*in_Counter) = ReloadCnt;
        (*in_FlagREG) &= ( ~(in_FLAG_0+in_FLAG_1) );
        ioStatus = 0x00;
    }
    return  ioStatus;
}


void Oem_Check1XBtn0(void)
{
	BYTE BTemp;
	BYTE DTemp;

    BTemp = InputDebounce(IS_BIT_SET(GPIO_1x, 0), LowActive, 0x01, T_PANEL_SIDE_ONDB) ;

    if ( BTemp == 0x02 )        // Active and Debounced
    {
		
    }
    else if ( BTemp == 0x03 )        // Active and Debounced
    {
        BtnOverTimer1++;
        if  ( ( BtnOverTimer1 > T_PANEL_BTN_DELAY) && (BtnOverTimer1%30 == 0x00) )
        {
		
        }
   }  
    else
   {
   	BtnOverTimer1= 0 ;
   }

}


void Oem_Check1XBtn1(void)
{
    BYTE BTemp;
    BYTE DTemp;


    BTemp = InputDebounce(IS_BIT_SET(GPIO_1x, 1), LowActive, 0x02, T_PANEL_SIDE_ONDB) ;


    if ( BTemp == 0x02 )        // Active and Debounced
    {


    }
    else if ( BTemp == 0x03 )        // Active and Debounced
    {
        BtnOverTimer2++;
        if  ( ( BtnOverTimer2 > T_PANEL_BTN_DELAY) && (BtnOverTimer2%30 == 0x00) )
        {

        }
   }
   else
   {
   	BtnOverTimer2= 0 ;
   }

	
}






//Init EC side PWM output
//Freq = (CPRS+1) x 256 x Tclk
void Init_EC_PWM (void)
{
	CLR_BIT(PWMCTL, PCCE);		//Disable PWMOUT
	
	switch(PWM_Freq)
	{

		case PWM_Freq_64Hz:
			CLR_BIT(PWMCTL, PCFS);		//Clock: 32.768kHz
			CPRS = 1;
			// 		32.768k / ((1+1)*256) = 64 Hz
		break;


		case PWM_Freq_128Hz:
			CLR_BIT(PWMCTL, PCFS);		//Clock: 32.768kHz
			CPRS = 0;
			// 		32.768k / ((0+1)*256) = 128 Hz
		break;


		case PWM_Freq_200Hz:
			SET_BIT(PWMCTL, PCFS);		//Clock: 9.2MHz
			CPRS = 179;
			// 		9.2MHz / ((179+1)*256) = 199.6527Hz
		break;


		case PWM_Freq_250Hz:
			SET_BIT(PWMCTL, PCFS);		//Clock: 9.2MHz
			CPRS = 143;
			// 		9.2MHz / ((143+1)*256) = 249.5659Hz
		break;


		case PWM_Freq_500Hz:
			SET_BIT(PWMCTL, PCFS);		//Clock: 9.2MHz
			CPRS = 71;
			// 		9.2MHz / ((71+1)*256) = 499.1319444Hz
		break;


		case PWM_Freq_1kHz:
			SET_BIT(PWMCTL, PCFS);		//Clock: 9.2MHz
			CPRS = 35;
			// 		9.2MHz / ((35+1)*256) = 998.26388Hz		35937.5
		break;


		case PWM_Freq_2kHz:
			SET_BIT(PWMCTL, PCFS);		//Clock: 9.2MHz
			CPRS = 17;
			// 		9.2MHz / ((17+1)*256) = 1996.527777Hz		35937.5
		break;


		case PWM_Freq_35_9kHz:
			SET_BIT(PWMCTL, PCFS);		//Clock: 9.2MHz
			CPRS = 0;
			// 		9.2MHz / ((0+1)*256) = 35937.5Hz		
		break;


		case PWM_Freq_Other_Setting:
			
			//SET_BIT(PWMCTL, PCFS);		//Clock: 9.2MHz
			//CLR_BIT(PWMCTL, PCFS);		//Clock: 32.768kHz
			//CPRS = 0;
			
		break;


		default:
		break;
			
	}
}


