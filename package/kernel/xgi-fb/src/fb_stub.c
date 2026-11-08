// SPDX-License-Identifier: GPL-2.0
/*
 * Stand-ins for drivers/video/cmdline.c and nomodeset.c: the kernel is built
 * without CONFIG_VIDEO, so there is no video= or nomodeset to parse.
 */

#include <linux/export.h>
#include <linux/fb.h>
#include <video/nomodeset.h>

bool video_firmware_drivers_only(void)
{
	return false;
}

int fb_get_options(const char *name, char **option)
{
	if (option)
		*option = NULL;

	return 0;
}
EXPORT_SYMBOL(fb_get_options);
