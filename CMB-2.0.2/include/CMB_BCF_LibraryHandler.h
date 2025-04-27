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
 * @file CMB_BCF_LibraryHandler.h
 *
 * @brief Header file for BCF library handler.
 *
 ****************************************************/

#if !defined(CMB_BCF_ADAPTOR__LIBRARY_HANDLER_I_NCLUDED_)
#define CMB_BCF_ADAPTOR__LIBRARY_HANDLER_I_NCLUDED_

#include "CART_Cmd_Ret.h"
#include "CMB_BCF_Adaptor_Config.h"
#include "BCF_Callback_Register.h"
#include "BCF_Dll.h"


#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    BCF_Create_Fxn create;
    BCF_Resource_Fxn resource;
    BCF_Init_Fxn init;
    BCF_Command_Fxn command;
    BCF_Exec_Fxn exec;
    BCF_Receive_Fxn receive;
    BCF_Callback_Register_Post_Fxn register_post;
    BCF_Callback_Register_Notify_Fxn register_notify;
    BCF_Callback_Register_Send_Fxn register_send;
    BCF* bcf;
    void* libHandle;
} BCF_Library_Context;


typedef struct 
{
    BCF_Library_Context* libContext;
    
    // Thread context.

} CallbackPostContext;


typedef struct
{
    CMB_BCF_Proxy_Config* cfg;

    CallbackPostContext* postContext;

} BCF_Library_Config;


CART_Cmd_Ret CMB_BCF_libraryInitialize(BCF_Library_Context* bcfl, BCF_Library_Config* cfg);

CART_Cmd_Ret CMB_BCF_libraryDeinitialize(BCF_Library_Context* bcfl);

#ifdef __cplusplus
}
#endif

#endif /*!defined(CMB_BCF_ADAPTOR__LIBRARY_HANDLER_I_NCLUDED_)*/
