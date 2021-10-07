/*
 * main_power.c - main_power.c config and achieve;
 *
 * Copyright (c) 2014 Forlan.yung(YANGHUALIANG)
 *
 */

#define GLOBALS_POWER
#include "include.h"

/****************************************************************************
      变量定义区
****************************************************************************/
static uint8_t main_power_timer;         /* 电源端口定时器 */
static uint8_t power_state_timer;        /* 电源状态定时器 */
static uint8_t sleep_timer;              /* 进入睡眠状态(省电状态)的定时器 */


/****************************************************************************
      函数声明区
****************************************************************************/
static void poweroff_start(void);
static void poweroff_enter(void);


/****************************************************************************
      函数定义区
****************************************************************************/
void power_timer_100ms(void)
{
    /* power state timer control */
    if (power_state_timer != 0xFF) power_state_timer++;
}

void power_timer_1s(void)
{
    if (sleep_timer != 0xFF)
        sleep_timer++;
    return;
}

bool poweroff_request(void)
{
    /* alway power on */
    return false;
}

bool poweron_request(void)
{
    /* alway power on */
    return true;
}

static void poweroff_start(void)
{    
    /* If the MCU control the main power, here you can notify other module the main power will poweroff */
    
    n_power_state = WAIT_POWER_OFF;
    power_state_timer = 0;

    return;
}

static void poweroff_enter(void)
{
    n_power_state = POWER_OFF_ACC_ON;
    power_state_timer = 0;
    return;
}

bool main_power_state(void)
{
    /* If the main power control by MCU, please detect the control bit here */
    //if (!power_ctrl_val) return false;
    /* The timer is 12ms * 10 = 120ms */
    return(uint8_t)(main_power_timer > 10);
}

/* Time scheduler is 12ms */
void power_manage(void)
{
    if (main_power_timer != 0xFF)
        main_power_timer++;

    /* detect the acc status */
    /* detect the battery status */

    /* moduler power manage is here */
    mpu_power_manage();
	can_power_manage();

    switch (n_power_state)
    {
        case RESET_POWER_UP:
            if (poweroff_request())
            {
                /* 上电或者复位后，ACC为低 */
                n_power_state = POWER_OFF_ACC_ON;
                power_state_timer = 0x00;
            }
            else
            {
                n_power_state = SWITCH_ON_CHECK_BATTERY;
                power_state_timer = 0x00;
            }
            break;

        case SWITCH_ON_CHECK_BATTERY:
            if (poweroff_request())
            {
                n_power_state = POWER_OFF_ACC_ON;
                power_state_timer = 0x00;
                return;
            }
            /* main power timer counter 50 * 12ms = 600ms */
            if (main_power_timer < 50) break;
            /* power state timer counter 4 * 100ms = 400ms */
            if (power_state_timer > 4)
            {
                n_power_state++;
                return;
            }
            break;

        case SWITCH_ON_INIT:
            if (poweroff_request())
            {
                poweroff_start();
                break;
            }
            if (main_power_state())
            {
                n_power_state++;
                power_state_timer = 0;
                break;
            }
            break;

        case SYSTEM_RUN:
            if (poweroff_request())
            {
                poweroff_start();
            }
            break;

        case WAIT_POWER_OFF:
            /* timer 100ms * 10 = 1s, you can define timer by yourself */
            if (power_state_timer >= 10)
            {
                poweroff_enter();
            }
            break;

        case SYSTEM_IGNITION:
            #if 0
            if ()
            {
                n_power_state = POWER_OFF_ACC_ON;
                power_state_timer = 0;
            }
            #endif
            break;

        case POWER_OFF_ACC_ON:
            if (poweron_request())
            {
                n_power_state = SWITCH_ON_CHECK_BATTERY;
                power_state_timer = 0;
                break;
            }
            /* If the ACC detect by MCU and ACC if off, do this */
            #if 0
            if (ACCOFF)
            {
                n_power_state = POWER_OFF_ACC_OFF;
                sleep_timer = 0;
                break;
            }
            #endif
            break;

        case POWER_OFF_ACC_OFF:
            if (poweron_request())
            {
                n_power_state = SWITCH_ON_CHECK_BATTERY;
                power_state_timer = 0;
                break;
            }
            /* If the ACC detect by MCU and ACC if on, do this */
            #if 0
            if (ACCON)
            {
                n_power_state=POWER_OFF_ACC_ON;
                break;
            }
            #endif
            /* timer 1000ms * 60 = 60S */
            if (sleep_timer >= 60)
            {
                n_power_state = SYSTEM_SLEEP;
                sleep_timer = 0;
                break;
            }
            break;

        case SYSTEM_SLEEP:
            /* If ACC detect by MCU, please define here */
            #if 0
            if (ACCON)
            {
                n_power_state = POWER_OFF_ACC_ON;
                break;
            }
            #endif
            /* timer 1000ms * 5 = 5s */
            if (sleep_timer >= 5)
            {
                sleep_timer = 0;
                /* enter the sleep mode */
                while (true)
                {
                    /* wait ACC ON and back from sleep mode */
                    #if 0
                    if (ACCON)
                    {
                        break;
                    }
                    #endif
                }
            }
            break;

        default:
            poweroff_enter();
            break;
    }

    return;
}


