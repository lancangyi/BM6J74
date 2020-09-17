/*-----------------------------------------------------------------------------
 * TITLE: CORE_FLASH.C
 *
 * Copyright (c) ITE INC. All Rights Reserved.
 *
 *---------------------------------------------------------------------------*/
 
#include "Core_Inc.h"
#include "Oem_Inc.h"

//-----------------------------------------------------------------------------
// The function start address always at 0xFE00 (refer to link file)
//-----------------------------------------------------------------------------
void FuncAt_0xFE00(void)
{
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    FlashECCode();
}


//-----------------------------------------------------------------------------
// The function of EC flash
//-----------------------------------------------------------------------------
void FlashECCode(void)
{
	_FlashCMD = 0x00;
	_SEND = 0x00;

	PM1DO = 0x33;		// ACK

 	while(1) 
  	{	
  		#if SUPPORT_SWKBC
  		if( IsFlag1(KBHISR,IBF) )
  		{
			_FlashCMD = KBHIDIR;
			continue;
		}
		#endif
		if( IsFlag0(PM1STS,P_IBF) ) continue;
		if( IsFlag0(PM1STS,P_C_D) ) continue;
		_FlashCMD = PM1DI;

		if(_SEND==1)
		{
			ECINDDR = _FlashCMD;
			_SEND = 0x00;
			continue;
		}

		if(_FlashCMD==0x01)
		{
			ECINDAR3 = 0x0F;        // Enter follow mode
   			ECINDAR2 = 0xFF;
			ECINDAR1 = 0xFE;
   			ECINDAR0 = 0x00;   		// FFFFExx = 0xFF   
   			ECINDDR = 0x00;			// SCE# high level
		}
		else if(_FlashCMD==0x02)
		{							// Send SPI command
			ECINDAR1 = 0xFD;
			_SEND = 1;
		}
		else if(_FlashCMD==0x03)
		{							// write byte to spi
			_SEND = 1;
		}
		else if(_FlashCMD==0x04)
		{	
			PM1DO=ECINDDR;			// Read byte from spi			
		}
		else if(_FlashCMD==0x05)
		{	
			ECINDAR3 = 0x00;     	//Exit follow mode
			ECINDAR2 = 0x00;
		}
		else if(_FlashCMD==0xFC)
		{	
			ExitRamCodeCommand=0xAA;
			break;
		}
		else if(_FlashCMD==0xFD)
		{
			WDTCON |= 0x01;     /* WDTRST = 1 Reset watch dog timer.*/
			WDTCON |= 0x02;     /* WDTEN  = 1 Enable watch dog.     */
       		while(1);				// Wait for watch dog time-out				
		}
		else if(_FlashCMD==0xFE)
		{	
		    //BRAM[63]=0x55;
			BRAM[60]=0x55;	//J74_001A++ 
			WDTCON |= 0x01;     /* WDTRST = 1 Reset watch dog timer.*/
			WDTCON |= 0x02;     /* WDTEN  = 1 Enable watch dog.     */
       		while(1);				// Wait for watch dog time-out
		}
 	}
	main();
}


//-----------------------------------------------------------------------------
// The function of reading SPI status ( command 0x05)
//	After this function, spi status will save to SPIReadStatus
//-----------------------------------------------------------------------------
void SPI_Read_Status(void)
{
	ECINDAR3 = 0x0F; 
 	ECINDAR2 = 0xFF;
	ECINDAR0 = 0x00;   				// FFFFExx = 0xFF  

	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;					// SCE# high level
	ECINDAR1 = 0xFD;
	ECINDDR = SPICmd_ReadStatus;	// Read status command

	SPIReadStatus = ECINDDR;		// Save status Register to SPIReadStatus
	
	ECINDAR3 = 0x00;     			//Exit follow mode
	ECINDAR2 = 0x00;
}

