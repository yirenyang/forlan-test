/*
 * can.c - can.c config and achieve;
 *
 * Copyright (c) 2014 Forlan.yung(YANGHUALIANG)
 *
 */

#define CAN_ROOT
#include "include.h"

/*********************************************************************************************************
      常量定义区
*********************************************************************************************************/
/*********************************************************************************************************
波特率参数表
第一项：传输段及相位缓冲段1的和，取值范围：2～16
第二项：相位缓冲段2，取值范围：1～8
第三项：同步跳转宽度，取值范围1～4
第四项：分频值，取值范围1～1024
*********************************************************************************************************/
const CAN_BIT_CLK_PARM CANBitClkSettings[] =
{
    /* Fcan = 48MHz */
    #if FCAN == FCAN48M
    {15, 8, 4, 2},                                                      /* CANBAUD_1M                   */
    {15, 8, 4, 4},                                                      /* CANBAUD_500K                 */
    {15, 8, 4, 8},                                                      /* CANBAUD_250K                 */
    {15, 8, 4, 16},                                                     /* CANBAUD_125K                 */
    {15, 8, 4, 20},                                                     /* CANBAUD_100k                 */
    {15, 8, 4, 40},                                                     /* CANBAUD_50k                  */
    {15, 8, 4, 80},                                                     /* CANBAUD_25k                  */
    {15, 8, 4, 100},                                                    /* CANBAUD_20k                  */
    {15, 8, 4, 200},                                                    /* CANBAUD_10k                  */
    {15, 8, 4, 400},                                                    /* CANBAUD_5k                   */
    {15, 8, 4, 800},                                                    /* CANBAUD_2k5                  */

    /* Fcan = 6MHz */
    #elif FCAN == FCAN6M
    {3, 2, 2, 1},                                                       /* CANBAUD_1M                   */
    {6, 5, 4, 1},                                                       /* CANBAUD_500K                 */
    {6, 5, 4, 2},                                                       /* CANBAUD_250K                 */
    {15, 8, 4, 2},                                                      /* CANBAUD_125K                 */
    {11, 8, 4, 3},                                                      /* CANBAUD_100k                 */
    {15, 8, 4, 5},                                                      /* CANBAUD_50k                  */
    {15, 8, 4, 10},                                                     /* CANBAUD_25k                  */
    {16, 8, 4, 12},                                                     /* CANBAUD_20k                  */
    {15, 8, 4, 25},                                                     /* CANBAUD_10k                  */
    {15, 8, 4, 50},                                                     /* CANBAUD_5k                   */
    {15, 8, 4, 100},                                                    /* CANBAUD_2k5                  */

    /* Fcan = 2MHz */
    #elif FCAN == FCAN2M
    {0, 0, 0, 0},                                                       /* CANBAUD_1M （无法达到）      */
    {2, 1, 1, 1},                                                       /* CANBAUD_500K                 */
    {4, 3, 3, 1},                                                       /* CANBAUD_250K                 */
    {4, 3, 3, 2},                                                       /* CANBAUD_125K                 */
    {5, 4, 4, 2},                                                       /* CANBAUD_100k                 */
    {5, 4, 4, 4},                                                       /* CANBAUD_50k                  */
    {5, 4, 3, 8},                                                       /* CANBAUD_25k                  */
    {5, 4, 3, 10},                                                      /* CANBAUD_20k                  */
    {5, 4, 3, 20},                                                      /* CANBAUD_10k                  */
    {5, 4, 3, 40},                                                      /* CANBAUD_5k                   */
    {5, 4, 3, 80},                                                      /* CANBAUD_2k5                  */

    /*  Fcan = 8MHz */
    #else
    {4, 3, 3, 1},                                                       /* CANBAUD_1M                   */
    {8, 7, 4, 1},                                                       /* CANBAUD_500K                 */
    {8, 7, 4, 2},                                                       /* CANBAUD_250K                 */
    {11, 4, 4, 4},                                                      /* CANBAUD_125K                 */
    {11, 4, 4, 5},                                                      /* CANBAUD_100k                 */
    {11, 4, 4, 10},                                                     /* CANBAUD_50k                  */
    {11, 4, 4, 20},                                                     /* CANBAUD_25k                  */
    {11, 4, 4, 25},                                                     /* CANBAUD_20k                  */
    {11, 4, 4, 50},                                                     /* CANBAUD_10k                  */
    {11, 4, 4, 100},                                                    /* CANBAUD_5k                   */
    {11, 4, 4, 200},                                                    /* CANBAUD_2k5                  */
    #endif
};

/* 用于初始化CAN缓存块的数据 */
const CANFRAME GtCanFrameInit = {
    BUF_BLANK,                                                          /* 空白帧                       */
    0,                                                                  /* 数据域长度为0                */
    0,                                                                  /* 报文ID为                     */
    {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}                           /* 数据域内容                   */
};

const CANFRAME GtCanFramTest = {                                        /* 测试CAN通信时发送的数据帧    */
    XTD_DATA,                                                           /* 扩展帧                       */
    8,                                                                  /* 数据域长度为8                */
    0x123,                                                              /* 报文ID为0x123                */
    {0x55,0xAA,0x55,0xAA,0x03,0x02,0x01,0x00}                           /* 数据域内容                   */
};


CANFRAME GtCanFrameReBuf[CAN_BUF_RE_LENGTH] = {0};                      /* CAN通信接收缓冲区            */
CANFRAME GtCanFrameTxBuf[CAN_BUF_TX_LENGTH] = {0};                      /* CAN通信发送缓冲区            */

CANCIRBUF GtCanReCirBuf = {                                             /* 定义接收循环队列             */
    0,                                                                  /* 缓存写指针（索引）           */
    0,                                                                  /* 缓存读指针（索引）           */
    false,                                                              /* 标记队列未满                 */
    CAN_BUF_RE_LENGTH,                                                  /* 记录缓存深度                 */
    GtCanFrameReBuf                                                     /* 指向数据场缓冲区             */
};

CANCIRBUF GtCanTxCirBuf = {                                             /* 定义发送循环队列             */
    0,                                                                  /* 缓存Buffer[]写下标           */
    0,                                                                  /* 缓存Buffer[]读下标           */
    false,                                                              /* 标记队列未满                 */
    CAN_BUF_TX_LENGTH,                                                  /* 记录缓存深度                 */
    GtCanFrameTxBuf                                                     /* 指向数据场缓冲区             */
};

