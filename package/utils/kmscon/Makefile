include $(TOPDIR)/rules.mk

PKG_NAME:=kmscon
PKG_VERSION:=10.0.4
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://codeload.github.com/kmscon/kmscon/tar.gz/v$(PKG_VERSION)?
PKG_HASH:=6918c748c26e9c8cfe81783400be3732792a73e532d6235f40c4b332ca4fde0b

PKG_LICENSE:=MIT
PKG_LICENSE_FILES:=COPYING
PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/meson.mk

define Package/kmscon
  SECTION:=utils
  CATEGORY:=Utilities
  TITLE:=Terminal emulator on the framebuffer
  URL:=https://github.com/kmscon/kmscon
  DEPENDS:=+libtsm +libudev +libudev-zero-helper +libxkbcommon \
	+xkeyboard-config +zlib +terminfo +kmod-input-evdev
endef

define Package/kmscon/description
  Login console on the framebuffer that also works on kernels without
  VT support. Built with the fbdev backend and the built-in 8x16 font only.
endef

MESON_ARGS += \
	--wrap-mode=nodownload \
	-Dtests=false \
	-Ddocs=disabled \
	-Dlibseat=disabled \
	-Ddbus=disabled \
	-Dvideo_fbdev=enabled \
	-Dvideo_drm2d=disabled \
	-Dvideo_drm3d=disabled \
	-Drenderer_gltex=disabled \
	-Dfont_psf=disabled \
	-Dfont_unifont=disabled \
	-Dfont_freetype=disabled \
	-Dfont_pango=disabled \
	-Dterm=xterm-256color

define Package/kmscon/install
	$(INSTALL_DIR) $(1)/usr/bin $(1)/etc/init.d
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/kmscon $(1)/usr/bin/
	$(INSTALL_BIN) ./files/kmscon.init $(1)/etc/init.d/kmscon
endef

$(eval $(call BuildPackage,kmscon))
