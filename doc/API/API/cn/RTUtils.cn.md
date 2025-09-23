# 实时工具

一些能提升实时性的接口

## 导入
```py
import elite_cs_sdk
```

## 接口

### 设置实时线程
```py
def setCurrentThreadFiFoScheduling(priority: int) -> bool
```

- ***功能***

    设置当前线程为FIFO调度，并设置优先级

- ***参数***

  - `priority`: 优先级

- ***返回值***
    - `true` ： 设置成功
    - `false` ：设置失败

### 获取线程最高优先级
```py
def getThreadFiFoMaxPriority() -> int
```

- ***功能***

    获取线程最高优先级

- ***返回值***：最高优先级

### 绑定线程到CPU核心
```py
def bindCurrentThreadToCpus(cpu: int) -> bool
``` 

- ***功能***

    绑定当前线程到CPU核心

- ***参数***

  - `cpu`: CPU核心编号

- ***返回值***
    - `true` ： 绑定成功
    - `false` ：绑定失败
