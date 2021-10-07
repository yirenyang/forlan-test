/*
 * can_drv.h - can_drv.h config header file;
 *
 * Copyright (c) 2014 Forlan.yung(YANGHUALIANG)
 *
 */
#ifndef _CAN_DRV_H_
#define _CAN_DRV_H_

#ifndef GLOBALS_CAN_DVR
#define can_extern extern
#else
#define can_extern
#endif


/****************************************************************************
      常量声明区
****************************************************************************/
#define CANCNTL_INIT_BIT_OFFSET_VAL                0
#define CANCNTL_IE_BIT_OFFSET_VAL                  1
#define CANCNTL_SIE_BIT_OFFSET_VAL                 2
#define CANCNTL_EIE_BIT_OFFSET_VAL                 3
#define CANCNTL_DAR_BIT_OFFSET_VAL                 5
#define CANCNTL_CCE_BIT_OFFSET_VAL                 6
#define CANCNTL_TEST_BIT_OFFSET_VAL                7

#define CANCLKDIV_VAL_DIVIDED_BY_01                0x00
#define CANCLKDIV_VAL_DIVIDED_BY_02                0x01
#define CANCLKDIV_VAL_DIVIDED_BY_03                0x02
#define CANCLKDIV_VAL_DIVIDED_BY_04                0x03
#define CANCLKDIV_VAL_DIVIDED_BY_05                0x04
#define CANCLKDIV_VAL_DIVIDED_BY_06                0x05

/*
 * These are the flags used by the CAN_MSG_OBJ variable when calling the
 * can_message_set() and can_message_get() functions.
 */
typedef enum
{
    /* This indicates that transmit interrupts should be enabled, or are enabled. */
    MSG_OBJ_TX_INT_ENABLE =     0x00000001,

    /* This indicates that receive interrupts should be enabled, or are enabled. */
    MSG_OBJ_RX_INT_ENABLE =     0x00000002,

    /* This indicates that a message object will use or is using an extended identifier. */
    MSG_OBJ_EXTENDED_ID =       0x00000004,

    /*
     * This indicates that a message object will use or is using filtering
     * based on the object's message identifier.
     */
    MSG_OBJ_USE_ID_FILTER =     0x00000008,

    /* This indicates that new data was available in the message object. */
    MSG_OBJ_NEW_DATA =          0x00000080,

    /* This indicates that data was lost since this message object was last read. */
    MSG_OBJ_DATA_LOST =         0x00000100,

    /*
     * This indicates that a message object will use or is using filtering
     * based on the direction of the transfer.  If the direction filtering is
     * used, then ID filtering must also be enabled.
     */
    MSG_OBJ_USE_DIR_FILTER =    (0x00000010 | MSG_OBJ_USE_ID_FILTER),

    /*
     * This indicates that a message object will use or is using message
     * identifier filtering based on the extended identifier.  If the extended
     * identifier filtering is used, then ID filtering must also be enabled.
     */
    MSG_OBJ_USE_EXT_FILTER =    (0x00000020 | MSG_OBJ_USE_ID_FILTER),

    /* This indicates that a message object is a remote frame. */
    MSG_OBJ_REMOTE_FRAME =      0x00000040,

    /* This indicates that a message object has no flags set. */
    MSG_OBJ_NO_FLAGS =          0x00000000
}CAN_OBJ_FLG;

/*
 * This define is used with the #CAN_OBJ_FLG enumerated values to allow
 * checking only status flags and not configuration flags.
 */
#define MSG_OBJ_STATUS_MASK     (MSG_OBJ_NEW_DATA | MSG_OBJ_DATA_LOST)

/*
 * The structure used for encapsulating all the items associated with a CAN
 * message object in the CAN controller.
 */
typedef struct
{
    /* The CAN message identifier used for 11 or 29 bit identifiers. */
    unsigned long ulMsgID;

    /* The message identifier mask used when identifier filtering is enabled. */
    unsigned long ulMsgIDMask;

    /* This value holds various status flags and settings specified by CAN_OBJ_FLG. */
    unsigned long ulFlags;

    /* This value is the number of bytes of data in the message object. */
    unsigned long ulMsgLen;

    /* This is a pointer to the message object's data. */
    unsigned char *pucMsgData;
}CAN_MSG_OBJ;

