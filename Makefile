PYTHON=python
SPHINX=sphinx
PYINSTALLER=PyInstaller

NAME:=$(shell $(PYTHON) setup.py --name)

.PHONY: default install test clean docs dist source zip tar wheel release

default:
	@echo "make install - Install on local system"
	@echo "make test - Run unit tests"
	@echo "make clean - Clean-up all generated files"
	# @echo "make docs - Generate HTML documentation"
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
	$(PYTHON) tests/tests.py || (echo "Tests Failed!"; exit 1)

clean:
	rm -rf build/
	rm -rf dist/
	rm -rf targets/
	rm -rf $(NAME).egg-info/
	rm -f MANIFEST

# docs:
# 	$(PYTHON) -m $(SPHINX) -M clean "docs" "docs\_build"
#	$(PYTHON) -m $(SPHINX) -M html "docs" "docs\_build"

dist: test zip tar exec #docs wheel

source: zip tar #docs

zip:
	$(PYTHON) setup.py sdist --formats zip

tar:
	$(PYTHON) setup.py sdist --formats gztar

wheel:
	$(PYTHON) setup.py bdist_wheel

exec:
	$(PYTHON) setup.py build
	$(PYTHON) -m $(PYINSTALLER) hboot_image_compiler_com.spec
	$(PYTHON) -m $(PYINSTALLER) hboot_image_compiler_app_onefile.spec
	$(PYTHON) -m $(PYINSTALLER) hboot_image_compiler_app_onedir.spec

release: zip exec #docs