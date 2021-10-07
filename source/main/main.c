/****************************************************************************
*                                                                           *
*            Software title : mx7 main control software                     *
*                                                                           *
*            Copyright :                                                    *
*                                                                           *
*            Language : ANSI C                                              *
*                                                                           *           
*   Author:FORLAN(杨华良)        Version : V0.00         Date:2014.01.06    *        
*---------------------------------------------------------------------------*
*                                                                           *
*        The program is targeted to build on LPC11XX MCU                    *
*        Program memory map:                                                *
*                            0x0000 0000 - 0x0000 8000 32k Flash memory     *
*        Data memory map:                                                   *
*                            0x1000 0000 - 0x1000 2000 8k SRAM              *
*                            0x1FFF 0000 - 0x1FFF 4000 16k boot ROM         *
*                            0x4000 0000 - 0x4008 0000 512K APB perpherals  *
*                            0x5000 0000 - 0x5020 0000 2M AHB peripherals   *
*        PIN Number:48 PIN                                                  *
*                                                                           *
*---------------------------------------------------------------------------*
*        MCU frequency :                                                    *
*            External crystal oscillator, Fosc = 24MHz.                     *
*---------------------------------------------------------------------------*

****************************************************************************/

#define GLOBALS_MAIN

#include "include.h"
#include <stdio.h>


/****************************************************************************
      变量定义区
****************************************************************************/
uint8_t test_value;


/****************************************************************************
      函数申明区
****************************************************************************/
static void mcu_init(void);
static void start_up_init(void);
static void timer_100ms(void);
static void timer_1s(void);
static void timer_3s(void);
static void timer_10s(void);
static void main_4ms_scheduler(void);
static void main_12ms_scheduler(void);
static void main_32ms_scheduler(void);
static void main_100ms_scheduler(void);


/****************************************************************************
      函数定义区
****************************************************************************/
int main(void)
{
    uint16_t nt_watch;

    __disable_irq();

    watchdog_enable();
    mcu_init();

    nt_watch = 10000;
    while (--nt_watch)
        watchdog_reset();

    mcu_init();
    //mcu_io_refresh();
    start_up_init();

    watchdog_reset();

    __enable_irq();
    /* 设置端口2的0位输出*/
    gpio_direction_value_set(3, 0, 1);

    //printf("\n\r-- Basic UART Project V1.0 --\n\r");
    //printf("\n\r-- EM-LPC1101 --\n\r");
    //printf("\n\r-- Please input any key on the keyboard --\n\r");
  
    while (TRUE)
    {
        watchdog_reset();

        /* 4ms scheduler */
        if (n_scheduler_timer0 >= SCHEDULER_TIMER_4MS)
        {
            n_scheduler_timer0 = SCHEDULER_TIMER0_INIT_VAL;
            main_4ms_scheduler();
            continue;
        }

        /* 12ms scheduler */
        if (n_scheduler_timer1 >= SCHEDULER_TIMER_12MS)
        {
            n_scheduler_timer1 = SCHEDULER_TIMER1_INIT_VAL;
            main_12ms_scheduler();
            continue;
        }

        /* 32ms scheduler */
        if (n_scheduler_timer2 >= SCHEDULER_TIMER_32MS)
        {
            n_scheduler_timer2 = SCHEDULER_TIMER2_INIT_VAL;
            main_32ms_scheduler();
            continue;
        }

        /* 100ms scheduler */
        if (n_scheduler_timer3 >= SCHEDULER_TIMER_100MS)
        {
            n_scheduler_timer3 = SCHEDULER_TIMER3_INIT_VAL;
            timer_100ms();
            timer_1s();
			timer_3s();
            timer_10s();
            main_100ms_scheduler();
            continue;
        }
    }
}

/* Initialize the MCU system */
static void mcu_init(void)
{
    system_init();
    mcu_io_init();
    systick_config();
    config_output_clock();
    uart_init();
}

/* Put the modules initializatiomo here */
static void start_up_init(void)
{
    ;
}

void timer_4ms(void)
{
    schedule_timer_4ms();

    return;
}

static void timer_100ms(void)
{
    /* 100ms timer is define here */
    power_timer_100ms();
	can_timer_100ms();
    return;
}

static void timer_1s(void)
{
    static uint8_t _100ms_counter_1;

    _100ms_counter_1++;
    if (_100ms_counter_1 < 10)
        return;
    _100ms_counter_1 = 0;
    
    /* 1s timer is define here */
    power_timer_1s();
    return;
}

static void timer_3s(void)
{
    static uint8_t _100ms_counter_2;

    _100ms_counter_2++;
    if (_100ms_counter_2 < 30)
   	{
        return;
    }
    _100ms_counter_2 = 0;
    
    /* 3s timer is define here */
    return;
}

static void timer_10s(void)
{
    static uint8_t _100ms_counter_3;

    _100ms_counter_3++;
    if (_100ms_counter_3 < 100)
        return;
    _100ms_counter_3 = 0;

    /* 10s timer is define here */
    return;
}

/* 4ms的定时调度器 */
static void main_4ms_scheduler(void)
{
    return;
}

/* 12ms的定时调度器 */
static void main_12ms_scheduler(void)
{
    power_manage();
    mpu_main();
	can_main();

    return;
}

/* 32ms的定时调度器 */
static void main_32ms_scheduler(void)
{
    return;
}

/* 100ms的定时调度器 */
static void main_100ms_scheduler(void)
{
	gpio_data_value_turn(3, 0);

    return;
}


