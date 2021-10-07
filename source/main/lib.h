/*
 * lib.h - lib.h config header file;
 *
 * Copyright (c) 2014 Forlan.yung(YANGHUALIANG)
 *
 */

#ifndef _LIB_H_
#define _LIB_H_

#ifdef LIB_ROOT
#define EXTERN_LIB
#else
#define EXTERN_LIB extern
#endif

#define NONE  0


/****************************************************************************
      变量声明区
****************************************************************************/
extern const uint8_t hex2bcd[];


/****************************************************************************
      函数声明区
****************************************************************************/
//point to RAM area only
extern void FindBitLocationInBytes(uint8_t location, uint8_t *byteIndex, uint8_t *bitIndex);
extern uint16_t Margin(uint16_t a, uint16_t b);
extern uint8_t Margin8(uint8_t a, uint8_t b);
extern uint8_t bcd2dec(uint8_t nbcd);
extern void itoa(uint8_t * str, uint8_t i);
extern void i16toa(uint8_t * str, uint16_t i);
extern void strclr(uint8_t * str, uint8_t size);
extern void buffer_clr(uint8_t * ptr, uint16_t size);
extern void MEMSET(void *buff, uint8_t data, uint16_t length);

//point to RAM area
extern uint8_t strlen(uint8_t * str);
extern void strcpy(uint8_t * to, uint8_t * from);
extern void strncpy(uint8_t * to, uint8_t * from, uint8_t size);
extern void strncpy_Int16u(uint8_t * to, uint8_t * from, uint16_t size);
extern bool memcpy(void * to, void * from, uint8_t size);
extern void strcat(uint8_t * to, uint8_t * from);
extern void strncat(uint8_t * to, uint8_t * from, uint8_t size);
extern int strcmp(uint8_t * str1, uint8_t * str2);
extern int strncmp(uint8_t * str1, uint8_t * str2, uint8_t size);

//point to ROM area
extern uint8_t strlen_rom(const uint8_t str[]);
extern void strcpy_rom(uint8_t * to, uint8_t *from);
extern void charcpy_rom(uint8_t * to, const uint8_t from[]);
extern void strncpy_rom(uint8_t * to, const uint8_t from[], uint8_t size);
extern bool memcpy_rom(void * to, const uint8_t from[], uint8_t size);
extern void strcat_rom(uint8_t * to, const uint8_t from[]);
extern void strncat_rom(uint8_t * to, const uint8_t from[], uint8_t size);
extern int strcmp_rom(uint8_t * str1, const uint8_t str2[]);
extern int strncmp_rom(uint8_t * str1, const uint8_t str2[], uint8_t size);


#endif

