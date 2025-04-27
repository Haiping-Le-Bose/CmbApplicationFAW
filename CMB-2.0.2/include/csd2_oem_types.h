#ifndef CSD2_OEM_TYPES_H
#define CSD2_OEM_TYPES_H

/*
 * @file csd2_oem_types.h
 * @author 
 * @date
 * @brief Graph node definition headerfile.
 * Usually a full HLOS graph the data flow can look like below:
 * Stream -> StreamPP -> StreamDevice -> DevicePP -> Device;
 * For a valid HLOS graph it shall include at least Stream + Device node,
 * Otherwise Error code will be returned; 
 * Depends on graph design additional StreamPP/StreamDevice/DevicePP can
 * be utilized to support more complex usecase.
 */

/*************************************************************************
*  Copyright (c) 2019-2020 by Qualcomm Technologies, Inc. and/or its
*  subsidiaries. All rights reserved.
*  Confidential and Proprietary - Qualcomm Technologies, Inc.
**************************************************************************/

/*=========================================================================
                      edit history for module
  this section contains comments describing changes made to this module.
  notice that changes are listed in reverse chronological order.
  when				who				what, where, why
  -----------     --------		------------------------------------------
  06/16/2020        lkathy      Edited for Agile release (Rev. AA)
  11/30/2019		congt		initial version
=========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

#include "csd2_types.h"

/** @addtogroup csd2_node_datatypes
@{ */

/**
  Defines available Stream nodes.

  Stream node is a mandatory node of the high-level operating system (HLOS)
  graph with the following terms:
  - StreamRx node: Data source for PLAYBACK.
  - StreamTx node: Data sink for CAPTURE case.
  - Loopback node: Both data source and sink for DSP LOOPBACK case.
 */
typedef enum {
  CSD2_STREAM_RANGE_INVALID = CSD2_STREAM_TYPE_BEGIN,
  /**< */
  CSD2_STREAM_PCM_PLAYBACK,
  /**< pcm playback stream with no instance. */

  CSD2_STREAM_PCM_PLAYBACK_1,
  /**< pcm playback stream instance 1. */

  CSD2_STREAM_PCM_PLAYBACK_2,
  /**< PCM Playback Stream Instance 2. */

  CSD2_STREAM_PCM_PLAYBACK_3,
  /**< PCM Playback Stream Instance 3. */

  CSD2_STREAM_PCM_PLAYBACK_4,
  /**< PCM Playback Stream Instance 4. */

  CSD2_STREAM_PCM_PLAYBACK_5,
  /**< PCM Playback Stream Instance 5. */

  CSD2_STREAM_PCM_PLAYBACK_6,
  /**< PCM Playback Stream Instance 6. */

  CSD2_STREAM_PCM_PLAYBACK_7,
  /**< PCM Playback Stream Instance 7. */

  CSD2_STREAM_PCM_PLAYBACK_8,
  /**< PCM Playback Stream Instance 8. */

  CSD2_STREAM_PCM_PLAYBACK_9,
  /**< PCM Playback Stream Instance 9. */

  CSD2_STREAM_PCM_PLAYBACK_10,
  /**< PCM Playback Stream Instance 10. */

  CSD2_STREAM_PCM_LL_PLAYBACK,
  /**< Low latency PCM Playback Stream Instance 1. */

  CSD2_STREAM_PCM_LL_PLAYBACK_2,
  /**< Low latency PCM Playback Stream Instance 2. */

  CSD2_STREAM_PCM_LL_PLAYBACK_3,
  /**< Low latency PCM Playback Stream Instance 3. */

  CSD2_STREAM_PCM_LL_PLAYBACK_4,
  /**< Low latency PCM Playback Stream Instance 4. */

  CSD2_STREAM_PCM_RECORD,
  /**< PCM Record Stream Instance 1. */

  CSD2_STREAM_PCM_RECORD_INSTANCE_1,
  /**< PCM Record Stream Instance 1. */
  
  CSD2_STREAM_PCM_RECORD_1,
  /**< PCM Record Stream Instance 1. */
  
  CSD2_STREAM_PCM_RECORD_2,
  /**< PCM Record Stream Instance 2. */
  
  CSD2_STREAM_PCM_HFP_RX_CAPTURE,

  CSD2_STREAM_PCM_HFP_TX_CAPTURE,

  CSD2_STREAM_PCM_LOOPBACK,
  /**< PCM Loopback Stream Instance 1. */

  CSD2_STREAM_COMPRESS_OFFLOAD_PLAYBACK,
  /**< Offload Stream Instance 1. */
  
  CSD2_STREAM_PCM_MDF_PLAYBACK_1,
  /**< pcm mdf playback stream instance 1. */

  CSD2_STREAM_PCM_MDF_PLAYBACK_2,
  /**< PCM mdf Playback Stream Instance 2. */

  CSD2_STREAM_PCM_MDF_PLAYBACK_3,
  /**< PCM mdf Playback Stream Instance 3. */
  
  CSD2_STREAM_RANGE_END = CSD2_STREAM_TYPE_END,
  /**< Indicates end of a valid Stream. */
} csd2_stream_t;

/**
  Defines available Stream postprocessing effect nodes with the following
  terms:
   - Stream PP Rx: Stream postprocessing effect applied after StreamRx node.
   - Stream PP Tx: Stream postprocessing effect applied before StreamTx node.
 */
typedef enum {
    CSD2_STREAM_PP_RANGE_BEGIN = CSD2_STREAM_PP_TYPE_BEGIN,
    /**< Start of valid STREAM_PP node definition. */

    CSD2_STREAM_PP_RANGE_END = CSD2_STREAM_PP_TYPE_END,
    /**< End of valid STREAM_PP definition. */
} csd2_stream_pp_t;

