/*
 * can_drv.c - can_drv.c config and achieve;
 *
 * Copyright (c) 2014 Forlan.yung(YANGHUALIANG)
 *
 */

#define GLOBALS_CAN_DVR
#include "include.h"


/****************************************************************************
      常量定义区
****************************************************************************/
/* This is the maximum number that can be stored as an 11bit Message identifier. */
#define CAN_MAX_11BIT_MSG_ID    (0x7ff)
/* This is used as the loop delay for accessing the CAN controller registers. */
#define CAN_RW_DELAY            (5)


/****************************************************************************
      函数定义区
****************************************************************************/
//*****************************************************************************
//
//! \internal
//! Checks a CAN base address.
//!
//! \param ptBase is the base address of the CAN controller.
//!
//! This function determines if a CAN controller base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
void assert_param(long ulData)
{
    ;
}

int CANBaseValid(unsigned long ulBaseAddr)
{
    if (ulBaseAddr == LPC_CAN_BASE) {
        return 1;
    }
    return -1;
}

/*********************************************************************************************************
** Function name:           __ENTER_CIRTICAL, __EXIT_CIRTICAL
** Descriptions:            临界区代码保护宏
** input parameters:        返回总中断标志  , 原总中断标志
** Descriptions:            必须成对调用，这对宏之间的操作将关闭总中断，退出临界区后恢复原总中断设置
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#if defined(__arm__) && defined(__ARMCC_VERSION)                        /* 对应KEIL/RVMDK               */
__asm unsigned char __enterCirtical(void) {
    MRS     R0,PRIMASK                                                  /* 返回原总中断的状态           */
    CPSID   I                                                           /* 关闭总中断                   */
    BX      LR
}
__asm void __intEnable() {
    CPSIE   I                                                           /* 打开总中断                   */
    BX      LR
}
#define __ENTER_CIRTICAL()          __enterCirtical()                   /* 进入临界区关闭总中断         */
#define __EXIT_CIRTICAL(isEnable)   if(isEnable == 0) {__intEnable();}  /* 根据isEnable检查是否开中断   */

#elif defined (__IAR_SYSTEMS_ICC__)                                     /* 对应IAR集成开发工具          */
__enterCirtical(void)
{
    asm("MRS R0,PRIMASK");                                              /* 返回总中断状态               */
    asm("CPSID I");                                                     /* 关闭总中断                   */
}
#define __ENTER_CIRTICAL()         __enterCirtical()                    /* 进入临界区关闭总中断         */
#define __EXIT_CIRTICAL(isEnable)  if(isEnable == 0) {asm("CPSIE I");}  /* 根据isEnable检查是否开中断   */

#else                                                                   /* 对应GCC开发工具              */
__enterCirtical(void)
{
    asm("MRS R0,PRIMASK");                                              /* 返回总中断状态               */
    asm("CPSID I");                                                     /* 关闭总中断                   */
}
#define __ENTER_CIRTICAL()         __enterCirtical()                    /* 进入临界区关闭总中断         */
#define __EXIT_CIRTICAL(isEnable)  if(isEnable == 0) {asm("CPSIE I");}  /* 根据isEnable检查是否开中断   */
#endif

/*********************************************************************************************************
** Function name:           __canIntNumberGet
** Descriptions:            获取CAN中断号
** input parameters:        ulRegAddress:CAN寄存器地址
** output parameters:       无
** Returned value:          >0:CAN中断号 -1:无效的CAN寄存器地址
** Created By:
** Created date:
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
IRQn_Type __canIntNumberGet(unsigned long ulBase)
{
    IRQn_Type lIntNumber;
    switch(ulBase) {
        case LPC_CAN_BASE:{
            lIntNumber = CAN_IRQn;
            break;
        }
        
        default:{
            lIntNumber = (IRQn_Type)-1;                                 /* 基址错误                     */
        }
    }
    return(lIntNumber);
}

/*********************************************************************************************************
** Function name:           __canRegWrite
** Descriptions:            CAN寄存器读操作
** input parameters:        ulRegAddress:CAN寄存器地址
** output parameters:       无
** Returned value:          unsigned long:寄存器值
** Created By:
** Created date:
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
unsigned long __canRegRead(unsigned long ulRegAddress)
{
    volatile int iDelay;
    unsigned long ulRetVal;
    unsigned char ucEnable;
    
    ucEnable = __ENTER_CIRTICAL();                                      /* 进入临界区                   */
    
    HWREG(ulRegAddress);
    for(iDelay = 0; iDelay < 5; iDelay++)
    {
    }
    
    ulRetVal = HWREG(ulRegAddress);
    __EXIT_CIRTICAL(ucEnable);                                          /* 退出临界区                   */
    return(ulRetVal);
}

/*********************************************************************************************************
** Function name:           __canRegWrite
** Descriptions:            CAN寄存器写操作
** input parameters:        ulRegAddress:CAN寄存器地址
**                          ulRegValue:需要写的数据
** output parameters:       无
** Returned value:          无
** Created By:
** Created date:
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void __canRegWrite(unsigned long ulRegAddress, unsigned long ulRegValue)
{
    volatile int iDelay;
    HWREG(ulRegAddress) = ulRegValue;
    for(iDelay = 0; iDelay < 5; iDelay++)
    {
    }
}


//*****************************************************************************
//
//! \internal
//!
//! Copies data from a buffer to the CAN Data registers.
//!
//! \param pucData is a pointer to the data to be written out to the CAN
//! controller's data registers.
//! \param pulRegister is an unsigned long pointer to the first register of the
//! CAN controller's data registers.  For example, in order to use the IF1
//! register set on CAN controller 0, the value would be: \b CAN0_BASE \b +
//! \b CAN_O_IF1DA1.
//! \param iSize is the number of bytes to copy into the CAN controller.
//!
//! This function takes the steps necessary to copy data from a contiguous
//! buffer in memory into the non-contiguous data registers used by the CAN
//! controller.  This function is rarely used outside of the can_message_set()
//! function.
//!
//! This function replaces the original CANWriteDataReg() API and performs the
//! same actions.  A macro is provided in <tt>can.h</tt> to map the original
//! API to this API.
//!
//! \return None.
//
//*****************************************************************************
void can_data_register_write(unsigned char *pucData, unsigned long *pulRegister, int iSize)
{
    int iIdx;
    unsigned long ulValue;

    /* Loop always copies 1 or 2 bytes per iteration. */
    for (iIdx = 0; iIdx < iSize; )
    {
        /*
         * Write out the data 16 bits at a time since this is how the registers
         * are aligned in memory.
         */
        ulValue = pucData[iIdx++];

        /* Only write the second byte if needed otherwise it will be zero. */
        if (iIdx < iSize)
        {
            ulValue |= (pucData[iIdx++] << 8);
        }

        canRegWrite((unsigned long)(pulRegister++), ulValue);
    }
}

//*****************************************************************************
//
//! \internal
//!
//! Copies data from a buffer to the CAN Data registers.
//!
//! \param pucData is a pointer to the location to store the data read from the
//! CAN controller's data registers.
//! \param pulRegister is an unsigned long pointer to the first register of the
//! CAN controller's data registers.  For example, in order to use the IF1
//! register set on CAN controller 1, the value would be: \b CAN0_BASE \b +
//! \b CAN_O_IF1DA1.
//! \param iSize is the number of bytes to copy from the CAN controller.
//!
//! This function takes the steps necessary to copy data to a contiguous buffer
//! in memory from the non-contiguous data registers used by the CAN
//! controller.  This function is rarely used outside of the can_message_get()
//! function.
//!
//! This function replaces the original CANReadDataReg() API and performs the
//! same actions.  A macro is provided in <tt>can.h</tt> to map the original
//! API to this API.
//!
//! \return None.
//
//*****************************************************************************
void can_data_register_read(unsigned char *pucData, unsigned long *pulRegister, int iSize)
{
    int iIdx;
    unsigned long ulValue;

    /* Loop always copies 1 or 2 bytes per iteration. */
    for (iIdx = 0; iIdx < iSize; )
    {
        /* Read out the data 16 bits at a time since this is how the registers are aligned in memory. */
        ulValue = canRegRead((unsigned long)(pulRegister++));

        /* Store the first byte. */
        pucData[iIdx++] = (unsigned char)ulValue;

        /* Only read the second byte if needed. */
        if (iIdx < iSize)
        {
            pucData[iIdx++] = (unsigned char)(ulValue >> 8);
        }
    }
}

