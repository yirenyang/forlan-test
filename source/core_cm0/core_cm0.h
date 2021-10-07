/*
 * core_cm0.h - core_cm0.h config header file;
 *
 * Copyright (c) 2014 Forlan.yung(YANGHUALIANG)
 *
 */

#ifndef __CM0_CORE_H__
#define __CM0_CORE_H__

#ifdef __cplusplus
extern "C" {
#endif 

#define __CM0_CMSIS_VERSION_MAIN  (0x01)                                                       /*!< [31:16] CMSIS HAL ���汾�� */
#define __CM0_CMSIS_VERSION_SUB   (0x20)                                                       /*!< [15:0]  CMSIS HAL �Ӱ汾�� */
#define __CM0_CMSIS_VERSION       ((__CM0_CMSIS_VERSION_MAIN << 16) | __CM0_CMSIS_VERSION_SUB) /*!< CMSIS HAL �汾��           */

#define __CORTEX_M                (0x00)                                                       /*!< Cortex ��                  */


#include <stdint.h>                           

#if defined (__ICCARM__)
#include <intrinsics.h>                         /* IAR ����  */
#endif


#ifndef __NVIC_PRIO_BITS
#define __NVIC_PRIO_BITS    2                 /*!< NVIC���ȼ�λ������*/
#endif

/*
 * IO ����
 *
 * ������Χ�Ĵ�������Ȩ��
 */
#ifdef __cplusplus
#define     __I     volatile                    /*!< 'read only'����             */
#else
#define     __I     volatile const              /*!< 'read only'����             */
#endif
#define     __O     volatile                    /*!< 'write only'����            */
#define     __IO    volatile                    /*!< 'read / write'�ɶ�д        */


/* System Reset */
#define NVIC_VECTRESET              0           /*!< ������λ                  */
#define NVIC_SYSRESETREQ            2           /*!< ϵͳ��λ����                */
#define NVIC_AIRCR_VECTKEY    (0x5FA << 16)     /*!< AIRCR Key����д����         */
#define NVIC_AIRCR_ENDIANESS        15          /*!< �˶���                      */

/* Ƕ�������жϿ�����(NVIC)�Ĵ���ӳ�� */
typedef struct
{
    __IO uint32_t ISER[1];                      /*!< �ж�����ʹ�ܼĴ���           */
         uint32_t RESERVED0[31];
    __IO uint32_t ICER[1];                      /*!< �ж����ʹ�ܼĴ���           */
         uint32_t RSERVED1[31];
    __IO uint32_t ISPR[1];                      /*!< �ж���������Ĵ���           */
         uint32_t RESERVED2[31];
    __IO uint32_t ICPR[1];                      /*!< �ж��������Ĵ���           */
         uint32_t RESERVED3[31];
         uint32_t RESERVED4[64];
    __IO uint32_t IPR[8];                       /*!< �ж����ȼ��Ĵ���             */
} NVIC_Type;

/* ϵͳ���ƿ�Ĵ���ӳ�� */
typedef struct
{
    __I  uint32_t CPUID;                        /*!< CPU ID��ַ�Ĵ���              */
    __IO uint32_t ICSR;                         /*!< �жϿ���״̬�Ĵ���            */
         uint32_t RESERVED0;
    __IO uint32_t AIRCR;                        /*!< Ӧ�ó����ж�/��λ���ƼĴ���   */
    __IO uint32_t SCR;                          /*!< ϵͳ���ƼĴ���                */
    __IO uint32_t CCR;                          /*!< ���ÿ��ƼĴ���                */
         uint32_t RESERVED1;
    __IO uint32_t SHP[2];                       /*!< ϵͳ�������ȼ��Ĵ�����0λ���� */
    __IO uint32_t SHCSR;                        /*!< ϵͳ������ƺ�״̬�Ĵ���      */
         uint32_t RESERVED2[2];
    __IO uint32_t DFSR;                         /*!< ���Թ���״̬�Ĵ���            */
} SCB_Type;

/* ϵͳ�δ�洢��ӳ�� */
typedef struct
{
    __IO uint32_t CTRL;                         /*!< SysTick���ƺ�״̬�Ĵ���       */
    __IO uint32_t LOAD;                         /*!< SysTick��װ��ֵ�Ĵ���         */
    __IO uint32_t VAL;                          /*!< SysTick��ǰֵ�Ĵ���           */
    __I  uint32_t CALIB;                        /*!< SysTickУ��Ĵ���             */
} SysTick_Type;

/* �ں˵��ԼĴ��� */
typedef struct
{
    __IO uint32_t DHCSR;                        /*!< ����ͣ�����ƺ�״̬�Ĵ���      */
    __O  uint32_t DCRSR;                        /*!< �����ں˼Ĵ���ѡ��Ĵ���      */
    __IO uint32_t DCRDR;                        /*!< �����ں˼Ĵ������ݼĴ���      */
    __IO uint32_t DEMCR;                        /*!< �����쳣�ͼ�ؿ��ƼĴ���      */
} CoreDebug_Type;

/* Cortex-M0Ӳ���洢��ӳ�� */
#define SCS_BASE            (0xE000E000)                              /*!< ϵͳ���ƿռ����ַ  */
#define CoreDebug_BASE      (0xE000EDF0)                              /*!< �ں˵��Ի���ַ      */
#define SysTick_BASE        (SCS_BASE +  0x0010)                      /*!< SysTick����ַ       */
#define NVIC_BASE           (SCS_BASE +  0x0100)                      /*!< NVIC����ַ          */
#define SCB_BASE            (SCS_BASE +  0x0D00)                      /*!< ϵͳ���ƿ����ַ    */

#define SCB                 ((SCB_Type *)           SCB_BASE)         /*!< SCB���ýṹ         */
#define SysTick             ((SysTick_Type *)       SysTick_BASE)     /*!< SysTick���ýṹ     */
#define NVIC                ((NVIC_Type *)          NVIC_BASE)        /*!< NVIC���ýṹ        */
#define CoreDebug           ((CoreDebug_Type *)     CoreDebug_BASE)   /*!< Core Debug���ýṹ  */


/****************************************************************************
      Ӳ�������
****************************************************************************/
#if defined ( __CC_ARM   )
#define __ASM            __asm                                      
#define __INLINE         __inline                                  

#elif defined ( __ICCARM__ )
#define __ASM           __asm                                      
#define __INLINE        inline                                     

#elif defined   (  __GNUC__  )
#define __ASM            __asm                                      
#define __INLINE         inline                                     

#elif defined   (  __TASKING__  )
#define __ASM            __asm                                      
#define __INLINE         inline                                     

#endif

/****************************************************************************
      �������������
****************************************************************************/
/* RealView������ */
#if defined ( __CC_ARM   )

#define __enable_fault_irq                __enable_fiq
#define __disable_fault_irq               __disable_fiq

#define __NOP                             __nop
#define __WFI                             __wfi
#define __WFE                             __wfe
#define __SEV                             __sev
#define __ISB()                           __isb(0)
#define __DSB()                           __dsb(0)
#define __DMB()                           __dmb(0)
#define __REV                             __rev

/* intrinsic void __enable_irq();     */
/* intrinsic void __disable_irq();    */

extern uint32_t __get_PSP(void);
extern void __set_PSP(uint32_t topOfProcStack);
extern uint32_t __get_MSP(void);
extern void __set_MSP(uint32_t topOfMainStack);
extern uint32_t __REV16(uint16_t value);
extern int32_t __REVSH(int16_t value);
//extern void __enable_irq(void);
//extern void __disable_irq(void);
//extern void __nop(void);

#if (__ARMCC_VERSION < 400000)

extern uint32_t __get_PRIMASK(void);
extern void __set_PRIMASK(uint32_t priMask);
extern uint32_t __get_CONTROL(void);
extern void __set_CONTROL(uint32_t control);

#else  /* (__ARMCC_VERSION >= 400000)  */

/*
 * @��������__get_PRIMASK
 * @��������ȡ���ȼ�����״̬
 * @������ ��
 * @����ֵ��uint32_t PriMask
 */ 
static __INLINE uint32_t __get_PRIMASK(void)
{
    register uint32_t __regPriMask         __ASM("primask");
    return(__regPriMask);
}

/*
 * @��������__set_PRIMASK
 * @�������������ȼ����μĴ���
 * @������ uint32_t PriMask
 * @����ֵ����
 */
static __INLINE void __set_PRIMASK(uint32_t priMask)
{
    register uint32_t __regPriMask         __ASM("primask");
    __regPriMask = (priMask);
}

/*
 * @��������__get_CONTROL
 * @���������ؿ��ƼĴ���ֵ
 * @������ ��
 * @����ֵ��uint32_t ���ƼĴ���ֵ
 */
static __INLINE uint32_t __get_CONTROL(void)
{
    register uint32_t __regControl         __ASM("control");
    return(__regControl);
}

/*
 * @��������__set_CONTROL
 * @���������ÿ��ƼĴ���
 * @������ uint32_t ���ƼĴ���ֵ
 * @����ֵ����
 */ 
static __INLINE void __set_CONTROL(uint32_t control)
{
    register uint32_t __regControl         __ASM("control");
    __regControl = control;
}

#endif /* __ARMCC_VERSION  */ 

/* ICC������ */
#elif (defined (__ICCARM__))

#define __enable_irq                              __enable_interrupt        /*!< ȫ���ж�ʹ�� */
#define __disable_irq                             __disable_interrupt       /*!< ȫ���жϳ��� */

static __INLINE void __enable_fault_irq()         { __ASM ("cpsie f"); }
static __INLINE void __disable_fault_irq()        { __ASM ("cpsid f"); }

#define __NOP                                     __no_operation()          
static __INLINE  void __WFI()                     { __ASM ("wfi"); }
static __INLINE  void __WFE()                     { __ASM ("wfe"); }
static __INLINE  void __SEV()                     { __ASM ("sev"); }

/* intrinsic void __ISB(void)                                     */
/* intrinsic void __DSB(void)                                     */
/* intrinsic void __DMB(void)                                     */
/* intrinsic void __set_PRIMASK();                                */
/* intrinsic void __get_PRIMASK();                                */

/* intrinsic uint32_t __REV(uint32_t value);                      */
/* intrinsic uint32_t __REVSH(uint32_t value);                    */

extern uint32_t __get_PSP(void);
extern void __set_PSP(uint32_t topOfProcStack);
extern uint32_t __get_MSP(void);
extern void __set_MSP(uint32_t topOfMainStack);
extern uint32_t __REV16(uint16_t value);

/* GNU������ */
#elif (defined (__GNUC__))
static __INLINE void __enable_irq()               { __ASM volatile ("cpsie i"); }
static __INLINE void __disable_irq()              { __ASM volatile ("cpsid i"); }

static __INLINE void __enable_fault_irq()         { __ASM volatile ("cpsie f"); }
static __INLINE void __disable_fault_irq()        { __ASM volatile ("cpsid f"); }

static __INLINE void __NOP()                      { __ASM volatile ("nop"); }
static __INLINE void __WFI()                      { __ASM volatile ("wfi"); }
static __INLINE void __WFE()                      { __ASM volatile ("wfe"); }
static __INLINE void __SEV()                      { __ASM volatile ("sev"); }
static __INLINE void __ISB()                      { __ASM volatile ("isb"); }
static __INLINE void __DSB()                      { __ASM volatile ("dsb"); }
static __INLINE void __DMB()                      { __ASM volatile ("dmb"); }

extern uint32_t __get_PSP(void);
extern void __set_PSP(uint32_t topOfProcStack);
extern uint32_t __get_MSP(void);
extern void __set_MSP(uint32_t topOfMainStack);
extern uint32_t  __get_PRIMASK(void);
extern void __set_PRIMASK(uint32_t priMask);
extern uint32_t __get_CONTROL(void);
extern void __set_CONTROL(uint32_t control);
extern uint32_t __REV(uint32_t value);
extern uint32_t __REV16(uint16_t value);
extern int32_t __REVSH(int16_t value);

 /* TASKING ������ */
#elif (defined (__TASKING__))

#endif

/* NVIC ���� */
#define _BIT_SHIFT(IRQn)         (  (((uint32_t)(IRQn)       )    &  0x03) * 8 )
#define _SHP_IDX(IRQn)           ( ((((uint32_t)(IRQn) & 0x0F)-8) >>    2)     )
#define _IP_IDX(IRQn)            (   ((uint32_t)(IRQn)            >>    2)     )

/*
 * @��������NVIC_EnableIRQ
 * @������ʹ��NVIC�жϿ��ƼĴ�������Ӧλ
 * @������ IRQn_Type IRQnָ���жϺ�
 * @����ֵ����
 */  
static __INLINE void NVIC_EnableIRQ(IRQn_Type IRQn)
{
    NVIC->ISER[0] = (1 << ((uint32_t)(IRQn) & 0x1F)); /* ʹ���ж� */
}

/*
 * @��������NVIC_DisableIRQ
 * @����������һ�������豸�ⲿ�ж�
 * @������ IRQn_Type IRQn�ⲿ�жϺţ�����
 * @����ֵ����
 */  
static __INLINE void NVIC_DisableIRQ(IRQn_Type IRQn)
{
    NVIC->ICER[0] = (1 << ((uint32_t)(IRQn) & 0x1F)); /* �����ж� */
}

/*
 * @��������NVIC_GetPendingIRQ
 * @��������ȡ�ж�����״̬
 * @������ IRQn_Type  IRQn�����豸�жϺ�
 * @����ֵ��uint32_t   ����ж����𷵻�1�����򷵻�0
 */  
static __INLINE uint32_t NVIC_GetPendingIRQ(IRQn_Type IRQn)
{
    return((uint32_t) ((NVIC->ISPR[0] & (1 << ((uint32_t)(IRQn) & 0x1F)))?1:0)); 
}

/*
 * @��������NVIC_SetPendingIRQ
 * @������Ϊ�ⲿ�ж���������λ
 * @������ IRQn_Type IRQn�жϺ�
 * @����ֵ����
 */ 
static __INLINE void NVIC_SetPendingIRQ(IRQn_Type IRQn)
{
    NVIC->ISPR[0] = (1 << ((uint32_t)(IRQn) & 0x1F)); 
}
 
/*
 * @��������NVIC_ClearPendingIRQ
 * @����������ⲿ�ж�����λ
 * @������ IRQn_Type  IRQnΪ�жϺ�
 * @����ֵ����
 */  
static __INLINE void NVIC_ClearPendingIRQ(IRQn_Type IRQn)
{
    NVIC->ICPR[0] = (1 << ((uint32_t)(IRQn) & 0x1F)); 
}

/*
 * @��������NVIC_SetPriority
 * @�����������ж����ȼ�
 * @������ IRQn_Type  IRQn�жϺ�
 * @����ֵ����
 */ 
static __INLINE void NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority)
{
    if (IRQn < 0) 
    {
        SCB->SHP[_SHP_IDX(IRQn)] = (SCB->SHP[_SHP_IDX(IRQn)] & ~(0xFF << _BIT_SHIFT(IRQn))) | 
            (((priority << (8 - __NVIC_PRIO_BITS)) & 0xFF) << _BIT_SHIFT(IRQn));
    }
    else
    {
        NVIC->IPR[_IP_IDX(IRQn)] = (NVIC->IPR[_IP_IDX(IRQn)] & ~(0xFF << _BIT_SHIFT(IRQn))) |
            (((priority << (8 - __NVIC_PRIO_BITS)) & 0xFF) << _BIT_SHIFT(IRQn));
    }
}

