/*
 * uart_drv.h - uart_drv.h config header file;
 *
 * Copyright (c) 2014 Forlan.yung(YANGHUALIANG)
 *
 */
#ifndef _UART_DRV_H_
#define _UART_DRV_H_

#ifndef GLOBALS_UART
#define uart_extern extern
#else
#define uart_extern
#endif


/****************************************************************************
      常量声明区
****************************************************************************/
#define U0LCR_WLS_BIT_OFFSET_VAL                0               /* 1:0 WLS -- word length select */
#define UOLCR_SBS_BIT_OFFSET_VAL                2               /* 2 SBS -- stop bit select */
#define U0LCR_PE_BIT_OFFSET_VAL                 3               /* 3 PE -- parity enable */
#define U0LCR_PS_BIT_OFFSET_VAL                 4               /* 5:4 PS -- parity select */
#define U0LCR_BC_BIT_OFFSET_VAL                 6               /* 6 BC -- break control */
#define U0LCR_DLAB_BIT_OFFSET_VAL               7               /* 7 DLAB -- divisor latch access bit */

#define U0LCR_WLS_WORD_LENGTH_5BIT              0x00
#define U0LCR_WLS_WORD_LENGTH_6BIT              0b01
#define U0LCR_WLS_WORD_LENGTH_7BIT              0x02
#define U0LCR_WLS_WORD_LENGTH_8BIT              0x03
#define U0LCR_SBS_STOP_BIT_1BIT                 0x00
#define U0LCR_SBS_STOP_BIT_2BIT                 0x04
#define U0LCR_PE_PARITY_DISABLE                 0x00
#define U0LCR_PE_PARITY_ENABLE                  0x08
#define U0LCR_PS_ODD_PARITY                     0x00
#define U0LCR_PS_EVEN_PARITY                    0x10
#define U0LCR_PS_FORCED_1STICK_PARITY           0x20
#define U0LCR_PS_FORCED_0STICK_PARITY           0x30
#define U0LCR_BC_BREAK_TRAN_DISABLE             0x00
#define U0LCR_BC_BREAK_TRAN_ENABLE              0x40
#define U0LCR_DLAB_ACCESS_DIVI_LAT_DISABLE      0x00
#define U0LCR_DLAB_ACCESS_DIVI_LAT_ENABLE       0x80

#define U0FCR_FIFOEN_BIT_OFFSET_VAL             0               /* 0 FIFOEn -- FIFO Enable */
#define U0FCR_RXFIFORES_BIT_OFFSET_VAL          1               /* 1 RXFIFO -- RX FIFO Reset */
#define U0FCR_TXFIFORES_BIT_OFFSET_VAL          2               /* 2 TXFIFO -- TX FIFO Reset */
#define U0FCR_RXTL_BIT_OFFSET_VAL               6               /* 7:6 RXTL -- RX Trigger Level */

#define U0FCR_FIFOS_DISABLE                     0x00
#define U0FCR_RX_TX_FIFOS_ENABLE                0x01
#define U0FCR_RXFIFO_RESET_NO                   0x00
#define U0FCR_RXFIFO_RESET_YES                  0x02
#define U0FCR_TXFIFO_RESET_NO                   0x00
#define U0FCR_TXFIFO_RESET_YES                  0x04
#define U0FCR_RXTL_1CHAR_TRIGGER_LEVL           0x00
#define U0FCR_RXTL_4CHAR_TRIGGER_LEVL           0x40
#define U0FCR_RXTL_8CHAR_TRIGGER_LEVL           0x80
#define U0FCR_RXTL_14CHAR_TRIGGER_LEVL          0xC0

#define U0LSR_RDR_BIT_OFFSET_VAL                0               /* 0 RDR -- Receiver Data Ready */
#define U0LSR_OE_BIT_OFFSET_VAL                 1               /* 1 OE -- Overrun Error */
#define U0LSR_PE_BIT_OFFSET_VAL                 2               /* 2 PE -- Parity Error */
#define U0LSR_FE_BIT_OFFSET_VAL                 3               /* 3 FE -- Framing Error */
#define U0LSR_BI_BIT_OFFSET_VAL                 4               /* 4 BI -- Break Interrupt */
#define U0LSR_THRE_BIT_OFFSET_VAL               5               /* 5 THRE -- Transmitter Holding Register Empty */
#define U0LSR_TEMT_BIT_OFFSET_VAL               6               /* 6 TEMT -- Transmitter Empty */
#define U0LSR_RXFE_BIT_OFFSET_VAL               7               /* 7 RXFE -- Error in RX FIFO */

#define U0LSR_RDR_U0RBR_EMPTY                   0x00
#define U0LSR_RDR_U0RBR_VALID_DATA              0x01
#define U0LSR_OE_OVERRUN_ERR_INACTIVE           0x00
#define U0LSR_OE_OVERRUN_ERR_ACTIVE             0x02
#define U0LSR_PE_PARITY_ERR_INACTIVE            0x00
#define U0LSR_PE_PARITY_ERR_ACTIVE              0x04
#define U0LSR_FE_FRAMING_ERR_INACTIVE           0x00
#define U0LSR_FE_FRAMING_ERR_ACTIVE             0x08
#define U0LSR_BI_BREAK_INTERRUPT_INACTIVE       0x00
#define U0LSR_BI_BREAK_INTERRUPT_ACTIVE         0x10
#define U0LSR_THRE_U0THR_VALID_DATA             0x00
#define U0LSR_THRE_U0THR_EMPTY                  0x20
#define U0LSR_TEMT_U0THR_U0TSR_VALID_DATA       0x00
#define U0LSR_TEMT_U0THR_U0TSR_EMPTY            0x40
#define U0LSR_RXFE_UART_RX_ERR_NO               0x00
#define U0LSR_RXFE_UART_RX_ERR_YES              0x80

