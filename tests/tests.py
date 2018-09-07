import unittest

import os
import re
import shutil
import subprocess
import sys


class TestExpectedBinaries(unittest.TestCase):

    def setUp(self):
        self.strTestsBaseDir = os.path.realpath(os.path.dirname(__file__))
        self.strOutputBaseDir = os.path.realpath(os.path.join(os.path.dirname(__file__), '..', 'targets', 'tests', 'output'))
        self.strHBootImageCompiler = os.path.realpath(os.path.join(os.path.dirname(__file__), '..', 'targets', 'tests', 'bin', 'hboot_image_compiler', 'hboot_image_compiler'))

    def __get_env_var(self, tMatch):
        strEnvKey = tMatch.group(1)
        if strEnvKey not in os.environ:
            raise Exception('Referened non-existing environment variable "%s".' % strEnvKey)
        return os.environ[strEnvKey]

    def __run_hboot_image_compiler(self, strCwd, strXml, strOutput, strNetx, atExtraArguments):
        # Save the current working directory for later.
        strOldPath = os.getcwd()

        # Change to the new working directory.
        os.chdir(strCwd)

        # Run the HBOOT image compiler.
        astrCmd = [
            sys.executable,
            self.strHBootImageCompiler,
            '--netx-type', strNetx
        ]
        if atExtraArguments is not None:
            tRe = re.compile('%%([\w]+)%%')
            # Replace all ENV vars in the extra arguments.
            for strArg in atExtraArguments:
                astrCmd.append(tRe.sub(self.__get_env_var, strArg))
        astrCmd.extend([
            strXml,
            strOutput
        ])

        subprocess.check_call(astrCmd)

        # Restore the old working directory.
        os.chdir(strOldPath)

    def __test_with_reference_bin(self, strInput, strReference, strNetx, atExtraArguments, atCopyFiles):
        strInputBase = os.path.basename(strInput)
        strInputPathFull = os.path.join(self.strTestsBaseDir, strInput)
        strInputDirectoryFull = os.path.dirname(strInputPathFull)

        strOutputDirectory = os.path.dirname(strReference)

        # Create the output folder.
        strOutputDirectoryFull = os.path.join(self.strOutputBaseDir, strOutputDirectory)
        if os.path.exists(strOutputDirectoryFull) == False:
            os.makedirs(strOutputDirectoryFull)
        strOutputPathFull = os.path.join(self.strOutputBaseDir, strReference)

        # Copy files.
        if atCopyFiles is not None:
            for strFile in atCopyFiles:
                strSrcAbs = os.path.join(self.strTestsBaseDir, strFile)
                strSrcDirAbs = os.path.dirname(strSrcAbs)
                strDstAbs = os.path.join(self.strOutputBaseDir, strFile)
                strDstDirAbs = os.path.dirname(strDstAbs)
                if os.path.exists(strSrcDirAbs) == False:
                    os.makedirs(strSrcDirAbs)
                if os.path.exists(strDstDirAbs) == False:
                    os.makedirs(strDstDirAbs)
                shutil.copy(strSrcAbs, strDstAbs)

        # Copy the input file to the working folder.
        shutil.copy(strInputPathFull, strOutputDirectoryFull)

        # The working folder is the test path.
        strCwd = strOutputDirectoryFull

        self.__run_hboot_image_compiler(strCwd, strInputPathFull, strOutputPathFull, strNetx, atExtraArguments)

        # Read the reference binary.
        tFile = open(os.path.join(self.strTestsBaseDir, strReference), 'rb')
        strBinReference = tFile.read()
        tFile.close()

        # Read the output.
        tFile = open(strOutputPathFull, 'rb')
        strBinOutput = tFile.read()
        tFile.close()

        self.assertEqual(strBinReference, strBinOutput)

    def test_data_concat(self):
        self.__test_with_reference_bin('data/data_concat.xml', 'data/data_concat.bin', 'NETX90_MPW', None, None)

    def test_data_file_alias(self):
        self.__test_with_reference_bin('data/data_file_alias.xml', 'data/data_file_alias.bin', 'NETX90', ['--alias', 'FillData=fill_data.bin'], ['data/fill_data.bin'])

    def test_data_hex(self):
        self.__test_with_reference_bin('data/data_hex.xml', 'data/data_hex.bin', 'NETX90_MPW', None, None)

    def test_data_uint08(self):
        self.__test_with_reference_bin('data/data_uint8.xml', 'data/data_uint8.bin', 'NETX90_MPW', None, None)

    def test_data_uint16(self):
        self.__test_with_reference_bin('data/data_uint16.xml', 'data/data_uint16.bin', 'NETX90_MPW', None, None)

    def test_data_uint32(self):
        self.__test_with_reference_bin('data/data_uint32.xml', 'data/data_uint32.bin', 'NETX90_MPW', None, None)

    def test_execute_file_elf(self):
        self.__test_with_reference_bin('execute/execute_file_elf.xml', 'execute/execute_file_elf.bin', 'NETX4000', ['--objcopy', '%%NETX4000_OBJCOPY%%', '--objdump', '%%NETX4000_OBJDUMP%%', '--readelf', '%%NETX4000_READELF%%', '--alias', 'Program=%%ELF_NETX4000_SKIP%%'], None)

    def test_execute_address_netx90_mpw(self):
        self.__test_with_reference_bin('execute/execute_address_netx90_mpw.xml', 'execute/execute_address_netx90_mpw.bin', 'NETX90_MPW', None, None)

    def test_execute_address_netx90(self):
        self.__test_with_reference_bin('execute/execute_address_netx90.xml', 'execute/execute_address_netx90.bin', 'NETX90', None, None)

    def test_include_file_alias(self):
        self.__test_with_reference_bin('include/include_file_alias.xml', 'include/include_file_alias.bin', 'NETX4000', ['--alias', 'Data=data.xml'], ['include/data.xml'])

    def test_netx_types_netx4000(self):
        self.__test_with_reference_bin('netx_types/netx4000.xml', 'netx_types/netx4000.bin', 'NETX4000', None, None)

    def test_netx_types_netx4000_alternative(self):
        self.__test_with_reference_bin('netx_types/netx4000_alternative.xml', 'netx_types/netx4000_alternative.bin', 'NETX4000', None, None)

    def test_netx_types_netx4000_apply_port_control(self):
        self.__test_with_reference_bin('netx_types/netx4000_apply_port_control.xml', 'netx_types/netx4000_apply_port_control.bin', 'NETX4000', None, None)

    def test_netx_types_netx4000_relaxed_apply_port_control(self):
        self.__test_with_reference_bin('netx_types/netx4000_relaxed_apply_port_control.xml', 'netx_types/netx4000_relaxed_apply_port_control.bin', 'NETX4000_RELAXED', None, None)

    def test_netx_types_netx4100(self):
        self.__test_with_reference_bin('netx_types/netx4100.xml', 'netx_types/netx4100.bin', 'NETX4100', None, None)

    def test_netx_types_netx4100_alternative(self):
        self.__test_with_reference_bin('netx_types/netx4100_alternative.xml', 'netx_types/netx4100_alternative.bin', 'NETX4100', None, None)

    def test_netx_types_netx4100_apply_port_control(self):
        self.__test_with_reference_bin('netx_types/netx4100_apply_port_control.xml', 'netx_types/netx4100_apply_port_control.bin', 'NETX4100', None, None)

    def test_netx_types_netx90_alternative(self):
        self.__test_with_reference_bin('netx_types/netx90_alternative.xml', 'netx_types/netx90_alternative.bin', 'NETX90', None, None)

    def test_offset_decimal(self):
        self.__test_with_reference_bin('offset/offset_decimal.xml', 'offset/offset_decimal.bin', 'NETX90_MPW', None, None)

    def test_offset_hexadecimal(self):
        self.__test_with_reference_bin('offset/offset_hexadecimal.xml', 'offset/offset_hexadecimal.bin', 'NETX90_MPW', None, None)

    def test_offset_xip(self):
        self.__test_with_reference_bin('offset/offset_xip.xml', 'offset/offset_xip.bin', 'NETX90_MPW', None, None)

    def test_option_chunks_netx90_mpw_disable_iflash_redundancy(self):
        self.__test_with_reference_bin('option_chunks/netx90_mpw_disable_iflash_redundancy.xml', 'option_chunks/netx90_mpw_disable_iflash_redundancy.bin', 'NETX90_MPW', None, None)

    def test_option_chunks_netx90_options(self):
        self.__test_with_reference_bin('option_chunks/netx90_options.xml', 'option_chunks/netx90_options.bin', 'NETX90', None, None)

    def test_regi_chunk(self):
        self.__test_with_reference_bin('regi/regi.xml', 'regi/regi.bin', 'NETX90', None, None)
        
    def test_partial_images_full(self):
        self.__test_with_reference_bin('partial_images/full.xml', 'partial_images/full.bin', 'NETX90_MPW', None, None)

    def test_partial_images_no_header_no_end(self):
        self.__test_with_reference_bin('partial_images/no_header_no_end.xml', 'partial_images/no_header_no_end.bin', 'NETX90_MPW', None, None)

    def test_partial_images_no_header_with_end(self):
        self.__test_with_reference_bin('partial_images/no_header_with_end.xml', 'partial_images/no_header_with_end.bin', 'NETX90_MPW', None, None)

    def test_partial_images_with_header_no_end(self):
        self.__test_with_reference_bin('partial_images/with_header_no_end.xml', 'partial_images/with_header_no_end.bin', 'NETX90_MPW', None, None)

    def test_secure_ca9sw_file(self):
        self.__test_with_reference_bin('secure/ca9sw_file.xml', 'secure/ca9sw_file.bin', 'NETX4000', None, ['secure/fake_ca9sw.bin'])

    def test_secure_cr7sw_file(self):
        self.__test_with_reference_bin('secure/cr7sw_file.xml', 'secure/cr7sw_file.bin', 'NETX4000', None, ['secure/fake_cr7sw.bin'])

    def test_secure_license_cert_file(self):
        self.__test_with_reference_bin('secure/license_cert_file.xml', 'secure/license_cert_file.bin', 'NETX4000', None, ['secure/fake_license_cert.bin'])

    def test_secure_root_cert_file(self):
        self.__test_with_reference_bin('secure/root_cert_file.xml', 'secure/root_cert_file.bin', 'NETX4000', None, ['secure/fake_root_cert.bin'])

