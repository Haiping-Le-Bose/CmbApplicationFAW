#ifndef __GSL_BE_H__
#define __GSL_BE_H__

/*
Copyright (C) 2019 Qualcomm Technologies Incorporated.
All rights reserved.
Qualcomm Confidential and Proprietary

$Header: //components/rel/audio.qxa_qa/2.0.c29/audio_ar/audio_driver/public/amss/multimedia/audio_driver_ar/gsl_be.h#1 $
$Author: mplcsds1 $
*/
#ifdef __cplusplus
extern "C" {
#endif

/**
Initializes the GSL BE.
*/
int32_t gsl_be_init ( void );

/**
De-initializes the GSL BE.
*/
int32_t gsl_be_deinit ( void );

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* __GSL_BE_H__ */
