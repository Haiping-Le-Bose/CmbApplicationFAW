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
 * @file CMB_Manager_private.h
 *
 * @ingroup CMB_Manager_private
 *
 * @brief Declaration of CART Message Bus Framework (CMBF) internal structure 
 *  (private data).
 *
 ****************************************************/

#if !defined(BC__CMBM__INCLUDED_)
#define BC__CMBM__INCLUDED_


#ifdef __cplusplus
extern "C" {
#endif

#include "CMB.h"
#include "CART_ID.h"
#include "CMB_TYPES.h"
#include "CMB_Resource.h"
#include "CMB_AdaptorInterface.h"
#include "CMB_Framework.h"

// Resize array according to feature list and adaptor per feature that need BxF_exec calls.
#define MAX_ADAPTOR_EXEC_LIST_SIZE MAX_NUM_OF_ADAPTORS

typedef enum
{
    CMB_STATE_FIRST = 0,
    CMB_STATE_IDLE,
    CMB_STATE_STARTING,
    CMB_STATE_RUNNING_ON,
    CMB_STATE_RUNNING_SUSPENDED,
    CMB_STATE_RUNNING_OFF,
    CMB_STATE_TERMINATING,
    CMB_STATE_TERMINATED,
    CMB_STATE_LAST,
    CMB_STATE_COUNT = CMB_STATE_LAST - CMB_STATE_FIRST,
} CMB_STATE;


/**
 * @ingroup CMB_Manager_private
 *
 * @brief This is the internal structure that holds the CMBM details.
 * This structure is not visible to the CART Integrator and is hidden through the CMBM object.
 *  
 * @version 1.0
 */
typedef struct
{
    uint8_t created; // Deprecate this and only use state.

    CMB_STATE state;

    //CART_ID id; Consider making instance_id as cart id ? distributed bus management may need it.
    // uint8_t reserved_instance_id;

    //CMBM_Resource resource;

    // CMBM_Context* reserved_context; // for multi-instance.

    // Pointer to the creator of the CMB Manager that will register callbacks.
    // Should be extended to an array if multiple adaptors need to register callbacks.
    CART_ID creators_id;

    CMB_Adaptor_Id adaptorIdForCallbacks;

    CMB_AdaptorInterface* adaptorObjectForCallbacks;

    // Runtime parameters (overrides compile time configuration) provided by application.
    CMB_Framework_params applicationParams;

    // For multi-BxF, the list should include BxF for each feature (ENT and RNC for example).
    CMB_Adaptor_Id adaptorExecList[MAX_ADAPTOR_EXEC_LIST_SIZE];

    // Number of valid entries in adaptorExecList.
    uint16_t numAdaptorToExec;

    // List of adaptors that need to be called periodically to get external messages.
    CMB_AdaptorInterface* adaptorRevcList[MAX_ADAPTOR_EXEC_LIST_SIZE];

    uint16_t numAdaptorToRecvOn;

    // Number of times Periodic operations loop has been executed.
    unsigned long long counter;
} _CMB_Framework;


#ifdef __cplusplus
}
#endif


#endif /*!defined(BC__CMBM__INCLUDED_)*/
