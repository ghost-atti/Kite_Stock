/*
 * LP5521 LED chip driver.
 *
 * Copyright (C) 2010 Nokia Corporation
 *
 * Contact: Samu Onkalo <samu.p.onkalo@nokia.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA
 */

#ifndef __LINUX_LP5521_H
#define __LINUX_LP5521_H

/* See Documentation/leds/leds-lp5521.txt */

struct lp5521_led_config {
	char		*name;
	u8		chan_nr;
	u8		led_current; /* mA x10, 0 if led is not connected */
	u8		max_current;
};

struct lp5521_led_pattern {
	const u8 *r;
	const u8 *g;
	const u8 *b;
	u8 size_r;
	u8 size_g;
	u8 size_b;
};

#define LP5521_CLOCK_AUTO	0
#define LP5521_CLOCK_INT	1
#define LP5521_CLOCK_EXT	2

/* Bits in CONFIG register */
#define LP5521_PWM_HF			0x40	/* PWM: 0 = 256Hz, 1 = 558Hz */
#define LP5521_PWRSAVE_EN		0x20	/* 1 = Power save mode */
#define LP5521_CP_MODE_OFF		0	/* Charge pump (CP) off */
#define LP5521_CP_MODE_BYPASS		8	/* CP forced to bypass mode */
#define LP5521_CP_MODE_1X5		0x10	/* CP forced to 1.5x mode */
#define LP5521_CP_MODE_AUTO		0x18	/* Automatic mode selection */
#define LP5521_R_TO_BATT		4	/* R out: 0 = CP, 1 = Vbat */
#define LP5521_CLK_SRC_EXT		0	/* Ext-clk source (CLK_32K) */
#define LP5521_CLK_INT			1	/* Internal clock */
#define LP5521_CLK_AUTO			2	/* Automatic clock selection */

struct lp5521_platform_data {
	struct lp5521_led_config *led_config;
	u8	num_channels;
	u8	clock_mode;
	int	(*setup_resources)(void);
	void	(*release_resources)(void);
	void	(*enable)(bool state);
	const char *label;
	u8	update_config;
	struct lp5521_led_pattern *patterns;
	int num_patterns;
};
#define LP5521_INFO_PRINT   	(1)