CANNODEINFO tCanNode0 = CANNODE(LPC_CAN_BASE,                           /* CAN寄存器基址                */
	                            CANBAUD_100K,                           /* CAN波特率                    */
							    RE_DATA_SN,                             /* 按位选择接收数据针报文对象   */
	                            RE_REMOTE_SN,	                        /* 按位选择接收远程针报文对象   */
							    TX_MSG_SN,		                        /* 发送报文对象编号             */
								&GtCanReCirBuf,	                        /* 指向本节点的接收缓冲区       */
								0,
								0);


/****************************************************************************
      变量定义区
****************************************************************************/
static uint8_t can_msg_id = NO_MSG;
static uint16_t can_msg_prm = 0;


/****************************************************************************
      函数声明区
****************************************************************************/
static void can_hardware_init(void);
static void can_node_state_check(void);


/****************************************************************************
      函数定义区
****************************************************************************/
/* 12ms:can模块主控函数，负责整个模块的运转 */
void can_main(void)
{
    MESSAGE *n_msg;
	CANFRAME can_frame;                                             /* 定义表示CAN帧结构体变量      */

    switch (can_main_status)
    {
        case CAN_STATUS_POWERDN:
            break;

        case CAN_STATUS_WAIT_POWERREADY:
            if (can_power_ready())
            {
                can_main_status = CAN_STATUS_INIT;
            }
            break;

        case CAN_STATUS_INIT:
            can_hardware_init();
            can_user_init(GptCanNode0, 0x123, UNMASK, STD_ID_FILTER | EXT_ID_FILTER);
            can_main_status = CAN_STATUS_RUNING;
            break;

        case CAN_STATUS_RUNING:
			can_node_state_check();
			if (can_circulation_buffer_read(GptCanNode0->ptCanReCirBuf, &can_frame) == CAN_OK)
			{
				can_rx_handle((CANFRAME *)&can_frame);
			}

            if (can_msg_id == NO_MSG)
            {
                n_msg = get_message(CAN_MSG_QUEUE);
                can_msg_id = n_msg->id;
                can_msg_prm = n_msg->prm;
            }
            if (can_msg_id != NO_MSG)
            {
                if (can_tx_handle(can_msg_id, can_msg_prm))
                {
                    can_msg_id = NO_MSG;
                }
            }
            break;

        default:
            break;
    }
}

static void can_hardware_init(void)
{
    clear_message(CAN_MSG_QUEUE);
    GptCanNode0 = &tCanNode0;

    return;
}

/*********************************************************************************************************
** Function name:           can_user_init
** Descriptions:            CAN应用初始化（设置中断服务函数及初始化CAN控制器，设定波特率及验收滤波条件等）
** input parameters:        ptCanNode    指向软件CAN节点结构体变量的指针
**                          ulFrameID    报文的验收ID
**                          ulFrameIDMsk 报文验收ID屏蔽码（对应位为1时，表示验收ID的对应位参与验收滤波）
**                          ucFramType   验收的帧类型：
**                             STD_ID_FILTER   过滤接收标准格式的报文
**                             EXT_ID_FILTER   过滤接收扩展格式的报文
**                             STD_EXT_FILTER  过滤接收标准及扩展格式的报文，使用此类型
**                                             时ulFrameID及ulFrameIDMsk的配置为无效，即接收所有格式的报文
**                          pfun         指向中断服务函数的函数指针
** output parameters:       无
** Returned value:          无
** Created By:
** Created date:
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
uint8_t can_user_init(CANNODEINFO *ptCanNode, unsigned long ulFrameID, unsigned long ulFrameIDMsk, unsigned char ucFramType)
{
    if (ptCanNode == 0) {                                                     /* 检查节点的有效性             */
        return CAN_ERROR;
    }
    
    /* 硬件初始化 */
    LPC_SYSCON->PRESETCTRL |= (0x01 << PRESETCTRL_CAN_RST_N_BIT_OFFSET_VAL);  /* Peripheral reset control     */
    LPC_SYSCON->SYSAHBCLKCTRL |= (0x01 << SYSAHBCLKCTRL_CAN_BIT_OFFSET_VAL);  /* System AHB clock control     */
    LPC_CAN->CLKDIV = CANCLKDIV_DIVIDED_BY_01;                                /* Divided by 1                 */
    
    can_init(ptCanNode->ulBaseAddr);                                          /* 初始化CAN控制器              */
    can_bit_timing_set(ptCanNode->ulBaseAddr, (CAN_BIT_CLK_PARM *)(&CANBitClkSettings[ptCanNode->ucBaudIndex]));
                                                                              /* 设定节点波特率               */
    can_enable(ptCanNode->ulBaseAddr);                                        /* 退出初始化模式，启动CAN节点  */
    
    /* 验收滤波设置 */
    can_accept_filter_set(ptCanNode, ulFrameID, ulFrameIDMsk, ucFramType);
                                                                              /* 验收滤波设置                 */
    /* 中断使能 */
    can_user_interrupt_control(ptCanNode);                                    /* 注册中断服务函数并使能CAN中断*/

    return CAN_OK;
}

static void can_node_state_check(void)
{
	/* 
	 * 总线接入状态判断
	 */
	if ((GptCanNode0->ucNodeState & CAN_BUS_OFF) && (GptCanNode0->ulBofTimer > 25))
	{
		/* CAN控制器脱离总线2.5秒后节点重新上线 */
		can_node_bus_on(GptCanNode0);
		/* 清除离线标志 */
		GptCanNode0->ucNodeState &= ~CAN_BUS_OFF;
	}

	/* 
	 * 发送成功	
	 */
	if (GptCanNode0->ucNodeState & CAN_FRAM_SEND) 
	{
		/* 发送完成, 清除发送完成标 */
		GptCanNode0->ucNodeState &= ~CAN_FRAM_SEND;
	}

	/* 
	 *  传输失败	
	 */
	if (GptCanNode0->ucNodeState & CAN_SEND_FAIL)
	{
		/* 发送失败, 清除发送失败标志 */
		GptCanNode0->ucNodeState &= ~CAN_SEND_FAIL;
	}

	return;
}

void can_to_mpu_cmd(uint8_t id, uint16_t param)
{
    post_message(MPU_MSG_QUEUE, id, param);
}

void can_timer_100ms(void)
{
	if (GptCanNode0->ulBofTimer < 0xFF)
	{
		GptCanNode0->ulBofTimer++;
	}

	return;
}

