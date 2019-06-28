@echo off
set FLA=lua5.1.exe cli_flash.lua
set INTERFACE=-p %2
set ROOTDIR=%3
set DATADIR=%ROOTDIR%\targets\tests\output\netx90_app_image\


if "%1"=="erase" goto erase
if "%1"=="com_rev3" goto flash_com_rev3
if "%1"=="com_rev4" goto flash_com_rev4
if "%1"=="app_iflash" goto flash_app_iflash
if "%1"=="app_iflash_sqi" goto flash_app_iflash_sqi

echo Usage: flash.bat  task  interface  [root_dir]
echo tasks: com_rev3, com_rev4, app_iflash, app_iflash_sqi, erase
echo interface: Name of the interface to use for flashing.
echo root_dir: Path to the cloned repository (not required for erase).
echo .
echo com_rev3: write hw config for NXHX90-JTAG Rev. 3 and a firmware to start the APP CPU.
echo com_rev4: write hw config for NXHX90-JTAG Rev. 4 and a firmware to start the APP CPU.
echo app_iflash: write single-part blinki for APP CPU (intflash2 only)
echo app_iflash_sqi: write single-part blinki for APP CPU (intflash2+SQI)
echo erase: erase internal and SQI flash
echo .
echo Note: Call this script from the directory containing cli_flash.lua
goto end


:erase
%FLA% erase %INTERFACE% -b 2 -u 3 -l 0xffffffff
if errorlevel 1 goto error

%FLA% erase %INTERFACE% -b 2 -u 2 -l 0xffffffff
if errorlevel 1 goto error

%FLA% erase %INTERFACE% -b 1 -u 0 -l 0xffffffff
if errorlevel 1 goto error
goto ok

:flash_com_rev3

echo COM CPU: NXHX90-JTAG Rev3 hardware config + start APP CPU
echo ----------------------------------------------------------
%FLA% flash %INTERFACE% -b 2 -u 0 %DATADIR%\hwc\next_chunk_hwc_nxhx90-jtag_rev3_hboot.hwc
if errorlevel 1 goto error
targets\tests\output\netx90_app_image\hwc\

echo Intflash 0 offset 0x3000: COM blinki
%FLA% flash %INTERFACE% -b 2 -u 0 -s 0x3000  %DATADIR%\netx90_COM_start_APP.nxi
if errorlevel 1 goto error
goto ok



:flash_com_rev4

echo COM CPU: NXHX90-JTAG Rev4 hardware config + start APP CPU
echo ----------------------------------------------------------
%FLA% flash %INTERFACE% -b 2 -u 0 %DATADIR%\hwc\next_chunk_hwc_nxhx90-jtag_rev4_hboot.hwc
if errorlevel 1 goto error
targets\tests\output\netx90_app_image\hwc\

echo Intflash 0 offset 0x3000: COM blinki
%FLA% flash %INTERFACE% -b 2 -u 0 -s 0x3000 %DATADIR%\netx90_COM_start_APP.nxi
if errorlevel 1 goto error
goto ok


:flash_app_iflash
echo Single-part blinki for APP CPU
echo --------------------------------
echo Intflash 2 offset 0
%FLA% flash %INTERFACE% -b 2 -u 2  %DATADIR%\netx90_app_iflash.nai
if errorlevel 1 goto error
goto ok

:flash_app_iflash_sqi
echo Two-part blinki for APP CPU (Intflash + SQI)
echo ---------------------------------------------
echo Intflash 2 offset 0
%FLA% flash %INTERFACE% -b 2 -u 2  %DATADIR%\netx90_app_iflash_sdram.nai
if errorlevel 1 goto error

echo SQI offset 3 MB (0x300000)
%FLA% flash %INTERFACE% -b 1 -u 0 -s 0x300000 %DATADIR%\netx90_app_iflash_sdram.nae
if errorlevel 1 goto error
goto ok




:ok
echo ==========================
echo           DONE
echo ==========================

goto end

:error

echo ==========================
echo          FAILED
echo ==========================
exit /b 1

:end
