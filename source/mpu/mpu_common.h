/*
 * mpu_common.h - mpu_common.h config header file;
 *
 * Copyright (c) 2014 Forlan.yung(YANGHUALIANG)
 *
 */

#ifndef _MPU_COMMON_H_
#define _MPU_COMMON_H_

/*
 * MCU-MPUͨ�ŵ��������,�����Ϊ4��:
 * REQ: MPU��MCU���͵������������ҪӦ������
 * CFM: MCU��ӦMPU����������
 * REPORT: MPU������MCU���������״̬������ҪӦ��
 * IND: MCU������MPU���������״̬������ҪӦ��
 */
/* ϵͳ����/���ñ��� */
#define MCU_MPU_INIT_REQ                    0x00
#define MCU_MPU_INIT_CFM                    0x80

/* �汾��Ϣ */
#define MCU_MPU_VERSION_REQ                 0x01
#define MCU_MPU_VERSION_CFM                 0x81

/* MCU���� */
#define MCU_MPU_UPGRADE_START_REQ           0x02
#define MCU_MPU_UPGRADE_START_CFM           0x82
#define MCU_MPU_UPGRADE_DATA_REQ            0x03
#define MCU_MPU_UPGRADE_DATA_CFM            0x83
#define MCU_MPU_UPGRADE_CHECKSUM_REQ        0x04
#define MCU_MPU_UPGRADE_CHECKSUM_CFM        0x84

/* MPU��ԭ������״̬��Ϣ */
#define MCU_MPU_TO_CAN_BT_INFO_IND          0x07
#define MCU_CAN_TO_MPU_BT_INFO_IND          0x07


#endif

