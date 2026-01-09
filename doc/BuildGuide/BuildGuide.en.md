# Compilation and Installation Guide

## Dependency Installation

### Ubuntu
```bash
sudo apt update

sudo apt install libboost-all-dev

sudo apt install libssh-dev # Optional, recommended, version 0.9.6 is recommended

# sudo apt install sshpass # Required if libssh-dev is not installed
```
If you’re using a Python virtual environment to install, skip this step.

```bash
python3 -m pip install --upgrade pip setuptools wheel build

python3 -m pip install --user pybind11 pybind11_stubgen
```

### Windows

Install using `vcpkg`
```bash
.\vcpkg install boost-asio

.\vcpkg install libssh

.\vcpkg integrate install
```

(Optional) If you have already installed the complete `boost` library using vcpkg, it is recommended to execute the following command to remove Python-related content from vcpkg. Otherwise, the compilation of this library will use vcpkg's Python instead of the Python in your operating system.
```bash
.\vcpkg remove python3 boost-parameter-python boost-python

.\vcpkg integrate install
```

Install required components for Python packaging（If you’re using a Python virtual environment to install, skip this step.）
```bash
python3 -m pip install --upgrade pip setuptools wheel build

python3 -m pip install --user pybind11 pybind11_stubgen
```

## Compilation and Installation

### Ubuntu
Install using the default Python environment.

```bash
cd <clone of this repository>

mkdir build && cd build

cmake ..

make

pip install ../dist/elite_cs_sdk-*.whl
```

If you’re using a Python virtual environment to install(venv)
```bash
cd <clone of this repository>

sudo apt update

sudo apt install python3.xx-venv   ## xx is the Python version number, xx ≥ 3.8.

python3.xx -m venv .venvtest       ## .venvtest is the virtual environment folder name.

source .venvtest/bin/activate

python3 -m pip install pyyaml jinja2 typeguard

python3 -m pip install --upgrade pip setuptools wheel build

python3 -m pip install pybind11 pybind11_stubgen

mkdir build && cd build

cmake ..

make

pip install ../dist/elite_cs_sdk-*.whl
```
### Windows
Install using the default Python environment.

```bash
cd <clone of this repository>

mkdir build && cd build

cmake ..

cmake --build . --config Release

pip install ../dist/elite_cs_sdk-*.whl
```
If you’re using a Python virtual environment to install(venv)
```bash

Same as above.
```