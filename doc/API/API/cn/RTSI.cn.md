# RTSI

## 简介

RTSI 是 Elite 机器人的实时通讯接口，可以获取机器人状态、设置IO等。SDK中提供了RTSI的两种接口：`RtsiClientInterface`和`RtsiIOInterface`。`RtsiClientInterface`需要手动操作连接、版本验证等。`RtsiIOInterface`则封装了大部分的接口。实际测试中`RtsiIOInterface`的实时性要差一点，而`RtsiClientInterface`的实时性取决于使用者的代码。

# RtsiClientInterface 类

## 简介

RTSI 客户端

## 导入
```py
from elite_cs_sdk import RtsiClientInterface
from elite_cs_sdk import RtsiIOInterface
from elite_cs_sdk import RtsiRecipe
```

### ***连接***
```py
def connect(ip: str, port = 30004)
```

- ***功能***

    连接到机器人的RTSI端口

- ***参数***
    - ip：机器人IP。

    - port：RTSI端口。

---

### ***断开连接***
```py
def disconnect()
```
- ***功能***

    断开与机器人的连接

---

### ***协议版本验证***
```py
def negotiateProtocolVersion(version = 1) -> bool
```
- ***功能***
    
    发送协议版本验证。

- ***参数***
    - version：协议版本
    
- ***返回值***：验证成功返回 true，否则返回 false。

---

### ***获取Elite CS Controller版本***
```py
def getControllerVersion() -> VersionInfo
```
- ***功能***

    获取Elite CS Controller版本

- ***返回值***：Elite CS Controller版本

---

### ***配置输出订阅配方***
```py
def setupOutputRecipe(recipe_list: list[str], frequency = 250) -> RtsiRecipe
```
- ***功能***
    
    配置输出订阅配方

- ***参数***
    - recipe_list：配方字符串。具体内容参考Elite官方文档“RTSI用户手册”

    - frequency：更新频率
    
- ***返回值***：输出订阅配方。如果为nullptr表示订阅失败。

---

### ***配置输入订阅配方***
```py
def setupInputRecipe(recipe_list: list[str]) -> RtsiRecipe
```
- ***功能***
    
    配置输入订阅配方

- ***参数***
    - recipe：配方字符串。具体内容参考Elite官方文档“RTSI用户手册”
    
- ***返回值***：输入订阅配方。如果为nullptr表示订阅失败。

---

### ***启动数据同步***
```py
def start() -> bool
```
- ***功能***

    启动数据同步

- ***返回值***：成功为true，失败为false。

---

### ***暂停数据同步***
```py
def pause() -> bool
```
- ***功能***

    暂停数据同步

- ***返回值***：成功为true，失败为false。

---

### ***发送输入订阅的配方***
```py
def send(recipe: RtsiRecipe)
```
- ***功能***

    发送输入订阅的配方，设置数据给机器人

- ***参数***
    - recipe：输入订阅配方。

---

### 接收输出订阅
```py
def receiveData(recipes :list[RtsiRecipe], read_newest = False) -> int
```
- ***功能***

    接收输出订阅的配方数据。

- ***参数***
    - recipes：输出订阅的配方列表。仅接收一个配方，并更新列表中配方的数据。建议read_newest为false。

    - read_newest：是否接收最新的数据包。（系统缓存中可能多个数据包）

- ***返回值***：接收到的配方ID。

---

### 接收输出订阅
```py
def receiveData(recipe : RtsiRecipe, read_newest = False) -> bool
```
- ***功能***

    接收输出订阅的配方数据。

- ***参数***
    - recipe：输出订阅的配方。多配方的情况下，如果接收到的不是输入的配方，则不会更新此配方的数据。

    - read_newest：是否接收最新的数据包。（系统缓存中可能多个数据包）

- ***返回值***：配方更新成功返回true。

---

### ***连接状态***
```py
def isConnected() -> bool
```

- ***功能***
    连接状态

- ***返回值***：连接正常返回 true，否则返回 false。

---

### ***同步状态***
```py
def isStarted() -> bool
```
- ***功能***
    是否已开始同步机器人数据

- ***返回值***：是返回 true，否返回 false。

---

### ***可读状态***
```py
def isReadAvailable() -> bool
```

- ***功能***
   是否有可读数据。通常用于接收机器人状态时判断缓冲区里是否有可读数据。

