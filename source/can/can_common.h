/*
 * can_common.h - can_common.h config header file;
 *
 * Copyright (c) 2014 Forlan.yung(YANGHUALIANG)
 *
 */

#ifndef _CAN_COMMON_H_
#define _CAN_COMMON_H_

/*
 * MCU-CAN通信的命令集定义,命令分为4类:
 * REQ: CAN向MCU发送的请求命令，必须要应答命令
 * CFM: MCU响应CAN的请求命令
 * REPORT: MCU主动向CAN报告自身的状态，不需要应答
 * IND: CAN主动向MCU报告自身的状态，不需要应答
 */
/* 系统启动/配置报告 */
#define MCU_CAN_INIT_REQ                    0x00
#define MCU_CAN_INIT_CFM                    0x80

/* 版本信息 */
#define MCU_CAN_VERSION_REQ                 0x01
#define MCU_CAN_VERSION_CFM                 0x81


/* MCU向原车报告状态信息 */
#define MCU_MCU_TO_CAN_BT_INFO_IND          0x02
#define MCU_CAN_TO_MCU_BT_INFO_IND          0x03


#endif

