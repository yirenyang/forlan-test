/*
 * core_cm0.c - core_cm0.c config and achieve;
 *
 * Copyright (c) 2014 Forlan.yung(YANGHUALIANG)
 *
 */

#include <stdint.h>


/* �����������Է��Ŷ��� */
#if defined (__CC_ARM)
#define __ASM                   __asm            /*!< armcc������asm�ؼ���          */
#define __INLINE                __inline         /*!< armcc������inline�ؼ���       */
#elif defined (__ICCARM__)
#define __ASM                   __asm            /*!< iarcc������asm�ؼ���          */
#define __INLINE                inline           /*!< iarcc������inline�ؼ���       */
#define __nop                   __no_operation   /*!< �޲��� */
#elif defined (__GNUC__)
#define __ASM                   asm              /*!< gcc������asm�ؼ���            */
#define __INLINE                inline           /*!< gcc������inline�ؼ���         */
#endif

#if (defined (__ARMCC_VERSION)) && (__ARMCC_VERSION < 400000)
/*
 * @��������uint32_t __get_PSP
 * @���������ؽ��̶�ջָ��
 * @������ ��
 * @����ֵ��uint32_t ���̶�ջָ��
 *          ����һ������Ľ��̶�ջָ��
 */
__ASM uint32_t __get_PSP(void)
{
    mrs r0, psp
    bx lr
}

/*
 * @��������__set_PSP 
 * @���������ý��̶�ջָ��
 * @������ uint32_t ���̶�ջָ��
 * @����ֵ����
 * @����һ�����̶�ջָ��ֵ��Cortex-M0��PSP�Ĵ��� 
 */
__ASM void __set_PSP(uint32_t topOfProcStack)
{
    msr psp, r0
    bx lr
}

/*
 * @��������__get_MSP
 * @��������������ջָ��
 * @������ ��
 * @����ֵ��uint32_t ���̶�ջָ��
 */
__ASM uint32_t __get_MSP(void)
{
    mrs r0, msp
    bx lr
}

/*
 * @��������__set_MSP
 * @��������������ջָ��
 * @������uint32_t ���̶�ջָ��
 * @����ֵ����
 * @����һ������ֵ��MSP����ջָ��Ĵ���
 */
__ASM void __set_MSP(uint32_t mainStackPointer)
{
    msr msp, r0
    bx lr
}

/*
 * @��������__get_BASEPRI
 * @���������ػ����ȼ�ֵ
 * @��������
 * @����ֵ��uint32_t �����ȼ�
 */
__ASM uint32_t  __get_BASEPRI(void)
{
    mrs r0, basepri
    bx lr
}

/*
 * @��������__set_BASEPRI
 * @���������û����ȼ�ֵ
 * @������uint32_t �����ȼ�
 * @����ֵ����
 */
__ASM void __set_BASEPRI(uint32_t basePri)
{
    msr basepri, r0
    bx lr
}

/*
 * @������: __get_PRIMASK
 * @�������������ȼ�����ֵ
 * @��������
 * @����ֵ��uint32_t ���ȼ�����ֵ
 */
__ASM uint32_t __get_PRIMASK(void)
{
    mrs r0, primask
    bx lr
}

/*
 * @��������__set_PRIMASK
 * @�������������ȼ����μĴ���
 * @������uint32_t ���ȼ�����ֵ
 * @����ֵ����           
 */
__ASM void __set_PRIMASK(uint32_t priMask)
{
    msr primask, r0
    bx lr
}

/*
 * @��������__get_FAULTMASK 
 * @���������ع������μĴ���ֵ
 * @��������
 * ����ֵ��uint32_t ��������ֵ           
 */
__ASM uint32_t  __get_FAULTMASK(void)
{
    mrs r0, faultmask
    bx lr
}

/*
 * @��������__set_FAULTMASK
 * @���������ù������μĴ���
 * @������uint32_t ��������ֵ
 * @����ֵ����         
 */
