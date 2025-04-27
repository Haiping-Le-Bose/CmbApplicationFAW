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
 * @file CMB_Logger.h
 *
 * @brief Header file for logging functionality to be used by CMB
 *  and its adaptors.
 *
 ****************************************************/

#if !defined(CMB_LOGGER__INCLUDED_)
#define CMB_LOGGER__INCLUDED_

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

//#define Logger_log CMB_Logger_info

typedef enum
{
    CMB_LOG_FIRST = 0,
    CMB_LOG_DIABLE = CMB_LOG_FIRST,
    CMB_LOG_LEVEL_CRITICAL,
    CMB_LOG_LEVEL_ERROR,
    CMB_LOG_LEVEL_WARN,
    CMB_LOG_LEVEL_INFO,
    CMB_LOG_LEVEL_DEBUG,
    CMB_LOG_LEVEL_VERBOSE,
    CMB_LOG_LAST,
    CMB_LOG_COUNT = CMB_LOG_LAST - CMB_LOG_FIRST + 1,
} CMB_LOG_LEVEL;

void CMB_Logger_setLevel(CMB_LOG_LEVEL level);

// Used to indicate critical events that prevent functional operations.
int32_t CMB_Logger_critical(const char* fmt, ...);

// Indicate error, but system may still be functional. Example, error processing some but not all commands.
int32_t CMB_Logger_error(const char* fmt, ...);

// Warn for unexpected events or data, but may not be an error.
int32_t CMB_Logger_warn(const char* fmt, ...);

// Used to log information that is not error condition.
int32_t CMB_Logger_info(const char* fmt, ...);

// Enable for debugging. May affect performance by slowing down normal processing.
int32_t CMB_Logger_debug(const char* fmt, ...);

// Extra verbose. Significantly affects performance by slowing down normal processing.
int32_t CMB_Logger_verbose(const char* fmt, ...);

#ifdef __cplusplus
}
#endif

#endif /*!defined(CMB_LOGGER__INCLUDED_)*/
