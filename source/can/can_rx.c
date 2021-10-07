/*
 * can_rx.c - can_rx.c config and achieve;
 *
 * Copyright (c) 2014 Forlan.yung(YANGHUALIANG)
 *
 */

#include "include.h"

/****************************************************************************
      ����������
****************************************************************************/


/****************************************************************************
      ����������
****************************************************************************/


/****************************************************************************
      ����������
****************************************************************************/
static void transfer_data_to_mpu_rx_can_buffer(CANFRAME *pt_can_frame);


/****************************************************************************
      ����������
****************************************************************************/
void can_rx_handle(CANFRAME *pt_can_frame)
{
    transfer_data_to_mpu_rx_can_buffer(pt_can_frame);
}

static void transfer_data_to_mpu_rx_can_buffer(CANFRAME *pt_can_frame)
{
    /* ���mpu_rx_can_frame_buffû�������������ݵ�buffer�У���������ǰ֡ */
    if (!mpu_rx_can_frame_buff_full())
    {
        mpu_rx_can_prm0 = pt_can_frame->ucTtypeFormat;
        mpu_rx_can_prm1 = pt_can_frame->ucDLC;

        /*
         * id��һ��32λ��ֵ����ͨѶ�зֳ�4��unsigned char����������;
         * mpu_rx_prm5  mpu_rx_prm4  mpu_rx_prm3  mpu_rx_prm2
         *   (��8λ)     (�θ�8λ)    (�ε�8λ)      (��8λ)
         */
        mpu_rx_can_prm2 = (uint8_t)(pt_can_frame->ulID & 0x000000FF);
        mpu_rx_can_prm3 = (uint8_t)((pt_can_frame->ulID & 0x0000FF00) >> 8);
        mpu_rx_can_prm4 = (uint8_t)((pt_can_frame->ulID & 0x00FF0000) >> 16);
        mpu_rx_can_prm5 = (uint8_t)((pt_can_frame->ulID & 0xFF000000) >> 24);

        /* ����can�� 8 bytes ���� */
        strncpy(&mpu_rx_can_prm6, &pt_can_frame->ucDatBuf[0], CAN_DATA_LENGTH);

        mpu_data.mpu_rx_can_frame_index++;
        if (mpu_data.mpu_rx_can_frame_index >= MPU_RX_CAN_FRAME_MAX)
        {
            mpu_data.mpu_rx_can_frame_index = 0;
        }

        can_to_mpu_cmd(MCU_CAN_TO_MPU_BT_INFO_IND, 0);
    }

    return;
}


