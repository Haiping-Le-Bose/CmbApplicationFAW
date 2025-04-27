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
 * @file _BTF.h
 *
 * @ingroup _BTF
 *
 * @brief Implementation of the Class _BTF
 *
 * @author: cb1037694
 ****************************************************/

#if !defined(BC__BTF__INCLUDED_)
#define BC__BTF__INCLUDED_

#include "BTF.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "BTF_Resource.h"

typedef struct _BTF _BTF;
/**
 * Function pointer definition to be used for BTF Exec function
 * prototypes
 */
typedef void (*BTF_Process_Fn)(_BTF* btf);

/**
 * @ingroup _BTF
 *
 * @brief This is the internal structure that holds the Bose Tuning Framework (BTF) details.
 * This structure is not visible to the CART Integrator and is hidden through the BTF object.
 * 
 * @author cb1037694
 * 
 * @version 1.1
 */
struct _BTF
{
   CART_ID id;
   /**
    * @ingroup _BTF
    *
    * @brief Application context
    */
   void *ctx;
   BTF_Resource resource;
   CART_ID srcId;

   uint32_t bamfRespCount;
   uint32_t bamfNotifyCount;
   uint32_t bamfInvalidCount;
   uint32_t bamfSendCount;

   uint32_t numExecs;
   BTF_Process_Fn execs[CART_EXEC_ID_NUM];
};


/**
 * @ingroup _BTF
 *
 * @brief This API registers an exec function pointer associated with
 *        a given exec ID.
 *
 * @param btf Pointer to the BTF object
 *
 * @param exec_id Integer value indicating the thread execution function to be
 * executed. This value must be a valid exec ID value.
 *
 * @param execFnPtr Function pointer to exec function to be called. If this parameter
 * is NULL, then the exec ID no longer has a function registered for it.
 */
CART_Cmd_Ret _BTF_register_exec(BTF* btf, CART_EXEC_ID exec_id, BTF_Process_Fn execFnPtr);

#ifdef __cplusplus
}
#endif


#endif /*!defined(BC__BTF__INCLUDED_)*/
