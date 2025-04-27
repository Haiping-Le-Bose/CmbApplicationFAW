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
 * @file CMB_Framework.c
 *
 * @brief Implementation of the CMB_Framework to create and attach
 * CART Message Bus with various adaptors io-audio and CSD2 adaptors.
 * BTF and BAFs on hardware, AATMA on PC to send BDP messages to this application.
 ****************************************************/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/stat.h>
#include <stddef.h>
#include <stdarg.h>

#include <unistd.h>
#include <signal.h>
#include <time.h>

#include "CART.h"
// #include "BTF.h"  

// #ifdef ENABLE_BRF
// #include "BRF.h"  
// #endif  //  ENABLE_BRF

#include "CMB.h"
#include "CART_ID.h"
#include "CMB_TYPES.h"
#include "CMB_Socket_Types.h"
#include "CMB_Logger.h"
#include "CMB_Framework_config.h"
#include "CMB_Framework.h"
#include "CMB_Framework_private.h"

#define LOG_STR "CMB Framework:"
#define BUFFER_SIZE  (2 * MAX_MSG_SIZE)

#ifndef APX_BAF_ID
#define APX_BAF_ID CART_ID_BAF4
#endif

CMB_Context busContext;

// Size, in bytes, of heap for CMB.
#define CMB_HEAP_SIZE 4096

uint8_t busHeap[CMB_HEAP_SIZE];

// Should move CMB_Context, busHeap and all globals into _CMB_Framework object.
_CMB_Framework CMB_Framework_obj;

// In case poller is triggered by a timer.
// static const uint8_t intervalExpired = 1;


CART_STATUS CMB_Framework_initializeTimer(const CMB_Framework_params* userParams)
{
    CART_STATUS retVal = CART_STATUS_SUCCESS;

#if 0
    // Design.
    struct itimerspec its;

    its.it_value.tv_sec = freq_nanosecs / 1000000000;
    its.it_value.tv_nsec = freq_nanosecs % 1000000000;
    its.it_interval.tv_sec = its.it_value.tv_sec;
    its.it_interval.tv_nsec = its.it_value.tv_nsec;
#endif
    return retVal;
}

