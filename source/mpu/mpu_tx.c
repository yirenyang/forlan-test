/*
 * mpu_tx.c - mpu_tx.c config and achieve;
 *
 * Copyright (c) 2014 Forlan.yung(YANGHUALIANG)
 *
 */

#include "include.h"


/****************************************************************************
      常量定义区
****************************************************************************/
#define LEN_MAX_MODEL           10
#define LEN_MAX_MCU_TYPE        10
#define LEN_MAX_VERSION         8
#define LEN_MAX_DATE            16
#define LEN_MAX_DATE_TIME       25
#define LEN_MAX_MODEL_C         16
#define LEN_MAX_MODEL_F         16

const uint8_t str_version[LEN_MAX_VERSION] = STR_VERSION;
const uint8_t hardware_version[] = HW_VERSION;
//const uint8_t str_date[LEN_MAX_DATE]  = __DATE__;


/****************************************************************************
      函数声明区
****************************************************************************/
static void mcu_mpu_cmd_null(uint16_t prm);
static bool mpu_package_proc(void);
static void mpu_tx_start(void);
static void mcu_can_to_mpu_info_cfm(uint16_t prm);


/****************************************************************************
      函数定义区
****************************************************************************/
bool mpu_tx_handle(uint8_t msg_id, uint16_t prm)
{
    mpu_cmd_length = 0;

    switch (msg_id)
    {
        case MCU_MPU_INIT_CFM:
            break;

        case MCU_MPU_VERSION_CFM:
            break;

        case MCU_CAN_TO_MPU_BT_INFO_IND:
            mcu_can_to_mpu_info_cfm(prm);
            break;

        default:
            mcu_mpu_cmd_null(prm);
            return true;
    }

    if (mpu_package_proc())
    {
        mpu_tx_start();
        return true;
    }

    return false;
}


static void mcu_mpu_cmd_null(uint16_t prm)
{
    return;
}

static void mcu_can_to_mpu_info_cfm(uint16_t prm)
{
    uint8_t *ptr;
    uint8_t *p_frame;

    mpu_cmd_id = MCU_CAN_TO_MPU_BT_INFO_IND;

    ptr = &mpu_cmd_prm0;
    p_frame = &mpu_data.mpu_rx_can_frame_buffer[mpu_data.mpu_rx_can_frame_handle][0];

    /* Clear the can frame buffer */
    MEMSET(ptr, 0, CAN_FRAME_LENGTH);

    /* Package the can frame data to the transmission buffer */
    strncpy(ptr, p_frame, CAN_FRAME_LENGTH);

    /* CMD + PARAM的长度 */
    mpu_cmd_length = CAN_FRAME_LENGTH + 1;

    mpu_data.mpu_rx_can_frame_handle++;
    if (mpu_data.mpu_rx_can_frame_handle >= MPU_RX_CAN_FRAME_MAX)
    {
        mpu_data.mpu_rx_can_frame_handle = 0;
    }

    return;
}


/*
 * 打包发送到MPU的数据
 *
 *    主要是设置帧头，序列号，校验和
 *      5AH    A5H    LEN    CMD    PARAM     CHECKSUM
 *      LEN为CMD、PARAM和CHECKSUM的字节总数
 *        CHECKSUM为LEN、CMD、PARAM各字节总和的补码，即：CHECKSUM ＝ 0 － （LEN + CMD + PARAM）
 *
 * @param pdata  数据指针
 * @param len    数据长度
 */
static bool mpu_package_proc(void)
{
    uint8_t i;
    uint8_t * p_datas;
    uint8_t * p_datat;
    uint8_t * p_max;
    uint16_t temp;
    uint8_t checksum = 0;
    uint8_t frame_len = 0;
    uint8_t checksum_len = 0;

    /* 如果没有要发的消息则返回 */
    if(mpu_cmd_length == 0)
        return false;

    mpu_frame_head  = 0x5A;
    mpu_frame_head2 = 0xA5;
    mpu_cmd_length += 1;

    frame_len = (uint8_t)(mpu_cmd_length + 3);
    checksum_len = (uint8_t)(frame_len - 3);

    if (uart_tx_buffer_space() >= frame_len)
    {
        p_datat = &mpu_data.tx_buffer[mpu_data.tx_index];
        p_max = &mpu_data.tx_buffer[UART_TX_BUFF_MAX - 1] + 1;

        //checksum
        p_datas = &mpu_cmd_length;
        for (i = 0; i < checksum_len; i++)
        {
            checksum += *p_datas++;
        }

        p_datas = &mpu_frame_head;
        for (i = 0; i < frame_len - 1; i++)
        {
            *p_datat++ = *p_datas++;
            if (p_datat == p_max)
                p_datat = &mpu_data.tx_buffer[0];
        }
        *p_datat = (uint8_t)(~checksum + 1);

        temp = mpu_data.tx_index + frame_len;
        mpu_data.tx_index = (uint8_t)(temp % UART_TX_BUFF_MAX);
        return true;
    }

    return false;
}

static void mpu_tx_start(void)
{
    uint8_t n_data;
    uint16_t temp;

    if (mpu_data.txing == 0)
    {
        mpu_data.txing = 1;
        n_data = mpu_data.tx_buffer[mpu_data.tx_handle];

        temp = mpu_data.tx_handle + 1;
        mpu_data.tx_handle = (uint8_t)(temp % UART_TX_BUFF_MAX);

        LPC_UART->THR = n_data;
    }
}


