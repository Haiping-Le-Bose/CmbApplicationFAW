/**
 * \file include/asound_qnx.h
 * \brief Application interface library for the ALSA driver
 * \date 2024
 *
 * Application interface library for the ALSA driver (QNX specific definitions)
 */
/*
 *   This library is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU Lesser General Public License as
 *   published by the Free Software Foundation; either version 2.1 of
 *   the License, or (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU Lesser General Public License for more details.
 *
 *   You should have received a copy of the GNU Lesser General Public
 *   License along with this library; if not, write to the Free Software
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#ifndef __ASOUND_QNX_H
#define __ASOUND_QNX_H

#include <sys/mman.h>

/*****************/
/***  CONTROL  ***/
/*****************/
/*****************/

/* Commands for AFM and CM control events (struct snd_ctl_event) */
#define SND_CTL_READ_AFM_STATE      126
#define SND_CTL_READ_AFM_AUDIO_MODE 127
#define SND_CTL_READ_AFM_DATASET    128
#define SND_CTL_READ_AFM_DETECT     129
#define SND_CTL_READ_CM_STATUS_CHG  130

typedef struct snd_pcm_stream_cm_info
{
    pid_t     pid;           /* Client process id      */
    uint32_t  prio;          /* Concurrency Management priority level */
    uint32_t  state;         /* Concurrency Management state SND_PCM_CM_STATE_*  */
    uint32_t  ducked_by;
#define SND_PCM_DUCKED_BY_SAME_PRIO    (1<<0)
#define SND_PCM_DUCKED_BY_HIGHER_PRIO  (1<<1)
#define SND_PCM_DUCKED_BY_NONTRANSIENT (1<<2)
    char      name[32];      /* Sound type name     */
}snd_pcm_stream_cm_info_t;

typedef struct snd_pcm_cm_priority_status {
    int      nstreams;                    /* Number of streams at this priority */
    snd_pcm_stream_cm_info_t streams[];   /* Variable array of stream structures */
} snd_pcm_cm_priority_status_t;

typedef struct snd_event_filter
{
    uint32_t    enable;             /* bitfield created using SND_*_EVENT_MASK() */
    uint8_t     reserved[124];      /* must be filled with zero */
} snd_event_filter_t;


/* Output classes - used for DRM purposes */
#define     SND_OUTPUT_CLASS_UNKNOWN                0
#define     SND_OUTPUT_CLASS_SPEAKER                1
#define     SND_OUTPUT_CLASS_HEADPHONE              2
#define     SND_OUTPUT_CLASS_LINEOUT                3
#define     SND_OUTPUT_CLASS_BLUETOOTH              4
#define     SND_OUTPUT_CLASS_HDMI                   5
#define     SND_OUTPUT_CLASS_TOSLINK                6
#define     SND_OUTPUT_CLASS_MIRACAST               7
#define     SND_NUM_OUTPUT_CLASSES                  8

/*****************/
/*****************/
/***    PCM    ***/
/*****************/
/*****************/

/* Concurrency Management states */
#define SND_PCM_CM_STATE_INACTIVE          (0x00)    /* Concurrency Management inactive */
#define SND_PCM_CM_STATE_ACTIVE            (1U<<0)   /* Concurrency Management active due to stream active */
#define SND_PCM_CM_STATE_HARD_SUSPENDED    (1U<<1)   /* Cannot be unsuspended via resume API */
#define SND_PCM_CM_STATE_SOFT_SUSPENDED    (1U<<2)   /* Can be unsuspended via resume API */
#define SND_PCM_CM_STATE_PAUSED            (1U<<3)   /* state will transition to SND_PCM_STATE_PAUSED on unsuspended */
#define SND_PCM_CM_STATE_FORCED_ACTIVE     (1U<<4)   /* Concurrency Management active due snd_pcm_concurrency_management() API */
#define SND_PCM_CM_STATE_MUTE_BY_HIGHER    (1U<<5)
#define SND_PCM_CM_STATE_MUTE_BY_SAME      (1U<<6)
#define SND_PCM_CM_STATE_DUCKED            (1U<<7)

