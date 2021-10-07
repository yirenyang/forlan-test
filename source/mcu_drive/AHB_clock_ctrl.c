/*
 * AHB_clock_ctrl.c - AHB_clock_ctrl.c config and achieve;
 *
 * Copyright (c) 2014 Forlan.yung(YANGHUALIANG)
 *
 */

#include "include.h"


/****************************************************************************
      函数定义区
****************************************************************************/
void AHB_clock_enable(const uint8_t AHB_clk_src)
{
	LPC_SYSCON->SYSAHBCLKCTRL |= (1 << AHB_clk_src);
}

void AHB_clock_disable(const uint8_t AHB_clk_src)
{
	LPC_SYSCON->SYSAHBCLKCTRL &= ~(1 << AHB_clk_src);
}


