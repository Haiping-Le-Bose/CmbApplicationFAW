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
 * @file ams_wrapper.h
 *
 * @brief Header file for interacting with AMS 
 * framework.
 *
 ****************************************************/

#ifndef _AMS_WRAPPER__H_
#define _AMS_WRAPPER__H_


#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "mmdefs.h"

#ifdef __cplusplus
extern "C" {
#endif

#define BOSE_PARAM_MOD_ENABLE  0x1000B800
#define BOSE_PARAM_MESSAGE 0x1000B801
#define BOSE_PARAM_VERSION 0x1000B802

#define AMS_GRAPH_FLAGS 0
#define AMS_BLOCK_SIZE 24
#define AMS_PROCESSOR_ID 0
#define AMS_SAMPLE_RATE 48000

#define AMS_UC_MIN 1
#define AMS_UC_MAX 2
#define AMS_OPERATE_DEV_NUM_MAX 5

#define A2B_UC_MIN 1
#define A2B_UC_MAX 2

#define DSP_AMS_TS_PAIR 10
#define DSP_AMS_TS_PORT 2

typedef struct opt_args_a
{
    int block_size;
} opt_args_t;

typedef struct 
{
    uint32_t en;
    uint32_t dev_id;
    uint32_t sample_rate;
    uint32_t sample_width;
}ams_operate_dev_t;

typedef struct ams_timestamp
{
    uint64_t input_ts[DSP_AMS_TS_PAIR];
    uint64_t output_ts[DSP_AMS_TS_PAIR];
} ams_timestamp_t;

typedef struct ams_interface
{
    int (*start_ams)(uint32_t usecase);
    int (*set_params)(uint32_t paramID, uint8_t *data, uint32_t dataSize);
    int (*get_params)(uint32_t paramID, uint8_t *data, uint32_t *dataSize);
    int (*close_ams)();
} ams_interface_t;

//ams_interface_t ams_interface;
//opt_args_t opt_args;

#ifdef __cplusplus
}
#endif

#endif /* AMS_WRAPPER__H_ */
