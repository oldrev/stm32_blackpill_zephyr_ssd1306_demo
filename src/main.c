/*
 * Copyright (c) 2018 PHYTEC Messtechnik GmbH
 * Copyright (c) 2020 Li "oldrev" Wei <oldrevATTgmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <device.h>
#include <display/cfb.h>
#include <stdio.h>

#include "cfb_font_fixedsys32.h"
#include "cfb_font_jetbrains_mono_bold.h"

#if defined(CONFIG_SSD1306)
#define DISPLAY_DRIVER "SSD1306"
#endif

#ifndef DISPLAY_DRIVER
#define DISPLAY_DRIVER "DISPLAY"
#endif

void main(void)
{
	const struct device *dev;
	uint16_t rows;
	uint8_t ppt;

	dev = device_get_binding(DISPLAY_DRIVER);

	if (dev == NULL)
	{
		printf("Device not found\n");
		return;
	}

	if (display_set_pixel_format(dev, PIXEL_FORMAT_MONO10) != 0)
	{
		printf("Failed to set required pixel format\n");
		return;
	}

	printf("initialized %s\n", DISPLAY_DRIVER);

	if (cfb_framebuffer_init(dev))
	{
		printf("Framebuffer initialization failed!\n");
		return;
	}

	cfb_framebuffer_clear(dev, true);

	display_blanking_off(dev);

	rows = cfb_get_display_parameter(dev, CFB_DISPLAY_ROWS);
	ppt = cfb_get_display_parameter(dev, CFB_DISPLAY_PPT);

	for (int idx = 0; idx < 42; idx++)
	{
		int font_width, font_height;
		if (cfb_get_font_size(dev, idx, &font_width, &font_height))
		{
			break;
		}
		cfb_framebuffer_set_font(dev, idx);
		printf("font width %d, font height %d\n",
			   font_width, font_height);
	}

	printf("x_res %d, y_res %d, ppt %d, rows %d, cols %d\n",
		   cfb_get_display_parameter(dev, CFB_DISPLAY_WIDTH),
		   cfb_get_display_parameter(dev, CFB_DISPLAY_HEIGH),
		   ppt,
		   rows,
		   cfb_get_display_parameter(dev, CFB_DISPLAY_COLS));

	char buf[32];
	int i = 0;
	while (1)
	{
		cfb_framebuffer_clear(dev, false);
		cfb_framebuffer_set_font(dev, 1);
		cfb_print(dev, "Hi! FixedSys32!", 0, 0);
		cfb_framebuffer_set_font(dev, 0);
		snprintf(buf, sizeof(buf), "%d", i);
		cfb_print(dev, buf, 0, 16);
		cfb_framebuffer_finalize(dev);
		i++;
		k_msleep(1000);
	}
}
