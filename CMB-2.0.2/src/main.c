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
 * @file main.c
 *
 * @brief Implementation of the application to
 * demostrate and test CART Message Bus and adaptors.
 ****************************************************/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <stddef.h>
#include <stdarg.h>

#include "CMB_BRF_Adaptor_Config.h"
//#include "RNC_CART_Callbacks.h"
#include "CMB_Framework.h"
#include "CMB_Framework_config.h"

#define LOG_STR                 "IP6-test: "
#define BDP_CMD_STR_MAX_LEN     (1024 - 1)

#ifndef INPUT_CMD_FILE_PATH
#define INPUT_CMD_FILE_PATH        "/mnt/data/interactive-usage"
#endif

extern CMB_Framework_config frameworkConfig[MAX_FRAMEWORK_CONFIGS];
//extern CMB_BRF_RNDB_Proxy_Config asmBrfParams;

// Index into command array to send the next command message.
uint8_t i = 0;

// Dont query any TOP and TSP commands at the beginning.
uint8_t loopCount = 0;

size_t getNextBdpCommand( char* bdpCommand )
{
    size_t totalSize = 0;

    FILE* fpInteractive = fopen(INPUT_CMD_FILE_PATH, "rb");

    if (NULL == fpInteractive)
    {
        printf("\t Ingress command file does not exist %s. Exiting.", INPUT_CMD_FILE_PATH);

        totalSize = 1;
        bdpCommand[0] = 'q';
    }
    else
    {
        char readDone = 0;

        // Interactive mode. Expect commands from user. 'q' to quit this application.
        //printf("%s present. Begin interactive mode. Enter 'q' to quit interactive mode in the file. ", INPUT_CMD_FILE_PATH);
        size_t numberBytes = 0;

        if ((numberBytes  =  fread(bdpCommand, 1, BDP_CMD_STR_MAX_LEN - 1, fpInteractive)) != 0)
        {
            bdpCommand[numberBytes - 1] = '\r';

            bdpCommand[numberBytes] = '\0';

            totalSize += numberBytes;

            printf("\t Ingress command %s. Sz %lu.", bdpCommand, totalSize);

            readDone = 1;
        }

        fclose(fpInteractive);

        fpInteractive = NULL;

        // Remove the entry from the file.
        if (1 == readDone)
        {
            fpInteractive = fopen(INPUT_CMD_FILE_PATH, "wb");
            fclose(fpInteractive);
        }
    }

    return totalSize;
}

CART_Cmd_Ret getUserCmd(uint8_t* reqBuffer, const uint32_t bufferMaxLength, ssize_t* dataSize)
{
    // Return CART_STATUS_DISCONNEDTED to end application processing.
    CART_Cmd_Ret retVal = {CART_STATUS_SUCCESS};

    // Example to send fixed BDP messages. Instead of getting commands from Android UI or head unit.
    // And translating them to BDP.
    *dataSize = 0;

    // Send a couple of BDP message.
    if (loopCount > 0)
    {
        loopCount--;

        // BDP command for volume.
        //char volume[2][16] = {"*AV0000",  "*AV00FF"};
        char query[2][20] = {"?DtA10002C4000001", "?Dt50fb0000000001"};

        query[0][17] = '\r';
        query[0][18] = '\0';

        query[1][17] = '\r';
        query[1][18] = '\0';

        uint32_t payloadsize = 20;

        if (bufferMaxLength > payloadsize)
        {
            char* cmd = query[i];

            memcpy(reqBuffer, cmd, payloadsize);

            *dataSize = payloadsize;

            // Toggle for next command.
            if (0 == i)
                i = 1;
            else
                i = 0;
        }
        else
        {
            // Request buffer too small for command to be sent.
            *dataSize = 0;
        }
    }
    else
    {
        char bdpCommand[BDP_CMD_STR_MAX_LEN] = {};

        ssize_t size = 0;

        if (0 == (size = getNextBdpCommand(bdpCommand)))
        {
            // Do nothing.
        }
        else
        {
            // Does any BDP command start with lower case q?
            if ('q' == bdpCommand[0])
            {
                retVal.status = CART_STATUS_DISCONNECTED;
            }
            else if (bufferMaxLength > BDP_CMD_STR_MAX_LEN)
            {
                printf("\n\t User entered: %s. sz %lu.", bdpCommand, size);

                memcpy(reqBuffer, bdpCommand, size);

                *dataSize = size;
            }
            else
            {
                // Request buffer too small for command to be sent.
                *dataSize = 0;
            }
        }
    }

    return retVal;
}

CART_Cmd_Ret sendResponse(uint8_t* payload, uint32_t size)
{
    CART_Cmd_Ret retVal = {CART_STATUS_SUCCESS};

    printf("ACS_sendCallback Response: Payload %s Size %u.\n",
           (0 == payload) ? "NULL" : (char*)payload, size);

    // Translate BDP to Head Unit format.
    return retVal;
}

