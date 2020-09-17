
COREInclude=Core\Include\*.H
OEMInclude=Oem\Include\*.H
CDirectives=LA WL(1) CD OT(9, size) NOAREGS OR INCDIR(.\Core\Include\;.\Oem\Include\)
#CDirectives1=LA WL(1) CD OT(9, size) NOAREGS OR SRC INCDIR(.\Core\Include\;.\Oem\Include\)
#CDirectives2=LA WL(1) CD OT(8, size) NOAREGS OR INCDIR(.\Core\Include\;.\Oem\Include\)
ADirectives=SET (LA) DEBUG EP
CC=C51
AS=A51

ALL:ITEEC.BIN

#------------------------------------------------------------------
# Hex file to bin file
#------------------------------------------------------------------
ITEEC.BIN:ITEEC.HEX
	Hex2bin -s 0x0000 -k 2 ITEEC.HEX 


ITEEC.HEX:ITEEC.ABS
	OH51 ITEEC.ABS HEXFILE (ITEEC.HEX)

#------------------------------------------------------------------
# Link all obj fils
#------------------------------------------------------------------
ITEEC.ABS:KeilMisc\Obj\Core\Core_Irq.OBJ\
			KeilMisc\Obj\Core\Core_Main.OBJ\
			KeilMisc\Obj\Core\Core_Ram.OBJ\
			KeilMisc\Obj\Core\Core_Init.OBJ\
			KeilMisc\Obj\Core\Core_module.OBJ\
			KeilMisc\Obj\Core\Core_Flash.OBJ\
			KeilMisc\Obj\Core\Core_smbus.OBJ\
			KeilMisc\Obj\Core\Core_ACPI.OBJ\
			KeilMisc\Obj\Core\Core_PMC2.OBJ\
			KeilMisc\Obj\Core\Core_PECI.OBJ\
			KeilMisc\Obj\Core\Core_UART.OBJ\
			KeilMisc\Obj\Core\CORE_PORT6064.OBJ\
			KeilMisc\Obj\Core\CORE_ITEString.OBJ\
			KeilMisc\Obj\Core\CORE_FW_VERSION.OBJ\
			KeilMisc\Obj\Core\Reg_EC.OBJ\
			KeilMisc\Obj\Oem\Oem_Main.OBJ\
			KeilMisc\Obj\Oem\Oem_Ram.OBJ\
			KeilMisc\Obj\Oem\Oem_GPIO.OBJ\
			KeilMisc\Obj\Oem\Oem_6266.OBJ\
			KeilMisc\Obj\Oem\Oem_686C.OBJ\
			KeilMisc\Obj\Oem\Oem_Power.OBJ\
			KeilMisc\Obj\Oem\Oem_CIR.OBJ\
			KeilMisc\Obj\Oem\Oem_SMBUS.OBJ\
			KeilMisc\Obj\Oem\Oem_FW_VERSION.OBJ\
			KeilMisc\Obj\Oem\Oem_Fan.OBJ\
			KeilMisc\Obj\Oem\Oem_SWKBC.OBJ\
			KeilMisc\Obj\Core\STARTUP.OBJ
	bl51 @.\core\ITE_Bank_NOBBK.L51

#------------------------------------------------------------------
# Compile core file
#------------------------------------------------------------------
KeilMisc\Obj\Core\Core_Irq.OBJ:Core\Core_Irq.c $(COREInclude) $(OEMInclude)
	$(CC) Core\Core_Irq.c $(CDirectives)
	move Core\Core_Irq.OBJ KeilMisc\Obj\Core
	move Core\Core_Irq.LST KeilMisc\Lst\Core

KeilMisc\Obj\Core\Core_Main.OBJ:Core\Core_Main.c $(COREInclude) $(OEMInclude)
	$(CC) Core\Core_Main.c $(CDirectives)
	move Core\Core_Main.OBJ KeilMisc\Obj\Core
	move Core\Core_Main.LST KeilMisc\Lst\Core

KeilMisc\Obj\Core\Core_Ram.OBJ:Core\Core_Ram.c $(COREInclude) $(OEMInclude)
	$(CC) Core\Core_Ram.c $(CDirectives)
	move Core\Core_Ram.OBJ KeilMisc\Obj\Core
	move Core\Core_Ram.LST KeilMisc\Lst\Core

