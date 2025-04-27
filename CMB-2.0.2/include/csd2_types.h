#ifndef CSD2_TYPES_H
#define CSD2_TYPES_H

/*
 * @file csd2_types.h
 * @author 
 * @date
 * @brief Basic data structure definitions for Core Sound Driver 2.0.
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


/**  @ingroup csd2_common_macros
  Maximum number of nodes that can be defined for each type. */
#define CSD2_TYPES_MAX_NUMBER   0x100

/** @addtogroup csd2_common_datatypes
@{ */

/**
  Node value definition.
 */
typedef uint32_t csd2_node_id_t;

/**
  Graph node definitions.
 */
typedef enum {
  CSD2_INVALID_TYPE = 0,    /**< */
  CSD2_STREAM_TYPE,         /**< */
  CSD2_STREAM_PP_TYPE,      /**< Stream postprocessing definition. */
  CSD2_STREAM_DEVICE_TYPE,  /**< Stream to device processing definition. */
  CSD2_DEVICE_PP_TYPE,      /**< Device to postprocessing definition. */
  CSD2_DEVICE_TYPE,         /**< */
  CSD2_MAX_TYPE,            /**< Maximum node type supported. */
} csd2_node_type_t;
/** @} *//* end_addtogroup csd2_common_datatypes */

/** @addtogroup csd2_common_macros
@{ */

/** Shift bit that identifies Stream type.
  @hideinitializer
 */
#define CSD2_STREAM_TYPE_SHIFT                  (8)

/** Mask that identifies Stream type.
  @hideinitializer
 */
#define CSD2_STREAM_TYPE_MASK                   (1 << CSD2_STREAM_TYPE_SHIFT)

/** Supported Stream value start index.
  @hideinitializer
 */
#define CSD2_STREAM_TYPE_BEGIN                  (1 << CSD2_STREAM_TYPE_SHIFT)

/** Supported Stream value end index.
  @hideinitializer
 */
#define CSD2_STREAM_TYPE_END                    (CSD2_STREAM_TYPE_BEGIN + CSD2_TYPES_MAX_NUMBER)

/** Shift bit that identifies a Stream postprocessing type.
  @hideinitializer
 */
#define CSD2_STREAM_PP_TYPE_SHIFT               (9)

/** Mask that identifies a Stream postprocessing type.
  @hideinitializer
 */
#define CSD2_STREAM_PP_TYPE_MASK                (1 << CSD2_STREAM_PP_TYPE_SHIFT)

/** Supported Stream postprocessing value start index.
  @hideinitializer
 */
#define CSD2_STREAM_PP_TYPE_BEGIN               (1 << CSD2_STREAM_PP_TYPE_SHIFT)

/** Supported Stream postprocessing value end index.
  @hideinitializer
 */
#define CSD2_STREAM_PP_TYPE_END                 (CSD2_STREAM_PP_TYPE_BEGIN + CSD2_TYPES_MAX_NUMBER)

/** Shift bit that identifies a StreamDevice type.
  @hideinitializer
 */
#define CSD2_STREAM_DEVICE_TYPE_SHIFT           (10)

/** Mask that identifies a StreamDevice Mixer postprocessing type.
  @hideinitializer
 */
#define CSD2_STREAM_DEVICE_TYPE_MASK            (1 << CSD2_STREAM_DEVICE_TYPE_SHIFT)

/** Supported StreamDevice value start index.
  @hideinitializer
 */
#define CSD2_STREAM_DEVICE_TYPE_BEGIN           (1 << CSD2_STREAM_DEVICE_TYPE_SHIFT)

/** Supported StreamDevice value end index.
  @hideinitializer
 */
#define CSD2_STREAM_DEVICE_TYPE_END             (CSD2_STREAM_DEVICE_TYPE_BEGIN + CSD2_TYPES_MAX_NUMBER)

/** Shift bit that identifies a Device postprocessing type.
  @hideinitializer
 */
#define CSD2_DEVICE_PP_TYPE_SHIFT               (11)

/** Mask that identifies a Device postprocessing type.
  @hideinitializer
 */
#define CSD2_DEVICE_PP_TYPE_MASK                (1 << CSD2_DEVICE_PP_TYPE_SHIFT)

/** Supported Device postprocessing value start index.
  @hideinitializer
 */
#define CSD2_DEVICE_PP_TYPE_BEGIN               (1 << CSD2_DEVICE_PP_TYPE_SHIFT)

/** Supported Device postprocessing value end index.
  @hideinitializer
 */
#define CSD2_DEVICE_PP_TYPE_END                 (CSD2_DEVICE_PP_TYPE_BEGIN + CSD2_TYPES_MAX_NUMBER)

/** Shift bit that identifies a Device type.
  @hideinitializer
 */
#define CSD2_DEVICE_TYPE_SHIFT                  (12)

/** Mask that identifies as a Device type.
  @hideinitializer
 */
#define CSD2_DEVICE_TYPE_MASK                   (1 << CSD2_DEVICE_TYPE_SHIFT)

/** Supported Device value start index.
  @hideinitializer
 */
#define CSD2_DEVICE_TYPE_BEGIN                  (1 << CSD2_DEVICE_TYPE_SHIFT)

/** Supported Device postprocessing value end index.
  @hideinitializer
 */
#define CSD2_DEVICE_TYPE_END                    (CSD2_DEVICE_TYPE_BEGIN + CSD2_TYPES_MAX_NUMBER)
/** @} *//* end_addtogroup csd2_common_macros */

/** @addtogroup csd2_common_datatypes
@{ */

/**
  Argument for #csd2_init, reserved.
 */
 struct csd2_init_data {
     int32_t reserved;  /**< Reserved parameter for future use. */
 };

/**
  Describes how an audio graph consists of nodes.
 */
 struct csd2_graph_info {
     uint32_t number_of_nodes;  /**< Number of nodes. */
     csd2_node_id_t node_id[];  /**< Array of graph node IDs. */
 };
/** @} *//* end_addtogroup csd2_common_datatypes */

/** @addtogroup csd2_common_msg
@{ */

/** CSD2 is open for read. */
#define CSD2_OPEN_OP_R        0x01

/** CSD2 is open for write. */
#define CSD2_OPEN_OP_W        0x02

/** CSD2 is open for read and write. */
#define CSD2_OPEN_OP_RW       0x03

/** CSD2 is open for a loopback (Tx to Rx). */
#define CSD2_OPEN_OP_LOOPBACK 0x04

/** CSD2 is open for a hostless session. */
#define CSD2_OPEN_OP_HOSTLESS 0x05
 /** @} *//* end_addtogroup csd2_common_msg */

/** @ingroup csd2_common_datatypes
  Payload for #csd2_open(). The given op_code and graph creates a session.
 */
struct csd2_open_config {
  int32_t op_code;
  /**< Operation code for CSD2 to open the audio graph.

       @values
        - CSD_OPEN_OP_R
        - CSD_OPEN_OP_W
        - CSD_OPEN_OP_RW
        - CSD_OPEN_OP_LOOPBACK
        - CSD2_OPEN_HOSTLESS @tablebulletend */

  struct csd2_graph_info*  graph_info;
  /**< Pointer to graph structure. */
};

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* CSD2_TYPES_H */
