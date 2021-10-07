/*
 * uart_drv.c - uart_drv.c config and achieve;
 *
 * Copyright (c) 2014 Forlan.yung(YANGHUALIANG)
 *
 */

#define GLOBALS_UART
#include "include.h"


/****************************************************************************
      变量定义区
****************************************************************************/


/****************************************************************************
      函数定义区
****************************************************************************/
void uart_init(void)
{
    uint32_t fre_div;
    uint32_t reg_val;

    NVIC_DisableIRQ(UART_IRQn);
    
    /* Enable UART clock */
    AHB_clock_enable(SYSAHBCLKCTRL_UART_BIT_OFFSET_VAL);
    /* Set the divider value to 1 */
    LPC_SYSCON->UARTCLKDIV = UARTCLKDIV_VAL_SET_001;
    /* 8 data word length, no parity, 1bit stop */
    LPC_UART->LCR = U0LCR_DLAB_ACCESS_DIVI_LAT_ENABLE
                  | U0LCR_PE_PARITY_DISABLE
                  | U0LCR_SBS_STOP_BIT_1BIT
                  | U0LCR_WLS_WORD_LENGTH_8BIT;

    /* Set the baudrate to 115200 */
    reg_val = LPC_SYSCON->UARTCLKDIV;
    fre_div = ((system_clock_frequency / reg_val) / 16) / UART_BAUDRATE_115200;
    LPC_UART->DLM = fre_div / 256;
    LPC_UART->DLL = fre_div % 256;
    /* Disable access to divisor latches. */
    LPC_UART->LCR &= ~(0x01 << U0LCR_DLAB_BIT_OFFSET_VAL);
    /* Enable FIFO, reset RX and TX */
    LPC_UART->FCR = U0FCR_RX_TX_FIFOS_ENABLE
                  | U0FCR_RXFIFO_RESET_YES
                  | U0FCR_TXFIFO_RESET_YES;

    /* Read and clear the line status */
    reg_val = LPC_UART->LSR;
    /* Clear the TX buffer */
    while (LPC_UART->LSR & (U0LSR_THRE_U0THR_EMPTY | U0LSR_TEMT_U0THR_U0TSR_EMPTY)
          != (U0LSR_THRE_U0THR_EMPTY | U0LSR_TEMT_U0THR_U0TSR_EMPTY));
    /* Cear the RX buffer */
    while (LPC_UART->LSR & U0LSR_RDR_U0RBR_VALID_DATA)
    {
        reg_val = LPC_UART->RBR;
    }

    NVIC_EnableIRQ(UART_IRQn);

    LPC_UART->IER = U0IER_RBRIE_RDA_INTERRUPT_ENABLE
                  | U0IER_THREIE_THRE_INTERRUPT_ENABLE
                  | U0IER_RXLIE_RX_LINE_INTERRUPT_ENABLE;

    LPC_UART->IER = U0IER_RBRIE_RDA_INTERRUPT_ENABLE
                  | U0IER_RXLIE_RX_LINE_INTERRUPT_ENABLE;

    return;
}

void uart_data_init(void)
{
    mpu_data.rx_index = 0;
    mpu_data.rx_handle = 0;
    mpu_data.rx_frame_index = 0;
    mpu_data.rx_frame_handle = 0;

    mpu_data.tx_index = 0;
    mpu_data.tx_handle = 0;
    mpu_data.mpu_rx_can_frame_index = 0;
    mpu_data.mpu_rx_can_frame_handle = 0;

    mpu_data.txing = 0;
}

void uart_enable(void)
{
    /* Enable Tx, Rx, as well as enable interrupt */
    LPC_UART->IER = U0IER_RBRIE_RDA_INTERRUPT_ENABLE
                  | U0IER_THREIE_THRE_INTERRUPT_ENABLE
                  | U0IER_RXLIE_RX_LINE_INTERRUPT_ENABLE;
}

void uart_disable(void)
{
    /* disable Tx, Rx, as well as diable interrupt */
    LPC_UART->IER &= ~(U0IER_RBRIE_RDA_INTERRUPT_ENABLE
                     | U0IER_THREIE_THRE_INTERRUPT_ENABLE
                     | U0IER_RXLIE_RX_LINE_INTERRUPT_ENABLE);
}

