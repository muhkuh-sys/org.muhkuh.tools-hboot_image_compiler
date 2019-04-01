Check for changed line endings 
==============================

Configure git to disable automatic line ending conversions.
Make a new clone of the repository and continue working in that clone.
After creating a release, compare it to the previous release. Check for files that have equal content but differ in the line endings.


Testing the APP image builder (netx90_app_image.py)
===================================================
The test files are located in the directory tests\netx90_app_image.
Check out the netx_chunk_example and build it using netx Studio.

Copy the following elf files from build\debug\Targets\NXHX90-JTAG_APP to the test directory:
netx90_app_iflash_sdram.elf
netx90_app_iflash.elf


Open a shell in the test directory:
tests\netx90_app_image
Run the script
test_app_bootimages.bat
