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
 * @file CMB_OSAL.h
 *
 * @brief Header file for abstracting OS API needed by CMB
 *  and its adaptors. This implementation is for POSIX threads. 
 *  If a different type of threads is needed by the operating system in which
 *  CMB is required to run in, a OSAL (OS Abstraction Layer)
 *  implementation is must be provided for that OS.
 *
 ****************************************************/

#if !defined(CMB_OSAL__INCLUDED_)
#define CMB_OSAL__INCLUDED_

// Windows specific Process ID information requires
// [Haiping] To avid include this header when building in Linux.
#ifdef _WIN32
#include "processthreadsapi.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    int32_t threadPriority;

    size_t stackSize;
} CMB_OSAL_Thread_config;

#include <pthread.h>
#include <semaphore.h>
#include <sched.h>

typedef void* (*CMB_OSAL_ThreadFunction)(void *);

#ifndef __cplusplus
#include <stdatomic.h>

typedef struct
{
    void* context;

    // Thread level and priority value will be different for pthreads.
    // For CART Adaptor, thread_level is of type CART_EXEC_ID.
    uint32_t thread_level;

    sem_t semaphore;

    unsigned char exec;

    //sem_t wait;

    volatile atomic_flag keepRunning;

    pthread_t threadHandle;

    uint8_t proxyId;
} CMB_OSAL_Thread_context;
#endif

#define CMB_OSAL_CONNECTION_RESET WSAECONNRESET

int CMB_OSAL_getLastError();

// Any OS specific initialization.
CART_STATUS CMB_OSAL_initialize();

// Any OS specific de-initialization.
CART_STATUS CMB_OSAL_deinitialize();

// This function creates a thread using parameters specified in CMB_OSAL_Thread_config.
CART_STATUS CMB_OSAL_threadCreate(CMB_OSAL_ThreadFunction func, CMB_OSAL_Thread_config *config, void* context);

CART_STATUS CMB_OSAL_threadExit(void* context);

CART_STATUS CMB_OSAL_threadJoin(void* handle); 

#ifdef __cplusplus
}
#endif

#endif /*!defined(CMB_OSAL__INCLUDED_)*/