//-----------------------------------------------------------------------------
// The function of Write SPI status ( command 0x01)
//	After this function, the value of SPIWriteStatus will write to spi status
//-----------------------------------------------------------------------------
void SPI_Write_Status(void)
{
	ECINDAR3 = 0x0F; 
 	ECINDAR2 = 0xFF;
	ECINDAR0 = 0x00;   				// FFFFExx = 0xFF  

	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;					// SCE# high level
	ECINDAR1 = 0xFD;
	ECINDDR = SPICmd_ReadStatus;	// Read Status Register
	while(1)						// waiting spi free
	{
		if((ECINDDR&SPIStatus_BUSY)==0x00)
        {
            break;
        } 
	}								

	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;					// SCE# high level
	ECINDAR1 = 0xFD;
	ECINDDR = SPICmd_WREN;			// Write enable	
	
    if(SPIID==SSTID)
	{
		ECINDAR1 = 0xFE;
		ECINDDR = 0xFF;				// SCE# high level
		ECINDAR1 = 0xFD;
		ECINDDR = SPICmd_EWSR;		// Enable Write Status Register
	}    
	
	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;					// SCE# high level
	ECINDAR1 = 0xFD;
	ECINDDR = SPICmd_WRSR;			// Write status command
	ECINDDR = SPIWriteStatus;		// Write SPIWriteStatus to spi status register

	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;					// SCE# high level
	ECINDAR1 = 0xFD;
	ECINDDR = SPICmd_ReadStatus;	// Read Status Register
	while(1)						// waiting spi free
	{
		if((ECINDDR&SPIStatus_BUSY)==0x00)
        {
            break;
        } 
	}
	
	ECINDAR3 = 0x00;     			//Exit follow mode
	ECINDAR2 = 0x00;
}

//-----------------------------------------------------------------------------
// The function of reading SPI ID (command 0x9F)
//	After this function, spi id will save to array SPIIDBuf[] 
//-----------------------------------------------------------------------------
void SPI_Read_ID(void)
{
	ECINDAR3 = 0x0F; 
 	ECINDAR2 = 0xFF;
	ECINDAR0 = 0x00;   				// FFFFExx = 0xFF  
	
	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;					// SCE# high level
	ECINDAR1 = 0xFD;
	ECINDDR = SPICmd_ReadStatus;	// Read Status Register
	while(1)						// waiting spi free
	{
		if((ECINDDR&SPIStatus_BUSY)==0x00)
        {
            break;
        } 
	}								

	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;					// SCE# high level
	ECINDAR1 = 0xFD;
	ECINDDR = SPICmd_DeviceID;  // Manufacture ID command
	for(SPIIndex=0x00;SPIIndex<4;SPIIndex++)
	{
		SPIIDBuf[SPIIndex] = ECINDDR;
	}
	SPIID = SPIIDBuf[0];	

	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;					// SCE# high level
	ECINDAR1 = 0xFD;
	ECINDDR = SPICmd_ReadStatus;	// Read Status Register

	while(1)						// waiting spi free
	{
		if((ECINDDR&SPIStatus_BUSY)==0x00)
        {
            break;
        } 
	}
	ECINDAR3 = 0x00;     	//Exit follow mode
	ECINDAR2 = 0x00;
}

//-----------------------------------------------------------------------------
// The function of reading SPI ID (command 0xAB)
//	After this function, spi id will save to array SPIIDBuf[] 
//-----------------------------------------------------------------------------
void SPI_Read_ID_CmdAB(void)
{
	ECINDAR3 = 0x0F; 
 	ECINDAR2 = 0xFF;
	ECINDAR0 = 0x00;   				// FFFFExx = 0xFF  
	
	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;					// SCE# high level
	ECINDAR1 = 0xFD;
	ECINDDR = SPICmd_ReadStatus;	// Read Status Register
	while(1)						// waiting spi free
	{
		if((ECINDDR&SPIStatus_BUSY)==0x00)
        {
            break;
        } 
	}								

	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;					// SCE# high level
	ECINDAR1 = 0xFD;
	ECINDDR = SPICmd_RDID;		    // Read ID command
    ECINDDR = 0x00;		            // Read ID command addr2
    ECINDDR = 0x00;		            // Read ID command addr1
    ECINDDR = 0x00;		            // Read ID command addr0
    
	for(SPIIndex=0x00;SPIIndex<4;SPIIndex++)
	{
		SPIIDBuf[SPIIndex] = ECINDDR; 
	}
	SPIID = SPIIDBuf[0];	

	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;					// SCE# high level
	ECINDAR1 = 0xFD;
	ECINDDR = SPICmd_ReadStatus;	// Read Status Register

	while(1)						// waiting spi free
	{
		if((ECINDDR&SPIStatus_BUSY)==0x00)
        {
            break;
        } 
	}
	ECINDAR3 = 0x00;     	//Exit follow mode
	ECINDAR2 = 0x00;
}

