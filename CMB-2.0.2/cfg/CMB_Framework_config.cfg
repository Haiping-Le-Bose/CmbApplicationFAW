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
 * @file CMB_Framework_config.c
 *
 * @brief CMB Framework configuration.
 *
 ****************************************************/

#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>

#include "CART_ID.h"
#include "BTF_Resource.h"
#include "CMB_TYPES.h"

#ifdef ENABLE_SOCKET_THREADS
#include "CMB_OSAL.h"
#endif

#include "CMB_Adaptor_List.h"
#include "CMB_Socket_Types.h"
#include "CMB_Framework_config.h"

// Include file for specific Adaptor's configuration structures.
#include "CMB_CSD2_Adaptor_Config.h"
#include "CMB_IO-AUDIO_Adaptor_Config.h"
//#include "CMB_BAF_Adaptor_Config.h"
#include "CMB_BRF_Adaptor_Config.h"
#include "CMB_BTF_Adaptor_Config.h"
#include "CMB_BCF_Adaptor_Config.h"
#include "CMB_AMS_Adaptor_Config.h"

namespace BAFS
{
#if ENABLE_BAF_ADAPTOR
#include "CMB_BAF_Adaptor_Config.h"
#endif
}
using namespace BAFS;

#if ENABLE_ASDS_ADAPTOR
#include "CMB_ASDS_Adaptor_Config.h"
#endif

#define CART_ID_RNC_TUNING_APP  0x95
#define CART_ID_RNC_CONTROL_APP 0x94

#ifndef IP_OF_TARGET_BOARD
#define IP_OF_TARGET_BOARD      "192.168.1.1"
#endif

#define ENT_CONTROL_PORT        5503
#define RNC_CONTROL_PORT        5513
#define ENT_TUNING_PORT         5501
#define RNC_TUNING_PORT         5511

// Define the number of adaptors for use case index 0 (A2B) and 1 (NXP) for target.
#ifndef STUB_DRIVER
// CSD2, IOAUDIO and ACS = 3 adaptor + AATMA and Ducttape = 5. AMS adaptor = 6
#define NUMBER_OF_ADAPTORS   (ENABLE_BTF_ADAPTOR + ENABLE_BCF_ADAPTOR + ENABLE_BRF_ADAPTOR + 6)

#else
// CSD2 Stub, IOAUDIO Stub and ACS = 3 adaptor
#define NUMBER_OF_ADAPTORS  (ENABLE_BTF_ADAPTOR + ENABLE_BCF_ADAPTOR + ENABLE_BRF_ADAPTOR + 3)
#endif  // STUB_DRIVER

#define NUMBER_OF_ASM_ADAPTER 7
#define NUMBER_OF_ENT_ASM_ADAPTER 9

// Use case index 3.
// BAF, BCF, BTF, BRF and ACS adaptors for Linux and Windows build of CMB.
#define HOST_SIMULATION_NUMBER_OF_ADAPTORS (1 + ENABLE_BTF_ADAPTOR + ENABLE_BCF_ADAPTOR + ENABLE_BRF_ADAPTOR + ENABLE_BAF_ADAPTOR)
#define PRODUCTION_DEPLOYMENT_NUMBER_OF_ADAPTORS 6

#define NUM_BAF_RESOURCES 10

// Or expand each Adaptors configuration internals in this file.
// Example BRF's configuration is expanded in this C file.
#define OPTC_STEERING_MASK (0x30UL) /* from database_defs.h*/
#define OPTC_STEERING_LEFT (0x10UL) /* from database_defs.h*/
#define OPTC_STEERING_RIGHT (0x20UL) /* from database_defs.h*/

#define RNDB_START_ADDRESS 0x00204000
#define FFDB_START_ADDRESS 0x00064000

#define RNC_RNDB_START_ADDRESS 0x00204000
#define RNC_FFDB_START_ADDRESS 0x00064000

#ifndef RNDB_PATH
#define RNDB_PATH "/mnt/data/RNDB.bin"
#define FFDB_PATH "/mnt/data/FFDB.bin"
#endif

