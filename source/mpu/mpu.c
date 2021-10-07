/*
 * mpu.c - mpu.c config and achieve;
 *
 * Copyright (c) 2014 Forlan.yung(YANGHUALIANG)
 *
 */

#define MPU_ROOT
#include "include.h"


/****************************************************************************
      ����������
****************************************************************************/
static uint8_t mpu_msg_id = NO_MSG;
static uint16_t mpu_msg_prm = 0;


/****************************************************************************
      ����������
****************************************************************************/
static void mpu_hardware_init(void);


/****************************************************************************
      ����������
****************************************************************************/
void mpu_init(void)
{
    return;
}

static void mpu_hardware_init(void)
{
    clear_message(MPU_MSG_QUEUE);
    return;
}


/* 12ms:MPUģ�����غ�������������ģ�����ת */
void mpu_main(void)
{
    MESSAGE *n_msg;

    switch (mpu_main_status)
    {
        case MPU_STATUS_POWERDN:
            break;

        case MPU_STATUS_WAIT_POWERREADY:
            if (mpu_power_ready())
            {
                mpu_main_status = MPU_STATUS_INIT;
            }
            break;

        case MPU_STATUS_INIT:
            mpu_hardware_init();
            uart_init();
            uart_data_init();
            uart_enable();
            mpu_main_status = MPU_STATUS_RUNING;
            break;

        case MPU_STATUS_RUNING:
            mpu_rx_buffer_analyse();
            if (mpu_data.rx_frame_handle != mpu_data.rx_frame_index)
            {
                mpu_rx_handle();
            }

            if (mpu_data.txing)
            {
                break;
            }

            if (mpu_msg_id == NO_MSG)
            {
                n_msg = get_message(MPU_MSG_QUEUE);
                mpu_msg_id = n_msg->id;
                mpu_msg_prm = n_msg->prm;
            }
            if (mpu_msg_id != NO_MSG)
            {
                if (mpu_tx_handle(mpu_msg_id, mpu_msg_prm))
                {
                    mpu_msg_id = NO_MSG;
                }
            }
            break;

        default:
            break;
    }
}

void mpu_to_can_cmd(uint8_t id, uint16_t param)
{
    post_message(CAN_MSG_QUEUE, id, param);
}


