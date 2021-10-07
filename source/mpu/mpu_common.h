/*
 * mpu_common.h - mpu_common.h config header file;
 *
 * Copyright (c) 2014 Forlan.yung(YANGHUALIANG)
 *
 */

#ifndef _MPU_COMMON_H_
#define _MPU_COMMON_H_

/*
 * MCU-MPU通信的命令集定义,命令分为4类:
 * REQ: MPU向MCU发送的请求命令，必须要应答命令
 * CFM: MCU响应MPU的请求命令
 * REPORT: MPU主动向MCU报告自身的状态，不需要应答
 * IND: MCU主动向MPU报告自身的状态，不需要应答
 */
/* 系统启动/配置报告 */
#define MCU_MPU_INIT_REQ                    0x00
#define MCU_MPU_INIT_CFM                    0x80

/* 版本信息 */
#define MCU_MPU_VERSION_REQ                 0x01
#define MCU_MPU_VERSION_CFM                 0x81

/* MCU升级 */
#define MCU_MPU_UPGRADE_START_REQ           0x02
#define MCU_MPU_UPGRADE_START_CFM           0x82
#define MCU_MPU_UPGRADE_DATA_REQ            0x03
#define MCU_MPU_UPGRADE_DATA_CFM            0x83
#define MCU_MPU_UPGRADE_CHECKSUM_REQ        0x04
#define MCU_MPU_UPGRADE_CHECKSUM_CFM        0x84

/* MPU向原车报告状态信息 */
#define MCU_MPU_TO_CAN_BT_INFO_IND          0x07
#define MCU_CAN_TO_MPU_BT_INFO_IND          0x07


#endif

