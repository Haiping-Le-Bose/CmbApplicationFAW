#ifndef CSD2_STATUS_H
#define CSD2_STATUS_H

/*
 * @file csd2_status.h
 * @author 
 * @date
 * @brief Public error code definition for Core Sound Driver 2.0.
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

/** @addtogroup csd2_common_msg
@{ */

/** The operation completed, and there were no errors.
  @hideinitializer
 */
#define CSD2_EOK            (0x0)

/** General failure.
  @hideinitializer
 */
#define CSD2_EFAILED        (0x00012313)

/** Invalid operation parameters.
  @hideinitializer
 */
#define CSD2_EBADPARAM     (0x00012314)

/** Unsupported routine or operation.
  @hideinitializer
 */
#define CSD2_EUNSUPPORTED   (0x00012315)

/** Unsupported version.
  @hideinitializer
 */
#define CSD2_EVERSION       (0x00012316)

/** An unexpected problem was encountered.
  @hideinitializer
 */
#define CSD2_EUNEXPECTED    (0x00012317)

/** Unhandled problem occurred.
  @hideinitializer
 */
#define CSD2_EPANIC        (0x00012318)

/** Unable to allocate resources.
  @hideinitializer
 */
#define CSD2_ENORESOURCE    (0x00012319)

/** Invalid handle.
  @hideinitializer
 */
#define CSD2_EHANDLE        (0x0001231A)

/** Operation already processed.
  @hideinitializer
 */
#define CSD2_EALREADY       (0x0001231B)

/** Operation is not ready to be processed.
  @hideinitializer
 */
#define CSD2_ENOTREADY      (0x0001231C)

/** Operation is pending completion.
  @hideinitializer
 */
#define CSD2_EPENDING       (0x0001231D)

/** Operation cannot be accepted or processed.
  @hideinitializer
 */
#define CSD2_EBUSY          (0x0001231E)

/** Operation aborted because of an error.
  @hideinitializer
 */
#define CSD2_EABORTED      (0x0001231F)

/** Operation was preempted by a higher priority.
  @hideinitializer
 */
#define CSD2_EPREEMPTED    (0x00012320)

/** Operation requires intervention to complete.
  @hideinitializer
 */
#define CSD2_ECONTINUE     (0x00012321)

/** Operation requires immediate intervention to complete.
  @hideinitializer
 */
#define CSD2_EIMMEDIATE    (0x00012322)

/** Operation not implemented.
  @hideinitializer
 */
#define CSD2_ENOTIMPL       (0x00012323)

/** Operation requires more data or resources.
  @hideinitializer
 */
#define CSD2_ENEEDMORE       (0x00012324)

/** Operation is a local procedure call.
  @hideinitializer
 */
#define CSD2_ELPC           (0x00012325)

/** Operation timed out.
  @hideinitializer
 */
#define CSD2_ETIMEOUT       (0x00012326)

/** CSD2 did not find the handle or an internal resource required to process
  the request.
  @hideinitializer
 */
#define CSD2_ENOTFOUND      (0x00012327)

/** Operation cannot proceed because of an improper state.
  @hideinitializer
 */
#define CSD2_EBADSTATE      (0x00012328)

/** Qualcomm aDSP returns error status.
  @hideinitializer
 */
#define CSD2_EQADSP         (0x00012329)

/** Subsystem is in reset.
  @hideinitializer
 */
#define CSD2_ESSRESET       (0x0001232A)

/** Operation is not permitted.
  @hideinitializer
 */
#define CSD2_EPERMISSION    (0x0001232B)

/** For internal use only.
  @hideinitializer
 */
#define CSD2_ESTATUS_END    (0x00012700)
/** @} *//* end_addtogroup csd2_common_msg */

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* CSD2_STATUS_H */
