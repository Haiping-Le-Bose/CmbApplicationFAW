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
 * @file CMB_BTF_LibraryHandler.h
 *
 * @brief Header file for BTF library handler.
 *
 ****************************************************/

#if !defined(CMB_BTF_ADAPTOR__LIBRARY_HANDLER_I_NCLUDED_)
#define CMB_BTF_ADAPTOR__LIBRARY_HANDLER_I_NCLUDED_

#include "CART_Cmd_Ret.h"
#include "CMB_BTF_Adaptor_Config.h"
#include "BTF_Callback_Register.h"
#include "BTF_Dll.h"


#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    BTF_Create_Fxn create;
    BTF_Resource_Fxn resource;
    BTF_Init_Fxn init;
    BTF_Command_Fxn command;
    BTF_Exec_Fxn exec;
    BTF_Receive_Fxn receive;
    BTF_Callback_Register_Post_Fxn register_post;
    BTF_Callback_Register_Notify_Fxn register_notify;
    BTF_Callback_Register_Send_Fxn register_send;        
    BTF* btf;
    void* libHandle;
} BTF_Library_Context;


typedef struct 
{
    BTF_Library_Context* libContext;
    
    // Thread context.

} CallbackPostContext;


typedef struct
{
    CMB_BTF_Proxy_Config* cfg;    

    CallbackPostContext* postContext;

} BTF_Library_Config;


CART_Cmd_Ret CMB_BTF_libraryInitialize(BTF_Library_Context* btfl, BTF_Library_Config* cfg);

CART_Cmd_Ret CMB_BTF_libraryDeinitialize(BTF_Library_Context* btfl);

#ifdef __cplusplus
}
#endif

#endif /*!defined(CMB_BTF_ADAPTOR__LIBRARY_HANDLER_I_NCLUDED_)*/
