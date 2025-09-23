# Primary Port

## Introduction
The SDK provides interfaces for connecting to the robot's port 30001, sending scripts, and a framework for parsing the data from port 30001. Only partial data packets are parsed in the SDK. If you want to parse other data packets, you need to write the parsing code manually.

# PrimaryPortInterface Class

## Introduction
This interface provides methods for communicating with the robot's primary port interface.

## Import
```python
from elite_cs_sdk import PrimaryClientInterface, PrimaryPackage, KinematicsInfo
from elite_cs_sdk import RobotError, RobotRuntimeException
```

---

## Communication

### ***Connection***
```python
def connect(ip: str, port = 30001) -> bool
```
- ***Function***
Connects to the robot's port 30001 (by default).
- ***Parameters***
    - ip: The IP address of the robot.
    - timeout_ms: Sets the timeout for the robot to read the next instruction. If it is less than or equal to 0, it will wait indefinitely.
- ***Return Value***: Returns true if successful, and false if failed.

- ***Note***
    1. Warning: Repeated calls to this function without intermediate disconnect() will force-close the active connection.
    2. Usage constraint: Call rate must be ≤ 2Hz (once per 500ms minimum interval).

---

### ***Disconnection***
```python
def disconnect()
```
- ***Function***
Disconnects from the robot.

- ***Note***

    Suggest adding ~500ms delay between this function and connect calls.

---

### ***Send Script***
```python
def sendScript(script: str) -> bool
```
- ***Function***
Sends an executable script to the robot.
- ***Parameters***
    - script: The script to be sent.
- ***Return Value***: Returns true if the sending is successful, and false if failed.

---

### ***Get Data Packet***
```python
def getPackage(pkg: PrimaryPackage, timeout_ms: int) -> bool
```
- ***Function***
Retrieves and parses the robot's data packet.
- ***Parameters***
    - pkg: The data packet to be retrieved.
    - timeout_ms: The waiting timeout.
- ***Return Value***: Returns true if the retrieval is successful, and false if failed.

---

### ***Get local IP***
```python
def getLocalIP() -> str
```
- ***Function***

    Get local IP address

- ***Return Value***：Local IP address. If empty, connection had some errors.

---

### ***Register Robot Exception Callback***
```python
def registerRobotExceptionCallback(cb: Callable[[RobotException]])
```

- ***Functionality***
    Registers a callback function for robot exceptions. This callback will be invoked when an exception message is received from the robot's primary port. The callback function takes a parameter of type `RobotExceptionSharedPtr`, representing the exception information.

- ***Parameters***
    - `cb`: The callback function to handle received robot exceptions. The parameter is a shared pointer to a robot exception (see: [RobotException](./RobotException.en.md)).

# PrimaryPackage Class

## Introduction
This class is mainly used to be inherited to obtain the data from the Primary port.
The SDK does not provide parsing for all data packets. If you need other data packets, you can refer to the implementation of `KinematicsInfo` in `RobotConfPackage.hpp` to write the data packet parsing code you need. Refer to the Elite official document "CS_User Manual_Robot Status Message.xlsx" for the message format.

## Header File of PrimaryPackage
```python
#include <Elite/PrimaryPackage.hpp>
```

## Constructor of the PrimaryPackage Class
### ***Constructor***
```python
def __init__(type: int)
```
- ***Function***
Initializes the data.
- ***Parameters***
    - type: The type of the data packet (refer to the Elite official document: CS_User Manual_Robot Status Message.xlsx).

---

## Pure Virtual Function

### Parse Message
```python
def parser(len: int, data: bytes)
```
- ***Function***
The specific implementation is to be completed by subclasses. It parses the sub-message of the robot status message from the Primary port. When an instance of a subclass is passed as a parameter to `PrimaryPortInterface::getPackage()`, this function will be called.
- ***Parameters***
    - len: The length of the sub-message.
    - iter: The sub-message bytes.

---

## Others

### ***Get Message Type***
```python
def getType() -> int
```
- ***Function***
Gets the type of the data packet.
- ***Return Value***: The type of the data packet.

---

## Internal Use in the SDK
### Wait for Update
```python
def waitUpdate(timeout_ms: int) -> bool
```
- ***Function***
Waits for the data packet to be updated. It is called in the `getPackage()` function.
- ***Parameters***
    - timeout_ms: The timeout.
- ***Return Value***: Returns true if it does not time out, and false if it times out.

---

# KinematicsInfo Class

## Introduction
This is for parsing the kinematics data packet in the robot configuration data. `PrimaryPackage` is the parent class of this interface. In addition to the methods in the `PrimaryPackage` class, the main content of this interface is the robot's DH parameters.

## KinematicsInfo 接口
```python
from elite_cs_sdk.primary_client import KinematicsInfo
```

## DH Parameters

- `dh_a_ : list[6]`

- `dh_d_: list[6]`

- `dh_alpha_: list[6]`