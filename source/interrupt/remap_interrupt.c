/*
 * Remap_interrupt.c - Remap_interrupt.c config and achieve;
 *
 * Copyright (c) 2014 Forlan.yung(YANGHUALIANG)
 *
 */

#include "include.h"


/****************************************************************************
      函数定义区
****************************************************************************/
/*
 * @brief NMI interrupt routine
 * @par Parameters:
 * None
 * @retval void None
 * @par Required preconditions:
 * None
 * @par Called functions:
 * None
 */
void NMI_Handler(void)
{
    remap_nmi_handler();
}

/*
 * @brief HardFault interrupt routine
 * @par Parameters:
 * None
 * @retval void None
 * @par Required preconditions:
 * None
 * @par Called functions:
 * None
 */
void HardFault_Handler(void)
{
    remap_hardfault_handler();
}

/*
 * @brief MemManage interrupt routine
 * @par Parameters:
 * None
 * @retval void None
 * @par Required preconditions:
 * None
 * @par Called functions:
 * None
 */
void MemManage_Handler(void)
{
    remap_memmanage_handler();
}

/*
 * @brief BusFault interrupt routine
 * @par Parameters:
 * None
 * @retval void None
 * @par Required preconditions:
 * None
 * @par Called functions:
 * None
 */
void BusFault_Handler(void)
{
    remap_busfault_handler();
}

/*
 * @brief UsageFault interrupt routine
 * @par Parameters:
 * None
 * @retval void None
 * @par Required preconditions:
 * None
 * @par Called functions:
 * None
 */
void UsageFault_Handler(void)
{
    remap_usagefault_handler();
}

/*
 * @brief SVC interrupt routine
 * @par Parameters:
 * None
 * @retval void None
 * @par Required preconditions:
 * None
 * @par Called functions:
 * None
 */
void SVC_Handler(void)
{
    remap_svc_handler();
}

/*
 * @brief SVC interrupt routine
 * @par Parameters:
 * None
 * @retval void None
 * @par Required preconditions:
 * None
 * @par Called functions:
 * None
 */
void DebugMon_Handler(void)
{
    remap_debugmon_handler();
}

/*
 * @brief pendsv interrupt routine
 * @par Parameters:
 * None
 * @retval void None
 * @par Required preconditions:
 * None
 * @par Called functions:
 * None
 */
void PendSV_Handler(void)
{
    remap_pendsv_handler();
}

/*
 * @brief SysTick interrupt routine
 * @par Parameters:
 * None
 * @retval void None
 * @par Required preconditions:
 * None
 * @par Called functions:
 * None
 */
void SysTick_Handler(void)
{
    remap_systick_handler();
}

/*
 * @brief CAN interrupt routine
 * @par Parameters:
 * None
 * @retval void None
 * @par Required preconditions:
 * None
 * @par Called functions:
 * None
 */
void CAN_IRQHandler(void)
{
    remap_can_irqhandler();
}

/*
 * @brief SSP1 interrupt routine
 * @par Parameters:
 * None
 * @retval void None
 * @par Required preconditions:
 * None
 * @par Called functions:
 * None
 */
void SSP1_IRQHandler(void)
{
    remap_ssp1_irqhandler();
}

/*
 * @brief I2C interrupt routine
 * @par Parameters:
 * None
 * @retval void None
 * @par Required preconditions:
 * None
 * @par Called functions:
 * None
 */
void I2C_IRQHandler(void)
{
    remap_i2c_irqhandler();
}

/*
 * @brief TIMER16_0 interrupt routine
 * @par Parameters:
 * None
 * @retval void None
 * @par Required preconditions:
 * None
 * @par Called functions:
 * None
 */
void TIMER16_0_IRQHandler(void)
{
    remap_timer16_0_irqhandler();
}

/*
 * @brief TIMER16_1 interrupt routine
 * @par Parameters:
 * None
 * @retval void None
 * @par Required preconditions:
 * None
 * @par Called functions:
 * None
 */
