/*
 * Copyright (C) 2015 MediaTek Inc.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */

#ifndef __MTK_CM_MGR_PLATFORM_REG_H__
#define __MTK_CM_MGR_PLATFORM_REG_H__

#undef MCUSYS_MP0
#define MCUSYS_MP0 mcucfg_mp0_counter_base

#define MP0_CPU_AVG_STALL_RATIO	(MCUSYS_MP0 + 0x1600)
#define MP0_CPU0_AVG_STALL_RATIO_CTRL	(MCUSYS_MP0 + 0x1604)
#define MP0_CPU1_AVG_STALL_RATIO_CTRL	(MCUSYS_MP0 + 0x1608)
#define MP0_CPU2_AVG_STALL_RATIO_CTRL	(MCUSYS_MP0 + 0x160C)
#define MP0_CPU3_AVG_STALL_RATIO_CTRL	(MCUSYS_MP0 + 0x1610)
#define MP0_AVG_STALL_RATIO_STATUS	(MCUSYS_MP0 + 0x1614)
#define MP0_CPU0_STALL_COUNTER	(MCUSYS_MP0 + 0x1618)
#define MP0_CPU1_STALL_COUNTER	(MCUSYS_MP0 + 0x161C)
#define MP0_CPU2_STALL_COUNTER	(MCUSYS_MP0 + 0x1620)
#define MP0_CPU3_STALL_COUNTER	(MCUSYS_MP0 + 0x1624)
#define MP0_CPU0_NON_WFI_COUNTER	(MCUSYS_MP0 + 0x1628)
#define MP0_CPU1_NON_WFI_COUNTER	(MCUSYS_MP0 + 0x162C)
#define MP0_CPU2_NON_WFI_COUNTER	(MCUSYS_MP0 + 0x1630)
#define MP0_CPU3_NON_WFI_COUNTER	(MCUSYS_MP0 + 0x1634)
#define MP0_CPU_STALL_INFO	(MCUSYS_MP0 + 0x1638)

#define RG_CPU0_AVG_STALL_RATIO	(1 << 0)
#define RG_CPU1_AVG_STALL_RATIO	(1 << 8)
#define RG_CPU2_AVG_STALL_RATIO	(1 << 16)
#define RG_CPU3_AVG_STALL_RATIO	(1 << 24)

#define RG_CPU0_AVG_STALL_RATIO_EN	(1 << 0)
#define RG_CPU0_AVG_STALL_RATIO_RESTART	(1 << 1)
#define RG_CPU0_STALL_COUNTER_EN	(1 << 4)
#define RG_CPU0_NON_WFX_COUNTER_EN	(1 << 5)
#define RG_CPU0_STALL_COUNTER_RESET	(1 << 6)
#define RG_CPU0_NON_WFX_COUNTER_RESET	(1 << 7)
#define RG_MP0_AVG_STALL_PERIOD	8
#define RG_MP0_AVG_STALL_PERIOD_1MS	(0x8 << RG_MP0_AVG_STALL_PERIOD)
#define RG_MP0_AVG_STALL_PERIOD_2MS	(0x9 << RG_MP0_AVG_STALL_PERIOD)
#define RG_MP0_AVG_STALL_PERIOD_4MS	(0xa << RG_MP0_AVG_STALL_PERIOD)
#define RG_MP0_AVG_STALL_PERIOD_8MS	(0xb << RG_MP0_AVG_STALL_PERIOD)
#define RG_MP0_AVG_STALL_PERIOD_10MS	(0xc << RG_MP0_AVG_STALL_PERIOD)
#define RG_MP0_AVG_STALL_PERIOD_20MS	(0xd << RG_MP0_AVG_STALL_PERIOD)
#define RG_MP0_AVG_STALL_PERIOD_40MS	(0xe << RG_MP0_AVG_STALL_PERIOD)
#define RG_MP0_AVG_STALL_PERIOD_80MS	(0xf << RG_MP0_AVG_STALL_PERIOD)
#define RG_FMETER_MIN_FREQUENCY	(1 << 12)
#define RG_FMETER_EN	(1 << 24)

#define cm_mgr_read(addr)	__raw_readl((void __force __iomem *)(addr))
#define cm_mgr_write(addr, val)	mt_reg_sync_writel(val, addr)

#endif /* __MTK_CM_MGR_PLATFORM_REG_H__*/
