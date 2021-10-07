/*
 * watchdog.h - watchdog.h config header file;
 *
 * Copyright (c) 2014 Forlan.yung(YANGHUALIANG)
 *
 */
 
#ifndef _WATCHDOG_H_
#define _WATCHDOG_H_


/****************************************************************************
      常量声明区
****************************************************************************/
#define WDMOD_WDEN_BIT_OFFSET_VAL       0
#define WDMOD_WDRESET_BIT_OFFSET_VAL    1
#define WDMOD_WDTOF_BIT_OFFSET_VAL      2
#define WDMOD_WDINT_BIT_OFFSET_VAL      3


/****************************************************************************
      函数申明区
****************************************************************************/
extern void watchdog_enable(void);
extern void watchdog_disable(void);
extern void watchdog_reset(void);
extern void isr_watchdog(void);


#endif  //_WATCHDOG_H_

