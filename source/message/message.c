/*
 * mpu_rx.c - mpu_rx.c config and achieve;
 *
 * Copyright (c) 2014 Forlan.yung(YANGHUALIANG)
 *
 */

#include "include.h"

static MSGQUEUE msg_queue[NUM_OF_MSG_QUEUE];


//将指定的消息放到消息队列中
//如果消息队列已满，则将该消息丢弃
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
        if (enque >= QUEUE_LENGTH)  /* 注意，QUEUE_LENGTH不要超过0x7f */
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

//将指定的消息放到消息队列中
//在放入之前，首先查询队列中有无相同的消息
//如果有，则不再放入。
//如果消息队列已满，则将该消息丢弃
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
                return;     /* 队列中已有相同的消息，返回 */
            }
            i++;
            if (i >= QUEUE_LENGTH)
            {
                i = 0;
            }
        }

        msg_queue[module].queue[enque] = msg;
        enque++;
        if (enque >= QUEUE_LENGTH)  /* 注意，QUEUE_LENGTH不要超过0x7f */
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

//将指定的消息插入到消息队列的第一个位置
//如果消息队列已满，则将最后一个消息丢弃
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
        else enque--;  //将最后进入队列的消息丢弃
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

//从消息队列中取出消息
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

/* 查询消息队列中的消息 */
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

/* 将指定消息队列清空 */
extern void clear_message(MSG_MODULE module)
{
    msg_queue[module].n_enque = 0x00;  /* b_full=false; */
    msg_queue[module].n_deque = 0x80;  /* b_empty=true; */

    return;
}

/* 将所有消息队列清空 */
extern void message_init(void)
{
    uint8_t i;

    for (i = 0; i < NUM_OF_MSG_QUEUE; i++)
    {
        clear_message(i);
    }

    return;
}


