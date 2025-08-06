# NFC System OFF

## Overview

The NFC System OFF sample shows how to make the NFC Tag device wake up from the System OFF mode when it detects the NFC field. It uses the [NFC Data Exchange Format (NDEF)] library.

The sample starts with the initialization of the NFC Tag device. The device then attempts to detect an external NFC field. If the field is not detected within three seconds, the device goes into the System OFF mode.

The device wakes up from the System OFF mode when an NFC field is detected. The system is started and the NFC Tag device is reinitialized. The tag can be read afterwards.

When the NFC field is not within range anymore, the device goes back to the System OFF mode.

## Requirements

Before you start, check that you have the required hardware and software:

- 1x [nRF54L15 Connect Kit](https://makerdiary.com/products/nrf54l15-connectkit)
- 1x U.FL cabled 13.56 MHz NFC Antenna (included in the box)
- 1x USB-C Cable
- A smartphone or a tablet with NFC support
- A computer running macOS, Ubuntu, or Windows 10 or newer

## Attaching the NFC antenna

Before applying power to the board, ensure the U.FL cabled NFC antenna is properly installed.

![](../../../../assets/images/attaching-nfc-antenna.png)


## Building the sample

To build the sample, follow the instructions in [Getting Started Guide] to set up your preferred building environment.

Use the following steps to build the [NFC System OFF] sample on the command line.

1. Open a terminal window.

2. Go to `NCS-Project/nrf54l15-connectkit` repository cloned in the [Getting Started Guide].

3. Build the sample using the `west build` command, specifying the board (following the `-b` option) as `nrf54l15_connectkit/nrf54l15/cpuapp`.

	``` bash
	west build -p always -b nrf54l15_connectkit/nrf54l15/cpuapp samples/nfc/system_off
	```

	!!! Tip
		The `-p` always option forces a pristine build, and is recommended for new users. Users may also use the `-p auto` option, which will use heuristics to determine if a pristine build is required, such as when building another sample.

4. After building the sample successfully, the firmware with the name `merged.hex` can be found in the `build` directory.

## Flashing the firmware

Connect the nRF54L15 Connect Kit to the computer with a USB-C cable:

![](../../../../assets/images/connecting-board-with-nfc-ant.png)

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

3. Once the sample starts running, you should see the following output:

	``` { .bash .no-copy linenums="1" title="Terminal" }
	*** Booting nRF Connect SDK v3.1.0-rc1-8505887182fe ***
	*** Using Zephyr OS v4.1.99-797a60e8542a ***
	Reset by pin-reset
	NFC configuration done
	Powering off.
	Approach a NFC reader to restart.
	```

4. Observe that the __Green LED__ turns off three seconds after the programming has completed. This indicates that the system is in the System OFF mode.

5. Touch the NFC antenna with the smartphone or tablet.

6. Observe that the __Green LED__ is lit. It turns off after three seconds. This indicates that system is in the System OFF mode again. Expected terminal output:

	``` { .bash .no-copy linenums="7" title="Terminal" }
	*** Booting nRF Connect SDK v3.1.0-rc1-8505887182fe ***
	*** Using Zephyr OS v4.1.99-797a60e8542a ***
	Wake up by NFC field detect
	NFC configuration done
	Powering off.
	Approach a NFC reader to restart.
	```

[NFC Data Exchange Format (NDEF)]: https://docs.nordicsemi.com/bundle/ncs-latest/page/nrf/libraries/nfc/ndef/index.html#lib-nfc-ndef
[Getting Started Guide]: ../../getting-started.md
[NFC System OFF]: https://github.com/makerdiary/nrf54l15-connectkit/tree/main/samples/nfc/system_off
[PuTTY]: https://apps.microsoft.com/store/detail/putty/XPFNZKSKLBP7RJ

