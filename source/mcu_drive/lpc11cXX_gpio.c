/*
 * lpc11cXX_gpio.c - lpc11cXX_gpio.c config and achieve;
 *
 * Copyright (c) 2014 Forlan.yung(YANGHUALIANG)
 *
 */

#include "include.h"


/****************************************************************************
      函数定义区
****************************************************************************/
/*
 * @function name: mcu_io_init();
 * @brief: init mcu gpio;
 * @param: no
 * @return: no
 */
void mcu_io_init(void)
{
    /* 使能AHB时钟到GPIO域。*/
    AHB_clock_enable(SYSAHBCLKCTRL_GPIO_BIT_OFFSET_VAL);

    /* CLKOUT I/O config */
    LPC_IOCON->PIO0_1 &= ~IOCON_FUNC_BIT_MASK_VAL;	
    LPC_IOCON->PIO0_1 |= IOCON_PIO0_1_FUNC_CLKOUT;		        /* CLK OUT */

    /* UART I/O config */
    LPC_IOCON->PIO1_6 &= ~IOCON_FUNC_BIT_MASK_VAL;
    LPC_IOCON->PIO1_6 |= IOCON_PIO1_6_FUNC_RXD;                 /* UART RXD */
    LPC_IOCON->PIO1_7 &= ~IOCON_FUNC_BIT_MASK_VAL;	
    LPC_IOCON->PIO1_7 |= IOCON_PIO1_7_FUNC_TXD;                 /* UART TXD */

    /* 当I/O管脚被配置为外部中断时，建立NVIC。*/
    NVIC_DisableIRQ(EINT0_IRQn);
    NVIC_DisableIRQ(EINT1_IRQn);
    NVIC_DisableIRQ(EINT2_IRQn);
    NVIC_DisableIRQ(EINT3_IRQn);

    return;
}

/*
 * @function name: gpio_direction_value_set();
 * @brief: set gpio direction value;
 * @active: 
 *        dir_val -- 0: input;
 *                   1: output;
 * @param: port number, bit position, dir_val;
 * @return: no
 */
void gpio_direction_value_set(uint32_t port_num, uint32_t bit_posi, uint32_t dir_val)
{
    switch (port_num)
    {
        case PORT0:
            if (!(LPC_GPIO0->DIR & (0x1 << bit_posi)) && (dir_val == GPIO_DIRECTION_STATUS_OUTPUT))
                LPC_GPIO0->DIR |= (0x1 << bit_posi);
            else if ((LPC_GPIO0->DIR & (0x1 << bit_posi)) && (dir_val == GPIO_DIRECTION_STATUS_INPUT))
                LPC_GPIO0->DIR &= ~(0x1 << bit_posi);
            break;

        case PORT1:
            if (!(LPC_GPIO1->DIR & (0x1 << bit_posi)) && (dir_val == GPIO_DIRECTION_STATUS_OUTPUT))
                LPC_GPIO1->DIR |= (0x1 << bit_posi);
            else if ((LPC_GPIO1->DIR & (0x1 << bit_posi)) && (dir_val == GPIO_DIRECTION_STATUS_INPUT))
                LPC_GPIO1->DIR &= ~(0x1 << bit_posi);
            break;

        case PORT2:
            if (!(LPC_GPIO2->DIR & (0x1 << bit_posi)) && (dir_val == GPIO_DIRECTION_STATUS_OUTPUT))
                LPC_GPIO2->DIR |= (0x1 << bit_posi);
            else if ((LPC_GPIO2->DIR & (0x1 << bit_posi)) && (dir_val == GPIO_DIRECTION_STATUS_INPUT))
                LPC_GPIO2->DIR &= ~(0x1 << bit_posi);
            break;

        case PORT3:
            if (!(LPC_GPIO3->DIR & (0x1 << bit_posi)) && (dir_val == GPIO_DIRECTION_STATUS_OUTPUT))
                LPC_GPIO3->DIR |= (0x1 << bit_posi);
            else if ((LPC_GPIO3->DIR & (0x1 << bit_posi)) && (dir_val == GPIO_DIRECTION_STATUS_INPUT))
                LPC_GPIO3->DIR &= ~(0x1 << bit_posi);
            break;

        default:
            break;
    }
}

/*
 * @function name: gpio_data_value_set();
 * @brief: set gpio bit data value;
 * @active: 
 *        bit_val -- 0: low level;
 *                   1: high;
 * @param: port number, bit position, bit_val;
 * @return: no
 */
