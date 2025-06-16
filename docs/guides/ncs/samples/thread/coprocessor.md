# Thread: Co-processor

## Overview

The Thread Co-processor sample demonstrates how to implement OpenThread’s [Co-processor designs] inside the Zephyr environment. The sample uses the [Radio co-processor (RCP)] architecture.

The sample is based on [Zephyr’s OpenThread co-processor] sample. However, it customizes Zephyr’s sample to fulfill the nRF Connect SDK requirements (for example, by increasing the stack size dedicated for the user application), and also extends it with features such as:

- Increased Mbed TLS heap size.
- Lowered main stack size to increase user application space.
- No obsolete configuration options.
- Vendor hooks for co-processor architecture allowing users to extend handled properties by their own, customized functionalities.
- Thread 1.2 features.

## Requirements

Before you start, check that you have the required hardware and software:

- 1x [nRF54L15 Connect Kit](https://makerdiary.com/products/nrf54l15-connectkit)
- 1x U.FL cabled 2.4 GHz Antenna (included in the box)
- 1x USB-C Cable
- A computer running macOS, Ubuntu, or Windows 10 or newer

## Attaching the 2.4 GHz antenna

Before applying power to the board, ensure the U.FL cabled 2.4 GHz antenna is properly installed.

![](../../../../assets/images/attaching-bt-antenna.png)

## Building the sample

To build the sample, follow the instructions in [Getting Started Guide] to set up your preferred building environment.

Use the following steps to build the [Thread Co-processor] sample on the command line.

1. Open a terminal window.

2. Go to `NCS-Project/nrf54l15-connectkit` repository cloned in the [Getting Started Guide].

3. Build the sample using the `west build` command, specifying the board (following the `-b` option) as `nrf54l15_connectkit/nrf54l15/cpuapp`.

	=== "Default"

		``` bash
		west build -p always -b nrf54l15_connectkit/nrf54l15/cpuapp samples/openthread/coprocessor
		```

	=== "Vendor hooks"

		``` bash
		west build -p always -b nrf54l15_connectkit/nrf54l15/cpuapp samples/openthread/coprocessor -- -DSNIPPET="ci;logging;vendor_hook"
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

1. Connect the board to your computer using the USB-C Cable.

2. Get the primary COM port that your computer uses to communicate with the nRF54L15 (e.g., `/dev/cu.usbmodem14502`).

3. Build the OpenThread POSIX applications by performing the following steps:

	1. Enter the openthread directory:

		``` bash linenums="1"
		cd modules/lib/openthread
		```

	2. Install the OpenThread dependencies:

		``` bash linenums="2"
		./script/bootstrap
		```

	3. Build the applications with the required options. For example, to build the `ot-cli` application, run the following command:

		``` bash linenums="3"
		./script/cmake-build posix
		```

		Alternatively, to build the `ot-daemon` and `ot-ctl` applications, run the following command:

		``` bash linenums="3"
		./script/cmake-build posix -DOT_DAEMON=ON
		```

	You can find the generated applications in `./build/posix/src/posix/`.

4. Use the following radio URL parameter to connect to the board:

	``` bash
	'spinel+hdlc+uart://\ *ncp_uart_device*\ ?uart-baudrate=\ *baud_rate*' -B *backbone_link*
	```

	Replace the following parameters:

	- `ncp_uart_device` - Specifies the location of the device, for example: `/dev/cu.usbmodem14502`.
	- `baud_rate` - Specifies the baud rate to use. The Thread Co-Processor sample supports baud rate `1000000`.
	- `backbone_link` - Specifies Backbone link for communication with external network. This parameter can be omitted.


	=== "Using __`ot-cli`__"

		``` bash
		sudo ./build/posix/src/posix/ot-cli 'spinel+hdlc+uart:///dev/cu.usbmodem14502?uart-baudrate=1000000' --verbose -B eth0
		```

	=== "Using __`ot-daemon`__ + __`ot-ctl`__"

		``` bash
		sudo ./build/posix/src/posix/ot-daemon 'spinel+hdlc+uart:///dev/cu.usbmodem14502?uart-baudrate=1000000' --verbose -B eth0
		```

		And on a separate terminal window, specifying the Thread interface `utun4` shown in `ot-daemon` log output:

		``` bash
		sudo ./build/posix/src/posix/ot-ctl -I utun4
		```

5. From this point, you can follow the [Testing](./cli.md#testing) instructions in the CLI sample by removing the `ot` prefix for each command.

[Co-processor designs]: https://docs.nordicsemi.com/bundle/ncs-latest/page/nrf/protocols/thread/overview/architectures.html#thread-architectures-designs-cp
[Radio co-processor (RCP)]: https://docs.nordicsemi.com/bundle/ncs-latest/page/nrf/protocols/thread/overview/architectures.html#thread-architectures-designs-cp-rcp
[Zephyr’s OpenThread co-processor]: https://docs.nordicsemi.com/bundle/ncs-latest/page/zephyr/samples/net/openthread/coprocessor/README.html#openthread-coprocessor
[Getting Started Guide]: ../../getting-started.md
[Thread Co-processor]: https://github.com/makerdiary/nrf54l15-connectkit/tree/main/samples/openthread/coprocessor
[PuTTY]: https://apps.microsoft.com/store/detail/putty/XPFNZKSKLBP7RJ
