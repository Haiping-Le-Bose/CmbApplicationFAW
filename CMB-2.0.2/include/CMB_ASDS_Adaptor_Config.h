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
 * @file CMB_ASDS_Adaptor_Config.h
 *
 * @brief Header file for BAF adaptor proxy configuration.
 *
 ****************************************************/

#if !defined(CMB_ASDS_ADAPTOR_CFG__INCLUDED_)
#define CMB_ASDS_ADAPTOR_CFG__INCLUDED_

#include "CART_ID.h"
#include "CMB_Socket_Types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    CART_ID dstId;

    Adaptor_Connection_cfg connection;

} CMB_ASDS_Proxy_Config;

#ifdef __cplusplus
}
#endif

#endif /*!defined(CMB_ASDS_ADAPTOR_CFG__INCLUDED_)*/
