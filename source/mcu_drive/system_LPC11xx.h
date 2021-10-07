/*
 * system-LPC11xx.h - system-LPC11xx.h config header file;
 *
 * Copyright (c) 2014 Forlan.yung(YANGHUALIANG)
 *
 */

#ifndef _SYSTEM_LPC11XX_H_
#define _SYSTEM_LPC11XX_H_


/****************************************************************************
      常量申明区
****************************************************************************/
/* Define the NVIC table address */
#define NVIC_VectTab_RAM             		    (0x10000000)
#define NVIC_VectTab_FLASH           		    (0x00000000)

/* Define the system memory remap */
#define SYSMEMREMAP_VAL_BOOT_LOADER_MODE        0x00000000
#define SYSMEMREMAP_VAL_USER_RAM_MODE           0x00000001
#define SYSMEMREMAP_VAL_USER_FLASH_MODE         0x00000002

/* Define the peripheral reset control register bits */
#define PRESETCTRL_SSP0_RST_N_BIT_OFFSET_VAL    0
#define PRESETCTRL_I2C_RST_N_BIT_OFFSET_VAL     1
#define PRESETCTRL_SSP1_RST_N_BIT_OFFSET_VAL    2
#define PRESETCTRL_CAN_RST_N_BIT_OFFSET_VAL     3

/* Define the system oscillator control register */
#define SYSOSCCTRL_SYS_OSC_NOT_BYPASS           0x00000000
#define SYSOSCCTRL_SYS_OSC_BYPASS               0x00000001
#define SYSOSCCTRL_FREQRANGE_VAL_1_20M          0x00000000
#define SYSOSCCTRL_FREQRANGE_VAL_15_25M         0x00000002

/* Define the bits in the PDRUNCFG register */
#define PDRUNCFG_IFCONT_PD_BIT_VAL              0
#define PDRUNCFG_IRC_PD_BIT_VAL                 1
#define PDRUNCFG_FLASH_PD_BIT_VAL               2
#define PDRUNCFG_BOD_PD_BIT_VAL                 3
#define PDRUNCFG_ADC_PD_BIT_VAL                 4
#define PDRUNCFG_SYSOSC_PD_BIT_VAL              5
#define PDRUNCFG_WDTOSC_PD_BIT_VAL              6
#define PDRUNCFG_SYSPLL_PD_BIT_VAL              7

/* System PLL clock source value */
#define SYSPLLCLKSEL_SRC_VAL_IRC_OSC            0x00000000
#define SYSPLLCLKSEL_SRC_VAL_SYS_OSC            0x00000001

/* Main clock source select value */
#define MAINCLKSEL_SRC_VAL_IRC_OSC              0x00000000
#define MAINCLKSEL_SRC_VAL_INT_CLK_TO_PLL       0x00000001
#define MAINCLKSEL_SRC_VAL_WDT_OSC              0x00000002
#define MAINCLKSEL_SRC_VAL_PLL_CLK_OUT          0x00000003

/* Define the clock source update states */
#define CLOCK_UPDATE_STATE_NO_UPDATE            0x00
#define CLOCK_UPDATE_STATE_UPDATE               0x01

/*
 * System AHB clock divider value
 * 1: Divide by 1 to 255 Divide by 255
 */
#define SYSAHBCLKDIV_VAL_DISABLE_SYSCLK         0x00
#define SYSAHBCLKDIV_VAL_SET_001                0x01
#define SYSAHBCLKDIV_VAL_SET_002                0x02
#define SYSAHBCLKDIV_VAL_SET_003                0x03
#define SYSAHBCLKDIV_VAL_SET_004                0x04

/* Define system AHB clock control register bits */
#define SYSAHBCLKCTRL_SYS_BIT_OFFSET_VAL			0
#define SYSAHBCLKCTRL_ROM_BIT_OFFSET_VAL			1
#define SYSAHBCLKCTRL_RAM_BIT_OFFSET_VAL			2
#define SYSAHBCLKCTRL_FLASHREG_BIT_OFFSET_VAL		3
#define SYSAHBCLKCTRL_FLASHARRAY_BIT_OFFSET_VAL		4
#define SYSAHBCLKCTRL_I2C_BIT_OFFSET_VAL            5
#define SYSAHBCLKCTRL_GPIO_BIT_OFFSET_VAL			6
#define SYSAHBCLKCTRL_CT16B0_BIT_OFFSET_VAL			7
#define SYSAHBCLKCTRL_CT16B1_BIT_OFFSET_VAL			8
#define SYSAHBCLKCTRL_CT32B0_BIT_OFFSET_VAL			9
#define SYSAHBCLKCTRL_CT32B1_BIT_OFFSET_VAL			10
#define SYSAHBCLKCTRL_SSP0_BIT_OFFSET_VAL			11
#define SYSAHBCLKCTRL_UART_BIT_OFFSET_VAL			12
#define SYSAHBCLKCTRL_ADC_BIT_OFFSET_VAL			13
#define SYSAHBCLKCTRL_WDT_BIT_OFFSET_VAL			15
#define SYSAHBCLKCTRL_IOCON_BIT_OFFSET_VAL			16
#define SYSAHBCLKCTRL_CAN_BIT_OFFSET_VAL            17
#define SYSAHBCLKCTRL_SSP1_BIT_OFFSET_VAL           18