//*****************************************************************************
//
//! Initializes the CAN controller after reset.
//!
//! \param ptBase is the base address of the CAN controller.
//!
//! After reset, the CAN controller is left in the disabled state.  However,
//! the memory used for message objects contains undefined values and must be
//! cleared prior to enabling the CAN controller the first time.  This prevents
//! unwanted transmission or reception of data before the message objects are
//! configured.  This function must be called before enabling the controller
//! the first time.
//!
//! \return None.
//
//*****************************************************************************
void can_init(unsigned long ulBaseAddr)
{
    int iMsg;
    LPC_CAN_TypeDef *ptBase = (LPC_CAN_TypeDef *)ulBaseAddr;

    /* Check the arguments. */
    assert_param(CANBaseValid((unsigned long)ptBase));

    /*
     * Place CAN controller in init state, regardless of previous state.  This
     * will put controller in idle, and allow the message object RAM to be
     * programmed.
     */
    canRegWrite((unsigned long)&ptBase->CNTL, CAN_CTL_INIT);

    /* Wait for busy bit to clear */
    while (canRegRead((unsigned long)&ptBase->IF1_CMDREQ) & CAN_IF1CRQ_BUSY)
    {
        ;
    }

    /*
     * Clear the message value bit in the arbitration register.  This indicates
     * the message is not valid and is a "safe" condition to leave the message
     * object.  The same arb reg is used to program all the message objects.
     */
    canRegWrite((unsigned long)&ptBase->IF1_CMDMSK, CAN_IF1CMSK_WRNRD | CAN_IF1CMSK_ARB | CAN_IF1CMSK_CONTROL);
    canRegWrite((unsigned long)&ptBase->IF1_ARB2, 0);
    canRegWrite((unsigned long)&ptBase->IF1_MCTRL, 0);

    /* Loop through to program all 32 message objects */
    for (iMsg = 1; iMsg <= 32; iMsg++)
    {
        /* Wait for busy bit to clear */
        while (canRegRead((unsigned long)&ptBase->IF1_CMDREQ) & CAN_IF1CRQ_BUSY)
        {
            ;
        }

        /* Initiate programming the message object */
        canRegWrite((unsigned long)&ptBase->IF1_CMDREQ, iMsg);
    }

    /* Make sure that the interrupt and new data flags are updated for the message objects. */
    canRegWrite((unsigned long)&ptBase->IF1_CMDMSK, CAN_IF1CMSK_NEWDAT | CAN_IF1CMSK_CLRINTPND);

    /* Loop through to program all 32 message objects */
    for (iMsg = 1; iMsg <= 32; iMsg++)
    {
        /* Wait for busy bit to clear. */
        while (canRegRead((unsigned long)&ptBase->IF1_CMDREQ) & CAN_IF1CRQ_BUSY)
        {
            ;
        }

        /* Initiate programming the message object */
        canRegWrite((unsigned long)&ptBase->IF1_CMDREQ, iMsg);
    }

    /* Acknowledge any pending status interrupts. */
    canRegRead((unsigned long)&ptBase->STAT);
}

//*****************************************************************************
//
//! Enables the CAN controller.
//!
//! \param ptBase is the base address of the CAN controller to enable.
//!
//! Enables the CAN controller for message processing.  Once enabled, the
//! controller will automatically transmit any pending frames, and process any
//! received frames.  The controller can be stopped by calling can_disable().
//! Prior to calling can_enable(), can_init() should have been called to
//! initialize the controller and the CAN bus clock should be configured by
//! calling can_bit_timing_set().
//!
//! \return None.
//
//*****************************************************************************
void can_enable(unsigned long ulBaseAddr)
{
    LPC_CAN_TypeDef *ptBase = (LPC_CAN_TypeDef *)ulBaseAddr;

    /* Check the arguments. */
    assert_param(CANBaseValid((unsigned long)ptBase));

    /* Clear the init bit in the control register. */
    canRegWrite((unsigned long)&ptBase->CNTL, canRegRead((unsigned long)&ptBase->CNTL) & ~CAN_CTL_INIT);
}

//*****************************************************************************
//
//! Disables the CAN controller.
//!
//! \param ptBase is the base address of the CAN controller to disable.
//!
//! Disables the CAN controller for message processing.  When disabled, the
//! controller will no longer automatically process data on the CAN bus.  The
//! controller can be restarted by calling can_enable().  The state of the CAN
//! controller and the message objects in the controller are left as they were
//! before this call was made.
//!
//! \return None.
//
//*****************************************************************************
void can_disable(unsigned long ulBaseAddr)
{
    LPC_CAN_TypeDef *ptBase = (LPC_CAN_TypeDef *)ulBaseAddr;

    /* Check the arguments. */
    assert_param(CANBaseValid((unsigned long)ptBase));

    /* Set the init bit in the control register. */
    canRegWrite((unsigned long)&ptBase->CNTL, canRegRead((unsigned long)&ptBase->CNTL) | CAN_CTL_INIT);
}

//*****************************************************************************
//
//! Reads the current settings for the CAN controller bit timing.
//!
//! \param ptBase is the base address of the CAN controller.
//! \param pClkParms is a pointer to a structure to hold the timing parameters.
//!
//! This function reads the current configuration of the CAN controller bit
//! clock timing, and stores the resulting information in the structure
//! supplied by the caller.  Refer to can_bit_timing_set() for the meaning of the
//! values that are returned in the structure pointed to by \e pClkParms.
//!
//! This function replaces the original CANGetBitTiming() API and performs the
//! same actions.  A macro is provided in <tt>can.h</tt> to map the original
//! API to this API.
//!
//! \return None.
//
//*****************************************************************************
void can_bit_timing_get(unsigned long ulBaseAddr, CAN_BIT_CLK_PARM *pClkParms)
{
    unsigned int uBitReg;
    LPC_CAN_TypeDef *ptBase = (LPC_CAN_TypeDef *)ulBaseAddr;

    /* Check the arguments. */
    assert_param(CANBaseValid((unsigned long)ptBase));
    assert_param(pClkParms != 0);

    /* Read out all the bit timing values from the CAN controller registers. */
    uBitReg = canRegRead((unsigned long)&ptBase->BT);

    /* Set the phase 2 segment. */
    pClkParms->uPhase2Seg = ((uBitReg & CAN_BIT_TSEG2_M) >> 12) + 1;

    /* Set the phase 1 segment. */
    pClkParms->uSyncPropPhase1Seg = ((uBitReg & CAN_BIT_TSEG1_M) >> 8) + 1;

    /* Set the sychronous jump width. */
    pClkParms->uSJW = ((uBitReg & CAN_BIT_SJW_M) >> 6) + 1;

    /* Set the pre-divider for the CAN bus bit clock. */
    pClkParms->uQuantumPrescaler = ((uBitReg & CAN_BIT_BRP_M)
                                 | ((canRegRead((unsigned long)&ptBase->BRPE) & CAN_BRPE_BRPE_M) << 6)) + 1;
}

