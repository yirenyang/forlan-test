/*
 * mpu_rx.c - mpu_rx.c config and achieve;
 *
 * Copyright (c) 2014 Forlan.yung(YANGHUALIANG)
 *
 */

#include "include.h"

static MSGQUEUE msg_queue[NUM_OF_MSG_QUEUE];


//��ָ������Ϣ�ŵ���Ϣ������
//�����Ϣ�����������򽫸���Ϣ����
extern void post_message(MSG_MODULE module, MESSAGE_ID id, uint16_t param)
{
    MESSAGE msg;
    uint8_t enque;
    uint8_t deque;
    bool b_full;

    msg.id = id;
    msg.prm = param;

    enque = (uint8_t)(msg_queue[module].n_enque & 0x7F);
    b_full = (uint8_t)(msg_queue[module].n_enque & 0x80);
    deque = (uint8_t)(msg_queue[module].n_deque & 0x7F);

    if (b_full == 0)
    {
        msg_queue[module].queue[enque] = msg;
        enque++;
        if (enque >= QUEUE_LENGTH)  /* ע�⣬QUEUE_LENGTH��Ҫ����0x7f */
        {
            enque = 0;
        }
        if (enque == deque)
        {
            b_full = true;
        }
    }
    if (b_full)
    {
        SetBit(enque, 7);
    }
    msg_queue[module].n_enque = enque;
    msg_queue[module].n_deque = deque;

    return;
}

//��ָ������Ϣ�ŵ���Ϣ������
//�ڷ���֮ǰ�����Ȳ�ѯ������������ͬ����Ϣ
//����У����ٷ��롣
//�����Ϣ�����������򽫸���Ϣ����
extern void post_new_message(MSG_MODULE module, MESSAGE_ID id, uint16_t param)
{
    MESSAGE msg;
    uint8_t enque, deque, i;
    bool b_full;

    msg.id = id;
    msg.prm = param;

    enque = (uint8_t)(msg_queue[module].n_enque & 0x7F);
    b_full = (uint8_t)(msg_queue[module].n_enque & 0x80);
    deque = (uint8_t)(msg_queue[module].n_deque & 0x7F);

    if (b_full == 0)
    {
        i = deque;
        while (i != enque)
        {
            /* Message Queue is not empty */
            if (msg_queue[module].queue[i].id == id)
            {
                return;     /* ������������ͬ����Ϣ������ */
            }
            i++;
            if (i >= QUEUE_LENGTH)
            {
                i = 0;
            }
        }

        msg_queue[module].queue[enque] = msg;
        enque++;
        if (enque >= QUEUE_LENGTH)  /* ע�⣬QUEUE_LENGTH��Ҫ����0x7f */
        {
            enque = 0;  
        }
        if (enque == deque)
        {
            b_full = true;
        }
    }
    if (b_full)
    {
        SetBit(enque, 7);
    }
    msg_queue[module].n_enque = enque;
    msg_queue[module].n_deque = deque;

    return;
}

//��ָ������Ϣ���뵽��Ϣ���еĵ�һ��λ��
//�����Ϣ���������������һ����Ϣ����
extern void insert_message(MSG_MODULE module, MESSAGE_ID id, uint16_t param)
{
    MESSAGE msg;
    uint8_t enque, deque;
    bool b_full;

    msg.id = id;
    msg.prm = param;

    enque = (uint8_t)(msg_queue[module].n_enque & 0x7F);
    b_full = (uint8_t)(msg_queue[module].n_enque & 0x80);
    deque = (uint8_t)(msg_queue[module].n_deque & 0x7F);

    if (b_full)
    {
        if (enque == 0)
        {
            enque = QUEUE_LENGTH - 1;
        }
        else enque--;  //����������е���Ϣ����
    }

    if (deque == 0)
    {
        deque = QUEUE_LENGTH - 1;
    }
    else deque--;

    msg_queue[module].queue[deque] = msg;
    if (enque == deque)
    {
        b_full = true;
    }

    if (b_full)
    {
        SetBit(enque, 7);
    }
    msg_queue[module].n_enque = enque;
    msg_queue[module].n_deque = deque;

    return;
}

//����Ϣ������ȡ����Ϣ
extern MESSAGE *get_message(MSG_MODULE module)
{
    static MESSAGE msg;
    uint8_t enque, deque;
    bool b_empty;

    msg.id = NO_MSG;

    enque = (uint8_t)(msg_queue[module].n_enque & 0x7F);
    deque = (uint8_t)(msg_queue[module].n_deque & 0x7F);
    b_empty = (uint8_t)(msg_queue[module].n_deque & 0x80);

    if (b_empty == 0)
    {
        msg = msg_queue[module].queue[deque];
        deque++;
        if (deque >= QUEUE_LENGTH)
        {
            deque = 0;
        }
        if (enque == deque)
        {
            b_empty = true;
        }
    }

    if (b_empty)
    {
        SetBit(deque, 7);
    }
    msg_queue[module].n_enque = enque;
    msg_queue[module].n_deque = deque;

    return &msg;
}

/* ��ѯ��Ϣ�����е���Ϣ */
extern MESSAGE *query_message(MSG_MODULE module)
{
    static MESSAGE msg;
    uint8_t deque;
    bool b_empty;

    msg.id = NO_MSG;

    deque = (uint8_t)(msg_queue[module].n_deque & 0x7F);
    b_empty = (uint8_t)(msg_queue[module].n_deque & 0x80);

    if (b_empty == 0)
    {
        msg = msg_queue[module].queue[deque];
    }

    return &msg;
}

/* ��ָ����Ϣ������� */
extern void clear_message(MSG_MODULE module)
{
    msg_queue[module].n_enque = 0x00;  /* b_full=false; */
    msg_queue[module].n_deque = 0x80;  /* b_empty=true; */

    return;
}

/* ��������Ϣ������� */
extern void message_init(void)
{
    uint8_t i;

    for (i = 0; i < NUM_OF_MSG_QUEUE; i++)
    {
        clear_message(i);
    }

    return;
}