/*
 * MSEL -- Feedback divider value. The division value M is the 
 * programmed MSEL value + 1.
 * 00000: Division ratio M = 1 to 11111: Division ratio M = 32.
 * You can define the value by youself as follows format.
 */
#define SYSPLLCTRL_MSEL_VAL_01                  0x00000000
#define SYSPLLCTRL_MSEL_VAL_02                  0x00000001
#define SYSPLLCTRL_MSEL_VAL_03                  0x00000002
#define SYSPLLCTRL_MSEL_VAL_04                  0x00000003
#define SYSPLLCTRL_MSEL_VAL_05                  0x00000004
#define SYSPLLCTRL_MSEL_VAL_06                  0x00000005
#define SYSPLLCTRL_MSEL_VAL_07                  0x00000006
#define SYSPLLCTRL_MSEL_VAL_08                  0x00000007

/* PSEL -- Post divider ratio p. The division ratio is 2 * P */
#define SYSPLLCTRL_PSEL_VAL_01                  0x00000000
#define SYSPLLCTRL_PSEL_VAL_02                  0x00000001
#define SYSPLLCTRL_PSEL_VAL_04                  0x00000002
#define SYSPLLCTRL_PSEL_VAL_08                  0x00000003

/* The system PLL control register bit set */
#define SYSPLLCTRL_MSEL_BIT_OFFSET_VAL          0
#define SYSPLLCTRL_PSEL_BIT_OFFSET_VAL          5

/* Define the system clock */
#define XTAL                                    (24000000UL)        /* 晶体振荡器频率 */
#define OSC_CLK                                 (      XTAL)        /* 主晶振频率 */
#define IRC_OSC                                 (12000000UL)        /* 内部RC晶振频率 */
#define WDT_OSC                                 (  250000UL)        /* 看门狗晶振频率 */

/* Watchdog clock source type define */
#define WDTCLKSEL_SRC_IRC_OSC			        0x00
#define WDTCLKSEL_SRC_MAIN_CLK			        0x01
#define WDTCLKSEL_SRC_WDT_OSC			        0x02

/* divider value for Fclkana */
#define WDTOSCCTRL_DIVSEL_VAL_02                0x00
#define WDTOSCCTRL_DIVSEL_VAL_04                0x01
#define WDTOSCCTRL_DIVSEL_VAL_06                0x02

/* Fclkana -- watchdog oscillator analog output frequency */
#define WDTOSCCTRL_FREQSEL_VAL_0_5M             0x01
#define WDTOSCCTRL_FREQSEL_VAL_0_8M             0x02
#define WDTOSCCTRL_FREQSEL_VAL_1_1M             0x03
#define WDTOSCCTRL_FREQSEL_VAL_2_0M             0x07

/* Watchodg oscillator control register bit set */
#define WDTOSCCTRL_DIVSET_BIT_OFFSET_VAL        0
#define WDTOSCCTRL_FREQSEL_BIT_OFFSET_VAL       5

/*
 * Watchdog clock divider value.
 * 0: Disable watchdog clock.
 * 1: Divide by 1 to 255 Divide by 255.
 */
#define WDTCLKDIV_VAL_DISABLE_WDCLK             0x00
#define WDTCLKDIV_VAL_SET_001                   0x01
#define WDTCLKDIV_VAL_SET_002                   0x02
#define WDTCLKDIV_VAL_SET_003                   0x03
#define WDTCLKDIV_VAL_SET_004                   0x04


/* Output clock source type define */
#define CLKOUTCLK_SRC_IRC_OSC		            0
#define CLKOUTCLK_SRC_SYS_OSC		            1
#define CLKOUTCLK_SRC_WDT_OSC		            2
#define CLKOUTCLK_SRC_MAIN_CLK		            3

/*
 * Clock output divider value.
 * 0: Disable clock output.
 * 1: Divide by 1 to 255 Divide by 255.
 */
#define CLKOUTCLKDIV_VAL_DISABLE_CLKOUT         0x00
#define CLKOUTCLKDIV_VAL_SET_001                0x01
#define CLKOUTCLKDIV_VAL_SET_002                0x02
#define CLKOUTCLKDIV_VAL_SET_003                0x03

/*
 * UART_PCLK -- UART  peripheral clock divider value
 * 0: Disable clock output.
 * 1: Divide by 1 to 255 Divide by 255.
 */
#define UARTCLKDIV_VAL_DISABLE_UART_PCLK        0x00
#define UARTCLKDIV_VAL_SET_001                  0x01
#define UARTCLKDIV_VAL_SET_002                  0x02
#define UARTCLKDIV_VAL_SET_003                  0x03

/****************************************************************************
      变量申明区
****************************************************************************/
extern uint32_t clock_source;
extern uint32_t main_clock_frequency;    		/*!< 系统时钟频率 (内核时钟)  */
extern uint32_t system_clock_frequency;


/****************************************************************************
      函数申明区
****************************************************************************/
extern void system_init(void);
extern void output_clock_setup (const uint32_t clk_src);

#endif