/* Sound Management PCM events */
typedef struct snd_pcm_state_event
{
    int      old_state;
    int      new_state;
    uint32_t flags;                                   /* Additional info regarding the new state     */
#define SND_PCM_CM_STATE_EVENT_HARD_SUSPEND (1<<0)    /* Cannot be unsuspended via pause/resume API  */
#define SND_PCM_CM_STATE_EVENT_SOFT_SUSPEND (1<<1)    /* Can be unsuspended via pause/resume API     */
#define SND_PCM_CM_STATE_EVENT_AUTOPAUSE    (1<<2)    /* Paused caused by Sound Management           */
} snd_pcm_state_event_t;

typedef struct snd_pcm_cm_mute_event
{
    uint32_t  mute;
    uint32_t  reason;              /* Same or higher priority sound type which caused the Concurrency Management transition */
#define SND_PCM_CM_MUTE_EVENT_SAME_PRIORITY   (1<<0)
#define SND_PCM_CM_MUTE_EVENT_HIGHER_PRIORITY (1<<1)
} snd_pcm_cm_mute_event_t;

typedef struct snd_pcm_outputclass_event
{
    uint32_t  old_output_class;
    uint32_t  new_output_class;
} snd_pcm_outputclass_event_t;

#define     SND_PCM_EVENT_STATE              0   /* PCM State change */
#define     SND_PCM_EVENT_CM_MUTE            1   /* Concurrency Management Mute  */
#define     SND_PCM_EVENT_OUTPUTCLASS        2
#define     SND_PCM_EVENT_MASK(x)            (1<<x)  /* Use with SND_PCM_EVENT_* definitions */

typedef struct snd_pcm_event
{
    int32_t type;
    uint8_t zero[4];               /* alignment -- zero fill */
    union
    {
        snd_pcm_state_event_t        state;
        snd_pcm_cm_mute_event_t      cm_mute;
        snd_pcm_outputclass_event_t  outputclass;
        uint8_t                      reserved[128];        /* must be filled with zero */
    } data;
    uint8_t reserved[128];        /* must be filled with zero */
} snd_pcm_event_t;

/* Channel Link Mode */
#define     SND_PCM_LINK_MODE_SYNC          0
#define     SND_PCM_LINK_MODE_ASYNC         1
#define     SND_PCM_LINK_MODE_TRANSITION    2

typedef struct snd_pcm_link_info
{
    int     cardno;
    int     coid;
    int32_t channel;
} snd_pcm_link_info_t;

/* shared pcm buffer attributs defines used by pcm_hw.c when interfacing with io-snd to configure and use shared memory */
#define	SND_BUF_DMA_SAFE			(1<<0)  /* shared PCM buffer must be DMA safe, can not use DUAL_MAP */
#define	SND_BUF_DUAL_MAP			(1<<1)  /* shared PCM buffer will use dual mapping to avoid having to do misaligned data accesses that wrap the buffer */
#define	SND_BUF_CACHE				(1<<20) /* DO cache the buffer                        */
#define	SND_BUF_CACHE_NOPS			(1<<21) /* DON'T Flush OR Invalidate the buffer cache */

/* TODO: These mmap structs need to be removed once we properly implement mmap */
typedef struct snd_pcm_mmap_info_s
{
    shm_handle_t dhandle;
    shm_handle_t chandle;
    int32_t      dsize;
    int32_t      csize;
    uint32_t     dflags;          /* See ADO_BUF_*            */
    uint32_t     cflags;          /* See ADO_BUF_*            */
    uint8_t      reserved[144];   /* must be filled with zero */
}       snd_pcm_mmap_info_t;

