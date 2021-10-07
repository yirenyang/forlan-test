/*
 * can.c - can.c config and achieve;
 *
 * Copyright (c) 2014 Forlan.yung(YANGHUALIANG)
 *
 */

#define CAN_ROOT
#include "include.h"

/*********************************************************************************************************
      ����������
*********************************************************************************************************/
/*********************************************************************************************************
�����ʲ�����
��һ�����μ���λ�����1�ĺͣ�ȡֵ��Χ��2��16
�ڶ����λ�����2��ȡֵ��Χ��1��8
�����ͬ����ת��ȣ�ȡֵ��Χ1��4
�������Ƶֵ��ȡֵ��Χ1��1024
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
    {0, 0, 0, 0},                                                       /* CANBAUD_1M ���޷��ﵽ��      */
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

/* ���ڳ�ʼ��CAN���������� */
const CANFRAME GtCanFrameInit = {
    BUF_BLANK,                                                          /* �հ�֡                       */
    0,                                                                  /* �����򳤶�Ϊ0                */
    0,                                                                  /* ����IDΪ                     */
    {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}                           /* ����������                   */
};

const CANFRAME GtCanFramTest = {                                        /* ����CANͨ��ʱ���͵�����֡    */
    XTD_DATA,                                                           /* ��չ֡                       */
    8,                                                                  /* �����򳤶�Ϊ8                */
    0x123,                                                              /* ����IDΪ0x123                */
    {0x55,0xAA,0x55,0xAA,0x03,0x02,0x01,0x00}                           /* ����������                   */
};


CANFRAME GtCanFrameReBuf[CAN_BUF_RE_LENGTH] = {0};                      /* CANͨ�Ž��ջ�����            */
CANFRAME GtCanFrameTxBuf[CAN_BUF_TX_LENGTH] = {0};                      /* CANͨ�ŷ��ͻ�����            */

CANCIRBUF GtCanReCirBuf = {                                             /* �������ѭ������             */
    0,                                                                  /* ����дָ�루������           */
    0,                                                                  /* �����ָ�루������           */
    false,                                                              /* ��Ƕ���δ��                 */
    CAN_BUF_RE_LENGTH,                                                  /* ��¼�������                 */
    GtCanFrameReBuf                                                     /* ָ�����ݳ�������             */
};

CANCIRBUF GtCanTxCirBuf = {                                             /* ���巢��ѭ������             */
    0,                                                                  /* ����Buffer[]д�±�           */
    0,                                                                  /* ����Buffer[]���±�           */
    false,                                                              /* ��Ƕ���δ��                 */
    CAN_BUF_TX_LENGTH,                                                  /* ��¼�������                 */
    GtCanFrameTxBuf                                                     /* ָ�����ݳ�������             */
};

CANNODEINFO tCanNode0 = CANNODE(LPC_CAN_BASE,                           /* CAN�Ĵ�����ַ                */
	                            CANBAUD_100K,                           /* CAN������                    */
							    RE_DATA_SN,                             /* ��λѡ����������뱨�Ķ���   */
	                            RE_REMOTE_SN,	                        /* ��λѡ�����Զ���뱨�Ķ���   */
							    TX_MSG_SN,		                        /* ���ͱ��Ķ�����             */
								&GtCanReCirBuf,	                        /* ָ�򱾽ڵ�Ľ��ջ�����       */
								0,
								0);


/****************************************************************************
      ����������
****************************************************************************/
static uint8_t can_msg_id = NO_MSG;
static uint16_t can_msg_prm = 0;


/****************************************************************************
      ����������
****************************************************************************/
static void can_hardware_init(void);
static void can_node_state_check(void);


