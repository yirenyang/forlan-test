/*
 * LPC11xx.h - LPC11xx.h config header file;
 *
 * Copyright (c) 2014 Forlan.yung(YANGHUALIANG)
 *
 */
 
#ifndef _LPC11xx_H_
#define _LPC11xx_H_
/****************************************************************************
      �жϺŶ���
****************************************************************************/
typedef enum IRQn
{
    /* Cortex-M3�������쳣�� */
    NonMaskableInt_IRQn           = -14,      /*!< 2 ���������ж�               */
    MemoryManagement_IRQn         = -12,      /*!< 4 Cortex-M0�洢����������ж�*/
    BusFault_IRQn                 = -11,      /*!< 5 Cortex-M0���߹����ж�      */
    UsageFault_IRQn               = -10,      /*!< 6 Cortex-M0�÷������ж�      */
    SVCall_IRQn                   = -5,       /*!< 11 Cortex-M0 SV Call�ж�     */
    DebugMonitor_IRQn             = -4,       /*!< 12 Cortex-M0 DebugMonitor�ж�*/
    PendSV_IRQn                   = -2,       /*!< 14 Cortex-M0 Pend SV�ж�     */
    SysTick_IRQn                  = -1,       /*!< 15 Cortex-M0 SystemTick�ж�  */

    /* LPC11xx �ⲿ�жϺ� */
    WAKEUP0_IRQn                  = 0,        /*!< ���е�I/O���Ŷ�����������Դ  */
    WAKEUP1_IRQn                  = 1,
    WAKEUP2_IRQn                  = 2,
    WAKEUP3_IRQn                  = 3,
    WAKEUP4_IRQn                  = 4,
    WAKEUP5_IRQn                  = 5,
    WAKEUP6_IRQn                  = 6,
    WAKEUP7_IRQn                  = 7,
    WAKEUP8_IRQn                  = 8,
    WAKEUP9_IRQn                  = 9,
    WAKEUP10_IRQn                 = 10,
    WAKEUP11_IRQn                 = 11,
    WAKEUP12_IRQn                 = 12,
    CAN_IRQn                      = 13,       /*!< CAN �ж�                     */
    SSP1_IRQn                     = 14,       /*!< SSP1 �ж�                    */
    I2C_IRQn                      = 15,       /*!< I2C �ж�                     */
    TIMER_16_0_IRQn               = 16,       /*!< 16-bit Timer0 �ж�           */
    TIMER_16_1_IRQn               = 17,       /*!< 16-bit Timer1 �ж�           */
    TIMER_32_0_IRQn               = 18,       /*!< 32-bit Timer0 �ж�           */
    TIMER_32_1_IRQn               = 19,       /*!< 32-bit Timer1 �ж�           */
    SSP0_IRQn                     = 20,       /*!< SSP0 �ж�                    */
    UART_IRQn                     = 21,       /*!< UART �ж�                    */
    USB_IRQn                      = 22,       /*!< USB�����ж�                  */
    USB_FIQn                      = 23,       /*!< USB�����ж�                  */
    ADC_IRQn                      = 24,       /*!< A/D ת���ж�                 */
    WDT_IRQn                      = 25,       /*!< Watchdog��ʱ���ж�           */  
    BOD_IRQn                      = 26,       /*!< Brown Out Detect(BOD)�ж�    */
    RESERVED_IRQn                 = 27,       /*!< ����                         */
    EINT3_IRQn                    = 28,       /*!< �ⲿPIO3�ж�                 */
    EINT2_IRQn                    = 29,       /*!< �ⲿPIO2�ж�                 */
    EINT1_IRQn                    = 30,       /*!< �ⲿPIO1�ж�                 */
    EINT0_IRQn                    = 31,       /*!< �ⲿPIO0�ж�                 */
} IRQn_Type;