CART_STATUS CMB_Framework_initialize(const CMB_Framework_params* userParams)
{
    CART_STATUS retVal = CART_STATUS_SUCCESS;
    CART_STATUS retVal1 = CART_STATUS_SUCCESS;

    CMB_Framework_params* params = &CMB_Framework_obj.applicationParams;

    params->enableControlAppConnection = userParams->enableControlAppConnection;

    params->enableTuningAppConnection = userParams->enableTuningAppConnection;

    params->periodicWorkInterval = userParams->periodicWorkInterval;

    params->socketType = userParams->socketType;

    params->logLevel = userParams->logLevel;

    params->pollApxBaf = userParams->pollApxBaf;

    memcpy(params->sndPcmDeviceName, userParams->sndPcmDeviceName, SND_PCM_DEVICE_NAME_LEN); 

    memcpy(&params->configuration, &userParams->configuration, sizeof(params->configuration)); 

    CMB_Logger_setLevel(params->logLevel);

    const CMB_Framework_config* const cfg = &params->configuration; 

    const CMB_Config busCfg = {cfg->busId, cfg->numberOfAdaptors};

    memset((void*)&busContext, 0, sizeof(busContext));

    busContext.cmb = CMB_create(&busCfg);

#ifdef STUB_DRIVER
    CMB_Logger_warn("%s STUB_DRIVERs enabled. \n", LOG_STR);
#endif

    CMB *ccbHandle = busContext.cmb;

    CMB_Resource *resource = CMB_resource(ccbHandle);

    if (resource->memorySize > CMB_HEAP_SIZE)
    {
        CMB_Logger_error("%s: Error: Control bus needs heap of size %d. \n",
               LOG_STR, resource->memorySize);

        retVal = CART_STATUS_ERROR;
    }
    else
    {
        CART_Cmd_Ret ccbStatus = {CART_STATUS_SUCCESS};

        resource->memoryPointer = busHeap;

        retVal = CMB_init(ccbHandle, 0);

        //ccbStatus.status = CMB_Framework_initializeTimer(userParams);

        retVal1= CMB_Framework_initializeTimer(userParams);

        if (CART_STATUS_SUCCESS != retVal)
        {
            CMB_Logger_error("%s Error in CMB initializaton: %d. \n", LOG_STR, retVal);
        }
        else if (CART_STATUS_SUCCESS != retVal1)
        {
            retVal = CART_STATUS_ERROR;
            CMB_Logger_error("%s Error in CMB initializaton: %d. \n", LOG_STR, retVal1);
        }
        else
        {
            uint8_t count = 0;
            uint8_t a =0;
            // Add adaptors and proxys according to the selected framework configuration and overrides to the configuration table entry.
            for (a= 0; a < cfg->numberOfAdaptors; a++)
            {
                CMB_Framework_adaptorConfig* adaptorConfig = &cfg->adaptorList[a];

                CMB_Adaptor_Id adaptorId;

                // The connections to tuning and control application are determined based on configuration
                // table overrides by application.
                uint8_t addAdaptor = 1;

                if (CART_ID_TUNING_APP == adaptorConfig->proxyList[0].dstId)
                {
                    if (0 == params->enableTuningAppConnection)
                    {
                        addAdaptor = 0;
                    }
                }
                else if (CART_ID_CONTROL_APP == adaptorConfig->proxyList[0].dstId)
                {
                    if (0 == params->enableControlAppConnection)
                    {
                        addAdaptor = 0;
                    }
                }

#if 0 // Deprecated. Not needed as application has control of this configuration now.               
                else if (APX_BAF_ID == adaptorConfig->proxyList[0].dstId)
                {
                    CMB_APX_Proxy_config* ioaudioCfg = (CMB_APX_Proxy_config*)adaptorConfig->proxyList[0].configuration;

                    if ('\0' == params->sndPcmDeviceName[0])
                    {
                        // Keep the default value during compile time.
                    }
                    else
                    {
                        // Override compiled configuration with runtime value.            
                        memcpy(ioaudioCfg->deviceName, params->sndPcmDeviceName, SND_PCM_DEVICE_NAME_LEN);
                    }

                    CMB_Logger_debug("%s IO-AUDIO using PCM device default %s %x. \n", LOG_STR, ioaudioCfg->deviceName, ioaudioCfg->deviceName);
                }
#endif

                if (0 != addAdaptor)
                {
                    if (CART_STATUS_SUCCESS != CMB_add_adaptor(ccbHandle,
                                                               (CMB_AdaptorInterface*)adaptorConfig->adaptorObject,
                                                               &adaptorId))
                    {
                        CMB_Logger_error("%s Failed to add adaptor at index %u. \n", LOG_STR, a);

                        ccbStatus.status = CART_STATUS_ERROR;

                        break;
                    }
                    else
                    {
                        ++count;

                        if (0 != adaptorConfig->enableAdaptorExecs)
                        {
                            if (MAX_ADAPTOR_EXEC_LIST_SIZE > CMB_Framework_obj.numAdaptorToExec)
                            {
                                CMB_Framework_obj.adaptorExecList[CMB_Framework_obj.numAdaptorToExec] = adaptorId;

                                CMB_Logger_verbose("%s  add adaptor at index %u to exec list at %u. \n", LOG_STR, a, CMB_Framework_obj.numAdaptorToExec);

                                ++CMB_Framework_obj.numAdaptorToExec;
                            }
                            else
                            {
                                CMB_Logger_error("%s Failed to add adaptor at index %u to exec list at %u. \n", LOG_STR, a, CMB_Framework_obj.numAdaptorToExec);

                                ccbStatus.status = CART_STATUS_QUEUE_FULL;
                                break;
                            }
                        }
                        
                        if (0 != adaptorConfig->enableAdaptorRecv)
                        {
                            if ((MAX_ADAPTOR_EXEC_LIST_SIZE > CMB_Framework_obj.numAdaptorToRecvOn) && 
                                (0 != adaptorConfig->adaptorObject))
                            {
                                CMB_Framework_obj.adaptorRevcList[CMB_Framework_obj.numAdaptorToRecvOn] = adaptorConfig->adaptorObject;

                                CMB_Logger_verbose("%s  add adaptor at index %u to recv list at %u. \n", LOG_STR, a, CMB_Framework_obj.numAdaptorToRecvOn);

                                ++CMB_Framework_obj.numAdaptorToRecvOn;
                            }
                            else
                            {
                                CMB_Logger_error("%s Failed to add adaptor at index %u to recv list at %u. \n", LOG_STR, a, CMB_Framework_obj.numAdaptorToRecvOn);

                                ccbStatus.status = CART_STATUS_QUEUE_FULL;
                                break;
                            }
                        }

                        uint8_t p = 0;

                        for ( p = 0;
                             (p < adaptorConfig->numberOfProxys && CART_STATUS_SUCCESS == ccbStatus.status);
                             p++)
                        {
                            adaptorConfig->proxyList[p].id = adaptorId;

                            ccbStatus = CMB_command(ccbHandle,
                                                    CMB_CMD_ADD_PROXY,
                                                    (void*)&(adaptorConfig->proxyList[p]));

                            if (CART_STATUS_SUCCESS != ccbStatus.status)
                            {
                                break;
                            }
                            else if (adaptorConfig->proxyList[p].dstId == CMB_Framework_obj.creators_id)
                            {
                                CMB_Framework_obj.adaptorIdForCallbacks = adaptorId;

                                CMB_Framework_obj.adaptorObjectForCallbacks = adaptorConfig->adaptorObject;
                            }
                        }

                        // Provide a generic interface to the adaptor, for it to manage the driver it handles. 
                        // This can be used to extend the commands sent to the adaptor, example, 
                        // override build-time configuration. or per adaptor/driver pre-init / post-init hook
                        // functions based on other events in the system, sometime required to support hot-pluggins.
                        // Or pre and post-exec() to measure MIPS.
                        // Requires a new API in adaptor interface and  more functionality: 
                        // void* (*adaptorIoctl)(void* arg);

                        // adaptor-pre-init-hooks();

                        if (CART_STATUS_SUCCESS != ccbStatus.status)
                        {
                            CMB_Logger_error("%s Failed to add proxy %u for adaptor at %u. \n", LOG_STR, p, a);
                            break;
                        }
                        // Once both adaptors and proxies are added, initialize the adaptor
                        else
                        {
                            CMB_Adaptor_config initCfg = {adaptorId, 0};

                            ccbStatus = CMB_command(ccbHandle, CMB_CMD_INITIALIZE_ADAPTOR, (void*)&initCfg);

                            if (CART_STATUS_SUCCESS != ccbStatus.status)
                            {
                                CMB_Logger_error("%s Failed to initialize adaptor (id %x) for adaptor at %u. \n",
                                       LOG_STR, adaptorConfig->proxyList[p].dstId, a);
                                break;
                            }
                            // else adaptor-post-init-hooks();
                        }
                    }
                }
            }

            if (CART_STATUS_SUCCESS == ccbStatus.status)
            {
                CMB_Logger_info("%s initialized use case: %s with %u adaptors. \n",
                                LOG_STR, cfg->name, cfg->numberOfAdaptors);
            }

            retVal = ccbStatus.status;
        }
    }

    return retVal;
}

