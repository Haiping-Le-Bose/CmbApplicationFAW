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
 * @file CMB_ACS_Adaptor.h
 *
 * @brief Header file for Audio Control Service (ACS) adaptor.
 *
 ****************************************************/

#if !defined(ACS_ADAPTOR__INCLUDED_)
#define ACS_ADAPTOR__INCLUDED_

#include "CMB_AdaptorInterface.h"

#ifdef __cplusplus
extern "C" {
#endif

const CMB_AdaptorInterface * const ACS_Adaptor_getInstance();

#ifdef __cplusplus
}
#endif

#endif /*!defined(ACS_ADAPTOR__INCLUDED_)*/
