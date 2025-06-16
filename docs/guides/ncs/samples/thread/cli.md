# Thread: CLI

## Overview

The Thread CLI sample demonstrates how to send commands to a Thread device using the OpenThread Command Line Interface (CLI). The CLI is integrated into the Zephyr shell.

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

Use the following steps to build the [Thread CLI] sample on the command line.

1. Open a terminal window.

2. Go to `NCS-Project/nrf54l15-connectkit` repository cloned in the [Getting Started Guide].

3. Build the sample using the `west build` command, specifying the board (following the `-b` option) as `nrf54l15_connectkit/nrf54l15/cpuapp`.

	``` bash
	west build -p always -b nrf54l15_connectkit/nrf54l15/cpuapp samples/openthread/cli
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

After both boards are programmed with the CLI sample, complete the following steps to test communication between boards:

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

3. Configure the required Thread network parameters with the `ot channel`, `ot panid`, and `ot networkkey` commands. Make sure to use the same parameters for all nodes that you add to the network. The following example uses the default OpenThread parameters:

	``` { .bash .no-copy linenums="1" title="Terminal" }
	uart:~$ ot channel 11
	Done
	uart:~$ ot panid 0xabcd
	Done
	uart:~$ ot networkkey 00112233445566778899aabbccddeeff
	Done
	```

4. Enable the Thread network with the `ot ifconfig up` and `ot thread start` commands:

	``` { .bash .no-copy linenums="7" title="Terminal" }
	uart:~$ ot ifconfig up
	Done
	uart:~$ ot thread start
	Done
	```

5. Invoke some of the OpenThread commands to obtain network-related details from each device:

	=== "Device-1"

		``` { .bash .no-copy linenums="11" title="Terminal" }
		uart:~$ ot state
		leader
		Done
		uart:~$ ot networkname
		OpenThread
		Done
		uart:~$ ot ipaddr
		fdde:ad00:beef:0:0:ff:fe00:fc00
		fdde:ad00:beef:0:0:ff:fe00:1c00
		fdde:ad00:beef:0:7e01:5f90:7cda:5690
		fe80:0:0:0:bc1a:d6d8:9009:75a0
		Done
		```

	=== "Device-2"

		``` { .bash .no-copy linenums="11" title="Terminal" }
		uart:~$ ot state
		router
		Done
		uart:~$ ot networkname
		OpenThread
		Done
		uart:~$ ot ipaddr
		fdde:ad00:beef:0:0:ff:fe00:a800
		fdde:ad00:beef:0:1c64:740:cc44:1066
		fe80:0:0:0:e8a9:c27c:1a5:a188
		Done
		```

6. Test communication between the devices with the `ot ping` command. For example:

	=== "Device-1"

		``` { .bash .no-copy linenums="23" title="Terminal" }
		uart:~$ ot ping fdde:ad00:beef:0:1c64:740:cc44:1066
		16 bytes from fdde:ad00:beef:0:1c64:740:cc44:1066: icmp_seq=1 hlim=64 time=41ms
		1 packets transmitted, 1 packets received. Packet loss = 0.0%. Round-trip min/avg/max = 41/41.0/41 ms.
		Done
		```

	=== "Device-2"

		``` { .bash .no-copy linenums="23" title="Terminal" }
		uart:~$ ot ping fdde:ad00:beef:0:7e01:5f90:7cda:5690
		16 bytes from fdde:ad00:beef:0:7e01:5f90:7cda:5690: icmp_seq=1 hlim=64 time=11ms
		1 packets transmitted, 1 packets received. Packet loss = 0.0%. Round-trip min/avg/max = 11/11.0/11 ms.
		Done
		```

[Getting Started Guide]: ../../getting-started.md
[Thread CLI]: https://github.com/makerdiary/nrf54l15-connectkit/tree/main/samples/openthread/cli
[PuTTY]: https://apps.microsoft.com/store/detail/putty/XPFNZKSKLBP7RJ
