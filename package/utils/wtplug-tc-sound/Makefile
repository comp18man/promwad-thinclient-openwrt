include $(TOPDIR)/rules.mk

PKG_NAME:=wtplug-tc-sound
PKG_RELEASE:=1
PKG_LICENSE:=GPL-2.0

include $(INCLUDE_DIR)/package.mk

define Package/wtplug-tc-sound
  SECTION:=utils
  CATEGORY:=Utilities
  TITLE:=ALSA setup for the WTPlug TC onboard sound
  DEPENDS:=@TARGET_kirkwood +kmod-sound-soc-wtplug-tc +alsa-utils +alsa-utils-tests
  PKGARCH:=all
endef

define Package/wtplug-tc-sound/description
  Restores the ALC5621 mixer (headphones and the internal buzzer) when
  the sound card appears, then beeps once.
endef

define Package/wtplug-tc-sound/conffiles
/etc/asound.state
endef

define Build/Compile
endef

define Package/wtplug-tc-sound/install
	$(INSTALL_DIR) $(1)/etc/hotplug.d/sound
	$(INSTALL_DATA) ./files/sound.hotplug $(1)/etc/hotplug.d/sound/50-wtplug-tc
	$(INSTALL_DATA) ./files/asound.state $(1)/etc/asound.state
endef

$(eval $(call BuildPackage,wtplug-tc-sound))
