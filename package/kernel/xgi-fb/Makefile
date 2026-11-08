include $(TOPDIR)/rules.mk

PKG_NAME:=xgi-fb
PKG_RELEASE:=1
PKG_LICENSE:=GPL-2.0

include $(INCLUDE_DIR)/kernel.mk
include $(INCLUDE_DIR)/package.mk

FB_CORE_FILES:= \
	fb_internal.h fbcon.h fb_info.c fbmem.c fbcmap.c modedb.c fbcvt.c \
	fb_chrdev.c fb_procfs.c fbsysfs.c fb_io_fops.c

define KernelPackage/xgi-fb
	SUBMENU:=Video Support
	TITLE:=XGI Z11 framebuffer set up by U-Boot
	DEPENDS:=@TARGET_kirkwood
	FILES:= \
		$(PKG_BUILD_DIR)/fb.ko \
		$(PKG_BUILD_DIR)/xgi-fb.ko
	AUTOLOAD:=$(call AutoLoad,30,fb xgi-fb)
endef

define KernelPackage/xgi-fb/description
	/dev/fb0 on the XGI Volari Z11 (XG27) in the mode U-Boot has set.
	The kernel is built without fbdev, so its core is built here too,
	from the kernel sources.
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) $(addprefix $(LINUX_DIR)/drivers/video/fbdev/core/,$(FB_CORE_FILES)) $(PKG_BUILD_DIR)/
	$(CP) ./src/* $(PKG_BUILD_DIR)/
endef

define Build/Compile
	$(KERNEL_MAKE) M="$(PKG_BUILD_DIR)" modules
endef

$(eval $(call KernelPackage,xgi-fb))
