/*
 * interrupt.c - interrupt.c config and achieve;
 *
 * Copyright (c) 2014 Forlan.yung(YANGHUALIANG)
 *
 */

#include "include.h"


/****************************************************************************
      函数定义区
****************************************************************************/
/* @brief nmi interrupt routine */
void remap_nmi_handler(void)
{
    return;
}

/* @brief hardfault interrupt routine */
void remap_hardfault_handler(void)
{
    __nop();
    __nop();
    /* Wait WatchDog  timeout and reset the MCU */
    for (;;);
}

/* @brief memmanage interrupt routine */
void remap_memmanage_handler(void)
{
    __nop();
    __nop();
    /* Wait WatchDog  timeout and reset the MCU */
    for (;;);
}

/* @brief busfault interrupt routine */
void remap_busfault_handler(void)
{
    __nop();
    __nop();
    /* Wait WatchDog  timeout and reset the MCU */
    for (;;);
}

/* @brief usagefault interrupt routine */
void remap_usagefault_handler(void)
{
    __nop();
    __nop();
    /* Wait WatchDog  timeout and reset the MCU */
    for (;;);
}

/* @brief svc interrupt routine */
void remap_svc_handler(void)
{
    return;
}

/* @brief debugmon interrupt routine */
void remap_debugmon_handler(void)
{
    return;
}

/* @brief pendsv interrupt routine */
void remap_pendsv_handler(void)
{
    return;
}

/* @brief systick interrupt routine */
void remap_systick_handler(void)
{
    isr_systick();
    return;
}

/* @brief can interrupt routine */
void remap_can_irqhandler(void)
{
    isr_can(GptCanNode0);
    return;
}

/* @brief ssp1 interrupt routine */
void remap_ssp1_irqhandler(void)
{
    return;
}

/* @brief i2c interrupt routine */
void remap_i2c_irqhandler(void)
{
    return;
}

/* @brief timer16_0 interrupt routine */
void remap_timer16_0_irqhandler(void)
{
    return;
}

/* @brief timer16_1 interrupt routine */
void remap_timer16_1_irqhandler(void)
{
    return;
}

/* @brief timer32_0 interrupt routine */
void remap_timer32_0_irqhandler(void)
{
    return;
}

/* @brief timer32_1 interrupt routine */
void remap_timer32_1_irqhandler(void)
{
    return;
}

/* @brief ssp0 interrupt routine */
void remap_ssp0_irqhandler(void)
{
    return;
}

/* @brief uart interrupt routine */
void remap_uart_irqhandler(void)
{
    isr_uart();
    return;
}

/* @brief usb interrupt routine */
void remap_usb_irqhandler(void)
{
    return;
}

/* @brief usb fiq interrupt routine */
void remap_usb_fiqhandler(void)
{
    return;
}

/* @brief adc interrupt routine */
void remap_adc_irqhandler(void)
{
    return;
}

/* @brief wdt interrupt routine */
void remap_wdt_irqhandler(void)
{
    isr_watchdog();
    return;
}

/* @brief bod interrupt routine */
void remap_bod_irqhandler(void)
{
    return;
}

/* @brief fmc interrupt routine */
void remap_fmc_irqhandler(void)
{
    return;
}

/* @brief pioint3 interrupt routine */
void remap_pioint3_irqhandler(void)
{
    return;
}

/* @brief pioint2 interrupt routine */
void remap_pioint2_irqhandler(void)
{
    return;
}

/* @brief pioint1 interrupt routine */
void remap_pioint1_irqhandler(void)
{
    return;
}

/* @brief pioint0 interrupt routine */
void remap_pioint0_irqhandler(void)
{
    return;
}