#define U0IER_RBRIE_BIT_OFFSET_VAL              0
#define U0IER_THREIE_BIT_OFFSET_VAL             1
#define U0IER_RXLIE_BIT_OFFSET_VAL              2
#define U0IER_ABEOINTEN_BIT_OFFSET_VAL          8
#define U0IER_ABTOINTEN_BIT_OFFSET_VAL          9

#define U0IER_RBRIE_RDA_INTERRUPT_DISABLE       0x00
#define U0IER_RBRIE_RDA_INTERRUPT_ENABLE        0x01
#define U0IER_THREIE_THRE_INTERRUPT_DISABLE     0x00
#define U0IER_THREIE_THRE_INTERRUPT_ENABLE      0x02
#define U0IER_RXLIE_RX_LINE_INTERRUPT_DISABLE   0x00
#define U0IER_RXLIE_RX_LINE_INTERRUPT_ENABLE    0x04

#define U0IIR_INTSTATUS_BIT_OFFSET_VAL          0               /* 0 IntStaus -- interrupt status */
#define U0IIR_INTID_BIT_OFFSET_VAL              1               /* 3:1 IntId -- Interrupt identification */
#define U0IIR_FIFOENABLE_BIT_OFFSET_VAL         6               /* 7:6 FIFOEnable -- These bits are equivalent to U0FCR[0] */
#define U0IIR_ABEOINT_BIT_OFFSET_VAL            8               /* 8 ABEOInt -- End of auto-baud interrupt */
#define U0IIR_ABTOINT_BIT_OFFSET_VAL            9               /* 9 ABTOInt -- Auto-baud time-out interrupt */

#define U0IIR_INTSTATUS_INT_IS_PENDING			0x00
#define U0IIR_INTSTATUS_NO_INT_PENDING			0x01
#define U0IIR_INTID_MODEM_INTERRUPT				0x00
#define U0IIR_INTID_THRE_INTERRUPT              0x01
#define U0IIR_INTID_RECEIVE_DATA_AVALIABLE	    0x02
#define U0IIR_INTID_RECEIVE_LINE_STATUS			0x03
#define U0IIR_INTID_CHAR_TIME_OUR_IND           0x06

#define UART_BAUDRATE_9600                      9600
#define UART_BAUDRATE_19200                     19200
#define UART_BAUDRATE_115200                    115200
#define UART_INTERRUPT_ID_MASK                  0x07
#define UART_INTERRUPT_ERR_MASK                 (U0LSR_OE_OVERRUN_ERR_ACTIVE | \
                                                 U0LSR_PE_PARITY_ERR_ACTIVE |  \
                                                 U0LSR_FE_FRAMING_ERR_ACTIVE | \
                                                 U0LSR_RXFE_UART_RX_ERR_YES |  \
                                                 U0LSR_BI_BREAK_INTERRUPT_ACTIVE)

#define UART_RX_FRAME_MAX                       2
#define UART_RX_FRAME_LEN_MAX                   110
#define UART_TX_FRAME_LEN_MAX                   110

#define UART_RX_BUFF_MAX                        (UART_RX_FRAME_LEN_MAX + 10)
#define UART_TX_BUFF_MAX                        (UART_TX_FRAME_LEN_MAX + 10)

#define INDEX_UART                              0

#define MPU_RX_CAN_FRAME_MAX                    10
#define MPU_RX_CAN_FRAME_LEN_MAX                20



/****************************************************************************
      变量声明区
****************************************************************************/
typedef struct
{
    volatile uint8_t rx_buffer[UART_RX_BUFF_MAX];						        // 接收缓冲
    volatile uint8_t rx_index;                                       	        // 当前的接收数据缓冲索引
    uint8_t rx_handle;                                               	        // 当前正在处理的接收缓冲索引
    uint8_t rx_frame_buffer[UART_RX_FRAME_MAX][UART_RX_FRAME_LEN_MAX];          // 接收帧缓冲
    uint8_t rx_frame_index;                                           	        // 当前的正在接收的帧缓冲索引
    uint8_t rx_frame_handle;                                          	        // 当前正在处理的帧索引

    volatile bool txing;                                           		        // 发送正在进行中
    uint8_t tx_index;                                                	        // 当前的发送数据缓冲索引
    volatile uint8_t tx_handle;                                      	        // 当前正在处理的发送数据缓冲索引
    uint8_t tx_buffer[UART_TX_BUFF_MAX];                             	        // 发送缓冲
    uint8_t mpu_rx_can_frame_buffer[MPU_RX_CAN_FRAME_MAX][MPU_RX_CAN_FRAME_LEN_MAX];  // MPU接收CAN帧缓冲
    uint8_t mpu_rx_can_frame_index;                                           	// 当前的正在接收的CAN帧缓冲索引
    uint8_t mpu_rx_can_frame_handle;                                          	// 当前正在处理的CAN帧索引

}UART_STRUCT;

uart_extern UART_STRUCT mpu_data;


/****************************************************************************
      函数申明区
****************************************************************************/
extern void uart_init(void);
extern void uart_enable(void);
extern void uart_disable(void);
extern void uart_data_init(void);
extern void isr_uart(void);
extern uint8_t uart_txbuffer_space(void);
extern uint8_t uart_tx_buffer_space(void);
extern bool uart_rx_frame_buff_full(uint8_t uart_index);
extern bool mpu_rx_can_frame_buff_full(void);


#endif
 
