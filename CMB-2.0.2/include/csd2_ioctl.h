#ifndef CSD2_IOCTL_H
#define CSD2_IOCTL_H

/*
  @file csd2_ioctl.h
  @author
  @date
  @brief Contains audio context IOCTL definitions.
 */

/*************************************************************************
  Copyright (c) 2019-2021 by Qualcomm Technologies, Inc. and/or its
  subsidiaries. All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
**************************************************************************/

/*=========================================================================
                      EDIT HISTORY FOR MODULE
  This section contains comments describing changes made to this module.
  Notice that changes are listed in reverse chronological order.
  when				who				what, where, why
  -----------     --------		------------------------------------------
  02/02/2021        lkathy      Edited for Agile release (Rev. AB)
  06/16/2020        lkathy      Edited for Agile release (Rev. AA)
  12/27/2019		congt		Initial version
=========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif
#include "mmdefs.h"
#include "csd2_media_format.h"
#include "csd2_types.h"
#include "csd2_ams_ioctl.h"
/** @addtogroup csd2_control_macros
@{ */

/** Starts session (no payload required). */
#define CSD2_CMD_START                          0x1001

/** Stops session(no payload required). */
#define CSD2_CMD_STOP                           0x1002

/** Configures stream buffer size/count (must be called before write/read
  audio data).

  Payload: #csd2_stream_buffer_config
 */
#define CSD2_CMD_BUFFER_CONFIG                  0x1003

/** Streams input and output media format configuration (must be called
  before write/read audio data).

  Payload: #csd2_stream_fmt_config
 */
#define CSD2_CMD_SET_STREAM_FORMAT              0x1004

/** Device media format configuration (must be called before write/read
  audio data).

  Payload: #csd2_device_config
 */
#define CSD2_CMD_DEVICE_CONFIG                  0x1005

/** Register stream event callback for write/read done, or EOS event
  (can be called before start).

  Payload: #csd2_reg_event
 */
#define CSD2_CMD_REG_EVENT                      0x1006

/** Register global event like aDSP up or down if client is interested.

  Payload: #csd2_reg_global_event
 */
#define CSD2_CMD_REG_GLOBAL_EVENT               0x1007

/** Notifies session of EOS event to a signal processing framework (SPF).
  One EOS event received by session; no payload required.
 */
#define CSD2_CMD_SET_STREAM_EOS                 0x1008
/** @} *//* end_addtogroup csd2_control_macros */

/** @addtogroup csd2_ppcontrols_macros
@{ */

/** Sets postprocessing control parameter.

  Payload: #csd2_pp_param_config
 */
#define CSD2_CMD_PP_CONTROL_SET                 0x1009

/** Gets postprocessing control parameter.

  Payload: #csd2_pp_param_config
 */
#define CSD2_CMD_PP_CONTROL_GET                 0x100A
/** @} *//* end_addtogroup csd2_ppcontrols_macros */

/** @addtogroup csd2_control_macros
@{ */

/** Allocates buffer to Shared Memory mode.

  Payload: #csd2_get_shmem_buf_info
 */
#define CSD2_CMD_GET_BUF                        0x100B

/** Changes session graph during runtime.

  Payload: #csd2_cmd_change_graph
 */
#define CSD2_CMD_CHANGE_GRAPH                   0x100C

/** Adds a new graph for session during runtime.

  Payload: #csd2_cmd_add_graph
 */
#define CSD2_CMD_ADD_GRAPH                      0x100D

/** Removes graph for session during runtime.

  Payload: #csd2_cmd_remove_graph
 */
#define CSD2_CMD_REMOVE_GRAPH                   0x100E

/** Sets calibration data. Must be called for a session starts.

  Payload: #csd2_cal_config
 */
#define CSD2_CMD_SET_CAL                        0x100F

/** Registers a custom module event (must be called before a session starts).

  Payload: #csd2_register_custom_event
 */
#define CSD2_CMD_REGISTER_CUSTOM_EVENT          0x1010
/** @} *//* end_addtogroup csd2_control_macros */

