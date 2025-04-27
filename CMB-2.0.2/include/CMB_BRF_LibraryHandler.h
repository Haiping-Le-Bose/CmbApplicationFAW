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
 * @file CMB_BRF_LibraryHandler.h
 *
 * @brief Header file for BRF library handler.
 *
 ****************************************************/

#if !defined(CMB_BRF_ADAPTOR__LIBRARY_HANDLER_I_NCLUDED_)
#define CMB_BRF_ADAPTOR__LIBRARY_HANDLER_I_NCLUDED_

#include "CART_Cmd_Ret.h"
#include "CMB_BRF_Adaptor_Config.h"
#include "BRF_Callback_Register.h"
#include "BRF_Dll.h"


#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    BRF_Create_Fxn create;
    BRF_Resource_Fxn resource;
    BRF_Init_Fxn init;
    BRF_Command_Fxn command;
    BRF_Exec_Fxn exec;
    BRF_Receive_Fxn receive;
    BRF_Callback_Func_Read read;
    BRF_Callback_Func_Write write;
    BRF_Callback_Register_Post_Fxn register_post;
    BRF_Callback_Register_Notify_Fxn register_notify;
    BRF_Callback_Register_Send_Fxn register_send;
    BRF_Callback_Register_Read_Fxn register_read;
    BRF_Callback_Register_Write_Fxn register_write;
    BRF* brf;
    void* libHandle;
} BRF_Library_Context;


typedef struct 
{
    BRF_Library_Context* libContext;
    
    // Adaptor context to get to database variables managed by the adaptor.
    void* brfaCtx;

    uint8_t proxyIndex;

    void* applicationContext;
    // Thread context.

} CallbackPostContext;


typedef struct
{
    CMB_BRF_RNDB_Proxy_Config* cfg;

    CallbackPostContext* postContext;

} BRF_Library_Config;


CART_Cmd_Ret CMB_BRF_libraryInitialize(BRF_Library_Context* brfl, BRF_Library_Config* cfg);

CART_Cmd_Ret CMB_BRF_libraryDeinitialize(BRF_Library_Context* brfl);

#ifdef __cplusplus
}
#endif

#endif /*!defined(CMB_BRF_ADAPTOR__LIBRARY_HANDLER_I_NCLUDED_)*/
