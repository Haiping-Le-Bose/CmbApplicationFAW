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
 * @file BRF.h
 *
 * @brief Implementation of the Class BRF
 *
 * @author: cb1037694
 ****************************************************/

#include "BRF.h"
#include "_BRF.h"
#include "FeatureLib.h"
#include "BACR_API.h"
#include "RMDL.h"

_BRF BRF_obj;

/**
 * Returns pointer to the BRF object associated with the CART_ID passed as argument
 */
BRF* BRF_create(CART_ID brf_id)
{
   BRF_obj.id = brf_id;
   uint8_t baf_id;

   /* set BAF id defaults */
   for (uint8_t i = 0; i < (uint8_t)BRF_RESOURCE_NUM_BAF; i++) {
      baf_id = (uint8_t)CART_ID_BAF + i;
      BRF_obj.resource.baf_id[i] = (CART_ID)(baf_id);
   }
   return  (BRF*) &BRF_obj;
}

BRF_Resource* BRF_resource(BRF* brf)
{
    _BRF* brf_private = (_BRF*) brf;
    return &brf_private->resource;
}

/**
 * This API initializes the BRF module.
 * Prerequisite: BRF_create()
 */
CART_Cmd_Ret BRF_init(BRF* brf, void* ctx)
{
  _BRF* brf_private = (_BRF*) brf;
   CART_Cmd_Ret ret;
   ret.status = CART_STATUS_SUCCESS;

  brf_private->ctx = ctx;
  brf_private->bamfRespCount = 0;
  brf_private->bamfNotifyCount = 0;
  brf_private->bamfInvalidCount = 0;
  for (uint32_t i = 0; i < CART_EXEC_ID_NUM; i++)
  {
    brf_private->execs[i] = NULL;
  }

  brf_private->execs[CART_EXEC_ID_BACR] = BRF_BACR_PeriodicWork;
  brf_private->execs[CART_EXEC_ID_RMDL] = RMDL_StateMachine;
  brf_private->numExecs = 2;

  BRF_FeatureLib_Init(brf_private);

  return ret;
}

/**
 * This API is used to send tune commands to BRF (ex. BDP. BCP)
 */
//#include "bdp.h"
CART_Cmd_Ret BRF_command(BRF* brf, CART_Message* req, CART_Message* rsp)
{
   _BRF* brf_private = (_BRF*) brf;

   CART_Cmd_Ret cmd_ret;
   cmd_ret.status = CART_STATUS_ERROR;
   uint32_t *pCmd = (uint32_t *)req->data;
   // uint32_t *rspBuf = (uint32_t *)rsp->data;
   // uint16_t rspLen = rsp->size;
   CART_ID src, dst;
   uint32_t handle,dstId,srcId,msgId;
   const char* ver;
   char* msg ;
   int32_t status = -1;

   dstId=CART_Message_get_dst(req);
   srcId=CART_Message_get_src(req);
   src = (CART_ID)srcId;
   dst = (CART_ID)dstId;
   brf_private->srcId = src;

   if (!!(brf_private->id != dst)) {
      CART_Message_copy_header(rsp, req);
      rsp->data = req->data;
      CART_Message_set_type(rsp, CART_MESSAGE_TYPE_ERROR);
      CART_Message_set_src(rsp, brf_private->id);
      CART_Message_set_dst(rsp, src);
      cmd_ret.status = CART_STATUS_ERROR;
      return cmd_ret;
   }
   msgId = CART_Message_get_id(req);
   CART_MESSAGE_ID msg_id = (CART_MESSAGE_ID)msgId;
   switch (msg_id)
   {
   case CART_MESSAGE_ID_RMDL_INIT:
      cmd_ret = RMDL_Init(brf_private, req, rsp);

      if(CART_STATUS_SUCCESS == cmd_ret.status)    {
         BRF_Callback_post(CART_EXEC_ID_BACR, brf_private->ctx);
         CART_Message_set_type(rsp, CART_MESSAGE_TYPE_RSP);
      }
      else {
         CART_Message_set_type(rsp, CART_MESSAGE_TYPE_ERROR);
      }
      break;
   case CART_MESSAGE_ID_RMDL_ENG:
      cmd_ret = RMDL_SetEngRoomMode(req, pCmd[0]);

      if(CART_STATUS_SUCCESS == cmd_ret.status)    {
         BRF_Callback_post(CART_EXEC_ID_BACR, brf_private->ctx);
         CART_Message_set_type(rsp, CART_MESSAGE_TYPE_RSP);
      }
      else {
         CART_Message_set_type(rsp, CART_MESSAGE_TYPE_ERROR);
      }
      break;

   case CART_MESSAGE_ID_RMDL_OPT:
      cmd_ret = RMDL_SetOptRoomMode(req, rsp);

      if(CART_STATUS_SUCCESS == cmd_ret.status)    {
         BRF_Callback_post(CART_EXEC_ID_BACR, brf_private->ctx);
         CART_Message_set_type(rsp, CART_MESSAGE_TYPE_RSP);
      }
      else {
         CART_Message_set_type(rsp, CART_MESSAGE_TYPE_ERROR);
      }
      break;
   case CART_MESSAGE_ID_RMDL_BDP:

      BRF_Callback_post(CART_EXEC_ID_BACR, brf_private->ctx);
      CART_Message_set_type(rsp, CART_MESSAGE_TYPE_RSP);
      cmd_ret.status = CART_STATUS_SUCCESS;
      break;
   case CART_MESSAGE_ID_VERSION:
      if ((rsp->data == NULL) || ( rsp->size < (uint32_t)12 )) {
         CART_Message_set_type(rsp, CART_MESSAGE_TYPE_ERROR);
      }
      else {
         CART_Message_set_type(rsp, CART_MESSAGE_TYPE_RSP);
         ver = RMDL_GetVersion();
         msg = (char *)rsp->data;
         for ( uint8_t i = 0; i < (uint8_t)9; i++ )
           {
               *msg++ = *ver++;	// version string length is 9
           }
         status = 12;
         CART_Message_set_size(rsp , status); // roundup to 32bit word size
      }
      cmd_ret.status = CART_STATUS_SUCCESS;
      break;
   case CART_MESSAGE_ID_NVM_STORE_RESTORE:
      if (0 == pCmd[0])
      {
         BRF_Callback_post(CART_EXEC_ID_STATE_RESTORE, brf_private->ctx);
      }
      else if (1 == pCmd[0])
      {
         BRF_Callback_post(CART_EXEC_ID_STATE_SAVE, brf_private->ctx);
      }
      CART_Message_set_type(rsp, CART_MESSAGE_TYPE_RSP);
      cmd_ret.status = CART_STATUS_SUCCESS;
      break;
   default:
      CART_Message_set_type(rsp, CART_MESSAGE_TYPE_ERROR);
      CART_Message_set_size(rsp, 0);
      cmd_ret.status = CART_STATUS_ERROR;
      break;
   }
   srcId=CART_Message_get_src(req);
   dstId=CART_Message_get_dst(req);
   src = (CART_ID)srcId;
   dst = (CART_ID)dstId;
   handle=CART_Message_get_handle(req);
   CART_Message_set_src(rsp, dst);
   CART_Message_set_id(rsp, msg_id);
   CART_Message_set_dst(rsp, src);
   CART_Message_set_handle(rsp, handle);

   return cmd_ret;
}

