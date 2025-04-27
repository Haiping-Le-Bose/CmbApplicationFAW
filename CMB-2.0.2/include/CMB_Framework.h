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
 * @file CMB_Framework.h
 *
 * @ingroup CMB_Framework
 *
 * @brief Declaration of CART Message Bus (CMB) Framework (CMBF)
 *
 ****************************************************/

#if !defined(BC_CMB_FRAMEWORK__INCLUDED_)
#define BC_CMB_FRAMEWORK__INCLUDED_


#ifdef __cplusplus
extern "C" {
#endif

#include "CART_Cmd_Ret.h"
#include "CART.h"
#include "CMB_TYPES.h"
#include "CMB_Framework_config.h"

/**
 * @ingroup CMB_Framework
 *
 * @brief 1. CART Message Bus Framework (CMBF)
 *
 * @version 1.5.2
 */

#define CMBF_VERSION CMB_VERSION  1.5.2
#define SND_PCM_DEVICE_NAME_LEN   256

/**
 * @ingroup CMB_Framework
 *
 * @brief A handle used to communicate with an instance of CMBF. 
 */
typedef unsigned long long CMB_Framework_handle;

/**
 * @ingroup CMB_Framework
 *
 * @brief This structure has attributes to select (and potentially override )
 * configuration of CMB Framework at runtime.
 */
typedef struct CMB_Framework_params
{
   /**
    * @ingroup CMB_Framework
    *
    * @brief Index into the table to select the framework configuration. 0 for A2B, 1 for NXP.
    */
    CMB_Framework_config configuration;

   /**
    * @ingroup CMB_Framework
    *
    * @brief  Enable connection to control application, if included in compile time configuraion.
    */    
    uint8_t enableControlAppConnection;

   /**
    * @ingroup CMB_Framework
    *
    * @brief  Enable connection to tuning application, if included in compile time configuraion.
    */ 
    uint8_t enableTuningAppConnection;

   /**
    * @ingroup CMB_Framework
    *
    * @brief  Time Interval, in micro-seconds, for periodic task, including polling for notification.
    */ 
    uint32_t periodicWorkInterval;

   /**
    * @ingroup CMB_Framework
    *
    * @brief  IP connection type. 1 for TCP stream socket, 2 for UDP Datagram. 
    * This is obsoleted with CMB 1.4.3. And will be removed in future releases.
    */ 
    uint8_t socketType;

   /**
    * @ingroup CMB_Framework
    *
    * @brief  Set ammount of logging from CMBF. Set using enum CMB_LOG_LEVEL. 
    */
    uint8_t logLevel;

   /**
    * @ingroup CMB_Framework
    *
    * @brief  AMS graph ID cannot be controlled using this at this time. Reserved for future implementation.
    */ 
    uint32_t amsGraphId;

   /**
    * @ingroup CMB_Framework
    *
    * @brief  Enable polling of APX module for CART message notification response. Default to 0.  
    */ 
    uint8_t pollApxBaf;

   /**
    * @ingroup CMB_Framework
    *
    * @brief  Reserved for future use.
    */ 
    uint32_t frameCount;

   /**
    * @ingroup CMB_Framework
    *
    * @brief  Sound PCM device name. memset to 0 to force the library to use the default value  
    *  of device name the library is compiled with.
    *  This is obsoleted with CMB 1.4.3. And will be removed in future releases.
    */ 
    char sndPcmDeviceName[SND_PCM_DEVICE_NAME_LEN];
} CMB_Framework_params;


/**
 * @ingroup CMB_Framework
 *
 * @brief This structure is used by user of the API to provide context and configuration to CMBF.
 */
typedef struct CMB_Framework_context
{
   /**
    * @ingroup CMB_Framework
    *
    * @brief CART ID of the user application that attaches to the CMB Framework.
    */
    CART_ID creater_id;

   /**
    * @ingroup CMB_Framework
    *
    * @brief Parameter with which the CMB Framework is to be configured with during CMB_Framework_create().
    */
    CMB_Framework_params params;

} CMB_Framework_context;

/**
 * @ingroup CMB_Framework
 *
 * @brief This API instantiates a CMB and a set of adaptors needed to communicate 
 * with CART components. 
 *
 * @param cfg Configuration of the CMBF. It takes the CART ID of the application 
 * that instantiates the CMBF.
 *
 * param handle Pointer to a handle for the framework. It will be set to valid value
 * by this API if the return value is CART_STATUS_SUCCESS.
 *
 *  @return This API returns CART_STATUS_SUCCESS if framework was created successfully,
 *   and the handle is set to a valid CMB Framework object.
 */
CART_STATUS CMB_Framework_create(CMB_Framework_context* cfg, CMB_Framework_handle* handle);

/**
 * @ingroup CMB_Framework
 *
 * @brief This API destroys the CMB Framework object.
 *
 * @param handle Handle to the CMB Framework object
 */
CART_STATUS CMB_Framework_destroy(CMB_Framework_handle* handle);

/**
 * @ingroup CMB_Framework
 *
 * @brief This is a blocking call for the duration of the application. It calls the 
 * callbacks registered by the creater of the framework. And also manages callbacks 
 * and connection of other adaptors that are built into the CMB Framework.  
 * This function returns when when the callback registered using CMB_Framework_register_recv()  
 * return CART_STATUS_DISCONNEDTED.   
 * 
 * @param handle Handle to the CMB Framework object
 *
 * @return Returns 0 in status field if no error are encountered.
 */
CART_Cmd_Ret CMB_Framework_exec(CMB_Framework_handle* handle);

/**
 * @ingroup CMB_Framework
 *
 * @brief Register the application's function that will receive (BDP) command
 * messages that are to be sent to CART components (BAF, BTF for example).   
 * The CMB_Framework_exec calls this function periodically to check for 
 * command request.
 * This function can block, but must return within few milliseconds, so that
 * CMB_Framework_exec can poll callbacks for other adaptors built-in into the 
 * CMB framework.
 *
 * @param handle Handle to the CMB Framework object. 
 *
 * @param recv The callback to be registered with CMBF that will be called 
 * periodically by CMB_Framework_exec() to receive command messages.
 * When this callback returns CART_STATUS_DISCONNECTED, command processing stops and
 * the CMB_Framework_exec() returns control to the application. And the application
 * should call CMB_Framework_destroy() to shutdown the CMB library gracefully.
 *
 * @return Returns 0 in status field of CART_Cmd_Ret if no error are 
 * encountered, CART_STATUS with appropriate error code otherwise.
 */ 
CART_Cmd_Ret CMB_Framework_register_recv(CMB_Framework_handle* handle, CMB_Callback_recv recv);

/**
 * @ingroup CMB_Framework
 *
 * @brief Register the application's function that will send BDP command 
 * messages response notification from BAF/BTF back to the application.
 * The CMBF will call this callback when a response / notification message 
 * is available.
 * @param handle Handle to the CMB Framework object. 
 *
 * @param recv The callback to be registered with CMBF that will be called 
 * periodically by CMB_Framework_exec(). This callback should provide 
 *
 * @return Returns 0 in status field of CART_Cmd_Ret if no error are 
 * encountered, CART_STATUS with appropriate error code otherwise.
 */ 
CART_Cmd_Ret CMB_Framework_register_send(CMB_Framework_handle* handle, CMB_Callback_send send);

#ifdef __cplusplus
}
#endif


#endif /*!defined(BC_CMB_FRAMEWORK__INCLUDED_)*/
