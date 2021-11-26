How to build the hboot image compiler
=====================================
## Requirements
- Python 3.7 (Python 2.7 also supported)

## Setup
Clone this repo including its submodules to your local machine.
```
git clone --recurse-submodules https://github.com/muhkuh-sys/org.muhkuh.tools-hboot_image_compiler.git
```
Make sure the submodules are up to date.
```commandline
cd org.muhkuh.tools-hboot_image_compiler
git submodule init
git submodule update
```
Set up a python 3 environment inside the project directory
```
python3 -m venv .venv
```

Activate the environment (afterwards the commandline should show "(.venv)" at the beginning)
```
.venv\scripts\activate
```
Then install the requirements into the environment
```
(.venv) python -m pip install -r requirements.txt
```

## Build distribution
To build the distributions and also run tests upfront run command:
```
(.venv) python maker.py dist
```
Or ad a release version
```
(.venv) python maker.py release
```

The results show in directory ```dist```


## Run tests separately
To only run the tests run command:
```
(.venv) python testsa/test.py
```

## Clean up in case that something goes wrong
To start from scratch again you could clean with mbs
```
(.venv) python maker.py clean
```
Or just remove the following folders
 - build
 - targets
 - dist

