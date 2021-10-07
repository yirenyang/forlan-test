/*
 * mpu.h - mpu.h config header file;
 *
 * Copyright (c) 2014 Forlan.yung(YANGHUALIANG)
 *
 */

#ifndef _MPU_H_
#define _MPU_H_

#ifdef MPU_ROOT
#define EXTERN_MPU
#else
#define EXTERN_MPU extern
#endif


/****************************************************************************
      常量声明区
****************************************************************************/
enum
{
    MPU_STATUS_POWERDN,
    MPU_STATUS_WAIT_POWERREADY,
    MPU_STATUS_INIT,
    MPU_STATUS_RUNING
};


/****************************************************************************
      变量定义区
****************************************************************************/
EXTERN_MPU uint8_t mpu_main_status;
EXTERN_MPU uint8_t mpu_tx_buffer[UART_TX_FRAME_LEN_MAX];

#define mpu_frame_head          mpu_tx_buffer[0]
#define mpu_frame_head2         mpu_tx_buffer[1]
#define mpu_cmd_length          mpu_tx_buffer[2]
#define mpu_cmd_id              mpu_tx_buffer[3]
#define mpu_cmd_prm0            mpu_tx_buffer[4]
#define mpu_cmd_prm1            mpu_tx_buffer[5]
#define mpu_cmd_prm2            mpu_tx_buffer[6]
#define mpu_cmd_prm3            mpu_tx_buffer[7]
#define mpu_cmd_prm4            mpu_tx_buffer[8]
#define mpu_cmd_prm5            mpu_tx_buffer[9]
#define mpu_cmd_prm6            mpu_tx_buffer[10]
#define mpu_cmd_prm7            mpu_tx_buffer[11]
#define mpu_cmd_prm8            mpu_tx_buffer[12]
#define mpu_cmd_prm9            mpu_tx_buffer[13]
#define mpu_cmd_prm10           mpu_tx_buffer[14]
#define mpu_cmd_prm11           mpu_tx_buffer[15]
#define mpu_cmd_prm12           mpu_tx_buffer[16]
#define mpu_cmd_prm13           mpu_tx_buffer[17]
#define mpu_cmd_prm14           mpu_tx_buffer[18]
#define mpu_cmd_prm15           mpu_tx_buffer[19]
#define mpu_cmd_prm16           mpu_tx_buffer[20]
#define mpu_cmd_prm17           mpu_tx_buffer[21]
#define mpu_cmd_prm18           mpu_tx_buffer[22]

#define mpu_frame_rx_head       mpu_data.rx_frame_buffer[mpu_data.rx_frame_handle][0]
#define mpu_frame_rx_head2      mpu_data.rx_frame_buffer[mpu_data.rx_frame_handle][1]
#define mpu_rx_length           mpu_data.rx_frame_buffer[mpu_data.rx_frame_handle][2]
#define mpu_rx_id               mpu_data.rx_frame_buffer[mpu_data.rx_frame_handle][3]
#define mpu_rx_prm0             mpu_data.rx_frame_buffer[mpu_data.rx_frame_handle][4]
#define mpu_rx_prm1             mpu_data.rx_frame_buffer[mpu_data.rx_frame_handle][5]
#define mpu_rx_prm2             mpu_data.rx_frame_buffer[mpu_data.rx_frame_handle][6]
#define mpu_rx_prm3             mpu_data.rx_frame_buffer[mpu_data.rx_frame_handle][7]
#define mpu_rx_prm4             mpu_data.rx_frame_buffer[mpu_data.rx_frame_handle][8]
#define mpu_rx_prm5             mpu_data.rx_frame_buffer[mpu_data.rx_frame_handle][9]
#define mpu_rx_prm6             mpu_data.rx_frame_buffer[mpu_data.rx_frame_handle][10]
#define mpu_rx_prm7             mpu_data.rx_frame_buffer[mpu_data.rx_frame_handle][11]
#define mpu_rx_prm8             mpu_data.rx_frame_buffer[mpu_data.rx_frame_handle][12]
#define mpu_rx_prm9             mpu_data.rx_frame_buffer[mpu_data.rx_frame_handle][13]
#define mpu_rx_prm10            mpu_data.rx_frame_buffer[mpu_data.rx_frame_handle][14]
#define mpu_rx_prm11            mpu_data.rx_frame_buffer[mpu_data.rx_frame_handle][15]
#define mpu_rx_prm12            mpu_data.rx_frame_buffer[mpu_data.rx_frame_handle][16]
#define mpu_rx_prm13            mpu_data.rx_frame_buffer[mpu_data.rx_frame_handle][17]
#define mpu_rx_prm14            mpu_data.rx_frame_buffer[mpu_data.rx_frame_handle][18]
#define mpu_rx_prm15            mpu_data.rx_frame_buffer[mpu_data.rx_frame_handle][19]
#define mpu_rx_prm16            mpu_data.rx_frame_buffer[mpu_data.rx_frame_handle][20]

#define mpu_rx_can_prm0         mpu_data.mpu_rx_can_frame_buffer[mpu_data.mpu_rx_can_frame_index][0]
#define mpu_rx_can_prm1         mpu_data.mpu_rx_can_frame_buffer[mpu_data.mpu_rx_can_frame_index][1]
#define mpu_rx_can_prm2         mpu_data.mpu_rx_can_frame_buffer[mpu_data.mpu_rx_can_frame_index][2]
#define mpu_rx_can_prm3         mpu_data.mpu_rx_can_frame_buffer[mpu_data.mpu_rx_can_frame_index][3]
#define mpu_rx_can_prm4         mpu_data.mpu_rx_can_frame_buffer[mpu_data.mpu_rx_can_frame_index][4]
#define mpu_rx_can_prm5         mpu_data.mpu_rx_can_frame_buffer[mpu_data.mpu_rx_can_frame_index][5]
#define mpu_rx_can_prm6         mpu_data.mpu_rx_can_frame_buffer[mpu_data.mpu_rx_can_frame_index][6]



/****************************************************************************
      函数申明区
****************************************************************************/
extern void mpu_init(void);
extern void mpu_main(void);
extern void mpu_rx_buffer_analyse(void);
extern void mpu_rx_handle(void);
extern bool mpu_tx_handle(uint8_t msg_id, uint16_t prm);
extern void mpu_to_can_cmd(uint8_t id, uint16_t param);

#endif

