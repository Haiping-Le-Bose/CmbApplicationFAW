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
 * @file CMB_BRF_ADAPTOR_Config.h
 *
 * @brief Header file for BRF adaptor proxy configuration.
 *
 ****************************************************/

#if !defined(CMB_BRF_ADAPTOR_CFG__INCLUDED_)
#define CMB_BRF_ADAPTOR_CFG__INCLUDED_

#include <unistd.h>
#include "CMB_TYPES.h"
#include "BRF_Callback_Register.h"
#include "BRF_Callback.h"

#define RNDB_PATH_SIZE      256
#define MAX_DB_PER_PROXY    4
#define MAX_SHLIB_PATH      512
#define MAX_BRF_PROXY_CNT   8

typedef struct
{
    uint8_t databaseCount;

    // List the storage ID, in order, for the databases that are present.
    // Better create a struct with BRF_STORAGE_ID to gather all related params. 
    // BRF_STORAGE_ID storageId[MAX_DB_PER_PROXY];

    // The order must match the BRF_STORAGE_ID.
    uint32_t rndbStartAddress[MAX_DB_PER_PROXY];

    uint32_t steeringWheelPosition; 

    // The order must match the BRF_STORAGE_ID.
    int8_t rndbPath[MAX_DB_PER_PROXY][RNDB_PATH_SIZE];

    CART_ID dstId;

    uint16_t numBaf;

    CART_ID bafList[10]; // BTF_RESOURCE_NUM_BAF need to be updated to 10.
    
    BRF_Callback_Register* cb;

    int8_t libraryPath[MAX_SHLIB_PATH];

    void* applicationContext;
    // void* threadConfig;
} CMB_BRF_RNDB_Proxy_Config;

#endif /*!defined(CMB_BRF_ADAPTOR_CFG__INCLUDED_)*/