/*
 * @��������NVIC_GetPriority
 * @��������ȡ�ж����ȼ�
 * @������ IRQn_Type IRQn�жϺ�
 * @����ֵ��priority�ж����ȼ�
 */ 
static __INLINE uint32_t NVIC_GetPriority(IRQn_Type IRQn)
{
    if(IRQn < 0)
    {
        return((uint32_t)((SCB->SHP[_SHP_IDX(IRQn)] >> _BIT_SHIFT(IRQn) ) >> (8 - __NVIC_PRIO_BITS)));
    } 
    else
    {
        return((uint32_t)((NVIC->IPR[_IP_IDX(IRQn)] >> _BIT_SHIFT(IRQn) ) >> (8 - __NVIC_PRIO_BITS)));
    } 
}

/* SysTick���� */
#if (!defined (__Vendor_SysTickConfig)) || (__Vendor_SysTickConfig == 0)

/* SysTick ���� */
#define SYSTICK_ENABLE              0                                                       /* ���õ�0λ������ֹͣ�δ�ʱ��      */
#define SYSTICK_TICKINT             1                                                       /* ʹ�ܻ���ܵδ��ж�                 */
#define SYSTICK_CLKSOURCE           2                                                       /* �δ�ʱ��Դ����                     */
#define SYSTICK_MAXCOUNT       ((1<<24) -1)                                                 /* �δ�������                       */

