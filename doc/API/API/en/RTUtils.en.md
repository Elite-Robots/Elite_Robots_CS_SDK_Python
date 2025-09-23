# Real-Time Tools

Some interfaces that can improve real-time performance

## Import
```py
import elite_cs_sdk
```

## Interfaces

### Set Real-Time Thread
```py
def setCurrentThreadFiFoScheduling(priority: int) -> bool
```

- ***Function***

    Set the current thread to FIFO scheduling and set the priority

- ***Parameters***

  - `priority`: Priority level

- ***Return Value***
    - `true`: Setting successful
    - `false`: Setting failed

### Get Maximum Thread Priority
```py
def getThreadFiFoMaxPriority() -> int
```

- ***Function***

    Get the maximum thread priority

- ***Return Value***: Maximum priority

### Bind Thread to CPU Core
```py
def bindCurrentThreadToCpus(cpu: int) -> bool
``` 

- ***Function***

    Bind the current thread to a CPU core

- ***Parameters***

  - `cpu`: CPU core number

- ***Return Value***
    - `true`: Binding successful
    - `false`: Binding failed