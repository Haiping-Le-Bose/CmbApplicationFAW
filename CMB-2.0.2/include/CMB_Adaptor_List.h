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
 * @file AdaptorList.h
 *
 * @brief Header file to include all adaptors required
 * for this use case.
 ****************************************************/

#if !defined(CMB_ADAPTOR_LIST__INCLUDED_)
#define CMB_ADAPTOR_LIST__INCLUDED_

#include "CMB_TYPES.h"

// Include file for Adaptors.
#if ENABLE_BAF_ADAPTOR
#include "CMB_BAF_Adaptor.h"
#endif

#include "CMB_BTF_Adaptor.h"
#include "CMB_BCF_Adaptor.h"
#include "CMB_BRF_Adaptor.h"
#include "CMB_IO-AUDIO_Adaptor.h"
#include "CMB_CSD2_Adaptor.h"
#include "CMB_ACS_Adaptor.h"
#include "CMB_AMS_Adaptor.h"

#if ENABLE_ASDS_ADAPTOR
#include "CMB_ASDS_Adaptor.h"
#endif

#include "CMB_Control_Adaptor.h"
#include "CMB_Tuning_Adaptor.h"


#endif /*!defined(CMB_ADAPTOR_LIST__INCLUDED_)*/