/** @addtogroup csd2_ppcontrols_macros
@{ */

/** Adds active graph GKVs to CSD2 PP.

  Payload: #csd2_pp_control_active_graph_info
 */
#define CSD2_CMD_PP_ADD_ACTIVE_GRAPH            0x1011

/** Removes the graph GKVs from CSD2 PP.

  Payload: #gsl_handle_t
 */
#define CSD2_CMD_PP_RM_ACTIVE_GRAPH             0x1012

/** Register CSD2 PP callback for events.

  Payload: #csd2_pp_control_reg_event
 */
#define CSD2_CMD_PP_REG_EVENT                   0x1013

/** @} *//* end_addtogroup csd2_ppcontrols_macros */

/** Allocates shared memory.

  Payload: #csd2_pp_shmem_alloc
 */
#define CSD2_CMD_PP_CONTROL_SHARED_MEM_ALLOC      0x1014

/** Frees allocated shared memory

  Payload: #csd2_pp_shmem_free
 */
#define CSD2_CMD_PP_CONTROL_SHARED_MEM_FREE       0x1015

/** @addtogroup csd2_control_datatypes
@{ */

/**
  Key or value metadata.
 */
struct csd2_key_value {
    uint32_t key;    /**< Key stored in audio calibration database (ACDB). */
    uint32_t value;  /**< Value stored in ACDB. */
};

/**
  Payload of #CSD2_CMD_DEVICE_CONFIG single device configuration entry payload.
 */
 struct csd2_device_config_entry {
    uint32_t device_id;
    /**< Device ID to be configured. */

    uint32_t sample_rate;
    /**< Sample rate for hardware interface. */

    uint32_t bits;
    /**< Bits for the hardware interface. */

    uint32_t channels;
    /**< Number of channels for the hardware interface. */
 };

/**
  Payload of #CSD2_CMD_DEVICE_CONFIG.

  Multiple entries are required if more than one device appears in the graph.
 */
struct csd2_device_config {
    uint32_t num_of_devices;
    /**< Number of devices to be configured. */

    struct csd2_device_config_entry entries[];
    /**< Device configuration payload entry. @newpagetable*/
};
/** @} *//* end_addtogroup csd2_control_datatypes */

/** @addtogroup csd2_control_macros
@{ */

/** Shared Memory mode for playback/capture data transfer. */
#define CSD2_DATA_MODE_SHMEM                    0x0

/** Heap Memory mode blocking for playback/capture data transfer. */
#define CSD2_DATA_MODE_BLOCKING                 0x1

/** Heap Memory mode non-blocking for playback/capture data transfer. */
#define CSD2_DATA_MODE_NON_BLOCKING             0x2
/** @} *//* end_addtogroup csd2_control_macros */

/** @addtogroup csd2_control_datatypes
@{ */

/**
  Payload of #CSD2_CMD_BUFFER_CONFIG.

  Configures period_number, period_size, and threshold for
  playback/capture stream.
 */
struct csd2_stream_buffer_config {
    uint32_t buff_size;
    /**< Maximum number of bytes in a single buffer. Read/write operations
         take buffers where the size is a multiple of #buff_size. */

    uint32_t num_buffs;
    /**< Number of buffers used for data exchange. */

    uint32_t start_threshold;
    /**< Threshold to start the stream. */

    uint32_t stop_threshold;
    /**< Threshold to stop the stream. */

    uint32_t buffer_mode;
    /**< Heap block/nonblocking or Shared Memory mode. */
};

/**
  Payload of #CSD2_CMD_SET_STREAM_FORMAT.

  Configures the stream media format of the shared memory endpoint for playback
  and capture stream.
 */
struct csd2_stream_fmt_config {
    union {
        struct csd2_media_fmt_rx rx_fmt;
        /**< Playback media format payload. */
        struct csd2_media_fmt_tx tx_fmt;
        /**< Captures the media format payload. @newpagetable*/
    }u /** Payload of stream media format. */;
};

/**
  Calibration payload for #CSD2_CMD_SET_CAL.
 */
