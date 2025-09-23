# RemoteUpgrade 模块

## 简介

RemoteUpgrade模块提供了机器人控制软件的远程升级功能。

## 导入
```py
import elite_cs_sdk
```

## 升级控制软件

```python
def upgradeControlSoftware(ip: str, file: str, password: str) -> bool
```
- ***功能***

  升级机器人控制软件

- ***参数***

  - `ip`: 机器人IP地址
  - `file`: 升级文件路径
  - `password`: 机器人控制器SSH密码

- ***返回值***

  - `true`: 升级成功
  - `false`: 升级失败

- ***注意事项***

  1. 在Linux系统下，如果未安装`libssh`，需要确保运行SDK的计算机具有`scp`、`ssh`和`sshpass`命令可用
  2. 在Windows系统下，如果未安装libssh，则此接口不可用