/*
 * This structure is used for encapsulating the values associated with setting
 * up the bit timing for a CAN controller.  The structure is used when calling
 * the CANGetBitTiming and CANSetBitTiming functions.
*/
typedef struct
{
    /*
     * This value holds the sum of the Synchronization, Propagation, and Phase
     * Buffer 1 segments, measured in time quanta.  The valid values for this
     * setting range from 2 to 16.
     */
    unsigned int uSyncPropPhase1Seg;

    /*
     * This value holds the Phase Buffer 2 segment in time quanta.  The valid
     * values for this setting range from 1 to 8.
     */
    unsigned int uPhase2Seg;

    /*
     * This value holds the Resynchronization Jump Width in time quanta.  The
     * valid values for this setting range from 1 to 4.
     */
    unsigned int uSJW;

    /*
     * This value holds the CAN_CLK divider used to determine time quanta.
     * The valid values for this setting range from 1 to 1023.
     */
    unsigned int uQuantumPrescaler;
}CAN_BIT_CLK_PARM;

/*
 * This data type is used to identify the interrupt status register.  This is
 * used when calling the can_interrupt_status() function.
*/
typedef enum
{
    /* Read the CAN interrupt status information. */
    CAN_INT_STS_CAUSE,

    /* Read a message object's interrupt status. */
    CAN_INT_STS_OBJECT
}CAN_INT_STS_REG;

/*
 * This data type is used to identify which of several status registers to
 * read when calling the can_status_get() function.
*/
typedef enum
{
    /* Read the full CAN controller status. */
    CAN_STS_CONTROL,

    /* Read the full 32-bit mask of message objects with a transmit request set. */
    CAN_STS_TXREQUEST,

    /* Read the full 32-bit mask of message objects with new data available. */
    CAN_STS_NEWDAT,

    /* Read the full 32-bit mask of message objects that are enabled. */
    CAN_STS_MSGVAL
}CAN_STS_REG;

/*
 * These definitions are used to specify interrupt sources to can_interrupt_enable()
 * and can_interrupt_disable().
 */
typedef enum
{
    /* This flag is used to allow a CAN controller to generate error interrupts. */
    CAN_INT_ERROR =             0x00000008,

    /* This flag is used to allow a CAN controller to generate status interrupts. */
    CAN_INT_STATUS =            0x00000004,

    /*
     * This flag is used to allow a CAN controller to generate any CAN
     * interrupts.  If this is not set, then no interrupts will be generated
     * by the CAN controller.
     */
    CAN_INT_MASTER =            0x00000002
}CAN_INT_FLAGS;

/*
 * This definition is used to determine the type of message object that will
 * be set up via a call to the can_message_set() API.
 */
typedef enum
{
    /* Transmit message object. */
    MSG_OBJ_TYPE_TX,

    /* Transmit remote request message object */
    MSG_OBJ_TYPE_TX_REMOTE,

    /* Receive message object. */
    MSG_OBJ_TYPE_RX,

    /* Receive remote request message object. */
    MSG_OBJ_TYPE_RX_REMOTE,

    /* Remote frame receive remote, with auto-transmit message object. */
    MSG_OBJ_TYPE_RXTX_REMOTE
}MSG_OBJ_TYPE;

/*
 * The following enumeration contains all error or status indicators that can
 * be returned when calling the can_status_get() function.
 */
typedef enum
{
    /* CAN controller has entered a Bus Off state. */
    CAN_STATUS_BUS_OFF =        0x00000080,

    /* CAN controller error level has reached warning level. */
    CAN_STATUS_EWARN =          0x00000040,

    /* CAN controller error level has reached error passive level. */
    CAN_STATUS_EPASS =          0x00000020,

    /* A message was received successfully since the last read of this status. */
    CAN_STATUS_RXOK =           0x00000010,

    /* A message was transmitted successfully since the last read of this status. */
    CAN_STATUS_TXOK =           0x00000008,

    /* This is the mask for the last error code field. */
    CAN_STATUS_LEC_MSK =        0x00000007,

    /* There was no error. */
    CAN_STATUS_LEC_NONE =       0x00000000,

    /* A bit stuffing error has occurred. */
    CAN_STATUS_LEC_STUFF =      0x00000001,

    /* A formatting error has occurred. */
    CAN_STATUS_LEC_FORM =       0x00000002,

    /* An acknowledge error has occurred. */
    CAN_STATUS_LEC_ACK =        0x00000003,

    /* The bus remained a bit level of 1 for longer than is allowed. */
    CAN_STATUS_LEC_BIT1 =       0x00000004,

    /* The bus remained a bit level of 0 for longer than is allowed. */
    CAN_STATUS_LEC_BIT0 =       0x00000005,

    /* A CRC error has occurred. */
    CAN_STATUS_LEC_CRC =        0x00000006,

    /* This is the mask for the CAN Last Error Code (LEC). */
    CAN_STATUS_LEC_MASK =       0x00000007
}CAN_STS_CTRL;


