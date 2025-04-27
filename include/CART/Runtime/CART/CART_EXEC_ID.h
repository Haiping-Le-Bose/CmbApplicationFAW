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
 * @file CART_EXEC_ID.h
 * 
 * @ingroup CART_EXEC_ID
 *
 * @brief Implementation of the Enumeration CART_EXEC_ID       
 *
 * @author: cb1037694                     
 ****************************************************/

#if !defined(BC_CART_EXEC_ID__INCLUDED_)
#define BC_CART_EXEC_ID__INCLUDED_


#ifdef __cplusplus
extern "C" {
#endif


/**
 * @ingroup CART_EXEC_ID
 *
 * @brief @author cb1037694
 * 
 * @version 1.1
 */
typedef enum
{
  /**
   * @ingroup CART_EXEC_ID
   *
   * @brief Default exec id.
   */
   CART_EXEC_ID_DEFAULT,
  /**
   * @ingroup CART_EXEC_ID
   *
   * @brief Bose Audio Controller exec id.
   */
   CART_EXEC_ID_BACR = CART_EXEC_ID_DEFAULT,
  /**
   * @ingroup CART_EXEC_ID
   *
   * @brief RMDL exec id.
   */
   CART_EXEC_ID_RMDL, /* exec id for rmdl state machine */
  /**
   * @ingroup CART_EXEC_ID
   *
   * @brief Input Eq exec id.
   */
   CART_EXEC_ID_INPUTEQ,
  /**
   * @ingroup CART_EXEC_ID
   *
   * @brief State Save state machine exec id.
   */
   CART_EXEC_ID_STATE_SAVE,
  /**
   * @ingroup CART_EXEC_ID
   *
   * @brief State Restore state machine exec id.
   */
   CART_EXEC_ID_STATE_RESTORE,
  /**
   * @ingroup CART_EXEC_ID
   *
   * @brief Number of defined CART EXEC ID values
   */
   CART_EXEC_ID_NUM /* exec id defining the number of defined values */
} CART_EXEC_ID;


#ifdef __cplusplus
}
#endif


#endif /*!defined(BC_CART_EXEC_ID__INCLUDED_)*/
