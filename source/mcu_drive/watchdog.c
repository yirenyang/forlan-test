/*
 * watchdog.c - watchdog.c config and achieve;
 *
 * Copyright (c) 2014 Forlan.yung(YANGHUALIANG)
 *
 */

#include "include.h"


/****************************************************************************
      常量申明区
****************************************************************************/
/* This value written in the Key register prevent the watchdog reset */
#define WATCHDOG_KEY_REFRESH            0xAA
/* This value written in the Key register start the watchdog counting down */
#define WATCHDOG_KEY_ENABLE             0x55
/* The watchdog reset timer is 1S */
#define WATCHDOG_TIMER_CONSTANT_VALUE   0xB71B00
#define WATCHDOG_INTERRUPT_MODE_START   0x00000001
#define WATCHDOG_RESET_MODE_START       0x00000003


/****************************************************************************
      函数声明区
****************************************************************************/
static void watchdog_config(void);
static void watchdog_clock_setup(void);
static void watchdog_workmode_set(void);
static void watchdog_timer_set(void);
static void watchdog_feedvalue_relaod(void);


/****************************************************************************
      函数定义区
****************************************************************************/
void watchdog_enable(void)
{
    watchdog_config();

    return;
}

void watchdog_disable(void)
{
    return;
}

void watchdog_reset(void)
{
    watchdog_feedvalue_relaod();

    return;
}

static void watchdog_config(void)
{
    watchdog_clock_setup();
    AHB_clock_enable(SYSAHBCLKCTRL_WDT_BIT_OFFSET_VAL);
    watchdog_timer_set();
    watchdog_workmode_set();
    watchdog_feedvalue_relaod();
    //NVIC_EnableIRQ(WDT_IRQn);

    return;
}

static void watchdog_clock_setup(void)
{
    /* 
     * Watchdog configuration.
     * wdt_osc_clk = Fclknana / (2 x (1 + DIVSEL))
     * Freq = 0.5Mhz, div_sel 为 0, 除以 2. WDT_OSC 是 250khz
     */
    LPC_SYSCON->WDTOSCCTRL = (WDTOSCCTRL_FREQSEL_VAL_0_5M << WDTOSCCTRL_FREQSEL_BIT_OFFSET_VAL) | WDTOSCCTRL_DIVSEL_VAL_02;

    /*
     * Select the main clock for watchdog clock source
     * Main_Clock = 48MHz
     */
    LPC_SYSCON->WDTCLKSEL = WDTCLKSEL_SRC_MAIN_CLK;

    /* Watchdog clock source update enable */
    LPC_SYSCON->WDTCLKUEN = CLOCK_UPDATE_STATE_UPDATE;              /* 更新时钟 */
    LPC_SYSCON->WDTCLKUEN = CLOCK_UPDATE_STATE_NO_UPDATE;           /* 切换更新寄存器一次 */
    LPC_SYSCON->WDTCLKUEN = CLOCK_UPDATE_STATE_UPDATE;
    while (!(LPC_SYSCON->WDTCLKUEN & 0x01));                        /* 等待直到更新完成 */

    /*
     * Set the watchdog clock divider value to 1
     * WATCHDOG_CLOCK = 48MHz
     * watchdog_cycle = 1 / WATCHDOG_CLOCK x WATCHDOG_TIMER_CONSTANT_VALUE x 4
     */
    LPC_SYSCON->WDTCLKDIV = WDTCLKDIV_VAL_SET_001;
    /* Power on the watchdog oscillator */
    LPC_SYSCON->PDRUNCFG &= ~(0x01 << PDRUNCFG_WDTOSC_PD_BIT_VAL);
}

static void watchdog_timer_set(void)
{
    LPC_WDT->TC = WATCHDOG_TIMER_CONSTANT_VALUE;
}

static void watchdog_workmode_set(void)
{
    LPC_WDT->MOD = WATCHDOG_RESET_MODE_START;
}

static void watchdog_feedvalue_relaod(void)
{
    LPC_WDT->FEED = WATCHDOG_KEY_REFRESH;
    LPC_WDT->FEED = WATCHDOG_KEY_ENABLE;
}

void isr_watchdog(void)
{
    /* Take care the sequence */

    /* Clear watchdog time-out flag */
    LPC_WDT->MOD &= ~(0x1 << WDMOD_WDTOF_BIT_OFFSET_VAL);
	/* Clear watchdog interrupt flag */
    LPC_WDT->MOD &= ~(0x1 << WDMOD_WDINT_BIT_OFFSET_VAL);
}

