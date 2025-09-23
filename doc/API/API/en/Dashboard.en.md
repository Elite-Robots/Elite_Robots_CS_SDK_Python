# DashboardClient Class

## Introduction
The DashboardClient class provides an interface for interacting with the robot's dashboard server, which is used to execute various robot control commands and query the status.

## Import
```python
from elite_cs_sdk import DashboardClientInterface
```

## Interfaces

### Connect to the Server
```python
def connect(ip: str, port = 29999) -> bool
```
- ***Function***
Connects to the dashboard server.
- ***Parameters***
    - ip: The IP address of the dashboard server.
    - port: The port of the dashboard server (default is 29999).
- ***Return Value***: Returns true if the connection is successful, and false if it fails.

---

### Disconnect
```python
def disconnect()
```
- ***Function***
Disconnects from the dashboard server.

---

### Brake Release
```python
def brakeRelease() -> bool
```
- ***Function***
Releases the robot's brakes.
- ***Return Value***: Returns true if the operation is successful, and false if it fails.

---

### Close the Safety Pop-up Window
```python
def closeSafetyDialog()
```
- ***Function***
Closes the safety message pop-up window.
- ***Return Value***: Returns true if the operation is successful, and false if it fails.

---

### Connection Check
```python
def echo() -> bool
```
- ***Function***
Checks the connection status with the dashboard shell server.
- ***Return Value***: Returns true if the robot responds successfully.

---

### Get Help Information
```python
def help(cmd: str) -> str
```
- ***Function***
Gets the help information for the specified command.
- ***Parameters***
    - cmd: The command that needs help.
- ***Return Value***: The help string for the command.

---

### Add Log
```python
def log(const std::string& message) -> bool
```
- ***Function***
Adds a log message ('\n' or '\r' in the message will be replaced with "\\n" and "\\r").
- ***Parameters***
    - message: The content of the log.
- ***Return Value***: Returns true if the operation is successful, and false if it fails.

---

### Pop-up/Close the Message Box
```python
def popup(arg : str, message = "") -> bool
```
- ***Function***
Pops up or closes the message box.
- ***Parameters***
    - arg:
        - "-c": Closes the message box.
        - "-s": Pops up the message box.
    - message: The content of the message (optional).
- ***Return Value***: Returns true if the operation is successful, and false if it fails.

---

### Quit the Dashboard
```python
def quit()
```
- ***Function***
Quits the dashboard and disconnects the connection.

---

### Reboot the Robot
```python
def reboot()
```
- ***Function***
Reboots the robot and disconnects the connection.

---

### Get the Robot Type
```python
def robotType() -> str
```
- ***Function***

    Gets the type of the robot.

- ***Return Value***: The string representing the robot type.

---

### Get the robot serial number
```python
def robotSerialNumber() -> str
```
- ***Function***

    Get the robot serial number

- ***Return Value**: The robot serial number

---

### Get the robot ID
```python
def robotID() -> str
```
- ***Function***

    Get the robot ID

- ***Return Value***: The robot ID

---

### Power On the Robot
```python
def powerOn() -> bool
```
- ***Function***
Powers on the robot.
- ***Return Value***: Returns true if the operation is successful, and false if it fails.

---

### Power Off the Robot
```python
def powerOff() -> bool
```
- ***Function***
Powers off the robot.
- ***Return Value***: Returns true if the operation is successful, and false if it fails.

---

### Shut Down the Robot
```python
def shutdown()
```
- ***Function***
Shuts down the robot and disconnects the connection.

---

### Get the Speed Scaling
```python
def speedScaling() -> int
```
- ***Function***
Gets the percentage of the robot's speed scaling.
- ***Return Value***: The percentage of the speed scaling.

---

### Get the Robot Mode
```python
def robotMode() -> RobotMode
```
- ***Function***
Gets the current mode of the robot.
- ***Return Value***: An enumeration value of RobotMode.