//-----------------------------------------------------------------------------
// The function of Erasing SPI
//-----------------------------------------------------------------------------
void SPI_Erase(void)
{
	ECINDAR3 = 0x0F; 
 	ECINDAR2 = 0xFF;
	ECINDAR0 = 0x00;   				// FFFFExx = 0xFF  
	
	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;					// SCE# high level
	ECINDAR1 = 0xFD;
	ECINDDR = SPICmd_ReadStatus;	// Read Status Register
	while(1)						// waiting spi free
	{
		if((ECINDDR&(SPIStatus_BUSY+SPIStatus_WEL))==SPIStatus_WriteEnable)
        {
            break;
        } 
	}								

	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;					// SCE# high level
	ECINDAR1 = 0xFD;
	ECINDDR = SPIAEraseCmd;			// Send erase command
	for(SPIIndex=0x00;SPIIndex<3;SPIIndex++)
	{
		ECINDDR = SPIAddrCycle[SPIIndex];
	}								// Send address cycle

	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;					// SCE# high level

	ECINDAR1 = 0xFD;
	ECINDDR = SPICmd_ReadStatus;	// Read Status Register

	while(1)						// waiting spi free
	{
		if((ECINDDR&SPIStatus_BUSY)==0x00)
        {
            break;
        } 
	}
	ECINDAR3 = 0x00;     			//Exit follow mode
	ECINDAR2 = 0x00;
}

//-----------------------------------------------------------------------------
// The function of SPI write enable
//-----------------------------------------------------------------------------
void SPI_Write_Enable(void)
{
	ECINDAR3 = 0x0F; 
 	ECINDAR2 = 0xFF;
	ECINDAR0 = 0x00;   				// FFFFExx = 0xFF  
	
	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;					// SCE# high level
	ECINDAR1 = 0xFD;
	ECINDDR = SPICmd_ReadStatus;	// Read Status Register
	while(1)						// waiting spi free
	{
		if((ECINDDR&SPIStatus_BUSY)==0x00)
        {
            break;
        } 
	}								

	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;					// SCE# high level
	ECINDAR1 = 0xFD;
	ECINDDR = SPICmd_WREN;			// Write enable	
	
    if(SPIID==SSTID)
    {
        ECINDAR1 = 0xFE;
        ECINDDR = 0xFF;				// SCE# high level
        ECINDAR1 = 0xFD;
        ECINDDR = SPICmd_EWSR;		// Enable Write Status Register
    }
    
	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;					// SCE# high level
	ECINDAR1 = 0xFD;
	ECINDDR = SPICmd_ReadStatus;	// Read Status Register
	while(1)						// waiting spi free
	{
		if((ECINDDR&(SPIStatus_WEL+SPIStatus_BUSY))==0x02) // Check write enable and spi not busy
        {
            break;
        } 
	}

	ECINDAR3 = 0x00;     			//Exit follow mode
	ECINDAR2 = 0x00;
}

//-----------------------------------------------------------------------------
// The function of SPI write disable
//-----------------------------------------------------------------------------
void SPI_Write_Disable(void)
{
	ECINDAR3 = 0x0F; 
 	ECINDAR2 = 0xFF;
	ECINDAR0 = 0x00;   				// FFFFExx = 0xFF  
	
	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;					// SCE# high level
	ECINDAR1 = 0xFD;
	ECINDDR = SPICmd_ReadStatus;	// Read Status Register
	while(1)						// waiting spi free
	{
		if((ECINDDR&SPIStatus_BUSY)==0x00)
        {
            break;
        } 
	}								

	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;					// SCE# high level
	ECINDAR1 = 0xFD;
	ECINDDR = SPICmd_WRDI;			// Write disable	

	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;					// SCE# high level
	ECINDAR1 = 0xFD;
	ECINDDR = SPICmd_ReadStatus;	// Read Status Register
	while(1)						// waiting spi free
	{
		if((ECINDDR&(SPIStatus_WEL+SPIStatus_BUSY))==0x00) // Check write disable and spi not busy
        {
            break;
        } 
	}

	ECINDAR3 = 0x00;     			//Exit follow mode
	ECINDAR2 = 0x00;
}