//*****************************************************************************
//
//! Configures the CAN controller bit timing.
//!
//! \param ptBase is the base address of the CAN controller.
//! \param pClkParms points to the structure with the clock parameters.
//!
//! Configures the various timing parameters for the CAN bus bit timing:
//! Propagation segment, Phase Buffer 1 segment, Phase Buffer 2 segment, and
//! the Synchronization Jump Width.  The values for Propagation and Phase
//! Buffer 1 segments are derived from the combination
//! \e pClkParms->uSyncPropPhase1Seg parameter.  Phase Buffer 2 is determined
//! from the \e pClkParms->uPhase2Seg parameter.  These two parameters, along
//! with \e pClkParms->uSJW are based in units of bit time quanta.  The actual
//! quantum time is determined by the \e pClkParms->uQuantumPrescaler value,
//! which specifies the divisor for the CAN module clock.
//!
//! The total bit time, in quanta, will be the sum of the two Seg parameters,
//! as follows:
//!
//! bit_time_q = uSyncPropPhase1Seg + uPhase2Seg + 1
//!
//! Note that the Sync_Seg is always one quantum in duration, and will be added
//! to derive the correct duration of Prop_Seg and Phase1_Seg.
//!
//! The equation to determine the actual bit rate is as follows:
//!
//! CAN Clock /
//! ((\e uSyncPropPhase1Seg + \e uPhase2Seg + 1) * (\e uQuantumPrescaler))
//!
//! This means that with \e uSyncPropPhase1Seg = 4, \e uPhase2Seg = 1,
//! \e uQuantumPrescaler = 2 and an 8 MHz CAN clock, that the bit rate will be
//! (8 MHz) / ((5 + 2 + 1) * 2) or 500 Kbit/sec.
//!
//! This function replaces the original CANSetBitTiming() API and performs the
//! same actions.  A macro is provided in <tt>can.h</tt> to map the original
//! API to this API.
//!
//! \return None.
//
//*****************************************************************************
void can_bit_timing_set(unsigned long ulBaseAddr, CAN_BIT_CLK_PARM *pClkParms)
{
    unsigned int uBitReg;
    unsigned int uSavedInit;
    LPC_CAN_TypeDef *ptBase = (LPC_CAN_TypeDef *)ulBaseAddr;

    /* Check the arguments. */
    assert_param(CANBaseValid((unsigned long)ptBase));
    assert_param(pClkParms != 0);

    /* The phase 1 segment must be in the range from 2 to 16. */
    assert_param((pClkParms->uSyncPropPhase1Seg >= 2) && (pClkParms->uSyncPropPhase1Seg <= 16));

    /* The phase 2 segment must be in the range from 1 to 8. */
    assert_param((pClkParms->uPhase2Seg >= 1) && (pClkParms->uPhase2Seg <= 8));

    /* The synchronous jump windows must be in the range from 1 to 4. */
    assert_param((pClkParms->uSJW >= 1) && (pClkParms->uSJW <= 4));

    /* The CAN clock pre-divider must be in the range from 1 to 1024. */
    assert_param((pClkParms->uQuantumPrescaler <= 1024) && (pClkParms->uQuantumPrescaler >= 1));

    /*
     * To set the bit timing register, the controller must be placed in init
     * mode (if not already), and also configuration change bit enabled.  State
     * of the init bit should be saved so it can be restored at the end.
     */
    uSavedInit = canRegRead((unsigned long)&ptBase->CNTL);
    canRegWrite((unsigned long)&ptBase->CNTL, uSavedInit | CAN_CTL_INIT | CAN_CTL_CCE);

    /* Set the bit fields of the bit timing register according to the parms. */
    uBitReg = ((pClkParms->uPhase2Seg - 1) << 12) & CAN_BIT_TSEG2_M;
    uBitReg |= ((pClkParms->uSyncPropPhase1Seg - 1) << 8) & CAN_BIT_TSEG1_M;
    uBitReg |= ((pClkParms->uSJW - 1) << 6) & CAN_BIT_SJW_M;
    uBitReg |= (pClkParms->uQuantumPrescaler - 1) & CAN_BIT_BRP_M;
    canRegWrite((unsigned long)&ptBase->BT, uBitReg);

    /* Set the divider upper bits in the extension register. */
    canRegWrite((unsigned long)&ptBase->BRPE, ((pClkParms->uQuantumPrescaler - 1) >> 6) & CAN_BRPE_BRPE_M);

    /* Clear the config change bit, and restore the init bit. */
    uSavedInit &= ~CAN_CTL_CCE;

    /* If Init was not set before, then clear it. */
    if (uSavedInit & CAN_CTL_INIT)
    {
        uSavedInit &= ~CAN_CTL_INIT;
    }

    canRegWrite((unsigned long)&ptBase->CNTL, uSavedInit);
}

//*****************************************************************************
//
//! Registers an interrupt handler for the CAN controller.
//!
//! \param ptBase is the base address of the CAN controller.
//! \param pfnHandler is a pointer to the function to be called when the
//! enabled CAN interrupts occur.
//!
//! This function registers the interrupt handler in the interrupt vector
//! table, and enables CAN interrupts on the interrupt controller; specific CAN
//! interrupt sources must be enabled using can_interrupt_enable().  The interrupt
//! handler being registered must clear the source of the interrupt using
//! can_interrupt_clear().
//!
//! If the application is using a static interrupt vector table stored in
//! flash, then it is not necessary to register the interrupt handler this way.
//! Instead, IntEnable() should be used to enable CAN interrupts on the
//! interrupt controller.
//!
//! \sa interrupt_register() for important information about registering interrupt
//! handlers.
//!
//! \return None.
//
//*****************************************************************************
//中断注册函数
void interrupt_register(unsigned long ulSn, void (*pfnHandler)(void))
{
    ;
}

void can_interrupt_register(unsigned long ulBaseAddr, void (*pfnHandler)(void))
{
    unsigned long ulIntNumber;

    /* Check the arguments. */
    assert_param(CANBaseValid(ulBaseAddr));

    /* Get the actual interrupt number for this CAN controller. */
    ulIntNumber = __canIntNumberGet(ulBaseAddr);

    /* Register the interrupt handler. */
    interrupt_register(ulIntNumber, pfnHandler);

    /* Enable the Ethernet interrupt. */
    IntEnable(ulIntNumber);
}


//*****************************************************************************
//
//! Enables individual CAN controller interrupt sources.
//!
//! \param ptBase is the base address of the CAN controller.
//! \param ulIntFlags is the bit mask of the interrupt sources to be enabled.
//!
//! Enables specific interrupt sources of the CAN controller.  Only enabled
//! sources will cause a processor interrupt.
//!
//! The \e ulIntFlags parameter is the logical OR of any of the following:
//!
//! - \b CAN_INT_ERROR - a controller error condition has occurred
//! - \b CAN_INT_STATUS - a message transfer has completed, or a bus error has
//! been detected
//! - \b CAN_INT_MASTER - allow CAN controller to generate interrupts
//!
//! In order to generate any interrupts, \b CAN_INT_MASTER must be enabled.
//! Further, for any particular transaction from a message object to generate
//! an interrupt, that message object must have interrupts enabled (see
//! can_message_set()).  \b CAN_INT_ERROR will generate an interrupt if the
//! controller enters the ``bus off'' condition, or if the error counters reach
//! a limit.  \b CAN_INT_STATUS will generate an interrupt under quite a few
//! status conditions and may provide more interrupts than the application
//! needs to handle.  When an interrupt occurs, use can_interrupt_status() to determine
//! the cause.
//!
//! \return None.
//
//*****************************************************************************
void can_interrupt_enable(unsigned long ulBaseAddr, unsigned long ulIntFlags)
{
    LPC_CAN_TypeDef *ptBase = (LPC_CAN_TypeDef *)ulBaseAddr;

    /* Check the arguments. */
    assert_param(CANBaseValid((unsigned long)ptBase));
    assert_param((ulIntFlags & ~(CAN_CTL_EIE | CAN_CTL_SIE | CAN_CTL_IE)) == 0);

    /* Enable the specified interrupts. */
    canRegWrite((unsigned long)&ptBase->CNTL, canRegRead((unsigned long)&ptBase->CNTL) | ulIntFlags);
}