/*********************************************************************************************************
** Function name:           can_circulation_buffer_init
** Descriptions:            初始化帧接收软件FIFO
** input parameters:        ptBuf      指向接收循环队列的指针
** output parameters:       无
** Returned value:          无
** Created By:
** Created date:            2008.09.03
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:           2009.04.29
** Descriptions:            将帧类型格式初始化为BUF_BLANK，用于防止误读
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void can_circulation_buffer_init(CANCIRBUF *ptCanCirBuf, CANFRAME *ptCanFrameBuf, uint8_t ucLength)
{
    unsigned int i;
    
    ptCanCirBuf->ulWriteIndex    = 0;                                   /* Buffer[]写下标清零           */
    ptCanCirBuf->ulReadIndex     = 0;                                   /* Buffer[]读下标清零           */
    ptCanCirBuf->bIsFull         = false;                               /* 循环队列不满                 */
    ptCanCirBuf->ulLength        = ucLength;                            /* 记录长度,此值不允再许更改    */
    ptCanCirBuf->ptCanFramBuf    = ptCanFrameBuf;                       /* 指向数据缓存区首地址         */

    for (i = 0; i < ucLength; i++)
    {
        ptCanCirBuf->ptCanFramBuf[i] = GtCanFrameInit;                  /* 初始化为空帧                 */
    }
}

/*********************************************************************************************************
** Function name:           can_circulation_buffer_malloc
** Descriptions:            向循环队列（软件FIFO）申请一块帧缓存区域 帧类型格式将被初始化为BUF_BLANK
** input parameters:        ptBuf          指向循环队列的指针
** output parameters:       无
** Returned value:          ptCanFrame     帧缓存地址，若为0则表示循环队列满
** Created By:
** Created date:
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:            添加临界区保护
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
static CANFRAME *can_circulation_buffer_malloc(CANCIRBUF *ptCanCirBuf)
{
    CANFRAME  *ptCanFrame;
    unsigned char ucEnable = 0;
    
    if (ptCanCirBuf == (CANCIRBUF *)0)
    {
        return 0;                                                       /* 队列错误                     */
    }
    if (ptCanCirBuf->bIsFull == true)
    {
        return 0;                                                       /* 队列满,则返回 0              */
    }
    
    ucEnable = __ENTER_CIRTICAL();                                      /* 进入临界区                   */
    ptCanFrame = &(ptCanCirBuf->ptCanFramBuf[ptCanCirBuf->ulWriteIndex++]);
                                                                        /* 取得需要返回的地址           */
    if (ptCanCirBuf->ulWriteIndex == ptCanCirBuf->ulLength)
    {
        ptCanCirBuf->ulWriteIndex = 0;                                  /* 构成循环队列                 */
    }
    if (ptCanCirBuf->ulWriteIndex == ptCanCirBuf->ulReadIndex)          /* 写指针赶上读指针，队列满     */
    {
        ptCanCirBuf->bIsFull = true;                                    /* 置位队列满标志               */
    }
    __EXIT_CIRTICAL(ucEnable);                                          /* 退出临界区                   */
    
    *ptCanFrame = GtCanFrameInit;                                       /* 初始化申请的存储空间         */
    return ptCanFrame;
}

/*********************************************************************************************************
** Function name:           can_circulation_buffer_read
** Descriptions:            从循环队列读取一帧数据
** input parameters:        ptCanBuf       指向循环队列的指针
** output parameters:       ptFrame        数据输出指针
** Returned value:          EMPTY          循环队列为空，循环队列中无可用数据
**                          NOT_EMPTY      循环队列非空
**                          CAN_ERROR           循环队列错误，操作失败
** Created By:
** Created date:
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:            添加临界区保护及误读保护
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
uint8_t can_circulation_buffer_read(CANCIRBUF *ptCanCirBuf, CANFRAME  *ptCanFrame)
{
    uint8_t  ucReturn = CAN_ERROR;
    unsigned long ulIndex;
    unsigned char ucEnable = 0;
    
    if (ptCanCirBuf == (CANCIRBUF *)0) {
        return CAN_ERROR;                                               /* 队列错误                     */
    }
    
    ucEnable = __ENTER_CIRTICAL();                                      /* 进入临界区                   */
    
    if ((ptCanCirBuf->ulReadIndex != ptCanCirBuf->ulWriteIndex) || (ptCanCirBuf->bIsFull == true)) {
        ulIndex = ptCanCirBuf->ulReadIndex;                             /* 缓存下标                     */
        if (ptCanCirBuf->ptCanFramBuf[ulIndex].ucTtypeFormat != BUF_BLANK) {
            //帧允许读（帧写结束之前ucTtypeFormat = BUF_BLANK）
            *ptCanFrame = ptCanCirBuf->ptCanFramBuf[ulIndex];
            ptCanCirBuf->ulReadIndex += 1;                              /* 读指针加1                    */
            if (ptCanCirBuf->ulReadIndex == ptCanCirBuf->ulLength) {
                ptCanCirBuf->ulReadIndex = 0;                           /* 形成环形缓冲器               */
            }
            ptCanCirBuf->bIsFull = false;                               /* 清零缓冲区满标志             */
            ucReturn = CAN_OK;
        }
    }
    __EXIT_CIRTICAL(ucEnable);                                          /* 退出临界区                   */
    
    return ucReturn;
}

/*********************************************************************************************************
** Function name:           can_circulation_buffer_write
** Descriptions:            往循环队列写一帧数据
** input parameters:        ptCanBuf   指向循环队列的指针
** output parameters:       ptFrame    数据输出指针
** Returned value:          CAN_OK    操作成功
**                          CAN_ERROR       操作失败
** Created By:
** Created date:
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:            将帧类型格式的保存放到最后来操作，防止误读
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
uint8_t can_circulation_buffer_write(CANCIRBUF *ptCanCirBuf, CANFRAME *ptCanFrame)
{
    CANFRAME *ptCanFrameObject;
    uint8_t i = 0;
    
    ptCanFrameObject = can_circulation_buffer_malloc(ptCanCirBuf);                    /* 从缓冲区申请一帧报文的存储   */
                                                                        /* 空间                         */
    if (ptCanFrameObject == (CANFRAME *)0) {                            /* 缓冲区未满，申请成功         */
        return CAN_ERROR;
    }
    ptCanFrameObject->ucDLC = ptCanFrame->ucDLC;                        /* 报文数据场长度               */
    ptCanFrameObject->ulID  = ptCanFrame->ulID;                         /* 报文ID（标志字符）           */
    for (i= 0; i < CAN_DATA_LENGTH; i++) {
        ptCanFrameObject->ucDatBuf[i] = ptCanFrame->ucDatBuf[i];        /* 读出数据场内容               */
    }
    ptCanFrameObject->ucTtypeFormat = ptCanFrame->ucTtypeFormat;        /* 写报文类型，使这帧报文有效   */
    return CAN_OK;                                                      /* 返回操作成功                 */
}

