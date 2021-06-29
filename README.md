How to build the hboot image compiler
=====================================
## Requirements
- Python 2.7

## Setup
After cloning this repo to your local machine, 
update the git submodules.
```commandline
cd org.muhkuh.tools-hboot_image_compiler
git submodule init
git submodule update
```
set up a python2 environment inside the project directory
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
(.venv) make dist
```

the results show in directory ```dist```


## Run the tests
To only run the tests run command:
```
(.venv) make test
```

## Clean up in case that something goes wrong
To start from scratch again you could clean with mbs
```commandline
make clean
```

or just remove the following folders
 - build
 - targets
 - dist

