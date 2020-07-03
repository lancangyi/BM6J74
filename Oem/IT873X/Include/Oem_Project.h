

#ifndef OEM_PROJECT_H
#define OEM_PROJECT_H


#define SUPPORT_EC_FLASH_CODE				TRUE

#define SUPPORT_MAIN_SERVICE				TRUE
#define SUPPORT_SHARE_ROM					FALSE

//------------------------------------------------------------------
//SMBUS Setting
//------------------------------------------------------------------
#define	Disable_All_SMBUS_Channel	FALSE

#define	Enable_SMBUS_ChannelA		TRUE
#define	Enable_SMBUS_ChannelB		FALSE
#define	Enable_SMBUS_ChannelC		FALSE

#define SMBus_Freq							100//400,100,50,20,13,10
//------------------------------------------------------------------


// IRQ Settings

#define IRQ_ROUTINE_ENABLE		FALSE

//Use LRESET INT
#define	USE_LRESET_INT			FALSE
#define	PECI_Busy_Workaround	FALSE

#define INIT_CLEAR_IRAM			TRUE
#define INIT_CLEAR_XRAM		TRUE


//------------------------------------------------------------------
//FW Power sequence Debug
//------------------------------------------------------------------
#define PWR_ON_SEQ_DEBUG		FALSE
#define RESUME_SEQ_DEBUG		FALSE
#define PWR_OFF_SEQ_DEBUG		FALSE
#define SUSPEND_SEQ_DEBUG		FALSE
#define SB_PWRBTN_DEBUG		FALSE




//-----------------------------------------------------------------------------
// TIMERS (CORE_TIMER.CORE_ADC)
//
#define T_Timer_150us       (0xFFFF-167)
#define T_Timer_SEND        T_Timer_2ms
#define T_Timer_1ms         (0xFFFF-767)
#define T_Timer_2ms         (0xFFFF-1534)
#define T_Timer_5ms         (0xFFFF-3833)
#define T_Timer_10ms        (0xFFFF-7660)
#define T_Timer_20ms	     (0xFFFF-15332)
#define T_Timer_25ms        (0xFFFF-19165)
#define T_Timer_26ms	(0xFFFF-19942)
#define T_Timer_30ms        (0xFFFF-22998)
#define T_Timer_85ms        (0xFFFF-65534)
#define T_ACPI_BurstTime    T_Timer_2ms

//-----------------------------------------------------------------------------
// Power Switch Function Setting (x5ms)
//
#define T_POWSW_INTR    100     // 500ms timing for interrupt sequence
#define T_POWSW_OVER    50      //PowerSwitch override timeout debounce
#define T_POWSW_ToBTN   10      //PowerSwitch to PM PWRBTN# debounce
#define T_POWSW_LockON  200     // 1 Sec timer for PowerSwitch lock
#define T_POWSW_ONDB    10      // 50ms for PowerSwitch on debounce
#define T_POWSW_BBK     200     //Boot Block Entry debounce

//-----------------------------------------------------------------------------
// ACPI Module Setting
//
#define SUPPORTED_ACPI_SMB_EC		FALSE
#define SUPPORT_ACPI_SMI			FALSE	//Use SMI in ACPI Mode(No recommend)
#define EC_SMB_SCI_Number       		0x20    // ACPI EC SMBus Event
#define USE_SERVICE_EVENT_CENTER	TRUE
/* ACPI EC SCI Interrupt Response Timing ( 8-16uSec).*/
#define T_SCI_RESPONSE				5       // 0:10-12us,2:18-20us,4:26-28us
#define T_SCI_EVENT					25      // ~100us
#define T_SCI_STEP					40      //40x5ms=200ms step timing


//-----------------------------------------------------------------------------
// Legacy SMI Setting
//
#define T_SMI_EVENT             25      // ~100us
#define T_SMI_STEP              40      //40x5ms=200ms step timing
#define WaitECDataDelay         0x200
#define WaitPM2DataDelay        0x200
//-----------------------------------------------------------------------------

#define SUPPORTED_RECORDER  		FALSE   //Set 0 ->Remove Record Code from Source
#define SCI_EVENT_LOG				TRUE	//Support Record SCI Code from Source
#define En_Record62     				FALSE       //Enable Debug Port 62 Recorder
#define En_Record66     				FALSE       //Enable Debug Port 66 Recorder
#define En_Record68     				FALSE       //Enable Debug Port 68 Recorder
#define En_Record6C     				FALSE       //Enable Debug Port 6C Recorder

#define	Support_EC_CIR				FALSE


//Support 1ms Hook Timer
#define	SUPPORT_Hook_1ms_Timer	FALSE

#define	SMBusServiceCenterFunc		FALSE


#define	CIRRX_mapping_to_Pin84		FALSE


//Support Software KBC
#define SUPPORT_SWKBC		FALSE

//-----------------------------------------------------------------------------
//Set EC side PWM (PWMOUT)
//-----------------------------------------------------------------------------
#define	Support_EC_PWMOUT			FALSE

#define	PWM_Freq	PWM_Freq_128Hz

#define	PWM_Freq_64Hz				0
#define	PWM_Freq_128Hz			1
#define	PWM_Freq_200Hz			2
#define	PWM_Freq_250Hz			3
#define	PWM_Freq_500Hz			4
#define	PWM_Freq_1kHz				5
#define	PWM_Freq_2kHz				6
#define	PWM_Freq_35_9kHz			7
#define	PWM_Freq_Other_Setting		8

#define	PWM_Duty_100percent		0xFF
#define	PWM_Duty_75percent		0xC0
#define	PWM_Duty_50percent		0x80
#define	PWM_Duty_25percent		0x40
#define	PWM_Duty_0percent			0x00

//-----------------------------------------------------------------------------

//Disable DCache without checking
//IT8738 default: Disable
#define	Disable_DCache_without_checking	TRUE


//VCC Power status is treated as power-on
#define	VCC_POWER_ON_TREATED		FALSE

//Enable K8 function for AMD chipset
#define	K8_Function_Enable				FALSE


//Reset PMC in S5
#define	Reset_PMC_UnderS5			FALSE

//OEM Version number
#define	OEM_Version_MSB	0x04
#define	OEM_Version_LSB	0x00


//COMPARE_CHECKSUM ROM(0xFFFE-0xFFFF)
#define	COMPARE_CHECKSUM			FALSE


#endif



