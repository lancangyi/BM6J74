/*-----------------------------------------------------------------------------
 * Filename: OEM_POWER.C
 * Function: OEM USE EC CONTROL SYSTEM POWER
 *
 * Copyright (c) 2006-2009, ITE Tech. Inc. All Rights Reserved.
 *---------------------------------------------------------------------------*/
#include "CORE_INC.H"
#include "OEM_INC.H"

//-----------------------------------------------------------------------------
//OEM_POWER.H Parameter
//define    _PowrUp_S5      0
//define    _SYSTEM_S0      1
//define    _SYSTEM_S1      2
//define    _SYSTEM_S3      3
//define    _SYSTEM_S4      4
//define    _SYSTEM_S5      5
//define    _GO_POWER_ON    6
//define    _GO_RESUME_ON   7
//define    _GO_SUSPNED_OFF 8
//define    _GO_POWER_OFF   9


//-----------------------------------------------------------------------------

/*-----------------------------------------------------------------------------
 * Internal Process Definition
 *---------------------------------------------------------------------------*/
static void Oem_CheckPowSwitch(void);
static void Oem_PowSwToPWRBTN(void);
static void Oem_ChkS3Suspend(void);
static void Oem_ChkS5Shutdown(void);
static void Oem_ChkS3WakeUp(void);
static void Oem_SysOnSequence(void);
static void Oem_SysOffSequence(void);
static void Oem_SysResumeSequence(void);
static void Oem_SysSuspendSequence(void);
static void Oem_SysSuspendInit(void);
static void Oem_SysResumeInit(void);
static void Oem_PowSwitchIntr(void);
static void Oem_PowSwOver5Sec(void);
static void Oem_PowSwOver5Sec_ForceShutdown(void);


/****************************************/
/*	ADC Base and Calculation Reference		*/
/****************************************
base : 0.0029296875

Setting 1: 1.55V

Max:1.6171875
Min:1.453125
Assume: 1.4V => 478d => 1DEh


Setting 2: 1.294V

Max:1E0=>
Min:199=>1.1982421875 
Assume 1.2V => 410d => 19Ah

Setting 3: 1.107V

Max:1A0 :1.21875
Min:15F :1.0283203125
Assume: 1V => 341d => 155h

  ****************************************/
/*				End						*/
/****************************************/

