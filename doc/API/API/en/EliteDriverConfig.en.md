# EliteDriverConfig

## Definition

```python
class EliteDriverConfig:
    def __init__(self) -> None:
        ...
    @property
    def headless_mode(self) -> bool:
        """
        If the driver should be started in headless mode.
        """
    @headless_mode.setter
    def headless_mode(self, arg0: bool) -> None:
        ...
    @property
    def local_ip(self) -> str:
        """
        Local IP-address that the reverse_port and trajectory_port will bound.
        """
    @local_ip.setter
    def local_ip(self, arg0: str) -> None:
        ...
    @property
    def reverse_port(self) -> int:
        """
        Port that will be opened by the driver to allow direct communication between the driver and the robot controller.
        """
    @reverse_port.setter
    def reverse_port(self, arg0: int) -> None:
        ...
    @property
    def robot_ip(self) -> str:
        """
        IP-address under which the robot is reachable.
        """
    @robot_ip.setter
    def robot_ip(self, arg0: str) -> None:
        ...
    @property
    def script_command_port(self) -> int:
        """
        Port used for forwarding script commands to the robot. The script commands will be executed locally on the robot.
        """
    @script_command_port.setter
    def script_command_port(self, arg0: int) -> None:
        ...
    @property
    def script_file_path(self) -> str:
        """
        EliRobot template script file that should be used to generate scripts that can be run.
        """
    @script_file_path.setter
    def script_file_path(self, arg0: str) -> None:
        ...
    @property
    def script_sender_port(self) -> int:
        """
        The driver will offer an interface to receive the program's script on this port.If the robot cannot connect to this port, `External Control` will stop immediately.
        """
    @script_sender_port.setter
    def script_sender_port(self, arg0: int) -> None:
        ...
    @property
    def servoj_gain(self) -> int:
        """
        Servo gain.
        """
    @servoj_gain.setter
    def servoj_gain(self, arg0: int) -> None:
        ...
    @property
    def servoj_lookahead_time(self) -> float:
        """
        Time [S], range [0.03,0.2] smoothens the trajectory with this lookahead time
        """
    @servoj_lookahead_time.setter
    def servoj_lookahead_time(self, arg0: float) -> None:
        ...
    @property
    def servoj_time(self) -> float:
        """
        The duration of servoj motion.
        """
    @servoj_time.setter
    def servoj_time(self, arg0: float) -> None:
        ...
    @property
    def stopj_acc(self) -> float:
        """
        Acceleration [rad/s^2]. The acceleration of stopj motion.
        """
    @stopj_acc.setter
    def stopj_acc(self, arg0: float) -> None:
        ...
    @property
    def trajectory_port(self) -> int:
        """
        Port used for sending trajectory points to the robot in case of trajectory forwarding.
        """
    @trajectory_port.setter
    def trajectory_port(self, arg0: int) -> None:
        ...
```

## Description

This class serves as the configuration input when constructing the `EliteDriver` class, providing parameters such as the robot's IP address and control script path.

## Parameters

- `robot_ip`
    - Type: `str`
    - Description: Robot IP address.

- `script_file_path`
    - Type: `str`
    - Description: Template for the robot control script. An executable script will be generated based on this template.

- `local_ip`
    - Type: `str`
    - Description: Local IP address. When left as default (empty string), `EliteDriver` will attempt to automatically detect the local IP.
    - Note: If the robot cannot connect to your local TCP server via the `socket_open()` script command, you need to manually set this parameter or check your network.

- `headless_mode`:
    - Type: `bool`
    - Description: Whether to run in headless mode。 After using this mode, there is no need to use the 'External Control' plugin. If true, the constructor will send a control script to the robot's primary port once.

- `script_sender_port`
    - Type: `int`
    - Description: Port used for sending control scripts. If this port cannot be connected, the `External Control` plugin will stop immediately.

- `reverse_port`
    - Type: `int`
    - Description: Reverse communication port. This port primarily sends control modes and partial control data.

- `trajectory_port`
    - Type: `int`
    - Description: Port for sending trajectory points.

- `script_command_port`
    - Type: `int`
    - Description: Port for sending script commands.

- `servoj_time`
    - Type: `float`
    - Description: Time interval for `servoj()` command.

- `servoj_lookhead_time`
    - Type: `float`
    - Description: Lookahead time for `servoj()` command, range [0.03, 0.2] seconds.

- `servoj_gain`
    - Type: `int`
    - Description: Servo gain.

- `stopj_acc`
    - Type: `float`
    - Description: Acceleration for stopping motion (rad/s²).