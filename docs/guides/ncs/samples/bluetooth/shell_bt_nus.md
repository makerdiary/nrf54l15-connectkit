# Bluetooth Low Energy: NUS Shell Transport

## Overview

The Nordic UART Service (NUS) Shell Transport sample demonstrates how to use the [Nordic UART Service (NUS) shell transport] to receive shell commands from a remote device over Bluetooth

When the connection is established, you can connect to the sample through the [Nordic UART Service (NUS)] by using a host application. You can then send shell commands that are executed on the device running the sample, and see the logs.

## Requirements

Before you start, check that you have the required hardware and software:

- 1x [nRF54L15 Connect Kit](https://makerdiary.com/products/nrf54l15-connectkit)
- 1x U.FL cabled 2.4 GHz Antenna (included in the box)
- 1x USB-C Cable
- Chrome browser with [Web Bluetooth supported]
- A computer running macOS, Ubuntu, or Windows 10 or newer

## Attaching the 2.4 GHz antenna

Before applying power to the board, ensure the U.FL cabled 2.4 GHz antenna is properly installed.

![](../../../../assets/images/attaching-bt-antenna.png)

## Building the sample

To build the sample, follow the instructions in [Getting Started Guide] to set up your preferred building environment.

Use the following steps to build the [NUS Shell Transport] sample on the command line.

1. Open a terminal window.

2. Go to `NCS-Project/nrf54l15-connectkit` repository cloned in the [Getting Started Guide].

3. Build the sample using the `west build` command, specifying the board (following the `-b` option) as `nrf54l15_connectkit/nrf54l15/cpuapp`.

	``` bash
	west build -p always -b nrf54l15_connectkit/nrf54l15/cpuapp samples/bluetooth/shell_bt_nus
	```

	!!! Tip
		The `-p` always option forces a pristine build, and is recommended for new users. Users may also use the `-p auto` option, which will use heuristics to determine if a pristine build is required, such as when building another sample.

4. After building the sample successfully, the firmware with the name `merged.hex` can be found in the `build` directory.

## Flashing the firmware

Connect the nRF54L15 Connect Kit to the computer with a USB-C cable:

![](../../../../assets/images/connecting-board-with-bt-ant.png)

Then flash the sample using `west flash`:

``` bash
west flash
```

!!! Tip
	In case you wonder, the `west flash` will execute the following command:

	``` bash
	pyocd load --target nrf54l --frequency 4000000 build/merged.hex
	```

## Testing

After programming the sample, test it by performing the following steps:

1. Open up a serial terminal, specifying the primary COM port that your computer uses to communicate with the nRF54L15:

	=== "Windows"

		1. Start [PuTTY].
		2. Configure the correct serial port and click __Open__:

			![](../../../../assets/images/putty-settings.png)

	=== "macOS"

		Open up a terminal and run:

		``` bash
		screen <serial-port-name> 115200
		```

	=== "Ubuntu"

		Open up a terminal and run:

		``` bash
		screen <serial-port-name> 115200
		```

2. Press the __DFU/RST__ button to reset the nRF54L15.

3. Observe the output of the terminal. You should see the output, similar to what is shown in the following:

	``` { .txt .no-copy linenums="1" title="Terminal" }
	*** Booting nRF Connect SDK v3.1.0-6c6e5b32496e ***
	*** Using Zephyr OS v4.1.99-1612683d4010 ***
	Starting Bluetooth NUS shell transport sample
	Advertising successfully started

	uart:~$
	```

4. Open the online [Web Device CLI] in the Chrome brower:

	[:material-console: Web Device CLI](https://wiki.makerdiary.com/web-device-cli/){ .md-button }

5. Click <kbd>**Connect**</kbd> to scan devices.
6. Pair  __`BT_NUS_shell`__ discovered in the list.
7. Run `help` to print the help message.

![](../../../../assets/images/web-device-cli-nus.png)

[Nordic UART Service (NUS) shell transport]: https://docs.nordicsemi.com/bundle/ncs-latest/page/nrf/libraries/shell/shell_bt_nus.html#shell-bt-nus-readme
[Nordic UART Service (NUS)]: https://docs.nordicsemi.com/bundle/ncs-latest/page/nrf/libraries/bluetooth/services/nus.html#nus-service-readme
[Web Bluetooth supported]: https://github.com/WebBluetoothCG/web-bluetooth/blob/main/implementation-status.md
[Getting Started Guide]: ../../getting-started.md
[NUS Shell Transport]: https://github.com/makerdiary/nrf54l15-connectkit/tree/main/samples/bluetooth/shell_bt_nus
[PuTTY]: https://apps.microsoft.com/store/detail/putty/XPFNZKSKLBP7RJ
[Web Device CLI]: https://wiki.makerdiary.com/web-device-cli/
