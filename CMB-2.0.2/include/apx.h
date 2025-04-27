/* =============================================================================
 * Processing module for APX
 *
 * Copyright 2018-2021, QNX Software Systems. All Rights Reserved.
 *
 * This source code may contain confidential information of QNX Software
 * Systems (QSS) and its licensors.  Any use, reproduction, modification,
 * disclosure, distribution or transfer of this software, or any software
 * that includes or is based upon any of this code, is prohibited unless
 * expressly authorized by QSS by written agreement.  For more information
 * (including whether this source code file has been published) please
 * email licensing@qnx.com.
 * ---------------------------------------------------------------------------*/
/**
 *  @internal
 *  @file            apx.h
 *  @author          QNX, Bose
 *
 *  Public declarations for APX processing module
 */
/*============================================================================*/

#ifndef APX_API_H
#define APX_API_H

// Required for definition of int16_t datatype.
#include "inttypes.h"
#include <stdbool.h>
// Required for definition of snd_pcm_chmap_t needed for the API below.
#include <snd/asound.h>

#define DISABLED_NOTIFICATION_THREAD

#ifndef DISABLED_NOTIFICATION_THREAD

#include <sys/siginfo.h>
#include <signal.h>

#endif // DISABLED_NOTIFICATION_THREAD


#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    void* (*malloc)( size_t size );
    void* (*realloc)( void * old_blk, size_t size );
    void* (*calloc)( size_t n, size_t size );
    void* (*aligned_alloc)( size_t alignment, size_t size );
    void  (*free)( void * ptr );
} module_allocator_t;

// Source (input) and destination (output) chmap pairing
// - describes a compatible input & output configuration
// - use .channels = 0 to indicate "any number of channels"
// - use .pos[i] = SND_CHMAP_UNKNOWN to indicate "any channel position"
typedef struct
{
    snd_pcm_chmap_t const * src_chmap;
    snd_pcm_chmap_t const * dst_chmap;
} chconfig_t;
/** Function list exported by dll module. */
typedef struct
{
    // Module version info
    void (*get_version)(char const ** pszVersionString);

    // Specify the allocator for the module to use
    int16_t (*set_allocator)(module_allocator_t * allocator);

    // Module lifetime
    int16_t (*create)(void ** handle);
    int16_t (*destroy)(void ** handle);
    int16_t (*initialize)(void * handle, void const * config);
    int16_t (*reset)(void * handle);
    int16_t (*deinitialize)(void * handle);

    // Capabilities queries
    // - get range of capabilities supported by module
    // - these queries may be independent of a module instance
    int16_t (*get_supported_pcm_rates)(void * handle, uint32_t * pcm_rates);
    int16_t (*get_supported_pcm_formats)(void * handle, uint32_t * pcm_formats);
    int16_t (*get_supported_pcm_channel_info)(void * handle, uint32_t * pcm_channel_info);
    int16_t (*get_supported_channel_configs)(void * handle, chconfig_t const * const * * channel_configs);

    // Audio param queries
    // - get parameter values for a specific module instance
    int16_t (*get_sample_rate)(void * handle, uint32_t * sample_rate);
    int16_t (*get_samples_per_frame)(void * handle, unsigned int * num_samples_per_frame);
    int16_t (*get_channel_counts)(void * handle, unsigned int * num_chan_in, unsigned int * num_chan_out);
    int16_t (*get_processing_delay)(void * handle, unsigned int * delay);

    // Process frame of audio
    // - in this example, processing is done with separate input and output buffers
    int16_t (*process)(void * handle, float const * in_data_ptr, float * out_data_ptr);

    // Data passing methods
    // - the APX wrapper will connect these methods to a corresponding libasound API

    // This is mapped to the libasound method: snd_pcm_get_apx_data(snd_pcm_t *pcm, uint32_t apx_id, snd_pcm_apx_param_t *param, void *data);
    //      param->size     ↔ size
    //      param->dataId   → data_id
    //      param->channel  → channel
    //      param->status   ← <return_value>
    //      data            ← data
    int16_t (*get_data)(void * handle, int data_id, int channel, size_t * size, void * data);
    // This is mapped to the libasound method: snd_pcm_set_apx_data(snd_pcm_t *pcm, uint32_t apx_id, snd_pcm_apx_param_t *param, const void *data);
    //      param->size     → size
    //      param->dataId   → data_id
    //      param->channel  → channel
    //      param->status   ← <return_value>
    //      data            → data
    int16_t (*set_data)(void * handle, int data_id, int channel, size_t size, void const * data);

    // Helpers
    int16_t (*get_config)(uint32_t sample_rate, snd_pcm_chmap_t const * const src_chmap, snd_pcm_chmap_t const * const dst_chmap, void const ** ppConfig);

} module_funcs_t;

