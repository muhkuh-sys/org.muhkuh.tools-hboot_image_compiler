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


import subprocess
import sys

import SCons.Script


def tests_action(target, source, env):
    strSourcePath = source[0].get_path()
    strTargetPath = target[0].get_path()

    subprocess.check_call([
        sys.executable,
        strSourcePath,
        '-v'
    ])

    # Create a test stamp.
    tFile = open(strTargetPath, 'wt')
    tFile.write('Tested "%s"...' % strSourcePath)
    tFile.close()


def tests_emitter(target, source, env):
    return target, source


def tests_string(target, source, env):
    return 'Tests %s' % target[0].get_path()


def ApplyToEnv(env):
    # ---------------------------------------------------------------------------
    #
    # Add the tests builder.
    #
    tests_act = SCons.Action.Action(tests_action, tests_string)
    tests_bld = SCons.Script.Builder(action=tests_act, emitter=tests_emitter, single_source=1)
    env['BUILDERS']['Tests'] = tests_bld