//-----------------------------------------------------------------------------
// Handle System Power Control
//-----------------------------------------------------------------------------
void Oem_SysPowerContrl(void)
{
    switch (SysPowState)
    {
        case 0: // EC Initial Boot
                Oem_CheckPowSwitch();
		

                break;

        case 1: // System S0

                Oem_PowSwToPWRBTN();
		  #if 1
                Oem_PowSwOver5Sec();
		  #endif

                Oem_ChkS5Shutdown();
		  
		if(SysPowState == _SYSTEM_S0)
		{
                Oem_ChkS3Suspend();
		}

		Oem_PowSwOver5Sec_ForceShutdown();
		
                break;

        case 2: // System S1

                break;

        case 3: // System S3
                Oem_PowSwToPWRBTN();
                //Oem_PowSwOver5Sec();
                Oem_ChkS3WakeUp();

		if(SysPowState == _SYSTEM_S3)
		{
                Oem_ChkS5Shutdown();
		}
                break;

        case 4: // System S4

        case 5: // System S5

                Oem_CheckPowSwitch();

		  	if(STATE_PM_SLP_S4() == HighActive)
		  	{
		  		Oem_TriggerPowerOn();
		  	}


                break;

        case 6: // S5 -> S0  system power on sequence
                Oem_SysOnSequence();
		  Oem_PowSwOver5Sec_ForceShutdown();
                break;

        case 7: // S3 -> S0 resume power sequence
                Oem_SysResumeSequence();
		  Oem_PowSwOver5Sec_ForceShutdown();
                break;

        case 8: // S0 -> S3  system suspend sequence
                Oem_SysSuspendSequence();
		  Oem_PowSwOver5Sec_ForceShutdown();
                break;

        case 9: // S0 -> S5 system power off sequence

                Oem_SysOffSequence();
		  Oem_PowSwOver5Sec_ForceShutdown();
                break;

        default:
                SysPowState=0;
                return;
    }
    //-------------------------------------------------------------------------

}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Automatic Cold Boot Test Service (Suggestion: 1 Sec Hook)
//-----------------------------------------------------------------------------
void Oem_ColdBootTester(void)
{
    if ( AutoColdBootTimer > 0 )
    {
        if ( SysPowState == _SYSTEM_S5 )
        {
            if ( ColdBootTimer == 0x00 )
            {
                ColdBootTimer = AutoColdBootTimer;
            }
            else
            {
                ColdBootTimer--;

                if ( ColdBootTimer == 0x00 )
                {
                    Oem_TriggerPowerOn();
                }
            }

        }
        else
        {
            ColdBootTimer = AutoColdBootTimer;

        }
    }

}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Power Switch Control
//-----------------------------------------------------------------------------
void Oem_CheckPowSwitch(void)
{
    BYTE BTemp;
    if ( LockSwitchPowerOn > 0 )
    {
        LockSwitchPowerOn--;
        return;
    }
    #if PowerSW_Active
    //InputDebounce(FLAG PIN_STATUS,FLAG _ACTIVE,BYTE Counter_ID,BYTE ReloadCnt)
    BTemp = InputDebounce(STATE_PANSHW(),HighActive,0x00,T_POWSW_ONDB);
    //Return_0x00:NoAcitve 0x01:Active 0x02:Active&Debounced 0x03:RepeatActive
    #else
    BTemp = InputDebounce(STATE_PANSHW(),LowActive,0x00,T_POWSW_ONDB);
    #endif

    if ( BTemp == 0x02 )        // Active and Debounced
    {
        Oem_TriggerPowerOn();
    }

}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Trigger Control System Power On
//-----------------------------------------------------------------------------
void Oem_TriggerPowerOn(void)
{
    CtrlPowStep = 0;    //Reset Power Step Control Register
    PowSeqDelay = 0;    //Clear Sequence Delay Register
    SysPowState = _GO_POWER_ON; // Trigger S5->S0 system power on sequence

}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Trigger Control System Power Off
//-----------------------------------------------------------------------------
void Oem_TriggerPowerOff(void)
{
    CtrlPowStep = 0;    //Reset Power Step Control Register
    PowSeqDelay = 0;    //Clear Sequence Delay Register
    SysPowState = _GO_POWER_OFF;    // Trigger S5 system power off sequence
    LockSwitchPowerOn = T_POWSW_LockON;    // Lock Power timer

}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Power Switch routine to PWRBTN# Control
//-----------------------------------------------------------------------------
void Oem_PowSwToPWRBTN(void)
{
    BYTE    BTemp;

    #if PowerSW_Active
    //InputDebounce(FLAG PIN_STATUS,FLAG _ACTIVE,BYTE Counter_ID,BYTE ReloadCnt)
    BTemp = InputDebounce(STATE_PANSHW(),HighActive,0x00,T_POWSW_ToBTN);
    //Return_0x00:NoAcitve 0x01:Active 0x02:Active&Debounced 0x03:RepeatActive
    #else
    BTemp = InputDebounce(STATE_PANSHW(),LowActive,0x00,T_POWSW_ToBTN);
    #endif

    if ( BTemp == 0x03 )
    {
        //PWRBTN_LO();

	#if SB_PWRBTN_DEBUG
		RamDebug(0x5A);
	#endif
    }
    else
    {
        //PWRBTN_HI();
    }

}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Power Switch Interrupt Sequence Control
//-----------------------------------------------------------------------------
void Oem_PowSwitchIntr(void)
{
    BYTE BTemp;

    #if PowerSW_Active
    //InputDebounce(FLAG PIN_STATUS,FLAG _ACTIVE,BYTE Counter_ID,BYTE ReloadCnt)
    BTemp = InputDebounce(STATE_PANSHW(),HighActive,0x00,T_POWSW_INTR);
    //Return_0x00:NoAcitve 0x01:Active 0x02:Active&Debounced 0x03:RepeatActive
    #else
    BTemp = InputDebounce(STATE_PANSHW(),LowActive,0x00,T_POWSW_INTR);
    #endif
    if ( BTemp == 0x02 )        // Active and Debounced
    {
        Oem_TriggerPowerOff();
    }

}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Power Switch Control
//-----------------------------------------------------------------------------
void Oem_PowSwOver5Sec(void)
{
    BYTE BTemp;
    if ( (SysPowState == _SYSTEM_S4) || (SysPowState == _SYSTEM_S5) || (SysPowState == _PowrUp_S5) )
    {
        return;
    }
    #if PowerSW_Active
    //InputDebounce(FLAG PIN_STATUS,FLAG _ACTIVE,BYTE Counter_ID,BYTE ReloadCnt)
	BTemp = InputDebounce(STATE_PANSHW(),HighActive,0x00,T_POWSW_OVER);
    //Return_0x00:NoAcitve 0x01:Active 0x02:Active&Debounced 0x03:RepeatActive
    #else
	BTemp = InputDebounce(STATE_PANSHW(),LowActive,0x00,T_POWSW_OVER);
    #endif

    if ( BTemp == 0x03 )        // Active and Debounced
    {
        PowSwOverTimer++;
        if ( PowSwOverTimer > 1000 )
        {
            Oem_TriggerPowerOff();
        }
    }
    else
    {
        PowSwOverTimer = 0;
    }

}

