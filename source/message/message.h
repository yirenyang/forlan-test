/*
 * message.h - message.h config header file;
 *
 * Copyright (c) 2014 Forlan.yung(YANGHUALIANG)
 *
 */
 
#ifndef _MESSAGE_H_
#define _MESSAGE_H_


/****************************************************************************
      常量定义区
****************************************************************************/
#define MESSAGE_ID          uint8_t
#define MSG_MODULE          uint8_t
#define MSG_TYPE            uint8_t
#define QUEUE_LENGTH        15

enum
{
    NO_MSG,
    MSG_BEEP_ACK,
    MSG_BEEP_WELCOME,
    MSG_BEEP_FAIL,
    MSG_BEEP_CONTINUE_START,
    MSG_BEEP_CONTINUE_END
};

typedef struct
{
    MESSAGE_ID id;
    uint16_t prm;
}MESSAGE;

enum
{
    PWR_MSG_QUEUE,
    MPU_MSG_QUEUE,
    CAN_MSG_QUEUE,
    NUM_OF_MSG_QUEUE
};

typedef struct
{
    uint8_t n_enque;
    uint8_t n_deque;
    MESSAGE queue[QUEUE_LENGTH];
}MSGQUEUE;

enum
{
    MSG_TYPE_NULL = 0,
    MSG_TYPE_MPU_CFM,
    MSG_TYPE_MPU_IND
};


/****************************************************************************
      函数申明区
****************************************************************************/
extern void post_message(MSG_MODULE module, MESSAGE_ID id, uint16_t param);
extern void post_new_message(MSG_MODULE module, MESSAGE_ID id, uint16_t param);
extern void insert_message(MSG_MODULE module, MESSAGE_ID id, uint16_t param);
extern MESSAGE *get_message(MSG_MODULE module);
extern MESSAGE *query_message(MSG_MODULE module);
extern void clear_message(MSG_MODULE module);
extern void message_init(void);


#endif

