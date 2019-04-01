@echo off
setlocal

set GCCPATH=..\arm-none-eabi-gcc_4.9.3
set GCCPATH=C:\ProgramData\Hilscher GmbH\netX Studio CDT\BuildTools\arm-none-eabi-gcc\4.9.3\bin\
set OC="%GCCPATH%\arm-none-eabi-objcopy.exe"
set OD="%GCCPATH%\arm-none-eabi-objdump.exe"
set RE="%GCCPATH%\arm-none-eabi-readelf.exe"
set HIC=..\..\targets\tests\bin\hboot_image_compiler\hboot_image_compiler\netx90_app_image.py
set BD=.\build
set TD=.\Targets\NXHX90-JTAG_APP
set RD=.\reference

rem set COMPDIR="targets\tests\bin\hboot_image_compiler\hboot_image_compiler\netx90_app_image.py"

echo Build images for the version for intflash + SDRAM
python "%HIC%" ^
-c %OC% -d %OD% -r %RE% ^
-A tElf="%BD%\netx90_app_iflash_sdram.elf" ^
-A headeraddress_extflash=0x64300000 ^
-A segments_intflash=".header,.code" ^
-A segments_extflash=".code_SDRAM1,.code_SDRAM2" ^
"app_images_iflash_extflash.xml" "%BD%\netx90_app_iflash_sdram.nai" "%BD%\netx90_app_iflash_sdram.nae"
if errorlevel 1 goto failed
echo Compare build to reference files
fc /b "%BD%\netx90_app_iflash_sdram.nai" "%RD%/netx90_app_iflash_sdram.nai"
if errorlevel 1 goto failed
fc /b "%BD%\netx90_app_iflash_sdram.nae" %RD%/netx90_app_iflash_sdram.nae"
if errorlevel 1 goto failed


echo Build an image for the intflash-only version
python "%HIC%" ^
-c %OC% -d %OD% -r %RE% ^
-A tElf="%BD%\netx90_app_iflash.elf" ^
-A segments_intflash=".header,.code" ^
"app_image_iflash.xml" "%BD%\netx90_app_iflash.nai"
if errorlevel 1 goto failed
echo Compare build to reference files
fc /b "%BD%\netx90_app_iflash.nai" "%RD%/netx90_app_iflash.nai"
if errorlevel 1 goto failed


echo Build the image for the intflash-only version without explicitly listing segments.
python "%HIC%" ^
-c %OC% -d %OD% -r %RE% ^
-A tElf="%BD%\netx90_app_iflash.elf" ^
"app_image_iflash_nosegments.xml" "%BD%\netx90_app_iflash_nosegments.nai"
if errorlevel 1 goto failed
echo Compare build to reference files
fc /b "%BD%\netx90_app_iflash.nai" "%RD%/netx90_app_iflash.nai"
if errorlevel 1 goto failed

goto passed

rem usage: app_image.py [-h] [-c FILE] [-d FILE] [-r FILE] [-A ALIAS=FILE]
rem                     [-I PATH] [-k FILE] [-v]
rem                     INPUT_FILE OUTPUT_FILE [OUTPUT_FILE ...]
rem 
rem Translate an XML APP image description file.
rem 
rem positional arguments:
rem   INPUT_FILE            read the XML data from INPUT_FILE
rem   OUTPUT_FILE           write the output to OUTPUT_FILE
rem 
rem optional arguments:
rem   -h, --help            show this help message and exit
rem   -c FILE, --objcopy FILE
rem                         Use FILE as the objcopy tool.
rem   -d FILE, --objdump FILE
rem                         Use FILE as the objdump tool.
rem   -r FILE, --readelf FILE
rem                         Use FILE as the readelf tool.
rem   -A ALIAS=FILE, --alias ALIAS=FILE
rem                         Add an alias in the form ALIAS=FILE.
rem   -I PATH, --include PATH
rem                         Add PATH to the list of include paths.
rem   -k FILE, --keyrom FILE
rem                         Read the keyrom data from FILE.
rem   -s SDRAM, --sdsize SDRAM
rem                         sdram size to set the offset
rem   -v, --verbose         be verbose



:failed
echo ===========================
echo         Test FAILED 
echo ===========================
exit /b 1

:passed
echo ===========================
echo         Test PASSED 
echo ===========================
exit /b 0


:end