/**
 * This API is invoked by the BRF_receive() dispatcher to send BAF responses to
 * BRF (ex. TOP, TSP reads)
 */
CART_Cmd_Ret BRF_receive(BRF* brf, CART_Message* rsp)
{
   _BRF* brf_private = (_BRF*) brf;
   CART_Cmd_Ret ret;
   ret.status = CART_STATUS_SUCCESS;
   BRF_BACR_receive(brf_private, rsp);
   return ret;
}

/**
 * This API translates Tune commands to BAF command message(s), serializes and
 * sends the message to BAF
 */
CART_Cmd_Ret BRF_exec(BRF* brf, CART_EXEC_ID exec_id, void* ctx)
{
   _BRF* brf_private = (_BRF*) brf;
   CART_Cmd_Ret ret;
   ret.status = CART_STATUS_SUCCESS;

   if ((exec_id < CART_EXEC_ID_NUM) &&
       (brf_private->execs[exec_id] != NULL))
   {
      brf_private->execs[exec_id](brf_private);
   }
   else
   {
      ret.status = CART_STATUS_ERROR;
   }
   return ret;
} 

/**
 * This API is used by the application to register a new exec
 * function. The exec_id to be used must be predefined in CART.
 * This function can also be used to deregister a function by
 * specifying CART_NULL as the execFnPtr parameter.
 */
CART_Cmd_Ret _BRF_register_exec(BRF* brf, CART_EXEC_ID exec_id, BRF_Process_Fn execFnPtr)
{
   _BRF* brf_private = (_BRF*) brf;
   CART_Cmd_Ret cmd_ret = {CART_STATUS_SUCCESS};
   if (exec_id < CART_EXEC_ID_NUM)
   {
      /* Was an exec function not previously defined? increment */
      if (brf_private->execs[exec_id] == NULL)
      {
         if (execFnPtr != NULL)
         {
            brf_private->numExecs += 1;
         }
      }
      else
      {
         /* Was an exec function previously defined? leave the number intact, unless
          * it is being replaced with null
          */
         if (execFnPtr == NULL)
         {
            brf_private->numExecs -= 1;
         }
      }
      brf_private->execs[exec_id] = execFnPtr;
   }
   else
   {
      cmd_ret.status = CART_STATUS_OUTOFRANGE;
   }
   return cmd_ret;
}