#ifndef BTF_DLL_PATH
#define BTF_DLL_PATH "libBtf_dll.so"
#endif
#ifndef BRF_DLL_PATH
#define BRF_DLL_PATH "libBrf_dll.so"
#endif

#ifndef BCF_DLL_PATH
#define BCF_DLL_PATH "libBcf_dll.so"
#endif

#if 0
#ifndef RNC_BTF_DLL_PATH
#define RNC_BTF_DLL_PATH "libBtf_asm_dll.so"
#endif

#ifndef RNC_BRF_DLL_PATH
#define RNC_BRF_DLL_PATH "libBrf_asm_dll.so"
#endif

#ifndef RNC_BCF_DLL_PATH
#define RNC_BCF_DLL_PATH "libBcf_asm_dll.so"
#endif

#ifndef RNC_RNDB_PATH
#define RNC_RNDB_PATH "/mnt/data/RNDB_asm.bin"
#define RNC_FFDB_PATH "/mnt/data/FFDB_asm.bin"
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef ENABLE_SOCKET_THREADS
static const int32_t defaultPThreadPriority = 150;

// 8192 is too small since the buffer request and response is 2 * 1024.
static const size_t defaultPThreadStackSize = 32768;

CMB_OSAL_Thread_config pthreadParam =
{
    defaultPThreadPriority,
    defaultPThreadStackSize,
};
#endif
const CMB_Framework_periodicOperationsConfig poller =
{
    .numBafToPoll = 1, 

    // List of BAFs to send notification poll requests.
    .bafList = 
    {
        CART_ID_BAF1,
    },
};

#if BOSE_ENTERTAINMENT_AUDIO
#if ENABLE_BRF_ADAPTOR
#include "BRF_Callback_Register.h"

BRF_Callback_Register beaBrfCb =
{
    .post = BOSE_BRF_Callback_post,
    .clock = 0,
    .notify = BOSE_BRF_Callback_notify,
    .read = ENT_BRF_Callback_read,
    .write = NULL,
    .send = BOSE_BRF_Callback_send,
    .print = BRF_printf,
};

const CMB_BRF_RNDB_Proxy_Config entBrfParams = 
{
    2,
    { RNDB_START_ADDRESS, FFDB_START_ADDRESS}, 
    OPTC_STEERING_MASK,
    { RNDB_PATH, FFDB_PATH},
    CART_ID_BRF,
    NUM_BAF_RESOURCES, // libBRF Should have a BRF_RESOURCE_NUM_BAF.
    {CART_ID_BAF1,   //1_1
     0,              //1_2
     CART_ID_BAF3,   //1_3
     CART_ID_BAF5,   //1_4
     CART_ID_BAF2,   //1_5
     0,              //1_6
     CART_ID_BAF4,   //1_7
     },
     &beaBrfCb,
     BRF_DLL_PATH,
     // thread
};
#endif
#endif

#if 0

#endif
#ifndef APX_BAF_ID
#define APX_BAF_ID CART_ID_BAF1
#endif
#define APX_DEFAULT_PCM_DEVICE_NAME "hw:/dev/snd/pcmPreferredp"
CMB_APX_Proxy_config ioaudioParams =
{
    APX_BAF_ID,
    APX_BOSE_ID_ENT,
    APX_DEFAULT_PCM_DEVICE_NAME,
};

// NXP use case with developers ACDB. Not present in official ACDB released for IP5.
// const CMB_CSD2_Graph_Config nxpSpeakerConfig = 
// {
//     .usecaseId = 0,
// 	.listSize = 5,
//     .valueList = {
//         {STREAMRX, PCM_DEEP_BUFFER},
//         {INSTANCE, INSTANCE_3},
//         {VMID, PVM},
//         {DEVICEPP_RX, DEVICEPP_RX_AUDIO_MBDRC},
//         {DEVICERX, MEDIA_SPKR},
//     },
// };