//*****************************************************************************
//
//! Disables individual CAN controller interrupt sources.
//!
//! \param ptBase is the base address of the CAN controller.
//! \param ulIntFlags is the bit mask of the interrupt sources to be disabled.
//!
//! Disables the specified CAN controller interrupt sources.  Only enabled
//! interrupt sources can cause a processor interrupt.
//!
//! The \e ulIntFlags parameter has the same definition as in the
//! can_interrupt_enable() function.
//!
//! \return None.
//
//*****************************************************************************
void can_interrupt_disable(unsigned long ulBaseAddr, unsigned long ulIntFlags)
{
    LPC_CAN_TypeDef *ptBase = (LPC_CAN_TypeDef *)ulBaseAddr;

    /* Check the arguments. */
    assert_param(CANBaseValid((unsigned long)ptBase));
    assert_param((ulIntFlags & ~(CAN_CTL_EIE | CAN_CTL_SIE | CAN_CTL_IE)) == 0);

    /* Disable the specified interrupts. */
    canRegWrite((unsigned long)&ptBase->CNTL, canRegRead((unsigned long)&ptBase->CNTL) & ~(ulIntFlags));
}

//*****************************************************************************
//
//! Returns the current CAN controller interrupt status.
//!
//! \param ptBase is the base address of the CAN controller.
//! \param eIntStsReg indicates which interrupt status register to read
//!
//! Returns the value of one of two interrupt status registers.  The interrupt
//! status register read is determined by the \e eIntStsReg parameter, which
//! can have one of the following values:
//!
//! - \b CAN_INT_STS_CAUSE - indicates the cause of the interrupt
//! - \b CAN_INT_STS_OBJECT - indicates pending interrupts of all message
//! objects
//!
//! \b CAN_INT_STS_CAUSE returns the value of the controller interrupt register
//! and indicates the cause of the interrupt.  It will be a value of
//! \b CAN_INT_INTID_STATUS if the cause is a status interrupt.  In this case,
//! the status register should be read with the can_status_get() function.
//! Calling this function to read the status will also clear the status
//! interrupt.  If the value of the interrupt register is in the range 1-32,
//! then this indicates the number of the highest priority message object that
//! has an interrupt pending.  The message object interrupt can be cleared by
//! using the can_interrupt_clear() function, or by reading the message using
//! can_message_get() in the case of a received message.  The interrupt handler
//! can read the interrupt status again to make sure all pending interrupts are
//! cleared before returning from the interrupt.
//!
//! \b CAN_INT_STS_OBJECT returns a bit mask indicating which message objects
//! have pending interrupts.  This can be used to discover all of the pending
//! interrupts at once, as opposed to repeatedly reading the interrupt register
//! by using \b CAN_INT_STS_CAUSE.
//!
//! \return Returns the value of one of the interrupt status registers.
//
//*****************************************************************************
unsigned long can_interrupt_status(unsigned long ulBaseAddr, CAN_INT_STS_REG eIntStsReg)
{
    unsigned long ulStatus;
    LPC_CAN_TypeDef *ptBase = (LPC_CAN_TypeDef *)ulBaseAddr;

    /* Check the arguments. */
    assert_param(CANBaseValid((unsigned long)ptBase));

    /* See which status the caller is looking for. */
    switch (eIntStsReg)
    {
        /* The caller wants the global interrupt status for the CAN controller specified by ptBase. */
        case CAN_INT_STS_CAUSE:
        {
            ulStatus = canRegRead((unsigned long)&ptBase->INT);
            break;
        }

        /* The caller wants the current message status interrupt for all messages. */
        case CAN_INT_STS_OBJECT:
        {
            /* Read and combine both 16 bit values into one 32bit status. */
            ulStatus = (canRegRead((unsigned long)&ptBase->IR1) & CAN_MSG1INT_INTPND_M);
            ulStatus |= (canRegRead((unsigned long)&ptBase->IR2) << 16);
            break;
        }

        /* Request was for unknown status so just return 0. */
        default:
        {
            ulStatus = 0;
            break;
        }
    }

    /* Return the interrupt status value. */
    return(ulStatus);
}

//*****************************************************************************
//
//! Clears a CAN interrupt source.
//!
//! \param ptBase is the base address of the CAN controller.
//! \param ulIntClr is a value indicating which interrupt source to clear.
//!
//! This function can be used to clear a specific interrupt source.  The
//! \e ulIntClr parameter should be one of the following values:
//!
//! - \b CAN_INT_INTID_STATUS - Clears a status interrupt.
//! - 1-32 - Clears the specified message object interrupt
//!
//! It is not necessary to use this function to clear an interrupt.  This
//! should only be used if the application wants to clear an interrupt source
//! without taking the normal interrupt action.
//!
//! Normally, the status interrupt is cleared by reading the controller status
//! using can_status_get().  A specific message object interrupt is normally
//! cleared by reading the message object using can_message_get().
//!
//! \note Since there is a write buffer in the Cortex-M3 processor, it may take
//! several clock cycles before the interrupt source is actually cleared.
//! Therefore, it is recommended that the interrupt source be cleared early in
//! the interrupt handler (as opposed to the very last action) to avoid
//! returning from the interrupt handler before the interrupt source is
//! actually cleared.  Failure to do so may result in the interrupt handler
//! being immediately reentered (since NVIC still sees the interrupt source
//! asserted).
//!
//! \return None.
//
//*****************************************************************************
void can_interrupt_clear(unsigned long ulBaseAddr, unsigned long ulIntClr)
{
    LPC_CAN_TypeDef *ptBase = (LPC_CAN_TypeDef *)ulBaseAddr;

    /* Check the arguments. */
    assert_param(CANBaseValid((unsigned long)ptBase));
    assert_param((ulIntClr == CAN_INT_INTID_STATUS) || ((ulIntClr >= 1) && (ulIntClr <= 32)));

    if (ulIntClr == CAN_INT_INTID_STATUS)
    {
        /* Simply read and discard the status to clear the interrupt. */
        canRegRead((unsigned long)&ptBase->STAT);
    }
    else
    {
        /* Wait to be sure that this interface is not busy. */
        while (canRegRead((unsigned long)&ptBase->IF1_CMDREQ) & CAN_IF1CRQ_BUSY)
        {
            ;
        }

        // Only change the interrupt pending state by setting only the CAN_IF1CMSK_CLRINTPND bit.
        canRegWrite((unsigned long)&ptBase->IF1_CMDMSK, CAN_IF1CMSK_CLRINTPND);

        /* Send the clear pending interrupt command to the CAN controller. */
        canRegWrite((unsigned long)&ptBase->IF1_CMDREQ, ulIntClr & CAN_IF1CRQ_MNUM_M);

        /* Wait to be sure that this interface is not busy. */
        while(canRegRead((unsigned long)&ptBase->IF1_CMDREQ) & CAN_IF1CRQ_BUSY)
        {
            ;
        }
    }
}

//*****************************************************************************
//
//! Sets the CAN controller automatic retransmission behavior.
//!
//! \param ptBase is the base address of the CAN controller.
//! \param bAutoRetry enables automatic retransmission.
//!
//! Enables or disables automatic retransmission of messages with detected
//! errors.  If \e bAutoRetry is \b true, then automatic retransmission is
//! enabled, otherwise it is disabled.
//!
//! \return None.
//
//*****************************************************************************
void can_retry_set(unsigned long ulBaseAddr, bool bAutoRetry)
{
    unsigned long ulCtlReg;
    LPC_CAN_TypeDef *ptBase = (LPC_CAN_TypeDef *)ulBaseAddr;

    /* Check the arguments. */
    assert_param(CANBaseValid((unsigned long)ptBase));

    ulCtlReg = canRegRead((unsigned long)&ptBase->CNTL);

    /* Conditionally set the DAR bit to enable/disable auto-retry. */
    if (bAutoRetry)
    {
        /*
         * Clearing the DAR bit tells the controller to not disable the
         * auto-retry of messages which were not transmited or received
         * correctly.
         */
        ulCtlReg &= ~CAN_CTL_DAR;
    }
    else
    {
        /*
         * Setting the DAR bit tells the controller to disable the auto-retry
         * of messages which were not transmited or received correctly.
         */
        ulCtlReg |= CAN_CTL_DAR;
    }
    
    canRegWrite((unsigned long)&ptBase->CNTL, ulCtlReg);
}

