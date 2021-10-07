/*
 * lib.c - lib.c config and achieve;
 *
 * Copyright (c) 2014 Forlan.yung(YANGHUALIANG)
 *
 */

#define LIB_ROOT

#include "include.h"


/****************************************************************************
      函数定义区
****************************************************************************/
/*---------------------------------------------------------------------------
                 *bitIndex:     2           0
                                |           |
                 location:  0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 ....
                            |             | |                      | |
                            |-------------| |----------------------| |-----
                 *byteIndex:       0                   1                  2
                                       
 Input  parameter : location,byteIndex,bitIndex
 Output parameter : byteIndex,bitIndex
 Use  Function    : 比特定位函数
 Reserve  date    : 2004-6-29
---------------------------------------------------------------------------*/
extern void FindBitLocationInBytes(uint8_t location, uint8_t * byteIndex, uint8_t * bitIndex)
{
    *bitIndex = (uint8_t)(location & 0x07);     //取location除8的余数
    *byteIndex = (uint8_t)(location >> 3);      //取location除8的商数
}


extern uint16_t Margin(uint16_t a, uint16_t b)
{
    return(a > b) ? (a - b) : (b-a);
}


extern uint8_t Margin8(uint8_t a, uint8_t b)
{
    return(uint8_t)((a > b) ? (a - b) : (b - a));
}


extern uint8_t bcd2dec(uint8_t nbcd)
{
    uint8_t hNibble, lNibble;

    hNibble = (uint8_t)((HighNibble(nbcd)) * 10);
    lNibble = (uint8_t)LowNibble(nbcd);

    return (uint8_t)(hNibble + lNibble);
}


/* Lookup table to convert HEX to BCD */
const uint8_t hex2bcd[] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, /* 00-09 */
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, /* 10-19 */
    0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, /* 20-29 */
    0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, /* 30-39 */
    0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, /* 40-49 */
    0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, /* 50-59 */
    0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, /* 60-69 */
    0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, /* 70-79 */
    0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, /* 80-89 */
    0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, /* 90-99 */
};


/****************************************************************************
下面的这几个函数，其操纵对象，只能是指向内存区域的指针
itoa:         Convert uint8_t to string
strclr:       Set string to space ' '
buffer_clr:   Clear buffer to zero.
MEMSET:       Set buffer to specified value.
****************************************************************************/
//Convert hex digit to NULL-terminated string
//Note that i is not BCD digit
//注意，str是指向内存区域的字符串指针
extern void itoa(uint8_t * str, uint8_t i)
{
    if (i >= 200)
    {
        *str = '2';
        str++;
        i-=200;
    }
    else if (i >= 100)
    {
        *str = '1';
        str++;
        i -= 100;
    }
    i = hex2bcd[i];
    *str = (uint8_t)(i >> 4);
    *str += '0';
    str++;
    i&=0x0f;
    i += '0';
    *str = i;
    str++;
    *str = '\0';

    return;
}


// Convert 16bit hex digit to NULL-terminated string
// Note that i is not BCD digit
// 注意，str是指向内存区域的字符串指针
extern void i16toa(uint8_t * str, uint16_t i)
{
    uint8_t num;
    uint16_t i_bak;

    i_bak = i;
    if (i >= 10000)
    {
        num = (uint8_t)(i / 10000);
        *str = (uint8_t)('0' + num);
        str++;
        i_bak -= 10000 * num;
    }
    else
        *str ++= 0;

    if (i >= 1000)
    {
        num = (uint8_t)(i_bak / 1000);
        *str = (uint8_t)('0' + num);
        str++;
        i_bak -= 1000 * num;
    }
    else
        *str ++= 0;

    if (i >= 100)
    {
        num = (uint8_t)(i_bak / 100);
        *str = (uint8_t)('0' + num);
        str++;
        i_bak -= 100 * num;
    }
    else
        *str ++= 0;

    if(i >= 10)
    {
        num = (uint8_t)(i_bak / 10);
        *str = (uint8_t)('0' + num);
        str++;
        i_bak -= 10 * num;
    }
    else
        *str ++= 0;

    *str = (uint8_t)('0' + i_bak);
    str++;
    *str = '\0';

    return;
}


extern void strclr(uint8_t * str, uint8_t size)
{
    for ( ; size; size--)
    {
        *str = ' ';
        str++;
    }

    return;
}


extern void buffer_clr(uint8_t * ptr, uint16_t size)
{
    for ( ; size; size--)
    {
        *ptr = 0;
        ptr++;
    }

    return;
}


extern void MEMSET(void *buff, uint8_t data, uint16_t length)
{
    uint16_t i;
    uint8_t *p;

    p = (uint8_t *)buff;

    for (i = 0; i < length; i++)
    {
        *p = data;
        p++;
    }
}


/****************************************************************************
      下面的这几个函数，其操纵对象，都是指向内存区域的指针
****************************************************************************/
extern uint8_t strlen(uint8_t * str)
{
    uint8_t i;
    for (i = 0; str[i]; i++);

    return i;
}


//字符串拷贝，注意to,from的区域不能重叠。
extern void strcpy(uint8_t * to, uint8_t * from)
{
    while (*from)
    {
        *to = *from;
        to++;
        from++;
    }
    *to = '\0';

    return;
}


//字符串拷贝，注意to,from的区域不能重叠。
extern void strncpy(uint8_t * to, uint8_t * from, uint8_t size)
{
    while (size)
    {
        *to = *from;
        to++;
        from++;
        size--;
    }

    return;
}


//字符串拷贝，注意to,from的区域不能重叠。
extern void strncpy_Int16u(uint8_t * to, uint8_t * from, uint16_t size)
{
    while (size)
    {
        *to = *from;
        to++;
        from++;
        size--;
    }

    return;
}


