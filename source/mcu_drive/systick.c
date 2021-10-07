/*
 * systick.c - systick.c config and achieve;
 *
 * Copyright (c) 2014 Forlan.yung(YANGHUALIANG)
 *
 */

#define GLOBALS_SYSTICK

#include "include.h"

 
/****************************************************************************
      常量申明区
****************************************************************************/
#define SYSTICK_TIME_4MS_RELAOD_VAL         0xFA


/****************************************************************************
      常量申明区
****************************************************************************/


/****************************************************************************
      函数申明区
****************************************************************************/
static void schedule_timer_4ms_init(void);
static uint8_t systick_init(void);


/****************************************************************************
      函数申明区
****************************************************************************/
void systick_config(void)
{
    schedule_timer_4ms_init();
    systick_init();
}

static void schedule_timer_4ms_init(void)
{
    n_scheduler_timer0 = SCHEDULER_TIMER0_INIT_VAL;
    n_scheduler_timer1 = SCHEDULER_TIMER1_INIT_VAL;
    n_scheduler_timer2 = SCHEDULER_TIMER2_INIT_VAL;
    n_scheduler_timer3 = SCHEDULER_TIMER3_INIT_VAL;
}

static uint8_t systick_init(void)
{
    uint32_t ticks;

    /*
     * system_clock_frequency = 48MHz
     * system timer = ticks / system_clock_frequency 
     *              = 1 / SYSTICK_TIME_4MS_RELAOD_VAL
     *              = 4ms
     */
    ticks = system_clock_frequency / SYSTICK_TIME_4MS_RELAOD_VAL;

    if (ticks > SYSTICK_LOAD_RELOAD_MSK)                                        /* Reload value impossible */
        return 1;

    SysTick->LOAD = (ticks & SYSTICK_LOAD_RELOAD_MSK) - 1;                      /* Set reload register */
    NVIC_SetPriority(SysTick_IRQn, (1 << __NVIC_PRIO_BITS) - 1);                /* set Priority for Cortex-M0 System Interrupts */
    SysTick->VAL = 0x00;                                                        /* Set the systick counter value */

    /* Enable SysTick IRQ and SysTick Timer */
    SysTick->CTRL = (1 << SYST_CST_CLKSOURCE_BIT_OFFSET_VAL)
                  | (1 << SYST_CSR_TICKINT_BIT_OFFSET_VAL)
                  | (1 << SYST_CSR_ENABLE_BIT_OFFSET_VAL);

    return 0;
}

void isr_systick(void)
{
    timer_4ms();

    return;
}

void schedule_timer_4ms(void)
{
    /* Initial value=0, Scheduler time=(1-0)*4=4ms */
    if (n_scheduler_timer0 != 0xff)
	{
		n_scheduler_timer0++;
	}

    /* Initial value=1, Scheduler time=(4-1)*4=12ms */
    if (n_scheduler_timer1 != 0xff)
	{
		n_scheduler_timer1++;
    }

    /* Initial value=0, Scheduler time=8*4=32ms */
    if (n_scheduler_timer2 != 0xff)
	{
		n_scheduler_timer2++;
    }

    /* Initial value=7, Scheduler time=(32-7)*4=100ms */
    if (n_scheduler_timer3 != 0xff)
	{
		n_scheduler_timer3++;
    }
    
    return;
}