/****************************************************************************
      ���������ں���Χ����
****************************************************************************/
/* Cortex-M0���������ں���Χ���� */
#define __MPU_PRESENT             1         /*!< MPU�л���                    */
#define __NVIC_PRIO_BITS          5         /*!< ���ȼ�λ������               */
#define __Vendor_SysTickConfig    1         /*!< ʹ�ܲ�ͬ�ĵδ����ã���λ��λ */


#include "core_cm0.h"                       /* Cortex-M0���������ں���Χ      */
#include "system_LPC11xx.h"            


/****************************************************************************
      ����������
****************************************************************************/
extern void SystemInit (void);


/****************************************************************************
      ��Χ�豸�Ĵ���
****************************************************************************/
#pragma anon_unions


/****************************************************************************
      ϵͳ���� (SYSCON)
****************************************************************************/
typedef struct
{
    __IO uint32_t SYSMEMREMAP;     /* ϵͳ�洢����ӳ�䣬ƫ��0x0 */
    __IO uint32_t PRESETCTRL;
    __IO uint32_t SYSPLLCTRL;      /* ϵͳPLL���� */
    __IO uint32_t SYSPLLSTAT;
    __IO uint32_t USBPLLCTRL;      /* USB PLL���ƣ�ƫ��0x10 */
    __IO uint32_t USBPLLSTAT;
         uint32_t RESERVED0[2];

    __IO uint32_t SYSOSCCTRL;      /* ƫ�� 0x20 */
    __IO uint32_t WDTOSCCTRL;
    __IO uint32_t IRCCTRL;
         uint32_t RESERVED1[1];
    __IO uint32_t SYSRESSTAT;      /* ƫ�� 0x30 */
         uint32_t RESERVED2[3];
    __IO uint32_t SYSPLLCLKSEL;    /* ƫ�� 0x40 */	
    __IO uint32_t SYSPLLCLKUEN;
    __IO uint32_t USBPLLCLKSEL;
    __IO uint32_t USBPLLCLKUEN;
         uint32_t RESERVED3[8];

    __IO uint32_t MAINCLKSEL;      /* ƫ�� 0x70 */
    __IO uint32_t MAINCLKUEN;
    __IO uint32_t SYSAHBCLKDIV;
         uint32_t RESERVED4[1];

    __IO uint32_t SYSAHBCLKCTRL;   /* ƫ�� 0x80 */
         uint32_t RESERVED5[4];
    __IO uint32_t SSP0CLKDIV;           
    __IO uint32_t UARTCLKDIV;
    __IO uint32_t SSP1CLKDIV;
         uint32_t RESERVED6[3];
    __IO uint32_t TRACECLKDIV;

    __IO uint32_t SYSTICKCLKDIV;   /* ƫ�� 0xB0 */           
         uint32_t RESERVED7[3];

    __IO uint32_t USBCLKSEL;       /* ƫ�� 0xC0 */ 
    __IO uint32_t USBCLKUEN;
    __IO uint32_t USBCLKDIV;
         uint32_t RESERVED8[1];
    __IO uint32_t WDTCLKSEL;       /* ƫ�� 0xD0 */
    __IO uint32_t WDTCLKUEN;
    __IO uint32_t WDTCLKDIV;
         uint32_t RESERVED9[1];         
    __IO uint32_t CLKOUTCLKSEL;    /* ƫ�� 0xE0 */
    __IO uint32_t CLKOUTUEN;
    __IO uint32_t CLKOUTDIV;      
         uint32_t RESERVED10[5];
  
    __IO uint32_t PIOPORCAP0;      /* ƫ�� 0x100 */           
    __IO uint32_t PIOPORCAP1;
         uint32_t RESERVED11[18];

    __IO uint32_t BODCTRL;         /* ƫ�� 0x150 */
         uint32_t RESERVED12[1];
    __IO uint32_t SYSTCKCAL;
         uint32_t RESERVED13[5];
    __IO uint32_t INT_IRQ_LATENCY; /* ƫ�� 0x170 */
         uint32_t RESERVED14[35];

    __IO uint32_t STARTAPRP0;      /* ƫ�� 0x200 */     
    __IO uint32_t STARTERP0;    
    __IO uint32_t STARTRSRP0CLR;
    __IO uint32_t STARTSRP0;
    __IO uint32_t STARTAPRP1;   
    __IO uint32_t STARTERP1;
    __IO uint32_t STARTRSRP1CLR;
    __IO uint32_t STARTSRP1;
         uint32_t RESERVED15[4];

    __IO uint32_t PDSLEEPCFG;      /* ƫ�� 0x230 */
    __IO uint32_t PDAWAKECFG;      
    __IO uint32_t PDRUNCFG;
         uint32_t RESERVED16[110];
    __I  uint32_t DEVICE_ID;
} LPC_SYSCON_TypeDef;