CART_STATUS CMB_Framework_deinitialize()
{
    CART_Cmd_Ret retVal = CMB_command(busContext.cmb,
                                      CMB_CMD_DEINITIALIZE_ADAPTORS,
                                      &busContext);
    CMB_destroy(busContext.cmb);

    return retVal.status;
}

void CART_Message_set_header(CART_Message* msg, CART_MESSAGE_ID id, CART_MESSAGE_TYPE type, CART_ID src, CART_ID dst, uint32_t size){
    CART_Message_set_id(msg, id);
    CART_Message_set_type(msg, type);
    CART_Message_set_src(msg, src);
    CART_Message_set_dst(msg, dst);
    CART_Message_set_size(msg, size);
}

CMB_STATE CMB_Framework_periodicOperations(CMB_Framework_handle* handle)
{
    CMB_STATE retVal = CMB_STATE_IDLE;

    _CMB_Framework* this_private = (_CMB_Framework*) *handle;

    if ((0 != this_private) && (0 != this_private->created))
    {
        const CMB_Framework_params* const params = &this_private->applicationParams;

        const CMB_Framework_config* const cfg = &params->configuration;

        uint16_t i = 0;

        CMB_Adaptor_execContext adaptorContext = {.id = 0, .context = 0};

        // if (0 != this_private->applicationParams.enablePeriocAdaptorExecutions)
        // CART_STATE Add state machine - ready/run/pause/stop.

        {
            for (i = 0; i < this_private->numAdaptorToExec; i++)
            {
                adaptorContext.id = this_private->adaptorExecList[i];

                CMB_command(busContext.cmb, CMB_CMD_ADAPTOR_EXEC, (void*)&adaptorContext);
            }
        }

        // CMB_STATE_IDLE

        // Lets disable polling if interval is explicitly set to 0.
        if (0 != this_private->applicationParams.periodicWorkInterval)
        {
            // Change the list according to model partitions.
            for (i = 0; i < cfg->cartPoller.numBafToPoll; i++)
            {
                if ((APX_BAF_ID == cfg->cartPoller.bafList[i]) &&                
                    (0 == this_private->applicationParams.pollApxBaf))
                {
                    continue;
                }
                
                // Initialize it to zero for notification request as it takes no payload data.
                uint32_t responseBuffer[(MAX_MSG_SIZE + 3) >> 2] = {0};

                CART_Message ntf = {0, 0, responseBuffer};

                CART_Message_set_header(&ntf,
                                        CART_MESSAGE_ID_NOTIFICATION_POLL,
                                        CART_MESSAGE_TYPE_REQ,
                                        CART_ID_HEAD_UNIT,
                                        cfg->cartPoller.bafList[i],
                                        0);

                CMB_command(busContext.cmb, CMB_CMD_SEND_MSG, &ntf);
            }

            // Sleep until a timer is implemented.
            usleep(this_private->applicationParams.periodicWorkInterval);
        }
    }

    return retVal;
}

