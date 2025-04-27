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
 * @file CMB_Socket_Types.h
 *
 * @brief Header file for socket related data structures needed by CMB
 *  and its adaptors.
 *
 ****************************************************/

#if !defined(CMB_SOCKET_TYPES__INCLUDED_)
#define CMB_SOCKET_TYPES__INCLUDED_


#ifdef __cplusplus
extern "C" {
#endif
#include "CART_ID.h"

// Support IPv4 only. Modify for IPv6.
#define IP_ADDR_STR_MAX_LEN         200
#define SOCK_TYPE_TCP_SOCK_STREAM   1
#define SOCK_TYPE_UDP_SOCK_DGRAM    2

typedef struct Adaptor_socket_cfg
{
    char remoteIpAddr[IP_ADDR_STR_MAX_LEN];

    int32_t remotePort;

    char localIpAddr[IP_ADDR_STR_MAX_LEN];

    int32_t localPort;

    int maxConnections;

    uint8_t promptUserForIp;
} Adaptor_socket_cfg;


typedef struct Adaptor_Connection_cfg
{
    Adaptor_socket_cfg socket;

    int socketType;

    void* threadConfig;

    // SOCK_DGRAM vs SOCK_STREAM
    // backlog for IPPROTO_TCP if multiple connections are supported.
} Adaptor_Connection_cfg;


typedef struct
{
    CART_ID srcId;

    CART_ID dstId;

    Adaptor_Connection_cfg connection;

} Adaptor_Connection_Proxy_Config;

#ifdef __cplusplus
}
#endif

#endif /*!defined(CMB_SOCKET_TYPES__INCLUDED_)*/