//*****************************************************************************
//
//! Returns the current setting for automatic retransmission.
//!
//! \param ptBase is the base address of the CAN controller.
//!
//! Reads the current setting for the automatic retransmission in the CAN
//! controller and returns it to the caller.
//!
//! \return Returns \b true if automatic retransmission is enabled, \b false
//! otherwise.
//
//*****************************************************************************
bool can_retry_get(unsigned long ulBaseAddr)
{
    LPC_CAN_TypeDef *ptBase = (LPC_CAN_TypeDef *)ulBaseAddr;

    /* Check the arguments. */
    assert_param(CANBaseValid((unsigned long)ptBase));

    /* Read the disable automatic retry setting from the CAN controller. */
    if (canRegRead((unsigned long)&ptBase->CNTL) & CAN_CTL_DAR)
    {
        /* Automatic data retransmission is not enabled. */
        return(false);
    }

    /* Automatic data retransmission is enabled. */
    return(true);
}

//*****************************************************************************
//
//! Reads one of the controller status registers.
//!
//! \param ptBase is the base address of the CAN controller.
//! \param eStatusReg is the status register to read.
//!
//! Reads a status register of the CAN controller and returns it to the caller.
//! The different status registers are:
//!
//! - \b CAN_STS_CONTROL - the main controller status
//! - \b CAN_STS_TXREQUEST - bit mask of objects pending transmission
//! - \b CAN_STS_NEWDAT - bit mask of objects with new data
//! - \b CAN_STS_MSGVAL - bit mask of objects with valid configuration
//!
//! When reading the main controller status register, a pending status
//! interrupt will be cleared.  This should be used in the interrupt handler
//! for the CAN controller if the cause is a status interrupt.  The controller
//! status register fields are as follows:
//!
//! - \b CAN_STATUS_BUS_OFF - controller is in bus-off condition
//! - \b CAN_STATUS_EWARN - an error counter has reached a limit of at least 96
//! - \b CAN_STATUS_EPASS - CAN controller is in the error passive state
//! - \b CAN_STATUS_RXOK - a message was received successfully (independent of
//! any message filtering).
//! - \b CAN_STATUS_TXOK - a message was successfully transmitted
//! - \b CAN_STATUS_LEC_MSK - mask of last error code bits (3 bits)
//! - \b CAN_STATUS_LEC_NONE - no error
//! - \b CAN_STATUS_LEC_STUFF - stuffing error detected
//! - \b CAN_STATUS_LEC_FORM - a format error occurred in the fixed format part
//! of a message
//! - \b CAN_STATUS_LEC_ACK - a transmitted message was not acknowledged
//! - \b CAN_STATUS_LEC_BIT1 - dominant level detected when trying to send in
//! recessive mode
//! - \b CAN_STATUS_LEC_BIT0 - recessive level detected when trying to send in
//! dominant mode
//! - \b CAN_STATUS_LEC_CRC - CRC error in received message
//!
//! The remaining status registers are 32-bit bit maps to the message objects.
//! They can be used to quickly obtain information about the status of all the
//! message objects without needing to query each one.  They contain the
//! following information:
//!
//! - \b CAN_STS_TXREQUEST - if a message object's TxRequest bit is set, that
//! means that a transmission is pending on that object.  The application can
//! use this to determine which objects are still waiting to send a message.
//! - \b CAN_STS_NEWDAT - if a message object's NewDat bit is set, that means
//! that a new message has been received in that object, and has not yet been
//! picked up by the host application
//! - \b CAN_STS_MSGVAL - if a message object's MsgVal bit is set, that means
//! it has a valid configuration programmed.  The host application can use this
//! to determine which message objects are empty/unused.
//!
//! \return Returns the value of the status register.
//
//*****************************************************************************
unsigned long can_status_get(unsigned long ulBaseAddr, CAN_STS_REG eStatusReg)
{
    unsigned long ulStatus;
    LPC_CAN_TypeDef *ptBase = (LPC_CAN_TypeDef *)ulBaseAddr;

    /* Check the arguments. */
    assert_param(CANBaseValid((unsigned long)ptBase));
    
    switch (eStatusReg)
    {
        /* Just return the global CAN status register since that is what was requested. */
        case CAN_STS_CONTROL:
        {
            ulStatus = canRegRead((unsigned long)&ptBase->STAT);
            canRegWrite((unsigned long)&ptBase->STAT, ~(CAN_STS_RXOK | CAN_STS_TXOK | CAN_STS_LEC_M));
            break;
        }

        /* Combine the Transmit status bits into one 32bit value. */
        case CAN_STS_TXREQUEST:
        {
            ulStatus = canRegRead((unsigned long)&ptBase->TXREQ1);
            ulStatus |= canRegRead((unsigned long)&ptBase->TXREQ2) << 16;
            break;
        }

        /* Combine the New Data status bits into one 32bit value. */
        case CAN_STS_NEWDAT:
        {
            ulStatus = canRegRead((unsigned long)&ptBase->ND1);
            ulStatus |= canRegRead((unsigned long)&ptBase->ND2) << 16;
            break;
        }

        /* Combine the Message valid status bits into one 32bit value. */
        case CAN_STS_MSGVAL:
        {
            ulStatus = canRegRead((unsigned long)&ptBase->MSGV1);
            ulStatus |= canRegRead((unsigned long)&ptBase->MSGV2) << 16;
            break;
        }

        /* Unknown CAN status requested so return 0. */
        default:
        {
            ulStatus = 0;
            break;
        }
    }

    return(ulStatus);
}

//*****************************************************************************
//
//! Reads the CAN controller error counter register.
//!
//! \param ptBase is the base address of the CAN controller.
//! \param pulRxCount is a pointer to storage for the receive error counter.
//! \param pulTxCount is a pointer to storage for the transmit error counter.
//!
//! Reads the error counter register and returns the transmit and receive error
//! counts to the caller along with a flag indicating if the controller receive
//! counter has reached the error passive limit.  The values of the receive and
//! transmit error counters are returned through the pointers provided as
//! parameters.
//!
//! After this call, \e *pulRxCount will hold the current receive error count
//! and \e *pulTxCount will hold the current transmit error count.
//!
//! \return Returns \b true if the receive error count has reached the error
//! passive limit, and \b false if the error count is below the error passive
//! limit.
//
//*****************************************************************************
bool can_err_cntr_get(unsigned long ulBaseAddr, unsigned long *pulRxCount, unsigned long *pulTxCount)
{
    unsigned long ulCANError;
    LPC_CAN_TypeDef *ptBase = (LPC_CAN_TypeDef *)ulBaseAddr;

    /* Check the arguments. */
    assert_param(CANBaseValid((unsigned long)ptBase));

    /* Read the current count of transmit/receive errors. */
    ulCANError = canRegRead((unsigned long)&ptBase->EC);

    /* Extract the error numbers from the register value. */
    *pulRxCount = (ulCANError & CAN_ERR_REC_M) >> CAN_ERR_REC_S;
    *pulTxCount = (ulCANError & CAN_ERR_TEC_M) >> CAN_ERR_TEC_S;

    if (ulCANError & CAN_ERR_RP)
    {
        return(true);
    }

    return(false);
}

