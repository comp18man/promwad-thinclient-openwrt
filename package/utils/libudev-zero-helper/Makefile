include $(TOPDIR)/rules.mk

PKG_NAME:=libudev-zero-helper
PKG_VERSION:=1.0.4
PKG_RELEASE:=1

PKG_SOURCE:=libudev-zero-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://codeload.github.com/illiliti/libudev-zero/tar.gz/$(PKG_VERSION)?
PKG_HASH:=10148cfd6047d387bf71eca72cd19c177084224d96434a118d8def6e0a3d6316
PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)/libudev-zero-$(PKG_VERSION)

PKG_LICENSE:=ISC
PKG_LICENSE_FILES:=LICENSE

include $(INCLUDE_DIR)/package.mk

define Package/libudev-zero-helper
  SECTION:=utils
  CATEGORY:=Utilities
  TITLE:=Uevent rebroadcast for libudev-zero hotplug
  URL:=https://github.com/illiliti/libudev-zero
  DEPENDS:=+libudev-zero
endef

define Package/libudev-zero-helper/description
  libudev-zero monitors only hear uevents on netlink group 0x4, where
  udevd would resend them. This is contrib/helper.c from libudev-zero,
  run by procd hotplug for input devices.
endef

define Build/Compile
	$(TARGET_CC) $(TARGET_CPPFLAGS) $(TARGET_CFLAGS) $(TARGET_LDFLAGS) \
		-o $(PKG_BUILD_DIR)/helper $(PKG_BUILD_DIR)/contrib/helper.c
endef

define Package/libudev-zero-helper/install
	$(INSTALL_DIR) $(1)/usr/libexec $(1)/etc/hotplug.d/input
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/helper $(1)/usr/libexec/libudev-zero-helper
	$(INSTALL_DATA) ./files/input.hotplug $(1)/etc/hotplug.d/input/00-libudev-zero
endef

$(eval $(call BuildPackage,libudev-zero-helper))
