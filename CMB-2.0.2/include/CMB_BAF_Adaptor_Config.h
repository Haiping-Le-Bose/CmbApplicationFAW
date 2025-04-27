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
 * @file CMB_BAF_ADAPTOR_Config.h
 *
 * @brief Header file for BAF adaptor proxy configuration.
 *
 ****************************************************/

#if !defined(CMB_BAF_ADAPTOR_CFG__INCLUDED_)
#define CMB_BAF_ADAPTOR_CFG__INCLUDED_

#include "CART_ID.h"
#include "BAF_Callback_Register.h"

#define MAX_NUM_BAF_PROXYS              16
#define MAX_SHLIB_PATH                  512

typedef struct
{
    CART_ID id;

    uint32_t mask;

    uint8_t* bafPrivateMemory;

    uint32_t memorySize;
    
    BAF_Callback_Register* cb;

    char libraryPath[MAX_SHLIB_PATH];
} CMB_BAF_Proxy_Config;

#endif /*!defined(CMB_BAF_ADAPTOR_CFG__INCLUDED_)*/
