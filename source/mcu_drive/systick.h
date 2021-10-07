/*
 * systick.h - systick.h config header file;
 *
 * Copyright (c) 2014 Forlan.yung(YANGHUALIANG)
 *
 */

#ifndef _SYSTICK_H_
#define _SYSTICK_H_

/* Global variables and functions defined in systick module */
#ifndef GLOBALS_SYSTICK
#define systick_extern extern
#else
#define systick_extern
#endif

/****************************************************************************
      常量申明区
****************************************************************************/
#define SYSTICK_LOAD_RELOAD_MSK                         0xFFFFFF                                    /* 滴答最大记数                       */
#define SYST_CSR_ENABLE_BIT_OFFSET_VAL                  0
#define SYST_CSR_TICKINT_BIT_OFFSET_VAL                 1
#define SYST_CST_CLKSOURCE_BIT_OFFSET_VAL               2

#define SCHEDULER_TIMER_4MS                             1
#define SCHEDULER_TIMER_12MS                            4
#define SCHEDULER_TIMER_32MS                            8
#define SCHEDULER_TIMER_100MS                           32

/* Initial value=0, Scheduler time=(1-0)*4=4ms */
#define SCHEDULER_TIMER0_INIT_VAL                       0
/* Initial value=1, Scheduler time=(4-1)*4=12ms */
#define SCHEDULER_TIMER1_INIT_VAL                       1
/* Initial value=0, Scheduler time=(8-0)*4=32ms */
#define SCHEDULER_TIMER2_INIT_VAL                       0
/* Initial value=7, Scheduler time=(32-7)*4=100ms */
#define SCHEDULER_TIMER3_INIT_VAL                       7


/****************************************************************************
      变量申明区
****************************************************************************/
systick_extern uint8_t n_scheduler_timer0;
systick_extern uint8_t n_scheduler_timer1;
systick_extern uint8_t n_scheduler_timer2;
systick_extern uint8_t n_scheduler_timer3;


/****************************************************************************
      函数申明区
****************************************************************************/
extern void systick_config(void);
extern void isr_systick(void);
extern void schedule_timer_4ms(void);


#endif