// Later, do not set states directly, pass events that then calculates the next state.
void CMB_Framework_setState(CMB_Framework_handle* handle, CMB_STATE newState)
{
    if (0 != handle)
    {
        _CMB_Framework* this_private = (_CMB_Framework*) *handle;

        this_private->state = newState;
    }
}

CMB_STATE CMB_Framework_getState(CMB_Framework_handle* handle)
{
    CMB_STATE state = CMB_STATE_TERMINATED;

    if (0 != handle)
    {
        _CMB_Framework* this_private = (_CMB_Framework*) *handle;

        state = this_private->state; // Or CMB_STATE_TERMINATING after event based setup.
    }

    return state;
}

// Implemented CMB_Framework_isTerminated in the state machine becomes complex.


CART_Cmd_Ret CMB_Framework_processAllMessages(CMB_Framework_handle* handle)
{
    CART_Cmd_Ret retVal = {CART_STATUS_SUCCESS};

    _CMB_Framework* this_private = (_CMB_Framework*) *handle;

    if (0 == handle)
    {
        retVal.status = CART_STATUS_INVALID;
    }
    else if (0 == this_private->created)
    {
        retVal.status = CART_STATUS_DISCONNECTED;
    }
    else
    {
        unsigned char buffer[BUFFER_SIZE] = {};

        // uint8_t acsAppDisconnected = 0;

        CMB_Framework_params* params = (CMB_Framework_params*) &(this_private->applicationParams);

        CMB_STATE currentState = CMB_Framework_getState(handle);

        while ((CMB_STATE_TERMINATING != currentState) &&
               (CMB_STATE_TERMINATED != currentState))
        {
            for (uint8_t i = 0; i < this_private->numAdaptorToRecvOn; i++)
            {
                ssize_t recv_length = 0;

                // Get message from AATMA, and send it to the CART component.
                retVal = this_private->adaptorRevcList[i]->receiveBufferMessage(buffer, sizeof(buffer), &recv_length);

                if (CART_STATUS_TIMEOUT == retVal.status)
                {
                    // No operation here.                    
                }
                else if ((recv_length > 0) && (CART_STATUS_SUCCESS == retVal.status))
                {
                    this_private->adaptorRevcList[i]->sendBufferMessage(busContext.cmb, buffer, recv_length);
                }
                else if (CART_STATUS_DISCONNECTED == retVal.status)
                {
                    CMB_Logger_info("\n Adaptor %x disconnected.\n", this_private->adaptorRevcList[i]);

                    if (this_private->adaptorRevcList[i] == this_private->adaptorObjectForCallbacks)
                    {
                        CMB_Framework_setState(handle, CMB_STATE_TERMINATING);

                        currentState = CMB_Framework_getState(handle);

                        CMB_Logger_info("\n ACS Adaptor %x triggered shutdown.\n", this_private->adaptorRevcList[i]);
                    }
                }
                else if (CART_STATUS_ERROR == retVal.status)
                {
                    CMB_Logger_error("\n Adaptor %x Error: Possibly, buffer too small. \n",
                        this_private->adaptorRevcList[i]);
                }
                else // if (CART_STATUS_NO_ACTION == retVal.status)
                {
                    // Increment counter for diagnostics if interested.
                }
            }

            if ((CMB_STATE_TERMINATING != currentState) &&
               (CMB_STATE_TERMINATED != currentState))
            {
                currentState = CMB_Framework_periodicOperations(handle);
            }
        }
    }

    return retVal;
}


