@echo off

REM ***********************************************************************************************************
REM	Setting
REM ***********************************************************************************************************

path=C:\Keil\C51\BIN;.\Tools;.\Tools\NMake;

REM ***********************************************************************************************************

IF  "%1" == ""     GOTO OPTIONS
IF  "%1" == "?"    GOTO OPTIONS
IF  "%1" == "/?"   GOTO OPTIONS

:BUILDALL
del ITEEC.bin
del .\KeilMisc\Obj\Core\*.obj
del .\KeilMisc\Obj\Oem\*.obj

:BUILD
cd OEM
if not exist %1 goto NotExit
mkdir INCLUDE
copy .\%1\*.c
cd INCLUDE
copy ..\%1\INCLUDE\*.h
cd..
cd..

NMAKE .\Core\ITEEC.mak
if errorlevel 2 goto end
FU /SIZE 64 ITEEC.BIN ITEEC64.BIN FF
FU /WCS ITEEC64.bin 0000 FFFF FFFE
move ITEEC64.bin ITEEC.bin

move ITEEC.bin .\ROM
move ITEEC.ABS .\KeilMisc\obj
move ITEEC.HEX .\KeilMisc\obj
move ITEEC.SBR .\KeilMisc\obj
ren ITEEC.M51 ITEEC.MAP

cd rom
copy ITEEC.bin %1_%2.fd
cd..
move *.MAP .\KeilMisc\map

cls
FU /CHECKSUM ROM\ITEEC.bin
FU /FCHECKSUM ROM\ITEEC.bin
ECHO    ********************************************************************
ECHO    *    ITE Embedded Controller Firmware Build Process                *
ECHO    *    Copyright (c) 2006-2010, ITE Tech. Inc. All Rights Reserved.  *
ECHO    ********************************************************************
ECHO.  
ECHO    Making EC bin file successfully !!!
GOTO end


:NotExit
cls
ECHO    ********************************************************************
ECHO    *    ITE Embedded Controller Firmware Build Process                *
ECHO    *    Copyright (c) 2006-2010, ITE Tech. Inc. All Rights Reserved.  *
ECHO    ********************************************************************
ECHO.  
ECHO    Project folder isn't exit.
cd ..
GOTO done


:OPTIONS
cls
ECHO    ********************************************************************
ECHO    *    ITE Embedded Controller Firmware Build Process                *
ECHO    *    Copyright (c) 2006-2010, ITE Tech. Inc. All Rights Reserved.  *
ECHO    ********************************************************************
ECHO.    
ECHO    USAGE:  Make [P1] [P2]
ECHO                  P1 = The project name of OEM folder.
ECHO                  P2 = code version.
ECHO.
GOTO done

:end
cd OEM
del *.c
rd /S /Q INCLUDE
cd..

:done
pause

@echo on