/****************************************************************************
      ����������
****************************************************************************/
/* 12ms:canģ�����غ�������������ģ�����ת */
void can_main(void)
{
    MESSAGE *n_msg;
	CANFRAME can_frame;                                             /* �����ʾCAN֡�ṹ�����      */

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
** Descriptions:            CANӦ�ó�ʼ���������жϷ���������ʼ��CAN���������趨�����ʼ������˲������ȣ�
** input parameters:        ptCanNode    ָ�����CAN�ڵ�ṹ�������ָ��
**                          ulFrameID    ���ĵ�����ID
**                          ulFrameIDMsk ��������ID�����루��ӦλΪ1ʱ����ʾ����ID�Ķ�Ӧλ���������˲���
**                          ucFramType   ���յ�֡���ͣ�
**                             STD_ID_FILTER   ���˽��ձ�׼��ʽ�ı���
**                             EXT_ID_FILTER   ���˽�����չ��ʽ�ı���
**                             STD_EXT_FILTER  ���˽��ձ�׼����չ��ʽ�ı��ģ�ʹ�ô�����
**                                             ʱulFrameID��ulFrameIDMsk������Ϊ��Ч�����������и�ʽ�ı���
**                          pfun         ָ���жϷ������ĺ���ָ��
** output parameters:       ��
** Returned value:          ��
** Created By:
** Created date:
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
uint8_t can_user_init(CANNODEINFO *ptCanNode, unsigned long ulFrameID, unsigned long ulFrameIDMsk, unsigned char ucFramType)
{
    if (ptCanNode == 0) {                                                     /* ���ڵ����Ч��             */
        return CAN_ERROR;
    }
    
    /* Ӳ����ʼ�� */
    LPC_SYSCON->PRESETCTRL |= (0x01 << PRESETCTRL_CAN_RST_N_BIT_OFFSET_VAL);  /* Peripheral reset control     */
    LPC_SYSCON->SYSAHBCLKCTRL |= (0x01 << SYSAHBCLKCTRL_CAN_BIT_OFFSET_VAL);  /* System AHB clock control     */
    LPC_CAN->CLKDIV = CANCLKDIV_DIVIDED_BY_01;                                /* Divided by 1                 */
    
    can_init(ptCanNode->ulBaseAddr);                                          /* ��ʼ��CAN������              */
    can_bit_timing_set(ptCanNode->ulBaseAddr, (CAN_BIT_CLK_PARM *)(&CANBitClkSettings[ptCanNode->ucBaudIndex]));
                                                                              /* �趨�ڵ㲨����               */
    can_enable(ptCanNode->ulBaseAddr);                                        /* �˳���ʼ��ģʽ������CAN�ڵ�  */
    
    /* �����˲����� */
    can_accept_filter_set(ptCanNode, ulFrameID, ulFrameIDMsk, ucFramType);
                                                                              /* �����˲�����                 */
    /* �ж�ʹ�� */
    can_user_interrupt_control(ptCanNode);                                    /* ע���жϷ�������ʹ��CAN�ж�*/

    return CAN_OK;
}

static void can_node_state_check(void)
{
	/* 
	 * ���߽���״̬�ж�
	 */
	if ((GptCanNode0->ucNodeState & CAN_BUS_OFF) && (GptCanNode0->ulBofTimer > 25))
	{
		/* CAN��������������2.5���ڵ��������� */
		can_node_bus_on(GptCanNode0);
		/* ������߱�־ */
		GptCanNode0->ucNodeState &= ~CAN_BUS_OFF;
	}

	/* 
	 * ���ͳɹ�	
	 */
	if (GptCanNode0->ucNodeState & CAN_FRAM_SEND) 
	{
		/* �������, ���������ɱ� */
		GptCanNode0->ucNodeState &= ~CAN_FRAM_SEND;
	}

	/* 
	 *  ����ʧ��	
	 */
	if (GptCanNode0->ucNodeState & CAN_SEND_FAIL)
	{
		/* ����ʧ��, �������ʧ�ܱ�־ */
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
** Descriptions:            ��ʼ��֡�������FIFO
** input parameters:        ptBuf      ָ�����ѭ�����е�ָ��
** output parameters:       ��
** Returned value:          ��
** Created By:
** Created date:            2008.09.03
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:           2009.04.29
** Descriptions:            ��֡���͸�ʽ��ʼ��ΪBUF_BLANK�����ڷ�ֹ���
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void can_circulation_buffer_init(CANCIRBUF *ptCanCirBuf, CANFRAME *ptCanFrameBuf, uint8_t ucLength)
{
    unsigned int i;
    
    ptCanCirBuf->ulWriteIndex    = 0;                                   /* Buffer[]д�±�����           */
    ptCanCirBuf->ulReadIndex     = 0;                                   /* Buffer[]���±�����           */
    ptCanCirBuf->bIsFull         = false;                               /* ѭ�����в���                 */
    ptCanCirBuf->ulLength        = ucLength;                            /* ��¼����,��ֵ�����������    */
    ptCanCirBuf->ptCanFramBuf    = ptCanFrameBuf;                       /* ָ�����ݻ������׵�ַ         */

    for (i = 0; i < ucLength; i++)
    {
        ptCanCirBuf->ptCanFramBuf[i] = GtCanFrameInit;                  /* ��ʼ��Ϊ��֡                 */
    }
}

/*********************************************************************************************************
** Function name:           can_circulation_buffer_malloc
** Descriptions:            ��ѭ�����У����FIFO������һ��֡�������� ֡���͸�ʽ������ʼ��ΪBUF_BLANK
** input parameters:        ptBuf          ָ��ѭ�����е�ָ��
** output parameters:       ��
** Returned value:          ptCanFrame     ֡�����ַ����Ϊ0���ʾѭ��������
** Created By:
** Created date:
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:            ����ٽ�������
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
static CANFRAME *can_circulation_buffer_malloc(CANCIRBUF *ptCanCirBuf)
{
    CANFRAME  *ptCanFrame;
    unsigned char ucEnable = 0;
    
    if (ptCanCirBuf == (CANCIRBUF *)0)
    {
        return 0;                                                       /* ���д���                     */
    }
    if (ptCanCirBuf->bIsFull == true)
    {
        return 0;                                                       /* ������,�򷵻� 0              */
    }
    
    ucEnable = __ENTER_CIRTICAL();                                      /* �����ٽ���                   */
    ptCanFrame = &(ptCanCirBuf->ptCanFramBuf[ptCanCirBuf->ulWriteIndex++]);
                                                                        /* ȡ����Ҫ���صĵ�ַ           */
    if (ptCanCirBuf->ulWriteIndex == ptCanCirBuf->ulLength)
    {
        ptCanCirBuf->ulWriteIndex = 0;                                  /* ����ѭ������                 */
    }
    if (ptCanCirBuf->ulWriteIndex == ptCanCirBuf->ulReadIndex)          /* дָ����϶�ָ�룬������     */
    {
        ptCanCirBuf->bIsFull = true;                                    /* ��λ��������־               */
    }
    __EXIT_CIRTICAL(ucEnable);                                          /* �˳��ٽ���                   */
    
    *ptCanFrame = GtCanFrameInit;                                       /* ��ʼ������Ĵ洢�ռ�         */
    return ptCanFrame;
}

/*********************************************************************************************************
** Function name:           can_circulation_buffer_read
** Descriptions:            ��ѭ�����ж�ȡһ֡����
** input parameters:        ptCanBuf       ָ��ѭ�����е�ָ��
** output parameters:       ptFrame        �������ָ��
** Returned value:          EMPTY          ѭ������Ϊ�գ�ѭ���������޿�������
**                          NOT_EMPTY      ѭ�����зǿ�
**                          CAN_ERROR           ѭ�����д��󣬲���ʧ��
** Created By:
** Created date:
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:            ����ٽ����������������
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
uint8_t can_circulation_buffer_read(CANCIRBUF *ptCanCirBuf, CANFRAME  *ptCanFrame)
{
    uint8_t  ucReturn = CAN_ERROR;
    unsigned long ulIndex;
    unsigned char ucEnable = 0;
    
    if (ptCanCirBuf == (CANCIRBUF *)0) {
        return CAN_ERROR;                                               /* ���д���                     */
    }
    
    ucEnable = __ENTER_CIRTICAL();                                      /* �����ٽ���                   */
    
    if ((ptCanCirBuf->ulReadIndex != ptCanCirBuf->ulWriteIndex) || (ptCanCirBuf->bIsFull == true)) {
        ulIndex = ptCanCirBuf->ulReadIndex;                             /* �����±�                     */
        if (ptCanCirBuf->ptCanFramBuf[ulIndex].ucTtypeFormat != BUF_BLANK) {
            //֡�������֡д����֮ǰucTtypeFormat = BUF_BLANK��
            *ptCanFrame = ptCanCirBuf->ptCanFramBuf[ulIndex];
            ptCanCirBuf->ulReadIndex += 1;                              /* ��ָ���1                    */
            if (ptCanCirBuf->ulReadIndex == ptCanCirBuf->ulLength) {
                ptCanCirBuf->ulReadIndex = 0;                           /* �γɻ��λ�����               */
            }
            ptCanCirBuf->bIsFull = false;                               /* ���㻺��������־             */
            ucReturn = CAN_OK;
        }
    }
    __EXIT_CIRTICAL(ucEnable);                                          /* �˳��ٽ���                   */
    
    return ucReturn;
}