struct csd2_cal_config {
    struct csd2_graph_info *graph_info;
    /**< Identifies the portion of the graph to which this postprocessing
         configuration must be applied (optional). */

    uint32_t num_kvs;
    /**< Number of calibration KVPS to be set during one calibration. */

    struct csd2_key_value *cal_key_vector;
    /**< Payload of calibration key_vector. */
};

/*
  Calibration payload for CSD2_CMD_PP_CONTROL_SET_ or
  CSD2_CMD_PP_CONTROL_GET. Replaces deprecated.
 */

/**
  Payload of GKV.
 */
struct csd2_gkv_info
{
    uint32_t num_kvs;
    /**< Number of GKV in the graph. */
    struct csd2_key_value *kv;
    /**< Payload of graph key_vector. */
};

/**
  Defines a type of TKV or tagged parameter.
*/
enum csd2_pp_param_config_mode {
    CSD2_PP_CFG_MODE_TKV,
    /**< Tagged Key Vector mode for set/get configuration. */

    CSD2_PP_CFG_MODE_TAGGED_PARAM,
    /**< Tag + payload mode for set/get configuration. */
};

/**
  Defines the cache values for the shared memory allocation. This is only used for HLOS
 */
enum csd2_pp_param_cache {
    CSD2_PP_CACHE_NONE,
    /** No cache param required in HLOS.*/

    CSD2_PP_CACHE_WB_WA,
    /**Write back, Write allocate memory allocated. */

    CSD2_PP_CACHE_WB_NWA,
    /**Write back, no write allocate memory allocated. */

    CSD2_PP_CACHE_WT_NWA,
    /**Write through, no write allocate memory allocated.*/
};

/**
  Defines the cache values for the shared memory allocation. This is only used for SPF
 */
enum csd2_pp_param_cache_spf {
    CSD2_PP_UNCACHED,
    /** No cache param required in SPF.*/

    CSD2_PP_CACHED,
    /** Cache param required in SPF.*/
};

/**
  Defines the type of shared memory allocation needed
 */
enum csd2_pp_param_contig {
    CSD2_PP_MEM_CONTIG_NONE,
    /** Non-contiguous memory allocation. PMEM_FLAGS_PHYS_NON_CONTIG */

    CSD2_PP_MEM_CONTIG_ALLOC,
    /** Contiguous memory allocation. The pmem allocation will contain the pmem defined flag PMEM_FLAGS_PHYS_CONTIG. */
};

/**
  Payload of TKV.
 */
    struct csd2_pp_cfg_tkv
    {
    uint32_t num_kvs;
        /**< Number of TKV pairs to be set during one postprocessing
         configuration. */

        struct csd2_key_value *kv;
        /**< Payload of TKV. */
};

/**
  Payload for tagged custom parameters.
 */
    struct csd2_pp_cfg_tagged_param
    {
        uint32_t param_id;
        /**< Parameter ID defined in ACDB. */

        size_t data_sz;
        /**< Size of payload. */

        void *data;
        /**< Payload data. */
};

/**
  Payload of #CSD2_CMD_PP_CONTROL_SET/CSD2_CMD_PP_CONTROL_GET.
 */
struct csd2_pp_param_config {
    struct csd2_gkv_info gkv;
    /**< GKV describing graph. */

    uint32_t tag;
    /**< Tag ID defined in ACDB. */

    bool_t is_persist;
    /**< Flag that indicates persistence of applied parameter. */

    enum csd2_pp_param_config_mode mode;
    /**< Configuration mode. */
    union {
        struct csd2_pp_cfg_tkv tkv;
        /**< Holds payload for tagged key vector (TKV) parameter. */
        struct csd2_pp_cfg_tagged_param tagged_param;
        /**< Holds payload for custom (param_id + data) payload. */
    }u /** Holds payload for parameters of DSP modules configuration. */;
};
/** @} *//* end_addtogroup csd2_control_datatypes */


/** @ingroup csd2_control_macros
  Indicates a given buffer is the final buffer. */
#define CSD2_BUF_MASK_EOF_FLAG 0x1


