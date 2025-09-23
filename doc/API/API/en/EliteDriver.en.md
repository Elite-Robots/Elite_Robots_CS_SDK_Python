# EliteDriver Class

## Introduction
The EliteDriver is the main class for data interaction with the robot. It is responsible for establishing all necessary socket connections and handling the data exchange with the robot. The EliteDriver sends control scripts to the robot. After the robot runs the control script, it will establish communication with the EliteDriver, receive motion data, and send the motion results when necessary.

## Import
```python
from elite_cs_sdk import EliteDriver, EliteDriverConfig
```

## Constructor

### ***Constructor***
```python
def __init__(config: EliteDriverConfig)
```
- ***Function***

    Creates an EliteDriver object and initializes necessary connections for robot communication.  
    This function will throw exceptions in the following cases:  
    1. TCP server creation fails (typically due to port being occupied).
    2. Failed to connect to the robot's primary port.

- ***Parameters***
    - config: Configuration, refer to [Configuration](./EliteDriverConfig.en.md)

---

## Motion Control

### ***Control Joint Position***
```cpp
def writeServoj(pos: list, timeout_ms: int, cartesian = False, queue_mode = False) -> bool
```
- ***Function***
Sends a servo motion instruction to the robot.
- ***Parameters***
    - pos: The target position.

    - timeout_ms: Sets the timeout for the robot to read the next instruction. If it is less than or equal to 0, it will wait indefinitely.

    - `cartesian`: Set to `true` if sending Cartesian coordinates, `false` for joint-based positions.  
    
    - `queue_mode`: Set to `true` to enable queue mode, `false` otherwise.  
        > **Queue Mode**: In this mode, control commands are queued and executed sequentially. A specified number of commands are pre-stored before motion starts. Note that this introduces additional latency.
- ***Return Value***: Returns true if the instruction is sent successfully, and false if it fails.

---

### ***Control End-effector Velocity***
```python
def writeSpeedl(vel: list, timeout_ms: int) -> bool
```
- ***Function***
Sends a linear velocity control instruction to the robot.
- ***Parameters***
    - vel: The linear velocity [x, y, z, rx, ry, rz].
    - timeout_ms: Sets the timeout for the robot to read the next instruction. If it is less than or equal to 0, it will wait indefinitely.
- ***Return Value***: Returns true if the instruction is sent successfully, and false if it fails.

---

### ***Make the Robot Idle***
```python
def writeIdle(timeout_ms: int) -> bool
```
- ***Function***
Sends an idle instruction. If the robot is in motion, it will make the robot stop moving.
- ***Parameters***
    - timeout_ms: Sets the timeout for the robot to read the next instruction. If it is less than or equal to 0, it will wait indefinitely.
- ***Return Value***: Returns true if the instruction is sent successfully, and false if it fails.

---

### ***Freedrive***
```python
def writeFreedrive(action: FreedriveAction, timeout_ms: int) -> bool
```
- ***Function***

Send commands for Freedrive mode, such as enabling and stopping Freedrive.

- ***Parameters***
    - action: Freedrive action, including: START, END, NOOP
    - timeout_ms: Set the timeout for the robot to read the next instruction. If it is less than or equal to 0, it will wait indefinitely.

- *** Note***: After writing the 'START' action, the next instruction needs to be written within the timeout period, which can be written as' NOOP '.

---

## Trajectory Motion

### ***Set Trajectory Motion Result Callback***
```python
def setTrajectoryResultCallback(cb: Callable[[TrajectoryMotionResult]])
```
- ***Function***
Registers a callback function for when the trajectory is completed.
One way to control the robot is to send all the waypoints to the robot at once. When the execution is completed, the callback function registered here will be triggered.
- ***Parameters***
    - cb: The callback function when the execution is completed.

---