//-----------------------------------------------------------------------------
// Check System S5 Shutdown Signal (PM_SLP_S5 or SUSC)
// Usually from System South Bridge
//-----------------------------------------------------------------------------
void Oem_ChkS5Shutdown(void)
{
    bit bTemp;
    bTemp = STATE_PM_SLP_S4();   // Get SLP_S4 Status
    if ( !bTemp )   // Low Active
    {
        Oem_TriggerPowerOff();
    }

}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Check System S3 Suspend Signal (PM_SLP_S3 or SUSB)
// Usually from System South Bridge
//-----------------------------------------------------------------------------
void Oem_ChkS3Suspend(void)
{
    bit bTemp;
    bTemp = STATE_PM_SLP_S3();   // Get SLP_S3 Status
    if ( !bTemp )   // Low Active
    {
        CtrlPowStep = 0;    //Reset Power Step Control Register
        PowSeqDelay = 0;    //Clear Sequence Delay Register
        // Trigger S0 -> S3  system suspend power off sequence
        SysPowState = _GO_SUSPNED_OFF;
    }

}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Check System S3 Resume Signal (PM_SLP_S3 or SUSB)
// Usually from System South Bridge
//-----------------------------------------------------------------------------
void Oem_ChkS3WakeUp(void)
{
    bit bTemp;
    bTemp = STATE_PM_SLP_S3();   // Get SLP_S3 Status
    if ( bTemp )    // Hi->Wake-Up
    {
        CtrlPowStep = 0;    //Reset Power Step Control Register
        PowSeqDelay = 0;    //Clear Sequence Delay Register
        // Trigger S3 -> S0  system resume power on sequence
        SysPowState = _GO_RESUME_ON;
    }

}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// System Power On RAM & Register configuration
//-----------------------------------------------------------------------------
void Oem_SysOnInit(void)
{
	
    SysPowState = _SYSTEM_S0;   // Set System S0

    LED_S0_Status = 0;
    _CORE_PMFLAG = 0;
    CORE_PMFLAG_S0 = 1;

	EC_start();
}
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// System Power Off RAM & Register configuration
//-----------------------------------------------------------------------------
void Oem_SysOffInit(void)
{
    SysPowState = _SYSTEM_S5;   // Set System S5

    _CORE_PMFLAG = 0;
    CORE_PMFLAG_S5 = 1;
    CtrlPowStep = 0;    //Reset Power Step Control Register
    PowSeqDelay = 0;    //Clear Sequence Delay Register
    
	#if	Reset_PMC_UnderS5
	RSTC1 = BIT2;	//Reset PMC
	Index_07H = 0x11;
	Index_30H = 0x01;
	Index_07H = 0x00;
	SET_MASK(IER3, Int_PMCIBF);
	ISR3 = Int_PMCIBF;
	SET_BIT(PM1CTL, 0);

	//PMC2	
	Index_07H = 0x12;
	Index_30H = 0x01;
	Index_07H = 0x00;
	SET_MASK(IER3, Int_PMC2IBF);
	ISR3 = Int_PMC2IBF;
	SET_BIT(PM2CTL, 0);
	#endif
	
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// System Suspend Power Off RAM & Register configuration
//-----------------------------------------------------------------------------
void Oem_SysSuspendInit(void)
{
    SysPowState = _SYSTEM_S3;   // Set System S3

    _CORE_PMFLAG = 0;
    CORE_PMFLAG_S3 = 1;


}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// System Suspend Power On RAM & Register configuration
//-----------------------------------------------------------------------------
void Oem_SysResumeInit(void)
{
    SysPowState = _SYSTEM_S0;   // Set System S0

    _CORE_PMFLAG = 0;
    CORE_PMFLAG_S0 = 1;
}

//-----------------------------------------------------------------------------
// Init Share Memory Register
//-----------------------------------------------------------------------------
void InitShareMemory(void)
{
    //UCCTRLR = 0x83;   //ATi Chipset Need (INTEL don't)
//    SWCTL2 = 0;         //Set sysetm power on
    FMSSR = 0x0F;       //For 1M Bytes Share Rom
    SET_BIT(FPCFG,4);   //Enable LPC Bust mode

}

//-----------------------------------------------------------------------------
// FUNCTION: System Power On Sequence (Turns On System Power)
// TimeHook: 5mSec
//-----------------------------------------------------------------------------
void Oem_SysOnSequence(void)
{
    //bit  bTemp;
    //BYTE BTemp;
    //-------------------------------------------------------------------------
    if ( PowSeqDelay > 4 )
    {
        PowSeqDelay-=5; //5mSec count base
        if ( PowSeqDelay < 4 )
        {
            PowSeqDelay=0;
        }
        else
        {
            return;
        }
    }
    //-------------------------------------------------------------------------
    //Power On Sequence step control
    //-------------------------------------------------------------------------
    switch (CtrlPowStep)    //Step 5mSec
    {

	case 0:

		#if PWR_ON_SEQ_DEBUG
		RamDebug(0xE0) ;
		#endif
		
		PowSeqDelay = 15;
		break;
		
	case 1:

		#if PWR_ON_SEQ_DEBUG
		RamDebug(0xE1) ;
		#endif
				
		PowSeqDelay = 150;	//delay 110ms		
		break;


        case 2:

		#if PWR_ON_SEQ_DEBUG
		RamDebug(0xE2) ;
		#endif
		
		PowSeqDelay = 80 ;
		break ;

	case 3:

		#if PWR_ON_SEQ_DEBUG
		RamDebug(0xE3) ;
		#endif
		
		break;

        case 4:

		#if PWR_ON_SEQ_DEBUG
		RamDebug(0xE4) ;
		#endif
		
		break;

        case 5:

		#if PWR_ON_SEQ_DEBUG
		RamDebug(0xE5) ;
		#endif

		PowSeqDelay = 5 ;		
		break;

	case 6:

		#if PWR_ON_SEQ_DEBUG
		RamDebug(0xE6) ;
		#endif
		
		PowSeqDelay = 5 ;
		break ;

        case 7:

		#if PWR_ON_SEQ_DEBUG
		RamDebug(0xE7) ;
		#endif

		PowSeqDelay = 5 ;
		break ;

	case 8:

		#if PWR_ON_SEQ_DEBUG
		RamDebug(0xE8) ;
		#endif
		
		PowSeqDelay = 10 ;
		break ;

	case 9:

		#if PWR_ON_SEQ_DEBUG
		RamDebug(0xE9) ;
		#endif

		PowSeqDelay = 10 ;

		break ;


	case 10:

		#if PWR_ON_SEQ_DEBUG
		RamDebug(0xEA) ;
		#endif
		
		PowSeqDelay = 10 ;
		break ;



	case 11:

		#if PWR_ON_SEQ_DEBUG
		RamDebug(0xEB) ;
		#endif

		Oem_SysOnInit();


		break;

        default:
                CtrlPowStep=0;
                break;
    }

    //-------------------------------------------------------------------------

        CtrlPowStep++;

    //-------------------------------------------------------------------------

}


//-----------------------------------------------------------------------------
// FUNCTION: System Resume from S3 Sequence (Turns On Suspend Power)
// TimeHook: 5mSec
//-----------------------------------------------------------------------------
void Oem_SysResumeSequence(void)
{
    //bit bTemp;

    //-------------------------------------------------------------------------
    if ( PowSeqDelay > 4 )
    {
        PowSeqDelay-=5; //5mSec count base

        if ( PowSeqDelay < 4 )
        {
            PowSeqDelay=0;
        }
        else
        {
            return;
        }
    }
    //-------------------------------------------------------------------------
    //System Resume Sequence step control
    //-------------------------------------------------------------------------
    switch (CtrlPowStep)    //Step 5mSec
    {

	case 0:

		#if RESUME_SEQ_DEBUG
		RamDebug(0xC0) ;
		#endif

		PowSeqDelay = 5 ;

		break;


        case 1:

		#if RESUME_SEQ_DEBUG
		RamDebug(0xC1) ;
		#endif


		PowSeqDelay = 5 ;
		
		break;


        case 2:

		#if RESUME_SEQ_DEBUG
		RamDebug(0xC2) ;
		#endif

		
		PowSeqDelay = 5 ;

		break;

        case 3:

		#if RESUME_SEQ_DEBUG
		RamDebug(0xC3) ;
		#endif

		PowSeqDelay = 5 ;

		break;

        case 4:

		#if RESUME_SEQ_DEBUG
		RamDebug(0xC4) ;
		#endif

		PowSeqDelay = 10 ;

		break;




        case 5:

		#if RESUME_SEQ_DEBUG
		RamDebug(0xC5) ;
		#endif

		PowSeqDelay = 10 ;

		break;

	case 6:

		#if RESUME_SEQ_DEBUG
		RamDebug(0xC6) ;
		#endif

		break ;

	case 7:

		#if PWR_ON_SEQ_DEBUG
		RamDebug(0xC7) ;
		#endif
		
		break;


	case 8:

		#if PWR_ON_SEQ_DEBUG
		RamDebug(0xC8) ;
		#endif
		
		break;


        case 9:

		#if RESUME_SEQ_DEBUG
		RamDebug(0xC9) ;
		#endif

		Oem_SysOnInit();

		break ;

        default:
                CtrlPowStep=0;
                break;
    }

    //-------------------------------------------------------------------------

        CtrlPowStep++;

    //-------------------------------------------------------------------------

}

//-----------------------------------------------------------------------------
// FUNCTION: Force System Power Off Sequence
//
//-----------------------------------------------------------------------------
void Oem_ForceSystemOff(void)
{
    CtrlPowStep = 0;
    while(1)
    {
        vDelay1ms(5);   // Delay 5ms
        Oem_SysOffSequence();
        if( CtrlPowStep == 0 )
        {
            break;
        }
    }

}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// FUNCTION: System Power Off Sequence
// TimeHook: 5mSec
//-----------------------------------------------------------------------------
void Oem_SysOffSequence(void)
{
    //bit   bTemp;
    //-------------------------------------------------------------------------
    if ( PowSeqDelay > 4 )
    {
        PowSeqDelay-=5; //5mSec count base

        if ( PowSeqDelay < 4 )
        {
            PowSeqDelay=0;
        }
        else
        {
            return;
        }
    }
    //-------------------------------------------------------------------------
    // System Off step contrl
    //-------------------------------------------------------------------------
    switch (CtrlPowStep)    //Step 5mSec
    {
        case 0:
			
		#if PWR_OFF_SEQ_DEBUG
		RamDebug(0xF0) ;
		#endif
		
                break;
				

        case 1:
			
		#if PWR_OFF_SEQ_DEBUG
		RamDebug(0xF1) ;
		#endif

                break;


        case 2:
			
		#if PWR_OFF_SEQ_DEBUG
		RamDebug(0xF2) ;
		#endif

                break;

        case 3:
			
		#if PWR_OFF_SEQ_DEBUG
		RamDebug(0xF3) ;
		#endif


		PowSeqDelay = 10 ;
                break;


        case 4:
			
		#if PWR_OFF_SEQ_DEBUG
		RamDebug(0xF4) ;
		#endif


		
		PowSeqDelay = 10 ;
                break;
				
        case 5:

		#if PWR_OFF_SEQ_DEBUG
		RamDebug(0xF5) ;
		#endif

		
		
		break;
				
        case 6:

		#if PWR_OFF_SEQ_DEBUG
		RamDebug(0xF6) ;
		#endif
		
		
               break;

				
        case 7:

		#if PWR_OFF_SEQ_DEBUG
		RamDebug(0xF7) ;
		#endif
		
		PowSeqDelay = 5 ;

		break ;
		
        case 8:

		#if PWR_OFF_SEQ_DEBUG
		RamDebug(0xF8) ;
		#endif

		
		PowSeqDelay = 5 ;

		break ;

        case 9:

		#if PWR_OFF_SEQ_DEBUG
		RamDebug(0xF9) ;
		#endif

		
		PowSeqDelay = 5 ;

		break ;

        case 10:

		#if PWR_OFF_SEQ_DEBUG
		RamDebug(0xFA) ;
		#endif


		PowSeqDelay = 5 ;

		break ;


        case 11:

		#if PWR_OFF_SEQ_DEBUG
		RamDebug(0xFB) ;
		#endif

		
		PowSeqDelay = 5 ;

		break ;


        case 12:

		#if PWR_OFF_SEQ_DEBUG
		RamDebug(0xFC) ;
		#endif
	
		
		PowSeqDelay = 5 ;

		break ;


        case 13:

		#if PWR_OFF_SEQ_DEBUG
		RamDebug(0xFD) ;
		#endif

		
		PowSeqDelay = 5 ;

		break ;


	case 14:

		
		#if PWR_OFF_SEQ_DEBUG
		RamDebug(0xFE) ;
		#endif

		Oem_SysOffInit();

                break;
				
        default:
                CtrlPowStep=0;
                return;
    }

    //-------------------------------------------------------------------------

        CtrlPowStep++;

    //-------------------------------------------------------------------------

}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// FUNCTION: System Suspend Power Off Sequence
// TimeHook: 5mSec
//-----------------------------------------------------------------------------
void Oem_SysSuspendSequence(void)
{
    //bit   bTemp;

    //-------------------------------------------------------------------------
    if ( PowSeqDelay > 4 )
    {
        PowSeqDelay-=5; //5mSec count base

        if ( PowSeqDelay < 4 )
        {
            PowSeqDelay=0;
        }
        else
        {
            return;
        }
    }
    //-------------------------------------------------------------------------
    //System Suspend step control
    //-------------------------------------------------------------------------
    switch (CtrlPowStep)    //Step 5mSec
    {
	
        case 0:

		#if SUSPEND_SEQ_DEBUG
		RamDebug(0xB0) ;
		#endif

		
		break ;

        case 1:

		#if SUSPEND_SEQ_DEBUG
		RamDebug(0xB1) ;
		#endif
		
		

		break;
		
        case 2:

		#if SUSPEND_SEQ_DEBUG
		RamDebug(0xB2) ;
		#endif

		break;

        case 3:

		#if SUSPEND_SEQ_DEBUG
		RamDebug(0xB3) ;
		#endif
		

		break;

        case 4:
			
		#if SUSPEND_SEQ_DEBUG
		RamDebug(0xB4) ;
		#endif


		PowSeqDelay = 10;
		break;

        case 5:
			
		#if SUSPEND_SEQ_DEBUG
		RamDebug(0xB5) ;
		#endif
		

		PowSeqDelay = 10;
		break;

        case 6:
			
		#if SUSPEND_SEQ_DEBUG
		RamDebug(0xB6) ;
		#endif
		

		break;

        case 7:
			
		#if SUSPEND_SEQ_DEBUG
		RamDebug(0xB7) ;
		#endif
		
		

		break;

        case 8:
			
		#if SUSPEND_SEQ_DEBUG
		RamDebug(0xB8) ;
		#endif
		
		

		break;

        case 9:
			
		#if SUSPEND_SEQ_DEBUG
		RamDebug(0xB9) ;
		#endif
		
		Oem_SysSuspendInit();

		break;
				
        default:
                CtrlPowStep=0;
                break;
    }

    //-------------------------------------------------------------------------

        CtrlPowStep++;

    //-------------------------------------------------------------------------

}
//-----------------------------------------------------------------------------


void Oem_PowSwOver5Sec_ForceShutdown(void)
{
	BYTE BTemp;
	#if PowerSW_Active
	//InputDebounce(FLAG PIN_STATUS,FLAG _ACTIVE,BYTE Counter_ID,BYTE ReloadCnt)
	BTemp = InputDebounce(STATE_PANSHW(),HighActive,0x00,T_POWSW_OVER);
	//Return_0x00:NoAcitve 0x01:Active 0x02:Active&Debounced 0x03:RepeatActive
	#else
	BTemp = InputDebounce(STATE_PANSHW(),LowActive,0x00,T_POWSW_OVER);
	#endif

	if ( BTemp == 0x03 )        // Active and Debounced
	{
		PowSwOverTimer++;
		if ( PowSwOverTimer > 1500 )
		{

			
			PowSwOverTimer = 0;
			Oem_SysOffInit();
		}
	}
	else
	{
		PowSwOverTimer = 0;
	}
}


void Check_Power_State(void)
{
	if(STATE_PM_SLP_S4() == HIGH)	//Not S5
	{

		if(STATE_PM_SLP_S3() == HIGH )	//S0
		{
			if( (SysPowState == _SYSTEM_S5) ||(SysPowState == _PowrUp_S5) || (SysPowState == _SYSTEM_S4)  )	//S4/S5 -> S0
			{

				Oem_SysOnInit();
				
				CLR_BIT(Index_23H, 0);	//Enable 48M clock				
			}
			else if( (SysPowState == _SYSTEM_S3) )	//S3->S0
			{
				Oem_SysResumeInit();
				CLR_BIT(Index_23H, 0);	//Enable 48M clock				
			}
			
		}
		else		//S3
		{
			if( SysPowState == _SYSTEM_S0 )	//S0->S3
			{
				#ifdef Check_SUSB_Twice
				SysPowState = _Ready_to_S3;
				#else
				Oem_SysSuspendInit();	
				SET_BIT(Index_23H,0);	//Disable 48M clock
				#endif

			}
			#ifdef Check_SUSB_Twice
			else if( SysPowState == _Ready_to_S3 )	//S0->S3 (ready to S3)
			{
				Oem_SysSuspendInit();	
				SET_BIT(Index_23H,0);	//Disable 48M clock
			}
			#endif
			
		}

		
	}
	else			//S4 or S5
	{
		#ifdef Check_SUSB_Twice
		if( (SysPowState == _SYSTEM_S0) ||(SysPowState == _SYSTEM_S3) ||(SysPowState == _Ready_to_S3) )	//S0/S3 -> S4/S5
		#else
		if( (SysPowState == _SYSTEM_S0) ||(SysPowState == _SYSTEM_S3) )	//S0/S3 -> S4/S5
		#endif
		{
		
			Oem_SysOffInit();
			SET_BIT(Index_23H,0);	//Disable 48M clock
			
		}
	}
	
}

//power led
const WORD code PowerLEDPattern[]= 
{
  	//--------------------------------------------------------------------------
  	// 	S0      S3   	S4      S5      index4  index5    					 
	//--------------------------------------------------------------------------
  		0xFFFF, 0x5555, 0x0000, 0x0000, 0x0000, 0x0000,		//	Power LED1
};

//----------------------------------------------------------------------------
// Turn on/off LEDs according to machine status.
// Executed once per 1 sec
// for example:
//		 ->BIT14	
// 		1010101010101010
// 		0101010101010101
//				  <-BIT3 				
//----------------------------------------------------------------------------
void ProcessLED(void) 
{
	BYTE bat_index, pwr_index;   
    
   	LED_FLASH_CNT <<= 1;
	if(LED_FLASH_CNT == 0)
		LED_FLASH_CNT=0x0001;

    /* Power LED control method */
    pwr_index=0;                // pre-set S0                  
    
	if(SystemIsS5)              // pre-set S5    
	{
		pwr_index=3;
	}
	if(SystemIsS4)              // pre-set S4   
	{
		pwr_index=2;
	}
	if(SystemIsS3)              // pre-set S3    
	{
		pwr_index=1;
	}

	if(PowerLEDPattern[pwr_index] & LED_FLASH_CNT)	// setup power LED
	{	
		PWR_LED_ON();
	} 
	else 
	{	
		PWR_LED_OFF();
	}
    

}
/*-----------------------------------------------------------------------------
 * End
 *---------------------------------------------------------------------------*/

