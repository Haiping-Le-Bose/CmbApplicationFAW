#ifndef DALSYSQNX_H
#define DALSYSQNX_H
/*==============================================================================
@file dalsysqnx.h

                  DAL System lib API Extensions for QNX

        Copyright (c) 2011,Qualcomm Technologies Incorporated.
        All Rights Reserved.
        Qualcomm Confidential and Proprietary

$Header: //source/qcom/qct/platform/qnp/qnx_core/AMSS/qal/dal/dalsys/public/amss/core/dalsysqnx.h#1 $
=============================================================================*/

/*------------------------------------------------------------------------------
* Include Files
*-----------------------------------------------------------------------------*/
#include "DALSys.h"

/*------------------------------------------------------------------------------
* Function declaration and documentation
*-----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif /* #ifdef __cplusplus */

/*
  @brief Registers the DALs specified by the directory driver_list

  This function allows DALs to be added to the dalsys directory table

  @param driver_list  : pointer of DALs within this module/DLL 

  @return nothing
*/
void
DALSYS_RegisterMod(DALREG_DriverInfoList *driver_list);

/*
  @brief Un-Registers the DALs specified by the directory driver_list

  This function allows DALs to be removed from the dalsys directory table

  @param driver_list  : pointer to directory of DALs to be removed

  @return nothing
*/
void
DALSYS_UnRegisterMod(DALREG_DriverInfoList *driver_list);


/*
  @brief Sets the DAL Remoting client and server vTbl

  This functions sets the vTbl in DALSys which also starts RDAL client/servers
  This function is only called by the RDAL dll.

  @param : pRDALVtbl pointer to vTbl

  @return result based on whether RDAL init was successful
*/

DALResult
DALSYS_SetRemoteInterfaceVtbl(DALRemoteVtbl * pRDALVtbl);

#ifdef __cplusplus
}
#endif /* #ifdef __cplusplus */

#endif /* DALSYSQNX_H */
