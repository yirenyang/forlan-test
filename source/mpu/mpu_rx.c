/*
 * mpu_rx.c - mpu_rx.c config and achieve;
 *
 * Copyright (c) 2014 Forlan.yung(YANGHUALIANG)
 *
 */

#include "include.h"

/****************************************************************************
      ����������
****************************************************************************/
#define HEAD_MAX    5


/****************************************************************************
      ����������
****************************************************************************/
static uint8_t mpu_rx_timer = 0;           /* ��δ��������������֡���м��� */
extern CANCIRBUF GtCanTxCirBuf;


/****************************************************************************
      ����������
****************************************************************************/
static void cmd_null(void);
static void transfer_data_to_can_tx_buff(void);
static void mpu_checksum(volatile uint8_t *p_buff, uint8_t frame_len, BOOL b_buff_offset);


/****************************************************************************
      ����������
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

    /* û������Ҫ���� */
    if (rx_index == rx_handle)
    {
        return;
    }
    
    /* ����δ��������ݳ��� */
    if (rx_index > rx_handle)
    {
        data_len = (uint8_t)(rx_index - rx_handle);
    }
    else
    {
        data_len = (uint8_t)(UART_RX_BUFF_MAX - rx_handle + rx_index);
        b_buff_offset = 1;
    }

    /* ����һ��֡���Ȳ����� */
    if (data_len < 5)
        return;

    p_hdl = &mpu_data.rx_buffer[mpu_data.rx_handle];
    p_hdl_max = &mpu_data.rx_buffer[UART_RX_BUFF_MAX - 1] + 1;

    /* ɨ������buff�ڵ�֡ͷ��Ϣ����2��������Ϊ�˼���ѭ���ڵ�Խ���ж� */
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
                    /* ���� */
                    p_data++;
                    if (p_data == p_hdl_max)
                        p_data = &mpu_data.rx_buffer[0];
                    cmd_len[head_index++] = *p_data;
                    /* buff�����˳�ѭ�� */
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
                    /* ���� */
                    p_data++;
                    cmd_len[head_index++] = *p_data;
                    /* buff�����˳�ѭ�� */
                    if (head_index == HEAD_MAX)
                        i = cyc_len;
                }
            }
        }
    }

    /* û����Ч֡ */
    if (head_index == 0)
    {
        mpu_data.rx_handle = rx_index;
        return;
    }

    /* ��λָ�� */
    temp = mpu_data.rx_handle + head[0];
    mpu_data.rx_handle = (uint8_t)(temp % UART_RX_BUFF_MAX);

    p_hdl = &mpu_data.rx_buffer[mpu_data.rx_handle];

    /* һ֡����Ϊ����ȼ��� 0x5A ��0xA5��LEN 3���ֽ� */
    frame_len = (uint8_t)(cmd_len[0] + 3);

    if (head_index == 1)
    {
        /* ֻ��һ֡�Ļ�����ȷ��֡��Ӧ��С�ڵ�����Ч���ݳ� */
        if (frame_len <= data_len)
        {
            mpu_checksum(p_hdl, frame_len, b_buff_offset);
            return;
        }
        else
        {
            /* Ҳ�������ݻ�δ������ȫ���ȴ���һ���ٴ��� */
            return;
        }
    }

    /* headindex > 1 */
    /* �����ж����е������Ƿ���һ֡ */
    if (frame_len == data_len)
    {
        mpu_checksum(p_hdl, frame_len, b_buff_offset);
        return;
    }

    /* Ѱ����֡�������2֡ͷ��� */
    for (i = 1; i < head_index; i++)
    {
        if (frame_len == (head[i] - head[0]))
            break;
    }
    if (i >= head_index)
    {
        /* ����֡δ������ȫ����ʱ���� */
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
        /* ֡���������һ֡���󣬶��� */
        else
        {
            temp = mpu_data.rx_handle + (uint8_t)(head[1] - head[0]);
            mpu_data.rx_handle = (uint8_t)(temp % UART_RX_BUFF_MAX);
        }
        return;
    }
    /* ֡����ȷ�����checksum */
    else
    {
        mpu_checksum(p_hdl, frame_len, b_buff_offset);
        return;
    }
}

/* ��1֡���ݽ���checksumУ�� */
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

    /* checksum�Ǵ�LENλ��ʼ����,ָ�����ƶ�2��BYTE(֡ͷ)ָ��LEN */
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

    /* checksum����Ϊ֡����ȥ2�ֽڵĿ��� */
    cyc_len = (uint8_t)(frame_len - 2);
    checksum = 0;
    /* ��λ����֡������ */
    mpu_rx_timer = 0;

    /* checksum���� */
    /* bufferԽ��ѭ������ */
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

    /* ��ȷ֡����֡���廹�пռ� */
    if ((checksum == 0) && (!uart_rx_frame_buff_full(INDEX_UART)))
    {
        p_frame = &mpu_data.rx_frame_buffer[mpu_data.rx_frame_index][0];
        p_hdl = p_buff;

        /* ȡ����ȷ֡���ݣ�����֡���� */
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

        /* ����bufferָ��λ�� */
        temp = mpu_data.rx_handle + cyc_len;
        mpu_data.rx_handle = (uint8_t)(temp % UART_RX_BUFF_MAX);
        return;
    }
    else
    {
        /* ����bufferָ��λ�� */
        temp = mpu_data.rx_handle + frame_len;
        mpu_data.rx_handle = (uint8_t)(temp % UART_RX_BUFF_MAX);

        return;
    }
}

/* �Խ��յ���֡���д��� */
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
     * id��һ��32λ��ֵ����ͨѶ�зֳ�4��unsigned char����������;
     * mpu_rx_prm5  mpu_rx_prm4  mpu_rx_prm3  mpu_rx_prm2
     *   (��8λ)     (�θ�8λ)    (�ε�8λ)      (��8λ)
     */
    can_frame.ulID = (unsigned long)(mpu_rx_prm2
                                  | (mpu_rx_prm3 << 8)
                                  | (mpu_rx_prm4 << 16)
                                  | (mpu_rx_prm5 << 24));

    /* Save the 8 bytes can data */
	strncpy(&can_frame.ucDatBuf[0], &mpu_rx_prm6, CAN_DATA_LENGTH);

    /* ���can����buffer���пռ䣬���浱ǰ����֡�������� */
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


