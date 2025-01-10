# Copyright 2022 Flavien Solt, ETH Zurich.
# Licensed under the General Public License, Version 3.0, see LICENSE for details.
# SPDX-License-Identifier: GPL-3.0-only

RESOURCEWRAPPER_TAG = boom
DESIGN_NAME = boom
# Used in the Modelsim infra.
VARIANT_ID = _boom

REPLACE_BOOTROM ?= 0
VCD_REGEX = tb_top/i_dut/*
TOP_MODULE = boom_mem_top # Top module for the Yosys instrumentation.

# DESIGN_CONFIG = MySmallBoomConfigNoTracing
DESIGN_CONFIG = MyMediumBoomConfigNoTracing

MILESAN_DIR := ${shell dirname ${shell pwd}}/milesan-boom

include ../common/common.mk
