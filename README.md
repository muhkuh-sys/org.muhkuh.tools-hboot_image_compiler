How to build the hboot image compiler on Ubuntu 18.04?
======================================================

After cloning this repo to your local machine, 
update the git submodules.
```commandline
cd org.muhkuh.tools-hboot_image_compiler
git submodule init
git submodule update
```
Next, build it with python2, this will take a while, 
so better get a cup of fresh hot coffee.
```commandline
python2 mbs/mbs
```
N.B. the mbs will download some tgz, zip files etc in your home directory to
the folder ".mbs" .

After a while the resulting zip file should be located in:
```commandline
./targets/repository/org/muhkuh/tools/hboot_image_compiler/CURRENTVERSION/
```
Where the CURRENTVERSION is the something like 0.0.1.2

Run the tests!
===============

To run the test, just execute:
```commandline
python2 tests/tests.py
```

Clean up in case that something goes wrong
==========================================

To start from scratch again you could clean with mbs
```commandline
python2 mbs/mbs -c
```

or just remove the targets folder
```commandline
rm -rf ./targets
```

or throw the ~/.mbs away with
```commandline
rm -rf ~/.mbs
```
