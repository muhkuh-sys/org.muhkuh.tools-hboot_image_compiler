#  -*- coding: utf-8 -*-

#  ***************************************************************************
#  *   Copyright (C) 2021 by Hilscher GmbH                                   *
#  *   netXsupport@hilscher.com                                              *
#  *                                                                         *
#  *   This program is free software; you can redistribute it and/or modify  *
#  *   it under the terms of the GNU General Public License as published by  *
#  *   the Free Software Foundation; either version 2 of the License, or     *
#  *   (at your option) any later version.                                   *
#  *                                                                         *
#  *   This program is distributed in the hope that it will be useful,       *
#  *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
#  *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
#  *   GNU General Public License for more details.                          *
#  *                                                                         *
#  *   You should have received a copy of the GNU General Public License     *
#  *   along with this program; if not, write to the                         *
#  *   Free Software Foundation, Inc.,                                       *
#  *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
#  ***************************************************************************

"""
A script used to build project python package and create executable(s).
The tool can execute the following operations:
    - Clean generated files
    - Run unit tests
    - Generate Sphinx documentation
    - Create python package
    - Create executables from sources
    - Create and push a build tag
"""

import argparse
import importlib
import logging
import os
# import pathlib
import platform
import re
import shutil
import struct
import subprocess
import sys
import zipfile

import venv

from hil_nxt_hboot_image_compiler.nxt_version import get_version_strings


#########################################
# initial information and path settings #
#########################################


def get_platform():
    if platform.system() == 'Windows':
        return 'win'
    elif platform.system() == 'Linux':
        return 'linux'
    elif platform.system() == 'Darwin':
        return 'macos'
    else:
        return platform.system()


def get_architecture():
    architecture = 8 * struct.calcsize('P')
    if architecture == 64:
        return 'x86_64'
    elif architecture == 32:
        return 'x86'
    else:
        return architecture


PLATFORM = get_platform()
ARCHITECTURE = get_architecture()
PYTHON_EXECUTABLE = sys.executable
GIT_EXECUTABLE = 'git'

TOOL_NAME = 'hil_nxt_hboot_image_compiler'

ROOT_DIR = os.path.dirname(os.path.realpath(__file__))
DIST_DIR = os.path.join(ROOT_DIR, 'dist')
TMP_DIR = os.path.join(ROOT_DIR, '.tmp')
LOG_DIR = os.path.join(TMP_DIR, 'build_log')

BUILD_DIR = os.path.join(ROOT_DIR, 'build')
FILE_VERSION_INFO = os.path.join(ROOT_DIR, 'file_version_info.txt')
SETUP_PY = os.path.join(ROOT_DIR, 'setup.py')
BUILD_TOOL_DIR = os.path.join(BUILD_DIR, 'lib', TOOL_NAME)
VERSION_PY = os.path.join(BUILD_TOOL_DIR, '_version.py')
NXT_VERSION_PY = os.path.join(BUILD_TOOL_DIR, 'nxt_version.py')

EXEC_FILES = {
    'hboot_image_compiler_app': {
        'script': 'hboot_image_compiler_app_onedir.spec',
        'options': []
    },
    'hboot_image_compiler_com': {
        'script': 'hboot_image_compiler_com_onedir.spec',
        'options': []
    }
}

CLEAN_RESOURCES = [
    BUILD_DIR,
    DIST_DIR,
    os.path.join(ROOT_DIR, 'docs', '_build'),
    os.path.join(ROOT_DIR, '{}.egg-info'.format(TOOL_NAME)),
    os.path.join(ROOT_DIR, 'file_version_info.txt'),
    os.path.join(ROOT_DIR, 'MANIFEST'),
]

# for script in EXEC_FILES.keys():
#     CLEAN_RESOURCES.append(os.path.join(ROOT_DIR, '{}.spec'.format(script)))

#####################################################
# clear log dir if already exist, then re create it #
#####################################################
if os.path.exists(LOG_DIR):
    shutil.rmtree(LOG_DIR)
os.makedirs(LOG_DIR)


#################
# create logger #
#################


def create_logger():
    global logger
    logger = logging.getLogger('maker')
    logger.setLevel(logging.DEBUG)

    file_handler = logging.FileHandler(os.path.join(LOG_DIR, 'maker.log'))
    file_handler.setLevel(logging.DEBUG)

    stream_handler = logging.StreamHandler()
    stream_handler.setLevel(logging.DEBUG)

    formatter = logging.Formatter('%(asctime)s - %(name)s - %(levelname)s - %(message)s')
    file_handler.setFormatter(formatter)
    stream_handler.setFormatter(formatter)

    logger.addHandler(file_handler)
    logger.addHandler(stream_handler)
    return logger