__ASM void __set_FAULTMASK(uint32_t faultMask)
{
    msr faultmask, r0
    bx lr
}


/*
 * ��������__get_CONTROL
 * @���������ؿ��ƼĴ���ֵ
 * @����: ��
 * @����ֵ: uint32_t ���ƼĴ���ֵ
 */
__ASM uint32_t  __get_CONTROL(void)
{
    mrs r0, control
    bx lr
}

/*
 * @��������__set_CONTROL
 * @���������ÿ��ƼĴ���
 * @������uint32_t ���ƼĴ���ֵ
 * @����ֵ����
 */
__ASM void __set_CONTROL(uint32_t control)
{
    msr control, r0
    bx lr
}

/*
 * @��������__REV16
 * @��������תunsigned short�����ֽ�˳��
 * @������uint16_t value ��ת��ֵ
 * @����ֵ��uint32_t ת�����ֵ
 */
__ASM uint32_t __REV16(uint16_t value)
{
    rev16 r0, r0
    bx lr
}

/*
 * @��������__REVSH
 * @��������תsigned short����ֵ�ֽ�˳�򲢽��з�����չ
 * @������int16_t value��ת��ֵ
 * @����ֵ��int32_t ת�����ֵ
 */
__ASM int32_t __REVSH(int16_t value)
{
    revsh r0, r0
    bx lr
}

/*
 * @��������__enable_irq
 * @���������ж�
 * @������NO
 * @����ֵ��NO
 */
__ASM void __enable_irq(void)
{
    __ASM volatile ("cpsie i");
}

/*
 * @��������__disable_irq
 * @�������ر��ж�
 * @������NO
 * @����ֵ��NO
 */
__ASM void  __disable_irq(void)
{
    __ASM volatile ("cpsid i");
}

/*
 * @��������__disable_irq
 * @�������ر��ж�
 * @������NO
 * @����ֵ��NO
 */
__ASM void  __nop(void)
{
    __ASM volatile ("nop");
}

#elif (defined (__ICCARM__))
#pragma diag_suppress=Pe940

/*
 * @��������__get_PSP
 * @���������ؽ��̶�ջָ��
 * @��������
 * @����ֵ��uint32_t ���̶�ջָ��
 */
uint32_t __get_PSP(void)
{
    __ASM("mrs r0, psp");
    __ASM("bx lr");
}

/*
 * @��������__set_PSP
 * @���������ý��̶�ջָ��
 * @������uint32_t ���̶�ջָ��
 * @����ֵ����
 *          ΪPSP��ջָ��Ĵ�������һ��ֵ
 */
void __set_PSP(uint32_t topOfProcStack)
{
    __ASM("msr psp, r0");
    __ASM("bx lr");
}

/*
 * @��������__get_MSP
 * @��������������ջָ��
 * @��������
 * @����ֵ�� uint32_t ����ջָ��
 */
uint32_t __get_MSP(void)
{
    __ASM("mrs r0, msp");
    __ASM("bx lr");
}

/*
 * @��������__set_MSP
 * @��������������ջָ��
 * @������uint32_t ����ջָ��
 * @����ֵ����
 * @ΪMSP����ջָ��Ĵ�������һ��ֵ
 */
void __set_MSP(uint32_t topOfMainStack)
{
    __ASM("msr msp, r0");
    __ASM("bx lr");
}

/*
 * @��������__REV16
 * @��������תunsigned short����ֵ�ֽ�˳��
 * @������uint16_t value��ת��ֵ
 * @����ֵ��uint32_t ת�����ֵ
 */
uint32_t __REV16(uint16_t value)
{
    __ASM("rev16 r0, r0");
    __ASM("bx lr");
}

/*
 * @��������__RBIT
 * @��������תһ��ֵ������λ˳��
 * @������uint32_t value��ת��ֵ
 * @����ֵ��uint32_t ת�����ֵ
 */