/*********************************************************************************************************
** Function name:           can_circulation_buffer_write
** Descriptions:            ��ѭ������дһ֡����
** input parameters:        ptCanBuf   ָ��ѭ�����е�ָ��
** output parameters:       ptFrame    �������ָ��
** Returned value:          CAN_OK    �����ɹ�
**                          CAN_ERROR       ����ʧ��
** Created By:
** Created date:
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:            ��֡���͸�ʽ�ı���ŵ��������������ֹ���
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
uint8_t can_circulation_buffer_write(CANCIRBUF *ptCanCirBuf, CANFRAME *ptCanFrame)
{
    CANFRAME *ptCanFrameObject;
    uint8_t i = 0;
    
    ptCanFrameObject = can_circulation_buffer_malloc(ptCanCirBuf);                    /* �ӻ���������һ֡���ĵĴ洢   */
                                                                        /* �ռ�                         */
    if (ptCanFrameObject == (CANFRAME *)0) {                            /* ������δ��������ɹ�         */
        return CAN_ERROR;
    }
    ptCanFrameObject->ucDLC = ptCanFrame->ucDLC;                        /* �������ݳ�����               */
    ptCanFrameObject->ulID  = ptCanFrame->ulID;                         /* ����ID����־�ַ���           */
    for (i= 0; i < CAN_DATA_LENGTH; i++) {
        ptCanFrameObject->ucDatBuf[i] = ptCanFrame->ucDatBuf[i];        /* �������ݳ�����               */
    }
    ptCanFrameObject->ucTtypeFormat = ptCanFrame->ucTtypeFormat;        /* д�������ͣ�ʹ��֡������Ч   */
    return CAN_OK;                                                      /* ���ز����ɹ�                 */
}

/*********************************************************************************************************
** Function name:           can_node_create
** Descriptions:            ��ʼ��һ������CAN�ڵ���Ϣ�Ľṹ�����
** input parameters:        ptCanNode:ָ��ڵ�ṹ��ָ��
**                          ulBaseAddr:�ڵ��Ӧ��CAN��������ַ
**                          ulBaudIn:�ڵ�ͨ�Ų����ʣ������ʱ��������
**                          ulDaReObjMsk:��λѡͨ���ڽ�������֡�ı��Ķ���
**                          ulRmReObjMsk:��λѡͨ���ڽ���Զ��֡�ı��Ķ���
**                          ulTxMsgObjNr:���͵ı��ı��
**                          ptRecvList:ָ�򱾽ڵ�Ľ���"����"������ṹ��
**                          pfCanHandlerCallBack:ָ��canHandler()�ص�������ָ��
** output parameters:       *ptCanNode����ʼ��
** Returned value:          ��
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
    if (ptCanNode == 0) {                                               /* ���ڵ����Ч��             */
        return;
    }
    // ���������ʼ��
    ptCanNode->ulBaseAddr    = ulBaseAddr;                              /* CAN����������ַ              */
    ptCanNode->ucNodeState   = CAN_NO_ERROR;
    ptCanNode->ucBaudIndex   = ucBaudIndex;                             /* CAN����������������          */
    ptCanNode->ulBofTimer    = 0;
    
    ptCanNode->ulDaReObjMsk  = ulDaReObjMsk;                            /* ��������֡���Ķ���           */
    ptCanNode->ulRmReObjMsk  = ulRmReObjMsk;
    ptCanNode->ulTxMsgObjNr  = ulTxMsgObjNr;                            /* ���ͱ��Ķ���                 */
    
    ptCanNode->ptCanReCirBuf = ptReCirBuf;                              /* ָ�������������             */
    ptCanNode->ptCanTxCirBuf = 0;                                       /* ��շ�����������             */
    
    ptCanNode->pfCanHandlerCallBack = pfCanHandlerCallBack;             /* ��ʼ���ص�����               */
    ptCanNode->pfIsrHandler = pfIsrHandler;                             /* �жϷ�����                 */
}

