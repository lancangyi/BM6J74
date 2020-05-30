/*----------------------------------------------------------------------------
 * TITLE: CORE_ACPI.C - ACPI Handler
 * FUNCTION:
 * SCI event generation.
 * ACPI SMBus transfer initiated by ACPI command.
 *
 * Copyright(c)1983-2009, Insyde Software Corporation. All Rights Reserved.
 *
 * You may not reproduce,distribute,publish,display,perform,modify,adapt,
 * transmit,broadcast,present,recite,release,license or otherwise exploit
 * any part of this publication in any form,by any means,without the prior
 * written permission of Insyde Software Corporation.
 *---------------------------------------------------------------------------*/
#include "CORE_INC.H"
#include "OEM_INC.H"

/*-----------------------------------------------------------------------------
 * Local Parameter Definition
 *---------------------------------------------------------------------------*/
#define T_PMC2_Burst_Loop        250

//-----------------------------------------------------------------------------
// ACPI Spec.13 ACPI Embedded Controller Interface Specification
// Embedded Controller Command
// Read Embedded Controller (RD_EC) 0x80
// Write Embedded Controller (WR_EC) 0x81
// Burst Enable Embedded Controller (BE_EC) 0x82
// Burst Disable Embedded Controller (BD_EC) 0x83
// Query Embedded Controller (QR_EC) 0x84
// Process Command/Data received from System via the 2nd Host interface
//-----------------------------------------------------------------------------
void Service_PCI3(void)
{
    if ( IsFlag0(PM2STS, IBF1) )  return;
    PMC2_vSetTotalBurstTime();   // Set Burst mode total time (2ms)
    Service_PCI3_Main();    // Process Command/Data

}

//-----------------------------------------------------------------------------
// ACPI EC Command 0x80:
// ACPI Spec.13.3.1 Read Embedded Controller, RD_EC (0x80)
// Read Command (3 Bytes) -- First Bytes: Port 66H <-0x80
// Byte #1 (Command byte Header) Interrupt on IBF=0
//-----------------------------------------------------------------------------
void EC686C_CMD_80(void)
{
    //SCI_RESPONSE();     // Interrupt on IBF=0
    PM2Step = _PM2_STEP_1;

}

//-----------------------------------------------------------------------------
// ACPI Spec.13.3.1 Read Embedded Controller, RD_EC (0x80)
// Second Bytes: Port 62H -> Address Index (EC Space)
// Byte #2 (Address byte to read) No Interrupt
//-----------------------------------------------------------------------------
void EC68_DATA_STEP1(void)
{   // Byte #3 (Data read to host)
    // PM1DO = ACPI Sepc.13.2.3 Embedded Controller Data, EC_DATA (R/W)
    PM2Data1 = PMC2_Read_MapECSpace(PM2Data);
    PM2DO = PM2Data1;
//    SCI_RESPONSE();     // Interrupt on OBF=1
    #if En_Record68
    RamDebug(PM2Data1);
    #endif
    PM2Step = 0;
}

//-----------------------------------------------------------------------------
// ACPI EC Command 0x81:
// ACPI Spec.13.3.2 Write Embedded Controller, WR_EC (0x81)
// Write Command (3 Bytes) -- First Bytes: Port 66H <-0x81
// Byte #1 (Command byte Header) Interrupt on IBF=0
//-----------------------------------------------------------------------------
void EC686C_CMD_81(void)
{
//    SCI_RESPONSE();     // Interrupt on IBF=0
    PM2Step = _PM2_STEP_2;

}

//-----------------------------------------------------------------------------
// ACPI Spec.13.3.2 Write Embedded Controller, WR_EC (0x81)
// Second Bytes: Port 62H -> Address Index (EC Space)
// Byte #2 (Address byte to write) Interrupt on IBF=0
//-----------------------------------------------------------------------------
void EC68_DATA_STEP2(void)
{
    PM2Data1=PM2Data;   //  Byte #2 Save Address Index
//    SCI_RESPONSE();     // Interrupt on OBF=1
    PM2Step = _PM2_STEP_3;
//AGA-Kernel>>

//AGA-Kernel<<   	
}