#    def test_secure_root_cert(self):
#        self.__test_with_reference_bin('secure/root_cert.xml', 'secure/root_cert.bin', 'NETX90_MPW', ['--keyrom', 'keyrom.xml', '--openssl-options=-rand', '--openssl-options=random.bin'], ['secure/demo_key_public.der', 'secure/keyrom.xml', 'secure/random.bin'])

    def test_skip_absolute(self):
        self.__test_with_reference_bin('skip/absolute.xml', 'skip/absolute.bin', 'NETX90_MPW', None, None)

    def test_skip_absolute_parameter(self):
        self.__test_with_reference_bin('skip/absolute_parameter.xml', 'skip/absolute_parameter.bin', 'NETX90', ['--define', 'skipUntil=0x1000'], None)

    def test_skip_absolute_file_bin(self):
        self.__test_with_reference_bin('skip/absolute_file_bin.xml', 'skip/absolute_file_bin.bin', 'NETX90_MPW', None, ['skip/fill_data.bin'])

    def test_skip_absolute_file_elf(self):
        self.__test_with_reference_bin('skip/absolute_file_elf.xml', 'skip/absolute_file_elf.bin', 'NETX90_MPW', ['--objcopy', '%%NETX90_OBJCOPY%%', '--objdump', '%%NETX90_OBJDUMP%%', '--readelf', '%%NETX90_READELF%%', '--alias', 'FillData=%%ELF_NETX4000_SKIP%%'], None)

    def test_skip_absolute_file_elf_sect(self):
        self.__test_with_reference_bin('skip/absolute_file_elf_sect.xml', 'skip/absolute_file_elf_sect.bin', 'NETX90_MPW', ['--objcopy', '%%NETX90_OBJCOPY%%', '--objdump', '%%NETX90_OBJDUMP%%', '--readelf', '%%NETX90_READELF%%', '--alias', 'FillData=%%ELF_NETX4000_SKIPSECT%%'], None)

    def test_skip_absolute_with_offset(self):
        self.__test_with_reference_bin('skip/absolute_with_offset.xml', 'skip/absolute_with_offset.bin', 'NETX90_MPW', None, None)

    def test_skip_file(self):
        self.__test_with_reference_bin('skip/file.xml', 'skip/file.bin', 'NETX90_MPW', None, ['skip/file.bin'])

    def test_skip_file_alias(self):
        self.__test_with_reference_bin('skip/file_alias.xml', 'skip/file_alias.bin', 'NETX90', ['--alias', 'FillData=fill_data.bin'], ['skip/fill_data.bin'])

    def test_skip_file_alias_multi(self):
        self.__test_with_reference_bin('skip/file_alias_multi.xml', 'skip/file_alias_multi.bin', 'NETX90', ['--alias', 'FillData0=fill_data.bin', '--alias', 'FillData1=fill_data2.bin'], ['skip/fill_data.bin', 'skip/fill_data2.bin'])

    def test_skip_file_with_fill(self):
        self.__test_with_reference_bin('skip/file_with_fill.xml', 'skip/file_with_fill.bin', 'NETX90_MPW', None, ['skip/fill_data.bin'])

    def test_skip_relative(self):
        self.__test_with_reference_bin('skip/relative.xml', 'skip/relative.bin', 'NETX90_MPW', None, None)

    def test_skip_relative_file(self):
        self.__test_with_reference_bin('skip/relative_file.xml', 'skip/relative_file.bin', 'NETX90_MPW', None, ['skip/fill_data.bin'])

    def test_skip_incomplete_absolute(self):
        self.__test_with_reference_bin('skip_incomplete/absolute.xml', 'skip_incomplete/absolute.bin', 'NETX90_MPW', None, None)

    def test_skip_incomplete_absolute_file(self):
        self.__test_with_reference_bin('skip_incomplete/absolute_file.xml', 'skip_incomplete/absolute_file.bin', 'NETX90_MPW', None, ['skip_incomplete/fill_data.bin'])

    def test_skip_incomplete_absolute_with_offset(self):
        self.__test_with_reference_bin('skip_incomplete/absolute_with_offset.xml', 'skip_incomplete/absolute_with_offset.bin', 'NETX90_MPW', None, None)

    def test_skip_incomplete_file(self):
        self.__test_with_reference_bin('skip_incomplete/file.xml', 'skip_incomplete/file.bin', 'NETX90_MPW', None, ['skip_incomplete/file.bin'])

    def test_skip_incomplete_file_with_fill(self):
        self.__test_with_reference_bin('skip_incomplete/file_with_fill.xml', 'skip_incomplete/file_with_fill.bin', 'NETX90_MPW', None, ['skip_incomplete/fill_data.bin'])

    def test_skip_incomplete_relative(self):
        self.__test_with_reference_bin('skip_incomplete/relative.xml', 'skip_incomplete/relative.bin', 'NETX90_MPW', None, None)

    def test_skip_incomplete_relative_file(self):
        self.__test_with_reference_bin('skip_incomplete/relative_file.xml', 'skip_incomplete/relative_file.bin', 'NETX90_MPW', None, ['skip_incomplete/fill_data.bin'])

    def test_snippets_cdata(self):
        self.__test_with_reference_bin('snippets/cdata.xml', 'snippets/cdata.bin', 'NETX90_MPW', None, ['snippets/sniplib/cdata-1.0.0.xml'])

    def test_snippets_custom_location(self):
        self.__test_with_reference_bin('snippets/custom_location.xml', 'snippets/custom_location.bin', 'NETX90_MPW', ['--sniplib', 'custom_sniplib'], ['snippets/custom_sniplib/custom-1.0.0.xml'])

    def test_snippets_default_location(self):
        self.__test_with_reference_bin('snippets/default_location.xml', 'snippets/default_location.bin', 'NETX90_MPW', None, ['snippets/sniplib/default-1.0.0.xml'])

    def test_snippets_precedence(self):
        self.__test_with_reference_bin('snippets/precedence.xml', 'snippets/precedence.bin', 'NETX90_MPW', ['--sniplib', 'custom_sniplib', '--sniplib', 'sniplib'], ['snippets/sniplib/precedence-1.0.0.xml', 'snippets/custom_sniplib/precedence-1.0.0.xml'])

    def test_xip_file_alias_NETX4000_SQIROM0(self):
        self.__test_with_reference_bin('xip/xip_file_alias_NETX4000_SQIROM0.xml', 'xip/xip_file_alias_NETX4000_SQIROM0.bin', 'NETX4000', ['--alias', 'FillData=fill_data.bin'], ['xip/fill_data.bin'])

    def test_xip_hex_NETX4000_RELAXED_SQIROM0(self):
        self.__test_with_reference_bin('xip/xip_hex_NETX4000_RELAXED_SQIROM0.xml', 'xip/xip_hex_NETX4000_RELAXED_SQIROM0.bin', 'NETX4000_RELAXED', None, None)

    def test_xip_hex_NETX4000_RELAXED_SQIROM1(self):
        self.__test_with_reference_bin('xip/xip_hex_NETX4000_RELAXED_SQIROM1.xml', 'xip/xip_hex_NETX4000_RELAXED_SQIROM1.bin', 'NETX4000_RELAXED', None, None)

    def test_xip_hex_NETX4000_SQIROM0(self):
        self.__test_with_reference_bin('xip/xip_hex_NETX4000_SQIROM0.xml', 'xip/xip_hex_NETX4000_SQIROM0.bin', 'NETX4000', None, None)

    def test_xip_hex_NETX4000_SQIROM1(self):
        self.__test_with_reference_bin('xip/xip_hex_NETX4000_SQIROM1.xml', 'xip/xip_hex_NETX4000_SQIROM1.bin', 'NETX4000', None, None)

    def test_xip_hex_NETX4100_SQIROM0(self):
        self.__test_with_reference_bin('xip/xip_hex_NETX4100_SQIROM0.xml', 'xip/xip_hex_NETX4100_SQIROM0.bin', 'NETX4100', None, None)

    def test_xip_hex_NETX4100_SQIROM1(self):
        self.__test_with_reference_bin('xip/xip_hex_NETX4100_SQIROM1.xml', 'xip/xip_hex_NETX4100_SQIROM1.bin', 'NETX4100', None, None)

    def test_xip_hex_NETX90_MPW_INTFLASH(self):
        self.__test_with_reference_bin('xip/xip_hex_NETX90_MPW_INTFLASH.xml', 'xip/xip_hex_NETX90_MPW_INTFLASH.bin', 'NETX90_MPW', None, None)

    def test_xip_hex_NETX90_MPW_SQIROM(self):
        self.__test_with_reference_bin('xip/xip_hex_NETX90_MPW_SQIROM.xml', 'xip/xip_hex_NETX90_MPW_SQIROM.bin', 'NETX90_MPW', None, None)

if __name__ == '__main__':
    unittest.main()
