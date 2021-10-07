/*
 * can_tx.c - can_tx.c config and achieve;
 *
 * Copyright (c) 2014 Forlan.yung(YANGHUALIANG)
 *
 */

#include "include.h"


/****************************************************************************
      常量定义区
****************************************************************************/


/****************************************************************************
      函数声明区
****************************************************************************/
static void mcu_can_cmd_null(uint16_t prm);


/****************************************************************************
      函数定义区
****************************************************************************/
bool can_tx_handle(uint8_t msg_id, uint16_t prm)
{
    switch (msg_id)
    {
        case MCU_CAN_TO_MPU_BT_INFO_IND:
            break;

        default:
            mcu_can_cmd_null(prm);
            return true;
    }

	if (can_data_send() == CAN_OK)
	{
		return true;
	}

    return false;
}

static void mcu_can_cmd_null(uint16_t prm)
{
    return;
}



