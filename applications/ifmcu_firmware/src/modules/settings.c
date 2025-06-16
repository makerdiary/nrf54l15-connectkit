/*
 * Copyright (c) 2020 Nordic Semiconductor ASA
 * Copyright (c) 2016-2025 Makerdiary <https://makerdiary.com>
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#include <stdlib.h>

#include <zephyr/device.h>
#include <zephyr/settings/settings.h>
#include <zephyr/shell/shell.h>
#include <zephyr/sys/util.h>

#define MODULE settings
#include "module_state_event.h"

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(MODULE, CONFIG_IFMCU_SETTINGS_LOG_LEVEL);

#define SETTINGS_KEY "cfg"
#define VIOSEL_STORAGE_NAME				"viosel"

extern int viosel_set(int val);
extern int viosel_get(void);

static int settings_set(const char *key, size_t len_rd,
		   settings_read_cb read_cb, void *cb_arg)
{
	int ret;
	ssize_t rc;

	if (!strcmp(key, VIOSEL_STORAGE_NAME)) {
		/* Ignore record when size is improper. */
		if (len_rd == sizeof(int)) {
			int viosel;
			rc = read_cb(cb_arg, &viosel, sizeof(viosel));
			if (rc == sizeof(viosel)) {
				if ((viosel == -1 || viosel == 0 || viosel == 1) && viosel != viosel_get()) {
					ret = viosel_set(viosel);
					if (ret < 0) {
						LOG_ERR("Fail to set VIOSEL: (err = %d)", ret);
						return 0;
					}
					LOG_DBG("Load VIOSEL = %d", viosel);
				}
			} else {
				if (rc < 0) {
					LOG_ERR("Settings read-out error");
					return rc;
				}
			}
		}
	}

	return 0;
}

static void settings_init(void)
{
	int err;

	err = settings_subsys_init();
	if (err) {
		return;
	}

	static struct settings_handler sh = {
		.name = SETTINGS_KEY,
		.h_set = settings_set,
	};

	err = settings_register(&sh);
	if (err) {
		return;
	}

	err = settings_load();
	if (err) {
		return;
	}
}

static int cmd_cfgsync(const struct shell *sh, size_t argc, char **argv)
{
	int ret;

	/* Store VIOSEL */
	char viosel_key[] = SETTINGS_KEY "/" VIOSEL_STORAGE_NAME;
	int viosel = viosel_get();
	ret = settings_save_one(viosel_key, &viosel, sizeof(viosel));
	if (ret) {
		shell_error(sh, "Problem storing %s: (err = %d)", viosel_key, ret);
	}

	return 0;
}

SHELL_CMD_ARG_REGISTER(cfgsync, NULL,
		   "Store settings to the non-volatile memory", cmd_cfgsync, 1, 0);

static bool app_event_handler(const struct app_event_header *aeh)
{
	if (is_module_state_event(aeh)) {
		const struct module_state_event *event =
			cast_module_state_event(aeh);

		if (check_state(event, MODULE_ID(main), MODULE_STATE_READY)) {
			settings_init();
		}

		return false;
	}

	/* If event is unhandled, unsubscribe. */
	__ASSERT_NO_MSG(false);

	return false;
}

APP_EVENT_LISTENER(MODULE, app_event_handler);
APP_EVENT_SUBSCRIBE(MODULE, module_state_event);
