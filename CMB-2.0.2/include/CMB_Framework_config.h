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
 * @file CMB_Framework_config.h
 *
 * @brief Header file defines the structures and types  
 * needed for configuring the CMBF.
 ****************************************************/

#if !defined(CMB_FRAMEWORK_CONFIG__INCLUDED_)
#define CMB_FRAMEWORK_CONFIG__INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include "CMB_TYPES.h"
#include "CMB_AdaptorInterface.h"

#define MAX_FRAMEWORK_CONFIGS     16
#define MAX_ADAPTOR_CONFIGS       16
#define MAX_PROXY_CONFIGS         16
#define MAX_BAF_LIST_SIZE         16

typedef struct CMB_Framework_periodOperationsConfig
{
    // Number of valid entries in bafList.
    uint16_t numBafToPoll;

    // List of BAFs to send periodic notification requests.
    CART_ID bafList[MAX_BAF_LIST_SIZE];
} CMB_Framework_periodicOperationsConfig;


typedef struct CMB_Framework_adaptorConfig
{    
    // Pointer to adaptor interface object defined by the adaptor.
    CMB_AdaptorInterface* adaptorObject;

    // Number of proxys connected to this adaptor in the current framework.
    uint8_t numberOfProxys;

    // Configuration of each proxy.
    CMB_Adaptor_proxyConfig proxyList[MAX_PROXY_CONFIGS]; 

    // Set to 0 if application prefers to call BxF_exec(CART_EXEC_ID_DEFAULT) manually. 
    // Recommend setting it to non-zero to let the framework manage those calls internally.
    // Non-BxF adaptors (example, CSD2 adaptor, Tuning adaptor) should set this to 0.
    uint8_t enableAdaptorExecs;

    // Set to non-zero value if the adaptor interface's receive() is to called 
    // periodically to get messages. Set to 0 otherwise.
    uint8_t enableAdaptorRecv;    
} CMB_Framework_adaptorConfig;


typedef struct CMB_Framework_config
{
    // The CART ID of the CMB.
    CART_ID busId;
    
    // Provide a name for the configuration.
    uint8_t name[256];

    // Configuration for period operations such as polling for notifications.
    CMB_Framework_periodicOperationsConfig cartPoller;

    // Number of Adaptors to be connected to the CMB in this framework.
    uint8_t numberOfAdaptors;

    // Configuration of each adaptor.
    CMB_Framework_adaptorConfig adaptorList[MAX_ADAPTOR_CONFIGS];

} CMB_Framework_config;

#ifdef __cplusplus
}
#endif

#endif /*!defined(CMB_FRAMEWORK_CONFIG__INCLUDED_)*/