//-----------------------------------------------------------------------------
// ACPI Spec.13.3.2 Write Embedded Controller, WR_EC (0x81)
// Third Bytes: Port 62H -> Data Write to Address Index (EC Space)
// Byte #3 (data byte to write) Interrupt on IBF=0
//-----------------------------------------------------------------------------
void EC68_DATA_STEP3(void)
{   // Byte #3 (Data read to host)
//    SCI_RESPONSE(); // Interrupt on OBF=1
    PMC2_Write_MapECSpace( PM2Data1,PM2Data );
    PM2Step = 0;
}

//-----------------------------------------------------------------------------
// ACPI EC Command 0x82:
// ACPI Spec.13.3.3 Burst Enable Embedded Controller, BE_EC (0x82)
// Burst Enable Command (2 Bytes)
// Byte #1 (Command byte Header) No Interrupt
// The Embedded Controller sets the Burst bit of the Embedded Controller
// Status Register, puts the Burst Acknowledge byte (0x90) into the SCI output
// buffer, sets the OBF bit, and generates an SCI to signal OSPM that it is
// in Burst mode.
//-----------------------------------------------------------------------------
void EC686C_CMD_82(void)
{
    SET_BIT(PM2STS,4);  // PM1STS.4 Set Burst mode flag
    PM2DO = 0x90;       // Byte #2 (Burst acknowledge byte)
    OS_PMC2_Mode = 1;   // Auto Set ACPI Mode if Host Do ECCmd82
//    SCI_RESPONSE();     // Interrupt on IBF=0
    #if En_Record68
    RamDebug(0x90);
    #endif

}

//-----------------------------------------------------------------------------
// ACPI EC Command 0x83:
// ACPI Spec.13.3.4 Burst Disable Embedded Controller, BD_EC (0x83)
// Burst Disable Command (1 Byte)
// Byte #1 (Command byte Header) Interrupt on IBF=0
//-----------------------------------------------------------------------------
void EC686C_CMD_83(void)
{
    CLEAR_BIT(PM2STS,4);    /* PM1STS.4 Set Burst mode flag.        */
    /*  Clear Burst bit in secondary Host interface status register.*/
//    SCI_RESPONSE();         /* Interrupt on IBF=0.                  */

}

//-----------------------------------------------------------------------------
// Burst mode or normal mode
//-----------------------------------------------------------------------------
bit PMC2_CheckBurstMode(void)
{
    WORD BurstLoopOut;

    BurstLoopOut = T_PMC2_Burst_Loop;

    while((PM2STS&0x02)==0x00)
    {
        BurstLoopOut--;
        if( TF1 || (BurstLoopOut==0) )  // Time-Out
        {
            ClearFlag( PM2STS,BURST );
            //SCI_RESPONSE();     // Generate Interrupt
            TF1=0;
            return(0);
        }
    }
    return(1);

}

