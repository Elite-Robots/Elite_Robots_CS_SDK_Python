# RobotException

## Overview

When an exception occurs during the robot's operation, it will send an exception message to the client through the primary port. The SDK parses this message to obtain exception information. For detailed descriptions of exceptions, please refer to the content in ` CS_UserManual_Robot_State_Message_v2.14.2.xlsx`.

---

# RobotException Class

## Overview

The base class for robot exceptions, representing common exception properties such as type and timestamp.

## Import

```py
from elite_cs_sdk import RobotError
from elite_cs_sdk import RobotRuntimeException
from elite_cs_sdk import RobotExceptionType
from elite_cs_sdk import RobotErrorType
```

## Exception Type

```py
class RobotExceptionType:
    """
    Members:
    
      ROBOT_DISCONNECTED : Robot disconnected
    
      ROBOT_ERROR : Robot hardware or system error
    
      SCRIPT_RUNTIME : Robot script exception
    """
```

* `ROBOT_DISCONNECTED` : Represents a disconnection from the robot.
* `ROBOT_ERROR`: Represents a robot operation error.
* `SCRIPT_RUNTIME`: Represents a runtime error, such as script execution or syntax issues.

## Constructor

### ***Constructor***

```py
def __init__(type: RobotExceptionType, ts: int)
```

* **Description**: Constructs an exception object with a specific type and timestamp.
* **Parameters**:

  * `type`: The type of exception (ROBOT_ERROR or SCRIPT_RUNTIME).
  * `ts`: Timestamp in microseconds.

## Interface Methods

### Get Exception Type

```cpp
def getType() -> RobotExceptionType
```

* **Returns**: Exception type.

---

### Get Timestamp

```py
def getTimestamp() -> int
```

* **Returns**: The timestamp when the exception occurred (in microseconds).

---

# RobotError Class

## Overview

Represents an error exception on the robot side, including error codes, source modules, severity level, and additional data. It describes errors at the controller or hardware level.

## Error Source Enumeration

```py
class RobotErrorType:
    """
    Members:
    
      SAFETY
    
      GUI
    
      CONTROLLER
    
      RTSI
    
      JOINT
    
      TOOL
    
      TP
    
      JOINT_FPGA
    
      TOOL_FPGA
    """
```

* `SAFETY`: Safety module
* `GUI`: Teach pendant UI
* `CONTROLLER`: Controller
* `RTSI`:  RTSI protocol
* `JOINT`: Joint module
* `TOOL`: Tool module
* `TP`: Teach pendant
* `JOINT_FPGA`: Joint FPGA
* `TOOL_FPGA`: Tool FPGA

---

## Error Level Enumeration

```py
class RobotErrorLevel:
    """
    Members:
    
      INFO
    
      WARNING
    
      ERROR
    
      FATAL
    """
```

* `INFO`: Informational
* `WARNING`: Warning
* `ERROR`: Error
* `FATAL`: Fatal error

---

## Error Data Type Enumeration

```py
class RobotErrorDataType:
    """
    Members:
    
      NONE
    
      UNSIGNED
    
      SIGNED
    
      FLOAT
    
      HEX
    
      STRING
    
      JOINT
    """
```

* `NONE`: Unknown or no type, `uint32_t`
* `UNSIGNED`: Unsigned integer, `uint32_t`
* `SIGNED`: Signed integer, `int32_t`
* `FLOAT`: Floating-point number, `float`
* `HEX`: Hexadecimal data, unsigned integer (hexadecimal representation recommended)
* `STRING`: String
* `JOINT`: Joint exception data, `int32_t`

---

## Constructor

```py
def __init__(ts: int, code: int, sc: int, es: RobotErrorType, el: RobotErrorLevel, et: RobotErrorDataType, data: int | float | str)
```

* **Description**: Creates a robot error object.
* **Parameters**:

  * `ts`: Timestamp.
  * `code`: Error code.
  * `sc`: Sub-error code.
  * `es`: Error source module.
  * `el`: Error level.
  * `et`: Error data type.
  * `data`: Additional data (e.g., string, integer, float).

---

## Interface Methods

```py
def getErrorCode() -> int:
  ...
def getSubErrorCode() -> int:
  ...
def getErrorSouce() -> RobotErrorType:
  ...
def getErrorLevel() -> RobotErrorLevel:
  ...
def getErrorDataType() -> RobotErrorDataType:
  ...
def getData() -> int | float | str:
  ...
```

* **Description**: Retrieves the error code, sub-code, source, severity level, data type, and data respectively.

---

# RobotRuntimeException Class

## Overview

Represents runtime exceptions in the robot, such as syntax or execution errors in scripts. It contains line/column information and error messages.

## Constructor

```py
def __init__(self, ts: int, line: int, column: int, msg: str)
```

* **Description**: Constructs a runtime exception object.
* **Parameters**:

  * `ts`: Timestamp.
  * `line`: Line number where the error occurred.
  * `column`: Column number of the error.
  * `msg`: Error message.

---

## Interface Methods

```py
def getLine() -> int:
  ...
def getColumn() -> int:
  ...
def getMessage() -> str:
  ...
```

* **Description**: Returns the line number, column number, and error message respectively.

---

# Exception Pointer Types

These are shared pointer types for the exception classes, typically used for memory management and callback registration.

```cpp
using RobotExceptionSharedPtr = std::shared_ptr<RobotException>;
using RobotErrorSharedPtr = std::shared_ptr<RobotError>;
using RobotRuntimeExceptionSharedPtr = std::shared_ptr<RobotRuntimeException>;
```

