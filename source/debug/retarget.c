/*
 * retarget.c - retarget.c config and achieve;
 *
 * Copyright (c) 2014 Forlan.yung(YANGHUALIANG)
 *
 */

#include <stdio.h>
#include "include.h"


/****************************************************************************
      ����������
****************************************************************************/
int fputc(int ch, FILE *f)
{
    /* ѭ��ֱ�����ͽ��� */
    while (!(LPC_UART->LSR & U0LSR_THRE_U0THR_EMPTY));

    /* ���Լ�ʵ�ֵ�fputc���õ����� */
    /* ����дһ���ַ���USART */  
    LPC_UART->THR = ch;

    return ch;
}

