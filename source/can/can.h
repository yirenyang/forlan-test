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
      常量声明区
****************************************************************************/
enum
{
    CAN_STATUS_POWERDN,
    CAN_STATUS_WAIT_POWERREADY,
    CAN_STATUS_INIT,
    CAN_STATUS_RUNING
};

/* 选择CAN 模块时钟 */
#define FCAN8M                  8000000UL
#define FCAN6M                  6000000UL
#define FCAN2M                  2000000UL
#define FCAN48M                 48000000UL
#define FCAN                    FCAN48M                                 /* 定义CAN模块时钟 */

/* 宏定义接收、发送报文对象 */
#define RE_DATA_SN              0x00FFFFFFUL                            /* 按位选择接收数据帧的报文对象 */
#define RE_REMOTE_SN            0x7F000000UL                            /* 按位选择接收远程帧的报文对象 */
#define TX_MSG_SN               32                                      /* 发送报文对象编号 */

/* 宏定义CAN报文缓冲区长度 */
#define CAN_BUF_RE_LENGTH       50
#define CAN_BUF_TX_LENGTH       50

/* 宏定义CAN帧的长度 */
#define CAN_FRAME_LENGTH        14
#define CAN_DATA_LENGTH         8

/* 函数返回值 */
#define CAN_ERROR               0
#define CAN_OK                  1
#define BUSY                    2                                       /* 表示当前队列正在发送 */

/* CAN中断回调函数的消息类型(CAN节点状态) */
#define CAN_FRAM_RECV           0x01                                    /* 成功接收到数据帧或远程帧 */
#define CAN_FRAM_SEND           0x02                                    /* 发送完成 */
#define CAN_BUS_OFF             0x04                                    /* 节点脱离总线 */
#define CAN_SEND_FAIL           0x08                                    /* 发送失败 */
#define CAN_NO_ERROR            0x00                                    /* 没有错误 */

/* 定义验收过滤验收方式 */
#define EXT_ID_FILTER           1                                       /* 验收扩展帧                   */
#define STD_ID_FILTER           2                                       /* 验收标准帧                   */
#define STD_EXT_FILTER          3                                       /* 验收标准帧和扩展帧           */

#define UNMASK                  0x00000000UL                            /* 不使用ID滤波                 */
#define MASK                    0x1FFFFFFFUL                            /* 所有ID均参与验收滤波         */

/* 波特率表索引宏定义 */
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

/* 帧类型及格式 */
#define STD_DATA                0xF0                                     /* 标准格式数据帧               */
#define XTD_DATA                0xF2                                     /* 扩展格式数据帧               */

#define STD_RMRQS               0xF1                                     /* 标准格式远程帧               */
#define XTD_RMRQS               0xF3                                     /* 扩展格式远程帧               */

#define XTD_MASK                0x02                                     /* 扩展帧掩码                   */
#define RMRQS_MASK              0x01                                     /* 远程帧掩码                   */

#define BUF_BLANK               0x00                                     /* 标记空白帧，用于队列写保护   */


/****************************************************************************
      变量声明区
****************************************************************************/
/* 定义CAN报文结构体 */
typedef struct
{
    unsigned char ucTtypeFormat;                                        /* 0～3 帧类型及格式            */
    unsigned char ucDLC;                                                /* 数据场长度                   */
    unsigned long ulID;                                                 /* CAN报文ID                    */
    unsigned char ucDatBuf[8];                                          /* 报文数据场                   */
}CANFRAME;

/* 定义CAN接收环形缓冲区结构 */
typedef struct
{
    unsigned long ulWriteIndex;                                         /* 缓存Buffer[]写下标           */
    unsigned long ulReadIndex;                                          /* 缓存Buffer[]读下标           */
    BOOL bIsFull;
    unsigned long ulLength;                                             /* 记录缓存深度                 */
    CANFRAME *ptCanFramBuf;                                             /* 指向数据场缓冲区             */
}CANCIRBUF;

/* 定义CAN控制器外设结构 */
typedef struct
{
    unsigned long ulSysPeriph;                                          /* CAN控制器系统外设            */
    unsigned long ulBase;                                               /* CAN控制器基址                */

    unsigned long ulGpioPeriph;                                         /* GPIO外设                     */
    unsigned long ulGpioBase;                                           /* GPIO对应基址                 */
    unsigned long ulGpioPin;                                            /* 对应引脚连接                 */
} CANHARDWARE;

/* 定义CAN节点结构体 */
typedef struct {
    unsigned long ulBaseAddr;                                           /* CAN控制器基址                */
    unsigned char ucNodeState;                                          /* 用于记录节点状态             */
    unsigned char ucBaudIndex;                                          /* 波特率参数索引               */
    unsigned long ulBofTimer;                                           /* 本节点脱离总线后的计时变量   */
    unsigned long ulDaReObjMsk;                                         /* 接收数据帧的报文对象,按位选通*/
    unsigned long ulRmReObjMsk;                                         /* 接收远程帧的报文对象,按位选通*/
    unsigned long ulTxMsgObjNr;                                         /* 按位标记发送报文对象         */
    CANCIRBUF *ptCanReCirBuf;                                           /* 指向本节点的接收缓冲区       */
    CANCIRBUF *ptCanTxCirBuf;                                           /* 指向本节点的发送缓冲区       */
    void (*pfCanHandlerCallBack)(unsigned long ulMessage, long lParam1, long lParam2);
    //提供给中断处理函数canHandler()的回调函数,在收到数据帧或远程帧时调用
    void (*pfIsrHandler)(void);                                         /* CAN节点的中断服务函数        */
}CANNODEINFO;

/* 用于定义并初始化CAN节点结构体变量的宏 */
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
      变量定义区
****************************************************************************/
EXTERN_CAN uint8_t can_main_status;
/* 提供给外部引用的结构体常量 */
EXTERN_CAN const CANFRAME GtCanFrameInit;                                   /* 已初始化为空白的CAN缓存块    */
EXTERN_CAN CANNODEINFO *GptCanNode0;                                        /* 定义指向CAN0的节点指针       */


/****************************************************************************
      函数申明区
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


