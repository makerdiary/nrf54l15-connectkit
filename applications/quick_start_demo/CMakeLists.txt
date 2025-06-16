#
# Copyright (c) 2018 Nordic Semiconductor
# Copyright (c) 2016-2025 Makerdiary <https://makerdiary.com>
#
# SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
#
cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(quick_start_demo)

# NORDIC SDK APP START
target_sources(app PRIVATE
  src/main.c
)

# NORDIC SDK APP END
