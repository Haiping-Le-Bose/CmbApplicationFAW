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
 * @file CMB_BTF_Adaptor.h
 *
 * @brief Header file for BTF adaptor.
 *
 ****************************************************/

#if !defined(CMB_BTFADAPTOR__INCLUDED_)
#define CMB_BTFADAPTOR__INCLUDED_

#include "CMB_AdaptorInterface.h"
#include "BRF_Callback.h"

#ifdef __cplusplus
extern "C" {
#endif

const CMB_AdaptorInterface * const BTF_Adaptor_getInstance();

void BEA_BTF_Callback_post(CART_EXEC_ID id, void* arg);

CART_Cmd_Ret BEA_BTF_Callback_notify(CART_Message* notify);

CART_Cmd_Ret BEA_BRF_Callback_read(BRF_STORAGE_ID storage_id, uint32_t address, uint32_t size, uint8_t* buf, void* arg);

CART_Cmd_Ret BEA_BTF_Callback_send(CART_Message* msg);

int BTF_printf(const char* fmt, ...);

#ifdef __cplusplus
}
#endif

#endif /*!defined(CMB_BTFADAPTOR__INCLUDED_)*/
