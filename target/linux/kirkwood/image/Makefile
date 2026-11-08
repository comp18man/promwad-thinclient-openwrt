# SPDX-License-Identifier: GPL-2.0-only
#
# Copyright (C) 2009-2013 OpenWrt.org

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/image.mk

KERNEL_LOADADDR:=0x8000

define Device/Default
  PROFILES := Default
  DEVICE_DTS_DIR := $(DTS_DIR)/marvell
  DEVICE_DTS = kirkwood-$(lastword $(subst _, ,$(1)))
  KERNEL_DEPENDS = $$(wildcard $(DTS_DIR)/$$(DEVICE_DTS).dts)
  KERNEL := kernel-bin | append-dtb | uImage none
  KERNEL_NAME := zImage
  KERNEL_SUFFIX  := -uImage
  KERNEL_IN_UBI := 1

  PAGESIZE := 2048
  SUBPAGESIZE := 512
  BLOCKSIZE := 128k
  IMAGES := sysupgrade.bin factory.bin
  IMAGE/sysupgrade.bin := sysupgrade-tar | append-metadata
  IMAGE/factory.bin := append-ubi
endef

define Device/promwad_wtplug-tc
  DEVICE_VENDOR := Promwad
  DEVICE_MODEL := wtplug-tc
  KERNEL_SIZE := 10240k
  PAGESIZE := 2048
  BLOCKSIZE := 128k
  VID_HDR_OFFSET := 512
  SUBPAGESIZE := 512
  UBIFS_OPTS := -m $(PAGESIZE) -e 129024 -c 8191
  IMAGES := sysupgrade.bin
  DEVICE_PACKAGES := kmod-mvsdio kmod-rtc-mv kmod-gpio-button-hotplug \
	kmod-usb251xb kmod-usb-hid kmod-xgi-fb kmscon \
	kmod-sound-soc-wtplug-tc wtplug-tc-sound alsa-utils
  SUPPORTED_DEVICES += promwad,wtplug-tc
endef
TARGET_DEVICES += promwad_wtplug-tc

$(eval $(call BuildImage))
