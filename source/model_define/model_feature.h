/*
 * model_feature.h - model_feature.h config header file;
 *
 * Copyright (c) 2014 Forlan.yung(YANGHUALIANG)
 *
 */

#ifndef _MODEL_FEATURE_H_
#define _MODEL_FEATURE_H_


/****************************************************************************
      ����������
****************************************************************************/
/* model���� */
#define MX7                         80
/* MCU ���Ͷ��� */
/* Flash:32K,RAM:8K,Pin:48 */
#define LPC11C24                    0

/* 
 * ����ѡ��˵��
 * MODEL ÿ��������͵ĵĹ�˾�ڲ�����
 */
#define MODEL                       MX7

/* ��Ӳ���汾 */
#define STR_VERSION                 "V0.01"
#define HW_VERSION                  "1"

/* ֵ Ԥ ���� */
/* MCU�ͺŶ��� */
#define STR_MCU_TYPE                "LPC11C24"

/* �������� */
//#define STR_DATE                    __DATE__


/****************************************************************************
      ���Ͷ�����
****************************************************************************/
#if MODEL == MX7
#include                    "model_mx7.h"
#else
#pragma message("!!! Model error !!!")
#endif


#endif  //_MODEL_FEATURE_H_

