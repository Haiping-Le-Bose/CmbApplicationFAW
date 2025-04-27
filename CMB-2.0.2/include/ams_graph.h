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
 * @file ams_struct.h
 *
 * @brief Header file for creating the AMS graph.
 *
 ****************************************************/


#ifndef _AMS_GRAPH_H_
#define _AMS_GRAPH_H_

#include <stdint.h>
#include "ams.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define STATIC_MODULE_ID              0x170010A6
#define DYNAMIC_MODULE_ID             0x1000B600
#define DYNAMIC_MULTI_PORT_MODULE_ID  0x170010AA
#define STATIC_PASSTHRU_MODULE_ID     0x00013378
#define DYNAMIC_PASSTHRU_MODULE_ID    0x070010A7

#define MAX_ENDPOINT_NUM 5
#define MAX_MODULE_NUM 5
#define MAX_CONNECTION_NUM 20
#define MAX_PROP_NUM 5
#define MAX_MSG_LINK_NUM 2

typedef enum
{
    ENDPOINT_1 = 1,
    ENDPOINT_2,
    ENDPOINT_3,
    ENDPOINT_4,
    MODULE_1,
    MODULE_2,
    CONNECTION_1,
    CONNECTION_2,
    CONNECTION_3,
    CONNECTION_4,
} graph1_id_e;

typedef struct
{
    uint8_t endpoint_nums;
    uint8_t module_nums;
    uint8_t connection_nums;
    uint8_t prop_nums;
    bool ch_mapping_manual;
    ams_msg_link_connection_t msg_link[MAX_MSG_LINK_NUM];
    ams_endpoint_t endpoint[MAX_ENDPOINT_NUM];
    ams_module_t module[MAX_MODULE_NUM];
    ams_connection_t connection[MAX_CONNECTION_NUM];
    ams_graph_property_t graph_prop[MAX_PROP_NUM];
} graph_config_t;

graph_config_t *get_graph_config(int use_case);
void create_graph_1(void);
void create_graph_2(void);

#define CHANNEL_MAPPING_GENERAL \
    .ch_mapping_manual = false,

#define CHANNEL_MAPPING_MANUAL \
    .ch_mapping_manual = true,

#ifdef __cplusplus
}
#endif

#endif // _AMS_GRAPH_H_