void gpio_data_value_set(uint32_t port_num, uint32_t bit_posi, uint32_t bit_val)
{
    switch (port_num)
    {
        case PORT0:
            if (!(LPC_GPIO0->DATA & (0x1 << bit_posi)) && (bit_val == GPIO_DATA_STATUS_HIGH))
                LPC_GPIO0->DATA |= (0x1 << bit_posi);
            else if ((LPC_GPIO0->DATA & (0x1 << bit_posi)) && (bit_val == GPIO_DATA_STATUS_LOW))
                LPC_GPIO0->DATA &= ~(0x1 << bit_posi);
            break;

        case PORT1:
            if (!(LPC_GPIO1->DATA & (0x1 << bit_posi)) && (bit_val == GPIO_DATA_STATUS_HIGH))
                LPC_GPIO1->DATA |= (0x1 << bit_posi);
            else if ((LPC_GPIO1->DATA & (0x1 << bit_posi)) && (bit_val == GPIO_DATA_STATUS_LOW))
                LPC_GPIO1->DATA &= ~(0x1 << bit_posi);
            break;

        case PORT2:
            if (!(LPC_GPIO2->DATA & (0x1 << bit_posi)) && (bit_val == GPIO_DATA_STATUS_HIGH))
                LPC_GPIO2->DATA |= (0x1 << bit_posi);
            else if ((LPC_GPIO2->DATA & (0x1 << bit_posi)) && (bit_val == GPIO_DATA_STATUS_LOW))
                LPC_GPIO2->DATA &= ~(0x1 << bit_posi);
            break;

        case PORT3:
            if (!(LPC_GPIO3->DATA & (0x1 << bit_posi)) && (bit_val == GPIO_DATA_STATUS_HIGH))
                LPC_GPIO3->DATA |= (0x1 << bit_posi);
            else if ((LPC_GPIO3->DATA & (0x1 << bit_posi)) && (bit_val == GPIO_DATA_STATUS_LOW))
                LPC_GPIO3->DATA &= ~(0x1 << bit_posi);
            break;

        default:
            break;
    }
}

/*
 * @function name: gpio_data_value_turn();
 * @brief: turn gpio bit data value status;
 * @param: port number, bit position;
 * @return: no
 */
void gpio_data_value_turn(uint32_t port_num, uint32_t bit_posi)
{
    switch (port_num)
    {
        case PORT0:
            if (!(LPC_GPIO0->DATA & (0x1 << bit_posi)))
                LPC_GPIO0->DATA |= (0x1 << bit_posi);
            else if ((LPC_GPIO0->DATA & (0x1 << bit_posi)))
                LPC_GPIO0->DATA &= ~(0x1 << bit_posi);
            break;

        case PORT1:
            if (!(LPC_GPIO1->DATA & (0x1 << bit_posi)))
                LPC_GPIO1->DATA |= (0x1 << bit_posi);
            else if ((LPC_GPIO1->DATA & (0x1 << bit_posi)))
                LPC_GPIO1->DATA &= ~(0x1 << bit_posi);
            break;

        case PORT2:
            if (!(LPC_GPIO2->DATA & (0x1 << bit_posi)))
                LPC_GPIO2->DATA |= (0x1 << bit_posi);
            else if ((LPC_GPIO2->DATA & (0x1 << bit_posi)))
                LPC_GPIO2->DATA &= ~(0x1 << bit_posi);
            break;

        case PORT3:
            if (!(LPC_GPIO3->DATA & (0x1 << bit_posi)))
                LPC_GPIO3->DATA |= (0x1 << bit_posi);
            else if ((LPC_GPIO3->DATA & (0x1 << bit_posi)))
                LPC_GPIO3->DATA &= ~(0x1 << bit_posi);
            break;

        default:
            break;
    }

    return;
}

/*
 * @function name: gpio_data_value_get();
 * @brief: get gpio bit data value;
 * @param: port number, bit position;
 * @return: gpio_data
 */
uint8_t gpio_data_value_get(uint32_t port_num, uint32_t bit_posi)
{
    uint8_t gpio_data = GPIO_DATA_STATUS_LOW;
    
    switch (port_num)
    {
        case PORT0:
            if ((LPC_GPIO0->DATA & (0x1 << bit_posi)))
                gpio_data = GPIO_DATA_STATUS_HIGH;
            break;

        case PORT1:
            if ((LPC_GPIO1->DATA & (0x1 << bit_posi)))
                gpio_data = GPIO_DATA_STATUS_HIGH;
            break;

        case PORT2:
            if ((LPC_GPIO2->DATA & (0x1 << bit_posi)))
                gpio_data = GPIO_DATA_STATUS_HIGH;
            break;

        case PORT3:
            if ((LPC_GPIO3->DATA & (0x1 << bit_posi)))
                gpio_data = GPIO_DATA_STATUS_HIGH;
            break;

        default:
            break;
    }

    return(gpio_data);
}