### ***Write Trajectory Waypoint***
```python
def writeTrajectoryPoint(positions : list, time : float, blend_radius: float, cartesian: bool) -> bool
```
- ***Function***
Writes a trajectory waypoint to a specific socket.
- ***Parameters***
    - positions: The waypoint.
    - time: The time to reach the waypoint.
    - blend_radius: The transition radius between two waypoints.
    - cartesian: If the sent point is Cartesian, it is True. If it is joint-based, it is false.
- ***Return Value***: Returns true if the instruction is sent successfully, and false if it fails.

---

### ***Trajectory Control Action***
```python
def writeTrajectoryControlAction(action: TrajectoryControlAction, point_number: int, timeout_ms: int) -> bool
```
- ***Function***
Sends a trajectory control instruction.
- ***Parameters***
    - action: The action of trajectory control.
    - point_number: The number of waypoints.
    - timeout_ms: Sets the timeout for the robot to read the next instruction. If it is less than or equal to 0, it will wait indefinitely.
- ***Return Value***: Returns true if the instruction is sent successfully, and false if it fails.
- ***Note***: After writing the `START` action, the next instruction needs to be written within the timeout period, and the `NOOP` can be written.

---

## Robot Configuration
### ***Zero the Force Sensor***
```python
def zeroFTSensor() -> bool
```
- ***Function***
Resets (zeros) the force/torque values measured by the force/torque sensor applied to the tool TCP. The force/torque values are the force/torque vectors obtained by the get_tcp_force(True) script instruction, and these vectors have been processed with load compensation, etc.
After this instruction is executed, the current force/torque measurement value will be saved as the force/torque reference value, and all subsequent force/torque measurement values will be subtracted by this force/torque reference value (zeroed).
Please note that the above force/torque reference value will be updated when this instruction is executed, and will be reset to 0 after the controller is restarted.
- ***Return Value***: Returns true if the instruction is sent successfully, and false if it fails.

---

### ***Set the End-effector Payload***
```python
def setPayload(mass: float, cog: list) -> bool
```
- ***Function***
This command is used to set the mass, center of gravity, and moment of inertia of the robot's payload.
- ***Parameters***
    - mass: The mass of the payload.
    - cog: The coordinates of the center of gravity of the payload (relative to the flange frame).
- ***Return Value***: Returns true if the instruction is sent successfully, and false if it fails.

---

### ***Set the Tool Voltage***
```python
def setToolVoltage(vol: ToolVoltage) -> bool
```
- ***Function***
Sets the tool voltage.
- ***Parameters***
    - vol: The tool voltage.
- ***Return Value***: Returns true if the instruction is sent successfully, and false if it fails.

---

### ***Enable the Force Control Mode***
```python
def startForceMode(reference_frame: list, selection_vector: list, wrench: list, mode: ForceMode, limits: list) -> bool
```
- ***Function***
Enables the force control mode.
- ***Parameters***
    - reference_frame: The pose vector that defines the force control reference coordinate system. This pose vector is defined relative to the base coordinate system. The format is [X,Y,Z,Rx,Ry,Rz], where X, Y, and Z represent the position in meters; Rx, Ry, and Rz represent the pose in radians. Rx, Ry, and Rz are defined using the standard RPY angles. selection_vector: A six-dimensional vector composed of 0s and 1s, used to define the force control axes in the force control coordinate system. 1 represents a force control axis, and 0 represents a non-force control axis.
    - selection_vector: A six-dimensional vector composed of 0s and 1s, used to define the force control axes in the force control coordinate system. 1 represents a force control axis, and 0 represents a non-force control axis.
    - wrench: The target force/torque applied by the robot to the environment. The robot will adjust its pose along/around the force control axes to achieve the specified target force/torque. The format is [Fx,Fy,Fz,Mx,My,Mz], where Fx, Fy, and Fz represent the force applied along the force control axes in Newtons; Mx, My, and Mz represent the torque applied around the force control axes in Newton-meters. This value is invalid for non-force control axes. Due to joint safety limitations, the actual applied force/torque may be lower than the set target force/torque. The actual force/torque applied to the environment can be read using the get_tcp_force script instruction in a separate thread.
    - mode: The force control mode parameter, an integer type data ranging from 0 to 3, used to define the force control mode, that is, how the force control coordinate system is defined or how it is transformed from the force control reference coordinate system.
        - 0: Fixed mode. The force control coordinate system is the force control reference coordinate system.
        - 1: Point mode. The Y-axis of the force control coordinate system points from the origin of the robot TCP to the origin of the force control reference coordinate system.
        - 2: Motion mode. The X-axis of the force control coordinate system is the projection of the TCP movement direction vector on the X-Y plane of the force control reference coordinate system.
    - limits: The speed limit parameter, a six-dimensional vector of float type data. The format is [Vx,Vy,Vz,ωx,ωy,ωz], where Vx, Vy, and Vz represent the maximum allowed TCP speed along the axis in m/s; ωx, ωy, and ωz represent the maximum allowed TCP speed around the axis in rad/s. This speed limit parameter is invalid for non-force control axes, and non-force control axes still execute the original trajectory on that axis.
