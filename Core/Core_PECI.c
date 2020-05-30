/*-----------------------------------------------------------------------------
 * Filename: CORE_PECI.C
 * Function: System Management SMBus Protocol drivers.
 *
 * Copyright (c) 2006-2013, ITE Tech. Inc. All Rights Reserved.
 *---------------------------------------------------------------------------*/
#include "CORE_INC.H"
#include "OEM_INC.H"


// ----------------------------------------------------------------------------
// The function of PECI3.0 Package power SKU unit read
// Output:
//          0 : Fail
//          1 : OK
// ----------------------------------------------------------------------------
BYTE PECI_ReadPowerUnit(void)
{
	BYTE result;
	if(PECI_RdPkgConfig(PECI_CPU_ADDR, &PECI_readBuffer[0], PECI_Domain_0, 0x00, PECI_Index_PPSU, 0x00, 0x00, 0x05, 0x05))
	{
		//
		PECI_PowerUnit = (PECI_readBuffer[1]&0x0F);      // bit 0 ~ bit3
		PECI_EnergyUnit = (PECI_readBuffer[2]&0x1F);     // bit 8 ~ bit12
		PECI_TimeUnit = (PECI_readBuffer[3]&0x0F);       // bit 16 ~ bit19
		result = 0x01;
	}
	else
	{
		result = 0x00;
	}
	return(result);
}



//-----------------------------------------------------------------------
// Read to the package configuration space (PCS) within the processor
//  return : 
//              1 : done
//              0 : error
//  Input : 
//              (1) HostTargetAddr : The address of processor
//              (2) *ReadData : the start address of variable to save data
//              (3) Domain : 0 or 1¡C 
//                           0 : Domain 0, 1 : Domain 1¡C
//              (4) Retry   0 or 1
//              (5) Index
//              (6) LSB of parameter
//              (7) MSB of parameter
//              (8) ReadLen read length 2 or 3 or 5
//              (9) WriteLen write length 5
//-----------------------------------------------------------------------
//PECI_RdPkgConfig(0x30, &EC_PECI_RdPkgConfig_Buf, 0, 0, PECI_Index_TTR, 0, 0, 5, 5);
// Tjmax : 4th byte, Tcontrol_offset : 3rd byte
//-----------------------------------------------------------------------
BYTE PECI_RdPkgConfig(BYTE HostTargetAddr, XBYTE *ReadData, BYTE Domain, BYTE Retry,BYTE Index, BYTE LSB, BYTE MSB, BYTE ReadLen, BYTE WriteLen)
{
	BYTE iTemp;
	BYTE done;

	// Initialize the host
	if(AWFCS_EN == 0x01)
	{
		IF_SELECT_REG = 0x65 ;

	}
	else
	{
		IF_SELECT_REG = 0x64 ;

	}

	// Reset Data FIFO Pointer
	SET_BIT(PECI_HOST_CTRL, 3);
	
	PECI_HOST_CTRL = 0x00; 
	PECI_HOST_STS = 0xFF ;

	PECI_TARGET_ADDR = HostTargetAddr ;
	PECI_WR_LENGTH = WriteLen ;	//Write Len = 05h
	PECI_RD_LENGTH = ReadLen ;	//Read Len = 05h

	if(Domain<2)
	{
		PECI_WR_DATA_1 = PECI_CMD_RdPkgConfig+Domain;
	}
	else
	{
		PECI_WR_DATA_1 = PECI_CMD_RdPkgConfig;
	}

	if(Retry<2)
	{
		PECI_WR_DATA_2_TO_8 = (PECI_HostID<<1)+Retry;
	}
	else
	{
		PECI_WR_DATA_2_TO_8 = (PECI_HostID<<1);
	}

	PECI_WR_DATA_2_TO_8= Index ;	//Index	PECI_Index_TTR = 16
	PECI_WR_DATA_2_TO_8= LSB ;	//LSB
	PECI_WR_DATA_2_TO_8= MSB ;	//MSB

	// Waiting for start
	Set_T1_Timeout(T_Timer_85ms);	//Reset TF1
	while( (IS_BIT_SET(PECI_HOST_STS, 0))&& (TF1 == 0) ) ;
	if(TF1 == 1)	//Timeout
		return 0;	//Fail
	
	// Start
	PECI_HOST_CTRL = 0x01 ;

	if(IS_BIT_SET(PECI_HOST_STS, 6)) return 0x0;


	Set_T1_Timeout(T_Timer_85ms);	//Reset TF1
	while( (!(IS_BIT_SET(PECI_HOST_STS, 1) )) && (TF1 == 0) ) ;
	if(TF1 == 1)	//Timeout
		return 0;	//Fail


	if(  (PECI_HOST_STS&0x6C)!=0 ) return 0x00;
	
	for(iTemp = 0x00;iTemp < ReadLen;iTemp++)
	{
	
		*(ReadData+iTemp) = PECI_FIFO;
	}
	

	// Reset Data FIFO Pointer
	SET_BIT(PECI_HOST_CTRL, 3);
	PECI_HOST_CTRL = 0x00;
	PECI_HOST_STS = 0xFE ;

	if(*ReadData == PECI_CC_Valid)
	{
		done = 0x01;
	}
	else
	{
		done = 0x00;
	}

	return done;
	
}



