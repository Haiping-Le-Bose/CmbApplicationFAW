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
 * @file CMB_ASDS_Adaptor.h
 *
 * @brief Header file for Bose ASDS (Automotive Sound 
 * Design Suite) application adaptor.
 *
 ****************************************************/

#if !defined(ASDS_TUNE_ADAPTOR__INCLUDED_)
#define ASDS_TUNE_ADAPTOR__INCLUDED_

#include "CMB_AdaptorInterface.h"
#include "CMB_Socket_Types.h"

#ifdef __cplusplus
extern "C" {
#endif

const CMB_AdaptorInterface * const ASDS_Adaptor_getInstance();

#ifdef __cplusplus
}
#endif

#endif /*!defined(ASDS_TUNE_ADAPTOR__INCLUDED_)*/