/****************************************************************************
      �������� (IOCON)
****************************************************************************/
typedef struct
{
    __IO uint32_t PIO2_6;
         uint32_t RESERVED0[1];
    __IO uint32_t PIO2_0;
    __IO uint32_t RESET_PIO0_0;
    __IO uint32_t PIO0_1;
    __IO uint32_t PIO1_8;
         uint32_t RESERVED1[1];
    __IO uint32_t PIO0_2;

    __IO uint32_t PIO2_7;
    __IO uint32_t PIO2_8;
    __IO uint32_t PIO2_1;
    __IO uint32_t PIO0_3;
    __IO uint32_t PIO0_4;
    __IO uint32_t PIO0_5;
    __IO uint32_t PIO1_9;
    __IO uint32_t PIO3_4;

    __IO uint32_t PIO2_4;
    __IO uint32_t PIO2_5;
    __IO uint32_t PIO3_5;
    __IO uint32_t PIO0_6;
    __IO uint32_t PIO0_7;
    __IO uint32_t PIO2_9;
    __IO uint32_t PIO2_10;
    __IO uint32_t PIO2_2;

    __IO uint32_t PIO0_8;
    __IO uint32_t PIO0_9;
    __IO uint32_t JTAG_TCK_PIO0_10;
    __IO uint32_t PIO1_10;
    __IO uint32_t PIO2_11;
    __IO uint32_t JTAG_TDI_PIO0_11;
    __IO uint32_t JTAG_TMS_PIO1_0;
    __IO uint32_t JTAG_TDO_PIO1_1;

    __IO uint32_t JTAG_nTRST_PIO1_2;
    __IO uint32_t PIO3_0;
    __IO uint32_t PIO3_1;
    __IO uint32_t PIO2_3;
    __IO uint32_t ARM_SWDIO_PIO1_3;
    __IO uint32_t PIO1_4;
    __IO uint32_t PIO1_11;
    __IO uint32_t PIO3_2;

    __IO uint32_t PIO1_5;
    __IO uint32_t PIO1_6;
    __IO uint32_t PIO1_7;
    __IO uint32_t PIO3_3;
    __IO uint32_t SCKLOC; 
    __IO uint32_t DSRLOC;
    __IO uint32_t DCDLOC;
    __IO uint32_t RILOC;
} LPC_IOCON_TypeDef;


/****************************************************************************
      ��Դ����Ԫ (PMU)
****************************************************************************/
typedef struct
{
    __IO uint32_t PCON;
    __IO uint32_t GPREG0;
    __IO uint32_t GPREG1;
    __IO uint32_t GPREG2;
    __IO uint32_t GPREG3;
    __IO uint32_t GPREG4;
} LPC_PMU_TypeDef;


/****************************************************************************
      ͨ��IO (GPIO)
****************************************************************************/
typedef struct
{
    union
    {
        __IO uint32_t MASKED_ACCESS[4096];
        struct
        {
            uint32_t RESERVED0[4095];
            __IO uint32_t DATA;
        };
    };

    uint32_t RESERVED1[4096];
    __IO uint32_t DIR;
    __IO uint32_t IS;
    __IO uint32_t IBE;
    __IO uint32_t IEV;
    __IO uint32_t IE;
    __IO uint32_t RIS;
    __IO uint32_t MIS;
    __IO uint32_t IC;
} LPC_GPIO_TypeDef;