/*
 * @������:	SysTick_Config
 * @����:	��ʼ���������δ�ʱ���������ж�����
 * @����:	uint32_t ticks�δ��ж�����
 * @����ֵ:	��
 */ 
static __INLINE uint32_t SysTick_Config(uint32_t ticks)
{ 
    if (ticks > SYSTICK_MAXCOUNT)  return (1);                                              /* ��װ�س���               */

    SysTick->LOAD  =  (ticks & SYSTICK_MAXCOUNT) - 1;                                       /* ������װ�ؼĴ���         */
    NVIC_SetPriority (SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);                             /* ���õδ��ж����ȼ�       */
    SysTick->VAL   =  (0x00);                                                               /* ���õδ��������ʼֵ     */
    SysTick->CTRL = (1 << SYSTICK_CLKSOURCE) | (1<<SYSTICK_ENABLE) | (1<<SYSTICK_TICKINT);  /* ʹ�ܵδ�ʱ��           */

    return (0);                                                                             /* ��ʼ���ɹ� */
}

#endif

/* Reset ���� */

/*
 * @������:	NVIC_SystemReset
 * @����:	��ʼ��һ��ϵͳ��λ������λMCU
 * @����:	��
 * @����ֵ:	��
 */
static __INLINE void NVIC_SystemReset(void)
{
  SCB->AIRCR  = (NVIC_AIRCR_VECTKEY | (1<<NVIC_SYSRESETREQ));                               /* �������ȼ����鲻��   */
  __DSB();                                                                                  /* ��֤�洢����������� */              
  while(1);                                                                                 /* �ȴ�ֱ����λ���     */
}

#ifdef __cplusplus
}
#endif

#endif /* __CM0_CORE_H__ */

