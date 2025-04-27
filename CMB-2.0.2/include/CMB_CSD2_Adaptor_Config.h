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
 * @file CMB_CSD2_Adaptor_Config.h
 *
 * @brief Header file for CSD2 adaptor proxy configuration.
 *
 ****************************************************/

#if !defined(CMB_CSD2_ADAPTOR_CFG__INCLUDED_)
#define CMB_CSD2_ADAPTOR_CFG__INCLUDED_

#include "CART_ID.h"
#include "mmdefs.h"
#include "kvh2xml.h"
#include "csd2_ioctl.h"

#ifdef __cplusplus
extern "C" {
#endif

#define CMB_CSD2_Graph_Config_maxListSize 5

// Graph configuration needed by csd2 driver.
typedef struct CMB_CSD2_Graph_Cfg
{
    uint32_t usecaseId;

    uint32_t listSize;
    
    struct csd2_key_value valueList[CMB_CSD2_Graph_Config_maxListSize];
} CMB_CSD2_Graph_Config;


// This is configuration data for csd2 adaptor and driver.
typedef struct
{
    uint32_t moduleTag;

    uint32_t pid;

    CART_ID id;

    CMB_CSD2_Graph_Config graph;

    uint32_t mask;
} CMB_CSD2_Proxy_Config;

#ifdef __cplusplus
}
#endif

#endif /*!defined(CMB_CSD2_ADAPTOR_CFG__INCLUDED_)*/