CART_Cmd_Ret CMB_Framework_exec(CMB_Framework_handle* handle)
{
    CART_Cmd_Ret retVal = {CART_STATUS_SUCCESS};

    retVal = CMB_Framework_processAllMessages(handle);

    return retVal;
}

CART_STATUS CMB_Framework_create(CMB_Framework_context* ctx, CMB_Framework_handle* handle)
{
    CART_STATUS status = CART_STATUS_SUCCESS;

    if ((0 == ctx) || (0 == handle))
    {
        CMB_Logger_error("%s Invalid pointer ctx %x handle %x \n", LOG_STR, ctx, handle);

        status = CART_STATUS_INVALID;
    }
    else if (0 != CMB_Framework_obj.created)
    {
        CMB_Logger_error("%s framework was already created. Destroy before recreating"
                " the framework with new configuration.\n", LOG_STR);

        *handle = 0;

        status = CART_STATUS_ERROR;
    }
    else
    {
        *handle = 0;

        // Consider overriding bus ID from user / external configuration, for distributed bus case.
        // CMB_obj.id = ctx->id;

        CMB_Framework_obj.creators_id = ctx->creater_id;

        if (CART_STATUS_SUCCESS != (status = CMB_Framework_initialize(&ctx->params)))
        {
            CMB_Logger_error("%s Initialize failed with return value %d. \n", LOG_STR, status);

            CMB_Framework_obj.creators_id = CART_ID_INVALID;
        }
        else
        {
            CMB_Framework_obj.created = 1; // Deprecate

            *handle = (CMB_Framework_handle)&CMB_Framework_obj;

            CMB_Framework_setState(handle, CMB_STATE_RUNNING_ON);

            CMB_Logger_info("%s created. \n", LOG_STR);
        }
    }

    return status;
}

CART_STATUS CMB_Framework_destroy(CMB_Framework_handle* handle)
{
    _CMB_Framework* this_private = (_CMB_Framework*) *handle;

    CART_STATUS status = CART_STATUS_SUCCESS;

    if (CART_STATUS_SUCCESS != (status = CMB_Framework_deinitialize()))
    {
        CMB_Logger_error("%s De-initialize failed %d. \n", LOG_STR, status);
    }
    else
    {
        this_private->created = 0;
        this_private->numAdaptorToExec = 0;

        CMB_Framework_setState(handle, CMB_STATE_TERMINATED);

        CMB_Logger_info("%s Deinitialized. \n", LOG_STR);
    }

    return status;
}


CART_Cmd_Ret CMB_Framework_register_recv(CMB_Framework_handle* handle, CMB_Callback_recv recv)
{
    CART_Cmd_Ret retVal = {CART_STATUS_SUCCESS};

    _CMB_Framework* this_private = (_CMB_Framework*) *handle;

    if ((0 == recv) || (0 == this_private))
    {
        retVal.status = CART_STATUS_INVALID;
    }
    else
    {
        CMB_Adaptor_recvCallbackConfig cfg = {this_private->adaptorIdForCallbacks, recv};

        retVal = CMB_command(busContext.cmb, CMB_CMB_REGISTER_RECV_CALLBACK, (void*)&cfg);
    }

    return retVal;
}


CART_Cmd_Ret CMB_Framework_register_send(CMB_Framework_handle* handle, CMB_Callback_send send)
{
    CART_Cmd_Ret retVal = {CART_STATUS_SUCCESS};

    _CMB_Framework* this_private = (_CMB_Framework*) *handle;

    if ((0 == send) || (0 == this_private))
    {
        retVal.status = CART_STATUS_INVALID;
    }
    else
    {
        CMB_Adaptor_sendCallbackConfig cfg = {this_private->adaptorIdForCallbacks, send};

        retVal = CMB_command(busContext.cmb, CMB_CMB_REGISTER_SEND_CALLBACK, (void*)&cfg);
    }

    return retVal;
}
