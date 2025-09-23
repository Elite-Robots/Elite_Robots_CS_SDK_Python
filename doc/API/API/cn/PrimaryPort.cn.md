# Primary Port

## 简介

SDK中提供了与机器人30001端口连接、发送脚本的接口，以及解析30001端口数据的框架。SDK中只有部分数据包的解析，如果要解析其他数据包，需要手动编写解析代码。

# PrimaryPortInterface 类

## 简介

此接口提供了与机器人primary port接口通讯的方法。

## 导入
```python
from elite_cs_sdk import PrimaryClientInterface, PrimaryPackage
from elite_cs_sdk import RobotError, RobotRuntimeException
```

## PrimaryPortInterface 类的构造函数

## 通讯

### ***连接***
```python
def connect(ip: str, port = 30001) -> bool
```

- ***功能***

    连接到机器人的30001端口（默认）。

- ***参数***
    - ip：机器人端口

    - timeout_ms：设置机器人读取下一条指令的超时时间，小于等于0时会无限等待。

- ***返回值***：成功返回 true，失败返回 false。

- ***注意***
    1. 如果重复调用此函数而没有调用disconnect，那么会断开原来的连接。
    2. 重复调用此函数的频率最好不要超过2HZ。

---

### ***断开连接***
```python
def disconnect()
```
- ***功能***

    断开与机器人的连接

- ***注意***

    建议在调用此函数之后进行500ms左右延迟再调用connect。

---

### ***发送脚本***
```python
def sendScript(script: str) -> bool
```
- ***功能***

    向机器人发送可执行脚本

- ***参数***
    - script：待发送的脚本。

- ***返回值***：发送成功返回 true，失败返回 false。

---

### 获取数据包
```python
def getPackage(pkg: PrimaryPackage, timeout_ms: int) -> bool
```
- ***功能***

    获取机器人数据包并解析

- ***参数***
    - pkg：待获取的数据包

    - timeout_ms：等待超时时间。

- ***返回值***：获取成功返回 true，失败返回 false。

---

### 获取本地的IP地址
```python
def getLocalIP() -> str
```
- ***功能***

    获取本机IP地址。

- ***返回值***：本机IP地址。如果为空，与机器人30001的连接则存在问题。

---

### ***注册机器人异常回调***
```python
def registerRobotExceptionCallback(cb: Callable[[RobotException]])
```

- ***功能***
    注册机器人异常回调函数。当从机器人的 primary 端口接收到异常报文时，将调用该回调函数。回调函数接收一个 RobotExceptionSharedPtr 类型的参数，表示发生的异常信息。

- ***参数***
    - registerRobotExceptionCallback: 回调函数，用于处理接收到的机器人异常。参数为机器人异常的共享指针(参考：[RobotException](./RobotException.cn.md))。


# PrimaryPackage 类

## 简介

此类主要用于被继承，以此来获取Primary端口数据。

SDK中没有提供全部的数据包解析，如果需要其他的数据包，可以参考Elite官方文档“CS_用户手册_机器人状态报文.xlsx”来编写自己需要的数据包解析。

## PrimaryPackage 接口
```python
from elite_cs_sdk.primary_client import PrimaryPackage
```

## PrimaryPackage 类的构造函数
### ***构造函数***
```python
def __init__(type: int)
```
- ***功能***

    初始化数据

- ***参数***
    - type：数据包类型（参考Elite官方文档：CS_用户手册_机器人状态报文.xlsx）

---

## 纯虚函数

### 解析报文
```python
def parser(len: int, data: bytes)
```
- ***功能***

     由子类来完成具体实现，解析Primary端口机器人状态报文的子报文。当子类实例作为参数传入`PrimaryPortInterface::getPackage()`中会被调用。
    
- ***参数***
    - len：子报文的长度。

    - data：子报文字节流。

---

## 其余

### ***获取报文类型***
```python
def getType() -> int
```
- ***功能***

    获取数据包的类型。

- ***返回值***：数据包类型。

---

## SDK内部使用
### 等待更新
```python
def waitUpdate(timeout_ms: int) -> bool
```
- ***功能***

    等待数据包数据更新。在getPackage（）函数中调用。

- ***参数***
    - timeout_ms：超时时间
    
- ***返回值***：未超时返回 true，超时返回 false。

---

# KinematicsInfo 类

## 简介

机器人配置数据中运动学的数据包解析。PrimaryPackage 是此接口的父类，除了 PrimaryPackage 类中的方法以外，此接口主要内容是机器人的DH参数。

## KinematicsInfo 接口

```python
from elite_cs_sdk import KinematicsInfo
```

## DH参数

- `dh_a_ : list[6]`

- `dh_d_: list[6]`

- `dh_alpha_: list[6]`
