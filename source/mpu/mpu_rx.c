/*
 * mpu_rx.c - mpu_rx.c config and achieve;
 *
 * Copyright (c) 2014 Forlan.yung(YANGHUALIANG)
 *
 */

#include "include.h"

/****************************************************************************
      常量定义区
****************************************************************************/
#define HEAD_MAX    5


/****************************************************************************
      变量定义区
****************************************************************************/
static uint8_t mpu_rx_timer = 0;           /* 对未接收完整的数据帧进行计数 */
extern CANCIRBUF GtCanTxCirBuf;


/****************************************************************************
      函数声明区
****************************************************************************/
static void cmd_null(void);
static void transfer_data_to_can_tx_buff(void);
static void mpu_checksum(volatile uint8_t *p_buff, uint8_t frame_len, BOOL b_buff_offset);


/****************************************************************************
      函数定义区
****************************************************************************/
void mpu_rx_buffer_analyse(void)
{
    volatile uint8_t *p_hdl;
    volatile uint8_t *p_hdl_max;
    volatile uint8_t *p_data;
    BOOL  b_buff_offset = 0;
    uint8_t data_len = 0;
    uint8_t cyc_len = 0;
    uint8_t frame_len = 0;
    uint8_t i = 0;
    uint8_t data = 0;
    uint8_t head[HEAD_MAX];
    uint8_t cmd_len[HEAD_MAX];
    uint8_t head_index = 0;
    uint8_t rx_index;
    uint8_t rx_handle;
    uint16_t temp;

    /* get the rx_index and rx_handle states */
    __disable_irq();
    rx_index = mpu_data.rx_index;
    rx_handle = mpu_data.rx_handle;
    __enable_irq();

    /* 没有数据要处理 */
    if (rx_index == rx_handle)
    {
        return;
    }
    
    /* 计算未处理的数据长度 */
    if (rx_index > rx_handle)
    {
        data_len = (uint8_t)(rx_index - rx_handle);
    }
    else
    {
        data_len = (uint8_t)(UART_RX_BUFF_MAX - rx_handle + rx_index);
        b_buff_offset = 1;
    }

    /* 不足一个帧长度不考虑 */
    if (data_len < 5)
        return;

    p_hdl = &mpu_data.rx_buffer[mpu_data.rx_handle];
    p_hdl_max = &mpu_data.rx_buffer[UART_RX_BUFF_MAX - 1] + 1;

    /* 扫描整个buff内的帧头信息，分2种类型是为了减少循环内的越界判断 */
    cyc_len = data_len;
    if (b_buff_offset)
    {
        for (i = 0; i < cyc_len; i++)
        {
            data = *p_hdl++;
            if (p_hdl == p_hdl_max)
                p_hdl = &mpu_data.rx_buffer[0];

            if (data == 0x5A)
            {
                p_data = p_hdl;
                if (*p_data == 0xA5)
                {
                    head[head_index] = i;
                    /* 长度 */
                    p_data++;
                    if (p_data == p_hdl_max)
                        p_data = &mpu_data.rx_buffer[0];
                    cmd_len[head_index++] = *p_data;
                    /* buff满了退出循环 */
                    if (head_index == HEAD_MAX)
                        i = cyc_len;
                }
            }
        }
    }
    else
    {
        for (i = 0; i < cyc_len; i++)
        {
            data = *p_hdl++;

            if (data == 0x5A)
            {
                p_data = p_hdl;
                if (*p_data == 0xA5)
                {
                    head[head_index] = i;
                    /* 长度 */
                    p_data++;
                    cmd_len[head_index++] = *p_data;
                    /* buff满了退出循环 */
                    if (head_index == HEAD_MAX)
                        i = cyc_len;
                }
            }
        }
    }

    /* 没有有效帧 */
    if (head_index == 0)
    {
        mpu_data.rx_handle = rx_index;
        return;
    }

    /* 复位指针 */
    temp = mpu_data.rx_handle + head[0];
    mpu_data.rx_handle = (uint8_t)(temp % UART_RX_BUFF_MAX);

    p_hdl = &mpu_data.rx_buffer[mpu_data.rx_handle];

    /* 一帧长度为命令长度加了 0x5A 、0xA5和LEN 3个字节 */
    frame_len = (uint8_t)(cmd_len[0] + 3);

    if (head_index == 1)
    {
        /* 只有一帧的话，正确的帧长应该小于等于有效数据长 */
        if (frame_len <= data_len)
        {
            mpu_checksum(p_hdl, frame_len, b_buff_offset);
            return;
        }
        else
        {
            /* 也许是数据还未接收完全，等待下一轮再处理 */
            return;
        }
    }

    /* headindex > 1 */
    /* 首先判断所有的数据是否是一帧 */
    if (frame_len == data_len)
    {
        mpu_checksum(p_hdl, frame_len, b_buff_offset);
        return;
    }

    /* 寻找与帧长相符的2帧头间隔 */
    for (i = 1; i < head_index; i++)
    {
        if (frame_len == (head[i] - head[0]))
            break;
    }
    if (i >= head_index)
    {
        /* 数据帧未接收完全，定时处理 */
        if (frame_len > (head[head_index - 1] - head[0]))
        {
            mpu_rx_timer++;
            if (mpu_rx_timer >= 3)
            {
                mpu_rx_timer = 0;
                temp = mpu_data.rx_handle + (uint8_t)(head[1] - head[0]);
                mpu_data.rx_handle = (uint8_t)(temp % UART_RX_BUFF_MAX);
            }
            return;
        }
        /* 帧长错误，则第一帧错误，丢弃 */
        else
        {
            temp = mpu_data.rx_handle + (uint8_t)(head[1] - head[0]);
            mpu_data.rx_handle = (uint8_t)(temp % UART_RX_BUFF_MAX);
        }
        return;
    }
    /* 帧长正确则进行checksum */
    else
    {
        mpu_checksum(p_hdl, frame_len, b_buff_offset);
        return;
    }
}

