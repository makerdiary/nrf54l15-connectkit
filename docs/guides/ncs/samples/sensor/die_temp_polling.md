# Die Temperature Polling

## Overview

The Die Temperature Polling sample periodically reads temperature values (in °C) from the nRF54L15's die temperature sensor and prints the results to the serial console.

To run this sample, enable the sensor node that supports __`SENSOR_CHAN_DIE_TEMP`__ and create an alias named `die-temp0` to link to the node. Here is the overlay file which supports this sample.

``` dts linenums="1" title="nrf54l15_connectkit_nrf54l15_cpuapp.overlay"
/ {
	aliases {
		die-temp0 = &temp;
	};
};
```

## Requirements

Before you start, check that you have the required hardware and software:

- 1x [nRF54L15 Connect Kit](https://makerdiary.com/products/nrf54l15-connectkit)
- 1x USB-C Cable
- A computer running macOS, Ubuntu, or Windows 10 or newer

## Building the sample

To build the sample, follow the instructions in [Getting Started Guide] to set up your preferred building environment.

Use the following steps to build the [Die Temperature Polling] sample on the command line.

1. Open a terminal window.

2. Go to `NCS-Project/nrf54l15-connectkit` repository cloned in the [Getting Started Guide].

3. Build the sample using the `west build` command, specifying the board (following the `-b` option) as `nrf54l15_connectkit/nrf54l15/cpuapp`.

	``` bash
	west build -p always -b nrf54l15_connectkit/nrf54l15/cpuapp samples/sensor/die_temp_polling
	```

	!!! Tip
		The `-p` always option forces a pristine build, and is recommended for new users. Users may also use the `-p auto` option, which will use heuristics to determine if a pristine build is required, such as when building another sample.

4. After building the sample successfully, the firmware with the name `merged.hex` can be found in the `build` directory.

## Flashing the firmware

Connect the nRF54L15 Connect Kit to the computer with a USB-C cable:

![](../../../../assets/images/connecting-board-without-ant.png)

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
	*** Booting nRF Connect SDK v3.1.0-preview2-3674486b55f7 ***
	*** Using Zephyr OS v4.1.99-701bd803eafa ***
	CPU Die temperature[temp@d7000]: 32.5 °C
	CPU Die temperature[temp@d7000]: 32.5 °C
	CPU Die temperature[temp@d7000]: 32.2 °C
	CPU Die temperature[temp@d7000]: 32.2 °C
	CPU Die temperature[temp@d7000]: 32.2 °C
	CPU Die temperature[temp@d7000]: 32.5 °C
	...
	```

[Getting Started Guide]: ../../getting-started.md
[Die Temperature Polling]: https://github.com/makerdiary/nrf54l15-connectkit/tree/main/samples/sensor/die_temp_polling
[PuTTY]: https://apps.microsoft.com/store/detail/putty/XPFNZKSKLBP7RJ
