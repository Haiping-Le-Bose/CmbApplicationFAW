#ifndef _CSD2_AMS_IOCTL_H_
#define _CSD2_AMS_IOCTL_H_
/**
	@file      csd2_ams_ioctl.h
    @brief
	Contains audio micro service IOCTL definitions
*/
/*===========================================================================
NOTE: The @brief description and any detailed descriptions above do not appear
      in the PDF.

      The CSD2_mainpage.dox file contains all file/group descriptions that are
      in the output PDF generated using Doxygen and LaTeX. To edit or update
      any of the file/group text in the PDF, edit the CSD2_mainpage.dox file or
      contact Tech Pubs.
===========================================================================*/

/*-----------------------------------------------------------------------------
     Copyright (C) 2010-2012,2018,2021 Qualcomm Technologies Incorporated.
	 All rights reserved.
	 Qualcomm Confidential and Proprietary.
-----------------------------------------------------------------------------*/
/*=============================================================================
                      EDIT HISTORY FOR MODULE
	This section contains comments describing changes made to this module.
	Notice that changes are listed in reverse chronological order.

	$DateTime: 2021/10/09 14:41:03 $
	$Author: pwbldsvc $
	$Revision: #1 $

    when		who			what, where, why
    --------	-------		---------------------------------------------------
    =========================================================================*/

#include "mmdefs.h"

/** TDM port enumeration. */
typedef enum
{
    CSD2_AMS_HW_INTERFACE_TDM1 = 1,
    CSD2_AMS_HW_INTERFACE_TDM2,
    CSD2_AMS_HW_INTERFACE_TDM3,
    CSD2_AMS_HW_INTERFACE_TDM4,
    CSD2_AMS_HW_INTERFACE_TDM5,
    CSD2_AMS_HW_INTERFACE_TDM6,
    CSD2_AMS_HW_INTERFACE_TDM7,
    CSD2_AMS_HW_INTERFACE_TDM8,
    CSD2_AMS_HW_INTERFACE_TDM9,
    CSD2_AMS_HW_INTERFACE_TDM10,
    CSD2_AMS_HW_INTERFACE_TDM11,
    CSD2_AMS_HW_INTERFACE_TDM12,
    CSD2_AMS_HW_INTERFACE_MAX,
} csd2_ams_hw_interface_id_t;

/** Exclusive endpoint - endpoint managed only by AMS. */
#define CSD2_AMS_ENDPOINT_EXCLUSIVE (0)

/**
  Shared endpoint - endpoint shared between AMS and AVS framework, where the
  AVS framework outputs to this endpoint. The configuration of the HW interface
  is done by AVS framework.
*/
#define CSD2_AMS_ENDPOINT_SHARED_WITH_ADSP_OUTPUT (1)

/**
  Shared endpoint - endpoint shared between AMS and AVS framework, where the
  AVS framework gets input from this endpoint. The configuration of the HW
  interface is done by AVS framework.
*/
#define CSD2_AMS_ENDPOINT_SHARED_WITH_ADSP_INPUT (2)

/** Send a command to AMS FW and return the response back to the caller. */
#define CSD2_AMS_CMD_TUNNEL 0x00015000
/**
  @brief Payload for the #CSD2_AMS_CMD_TUNNEL ioctl
*/

struct csd2_ams_tunnel_rsp
{
  uint32_t response_code;
  uint32_t response_size;
  uint8_t response[];
};

typedef struct
{
    uint32_t processor_id;   // [in] 0 for MDSP
    uint32_t opcode;         // [in]
    void *payload;           // [in]
    uint32_t payload_size;   // [in]
    struct csd2_ams_tunnel_rsp *rsp; // [out]
} csd2_ams_tunnel_t;

/** Enable endpoint of the graph. */
#define CSD2_AMS_CMD_ENABLE_ENDPOINT 0x00015001

/** Disable endpoint of the graph. */
#define CSD2_AMS_CMD_DISABLE_ENDPOINT 0x00015002

/** Set clk attribute. */
#define CSD2_AMS_CMD_SET_CLK_ATTR 0x00015003