bool uart_rx_frame_buff_full(uint8_t uart_index)
{
    uint8_t index;
    uint8_t handle;
    uint8_t rx_frame_max;

    switch (uart_index)
    {
        case INDEX_UART:
            index  = mpu_data.rx_frame_index;
            handle = mpu_data.rx_frame_handle;
            rx_frame_max = UART_RX_FRAME_MAX;
            break;

        default:
            break;
    }

    if (index > handle)
    {
        if ((index - handle) == (rx_frame_max - 1))
        {
            return true;
        }
    }
    else
    {
        index += rx_frame_max;
        if ((index - handle) == (rx_frame_max - 1))
        {
            return true;
        }
    }

    return false;
}

bool mpu_rx_can_frame_buff_full(void)
{
    uint8_t index;
    uint8_t handle;
    uint8_t rx_frame_max;

    index  = mpu_data.mpu_rx_can_frame_index;
    handle = mpu_data.mpu_rx_can_frame_handle;
    rx_frame_max = MPU_RX_CAN_FRAME_MAX;

    if (index > handle)
    {
        if ((index - handle) == (rx_frame_max - 1))
        {
            return true;
        }
    }
    else
    {
        index += rx_frame_max;
        if ((index - handle) == (rx_frame_max - 1))
        {
            return true;
        }
    }

    return false;
}


uint8_t uart_tx_buffer_space(void)
{
    uint8_t index;
    uint8_t handle;
    uint8_t space;

    __disable_irq();
    index = mpu_data.tx_index;
    handle = mpu_data.tx_handle;
    __enable_irq();

    if (index == handle)
    {
        space = UART_TX_BUFF_MAX - 1;
    }
    else
    {
        if (index > handle)
            space = (uint8_t)(UART_TX_BUFF_MAX - index + handle);
        else
            space = (uint8_t)(handle - index);
    }

    return(uint8_t)(space - 2);  // 保留一点余地
}

void isr_uart(void)
{
    uint8_t iir_value;
    uint8_t lsr_value;
    uint8_t n_data;
	//uint8_t val_reg;
	uint16_t temp;

    /* Read the interrupt identification register value */
    iir_value = LPC_UART->IIR;
    /* Get the interrupt identification value */
    iir_value >>= U0IIR_INTID_BIT_OFFSET_VAL;
    iir_value &= UART_INTERRUPT_ID_MASK;

    switch (iir_value)
    {
        case U0IIR_INTID_RECEIVE_LINE_STATUS:
            lsr_value = LPC_UART->LSR;
            n_data = LPC_UART->RBR;
            if (lsr_value & UART_INTERRUPT_ERR_MASK)
            {
                uart_init();
                uart_enable();
                return;
            }
            if (lsr_value & U0LSR_RDR_U0RBR_VALID_DATA)
            {
                /* Save the valid data */
				temp = mpu_data.rx_index;
				mpu_data.rx_buffer[temp] = n_data;         /* 一行里最好不要有两个volatile变量 */

				temp = mpu_data.rx_index + 1;
				mpu_data.rx_index = (uint8_t)(temp % UART_RX_BUFF_MAX);
            }
            break;

        case U0IIR_INTID_RECEIVE_DATA_AVALIABLE:
            /* Save the valid data */
            n_data = LPC_UART->RBR;
			temp = mpu_data.rx_index;
			mpu_data.rx_buffer[temp] = n_data;             /* 一行里最好不要有两个volatile变量 */

			temp = mpu_data.rx_index + 1;
			mpu_data.rx_index = (uint8_t)(temp % UART_RX_BUFF_MAX);
            break;

        case U0IIR_INTID_CHAR_TIME_OUR_IND:
            break;

        case U0IIR_INTID_THRE_INTERRUPT:
            lsr_value = LPC_UART->LSR;
			if (mpu_data.tx_handle == mpu_data.tx_index)
			{
				mpu_data.txing = 0;
			}
			else
			{
				n_data = mpu_data.tx_buffer[mpu_data.tx_handle];
				LPC_UART->THR = n_data;

				temp = mpu_data.tx_handle + 1;
				mpu_data.tx_handle=(uint8_t)(temp % UART_TX_BUFF_MAX);
			}
            break;

        default:
            break;
    }

    return;
}