- ***返回值***：是返回 true，否返回 false。

---

# RtsiIOInterface 类

## 简介

继承了`RtsiClientInterface`类。此接口对`RtsiClientInterface`进行了进一步封装，内部会启动一个线程来进行机器人数据的同步。

## 构造与析构函数

### ***构造函数***
```py
def __init__(output_recipe_file: str, input_recipe_file: str, frequency: float)
```
- ***功能***

    初始化数据并读取 `output_recipe_file` 和 `input_recipe_file` 两个文件，获取订阅配方。配方文件的格式为：  
    ```
    订阅项1
    订阅项2
    ```

- ***参数***
    - output_recipe_file：输出配方文件路径。

    - input_recipe_file：输入配方文件路径。

    - frequency：数据同步频率。

---

## 接口

### ***连接***
```py
def connect(ip: str) -> bool
```
- ***功能***

    连接机器人RTSI端口，进行版本校验，获取机器人控制器版本信息，配置输入、输出订阅配方，启动数据同步线程。

- ***参数***
    - ip：机器人IP。


- ***返回值***：成功返回true，失败返回false。

---

### ***断开连接***
```py
def disconnect()
```
- ***功能***

    断开与机器人的socket，结束数据同步线程。

---

### 获取控制器版本
```py
def getControllerVersion() -> VersionInfo
```
- ***功能***

    获取控制器版本信息

- ***返回值***：包含主版本号、次版本号、补丁号和构建号的VersionInfo对象

---

### 设置速度比例
```py
def setSpeedScaling(scaling: float) -> bool
```
- ***功能***

    设置机器人速度比例

- ***参数***

    - scaling：目标速度比例

- ***返回值***：设置成功返回true，失败返回false

---

### 设置标准数字IO
```py
def setStandardDigital(index: int, level: bool) -> bool
```
- ***功能***

    设置标准数字IO电平

- ***参数***

    - index：标准数字IO索引
    - level：高/低电平

- ***返回值***：设置成功返回true，失败返回false

---

### 设置可配置数字IO
```py
def setConfigureDigital(index: int, level: bool) -> bool
```
- ***功能***

    设置可配置数字IO电平

- ***参数***

    - index：可配置数字IO索引
    - level：高/低电平

- ***返回值***：设置成功返回true，失败返回false

---

### 设置模拟输出电压
```py
def setAnalogOutputVoltage(index: int, value: float) -> bool
```
- ***功能***

    设置模拟输出电压

- ***参数***

    - index：模拟IO索引
    - value：电压值(单位：V，范围[0,10]V)

- ***返回值***：设置成功返回true，失败返回false

---

### 设置模拟输出电流
```py
def setAnalogOutputCurrent(index: int, value: float) -> bool
```
- ***功能***

    设置模拟输出电流

- ***参数***

    - index：模拟IO索引
    - value：电流值(单位：A，范围[0.004,0.2]A)

- ***返回值***：设置成功返回true，失败返回false

---

### 设置外部力扭矩
```py
def setExternalForceTorque(value: list) -> bool
```
- ***功能***

    输入外部力传感器数据(当ft_rtsi_input_enable设置为true时生效)

- ***参数***

    - value：外部力传感器数据

- ***返回值***：设置成功返回true，失败返回false

---

### 设置工具数字输出
```py
def setToolDigitalOutput(index: int, level: bool) -> bool
```
- ***功能***

    设置工具数字输出电平

- ***参数***

    - index：工具输出IO索引
    - level：电平值

- ***返回值***：设置成功返回true，失败返回false

---

### 获取时间戳
```py
def getTimestamp() -> float
```
- ***功能***

    获取时间戳

- ***返回值***：时间戳(单位：秒)

---

### 获取负载质量
```py
def getPayloadMass() -> float
```
- ***功能***

    获取末端负载质量

- ***返回值***：负载质量(单位：kg)

---

### 获取负载重心
```py
def getPayloadCog() -> list
```
- ***功能***

    获取末端负载重心

- ***返回值***：负载重心坐标(单位：m)

---

### 获取脚本控制行号
```py
def getScriptControlLine() -> int
```
- ***功能***

    获取运行脚本的行号

- ***返回值***：脚本行号

---