/*********************************************************************************************************
** Function name:           can_node_create
** Descriptions:            初始化一个包含CAN节点信息的结构体变量
** input parameters:        ptCanNode:指向节点结构的指针
**                          ulBaseAddr:节点对应的CAN控制器基址
**                          ulBaudIn:节点通信波特率（波特率表的索引）
**                          ulDaReObjMsk:按位选通用于接收数据帧的报文对象
**                          ulRmReObjMsk:按位选通用于接收远程帧的报文对象
**                          ulTxMsgObjNr:发送的报文编号
**                          ptRecvList:指向本节点的接收"缓存"（链表结构）
**                          pfCanHandlerCallBack:指向canHandler()回调函数的指针
** output parameters:       *ptCanNode被初始化
** Returned value:          无
** Created By:
** Created date:
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void can_node_create(CANNODEINFO *ptCanNode, unsigned long ulBaseAddr, unsigned char ucBaudIndex,
                   unsigned long ulDaReObjMsk, unsigned long ulRmReObjMsk, unsigned long ulTxMsgObjNr,
				   CANCIRBUF *ptReCirBuf, void (*pfCanHandlerCallBack)(unsigned long ulMessage, long lParam1, long lParam2),
				   void (*pfIsrHandler)(void))
{
    if (ptCanNode == 0) {                                               /* 检查节点的有效性             */
        return;
    }
    // 软件环境初始化
    ptCanNode->ulBaseAddr    = ulBaseAddr;                              /* CAN控制器基地址              */
    ptCanNode->ucNodeState   = CAN_NO_ERROR;
    ptCanNode->ucBaudIndex   = ucBaudIndex;                             /* CAN控制器波特率索引          */
    ptCanNode->ulBofTimer    = 0;
    
    ptCanNode->ulDaReObjMsk  = ulDaReObjMsk;                            /* 接收数据帧报文对象           */
    ptCanNode->ulRmReObjMsk  = ulRmReObjMsk;
    ptCanNode->ulTxMsgObjNr  = ulTxMsgObjNr;                            /* 发送报文对象                 */
    
    ptCanNode->ptCanReCirBuf = ptReCirBuf;                              /* 指向接收数据链表             */
    ptCanNode->ptCanTxCirBuf = 0;                                       /* 清空发送数据链表             */
    
    ptCanNode->pfCanHandlerCallBack = pfCanHandlerCallBack;             /* 初始化回调函数               */
    ptCanNode->pfIsrHandler = pfIsrHandler;                             /* 中断服务函数                 */
}

/*********************************************************************************************************
** Function name:           can_node_call_back_set
** Descriptions:            设置节点回调函数
** input parameters:        ptCanNode              指向节点结构的指针
**                          pfCanHandlerCallBack      指向回调函数的函数指针
** output parameters:       无
** Returned value:          无
** Created By:
** Created date:
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void can_node_call_back_set(CANNODEINFO *ptCanNode, void (*pfCanHandlerCallBack)(unsigned long ulMessage, long lParam1, long lParam2))
{
    if (ptCanNode == 0) {                                               /* 检查节点的有效性             */
        return;
    }
    ptCanNode->pfCanHandlerCallBack = pfCanHandlerCallBack;
}

/*********************************************************************************************************
** Function name:           can_frame_send
** Descriptions:            发送一帧CAN报文至总线
** input parameters:        pCAN           指向发送报文结构体指针
**                          pFrame         数据块指针
** output parameters:       无
** Returned value:          无
** Created By:
** Created date:
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:            增加远程帧发送功能
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void can_frame_send(CANNODEINFO *ptCanNode, CANFRAME *ptCANFrame)
{
    CAN_MSG_OBJ tMsgObjectTx;
    unsigned char ucEnable = 0;
    if (ptCanNode == 0) {                                               /* 检查节点的有效性             */
        return;
    }
    
    ucEnable = __ENTER_CIRTICAL();                                      /* 进入临界区                   */
    tMsgObjectTx.ulMsgID = ptCANFrame->ulID;                            /* 取得报文标识符               */
    
    if ((ptCANFrame->ucTtypeFormat & XTD_MASK) != 0){
        tMsgObjectTx.ulFlags = MSG_OBJ_EXTENDED_ID;                     /* 扩展格式帧                   */
    } else {
        tMsgObjectTx.ulFlags = MSG_OBJ_NO_FLAGS;                        /* 标准格式帧                   */
    }
    
    tMsgObjectTx.ulFlags |= MSG_OBJ_TX_INT_ENABLE;                      /* 标记发送中断使能             */
    tMsgObjectTx.ulMsgLen = (unsigned long)ptCANFrame->ucDLC;           /* 标记数据域长度               */
    tMsgObjectTx.pucMsgData = ptCANFrame->ucDatBuf;                     /* 传递数据存放指针             */
    can_retry_set(ptCanNode->ulBaseAddr, true);                         /* 启动发送失败重发             */

    if ((ptCANFrame->ucTtypeFormat & RMRQS_MASK) != 0) {
        can_message_set(ptCanNode->ulBaseAddr,                          /* CAN控制器基址                */
        ptCanNode->ulTxMsgObjNr,                                        /* 发送报文对象编号             */
        &tMsgObjectTx, MSG_OBJ_TYPE_TX_REMOTE);                         /* 配置远程帧发送报文对象       */
    } else {
        can_message_set(ptCanNode->ulBaseAddr,                          /* CAN控制器基址                */
        ptCanNode->ulTxMsgObjNr,                                        /* 发送报文对象编号             */
        &tMsgObjectTx, MSG_OBJ_TYPE_TX);                                /* 配置数据帧发送报文对象       */
    }
    __EXIT_CIRTICAL(ucEnable);                                          /* 退出临界区                   */
}