/* 对1帧数据进行checksum校验 */
static void mpu_checksum(volatile uint8_t *p_buff, uint8_t frame_len, BOOL b_buff_offset)
{
    uint8_t i = 0;
    uint8_t checksum = 0;
    uint8_t cyc_len = 0;
    volatile uint8_t *p_frame;
    volatile uint8_t *p_hdl;
    volatile uint8_t *p_hdl_max;
    uint16_t temp;

    p_hdl_max = &mpu_data.rx_buffer[UART_RX_BUFF_MAX - 1] + 1;

    /* checksum是从LEN位开始计算,指针须移动2　BYTE(帧头)指向LEN */
    p_hdl = p_buff;
    if (b_buff_offset)
    {
        for (i = 0; i < 2; i++)
        {
            p_hdl++;
            if (p_hdl == p_hdl_max)
                p_hdl = &mpu_data.rx_buffer[0];
        }
    }
    else
    {
        p_hdl += 2;
    }

    /* checksum长度为帧长减去2字节的开销 */
    cyc_len = (uint8_t)(frame_len - 2);
    checksum = 0;
    /* 复位数据帧计数器 */
    mpu_rx_timer = 0;

    /* checksum计算 */
    /* buffer越界循环处理 */
    if (b_buff_offset)
    {
        for (i = 0; i < cyc_len; i++)
        {
            checksum += *p_hdl++;
            if (p_hdl == p_hdl_max)
                p_hdl = &mpu_data.rx_buffer[0];
        }
    }
    else
    {
        for (i = 0; i < cyc_len; i++)
        {
            checksum += *p_hdl++;
        }
    }

    /* 正确帧并且帧缓冲还有空间 */
    if ((checksum == 0) && (!uart_rx_frame_buff_full(INDEX_UART)))
    {
        p_frame = &mpu_data.rx_frame_buffer[mpu_data.rx_frame_index][0];
        p_hdl = p_buff;

        /* 取出正确帧数据，放入帧缓冲 */
        cyc_len = frame_len;
        if (b_buff_offset)
        {
            for (i = 0; i < cyc_len; i++)
            {
                *p_frame++ = *p_hdl++;
                if (p_hdl == p_hdl_max)
                    p_hdl = &mpu_data.rx_buffer[0];
            }

        }
        else
        {
            for (i = 0; i < cyc_len; i++)
                *p_frame++ = *p_hdl++;
        }
        
        mpu_data.rx_frame_index++;
        if (mpu_data.rx_frame_index >= UART_RX_FRAME_MAX)
            mpu_data.rx_frame_index = 0;

        /* 调整buffer指针位置 */
        temp = mpu_data.rx_handle + cyc_len;
        mpu_data.rx_handle = (uint8_t)(temp % UART_RX_BUFF_MAX);
        return;
    }
    else
    {
        /* 调整buffer指针位置 */
        temp = mpu_data.rx_handle + frame_len;
        mpu_data.rx_handle = (uint8_t)(temp % UART_RX_BUFF_MAX);

        return;
    }
}

/* 对接收到的帧进行处理 */
void mpu_rx_handle(void)
{
    switch (mpu_rx_id)
    {
        case MCU_MPU_INIT_REQ:
            break;

        case MCU_MPU_VERSION_REQ:
            break;

        case MCU_MPU_TO_CAN_BT_INFO_IND:
            transfer_data_to_can_tx_buff();
            break;
            
        default:
            cmd_null();
            break;
    }

    mpu_data.rx_frame_handle++;
    if (mpu_data.rx_frame_handle == UART_RX_FRAME_MAX)
    {
        mpu_data.rx_frame_handle = 0;
    }

    return;
}

static void transfer_data_to_can_tx_buff(void)
{
    CANFRAME can_frame;

    can_frame.ucTtypeFormat = mpu_rx_prm0;
    can_frame.ucDLC = mpu_rx_prm1;

    /*
     * id是一个32位的值，在通讯中分成4个unsigned char类型来传输;
     * mpu_rx_prm5  mpu_rx_prm4  mpu_rx_prm3  mpu_rx_prm2
     *   (高8位)     (次高8位)    (次低8位)      (低8位)
     */
    can_frame.ulID = (unsigned long)(mpu_rx_prm2
                                  | (mpu_rx_prm3 << 8)
                                  | (mpu_rx_prm4 << 16)
                                  | (mpu_rx_prm5 << 24));

    /* Save the 8 bytes can data */
	strncpy(&can_frame.ucDatBuf[0], &mpu_rx_prm6, CAN_DATA_LENGTH);

    /* 如果can发送buffer还有空间，保存当前数据帧，否则丢弃 */
    if (can_circulation_buffer_write(&GtCanTxCirBuf, &can_frame) == CAN_OK)
    {
        mpu_to_can_cmd(MCU_MPU_TO_CAN_BT_INFO_IND, 0);
    }

    return;
}

static void cmd_null(void)
{
    return;
}