extern const module_funcs_t module_funcs;

/** Error codes */
#define ERR_OK                            (0x0000)
#define ERR_ALLOC                         (0x0100)
#define ERR_NULL_POINTER                  (0x0101)
#define ERR_NOT_INIT                      (0x0102)
#define ERR_NOT_CREATED                   (0x0103)
#define ERR_ALREADY_INIT                  (0x0104)
#define ERR_EMPTY                         (0x0105)
#define ERR_INVALID_ID                    (0x010B)
#define ERR_INVALID_SIZE                  (0x010E)
#define ERR_PARAM                         (0x010F)
#define ERR_INVALID_CHANNEL_CNT           (0x0113)
#define ERR_OVERRUN                       (0x0120)
//custom error defines
#define ERR_QUEUE_FAIL                    (0x0200)
//errors that occur only in the multithreaded version
#define ERR_REGISTER_FAIL                 (0x0201)
#define ERR_CONDVAR_FAIL                  (0x0202)

#ifndef DISABLED_NOTIFICATION_THREAD

// Data IDs for set_data()
typedef enum
{
    E_DATA_CART_MESSAGE,
    E_DATA_CLIENT_PID,
    E_DATA_CART_NOTIFICATION // GetData of notifications
} data_id_t;

// Signal used for notifications from APX to client
#define APX_SIGNAL                      SIGUSR1

#else
// Data IDs for set_data()

typedef enum
{
    E_DATA_CART_MESSAGE
} data_id_t;

#endif // DISABLED_NOTIFICATION_THREAD

// ID assigned to Bose APX by QNX
#define APX_BOSE_ID                     (2)

// Maximum size of CART message supported by APX
#define APX_MAX_MSG_SIZE                (100)

#ifndef DISABLED_NOTIFICATION_THREAD

/**
* @brief Registers APX client for asynchronous signals about new CART notifications
*
* @param[in] handler – signal handler function,
* @param[in] pcm_handle - handle to APX PCM device,
* @param[in] apx_id – APX id,
* @param[in] pid – ID of the process
*
* @return ERR_OK on success, other error code on fail
*
*/
static inline int apx_register_signal(void (*handler)(int, siginfo_t *, void *), snd_pcm_t *pcm_handle, uint32_t apx_id, pid_t pid)
{
    int err = ERR_OK;

    if ((NULL == handler) || (NULL == pcm_handle))
    {
        err = ERR_NULL_POINTER;
    }
    else
    {
        // Register signal handler
        struct sigaction act = {
            .sa_flags = SA_SIGINFO,
            .sa_sigaction = handler,
        };
        sigaction(APX_SIGNAL, &act, NULL);

        // Provide pid to APX
        snd_pcm_apx_param_t param = {
            .size = sizeof(pid),
            .dataId = E_DATA_CLIENT_PID,
            .channel = 0
        };

        int ret = snd_pcm_set_apx_data(pcm_handle, apx_id, &param, (void *)&pid);
        if (ret < 0)
        {
            err = ERR_REGISTER_FAIL;
        }
    }

    return err;
}

// APX macro to register client for asynchronous messages about new CART notifications
#define APX_REGISTER_CLIENT(handler, pcm_hndl, apx_id)  apx_register_signal(handler, pcm_hndl, apx_id, getpid())

#endif // DISABLED_NOTIFICATION_THREAD

// Define macros to get version string from define
#define STRINGIZE(x) #x
#define GET_VERSION(x) STRINGIZE(x)

#ifdef __cplusplus
}
#endif


#endif /* #ifndef APX_API_H */