/****************************************************************************
      函数声明区
****************************************************************************/
/* API Function prototypes */
extern IRQn_Type __canIntNumberGet(unsigned long ulBase);
extern unsigned long __canRegRead(unsigned long ulRegAddress);
extern void __canRegWrite(unsigned long ulRegAddress, unsigned long ulRegValue);

extern void can_bit_timing_get(unsigned long ulBaseAddr, CAN_BIT_CLK_PARM *pClkParms);
extern void can_bit_timing_set(unsigned long ulBaseAddr, CAN_BIT_CLK_PARM *pClkParms);
extern void can_disable(unsigned long ulBaseAddr);
extern void can_enable(unsigned long ulBaseAddr);
extern bool can_err_cntr_get(unsigned long ulBaseAddr, unsigned long *pulRxCount,
                              unsigned long *pulTxCount);
extern void can_init(unsigned long ulBaseAddr);
extern void can_interrupt_clear(unsigned long ulBaseAddr, unsigned long ulIntClr);
extern void can_interrupt_disable(unsigned long ulBaseAddr, unsigned long ulIntFlags);
extern void can_interrupt_enable(unsigned long ulBaseAddr, unsigned long ulIntFlags);
extern void can_interrupt_register(unsigned long ulBaseAddr, void (*pfnHandler)(void));
extern unsigned long can_interrupt_status(unsigned long ulBaseAddr,
                                  CAN_INT_STS_REG eIntStsReg);
extern void CANIntUnregister(unsigned long ulBaseAddr);
extern void can_message_clear(unsigned long ulBaseAddr, unsigned long ulObjID);
extern void can_message_get(unsigned long ulBaseAddr, unsigned long ulObjID,
                          CAN_MSG_OBJ *pMsgObject, bool bClrPendingInt);
extern void can_message_set(unsigned long ulBaseAddr, unsigned long ulObjID,
                          CAN_MSG_OBJ *pMsgObject, MSG_OBJ_TYPE eMsgType);
extern bool can_retry_get(unsigned long ulBaseAddr);
extern void can_retry_set(unsigned long ulBaseAddr, bool bAutoRetry);
extern unsigned long can_status_get(unsigned long ulBaseAddr, CAN_STS_REG eStatusReg);

/*
 * Several CAN APIs have been renamed, with the original function name being
 * deprecated.  These defines provide backward compatibility.
 */
#if defined(__arm__) && defined(__ARMCC_VERSION)                          /* 对应KEIL/RVMDK               */
extern unsigned char __enterCirtical(void);
extern void __intEnable(void);
#define __ENTER_CIRTICAL()          __enterCirtical()                     /* 进入临界区关闭总中断         */
#define __EXIT_CIRTICAL(isEnable)   if(isEnable == 0) {__intEnable();}    /* 根据isEnable检查是否开中断   */

#elif defined (__IAR_SYSTEMS_ICC__)                                       /* 对应IAR集成开发工具          */
extern __enterCirtical(void);
#define __ENTER_CIRTICAL()         __enterCirtical()                      /* 进入临界区关闭总中断         */
#define __EXIT_CIRTICAL(isEnable)  if(isEnable == 0) {asm("CPSIE I");}    /* 根据isEnable检查是否开中断   */

#else 
extern __enterCirtical(void);
#define __ENTER_CIRTICAL()         __enterCirtical()                      /* 进入临界区关闭总中断         */
#define __EXIT_CIRTICAL(isEnable)  if(isEnable == 0) {asm("CPSIE I");}    /* 根据isEnable检查是否开中断   */
#endif

//#define interrupt_register(unsigned long ulInterrupt, void (*pfnHandler)(void));
#define IntEnable(IRQn) 	  NVIC_EnableIRQ((IRQn_Type)IRQn)
#define IntDisable(IRQn)      NVIC_DisableIRQ(IRQn)
#define canRegRead(ulRegAddress)  __canRegRead(ulRegAddress)
#define canRegWrite(ulRegAddress, ulRegValue)  __canRegWrite(ulRegAddress, ulRegValue)


#endif

