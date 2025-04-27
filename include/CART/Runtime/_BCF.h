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
 * @file _BCF.h
 *
 * @ingroup _BCF
 *
 * @brief Implementation of the Class _BCF
 *
 * @author: cb1037694
 ****************************************************/

#if !defined(BC__BCF__INCLUDED_)
#define BC__BCF__INCLUDED_

#include "BCF.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "BCF_Resource.h"

typedef struct _BCF _BCF;
/**
 * Function pointer definition to be used for BCF Exec function
 * prototypes
 */
typedef void (*BCF_Process_Fn)(_BCF* bcf);

/**
 * @ingroup _BCF
 *
 * @brief This is the internal structure that holds the Bose Tuning Framework (BCF) details.
 * This structure is not visible to the CART Integrator and is hidden through the BCF object.
 * 
 * @author cb1037694
 * 
 * @version 1.1
 */
struct _BCF
{
   CART_ID id;
   /**
    * @ingroup _BCF
    *
    * @brief Application context
    */
   void *ctx;
   BCF_Resource resource;
   CART_ID srcId;

   uint32_t bamfRespCount;
   uint32_t bamfNotifyCount;
   uint32_t bamfInvalidCount;
   uint32_t bamfSendCount;

   uint32_t numExecs;
   BCF_Process_Fn execs[CART_EXEC_ID_NUM];
};

/**
 * @ingroup _BCF
 *
 * @brief This API registers an exec function pointer associated with
 *        a given exec ID.
 *
 * @param bcf Pointer to the BCF object
 *
 * @param exec_id Integer value indicating the thread execution function to be
 * executed. This value must be a valid exec ID value.
 *
 * @param execFnPtr Function pointer to exec function to be called. If this parameter
 * is NULL, then the exec ID no longer has a function registered for it.
 */
CART_Cmd_Ret _BCF_register_exec(BCF* bcf, CART_EXEC_ID exec_id, BCF_Process_Fn execFnPtr);

#ifdef __cplusplus
}
#endif


#endif /*!defined(BC__BCF__INCLUDED_)*/
