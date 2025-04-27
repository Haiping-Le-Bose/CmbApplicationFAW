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
 * @file CMB_CSD2_Adaptor.h
 *
 * @brief Header file for CSD2 adaptor.
 *
 ****************************************************/

#if !defined(CMB_CSD2_ADAPTOR__INCLUDED_)
#define CMB_CSD2_ADAPTOR__INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include "CMB_AdaptorInterface.h"

const CMB_AdaptorInterface * const CSD2_Adaptor_getInstance();

#ifdef __cplusplus
}
#endif

#endif /*!defined(CMB_CSD2_ADAPTOR__INCLUDED_)*/
