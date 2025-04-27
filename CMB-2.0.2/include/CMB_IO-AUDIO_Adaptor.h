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
 * @file CMB_IO-AUDIO_Adaptor.h
 *
 * @brief Header file for io-audio adaptor.
 *
 ****************************************************/

#if !defined(CMB_IO_AUDIO_ADAPTOR__INCLUDED_)
#define CMB_IO_AUDIO_ADAPTOR__INCLUDED_


#include "CMB_AdaptorInterface.h"

#ifdef __cplusplus
extern "C" {
#endif

const CMB_AdaptorInterface * const IOA_Adaptor_getInstance();

#ifdef __cplusplus
}
#endif

#endif /*!defined(CMB_IO_AUDIO_ADAPTOR__INCLUDED_)*/