void showUsage()
{
    printf("\n Usage: -n [0|1|2] -t [0|1] -c [0|1|2|3] -i[Time in usec] -s[1|2] -a[1|0] -l[0|1|2|3|4|5|6]\n");
    printf("\t c: Accept control application (AATMA) connection. \n");
    printf("\t n: Use case: 0 Neutrino A2B, 1 Neutrino NXP, 2 Linux A2B. \n");
    printf("\t i: Time Interval, in micro-seconds, for periodic task, including polling for notification. \n");
    printf("\t s: Socket Type: 1 TCP, 2 UDP. \n");
    printf("\t a: Poll APX adaptor for notifications: 0 Disable (default), 1 Enable. \n");
    printf("\t t: Accept tuning application (Ducttape) connection. \n");
    printf("\t l: Log level: 0 Disable, 1 Critical, 2 Error, 3 Warning, 4 Info, 5 Debug, 6 Verbose. \n");
    printf("\t h: Display the usage. \n");
    printf("\t To exit application: echo q > /mnt/data/interactive-usage \n");
}

CART_STATUS parseArgs(int argc, char *argv[], CMB_Framework_params* params)
{
    CART_STATUS retVal = CART_STATUS_SUCCESS;

    int c = 0;

    uint8_t configurationTableIndex = 5;

    while(-1 != (c = getopt( argc, argv, "hc:n:i:l:s:t:a:r:d:" )))
    {
        switch( c )
        {
            case 'd':
            {
                if (0 != optarg)
                {
                    printf("PCM device name  = %s\n", optarg);

                    memcpy(params->sndPcmDeviceName, optarg, SND_PCM_DEVICE_NAME_LEN);
                }
                else
                {
                    memset(params->sndPcmDeviceName, 0, SND_PCM_DEVICE_NAME_LEN);
                }
                break;
            }

            case 'c':
            {
                if (0 != optarg)
                {
                    printf("(AATMA) Control connection  = %s\n", optarg);

                    params->enableControlAppConnection = atoi(optarg);
                }
                else
                {
                    params->enableControlAppConnection = 0;
                }
                break;
            }

            case 'n':
            {
                if (0 != optarg)
                {
                    printf("Use case # %s.\n", optarg);

                    configurationTableIndex = atoi(optarg);
                }
                else
                {
                    configurationTableIndex = 0;
                }


                configurationTableIndex = (configurationTableIndex <  MAX_FRAMEWORK_CONFIGS) ?
                                      configurationTableIndex : 0;

                memcpy(&params->configuration, &frameworkConfig[configurationTableIndex], sizeof(params->configuration)); 

                break;
            }

            case 's':
            {
                if (0 != optarg)
                {
                    params->socketType = atoi(optarg);
                }
                else
                {
                    params->socketType = 0;
                }

                // Check input value.
                if (2 < params->socketType)
                {
                    params->socketType = 2;
                }

                printf("Socket connection type = %u.\n", params->socketType);

                break;
            }

            case 'l':
            {
                if (0 != optarg)
                {
                    params->logLevel = atoi(optarg);
                }
                else
                {
                    params->logLevel = 5;
                }

                // Check input value.
                if (6 < params->logLevel)
                {
                    params->logLevel = 6;
                }

                printf("Log level = %u.\n", params->logLevel);

                break;
            }

            case 't':
            {
                if (0 != optarg)
                {
                    printf("(Ducttape) Tuning connection  = %s\n", optarg);
                    params->enableTuningAppConnection = atoi(optarg);
                }
                else
                {
                    params->enableTuningAppConnection = 0;
                }
                break;
            }

            case 'i':
            {
                if (0 != optarg)
                {
                    printf("Periodic task time interval (us)  = %s\n", optarg);

                    params->periodicWorkInterval = atoi(optarg);
                }
                else
                {
                    params->periodicWorkInterval = 1000;
                }
                break;
            }

            case 'r':
            {
                if (0 != optarg)
                {
                    // printf("AMS graph use case ID  = %s\n", optarg);
                    // Find a way to id the adaptor that will consume this runtime.
                    //params->periodicWorkInterval = 3; // atoi(optarg);
                }
                else
                {
                    //params->periodicWorkInterval = 3;
                }
                break;
            }

            case 'a':
            {
                if (0 != optarg)
                {
                    printf("Poll APX baf  = %s\n", optarg);
                    params->pollApxBaf = atoi(optarg);
                }
                else
                {
                    params->pollApxBaf = 0;
                }
                break;
            }

            case 'h':
            case '?':
            {
                showUsage();
                break;
            }
        }
    }

    printf("\n");

    return retVal;
}

#define CHECKSUM_CMB_APP "md5 /mnt/data/Cmb_application.out"
#define CHECKSUM_ACDB    "md5 /mnt/etc/acdb/*/*"
#define CHECKSUM_BTF_DLL "md5 /mnt/lib64/libBtf_dll.so"
#define CHECKSUM_BCF_DLL "md5 /mnt/lib64/libBcf_dll.so"
#define CHECKSUM_BRF_DLL "md5 /mnt/lib64/libBrf_dll.so"
#define CHECKSUM_ACDBS "md5 /mnt/lib64/libBrf_dll.so"

