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
 * @file CMB_Message_Helper.h
 *
 * @brief Header file for CART message helper functions needed by CMB
 *  and its adaptors.
 *
 ****************************************************/

#if !defined(CMB_MESSAGE_HELPER__INCLUDED_)
#define CMB_MESSAGE_HELPER__INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#define CART_ENDIAN_SWAP32(id)              ((((id)&0xFF000000UL)>>24) | (((id)&0x00FF0000UL)>>8) | (((id)&0x0000FF00UL)<<8) | (((id)&0x000000FFUL)<<24))

#define CART_ENDIAN_SWAP16(id)              ((((id)&0xFF00U)>>8) | (((id)&0x00FF)<<8))

#include "CART_Message.h"

uint8_t CMB_Message_isProcessingPending(uint8_t* payload, uint32_t size);

uint8_t CMB_Message_isDestinationValid(CART_Message* msg);

void CMB_Message_log(CART_Message* msg, const char* text, uint32_t arg);

CART_STATUS CMB_Message_setMessageForPayload(CART_Message* msg, const CART_MESSAGE_TYPE type,
                                             const CART_MESSAGE_ID srcid, const CART_MESSAGE_ID dstid,
                                             unsigned char * payload, const uint32_t payloadSize);

CART_STATUS byteArray2HexString ( uint8_t BIN_in, uint8_t *pASCIIh_out );

#ifdef __cplusplus
}
#endif

#endif /*!defined(CMB_MESSAGE_HELPER__INCLUDED_)*/
