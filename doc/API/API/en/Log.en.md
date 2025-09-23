# Log Module

## Introduction
The Log module provides settings related to the logging functionality in the Elite_Robots_CS_SDK, including log level definitions, log handler interfaces, and log output functions.

## Import
```py
import elite_cs_sdk
```

## Log Level Enumeration

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
- ***Description***
Defines the log levels, from lowest to highest:
  - `ELI_DEBUG`: Debug information
  - `ELI_INFO`: General information
  - `ELI_WARN`: Warning information
  - `ELI_ERROR`: Error information
  - `ELI_FATAL`: Severe error information
  - `ELI_NONE`: Do not output any logs

## Log Macro Definitions

### Debug Log
```cpp
def logDebugMessage(file: str, line: int, msg: str) -> None
```
- ***Function***
Outputs debug-level logs.

- ***Param***

  - file: source file
  - line: code line
  - msg: the log message

### Information Log
```cpp
def logInfoMessage(file: str, line: int, msg: str) -> None
```
- ***Function***
Outputs information-level logs.

- ***Param***

  - file: source file
  - line: code line
  - msg: the log message

### Warning Log
```cpp
def logWarnMessage(file: str, line: int, msg: str) -> None
```
- ***Function***
Outputs warning-level logs.

- ***Param***

  - file: source file
  - line: code line
  - msg: the log message

### Error Log
```cpp
def logErrorMessage(file: str, line: int, msg: str) -> None
```
- ***Function***
Outputs error-level logs.

- ***Param***

  - file: source file
  - line: code line
  - msg: the log message

### Severe Error Log
```cpp
def logFatalMessage(file: str, line: int, msg: str) -> None
```
- ***Function***
Outputs severe error-level logs.

- ***Param***

  - file: source file
  - line: code line
  - msg: the log message

## LogHandler Class

### Introduction
```cpp
class LogHandler
```
- ***Description***
An abstract base class for log handlers. You can inherit from this class and implement the `log()` method to customize the log handling method.

### Log Handling Function
```python
def log(const char* file, int line, LogLevel loglevel, const char* log)
```
- ***Function***
A pure virtual function used to handle log messages.
- ***Parameters***
  - `file`: The file where the log originated.
  - `line`: The line number where the log originated.
  - `loglevel`: The log level.
  - `log`: The content of the log message.

## Global Functions

### Register Log Handler
```cpp
def registerLogHandler(hanlder：LogHandler);
```
- ***Function***
Registers a custom log handler.
- ***Parameters***
  - `hanlder`: A unique_ptr pointing to the new log handler object.

### Unregister Log Handler
```cpp
def unregisterLogHandler()
```
- ***Function***
Unregisters the current log handler and enables the default log handler.

### Set Log Level
```cpp
def setLogLevel(level: LogLevel)
```
- ***Function***
Sets the log level. Logs below this level will not be output.
- ***Parameters***
  - `level`: The log level to be set.

## Usage Example

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