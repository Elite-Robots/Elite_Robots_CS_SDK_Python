# 编译安装向导

## 依赖安装

### Ubuntu
```bash
sudo apt update

sudo apt install libboost-all-dev

sudo apt install libssh-dev # 可选，建议安装，建议版本为0.9.6

# sudo apt install sshpass #如果没安装 libssh-dev 则需要安装此指令
```
如果使用python虚拟环境安装请跳过此步：
```bash
python3 -m pip install --upgrade pip setuptools wheel build

python3 -m pip install --user pybind11 pybind11_stubgen
```

### Windows

使用`vcpkg`安装
```bash
.\vcpkg install boost-asio

.\vcpkg install libssh

.\vcpkg integrate install
```

（可选）如果已经使用 vcpkg 安装过完整的`boost`库，建议执行下面指令删除 vcpkg 的 python 相关内容，否则编译此库时会使用 vcpkg 的 python 而不是你操作系统中的 python
``` bash
.\vcpkg remove python3 boost-parameter-python boost-python

.\vcpkg integrate install
```

安装python打包的必须组件(如果使用python虚拟环境，请跳过此步)
```bash
python3 -m pip install --upgrade pip setuptools wheel build

python3 -m pip install --user pybind11 pybind11_stubgen
```

## 编译与安装

### Ubuntu
使用默认python环境安装
```bash
cd <clone of this repository>

mkdir build && cd build

cmake ..

make

pip install ../dist/elite_cs_sdk-*.whl
```

如果使用虚拟环境(venv)
```bash
cd <clone of this repository>

sudo apt update

sudo apt install python3.xx-venv   ## xx为python版本号,xx>=3.8

python3.xx -m venv .venvtest       ## .venvtest为虚拟库文件夹名称

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
使用默认python环境安装
```bash
cd <clone of this repository>

mkdir build && cd build

cmake ..

cmake --build . --config Release

pip install ../dist/elite_cs_sdk-*.whl
```
如果使用虚拟环境(venv)
```bash

同上
```