//-----------------------------------------------------------------------------
// The function of other SPI write 256 bytes
//-----------------------------------------------------------------------------
void Other_SPI_Write_256Bytes(void)
{
	ECINDAR3 = 0x0F; 
 	ECINDAR2 = 0xFF;
	ECINDAR0 = 0x00;   				// FFFFExx = 0xFF  
	
	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;					// SCE# high level
	ECINDAR1 = 0xFD;
	ECINDDR = SPICmd_ReadStatus;	// Read Status Register
	while(1)						// waiting spi free
	{
		if((ECINDDR&SPIStatus_BUSY)==0x00)
        {
            break;
        } 
	}								

	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;				    // SCE# high level
	ECINDAR1 = 0xFD;
    ECINDDR = SPICmd_BYTEProgram;   // Send Program One Data Byte command

	ECINDDR = SPIAddrCycle[0];	    // For 256 bytes function limite
	ECINDDR = SPIAddrCycle[1];
	ECINDDR = SPIAddrCycle[2];
	
	SPIIndex = 0x00;
	do
	{
		ECINDDR = *SPIDataPointer;
		SPIIndex++;
		SPIDataPointerLowByte++;
	}while(SPIIndex!=0x00);		    // Send 256 bytes

	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;					// SCE# high level
	ECINDAR1 = 0xFD;
	ECINDDR = SPICmd_ReadStatus;	// Read Status Register
	while(1)						// waiting spi free
	{
		if((ECINDDR&SPIStatus_BUSY)==0x00)
        {
            break;
        } 
	}	

	ECINDAR3 = 0x00;     			// Exit follow mode
	ECINDAR2 = 0x00;				// For 256 bytes function limite
}

//-----------------------------------------------------------------------------
// The function of SST SPI write 256 bytes (for Word AAI command)
//-----------------------------------------------------------------------------
void SST_SPI_Write_256Bytes(void)
{
	ECINDAR3 = 0x0F; 
 	ECINDAR2 = 0xFF;
	ECINDAR0 = 0x00;   				// FFFFExx = 0xFF  
	
	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;					// SCE# high level
	ECINDAR1 = 0xFD;
	ECINDDR = SPICmd_ReadStatus;	// Read Status Register
	while(1)						// waiting spi free
	{
		if((ECINDDR&SPIStatus_BUSY)==0x00)
        {
            break;
        } 
	}								

	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;				    // SCE# high level
	ECINDAR1 = 0xFD;
    ECINDDR = SPICmd_AAIWordProgram;    // Auto Address Increment Programming

	ECINDDR = SPIAddrCycle[0];	    // For 256 bytes function limite
	ECINDDR = SPIAddrCycle[1];
	ECINDDR = SPIAddrCycle[2];
	
	SPIIndex = 0x00;
	do
	{ 
		ECINDDR = *SPIDataPointer;
		SPIIndex++;
		SPIDataPointerLowByte++;

	    if((SPIIndex%2)==0x00)
	    {
		    ECINDAR1 = 0xFE;
		    ECINDDR = 0xFF;					// SCE# high level
		    ECINDAR1 = 0xFD;
		    ECINDDR = SPICmd_ReadStatus;	// Read Status Register
		    while(1)						// waiting spi free
		    {
			    if((ECINDDR&SPIStatus_BUSY)==0x00)
        	    {
            	    break;
                } 
		    }	
                
            if(SPIIndex!=0x00)
            {
		        ECINDAR1 = 0xFE;
		        ECINDDR = 0xFF;						    // SCE# high level
		        ECINDAR1 = 0xFD;
		        ECINDDR = SPICmd_AAIWordProgram;		// Auto Address Increment Programming
            }
	    }
	}while(SPIIndex!=0x00);					// Send 256 bytes

	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;				    // SCE# high level
	ECINDAR1 = 0xFD;
    ECINDDR = SPICmd_WRDI;          // Write disable

    WNCKR = 0x00;                   // Delay 15.26 us
    WNCKR = 0x00;                   // Delay 15.26 us
    WNCKR = 0x00;                   // Delay 15.26 us
    WNCKR = 0x00;                   // Delay 15.26 us

	ECINDAR3 = 0x00;     			// Exit follow mode
	ECINDAR2 = 0x00;				// For 256 bytes function limite
}