/****************************************************************************
      ��ʱ�� (TMR)
****************************************************************************/
typedef struct
{
    __IO uint32_t IR;
    __IO uint32_t TCR;
    __IO uint32_t TC;
    __IO uint32_t PR;
    __IO uint32_t PC;
    __IO uint32_t MCR;
    __IO uint32_t MR0;
    __IO uint32_t MR1;
    __IO uint32_t MR2;
    __IO uint32_t MR3;
    __IO uint32_t CCR;
    __I  uint32_t CR0;
         uint32_t RESERVED1[3];
    __IO uint32_t EMR;
         uint32_t RESERVED2[12];
    __IO uint32_t CTCR;
    __IO uint32_t PWMC;
} LPC_TMR_TypeDef;


/****************************************************************************
      ͨ���첽�շ���(UART)
****************************************************************************/
typedef struct
{
    union
    {
        __I  uint32_t RBR;
        __O  uint32_t THR;
        __IO uint32_t DLL;
    };

    union
    {
        __IO uint32_t DLM;
        __IO uint32_t IER;
    };

    union
    {
        __I  uint32_t IIR;
        __O  uint32_t FCR;
    };

    __IO uint32_t LCR;
    __IO uint32_t MCR;
    __I  uint32_t LSR;
    __I  uint32_t MSR;
    __IO uint32_t SCR;
    __IO uint32_t ACR;
    __IO uint32_t ICR;
    __IO uint32_t FDR;
         uint32_t RESERVED0;
    __IO uint32_t TER;
         uint32_t RESERVED1[6];
    __IO uint32_t RS485CTRL;
    __IO uint32_t ADRMATCH;
    __IO uint32_t RS485DLY;
    __I  uint32_t FIFOLVL;
} LPC_UART_TypeDef;


/****************************************************************************
      ͬ������ͨ�� (SSP)
****************************************************************************/
typedef struct
{
    __IO uint32_t CR0;
    __IO uint32_t CR1;
    __IO uint32_t DR;
     __I  uint32_t SR;
    __IO uint32_t CPSR;
    __IO uint32_t IMSC;
    __IO uint32_t RIS;
    __IO uint32_t MIS;
    __IO uint32_t ICR;
} LPC_SSP_TypeDef;


/****************************************************************************
      I2C
****************************************************************************/
typedef __packed struct
{
    __IO uint32_t CONSET;
    __I  uint32_t STAT;
    __IO uint32_t DAT;
    __IO uint32_t ADR0;
    __IO uint32_t SCLH;
    __IO uint32_t SCLL;
    __O  uint32_t CONCLR;
    __IO uint32_t MMCTRL;
    __IO uint32_t ADR1;
    __IO uint32_t ADR2;
    __IO uint32_t ADR3;
    __I  uint32_t DATA_BUFFER;
    __IO uint32_t MASK0;
    __IO uint32_t MASK1;
    __IO uint32_t MASK2;
    __IO uint32_t MASK3;
} LPC_I2C_TypeDef;


/****************************************************************************
      ���Ź���ʱ�� (WDT)
****************************************************************************/
typedef struct
{
    __IO uint32_t MOD;
    __IO uint32_t TC;
    __O  uint32_t FEED;
    __I  uint32_t TV;
} LPC_WDT_TypeDef;


/****************************************************************************
      ģ��ת���� (ADC)
****************************************************************************/
typedef struct
{
    __IO uint32_t CR;
    __IO uint32_t GDR;
         uint32_t RESERVED0;
    __IO uint32_t INTEN;
    __I  uint32_t DR0;
    __I  uint32_t DR1;
    __I  uint32_t DR2;
    __I  uint32_t DR3;
    __I  uint32_t DR4;
    __I  uint32_t DR5;
    __I  uint32_t DR6;
    __I  uint32_t DR7;
    __I  uint32_t STAT;
} LPC_ADC_TypeDef;