#define CHECKSUM_BTF_ASM_DLL "md5 /mnt/lib64/libBtf_asm_dll.so"
#define CHECKSUM_BCF_ASM_DLL "md5 /mnt/lib64/libBcf_asm_dll.so"
#define CHECKSUM_BRF_ASM_DLL "md5 /mnt/lib64/libBrf_asm_dll.so"

#define CHECKSUM_CMB_ADAPTOR "md5 /mnt/lib64/*Adaptor*.so"
#define CHECKSUM_CMB_LIB "md5 /mnt/lib64/*Cmb*.so"

#define CHECKSUM_BAF_APX "md5 /mnt/lib64/lib_bose.so"
#define CHECKSUM_RNDB_APP "md5 /mnt/data/RNDB.bin"
#define CHECKSUM_FFDB_APP "md5 /mnt/data/FFDB.bin"

#define CHECKSUM_RNDB_ASM_APP "md5 /mnt/data/RNDB_asm.bin"
#define CHECKSUM_FFDB_ASM_APP "md5 /mnt/data/FFDB_asm.bin"


void applicationSpecificInitializaion()
{
#ifdef CMB_CMD_PIPE
    system("touch /mnt/data/interactive-usage");
#endif

#ifdef MD5_CHECKSUM
    system(CHECKSUM_CMB_APP);
    system(CHECKSUM_CMB_LIB);
    system(CHECKSUM_CMB_ADAPTOR);

    system(CHECKSUM_ACDB);

    system(CHECKSUM_BAF_APX);

    // ENT
    system(CHECKSUM_BTF_DLL);
    system(CHECKSUM_BCF_DLL);
    system(CHECKSUM_BRF_DLL);
    system(CHECKSUM_RNDB_APP);
    system(CHECKSUM_FFDB_APP);

    // RNC
    // system(CHECKSUM_BTF_ASM_DLL);
    // system(CHECKSUM_BCF_ASM_DLL);
    // system(CHECKSUM_BRF_ASM_DLL);
    // system(CHECKSUM_RNDB_ASM_APP);
    // system(CHECKSUM_FFDB_ASM_APP);
#endif

    // RNC_BRF_initialize(asmBrfParams);
    //RNC_BRF_initialize((CMB_BRF_RNDB_Proxy_Config*)frameworkConfig[5].adaptorList[2].proxyList[1].configuration);
}

void applicationSpecificDeinitializaion()
{
   // RNC_BRF_deinitialize();
}

void CMB_printf(int logLevel)
{
    // todo logLevel enum.
}

int main(int argc, char *argv[])
{
    /* CMB_printf */ printf("8295 application to demonstrate CART, CMB and Adpators %d.\n");
    
    CART_Cmd_Ret retVal = {CART_STATUS_SUCCESS};

    CMB_Framework_context config;

    memset((void*)&config, 0, sizeof(config));

    // Set to 100 msec as default.
    config.params.periodicWorkInterval = 100000;

    config.params.pollApxBaf = 0;

    // Configure the CMB library to use the default value with which it was compiled.
    memset(config.params.sndPcmDeviceName, 0, SND_PCM_DEVICE_NAME_LEN);

    if (CART_STATUS_SUCCESS != parseArgs(argc, argv, &config.params))
    {
        showUsage();

        exit(0);
    }

    applicationSpecificInitializaion();

    config.creater_id = CART_ID_HEAD_UNIT;

    // Create should be seperate. Another API that supplies the ID and receives the handle.
    CMB_Framework_handle handle = 0;

    retVal.status = CMB_Framework_create(&config, &handle);

    if ((0 == handle) || (CART_STATUS_SUCCESS != retVal.status))
    {
        printf("Error in CMB_Framework_create: handle %llx ret %d.\n", handle, retVal.status);
    }
    else
    {
        printf("Read user commands from %s.\n", INPUT_CMD_FILE_PATH);
        
        // This callback is used to send the CART_STATUS_DISCONNECTED message that
        // will cause the CMB_Framework_exec() to return. And allow the application
        // to gracefully exit by calling CMB_Framework_destroy().
        retVal = CMB_Framework_register_recv(&handle, getUserCmd);

        if (CART_STATUS_SUCCESS != retVal.status)
        {
            printf("CMB_Framework_register_recv failed with %d. \n", retVal.status);
        }
        else
        {
            // Only needed for side entry of commands for testing.
            retVal = CMB_Framework_register_send(&handle, sendResponse);

            if (CART_STATUS_SUCCESS != retVal.status)
            {
                printf("CMB_Framework_register_send failed with %d. \n", retVal.status);
            }
            else
            {
                CMB_Framework_exec(&handle);

                CMB_Framework_destroy(&handle);
            }
        }
    }

    applicationSpecificDeinitializaion();

    printf("CMB application done. Exiting. \n");

    return 0;
}