// A2B use case for IP5.
// const CMB_CSD2_Graph_Config a2bSpeakerConfig = 
// {
//     .usecaseId = 1,
// 	.listSize = 5,
// 	.valueList = {
//         {STREAMRX, PCM_DEEP_BUFFER},
//         {INSTANCE, INSTANCE_3},
//         {VMID, PVM},
//         {DEVICEPP_RX, DEVICEPP_RX_AUDIO_MBDRC},
//         {DEVICERX, MEDIA_SPKR},
//     },
// };

const CMB_CSD2_Graph_Config a2bSpeakerConfig2 = 
{
    .usecaseId = 1,
	.listSize = 5,
	.valueList = {
        {STREAMRX, PCM_DEEP_BUFFER},
        {INSTANCE, INSTANCE_10},
        {VMID, PVM},
        {DEVICEPP_RX, DEVICEPP_RX_AUDIO_MBDRC},
        {DEVICERX, NAVI_SPKR},
    },
};

// A2B Mic case. IP5 ACDB has Mic, but may not be working in ACDB setup.
const CMB_CSD2_Graph_Config a2bMicConfig = 
{
    .usecaseId = 1,
	.listSize = 4,
    .valueList = {
        {STREAMTX, PCM_RECORD},
        {VMID,PVM},
        {DEVICEPP_TX, DEVICEPP_TX_AUDIO_FLUENCE_SMECNS},
        {DEVICETX, A2B2_MIC},
    },
};

// IP5 ACDB Build 2.
// const CMB_CSD2_Proxy_Config csdA2bBose1ProxyCfg =
// {
//     0xC00FF021, 
//     0x1000b801,
//     CART_ID_BAF1,
//     a2bSpeakerConfig,
//     0
// };

const CMB_CSD2_Proxy_Config csdA2bBose2ProxyCfg =
{
    0xC00FF022,
    0x1000b801,
    CART_ID_BAF2,
    a2bSpeakerConfig2,
    0
};

// const CMB_CSD2_Proxy_Config csdA2bBose3ProxyCfg =
// {
//     0xC00FF023,
//     0x1000b801,
//     CART_ID_BAF3,
//     a2bSpeakerConfig,
//     0
// };

// NXP use case with developers ACDB. Not present in official ACDB released for IP5.
// const CMB_CSD2_Proxy_Config csdNxpBose1ProxyCfg =
// {
//     0xC00FF021,
//     0x1000b801, 
//     CART_ID_BAF1,
//     nxpSpeakerConfig,
//     0,
// };

// const CMB_CSD2_Proxy_Config csdNxpBose2ProxyCfg =
// {
//     0xC00FF022,
//     0x1000b801, 
//     CART_ID_BAF9,
//     nxpSpeakerConfig,
//     7
// };

// const CMB_CSD2_Proxy_Config csdNxpBose3ProxyCfg =
// {
//     0xC00FF023,
//     0x1000b801,  
//     CART_ID_BAF3,
//     nxpSpeakerConfig,
//     0
// };

// Todo Consider taking it out. Do not need for RNC? what are 20 chan in on TDM to gDSP1?
const CMB_CSD2_Proxy_Config csdBose3ProxyCfg =
{
    0xC00FF023, // 0xC00FF025
    0x1000b801, 
    CART_ID_BAF3,
    a2bMicConfig,
    0
};

// Provide configuration for connecting to tuning application (Ducttape for example).
Adaptor_Connection_Proxy_Config entTuningConfig =
{
    CART_ID_TUNING_APP,
    CART_ID_BTF1,
    {        
        {
            "0",            // IP of the PC on which the tuning application runs.
            0,              // Port on PC at which tuning application accepts messages.
            IP_OF_TARGET_BOARD,  // IP of target board.
            ENT_TUNING_PORT,           // Port number of application on  target board.
            1,               // Maximum number of connections between the two entities.
            0,
        },
        SOCK_TYPE_TCP_SOCK_STREAM, // Can override this runtime.
    #ifdef ENABLE_SOCKET_THREADS    
        &pthreadParam
    #else
        NULL,
    #endif
    }
};