/** @ingroup csd2_control_retval
  Returns TRUE if buffer has a valid timestamp. */
#define CSD2_BUF_MASK_TS_FLAG 0x2


/** @addtogroup csd2_control_datatypes
@{ */

/**
  Defines the buffer structure for reading and writing an audio stream
  with #csd2_read() and #csd2_write().
 */
struct csd2_buffer
{
    uint8_t* buf_addr;
    /**< Pointer to the beginning of the buffer. */

    uint32_t buf_size;
    /**< Buffer size in bytes. */

    uint32_t buf_mask;
    /**< Bitmask for the buffer:
          - #CSD2_BUF_MASK_EOF_FLAG
          - #CSD2_BUF_MASK_TS_FLAG */

    uint32_t    ts_high;
    /**< Upper 32 bits of the microsecond timestamp (field is valid only if
         #CSD2_BUF_MASK_TS_FLAG exists). */

    uint32_t ts_low;
    /**< Lower 32 bits of the microsecond timestamp (field is valid only if
         #CSD2_BUF_MASK_TS_FLAG exists). */

    uint32_t offset;
    /**< Offset in buffer where valid data begins (might be metadata
         inserted before real audio data). */
};

/**
  Adds new graph(s) to the opened graph for a single session.

  Payload: #CSD2_CMD_ADD_GRAPH.
 */
struct csd2_cmd_add_graph {
    struct csd2_graph_info* info;
    /**< Graph is added to a session. */

    struct csd2_device_config* device_config;
    /**< Device configuration if a new device is present in the graph. @newpagetable*/
};

/**
  Removes one or more graphs for a single session.

  Payload: #CSD2_CMD_REMOVE_GRAPH.
 */
struct csd2_cmd_remove_graph {
    struct csd2_graph_info* info;
    /**< Graph is removed from a session. */
};

/**
  Allows changes to a graph for a session during runtime.

  Payload: #CSD2_CMD_CHANGE_GRAPH
 */
struct csd2_cmd_change_graph {
    struct csd2_graph_info* info;
    /**< Graph changes for session. */

    struct csd2_device_config* device_config;
    /**< Device configuration if a new device is present in the graph. */
};

/**
  Shared memory allocation client provides Process ID (PID) for csd2 to map
  address into the client address space.

  Payload: #CSD2_CMD_GET_BUF
 */
struct csd2_shmem_buf {
    uint8_t* addr;      /**< Buffer address. */
    uint64_t metadata;  /**< Per buffer metadata. @newpagetable*/
};

/**
  Returns required buffer information for Shared Memory mode.

  Payload: #CSD2_CMD_GET_BUF
 */
struct csd2_get_shmem_buf_info {
    uint32_t pid;
    /**< Client PID (csd2 must map the virtual address to the PID address
         space). */

    uint32_t size;
    /**< Buffer size (all buffers have the same size). */

    uint32_t num_buffs;
    /**< Number of buffers. */

    struct csd2_shmem_buf* buffs;
    /**< List of buffers, containing #num_buffs entries. */
};

/**
  Digital signal processor (DSP) events that notify session.
 */
enum csd2_event_id
{
  CSD2_EVENT_ID_EOS = 0x0,
  /**< EOS event indicates that all data written to SPF before
       the client calls CSD2_CMD_EOS has played out. */

  CSD2_EVENT_ID_READ_DONE = 0x1,
  /**< Indicates provided buffer for the read call was filled.
       Payload: #csd2_event_read_write_done_payload.
 */

  CSD2_EVENT_ID_WRITE_DONE = 0x2,
  /**< Indicates provided buffer for write was consumed.
       Payload: #csd2_event_read_write_done_payload. */

  CSD2_EVENT_ID_BUFFER_AVAIL = 0x3,
  /**< Indicates buffer is available for client to write to (sent in
       Non-Blocking mode only). */

  CSD2_EVENT_ID_INVALID,
  /**< */
};

/**
  Data passed to a session in an event callback.
 */
struct csd2_event_cb_params {
    uint32_t source_module_id;
    /**< Identifies the module that generated the event. */