/**
  Defines available Stream Device effect nodes.

  The Stream Device node applies additional processing
  to stream before output to the device.
 */
typedef enum {
    CSD2_STREAM_DEVICE_RANGE_BEGIN = CSD2_STREAM_DEVICE_TYPE_BEGIN,
    /**< Start of valid StreamDevice node.*/

    CSD2_STREAM_DEVICE_RANGE_END = CSD2_STREAM_DEVICE_TYPE_END,
    /**< End of valid StreamDevice node definition. */
} csd2_stream_device_t;

/**
  Defines available Device postprocessing effect nodes with the following
  terms:
   - DevicePP_RX Node: Per device postprocessing effect before playback to
     DeviceRx.
   - DevicePP_TX Node: Per device postprocessing effect after capture from
     DeviceTx.
 */
typedef enum {
    CSD2_DEVICE_PP_RANGE_BEGIN = CSD2_DEVICE_PP_TYPE_BEGIN,
    /**< Start of valid DevicePP node definition. */

    /*DevicePP_Rx*/
    CSD2_DEVICE_PP_RX_DEFAULT,
    /**< DevicePP Rx with default processing. */
    CSD2_DEVICE_PP_RX_AUDIO_MBDRC,
    /**< DevicePP Rx with multiband dynamic range control (MBDRC) processing. */

    /*DevicePP_Tx*/
    CSD2_DEVICE_PP_TX_AUDIO_FLUENCE_SMECNS,
    /**< DevicePP Tx with single-mic fluence processing. */

    CSD2_DEVICE_PP_RANGE_END = CSD2_DEVICE_PP_TYPE_END,
    /**< End of valid DevicePP node definition. */
} csd2_device_pp_t;

/**
  Defines available Device nodes with the following terms:
   - DeviceRx node: Device for playback.
   - DeviceTx node: Device for capture.

  Device node is a mandatory node from the HLOS Graph view. The interface
  selected by this Device node can be customized in ACDB.
 */
typedef enum {
    CSD2_DEVICE_RANGE_BEGIN = CSD2_DEVICE_TYPE_BEGIN,
    /**< Start of valid Device definition. */

    /*Dummy Clk */
    CSD2_DEVICE_PRI_CLK,
    /**< Clk Device that enables Primary TDM interface clk. */
    CSD2_DEVICE_SEC_CLK,
    /**< Clk Device that enables Secondary TDM interface clk. */
    CSD2_DEVICE_TERT_CLK,
    /**< Clk Device that enables Tertiary TDM interface clk. */
    CSD2_DEVICE_QUAT_CLK,
    /**< Clk Device that enables Quaternary TDM interface clk. */
    CSD2_DEVICE_QUIN_CLK,
    /**< Clk Device that enables Quinary TDM interface clk. */
    CSD2_DEVICE_SEN_SINK,
    /**< Clk Device that enables Senary TDM interface clk. */
    CSD2_DEVICE_SEP_SINK,
    /**< Clk Device that enables Septenary TDM interface clk. */
    CSD2_DEVICE_HS_IF0_SINK,
    /**< Clk Device that enables HS IF0 TDM interface clk. */
    CSD2_DEVICE_HS_IF1_SINK,
    /**< Clk Device that enables HS IF1 TDM interface clk. */
    CSD2_DEVICE_HS_IF2_SINK,
    /**< Clk Device that enables HS IF2 TDM interface clk. */
    CSD2_DEVICE_HS_IF3_SINK,
    /**< Clk Device that enables HS IF3 TDM interface clk. */
    CSD2_DEVICE_HS_IF4_SINK,
    /**< Clk Device that enables HS IF4 TDM interface clk. */

    /* DeviceRx */
    CSD2_DEVICE_MEDIA_SPKR,
    /**< Playback Device for Media speaker */
    CSD2_DEVICE_NAVI_SPKR,
    /**< Playback Device for Navigation speaker. */
    CSD2_DEVICE_A2B_SPKR,
    /**< Playback Device for A2B Bus speaker. */
    CSD2_DEVICE_A2B2_SPKR,
    /**< Playback Device for 2nd A2B Bus speaker. */
    CSD2_DEVICE_BT_RX,
    /**< Playback Device for BT speaker. */

    /* DeviceTx */
    CSD2_DEVICE_RECORD_MIC,
    /**< Captures Device for mic input. */
    CSD2_DEVICE_A2B_MIC,
    /**< Captures Device for A2B Bus mic input. */
    CSD2_DEVICE_A2B2_MIC,
    /**< Captures Device for A2B2 Bus mic input. */
    CSD2_STREAM_BT_TX_1,
    /**< PCM Record Stream Instance 1. */
    CSD2_STREAM_BT_TX_2,
    /**< PCM Record Stream Instance 1. */
    CSD2_DEVICE_SEN_SOURCE,
    /**< Captures Device for SEN Bus mic input. */
    CSD2_DEVICE_SEP_SOURCE,
    /**< Captures Device for SEP Bus mic input. */
    CSD2_DEVICE_HS_IF0_SOURCE,
    /**< Captures Device that enables HS IF0 Bus mic input. */
    CSD2_DEVICE_HS_IF1_SOURCE,
    /**< Captures Device that enables HS IF1 Bus mic input. */
    CSD2_DEVICE_HS_IF2_SOURCE,
    /**< Captures Device that enables HS IF2 Bus mic input. */

    CSD2_DEVICE_RANGE_END = CSD2_DEVICE_TYPE_END,
    /**< End of valid Device definition. */
} csd2_device_t;
/** @} *//* end_addtogroup csd2_node_datatypes */

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* CSD2_OEM_TYPES_H */
