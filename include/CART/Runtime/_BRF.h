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
 * @file _BRF.h
 *
 * @ingroup _BRF
 *
 * @brief Implementation of the Class _BRF
 *
 * @author: cb1037694
 ****************************************************/

#if !defined(BC__BRF__INCLUDED_)
#define BC__BRF__INCLUDED_

#include "BRF.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "BRF_Resource.h"

typedef struct _BRF _BRF;
/**
 * Function pointer definition to be used for BRF Exec function
 * prototypes.
 */
typedef void (*BRF_Process_Fn)(_BRF* brf);

/**
 * @ingroup _BRF
 *
 * @brief This is the internal structure that holds the Bose RoomModelDownload Framework (BRF) details.
 * This structure is not visible to the CART Integrator and is hidden through the BRF object.
 * 
 * @author cb1037694
 * 
 * @version 1.1
 */
struct _BRF
{
   CART_ID id;
   /**
    * @ingroup _BRF
    *
    * @brief Application context
    */
   void *ctx;
   BRF_Resource resource;
   CART_ID srcId;

   uint32_t bamfRespCount;
   uint32_t bamfNotifyCount;
   uint32_t bamfInvalidCount;
   uint32_t bamfSendCount;

   uint32_t numExecs;
   BRF_Process_Fn execs[CART_EXEC_ID_NUM];
};

/**
 * @ingroup _BRF
 *
 * @brief This API registers an exec function pointer associated with
 *        a given exec ID.
 *
 * @param brf Pointer to the BRF object
 *
 * @param exec_id Integer value indicating the thread execution function to be
 * executed. This value must be a valid exec ID value.
 *
 * @param execFnPtr Function pointer to exec function to be called. If this parameter
 * is NULL, then the exec ID no longer has a function registered for it.
 */
CART_Cmd_Ret _BRF_register_exec(BRF* brf, CART_EXEC_ID exec_id, BRF_Process_Fn execFnPtr);

#ifdef __cplusplus
}
#endif


#endif /*!defined(BC__BRF__INCLUDED_)*/
