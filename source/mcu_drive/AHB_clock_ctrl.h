/*
 * AHB_clock_ctrl.h - AHB_clock_ctrl.h config header file;
 *
 * Copyright (c) 2014 Forlan.yung(YANGHUALIANG)
 *
 */

#ifndef _AHB_CLOCK_CTL_H_
#define _AHB_CLOCK_CTL_H_


/****************************************************************************
      常量申明区
****************************************************************************/

/****************************************************************************
      函数申明区
****************************************************************************/
extern void AHB_clock_enable(uint8_t AHB_clk_src);
extern void AHB_clock_disable(uint8_t AHB_clk_src);

#endif

