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
 * @file CMB_BAF_LibraryHandler.h
 *
 * @brief Header file for BAF library handler.
 *
 ****************************************************/

#if !defined(CMB_BAF_ADAPTOR__LIBRARY_HANDLER_I_NCLUDED_)
#define CMB_BAF_ADAPTOR__LIBRARY_HANDLER_I_NCLUDED_

#include "CART_Cmd_Ret.h"
#include "CMB_BAF_Adaptor_Config.h"
#include "BAF_Callback_Register.h"
#include "BAF_Dll.h"


#ifdef __cplusplus
extern "C" {
#endif

typedef void (*CART_Callback_Register_Sys_Process_Ctx_Fxn)(BAF_Callback_Func_Sys_Process_Ctx funcptr);
typedef void (*CART_Callback_Register_Sys_Process_Fxn)(BAF_Callback_Func_Sys_Process funcptr);


typedef struct {
    const char* path;
    CMB_BAF_Proxy_Config* cfg;

    BAF_Create_Fxn create;
    BAF_Resource_Fxn resource;
    BAF_Init_Fxn init;
    BAF_Command_Fxn command;
    BAF_Exec_Fxn exec;
    CART_Callback_Register_Sys_Process_Ctx_Fxn register_sys_process_ctx;
    
    // BTF_Callback_Register_Post_Fxn register_post;
    // BTF_Callback_Register_Notify_Fxn register_notify;
    // BTF_Callback_Register_Send_Fxn register_send;  

    BAF* baf;
    void* libHandle;
} BAF_Library_Context;

typedef struct 
{
    BAF_Library_Context* libContext;
    
    // Thread context.

} CallbackPostContext;


typedef struct
{
    CMB_BAF_Proxy_Config* cfg;    

    CallbackPostContext* postContext;

} BAF_Library_Config;

CART_Cmd_Ret CMB_BAF_libraryInitialize(BAF_Library_Context* bafl, BAF_Library_Config* cfg);

CART_Cmd_Ret CMB_BAF_libraryDeinitialize(BAF_Library_Context* bafl);

#ifdef __cplusplus
}
#endif

#endif /*!defined(CMB_BAF_ADAPTOR__LIBRARY_HANDLER_I_NCLUDED_)*/
