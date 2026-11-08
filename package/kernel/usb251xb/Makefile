include $(TOPDIR)/rules.mk
PKG_NAME:=usb251xb
PKG_RELEASE:=1
PKG_LICENSE:=GPL-2.0
PKG_MAINTAINER:=cmp18 comp18man@gmail.com

include $(INCLUDE_DIR)/kernel.mk
include $(INCLUDE_DIR)/package.mk

define KernelPackage/usb251xb
	SUBMENU:=USB Support
	TITLE:=Microchip USB251xB SMBus/I2C configuration driver
	DEPENDS:=+kmod-usb-core +kmod-i2c-core
	FILES:=$(PKG_BUILD_DIR)/usb251xb.ko
	AUTOLOAD:=$(call AutoLoad,70,usb251xb,1)
endef

define KernelPackage/usb251xb/description
	Out-of-tree build of the upstream usb251xb driver to configure Microchip USB251xB/USB351xB hubs over SMBus/I2C.
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) $(LINUX_DIR)/drivers/usb/misc/usb251xb.c $(PKG_BUILD_DIR)/
	echo 'obj-m += usb251xb.o' > $(PKG_BUILD_DIR)/Makefile
	$(Build/Patch)
endef

define Build/Compile
	$(KERNEL_MAKE) M="$(PKG_BUILD_DIR)" modules
endef

$(eval $(call KernelPackage,usb251xb))
