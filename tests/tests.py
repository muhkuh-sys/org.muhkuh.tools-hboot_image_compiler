import unittest

import os
import subprocess
import sys


class TestExpectedBinaries(unittest.TestCase):

    def setUp(self):
        self.strTestsBaseDir = os.path.realpath(os.path.dirname(__file__))
        self.strOutputBaseDir = os.path.realpath(os.path.join(os.path.dirname(__file__), '..', 'targets', 'tests', 'output'))
        self.strHBootImageCompiler = os.path.realpath(os.path.join(os.path.dirname(__file__), '..', 'targets', 'tests', 'bin', 'hboot_image_compiler', 'hboot_image_compiler'))
        self.strObjcopy = 'objcopy'
        self.strObjdump = 'objdump'
        self.strReadelf = 'readelf'

    def __run_hboot_image_compiler(self, strCwd, strXml, strOutput, strNetx):
        # Save the current working directory for later.
        strOldPath = os.getcwd()

        # Change to the new working directory.
        os.chdir(strCwd)

        # Run the HBOOT image compiler.
        subprocess.check_call([
            sys.executable,
            self.strHBootImageCompiler,
            '--netx-type', strNetx,
            '--objcopy', self.strObjcopy,
            '--objdump', self.strObjdump,
            '--readelf', self.strReadelf,
            strXml,
            strOutput
        ])

        # Restore the old working directory.
        os.chdir(strOldPath)

    def __test_with_reference_bin(self, strInput, strReference):
        strInputPathFull = os.path.join(self.strTestsBaseDir, strInput)
        strInputDirectoryFull = os.path.dirname(strInputPathFull)

        strOutputDirectory = os.path.dirname(strReference)

        # Create the output folder.
        strOutputDirectoryFull = os.path.join(self.strOutputBaseDir, strOutputDirectory)
        if os.path.exists(strOutputDirectoryFull) == False:
            os.makedirs(strOutputDirectoryFull)
        strOutputPathFull = os.path.join(self.strOutputBaseDir, strReference)

        # The working folder is the test path.
        strCwd = strInputDirectoryFull

        self.__run_hboot_image_compiler(strCwd, strInputPathFull, strOutputPathFull, 'NETX90_MPW')

        # Read the reference binary.
        tFile = open(os.path.join(self.strTestsBaseDir, strReference), 'rb')
        strBinReference = tFile.read()
        tFile.close()

        # Read the output.
        tFile = open(strOutputPathFull, 'rb')
        strBinOutput = tFile.read()
        tFile.close()

        self.assertEqual(strBinReference, strBinOutput)

    def test_partial_images_full(self):
        self.__test_with_reference_bin('partial_images/full.xml', 'partial_images/full.bin')

    def test_partial_images_no_header_no_end(self):
        self.__test_with_reference_bin('partial_images/no_header_no_end.xml', 'partial_images/no_header_no_end.bin')

    def test_partial_images_no_header_with_end(self):
        self.__test_with_reference_bin('partial_images/no_header_with_end.xml', 'partial_images/no_header_with_end.bin')

    def test_partial_images_with_header_no_end(self):
        self.__test_with_reference_bin('partial_images/with_header_no_end.xml', 'partial_images/with_header_no_end.bin')

    def test_skip_absolute(self):
        self.__test_with_reference_bin('skip/absolute.xml', 'skip/absolute.bin')

    def test_skip_absolute_file(self):
        self.__test_with_reference_bin('skip/absolute_file.xml', 'skip/absolute_file.bin')

    def test_skip_file(self):
        self.__test_with_reference_bin('skip/file.xml', 'skip/file.bin')

    def test_skip_file_with_fill(self):
        self.__test_with_reference_bin('skip/file_with_fill.xml', 'skip/file_with_fill.bin')

    def test_skip_relative(self):
        self.__test_with_reference_bin('skip/relative.xml', 'skip/relative.bin')

    def test_skip_relative_file(self):
        self.__test_with_reference_bin('skip/relative_file.xml', 'skip/relative_file.bin')

if __name__ == '__main__':
    unittest.main()