    enum csd2_event_id event_id;
    /**< Identifies event. */

    uint32_t event_payload_size;
    /**< Size of payload referred by event_payload pointer.\n
         For an EOS event, size may be 0.\n
         For a read/write done event, size is
         csd2_event_read_write_done_payload. */

    void* event_payload;
    /**< Payload associated with the event (if any). */
};

/**
  Event payload passed to client with #CSD2_EVENT_ID_READ_DONE and
  #CSD2_EVENT_ID_WRITE_DONE events.
 */
struct csd2_event_read_write_done_payload {
    void*    addr;       /**< Buffer that was passed to read/write. */
    size_t   count;      /**< Size of read/write. */
    uint64_t timestamp;  /**< Timestamp in microseconds. @newpagetable*/
};

/**
  Global events that can be raised through global callback.
 */
enum csd2_global_event_ids
{
  CSD2_GLOBAL_EVENT_AUDIO_SVC_UP,
  /**< Indicates that an audio service is up. For example, restart after SSR
       and payload is NULL. */

  CSD2_GLOBAL_EVENT_AUDIO_SVC_DN,
  /**< Indicates that an audio service is down, this can happen for example due
       to SSR. Payload: #csd2_global_event_svc_dn_payload. */

  CSD2_GLOBAL_EVENT_INVALID,
  /**< */
};

/**
  Event payload passed to client with #CSD2_GLOBAL_EVENT_AUDIO_SVC_DN.
 */
struct csd2_global_event_svc_dn_payload {
    uint32_t num_handles;
    /**< Number of handles. */

    int32_t* handle_list;
    /**< List of handles impacted by the audio service going down. The client is
         responsible for closing and reopening these handles once it receives
         the audio service up notification. */
};

/**
  Callback to notify global events to client.

  Global events are not bound to a specific session handle.

  @param[in] event_id          Indicates global event ID.
  @param[in] event_payload     Event ID of the specific payload.
  @param[in] event_payload_sz  Size of the event ID of the specific payload.
  @param[in] client_data       Opaque client data.

 */
typedef uint32_t(*csd2_global_cb_func_ptr)(enum csd2_global_event_ids event_id,
    void* event_payload, size_t event_payload_sz, void* client_data);

/**
  Callback function signature for events to client.

  @param[in] event_params  Holds all event related information.
  @param[in] client_data   Client data provided during cb registration.

 */
typedef void (*csd2_cb_func_ptr)(struct csd2_event_cb_params* event_params,
    void* client_data);

/**
  Payload for #CSD2_CMD_REG_EVENT register stream event.
 */
struct csd2_reg_event {
    csd2_cb_func_ptr event_cb;  /**< Session event callback. */
    void* client_data;          /**< Client callback data. */
};

/**
  Payload for #CSD2_CMD_REGISTER_CUSTOM_EVENT for module event.
 */
struct csd2_register_custom_event {
    uint32_t module_instance_id;
    /**< Valid instance ID of the module. */

    uint32_t event_id;
    /**< Valid event ID of the module. */

    uint32_t event_config_payload_size;
    /**< Size of the event configuration data based on the module_instance_id
         or event_id combination. Supported values are greater than 0 bytes
         in multiples of (at least) 4 bytes. */

    uint8_t is_register;
    /**< - 1 - Registers the event.

         - 0 - Deregisters the event. */

    uint8_t event_config_payload[];
    /**< Module specific event registration payload. @newpagetable*/
};

/**
  Payload for #CSD2_CMD_REG_GLOBAL_EVENT client_data.
 */
struct csd2_ssr_client_config {
	char name[12];
	void *config_payload; //reserved
};

/**
  Payload for #CSD2_CMD_REG_GLOBAL_EVENT register global event.
 */
struct csd2_reg_global_event {
    csd2_global_cb_func_ptr global_event_cb;  /**< Global event callback. */
    void* client_data;                        /**< Client callback data. */
};

/**
  Payload for #CSD2_CMD_PP_CONTROL_SHARED_MEM_ALLOC register global event.
 */
