/*
 * can_power.c - can_power.c config and achieve;
 *
 * Copyright (c) 2014 Forlan.yung(YANGHUALIANG)
 *
 */

#include "include.h"


/****************************************************************************
      ����������
****************************************************************************/
#define CAN_RESET_INTERVAL     16
#define CAN_DELAY_INTERVAL     250

enum
{
    CAN_POWER_OFF,
    CAN_POWER_INIT,
    CAN_RESET_START,
    CAN_RESET_END,
    CAN_POWER_OK,
    CAN_POWEROFF_DELAY
};


/****************************************************************************
      ����������
****************************************************************************/
static uint8_t can_power_timer;
static uint8_t can_power_state;


/****************************************************************************
      ����������
****************************************************************************/
void can_reset(void)
{
    can_power_state = CAN_RESET_START;

    return;
}

void can_poweroff_delay(void)
{
    can_power_state = CAN_POWEROFF_DELAY;
}


static void can_reset_start(void)
{
    /* Set the can reset */
    return;
}


static void can_reset_end(void)
{
    /* Clear the can reset */
    return;
}

bool can_power_ready(void)
{
    if (can_power_state == CAN_POWER_OK)
    {
        return true;
    }

    return false;
}

void can_power_req(bool b_flag)
{
    if (b_flag)
    {
        can_main_status = CAN_STATUS_WAIT_POWERREADY;
    }
    else
    {
        can_main_status = CAN_STATUS_POWERDN;
        //can_disable();

        can_poweroff_delay();
    }
}

//Time slot is 12ms
void can_power_manage(void)
{
    if (can_power_state)
    {
        if (can_power_state != CAN_POWEROFF_DELAY && !main_power_state())
        {
            can_reset_end();
            can_power_state = CAN_POWER_OFF;
        }
    }

    switch (can_power_state)
    {
        case CAN_POWER_OFF:                    /* ����Դ�رպ��ͷŸ�λ�˿� */
        default:
            if (main_power_state())
            {
                #if 0
                if (need to reset the can)
                {
                    can_reset_start();
                }
                else
                #endif
                {
                    can_power_req(1);
                    can_power_state = CAN_POWER_INIT;
                    can_power_timer = 0;
                }
            }
            break;

        case CAN_POWER_INIT:
            /* ִ�ж�CAN��λ�Ķ��� */
            if (can_power_timer == 0)
            {
                /* ��λ */
                can_reset_start();
                can_power_timer++;
                break;
            }
            can_power_timer++;
            if (can_power_timer == CAN_RESET_INTERVAL)
            {
                /* 200ms���ͷ�, CAN�ĸ�λʱ�� */
                can_power_state = CAN_RESET_END;
                break;
            }
            break;

        case CAN_RESET_START:                  /* ִ�ж�CAN��λ�Ķ��� */
            can_reset_start();
            can_power_timer = 0;
            can_power_state = CAN_RESET_END;
            break;

        case CAN_RESET_END:                    /* �ȴ���λʱ��ﵽ���ͷŸ�λ�˿� */
            can_power_timer++;
            if (can_power_timer < CAN_RESET_INTERVAL)
            {
                break;
            }
            //can_reset_end();
            can_power_state = CAN_POWER_OK;
            break;

        case CAN_POWER_OK:                     /* MPU�ĵ�Դ�͸�λ�����ȶ�״̬ */
            break;

        case CAN_POWEROFF_DELAY:
            if (!main_power_state())
            {
                can_power_state = CAN_POWER_OFF;
                can_power_timer = 0;
                break;
            }
    }

    return;
}