/*********************************************************************************************************
** Function name:           can_node_call_back_set
** Descriptions:            ���ýڵ�ص�����
** input parameters:        ptCanNode              ָ��ڵ�ṹ��ָ��
**                          pfCanHandlerCallBack      ָ��ص������ĺ���ָ��
** output parameters:       ��
** Returned value:          ��
** Created By:
** Created date:
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void can_node_call_back_set(CANNODEINFO *ptCanNode, void (*pfCanHandlerCallBack)(unsigned long ulMessage, long lParam1, long lParam2))
{
    if (ptCanNode == 0) {                                               /* ���ڵ����Ч��             */
        return;
    }
    ptCanNode->pfCanHandlerCallBack = pfCanHandlerCallBack;
}

/*********************************************************************************************************
** Function name:           can_frame_send
** Descriptions:            ����һ֡CAN����������
** input parameters:        pCAN           ָ���ͱ��Ľṹ��ָ��
**                          pFrame         ���ݿ�ָ��
** output parameters:       ��
** Returned value:          ��
** Created By:
** Created date:
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:            ����Զ��֡���͹���
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void can_frame_send(CANNODEINFO *ptCanNode, CANFRAME *ptCANFrame)
{
    CAN_MSG_OBJ tMsgObjectTx;
    unsigned char ucEnable = 0;
    if (ptCanNode == 0) {                                               /* ���ڵ����Ч��             */
        return;
    }
    
    ucEnable = __ENTER_CIRTICAL();                                      /* �����ٽ���                   */
    tMsgObjectTx.ulMsgID = ptCANFrame->ulID;                            /* ȡ�ñ��ı�ʶ��               */
    
    if ((ptCANFrame->ucTtypeFormat & XTD_MASK) != 0){
        tMsgObjectTx.ulFlags = MSG_OBJ_EXTENDED_ID;                     /* ��չ��ʽ֡                   */
    } else {
        tMsgObjectTx.ulFlags = MSG_OBJ_NO_FLAGS;                        /* ��׼��ʽ֡                   */
    }
    
    tMsgObjectTx.ulFlags |= MSG_OBJ_TX_INT_ENABLE;                      /* ��Ƿ����ж�ʹ��             */
    tMsgObjectTx.ulMsgLen = (unsigned long)ptCANFrame->ucDLC;           /* ��������򳤶�               */
    tMsgObjectTx.pucMsgData = ptCANFrame->ucDatBuf;                     /* �������ݴ��ָ��             */
    can_retry_set(ptCanNode->ulBaseAddr, true);                         /* ��������ʧ���ط�             */

    if ((ptCANFrame->ucTtypeFormat & RMRQS_MASK) != 0) {
        can_message_set(ptCanNode->ulBaseAddr,                          /* CAN��������ַ                */
        ptCanNode->ulTxMsgObjNr,                                        /* ���ͱ��Ķ�����             */
        &tMsgObjectTx, MSG_OBJ_TYPE_TX_REMOTE);                         /* ����Զ��֡���ͱ��Ķ���       */
    } else {
        can_message_set(ptCanNode->ulBaseAddr,                          /* CAN��������ַ                */
        ptCanNode->ulTxMsgObjNr,                                        /* ���ͱ��Ķ�����             */
        &tMsgObjectTx, MSG_OBJ_TYPE_TX);                                /* ��������֡���ͱ��Ķ���       */
    }
    __EXIT_CIRTICAL(ucEnable);                                          /* �˳��ٽ���                   */
}

