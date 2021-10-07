/*
 * can.h - can.h config header file;
 *
 * Copyright (c) 2014 Forlan.yung(YANGHUALIANG)
 *
 */

#ifndef _CAN_H_
#define _CAN_H_

#ifdef CAN_ROOT
#define EXTERN_CAN
#else
#define EXTERN_CAN extern
#endif


/****************************************************************************
      ����������
****************************************************************************/
enum
{
    CAN_STATUS_POWERDN,
    CAN_STATUS_WAIT_POWERREADY,
    CAN_STATUS_INIT,
    CAN_STATUS_RUNING
};

/* ѡ��CAN ģ��ʱ�� */
#define FCAN8M                  8000000UL
#define FCAN6M                  6000000UL
#define FCAN2M                  2000000UL
#define FCAN48M                 48000000UL
#define FCAN                    FCAN48M                                 /* ����CANģ��ʱ�� */

/* �궨����ա����ͱ��Ķ��� */
#define RE_DATA_SN              0x00FFFFFFUL                            /* ��λѡ���������֡�ı��Ķ��� */
#define RE_REMOTE_SN            0x7F000000UL                            /* ��λѡ�����Զ��֡�ı��Ķ��� */
#define TX_MSG_SN               32                                      /* ���ͱ��Ķ����� */

/* �궨��CAN���Ļ��������� */
#define CAN_BUF_RE_LENGTH       50
#define CAN_BUF_TX_LENGTH       50

/* �궨��CAN֡�ĳ��� */
#define CAN_FRAME_LENGTH        14
#define CAN_DATA_LENGTH         8

/* ��������ֵ */
#define CAN_ERROR               0
#define CAN_OK                  1
#define BUSY                    2                                       /* ��ʾ��ǰ�������ڷ��� */

/* CAN�жϻص���������Ϣ����(CAN�ڵ�״̬) */
#define CAN_FRAM_RECV           0x01                                    /* �ɹ����յ�����֡��Զ��֡ */
#define CAN_FRAM_SEND           0x02                                    /* ������� */
#define CAN_BUS_OFF             0x04                                    /* �ڵ��������� */
#define CAN_SEND_FAIL           0x08                                    /* ����ʧ�� */
#define CAN_NO_ERROR            0x00                                    /* û�д��� */

/* �������չ������շ�ʽ */
#define EXT_ID_FILTER           1                                       /* ������չ֡                   */
#define STD_ID_FILTER           2                                       /* ���ձ�׼֡                   */
#define STD_EXT_FILTER          3                                       /* ���ձ�׼֡����չ֡           */

#define UNMASK                  0x00000000UL                            /* ��ʹ��ID�˲�                 */
#define MASK                    0x1FFFFFFFUL                            /* ����ID�����������˲�         */

/* �����ʱ������궨�� */
#define CANBAUD_1M              0
#define CANBAUD_500K            1
#define CANBAUD_250K            2
#define CANBAUD_125K            3
#define CANBAUD_100K            4
#define CANBAUD_50K             5
#define CANBAUD_25K             6
#define CANBAUD_20K             7
#define CANBAUD_10K             8
#define CANBAUD_5K              9
#define CANBAUD_2K5             10

/* ֡���ͼ���ʽ */
#define STD_DATA                0xF0                                     /* ��׼��ʽ����֡               */
#define XTD_DATA                0xF2                                     /* ��չ��ʽ����֡               */

#define STD_RMRQS               0xF1                                     /* ��׼��ʽԶ��֡               */
#define XTD_RMRQS               0xF3                                     /* ��չ��ʽԶ��֡               */

#define XTD_MASK                0x02                                     /* ��չ֡����                   */
#define RMRQS_MASK              0x01                                     /* Զ��֡����                   */

#define BUF_BLANK               0x00                                     /* ��ǿհ�֡�����ڶ���д����   */


/****************************************************************************
      ����������
****************************************************************************/
/* ����CAN���Ľṹ�� */
typedef struct
{
    unsigned char ucTtypeFormat;                                        /* 0��3 ֡���ͼ���ʽ            */
    unsigned char ucDLC;                                                /* ���ݳ�����                   */
    unsigned long ulID;                                                 /* CAN����ID                    */
    unsigned char ucDatBuf[8];                                          /* �������ݳ�                   */
}CANFRAME;

/* ����CAN���ջ��λ������ṹ */
typedef struct
{
    unsigned long ulWriteIndex;                                         /* ����Buffer[]д�±�           */
    unsigned long ulReadIndex;                                          /* ����Buffer[]���±�           */
    BOOL bIsFull;
    unsigned long ulLength;                                             /* ��¼�������                 */
    CANFRAME *ptCanFramBuf;                                             /* ָ�����ݳ�������             */
}CANCIRBUF;

/* ����CAN����������ṹ */
typedef struct
{
    unsigned long ulSysPeriph;                                          /* CAN������ϵͳ����            */
    unsigned long ulBase;                                               /* CAN��������ַ                */

    unsigned long ulGpioPeriph;                                         /* GPIO����                     */
    unsigned long ulGpioBase;                                           /* GPIO��Ӧ��ַ                 */
    unsigned long ulGpioPin;                                            /* ��Ӧ��������                 */
} CANHARDWARE;

