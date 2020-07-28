/*
 * Copyright (C) 2016 MediaTek Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See http://www.gnu.org/licenses/gpl-2.0.html for more details.
 */

#define PFX "IMX230_pdafotp"
#define pr_fmt(fmt) PFX "[%s] " fmt, __func__


#include <linux/videodev2.h>
#include <linux/i2c.h>
#include <linux/platform_device.h>
#include <linux/delay.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/fs.h>
#include <linux/atomic.h>
#include <linux/slab.h>
#include "kd_camera_typedef.h"


#include "kd_imgsensor.h"
#include "kd_imgsensor_define.h"
#include "kd_imgsensor_errcode.h"
#include "imx230mipi_Sensor.h"


#define USHORT             unsigned short
#define BYTE               unsigned char
#define Sleep(ms) mdelay(ms)

#define IMX230_EEPROM_READ_ID  0xA0
#define IMX230_EEPROM_WRITE_ID   0xA1
#define IMX230_I2C_SPEED        100
#define IMX230_MAX_OFFSET		0xFFFF

#define DATA_SIZE 2048
#define SPC_START_ADDR (0x763 + 96)
#define DCC_START_ADDR 0x448

BYTE IMX230_DCC_data[96] = { 0 };

static bool get_done_dcc;
static int last_size_dcc;
static int last_offset_dcc;

static bool get_done_spc;
static int last_size_spc;
static int last_offset_spc;


static bool selective_read_eeprom(kal_uint16 addr, BYTE *data)
{
	char pu_send_cmd[2] = { (char)(addr >> 8), (char)(addr & 0xFF) };

	if (addr > IMX230_MAX_OFFSET)
		return false;

	if (iReadRegI2C(pu_send_cmd,
		2,
		(u8 *) data,
		1,
		IMX230_EEPROM_READ_ID) < 0)
		return false;
	return true;
}

static bool _read_imx230_eeprom(kal_uint16 addr, BYTE *data, int size)
{
	int i = 0;
	int offset = addr;


	for (i = 0; i < size; i++) {
		if (!selective_read_eeprom(offset, &data[i])) {
			pr_debug("%s fail 0x%0x %d\n", __func__, offset, i);
			return false;
		}
		offset++;
	}
	if (addr == SPC_START_ADDR) {
		get_done_spc = true;
		last_size_spc = size;
		last_offset_spc = offset;
	} else {
		get_done_dcc = true;
		last_size_dcc = size;
		last_offset_dcc = offset;
	}
	pr_debug("exit _read_eeprom size = %d\n", size);
	return true;
}


void read_imx230_SPC(BYTE *data)
{

	int addr = SPC_START_ADDR;
	int size = 352;

	pr_debug("read imx230 SPC, size = %d, %d\n", size, last_offset_spc);
#if 1
	if (!get_done_spc || last_size_spc != size) {
		if (!_read_imx230_eeprom(addr, data, size)) {
			get_done_spc = 0;
			last_size_spc = 0;
			last_offset_spc = 0;
		}
	}
#endif
	/* return true; */
}


void read_imx230_DCC(kal_uint16 addr, BYTE *data, kal_uint32 size)
{
	/* int i; */
	addr = DCC_START_ADDR;
	size = 96;

	pr_debug("read imx230 DCC, size = %d %d\n", size, last_offset_dcc);

	if (!get_done_dcc || last_size_dcc != size) {
		if (!_read_imx230_eeprom(addr, IMX230_DCC_data, size)) {
			get_done_dcc = 0;
			last_size_dcc = 0;
			last_offset_dcc = 0;
		}
	}

	memcpy(data, IMX230_DCC_data, size);
	/* return true; */
}