uint32_t __RBIT(uint32_t value)
{
    __ASM("rbit r0, r0");
    __ASM("bx lr");
}

/*
 * @��������__LDREXB
 * @������ LDR Exclusive
 * @������ uint8_t* address
 * @����ֵ�� uint8_t (*address)ֵ
 */
uint8_t __LDREXB(uint8_t *addr)
{
    __ASM("ldrexb r0, [r0]");
    __ASM("bx lr"); 
}

/*
 * @��������__LDREXH
 * @������LDR Exclusive
 * @������ uint16_t* address
 * @����ֵ��uint16_t (*address)ֵ
 *          Exclusive LDR ָ��
 */
uint16_t __LDREXH(uint16_t *addr)
{
    __ASM("ldrexh r0, [r0]");
    __ASM("bx lr");
}

/*
 * @��������__LDREXW
 * @������LDR Exclusive
 * @������ uint32_t* address
 * @����ֵ��uint32_t (*address)ֵ
 * Exclusive LDR ָ��
 */
uint32_t __LDREXW(uint32_t *addr)
{
    __ASM("ldrex r0, [r0]");
    __ASM("bx lr");
}

/*
 * @��������__STREXB
 * @������STR Exclusive
 * @������uint8_t *address
 * @������ uint8_t value���洢ֵ
 * @����ֵ��uint32_t �ɹ�/ʧ��
 * @Exclusive STR ָ��
 */
uint32_t __STREXB(uint8_t value, uint8_t *addr)
{
    __ASM("strexb r0, r0, [r1]");
    __ASM("bx lr");
}

/*
 * @��������__STREXH
 * @������ STR Exclusive
 * @������ uint16_t *address
 * @������ uint16_t value���洢ֵ
 * @����ֵ��uint32_t �ɹ�/ʧ��
 * @Exclusive STR ָ��
 */
uint32_t __STREXH(uint16_t value, uint16_t *addr)
{
    __ASM("strexh r0, r0, [r1]");
    __ASM("bx lr");
}

/*
 * @��������__STREXW
 * @������STR Exclusive
 * @������uint32_t *address
 * @������uint32_t value���洢ֵ
 * @����ֵ��uint32_t �ɹ�/ʧ��
 * @Exclusive STR ָ��
 */
uint32_t __STREXW(uint32_t value, uint32_t *addr)
{
    __ASM("strex r0, r0, [r1]");
    __ASM("bx lr");
}

#pragma diag_default=Pe940
#elif (defined (__GNUC__))
/*
 * @��������__get_CONTROL
 * @��������ȡ���ƼĴ���ֵ
 * @��������
 * @����ֵ��uint32_t ���ƼĴ���ֵ
 * @���ؿ��ƼĴ�������
 */
uint32_t __get_CONTROL(void)
{
    uint32_t result=0;

    __ASM volatile ("MRS %0, control" : "=r" (result) );

    return(result);
}

/*
 * @��������__set_CONTROL
 * @���������ÿ��ƼĴ���
 * @������ uint32_t ���ƼĴ���ֵ
 * @����ֵ����
 * @���ÿ��ƼĴ���
 */
void __set_CONTROL(uint32_t control)
{
    __ASM volatile ("MSR control, %0" : : "r" (control) );
}

/*
 * @��������__get_PSP
 * @���������ؽ��̶�ջָ��
 * @��������
 * @����ֵ��uint32_t ���̶�ջָ��
 *          ���ؽ��̶�ջָ��
 */
uint32_t __get_PSP(void)
{
    uint32_t result=0;
  
    __ASM volatile ("MRS %0, psp" : "=r" (result) );

    return(result);
}

/*
 * @��������__set_PSP
 * @���������ý��̶�ջָ��
 * @������uint32_t P���̶�ջָ��
 * @����ֵ����
 * @����һ�����̶�ջָ���MSP����ջָ��Ĵ���
 */
