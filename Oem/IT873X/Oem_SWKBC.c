#include "CORE_INC.H"
#include "OEM_INC.H"

#if SUPPORT_SWKBC
void Init_SWKBC(void)
{
    //RamDebug(0xDA);
    Index_07H = 0x07;
    SET_BIT(Index_F7H, 7);

    SET_MASK(SCCTRL,SCEN+SCSTART);
    SET_MASK(KBHICR,IBFCIE);
    SET_MASK(IER3,Int_KBCIBF);
    ISR3 = Int_KBCIBF;
}

/* ----------------------------------------------------------------------------
 * FUNCTION: Data_To_Host
 *
 *
 * ------------------------------------------------------------------------- */
void Data_To_Host(BYTE data_byte)
{
    //KBHISR &= 0x0F;
    //SET_MASK(KBHISR,KEYL);

	TR1 = 0;                 	// Disable timer1
	ET1 = 0;                  	// Disable timer1 interrupt
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	TH1 = T_Timer_20ms>>8;        // Set timer1 counter 20ms
	TL1 = T_Timer_20ms;           // Set timer1 counter 20ms
	TF1 = 0;                  	// Clear overflow flag
	TR1 = 1;                 	// Enable timer1

	while (!TF1)
	{
		if(IS_MASK_CLEAR(KBHISR,OBF) && IS_MASK_CLEAR(KBHISR,IBF))
		{
			break;
		}
	}

	TR1 = 0;            // Disable timer 1
       TF1 = 0;		    // clear overflow flag
       ET1 = 1;		    // Enable timer1 interrupt

	
    //while ((IS_MASK_SET(KBHISR,OBF)||IS_MASK_SET(KBHISR,IBF))) ;   
    KBHISR = 0x1C;
    
    KBHIKDOR = data_byte;
    //SET_MASK(SCCTRL,SCSTART);
    SCCTRL = 0x02;
}

/* ----------------------------------------------------------------------------
 * FUNCTION:   Buffer_Key
 *
 * Input:  Data to put in buffer.
 * Return: TRUE operation successful, FALSE unsuccessful.
 * ------------------------------------------------------------------------- */
BYTE Buffer_Key(BYTE bKBData)
{
    BYTE bFinish, bTmp;

    bFinish = TRUE;  				// Ready for successful operation
    bTmp = xbKbf_Tail;

    bTmp++;

    if(bTmp >= KBF_SIZE)
    {
        bTmp = 0;
    }

    // Check Overflow
    if(bTmp == xbKbf_Head)
    {
        //RamDebug(0xB1);
        bFinish = FALSE;           // Overflow Indication !!!
    }
    else
    {
        xbKEY_BUFF[xbKbf_Tail] = bKBData;  		// Store Data to Buffer Tail
        xbKbf_Tail++;					// Increment Buffer Tail (pointer)

        if(xbKbf_Tail >= KBF_SIZE) 
        {
            xbKbf_Tail = 0;  					// Wrap pointer if too large.
        }
    }

    return bFinish;
}


/* ----------------------------------------------------------------------------
 * FUNCTION:   Get_Buffer
 *
 * ------------------------------------------------------------------------- */
BYTE Get_KB_Buffer(void)
{

    BYTE bTmp = 0;

    if(xbKbf_Tail != xbKbf_Head)
    {
        bTmp = xbKEY_BUFF[xbKbf_Head++];
        if(xbKbf_Head >= KBF_SIZE) 
        {
            xbKbf_Head = 0;
        }
    }
    else
    {   
    	//Buffer is empty.
        bTmp = 0xFF;
    }

	return bTmp;

}


/* ----------------------------------------------------------------------------
 * FUNCTION:   Clear_Buffer
 *
 * ------------------------------------------------------------------------- */
void Clr_KB_Buffer(void)
{
    BYTE bIndex;

    for(bIndex=0 ; bIndex<=15 ; bIndex++)
    {
        xbKEY_BUFF[bIndex] = 0x00;
    }

    xbKbf_Head = 0;
    xbKbf_Tail = 0;
}


//--------------------------------------------------------------------------
//Example Function
//--------------------------------------------------------------------------
void BTN_VolUpPulse(void)
{
    #if SUPPORT_SWKBC
    //Make
    Buffer_Key(0xE0);
    Buffer_Key(0x30);
    //Break
    Buffer_Key(0xE0);
    Buffer_Key(0xB0);
    #endif    
}

void BTN_VolDownPulse(void)
{    
    #if SUPPORT_SWKBC
    //Make
    Buffer_Key(0xE0);
    Buffer_Key(0x2E);
    //Break
    Buffer_Key(0xE0);
    Buffer_Key(0xAE); 
    #endif    
}

#endif