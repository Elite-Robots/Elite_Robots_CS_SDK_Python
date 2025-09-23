# ControllerLog 类

## 简介

ControllerLog 类提供了从机器人控制器下载系统日志的功能。

## 导入
```python
from elite_cs_sdk import ControllerLog
```

## 接口说明

### 下载系统日志
```python
def downloadSystemLog(robot_ip: str, password: str, path: str, progress_cb: Callable[[f_z: int, r_z: int, err: Optional[str]]]) -> bool
```
- ***功能***

  从机器人控制器下载系统日志到本地路径

- ***参数***

- `robot_ip` : 机器人IP地址。
- `password` : 机器人SSH密码。
- `path` : 日志文件保存路径。
- `progress_cb` : 下载进度回调函数。

- ***回调函数参数***

- `f_z`：文件总大小(字节)。
- `r_z`：已下载大小(字节)。
- `err`：错误信息(无错误时为nullptr)。

- ***返回值***

  - `true`: 下载成功
  - `false`: 下载失败

- ***注意事项***

  1. 在Linux系统下，如果未安装`libssh`，需要确保运行SDK的计算机具有`scp`、`ssh`和`sshpass`命令可用
  2. 在Windows系统下，如果未安装libssh，则此接口不可用
