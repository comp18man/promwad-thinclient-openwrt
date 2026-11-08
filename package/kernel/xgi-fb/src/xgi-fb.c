// SPDX-License-Identifier: GPL-2.0
/*
 * XGI Volari Z11 (XG27) framebuffer in the mode set by U-Boot
 *
 * The mode registers sit behind the I/O BAR, which this driver keeps off,
 * so U-Boot leaves the mode in the last 4 KiB of VRAM: magic, width, height,
 * bpp, pitch.
 */

#include <linux/fb.h>
#include <linux/io.h>
#include <linux/module.h>
#include <linux/pci.h>
#include <linux/sizes.h>

#define XGI_MODE_INFO_MAGIC	0x42464758	/* "XGFB" */
#define XGI_MODE_INFO_SIZE	SZ_4K

static const struct fb_ops xgi_fb_ops = {
	.owner = THIS_MODULE,
	__FB_DEFAULT_IOMEM_OPS_RDWR,
	__FB_DEFAULT_IOMEM_OPS_MMAP,
};

static int xgi_fb_get_mode(struct pci_dev *pdev, struct fb_info *info)
{
	resource_size_t base = pci_resource_start(pdev, 0);
	resource_size_t size = pci_resource_len(pdev, 0);
	u32 magic, width, height, bpp, pitch;
	void __iomem *mi;

	mi = ioremap(base + size - XGI_MODE_INFO_SIZE, XGI_MODE_INFO_SIZE);
	if (!mi)
		return -ENOMEM;
	magic = readl(mi);
	width = readl(mi + 4);
	height = readl(mi + 8);
	bpp = readl(mi + 12);
	pitch = readl(mi + 16);
	iounmap(mi);

	if (magic != XGI_MODE_INFO_MAGIC) {
		dev_err(&pdev->dev, "no mode left by U-Boot\n");
		return -ENODEV;
	}
	if ((bpp != 16 && bpp != 32) || !width || !height ||
	    pitch < width * bpp / 8 ||
	    (u64)pitch * height > size - XGI_MODE_INFO_SIZE) {
		dev_err(&pdev->dev, "bad mode from U-Boot: %ux%u-%u, pitch %u\n",
			width, height, bpp, pitch);
		return -EINVAL;
	}

	info->var.xres = width;
	info->var.yres = height;
	info->var.xres_virtual = width;
	info->var.yres_virtual = height;
	info->var.bits_per_pixel = bpp;
	if (bpp == 16) {
		info->var.red = (struct fb_bitfield){ .offset = 11, .length = 5 };
		info->var.green = (struct fb_bitfield){ .offset = 5, .length = 6 };
		info->var.blue = (struct fb_bitfield){ .offset = 0, .length = 5 };
	} else {
		info->var.red = (struct fb_bitfield){ .offset = 16, .length = 8 };
		info->var.green = (struct fb_bitfield){ .offset = 8, .length = 8 };
		info->var.blue = (struct fb_bitfield){ .offset = 0, .length = 8 };
	}
	info->var.height = -1;
	info->var.width = -1;
	info->var.activate = FB_ACTIVATE_NOW;
	info->var.vmode = FB_VMODE_NONINTERLACED;

	strscpy(info->fix.id, "xgi-fb", sizeof(info->fix.id));
	info->fix.smem_start = base;
	info->fix.smem_len = PAGE_ALIGN(pitch * height);
	info->fix.type = FB_TYPE_PACKED_PIXELS;
	info->fix.visual = FB_VISUAL_TRUECOLOR;
	info->fix.line_length = pitch;
	info->fix.accel = FB_ACCEL_NONE;

	return 0;
}

static void xgi_fb_release(void *info)
{
	framebuffer_release(info);
}

static int xgi_fb_probe(struct pci_dev *pdev, const struct pci_device_id *id)
{
	struct fb_info *info;
	int ret;

	ret = pcim_enable_device(pdev);
	if (ret)
		return ret;

	ret = pcim_request_region(pdev, 0, "xgi-fb");
	if (ret)
		return ret;

	info = framebuffer_alloc(0, &pdev->dev);
	if (!info)
		return -ENOMEM;
	ret = devm_add_action_or_reset(&pdev->dev, xgi_fb_release, info);
	if (ret)
		return ret;

	ret = xgi_fb_get_mode(pdev, info);
	if (ret)
		return ret;

	info->screen_base = devm_ioremap_wc(&pdev->dev, info->fix.smem_start,
					    info->fix.smem_len);
	if (!info->screen_base)
		return -ENOMEM;
	info->screen_size = info->fix.smem_len;
	info->fbops = &xgi_fb_ops;

	ret = devm_register_framebuffer(&pdev->dev, info);
	if (ret)
		return ret;

	fb_info(info, "%ux%u-%u set by U-Boot\n", info->var.xres,
		info->var.yres, info->var.bits_per_pixel);

	return 0;
}

static const struct pci_device_id xgi_fb_ids[] = {
	{ PCI_DEVICE(0x18ca, 0x0027) },
	{ }
};
MODULE_DEVICE_TABLE(pci, xgi_fb_ids);

static struct pci_driver xgi_fb_driver = {
	.name		= "xgi-fb",
	.id_table	= xgi_fb_ids,
	.probe		= xgi_fb_probe,
};
module_pci_driver(xgi_fb_driver);

MODULE_DESCRIPTION("XGI Z11 framebuffer set up by U-Boot");
MODULE_LICENSE("GPL");
