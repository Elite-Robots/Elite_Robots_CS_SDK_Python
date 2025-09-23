# VersionInfo 类

## 简介

VersionInfo类用于包含和管理版本信息，提供了版本号的存储、比较和转换功能。

## 导入
```py
from elite_cs_sdk import VersionInfo, SDK_VERSION_INFO
```

## 接口

### 构造函数
```py
def __init__(self, ma: int, mi: int, bug: int, bui: int)
```
- ***功能***

    使用指定的版本号组件创建VersionInfo对象

- ***参数***

    - ma：主版本号
    - mi：次版本号
    - bug：补丁号
    - bui：构建号

---

### 字符串构造函数
```py
def __init__(version: str)
```
- ***功能***

    从版本字符串创建VersionInfo对象

- ***参数***

    - version：格式为"major.minor.bugfix.build"的版本字符串

---

### 默认构造函数
```py
def __init__()
```
- ***功能***

    创建默认的VersionInfo对象(所有版本号组件初始化为0)

---

### 转换为字符串
```py
def toString() -> str
```
- ***功能***

    将版本信息转换为字符串

- ***返回值***：格式为"major.minor.bugfix.build"的字符串

---

### 从字符串解析
```py
@staticmethod
def fromString(version_str: str) -> VersionInfo
```
- ***功能***

    从字符串解析版本信息

- ***参数***

    - str：要解析的版本字符串

- ***返回值***：解析得到的VersionInfo对象

---

## 运算符重载

- `=`
- `==`, `!=`
- `>`, `>=`, `<`, `<=`

## 成员变量

### 主版本号
```py
major = 0
```

### 次版本号
```py
minor = 0
```

### 补丁号
```py
bugfix = 0
```

### 构建号
```py
build = 0
```

## 全局常量

### SDK版本信息
```py
SDK_VERSION_INFO : VersionInfo
```
- ***功能***

    表示SDK版本信息的常量

--- 
