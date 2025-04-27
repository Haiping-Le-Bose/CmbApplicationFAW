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
 * @file CMB_IO-AUDIO_Stub.h
 *
 * @brief Header file for io-audio stub for snd pcm driver.
 *
 ****************************************************/

#if !defined(CMB_IO_AUDIO_STUB__INCLUDED_)
#define CMB_IO_AUDIO_STUB__INCLUDED_

#include <stddef.h>

typedef enum
{
    E_DATA_CART_MESSAGE
} data_id_t;

typedef void snd_pcm_t;

typedef struct snd_afm_ap_param {
    uint32_t size;
    uint32_t dataId;
    int32_t  channel;
    int32_t  status;
} snd_pcm_apx_param_t;


typedef snd_pcm_apx_param_t snd_pcm_ap_param_t;

#define EOK 0
#define SND_PCM_OPEN_PLAYBACK 0
#define SND_PCM_STREAM_PLAYBACK SND_PCM_OPEN_PLAYBACK

#ifdef __cplusplus
extern "C"
{
#endif

int snd_pcm_open_preferred(snd_pcm_t **handle, int *rcard, int *rdevice, int mode);

int snd_pcm_set_apx_data(snd_pcm_t *pcm, uint32_t apx_id, snd_pcm_apx_param_t *param, const void *data);

int snd_pcm_get_apx_data(snd_pcm_t *pcm, uint32_t apx_id, snd_pcm_apx_param_t *param, void *data);

int snd_pcm_set_ap_data(snd_pcm_t *pcm, uint32_t apx_id, snd_pcm_ap_param_t *param, const void *data);

int snd_pcm_get_ap_data(snd_pcm_t *pcm, uint32_t apx_id, snd_pcm_ap_param_t *param, void *data);

int snd_pcm_close(snd_pcm_t *handle);


#ifdef __cplusplus
}
#endif

#endif /*!defined(CMB_IO_AUDIO_STUB__INCLUDED_)*/