// Provide configuration for connecting to control application (AATMA for example).
Adaptor_Connection_Proxy_Config entControlConfig =
{
    CART_ID_CONTROL_APP,
    CART_ID_BTF1,
    {

        {
            "0",            // IP of the PC on which the tuning application runs.
            0,              // Port on PC at which tuning application accepts messages.
            IP_OF_TARGET_BOARD,  // IP of target board.
            ENT_CONTROL_PORT,           // Port number of application on  target board.
            1,               // Maximum number of connections between the two entities.
            0
        },
        SOCK_TYPE_TCP_SOCK_STREAM, // Can override this runtime.
    #ifdef ENABLE_SOCKET_THREADS
        &pthreadParam
    #else
        NULL,
    #endif
    }
};

// Provide configuration for connecting to control application (AATMA for example).
Adaptor_Connection_Proxy_Config rncControlConfig =
{   CART_ID_RNC_CONTROL_APP,
    CART_ID_BTF2,
    {
        {
            "0",            // IP of the PC on which the tuning application runs.
            0,              // Port on PC at which tuning application accepts messages.
            IP_OF_TARGET_BOARD,  // IP of target board.
            RNC_CONTROL_PORT,           // Port number of application on  target board.
            1,               // Maximum number of connections between the two entities.
            0
        },
        SOCK_TYPE_TCP_SOCK_STREAM, // Can override this runtime.
    #ifdef ENABLE_SOCKET_THREADS
        &pthreadParam
    #else
        NULL,
    #endif
    }
};

// Provide configuration for connecting to tuning application (Ducttape for example).
Adaptor_Connection_Proxy_Config rncTuningConfig =
{   CART_ID_RNC_TUNING_APP,
    CART_ID_BTF2,
    {
        {
            "0",            // IP of the PC on which the tuning application runs.
            0,              // Port on PC at which tuning application accepts messages.
            IP_OF_TARGET_BOARD,  // IP of target board.
            RNC_TUNING_PORT,           // Port number of application on  target board.
            1               // Maximum number of connections between the two entities.
        },
        SOCK_TYPE_TCP_SOCK_STREAM, // Can override this runtime.
    #ifdef ENABLE_SOCKET_THREADS
        &pthreadParam
    #else
        NULL,
    #endif
    }
};
// Bose Entertainment Audio (BEA).
#if BOSE_ENTERTAINMENT_AUDIO
#include "BTF_Callback_Register.h"

BTF_Callback_Register beaBtfCb =
{
    .post = BEA_BTF_Callback_post,
    .clock = 0,
    .notify = BEA_BTF_Callback_notify,
    .send = BEA_BTF_Callback_send,
    .print = BTF_printf
};

//This BAF order should match with model partition say 1_1, 1_2 and so on
const CMB_BTF_Proxy_Config beaBtfParams =
{
    CART_ID_BTF1,
    CART_ID_BRF,
    CART_ID_CONTROL_APP,
    NUM_BAF_RESOURCES,
    {CART_ID_BAF1,   //1_1
     0,              //1_2
     CART_ID_BAF3,   //1_3
     CART_ID_BAF5,   //1_4
     CART_ID_BAF2,   //1_5
     0,              //1_6
     CART_ID_BAF4,   //1_7
     },
     // Only used if DYNAMIC_LIBS is selected at build time.
     &beaBtfCb,
     "libBtf_dll.so",
    // &pthreadParam
};
#endif  // BOSE_ENTERTAINMENT_AUDIO

#if ENABLE_BTF_ADAPTOR
CMB_Framework_adaptorConfig btfAdaptor =
        {
            (CMB_AdaptorInterface*)BTF_Adaptor_getInstance(),
            BTF_PROXY_CNT,
            // CMB_Adaptor_proxyConfig[]
            {

#if BOSE_ENTERTAINMENT_AUDIO
                {0, beaBtfParams.dstId, 0, (void*)&beaBtfParams},
#endif

#if BOSE_RNC
                {0, asmBtfParams.dstId, 0, (void*)&asmBtfParams},
#endif

            },
            1,
            0
        };