/****************************************************************************
      CAN������ (CAN)
****************************************************************************/
typedef struct
{
    __IO uint32_t CNTL;				    /* 0x000 */
    __IO uint32_t STAT;
    __IO uint32_t EC;
    __IO uint32_t BT;
    __IO uint32_t INT;
    __IO uint32_t TEST;
    __IO uint32_t BRPE;
         uint32_t RESERVED0;
    __IO uint32_t IF1_CMDREQ;			/* 0x020 */
    __IO uint32_t IF1_CMDMSK;
    __IO uint32_t IF1_MSK1;
    __IO uint32_t IF1_MSK2;
    __IO uint32_t IF1_ARB1;
    __IO uint32_t IF1_ARB2;
    __IO uint32_t IF1_MCTRL;
    __IO uint32_t IF1_DA1;
    __IO uint32_t IF1_DA2;
    __IO uint32_t IF1_DB1;
    __IO uint32_t IF1_DB2;
         uint32_t RESERVED1[13];   
    __IO uint32_t IF2_CMDREQ;			/* 0x080 */
    __IO uint32_t IF2_CMDMSK;
    __IO uint32_t IF2_MSK1;
    __IO uint32_t IF2_MSK2;
    __IO uint32_t IF2_ARB1;
    __IO uint32_t IF2_ARB2;
    __IO uint32_t IF2_MCTRL;
    __IO uint32_t IF2_DA1;
    __IO uint32_t IF2_DA2;
    __IO uint32_t IF2_DB1;
    __IO uint32_t IF2_DB2;
         uint32_t RESERVED2[21];
    __I  uint32_t TXREQ1;				/* 0x100 */
    __I  uint32_t TXREQ2;
         uint32_t RESERVED3[6];
    __I  uint32_t ND1;				    /* 0x120 */
    __I  uint32_t ND2;
         uint32_t RESERVED4[6];
    __I  uint32_t IR1;				    /* 0x140 */
    __I  uint32_t IR2;
         uint32_t RESERVED5[6];
    __I  uint32_t MSGV1;				/* 0x160 */
    __I  uint32_t MSGV2;
         uint32_t RESERVED6[6];
    __IO uint32_t CLKDIV;				/* 0x180 */
} LPC_CAN_TypeDef;


/****************************************************************************
      ͨ�ô������� (USB)
****************************************************************************/
typedef struct
{
    __I  uint32_t DevIntSt;            /* USB�豸�жϼĴ���                     */
    __IO uint32_t DevIntEn;
    __O  uint32_t DevIntClr;
    __O  uint32_t DevIntSet;
 
    __O  uint32_t CmdCode;             /* USB�豸SIE����Ĵ���                  */
    __I  uint32_t CmdData;

    __I  uint32_t RxData;              /* USB�豸���ͼĴ���                     */
    __O  uint32_t TxData;
    __I  uint32_t RxPLen;
    __O  uint32_t TxPLen;
    __IO uint32_t Ctrl;
    __O  uint32_t DevFIQSel;
} LPC_USB_TypeDef;


#pragma no_anon_unions
/****************************************************************************
      ��Χ�洢��ӳ�� 
****************************************************************************/
/* ����ַ */
#define LPC_FLASH_BASE            (0x00000000UL)
#define LPC_RAM_BASE              (0x10000000UL)
#define LPC_APB0_BASE             (0x40000000UL)
#define LPC_AHB_BASE              (0x50000000UL)