/*********************************************************************************************************
** Function name:        can_read_message_object_set
** Descriptions:         设置接收数据帧及远程帧的报文对象,若选通多个报文对象则将报文对象串连成FIFO缓冲器
** input parameters:     ulBaseAddr      CAN模块基址
**                       ulMsgObjMask    按位选通要设置的报文对象
**                       ulFrameID       接收帧ID
**                       ulFrameIDMsk   接收帧屏蔽码
**                       ucFramType      STD_ID_FILTER    过滤接收标准格式的报文
**                                       EXT_ID_FILTER    过滤接收扩展格式的报文
**                                       STD_EXT_FILTER   过滤接收标准及扩展格式的报文，不使用ID掩码
**                       ucMsgType       MSG_OBJ_TYPE_RX          接收报文对象
**                                       MSG_OBJ_TYPE_RX_REMOTE   接收远程帧报文对象
** output parameters:    无
** Returned value:       无
** Created By:
** Created date:
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void can_read_message_object_set(CANNODEINFO *ptCanNode, unsigned long ulMsgObjMask, unsigned long ulFrameID,
                                 unsigned long ulFrameIDMsk, unsigned char ucFramType, unsigned char ucMsgType)
{
    CAN_MSG_OBJ tMsgObj;
    
    //unsigned long ulBaseAddr;
    LPC_CAN_TypeDef *ptCanBase;
    unsigned char ucDataBuf[8];
    unsigned short usCmdMaskReg;
    unsigned short usMaskReg[2];
    unsigned short usArbReg[2];
    unsigned short usMsgCtrl;
    bool bUseExtendedID = false;
    bool bEob           = false;
    int i;
    
    
    if (ptCanNode == 0) {                                               /* 检查节点的有效性             */
        return;
    }
    
    ptCanBase   = (LPC_CAN_TypeDef *)(ptCanNode->ulBaseAddr);
    
    if (ulMsgObjMask == 0) {
        return;                                                         /* 没有选定报文对象             */
    }
    
    if (ucMsgType == MSG_OBJ_TYPE_RX) {                                 /* 数据帧接收报文对象           */
        ptCanNode->ulDaReObjMsk |= ulMsgObjMask;                        /* 按位标记接收报文对象         */
    } else if (ucMsgType == MSG_OBJ_TYPE_RX_REMOTE){                    /* 远程帧报文接收对象           */
        ptCanNode->ulRmReObjMsk |= ulMsgObjMask;                        /* 按位标记"发送"报文对象       */
    } else {
        return;                                                         /* 参数非法，直接退出此函数     */
    }
    
    tMsgObj.ulMsgID = ulFrameID;                                        /* 报文滤波ID                   */
    tMsgObj.ulMsgIDMask = ulFrameIDMsk;                                 /* ID掩码*/ /* 接收报文对象处理 */
    switch (ucFramType) {                                               /* 帧类型处理                   */
        case STD_ID_FILTER: {                                           /* 标准帧                       */
            tMsgObj.ulFlags = (MSG_OBJ_RX_INT_ENABLE |                  /* 允许接收中断                 */
            MSG_OBJ_USE_ID_FILTER |                                     /* 使用报文ID滤波               */
            MSG_OBJ_USE_EXT_FILTER |                                    /* Xtd参与滤波                  */
            MSG_OBJ_USE_DIR_FILTER);                                    /* Dir参与滤波                  */
            bUseExtendedID = false;                                     /* 不是扩展帧                   */
            break;
        }
        case EXT_ID_FILTER: {                                           /* 扩展帧                       */
            tMsgObj.ulFlags = (MSG_OBJ_RX_INT_ENABLE |                  /* 允许接收中断                 */
            MSG_OBJ_EXTENDED_ID |                                       /* 扩展ID                       */
            MSG_OBJ_USE_ID_FILTER |                                     /* 使用报文ID滤波               */
            MSG_OBJ_USE_EXT_FILTER |                                    /* Xtd参与滤波                  */
            MSG_OBJ_USE_DIR_FILTER);                                    /* Dir参与滤波                  */
            bUseExtendedID = true;                                      /* 是扩展帧                     */
            break;
        }
        case STD_EXT_FILTER: {                                          /* 只对接收报文对象有意义       */
            tMsgObj.ulFlags = (MSG_OBJ_RX_INT_ENABLE |                  /* 允许接收中断                 */
            MSG_OBJ_USE_ID_FILTER |                                     /* 使用报文ID滤波               */
            MSG_OBJ_USE_DIR_FILTER);                                    /* Dir参与滤波                  */
            ulFrameIDMsk   = 0x00000000UL;                              /* 不对ID进行接收滤波           */
            bUseExtendedID = false;                                     /* 不是扩展帧(这里没影响)       */
            break;
        }
        default: {
            return;
        }
    }
    
    
    
    tMsgObj.pucMsgData = ucDataBuf;                                     /* 指向数据存储空间             */
    tMsgObj.ulMsgLen = 8;                                               /* 设置数据域长度               */
    while(__canRegRead((unsigned long)&ptCanBase->IF1_CMDREQ) & CAN_IF1CRQ_BUSY) {;}
                                                                        /* 等待报文处理器空闲           */
    
    usCmdMaskReg = CAN_IF1CMSK_WRNRD |                                  /* 写数据到报文对象存储器       */
    CAN_IF1CMSK_DATAA |                                                 /* 传输数据字节 0～3            */
    CAN_IF1CMSK_DATAB |                                                 /* 传输数据字节 4～7            */
    CAN_IF1CMSK_CONTROL |                                               /* 传输控制位                   */
    CAN_IF1CMSK_ARB;                                                    /* 传输ID+Dir+Xtd+MsgVal到MsgObj*/
    
    usArbReg[0] = 0;
    usMsgCtrl = 0;
    usMaskReg[0] = 0;
    usMaskReg[1] = 0;
    
    switch(ucMsgType) {                                                 /* 报文对象类型处理             */
        case MSG_OBJ_TYPE_RX: {                                         /* 接收数据帧类型               */
            usArbReg[1] = 0;
            break;
        }
        case MSG_OBJ_TYPE_RX_REMOTE: {                                  /* 接收远程帧类型               */
            usArbReg[1] = CAN_IF1ARB2_DIR;                              /* 置位报文方向位,发送方向      */
            usMsgCtrl = CAN_IF1MCTL_UMASK;                              /* Msk、MXtd、MDir用于接收滤波  */
            usMaskReg[0] = 0xffff;
            usMaskReg[1] = 0x1fff;
            usCmdMaskReg |= CAN_IF1CMSK_MASK;
            break;
        }
        default: {
            return;
        }
    }
    
    if(tMsgObj.ulFlags & MSG_OBJ_USE_ID_FILTER) {                       /* 使用报文ID滤波               */
        if(bUseExtendedID) {                                            /* 扩展帧                       */
            usMaskReg[0] = ulFrameIDMsk & CAN_IF1MSK1_IDMSK_M;
            usMaskReg[1] = (ulFrameIDMsk >> 16) & CAN_IF1MSK2_IDMSK_M;
        } else {                                                        /* 标准帧                       */
            usMaskReg[0] = 0;                                           /* 低十六位MSK[15:0]为0         */
            usMaskReg[1]  = (ulFrameIDMsk << 2) & CAN_IF1MSK2_IDMSK_M;  /* MSK[28:18]为标准帧ID MSK     */
        }
    }
    
    if((tMsgObj.ulFlags & MSG_OBJ_USE_EXT_FILTER) ==  MSG_OBJ_USE_EXT_FILTER) {
        usMaskReg[1] |= CAN_IF1MSK2_MXTD;                               /* 扩展标识符Xtd参与验收滤波    */
    }
    
    if((tMsgObj.ulFlags & MSG_OBJ_USE_DIR_FILTER) == MSG_OBJ_USE_DIR_FILTER) {
        usMaskReg[1] |= CAN_IF1MSK2_MDIR;                               /* 报文方向Dir参与验收滤波      */
    }
    
    if(tMsgObj.ulFlags & (MSG_OBJ_USE_ID_FILTER | MSG_OBJ_USE_DIR_FILTER | MSG_OBJ_USE_EXT_FILTER)) {
        usMsgCtrl |= CAN_IF1MCTL_UMASK;                                 /* Msk、MXtd、MDir用于接收滤波  */
        usCmdMaskReg |= CAN_IF1CMSK_MASK;                               /* 传输IDMask+Dir+Mxtd 到MsgObj */
    }
    
    if(bUseExtendedID) {                                                /* 扩展帧验收ID                 */
        usArbReg[0] |= ulFrameID & CAN_IF1ARB1_ID_M;
        usArbReg[1] |= (ulFrameID >> 16) & CAN_IF1ARB2_ID_M;
        usArbReg[1] |= CAN_IF1ARB2_MSGVAL | CAN_IF1ARB2_XTD;
    }  else {                                                           /* 标准帧验收ID                 */
        usArbReg[0] = 0;
        usArbReg[1] |= (ulFrameID << 2) & CAN_IF1ARB2_ID_M;
        usArbReg[1] |= CAN_IF1ARB2_MSGVAL;
    }
    
    usMsgCtrl |= (tMsgObj.ulMsgLen & CAN_IF1MCTL_DLC_M) | CAN_IF1MCTL_EOB;
                                                                        /* Eob = 1                      */
    if(tMsgObj.ulFlags & MSG_OBJ_RX_INT_ENABLE) {
        usMsgCtrl |= CAN_IF1MCTL_RXIE;                                  /* 使能接收中断                 */
    }
    
    __canRegWrite((unsigned long)&ptCanBase->IF1_CMDMSK, usCmdMaskReg);
    __canRegWrite((unsigned long)&ptCanBase->IF1_MSK1, usMaskReg[0]);
    __canRegWrite((unsigned long)&ptCanBase->IF1_MSK2, usMaskReg[1]);
    __canRegWrite((unsigned long)&ptCanBase->IF1_ARB1, usArbReg[0]);
    __canRegWrite((unsigned long)&ptCanBase->IF1_ARB2, usArbReg[1]);
    __canRegWrite((unsigned long)&ptCanBase->IF1_MCTRL, usMsgCtrl);
    
    
    bEob = false;
    for (i = 0; i < 32; i++){
        if (ulMsgObjMask & 0x80000000) {
            if (bEob == false) {
                __canRegWrite((unsigned long)&ptCanBase->IF1_MCTRL, (usMsgCtrl | CAN_IF1MCTL_EOB));
                bEob = true;                                            /* End of the FIFO              */
            } else {
                __canRegWrite((unsigned long)&ptCanBase->IF1_MCTRL, (usMsgCtrl & (~CAN_IF1MCTL_EOB)));
            }
            __canRegWrite((unsigned long)&ptCanBase->IF1_CMDREQ, ((32 - i) & CAN_IF1CRQ_MNUM_M));
                                                                        /* 更新到报文对象               */
            while(__canRegRead((unsigned long)&ptCanBase->IF1_CMDREQ) & CAN_IF1CRQ_BUSY) {
                ;                                                       /* 等待报文处理器空闲           */
            }
        }
        ulMsgObjMask = ulMsgObjMask << 1;                               /* 更形报文对象屏蔽选择         */
        if (ulMsgObjMask == 0) {
            break;                                                      /* 提前退出循环                 */
        }
    }
    return;
}