/*
 * @function name: gpio_interrupt_set();
 * @brief: set gpio interrupt;
 * @active: 
 *        sense -- 0: Interrupt on pin PIOn_x is configured as edge sensitive;
 *                 1: Interrupt on pin PIOn_x is configured as level sensitive;
 *        single -- 0: Interrupt on pin PIOn_x is controlled through register GPIOnIEV-event;
 *                  1: Both edges on pin PIOn_x trigger an interrupt;
 *        event -- 0: falling edges or LOW level on pin PIOn_x trigger an interrupt;
 *                 1: rising edges or HIGH level on pin PIOn_x trigger an interrupt;
 * @param: port number, bit position, sense, signal, event;
 * @return: no
 */
void gpio_interrupt_set(uint32_t port_num, uint32_t bit_posi, uint32_t sense, uint32_t signal, uint32_t event)
{
    switch (port_num)
    {
        case PORT0:
            /* Set the gpio interrupt sense status */
            if (sense == INTERRUPT_AS_EDGE_SENSITIVE)
            {
                LPC_GPIO0->IS &= ~(0x1 << bit_posi);
                /* Set the gpio interrupt both edges sense status */
                if (signal == INTERRUPT_SIGNAL_AS_LEVEL_OR_SINGLE_EDGE)
                    LPC_GPIO0->IBE &= ~(0x1 << bit_posi);
                else if (signal == INTERRUPT_SIGNAL_AS_BOTH_EDGES)
                    LPC_GPIO0->IBE |= (0x1 << bit_posi);
            }
            else if (sense == INTERRUPT_AS_LEVEL_SENSITIVE)
                LPC_GPIO0->IS |= (0x1 << bit_posi);
            /* Set the gpio interrupt event status */
            if (event == INTERRUPT_EVENT_FALLEDGES_OR_LOWLEVEL)
                LPC_GPIO0->IEV &= ~(0x1 << bit_posi);
            else if (event == INTERRUPT_EVENT_RISEEDGES_OR_HIGHLEVEL)
                LPC_GPIO0->IEV |= (0x1 << bit_posi);
            break;

        case PORT1:
            /* Set the gpio interrupt sense status */
            if (sense == INTERRUPT_AS_EDGE_SENSITIVE)
            {
                LPC_GPIO1->IS &= ~(0x1 << bit_posi);
                /* Set the gpio interrupt both edges sense status */
                if (signal == INTERRUPT_SIGNAL_AS_LEVEL_OR_SINGLE_EDGE)
                    LPC_GPIO1->IBE &= ~(0x1 << bit_posi);
                else if (signal == INTERRUPT_SIGNAL_AS_BOTH_EDGES)
                    LPC_GPIO1->IBE |= (0x1 << bit_posi);
            }
            else if (sense == INTERRUPT_AS_LEVEL_SENSITIVE)
                LPC_GPIO1->IS |= (0x1 << bit_posi);
            /* Set the gpio interrupt event status */
            if (event == INTERRUPT_EVENT_FALLEDGES_OR_LOWLEVEL)
                LPC_GPIO1->IEV &= ~(0x1 << bit_posi);
            else if (event == INTERRUPT_EVENT_RISEEDGES_OR_HIGHLEVEL)
                LPC_GPIO1->IEV |= (0x1 << bit_posi);  
            break;

        case PORT2:
            /* Set the gpio interrupt sense status */
            if (sense == INTERRUPT_AS_EDGE_SENSITIVE)
            {
                LPC_GPIO2->IS &= ~(0x1 << bit_posi);
                /* Set the gpio interrupt both edges sense status */
                if (signal == INTERRUPT_SIGNAL_AS_LEVEL_OR_SINGLE_EDGE)
                    LPC_GPIO2->IBE &= ~(0x1 << bit_posi);
                else if (signal == INTERRUPT_SIGNAL_AS_BOTH_EDGES)
                    LPC_GPIO2->IBE |= (0x1 << bit_posi);
            }
            else if (sense == INTERRUPT_AS_LEVEL_SENSITIVE)
                LPC_GPIO2->IS |= (0x1 << bit_posi);
            /* Set the gpio interrupt event status */
            if (event == INTERRUPT_EVENT_FALLEDGES_OR_LOWLEVEL)
                LPC_GPIO2->IEV &= ~(0x1 << bit_posi);
            else if (event == INTERRUPT_EVENT_RISEEDGES_OR_HIGHLEVEL)
                LPC_GPIO2->IEV |= (0x1 << bit_posi);  
            break;

        case PORT3:
            /* Set the gpio interrupt sense status */
            if (sense == INTERRUPT_AS_EDGE_SENSITIVE)
            {
                LPC_GPIO3->IS &= ~(0x1 << bit_posi);
                /* Set the gpio interrupt both edges sense status */
                if (signal == INTERRUPT_SIGNAL_AS_LEVEL_OR_SINGLE_EDGE)
                    LPC_GPIO3->IBE &= ~(0x1 << bit_posi);
                else if (signal == INTERRUPT_SIGNAL_AS_BOTH_EDGES)
                    LPC_GPIO3->IBE |= (0x1 << bit_posi);
            }
            else if (sense == INTERRUPT_AS_LEVEL_SENSITIVE)
                LPC_GPIO3->IS |= (0x1 << bit_posi);
            /* Set the gpio interrupt event status */
            if (event == INTERRUPT_EVENT_FALLEDGES_OR_LOWLEVEL)
                LPC_GPIO3->IEV &= ~(0x1 << bit_posi);
            else if (event == INTERRUPT_EVENT_RISEEDGES_OR_HIGHLEVEL)
                LPC_GPIO3->IEV |= (0x1 << bit_posi);  
            break;

        default:
            break;
    }

    return;
}

