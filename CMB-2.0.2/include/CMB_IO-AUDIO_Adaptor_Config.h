
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
 * @file CMB_IO-AUDIO_Adaptor_Config.h
 *
 * @brief Header file for tuning/testing adaptor configuration.
 *
 ****************************************************/

#if !defined(CMB_IO_AUDIO_ADAPTOR_CONFIG__INCLUDED_)
#define CMB_IO_AUDIO_ADAPTOR_CONFIG__INCLUDED_

#include "CART_ID.h"

#ifdef __cplusplus
extern "C" {
#endif

#define IO_AUDIO_APX_ID_MAX_SIZE            256
#define APX_BOSE_ID_ENT                     "Bose_processing"

#ifndef STUB_DRIVER

// Ideally, include these. But they pull in conflicts between alsa and snd
// #include <snd/asound.h>
// #include "apx.h"

typedef enum
{
    E_DATA_CART_MESSAGE
} data_id_t;

// Maximum size of CART message supported by APX
#define APX_MAX_MSG_SIZE                (100)

#endif  // !STUB_DRIVER


#define DEVICE_NAME_SIZE                256

typedef struct 
{
    CART_ID dstId;

    // int32_t apxId;

    char apxId[IO_AUDIO_APX_ID_MAX_SIZE];

    char deviceName[DEVICE_NAME_SIZE];
} CMB_APX_Proxy_config;


#ifdef __cplusplus
}
#endif

#endif /*!defined(CMB_IO_AUDIO_ADAPTOR_CONFIG__INCLUDED_)*/
