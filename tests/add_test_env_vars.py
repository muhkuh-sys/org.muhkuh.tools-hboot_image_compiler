import os
import tempfile


def update_os_env(project_root, test_elfs_dir):
    """ update the environment variables with paths that are necessary for hboot image compiler tests

    """
    new_vars = dict()
    do_not_check_list = []  # paths that do not need to be checked for since they won't exists yet

    new_vars['TMP'] = tempfile.gettempdir()
    new_vars['ELF_NETX4000_SKIPSECT'] = os.path.join(test_elfs_dir, "netx4000_skipsect", "netx4000_skipsect.elf")
    new_vars['ELF_NETX4000_SKIP'] = os.path.join(test_elfs_dir, "netx4000_skip", "netx4000_skip.elf")
    new_vars['ELF_NETX90_APP_BLINKI_IFLASH_SDRAM'] = os.path.join(test_elfs_dir, "netx90_app_blinki_iflash_sdram", "netx90_app_blinki_iflash_sdram.elf")
    new_vars['ELF_NETX90_APP_BLINKI_SDRAM'] = os.path.join(test_elfs_dir, "netx90_app_blinki_sdram", "netx90_app_blinki_sdram.elf")
    new_vars['ELF_NETX90_APP_BLINKI_IFLASH'] = os.path.join(test_elfs_dir, "netx90_app_blinki_iflash", "netx90_app_blinki_iflash.elf")
    new_vars['ELF_NETX90_APP_BLINKI_IFLASH_2PART'] = os.path.join(test_elfs_dir, "netx90_app_blinki_iflash_2part", "netx90_app_blinki_iflash_2part.elf")

    netx_studio_build_tools = os.path.join("C:%s" % os.sep, "ProgramData", "Hilscher GmbH", "netX Studio CDT", "BuildTools")
    print(os.path.exists(netx_studio_build_tools))
    arm_none_eabi_dir = os.path.join(netx_studio_build_tools, "arm-none-eabi-gcc", "4.9.3", "bin")

    new_vars['NETX4000_READELF'] = os.path.join(arm_none_eabi_dir, 'arm-none-eabi-readelf.exe')
    new_vars['NETX4000_OBJDUMP'] = os.path.join(arm_none_eabi_dir, 'arm-none-eabi-objdump.exe')
    new_vars['NETX4000_OBJCOPY'] = os.path.join(arm_none_eabi_dir, 'arm-none-eabi-objcopy.exe')

    new_vars['NETX90_READELF'] = os.path.join(arm_none_eabi_dir, 'arm-none-eabi-readelf.exe')
    new_vars['NETX90_OBJDUMP'] = os.path.join(arm_none_eabi_dir, 'arm-none-eabi-objdump.exe')
    new_vars['NETX90_OBJCOPY'] = os.path.join(arm_none_eabi_dir, 'arm-none-eabi-objcopy.exe')

    new_vars['HBOOT_DEPACK_FOLDER'] = os.path.join(project_root, 'targets', 'tests', 'bin')
    do_not_check_list.append(os.path.join(project_root, 'targets', 'tests', 'bin'))

    new_vars['SYSTEMROOT'] = os.path.join("C:%s" % os.sep, "windows")

    for new_var_name, new_var_path in new_vars.items():
        # check if path exists if we expect it to exists
        if not os.path.exists(new_var_path) and new_var_path not in do_not_check_list:
            raise IOError("WARNING: could not find path: '%s'" % new_var_path)
        else:
            # add new env var to os.environ if everything ok
            os.environ[new_var_name] = new_var_path