/*
 * @function name: gpio_interrupt_enable();
 * @brief: enable gpio interrupt;
 * @active: write 1: Interrupt on pin PIOn_x is not masked;
 * @param: port number, bit position
 * @return: no
 */
void gpio_interrupt_enable(uint32_t port_num, uint32_t bit_posi)
{
    switch (port_num)
    {
        case PORT0:
            LPC_GPIO0->IE |= (0x1 << bit_posi);
            break;

        case PORT1:
            LPC_GPIO1->IE |= (0x1 << bit_posi);
            break;

        case PORT2:
            LPC_GPIO2->IE |= (0x1 << bit_posi);
            break;

        case PORT3:
            LPC_GPIO3->IE |= (0x1 << bit_posi);
            break;

        default:
            break;
    }

    return;
}

/*
 * @function name: gpio_interrupt_disable()
 * @brief: disable gpio interrupt
 * @active: write 0: Interrupt on pin PIOn_x is masked.
 * @param: port number, bit position
 * @return: no
 */
void gpio_interrupt_disable(uint32_t port_num, uint32_t bit_posi)
{
    switch (port_num)
    {
        case PORT0:
            LPC_GPIO0->IE &= ~(0x1 << bit_posi);
            break;

        case PORT1:
            LPC_GPIO1->IE &= ~(0x1 << bit_posi);
            break;

        case PORT2:
            LPC_GPIO2->IE &= ~(0x1 << bit_posi);    
            break;

        case PORT3:
            LPC_GPIO3->IE &= ~(0x1 << bit_posi);    
            break;

        default:
            break;
    }

    return;
}

/*
 * @function name:	gpio_interrupt_satus_get();
 * @brief: return the gpio interrupt status;
 * @active: read 0: No interrupt on pin PIOn_x;
 *          read 1: Interrupt requirements met on PIOn_x;
 * @param: port number, bit position;
 * @return: interrupt_status.
 */
uint8_t gpio_interrupt_satus_get(uint32_t port_num, uint32_t bit_posi)
{
    uint8_t interrupt_status = RAW_INTERRUPT_STATUS_NO_INTERRUPT;

    switch (port_num)
    {
        case PORT0:
            if (LPC_GPIO0->MIS & (0x1 << bit_posi))
                interrupt_status = RAW_INTERRUPT_STATUS_INTERRUPT;
            break;

        case PORT1:
            if (LPC_GPIO1->MIS & (0x1 << bit_posi))
                interrupt_status = RAW_INTERRUPT_STATUS_INTERRUPT;
            break;

        case PORT2:
            if (LPC_GPIO2->MIS & (0x1 << bit_posi))
                interrupt_status = RAW_INTERRUPT_STATUS_INTERRUPT;    
            break;

        case PORT3:
            if (LPC_GPIO3->MIS & (0x1 << bit_posi))
                interrupt_status = RAW_INTERRUPT_STATUS_INTERRUPT;    
            break;

        default:
            break;
    }

    return(interrupt_status);
}

/*
 * @function name:	gpio_edge_interrupt_clear();
 * @brief: Clear edge detection for port bits that are identified as edge-sensitive in the
 *         interrupt sense register, has no effect on port bits identified as level-sensitive;
 * @active: write 0: No effect;
 *          write 1: clears edge detection logic for PIOn_x;
 * @param: port number, bit position;
 * @return: no
 */
void gpio_edge_interrupt_clear(uint32_t port_num, uint32_t bit_posi)
{
    switch (port_num)
    {
        case PORT0:
            LPC_GPIO0->IC |= (0x1 << bit_posi);
            break;

        case PORT1:
            LPC_GPIO1->IC |= (0x1 << bit_posi);
            break;

        case PORT2:
            LPC_GPIO2->IC |= (0x1 << bit_posi); 
            break;

        case PORT3:
            LPC_GPIO3->IC |= (0x1 << bit_posi);
            break;

        default:
            break;
    }

    return;
}


