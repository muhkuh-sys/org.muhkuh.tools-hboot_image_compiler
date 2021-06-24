# -*- coding: utf-8 -*-
#-------------------------------------------------------------------------#
#   Copyright (C) 2011 by Christoph Thelen                                #
#   doc_bacardi@users.sourceforge.net                                     #
#                                                                         #
#   This program is free software; you can redistribute it and/or modify  #
#   it under the terms of the GNU General Public License as published by  #
#   the Free Software Foundation; either version 2 of the License, or     #
#   (at your option) any later version.                                   #
#                                                                         #
#   This program is distributed in the hope that it will be useful,       #
#   but WITHOUT ANY WARRANTY; without even the implied warranty of        #
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         #
#   GNU General Public License for more details.                          #
#                                                                         #
#   You should have received a copy of the GNU General Public License     #
#   along with this program; if not, write to the                         #
#   Free Software Foundation, Inc.,                                       #
#   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             #
#-------------------------------------------------------------------------#


import os.path
import os
from datetime import datetime

#----------------------------------------------------------------------------
#
# Set up the Muhkuh Build System.
#
SConscript('mbs/SConscript')
Import('atEnv')

import tests
import unpack
tests.ApplyToEnv(atEnv.DEFAULT)
unpack.ApplyToEnv(atEnv.DEFAULT)

# Create a build environment for the Cortex-R7 and Cortex-A9 based netX chips.
env_cortexR7 = atEnv.DEFAULT.CreateEnvironment(['gcc-arm-none-eabi-4.9', 'asciidoc'])
env_cortexR7.CreateCompilerEnv('NETX4000_RELAXED', ['arch=armv7', 'thumb'], ['arch=armv7-r', 'thumb'])
env_cortexR7.CreateCompilerEnv('NETX4000', ['arch=armv7', 'thumb'], ['arch=armv7-r', 'thumb'])
env_cortexR7.CreateCompilerEnv('NETX4100', ['arch=armv7', 'thumb'], ['arch=armv7-r', 'thumb'])

# Create a build environment for the Cortex-M4 based netX chips.
env_cortexM4 = atEnv.DEFAULT.CreateEnvironment(['gcc-arm-none-eabi-4.9', 'asciidoc'])
env_cortexM4.CreateCompilerEnv('NETX90_MPW', ['arch=armv7', 'thumb'], ['arch=armv7e-m', 'thumb'])
env_cortexM4.CreateCompilerEnv('NETX90_FULL', ['arch=armv7', 'thumb'], ['arch=armv7e-m', 'thumb'])

env_cortexM4.CreateCompilerEnv('NETX90_APP', ['arch=armv7', 'thumb'], ['arch=armv7e-m', 'thumb'])

# ----------------------------------------------------------------------------
#
# Build demo ELF files.
#

# Demo contents for netX4000 skip tests.
tEnv_netx4000_skip = atEnv.NETX4000.Clone()
tEnv_netx4000_skip.Append(CPPPATH = ['src/netx4000_skip'])
tEnv_netx4000_skip.Replace(LDFILE = 'src/netx4000_skip/netx4000_cr7_intram.ld')
tSrc_netx4000_skip = tEnv_netx4000_skip.SetBuildPath('targets/netx4000_skip', 'src/netx4000_skip', ['src/netx4000_skip/init.S'])
tElf_netx4000_skip = tEnv_netx4000_skip.Elf('targets/netx4000_skip/netx4000_skip.elf', tSrc_netx4000_skip)
tTxt_netx4000_skip = tEnv_netx4000_skip.ObjDump('targets/netx4000_skip/netx4000_skip.txt', tElf_netx4000_skip, OBJDUMP_FLAGS=['--disassemble', '--source', '--all-headers', '--wide'])


# Demo contents for netX4000 skip section tests.
tEnv_netx4000_skipsect = atEnv.NETX4000.Clone()
tEnv_netx4000_skipsect.Append(CPPPATH = ['src/netx4000_skipsect'])
tEnv_netx4000_skipsect.Replace(LDFILE = 'src/netx4000_skipsect/netx4000_cr7_intram.ld')
tSrc_netx4000_skipsect = tEnv_netx4000_skipsect.SetBuildPath('targets/netx4000_skipsect', 'src/netx4000_skipsect', ['src/netx4000_skipsect/init.S'])
tElf_netx4000_skipsect = tEnv_netx4000_skipsect.Elf('targets/netx4000_skipsect/netx4000_skipsect.elf', tSrc_netx4000_skipsect)
tTxt_netx4000_skipsect = tEnv_netx4000_skipsect.ObjDump('targets/netx4000_skipsect/netx4000_skipsect.txt', tElf_netx4000_skipsect, OBJDUMP_FLAGS=['--disassemble', '--source', '--all-headers', '--wide'])

# ----------------------------------------------------------------------------
# Demo contents for netX90 app image tests.

src_netx90_app_blinki = [
    'src/netx90_app_blinki/cm4_app_vector_table_iflash.c',
    'src/netx90_app_blinki/init.S',
    'src/netx90_app_blinki/app_hboot_header_iflash.c',
    'src/netx90_app_blinki/main.c',
    'src/netx90_app_blinki/mmio6.c',
    'src/netx90_app_blinki/mmio7.c',
    'src/netx90_app_blinki/rdy_run.c',
    'src/netx90_app_blinki/systime.c'
]

