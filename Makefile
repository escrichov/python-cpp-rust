.PHONY: clean clean-test clean-pyc clean-build docs help

test: ## run tests quickly with the default Python
	py.test -v -s test.py

clean: clean-build clean-pyc clean-test ## remove all build, test, coverage and Python artifacts

clean-build: ## remove build artifacts
	rm -fr build/
	rm -fr dist/
	rm -fr .eggs/
	find . -name '*.egg-info' -exec rm -fr {} +
	find . -name '*.egg' -exec rm -f {} +

clean-pyc: ## remove Python file artifacts
	find . -name '*.pyc' -exec rm -f {} +
	find . -name '*.pyo' -exec rm -f {} +
	find . -name '*~' -exec rm -f {} +
	find . -name '__pycache__' -exec rm -fr {} +

clean-test: ## remove test and coverage artifacts
	rm -fr .tox/
	rm -f .coverage
	rm -fr htmlcov/

compile-rust: ## compile new rust lib
	@cd pyext-myrustlib;RUSTFLAGS="-C target-cpu=native" cargo build --release
	@cp pyext-myrustlib/target/release/libmyrustlib.so myrustlib.so

compile-c: ## compile new c lib
	@cd pyext-mylibcswig;python3 setup.py build_ext -i;python3 setup.py install

compile-cpython: ## compile new cpython lib
	@cd pyext-mylibcpython;python3 setup.py build_ext -i;python3 setup.py install

compile-cython: ## compile new cython lib
	@cd pyext-mylibcython;python3 setup.py build_ext -i;python3 setup.py install

compile-boost: ## compile new cython lib
	@cd pyext-mylibboost;python3 setup.py build_ext -i;python3 setup.py install

compile-pybind11: ## compile new cython lib
	@cd mylibpybind11;python3 setup.py build_ext -i;python3 setup.py install


build: compile-rust compile-c compile-cpython compile-cython compile-boost compile-pybind11