//-----------------------------------------------------------------------------
// The function of old SST SPI write 256 bytes
//-----------------------------------------------------------------------------
void Old_SST_SPI_Write_256Bytes(void)
{
	ECINDAR3 = 0x0F; 
 	ECINDAR2 = 0xFF;
	ECINDAR0 = 0x00;   				// FFFFExx = 0xFF  
	
	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;					// SCE# high level
	ECINDAR1 = 0xFD;
	ECINDDR = SPICmd_ReadStatus;	// Read Status Register
	while(1)						// waiting spi free
	{
		if((ECINDDR&SPIStatus_BUSY)==0x00)
        {
            break;
        } 
	}								

	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;				    // SCE# high level
	ECINDAR1 = 0xFD;
    ECINDDR = SPICmd_AAIProgram;    // Auto Address Increment Programming

	ECINDDR = SPIAddrCycle[0];	    // For 256 bytes function limite
	ECINDDR = SPIAddrCycle[1];
	ECINDDR = SPIAddrCycle[2];
	
	SPIIndex = 0x00;
	do
	{
		ECINDDR = *SPIDataPointer;
		SPIIndex++;
		SPIDataPointerLowByte++;

	    ECINDAR1 = 0xFE;
	    ECINDDR = 0xFF;					// SCE# high level
	    ECINDAR1 = 0xFD;
	    ECINDDR = SPICmd_ReadStatus;	// Read Status Register
	    while(1)						// waiting spi free
	    {
		    if((ECINDDR&SPIStatus_BUSY)==0x00)
            {
                break;
            } 
	    }	

        if(SPIIndex!=0x00)
        {
	        ECINDAR1 = 0xFE;
	        ECINDDR = 0xFF;			    // SCE# high level
	        ECINDAR1 = 0xFD;       
            ECINDDR = SPICmd_AAIProgram;    // Auto Address Increment Programming
        }
	}while(SPIIndex!=0x00);		    // Send 256 bytes

	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;				    // SCE# high level
	ECINDAR1 = 0xFD;
    ECINDDR = SPICmd_WRDI;          // Write disable


    WNCKR = 0x00;                   // Delay 15.26 us
    WNCKR = 0x00;                   // Delay 15.26 us
    WNCKR = 0x00;                   // Delay 15.26 us
    WNCKR = 0x00;                   // Delay 15.26 us
	//ECINDAR1 = 0xFE;
	//ECINDDR = 0xFF;					// SCE# high level
	//ECINDAR1 = 0xFD;
	//ECINDDR = SPICmd_ReadStatus;	// Read Status Register
	//while(1)						// waiting spi free
	//{
	//	if((ECINDDR&(SPIStatus_BUSY+SSTSPIStatus_AAI))==0x00)
    //    {
    //        break;
    //    } 
	//}	

	ECINDAR3 = 0x00;     			// Exit follow mode
	ECINDAR2 = 0x00;				// For 256 bytes function limite
}






//-----------------------------------------------------------------------------
// The function of SPI write 256 bytes
//-----------------------------------------------------------------------------
void SPI_Write_256Bytes(void)
{
    if(SPIID==SSTID)
    {
        if(SSTDeviceID==SSTID_Old) 
        {
            LoadSPIFucnToRam(Old_SST_SPI_Write_256Bytes);   // Load function to ram
        }
        else
        {
	        LoadSPIFucnToRam(SST_SPI_Write_256Bytes);	// Load function to ram
        }
    }
    else
    {
	    LoadSPIFucnToRam(Other_SPI_Write_256Bytes);	// Load function to ram
    }  
}




//-----------------------------------------------------------------------------
// The function of SPI read 256 bytes
//-----------------------------------------------------------------------------
void SPI_Read_256Bytes(void)
{
	ECINDAR3 = 0x0F; 
 	ECINDAR2 = 0xFF;
	ECINDAR0 = 0x00;   				// FFFFExx = 0xFF  
	
	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;					// SCE# high level
	ECINDAR1 = 0xFD;
	ECINDDR = SPICmd_ReadStatus;	// Read Status Register
	while(1)						// waiting spi free
	{
		if((ECINDDR&SPIStatus_BUSY)==0x00)
        {
            break;
        } 
	}								

	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;						// SCE# high level
	ECINDAR1 = 0xFD;
	ECINDDR = SPICmd_HighSpeedRead;		// High-Speed Read

	ECINDDR = SPIAddrCycle[0];			// For 256 bytes function limite
	ECINDDR = SPIAddrCycle[1];
	ECINDDR = SPIAddrCycle[2];
	ECINDDR = 0x00;						// dummy byte
	
	SPIIndex = 0x00;
	do
	{
		*SPIDataPointer = ECINDDR;;
		SPIIndex++;
		SPIDataPointerLowByte++;
	}while(SPIIndex!=0x00);					// Send 256 bytes

	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;					// SCE# high level
	ECINDAR1 = 0xFD;
	ECINDDR = SPICmd_ReadStatus;	// Read Status Register
	while(1)						// waiting spi free
	{
		if((ECINDDR&SPIStatus_BUSY)==0x00)
        {
            break;
        } 
	}	

	ECINDAR3 = 0x00;     			// Exit follow mode
	ECINDAR2 = 0x00;				// For 256 bytes function limite
}