---

### Get the Safety Mode
```python
def safetyMode() -> SafetyMode
```
- ***Function***
Gets the safety mode.
- ***Return Value***: An enumeration value of SafetyMode.

---

### Restart the Safety System
```python
def safetySystemRestart() -> bool
```
- ***Function***
Restarts the safety system.
- ***Return Value***: Returns true if the operation is successful, and false if it fails.

---

### Get the Task Status
```python
def runningStatus() -> TaskStatus
```
- ***Function***
Gets the running status of the task.
- ***Return Value***: An enumeration value of TaskStatus.

---

### Unlock the Protective Stop
```python
def unlockProtectiveStop() -> bool
```
- ***Function***
Unlocks the robot's protective stop.
- ***Return Value***: Returns true if the operation is successful, and false if it fails.

---

### Get the Command Usage
```python
def usage(cmd: str) ->str
```
- ***Function***
Queries the usage of the dashboard shell command.
- ***Parameters***
    - cmd: The command to be queried.
- ***Return Value***: The string of the command usage.

---

### Get the Dashboard Version
```python
def version() -> str
```
- ***Function***
Gets the version information of the dashboard.
- ***Return Value***: The string of the version information.

---

### Load the Robot Configuration
```python
def loadConfiguration(path: str) -> bool
```
- ***Function***
Loads the robot configuration file.
- ***Parameters***
    - path: The path of the configuration file.
- ***Return Value***: Returns true if the loading is successful, and false if it fails.

---

### Get the Configuration Path
```python
def configurationPath() -> str
```
- ***Function***
Gets the path of the current configuration file.
- ***Return Value***: The string of the configuration file path.

---

### Check the Configuration Modification
```python
def isConfigurationModify() -> bool
```
- ***Function***
Checks whether the configuration has been modified.
- ***Return Value***: Returns true if it has been modified.

---

### Run the Program
```python
def playProgram() -> bool
```
- ***Function***
Runs the program.
- ***Return Value***: Returns true if the operation is successful, and false if it fails.

---

### Pause the Program
```python
def pauseProgram() -> bool
```
- ***Function***
Pauses the program.
- ***Return Value***: Returns true if the operation is successful, and false if it fails.

---

### Stop the Program
```python
def stopProgram() -> bool
```
- ***Function***
Stops the program.
- ***Return Value***: Returns true if the operation is successful, and false if it fails.

---

### Set the Speed Scaling
```python
def setSpeedScaling(scaling: int) -> bool
```
- ***Function***
Sets the speed scaling.
- ***Parameters***
    - scaling: The speed scaling to be set.
- ***Return Value***: Returns true if the setting is successful, and false if it fails.

---

### Get the Task Path
```python
def getTaskPath() -> str
```
- ***Function***
Gets the current task path.
- ***Return Value***: The string of the relative task path.

---

### Load the Task
```python
def loadTask(path: str) -> bool
```
- ***Function***
Loads the task.
- ***Parameters***
    - path: The path of the task.
- ***Return Value***: Returns true if the loading is successful, and false if it fails.

---

### Get the Task Status
```python
def getTaskStatus() -> TaskStatus
```
- ***Function***
Gets the task status.
- ***Return Value***: An enumeration value of TaskStatus.

---

### Check the Task Running Status
```python
def taskIsRunning() -> bool
```
- ***Function***
Checks whether the task is running.
- ***Return Value***: Returns true if it is running.

---

### Check the Task Saving Status
```python
def isTaskSaved() -> bool
```
- ***Function***
Checks whether the task has been saved.
- ***Return Value***: Returns true if it has been saved.

---

### Send and Receive the Command
```python
def sendAndReceive(cmd: str) -> str
```
- ***Function***
Sends a dashboard command and receives the response.
- ***Parameters***
    - cmd: The dashboard command to be sent.
- ***Return Value***: The string of the command response.

---