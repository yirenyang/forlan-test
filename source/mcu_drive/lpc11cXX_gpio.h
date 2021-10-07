/*
 * lpc11cXX_gpio.h - lpc11cXX_gpio.h config header file;
 *
 * Copyright (c) 2014 Forlan.yung(YANGHUALIANG)
 *
 */

#ifndef _GPIO_H_
#define _GPIO_H_


/****************************************************************************
      常量申明区
****************************************************************************/
#define PORT0		0
#define PORT1		1
#define PORT2		2
#define PORT3		3

#define IOCON_FUNC_BIT_OFFSET_VAL           0            /* Bit 2:0 */
#define IOCON_SCK_LOC_BIT_OFFSET_VAL        0            /* Bit 1:0 */
#define IOCON_DSR_LOC_BIT_OFFSET_VAL        0            /* Bit 1:0 */
#define IOCON_DCD_LOC_BIT_OFFSET_VAL        0            /* Bit 1:0 */
#define IOCON_RI_LOC_BIT_OFFSET_VAL         0            /* Bit 1:0 */
#define IOCON_MODE_BIT_OFFSET_VAL           3            /* Bit 4:3 */
#define IOCON_HYS_BIT_OFFSET_VAL            5            /* Bit 5 */
#define IOCON_ADMODE_BIT_OFFSET_VAL         7            /* Bit 7 */
#define IOCON_I2CMODE_OFFSET_VAL            8            /* Bit 9:8 */
#define IOCON_OD_BIT_OFFSET_VAL             10           /* Bit 10 */

#define IOCON_FUNC_BIT_MASK_VAL             0x07
#define IOCON_MODE_BIT_MASK_VAL             0x18
#define IOCON_HYS_BIT_MASK_VAL              0x20

#define IOCON_PIO0_1_FUNC_GPIO              0x00
#define IOCON_PIO0_1_FUNC_CLKOUT            0x01
#define IOCON_PIO0_1_FUNC_CT32B0_MAT2       0x02

#define IOCON_PIO1_6_FUNC_GPIO              0x00
#define IOCON_PIO1_6_FUNC_RXD               0x01
#define IOCON_PIO1_6_FUNC_CT32B0_MAT0       0x02

#define IOCON_PIO1_7_FUNC_GPIO              0x00
#define IOCON_PIO1_7_FUNC_TXD               0x01
#define IOCON_PIO1_7_FUNC_CT32B0_MAT1       0x02

enum
{
    GPIO_DIRECTION_STATUS_INPUT = 0,
    GPIO_DIRECTION_STATUS_OUTPUT
};

enum
{
    GPIO_DATA_STATUS_LOW = 0,
    GPIO_DATA_STATUS_HIGH
};

enum
{
    INTERRUPT_AS_EDGE_SENSITIVE = 0,
    INTERRUPT_AS_LEVEL_SENSITIVE
};

enum
{
    INTERRUPT_SIGNAL_AS_LEVEL_OR_SINGLE_EDGE = 0,
    INTERRUPT_SIGNAL_AS_BOTH_EDGES
};

enum
{
    INTERRUPT_EVENT_FALLEDGES_OR_LOWLEVEL = 0,
    INTERRUPT_EVENT_RISEEDGES_OR_HIGHLEVEL
};

enum
{
    RAW_INTERRUPT_STATUS_NO_INTERRUPT = 0,
    RAW_INTERRUPT_STATUS_INTERRUPT
};


/****************************************************************************
      常量申明区
****************************************************************************/
extern void mcu_io_init(void);
extern void gpio_direction_value_set(uint32_t port_num, uint32_t bit_posi, uint32_t dir_val);
extern void gpio_data_value_set(uint32_t port_num, uint32_t bit_posi, uint32_t bit_val);
extern void gpio_data_value_turn(uint32_t port_num, uint32_t bit_posi);
extern uint8_t gpio_data_value_get(uint32_t port_num, uint32_t bit_posi);
extern void gpio_interrupt_set(uint32_t port_num, uint32_t bit_posi, uint32_t sense, uint32_t signal, uint32_t event);
extern void gpio_interrupt_enable(uint32_t port_num, uint32_t bit_posi);
extern void gpio_interrupt_disable(uint32_t port_num, uint32_t bit_posi);
extern uint8_t gpio_interrupt_satus_get(uint32_t port_num, uint32_t bit_posi);
extern void gpio_edge_interrupt_clear(uint32_t port_num, uint32_t bit_posi);


#endif

