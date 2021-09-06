from setuptools import setup, find_packages

import versioneer

setup(name='hboot_image_compiler',
      version=versioneer.get_version(),
      author='',
      author_email='',
      url='',
      description='A tool used to compile HBoot images',
      # long_description=open("README.rst").read(),
      license='',
      packages=find_packages(exclude=['tests', 'mbs', 'templates', 'src', 'targets', 'site_scons', 'build', 'dist']),
      package_data={'hil_nxt_hboot_image_compiler': ['patch_tables/*.xml',
                                                     'app/templates/*.xml',
                                                     'elf_compiler/arm-none-eabi-gcc/4.9.3/bin/arm-none-eabi-readelf.exe',
                                                     'elf_compiler/arm-none-eabi-gcc/4.9.3/bin/arm-none-eabi-objdump.exe',
                                                     'elf_compiler/arm-none-eabi-gcc/4.9.3/bin/arm-none-eabi-objcopy.exe']},

      include_package_data=True,
      cmdclass=versioneer.get_cmdclass(),
      zip_safe=False,
      extras_require={
          "build": ["pyinstaller==3.6", "setuptools"]
      }
      )
