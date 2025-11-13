# RS485 Serial Communication

## Summary

The robot's end effector and control cabinet are equipped with RS485 communication interfaces, and the SDK provides corresponding functionalities.

The essence of reading/writing robot serial ports through the SDK is that the robot forwards data from the RS485 interface to a specified TCP port, and the SDK directly reads/writes to that TCP port.

# SerialConfig Class

## Description

Contains configuration variables for serial port baud rate, parity, etc., along with enumeration definitions.

## Import
```py
import elite_cs_sdk
```

## Parameters

- `baud_rate`
    - Type: `SerialConfig.BaudRate`
    - Description: Serial port baud rate. Default value is `BR_115200` (115200 baud).

- `parity`
    - Type: `SerialConfig.Parity`
    - Description: Serial port parity check. Default value is `NONE` (no parity).

- `stop_bits`
    - Type: `SerialConfig.StopBits`
    - Description: Serial port stop bits. Default value is `ONE` (1 stop bit).

# SerialCommunication Class

## Description

TCP client for serial port forwarding.

## Import
```py
import elite_cs_sdk
```

## Interface

---

### ***Connect***
```py
def connect(timeout_ms: int) -> bool
```
- ***Description***
    
    Connect to the server forwarding the robot's serial port.

- ***Parameters***
    - `timeout_ms`: Timeout in milliseconds
    
- ***Return Value***: Returns True if connection is successful.

---

### ***Disconnect***
```py
def disconnect()
```

- ***Description***
    
    Disconnect from the server.

---

### ***Write Data to Serial Port***
```py
def write(data: bytes) -> int
```

- ***Description***
    
    Write data to the serial port.

- ***Parameters***
    - `data`: Data buffer
        
- ***Return Value***: Number of bytes written.

---

### ***Read Data from Serial Port***
```py
def read(size: int, timeout_ms: int) -> bytes
```

- ***Description***
    
    Read data from the serial port.

- ***Parameters***    
    - `size`: Data size
    
    - `timeout_ms`: Timeout in milliseconds. Values ≤ 0 indicate infinite waiting.
    
- ***Return Value***: Read data.

---

### ***Check Server Connection***
```py
def isConnected() -> bool
```

- ***Description***
    
    Check if connected to the server.

    
- ***Return Value***: Returns true if connected to the server.

---