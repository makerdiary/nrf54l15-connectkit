# Bluetooth Low Energy: Peripheral HIDS Keyboard

## Overview

The Peripheral HIDS Keyboard sample demonstrates how to use the [GATT Human Interface Device (HID) Service] to implement a keyboard input device that you can connect to your computer.

The sample uses the __USR__ button to simulate the letter keys by generating letter keystrokes for a predefined string.

## Requirements

Before you start, check that you have the required hardware and software:

- 1x [nRF54L15 Connect Kit](https://makerdiary.com/products/nrf54l15-connectkit)
- 1x U.FL cabled 2.4 GHz Antenna (included in the box)
- 1x USB-C Cable
- A computer running macOS, Ubuntu, or Windows 10 or newer with Bluetooth LE supported

## Attaching the 2.4 GHz antenna

Before applying power to the board, ensure the U.FL cabled 2.4 GHz antenna is properly installed.

![](../../../../assets/images/attaching-bt-antenna.png)

## Building the sample

To build the sample, follow the instructions in [Getting Started Guide] to set up your preferred building environment.

Use the following steps to build the [Peripheral HIDS Keyboard] sample on the command line.

1. Open a terminal window.

2. Go to `NCS-Project/nrf54l15-connectkit` repository cloned in the [Getting Started Guide].

3. Build the sample using the `west build` command, specifying the board (following the `-b` option) as `nrf54l15_connectkit/nrf54l15/cpuapp`.

	``` bash
	west build -p always -b nrf54l15_connectkit/nrf54l15/cpuapp samples/bluetooth/peripheral_hids_keyboard
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
	Starting Bluetooth Peripheral HIDS keyboard sample
	Bluetooth initialized
	Advertising successfully started

	uart:~$
	```

4. On your computer, search for Bluetooth devices and connect to the device named __Nordic_HIDS_keyboard__.

5. When pairing, press __USR__ button on the board to confirm the passkey value. Observe the output of the terminal:

	``` { .txt .no-copy linenums="8" title="Terminal" }
	Connected 3C:22:FB:4A:0A:79 (public)
	Passkey for 3C:22:FB:4A:0A:79 (public): 052475
	Press USR Button to confirm.
	Numeric Match, conn 0x20002360
	Security changed: 3C:22:FB:4A:0A:79 (public) level 4
	Pairing completed: 3C:22:FB:4A:0A:79 (public), bonded: 1
	```

6. Open a text editor on your computer, repeatedly press __USR__ button on the board. Every button press sends one character of the test message `hello` (the test message includes a carriage return) to the computer, and this will be displayed in the text editor.

	``` { .txt .no-copy linenums="1" title="Visual Studio Code" }
	hello
	hello
	hello
	...
	```

!!! Tip
	If pairing fails (e.g., after testing other Bluetooth examples), you can clear bond info with `bt clear all` command in the terminal and retry:

	``` { .bash .no-copy linenums="1" title="Terminal" }
	uart:~$ bt clear all
	Pairings successfully cleared
	```


[GATT Human Interface Device (HID) Service]: https://docs.nordicsemi.com/bundle/ncs-latest/page/nrf/libraries/bluetooth/services/hids.html#hids-readme
[Getting Started Guide]: ../../getting-started.md
[Peripheral HIDS Keyboard]: https://github.com/makerdiary/nrf54l15-connectkit/tree/main/samples/bluetooth/peripheral_hids_keyboard
[PuTTY]: https://apps.microsoft.com/store/detail/putty/XPFNZKSKLBP7RJ