### 获取目标关节位置
```py
def getTargetJointPositions() -> list
```
- ***功能***

    获取目标关节位置

- ***返回值***：关节位置(单位：rad)

---

### 获取目标关节速度
```py
def getTargetJointVelocity() -> list
```
- ***功能***

    获取目标关节速度

- ***返回值***：关节速度(单位：rad/s)

---

### 获取实际关节位置
```py
def getActualJointPositions() -> list
```
- ***功能***

    获取实际关节位置

- ***返回值***：关节位置(单位：rad)

---

### 获取实际关节扭矩
```py
def getActualJointTorques() -> list
```
- ***功能***

    获取实际关节扭矩

- ***返回值***：关节扭矩(单位：N*m)

---

### 获取实际关节速度
```py
def getActualJointVelocity() -> list
```
- ***功能***

    获取实际关节速度

- ***返回值***：关节速度(单位：rad/s)

---

### 获取实际关节电流
```py
def getActualJointCurrent() -> list
```
- ***功能***

    获取实际关节电流

- ***返回值***：关节电流(单位：A)

---

### 获取实际关节温度
```py
def getActualJointTemperatures() -> list
```
- ***功能***

    获取实际关节温度

- ***返回值***：关节温度(单位：摄氏度)

---

### 获取实际TCP位姿
```py
def getActualTCPPose() -> list
```
- ***功能***

    获取工具的实际笛卡尔坐标

- ***返回值***：[x, y, z, rx, ry, rz]，其中x,y,z是位置向量，rx,ry,rz是旋转向量

---

### 获取实际TCP速度
```py
def getActualTCPVelocity() -> list
```
- ***功能***

    获取工具的实际笛卡尔速度

- ***返回值***：[x, y, z, rx, ry, rz]/s，其中x,y,z是位置向量，rx,ry,rz是旋转向量

---

### 获取实际TCP力
```py
def getActualTCPForce() -> list
```
- ***功能***

    获取TCP的广义力(减去负载引起的力数据)

- ***返回值***：TCP力向量

---

### 获取目标TCP位姿
```py
def getTargetTpyose() -> list
```
- ***功能***

    获取工具的目标笛卡尔坐标

- ***返回值***：[x, y, z, rx, ry, rz]，其中x,y,z是位置向量，rx,ry,rz是旋转向量

---

### 获取目标TCP速度
```py
def getTargetTCPVelocity() -> list
```
- ***功能***

    获取工具的目标笛卡尔速度

- ***返回值***：[x, y, z, rx, ry, rz]，其中x,y,z是位置向量，rx,ry,rz是旋转向量

---

### 获取数字输入位
```py
def getDigitalInputBits() -> int
```
- ***功能***

    获取所有数字输入IO的位值

- ***返回值***：
    - bits 0-15：标准数字输入
    - bits 16-24：可配置数字输入
    - bits 24-28：工具数字输入

---

### 获取数字输出位
```py
def getDigitalOutputBits() -> int
```
- ***功能***

    获取所有数字输出IO的位值

- ***返回值***：
    - bits 0-15：标准数字输入
    - bits 16-24：可配置数字输入
    - bits 24-28：工具数字输入

---

### 获取机器人模式
```py
def getRobotMode() -> RobotMode
```
- ***功能***

    获取机器人模式

- ***返回值***：RobotMode枚举值

---

### 获取关节模式
```py
def getJointMode() -> list
```
- ***功能***

    获取各关节模式

- ***返回值***：包含6个JointMode的数组

---

### 获取安全状态
```py
def getSafetyStatus() -> SafetyMode
```
- ***功能***

    获取机器人安全模式

- ***返回值***：SafetyMode枚举值

---

### 获取实际速度比例
```py
def getActualSpeedScaling() -> float
```
- ***功能***

    获取实际机器人速度比例

- ***返回值***：速度比例值

---

### 获取目标速度比例
```py
def getTargetSpeedScaling() -> float
```
- ***功能***

    获取目标机器人速度比例

- ***返回值***：速度比例值

---

### 获取机器人电压
```py
def getRobotVoltage() -> float
```
- ***功能***

    获取机器人电压(48V)

- ***返回值***：电压值(单位：V)

---

### 获取机器人电流
```py
def getRobotCurrent() -> float
```
- ***功能***

    获取机器人电流

