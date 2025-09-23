# VersionInfo Class

## Introduction
The VersionInfo class is used to contain and manage version information, providing functions for storing, comparing, and converting version numbers.

## Import
```py
from elite_cs_sdk import VersionInfo, SDK_VERSION_INFO
```

## Interfaces

### Constructor
```py
def __init__(self, ma: int, mi: int, bug: int, bui: int)
```
- ***Function***
Creates a VersionInfo object with the specified version number components.
- ***Parameters***
    - ma: Major version number
    - mi: Minor version number
    - bug: Bug fix number
    - bui: Build number

---

### String Constructor
```py
def __init__(version: str)
```
- ***Function***
Creates a VersionInfo object from a version string.
- ***Parameters***
    - version: A version string in the format of "major.minor.bugfix.build".

---

### Default Constructor
```py
def __init__()
```
- ***Function***
Creates a default VersionInfo object (all version number components are initialized to 0).

---

### Convert to String
```py
def toString() -> str
```
- ***Function***
Converts the version information into a string.
- ***Return Value***: A string in the format of "major.minor.bugfix.build".

---

### Parse from String
```py
@staticmethod
def fromString(version_str: str) -> VersionInfo
```
- ***Function***
Parses the version information from a string.
- ***Parameters***
    - str: The version string to be parsed.
- ***Return Value***: The parsed VersionInfo object.

---

## Operator Overloading

### Assignment Operator
- `=`
- `==`, `!=`
- `>`, `>=`, `<`, `<=`

---

## Member Variables

### Major Version Number
```py
major = 0
```

### Minor Version Number
```py
minor = 0
```

### Bug Fix Number
```py
bugfix = 0
```

### Build Number
```py
build = 0
```

## Global Constants

### SDK Version Information
```py
SDK_VERSION_INFO : VersionInfo
```
- ***Function***
A constant representing the SDK version information.

---