#endif

#if ENABLE_BCF_ADAPTOR
BCF_Callback_Register beaBcfCb =
{
    .post = BEA_BCF_Callback_post,
    .clock = 0,
    .notify = BEA_BCF_Callback_notify,
    .send = BEA_BCF_Callback_send,
    .print = BCF_printf
};

//This BAF order should match with model partition say 1_1, 1_2 and so on
const CMB_BCF_Proxy_Config entBcfParams =
{
    CART_ID_BCF1,
    CART_ID_BRF,
    CART_ID_CONTROL_APP,
    NUM_BAF_RESOURCES,
    {CART_ID_BAF1,   //1_1
    0,              //1_2
    CART_ID_BAF3,   //1_3
    CART_ID_BAF5,   //1_4
    CART_ID_BAF2,   //1_5
    0,              //1_6
    CART_ID_BAF4,   //1_7
    },
    // &pthreadParam
     &beaBcfCb,
     BCF_DLL_PATH,
};

CMB_Framework_adaptorConfig bcfAdaptor =
        // CMB_Framework_adaptorConfig[]
        {
            (CMB_AdaptorInterface*)BCF_Adaptor_getInstance(),
            BCF_PROXY_CNT,
            // CMB_Adaptor_proxyConfig[]
            {
#if BOSE_ENTERTAINMENT_AUDIO
                {0, entBcfParams.dstId, 0, (void*)&entBcfParams},
#endif

#if BOSE_RNC
                {0, asmBcfParams.dstId, 0, (void*)&asmBcfParams},
#endif
            },
            1,
            0
        };
#endif

#if ENABLE_BRF_ADAPTOR
CMB_Framework_adaptorConfig  brfAdaptor =
        {
            (CMB_AdaptorInterface*)BRF_Adaptor_getInstance(),
            BRF_PROXY_CNT,
            // CMB_Adaptor_proxyConfig[]
            {
#if BOSE_ENTERTAINMENT_AUDIO                
                {0, entBrfParams.dstId, 0, (void*)&entBrfParams},
#endif

#if BOSE_RNC
                {0, asmBrfParams.dstId, 0, (void*)&asmBrfParams},
#endif
            },
            1,
            0
        };
#endif

#if ENABLE_BAF_ADAPTOR

const CMB_BAF_Proxy_Config bafBoseApxParams =
{
    APX_BAF_ID,
    0,
    bafBoseApxHeap,
    ENT_BAF_HEAP_S1ZE,
    &bafCb,
    BAF1_DLL_PATH,
};

const CMB_BAF_Proxy_Config bafBose1Params =
{
    CART_ID_BAF1,
    0,
    bafBose1Heap,
    ENT_BAF_HEAP_S1ZE,
    &bafCb,
    BAF1_DLL_PATH
};

const CMB_BAF_Proxy_Config bafBose2Params =
{
    CART_ID_BAF9,
    7,
    bafBose2Heap,
    ENT_BAF_HEAP_S1ZE,
    &bafCb,
    BAF2_DLL_PATH    
};

const CMB_BAF_Proxy_Config bafBose3Params =
{
    CART_ID_BAF3,
    0,
    bafBose3Heap,
    ENT_BAF_HEAP_S1ZE,
    &bafCb,
    BAF3_DLL_PATH
};

const CMB_BAF_Proxy_Config bafBose5Params =
{
    CART_ID_BAF5,
    0,
    bafBose5Heap,
    ENT_BAF_HEAP_S1ZE,
    &bafCb,
    BAF5_DLL_PATH
};