struct csd2_pp_shmem_alloc
{
    uint32_t size;
    /**< Size of shared memory. */

    uint32_t pid;
    /**< Process id of the application. This is required by
    the mmap64_peer function to map the process back to the client. */

    void *virt_addr;
    /**< The pointer to the virtual memory address,
    to be updated by the CSD2 driver */

    enum csd2_pp_param_cache cache;
    /**< Tells the type of caching the shared memory would present.
     The supported values are contains are the
     values present in enum CSD2_PP_PARAM_CACHE.
     This is used for HLOS*/

    enum csd2_pp_param_cache_spf cache_spf;
    /**< Tells the type of caching the shared memory would present.
     The supported values are contains are the
     values present in enum CSD2_PP_PARAM_CACHE.
     This is used for SPF*/

    enum csd2_pp_param_contig contig;
    /**< Tells type of memory allocation is required or not.
    The supported values are contains are the values
    present in enum CSD2_PP_PARAM_CONTIG. */

    uint32_t spf_mem_handle;
    /**< SPF Memory Handle of the shared memory. Used in the get and set pp params. */

    uint32_t spf_mem_addr_lsw;
    /**< Least significant bits of the spf address. */

    uint32_t spf_mem_addr_msw;
    /**< Most significant bits of the spf address. */
};

/**
  Payload of #CSD2_CMD_PP_CONTROL_SHARED_MEM_FREE
 */
struct csd2_pp_shmem_free {
    void *virt_addr;
    /**< The pointer to the virtual memory address, to be updated by the CSD2 driver. */
};

/** @} *//* end_addtogroup csd2_control_datatypes */


/** @addtogroup csd2_ppcontrols_datatypes
@{ */

/**
  Payload for #CSD2_CMD_PP_ADD_ACTIVE_GRAPH
 */
struct csd2_pp_control_active_graph_info
{
  struct csd2_gkv_info  gkv;
  uint32_t hdl;//only gkv is available in gsl_vm_be_close
};

/**
    CSD2 PP events that notify clients.
 */
enum csd2_pp_control_event_id
{
    CSD2_PP_EVENT_ID_GRAPH_ADD = 0x0,
    /**< Indicates a new active graph is added into CSD2 PP */

    CSD2_PP_EVENT_ID_GRAPH_RM = 0x1,
    /**< Indicates an active graph is removed from CSD2 PP */

    CSD2_PP_EVENT_ID_INVALID,
};

/**
    Data passed to clients in a graph event callback.
 */
struct csd2_pp_control_event_cb_params {
    enum csd2_pp_control_event_id event_id;
    /**< Identifies event. */

    uint32_t event_payload_size;
    /**< Size of payload referred by event_payload pointer.
         For CSD2_PP_EVENT_ID_GRAPH_ADD & CSD2_PP_EVENT_ID_GRAPH_RM
         event_payload_size = num_kvs * sizeof(struct csd2_key_value) */

    void* event_payload;
    /**< Payload associated with the event.
         For CSD2_PP_EVENT_ID_GRAPH_ADD & CSD2_PP_EVENT_ID_GRAPH_RM
         event_payload is struct csd2_key_value* */
};

/**
  Callback function signature for CSD2 PP graph events to client.

  @param[in] event_params  Holds all event related information.
  @param[in] client_data   Client data provided during cb registration.
 */
typedef void (*csd2_pp_control_cb_func_ptr)(struct csd2_pp_control_event_cb_params* event_params,
    void* client_data);

/**
  Payload for #CSD2_CMD_PP_RM_ACTIVE_GRAPH
 */
//gsl_handle_t hdl;

/**
  Payload for #CSD2_CMD_PP_REG_EVENT
 */
struct csd2_pp_control_reg_event
{
    csd2_pp_control_cb_func_ptr event_cb; /**< CSD2 PP event callback. */
    void* client_data;                    /**< Client callback data. */
};

/** @} *//* end_addtogroup csd2_ppcontrols_datatypes */

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* CSD2_IOCTL_H */
