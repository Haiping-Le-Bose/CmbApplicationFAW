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
 * @file CMB_BRF_Adaptor.h
 *
 * @brief Header file for BRF adaptor.
 *
 ****************************************************/

#if !defined(CMB_BRFADAPTOR__INCLUDED_)
#define CMB_BRFADAPTOR__INCLUDED_

#include "CART_Cmd_Ret.h"
#include "CMB_AdaptorInterface.h"

#ifdef __cplusplus
extern "C" {
#endif

const CMB_AdaptorInterface * const BRF_Adaptor_getInstance();

void BOSE_BRF_Callback_post(CART_EXEC_ID id, void* arg);

CART_Cmd_Ret BOSE_BRF_Callback_notify(CART_Message* notify);

CART_Cmd_Ret BOSE_BRF_Callback_send(CART_Message* msg);

CART_Cmd_Ret ENT_BRF_Callback_read(BRF_STORAGE_ID storage_id, uint32_t address, uint32_t size, uint8_t* buf, void* arg);

CART_Cmd_Ret BOSE_BRF_Callback_write(BRF_STORAGE_ID storage_id, uint32_t address, uint32_t size, uint8_t* buf, void* arg);

int BRF_printf(const char* fmt, ...);

#ifdef __cplusplus
}
#endif

#endif /*!defined(CMB_BRFADAPTOR__INCLUDED_)*/
