/*
 * power_init.c - power_init.c config and achieve;
 *
 * Copyright (c) 2014 Forlan.yung(YANGHUALIANG)
 *
 */

#include "include.h"

/****************************************************************************
      函数声明区
****************************************************************************/
static void sys_init1_after_pwron(void);
static void sys_init2_after_pwron(void);
static void sys_init3_after_pwron(void);
static void sys_init4_after_pwron(void);


/****************************************************************************
      函数定义区
****************************************************************************/
void sys_init_before_poweron(void)
{
    return;
}

static void sys_init1_after_pwron(void)
{
    return;
}

static void sys_init2_after_pwron(void)
{
    return;
}

static void sys_init3_after_pwron(void)
{
    return;
}

static void sys_init4_after_pwron(void)
{
    return;
}

void poweron_init_start(void)
{
    if (sys_init_state == NO_INIT)
		sys_init_state = INIT_STEP1;
    return;
}

void poweron_init_reset(void)
{
    sys_init_state = NO_INIT;
    return;
}

/* Call by 100ms scheduler */
void poweron_init_main(void)
{
    switch (sys_init_state)
    {
        case NO_INIT:
            break;

        case INIT_STEP1:
            sys_init1_after_pwron();
            sys_init_state++;
            break;

        case INIT_STEP2:
            sys_init2_after_pwron();
            sys_init_state++;
            break;

        case INIT_STEP3:
            sys_init3_after_pwron();
            sys_init_state++;
            break;

        case INIT_STEP4:
            sys_init4_after_pwron();
            sys_init_state++;
            break;

        case INIT_OK:
            break;

        default:
            sys_init_state = NO_INIT;
            break;
    }

    return;
}


