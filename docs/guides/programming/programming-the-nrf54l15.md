# Programming the nRF54L15

## Overview

This guide describes how to program the nRF54L15 on the nRF54L15 Connect Kit through the Interface MCU.

## Requirements

Before you start, check that you have the required hardware and software:

- 1x [nRF54L15 Connect Kit](https://makerdiary.com/products/nrf54l15-connectkit)
- 1x USB-C Cable
- [Python] 3.10.0 or newer
- [pyOCD v0.38.0]
- A computer running macOS, Ubuntu, or Windows 10 or newer

!!! Tip
	Python and pyOCD will be installed after setting up your development environment in [Getting Started Guide].

## Installing pyOCD

To program the nRF54L15, a tool that supports the CMSIS-DAP protocol should be installed. [pyOCD v0.38.0] or newer is required.

The latest stable version of pyOCD may be installed via [pip]. Open up a terminal and run:

=== "Windows"

    ``` bat
    py -3 -m pip install -U pyocd
    ```

=== "macOS"

    ``` bash
    python3 -m pip install -U pyocd
    ```

=== "Ubuntu"

    ``` bash
    python3 -m pip install -U pyocd
    ```

    !!! Note
        On Linux, permission to access USB devices from user space must be explicitly granted via udev rules. See [udev rules on Linux] for detailed instructions. 

## Connecting the board

Connect the nRF54L15 Connect Kit to your computer with a USB-C cable.

![](../../assets/images/connecting-board-without-ant.png)

Enter the following command to list the connected device:

``` bash
pyocd list
```

You should see the output, similar to what is shown in the following:

``` { .bash .no-copy linenums="1" title="Terminal" }
  #   Probe/Board              Unique ID               Target
-----------------------------------------------------------------
  0   ZEPHYR IFMCU CMSIS-DAP   820D9A5F0E322B8EFE662   ✔︎ nrf54l
      Makerdiary               nRF54L15 Connect Kit
```

## Programming with pyOCD

To program the nRF54L15 with pyOCD, complete the following steps:

1. Enter the following command to program the application firmware:

    ``` bash
    pyocd load -t nrf54l <firmware.hex> # (1)!
    ```

    1.  You can also use `pyocd flash` instead:
        ``` bash
        pyocd flash -t nrf54l <firmware.hex>
        ```

2. The RGB LED blinks blue rapidly during programming.
3. The application starts running after the firmware programming is completed. If not, press the __DFU/RST__ button to reset the nRF54L15.


In some cases, you may need to erase the entire non-volatile memory (RRAM) of the nRF54L15:

``` bash
pyocd erase -t nrf54l --chip
```

[Python]: https://www.python.org/downloads/
[pyOCD v0.38.0]: https://github.com/pyocd/pyOCD/releases/tag/v0.38.0
[udev rules on Linux]: ../../troubleshooting.md#udev-rules-on-linux
[pip]: https://pip.pypa.io/en/stable/index.html
[Getting Started Guide]: ../ncs/getting-started.md
