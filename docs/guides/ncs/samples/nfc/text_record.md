# NFC Text Record

## Overview

The NFC Text Record sample shows how to use the NFC tag to expose a text record to NFC polling devices. It uses the [NFC Data Exchange Format (NDEF)] library.

When the sample starts, it initializes the NFC tag and generates an NDEF message with three text records that contain the text “Hello World!” in three languages. Then it sets up the NFC library to use the generated message and sense the external NFC field.

The only events handled by the application are the NFC events. The Green LED turns on when an NFC field is present.

## Requirements

Before you start, check that you have the required hardware and software:

- 1x [nRF54L15 Connect Kit](https://makerdiary.com/products/nrf54l15-connectkit)
- 1x U.FL cabled 13.56 MHz NFC Antenna (included in the box)
- 1x USB-C Cable
- A smartphone or a tablet with NFC support
- A computer running macOS, Ubuntu, or Windows 10 or newer

## Installing NFC Tools App

NFC Tools App can read and write your NFC tags with a simple and lightweight user interface.

[![App Store](../../../../assets/images/appstore.png){ width='128' display='inline' }](https://apps.apple.com/us/app/nfc-tools/id1252962749)
[![Google Play](../../../../assets/images/google-play-badge.png){ width='148' display='inline' }](https://play.google.com/store/apps/details?id=com.wakdev.wdnfc)

## Attaching the NFC antenna

Before applying power to the board, ensure the U.FL cabled NFC antenna is properly installed.

![](../../../../assets/images/attaching-nfc-antenna.png)


## Building the sample

To build the sample, follow the instructions in [Getting Started Guide] to set up your preferred building environment.

Use the following steps to build the [NFC Text Record] sample on the command line.

1. Open a terminal window.

2. Go to `NCS-Project/nrf54l15-connectkit` repository cloned in the [Getting Started Guide].

3. Build the sample using the `west build` command, specifying the board (following the `-b` option) as `nrf54l15_connectkit/nrf54l15/cpuapp`.

	``` bash
	west build -p always -b nrf54l15_connectkit/nrf54l15/cpuapp samples/nfc/record_text
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
	Starting NFC Text Record sample
	NFC configuration done
	```

4. Open the [NFC Tools](#installing-nfc-tools-app) app and tap the __Read__ tab at the bottom.

5. Touch the NFC antenna with the smartphone or tablet and observe that the __Green LED__ blinks.

6. The app will automatically detect and read the tag. Observe that the app displays the encoded text.

[NFC Data Exchange Format (NDEF)]: https://docs.nordicsemi.com/bundle/ncs-latest/page/nrf/libraries/nfc/ndef/index.html#lib-nfc-ndef
[Getting Started Guide]: ../../getting-started.md
[NFC Text Record]: https://github.com/makerdiary/nrf54l15-connectkit/tree/main/samples/nfc/record_text
[PuTTY]: https://apps.microsoft.com/store/detail/putty/XPFNZKSKLBP7RJ