typedef struct
{
    volatile int32_t    status;             /* read only */
    volatile uint32_t   frag_io;            /* read only */
    volatile uint32_t   block;              /* read only */
    volatile uint32_t   expblock;           /* read write */
    volatile int32_t    voices;             /* read only */
    volatile int32_t    frag_size;          /* read only */
    volatile int32_t    frags;              /* read only */
    uint8_t             reserved[124];      /* must be filled with zero */
}       snd_pcm_mmap_io_status_t;

typedef struct
{
    volatile uint8_t   *addr;               /* read only */
    volatile uint32_t   number;             /* read only */
    volatile int32_t    voice;              /* read only */
    volatile int8_t     data;               /* read write */
    volatile int8_t     io;                 /* read only */
    uint8_t         res[2];
}       snd_pcm_mmap_fragment_t;

typedef struct
{
    snd_pcm_mmap_io_status_t    status;
    snd_pcm_mmap_fragment_t     fragments[];    /* This array is dynamic. See the mmap_io_status.frags variable for its length. */
}       snd_pcm_mmap_io_control_t;

typedef struct
{
    size_t        offset;         /* Offset into shared buffer        */
    uint64_t      signature;      /* Unique transaction signature     */
    size_t        size;           /* Transaction size                 */
} snd_pcm_transaction_t;

/*******************/
/*******************/
/*** AFM SERVICE ***/
/*******************/
/*******************/

#define SNDRV_AFM_VERSION SNDRV_PROTOCOL_VERSION(4,0,0)

typedef struct snd_afm_latency_test
{
    uint16_t input_device;   /* Latency measurement type:
                                0=spk->mic, 1=spk->ref (Voice)
                                0=dst->mic, 1=dst->ref (ICC < 2.1)
                                0=dst->mic, 1=ref->mic (ICC >= 2.1) */
    uint16_t input_voice;    /* Mic or Ref voice */
    uint16_t ms_offset;      /* normally 0 unless high latency (> 100 ms) system
                                (unused ICC >= 2.1) */
} snd_afm_latency_test_t;

typedef struct snd_afm_path
{
    int      type;
#define SND_AFM_WAV_FILE    0
    char     str[];
} snd_afm_path_t;

typedef struct snd_afm_vin_pair
{
    int16_t  key;
    int16_t  value;
} snd_afm_vin_pair_t;

typedef struct snd_afm_vin_list_item
{
    int16_t  key;
    int16_t  min;
    int16_t  max;
    int16_t  is_rpm;
} snd_afm_vin_list_item_t;

typedef struct snd_afm_ap_param {
    uint32_t size;
    uint32_t dataId;
    int32_t  channel;
    int32_t  status;
} snd_afm_ap_param_t;

#define SND_AFM_INFO_ROUTE_MAIN         0x0001
#define SND_AFM_INFO_START_ON_BOOT      0x0002
#define SND_AFM_INFO_PASS_THROUGH       0x0004
#define SND_AFM_INFO_VOL_CTRL           0x0008

typedef struct
{
    int32_t     card;
    int32_t     device;
    char        name[80];               /* sym name of this device */
    char        cardname[80];           /* name of card */
    uint32_t    flags;                  /* see SND_AFM_INFO_* */
    uint32_t    zero;                   /* for alignment - must be zero */
    uint8_t     reserved[120];          /* must be filled with zero */
} snd_afm_info_t;

#define SND_AFM_STATE_RUNNING             0x01
#define SND_AFM_STATE_RUNNING_PCM         0x02
#define SND_AFM_STATE_IDLE                0x03
#define SND_AFM_STATE_SHUTDOWN            0x04

typedef struct
{
    uint64_t    ms_processed;           /* milliseconds of audio that the AFM has processed since start */
    uint32_t    state;                  /* see SND_AFM_STATE_* */
    uint32_t    zero;                   /* for alignment - must be zero */
    uint8_t     reserved[128];          /* must be filled with zero */
} snd_afm_status_t;

