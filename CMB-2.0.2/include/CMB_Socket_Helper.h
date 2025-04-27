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
 * @file CMB_Socket_helper.h
 *
 * @brief Header file for socket related functions needed by CMB
 *  and its adaptors.
 *
 ****************************************************/

#if !defined(CMB_SOCKET_HELPER__INCLUDED_)
#define CMB_SOCKET_HELPER__INCLUDED_

#include "winsock2.h"
#include "ws2ipdef.h"
#include "ws2tcpip.h"

#include "CMB_Socket_Types.h"

#ifdef __cplusplus
extern "C" {
#endif

CART_STATUS Adaptor_udp_init(const Adaptor_socket_cfg* cfg,  int* fileDescriptor);

CART_STATUS Adaptor_tcp_init(const Adaptor_socket_cfg* cfg,  int* fileDescriptor);

CART_Cmd_Ret Adaptor_udp_sendMessage(int fd, const void* buffer, const size_t len, const struct sockaddr* to, socklen_t tolen);

CART_Cmd_Ret Adaptor_tcp_sendMessage(int fd, const void* buffer, const size_t len);

CART_Cmd_Ret Adaptor_udp_recv(int fd, uint8_t* buffer, const uint32_t len, ssize_t* recv_length);

CART_Cmd_Ret Adaptor_tcpConnect(char* ip, int32_t port);

#ifdef __cplusplus
}
#endif

#endif /*!defined(CMB_SOCKET_HELPER__INCLUDED_)*/
