# ControllerLog Class

## Introduction
The ControllerLog class provides the function of downloading system logs from the robot controller.

## Import
```python
from elite_cs_sdk import ControllerLog
```

## Interface Description

### Download System Log
```python
def downloadSystemLog(robot_ip: str, password: str, path: str, progress_cb: Callable[[f_z: int, r_z: int, err: Optional[str]]]) -> bool
```
- ***Function***
Downloads the system log from the robot controller to the local path.
- ***Parameters***
    - `robot_ip`: The IP address of the robot.
    - `password`: The SSH password of the robot.
    - `path`: The saving path of the log file.
    - `progress_cb`: The callback function for the download progress.
- ***Parameters of the Callback Function***
    - `f_z`: The total size of the file (in bytes).
    - `r_z`: The size that has been downloaded (in bytes).
    - `err`: The error information (nullptr when there is no error).
- ***Return Value***
    - `true`: The download is successful.
    - `false`: The download fails.
- ***Notes***
    1. Under the Linux system, if `libssh` is not installed, it is necessary to ensure that the computer running the SDK has the `scp`, `ssh`, and `sshpass` commands available.
    2. Under the Windows system, if `libssh` is not installed, this interface is not available. 