/* APB0��Χ */
#define LPC_I2C_BASE              (LPC_APB0_BASE + 0x00000)
#define LPC_WDT_BASE              (LPC_APB0_BASE + 0x04000)
#define LPC_UART_BASE             (LPC_APB0_BASE + 0x08000)
#define LPC_CT16B0_BASE           (LPC_APB0_BASE + 0x0C000)
#define LPC_CT16B1_BASE           (LPC_APB0_BASE + 0x10000)
#define LPC_CT32B0_BASE           (LPC_APB0_BASE + 0x14000)
#define LPC_CT32B1_BASE           (LPC_APB0_BASE + 0x18000)
#define LPC_ADC_BASE              (LPC_APB0_BASE + 0x1C000)
#define LPC_USB_BASE              (LPC_APB0_BASE + 0x20000)
#define LPC_PMU_BASE              (LPC_APB0_BASE + 0x38000)
#define LPC_SSP0_BASE             (LPC_APB0_BASE + 0x40000)
#define LPC_IOCON_BASE            (LPC_APB0_BASE + 0x44000)
#define LPC_SYSCON_BASE           (LPC_APB0_BASE + 0x48000)
#define LPC_CAN_BASE              (LPC_APB0_BASE + 0x50000)
#define LPC_SSP1_BASE             (LPC_APB0_BASE + 0x58000)

/* AHB��Χ */	
#define LPC_GPIO_BASE             (LPC_AHB_BASE  + 0x00000)
#define LPC_GPIO0_BASE            (LPC_AHB_BASE  + 0x00000)
#define LPC_GPIO1_BASE            (LPC_AHB_BASE  + 0x10000)
#define LPC_GPIO2_BASE            (LPC_AHB_BASE  + 0x20000)
#define LPC_GPIO3_BASE            (LPC_AHB_BASE  + 0x30000)


/****************************************************************************
      ��Χ���� 
****************************************************************************/
#define LPC_I2C                   ((LPC_I2C_TypeDef    *) LPC_I2C_BASE   )
#define LPC_WDT                   ((LPC_WDT_TypeDef    *) LPC_WDT_BASE   )
#define LPC_UART                  ((LPC_UART_TypeDef   *) LPC_UART_BASE  )
#define LPC_TMR16B0               ((LPC_TMR_TypeDef    *) LPC_CT16B0_BASE)
#define LPC_TMR16B1               ((LPC_TMR_TypeDef    *) LPC_CT16B1_BASE)
#define LPC_TMR32B0               ((LPC_TMR_TypeDef    *) LPC_CT32B0_BASE)
#define LPC_TMR32B1               ((LPC_TMR_TypeDef    *) LPC_CT32B1_BASE)
#define LPC_ADC                   ((LPC_ADC_TypeDef    *) LPC_ADC_BASE   )
#define LPC_PMU                   ((LPC_PMU_TypeDef    *) LPC_PMU_BASE   )
#define LPC_SSP0                  ((LPC_SSP_TypeDef    *) LPC_SSP0_BASE  )
#define LPC_SSP1                  ((LPC_SSP_TypeDef    *) LPC_SSP1_BASE  )
#define LPC_CAN                   ((LPC_CAN_TypeDef    *) LPC_CAN_BASE   )
#define LPC_IOCON                 ((LPC_IOCON_TypeDef  *) LPC_IOCON_BASE )
#define LPC_SYSCON                ((LPC_SYSCON_TypeDef *) LPC_SYSCON_BASE)
#define LPC_USB                   ((LPC_USB_TypeDef    *) LPC_USB_BASE   )

#define LPC_GPIO0                 ((LPC_GPIO_TypeDef   *) LPC_GPIO0_BASE )
#define LPC_GPIO1                 ((LPC_GPIO_TypeDef   *) LPC_GPIO1_BASE )
#define LPC_GPIO2                 ((LPC_GPIO_TypeDef   *) LPC_GPIO2_BASE )
#define LPC_GPIO3                 ((LPC_GPIO_TypeDef   *) LPC_GPIO3_BASE )


#endif  // __LPC11xx_H__