/*********************************************************************************************************
** Function name:        can_read_message_object_set
** Descriptions:         ���ý�������֡��Զ��֡�ı��Ķ���,��ѡͨ������Ķ����򽫱��Ķ�������FIFO������
** input parameters:     ulBaseAddr      CANģ���ַ
**                       ulMsgObjMask    ��λѡͨҪ���õı��Ķ���
**                       ulFrameID       ����֡ID
**                       ulFrameIDMsk   ����֡������
**                       ucFramType      STD_ID_FILTER    ���˽��ձ�׼��ʽ�ı���
**                                       EXT_ID_FILTER    ���˽�����չ��ʽ�ı���
**                                       STD_EXT_FILTER   ���˽��ձ�׼����չ��ʽ�ı��ģ���ʹ��ID����
**                       ucMsgType       MSG_OBJ_TYPE_RX          ���ձ��Ķ���
**                                       MSG_OBJ_TYPE_RX_REMOTE   ����Զ��֡���Ķ���
** output parameters:    ��
** Returned value:       ��
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
    
    
    if (ptCanNode == 0) {                                               /* ���ڵ����Ч��             */
        return;
    }
    
    ptCanBase   = (LPC_CAN_TypeDef *)(ptCanNode->ulBaseAddr);
    
    if (ulMsgObjMask == 0) {
        return;                                                         /* û��ѡ�����Ķ���             */
    }
    
    if (ucMsgType == MSG_OBJ_TYPE_RX) {                                 /* ����֡���ձ��Ķ���           */
        ptCanNode->ulDaReObjMsk |= ulMsgObjMask;                        /* ��λ��ǽ��ձ��Ķ���         */
    } else if (ucMsgType == MSG_OBJ_TYPE_RX_REMOTE){                    /* Զ��֡���Ľ��ն���           */
        ptCanNode->ulRmReObjMsk |= ulMsgObjMask;                        /* ��λ���"����"���Ķ���       */
    } else {
        return;                                                         /* �����Ƿ���ֱ���˳��˺���     */
    }
    
    tMsgObj.ulMsgID = ulFrameID;                                        /* �����˲�ID                   */
    tMsgObj.ulMsgIDMask = ulFrameIDMsk;                                 /* ID����*/ /* ���ձ��Ķ����� */
    switch (ucFramType) {                                               /* ֡���ʹ���                   */
        case STD_ID_FILTER: {                                           /* ��׼֡                       */
            tMsgObj.ulFlags = (MSG_OBJ_RX_INT_ENABLE |                  /* ��������ж�                 */
            MSG_OBJ_USE_ID_FILTER |                                     /* ʹ�ñ���ID�˲�               */
            MSG_OBJ_USE_EXT_FILTER |                                    /* Xtd�����˲�                  */
            MSG_OBJ_USE_DIR_FILTER);                                    /* Dir�����˲�                  */
            bUseExtendedID = false;                                     /* ������չ֡                   */
            break;
        }
        case EXT_ID_FILTER: {                                           /* ��չ֡                       */
            tMsgObj.ulFlags = (MSG_OBJ_RX_INT_ENABLE |                  /* ��������ж�                 */
            MSG_OBJ_EXTENDED_ID |                                       /* ��չID                       */
            MSG_OBJ_USE_ID_FILTER |                                     /* ʹ�ñ���ID�˲�               */
            MSG_OBJ_USE_EXT_FILTER |                                    /* Xtd�����˲�                  */
            MSG_OBJ_USE_DIR_FILTER);                                    /* Dir�����˲�                  */
            bUseExtendedID = true;                                      /* ����չ֡                     */
            break;
        }
        case STD_EXT_FILTER: {                                          /* ֻ�Խ��ձ��Ķ���������       */
            tMsgObj.ulFlags = (MSG_OBJ_RX_INT_ENABLE |                  /* ��������ж�                 */
            MSG_OBJ_USE_ID_FILTER |                                     /* ʹ�ñ���ID�˲�               */
            MSG_OBJ_USE_DIR_FILTER);                                    /* Dir�����˲�                  */
            ulFrameIDMsk   = 0x00000000UL;                              /* ����ID���н����˲�           */
            bUseExtendedID = false;                                     /* ������չ֡(����ûӰ��)       */
            break;
        }
        default: {
            return;
        }
    }
    
    
    
    tMsgObj.pucMsgData = ucDataBuf;                                     /* ָ�����ݴ洢�ռ�             */
    tMsgObj.ulMsgLen = 8;                                               /* ���������򳤶�               */
    while(__canRegRead((unsigned long)&ptCanBase->IF1_CMDREQ) & CAN_IF1CRQ_BUSY) {;}
                                                                        /* �ȴ����Ĵ���������           */
    
    usCmdMaskReg = CAN_IF1CMSK_WRNRD |                                  /* д���ݵ����Ķ���洢��       */
    CAN_IF1CMSK_DATAA |                                                 /* ���������ֽ� 0��3            */
    CAN_IF1CMSK_DATAB |                                                 /* ���������ֽ� 4��7            */
    CAN_IF1CMSK_CONTROL |                                               /* �������λ                   */
    CAN_IF1CMSK_ARB;                                                    /* ����ID+Dir+Xtd+MsgVal��MsgObj*/
    
    usArbReg[0] = 0;
    usMsgCtrl = 0;
    usMaskReg[0] = 0;
    usMaskReg[1] = 0;
    
    switch(ucMsgType) {                                                 /* ���Ķ������ʹ���             */
        case MSG_OBJ_TYPE_RX: {                                         /* ��������֡����               */
            usArbReg[1] = 0;
            break;
        }
        case MSG_OBJ_TYPE_RX_REMOTE: {                                  /* ����Զ��֡����               */
            usArbReg[1] = CAN_IF1ARB2_DIR;                              /* ��λ���ķ���λ,���ͷ���      */
            usMsgCtrl = CAN_IF1MCTL_UMASK;                              /* Msk��MXtd��MDir���ڽ����˲�  */
            usMaskReg[0] = 0xffff;
            usMaskReg[1] = 0x1fff;
            usCmdMaskReg |= CAN_IF1CMSK_MASK;
            break;
        }
        default: {
            return;
        }
    }
    
    if(tMsgObj.ulFlags & MSG_OBJ_USE_ID_FILTER) {                       /* ʹ�ñ���ID�˲�               */
        if(bUseExtendedID) {                                            /* ��չ֡                       */
            usMaskReg[0] = ulFrameIDMsk & CAN_IF1MSK1_IDMSK_M;
            usMaskReg[1] = (ulFrameIDMsk >> 16) & CAN_IF1MSK2_IDMSK_M;
        } else {                                                        /* ��׼֡                       */
            usMaskReg[0] = 0;                                           /* ��ʮ��λMSK[15:0]Ϊ0         */
            usMaskReg[1]  = (ulFrameIDMsk << 2) & CAN_IF1MSK2_IDMSK_M;  /* MSK[28:18]Ϊ��׼֡ID MSK     */
        }
    }
    
    if((tMsgObj.ulFlags & MSG_OBJ_USE_EXT_FILTER) ==  MSG_OBJ_USE_EXT_FILTER) {
        usMaskReg[1] |= CAN_IF1MSK2_MXTD;                               /* ��չ��ʶ��Xtd���������˲�    */
    }
    
    if((tMsgObj.ulFlags & MSG_OBJ_USE_DIR_FILTER) == MSG_OBJ_USE_DIR_FILTER) {
        usMaskReg[1] |= CAN_IF1MSK2_MDIR;                               /* ���ķ���Dir���������˲�      */
    }
    
    if(tMsgObj.ulFlags & (MSG_OBJ_USE_ID_FILTER | MSG_OBJ_USE_DIR_FILTER | MSG_OBJ_USE_EXT_FILTER)) {
        usMsgCtrl |= CAN_IF1MCTL_UMASK;                                 /* Msk��MXtd��MDir���ڽ����˲�  */
        usCmdMaskReg |= CAN_IF1CMSK_MASK;                               /* ����IDMask+Dir+Mxtd ��MsgObj */
    }
    
    if(bUseExtendedID) {                                                /* ��չ֡����ID                 */
        usArbReg[0] |= ulFrameID & CAN_IF1ARB1_ID_M;
        usArbReg[1] |= (ulFrameID >> 16) & CAN_IF1ARB2_ID_M;
        usArbReg[1] |= CAN_IF1ARB2_MSGVAL | CAN_IF1ARB2_XTD;
    }  else {                                                           /* ��׼֡����ID                 */
        usArbReg[0] = 0;
        usArbReg[1] |= (ulFrameID << 2) & CAN_IF1ARB2_ID_M;
        usArbReg[1] |= CAN_IF1ARB2_MSGVAL;
    }
    
    usMsgCtrl |= (tMsgObj.ulMsgLen & CAN_IF1MCTL_DLC_M) | CAN_IF1MCTL_EOB;
                                                                        /* Eob = 1                      */
    if(tMsgObj.ulFlags & MSG_OBJ_RX_INT_ENABLE) {
        usMsgCtrl |= CAN_IF1MCTL_RXIE;                                  /* ʹ�ܽ����ж�                 */
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
                                                                        /* ���µ����Ķ���               */
            while(__canRegRead((unsigned long)&ptCanBase->IF1_CMDREQ) & CAN_IF1CRQ_BUSY) {
                ;                                                       /* �ȴ����Ĵ���������           */
            }
        }
        ulMsgObjMask = ulMsgObjMask << 1;                               /* ���α��Ķ�������ѡ��         */
        if (ulMsgObjMask == 0) {
            break;                                                      /* ��ǰ�˳�ѭ��                 */
        }
    }
    return;
}

