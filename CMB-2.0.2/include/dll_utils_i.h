/*==========================================================================

  @file dll_utils_i.h 
  
  @brief: Contains external API interface to dll_utils

  @Copyright © 2012-2013 QUALCOMM Technologies Incorporated.
               All Rights Reserved.
               QUALCOMM Proprietary/GTDR
==========================================================================*/

/*==========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header$

when       who          what, where, why
--------   ---       ------------------------------------------------------
04/10/13   rohitn    Added loaddll_ext & init_daldir_by_names
10/25/12   rohitn    Added init_hwio_bases()
02/13/12   jsanpedr  Intial draft created.
==========================================================================*/
#ifndef DLL_UTILS_I_H_
#define DLL_UTILS_I_H_

#include "dalsysqnx.h"
#include "DalDevice.h"
#include <sys/procmgr.h>
#include <libgen.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

#define LOG_ENV                        "LOG_TO_CONSOLE"

/**
   @brief Resource_Daemonize - Run the given process in background
*/
static inline void Resource_Daemonize(void) {
    int flags = PROCMGR_DAEMON_KEEPUMASK | PROCMGR_DAEMON_NOCLOSE;
    char* log_env = getenv( LOG_ENV );
    
    if ( log_env && log_env[0]){
        flags |= PROCMGR_DAEMON_NODEVNULL ;
    }

    (void) procmgr_daemon( EOK , flags );
};


/**
   @brief Resource_BlockWait - Perform a block call that will unblock
   once a resource is available

   @param resourceName : Name of the resouce to wait for
   
   @return :
           0    SUCCESS
           -1   Failure
*/
static inline int Resource_BlockWait ( const char * resourceName ){
    int delay_ms = 100;
#if defined(__TOOLCHAIN_HYP710__) || defined(__TOOLCHAIN_QNX710__)
    while ( waitfor_attach( resourceName , delay_ms )){
#else
    int poll_ms = 10;
    while ( waitfor( resourceName , delay_ms, poll_ms )){
#endif
        if ( delay_ms > (60 * 60 * 1000)) {
            //There is no hope for this path to become available after an hour , 
            //block indefinitely now.
            pause () ;  
        }
        delay_ms *= 2;
#if defined(__TOOLCHAIN_HYP710__) || defined(__TOOLCHAIN_QNX710__)
        // null
#else
        poll_ms *= 2;
#endif
    }
    return EOK;
}


/**
   @brief Resource_Free - Indicate that process is free and available
   
   This is used in junction with Resource_BlockWait. Once Resource_Free
   is called, all users who have called Resource_BlockWait will check
   to see if the resource they are waiting for is available. Otherwise,
   they will continue to block.
  
   @return :
           0    SUCCESS
           -1   Failure
*/
static inline int Resource_Free ( void )  {
    return EOK;
}


/**
   @brief loaddll - Dynamically load a dll into a process
   
   @param input_dllname : Name of the dll
                  init_func_name : Name of the function within the dll
                  cmd_line_args : Pass in arguments for the function to call
                  err_msg : Error message
                  glbsyms : Search for global symbols
   
   @return :
           Success  The return value of the executed function
           -1           Failure
*/
int loaddll(const char * input_dllname, const char * init_func_name, const char * cmd_line_args, char * err_msg, int glbsyms);


/**
   @brief unloaddll - Remove a dll from a process
   
   @param dllname : Name of the dll
                  deinit_func_name : Name of the function within the dll
                  cmd_line_args : Pass in arguments for the function to call
                  glbsyms : Search for global symbols
   
   @return :
           0            Success
           -1           Failure
*/
int unloaddll(const char * dllname, const char * deinit_func_name, const char * cmd_line_args,  int glbsyms);


/**
   @brief dynscript_execute - Execute a function within a process
   
   @param progname - Program Name
              dynscript_fname - Name of function
   
   @return :
           > 0          Success
           -1           Failure
*/
int dynscript_execute (const char * progname, const char *dynscript_fname);

#endif /* DLL_UTILS_H_ */