//*****************************************************************************
//
//! Configures a message object in the CAN controller.
//!
//! \param ptBase is the base address of the CAN controller.
//! \param ulObjID is the object number to configure (1-32).
//! \param ptMsgObj is a pointer to a structure containing message object
//! settings.
//! \param eMsgType indicates the type of message for this object.
//!
//! This function is used to configure any one of the 32 message objects in the
//! CAN controller.  A message object can be configured as any type of CAN
//! message object as well as several options for automatic transmission and
//! reception.  This call also allows the message object to be configured to
//! generate interrupts on completion of message receipt or transmission.  The
//! message object can also be configured with a filter/mask so that actions
//! are only taken when a message that meets certain parameters is seen on the
//! CAN bus.
//!
//! The \e eMsgType parameter must be one of the following values:
//!
//! - \b MSG_OBJ_TYPE_TX - CAN transmit message object.
//! - \b MSG_OBJ_TYPE_TX_REMOTE - CAN transmit remote request message object.
//! - \b MSG_OBJ_TYPE_RX - CAN receive message object.
//! - \b MSG_OBJ_TYPE_RX_REMOTE - CAN receive remote request message object.
//! - \b MSG_OBJ_TYPE_RXTX_REMOTE - CAN remote frame receive remote, then
//! transmit message object.
//!
//! The message object pointed to by \e ptMsgObj must be populated by the
//! caller, as follows:
//!
//! - \e ulMsgID - contains the message ID, either 11 or 29 bits.
//! - \e ulMsgIDMask - mask of bits from \e ulMsgID that must match if
//! identifier filtering is enabled.
//! - \e ulFlags
//!   - Set \b MSG_OBJ_TX_INT_ENABLE flag to enable interrupt on transmission.
//!   - Set \b MSG_OBJ_RX_INT_ENABLE flag to enable interrupt on receipt.
//!   - Set \b MSG_OBJ_USE_ID_FILTER flag to enable filtering based on the
//!   identifier mask specified by \e ulMsgIDMask.
//! - \e ulMsgLen - the number of bytes in the message data.  This should be
//! non-zero even for a remote frame; it should match the expected bytes of the
//! data responding data frame.
//! - \e pucMsgData - points to a buffer containing up to 8 bytes of data for a
//! data frame.
//!
//! \b Example: To send a data frame or remote frame(in response to a remote
//! request), take the following steps:
//!
//! -# Set \e eMsgType to \b MSG_OBJ_TYPE_TX.
//! -# Set \e ptMsgObj->ulMsgID to the message ID.
//! -# Set \e ptMsgObj->ulFlags. Make sure to set \b MSG_OBJ_TX_INT_ENABLE to
//! allow an interrupt to be generated when the message is sent.
//! -# Set \e ptMsgObj->ulMsgLen to the number of bytes in the data frame.
//! -# Set \e ptMsgObj->pucMsgData to point to an array containing the bytes
//! to send in the message.
//! -# Call this function with \e ulObjID set to one of the 32 object buffers.
//!
//! \b Example: To receive a specific data frame, take the following steps:
//!
//! -# Set \e eMsgObjType to \b MSG_OBJ_TYPE_RX.
//! -# Set \e ptMsgObj->ulMsgID to the full message ID, or a partial mask to
//! use partial ID matching.
//! -# Set \e ptMsgObj->ulMsgIDMask bits that should be used for masking
//! during comparison.
//! -# Set \e ptMsgObj->ulFlags as follows:
//!   - Set \b MSG_OBJ_TX_INT_ENABLE flag to be interrupted when the data frame
//!   is received.
//!   - Set \b MSG_OBJ_USE_ID_FILTER flag to enable identifier based filtering.
//! -# Set \e ptMsgObj->ulMsgLen to the number of bytes in the expected data
//! frame.
//! -# The buffer pointed to by \e ptMsgObj->pucMsgData  and
//! \e ptMsgObj->ulMsgLen are not used by this call as no data is present at
//! the time of the call.
//! -# Call this function with \e ulObjID set to one of the 32 object buffers.
//!
//! If you specify a message object buffer that already contains a message
//! definition, it will be overwritten.
//!
//! \return None.
//
//*****************************************************************************
void can_message_set(unsigned long ulBaseAddr, unsigned long ulObjID, CAN_MSG_OBJ *ptMsgObj, MSG_OBJ_TYPE eMsgType)
{
    unsigned short usCmdMaskReg;
    unsigned short usMaskReg[2];
    unsigned short usArbReg[2];
    unsigned short usMsgCtrl;
    bool bTransferData;
    bool bUseExtendedID;
    LPC_CAN_TypeDef *ptBase = (LPC_CAN_TypeDef *)ulBaseAddr;

    bTransferData = 0;

    /* Check the arguments. */
    assert_param(CANBaseValid((unsigned long)ptBase));
    assert_param((ulObjID <= 32) && (ulObjID != 0));
    assert_param((eMsgType == MSG_OBJ_TYPE_TX)
              || (eMsgType == MSG_OBJ_TYPE_TX_REMOTE)
              || (eMsgType == MSG_OBJ_TYPE_RX)
              || (eMsgType == MSG_OBJ_TYPE_RX_REMOTE)
              || (eMsgType == MSG_OBJ_TYPE_TX_REMOTE)
              || (eMsgType == MSG_OBJ_TYPE_RXTX_REMOTE));

    /* Wait for busy bit to clear */
    while (canRegRead((unsigned long)&ptBase->IF1_CMDREQ) & CAN_IF1CRQ_BUSY)
    {
    }

    /* See if we need to use an extended identifier or not. */
    if ((ptMsgObj->ulMsgID > CAN_MAX_11BIT_MSG_ID) || (ptMsgObj->ulFlags & MSG_OBJ_EXTENDED_ID))
    {
        bUseExtendedID = 1;
    }
    else
    {
        bUseExtendedID = 0;
    }

    /*
     * This is always a write to the Message object as this call is setting a
     * message object.  This call will also always set all size bits so it sets
     * both data bits.  The call will use the CONTROL register to set control
     * bits so this bit needs to be set as well.
     */
    usCmdMaskReg = (CAN_IF1CMSK_WRNRD | CAN_IF1CMSK_DATAA | CAN_IF1CMSK_DATAB | CAN_IF1CMSK_CONTROL);

    /*
     * Initialize the values to a known state before filling them in based on
     * the type of message object that is being configured.
     */
    usArbReg[0] = 0;
    usMsgCtrl = 0;
    usMaskReg[0] = 0;
    usMaskReg[1] = 0;

    switch (eMsgType)
    {
        /* Transmit message object. */
        case MSG_OBJ_TYPE_TX:
        {
            /* Set the TXRQST bit and the reset the rest of the register. */
            usMsgCtrl |= CAN_IF1MCTL_TXRQST;
            usArbReg[1] = CAN_IF1ARB2_DIR;
            bTransferData = 1;
            break;
        }

        /* Transmit remote request message object */
        case MSG_OBJ_TYPE_TX_REMOTE:
        {
            /* Set the TXRQST bit and the reset the rest of the register. */
            usMsgCtrl |= CAN_IF1MCTL_TXRQST;
            usArbReg[1] = 0;
            break;
        }

        /* Receive message object. */
        case MSG_OBJ_TYPE_RX:
        {
            /*
             * This clears the DIR bit along with everthing else. The TXRQST
             * bit was cleard by defaulting usMsgCtrl to 0.
             */
            usArbReg[1] = 0;
            break;
        }

        /* Receive remote request message object. */
        case MSG_OBJ_TYPE_RX_REMOTE:
        {
            /*
             * The DIR bit is set to one for remote receivers.  The TXRQST bit
             * was cleard by defaulting usMsgCtrl to 0.
             */
            usArbReg[1] = CAN_IF1ARB2_DIR;
            
            /*
             * Set this object so that it only indicates that a remote frame
             * was received and allow for software to handle it by sending back
             * a data frame.
             */
            usMsgCtrl = CAN_IF1MCTL_UMASK;

            /* Use the full Identifier by default. */
            usMaskReg[0] = 0xffff;
            usMaskReg[1] = 0x1fff;

            /* Make sure to send the mask to the message object. */
            usCmdMaskReg |= CAN_IF1CMSK_MASK;
            break;
        }

        /* Remote frame receive remote, with auto-transmit message object. */
        case MSG_OBJ_TYPE_RXTX_REMOTE:
        {
            /* Oddly the DIR bit is set to one for remote receivers. */
            usArbReg[1] = CAN_IF1ARB2_DIR;

            /* Set this object to auto answer if a matching identifier is seen. */
            usMsgCtrl = CAN_IF1MCTL_RMTEN | CAN_IF1MCTL_UMASK;

            /* The data to be returned needs to be filled in. */
            bTransferData = 1;
            break;
        }

        /*
         * This case should never happen due to the assert_param statement at the
         * beginning of this function.
         */
        default:
        {
            return;
        }
    }

    /* Configure the Mask Registers. */
    if (ptMsgObj->ulFlags & MSG_OBJ_USE_ID_FILTER)
    {
        if (bUseExtendedID)
        {
            /* Set the 29 bits of Identifier mask that were requested. */
            usMaskReg[0] = ptMsgObj->ulMsgIDMask & CAN_IF1MSK1_IDMSK_M;
            usMaskReg[1] = ((ptMsgObj->ulMsgIDMask >> 16) & CAN_IF1MSK2_IDMSK_M);
        }
        else
        {
            /* Lower 16 bit are unused so set them to zero. */
            usMaskReg[0] = 0;
            
            /*
             * Put the 11 bit Mask Identifier into the upper bits of the field
             * in the register.
             */
            usMaskReg[1] = ((ptMsgObj->ulMsgIDMask << 2) & CAN_IF1MSK2_IDMSK_M);
        }
    }

    /* If the caller wants to filter on the extended ID bit then set it. */
    if ((ptMsgObj->ulFlags & MSG_OBJ_USE_EXT_FILTER) == MSG_OBJ_USE_EXT_FILTER)
    {
        usMaskReg[1] |= CAN_IF1MSK2_MXTD;
    }

    /* The caller wants to filter on the message direction field. */
    if ((ptMsgObj->ulFlags & MSG_OBJ_USE_DIR_FILTER) == MSG_OBJ_USE_DIR_FILTER)
    {
        usMaskReg[1] |= CAN_IF1MSK2_MDIR;
    }
    
    if (ptMsgObj->ulFlags & (MSG_OBJ_USE_ID_FILTER | MSG_OBJ_USE_DIR_FILTER | MSG_OBJ_USE_EXT_FILTER))
    {
        /* Set the UMASK bit to enable using the mask register. */
        usMsgCtrl |= CAN_IF1MCTL_UMASK;

        /* Set the MASK bit so that this gets trasferred to the Message Object. */
        usCmdMaskReg |= CAN_IF1CMSK_MASK;
    }

    /* Set the Arb bit so that this gets transferred to the Message object. */
    usCmdMaskReg |= CAN_IF1CMSK_ARB;

    /* Configure the Arbitration registers. */
    if (bUseExtendedID)
    {
        /* Set the 29 bit version of the Identifier for this message object. */
        usArbReg[0] |= ptMsgObj->ulMsgID & CAN_IF1ARB1_ID_M;
        usArbReg[1] |= (ptMsgObj->ulMsgID >> 16) & CAN_IF1ARB2_ID_M;

        /* Mark the message as valid and set the extended ID bit. */
        usArbReg[1] |= CAN_IF1ARB2_MSGVAL | CAN_IF1ARB2_XTD;
    }
    else
    {
        /*
         * Set the 11 bit version of the Identifier for this message object.
         * The lower 18 bits are set to zero.
         */
        usArbReg[1] |= (ptMsgObj->ulMsgID << 2) & CAN_IF1ARB2_ID_M;

        /*  Mark the message as valid. */
        usArbReg[1] |= CAN_IF1ARB2_MSGVAL;
    }

    /*
     * Set the data length since this is set for all transfers.  This is also a
     * single transfer and not a FIFO transfer so set EOB bit.
     */
    usMsgCtrl |= (ptMsgObj->ulMsgLen & CAN_IF1MCTL_DLC_M) | CAN_IF1MCTL_EOB;

    /* Enable transmit interrupts if they should be enabled. */
    if (ptMsgObj->ulFlags & MSG_OBJ_TX_INT_ENABLE)
    {
        usMsgCtrl |= CAN_IF1MCTL_TXIE;
    }

    /* Enable receive interrupts if they should be enabled. */
    if (ptMsgObj->ulFlags & MSG_OBJ_RX_INT_ENABLE)
    {
        usMsgCtrl |= CAN_IF1MCTL_RXIE;
    }

    /* Write the data out to the CAN Data registers if needed. */
    if (bTransferData)
    {
        can_data_register_write(ptMsgObj->pucMsgData, (unsigned long *)(&ptBase->IF1_DA1), ptMsgObj->ulMsgLen);
    }

    /* Write out the registers to program the message object. */
    canRegWrite((unsigned long)&ptBase->IF1_CMDMSK, usCmdMaskReg);
    canRegWrite((unsigned long)&ptBase->IF1_MSK1, usMaskReg[0]);
    canRegWrite((unsigned long)&ptBase->IF1_MSK2, usMaskReg[1]);
    canRegWrite((unsigned long)&ptBase->IF1_ARB1, usArbReg[0]);
    canRegWrite((unsigned long)&ptBase->IF1_ARB2, usArbReg[1]);
    canRegWrite((unsigned long)&ptBase->IF1_MCTRL, usMsgCtrl);

    /* Transfer the message object to the message object specifiec by ulObjID. */
    canRegWrite((unsigned long)&ptBase->IF1_CMDREQ, ulObjID & CAN_IF1CRQ_MNUM_M);
    
    return;
}