logger = create_logger()


#######################################
# define functions and helper classes #
#######################################

class VCSHandler:
    def __init__(self, root=ROOT_DIR):
        self.root = root

    @staticmethod
    def set_tag(tag_name, commit, push_tag=False):
        """Create a new tag on a commit

        Args:
            tag_name (str): name of the tag to be created
            commit (str): commit hash (from git)
            push_tag (bool): push tag after creating it (this only works if the commit is pushed already)
        """

        logger.info("Creating tag: '{}'".format(tag_name))
        call([GIT_EXECUTABLE, 'tag', '-a', tag_name, commit, '-m', 'Created {} tag'.format(tag_name)])
        # only push tag afterwards if wanted
        if push_tag:
            VCSHandler.push_tag(tag_name)

    @staticmethod
    def push_tag(tag_name):
        """Push tag to origin

        WARNING: this only works if the current commit is also pushed to origin

        Args:
            tag_name (str): name of the tag to be pushed to git
        """

        logger.info("Pushing tag to origin: '{}'".format(tag_name))
        call([GIT_EXECUTABLE, 'push', 'origin', tag_name])


def get_version():
    """Returns output from get_version() function from '_version.py' file that is the result of setup.py build

    We get the version info from that file to ensure to get the exact same version information as the build.
    We do not want the possibility that a new tag is set during the build-process
    that results in two different versions.

    Returns:
        dict: versions dictionary
    """
    """ import verison_dict from '-version.py' file that is the result of setup.py build

    We get the version info from that file to ensure to get the exact same version information as the build.
    We do not want the possibility that a new tag is set during the build-process
     that results in two different versions.

    :return:
    """
    if os.path.exists(VERSION_PY):
        version = importlib.import_module('build.lib.{}._version'.format(TOOL_NAME), VERSION_PY)
        version_dict = version.get_versions()
    else:
        raise AttributeError("version file not found: '%s'" % VERSION_PY)
    return version_dict


def get_time_string(version_dict):
    """Parses timestamp from version dict and converts it to own format

    Args:
        version_dict (dict): Version dictionary from _version.py file

    Returns:
        str: timestamp
    """

    # get the time string from version dict
    time_regex = r"(\d{4})-(\d{1,2})-(\d{1,2})T(\d{2}):(\d{2}):(\d{2})\+(\d{4})"
    time_match = re.match(time_regex, version_dict['date'])
    if not time_match:
        raise AttributeError("invalid date stamp found in version dict '{}'".format(version_dict['date']))
    year = time_match.group(1)
    month = time_match.group(2)
    day = time_match.group(3)
    hour = time_match.group(4)
    minute = time_match.group(5)
    time_string = "%s%s%sH%s%s" % (year, month, day, hour, minute)
    version_dict['time_string'] = time_string
    return time_string


def create_build_tag(push_tag=False):
    """Creates a build tag.
    Requires the project to be built and a _version.py file generated inside the build/lib folder

    Args:
        push_tag (bool): push tag after creating it
    """

    # after building the sources get information about the build
    version_dict = get_version()
    # create tag using the version information from build
    time_string = get_time_string(version_dict)
    # set tag name
    tag_name = 'BUILD{}'.format(time_string)
    # get the commit info
    commit = version_dict['full-revisionid']
    # create the tag
    vcs_handler = VCSHandler()
    vcs_handler.set_tag(tag_name, commit, push_tag)


def create_executables(tool_names, version):
    """Creates executable(s) using PyInstaller.
    Creates file_version_info.txt using pyinstaller-versionfile

    Args:
        tool_names (list): A list of tool names to create executables of
        version (str): Version string
    """

    match = re.search(r'[^0-9]*(([0-9]+\.){2}[0-9]+).*', version)
    if not match:
        raise ValueError("Failed to extract version in the format 'major.minor.patch' from '{}'".format(version))

    short_version = match.group(1)

    for tool_name in tool_names:
        tool = EXEC_FILES[tool_name]
        script_path = tool['script']
        options = tool['options']

        if PLATFORM == 'win':
            executable_path = os.path.join(DIST_DIR, tool_name, '{}.exe'.format(tool_name))
        else:
            executable_path = os.path.join(DIST_DIR, tool_name, tool_name)
        logger.info("creating '{}'".format(executable_path))

        if PLATFORM == 'win':
            # create file version info
            version_file = "%s_info.txt" % tool_name
            yaml_file = os.path.join(ROOT_DIR, '%s.yml' % tool_name)
            command = [PYTHON_EXECUTABLE, '-m', 'pyinstaller_versionfile', yaml_file, '--outfile', version_file,
                       '--version', short_version]
            call(command)
            # INFO: version files are integrated in the spec files

        # create executable
        command = [PYTHON_EXECUTABLE, '-m', 'PyInstaller', '--clean', script_path]
        command.extend(options)
        call(command)

        if not os.path.exists(executable_path):
            raise AttributeError("executable was not created successfully '{}'".format(executable_path))


