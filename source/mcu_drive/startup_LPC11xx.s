;/******************** (C) COPYRIGHT 2010 Embest Info&Tech Co.,LTD. **********
;* �ļ���: startup_LPC11xx.s
;* ����  : Wuhan R&D Center, Embest
;* ����  : 01/18/2010
;* ����  : CMSIS Cortex-M0����Χ���ʲ�Դ�ļ�������NXP LPC11xxϵ���豸
;*****************************************************************************
;*****************************************************************************
;* ��ʷ:
;* 01/18/2010		 : V1.0		   ��ʼ�汾
;*****************************************************************************/
; *------- <<< Use Configuration Wizard in Context Menu >>> ------------------


; <h> ջ����
;   <o> ջ��С (�ֽ�) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00000200

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> ������
;   <o>  �Ѵ�С (�ֽ�) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000000

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit


                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors

__Vectors       DCD     __initial_sp              ; ջ��
                DCD     Reset_Handler             ; ��λ�������
                DCD     NMI_Handler               ; NMI�������
                DCD     HardFault_Handler         ; Ӳ���ϴ������
                DCD     MemManage_Handler         ; MPU���ϴ���
                DCD     BusFault_Handler          ; ���߹��ϴ���
                DCD     UsageFault_Handler        ; �÷����ϴ���
                DCD     0                         ; ����
                DCD     0                         ; ����
                DCD     0                         ; ����
                DCD     0                         ; ����
                DCD     SVC_Handler               ; SVCall������
                DCD     DebugMon_Handler          ; Debug Monitor�������
                DCD     0                         ; ����
                DCD     PendSV_Handler            ; PendSV������
                DCD     SysTick_Handler           ; SysTick�жϴ�����

                ; �ⲿ�ж�
                DCD     WAKEUP_IRQHandler         ; 15������Դ��
                DCD     WAKEUP_IRQHandler         ; I/O����PIO0 (0:11)
                DCD     WAKEUP_IRQHandler         ; ����40���Œl������ISR                       
                DCD     WAKEUP_IRQHandler                         
                DCD     WAKEUP_IRQHandler                        
                DCD     WAKEUP_IRQHandler
                DCD     WAKEUP_IRQHandler
                DCD     WAKEUP_IRQHandler                       
                DCD     WAKEUP_IRQHandler                         
                DCD     WAKEUP_IRQHandler                        
                DCD     WAKEUP_IRQHandler
                DCD     WAKEUP_IRQHandler
                DCD     WAKEUP_IRQHandler         ; PIO1 (0:11)
                DCD     CAN_IRQHandler            ; CAN                
                DCD     SSP1_IRQHandler           ; SSP1               
                DCD     I2C_IRQHandler            ; I2C
                DCD     TIMER16_0_IRQHandler      ; 16-bit Timer0
                DCD     TIMER16_1_IRQHandler      ; 16-bit Timer1
                DCD     TIMER32_0_IRQHandler      ; 32-bit Timer0
                DCD     TIMER32_1_IRQHandler      ; 32-bit Timer1
                DCD     SSP0_IRQHandler           ; SSP0
                DCD     UART_IRQHandler           ; UART
                DCD     USB_IRQHandler            ; USB IRQ
                DCD     USB_FIQHandler            ; USB FIQ
                DCD     ADC_IRQHandler            ; A/D Converter
                DCD     WDT_IRQHandler            ; Watchdog timer
                DCD     BOD_IRQHandler            ; Brown Out Detect
                DCD     FMC_IRQHandler            ; IP2111 Flash Memory Controller
                DCD     PIOINT3_IRQHandler        ; PIO INT3
                DCD     PIOINT2_IRQHandler        ; PIO INT2
                DCD     PIOINT1_IRQHandler        ; PIO INT1
                DCD     PIOINT0_IRQHandler        ; PIO INT0


                IF      :LNOT::DEF:NO_CRP
                AREA    |.ARM.__at_0x02FC|, CODE, READONLY
CRP_Key         DCD     0xFFFFFFFF
                ENDIF


                AREA    |.text|, CODE, READONLY


; ��λ������

Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
                IMPORT  __main
                LDR     R0, =__main
                BX      R0
                ENDP


; �쳣���� (����ѭ�������޸�)                

NMI_Handler     PROC
                EXPORT  NMI_Handler               [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler         [WEAK]
                B       .
                ENDP
MemManage_Handler\
                PROC
                EXPORT  MemManage_Handler         [WEAK]
                B       .
                ENDP
BusFault_Handler\
                PROC
                EXPORT  BusFault_Handler          [WEAK]
                B       .
                ENDP
UsageFault_Handler\
                PROC
                EXPORT  UsageFault_Handler        [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler               [WEAK]
                B       .
                ENDP
DebugMon_Handler\
                PROC
                EXPORT  DebugMon_Handler          [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler            [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler           [WEAK]
                B       .
                ENDP

Default_Handler PROC

                EXPORT  WAKEUP_IRQHandler         [WEAK]
				EXPORT  CAN_IRQHandler            [WEAK]
				EXPORT  SSP1_IRQHandler           [WEAK]
                EXPORT  I2C_IRQHandler            [WEAK]
                EXPORT  TIMER16_0_IRQHandler      [WEAK]
                EXPORT  TIMER16_1_IRQHandler      [WEAK]
                EXPORT  TIMER32_0_IRQHandler      [WEAK]
                EXPORT  TIMER32_1_IRQHandler      [WEAK]
                EXPORT  SSP0_IRQHandler           [WEAK]
                EXPORT  UART_IRQHandler           [WEAK]

                EXPORT  USB_IRQHandler            [WEAK]
                EXPORT  USB_FIQHandler            [WEAK]
                EXPORT  ADC_IRQHandler            [WEAK]
                EXPORT  WDT_IRQHandler            [WEAK]
                EXPORT  BOD_IRQHandler            [WEAK]
                EXPORT  FMC_IRQHandler            [WEAK]
                EXPORT  PIOINT3_IRQHandler        [WEAK]
                EXPORT  PIOINT2_IRQHandler        [WEAK]
                EXPORT	PIOINT1_IRQHandler        [WEAK]
                EXPORT	PIOINT0_IRQHandler        [WEAK]


WAKEUP_IRQHandler
CAN_IRQHandler
SSP1_IRQHandler
I2C_IRQHandler
TIMER16_0_IRQHandler
TIMER16_1_IRQHandler
TIMER32_0_IRQHandler
TIMER32_1_IRQHandler
SSP0_IRQHandler
UART_IRQHandler
USB_IRQHandler
USB_FIQHandler
ADC_IRQHandler
WDT_IRQHandler
BOD_IRQHandler
FMC_IRQHandler
PIOINT3_IRQHandler  
PIOINT2_IRQHandler 
PIOINT1_IRQHandler
PIOINT0_IRQHandler

                B       .

                ENDP


                ALIGN


; �û���ʼ����ջ

                IF      :DEF:__MICROLIB
                
                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit
                
                ELSE
                
                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap
__user_initial_stackheap

                LDR     R0, =  Heap_Mem
                LDR     R1, =(Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem +  Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR

                ALIGN

                ENDIF


                END
