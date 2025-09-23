Here's the complete translation of the provided Markdown document into English:

```markdown
# RTSI  

## Introduction

RTSI is the Real-Time Communication Interface for Elite robots, which can be used to obtain robot status and set I/O, etc. The SDK provides two RTSI interfaces: `RtsiClientInterface` and `RtsiIOInterface`. `RtsiClientInterface` requires manual operations for connection, version verification, etc. `RtsiIOInterface` encapsulates most of the interfaces. In actual testing, the real-time performance of `RtsiIOInterface` is slightly worse, while the real-time performance of `RtsiClientInterface` depends on the user's code.

# RtsiClientInterface Class

## Introduction

RTSI Client

## Interfaces
```py
from elite_cs_sdk import RtsiClientInterface
from elite_cs_sdk import RtsiIOInterface
from elite_cs_sdk import RtsiRecipe
```

## Interfaces

### ***Connection***
```py
def connect(ip: str, port = 30004)
```

- ***Function***

    Connect to the robot's RTSI port

- ***Parameters***
    - ip: Robot IP.

    - port: RTSI port.

---

### ***Disconnect***
```py
def disconnect()
```
- ***Function***

    Disconnect from the robot

---

### ***Protocol Version Verification***
```py
def negotiateProtocolVersion(version = 1) -> bool
```
- ***Function***
    
    Send protocol version verification.

- ***Parameters***
    - version: Protocol version
    
- ***Return Value***: Returns true if verification succeeds, otherwise false.

---

### ***Get Elite CS Controller Version***
```py
def getControllerVersion() -> VersionInfo
```
- ***Function***

    Get Elite CS Controller version

- ***Return Value***: Elite CS Controller version

---

### ***Configure Output Subscription Recipe***
```py
def setupOutputRecipe(recipe_list: list[str], frequency = 250) -> RtsiRecipe
```
- ***Function***
    
    Configure output subscription recipe

- ***Parameters***
    - recipe_list: Recipe strings. For specific content, refer to the Elite official document "RTSI User Manual"

    - frequency: Update frequency
    
- ***Return Value***: Output subscription recipe. Returns nullptr if subscription fails.

---

### ***Configure Input Subscription Recipe***
```py
def setupInputRecipe(recipe_list: list[str]) -> RtsiRecipe
```
- ***Function***
    
    Configure input subscription recipe

- ***Parameters***
    - recipe: Recipe strings. For specific content, refer to the Elite official document "RTSI User Manual"
    
- ***Return Value***: Input subscription recipe. Returns nullptr if subscription fails.

---

### ***Start Data Synchronization***
```py
def start() -> bool
```
- ***Function***

    Start data synchronization

- ***Return Value***: true if successful, false if failed.

---

### ***Pause Data Synchronization***
```py
def pause() -> bool
```
- ***Function***

    Pause data synchronization

- ***Return Value***: true if successful, false if failed.

---

### ***Send Input Subscription Recipe***
```py
def send(recipe: RtsiRecipe)
```
- ***Function***

    Send input subscription recipe to set data for the robot

- ***Parameters***
    - recipe: Input subscription recipe.

---

### Receive Output Subscription
```py
def receiveData(recipes :list[RtsiRecipe], read_newest = False) -> int
```
- ***Function***

    Receive output subscription recipe data.

- ***Parameters***
    - recipes: List of output subscription recipes. Only one recipe is received, and the recipe data in the list is updated. It is recommended to set read_newest to false.

    - read_newest: Whether to receive the newest data packet (there may be multiple packets in the system cache).

- ***Return Value***: ID of the received recipe.

---

### Receive Output Subscription
```py
def receiveData(recipe : RtsiRecipe, read_newest = False) -> bool
```
- ***Function***

    Receive output subscription recipe data.

- ***Parameters***
    - recipe: Output subscription recipe. In the case of multiple recipes, if the received recipe is not the input recipe, the data of this recipe will not be updated.

    - read_newest: Whether to receive the newest data packet (there may be multiple packets in the system cache).

- ***Return Value***: Returns true if the recipe is successfully updated.

---

### ***Connection Status***
```py
def isConnected() -> bool
```

- ***Function***
    Connection status

- ***Return Value***: Returns true if the connection is normal, otherwise false.

---

### ***Synchronization Status***
```py
def isStarted() -> bool
```
- ***Function***
    Whether robot data synchronization has started

- ***Return Value***: Returns true if yes, false if no.

---

### ***Readable Status***
```py
def isReadAvailable() -> bool
```

- ***Function***
   Whether there is readable data. Typically used to determine if there is readable data in the buffer when receiving robot status.

- ***Return Value***: Returns true if yes, false if no.

---

# RtsiIOInterface Class

## Introduction

Inherits the `RtsiClientInterface` class. This interface further encapsulates `RtsiClientInterface` and internally starts a thread for robot data synchronization.

## Constructor and Destructor

### ***Constructor***
```py
def __init__(output_recipe_file: str, input_recipe_file: str, frequency: float)
```
- ***Function***

    Initialize data and read the `output_recipe_file` and `input_recipe_file` files to obtain subscription recipes. The format of the recipe files is:  
    ```
    Subscription Item 1
    Subscription Item 2
    ```

- ***Parameters***
    - output_recipe_file: Path to the output recipe file.

    - input_recipe_file: Path to the input recipe file.

    - frequency: Data synchronization frequency.

---

## Interfaces

### ***Connection***
```py
def connect(ip: str) -> bool
```
- ***Function***

    Connect to the robot's RTSI port, perform version verification, obtain robot controller version information, configure input and output subscription recipes, and start the data synchronization thread.

- ***Parameters***
    - ip: Robot IP.


- ***Return Value***: Returns true if successful, false if failed.

---

### ***Disconnect***
```py
def disconnect()
```
- ***Function***

    Disconnect the socket from the robot and terminate the data synchronization thread.

---

### Get Controller Version
```py
def getControllerVersion() -> VersionInfo
```
- ***Function***

    Get controller version information

- ***Return Value***: VersionInfo object containing major version, minor version, patch number, and build number

---

### Set Speed Scaling
```py
def setSpeedScaling(scaling: float) -> bool
```
- ***Function***

    Set robot speed scaling

- ***Parameters***

    - scaling: Target speed scaling

- ***Return Value***: Returns true if successful, false if failed

---

### Set Standard Digital IO
```py
def setStandardDigital(index: int, level: bool) -> bool
```
- ***Function***

    Set standard digital IO level

- ***Parameters***

    - index: Standard digital IO index
    - level: High/Low level

- ***Return Value***: Returns true if successful, false if failed

---

### Set Configurable Digital IO
```py
def setConfigureDigital(index: int, level: bool) -> bool
```
- ***Function***

    Set configurable digital IO level

- ***Parameters***

    - index: Configurable digital IO index
    - level: High/Low level

- ***Return Value***: Returns true if successful, false if failed

---

### Set Analog Output Voltage
```py
def setAnalogOutputVoltage(index: int, value: float) -> bool
```
- ***Function***

    Set analog output voltage

- ***Parameters***

    - index: Analog IO index
    - value: Voltage value (unit: V, range [0,10]V)

- ***Return Value***: Returns true if successful, false if failed

---

### Set Analog Output Current
```py
def setAnalogOutputCurrent(index: int, value: float) -> bool
```
- ***Function***

    Set analog output current

- ***Parameters***

    - index: Analog IO index
    - value: Current value (unit: A, range [0.004,0.2]A)

- ***Return Value***: Returns true if successful, false if failed

---

### Set External Force Torque
```py
def setExternalForceTorque(value: list) -> bool
```
- ***Function***

    Input external force sensor data (effective when ft_rtsi_input_enable is set to true)

- ***Parameters***

    - value: External force sensor data

- ***Return Value***: Returns true if successful, false if failed

---

### Set Tool Digital Output
```py
def setToolDigitalOutput(index: int, level: bool) -> bool
```
- ***Function***

    Set tool digital output level

- ***Parameters***

    - index: Tool output IO index
    - level: Level value

- ***Return Value***: Returns true if successful, false if failed

---

### Get Timestamp
```py
def getTimestamp() -> float
```
- ***Function***

    Get timestamp

- ***Return Value***: Timestamp (unit: seconds)

---

### Get Payload Mass
```py
def getPayloadMass() -> float
```
- ***Function***

    Get end-effector payload mass

- ***Return Value***: Payload mass (unit: kg)

---

### Get Payload Center of Gravity
```py
def getPayloadCog() -> list
```
- ***Function***

    Get end-effector payload center of gravity

- ***Return Value***: Payload center of gravity coordinates (unit: m)

---

### Get Script Control Line Number
```py
def getScriptControlLine() -> int
```
- ***Function***

    Get running script line number

- ***Return Value***: Script line number

---

### Get Target Joint Positions
```py
def getTargetJointPositions() -> list
```
- ***Function***

    Get target joint positions

- ***Return Value***: Joint positions (unit: rad)

---

### Get Target Joint Velocity
```py
def getTargetJointVelocity() -> list
```
- ***Function***

    Get target joint velocity

- ***Return Value***: Joint velocity (unit: rad/s)

---

### Get Actual Joint Positions
```py
def getActualJointPositions() -> list
```
- ***Function***

    Get actual joint positions

- ***Return Value***: Joint positions (unit: rad)

---

### Get Actual Joint Torques
```py
def getActualJointTorques() -> list
```
- ***Function***

    Get actual joint torques

- ***Return Value***: Joint torques (unit: N*m)

---

### Get Actual Joint Velocity
```py
def getActualJointVelocity() -> list
```
- ***Function***

    Get actual joint velocity

- ***Return Value***: Joint velocity (unit: rad/s)

---

### Get Actual Joint Current
```py
def getActualJointCurrent() -> list
```
- ***Function***

    Get actual joint current

- ***Return Value***: Joint current (unit: A)

---

### Get Actual Joint Temperatures
```py
def getActualJointTemperatures() -> list
```
- ***Function***

    Get actual joint temperatures

- ***Return Value***: Joint temperature (unit: °C)

---

### Get Actual TCP Pose
```py
def getAcutalTpyose() -> list
```
- ***Function***

    Get the actual Cartesian coordinates of the tool

- ***Return Value***: [x, y, z, rx, ry, rz], where x,y,z are position vectors and rx,ry,rz are rotation vectors

---

### Get Actual TCP Velocity
```py
def getAcutalTCPVelocity() -> list
```
- ***Function***

    Get the actual Cartesian velocity of the tool

- ***Return Value***: [x, y, z, rx, ry, rz]/s, where x,y,z are position vectors and rx,ry,rz are rotation vectors

---

### Get Actual TCP Force
```py
def getAcutalTCPForce() -> list
```
- ***Function***

    Get the generalized force of the TCP (minus the force data caused by the payload)

- ***Return Value***: TCP force vector

---

### Get Target TCP Pose
```py
def getTargetTpyose() -> list
```
- ***Function***

    Get the target Cartesian coordinates of the tool

- ***Return Value***: [x, y, z, rx, ry, rz], where x,y,z are position vectors and rx,ry,rz are rotation vectors

---

### Get Target TCP Velocity
```py
def getTargetTCPVelocity() -> list
```
- ***Function***

    Get the target Cartesian velocity of the tool

- ***Return Value***: [x, y, z, rx, ry, rz], where x,y,z are position vectors and rx,ry,rz are rotation vectors

---

### Get Digital Input Bits
```py
def getDigitalInputBits() -> int
```
- ***Function***

    Get the bit values of all digital input IOs

- ***Return Value***:
    - bits 0-15: Standard digital input
    - bits 16-24: Configurable digital input
    - bits 24-28: Tool digital input

---

### Get Digital Output Bits
```py
def getDigitalOutputBits() -> int
```
- ***Function***

    Get the bit values of all digital output IOs

- ***Return Value***:
    - bits 0-15: Standard digital input
    - bits 16-24: Configurable digital input
    - bits 24-28: Tool digital input

---

### Get Robot Mode
```py
def getRobotMode() -> RobotMode
```
- ***Function***

    Get robot mode

- ***Return Value***: RobotMode enum value

---

### Get Joint Mode
```py
def getJointMode() -> list
```
- ***Function***

    Get joint modes

- ***Return Value***: Array of 6 JointModes

---

### Get Safety Status
```py
def getSafetyStatus() -> SafetyMode
```
- ***Function***

    Get robot safety mode

- ***Return Value***: SafetyMode enum value

---

### Get Actual Speed Scaling
```py
def getActualSpeedScaling() -> float
```
- ***Function***

    Get actual robot speed scaling

- ***Return Value***: Speed scaling value

---

### Get Target Speed Scaling
```py
def getTargetSpeedScaling() -> float
```
- ***Function***

    Get target robot speed scaling

- ***Return Value***: Speed scaling value

---

### Get Robot Voltage
```py
def getRobotVoltage() -> float
```
- ***Function***

    Get robot voltage (48V)

- ***Return Value***: Voltage value (unit: V)

---

### Get Robot Current
```py
def getRobotCurrent() -> float
```
- ***Function***

    Get robot current

- ***Return Value***: Current value (unit: A)

---

### Get Runtime State
```py
def getRuntimeState() -> TaskStatus
```
- ***Function***

    Get program status

- ***Return Value***: TaskStatus enum value

---

### Get Elbow Position
```py
def getElbowPosition() -> list
```
- ***Function***

    Get real-time robot elbow position

- ***Return Value***: [x, y, z] coordinates

---

### Get Elbow Velocity
```py
def getElbowVelocity() -> list
```
- ***Function***

    Get real-time robot elbow velocity

- ***Return Value***: [x, y, z]/s velocity vector

---

### Get Robot Status
```py
def getRobotStatus() -> int
```
- ***Function***

    Get robot status

- ***Return Value***:
    - bits 0-3: Whether powered on | Whether program is running | Whether free drive button is pressed

---

### Get Safety Status Bits
```py
def getSafetyStatusBits() -> int
```
- ***Function***

    Get robot safety bit status

- ***Return Value***:
    - bits 0-10: Whether in normal mode | Whether in reduced mode | Whether in protective stop | Whether in recovery mode | Whether in safety protective stop | Whether in system emergency stop | Whether in robot emergency stop | Whether in emergency stop | Whether in violation | Whether in fault | Whether stopped due to safety

---

### Get Analog IO Types
```py
def getAnalogIOTypes() -> int
```
- ***Function***

    Get analog IO types

- ***Return Value***:
    - bits 0-3: Analog input 0 (bit 0), analog input 1 (bit 1), analog output 0 (bit 2), analog output 1 (bit 3)
    - 0: Current mode; 1: Voltage mode

---

### Get Analog Input
```py
def getAnalogInput(index: int) -> float
```
- ***Function***

    Get standard analog input value

- ***Parameters***

    - index: Standard analog input index [0,1]

- ***Return Value***: Analog input value (unit: A or V)

---

### Get Analog Output
```py
def getAnalogOutput(index: int) -> float
```
- ***Function***

    Get standard analog output value

- ***Parameters***

    - index: Standard analog output index [0,1]

- ***Return Value***: Analog output value (unit: A or V)

---

### Get IO Current
```py
def getIOCurrent() -> float
```
- ***Function***

    Get motherboard IO current

- ***Return Value***: Current value (unit: A)

---

### Get Tool Mode
```py
def getToolMode() -> ToolMode
```
- ***Function***

    Get tool mode

- ***Return Value***: ToolMode enum value

---

### Get Tool Analog Input Type
```py
def getToolAnalogInputType() -> int
```
- ***Function***

    Get tool analog input IO mode

- ***Return Value***: 0: Current mode, 1: Voltage mode

---

### Get Tool Analog Output Type
```py
def getToolAnalogOutputType() -> int
```
- ***Function***

    Get tool analog output IO mode

- ***Return Value***: 0: Current mode, 1: Voltage mode

---

### Get Tool Analog Input
```py
def getToolAnalogInput() -> float
```
- ***Function***

    Get tool analog input value

- ***Return Value***:
    - Current mode range [0.004-0.02]A
    - Voltage mode range [0-10]V

---

### Get Tool Analog Output
```py
def getToolAnalogOutput() -> float
```
- ***Function***

    Get tool analog output value

- ***Return Value***:
    - Current mode range [0.004-0.02]A
    - Voltage mode range [0-10]V

---

### Get Tool Output Voltage
```py
def getToolOutputVoltage() -> float
```
- ***Function***

    Get tool output voltage

- ***Return Value***: Voltage value (unit: V)

---

### Get Tool Output Current
```py
def getToolOutputCurrent() -> float
```
- ***Function***

    Get tool output current

- ***Return Value***: Current value (unit: A)

---

### Get Tool Output Temperature
```py
def getToolOutputTemperature() -> float
```
- ***Function***

    Get tool output temperature

- ***Return Value***: Temperature value (unit: °C)

---

### Get Tool Digital Mode
```py
def getToolDigitalMode() -> ToolDigitalMode
```
- ***Function***

    Get tool digital mode

- ***Return Value***: Single-pin, dual-pin mode 1, dual-pin mode 2, triple-pin

---

### Get Tool Digital Output Mode
```py
def getToolDigitalOutputMode(index: int) -> ToolDigitalOutputMode
```
- ***Function***

    Get tool digital output mode

- ***Parameters***

    - index: Tool digital index

- ***Return Value***: Push/pull, npn, pnp

---

### Get Output Boolean Registers 0-31
```py
def getOutBoolRegisters0To31() -> int
```
- ***Function***

    Get output values of boolean registers 0-31

- ***Return Value***: Register value

---

### Get Output Boolean Registers 32-63
```py
def getOutBoolRegisters32To63() -> int
```
- ***Function***

    Get output values of boolean registers 32-63

- ***Return Value***: Register value

---

### Get Input Boolean Registers 0-31
```py
def getInBoolRegisters0To31() -> int
```
- ***Function***

    Get input values of boolean registers 0-31

- ***Return Value***: Register value

---

### Get Input Boolean Registers 32-63
```py
def getInBoolRegisters32To63() -> int
```
- ***Function***

    Get input values of boolean registers 32-63

- ***Return Value***: Register value

---

### Get Input Boolean Register
```py
def getInBoolRegister(index: int) -> bool
```
- ***Function***

    Get input value of the specified boolean register

- ***Parameters***

    - index: Boolean register index [64,127]

- ***Return Value***: Register value

---

### Get Output Boolean Register
```py
def getOutBoolRegister(index: int) -> bool
```
- ***Function***

    Get output value of the specified boolean register

- ***Parameters***

    - index: Boolean register index

- ***Return Value***: Register value

---

### Get Input Integer Register
```py
def getInIntRegister(index: int) -> int
```
- ***Function***

    Get input value of the specified integer register

- ***Parameters***

    - index: Integer register index

- ***Return Value***: Register value

---

### Get Output Integer Register
```py
def getOutIntRegister(index: int) -> int
```
- ***Function***

    Get output value of the specified integer register

- ***Parameters***

    - index: Integer register index

- ***Return Value***: Register value

---

### Get Input Double Register
```py
def getInDoubleRegister(index: int)
```
- ***Function***

    Get input value of the specified double register

- ***Parameters***

    - index: Double register index

- ***Return Value***: Register value

---

### Get Output Double Register
```py
def getOutDoubleRegister(index: int) -> float
```
- ***Function***

    Get output value of the specified double register

- ***Parameters***

    - index: Double register index

- ***Return Value***: Register value

---

### Get Output Recipe Value
```py
def getRecipeValue(name: str) -> bool | list | int | float
```
- ***Function***

    Get the value of the specified subscription item in the output recipe.

- ***Parameters***
    - name: Subscription item name

- ***Return Value***: Returns true if successful, false if failed.

---

### Set Output Recipe Value
```py
def setInputRecipeValue(name: str, value: bool | list | int | float)
```
- ***Function***

   Set the value of the specified subscription item in the input recipe.

- ***Parameters***
    - name: Subscription item name

    - out_value: Input value. Note that the type of this value must match the type in the RTSI documentation.

- ***Return Value***: Returns true if successful, false if failed.

---

# RtsiRecipe Class

## Introduction

This interface provides basic operations for RTSI recipes. The RtsiRecipe class can only be obtained through the `RtsiClientInterface::setupOutputRecipe()` and `RtsiClientInterface::setupInputRecipe()` interfaces.

## Interfaces

### ***Get Value***
```py
def getValue(name: str) -> bool | list | int | float
```
- ***Function***

    Get the value of a subscription item in the recipe

- ***Parameters***

    - name: Subscription item name.

    - out_value: Subscription item output value. Note that the type of this value must match the type in the RTSI documentation.

- ***Return Value***: Returns true if successful, false if failed

---

### ***Set Value***
```py
def setValue(name: str, value: bool | list | int | float)
```
- ***Function***

    Set the value of a subscription item in the recipe

- ***Parameters***

    - name: Subscription item name.

    - out_value: Subscription item set value. Note that the type of this value must match the type in the RTSI documentation.

- ***Return Value***: Returns true if successful, false if failed.

---

### Get Recipe
```py
def getRecipe() -> list
```
- ***Function***
    
    Get the list of subscription item names in the recipe

- ***Return Value***: List of subscription item names in the recipe

---

### Get Recipe ID
```py
def getID() -> int
```
- ***Function***
    
    Get recipe ID

- ***Return Value***: Recipe ID
