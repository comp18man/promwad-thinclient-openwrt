include $(TOPDIR)/rules.mk

PKG_NAME:=libtsm
PKG_VERSION:=4.8.0
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://codeload.github.com/kmscon/libtsm/tar.gz/v$(PKG_VERSION)?
PKG_HASH:=50811e9e94fc798eb5dcbaff20f81067c942ec47f329f91bbe4caeb35a61ff05

PKG_LICENSE:=MIT
PKG_LICENSE_FILES:=COPYING
PKG_BUILD_DEPENDS:=libxkbcommon
PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/meson.mk

define Package/libtsm
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=Terminal-emulator state machine
  URL:=https://github.com/kmscon/libtsm
endef

define Package/libtsm/description
  State machine for DEC VT100-VT520 compatible terminal emulators.
endef

MESON_ARGS += \
	-Dtests=false \
	-Dextra_debug=false \
	-Dgtktsm=false

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include $(1)/usr/lib/pkgconfig
	$(CP) $(PKG_INSTALL_DIR)/usr/include/libtsm.h $(1)/usr/include/
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libtsm.so* $(1)/usr/lib/
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/pkgconfig/libtsm.pc $(1)/usr/lib/pkgconfig/
endef

define Package/libtsm/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libtsm.so.* $(1)/usr/lib/
endef

$(eval $(call BuildPackage,libtsm))
