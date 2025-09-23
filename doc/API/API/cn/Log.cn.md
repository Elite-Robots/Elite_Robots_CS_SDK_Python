# Log 模块

## 简介

Log模块提供了Elite_Robots_CS_SDK中的日志功能相关设置，包括日志级别定义、日志处理器接口和日志输出功能。

## 导入
```python
import elite_cs_sdk

```

## 日志级别枚举

```python
class LogLevel:
    """
    Members:
    
      ELI_DEBUG
    
      ELI_INFO
    
      ELI_WARN
    
      ELI_ERROR
    
      ELI_FATAL
    
      ELI_NONE
    """
    ...
```
- ***描述***
  
  定义了日志的级别，从低到高依次为：
  - `ELI_DEBUG`: 调试信息
  - `ELI_INFO`: 普通信息
  - `ELI_WARN`: 警告信息
  - `ELI_ERROR`: 错误信息
  - `ELI_FATAL`: 严重错误信息
  - `ELI_NONE`: 不输出任何日志

## 日志函数

### 调试日志
```python
def logDebugMessage(file: str, line: int, msg: str) -> None
```
- ***功能***
  
  输出调试级别日志

- ***参数***

  - file：源文件
  - line：行号
  - msg：日志消息

### 信息日志
```python
def logInfoMessage(file: str, line: int, msg: str) -> None
```
- ***功能***
  
  输出信息级别日志

- ***参数***

  - file：源文件
  - line：行号
  - msg：日志消息

### 警告日志
```python
def logWarnMessage(file: str, line: int, msg: str) -> None
```
- ***功能***
  
  输出警告级别日志

- ***参数***

  - file：源文件
  - line：行号
  - msg：日志消息

### 错误日志
```python
def logErrorMessage(file: str, line: int, msg: str) -> None
```
- ***功能***
  
  输出错误级别日志

- ***参数***

  - file：源文件
  - line：行号
  - msg：日志消息

### 严重错误日志
```python
def logFatalMessage(file: str, line: int, msg: str) -> None
```
- ***功能***
  
  输出严重错误级别日志

- ***参数***

  - file：源文件
  - line：行号
  - msg：日志消息

## LogHandler 类

### 简介
```python
class LogHandler
```
- ***描述***
  
  日志处理器抽象基类，可通过继承此类并实现`log()`方法来自定义日志处理方式。

### 日志处理函数
```python
def log(file: str, line: int, loglevel: LogLevel, log: str)
```
- ***功能***
  
  用于处理日志消息，重写此方法以实现自定义的日志输出

- ***参数***
  - `file`: 日志来源文件
  - `line`: 日志来源行号
  - `loglevel`: 日志级别
  - `log`: 日志消息内容

## 全局函数

### 注册日志处理器
```python
def registerLogHandler(hanlder：LogHandler);
```
- ***功能***
  
  注册自定义的日志处理器

- ***参数***
  - `hanlder`: 指向新日志处理器对象的unique_ptr

### 注销日志处理器
```python
def unregisterLogHandler()
```
- ***功能***
  
  注销当前日志处理器，将启用默认日志处理器

### 设置日志级别
```python
def setLogLevel(level: LogLevel)
```
- ***功能***
  
  设置日志级别，低于此级别的日志将不会被输出

- ***参数***
  - `level`: 要设置的日志级别

## 使用示例

```python
import elite_cs_sdk as cs

class MyLogHandler(cs.LogHandler):
  def log(self, file: str, line: int, loglevel: cs.LogLevel, msg: str):
    print(f"[{file}] : {line}: {loglevel}: {msg}")

my_log = MyLogHandler()

cs.registerLogHandler(my_log)

cs.setLogLevel(cs.LogLevel.ELI_DEBUG)

cs.logDebugMessage("elite_log.py", 1, "This is an debug message")
```
