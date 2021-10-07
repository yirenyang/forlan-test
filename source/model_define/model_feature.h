/*
 * model_feature.h - model_feature.h config header file;
 *
 * Copyright (c) 2014 Forlan.yung(YANGHUALIANG)
 *
 */

#ifndef _MODEL_FEATURE_H_
#define _MODEL_FEATURE_H_


/****************************************************************************
      常量定义区
****************************************************************************/
/* model定义 */
#define MX7                         80
/* MCU 类型定义 */
/* Flash:32K,RAM:8K,Pin:48 */
#define LPC11C24                    0

/* 
 * 机型选择说明
 * MODEL 每个具体机型的的公司内部名称
 */
#define MODEL                       MX7

/* 软硬件版本 */
#define STR_VERSION                 "V0.01"
#define HW_VERSION                  "1"

/* 值 预 定义 */
/* MCU型号定义 */
#define STR_MCU_TYPE                "LPC11C24"

/* 编译日期 */
//#define STR_DATE                    __DATE__


/****************************************************************************
      机型定义区
****************************************************************************/
#if MODEL == MX7
#include                    "model_mx7.h"
#else
#pragma message("!!! Model error !!!")
#endif


#endif  //_MODEL_FEATURE_H_