//-----------------------------------------------------------------------------
// The function of loading function to external ram 0x600 ~ 0x6FF
//										LoadSPIFucnToRam_Address in Core_Flash.h
//-----------------------------------------------------------------------------
void LoadSPIFucnToRam(FUNCT_PTR_V_V funcpoint)
{
	Tmp_XPntr = LoadSPIFucnToRam_Address;
	Tmp_code_pointer = funcpoint;

	_R2= 0x00;
	do
	{
		*Tmp_XPntr = *Tmp_code_pointer;
		Tmp_XPntr++;
   		Tmp_code_pointer++;
		_R2++;
	}while(_R2!=0x00);

}

//-----------------------------------------------------------------------------
// The function for ITE flash utility
//-----------------------------------------------------------------------------
#pragma ot(7, SIZE)
void ITE_Flash_Utility(void)
{
	DisableAllInterrupt();				// Disable all interrupt 
	LoadSPIFucnToRam(FlashECCode);		// Load function to ram
	SET_MASK(FBCFG,SSMC);       		// enable scatch ROM
	FuncAt_0xFE00();					// do function in extern ram 0x600
}


//*****************************************************************************
// OEM FUNCTION CALL
//*****************************************************************************
//-----------------------------------------------------------------------------
// The function for oem code write spi status
//-----------------------------------------------------------------------------
#pragma ot(7, SIZE)
void Do_SPI_Write_Status(BYTE statusvalue)
{
	SPIWriteStatus = statusvalue;
	
	DisableAllInterrupt();				// Disable all interrupt 
	LoadSPIFucnToRam(SPI_Write_Status);	// Load function to ram
	SET_MASK(FBCFG,SSMC);       		// enable scatch ROM
	FuncAt_0xFE00();					// do function in extern ram 0x600
	EnableAllInterrupt();				// Enable all interrupt 
	CLEAR_MASK(FBCFG,SSMC);       		// disable scatch ROM
}

//-----------------------------------------------------------------------------
// The function for oem code read spi status
//		Note : SPI status always save to SPIReadStatus
//-----------------------------------------------------------------------------
#pragma ot(7, SIZE)
void Do_SPI_Read_Status(void)
{
	DisableAllInterrupt();				// Disable all interrupt 
	LoadSPIFucnToRam(SPI_Read_Status);	// Load function to ram
	SET_MASK(FBCFG,SSMC);       		// enable scatch ROM
	FuncAt_0xFE00();					// do function in extern ram 0x600
	EnableAllInterrupt();				// Enable all interrupt 
	CLEAR_MASK(FBCFG,SSMC);       		// disable scatch ROM
}

//-----------------------------------------------------------------------------
// The function for oem code read spi ID (command 0x9F)   
//		Note : SPI ID always save to array SPIIDBuf[]
//-----------------------------------------------------------------------------
#pragma ot(7, SIZE)
void Do_SPI_Read_ID(void)
{
	DisableAllInterrupt();			// Disable all interrupt 
	LoadSPIFucnToRam(SPI_Read_ID);	// Load function to ram
	SET_MASK(FBCFG,SSMC);       	// enable scatch ROM
	FuncAt_0xFE00();				// do function in extern ram 0x600
	EnableAllInterrupt();		    // Enable all interrupt 
	CLEAR_MASK(FBCFG,SSMC);         // disable scatch ROM
}

//-----------------------------------------------------------------------------
// The function for oem code read spi ID (command 0xAB)
//		Note : SPI ID always save to array SPIIDBuf[]
//-----------------------------------------------------------------------------
#pragma ot(7, SIZE)
void Do_SPI_Read_ID_CmdAB(void)
{
	DisableAllInterrupt();			// Disable all interrupt 
	LoadSPIFucnToRam(SPI_Read_ID_CmdAB);	// Load function to ram
	SET_MASK(FBCFG,SSMC);       	// enable scatch ROM
	FuncAt_0xFE00();				// do function in extern ram 0x600
	EnableAllInterrupt();		    // Enable all interrupt 
	CLEAR_MASK(FBCFG,SSMC);         // disable scatch ROM
}

