/*-----------------------------------------------------------------------------
 * Filename: OEM_FAN.C
 * Function: OEM FAN Control
 *
 * Copyright (c) 2009-2012, ITE Tech. Inc. All Rights Reserved.
 *---------------------------------------------------------------------------*/
 
#include "CORE_INC.H"
#include "OEM_INC.H"

ECReg	ADC_TEMP_ENABLE			_at_ (GEE_BASE_ADDR + 0x51);
ECReg	ADC_TEMP_EXTRA_ENABLE	_at_ (GEE_BASE_ADDR + 0x55);

ECReg	FAN1_TEMP_OFF			_at_ (GEE_BASE_ADDR + 0x60);
ECReg	FAN1_TEMP_START			_at_ (GEE_BASE_ADDR + 0x61);
ECReg	FAN1_TEMP_FULL			_at_ (GEE_BASE_ADDR + 0x62);
ECReg	FAN1_CTRL				_at_ (GEE_BASE_ADDR + 0x64);
ECReg	FAN1_TEMP_DELTA			_at_ (GEE_BASE_ADDR + 0x65);
ECReg	FAN1_ZONE				_at_ (GEE_BASE_ADDR + 0x66);

ECReg	FAN2_TEMP_OFF			_at_ (GEE_BASE_ADDR + 0x68);
ECReg	FAN2_TEMP_START			_at_ (GEE_BASE_ADDR + 0x69);
ECReg	FAN2_TEMP_FULL			_at_ (GEE_BASE_ADDR + 0x6A);
ECReg	FAN2_CTRL				_at_ (GEE_BASE_ADDR + 0x6C);
ECReg	FAN2_TEMP_DELTA			_at_ (GEE_BASE_ADDR + 0x6D);
ECReg	FAN2_ZONE				_at_ (GEE_BASE_ADDR + 0x6E);

ECReg	FAN3_TEMP_OFF			_at_ (GEE_BASE_ADDR + 0x70);
ECReg	FAN3_TEMP_START			_at_ (GEE_BASE_ADDR + 0x71);
ECReg	FAN3_TEMP_FULL			_at_ (GEE_BASE_ADDR + 0x72);
ECReg	FAN3_CTRL				_at_ (GEE_BASE_ADDR + 0x74);
ECReg	FAN3_TEMP_DELTA			_at_ (GEE_BASE_ADDR + 0x75);
ECReg	FAN3_ZONE				_at_ (GEE_BASE_ADDR + 0x76);

ECReg	FAN_A_TEMP_START		_at_ (GEE_BASE_ADDR + 0x90);
ECReg	FAN_A_SLOP				_at_ (GEE_BASE_ADDR + 0x91);
ECReg	FAN_A_TEMP_DELTA		_at_ (GEE_BASE_ADDR + 0x92);

ECReg	FAN_B_TEMP_START		_at_ (GEE_BASE_ADDR + 0x94);
ECReg	FAN_B_SLOP				_at_ (GEE_BASE_ADDR + 0x95);
ECReg	FAN_B_TEMP_DELTA		_at_ (GEE_BASE_ADDR + 0x96);
//-----------------------------------------------------------------------------
/*****************************************************************************/
/* PWM/TACHX MODULE **********************************************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
// Calculation Fan Tachometer to Fan Speed (R.P.M)
// Fan Speed (R.P.M)=60/(1/fs sec * {FnTMRR,FnTLRR) * P )
//-----------------------------------------------------------------------------
WORD GetFanRPM(BYTE FnTMRR,BYTE FnTLRR)
{
	WORD	FanRPMSpd, FanRPMDiv;
	WORD	FnTWRR; 

	if( (FnTMRR == 0xFF)&&(FnTLRR == 0xFF) )
		return 0;


	FnTWRR = FnTMRR*0x100+FnTLRR;
	

	FanRPMSpd = 675000 / FnTWRR;

	return FanRPMSpd;

}

void EC_start(void)
{
	CFG_REG |= 0x80;				// Restore EC registers to their default values
	CFG_REG &= 0xFE;				// Put EC in standby mode

	PWM_STEP_FREQ_REG = 0x8F;		// FAN smoothing step freq: 8Hz, FAN4: none
	FAN_MAIN_CTL = 0x33;			// Enable TACH2/TACH1, enable FAN2/FAN1 smartguardian mode
	FAN_CTL = 0xC0;					// FAN Active Polarity: High, PWM freq for FAN1/FAN3: 23.43KHz
	ADC_TEMP_EXTRA_ENABLE = 0x40;	// PWM freq for FAN2: 23.43KHz

	FAN_CTL1 = 0x85;				// FAN1: auto mode, tacho close-loop mode, temperature: TMPIN2 CPU
	FAN1_TEMP_OFF = 0;
	FAN1_TEMP_START = 50;			// First phase: 50°C - 60°C
	FAN1_TEMP_FULL = 80;			// Full speed temperature: 80°C
	PWM_FAN_CTL1 = 125;			// Start RPM: 125 * 16 = 2000 RPM
	FAN1_CTRL = 0x80 + 15;			// Smoothing mode, Slop = 1200 RPM / 10°C = 120 RPM/°C(120 / 8 = 15)
	FAN1_TEMP_DELTA = 2;			// Delta-temperature: 2°C
	FAN1_ZONE = 16;					// Target Zone: 128 RPM = 16 * 8
	FAN_A_TEMP_START = 60;			// Second phase: 60°C - 70°C
	FAN_A_SLOP = 16;				// (FAN_B_TEMP_DELTA.1, FAN_B_SLOP.7)=00: TMPIN2, SLOP = 1300 RPM / 10°C = 130 RPM/°C(130 / 8 = 16.25)
	FAN_A_TEMP_DELTA = 0x42;		// Extra-A for FAN1, Delta-temperature: 2°C

	FAN_CTL2 = 0x84;				// FAN2: auto mode, tacho close-loop mode, temperature: TMPIN1 SYS
	FAN2_TEMP_OFF = 0;
	FAN2_TEMP_START = 50;			// First phase: 50°C - 60°C
	FAN2_TEMP_FULL = 80;			// Full speed temperature: 80°C
	PWM_FAN_CTL2 = 125;			// Start RPM: 125 * 16 = 2000 RPM
	FAN2_CTRL = 0x80 + 15;			// Smoothing mode, Slop = 1200 RPM / 10°C = 120 RPM/°C(120 / 8 = 15)
	FAN2_TEMP_DELTA = 2;			// Delta-temperature: 2°C
	FAN2_ZONE = 16;					// Target Zone: 128 RPM = 16 * 8
	FAN_B_TEMP_START = 60;			// Second phase: 60°C - 70°C
	FAN_B_SLOP = 0x80 + 16;			// (FAN_B_TEMP_DELTA.1, FAN_B_SLOP.7)=01: TMPIN1, SLOP = 1300 RPM / 10°C = 130 RPM/°C(130 / 8 = 16.25)
	FAN_B_TEMP_DELTA = 0x22;		// Extra-B for FAN2, Delta-temperature: 2°C

	ADC_TEMP_ENABLE = 0x03;			// TMPIN2/TMPIN1 enable thermal diode mode
	ADC_channel_enable = 0xFF;			// enable voltage A/D conversion for VIN0-VIN7

	CFG_REG |= 0x01;				// Start EC
}

void EC_stop(void)
{
	CFG_REG |= 0x80;				// Restore EC registers to their default values
	CFG_REG &= 0xFE;				// Put EC in standby mode
}