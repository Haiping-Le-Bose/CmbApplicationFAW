#ifndef CSD2_API_H
#define CSD2_API_H

/*
  @file csd2.h
  @brief Public APIs for 2nd Core Sound Driver's API. These APIs are public
  to any client that wants to set the audio features on Qualcomm MSM.
 */

/*************************************************************************
*  Copyright (c) 2019-2020 by Qualcomm Technologies, Inc. and/or its
*  subsidiaries. All Rights Reserved.
*  Confidential and Proprietary - Qualcomm Technologies, Inc.
**************************************************************************/

/*=========================================================================
                      EDIT HISTORY FOR MODULE
  This section contains comments describing changes made to this module.
  Notice that changes are listed in reverse chronological order.
  when				who				what, where, why
  -----------     --------		------------------------------------------
  06/16/2020        lkathy      Edited for Agile release (Rev. AA)
  11/30/2019		congt		Initial version
=========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

#include "mmdefs.h"
#include "csd2_status.h"
#include "csd2_types.h"
#include "csd2_ioctl.h"


/** @addtogroup csd2_common_macros
@{ */

/** Major version of the CSD2 API. */
#define CSD2_API_VER_MAIN 0x01

/** Minor version of the CSD2 API. */
#define CSD2_API_VER_MINOR 0x00
/** @} *//* end_addtogroup csd2_common_macros */

enum csd2_module_type{
  CSD2_MODULE_TYPE_NONE = 0,
  CSD2_MODULE_TYPE_AUDIO_SESSION = 1,  
  CSD2_MODULE_TYPE_PP_CONTROL,
  CSD2_MODULE_TYPE_AMS,
  CSD2_MODULE_TYPE_SSR,
  CSD2_MODULE_TYPE_MAX
};
/** @addtogroup csd2_common_functions
@{ */

/**
  Initializes CSD2.

  @param[in] init_param  Initialization parameters for CSD2.

  @detdesc
  This function blocks initialization until aDSP enters Up status (ready to
  provide service to the client) for the first call.

  @return
  #CSD2_EOK for success.\n
  #CSD2_EFAILED for failure.
 */
uint32_t csd2_init(struct csd2_init_data* init_param);

/**
  Opens a handle for the client to communicate with CSD2.

  @param[in] open_cfg  Configuration parameters to open a handle.
  @param[out] handle   Returned handle.

  @detdesc
  csd2_open() is a synchronous function.

  @return
  #CSD2_EOK for success, or any other error code for failure. @newpage
 */
uint32_t csd2_open(enum csd2_module_type type, void* open_cfg, uint32_t size, uint32_t *handle);

/**
  Audio stream playback for session.

  @param[in] handle   Handle for CSD2.
  @param[in] payload  Payload for control command #csd2_buffer*.
  @param[in] count    Size of the payload for the control command.

  @detdesc
  In Block mode, and when there are no available buffers inside CSD2,
  #csd2_write blocks and waits until a free buffer appears. After data
  is written, csd2_write() returns to the application to consume the next set
  of data.
  @par
  In Non-Block mode, #csd2_write returns zero immediately if there is no buffer
  inside CSD2.

  @return
  Positive number -- Byte count of encoded data consumed by CSD2.\n
  0 -- No free buffer available. This return value is for a heap
       memory type only.\n
  -1 -- Error occurred when sending the buffer. @newpage
 */
int32_t csd2_write(uint32_t handle, void* payload, size_t count);

/**
  Audio stream capture for session.

  @param[in] handle   Handle for CSD2.
  @param[in] payload  Payload for control command #csd2_buffer*.
  @param[in] count    Size of the payload for the control command.

  @detdesc
  In Block mode, and when there are no available buffers inside CSD2,
  #csd2_write blocks and waits until a free buffer appears. After data
  is written, csd2_write() returns to the application to consume the next set
  of data.
  @par
  In Non-Block mode, #csd2_write returns zero immediately if there is no buffer
  inside CSD2.

  @return
  Positive number -- Byte count of the data that was received.\n
  0 -- No free buffer available.\n
  -1 -- Error occurred. @newpage
 */
int32_t csd2_read(uint32_t handle, void* payload, size_t count);

/**
  Issues a control command from the client to CSD2 for a specific handle.

  @param[in] handle   Handle for CSD2.
  @param[in] cmd      Control command ID for the CSD2 handle.
  @param[in] payload  Payload for the control command.
  @param[in] count    Size of the payload for the control command.

  @return
  CSD2 status code.
 */
uint32_t csd2_ioctl(uint32_t handle, int32_t cmd, void* payload, size_t count);

/**
  Closes session.

  @param[in] handle  Handle for CSD2.

  @return
  #CSD2_EOK for success.\n
  #CSD2_EFAILED for failure.
 */
uint32_t csd2_close(uint32_t handle);

/**
  Deinitializes entire CSD2 context.

  @detdesc
  No sessions can be created after this function is called.

  @return
  #CSD2_EOK for success.\n
  #CSD2_EFAILED for failure.
 */
uint32_t csd2_deinit(void);
/** @} *//* end_addtogroup csd2_common_functions */

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* CSD2_API_H */