void __set_PSP(uint32_t topOfProcStack)
{
    __ASM volatile ("MSR psp, %0" : : "r" (topOfProcStack) );
}

/*
 * @��������__get_MSP
 * @��������ȡ����ջָ��
 * @��������
 * @����ֵ��uint32_t ����ջָ��
 *          ��������ջָ��Ĵ�����ֵ
 */
uint32_t __get_MSP(void)
{
    uint32_t result=0;

    __ASM volatile ("MRS %0, msp" : "=r" (result) );

    return(result);
}

/*
 * @��������__set_MSP
 * @��������������ջָ��
 * @������uint32_t ����ջָ��
 * @����ֵ����
 *          ����һ������ջָ���MSP����ջָ��Ĵ���
 */
void __set_MSP(uint32_t topOfMainStack)
{
    __ASM volatile ("MSR msp, %0" : : "r" (topOfMainStack) );
}

/*
 * @��������__get_BASEPRI
 * @���������ػ����ȼ�ֵ
 * @��������
 * @����ֵ��uint32_t �����ȼ�
 *          ���ػ����ȼ��Ĵ���ֵ
 */
uint32_t __get_BASEPRI(void)
{
    uint32_t result=0;
  
    __ASM volatile ("MRS %0, basepri_max" : "=r" (result) );

    return(result);
}

/*
 * @��������__set_BASEPRI
 * @���������û����ȼ��Ĵ���
 * @������uint32_t �����ȼ�
 * @����ֵ����
 *          ���û����ȼ��Ĵ���
 */
void __set_BASEPRI(uint32_t value)
{
    __ASM volatile ("MSR basepri, %0" : : "r" (value) );
}

/*
 * @��������__get_PRIMASK
 * @��������ȡ���ȼ�����ֵ
 * @��������
 * @����ֵ��uint32_t PriMask
 *          �������ȼ����μĴ�������״̬
 */
uint32_t __get_PRIMASK(void)
{
    uint32_t result=0;
  
    __ASM volatile ("MRS %0, primask" : "=r" (result) );

    return(result);
}

/*
 * @�������� __set_PRIMASK
 * @�������������ȼ�����λ
 * @������uint32_t PriMask
 * @����ֵ����
 *          �������ȼ����μĴ���
 */
void __set_PRIMASK(uint32_t priMask)
{
    __ASM volatile ("MSR primask, %0" : : "r" (priMask) );
}

/*
 * @��������__get_FAULTMASK
 * @���������ع�������״̬
 * @��������
 * @����ֵ��uint32_t FaultMask
 *          ���ع������μĴ���ֵ
 */
uint32_t __get_FAULTMASK(void)
{
    uint32_t result=0;
  
    __ASM volatile ("MRS %0, faultmask" : "=r" (result) );

    return(result);
}

/*
 * @��������__set_FAULTMASK
 * @���������ù�������λ
 * @������uint32_t ��������ֵ
 * @����ֵ����
 *          ���ù������μĴ���
 */
void __set_FAULTMASK(uint32_t faultMask)
{
    __ASM volatile ("MSR faultmask, %0" : : "r" (faultMask) );
}

/*
 * @��������__REV
 * @��������ת����ֵ�ֽ�˳��
 * @������uint32_t value��ת��ֵ
 * @����ֵ��uint32_t ת�����ֵ
 *          ��ת����ֵ�ֽ�˳��
 */
uint32_t __REV(uint32_t value)
{
    uint32_t result=0;
  
    __ASM volatile ("rev %0, %1" : "=r" (result) : "r" (value) );

    return(result);
}

/*
 * @��������  __REV16
 * @��������תunsigned short����ֵ�ֽ�˳��
 * @������uint16_t value��ת��ֵ
 * @����ֵ��uint32_t ת�����ֵ
 *          ��תunsigned short����ֵ�ֽ�˳��
 */