def create_executables_archive(tool_names, version):
    """Creates archive containing all generated executables

    Args:
        tool_names (list): A list of tool names to add to the archive
        version (str): Version string
    """

    zip_filename = '{0}-{1}-{2}_{3}.zip'.format(TOOL_NAME, version, PLATFORM, ARCHITECTURE)
    logger.info("creating '{}'".format(zip_filename))
    with zipfile.ZipFile(os.path.join(DIST_DIR, zip_filename), 'w', zipfile.ZIP_DEFLATED) as zip_file:
        for tool_name in tool_names:
            tool_directory = os.path.join(DIST_DIR, tool_name)

            for root, dirs, files in os.walk(tool_directory):
                arcname = os.path.relpath(root, DIST_DIR)
                logger.info("adding '{}'".format(arcname))
                zip_file.write(root, arcname)

                for file_path in files:
                    filename = os.path.join(root, file_path)
                    arcname = os.path.relpath(filename, DIST_DIR)
                    logger.info("adding '{}'".format(arcname))
                    zip_file.write(filename, arcname)


def remove_resource(path):
    """Removes file/directory resource if it exists

    Args:
        path (str): Path to resource
    """

    if os.path.exists(path):
        if os.path.isfile(path):
            logger.info("removing '{}'".format(path))
            os.remove(path)
        elif os.path.isdir(path):
            logger.info("removing '{}' (and everything under it)".format(path))
            shutil.rmtree(path)


