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
 * @file CMB_BTF_ADAPTOR_Config.h
 *
 * @brief Header file for BTF adaptor proxy configuration.
 *
 ****************************************************/

#if !defined(CMB_BTF_ADAPTOR_CFG__INCLUDED_)
#define CMB_BTF_ADAPTOR_CFG__INCLUDED_

#include "CART_ID.h"
#include "BTF_Callback_Register.h"

#define MAX_NUM_BTF_RESOURCES              16
#define MAX_SHLIB_PATH                     512
#define MAX_BTF_PROXY_CNT                  8

typedef struct
{
    CART_ID dstId;

    CART_ID brfId;
    
    CART_ID appId;

    uint16_t numBaf;

    CART_ID bafList[MAX_NUM_BTF_RESOURCES]; 

    BTF_Callback_Register* cb;

    char libraryPath[MAX_SHLIB_PATH];

    // void* threadConfig;
} CMB_BTF_Proxy_Config;

#endif /*!defined(CMB_BTF_ADAPTOR_CFG__INCLUDED_)*/
