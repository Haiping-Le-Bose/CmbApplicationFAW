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
 * @file CMB_AdaptorInterface.h
 *
 * @brief Header file for adaptor interface definition.
 *
 ****************************************************/

#if !defined(CMB_ADAPTOR_INTERFACE__INCLUDED_)
#define CMB_ADAPTOR_INTERFACE__INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include "CART_ID.h"
#include "CART_STATUS.h"
#include "CART_Message.h"
#include "CART_Cmd_Ret.h"
#include "CMB_TYPES.h"

#define MAX_MSG_SIZE                    (1024 + 64)
#define MAX_NUM_OF_DESTINATIONS         CART_ID_ALL
#define MAX_NUM_OF_ADAPTORS             16

typedef struct CMB_AdaptorInterface
{
    /**
     * @ingroup CMB
     *
     * @brief This API is used to initialize the adaptor.
     *
     * @param ccb Pointer to the CMB object
     *
     * @param configuration Configuration, if any, required to initialize the
     * adaptor.
     *
     * @return Returns CART_STATUS_SUCCESS if operation passes, error value
     * otherwise.
     */
    CART_STATUS (*initialize)(CMB* ccb, void* configuration);


    CART_Cmd_Ret (*addProxy)(CMB* cmb, void*);

    /**
     * @ingroup CMB
     *
     * @brief This API is used to send a CART message to the CART component
     * identified in the CART_Message header.
     *
     * @param ccb Pointer to the CMB object
     *
     * @param msg This is a CART message to be sent,
     *
     * @return Returns the status of send operation.
     *
     */
    CART_Cmd_Ret (*sendCartMessage)(CMB* ccb, CART_Message* msg);

    /**
     * @ingroup CMB
     *
     * @brief This API is used to deinitialize the adaptor.
     *
     * @param ccb Pointer to the CMB object
     *
     * @param reserved Parameter is reserved for future usage.
     *
     * @return Returns CART_STATUS_SUCCESS if operation passes, error value
     * otherwise.
     */
    CART_STATUS (*deinitialize)(CMB* ccb, void* reserved);

    /**
     * @ingroup CMB
     *
     * @brief This API is used to send a message that is
     * not in CART message format. The API creates a CART message out of the
     * payload before sending the message.
     * 
     * @param ccb Pointer to the CMB object
     *
     * @param payload This is the point to payload data in a format this is
     * pre-determined to be used with the adaptor.
     * 
     * @param reqPayloadSize This is size, in bytes, of the payload data to be
     * sent to the bus.
     * 
     * @return Returns the status of send operation.
     *
     */
    CART_Cmd_Ret (*sendBufferMessage)(CMB* ccb, unsigned char *payload, const uint32_t reqPayloadSize);

    /**
     * @ingroup CMB
     *
     * @brief This API is used to receive a message from a different application
     * from which the CMB is linked. This API must implement IPC mechanism to
     * receive message it. Example, Socket if the application is on another PC,
     * or shared memory, if the application is on same processor.
     *
     * @param buffer Pointer to buffer into which the message will be received.
     *
     * @param len Length of the buffer provided to receive data.
     *
     * @return recv_length Number of bytes actually received and copied into
     * buffer.
     *
     * @return Returns the status of receive operation.
     *
     */
    CART_Cmd_Ret (*receiveBufferMessage)(uint8_t* buffer, const uint32_t len, ssize_t* recv_length);

    CART_Cmd_Ret (*registerRecvCallback)(CMB_Callback_recv recv);

    CART_Cmd_Ret (*registerSendCallback)(CMB_Callback_send func);

    void (*exec)(void* arg);

} CMB_AdaptorInterface;

#ifdef __cplusplus
}
#endif

#endif /*!defined(CMB_ADAPTOR_INTERFACE__INCLUDED_)*/