- ***返回值***：电流值(单位：A)

---

### 获取运行时状态
```py
def getRuntimeState() -> TaskStatus
```
- ***功能***

    获取程序状态

- ***返回值***：TaskStatus枚举值

---

### 获取肘部位置
```py
def getElbowPosition() -> list
```
- ***功能***

    获取机器人肘部实时位置

- ***返回值***：[x, y, z]坐标

---

### 获取肘部速度
```py
def getElbowVelocity() -> list
```
- ***功能***

    获取机器人肘部实时速度

- ***返回值***：[x, y, z]/s速度向量

---

### 获取机器人状态
```py
def getRobotStatus() -> int
```
- ***功能***

    获取机器人状态

- ***返回值***：
    - bits 0-3：是否上电 | 程序是否运行 | 自由驱动按钮是否按下

---

### 获取安全状态位
```py
def getSafetyStatusBits() -> int
```
- ***功能***

    获取机器人安全位状态

- ***返回值***：
    - bits 0-10：是否正常模式 | 是否减速模式 | 是否保护性停止 | 是否恢复模式 | 是否安全保护停止 | 是否系统紧急停止 | 是否机器人紧急停止 | 是否紧急停止 | 是否违规 | 是否故障 | 是否因安全停止

---

### 获取模拟IO类型
```py
def getAnalogIOTypes() -> int
```
- ***功能***

    获取模拟IO类型

- ***返回值***：
    - bits 0-3：模拟输入0(bit 0)，模拟输入1(bit 1)，模拟输出0(bit 2)，模拟输出1(bit 3)
    - 0：电流模式；1：电压模式

---

### 获取模拟输入
```py
def getAnalogInput(index: int) -> float
```
- ***功能***

    获取标准模拟输入值

- ***参数***

    - index：标准模拟输入索引[0,1]

- ***返回值***：模拟输入值(单位：A或V)

---

### 获取模拟输出
```py
def getAnalogOutput(index: int) -> float
```
- ***功能***

    获取标准模拟输出值

- ***参数***

    - index：标准模拟输出索引[0,1]

- ***返回值***：模拟输出值(单位：A或V)

---

### 获取IO电流
```py
def getIOCurrent() -> float
```
- ***功能***

    获取主板IO电流

- ***返回值***：电流值(单位：A)

---

### 获取工具模式
```py
def getToolMode() -> ToolMode
```
- ***功能***

    获取工具模式

- ***返回值***：ToolMode枚举值

---

### 获取工具模拟输入类型
```py
def getToolAnalogInputType() -> int
```
- ***功能***

    获取工具模拟输入IO模式

- ***返回值***：0：电流模式，1：电压模式

---

### 获取工具模拟输出类型
```py
def getToolAnalogOutputType() -> int
```
- ***功能***

    获取工具模拟输出IO模式

- ***返回值***：0：电流模式，1：电压模式

---

### 获取工具模拟输入
```py
def getToolAnalogInput() -> float
```
- ***功能***

    获取工具模拟输入值

- ***返回值***：
    - 电流模式范围[0.004-0.02]A
    - 电压模式范围[0-10]V

---

### 获取工具模拟输出
```py
def getToolAnalogOutput() -> float
```
- ***功能***

    获取工具模拟输出值

- ***返回值***：
    - 电流模式范围[0.004-0.02]A
    - 电压模式范围[0-10]V

---

### 获取工具输出电压
```py
def getToolOutputVoltage() -> float
```
- ***功能***

    获取工具输出电压

- ***返回值***：电压值(单位：V)

---

### 获取工具输出电流
```py
def getToolOutputCurrent() -> float
```
- ***功能***

    获取工具输出电流

- ***返回值***：电流值(单位：A)

---

### 获取工具输出温度
```py
def getToolOutputTemperature() -> float
```
- ***功能***

    获取工具输出温度

- ***返回值***：温度值(单位：摄氏度)

---

### 获取工具数字模式
```py
def getToolDigitalMode() -> ToolDigitalMode
```
- ***功能***

    获取工具数字模式

- ***返回值***：单针、双针模式1、双针模式2、三针

---

### 获取工具数字输出模式
```py
def getToolDigitalOutputMode(index: int) -> ToolDigitalOutputMode
```
- ***功能***

    获取工具数字输出模式