CMB_Framework_adaptorConfig bafAdaptor =
    {
        (CMB_AdaptorInterface*)BAF_Adaptor_getInstance(),
        BAF_PROXY_CNT,
        // CMB_Adaptor_proxyConfig[]
        {
#if BOSE_ENTERTAINMENT_AUDIO
            // Simualted APX BAF.
            {0, bafBoseApxParams.id, bafBoseApxParams.mask, (void*)&bafBoseApxParams},
            // Simualted CAPI BAF.
            {0, bafBose1Params.id, bafBose1Params.mask, (void*)&bafBose1Params},
            {0, bafBose2Params.id, bafBose2Params.mask, (void*)&bafBose2Params},
            {0, bafBose3Params.id, bafBose3Params.mask, (void*)&bafBose3Params},
            {0, bafBose5Params.id, bafBose5Params.mask, (void*)&bafBose5Params},
#endif

#if BOSE_RNC
            {0, bafBoseAms.id, bafBoseAms.mask, (void*)&bafBoseAms},
#endif


#if BOSE_ASDS
            {0, bafBoseAsds.id, bafBoseAsds.mask, (void*)&bafBoseAsds},
#endif
        },
        1,
        0
    };
#endif

#if ENABLE_IOAUDIO_ADAPTOR
CMB_Framework_adaptorConfig ioaudioAdaptor =
    {
        (CMB_AdaptorInterface*)IOA_Adaptor_getInstance(),
        1,

        // CMB_Adaptor_proxyConfig[]
        {
            {0, ioaudioParams.dstId, 0, (void*)&ioaudioParams},
        },
        0,
        0
    };
#endif

#ifndef STUB_DRIVER
CMB_Framework_adaptorConfig entOnlyTuningAdaptor =
{
    (CMB_AdaptorInterface*)Tuning_Adaptor_getInstance(),
    1,

    // CMB_Adaptor_proxyConfig[]
    {
        {0, entTuningConfig.srcId, 0, (void*)&entTuningConfig}, // Adaptor_socket_cfg defaultCfg
    },
    0,
    1,
};

CMB_Framework_adaptorConfig rncOnlyTuningAdaptor =
{
    (CMB_AdaptorInterface*)Tuning_Adaptor_getInstance(),
    1,

    // CMB_Adaptor_proxyConfig[]
    {
        {0, rncTuningConfig.srcId, 0, (void*)&rncTuningConfig}, // Adaptor_socket_cfg defaultCfg
    },
    0,
    1,
};


CMB_Framework_adaptorConfig tuningAdaptor =
{
    (CMB_AdaptorInterface*)Tuning_Adaptor_getInstance(),
    2,

    // CMB_Adaptor_proxyConfig[]
    {
        {0, entTuningConfig.srcId, 0, (void*)&entTuningConfig}, // Adaptor_socket_cfg defaultCfg

        {0, rncTuningConfig.srcId, 0, (void*)&rncTuningConfig},
    },
    0,
    1,
};

CMB_Framework_adaptorConfig entOnlyControlAdaptor =
{
    (CMB_AdaptorInterface*)Control_Adaptor_getInstance(),
    1,

    // CMB_Adaptor_proxyConfig[]
    {
        {0, entControlConfig.srcId, 0, (void*)&entControlConfig},
    },
    0,
    1,
};

CMB_Framework_adaptorConfig rncOnlyControlAdaptor =
{
    (CMB_AdaptorInterface*)Control_Adaptor_getInstance(),
    1,

    // CMB_Adaptor_proxyConfig[]
    {
        {0, rncControlConfig.srcId, 0, (void*)&rncControlConfig},
    },
    0,
    1,
};

CMB_Framework_adaptorConfig controlAdaptor =
{
    (CMB_AdaptorInterface*)Control_Adaptor_getInstance(),
    2,

    // CMB_Adaptor_proxyConfig[]
    {
        // Takes in BTF and BCF for ENT. Based on first character of payload.
        // Tested *AV, ?AV -> BTF. #<someip> -> BCF.
        {0, entControlConfig.srcId, 0, (void*)&entControlConfig},

        // Takes in BTF and BCF for RNC. Based on first character of payload.
        // Tested *Dtxx -> RNC_BTF.
        // To Do: R#<RNC SomeIP command> -> RNC_BCF.
        {0, rncControlConfig.srcId, 0, (void*)&rncControlConfig},
    },
    0,
    1,
};
#endif

