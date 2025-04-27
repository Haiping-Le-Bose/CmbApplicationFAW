/*******************************************************************************
*  BOSE CORPORATION
*  COPYRIGHT (c) BOSE CORPORATION ALL RIGHTS RESERVED
*  This program may not be reproduced, in whole or in part in any
*  form or any means whatsoever without the written permission of:
*     BOSE CORPORATION
*     The Mountain
*     Framingham, MA 01701-9168
*******************************************************************************/
/****************************************************
 * @file CMB_BCF_ADAPTOR_Config.h
 *
 * @brief Header file for BCF adaptor proxy configuration.
 *
 ****************************************************/

#if !defined(CMB_BCF_ADAPTOR_CFG__INCLUDED_)
#define CMB_BCF_ADAPTOR_CFG__INCLUDED_

#include "CART_ID.h"
#include "BCF_Callback_Register.h"
#include "BCF_Resource.h"

#define MAX_SHLIB_PATH                     512
#define MAX_BCF_PROXY_CNT                  8
// BCF_PROXY_CNT

typedef struct
{
    CART_ID dstId;

    CART_ID brfId;
    
    CART_ID appId;
    
    uint16_t numBaf;

    CART_ID bafList[BCF_RESOURCE_NUM_BAF];

    BCF_Callback_Register* cb;

    char libraryPath[MAX_SHLIB_PATH];

    // void* threadConfig;
} CMB_BCF_Proxy_Config;

#endif /*!defined(CMB_BCF_ADAPTOR_CFG__INCLUDED_)*/