//*****************************************************************************
//
//! Reads a CAN message from one of the message object buffers.
//!
//! \param ptBase is the base address of the CAN controller.
//! \param ulObjID is the object number to read (1-32).
//! \param ptMsgObj points to a structure containing message object fields.
//! \param bClrPendingInt indicates whether an associated interrupt should be
//! cleared.
//!
//! This function is used to read the contents of one of the 32 message objects
//! in the CAN controller, and return it to the caller.  The data returned is
//! stored in the fields of the caller-supplied structure pointed to by
//! \e ptMsgObj.  The data consists of all of the parts of a CAN message,
//! plus some control and status information.
//!
//! Normally this is used to read a message object that has received and stored
//! a CAN message with a certain identifier.  However, this could also be used
//! to read the contents of a message object in order to load the fields of the
//! structure in case only part of the structure needs to be changed from a
//! previous setting.
//!
//! When using can_message_get, all of the same fields of the structure are
//! populated in the same way as when the can_message_set() function is used,
//! with the following exceptions:
//!
//! \e ptMsgObj->ulFlags:
//!
//! - \b MSG_OBJ_NEW_DATA indicates if this is new data since the last time it
//! was read
//! - \b MSG_OBJ_DATA_LOST indicates that at least one message was received on
//! this message object, and not read by the host before being overwritten.
//!
//! \return None.
//
//*****************************************************************************
void can_message_get(unsigned long ulBaseAddr, unsigned long ulObjID, CAN_MSG_OBJ *ptMsgObj, bool bClrPendingInt)
{
    unsigned short usCmdMaskReg;
    unsigned short usMaskReg[2];
    unsigned short usArbReg[2];
    unsigned short usMsgCtrl;
    LPC_CAN_TypeDef *ptBase = (LPC_CAN_TypeDef *)ulBaseAddr;

    /* Check the arguments. */
    assert_param(CANBaseValid((unsigned long)ptBase));
    assert_param((ulObjID <= 32) && (ulObjID != 0));

    /* This is always a read to the Message object as this call is setting a message object. */
    usCmdMaskReg = (CAN_IF1CMSK_DATAA 
                  | CAN_IF1CMSK_DATAB
                  | CAN_IF1CMSK_CONTROL
                  | CAN_IF1CMSK_MASK
                  | CAN_IF1CMSK_ARB);

    /* Clear a pending interrupt and new data in a message object. */
    if (bClrPendingInt)
    {
        usCmdMaskReg |= CAN_IF1CMSK_CLRINTPND;
    }

    /* Set up the request for data from the message object. */
    canRegWrite((unsigned long)&ptBase->IF2_CMDMSK, usCmdMaskReg);

    /* Transfer the message object to the message object specifiec by ulObjID. */
    canRegWrite((unsigned long)&ptBase->IF2_CMDREQ, ulObjID & CAN_IF1CRQ_MNUM_M);

    /* Wait for busy bit to clear */
    while (canRegRead((unsigned long)&ptBase->IF2_CMDREQ) & CAN_IF1CRQ_BUSY)
    {
    }

    /* Read out the IF Registers. */
    usMaskReg[0] = canRegRead((unsigned long)&ptBase->IF2_MSK1);
    usMaskReg[1] = canRegRead((unsigned long)&ptBase->IF2_MSK2);
    usArbReg[0] = canRegRead((unsigned long)&ptBase->IF2_ARB1);
    usArbReg[1] = canRegRead((unsigned long)&ptBase->IF2_ARB2);
    usMsgCtrl = canRegRead((unsigned long)&ptBase->IF2_MCTRL);

    ptMsgObj->ulFlags = MSG_OBJ_NO_FLAGS;

    /* Determine if this is a remote frame by checking the TXRQST and DIR bits. */
    if ((!(usMsgCtrl & CAN_IF1MCTL_TXRQST) && (usArbReg[1] & CAN_IF1ARB2_DIR))
        || ((usMsgCtrl & CAN_IF1MCTL_TXRQST) && (!(usArbReg[1] & CAN_IF1ARB2_DIR))))
    {
        ptMsgObj->ulFlags |= MSG_OBJ_REMOTE_FRAME;
    }

    /* Get the identifier out of the register, the format depends on size of the mask. */
    if (usArbReg[1] & CAN_IF1ARB2_XTD)
    {
        /* Set the 29 bit version of the Identifier for this message object. */
        ptMsgObj->ulMsgID = ((usArbReg[1] & CAN_IF1ARB2_ID_M) << 16) | usArbReg[0];
        
        ptMsgObj->ulFlags |= MSG_OBJ_EXTENDED_ID;
    }
    else
    {
        /* The Identifier is an 11 bit value. */
        ptMsgObj->ulMsgID = (usArbReg[1] & CAN_IF1ARB2_ID_M) >> 2;
    }

    /* Indicate that we lost some data. */
    if (usMsgCtrl & CAN_IF1MCTL_MSGLST)
    {
        ptMsgObj->ulFlags |= MSG_OBJ_DATA_LOST;
    }

    /* Set the flag to indicate if ID masking was used. */
    if (usMsgCtrl & CAN_IF1MCTL_UMASK)
    {
        if (usArbReg[1] & CAN_IF1ARB2_XTD)
        {
            /* The Identifier Mask is assumed to also be a 29 bit value. */
            ptMsgObj->ulMsgIDMask = ((usMaskReg[1] & CAN_IF1MSK2_IDMSK_M) << 16) | usMaskReg[0];

            /*
             * If this is a fully specified Mask and a remote frame then don't
             * set the MSG_OBJ_USE_ID_FILTER because the ID was not really
             * filtered.
             */
            if ((ptMsgObj->ulMsgIDMask != 0x1FFFFFFF) || ((ptMsgObj->ulFlags & MSG_OBJ_REMOTE_FRAME) == 0))
            {
                ptMsgObj->ulFlags |= MSG_OBJ_USE_ID_FILTER;
            }
        }
        else
        {
            /* The Identifier Mask is assumed to also be an 11 bit value. */
            ptMsgObj->ulMsgIDMask = ((usMaskReg[1] & CAN_IF1MSK2_IDMSK_M) >> 2);
            
            /*
             * If this is a fully specified Mask and a remote frame then don't
             * set the MSG_OBJ_USE_ID_FILTER because the ID was not really
             * filtered.
             */
            if ((ptMsgObj->ulMsgIDMask != 0x7FF) || ((ptMsgObj->ulFlags & MSG_OBJ_REMOTE_FRAME) == 0))
            {
                ptMsgObj->ulFlags |= MSG_OBJ_USE_ID_FILTER;
            }
        }

        /* Indicate if the extended bit was used in filtering. */
        if (usMaskReg[1] & CAN_IF1MSK2_MXTD)
        {
            ptMsgObj->ulFlags |= MSG_OBJ_USE_EXT_FILTER;
        }

        /* Indicate if direction filtering was enabled. */
        if (usMaskReg[1] & CAN_IF1MSK2_MDIR)
        {
            ptMsgObj->ulFlags |= MSG_OBJ_USE_DIR_FILTER;
        }
    }

    /* Set the interupt flags. */
    if (usMsgCtrl & CAN_IF1MCTL_TXIE)
    {
        ptMsgObj->ulFlags |= MSG_OBJ_TX_INT_ENABLE;
    }
    if (usMsgCtrl & CAN_IF1MCTL_RXIE)
    {
        ptMsgObj->ulFlags |= MSG_OBJ_RX_INT_ENABLE;
    }

    /* See if there is new data available. */
    if (usMsgCtrl & CAN_IF1MCTL_NEWDAT)
    {
        /* Get the amount of data needed to be read. */
        ptMsgObj->ulMsgLen = (usMsgCtrl & CAN_IF1MCTL_DLC_M);

        // Don't read any data for a remote frame, there is nothing valid in that buffer anyway.
        if ((ptMsgObj->ulFlags & MSG_OBJ_REMOTE_FRAME) == 0)
        {
            /* Read out the data from the CAN registers. */
            can_data_register_read(ptMsgObj->pucMsgData, (unsigned long *)(&(ptBase->IF2_DA1)), ptMsgObj->ulMsgLen);
        }

        /* Now clear out the new data flag. */
        canRegWrite((unsigned long)&ptBase->IF2_CMDMSK, CAN_IF1CMSK_NEWDAT);

        /* Transfer the message object to the message object specifiec by ulObjID. */
        canRegWrite((unsigned long)&ptBase->IF2_CMDREQ, ulObjID & CAN_IF1CRQ_MNUM_M);

        /* Wait for busy bit to clear */
        while (canRegRead((unsigned long)&ptBase->IF2_CMDREQ) & CAN_IF1CRQ_BUSY)
        {
        }

        /* Indicate that there is new data in this message. */
        ptMsgObj->ulFlags |= MSG_OBJ_NEW_DATA;
    }
    else
    {
        /*
         * Along with the MSG_OBJ_NEW_DATA not being set the amount of data
         * needs to be set to zero if none was available.
         */
        ptMsgObj->ulMsgLen = 0;
    }
}