/* ����CAN�ڵ�ṹ�� */
typedef struct {
    unsigned long ulBaseAddr;                                           /* CAN��������ַ                */
    unsigned char ucNodeState;                                          /* ���ڼ�¼�ڵ�״̬             */
    unsigned char ucBaudIndex;                                          /* �����ʲ�������               */
    unsigned long ulBofTimer;                                           /* ���ڵ��������ߺ�ļ�ʱ����   */
    unsigned long ulDaReObjMsk;                                         /* ��������֡�ı��Ķ���,��λѡͨ*/
    unsigned long ulRmReObjMsk;                                         /* ����Զ��֡�ı��Ķ���,��λѡͨ*/
    unsigned long ulTxMsgObjNr;                                         /* ��λ��Ƿ��ͱ��Ķ���         */
    CANCIRBUF *ptCanReCirBuf;                                           /* ָ�򱾽ڵ�Ľ��ջ�����       */
    CANCIRBUF *ptCanTxCirBuf;                                           /* ָ�򱾽ڵ�ķ��ͻ�����       */
    void (*pfCanHandlerCallBack)(unsigned long ulMessage, long lParam1, long lParam2);
    //�ṩ���жϴ�����canHandler()�Ļص�����,���յ�����֡��Զ��֡ʱ����
    void (*pfIsrHandler)(void);                                         /* CAN�ڵ���жϷ�����        */
}CANNODEINFO;

/* ���ڶ��岢��ʼ��CAN�ڵ�ṹ������ĺ� */
#define CANNODE(ulBaseAddr, ucBaudIndex, ulDaReObjMsk, ulRmReObjMsk,    \
                ulTxMsgObjNr,ptReCirBuf, pfCanHandlerCallBack,          \
                pfIsrHandler)                                           \
        {                                                               \
           ulBaseAddr,                                                  \
           0,                                                           \
           ucBaudIndex,                                                 \
           0,                                                           \
           ulDaReObjMsk,                                                \
           ulRmReObjMsk,                                                \
           ulTxMsgObjNr,                                                \
           (CANCIRBUF *)ptReCirBuf,                                     \
           (CANCIRBUF *)0,                                              \
           pfCanHandlerCallBack,                                        \
           pfIsrHandler,                                                \
        }


/****************************************************************************
      ����������
****************************************************************************/
EXTERN_CAN uint8_t can_main_status;
/* �ṩ���ⲿ���õĽṹ�峣�� */
EXTERN_CAN const CANFRAME GtCanFrameInit;                                   /* �ѳ�ʼ��Ϊ�հ׵�CAN�����    */
EXTERN_CAN CANNODEINFO *GptCanNode0;                                        /* ����ָ��CAN0�Ľڵ�ָ��       */


/****************************************************************************
      ����������
****************************************************************************/
extern void can_main(void);
extern void can_to_mpu_cmd(uint8_t id, uint16_t param);
extern void can_rx_handle(CANFRAME *pt_can_frame);
extern bool can_tx_handle(uint8_t msg_id, uint16_t prm);
extern void can_timer_100ms(void);

extern void can_circulation_buffer_init(CANCIRBUF *ptCanCirBuf, CANFRAME *ptCanFrameBuf, uint8_t ucLength);
extern uint8_t can_circulation_buffer_read(CANCIRBUF *ptCanCirBuf, CANFRAME  *ptCanFrame);
extern uint8_t can_circulation_buffer_write(CANCIRBUF *ptCanCirBuf, CANFRAME *ptCanFrame);
extern uint8_t can_circulation_buffer_send(CANNODEINFO *ptCanNode, CANCIRBUF *ptCanCirBuf);
extern void can_frame_send(CANNODEINFO *ptCanNode, CANFRAME  *pCANFrame);
extern void can_user_interrupt_control(CANNODEINFO *ptCanNode);
extern void isr_can(CANNODEINFO *ptCanNode);
extern void can_node_bus_on(CANNODEINFO *ptCanNode);
extern void can_node_create(CANNODEINFO *ptCanNode,
                          unsigned long ulBaseAddr,
                          unsigned char ucBaudIndex,
                          unsigned long ulDaReObjMsk,
                          unsigned long ulRmReObjMsk,
                          unsigned long ulTxMsgObjNr,
                          CANCIRBUF *ptReCirBuf,
                          void (*pfCanHandlerCallBack)(unsigned long ulMessage, long lParam1, long lParam2),
                          void (*pfIsrHandler)(void));
extern void can_node_call_back_set(CANNODEINFO *ptCanNode,
                               void (*pfHandlerCallBack)(unsigned long ulMessage, long lParam1, long lParam2));
extern void can_accept_filter_set(CANNODEINFO *ptCanNode,
                               unsigned long ulFrameID,
                               unsigned long ulFrameIDMask,
                               unsigned char ucFramType);
extern void can_read_message_object_set(CANNODEINFO *ptCanNode,
                           unsigned long ulMsgObjMask,
                           unsigned long ulFrameID,
                           unsigned long ulFrameIDMask,
                           unsigned char ucFramType,
                           unsigned char ucMsgType);
extern uint8_t can_user_init(CANNODEINFO *ptCanNode,
                          unsigned long ulFrameID,
                          unsigned long ulFrameIDMsk,
                          unsigned char ucFramType);

//unsigned char can_data_send(CANFRAME *ptCanFrame);
unsigned char can_data_send(void);



#endif


