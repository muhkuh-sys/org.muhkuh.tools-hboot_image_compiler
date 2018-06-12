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
#
# Build the artifact.
#

strGroup = 'org.muhkuh.tools'
strModule = 'hboot_image_compiler'

# Split the group by dots.
aGroup = strGroup.split('.')
# Build the path for all artifacts.
strModulePath = 'targets/repository/%s/%s/%s' % ('/'.join(aGroup), strModule, PROJECT_VERSION)

strArtifact = 'hboot_image_compiler'


tArcList = atEnv.DEFAULT.ArchiveList('zip')

tArcList.AddFiles('hboot_image_compiler/hboot_image_compiler/',
    'mbs/site_scons/hboot_image_compiler/__init__.py',
    'mbs/site_scons/hboot_image_compiler/__main__.py',
    'mbs/site_scons/elf_support.py',
    'mbs/site_scons/hboot_image_compiler/hboot_image.py',
    'mbs/site_scons/hboot_image_compiler/netx90_app_iflash_image.py',
    'mbs/site_scons/hboot_image_compiler/option_compiler.py',
    'mbs/site_scons/hboot_image_compiler/patch_definitions.py',
    'mbs/site_scons/hboot_image_compiler/snippet_library.py')

tArcList.AddFiles('hboot_image_compiler/',
    'mbs/site_scons/hboot_netx4000_relaxed_patch_table.xml',
    'mbs/site_scons/hboot_netx4000_patch_table.xml',
    'mbs/site_scons/hboot_netx56_patch_table.xml',
    'mbs/site_scons/hboot_netx90_full_patch_table.xml',
    'mbs/site_scons/hboot_netx90_mpw_patch_table.xml',
    'CHANGES.txt')


strBasePath = os.path.join(strModulePath, '%s-%s' % (strArtifact, PROJECT_VERSION))
tArtifactZip = atEnv.DEFAULT.Archive('%s.zip' % strBasePath, None, ARCHIVE_CONTENTS = tArcList)
tArtifactPom = atEnv.DEFAULT.ArtifactVersion('%s.pom' % strBasePath, 'templates/pom.xml')


#----------------------------------------------------------------------------
#
# Run tests.
#

atEnvVars = {
    'NETX4000_OBJCOPY': atEnv.NETX4000['OBJCOPY'],
    'NETX4000_OBJDUMP': atEnv.NETX4000['OBJDUMP'],
    'NETX4000_READELF': atEnv.NETX4000['READELF'],

    'NETX90_OBJCOPY': atEnv.NETX90_FULL['OBJCOPY'],
    'NETX90_OBJDUMP': atEnv.NETX90_FULL['OBJDUMP'],
    'NETX90_READELF': atEnv.NETX90_FULL['READELF'],

    'ELF_NETX4000_SKIP': tElf_netx4000_skip[0].get_abspath(),
    'ELF_NETX4000_SKIPSECT': tElf_netx4000_skipsect[0].get_abspath()
}

strHbootDepackPath = 'targets/tests/bin'
tUnpackStamp = atEnv.DEFAULT.Unpack('targets/tests/.unpack_stamp', tArtifactZip, UNPACK_FOLDER=strHbootDepackPath)
tTestStamp = atEnv.DEFAULT.Tests('targets/tests/.test_stamp', 'tests/tests.py', ENVVARS=atEnvVars)
atEnv.DEFAULT.Depends(tTestStamp, tUnpackStamp)
atEnv.DEFAULT.Depends(tTestStamp, tElf_netx4000_skip)
