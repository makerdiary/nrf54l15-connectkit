# Thread: CoAP

## Overview

The Thread CoAP sample demonstrates how to use OpenThread CoAP API. It can be built to work as a server or as a client.

By running a client and server on two boards, a local Thread network can be created. To create the network, OpenThread uses the network key provided with Kconfig. Once the boards have been flashed, the network will be automatically created and configured.

Once the network is operational, then the client could start interacting with the server. Every time the user presses the button, the LED on server should toggle.

## Requirements

Before you start, check that you have the required hardware and software:

- 2x [nRF54L15 Connect Kit](https://makerdiary.com/products/nrf54l15-connectkit) with U.FL cabled 2.4 GHz Antenna
- 2x USB-C Cable
- A computer running macOS, Ubuntu, or Windows 10 or newer

## Attaching the 2.4 GHz antenna

Before applying power to the board, ensure the U.FL cabled 2.4 GHz antenna is properly installed.

![](../../../../assets/images/attaching-bt-antenna.png)

## Building the sample

To build the sample, follow the instructions in [Getting Started Guide] to set up your preferred building environment.

Use the following steps to build the [Thread CoAP] sample on the command line.

1. Open a terminal window.

2. Go to `NCS-Project/nrf54l15-connectkit` repository cloned in the [Getting Started Guide].

3. Build the sample using the `west build` command, specifying the board (following the `-b` option) as `nrf54l15_connectkit/nrf54l15/cpuapp`.

	=== "Server"

		``` bash
		west build -p always -b nrf54l15_connectkit/nrf54l15/cpuapp samples/openthread/coap -- -DCONFIG_OT_COAP_SAMPLE_SERVER=y
		```

	=== "Client"

		``` bash
		west build -p always -b nrf54l15_connectkit/nrf54l15/cpuapp samples/openthread/coap
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

After both the server and the client are programmed, complete the following steps to test communication between boards:

1. Connect to both boards with a terminal emulator, specifying the primary COM port that your computer uses to communicate with the nRF54L15:

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

2. Press the __DFU/RST__ button on both boards to reset the nRF54L15.

3. The Thread network will be automatically created and configured. Invoke some of the OpenThread commands to obtain network-related details from each device:

	=== "Server"

		``` { .bash .no-copy linenums="1" title="Terminal" }
		server:~$ ot state
		leader
		Done
		server:~$ ot networkname
		OpenThreadDemo
		Done
		server:~$ ot ipaddr
		fdde:ad00:beef:0:0:ff:fe00:fc00
		fdde:ad00:beef:0:0:ff:fe00:2800
		fdde:ad00:beef:0:7d78:d429:f3e4:3903
		fe80:0:0:0:44b8:36d2:4cf7:cc9e
		Done
		```

	=== "Client"

		``` { .bash .no-copy linenums="1" title="Terminal" }
		client:~$ ot state
		router
		Done
		client:~$ ot networkname
		OpenThreadDemo
		Done
		client:~$ ot ipaddr
		fdde:ad00:beef:0:0:ff:fe00:3000
		fdde:ad00:beef:0:c53e:ecc0:e981:2524
		fe80:0:0:0:88b6:3602:586b:9c37
		Done
		```

6. Press __USR__ button on the client and you should see the __Green LED__ on the server toggling.

7. The example also provides a shell command to control the LED on the server from the client. To toggle the LED:

	=== "Client"

		``` { .bash .no-copy linenums="1" title="Terminal" }
		client:~$ ot_coap led set 0 toggle
		```

8. You can also get the __USR__ button state on the server from the client:

	=== "Client"

		``` { .bash .no-copy linenums="1" title="Terminal" }
		client:~$ ot_coap btn get 0
		off
		client:~$ ot_coap btn get 0
		on
		```

9. The example uses the broadcast address by default. To control the LED of a specific server, we can use it IPv6 address:

	=== "Client"

		``` { .bash .no-copy linenums="1" title="Terminal" }
		client:~$ ot_coap led set 0 toggle fdde:ad00:beef:0:7d78:d429:f3e4:3903
		```

[Getting Started Guide]: ../../getting-started.md
[Thread CoAP]: https://github.com/makerdiary/nrf54l15-connectkit/tree/main/samples/openthread/coap
[PuTTY]: https://apps.microsoft.com/store/detail/putty/XPFNZKSKLBP7RJ