#if defined(LP5521_INFO_PRINT)
#define LP5521_INFO_MSG(fmt, args...) \
		printk(KERN_INFO "[LP5521] " fmt, ##args);
#else
#define LP5521_INFO_MSG(fmt, args...)     {};
#endif

#ifdef CONFIG_LEDS_LP5521
/*[pattern_id : 1, PowerOn_Animation]*/
static const u8 mode1_red[] = {0xE0, 0x0C, 0x40, 0x00, 0x0C, 0x2F, 0x06, 0x28, 0x05, 0x2D, 0x06, 0x2A, 0x06, 0x25, 0x03, 0xDC, 0x02, 0xFA, 0x48, 0x00, 0x03, 0x54, 0x44, 0x01, 0x23, 0x06, 0x31, 0x84, 0x06, 0xA8, 0x0C, 0xAF};
static const u8 mode1_green[] = {0xE0, 0x80, 0x40, 0x00, 0x52, 0x00, 0x0B, 0x15, 0x05, 0x2D, 0x03, 0x48, 0x03, 0x4B, 0x09, 0x1B, 0x02, 0x63, 0x19, 0x89, 0x03, 0xCA, 0x04, 0xC1, 0x05, 0xB2, 0x06, 0xA6, 0x12, 0x8D, 0x52, 0x00};
static const u8 mode1_blue[] = {0xE0, 0x80, 0x40, 0x00, 0x12, 0xFE, 0x40, 0xC0, 0x0A, 0x18, 0x06, 0xA6, 0x06, 0xAA, 0x03, 0xCF, 0x04, 0xB6, 0x52, 0x00};

/*[pattern_id : 2, Not used, LCDOn]*/
static const u8 mode2_red[]={0x40, 0xff, 0x4d, 0x00, 0x0a, 0xff, 0x0a, 0xfe, 0xc0, 0x00};
static const u8 mode2_green[]={0x40, 0xff, 0x4d, 0x00, 0x0a, 0xff, 0x0a, 0xfe, 0xc0, 0x00};
static const u8 mode2_blue[]={0x40, 0xff, 0x4d, 0x00, 0x0a, 0xff, 0x0a, 0xfe, 0xc0, 0x00};

/*[pattern_id : 3, Charging0_99]*/
static const u8 mode3_red[] = {0x40, 0x0D, 0x44, 0x0C, 0x24, 0x32, 0x24, 0x32, 0x66, 0x00, 0x24, 0xB2, 0x24, 0xB2, 0x44, 0x8C};

/*[pattern_id : 4, Charging100]*/
static const u8 mode4_green[]={0x40, 0x80};

/*[pattern_id : 5, Not used, Charging16_99]*/
static const u8 mode5_red[]={0x40, 0x19, 0x27, 0x19, 0xe0, 0x04, 0x0c, 0x65, 0xe0, 0x04, 0x0c, 0x65, 0xe0, 0x04, 0x0c, 0xe5, 0xe0, 0x04, 0x0c, 0xe5, 0xe0, 0x04, 0x29, 0x98, 0xe0, 0x04, 0x5a, 0x00};
static const u8 mode5_green[]={0x40, 0x0c, 0x43, 0x0b, 0xe0, 0x80, 0x19, 0x30, 0xe0, 0x80, 0x19, 0x30, 0xe0, 0x80, 0x19, 0xb0, 0xe0, 0x80, 0x19, 0xb0, 0xe0, 0x80, 0x43, 0x8b, 0xe0, 0x80, 0x5a, 0x00};

/*[pattern_id : 6, PowerOff]*/
static const u8 mode6_red[] = {0xE0, 0x0C, 0x40, 0x00, 0x0C, 0x2F, 0x06, 0x28, 0x05, 0x2D, 0x06, 0x2A, 0x06, 0x25, 0x03, 0xDC, 0x02, 0xFA, 0x48, 0x00, 0x03, 0x54, 0x44, 0x01, 0x23, 0x06, 0x31, 0x84, 0x06, 0xA8, 0x0C, 0xAF};
static const u8 mode6_green[] = {0xE0, 0x80, 0x40, 0x00, 0x52, 0x00, 0x0B, 0x15, 0x05, 0x2D, 0x03, 0x48, 0x03, 0x4B, 0x09, 0x1B, 0x02, 0x63, 0x19, 0x89, 0x03, 0xCA, 0x04, 0xC1, 0x05, 0xB2, 0x06, 0xA6, 0x12, 0x8D, 0x52, 0x00};
static const u8 mode6_blue[] = {0xE0, 0x80, 0x40, 0x00, 0x12, 0xFE, 0x40, 0xC0, 0x0A, 0x18, 0x06, 0xA6, 0x06, 0xAA, 0x03, 0xCF, 0x04, 0xB6, 0x52, 0x00,};

/*[pattern_id : 7, MissedNoti]*/
static const u8 mode7_red[]={0x40, 0x00, 0x10, 0xFE, 0x40, 0x5D, 0xE2, 0x00, 0x07, 0xAD, 0xE2, 0x00, 0x07, 0xAE, 0xE2, 0x00, 0x48, 0x00, 0x40, 0x5D, 0xE2, 0x00, 0x07, 0xAD, 0xE2, 0x00, 0x07, 0xAE, 0xE2, 0x00, 0x25, 0xFE,};
static const u8 mode7_green[]={0x40, 0x00, 0x10, 0xFE, 0x40, 0xCD, 0xE2, 0x00, 0x03, 0xE6, 0xE2, 0x00, 0x03, 0xE5, 0xE2, 0x00, 0x48, 0x00, 0x40, 0xCD, 0xE2, 0x00, 0x03, 0xE6, 0xE2, 0x00, 0x03, 0xE5, 0xE2, 0x00, 0x25, 0xFE,};
static const u8 mode7_blue[]={0x40, 0x00, 0x10, 0xFE, 0x40, 0xE6, 0xE0, 0x06, 0x03, 0xF2, 0xE0, 0x06, 0x03, 0xF2, 0xE0, 0x06, 0x48, 0x00, 0x40, 0xE6, 0xE0, 0x06, 0x03, 0xF2, 0xE0, 0x06, 0x03, 0xF2, 0xE0, 0x06, 0x25, 0xFE,};

#if defined(CONFIG_MACH_APQ8064_GK_KR) || defined(CONFIG_MACH_APQ8064_GKATT)
/*[pattern_id : 14, MissedNoti(favorite)]*/
static const u8 mode8_red[]={0x40, 0x00, 0x10, 0xFE, 0x40, 0xFF, 0x4F, 0x00, 0x05, 0xE5, 0xE0, 0x0C, 0x05, 0xE5, 0xE0, 0x0C, 0x40, 0xFF, 0x4F, 0x00, 0x04, 0xFF, 0xE0, 0x0C, 0x04, 0xFE, 0xE0, 0x0C, 0x1A, 0xFE,};
static const u8 mode8_green[]={0x40, 0x00, 0x10, 0xFE, 0x40, 0x66, 0x4F, 0x00, 0x0B, 0xA8, 0xE0, 0x80, 0x0B, 0xA8, 0xE0, 0x80, 0x40, 0x66, 0x4F, 0x00, 0x09, 0xB2, 0xE0, 0x80, 0x09, 0xB2, 0xE0, 0x80, 0x1A, 0xFE,};
static const u8 mode8_blue[]={0x40, 0x00, 0x10, 0xFE, 0x40, 0x73, 0x4F, 0x00, 0x08, 0xBC, 0xE0, 0x80, 0x0F, 0x9E, 0xE0, 0x80, 0x40, 0x73, 0x4F, 0x00, 0x05, 0xD5, 0xE0, 0x80, 0x10, 0x9C, 0xE0, 0x80, 0x1A, 0xFE,};
#elif defined(CONFIG_MACH_APQ8064_GVDCM)
//[pattern_id 101, Felica_on]
static const  u8 mode8_blue[]={0x40, 0x33, 0x04, 0x65, 0x04, 0x65, 0x04, 0xE5, 0x04, 0xE5, 0x00, 0x00};

//[pattern_id 102, GPS_on]
static const u8 mode9_blue[]={0x40, 0x00, 0x08, 0x7E, 0x08, 0x7F, 0x08, 0xFE, 0x08, 0xFF, 0x00, 0x00};
#endif

#endif /* CONFIG_LEDS_LP5521 */

#endif /* __LINUX_LP5521_H */
