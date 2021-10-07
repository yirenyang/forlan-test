/*
 * mpu_power.c - mpu_power.c config and achieve;
 *
 * Copyright (c) 2014 Forlan.yung(YANGHUALIANG)
 *
 */

#include "include.h"


/****************************************************************************
      ����������
****************************************************************************/
#define MPU_RESET_INTERVAL     16
#define MPU_DELAY_INTERVAL     250

enum
{
    _MPU_POWER_OFF,
    _MPU_POWER_INIT,
    _MPU_RESET_START,
    _MPU_RESET_END,
    _MPU_POWER_OK,
    _MPU_POWEROFF_DELAY
};


/****************************************************************************
      ����������
****************************************************************************/
static uint8_t mpu_power_timer;
static uint8_t mpu_power_state;


/****************************************************************************
      ����������
****************************************************************************/
void mpu_reset(void)
{
    mpu_power_state = _MPU_RESET_START;

    return;
}

void mpu_poweroff_delay(void)
{
    mpu_power_state = _MPU_POWEROFF_DELAY;
}


static void mpu_reset_start(void)
{
    /* Set the mpu reset */
    return;
}


static void mpu_reset_end(void)
{
    /* Clear the mpu reset */
    return;
}

bool mpu_power_ready(void)
{
    if (mpu_power_state == _MPU_POWER_OK)
    {
        return true;
    }

    return false;
}

void mpu_power_req(bool b_flag)
{
    if (b_flag)
    {
        mpu_main_status = MPU_STATUS_WAIT_POWERREADY;
    }
    else
    {
        mpu_main_status = MPU_STATUS_POWERDN;
        uart_disable();

        mpu_poweroff_delay();
    }
}

//Time slot is 12ms
void mpu_power_manage(void)
{
    if (mpu_power_state)
    {
        if (mpu_power_state != _MPU_POWEROFF_DELAY && !main_power_state())
        {
            mpu_reset_end();
            mpu_power_state = _MPU_POWER_OFF;
        }
    }

    switch (mpu_power_state)
    {
        case _MPU_POWER_OFF:                    /* ����Դ�رպ��ͷŸ�λ�˿� */
        default:
            if (main_power_state())
            {
                #if 0
                if (need to reset the mpu)
                {
                    mpu_reset_start();
                }
                else
                #endif
                {
                    mpu_power_req(1);
                    mpu_power_state = _MPU_POWER_INIT;
                    mpu_power_timer = 0;
                }
            }
            break;

        case _MPU_POWER_INIT:
            /* ִ�ж�MPU��λ�Ķ��� */
            if (mpu_power_timer == 0)
            {
                /* ��λ */
                mpu_reset_start();
                mpu_power_timer++;
                break;
            }
            mpu_power_timer++;
            if (mpu_power_timer == MPU_RESET_INTERVAL)
            {
                /* 200ms���ͷ�, MPU�ĸ�λʱ�� */
                mpu_power_state = _MPU_RESET_END;
                break;
            }
            break;

        case _MPU_RESET_START:                  /* ִ�ж�MPU��λ�Ķ��� */
            mpu_reset_start();
            mpu_power_timer = 0;
            mpu_power_state = _MPU_RESET_END;
            break;

        case _MPU_RESET_END:                    /* �ȴ���λʱ��ﵽ���ͷŸ�λ�˿� */
            mpu_power_timer++;
            if (mpu_power_timer < MPU_RESET_INTERVAL)
            {
                break;
            }
            //mpu_reset_end();
            mpu_power_state = _MPU_POWER_OK;
            break;

        case _MPU_POWER_OK:                     /* MPU�ĵ�Դ�͸�λ�����ȶ�״̬ */
            break;

        case _MPU_POWEROFF_DELAY:
            if (!main_power_state())
            {
                mpu_power_state = _MPU_POWER_OFF;
                mpu_power_timer = 0;
                break;
            }
    }

    return;
}


