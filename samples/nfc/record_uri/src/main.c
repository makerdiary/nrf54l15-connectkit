/*
 * Copyright (c) 2018 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#include <zephyr/kernel.h>
#include <zephyr/sys/reboot.h>

#include <nfc_t2t_lib.h>
#include <nfc/ndef/uri_msg.h>

#include <dk_buttons_and_leds.h>

#define NDEF_MSG_BUF_SIZE	256

#define NFC_FIELD_LED		DK_LED1

/* URL makerdiary.com */
static const uint8_t m_url[] =
    {'m', 'a', 'k', 'e', 'r', 'd', 'i', 'a', 'r', 'y', '.', 'c', 'o', 'm'}; //URL "makerdiary.com"

/* Buffer used to hold an NFC NDEF message. */
static uint8_t ndef_msg_buf[NDEF_MSG_BUF_SIZE];

static void nfc_callback(void *context,
			 nfc_t2t_event_t event,
			 const uint8_t *data,
			 size_t data_length)
{
	ARG_UNUSED(context);
	ARG_UNUSED(data);
	ARG_UNUSED(data_length);

	switch (event) {
	case NFC_T2T_EVENT_FIELD_ON:
		dk_set_led_on(NFC_FIELD_LED);
		break;
	case NFC_T2T_EVENT_FIELD_OFF:
		dk_set_led_off(NFC_FIELD_LED);
		break;
	default:
		break;
	}
}

int main(void)
{
	uint32_t len = sizeof(ndef_msg_buf);

	printk("Starting NFC URI Record sample\n");

	/* Configure LED-pins as outputs */
	if (dk_leds_init() < 0) {
		printk("Cannot init LEDs!\n");
		goto fail;
	}

	/* Set up NFC */
	if (nfc_t2t_setup(nfc_callback, NULL) < 0) {
		printk("Cannot setup NFC T2T library!\n");
		goto fail;
	}

    /* Encode URI message into buffer */
    if (nfc_ndef_uri_msg_encode(NFC_URI_HTTPS, m_url, sizeof(m_url), ndef_msg_buf, &len) < 0) {
		printk("Cannot encode message!\n");
		goto fail;
	}

	/* Set created message as the NFC payload */
	if (nfc_t2t_payload_set(ndef_msg_buf, len) < 0) {
		printk("Cannot set payload!\n");
		goto fail;
	}


	/* Start sensing NFC field */
	if (nfc_t2t_emulation_start() < 0) {
		printk("Cannot start emulation!\n");
		goto fail;
	}
	printk("NFC configuration done\n");

	return 0;

fail:
#if CONFIG_REBOOT
	sys_reboot(SYS_REBOOT_COLD);
#endif /* CONFIG_REBOOT */

	return -EIO;
}
