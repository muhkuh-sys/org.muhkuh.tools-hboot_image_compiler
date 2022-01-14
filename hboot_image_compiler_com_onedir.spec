# -*- mode: python ; coding: utf-8 -*-

block_cipher = None


a = Analysis(['build/lib/hil_nxt_hboot_image_compiler/com/__main__.py'],
             pathex=['.venv/Lib/site-packages', 'build/lib/hil_nxt_hboot_image_compiler/com'],
             binaries=[],
             datas=[('build/lib/hil_nxt_hboot_image_compiler/patch_tables/*', 'patch_tables'),
              ('build/lib/hil_nxt_hboot_image_compiler/templates/com/*', 'templates/com'),
              ('build/lib/hil_nxt_hboot_image_compiler/elf_compiler/arm-none-eabi-gcc/4.9.3/bin/*',
              'elf_compiler/arm-none-eabi-gcc/4.9.3/bin'),
              ('bootswitch/*', 'bootswitch'),
              ('readme/com/readme.md', '.'),
              ('LICENSE.txt', '.')
              ],
             hiddenimports=[],
             hookspath=[],
             runtime_hooks=[],
             excludes=[],
             win_no_prefer_redirects=False,
             win_private_assemblies=False,
             cipher=block_cipher,
             noarchive=False)
pyz = PYZ(a.pure, a.zipped_data,
             cipher=block_cipher)
exe = EXE(pyz,
          a.scripts,
          [],
          exclude_binaries=True,
          name='hboot_image_compiler_com',
          debug=False,
          bootloader_ignore_signals=False,
          strip=False,
          upx=True,
          console=True,
          version='hboot_image_compiler_com_info.txt')
coll = COLLECT(exe,
               a.binaries,
               a.zipfiles,
               a.datas,
               strip=False,
               upx=True,
               upx_exclude=[],
               name='hboot_image_compiler_com')