def call(command):
    """Executes the command.
    Terminates the program if the process return code != 0.

    Args:
        command (list): Command list of strings
    """

    logger.info(' '.join(command))

    process = subprocess.Popen(command, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    with process.stdout:
        for line in iter(process.stdout.readline, b''):
            logger.info(line.decode('utf-8').strip())

    return_code = process.wait()
    if return_code != 0:
        sys.exit(return_code)


###############################################################
# define command functions to be linked directly to argparser #
###############################################################
def clean():
    """Cleans all generated files"""
    for root, dirs, files in os.walk(ROOT_DIR):
        for directory in dirs:
            if directory == '__pycache__':
                remove_resource(os.path.join(root, directory))
        for file in files:
            if file.endswith('.pyc'):
                remove_resource(os.path.join(root, file))

    for resource in CLEAN_RESOURCES:
        remove_resource(resource)


def test():  # too be added
    """Runs all unit tests"""
    call([PYTHON_EXECUTABLE, '-m', 'unittest', 'discover', '-v'])


def docs():
    """Generate Sphinx documentation"""
    call([PYTHON_EXECUTABLE, '-m', 'sphinx', '-M', 'clean', 'docs', os.path.join('docs', '_build')])
    call([PYTHON_EXECUTABLE, '-m', 'sphinx', '-M', 'html', 'docs', os.path.join('docs', '_build')])


def package(archive_format='zip'):
    """Generates python source distribution package

    Args:
        archive_format (str): Format of the archive zip or gztar
    """
    call([PYTHON_EXECUTABLE, SETUP_PY, 'sdist', '--formats', archive_format])


# noinspection PyShadowingBuiltins
def bin(tool_names):
    """Generates executable files

    Steps:
        - Builds python package
        - Gets version information from '_verison.py' file inside build folder
        - Creates file_version_info.txt using pyinstaller-versionfile
        - Creates executables using Pyinstaller
        - Creates executables archive

    Args:
        tool_names (list): A list of tool names to create executables of
    """

    # build python package
    call([PYTHON_EXECUTABLE, SETUP_PY, 'build'])

    version = get_version()['version']
    create_executables(tool_names, version)
    create_executables_archive(tool_names, version)

    # delete executables directories
    for tool_name in tool_names:
        remove_resource(os.path.join(DIST_DIR, tool_name))


def dist(build_tag=False, push_tag=False):
    """Generates release files: documentation, python package, executables

    Steps:
        - Cleans all generated files
        - Creates a new python virtual environment with all required dependencies for building
        - Runs unit tests
        - Generates Sphinx documentation
        - Generates source distribution (python package)
        - Creates executables from sources
        - Creates a build tag and push it (Optional)

    Args:
        build_tag (bool): Create tag after build was successful
        push_tag (bool): Push the build tag after it was created successfully
    """

    venv_dir = os.path.join(ROOT_DIR, '.venv')

    global PYTHON_EXECUTABLE
    if PLATFORM == 'win':
        PYTHON_EXECUTABLE = os.path.join(venv_dir, 'Scripts', 'python.exe')
    else:
        PYTHON_EXECUTABLE = os.path.join(venv_dir, 'bin', 'python')

    try:
        # logger.info("creating virtual environment '{}'".format(venv_dir))
        # # venv.create(venv_dir, clear=True)
        # venv.run([os.path.join(ROOT_DIR, ".venv")])
        # call([PYTHON_EXECUTABLE, '-m', 'ensurepip', '--upgrade', '--default-pip'])
        # call([PYTHON_EXECUTABLE, '-m', 'pip', 'install', '--upgrade', 'pip'])
        # call([PYTHON_EXECUTABLE, '-m', 'pip', 'install', '--upgrade', 'setuptools'])
        #
        # logger.info('Installing dependencies in venv')
        # call([PYTHON_EXECUTABLE, '-m', 'pip', 'install', '.[build,docs]'])

        clean()
        test()
        # docs()  # not done yet
        package()
        bin(list(EXEC_FILES.keys()))

        if build_tag:
            create_build_tag(push_tag)
    finally:
        # remove_resource(venv_dir)
        PYTHON_EXECUTABLE = sys.executable


def release(build_tag=False, push_tag=False):
    """Validates tool version and generates release files

    Steps:
        - Validate version (check if repository is dirty or the current tag is dev, eval or release)
        - Cleans all generated files
        - Creates a new python virtual environment with all required dependencies for building
        - Runs unit tests
        - Generates Sphinx documentation
        - Generates source distribution (python package)
        - Creates executables from sources
        - Creates a build tag and push it (Optional)

    Args:
        build_tag (bool): Create tag after build was successful
        push_tag (bool): Push the build tag after it was created successfully
    """

    # validate that there are no changes after the current tag
    get_version_strings()

    dist(build_tag, push_tag)


if __name__ == '__main__':
    # create argparser
    parser = argparse.ArgumentParser(
        prog='maker',
        usage='%(prog)s [options]',
        description='A tool used to build project python packages and executables.',
        epilog='Type \'%(prog)s clean|test|docs|package|bin|dist|release -h\' for more help.')

    sub_parsers = parser.add_subparsers(
        dest='command',
        metavar='clean|test|docs|package|bin|dist|release',
        help='The command to execute - clean, test, docs, package, bin, dist, or release'
    )

    # add parser for 'clean' command
    clean_parser = sub_parsers.add_parser('clean', help='Clean-up all generated files')

    # add parser for 'test' command
    test_parser = sub_parsers.add_parser('test', help='Run all unit tests')

    # add parser for 'docs' command
    docs_parser = sub_parsers.add_parser('docs', help='Generate Sphinx documentation')

    # add parser for 'package' command
    package_parser = sub_parsers.add_parser('package', help='Build a python distribution package')
    package_parser.add_argument(
        '-f', '--format',
        choices=['gztar', 'zip'],
        default='zip',
        help='Format of the python package. Choose from: {} (default: %(default)s)'.format(['gztar', 'zip']))

    # add parser for 'bin' command
    bin_parser = sub_parsers.add_parser('bin', help='Build an executable(s) from the sources')
    bin_parser.add_argument(
        '-t', '--tool-names',
        metavar='TOOL_NAME',
        nargs='+',
        choices=list(EXEC_FILES.keys()),
        default=list(EXEC_FILES.keys()),
        help='Tools to build executable. Choose from: {} (default: all)'.format(', '.join(list(EXEC_FILES.keys()))))

    # add parser for 'dist' command
    dist_parser = sub_parsers.add_parser('dist', help='Generate release files (docs, zip, executables)')

    # add parser for 'release' command
    release_parser = sub_parsers.add_parser('release', help='Validate tool version and generate release files.')
    release_parser.add_argument(
        '-b', '--build-tag',
        action='store_true',
        default=False,
        help='Create build tag after build was successful. (default: False)')
    release_parser.add_argument(
        '-p', '--push-tag',
        action='store_true',
        default=False,
        help='Push the tag after it was created successfully. (default: False)')

    if len(sys.argv) == 1:
        parser.print_help()
        parser.exit()

    args = parser.parse_args()

    try:
        if args.command == 'clean':
            clean()
        elif args.command == 'test':
            test()
        # elif args.command == 'docs':
        #     docs()
        elif args.command == 'package':
            package(args.format)
        elif args.command == 'bin':
            bin(args.tool_names)
        elif args.command == 'dist':
            dist()
        elif args.command == 'release':
            release(args.build_tag, args.push_tag)
        else:
            parser.print_help()
            parser.exit()
    except Exception as e:
        logger.exception(e)