/*********************************************************************************************************
** Function name:           can_accept_filter_set
** Descriptions:            �����˲�����
** input parameters:        ptCanNode       ָ��ڵ��ָ��
**                          ulFrameID       ����֡ID
**                          ulFrameIDMsk   ����֡ID������
**                          ucFramType      STD_ID_FILTER    ���˽��ձ�׼��ʽ�ı���
**                                          EXT_ID_FILTER    ���˽�����չ��ʽ�ı���
**                                          STD_EXT_FILTER   ���˽��ձ�׼����չ��ʽ�ı��ģ���ʹ��ID����
** output parameters:       ��
** Returned value:          ��
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
    /* ���ڵ����Ч�� */
    if (ptCanNode == 0)
    {
        return;
    }

    /* ��������֡���ձ��Ķ��� */
    can_read_message_object_set(ptCanNode, ptCanNode->ulDaReObjMsk, ulFrameID, ulFrameIDMsk, ucFramType, MSG_OBJ_TYPE_RX);

    /* ����Զ��֡���ձ��Ķ��� */
    can_read_message_object_set(ptCanNode, ptCanNode->ulRmReObjMsk, ulFrameID, ulFrameIDMsk, ucFramType, MSG_OBJ_TYPE_RX_REMOTE);
}

/*********************************************************************************************************
** Function name:           can_user_interrupt_control
** Descriptions:            ʹ��CAN�ж�
** input parameters:        pCAN           ָ��ڵ��ָ��
** output parameters:       ��
** Returned value:          ��
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
    
    if(ptCanNode == 0) {                                                /* �ڵ���Ч���ж�               */
        return ;
    }
    
    if (ptCanNode->pfIsrHandler) {                                      /* �жϷ�����������ע��ISR    */
        can_interrupt_register(ptCanNode->ulBaseAddr, ptCanNode->pfIsrHandler);
    } else {
        ulIntNum = __canIntNumberGet(ptCanNode->ulBaseAddr);
        IntEnable(ulIntNum);                                            /* ʹ��CAN�ڵ��ж�(to CPU)      */
    }
    can_interrupt_enable(ptCanNode->ulBaseAddr, CAN_INT_MASTER | CAN_INT_ERROR);
                                                                        /* ��������жϼ������жϲ�ʹ�� */
                                                                        /* CAN �������ж�Դ             */
}