//-----------------------------------------------------------------------------
// Set Burst mode total time (1ms)
//-----------------------------------------------------------------------------
void PMC2_vSetTotalBurstTime(void)
{
    ET1 = 0;                        // Disable timer1 interrupt
    TH1 = (T_ACPI_BurstTime)>>8;    // Set timer1 counter 2ms
    TL1 = (T_ACPI_BurstTime);       // Set timer1 counter 2ms
    TR1 = 1;                        // Enable timer1
    TF1 = 0;                        // Clear overflow flag
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
const FUNCT_PTR_V_V code EC686CCmd8X_Table[16] =
{
    EC686C_CMD_80,          // Process ACPI command 80
    EC686C_CMD_81,          // Process ACPI command 81
    EC686C_CMD_82,          // Process ACPI command 82
    EC686C_CMD_83,          // Process ACPI command 83
    EC686C_CMD_84,          // Process ACPI command 84
    EC686C_CMD_85,          // Process ACPI command 85
    EC686C_CMD_86,          // Process ACPI command 86
    EC686C_CMD_87,          // Process ACPI command 87
    EC686C_CMD_88,          // Process ACPI command 88
    EC686C_CMD_89,          // Process ACPI command 89
    EC686C_CMD_8A,          // Process ACPI command 8A
    EC686C_CMD_8B,          // Process ACPI command 8B
    EC686C_CMD_8C,          // Process ACPI command 8C
    EC686C_CMD_8D,          // Process ACPI command 8D
    EC686C_CMD_8E,          // Process ACPI command 8E
    EC686C_CMD_8F           // Process ACPI command 8F
};
//-----------------------------------------------------------------------------
void EC_PMC2_Cmd_8X(void)
{
    (EC686CCmd8X_Table[PM2Cmd&0x0F])();
}
//-----------------------------------------------------------------------------
// Process Command/Data received from System via the 2nd Host interface
//-----------------------------------------------------------------------------
const FUNCT_PTR_V_V code Port6C_Table[16] =
{
    EC_PMC2_Cmd_0X,          // Process ACPI command 0x
    EC_PMC2_Cmd_1X,          // Process ACPI command 1x
    EC_PMC2_Cmd_2X,          // Process ACPI command 2x
    EC_PMC2_Cmd_3X,          // Process ACPI command 3x
    EC_PMC2_Cmd_4X,          // Process ACPI command 4x
    EC_PMC2_Cmd_5X,          // Process ACPI command 5x
    EC_PMC2_Cmd_6X,          // Process ACPI command 6x
    EC_PMC2_Cmd_7X,          // Process ACPI command 7x
    EC_PMC2_Cmd_8X,          // Process ACPI command 8x
    EC_PMC2_Cmd_9X,          // Process ACPI command 9x
    EC_PMC2_Cmd_AX,          // Process ACPI command Ax
    EC_PMC2_Cmd_BX,          // Process ACPI command Bx
    EC_PMC2_Cmd_CX,          // Process ACPI command Cx
    EC_PMC2_Cmd_DX,          // Process ACPI command Dx
    EC_PMC2_Cmd_EX,          // Process ACPI command Ex
    EC_PMC2_Cmd_FX,          // Process ACPI command Fx
};
//-----------------------------------------------------------------------------
const FUNCT_PTR_V_V code Port68_Table[16] =
{
    EC68_DATA_STEP0,    // PM1Step=0 Process ACPI EC data
    EC68_DATA_STEP1,    // PM1Step=1 Process ACPI EC data
    EC68_DATA_STEP2,    // PM1Step=2 Process ACPI EC data
    EC68_DATA_STEP3,    // PM1Step=3 Process ACPI EC data
    EC68_DATA_STEP4,    // PM1Step=4 Process ACPI EC data
    EC68_DATA_STEP5,    // PM1Step=5 Process ACPI EC data
    EC68_DATA_STEP6,    // PM1Step=6 Process ACPI EC data
    EC68_DATA_STEP7     // PM1Step=7 Process ACPI EC data
};
//-----------------------------------------------------------------------------
// Service Embedded Controller Interface
//-----------------------------------------------------------------------------
void Service_PCI3_Main(void)
{

    do
    {   // PM2STS = Embedded Controller Status, EC_SC (R)
        if ( PM2STS & C_D1 )  // CMD:1=Byte in data register is a command byte
        {
            PM2Cmd  = PM2DI; // Load command from Port Buffer
            PM2Step = 0;

            #if SUPPORTED_RECORDER
            if(En_Record6C )
            {
                RamDebug(0x6C); RamDebug(PM2Cmd);
            }
            #endif

            (Port6C_Table[PM2Cmd>>4])(); // Handle command

        }
        else    // CMD:0=Byte in data register is a data byte
        {
            //PM1DI,PM1DO=ACPI Sepc.13.2.3 Embedded Controller Data,EC_DATA(R/W)
            PM2Data = PM2DI;         // Load data
            if (PM2Step!=0x00)
            {
                #if SUPPORTED_RECORDER
                if(En_Record68)
                {
                    RamDebug(0x68); RamDebug(PM2Data);
                }
                #endif

                (Port68_Table[PM2Step&0x07])(); // Handle command data

            }
            else
            {
                while( ECUnProcessCnt2 < 0xFF )
                {
                    ECUnProcessCnt2++;
                }
            }
        }

    }
    while( IsFlag1(PM2STS,BURST) && PMC2_CheckBurstMode() );

    ET1 = 1;    // Enable timer1 interrupt


}
//-----------------------------------------------------------------------------

/*-----------------------------------------------------------------------------
 * End
 *---------------------------------------------------------------------------*/