KeilMisc\Obj\Core\Core_Init.OBJ:Core\Core_Init.c $(COREInclude) $(OEMInclude)
	$(CC) Core\Core_Init.c $(CDirectives)
	move Core\Core_Init.OBJ KeilMisc\Obj\Core
	move Core\Core_Init.LST KeilMisc\Lst\Core
	
KeilMisc\Obj\Core\Core_module.OBJ:Core\Core_module.c $(COREInclude) $(OEMInclude)
	$(CC) Core\Core_module.c $(CDirectives)
	move Core\Core_module.OBJ KeilMisc\Obj\Core
	move Core\Core_module.LST KeilMisc\Lst\Core

KeilMisc\Obj\Core\Core_Flash.OBJ:Core\Core_Flash.c $(COREInclude) $(OEMInclude)
	$(CC) Core\Core_Flash.c $(CDirectives)
	move Core\Core_Flash.OBJ KeilMisc\Obj\Core
	move Core\Core_Flash.LST KeilMisc\Lst\Core
	
KeilMisc\Obj\Core\Core_smbus.OBJ:Core\Core_smbus.c $(COREInclude) $(OEMInclude)
	$(CC) Core\Core_smbus.c $(CDirectives)
	move Core\Core_smbus.OBJ KeilMisc\Obj\Core
	move Core\Core_smbus.LST KeilMisc\Lst\Core

KeilMisc\Obj\Core\Core_ACPI.OBJ:Core\Core_ACPI.c $(COREInclude) $(OEMInclude)
	$(CC) Core\Core_ACPI.c $(CDirectives)
	move Core\Core_ACPI.OBJ KeilMisc\Obj\Core
	move Core\Core_ACPI.LST KeilMisc\Lst\Core

KeilMisc\Obj\Core\Core_PMC2.OBJ:Core\Core_PMC2.c $(COREInclude) $(OEMInclude)
	$(CC) Core\Core_PMC2.c $(CDirectives)
	move Core\Core_PMC2.OBJ KeilMisc\Obj\Core
	move Core\Core_PMC2.LST KeilMisc\Lst\Core

KeilMisc\Obj\Core\Core_PECI.OBJ:Core\Core_PECI.c $(COREInclude) $(OEMInclude)
	$(CC) Core\Core_PECI.c $(CDirectives)
	move Core\Core_PECI.OBJ KeilMisc\Obj\Core
	move Core\Core_PECI.LST KeilMisc\Lst\Core

KeilMisc\Obj\Core\Core_UART.OBJ:Core\Core_UART.c $(COREInclude) $(OEMInclude)
	$(CC) Core\Core_UART.c $(CDirectives)
	move Core\Core_UART.OBJ KeilMisc\Obj\Core
	move Core\Core_UART.LST KeilMisc\Lst\Core
	
KeilMisc\Obj\Core\CORE_PORT6064.OBJ:Core\CORE_PORT6064.c $(COREInclude) $(OEMInclude)
	$(CC) Core\CORE_PORT6064.c $(CDirectives)
	move Core\CORE_PORT6064.OBJ KeilMisc\Obj\Core
	move Core\CORE_PORT6064.LST KeilMisc\Lst\Core
	
KeilMisc\Obj\Core\CORE_ITEString.OBJ:Core\CORE_ITEString.c $(COREInclude) $(OEMInclude)
	$(CC) Core\CORE_ITEString.c $(CDirectives)
	move Core\CORE_ITEString.OBJ KeilMisc\Obj\Core
	move Core\CORE_ITEString.LST KeilMisc\Lst\Core
	
KeilMisc\Obj\Core\CORE_FW_VERSION.OBJ:Core\CORE_FW_VERSION.c $(COREInclude) $(OEMInclude)
	$(CC) Core\CORE_FW_VERSION.c $(CDirectives)
	move Core\CORE_FW_VERSION.OBJ KeilMisc\Obj\Core
	move Core\CORE_FW_VERSION.LST KeilMisc\Lst\Core

KeilMisc\Obj\Core\Reg_EC.OBJ:Core\Reg_EC.c $(COREInclude) $(OEMInclude)
	$(CC) Core\Reg_EC.c $(CDirectives)
	move Core\Reg_EC.OBJ KeilMisc\Obj\Core
	move Core\Reg_EC.LST KeilMisc\Lst\Core

	
#------------------------------------------------------------------
#
#------------------------------------------------------------------

KeilMisc\Obj\Core\STARTUP.OBJ:Core\STARTUP.A51
	$(AS) Core\STARTUP.A51 $(ADirectives)
	move Core\STARTUP.OBJ KeilMisc\Obj\Core
	move Core\STARTUP.LST KeilMisc\Lst\Core