CMB_Framework_adaptorConfig csd2AdaptorA2B =
    {
        (CMB_AdaptorInterface*)CSD2_Adaptor_getInstance(),
        2,
        // CMB_Adaptor_proxyConfig[]
        {
            {0, csdA2bBose2ProxyCfg.id, csdA2bBose2ProxyCfg.mask, (void*)&csdA2bBose2ProxyCfg},
            {0, csdBose3ProxyCfg.id, csdBose3ProxyCfg.mask, (void*)&csdBose3ProxyCfg}
        },
    0,
    0,
    };

// CMB_Framework_adaptorConfig csd2AdaptorNxp =
//     {
//         &CSD2_Adaptor_obj,
//         4,
//         // CMB_Adaptor_proxyConfig[]
//         {
//             {0, csdNxpBose1ProxyCfg.id, csdNxpBose1ProxyCfg.mask, (void*)&csdNxpBose1ProxyCfg},
//             {0, CART_ID_BAF9, csdNxpBose2ProxyCfg.mask, (void*)&csdNxpBose2ProxyCfg},
//             {0, csdNxpBose3ProxyCfg.id, csdNxpBose3ProxyCfg.mask, (void*)&csdNxpBose3ProxyCfg},
//             {0, csdBose4ProxyCfg.id, csdBose4ProxyCfg.mask, (void*)&csdBose4ProxyCfg}
//         }
//     };

CMB_Framework_adaptorConfig acsAdaptor =
    {
    (CMB_AdaptorInterface*)ACS_Adaptor_getInstance(),
        1,
        // CMB_Adaptor_proxyConfig[]
        {
            {0, CART_ID_ACS, 0, NULL}
        },
    1,
    1,
    };

CMB_AMS_Proxy_Config amsProxy8295UseCase =
{
        CART_ID_BAF4, // CART_ID_BAF1 is taken
        {
            1,  // AMS graph use case ID.
        },
};
 


CMB_Framework_adaptorConfig amsAdaptor = 
    {
        (CMB_AdaptorInterface*)AMS_Adaptor_getInstance(),
        1,
        // CMB_Adaptor_proxyConfig[]
        {
            {0, CART_ID_BAF4, 0, (void*)&amsProxy8295UseCase}
        },
    0,
    0,
    };

CMB_Framework_config frameworkConfig[MAX_FRAMEWORK_CONFIGS] =
{
    // CMB_Framework_config[0] for HERA, A2B use case.
    {
        CART_ID_BUS,

        "8295-Ref-Design, A2B use case",

        poller,

        NUMBER_OF_ADAPTORS,

        // CMB_Framework_adaptorConfig[]
        {
#if ENABLE_BTF_ADAPTOR
            btfAdaptor,
#endif
#if ENABLE_BCF_ADAPTOR
            bcfAdaptor,
#endif
#if ENABLE_BRF_ADAPTOR
            brfAdaptor,
#endif            
#ifndef STUB_DRIVER
            entOnlyTuningAdaptor,
            entOnlyControlAdaptor,
#endif
#if ENABLE_IOAUDIO_ADAPTOR
            ioaudioAdaptor,
#endif
            csd2AdaptorA2B,
            acsAdaptor,
            amsAdaptor,
        }
    },

    #if 0

    // CMB_Framework_config[1] for HERA, NXP use case.
    {
        CART_ID_BUS,

        "HERA, NXP use case",

        poller,

        //NUMBER_OF_ADAPTORS,
        1,

        // CMB_Framework_adaptorConfig[]
        {
#if ENABLE_BTF_ADAPTOR
            btfAdaptor,
#endif
#if ENABLE_BCF_ADAPTOR
            bcfAdaptor,
#endif
#if ENABLE_BRF_ADAPTOR
            brfAdaptor,
#endif
#if 0
#ifndef STUB_DRIVER
            tuningAdaptor,
            controlAdaptor,
#endif
            ioaudioAdaptor,
            csd2AdaptorNxp,
#endif
            acsAdaptor,
        }
    },
    #endif
};

#ifdef __cplusplus
}
#endif