//*****************************************************************************
//
//! Clears a message object so that it is no longer used.
//!
//! \param ptBase is the base address of the CAN controller.
//! \param ulObjID is the message object number to disable (1-32).
//!
//! This function frees the specified message object from use.  Once a message
//! object has been ``cleared,'' it will no longer automatically send or
//! receive messages, or generate interrupts.
//!
//! \return None.
//
//*****************************************************************************
void can_message_clear(unsigned long ulBaseAddr, unsigned long ulObjID)
{
    LPC_CAN_TypeDef *ptBase = (LPC_CAN_TypeDef *)ulBaseAddr;
    
    /* Check the arguments. */
    assert_param(CANBaseValid((unsigned long)ptBase));
    assert_param((ulObjID >= 1) && (ulObjID <= 32));

    /* Wait for busy bit to clear. */
    while (canRegRead((unsigned long)&ptBase->IF1_CMDREQ) & CAN_IF1CRQ_BUSY)
    {
        ;
    }

    /*
     * Clear the message value bit in the arbitration register.  This indicates
     * the message is not valid.
     */
    canRegWrite((unsigned long)&ptBase->IF1_CMDMSK, CAN_IF1CMSK_WRNRD | CAN_IF1CMSK_ARB);
    canRegWrite((unsigned long)&ptBase->IF1_ARB1, 0);
    canRegWrite((unsigned long)&ptBase->IF1_ARB2, 0);

    /* Initiate programming the message object */
    canRegWrite((unsigned long)&ptBase->IF1_CMDREQ, ulObjID & CAN_IF1CRQ_MNUM_M);
}