- ***参数***

    - index：工具数字索引

- ***返回值***：推/拉、npn、pnp

---

### 获取输出布尔寄存器0-31
```py
def getOutBoolRegisters0To31() -> int
```
- ***功能***

    获取布尔寄存器0-31的输出值

- ***返回值***：寄存器值

---

### 获取输出布尔寄存器32-63
```py
def getOutBoolRegisters32To63() -> int
```
- ***功能***

    获取布尔寄存器32-63的输出值

- ***返回值***：寄存器值

---

### 获取输入布尔寄存器0-31
```py
def getInBoolRegisters0To31() -> int
```
- ***功能***

    获取布尔寄存器0-31的输入值

- ***返回值***：寄存器值

---

### 获取输入布尔寄存器32-63
```py
def getInBoolRegisters32To63() -> int
```
- ***功能***

    获取布尔寄存器32-63的输入值

- ***返回值***：寄存器值

---

### 获取输入布尔寄存器
```py
def getInBoolRegister(index: int) -> bool
```
- ***功能***

    获取指定布尔寄存器的输入值

- ***参数***

    - index：布尔寄存器索引[64,127]

- ***返回值***：寄存器值

---

### 获取输出布尔寄存器
```py
def getOutBoolRegister(index: int) -> bool
```
- ***功能***

    获取指定布尔寄存器的输出值

- ***参数***

    - index：布尔寄存器索引

- ***返回值***：寄存器值

---

### 获取输入整型寄存器
```py
def getInIntRegister(index: int) -> int
```
- ***功能***

    获取指定整型寄存器的输入值

- ***参数***

    - index：整型寄存器索引

- ***返回值***：寄存器值

---

### 获取输出整型寄存器
```py
def getOutIntRegister(index: int) -> int
```
- ***功能***

    获取指定整型寄存器的输出值

- ***参数***

    - index：整型寄存器索引

- ***返回值***：寄存器值

---

### 获取输入双精度寄存器
```py
def getInDoubleRegister(index: int)
```
- ***功能***

    获取指定双精度寄存器的输入值

- ***参数***

    - index：双精度寄存器索引

- ***返回值***：寄存器值

---

### 获取输出双精度寄存器
```py
def getOutDoubleRegister(index: int) -> float
```
- ***功能***

    获取指定双精度寄存器的输出值

- ***参数***

    - index：双精度寄存器索引

- ***返回值***：寄存器值

---

### 获取输出配方的值
```py
def getRecipeValue(name: str) -> bool | list | int | float
```
- ***功能***

    获取输出配方指定订阅项的值。

- ***参数***
    - name：订阅项名称

- ***返回值***：获取成功返回true，失败返回false。

---

### 设置输出配方的值
```py
def setInputRecipeValue(name: str, value: bool | list | int | float)
```
- ***功能***

   设置输入配方指定订阅项的值。

- ***参数***
    - name：订阅项名称

    - out_value：输入值，注意此值的类型需要和RTSI文档中的类型一致。

- ***返回值***：设置成功返回true，失败返回false。

---

# RtsiRecipe 类

## 简介

此接口为提供了RTSI配方的一些基础操作，RtsiRecipe 这个类只能由`RtsiClientInterface::setupOutputRecipe()`和`RtsiClientInterface::setupInputRecipe()`这两个接口获得。

## 接口

### ***获取值***
```py
def getValue(name: str) -> bool | list | int | float
```
- ***功能***

    获取配方中订阅项的值

- ***参数***

    - name：订阅项名称。

    - out_value：订阅项输出值，注意此值的类型需要和RTSI文档中的类型一致。

- ***返回值***：获取成功为true，失败为false

---

### ***设置值***
```py
def setValue(name: str, value: bool | list | int | float)
```
- ***功能***

    设置配方中订阅项的值

- ***参数***

    - name：订阅项名称。

    - out_value：订阅项设置值，注意此值的类型需要和RTSI文档中的类型一致。

- ***返回值***：设置成功为true，失败为false。

---

### 获取配方
```py
def getRecipe() -> list
```
- ***功能***
    
    获取配方订阅项名称的列表

- ***返回值***：配方订阅项名称的列表

---

### 获取配方ID
```py
def getID() -> int
```
- ***功能***
    
    获取配方ID

- ***返回值***：配方ID

---