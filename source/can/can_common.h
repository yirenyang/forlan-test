/*
 * can_common.h - can_common.h config header file;
 *
 * Copyright (c) 2014 Forlan.yung(YANGHUALIANG)
 *
 */

#ifndef _CAN_COMMON_H_
#define _CAN_COMMON_H_

/*
 * MCU-CANͨ�ŵ��������,�����Ϊ4��:
 * REQ: CAN��MCU���͵������������ҪӦ������
 * CFM: MCU��ӦCAN����������
 * REPORT: MCU������CAN���������״̬������ҪӦ��
 * IND: CAN������MCU���������״̬������ҪӦ��
 */
/* ϵͳ����/���ñ��� */
#define MCU_CAN_INIT_REQ                    0x00
#define MCU_CAN_INIT_CFM                    0x80

/* �汾��Ϣ */
#define MCU_CAN_VERSION_REQ                 0x01
#define MCU_CAN_VERSION_CFM                 0x81


/* MCU��ԭ������״̬��Ϣ */
#define MCU_MCU_TO_CAN_BT_INFO_IND          0x02
#define MCU_CAN_TO_MCU_BT_INFO_IND          0x03


#endif