/*********************************************************************************************************
** Function name:           can_circulation_buffer_send
** Descriptions:            ����ָ��ѭ�������е�֡���ݵķ��͹���
** input parameters:        ptBuf  ָ��ѭ�����е�ָ��
** global variable:         GptCanCirBuf:�����͵Ļ�������ڵ�ַ
**                          GbCanCirBufSend:��־�Ƿ񽫻��������ݷ��ͳ�ȥ
** Returned value:          EMPTY         ����Ϊ��
**                          NOT_EMPTY     ���治��
**                          CAN_ERROR          ѭ�����д��󣬲���ʧ��
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
    
    if (ptCanNode == 0) {                                               /* ���ڵ����Ч��             */
        return CAN_ERROR;
    }
    
    if (ptCanNode->ptCanTxCirBuf != (CANCIRBUF *)0) {                   /* ����"������"�ڷ��Ͷ���       */
        return BUSY;
    }
                                                                        /* ����Ҫ���͵�CAN�ڵ�          */
    if (can_circulation_buffer_read(ptCanCirBuf, &tCanFrame) != CAN_OK) {             /* ��������Ϊ��,��������        */
        return CAN_ERROR;
    }
    
    ucEnable = __ENTER_CIRTICAL();                                      /* �����ٽ���                   */
    ptCanNode->ptCanTxCirBuf = ptCanCirBuf;                             /* ��Ҫ���͵Ļ������׵�ַ����   */
    ptCanNode->ucNodeState &= ~CAN_FRAM_SEND;                           /* ״̬����Ϊ������δ��ɡ�     */
    can_frame_send(ptCanNode, &tCanFrame);                                /* ����һ֡���ݣ��������ݽ�     */
                                                                        /* ���ж��м�������             */
    __EXIT_CIRTICAL(ucEnable);                                          /* �˳��ٽ���                   */
    return CAN_OK;                                                      /* ���ز������                 */
}

