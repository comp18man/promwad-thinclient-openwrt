#
# Copyright (C) 2010-2014 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_VERSION:=2026.10
PKG_RELEASE:=1

PKG_HASH:=f943a88389c8fd70a6b0d061a88267465e143c7ca6ea2b75837ab20f5b60c739

include $(INCLUDE_DIR)/u-boot.mk

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://codeload.github.com/u-boot/u-boot/tar.gz/v$(PKG_VERSION)?

include $(INCLUDE_DIR)/package.mk

define U-Boot/Default
  BUILD_TARGET:=kirkwood
  BUILD_SUBTARGET:=generic
  UBOOT_IMAGE:=u-boot.kwb
endef

define U-Boot/wtplug_tc
  NAME:=Promwad WTPlug Thin Client
  BUILD_DEVICES:=promwad_wtplug-tc
endef

UBOOT_TARGETS := wtplug_tc

define Build/InstallDev
	$(INSTALL_DIR) $(STAGING_DIR_HOST)/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/tools/kwboot $(STAGING_DIR_HOST)/bin/
endef

$(eval $(call BuildPackage/U-Boot))
