How to build the hboot image compiler on Ubuntu 18.04?
======================================

After cloning this repo to your local maschine, 
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
After a while the resulting zip file should be located in:
```commandline
./targets/repository/org/muhkuh/tools/hboot_image_compiler/CURRENTVERION/
```
Where the CURRENTVERION is the something like 0.0.1.2
