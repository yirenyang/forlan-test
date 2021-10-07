/*
 * retarget.c - retarget.c config and achieve;
 *
 * Copyright (c) 2014 Forlan.yung(YANGHUALIANG)
 *
 */

#include <stdio.h>
#include "include.h"


/****************************************************************************
      函数定义区
****************************************************************************/
int fputc(int ch, FILE *f)
{
    /* 循环直到发送结束 */
    while (!(LPC_UART->LSR & U0LSR_THRE_U0THR_EMPTY));

    /* 你自己实现的fputc放置到这里 */
    /* 例如写一个字符到USART */  
    LPC_UART->THR = ch;

    return ch;
}

