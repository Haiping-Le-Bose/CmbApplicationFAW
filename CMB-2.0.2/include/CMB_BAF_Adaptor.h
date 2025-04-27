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
 * @file CMB_BAF_Adaptor.h
 *
 * @brief Header file for BAF adaptor.
 *
 ****************************************************/

#if !defined(CMB_BAFADAPTOR__INCLUDED_)
#define CMB_BAFADAPTOR__INCLUDED_

#include "CMB_AdaptorInterface.h"

#ifdef __cplusplus
extern "C" {
#endif

const CMB_AdaptorInterface * const BAF_Adaptor_getInstance();

void BAF_Callback_sys_process_ctx(uint32_t proc_Id, uint32_t frame_size, uint32_t num_chan_in, uint32_t num_chan_out, void* src, void* dst, void* arg);

void BAF_Callback_sys_process(uint32_t proc_Id, uint32_t frame_size, uint32_t num_chan_in, uint32_t num_chan_out, void* src, void* dst);

#ifdef __cplusplus
}
#endif

#endif /*!defined(CMB_BAFADAPTOR__INCLUDED_)*/
