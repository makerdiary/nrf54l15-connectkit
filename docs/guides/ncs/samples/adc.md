# ADC

## Overview

This sample demonstrates how to use the ADC driver API. It reads ADC samples from two channels specified in the devicetree and prints the readings on the console. If voltage of the used reference can be obtained, the raw readings are converted to millivolts.

Here is a minimal devicetree fragment which supports this sample.

``` dts linenums="1" title="nrf54l15_connectkit_nrf54l15_cpuapp.overlay"
/ {
	zephyr,user {
		io-channels = <&adc 0>, <&adc 1>;
	};
};

&adc {
	#address-cells = <1>;
	#size-cells = <0>;

	channel@0 {
		reg = <0>;
		zephyr,gain = "ADC_GAIN_1_4";
		zephyr,reference = "ADC_REF_INTERNAL";
		zephyr,acquisition-time = <ADC_ACQ_TIME_DEFAULT>;
		zephyr,input-positive = <NRF_SAADC_AIN0>; /* P1.04 */
		zephyr,resolution = <10>;
	};

	channel@1 {
		reg = <1>;
		zephyr,gain = "ADC_GAIN_1_4";
		zephyr,reference = "ADC_REF_INTERNAL";
		zephyr,acquisition-time = <ADC_ACQ_TIME_DEFAULT>;
		zephyr,input-positive = <NRF_SAADC_VDD>;
		zephyr,resolution = <12>;
		zephyr,oversampling = <8>;
	};
};
```

As shown, __AIN0__ is assigned to Channel 0, and __VDD_GPIO__ to Channel 1.

## Requirements

Before you start, check that you have the required hardware and software:

- 1x [nRF54L15 Connect Kit](https://makerdiary.com/products/nrf54l15-connectkit)
- 1x USB-C Cable
- A computer running macOS, Ubuntu, or Windows 10 or newer

## Building the sample

To build the sample, follow the instructions in [Getting Started Guide] to set up your preferred building environment.

Use the following steps to build the [ADC] sample on the command line.

1. Open a terminal window.

2. Go to `NCS-Project/nrf54l15-connectkit` repository cloned in the [Getting Started Guide].

3. Build the sample using the `west build` command, specifying the board (following the `-b` option) as `nrf54l15_connectkit/nrf54l15/cpuapp`.

	``` bash
	west build -p always -b nrf54l15_connectkit/nrf54l15/cpuapp samples/adc
	```

	!!! Tip
		The `-p` always option forces a pristine build, and is recommended for new users. Users may also use the `-p auto` option, which will use heuristics to determine if a pristine build is required, such as when building another sample.

4. After building the sample successfully, the firmware with the name `merged.hex` can be found in the `build` directory.

## Flashing the firmware

Connect the nRF54L15 Connect Kit to the computer with a USB-C cable:

![](../../../assets/images/connecting-board-without-ant.png)

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

			![](../../../assets/images/putty-settings.png)

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
	ADC reading[0]:
	- adc@d5000, channel 0: 85 = 298 mV
	- adc@d5000, channel 1: 3740 = 3287 mV
	ADC reading[1]:
	- adc@d5000, channel 0: 36 = 126 mV
	- adc@d5000, channel 1: 3740 = 3287 mV
	ADC reading[2]:
	- adc@d5000, channel 0: 83 = 291 mV
	- adc@d5000, channel 1: 3741 = 3287 mV
	ADC reading[3]:
	- adc@d5000, channel 0: 37 = 130 mV
	- adc@d5000, channel 1: 3742 = 3288 mV
	...
	```

[Getting Started Guide]: ../getting-started.md
[ADC]: https://github.com/makerdiary/nrf54l15-connectkit/tree/main/samples/adc
[PuTTY]: https://apps.microsoft.com/store/detail/putty/XPFNZKSKLBP7RJ
