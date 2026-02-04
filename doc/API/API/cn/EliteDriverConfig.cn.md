# EliteDriverConfig

## 定义

``` python
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

## 描述

这个类是用于输入给`EliteDriver`类构造时的配置，用于告知`EliteDriver`类机器人的IP地址、控制脚本路径等参数。

## 参数

- `robot_ip`
    - 类型：`str`
    - 描述：机器人IP。

- `script_file_path`
    - 类型：`str`
    - 描述：机器人控制脚本的模板，依据此模板会生成一个可以被运行的实际脚本。

- `local_ip`
    - 类型：`str`
    - 描述：本地IP，当其为默认值“空字符串”时，`EliteDriver`会尝试自动获取本机IP。
    - 注意：如果机器人无法通过脚本指令`socket_open()`连接到你本地的TCP服务器，那么就需要手动设置这个参数，或者检查网络。

- `headless_mode`：
    - 类型：`bool`
    - 描述：是否以无界面模式运行，使用此模式后，无需使用`External Control`插件。如果此参数为true，那么在构造函数中，将会向机器人的 primary 端口发送一次控制脚本。

- `script_sender_port`
    - 类型：`int`
    - 描述：用于发送控制脚本的端口。如果无法连接此端口，`External Control`插件将会停止运行。

- reverse_port
    - 类型：`int`
    - 描述：反向通信端口。此端口主要发送控制模式以及部分控制数据。

- trajectory_port
    - 类型：`int`
    - 描述：发送轨迹点的端口。

- script_command_port
    - 类型：`int`
    - 描述：发送脚本命令的端口。

- servoj_time
    - 类型：`float`
    - 描述：`servoj()`指令的时间间隔。


- servoj_lookhead_time
    - 类型：`float`
    - 描述：`servoj()`指令瞻时间，范围 [0.03, 0.2] 秒。

- servoj_gain
    - 类型：`int`
    - 描述：伺服增益。

- stopj_acc
    - 类型：`float`
    - 描述：停止运动的加速度 (rad/s²)。

