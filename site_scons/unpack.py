# -*- coding: utf-8 -*-
# ----------------------------------------------------------------------- #
#   Copyright (C) 2017 by Christoph Thelen                                #
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
# ----------------------------------------------------------------------- #


import os
import shutil
import zipfile

import SCons.Script


def unpack_action(target, source, env):
    if not 'UNPACK_FOLDER' in env:
        raise Exception('Missing environment variable "UNPACK_FOLDER".')

    strSourcePath = source[0].get_path()
    strTargetPath = target[0].get_path()

    strUnpackFolder = env['UNPACK_FOLDER']
    if os.path.exists(strUnpackFolder):
        # Remove the unpack folder.
        shutil.rmtree(strUnpackFolder)

    # Create a new empty unpack folder.
    os.makedirs(strUnpackFolder)

    # Unpack the zip archive.
    tZip = zipfile.ZipFile(strSourcePath)
    tZip.extractall(strUnpackFolder)
    tZip.close()

    # Create an unpack stamp.
    tFile = open(strTargetPath, 'wt')
    tFile.write('Extracted "%s" to "%s"...' % (strSourcePath, strUnpackFolder))
    tFile.close()


def unpack_emitter(target, source, env):
    env.Depends(target, SCons.Node.Python.Value(env['UNPACK_FOLDER']))
    return target, source


def unpack_string(target, source, env):
    return 'Unpack %s' % target[0].get_path()


def ApplyToEnv(env):
    # ---------------------------------------------------------------------------
    #
    # Add version builder.
    #
    unpack_act = SCons.Action.Action(unpack_action, unpack_string)
    unpack_bld = SCons.Script.Builder(action=unpack_act, emitter=unpack_emitter, single_source=1)
    env['BUILDERS']['Unpack'] = unpack_bld