//MEMORY拷贝，注意to,from的区域不能重叠。
extern bool memcpy(void * to, void * from, uint8_t size)
{
    uint8_t *pTo = (uint8_t *)to;
    uint8_t *pFrom = (uint8_t *)from;
    if ((NULL == pTo) || (NULL == pFrom))
    {
        return 0;
    }

    if (!((pTo >= pFrom + size) || (pFrom >= pTo + size)))
    {
        return 0;
    }

    while (size-- > 0)
    {
        *pTo++=*pFrom++;
    }

    return 1;
}


//字符串连接，注意to,from的区域不能重叠。
extern void strcat(uint8_t * to, uint8_t * from)
{
    while (*to)
        to++;
    while (*from)
    {
        *to = *from;
        to++;
        from++;
    }
    *to = '\0';

    return;
}


//注意!!!!
//以下的函数，不可以被放入到SECTOR0区域，原因如下：
//strncat()实际上从来未被系统所调用；
//Delay_ms()应该是不能用的，因为它造成了太长的延时；
//strcmp,strncmp可能会调用系统比较函数_CMPS；

//字符串连接，注意to,from的区域不能重叠。
extern void strncat(uint8_t * to, uint8_t * from, uint8_t size)
{
    while (*to)
        to++;
    while (size)
    {
        *to = *from;
        to++;
        from++;
        size--;
    }

    return;
}


//比较两个字符串
extern int strcmp(uint8_t * str1, uint8_t * str2)
{
    if (str1 == str2) return 0;
    while (*str1)
    {
        if (*str1 > *str2) return 1;
        else if(*str1 < *str2) return -1;
        else
        {
            ++str1;
            ++str2;
        }
    }

    return 0;
}


//比较两个字符串前n个字符
extern int strncmp(uint8_t * str1, uint8_t * str2, uint8_t size)
{
    uint8_t i;

    if (str1 == str2) return 0;
    for (i = 0; i < size; ++i)
    {
        if (*str1 > *str2) return 1;
        else if (*str1 < *str2) return -1;
        else
        {
            ++str1;
            ++str2;
        }
    }

    return 0;
}


/****************************************************************************
下面的这几个函数，其操纵对象中，from指针指向常量flash区域，to指针指向变量
内存区域参数为单一指针的函数，其指针指向常量flash区域。

适用于内存区域与程序存储区域分开编址的CPU。
同一个指针数值，必须指明到底是指向内存区域，还是指向程序存储区域。
否则，编译会报错，程序运行也会有问题
****************************************************************************/
extern uint8_t strlen_rom(const uint8_t str[])
{
    uint8_t i;
    for(i=0;str[i];i++);
    return i;
}


//字符串拷贝，注意to,from的区域不能重叠。
extern void strcpy_rom(uint8_t * to, uint8_t *from)
{
    while (*from)
    {
        *to = *from;
        to++;
        from++;
    }

    *to = '\0';
    return;
}


//字符拷贝，只拷贝字符串里的有效字符，不拷贝结束符，注意to,from的区域不能重叠。
extern void charcpy_rom(uint8_t * to, const uint8_t from[])
{
    while (*from)
    {
        *to = *from;
        to++;
        from++;
    }

    return;
}


//字符串拷贝，注意to,from的区域不能重叠。
extern void strncpy_rom(uint8_t * to, const uint8_t from[], uint8_t size)
{
    while (size)
    {
        *to = *from;
        to++;
        from++;
        size--;
    }

    return;
}


//MEMORY拷贝，注意to,from的区域不能重叠。
extern bool memcpy_rom(void * to, const uint8_t from[], uint8_t size)
{
    uint8_t *pTo = (uint8_t *)to;
    uint8_t *pFrom = (uint8_t *)from;
    if ((NULL == pTo) || (NULL == pFrom))
    {
        return 0;
    }

    if (!((pTo >= pFrom + size) || (pFrom >= pTo + size)))
    {
        return 0;
    }

    while (size-- > 0)
    {
        *pTo++=*pFrom++;
    }

    return 1;
}


//字符串连接，注意to,from的区域不能重叠。
extern void strcat_rom(uint8_t * to, const uint8_t from[])
{
    while (*to)
        to++;
    while (*from)
    {
        *to = *from;
        to++;
        from++;
    }
    *to = '\0';

    return;
}


//注意!!!!
//以下的函数，不可以被放入到SECTOR0区域，原因如下：
//strncat()实际上从来未被系统所调用；
//Delay_ms()应该是不能用的，因为它造成了太长的延时；
//strcmp,strncmp可能会调用系统比较函数_CMPS；

//字符串连接，注意to,from的区域不能重叠。
extern void strncat_rom(uint8_t * to, const uint8_t from[], uint8_t size)
{
    while (*to)
        to++;
    while (size)
    {
        *to = *from;
        to++;
        from++;
        size--;
    }

    return;
}


//比较两个字符串
//其中str1指向内存区域，str2指向程序区域
extern int strcmp_rom(uint8_t * str1, const uint8_t str2[])
{
    if (str1 == str2) return 0;
    while (*str1)
    {
        if (*str1 > *str2) return 1;
        else if(*str1 < *str2) return -1;
        else
        {
            ++str1;
            ++str2;
        }
    }

    return 0;
}


//比较两个字符串前n个字符
//其中str1指向内存区域，str2指向程序区域
extern int strncmp_rom(uint8_t * str1, const uint8_t str2[], uint8_t size)
{
    uint8_t i;
    if (str1 == str2) return 0;
    for (i = 0; i < size; ++i)
    {
        if (*str1 > *str2) return 1;
        else if (*str1 < *str2) return -1;
        else
        {
            ++str1;
            ++str2;
        }
    }

    return 0;
}


