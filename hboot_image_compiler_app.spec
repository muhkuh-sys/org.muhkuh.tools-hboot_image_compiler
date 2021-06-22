# -*- mode: python ; coding: utf-8 -*-

block_cipher = None


a = Analysis(['build/lib/hil_nxt_hboot_image_compiler/app/netx90_app_image.py'],
             pathex=['.venv/Lib/site-packages', 'build/lib/hil_nxt_hboot_image_compiler/app'],
             binaries=[],
             datas=[('build/lib/hil_nxt_hboot_image_compiler/patch_tables/*', 'hil_nxt_hboot_image_compiler/patch_tables')],
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
          a.binaries,
          a.zipfiles,
          a.datas,
          [],
          name='hboot_image_compiler_app',
          debug=False,
          bootloader_ignore_signals=False,
          strip=False,
          upx=True,
          upx_exclude=[],
          runtime_tmpdir=None,
          console=True )
