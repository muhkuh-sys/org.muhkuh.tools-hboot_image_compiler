PYTHON=python
SPHINX=sphinx
PYINSTALLER=PyInstaller

NAME:=$(shell $(PYTHON) setup.py --name)

.PHONY: default install test clean docs dist source zip tar wheel release

default:
	@echo "make install - Install on local system"
	@echo "make test - Run unit tests"
	@echo "make clean - Clean-up all generated files"
	@echo "make docs - Generate HTML documentation"
	@echo "make dist - Generate all packages"
	@echo "make source - Generate source package"
	@echo "make zip - Generate a source zip package"
	@echo "make tar - Generate a source tar package"
	@echo "make wheel - Build a wheel package"
	@echo "make exec - Generate executable file"
	@echo "make release - Generate release files (docs, zip, executable)"

install:
	$(PYTHON) setup.py install

test:
	$(PYTHON) -m unittest discover -v

clean:
	rm -rf hil_nxt_hboot_image_compiler/__pycache__/
	rm -f $(wildcard hil_nxt_hboot_image_compiler/*.pyc)
	rm -rf hil_nxt_hboot_image_compiler/com/__pycache__/
	rm -rf hil_nxt_hboot_image_compiler/app/__pycache__/
	rm -f $(wildcard hil_nxt_hboot_image_compiler/*.pyc)
	rm -rf docs/_build/
	rm -rf docs/__pycache__/
	rm -f $(wildcard docs/*.pyc)
	rm -rf __pycache__/
	rm -f $(wildcard *.pyc)
	rm -f $(wildcard *.spec)
	rm -rf build/
	rm -rf dist/
	rm -rf $(NAME).egg-info/
	rm -f MANIFEST

docs:
	$(PYTHON) -m $(SPHINX) -M clean "docs" "docs\_build"
	$(PYTHON) -m $(SPHINX) -M html "docs" "docs\_build"

dist: docs zip tar wheel

source: docs zip tar

zip:
	$(PYTHON) setup.py sdist --formats zip

tar:
	$(PYTHON) setup.py sdist --formats gztar

wheel:
	$(PYTHON) setup.py bdist_wheel

exec:
	$(PYTHON) setup.py build
	$(PYTHON) -m $(PYINSTALLER) hboot_image_compiler_com.spec
	$(PYTHON) -m $(PYINSTALLER) hboot_image_compiler_app.spec

release: docs zip exec