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
 * @file CMB_AMS_ADAPTOR_Config.h
 *
 * @brief Header file for AMS adaptor proxy configuration.
 *
 ****************************************************/

#if !defined(CMB_AMS_ADAPTOR_CFG__INCLUDED_)
#define CMB_AMS_ADAPTOR_CFG__INCLUDED_

#include "CMB_TYPES.h"

#ifdef __cplusplus
extern "C" {
#endif

// Graph configuration needed by AMS driver.
typedef struct CMB_AMS_Graph_Cfg
{
    uint32_t usecaseId;

} CMB_AMS_Graph_Config;


// This is configuration data for AMS adaptor and driver.
typedef struct
{
    CART_ID dstId;

    CMB_AMS_Graph_Config graph;

} CMB_AMS_Proxy_Config;

#ifdef __cplusplus
}
#endif

#endif /*!defined(CMB_AMS_ADAPTOR_CFG__INCLUDED_)*/