#------------------------------------------------------------------
# Compile oem file
#------------------------------------------------------------------
KeilMisc\Obj\Oem\Oem_Main.OBJ:Oem\Oem_Main.c $(COREInclude) $(OEMInclude)
	$(CC) Oem\Oem_Main.c $(CDirectives)
	move OEM\Oem_Main.OBJ KeilMisc\Obj\Oem
	move OEM\Oem_Main.LST KeilMisc\Lst\Oem

KeilMisc\Obj\Oem\Oem_Ram.OBJ:Oem\Oem_Ram.c $(COREInclude) $(OEMInclude)
	$(CC) Oem\Oem_Ram.c $(CDirectives)
	move OEM\Oem_Ram.OBJ KeilMisc\Obj\Oem
	move OEM\Oem_Ram.LST KeilMisc\Lst\Oem

KeilMisc\Obj\Oem\Oem_GPIO.OBJ:Oem\Oem_GPIO.c $(COREInclude) $(OEMInclude)
	$(CC) Oem\Oem_GPIO.c $(CDirectives)
	move OEM\Oem_GPIO.OBJ KeilMisc\Obj\Oem
	move OEM\Oem_GPIO.LST KeilMisc\Lst\Oem

KeilMisc\Obj\Oem\Oem_6266.OBJ:Oem\Oem_6266.c $(COREInclude) $(OEMInclude)
	$(CC) Oem\Oem_6266.c $(CDirectives)
	move OEM\Oem_6266.OBJ KeilMisc\Obj\Oem
	move OEM\Oem_6266.LST KeilMisc\Lst\Oem

KeilMisc\Obj\Oem\Oem_686C.OBJ:Oem\Oem_686C.c $(COREInclude) $(OEMInclude)
	$(CC) Oem\Oem_686C.c $(CDirectives)
	move OEM\Oem_686C.OBJ KeilMisc\Obj\Oem
	move OEM\Oem_686C.LST KeilMisc\Lst\Oem

KeilMisc\Obj\Oem\Oem_Power.OBJ:Oem\Oem_Power.c $(COREInclude) $(OEMInclude)
	$(CC) Oem\Oem_Power.c $(CDirectives)
	move OEM\Oem_Power.OBJ KeilMisc\Obj\Oem
	move OEM\Oem_Power.LST KeilMisc\Lst\Oem

KeilMisc\Obj\Oem\Oem_CIR.OBJ:Oem\Oem_CIR.c $(COREInclude) $(OEMInclude)
	$(CC) Oem\Oem_CIR.c $(CDirectives)
	move OEM\Oem_CIR.OBJ KeilMisc\Obj\Oem
	move OEM\Oem_CIR.LST KeilMisc\Lst\Oem
	
KeilMisc\Obj\Oem\Oem_SMBUS.OBJ:Oem\Oem_SMBUS.c $(COREInclude) $(OEMInclude)
	$(CC) Oem\Oem_SMBUS.c $(CDirectives)
	move OEM\Oem_SMBUS.OBJ KeilMisc\Obj\Oem
	move OEM\Oem_SMBUS.LST KeilMisc\Lst\Oem

KeilMisc\Obj\Oem\Oem_FW_VERSION.OBJ:Oem\Oem_FW_VERSION.c $(COREInclude) $(OEMInclude)
	$(CC) Oem\Oem_FW_VERSION.c $(CDirectives)
	move OEM\Oem_FW_VERSION.OBJ KeilMisc\Obj\Oem
	move OEM\Oem_FW_VERSION.LST KeilMisc\Lst\Oem	
	
KeilMisc\Obj\Oem\Oem_Fan.OBJ:Oem\Oem_Fan.c $(COREInclude) $(OEMInclude)
	$(CC) Oem\Oem_Fan.c $(CDirectives)
	move OEM\Oem_Fan.OBJ KeilMisc\Obj\Oem
	move OEM\Oem_Fan.LST KeilMisc\Lst\Oem

KeilMisc\Obj\Oem\Oem_SWKBC.OBJ:Oem\Oem_SWKBC.c $(COREInclude) $(OEMInclude)
	$(CC) Oem\Oem_SWKBC.c $(CDirectives)
	move OEM\Oem_SWKBC.OBJ KeilMisc\Obj\Oem
	move OEM\Oem_SWKBC.LST KeilMisc\Lst\Oem