/*
 * power.h - power.h config header file;
 *
 * Copyright (c) 2014 Forlan.yung(YANGHUALIANG)
 *
 */

#ifndef _POWER_H_
#define _POWER_H_

#ifndef GLOBALS_POWER
#define power_extern extern
#else
#define power_extern
#endif

/****************************************************************************
      
****************************************************************************/
enum
{
    NO_INIT,
    INIT_STEP1,
    INIT_STEP2,
    INIT_STEP3,
    INIT_STEP4,
    INIT_OK
};

enum POWER_STATE
{
    RESET_POWER_UP,
    SWITCH_ON_CHECK_BATTERY,
    SWITCH_ON_INIT,
    SYSTEM_RUN,
    WAIT_POWER_OFF,
    SYSTEM_IGNITION,
    POWER_OFF_ACC_ON,
    POWER_OFF_ACC_OFF,
    SYSTEM_SLEEP,
    SYSTEM_SLEEP2,
    SYSTEM_SLEEP3,
    SYSTEM_SLEEP4
};


/****************************************************************************
      全局变量定义区
****************************************************************************/
power_extern uint8_t n_power_state;
power_extern  uint8_t sys_init_state;


/****************************************************************************
      函数声明区
****************************************************************************/
extern void power_timer_100ms(void);
extern void power_timer_1s(void);
extern void power_manage(void);
extern bool poweroff_request(void);
extern bool poweron_request(void);
extern bool main_power_state(void);
extern void poweron_init_main(void);
extern void poweron_init_start(void);
extern void poweron_init_reset(void);
extern void sys_init_before_poweron(void);
extern void mpu_power_req (bool b_flag);
extern bool mpu_power_ready(void);
extern void mpu_power_manage(void);
extern void can_power_req(bool b_flag);
extern bool can_power_ready(void);
extern void can_power_manage(void);



#endif

