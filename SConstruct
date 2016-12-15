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


atInstallFiles = {
    'hboot_image_compiler/elf_support.py': 'mbs/site_scons/elf_support.py',
    'hboot_image_compiler/hboot_image.py': 'mbs/site_scons/hboot_image_compiler/hboot_image.py',
    'hboot_image_compiler/__init__.py': 'mbs/site_scons/hboot_image_compiler/__init__.py',
    'hboot_image_compiler/__main__.py': 'mbs/site_scons/hboot_image_compiler/__main__.py',
    'hboot_image_compiler/netx90_app_iflash_image.py': 'mbs/site_scons/hboot_image_compiler/netx90_app_iflash_image.py',
    'hboot_image_compiler/option_compiler.py': 'mbs/site_scons/hboot_image_compiler/option_compiler.py',
    'hboot_image_compiler/patch_definitions.py': 'mbs/site_scons/hboot_image_compiler/patch_definitions.py',
    'hboot_image_compiler/snippet_library.py': 'mbs/site_scons/hboot_image_compiler/snippet_library.py',

    'hboot_netx4000_relaxed_patch_table.xml': 'mbs/site_scons/hboot_netx4000_relaxed_patch_table.xml',
    'hboot_netx56_patch_table.xml': 'mbs/site_scons/hboot_netx56_patch_table.xml',
    'hboot_netx90_mpw_app_patch_table.xml': 'mbs/site_scons/hboot_netx90_mpw_app_patch_table.xml',
    'hboot_netx90_mpw_patch_table.xml': 'mbs/site_scons/hboot_netx90_mpw_patch_table.xml'
}

for strDst, strSrc in atInstallFiles.iteritems():
    strDstFull = os.path.join('targets/hboot_image_compiler', strDst)
    Command(strDstFull, strSrc, Copy("$TARGET", "$SOURCE"))