/**
  @brief Payload for the #CSD2_AMS_CMD_ENABLE_ENDPOINT and #CSD2_AMS_CMD_DISABLE_ENDPOINT ioctl
*/
typedef struct
{
    uint32_t flags; // [in] Optional flag: CSD2_AMS_ENDPOINT_FLAG_SHARED
    bool_t source;  // true: tx, false: rx
    struct
    {
        csd2_ams_hw_interface_id_t hw_interface_id;
        uint32_t num_channels;
        uint32_t sample_rate;
        uint32_t bit_width;
        uint16_t data_format;
        uint16_t sync_mode;
        uint16_t sync_src;
        uint16_t nslots_per_frame;
        uint16_t ctrl_data_out_enable;
        uint16_t ctrl_invert_sync_pulse;
        uint16_t ctrl_sync_data_delay;
        uint16_t slot_width;
        uint32_t slot_mask;
    } tdm_params; // [in]
} csd2_ams_endpoint_t;

typedef struct
{
    uint16_t ep_id;
    uint16_t attr;
} csd2_ams_clk_attr_t;


/** Get cached graph info. */
#define CSD2_AMS_CMD_GET_CACHED_GRAPH_INFO 0x00015004
// payload for get cached graph
typedef struct
{
    uint32_t idx;
    uint32_t state;
    uint32_t fw_handle;
    uint32_t gr_descr_sz;
    // void *gr_descr;
}csd2_ams_cached_graph_info_t;

#define CSD2_AMS_CMD_GET_CACHED_GRAPH_NUM 0x00015005
// payload
typedef struct
{
    uint32_t num;
}csd2_ams_cached_graph_num_t;

#define CSD2_AMS_CMD_OPERATE_DEVICE 0x00015006
//payload
typedef struct
{
    uint32_t enable;
    uint32_t device_id;
    uint32_t sample_rate;
    uint32_t sample_width;
}csd2_ams_operate_device_t;

#define CSD2_AMS_CMD_ALLOC_SHMEM 0x00015007

//payload
typedef struct
{
    uint32_t pid;
    uint32_t client_id;// idx in shmem array info on server
    uint32_t len;
}csd2_ams_shmem_alloc_req_t;

typedef struct
{
    uint32_t va_lsw; // virtual addr low
    uint32_t va_msw; // virtual addr high
    uint32_t mem_map_handle;
    uint32_t pa_lsw; // physical addr low
    uint32_t pa_msw; // physical addr high
}csd2_ams_shmem_alloc_rsp_t;

typedef struct
{
    csd2_ams_shmem_alloc_req_t req;
    csd2_ams_shmem_alloc_rsp_t resp;
}csd2_ams_shmem_alloc_t;

#define CSD2_AMS_CMD_FREE_SHMEM 0x00015008
typedef struct
{
    uint32_t client_id;// idx in shmem array info on server
    uint32_t pid;
    uint32_t va_lsw; // virtual addr low
    uint32_t va_msw; // virtual addr high
    uint32_t mem_map_handle;
    uint32_t pa_lsw; // physical addr low
    uint32_t pa_msw; // physical addr high
}csd2_ams_shmem_free_t;


#define CSD2_AMS_CMD_GET_CACHED_GRAPH_PROP_NUM 0x00015009
// payload
typedef struct
{
    // uint32_t gr_idx;
    uint32_t num;
}csd2_ams_cached_graph_prop_num_t;
#define CSD2_AMS_CMD_GET_CACHED_GRAPH_PROP_INFO 0x0001500A
typedef struct
{
    // uint32_t gr_idx;
    uint32_t prop_idx;
    uint32_t prop_descr_sz;
    // void *prop_descr;
}csd2_ams_cached_graph_prop_info_t;

#define CSD2_AMS_CMD_GET_CACHED_GRAPH_PROP_DESCR 0x0001500B
typedef struct
{
    uint32_t prop_idx;
    uint32_t prop_descr_sz;
    void *prop_descr;
}csd2_ams_cached_graph_prop_descr_t;

/** Get cached graph description. */
#define CSD2_AMS_CMD_GET_CACHED_GRAPH_DESCR 0x0001500C
// payload for get cached graph
typedef struct
{
    uint32_t idx;
    uint32_t gr_descr_sz;
    void *gr_descr;
}csd2_ams_cached_graph_descr_t;

#define CSD2_AMS_CMD_OPERATE_DEVICE_QUERY 0x0001500D
//payload
typedef struct
{
    uint32_t device_id;
    uint32_t *state;
}csd2_ams_operate_device_query_t;
#endif /* _CSD2_AMS_IOCTL_H_ */