/*********************************************************************************************************
** Function name:           can_accept_filter_set
** Descriptions:            验收滤波设置
** input parameters:        ptCanNode       指向节点的指针
**                          ulFrameID       接收帧ID
**                          ulFrameIDMsk   接收帧ID屏蔽码
**                          ucFramType      STD_ID_FILTER    过滤接收标准格式的报文
**                                          EXT_ID_FILTER    过滤接收扩展格式的报文
**                                          STD_EXT_FILTER   过滤接收标准及扩展格式的报文，不使用ID掩码
** output parameters:       无
** Returned value:          无
** Created By:
** Created date:
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void can_accept_filter_set(CANNODEINFO *ptCanNode, unsigned long ulFrameID, unsigned long ulFrameIDMsk,
                           unsigned char ucFramType)
{
    /* 检查节点的有效性 */
    if (ptCanNode == 0)
    {
        return;
    }

    /* 配置数据帧接收报文对象 */
    can_read_message_object_set(ptCanNode, ptCanNode->ulDaReObjMsk, ulFrameID, ulFrameIDMsk, ucFramType, MSG_OBJ_TYPE_RX);

    /* 配置远程帧接收报文对象 */
    can_read_message_object_set(ptCanNode, ptCanNode->ulRmReObjMsk, ulFrameID, ulFrameIDMsk, ucFramType, MSG_OBJ_TYPE_RX_REMOTE);
}

