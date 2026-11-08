include $(TOPDIR)/rules.mk

PKG_NAME:=sound-soc-wtplug-tc
PKG_RELEASE:=1
PKG_LICENSE:=GPL-2.0

include $(INCLUDE_DIR)/kernel.mk
include $(INCLUDE_DIR)/package.mk

SOUND_FILES:= \
	soc/kirkwood/kirkwood.h soc/kirkwood/kirkwood-dma.c \
	soc/kirkwood/kirkwood-i2s.c soc/codecs/alc5623.h soc/codecs/alc5623.c \
	soc/generic/simple-card-utils.c soc/generic/simple-card.c

define KernelPackage/sound-soc-wtplug-tc
	SUBMENU:=Sound Support
	TITLE:=Kirkwood I2S, ALC5621 codec and simple-card
	DEPENDS:=@TARGET_kirkwood +kmod-sound-soc-core +kmod-regmap-i2c
	FILES:= \
		$(PKG_BUILD_DIR)/snd-soc-kirkwood.ko \
		$(PKG_BUILD_DIR)/snd-soc-alc5623.ko \
		$(PKG_BUILD_DIR)/snd-soc-simple-card-utils.ko \
		$(PKG_BUILD_DIR)/snd-soc-simple-card.ko
	AUTOLOAD:=$(call AutoLoad,60,snd-soc-kirkwood snd-soc-alc5623 snd-soc-simple-card-utils snd-soc-simple-card)
endef

define KernelPackage/sound-soc-wtplug-tc/description
	Out-of-tree build of the upstream Kirkwood I2S, ALC5623/ALC5621 codec
	and simple-audio-card drivers for the onboard sound of the WTPlug TC.
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) $(addprefix $(LINUX_DIR)/sound/,$(SOUND_FILES)) $(PKG_BUILD_DIR)/
	$(CP) ./src/* $(PKG_BUILD_DIR)/
	$(Build/Patch)
endef

define Build/Compile
	$(KERNEL_MAKE) M="$(PKG_BUILD_DIR)" modules
endef

$(eval $(call KernelPackage,sound-soc-wtplug-tc))