//-----------------------------------------------------------------------------
// The function for oem code erase spi
//		Input : 1 EraseCmd --> Only support SPICmd_Erase4KByte, 
//								SPICmd_Erase32KByte, and SPICmd_Erase64KByte.
//				2 Addr2	   --> A23 ~ A16
//				3 Addr1	   --> A15 ~ A8
//				4 Addr0	   --> A7  ~ A0
//-----------------------------------------------------------------------------
#pragma ot(7, SIZE)
void Do_SPI_Erase(BYTE EraseCmd, BYTE Addr2, BYTE Addr1, BYTE Addr0)
{
	SPIAEraseCmd = EraseCmd;
	SPIAddrCycle[0] = Addr2;
	SPIAddrCycle[1] = Addr1;
	SPIAddrCycle[2] = Addr0;
			
	DisableAllInterrupt();			// Disable all interrupt 
	LoadSPIFucnToRam(SPI_Erase);	// Load function to ram
	SET_MASK(FBCFG,SSMC);       	// enable scatch ROM
	FuncAt_0xFE00();				// do function in extern ram 0x600
	EnableAllInterrupt();		    // Enable all interrupt 
	CLEAR_MASK(FBCFG,SSMC);         // disable scatch ROM
}

//-----------------------------------------------------------------------------
// The function for oem code write spi 256 bytes
//		Input : 1 DataPointer --> Pointe to external memory
//				2 Addr2	   --> A23 ~ A16
//				3 Addr1	   --> A15 ~ A8
//				4 Addr0	   --> A7  ~ A0
//-----------------------------------------------------------------------------
#pragma ot(7, SIZE)
void Do_SPI_Write_256Bytes(XBYTE *DataPointer, BYTE Addr2, BYTE Addr1, BYTE Addr0)
{
	SPIDataPointer = DataPointer;
	SPIAddrCycle[0] = Addr2;
	SPIAddrCycle[1] = Addr1;
	SPIAddrCycle[2] = Addr0;
			
	DisableAllInterrupt();				// Disable all interrupt 
	SPI_Write_256Bytes();               // Load function to ram
	SET_MASK(FBCFG,SSMC);       		// enable scatch ROM
	FuncAt_0xFE00();					// do function in extern ram 0x600
	EnableAllInterrupt();				// Enable all interrupt 
	CLEAR_MASK(FBCFG,SSMC);       		// disable scatch ROM
}

//-----------------------------------------------------------------------------
// The function for oem code read spi 256 bytes to external memory
//		Input : 1 DataPointer --> Pointe to external memory
//				2 Addr2	   --> A23 ~ A16
//				3 Addr1	   --> A15 ~ A8
//				4 Addr0	   --> A7  ~ A0
//-----------------------------------------------------------------------------
#pragma ot(7, SIZE)
void Do_SPI_Read_256Bytes(XBYTE *DataPointer, BYTE Addr2, BYTE Addr1, BYTE Addr0)
{
	SPIDataPointer = DataPointer;
	SPIAddrCycle[0] = Addr2;
	SPIAddrCycle[1] = Addr1;
	SPIAddrCycle[2] = Addr0;
			
	DisableAllInterrupt();				// Disable all interrupt 
	LoadSPIFucnToRam(SPI_Read_256Bytes);	// Load function to ram
	SET_MASK(FBCFG,SSMC);       		// enable scatch ROM
	FuncAt_0xFE00();					// do function in extern ram 0x600
	EnableAllInterrupt();				// Enable all interrupt 
	CLEAR_MASK(FBCFG,SSMC);       		// disable scatch ROM
}



//-----------------------------------------------------------------------------
// The function for oem code spi write enable
//-----------------------------------------------------------------------------
#pragma ot(7, SIZE)
void Do_SPI_Write_Enable(void)
{
	DisableAllInterrupt();				// Disable all interrupt 
	LoadSPIFucnToRam(SPI_Write_Enable);	// Load function to ram
	SET_MASK(FBCFG,SSMC);       		// enable scatch ROM
	FuncAt_0xFE00();					// do function in extern ram 0x600
	EnableAllInterrupt();				// Enable all interrupt 
	CLEAR_MASK(FBCFG,SSMC);       		// disable scatch ROM
}

//-----------------------------------------------------------------------------
// The function for oem code spi write disable
//-----------------------------------------------------------------------------
#pragma ot(7, SIZE)
void Do_SPI_Write_Disable(void)
{
	DisableAllInterrupt();				// Disable all interrupt 
	LoadSPIFucnToRam(SPI_Write_Disable);	// Load function to ram
	SET_MASK(FBCFG,SSMC);       		// enable scatch ROM
	FuncAt_0xFE00();					// do function in extern ram 0x600
	EnableAllInterrupt();				// Enable all interrupt 
	CLEAR_MASK(FBCFG,SSMC);       		// disable scatch ROM
}




