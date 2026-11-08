# SPDX-License-Identifier: MIT
# Copyright (c) 2026 YOUNGJIN JOO (neoelec@gmail.com)

PRJ_MCS51_MK_FILE	:= $(abspath $(lastword $(MAKEFILE_LIST)))
PRJ_MCS51_MK_DIR	:= $(patsubst %/,%,$(dir $(PRJ_MCS51_MK_FILE)))

I_HDD00			?= $(HOME)/iHDD00
PROJECT_DIR		?= $(I_HDD00)/08.PROJECT

MK_BUILD_RACCOON_DIR	?= $(PROJECT_DIR)/mk-build-raccoon

INCDIRS			+= $(PRJ_MCS51_MK_DIR)/inc
VPATH			+= $(PRJ_MCS51_MK_DIR)/src_c

MCU			?= mcs51
F_CPU			?= 24000000
IRAM_SIZE		?= --iram-size 256

USE_PAULMON		?= 0
ifneq ($(filter 1 y yes true,$(USE_PAULMON)),)
CODE_LOC		?= --code-loc 0x2000
CODE_SIZE		?= --code-size 0x4000
XRAM_LOC		?= --xram-loc 0x6000
XRAM_SIZE		?= --xram-size 0x2000
else
CODE_SIZE		?= --code-size 0x2000
XRAM_SIZE		?= --xram-size 0
endif

LDFLAGS			+= $(IRAM_SIZE)
LDFLAGS			+= $(CODE_SIZE)
LDFLAGS			+= $(XRAM_SIZE)

include $(MK_BUILD_RACCOON_DIR)/sdcc_mcs51.mk
