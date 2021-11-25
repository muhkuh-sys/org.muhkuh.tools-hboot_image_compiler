How to build the hboot image compiler
=====================================
## Requirements
- Python 2.7 or Python 3.7

## Setup
After cloning this repo to your local machine, 
update the git submodules.
```commandline
cd org.muhkuh.tools-hboot_image_compiler
git submodule init
git submodule update
```
set up a python 3 or 2 environment inside the project directory (python 3 is recommended)
```
python2 -m virtualenv .venv
```
activate the environment (afterwards the commandline should show "(.venv)" at the beginning)
```
.venv\scripts\activate
```
then install the requirements into the environment
```
(.venv) python -m pip install -r requirements.txt
```

## Build distribution
to build the distributions and also run tests upfront run command:
```
(.venv) python maker.py dist
```
or ad a release version
```
(.venv) python maker.py release
```

the results show in directory ```dist```


## Run the tests
To only run the tests run command:
```
(.venv) python testsa/test.py
```

## Clean up in case that something goes wrong
To start from scratch again you could clean with mbs
```
(.venv) python maker.py clean
```
or just remove the following folders
 - build
 - targets
 - dist