#define SNDRV_AFM_IOCTL_PVERSION             _IOR   ('S', 0x10, int32_t)
#define SNDRV_AFM_IOCTL_START                _IO    ('S', 0x20)
#define SNDRV_AFM_IOCTL_STOP                 _IO    ('S', 0x21)
#define SNDRV_AFM_DCMD_SET_PATH              __DIOT ('S', 0x22, snd_afm_path_t)
#define SNDRV_AFM_DCMD_SET_AUDIO_MODE        __DIOT ('S', 0x23, char)
#define SNDRV_AFM_DCMD_GET_AUDIO_MODE        __DIOF ('S', 0x24, char)
#define SNDRV_AFM_IOCTL_START_LATENCY_TEST   _IOW   ('S', 0x25, snd_afm_latency_test_t)
#define SNDRV_AFM_DCMD_GET_VIN_LIST_COUNT    __DIOF ('S', 0x26, int)
#define SNDRV_AFM_DCMD_GET_VIN_LIST          __DIOF ('S', 0x27, snd_afm_vin_list_item_t)
#define SNDRV_AFM_DCMD_SET_VIN_STREAM        __DIOT ('S', 0x28, snd_afm_vin_pair_t)
#define SNDRV_AFM_DCMD_GET_AP_DATA           __DIOTF('S', 0x29, snd_afm_ap_param_t)
#define SNDRV_AFM_DCMD_SET_AP_DATA           __DIOTF('S', 0x2A, snd_afm_ap_param_t)
#define SNDRV_AFM_DCMD_LOAD_AP_DATASET       __DIOTF('S', 0x2B, int)
#define SNDRV_AFM_IOCTL_INFO                 _IOR   ('S', 0x2C, snd_afm_info_t)
#define SNDRV_AFM_IOCTL_STATUS               _IOR   ('S', 0x2D, snd_afm_status_t)
#define SNDRV_AFM_DCMD_GET_PARAM             __DIOTF('S', 0x2E, int)
#define SNDRV_AFM_DCMD_SET_PARAM             __DIOTF('S', 0x2F, int)


/* APX IDs */
#define SND_APX_POSTMIX 1
#define SND_APX_PREMIX 2
typedef snd_afm_ap_param_t snd_pcm_ap_param_t;

typedef struct snd_afm snd_afm_t;

int snd_afm_open(snd_afm_t **handle, const int card, const int device);
int snd_afm_open_name(snd_afm_t **handle, const char *filename);
int snd_afm_close(snd_afm_t *handle);
int snd_afm_info(snd_afm_t *handle, snd_afm_info_t *info);
int snd_afm_status(snd_afm_t *handle, snd_afm_status_t *status);
int snd_afm_file_descriptor(snd_afm_t const * const handle);
int snd_afm_start(snd_afm_t const * const handle);
int snd_afm_stop(snd_afm_t const * const handle);
int snd_afm_set_path(snd_afm_t *handle, const int type, const char *path);
int snd_afm_get_audio_mode(snd_afm_t *handle, char *mode, const int size);
int snd_afm_set_audio_mode(snd_afm_t *handle, const char *mode);
int snd_afm_get_vin_list_count(snd_afm_t *handle, int *num);
int snd_afm_get_vin_list(snd_afm_t *handle, snd_afm_vin_list_item_t *list, const int num);
int snd_afm_set_vin_stream(snd_afm_t *handle, snd_afm_vin_pair_t *stream, const int num);
int snd_afm_set_ap_data(snd_afm_t *handle, snd_afm_ap_param_t *param, const void* data);
int snd_afm_get_ap_data(snd_afm_t *handle, snd_afm_ap_param_t *param, void* data);
int snd_afm_load_ap_dataset(snd_afm_t *handle, const char *dataset, int *ap_status);
int snd_afm_set_param(snd_afm_t *handle, const uint32_t id, const uint32_t size, const void* data);
int snd_afm_get_param(snd_afm_t *handle, uint32_t id, uint32_t* size, void* data);
int snd_afm_latency(snd_afm_t *handle, snd_afm_latency_test_t const * const test);

#endif  /* __ASOUND_QNX_H */