//-----------------------------------------------------------------------------
//				2 Addr2	   --> A23 ~ A16
//				3 Addr1	   --> A15 ~ A8
//				4 Addr0	   --> A7  ~ A0
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
// The example of reading SPI ROM 0x010000 ~ 0x0100FF to external ram 0x200 ~ 0x2FF
//----------------------------------------------------------------------------

void OEM_Read_SPI_256Bytes(BYTE Addr2, BYTE Addr1, BYTE Addr0)
{
	Do_SPI_Read_256Bytes(0x800,Addr2,Addr1,Addr0);
	//Note: 0x800 is buffer Ram address
}


//----------------------------------------------------------------------------
// The example of writing external ram 0x200 ~ 0x2FF to SPI ROM 0x010000 ~ 0x0100FF
//----------------------------------------------------------------------------
void OEM_Write_SPI_256Bytes(BYTE Addr2, BYTE Addr1, BYTE Addr0)
{
	Do_SPI_Write_Status(SPIStatus_UnlockAll);
	Do_SPI_Write_Enable();
	Do_SPI_Erase(SPICmd_Erase4KByte,Addr2,Addr1,Addr0);
	Do_SPI_Write_Enable();
	Do_SPI_Write_256Bytes(0x800,Addr2,Addr1,Addr0);
	Do_SPI_Write_Disable();
}


//-----------------------------------------------------------------------------
// The function of DMA for scratch sram
//
//-----------------------------------------------------------------------------
const sDMAScratchSRAM code asDMAScratchSRAM[]=
{
    { &SCAR1H, &SCAR1M, &SCAR1L },  //1024bytes(externl ram 0x800~BFF)
    { &SCAR2H, &SCAR2M, &SCAR2L },  // 512bytes(externl ram 0xC00~DFF)
    { &SCAR3H, &SCAR3M, &SCAR3L },  // 256bytes(externl ram 0xE00~EFF)
    { &SCAR4H, &SCAR4M, &SCAR4L }   // 256bytes(externl ram 0xF00~FFF)

};

//-----------------------------------------------------------------------------
void  CacheDma( BYTE sramnum, WORD addr )
{
	*asDMAScratchSRAM[sramnum].scarh = 0x80;
	
	/* high byte of function address.   */
	*asDMAScratchSRAM[sramnum].scarm = (WORD) addr >> 8;
	//*asDMAScratchSRAM[sramnum].scarm = 0xFE;	//For Test
	
	/* low byte of function address.    */
	*asDMAScratchSRAM[sramnum].scarl = (WORD) addr & 0xff;
	//*asDMAScratchSRAM[sramnum].scarl = 0x00;	//For Test
	
	/* start cache dma                  */
	*asDMAScratchSRAM[sramnum].scarh = 0x00;

}

//----------------------------------------------------------------------------
// Read SPI use EC-Indirect fast read
//----------------------------------------------------------------------------
BYTE EC_Indirect_Read_SPI(BYTE Addr2, BYTE Addr1, BYTE Addr0)
{
	BYTE itemp, SPI_Data;
	itemp = ECINDAR3;	//save ECINDAR3
	ECINDAR3 = 0;
	ECINDAR2 = Addr2;	//High Byte
	ECINDAR1 = Addr1;	//Middle Byte
	ECINDAR0 = Addr0;	//Low Byte
	SPI_Data = ECINDDR;
	ECINDAR3 = itemp;	//restore ECINDAR3

	return SPI_Data;
}


#if	COMPARE_CHECKSUM
void CalculateChecksum(void)
{
	BYTE code * data_pntr;
	
	data_pntr = 0;
	Calc_Checksum=0x00;

	while(data_pntr!=0xFFFE)        // End address ~0xFFFD
	{
		Calc_Checksum+= *data_pntr;  // To calculate checksum
		data_pntr++;

	}
	
	Calc_Checksum+=0x1FE;           // address == 0xFFFE,0xFFFF

}


WORD Get_Checksum(void)
{
	WORD code * data_pntr;

	data_pntr = 0xFFFE;
	
	return(*data_pntr);

}

void ClearSRamF(void)
{
	PORT_BYTE_PNTR byte_register_pntr;
	byte_register_pntr=0x0F00;

	while(byte_register_pntr<0x1000)// Clear external ram (0x000~0xFFF)
	{
	    *byte_register_pntr=0;
	    byte_register_pntr ++;
	}
		
}

#endif		//COMPARE_CHECKSUM