/*********************************************************************************************************
** Function name:           isr_can
** Descriptions:            ʵ���жϽ���һ֡���֡CAN���ģ��Լ����ͳɹ��ı�־����
** input parameters:        ptCanNode��ָ��CAN����ڵ��ָ��
** output parameters:       ��
** Returned value:          ��
** Modified by:
** Modified date:
** Descriptions:            CAN�жϴ�����
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
                                                                        /* ��ȡ�жϱ�־,���ڷ���״̬�ж�*/
    ulStatus   = can_status_get(ptCanNode->ulBaseAddr, CAN_STS_CONTROL);
    ulNewData  = can_status_get(ptCanNode->ulBaseAddr, CAN_STS_NEWDAT);
    ulTxReq    = can_status_get(ptCanNode->ulBaseAddr, CAN_STS_TXREQUEST);
    ulNewData &= ~ulTxObjMask;                                          /* ���Է��ͱ��Ķ����NewDat     */
    
    if (ulStatus & CAN_STATUS_LEC_MSK ) {
        ptCanNode->ucNodeState |= CAN_SEND_FAIL;                        /* ����ʧ��,��������˴���      */
    } else {
        ptCanNode->ucNodeState &= ~CAN_SEND_FAIL;                       /* ͨ�ųɹ�����������־       */
    }
    
    if (ulStatus & CAN_STATUS_BUS_OFF) {
        can_interrupt_disable(ptCanNode->ulBaseAddr, CAN_INT_MASTER | CAN_INT_ERROR);
                                                                        /* �ر�CAN�ж�                  */
        ptCanNode->ucNodeState |= CAN_BUS_OFF;                          /* ��������                     */
        ptCanNode->ulBofTimer = 0;
        
        ulCallBackMsg |= CAN_BUS_OFF;                                   /* ��������                     */
    }
    
    ulStatus = ulNewData;
    if (ulMsgObjID != 0) {                                              /* ���ڹ����ж�                 */
        for (i = 0; i < 32; i++) {
            ulBit = 1UL << i;
            if ((ptCanNode->ulDaReObjMsk & ulNewData & ulBit) != 0){    /* �յ�����֡                   */
                ptCanFrame = can_circulation_buffer_malloc(ptCanNode->ptCanReCirBuf); /* ȡ�û����ַ                 */
                if (ptCanFrame == (CANFRAME *)0) {                      /* ��������ʧ��,˵������������  */
                    ptCanFrame = &tCanFrame;                            /* �þֲ��������л���,��������  */
                }
                tMsgObjBuf.pucMsgData = ptCanFrame->ucDatBuf;           /* ����֡���ݻ����ַ           */
                can_message_get(ptCanNode->ulBaseAddr, (i + 1), &tMsgObjBuf, 0);
                                                                        /* ������������                 */
                ptCanFrame->ucDLC = tMsgObjBuf.ulMsgLen;                /* ��¼���ݳ�����               */
                if (tMsgObjBuf.ulFlags & MSG_OBJ_EXTENDED_ID) {         /* ��չ֡ 29 λ��־�ַ�         */
                    ptCanFrame->ulID = (tMsgObjBuf.ulMsgID & 0x1FFFFFFF);
                                                                        /* ��¼CAN����ID                */
                    ptCanFrame->ucTtypeFormat = XTD_DATA;               /* ��¼Ϊ��չ����֡             */
                } else {                                                /* ��׼֡ 11 λ��־�ַ�         */
                    ptCanFrame->ulID = (tMsgObjBuf.ulMsgID & 0x000007FF);
                                                                        /* ��¼CAN����ID                */
                    ptCanFrame->ucTtypeFormat = STD_DATA;               /* ��¼Ϊ��׼����֡             */
                }
            } else if ((ptCanNode->ulRmReObjMsk & ulNewData & ulBit) != 0) {
                                                                        /* �յ�Զ��֡                   */
                ptCanFrame = can_circulation_buffer_malloc(ptCanNode->ptCanReCirBuf); /* ȡ�û����ַ                 */
                if (ptCanFrame == (CANFRAME *)0) {                      /* ��������ʧ��,˵������������  */
                    ptCanFrame = &tCanFrame;                            /* �þֲ��������л���,��������  */
                }
                tMsgObjBuf.pucMsgData = ptCanFrame->ucDatBuf;           /* ����֡���ݻ����ַ           */
                can_message_get(ptCanNode->ulBaseAddr, (i + 1), &tMsgObjBuf, 0);
                ptCanFrame->ucDLC = tMsgObjBuf.ulMsgLen;                /* ��¼���ݳ�����               */
                
                if (tMsgObjBuf.ulFlags & MSG_OBJ_EXTENDED_ID) {         /* ��չ֡ 29 λ��־�ַ�         */
                    ptCanFrame->ulID = (tMsgObjBuf.ulMsgID & 0x1FFFFFFF);
                    ptCanFrame->ucTtypeFormat = XTD_RMRQS;              /* ��¼Ϊ��չԶ��֡             */
                } else {                                                /* ��׼֡ 11 λ��־�ַ�         */
                    ptCanFrame->ulID = (tMsgObjBuf.ulMsgID & 0x000007FF);
                    ptCanFrame->ucTtypeFormat = STD_RMRQS;              /* ��¼Ϊ��׼Զ��֡             */
                }
            }
            
            ulStatus &= ~ulBit;
            if (ulStatus == 0) {                                        /* ʣ�౨�Ķ����Ѿ�û���������� */
                break;
            }
        }
        
        ulStatus = ulMsgObjID;
        for (i = 0; i < 32; i++) {                                      /* ����жϱ�־                 */
            ulBit = 1UL << i;
            if (ulMsgObjID & ulBit) {
                can_interrupt_clear(ptCanNode->ulBaseAddr, i + 1);
            }
            
            ulStatus &= ~ulBit;
            if (ulStatus == 0) {                                        /* ʣ�౨�Ķ����Ѿ�û���������� */
                break;
            }
        }
        
        if (ulNewData & ((ptCanNode->ulRmReObjMsk) | (ptCanNode->ulDaReObjMsk))) {
                                                                        /* �յ�����֡��Զ��֡           */
            ptCanNode->ucNodeState |= CAN_FRAM_RECV;                    /* �յ�����                     */
            ulCallBackMsg |= CAN_FRAM_RECV;
        }
        
        if ((ulTxObjMask & ulMsgObjID) != 0) {                          /* �ɹ���������                 */
            ptCanNode->ucNodeState |= CAN_FRAM_SEND;                    /* �������                     */
            ulCallBackMsg |= CAN_FRAM_SEND;
        }
    }

    /* ����Ƿ������ݵȴ����� */
    ulTxReq  = can_status_get(ptCanNode->ulBaseAddr, CAN_STS_TXREQUEST);
    if ((ulTxReq & ulTxObjMask) == 0) {                                 /* ���CAN�������Ƿ���Է����վ�*/
        if (ptCanNode->ptCanTxCirBuf != 0) {                            /* ����Ƿ������ݵȴ�����       */
            if (can_circulation_buffer_read(ptCanNode->ptCanTxCirBuf, &tCanFrame) == CAN_OK) {
                ptCanNode->ucNodeState &= ~CAN_FRAM_SEND;               /* ��������Ϊ��,��������        */
                can_frame_send(ptCanNode, &tCanFrame);                    /* ������һ֡�ķ��͹���         */
            } else {
                ptCanNode->ptCanTxCirBuf    = 0;                        /* ���Ͷ��п���                 */
            }
        }
    }

    if (ulCallBackMsg) {                                                /* �ص���������Ϣ���Ͳ�Ϊ0      */
        if (ptCanNode->pfCanHandlerCallBack) {                          /* ���ڻص�����                 */
            ptCanNode->pfCanHandlerCallBack(ulCallBackMsg, ulNewData, ulMsgObjID);
        }
    }
    
    can_interrupt_clear(ptCanNode->ulBaseAddr, CAN_INT_INTID_STATUS);           /* ���״̬�жϱ�־             */
}

/*********************************************************************************************************
** Function name:           can_node_bus_on
** Descriptions:            CAN���������½������ߣ������ʼ��λ,ʹ����Ӧ���жϣ�
** input parameters:        ptCanNode��ָ��CAN����ڵ��ָ��
** output parameters:       ��
** Returned value:          ��
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
    if (ptCanNode == 0) {                                               /* ���ڵ����Ч��             */
        return;
    }
    
    can_enable(ptCanNode->ulBaseAddr);                                   /* �˳���ʼ��ģʽ������CAN�ڵ�  */
    can_interrupt_clear(ptCanNode->ulBaseAddr, CAN_INT_INTID_STATUS);           /* ���״̬�жϱ�־             */
    can_interrupt_enable(ptCanNode->ulBaseAddr, CAN_INT_MASTER | CAN_INT_ERROR);/* �����ж�Դ                   */
}

//unsigned char can_data_send(CANFRAME *ptCanFrame)
unsigned char can_data_send(void)
{
    if (can_circulation_buffer_send(GptCanNode0, &GtCanTxCirBuf) == BUSY)
	{
        
		/* ��һ֡������δ�����꣬��֡���Ľ��ڷ����жϳ������Զ���ɷ��� */
        GptCanNode0->ucNodeState |= CAN_SEND_FAIL;
        return BUSY;
    }

	return CAN_OK;                                                      /* ��ʱ����                     */
}