/*********************************************************************************************************
** Function name:           can_user_interrupt_control
** Descriptions:            使能CAN中断
** input parameters:        pCAN           指向节点的指针
** output parameters:       无
** Returned value:          无
** Created By:
** Created date:
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void can_user_interrupt_control(CANNODEINFO *ptCanNode)
{
    unsigned long ulIntNum;
    
    if(ptCanNode == 0) {                                                /* 节点有效性判断               */
        return ;
    }
    
    if (ptCanNode->pfIsrHandler) {                                      /* 中断服务函数存在则注册ISR    */
        can_interrupt_register(ptCanNode->ulBaseAddr, ptCanNode->pfIsrHandler);
    } else {
        ulIntNum = __canIntNumberGet(ptCanNode->ulBaseAddr);
        IntEnable(ulIntNum);                                            /* 使能CAN节点中断(to CPU)      */
    }
    can_interrupt_enable(ptCanNode->ulBaseAddr, CAN_INT_MASTER | CAN_INT_ERROR);
                                                                        /* 允许挂起中断及错误中断并使能 */
                                                                        /* CAN 控制器中断源             */
}

/*********************************************************************************************************
** Function name:           can_circulation_buffer_send
** Descriptions:            触发指定循环队列中的帧数据的发送工作
** input parameters:        ptBuf  指向循环队列的指针
** global variable:         GptCanCirBuf:待发送的缓冲区入口地址
**                          GbCanCirBufSend:标志是否将缓冲区数据发送出去
** Returned value:          EMPTY         缓存为空
**                          NOT_EMPTY     缓存不空
**                          CAN_ERROR          循环队列错误，操作失败
**
** Created By:
** Created date:
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
uint8_t can_circulation_buffer_send(CANNODEINFO *ptCanNode, CANCIRBUF *ptCanCirBuf)
{
    CANFRAME  tCanFrame;
    unsigned char ucEnable = 0;
    
    if (ptCanNode == 0) {                                               /* 检查节点的有效性             */
        return CAN_ERROR;
    }
    
    if (ptCanNode->ptCanTxCirBuf != (CANCIRBUF *)0) {                   /* 已有"缓存区"在发送队列       */
        return BUSY;
    }
                                                                        /* 给需要发送的CAN节点          */
    if (can_circulation_buffer_read(ptCanCirBuf, &tCanFrame) != CAN_OK) {             /* 缓存区不为空,继续发送        */
        return CAN_ERROR;
    }
    
    ucEnable = __ENTER_CIRTICAL();                                      /* 进入临界区                   */
    ptCanNode->ptCanTxCirBuf = ptCanCirBuf;                             /* 将要发送的缓冲区首地址传递   */
    ptCanNode->ucNodeState &= ~CAN_FRAM_SEND;                           /* 状态更新为“发送未完成”     */
    can_frame_send(ptCanNode, &tCanFrame);                                /* 发送一帧数据，其余数据将     */
                                                                        /* 在中断中继续发送             */
    __EXIT_CIRTICAL(ucEnable);                                          /* 退出临界区                   */
    return CAN_OK;                                                      /* 返回操作结果                 */
}

