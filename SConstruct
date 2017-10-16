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
    'mbs/site_scons/hboot_netx56_patch_table.xml',
    'mbs/site_scons/hboot_netx90_mpw_app_patch_table.xml',
    'mbs/site_scons/hboot_netx90_mpw_patch_table.xml',
    'CHANGES.txt')


strBasePath = os.path.join(strModulePath, '%s-%s' % (strArtifact, PROJECT_VERSION))
tArtifactZip = atEnv.DEFAULT.Archive('%s.zip' % strBasePath, None, ARCHIVE_CONTENTS = tArcList)
tArtifactPom = atEnv.DEFAULT.ArtifactVersion('%s.pom' % strBasePath, 'templates/pom.xml')


#----------------------------------------------------------------------------
#
# Run tests.
#

strHbootDepackPath = 'targets/tests/bin'
tUnpackStamp = atEnv.DEFAULT.Unpack('targets/tests/.unpack_stamp', tArtifactZip, UNPACK_FOLDER=strHbootDepackPath)
tTestStamp = atEnv.DEFAULT.Tests('targets/tests/.test_stamp', 'tests/tests.py')
atEnv.DEFAULT.Depends(tTestStamp, tUnpackStamp)