- ***Return Value***: Returns true if the instruction is sent successfully, and false if it fails.

---

### ***Disable the Force Control Mode***
```python
def endForceMode() -> bool
```
- ***Function***
Disables the force control mode.
- ***Return Value***: Returns true if the instruction is sent successfully, and false if it fails.

---

## Others

### ***Stop External Control***
```python
def stopControl(wait_ms = 10000) -> bool
```
- ***Function***
Sends a stop instruction to the robot. The robot will exit the control script and stop receiving instructions from the PC.

- ***Parameters***
    - wait_ms: Waiting for the robot to disconnect for a certain amount of time(ms). Range >5ms.

- ***Return Value***: 

    Return true for successful instruction sending and false for failure. The following situations will return false:
    - Disconnected from the robot.
    - Not disconnected from the robot during the waiting time.

---

### Is robot connected
```python
def isRobotConnected() -> bool
```
- ***Function***
Checks whether the connection to the robot is established.
- ***Return Value***: Returns true if connected, and false if not connected.

---

### Send Script
```python
def sendScript(script: str) -> bool
```
- ***Function***
Sends an executable script to port 30001 of the robot.
- ***Parameters***
    - script: The script to be sent.
- ***Return Value***: Returns true if the sending is successful, and false if it fails.

---

### ***Send Control Script***
```python
def sendExternalControlScript() -> bool
```
- ***Function***
Sends an external control script to the robot. It can be used to establish or restore control of the robot.
- ***Return Value***: Returns true if the sending is successful, and false if it fails.

---

### ***Get the Data Packet from the Robot's Primary Port***
```python
def getPrimaryPackage(pkg: PrimaryPackage, timeout_ms: int)
```
- ***Function***
Gets the data packet from port 30001 of the robot.
- ***Parameters***
    - pkg: The data packet to be obtained (refer to [PrimaryPort](./PrimaryPort.cn.md)).
    - timeout_ms: The timeout for obtaining the packet.
- ***Return Value***: Returns true if the obtaining is successful, and false if it fails.

---

### ***Reconnect to the Robot's Primary Port***
```python
def primaryReconnect() -> bool
```
- ***Function***
Re-establishes the connection to port 30001 of the robot.
- ***Return Value***: Returns true if successful, and false if it fails. 

---

### ***Register Robot Exception Callback***
```cpp
def registerRobotExceptionCallback(cb: Callable[[RobotExceptionSharedPtr]])
```

- ***Functionality***
    Registers a callback function for robot exceptions. This callback will be invoked when an exception message is received from the robot's primary port. The callback function takes a parameter of type `RobotExceptionSharedPtr`, representing the exception information.

- ***Parameters***
    - `cb`: The callback function to handle received robot exceptions. The parameter is a shared pointer to a robot exception (see: [RobotException](./RobotException.en.md)).