/*********************************************************************************************************
** Function name:           isr_can
** Descriptions:            实现中断接收一帧或多帧CAN报文，以及发送成功的标志设置
** input parameters:        ptCanNode：指向CAN软件节点的指针
** output parameters:       无
** Returned value:          无
** Modified by:
** Modified date:
** Descriptions:            CAN中断处理函数
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void isr_can(CANNODEINFO *ptCanNode)
{
    CANFRAME        *ptCanFrame;
    CANFRAME        tCanFrame;
    CAN_MSG_OBJ     tMsgObjBuf;
    
    unsigned long   ulMsgObjID;
    unsigned long   ulNewData;
    unsigned long   ulTxObjMask = 1UL << (ptCanNode->ulTxMsgObjNr - 1);
    uint32_t ulStatus = 0;
    uint32_t ulTxReq  = 0;
    uint32_t ulBit    = 0;
    uint8_t i = 0;
    unsigned long ulCallBackMsg = CAN_NO_ERROR;

    ulMsgObjID = can_interrupt_status(ptCanNode->ulBaseAddr,CAN_INT_STS_OBJECT);
                                                                        /* 读取中断标志,用于分析状态中断*/
    ulStatus   = can_status_get(ptCanNode->ulBaseAddr, CAN_STS_CONTROL);
    ulNewData  = can_status_get(ptCanNode->ulBaseAddr, CAN_STS_NEWDAT);
    ulTxReq    = can_status_get(ptCanNode->ulBaseAddr, CAN_STS_TXREQUEST);
    ulNewData &= ~ulTxObjMask;                                          /* 忽略发送报文对象的NewDat     */
    
    if (ulStatus & CAN_STATUS_LEC_MSK ) {
        ptCanNode->ucNodeState |= CAN_SEND_FAIL;                        /* 发送失败,传输产生了错误      */
    } else {
        ptCanNode->ucNodeState &= ~CAN_SEND_FAIL;                       /* 通信成功，清除错误标志       */
    }
    
    if (ulStatus & CAN_STATUS_BUS_OFF) {
        can_interrupt_disable(ptCanNode->ulBaseAddr, CAN_INT_MASTER | CAN_INT_ERROR);
                                                                        /* 关闭CAN中断                  */
        ptCanNode->ucNodeState |= CAN_BUS_OFF;                          /* 脱离总线                     */
        ptCanNode->ulBofTimer = 0;
        
        ulCallBackMsg |= CAN_BUS_OFF;                                   /* 脱离总线                     */
    }
    
    ulStatus = ulNewData;
    if (ulMsgObjID != 0) {                                              /* 存在挂起中断                 */
        for (i = 0; i < 32; i++) {
            ulBit = 1UL << i;
            if ((ptCanNode->ulDaReObjMsk & ulNewData & ulBit) != 0){    /* 收到数据帧                   */
                ptCanFrame = can_circulation_buffer_malloc(ptCanNode->ptCanReCirBuf); /* 取得缓存地址                 */
                if (ptCanFrame == (CANFRAME *)0) {                      /* 缓存申请失败,说明缓冲区已满  */
                    ptCanFrame = &tCanFrame;                            /* 用局部变量进行缓存,将被丢弃  */
                }
                tMsgObjBuf.pucMsgData = ptCanFrame->ucDatBuf;           /* 传递帧数据缓存地址           */
                can_message_get(ptCanNode->ulBaseAddr, (i + 1), &tMsgObjBuf, 0);
                                                                        /* 读出接收数据                 */
                ptCanFrame->ucDLC = tMsgObjBuf.ulMsgLen;                /* 记录数据场长度               */
                if (tMsgObjBuf.ulFlags & MSG_OBJ_EXTENDED_ID) {         /* 扩展帧 29 位标志字符         */
                    ptCanFrame->ulID = (tMsgObjBuf.ulMsgID & 0x1FFFFFFF);
                                                                        /* 记录CAN报文ID                */
                    ptCanFrame->ucTtypeFormat = XTD_DATA;               /* 记录为扩展数据帧             */
                } else {                                                /* 标准帧 11 位标志字符         */
                    ptCanFrame->ulID = (tMsgObjBuf.ulMsgID & 0x000007FF);
                                                                        /* 记录CAN报文ID                */
                    ptCanFrame->ucTtypeFormat = STD_DATA;               /* 记录为标准数据帧             */
                }
            } else if ((ptCanNode->ulRmReObjMsk & ulNewData & ulBit) != 0) {
                                                                        /* 收到远程帧                   */
                ptCanFrame = can_circulation_buffer_malloc(ptCanNode->ptCanReCirBuf); /* 取得缓存地址                 */
                if (ptCanFrame == (CANFRAME *)0) {                      /* 缓存申请失败,说明缓冲区已满  */
                    ptCanFrame = &tCanFrame;                            /* 用局部变量进行缓存,将被丢弃  */
                }
                tMsgObjBuf.pucMsgData = ptCanFrame->ucDatBuf;           /* 传递帧数据缓存地址           */
                can_message_get(ptCanNode->ulBaseAddr, (i + 1), &tMsgObjBuf, 0);
                ptCanFrame->ucDLC = tMsgObjBuf.ulMsgLen;                /* 记录数据场长度               */
                
                if (tMsgObjBuf.ulFlags & MSG_OBJ_EXTENDED_ID) {         /* 扩展帧 29 位标志字符         */
                    ptCanFrame->ulID = (tMsgObjBuf.ulMsgID & 0x1FFFFFFF);
                    ptCanFrame->ucTtypeFormat = XTD_RMRQS;              /* 记录为扩展远程帧             */
                } else {                                                /* 标准帧 11 位标志字符         */
                    ptCanFrame->ulID = (tMsgObjBuf.ulMsgID & 0x000007FF);
                    ptCanFrame->ucTtypeFormat = STD_RMRQS;              /* 记录为标准远程帧             */
                }
            }
            
            ulStatus &= ~ulBit;
            if (ulStatus == 0) {                                        /* 剩余报文对象已经没有新数据了 */
                break;
            }
        }
        
        ulStatus = ulMsgObjID;
        for (i = 0; i < 32; i++) {                                      /* 清除中断标志                 */
            ulBit = 1UL << i;
            if (ulMsgObjID & ulBit) {
                can_interrupt_clear(ptCanNode->ulBaseAddr, i + 1);
            }
            
            ulStatus &= ~ulBit;
            if (ulStatus == 0) {                                        /* 剩余报文对象已经没有新数据了 */
                break;
            }
        }
        
        if (ulNewData & ((ptCanNode->ulRmReObjMsk) | (ptCanNode->ulDaReObjMsk))) {
                                                                        /* 收到数据帧或远程帧           */
            ptCanNode->ucNodeState |= CAN_FRAM_RECV;                    /* 收到数据                     */
            ulCallBackMsg |= CAN_FRAM_RECV;
        }
        
        if ((ulTxObjMask & ulMsgObjID) != 0) {                          /* 成功发送数据                 */
            ptCanNode->ucNodeState |= CAN_FRAM_SEND;                    /* 发送完成                     */
            ulCallBackMsg |= CAN_FRAM_SEND;
        }
    }

    /* 检查是否有数据等待发送 */
    ulTxReq  = can_status_get(ptCanNode->ulBaseAddr, CAN_STS_TXREQUEST);
    if ((ulTxReq & ulTxObjMask) == 0) {                                 /* 检查CAN控制器是否可以发送收据*/
        if (ptCanNode->ptCanTxCirBuf != 0) {                            /* 检查是否有数据等待发送       */
            if (can_circulation_buffer_read(ptCanNode->ptCanTxCirBuf, &tCanFrame) == CAN_OK) {
                ptCanNode->ucNodeState &= ~CAN_FRAM_SEND;               /* 缓存区不为空,继续发送        */
                can_frame_send(ptCanNode, &tCanFrame);                    /* 触发下一帧的发送工作         */
            } else {
                ptCanNode->ptCanTxCirBuf    = 0;                        /* 发送队列空闲                 */
            }
        }
    }

    if (ulCallBackMsg) {                                                /* 回调函数的消息类型不为0      */
        if (ptCanNode->pfCanHandlerCallBack) {                          /* 存在回调函数                 */
            ptCanNode->pfCanHandlerCallBack(ulCallBackMsg, ulNewData, ulMsgObjID);
        }
    }
    
    can_interrupt_clear(ptCanNode->ulBaseAddr, CAN_INT_INTID_STATUS);           /* 清除状态中断标志             */
}

/*********************************************************************************************************
** Function name:           can_node_bus_on
** Descriptions:            CAN控制器重新接入总线（清零初始化位,使能相应的中断）
** input parameters:        ptCanNode：指向CAN软件节点的指针
** output parameters:       无
** Returned value:          无
** Modified by:
** Modified date:
** Descriptions:
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void can_node_bus_on(CANNODEINFO *ptCanNode)
{
    if (ptCanNode == 0) {                                               /* 检查节点的有效性             */
        return;
    }
    
    can_enable(ptCanNode->ulBaseAddr);                                   /* 退出初始化模式，启动CAN节点  */
    can_interrupt_clear(ptCanNode->ulBaseAddr, CAN_INT_INTID_STATUS);           /* 清除状态中断标志             */
    can_interrupt_enable(ptCanNode->ulBaseAddr, CAN_INT_MASTER | CAN_INT_ERROR);/* 设置中断源                   */
}

//unsigned char can_data_send(CANFRAME *ptCanFrame)
unsigned char can_data_send(void)
{
    if (can_circulation_buffer_send(GptCanNode0, &GtCanTxCirBuf) == BUSY)
	{
        
		/* 上一帧数据尚未发送完，本帧报文将在发送中断程序中自动完成发送 */
        GptCanNode0->ucNodeState |= CAN_SEND_FAIL;
        return BUSY;
    }

	return CAN_OK;                                                      /* 即时发送                     */
}


