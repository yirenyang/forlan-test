/*
 * Remap_interrupt.h - Remap_interrupt.h config header file;
 *
 * Copyright (c) 2014 Forlan.yung(YANGHUALIANG)
 *
 */

#ifndef _REMAP_INTERRUPT_H_
#define _REMAP_INTERRUPT_H_


/****************************************************************************
      º¯ÊýÉêÃ÷Çø
****************************************************************************/
extern void remap_reset_handler(void);
extern void remap_nmi_handler(void);
extern void remap_hardfault_handler(void);
extern void remap_memmanage_handler(void);
extern void remap_busfault_handler(void);
extern void remap_usagefault_handler(void);
extern void remap_svc_handler(void);
extern void remap_debugmon_handler(void);
extern void remap_pendsv_handler(void);
extern void remap_systick_handler(void);

extern void remap_can_irqhandler(void);
extern void remap_ssp1_irqhandler(void);
extern void remap_i2c_irqhandler(void);
extern void remap_timer16_0_irqhandler(void);
extern void remap_timer16_1_irqhandler(void);
extern void remap_timer32_0_irqhandler(void);
extern void remap_timer32_1_irqhandler(void);
extern void remap_ssp0_irqhandler(void);
extern void remap_uart_irqhandler(void);
extern void remap_usb_irqhandler(void);
extern void remap_usb_fiqhandler(void);
extern void remap_adc_irqhandler(void);
extern void remap_wdt_irqhandler(void);
extern void remap_bod_irqhandler(void);
extern void remap_fmc_irqhandler(void);
extern void remap_pioint3_irqhandler(void);
extern void remap_pioint2_irqhandler(void);
extern void remap_pioint1_irqhandler(void);
extern void remap_pioint0_irqhandler(void);

#endif