uint32_t __REV16(uint16_t value)
{
    uint32_t result=0;
  
    __ASM volatile ("rev16 %0, %1" : "=r" (result) : "r" (value) );

    return(result);
}

/*
 * @��������__REVSH
 * @��������תsigned short����ֵ�����з�����չ
 * @������ int32_t value��ת��ֵ
 * @����ֵ��int32_t ת�����ֵ 
 *          ��תsigned short����ֵ�����з�����չ
 */
int32_t __REVSH(int16_t value)
{
    uint32_t result=0;
  
    __ASM volatile ("revsh %0, %1" : "=r" (result) : "r" (value) );

    return(result);
}

/*
 * @��������__RBIT
 * @��������תλ��
 * @������ uint32_t value��ת��ֵ
 * @����ֵ��uint32_t ת�����ֵ
 *          ��תλ��
 */
uint32_t __RBIT(uint32_t value)
{
    uint32_t result=0;
  
    __ASM volatile ("rbit %0, %1" : "=r" (result) : "r" (value) );

    return(result);
}


/*
 * @��������__LDREXB
 * @������LDR Exclusive
 * @������ uint8_t* address
 * @����ֵ��uint8_t (*address)ֵ
 *          Exclusive LDR ָ��
 */
uint8_t __LDREXB(uint8_t *addr)
{
    uint8_t result=0;
  
    __ASM volatile ("ldrexb %0, [%1]" : "=r" (result) : "r" (addr) );

    return(result);
}

/*
 * @��������__LDREXH
 * @������LDR Exclusive
 * @������ uint16_t* address
 * @����ֵ��uint16_t (*address)ֵ
 *          Exclusive LDR ָ��
 */
uint16_t __LDREXH(uint16_t *addr)
{
    uint16_t result=0;
  
    __ASM volatile ("ldrexh %0, [%1]" : "=r" (result) : "r" (addr) );

    return(result);
}

/*
 * @��������__LDREXW
 * @������LDR Exclusive
 * @������uint32_t* address
 * @����ֵ��uint32_t (*address)ֵ
 *          Exclusive LDR ָ��
 */
uint32_t __LDREXW(uint32_t *addr)
{
    uint32_t result=0;
  
    __ASM volatile ("ldrex %0, [%1]" : "=r" (result) : "r" (addr) );

    return(result);
}

/*
 * @��������__STREXB
 * @������STR Exclusive
 * @������uint8_t *address
 * @������uint8_t value���洢ֵ
 * @����ֵ��uint32_t �ɹ�/ʧ��
 *          Exclusive STR ָ��
 */
uint32_t __STREXB(uint8_t value, uint8_t *addr)
{
    uint32_t result=0;
  
    __ASM volatile ("strexb %0, %2, [%1]" : "=r" (result) : "r" (addr), "r" (value) );

    return(result);
}

/*
 * @��������__STREXH
 * @������STR Exclusive
 * @������ uint16_t *address
 * @������ uint16_t value���洢ֵ
 * @����ֵ��uint32_t �ɹ�/ʧ��
 *          Exclusive STR ָ��
 */
uint32_t __STREXH(uint16_t value, uint16_t *addr)
{
    uint32_t result=0;
  
    __ASM volatile ("strexh %0, %2, [%1]" : "=r" (result) : "r" (addr), "r" (value) );

    return(result);
}

/*
 * @��������__STREXW
 * @������STR Exclusive
 * @������uint32_t *address
 * @������uint32_t value���洢ֵ
 * @����ֵ��uint32_t �ɹ�/ʧ��
 *          Exclusive STR ָ��
 */
uint32_t __STREXW(uint32_t value, uint32_t *addr)
{
    uint32_t result=0;
  
    __ASM volatile ("strex %0, %2, [%1]" : "=r" (result) : "r" (addr), "r" (value) );

    return(result);
}


#endif