//-----------------------------------------------------------------------
// Write to the package configuration space (PCS) within the processor
//  return : 
//              1 : done
//              0 : error
//  Input : 
//              (1) HostTargetAddr : The address of processor
//              (2) *WriteData : the start address of variable to wirte data
//              (3) Domain : 0 or 1¡C 
//                           0 : Domain 0, 1 : Domain 1¡C
//              (4) Retry   0 or 1
//              (5) Index
//              (6) LSB of parameter
//              (7) MSB of parameter
//              (8) ReadLen read length 1
//              (9) WriteLen write length 0x07 or 0x08 or 0x0A
//-----------------------------------------------------------------------
BYTE PECI_WrPkgConfig(BYTE HostTargetAddr, XBYTE *WriteData, BYTE Domain, BYTE Retry,BYTE Index, BYTE LSB, BYTE MSB, BYTE ReadLen, BYTE WriteLen)
{

	BYTE iTemp;
	BYTE done;

	if(AWFCS_EN == 0x01)
	{
		IF_SELECT_REG = 0x65 ;
	}
	else
	{
		IF_SELECT_REG = 0x64 ;
	}
	
	// Reset Data FIFO Pointer
	SET_BIT(PECI_HOST_CTRL, 3);
	
	PECI_HOST_CTRL = 0x00; 
	PECI_HOST_STS = 0xFF ;

	PECI_TARGET_ADDR = HostTargetAddr ;
	PECI_WR_LENGTH = WriteLen ;	//Write Len = 05h
	PECI_RD_LENGTH = ReadLen ;	//Read Len = 01h

	if(Domain<2)
	{
		PECI_WR_DATA_1 = PECI_CMD_WrPkgConfig+Domain;
	}
	else
	{
		PECI_WR_DATA_1 = PECI_CMD_RdPkgConfig;
	}

	if(Retry<2)
	{
		PECI_WR_DATA_2_TO_8 = (PECI_HostID<<1)+Retry;
	}
	else
	{
		PECI_WR_DATA_2_TO_8 = (PECI_HostID<<1);
	}

	PECI_WR_DATA_2_TO_8= Index ;	//Index	PECI_Index_TTR = 16
	PECI_WR_DATA_2_TO_8= LSB ;	//LSB
	PECI_WR_DATA_2_TO_8= MSB ;	//MSB
	for(iTemp=0x00; iTemp<(WriteLen-6); iTemp++)
	{
		PECI_WR_DATA_2_TO_8 = *(WriteData+iTemp);
	}

	// Waiting for start
	Set_T1_Timeout(T_Timer_85ms);	//Reset TF1
	while( (IS_BIT_SET(PECI_HOST_STS, 0)) && (TF1 == 0) ) ;
	if(TF1 == 1)	//Timeout
		return 0;	//Fail

	// Start
	PECI_HOST_CTRL = 0x01 ;
	
	if(IS_BIT_SET(PECI_HOST_STS, 6)) return 0x00;


	Set_T1_Timeout(T_Timer_85ms);	//Reset TF1
	while( (!(IS_BIT_SET(PECI_HOST_STS, 1) )) && (TF1 == 0) ) ;
	if(TF1 == 1)	//Timeout
		return 0;	//Fail

	if(  (PECI_HOST_STS&0x6C)!=0 ) return 0x00;

	iTemp = PECI_FIFO;

	// Reset Data FIFO Pointer
	SET_BIT(PECI_HOST_CTRL, 3);
	PECI_HOST_CTRL = 0x00;
	PECI_HOST_STS = 0xFE ;

	if(iTemp == PECI_CC_Valid )
	{
		done = 0x01;
	}
	else
	{
		done = 0x00;
	}

	return done;
}



