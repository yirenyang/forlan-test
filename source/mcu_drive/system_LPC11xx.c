/*
 * system-LPC11xx.c - system-LPC11xx.c config and achieve;
 *
 * Copyright (c) 2014 Forlan.yung(YANGHUALIANG)
 *
 */

#include "include.h"


/****************************************************************************
      ����������
****************************************************************************/
uint32_t clock_source;
uint32_t main_clock_frequency;                 /* ϵͳʱ��Ƶ�� (�ں�ʱ��) */
uint32_t system_clock_frequency;


/****************************************************************************
      ����������
****************************************************************************/
static void system_oscillator_setup(void);
static void main_pll_clock_setup(void);
static void system_clock_setup(void);
  

/****************************************************************************
      ����������
****************************************************************************/
void system_init(void)
{
    /* Set the system memory remap register */
    #ifdef __DEBUG_RAM
    LPC_SYSCON->SYSMEMREMAP = SYSMEMREMAP_VAL_USER_RAM_MODE;            /* ��ӳ�䵽Ƭ��RAM */
    #else
    #ifdef __DEBUG_FLASH
    LPC_SYSCON->SYSMEMREMAP = SYSMEMREMAP_VAL_USER_FLASH_MODE;          /* ��ӳ�䵽Ƭ��flash */
    #endif
    #endif

    system_oscillator_setup();
    main_pll_clock_setup();
    system_clock_setup();

	AHB_clock_enable(SYSAHBCLKCTRL_IOCON_BIT_OFFSET_VAL);
}

static void system_oscillator_setup(void)
{
    uint32_t i;

    /*
     * Set the system oscillator control registor.
     * Select system oscillator for the input clock source
     * and the system oscillator frequency is 24MHz.
     */
    LPC_SYSCON->SYSOSCCTRL = SYSOSCCTRL_SYS_OSC_NOT_BYPASS | SYSOSCCTRL_FREQRANGE_VAL_15_25M;

    /* Set the SYSOSC_PD bit for system clock power on */
    LPC_SYSCON->PDRUNCFG &= ~(0x01 << PDRUNCFG_SYSOSC_PD_BIT_VAL);
    
    /* Wait the power on status steady */
    for (i = 0x00; i < 0x100; i++);
}

static void main_pll_clock_setup(void)
{
    uint32_t regVal;
    clock_source = OSC_CLK;

    /* Select the system PLL clock source */
    LPC_SYSCON->SYSPLLCLKSEL = SYSPLLCLKSEL_SRC_VAL_SYS_OSC;        /* ѡ��OSC */
    LPC_SYSCON->SYSPLLCLKUEN = CLOCK_UPDATE_STATE_UPDATE;           /* ����ʱ��Դ */
    LPC_SYSCON->SYSPLLCLKUEN = CLOCK_UPDATE_STATE_NO_UPDATE;        /* �л����¼Ĵ���һ�� */
    LPC_SYSCON->SYSPLLCLKUEN = CLOCK_UPDATE_STATE_UPDATE;
    while (!(LPC_SYSCON->SYSPLLCLKUEN & 0x01));                     /* �ȴ�������� */

    /*
     * Config the PLL system
     * The system frequency = clock_source * (SYSPLLCTRL_MSEL_VAL_02 + 1)
     * FCLKOUT = M x FCLKIN = (FCCO) / (2 x P)
     * FCCO range: 156 to 320 MHz
     * FCLKOUT MUST BE < 100MHz
     * For this system: OSCCLK = 24MHz, FCLKOUT = 48MHz, FCCO = 192MHz
     */
    regVal = LPC_SYSCON->SYSPLLCTRL;
    regVal &= ~0x1FF;
    LPC_SYSCON->SYSPLLCTRL = (regVal | (SYSPLLCTRL_PSEL_VAL_02 << SYSPLLCTRL_PSEL_BIT_OFFSET_VAL) | SYSPLLCTRL_MSEL_VAL_02);
  
    /* ʹ����ϵͳPLLʱ�ӣ���ϵͳPLLΪPDRUNCFG�Ĵ����е���λ */
    LPC_SYSCON->PDRUNCFG &= ~(0x01 << PDRUNCFG_SYSPLL_PD_BIT_VAL);
    while (!(LPC_SYSCON->SYSPLLSTAT & 0x01));	                    /* �ȴ�ֱ�������� */

    /*
     * Set the main clock source select register
     * Select the system pll clock for the main clock source
     */
    LPC_SYSCON->MAINCLKSEL = MAINCLKSEL_SRC_VAL_PLL_CLK_OUT;		/* PLLʱ�����ѡ�� */
    LPC_SYSCON->MAINCLKUEN = CLOCK_UPDATE_STATE_UPDATE;		        /* ����MCLKʱ��Դ  */
    LPC_SYSCON->MAINCLKUEN = CLOCK_UPDATE_STATE_NO_UPDATE;		    /* �л����¼Ĵ���һ�� */
    LPC_SYSCON->MAINCLKUEN = CLOCK_UPDATE_STATE_UPDATE;
    while (!(LPC_SYSCON->MAINCLKUEN & 0x01));	                    /* �ȴ�������� */

    main_clock_frequency = clock_source * (SYSPLLCTRL_MSEL_VAL_02 + 1);
}

static void system_clock_setup(void)
{
    /*
     * Set the system AHB clock divider register to 1
     * system clock = main clock = 48MHz
     */
    LPC_SYSCON->SYSAHBCLKDIV = SYSAHBCLKDIV_VAL_SET_001;             /* SYS AHBʱ�ӣ�����ֵΪ1��2��4 */

    system_clock_frequency = (uint32_t)(main_clock_frequency / SYSAHBCLKDIV_VAL_SET_001);
}

void output_clock_setup(const uint32_t clk_src)
{
    /* ������ɵ��� debug PLL */

    /* Select system oscillator for CLKOUT clock source */
    LPC_SYSCON->CLKOUTCLKSEL = clk_src;

    /* Output clock source update enable */
    LPC_SYSCON->CLKOUTUEN = CLOCK_UPDATE_STATE_UPDATE;              /* ����ʱ�� */
    LPC_SYSCON->CLKOUTUEN = CLOCK_UPDATE_STATE_NO_UPDATE;           /* �л����¼Ĵ���һ�� */
    LPC_SYSCON->CLKOUTUEN = CLOCK_UPDATE_STATE_UPDATE;
    while (!(LPC_SYSCON->CLKOUTUEN & 0x01));                        /* �ȴ�ֱ��������� */

    /* Disable the output clock */
    LPC_SYSCON->CLKOUTDIV = CLKOUTCLKDIV_VAL_DISABLE_CLKOUT;
}