void TIMER16_1_IRQHandler(void)
{
    remap_timer16_1_irqhandler();
}

/*
 * @brief TIMER32_0 interrupt routine
 * @par Parameters:
 * None
 * @retval void None
 * @par Required preconditions:
 * None
 * @par Called functions:
 * None
 */
void TIMER32_0_IRQHandler(void)
{
    remap_timer32_0_irqhandler();
}

/*
 * @brief TIMER32_1 interrupt routine
 * @par Parameters:
 * None
 * @retval void None
 * @par Required preconditions:
 * None
 * @par Called functions:
 * None
 */
void TIMER32_1_IRQHandler(void)
{
    remap_timer32_1_irqhandler();
}

/*
 * @brief SSP0 interrupt routine
 * @par Parameters:
 * None
 * @retval void None
 * @par Required preconditions:
 * None
 * @par Called functions:
 * None
 */
void SSP0_IRQHandler(void)
{
    remap_ssp0_irqhandler();
}

/*
 * @brief UART interrupt routine
 * @par Parameters:
 * None
 * @retval void None
 * @par Required preconditions:
 * None
 * @par Called functions:
 * None
 */
void UART_IRQHandler(void)
{
    remap_uart_irqhandler();
}

/*
 * @brief USB interrupt routine
 * @par Parameters:
 * None
 * @retval void None
 * @par Required preconditions:
 * None
 * @par Called functions:
 * None
 */
void USB_IRQHandler(void)
{
    remap_usb_irqhandler();
}

/*
 * @brief USB interrupt routine
 * @par Parameters:
 * None
 * @retval void None
 * @par Required preconditions:
 * None
 * @par Called functions:
 * None
 */
void USB_FIQHandler(void)
{
    remap_usb_fiqhandler();
}

/*
 * @brief adc interrupt routine
 * @par Parameters:
 * None
 * @retval void None
 * @par Required preconditions:
 * None
 * @par Called functions:
 * None
 */
void ADC_IRQHandler(void)
{
    remap_adc_irqhandler();
}

/*
 * @brief WDT interrupt routine
 * @par Parameters:
 * None
 * @retval void None
 * @par Required preconditions:
 * None
 * @par Called functions:
 * None
 */
void WDT_IRQHandler(void)
{
    remap_wdt_irqhandler();
}

/*
 * @brief BOD interrupt routine
 * @par Parameters:
 * None
 * @retval void None
 * @par Required preconditions:
 * None
 * @par Called functions:
 * None
 */
void BOD_IRQHandler(void)
{
    remap_bod_irqhandler();
}

/*
 * @brief FMC interrupt routine
 * @par Parameters:
 * None
 * @retval void None
 * @par Required preconditions:
 * None
 * @par Called functions:
 * None
 */
void FMC_IRQHandler(void)
{
    remap_fmc_irqhandler();
}

/*
 * @brief PIOINT3 interrupt routine
 * @par Parameters:
 * None
 * @retval void None
 * @par Required preconditions:
 * None
 * @par Called functions:
 * None
 */
void PIOINT3_IRQHandler(void)
{
    remap_pioint3_irqhandler();
}

/*
 * @brief PIOINT2 interrupt routine
 * @par Parameters:
 * None
 * @retval void None
 * @par Required preconditions:
 * None
 * @par Called functions:
 * None
 */
void PIOINT2_IRQHandler(void)
{
    remap_pioint2_irqhandler();
}

/*
 * @brief PIOINT1 interrupt routine
 * @par Parameters:
 * None
 * @retval void None
 * @par Required preconditions:
 * None
 * @par Called functions:
 * None
 */
void PIOINT1_IRQHandler(void)
{
    remap_pioint1_irqhandler();
}

/*
 * @brief PIOINT0 interrupt routine
 * @par Parameters:
 * None
 * @retval void None
 * @par Required preconditions:
 * None
 * @par Called functions:
 * None
 */
void PIOINT0_IRQHandler(void)
{
    remap_pioint0_irqhandler();
}