BYTE PECI_Host_Access_GetTemp(BYTE HostTargetAddr)
{

	// Change LDN to Environment Controller Page
	//Index_07H = 0x04 ;

	//
	// Initialize the host
	//AWFCS_EN = 0x01;
	
	if(AWFCS_EN == 0x01)
	{
		IF_SELECT_REG = 0x65 ;		
		
	}
	else
	{
		IF_SELECT_REG = 0x64 ;	
	}

	// Reset Data FIFO Pointer
	SET_BIT(PECI_HOST_CTRL, 3);
	
	PECI_HOST_CTRL = 0x00; 
	PECI_HOST_STS = 0xFF ;

	PECI_TARGET_ADDR = HostTargetAddr ;
	PECI_WR_LENGTH = 0x01 ;
	PECI_RD_LENGTH = 0x02 ;

	PECI_WR_DATA_1 = 0x01 ;
	PECI_WR_DATA_2_TO_8= 0x00 ;

	// Waiting for start
	Set_T1_Timeout(T_Timer_85ms);	//Reset TF1
	while( (IS_BIT_SET(PECI_HOST_STS, 0))&& (TF1 == 0) ) ;
	if(TF1 == 1)	//Timeout
		return 0;	//Fail
	// Start
	PECI_HOST_CTRL = 0x01 ;

	if(IS_BIT_SET(PECI_HOST_STS, 6)) return 0x00;

	Set_T1_Timeout(T_Timer_85ms);	//Reset TF1
	while( (!(IS_BIT_SET(PECI_HOST_STS, 1) )) && (TF1 == 0) ) ;
	if(TF1 == 1)	//Timeout
		return 0;	//Fail
	
	if(  (PECI_HOST_STS&0x6C)!=0 ) return 0x00;
	
	PECI_FIFO_LB = PECI_FIFO ;
	PECI_FIFO_HB = PECI_FIFO ;

	// Reset Data FIFO Pointer
	SET_BIT(PECI_HOST_CTRL, 3);
	PECI_HOST_CTRL = 0x00;
	PECI_HOST_STS = 0xFE ;

	return 0x01;
	
}


void Calc_Update_PECI_Temp(void)
{

	WORD cpu_temperature ;
	BYTE temp_offset ;
	BYTE temp2;

	temp2 = PECI_Host_Access_GetTemp(0x30) ;

	/////////////////////////////////////////////////////////////////////
	// START : GETTING CPU TEMPERATURE FROM THE PECI FIRMWARE PROCEDURE
	/////////////////////////////////////////////////////////////////////
	
	if(temp2 == 0x01)
	{

		//Else we can get the temperature of the CPU from the PECI firmware procedure as follows:
		cpu_temperature =  (PECI_FIFO_HB <<8) + PECI_FIFO_LB ;
		cpu_temperature = (~cpu_temperature)+1 ;
		temp_offset = cpu_temperature>>6 ;

		if(CPUTjmax == 0)
		{
			CPUTjmax = _PECI_CPU_Tjmax;
		}


		if(temp_offset <= CPUTjmax )
		{
			CPUTemperature = ( CPUTjmax - temp_offset ) ;
		}

	}
	else
	{
		//PECI Fail
	}

	///////////////////////////////////////////////////////////////////
	// END : GETTING CPU TEMPERATURE FROM THE PECI FIRMWARE PROCEDURE
	///////////////////////////////////////////////////////////////////
		
}


// ----------------------------------------------------------------------------
// The function of PECI3.0 Read the Maximum Allowed Processor Temperature
// ----------------------------------------------------------------------------
void PECI_ReadTargetTemp(void)
{
	if(PECI_RdPkgConfig(PECI_CPU_ADDR, &PECI_readBuffer[0], PECI_Domain_0, 0, PECI_Index_TTR, 0x00, 0x00, 0x05, 0x05))
	{
		CPUTcontrol = PECI_readBuffer[2];
		CPUTjmax = PECI_readBuffer[3];
	}
	else
	{
		CPUTjmax = _PECI_CPU_Tjmax ; 
		CPUTcontrol = _PECI_CPU_Tcontrol ;
	}
	
}

// ----------------------------------------------------------------------------
// The function of PECI3.0 Thermal Margin read
// ----------------------------------------------------------------------------
void PECI_ReadThermMargin(void)
{	
    if(PECI_RdPkgConfig(PECI_CPU_ADDR, &PECI_readBuffer[0], PECI_Domain_0, 0, PECI_Index_TMR, 0x00, 0x00, 0x05, 0x05))
	//if(PECI_RdPkgConfig(_PECI_CPU_ADDR, &PECI_readBuffer[0], _PECI_Domain_0, 0, PECI_Index_PTR, 0xFF, 0x00, 0x05, 0x05))
    {
		CPUTermMargin = PECI_readBuffer[2]; 								// Integer
    }
    else
    {
        ;
    }
}