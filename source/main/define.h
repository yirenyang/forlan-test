/*
 * define.h - define.h config header file;
 *
 * Copyright (c) 2014 Forlan.yung(YANGHUALIANG)
 *
 */
 
#ifndef _DEFINE_H_
#define _DEFINE_H_


/****************************************************************************
      type定义
****************************************************************************/
typedef unsigned char bool;
typedef unsigned char BOOL;

typedef signed          char int8_t;
typedef signed short     int int16_t;
typedef signed           int int32_t;
typedef signed       __int64 int64_t;

typedef unsigned          char uint8_t;
typedef unsigned short     int uint16_t;
typedef unsigned           int uint32_t;
typedef unsigned       __int64 uint64_t;

typedef uint8_t * puint8_t;
typedef uint16_t * puint16_t;
typedef uint8_t volatile * puint8_tv;

typedef volatile signed long  vs32;
typedef volatile signed short vs16;
typedef volatile signed char  vs8;

typedef volatile unsigned long  vu32;
typedef volatile unsigned short vu16;
typedef volatile unsigned char  vu8;

typedef volatile unsigned long  const vuc32;  /* Read Only */
typedef volatile unsigned short const vuc16;  /* Read Only */
typedef volatile unsigned char  const vuc8;   /* Read Only */

typedef void (* pFuncVoid) (void);
typedef uint8_t (* pFunc_ptr) (puint8_t ptr);

#ifndef NULL
#define NULL    ((void *)0)
#endif

#ifndef FALSE
#define FALSE   (0)
#endif

#ifndef TRUE
#define TRUE    (1)
#endif

#ifndef false
#define false   (0)
#endif

#ifndef true
#define true    (1)
#endif

#define Set16Bit(Var,Place) ((Var)|=(uint16_t)((uint16_t)1<<(uint16_t)(Place)))
#define Clr16Bit(Var,Place) ((Var)&=(uint16_t)((uint16_t)((uint16_t)1<<(uint16_t)(Place))^(uint16_t)65535))
#define Val16Bit(Var,Place) ((uint16_t)(Var)&(uint16_t)((uint16_t)1<<(uint16_t)(Place)))

#define SetBit(Var,Place) (Var|=(uint8_t)(1<<Place))
#define ClrBit(Var,Place) (Var = (uint8_t)(Var&((1<<Place)^255)))
#define ValBit(Var,Place) (Var& (1<<Place))
#define ChgBit(Var,Place) (Var^=(1<<Place))
#define LSB(WORD)         (uint8_t)WORD
#define MSB(WORD)         (uint8_t)(WORD>>8)
#define WORD(MSB,LSB)     (uint16_t)(((uint16_t) MSB << 8) + LSB)

#define HighNibble(var)  (var>>4)
#define LowNibble(var)   (var&0x0f)
#define _BYTE(NibbleH,NibbleL)  ((NibbleH<<4)|NibbleL)

#define BIT_0           0x01
#define BIT_1           0x02
#define BIT_2           0x04
#define BIT_3           0x08
#define BIT_4           0x10
#define BIT_5           0x20
#define BIT_6           0x40
#define BIT_7           0x80

#define Chg_Bits(Val,Place)      ((Val)^=(Place))
#define Get_Bits(Val,Place)      ((Val)&(Place))
#define Set_Bits(Val,Place)      ((Val)|=(Place))
#define Clr_Bits(Val,Place)      ((Val)&=((Place)^0xff))

/*
 * 注意下面的联合体的定义,移植性是比较差的,不同的平台对于16位变量组成顺序的定义不尽一致.
 * 对于ST MCU平台(编译器):
 *      b_var[0] is MSB byte of w_var
 *      b_var[1] is LSB byte of w_var
 * 对于AVR MCU平台(编译器):
 *      b_var[0] is LSB byte of w_var
 *      b_var[1] is MSB byte of w_var
 */
#define BYTE_HIGH   0//ST MCU:0,AVR MCU:1
#define BYTE_LOW    1//ST MCU:1,AVR MCU:0

typedef union
{
    uint16_t  w_var;
    uint8_t   b_var[2];
}WORDVAR;

typedef union
{
    uint32_t  l_var;
    uint8_t   b_var[4];
}LONGVAR;

typedef union
{
    uint8_t byte;
    struct
    {
        unsigned B0:1;
        unsigned B1:1;
        unsigned B2:1;
        unsigned B3:1;
        unsigned B4:1;
        unsigned B5:1;
        unsigned B6:1;
        unsigned B7:1;
    }field;
}UCharField;

#define HWREG(x)                                                              \
        (*((volatile unsigned long *)(x)))
#define HWREGH(x)                                                             \
        (*((volatile unsigned short *)(x)))
#define HWREGB(x)                                                             \
        (*((volatile unsigned char *)(x)))
#define HWREGBITW(x, b)                                                       \
        HWREG(((unsigned long)(x) & 0xF0000000) | 0x02000000 |                \
              (((unsigned long)(x) & 0x000FFFFF) << 5) | ((b) << 2))
#define HWREGBITH(x, b)                                                       \
        HWREGH(((unsigned long)(x) & 0xF0000000) | 0x02000000 |               \
               (((unsigned long)(x) & 0x000FFFFF) << 5) | ((b) << 2))
#define HWREGBITB(x, b)                                                       \
        HWREGB(((unsigned long)(x) & 0xF0000000) | 0x02000000 |               \
               (((unsigned long)(x) & 0x000FFFFF) << 5) | ((b) << 2))


#endif  /* _DEFINE_H_ */