def build_blinki(strTargetDir, strTargetName, strLd):
    strTargetPath = os.path.join('targets', strTargetDir)
    strTarget = os.path.join('targets', strTargetDir, strTargetName)
    strElfPath = strTarget + '.elf'
    strTxtPath = strTarget + '.txt'
    
    tEnv = atEnv.NETX90_APP.Clone()
    tEnv.Append(CPPPATH = ['src/netx90_app_blinki'])
    tEnv.Replace(LDFILE = strLd)
    tSrc = tEnv.SetBuildPath(
        strTargetPath, 
        'src/netx90_app_blinki', 
        src_netx90_app_blinki
        )
    tElf = tEnv.Elf(strElfPath, tSrc)
    tTxt = tEnv.ObjDump(strTxtPath, tElf, 
        OBJDUMP_FLAGS=['--disassemble', '--source', '--all-headers', '--wide'])
    return tElf
    
tElf_netx90_app_blinki_iflash_sdram = build_blinki(
    'netx90_app_blinki_iflash_sdram', 'netx90_app_blinki_iflash_sdram', 'src/netx90_app_blinki/link/netx90_app_iflash_sdram.ld')
    
tElf_netx90_app_blinki_iflash = build_blinki(
    'netx90_app_blinki_iflash', 'netx90_app_blinki_iflash', 'src/netx90_app_blinki/link/netx90_app_iflash.ld')

tElf_netx90_app_blinki_iflash_2part = build_blinki(
    'netx90_app_blinki_iflash_2part', 'netx90_app_blinki_iflash_2part', 'src/netx90_app_blinki/link/netx90_app_iflash_2part.ld')

tElf_netx90_app_blinki_sdram = build_blinki(
    'netx90_app_blinki_sdram', 'netx90_app_blinki_sdram', 'src/netx90_app_blinki/link/netx90_app_sdram.ld')
    

# ----------------------------------------------------------------------------
# 
# Generate the version file.
# 

tBuildTime = datetime.now()
strBuildTime = tBuildTime.strftime("%Y-%B-%d-T%H:%M")
tDict = {'BUILD_TIME': strBuildTime, 'BUILD_TYPE': '_RC1'}
version_py_tmp = atEnv.DEFAULT.Version('targets/version/hboot_image_version_tmp.py', 'templates/hboot_image_version.py')
version_py = atEnv.DEFAULT.Filter('#/targets/version/hboot_image_version.py', version_py_tmp, SUBSTITUTIONS=tDict)
    
# ----------------------------------------------------------------------------
#
# Build the artifact.
#




#----------------------------------------------------------------------------
#
# Run tests.
#

strGccPath= 'C:/ProgramData/Hilscher GmbH/netX Studio CDT/BuildTools/arm-none-eabi-gcc/4.9.3/bin'

strHbootDepackPath = 'targets/tests/bin'

atEnvVars = {
    'NETX4000_OBJCOPY': atEnv.NETX4000['OBJCOPY'],
    'NETX4000_OBJDUMP': atEnv.NETX4000['OBJDUMP'],
    'NETX4000_READELF': atEnv.NETX4000['READELF'],

    'NETX90_OBJCOPY': atEnv.NETX90_FULL['OBJCOPY'],
    'NETX90_OBJDUMP': atEnv.NETX90_FULL['OBJDUMP'],
    'NETX90_READELF': atEnv.NETX90_FULL['READELF'],
    
#    'NETX90_OBJCOPY': os.path.join(strGccPath, 'arm-none-eabi-objcopy.exe'),
#    'NETX90_OBJDUMP': os.path.join(strGccPath, 'arm-none-eabi-objdump.exe'),
#    'NETX90_READELF': os.path.join(strGccPath, 'arm-none-eabi-readelf.exe'),

    'ELF_NETX4000_SKIP': tElf_netx4000_skip[0].get_abspath(),
    'ELF_NETX4000_SKIPSECT': tElf_netx4000_skipsect[0].get_abspath(),
    
    'ELF_NETX90_APP_BLINKI_IFLASH_SDRAM': tElf_netx90_app_blinki_iflash_sdram[0].get_abspath(),
    'ELF_NETX90_APP_BLINKI_IFLASH': tElf_netx90_app_blinki_iflash[0].get_abspath(),
    'ELF_NETX90_APP_BLINKI_IFLASH_2PART': tElf_netx90_app_blinki_iflash_2part[0].get_abspath(),
    'ELF_NETX90_APP_BLINKI_SDRAM': tElf_netx90_app_blinki_sdram[0].get_abspath(), 
    
    'HBOOT_DEPACK_FOLDER': strHbootDepackPath
}


# These environment variables are required by urandom() on Windoofs, which is required by tempfile.mkstemp()
astrWinRequiredEnv = [
    'TMP', 
    'SystemRoot'
]

for k in astrWinRequiredEnv:
    if k in os.environ:
        atEnvVars[k] = os.environ[k]

# tUnpackStamp = atEnv.DEFAULT.Unpack('targets/tests/.unpack_stamp', tArtifactZip, UNPACK_FOLDER=strHbootDepackPath)
tTestStamp = atEnv.DEFAULT.Tests('targets/tests/.test_stamp', 'tests/tests.py', ENVVARS=atEnvVars)
# atEnv.DEFAULT.Depends(tTestStamp, tUnpackStamp)
atEnv.DEFAULT.Depends(tTestStamp, tElf_netx4000_skip)
atEnv.DEFAULT.Depends(tTestStamp, tElf_netx4000_skipsect)
atEnv.DEFAULT.Depends(tTestStamp, tElf_netx90_app_blinki_iflash_sdram)
atEnv.DEFAULT.Depends(tTestStamp, tElf_netx90_app_blinki_iflash)
atEnv.DEFAULT.Depends(tTestStamp, tElf_netx90_app_blinki_sdram)
