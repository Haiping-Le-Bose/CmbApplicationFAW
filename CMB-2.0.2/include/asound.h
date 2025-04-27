/* SPDX-License-Identifier: GPL-2.0+ WITH Linux-syscall-note */
/*
 *  Advanced Linux Sound Architecture - ALSA - Driver
 *  Copyright (c) 1994-2003 by Jaroslav Kysela <perex@perex.cz>,
 *                             Abramo Bagnara <abramo@alsa-project.org>
 *
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 *
 */

#ifndef __SOUND_ASOUND_H
#define __SOUND_ASOUND_H

#if defined(__KERNEL__) || defined(__linux__)
#include <linux/types.h>
#include <asm/byteorder.h>
#elif defined(__QNX__)
#include <alsa/asound_endian.h>
#include <alsa/asound_qnx.h>
#include <alsa/type_compat.h>
typedef __s64 __S64_TYPE;
#else
#include <sys/endian.h>
#include <sys/ioctl.h>
#endif

#include <stdlib.h>
#include <time.h>

/*
 *  protocol version
 */

#define SNDRV_PROTOCOL_VERSION(major, minor, subminor) (((major)<<16)|((minor)<<8)|(subminor))
#define SNDRV_PROTOCOL_MAJOR(version) (((version)>>16)&0xffff)
#define SNDRV_PROTOCOL_MINOR(version) (((version)>>8)&0xff)
#define SNDRV_PROTOCOL_MICRO(version) ((version)&0xff)
#define SNDRV_PROTOCOL_INCOMPATIBLE(kversion, uversion) \
	(SNDRV_PROTOCOL_MAJOR(kversion) != SNDRV_PROTOCOL_MAJOR(uversion) || \
	 (SNDRV_PROTOCOL_MAJOR(kversion) == SNDRV_PROTOCOL_MAJOR(uversion) && \
	   SNDRV_PROTOCOL_MINOR(kversion) != SNDRV_PROTOCOL_MINOR(uversion)))

/****************************************************************************
 *                                                                          *
 *        Digital audio interface					    *
 *                                                                          *
 ****************************************************************************/

struct snd_aes_iec958 {
	unsigned char status[24];	/* AES/IEC958 channel status bits */
	unsigned char subcode[147];	/* AES/IEC958 subcode bits */
	unsigned char pad;		/* nothing */
	unsigned char dig_subframe[4];	/* AES/IEC958 subframe bits */
};

/****************************************************************************
 *                                                                          *
 *        CEA-861 Audio InfoFrame. Used in HDMI and DisplayPort		    *
 *                                                                          *
 ****************************************************************************/

struct snd_cea_861_aud_if {
	unsigned char db1_ct_cc; /* coding type and channel count */
	unsigned char db2_sf_ss; /* sample frequency and size */
	unsigned char db3; /* not used, all zeros */
	unsigned char db4_ca; /* channel allocation code */
	unsigned char db5_dminh_lsv; /* downmix inhibit & level-shit values */
};

/****************************************************************************
 *                                                                          *
 *      Section for driver hardware dependent interface - /dev/snd/hw?      *
 *                                                                          *
 ****************************************************************************/

#define SNDRV_HWDEP_VERSION		SNDRV_PROTOCOL_VERSION(1, 0, 1)

enum {
	SNDRV_HWDEP_IFACE_OPL2 = 0,
	SNDRV_HWDEP_IFACE_OPL3,
	SNDRV_HWDEP_IFACE_OPL4,
	SNDRV_HWDEP_IFACE_SB16CSP,	/* Creative Signal Processor */
	SNDRV_HWDEP_IFACE_EMU10K1,	/* FX8010 processor in EMU10K1 chip */
	SNDRV_HWDEP_IFACE_YSS225,	/* Yamaha FX processor */
	SNDRV_HWDEP_IFACE_ICS2115,	/* Wavetable synth */
	SNDRV_HWDEP_IFACE_SSCAPE,	/* Ensoniq SoundScape ISA card (MC68EC000) */
	SNDRV_HWDEP_IFACE_VX,		/* Digigram VX cards */
	SNDRV_HWDEP_IFACE_MIXART,	/* Digigram miXart cards */
	SNDRV_HWDEP_IFACE_USX2Y,	/* Tascam US122, US224 & US428 usb */
	SNDRV_HWDEP_IFACE_EMUX_WAVETABLE, /* EmuX wavetable */
	SNDRV_HWDEP_IFACE_BLUETOOTH,	/* Bluetooth audio */
	SNDRV_HWDEP_IFACE_USX2Y_PCM,	/* Tascam US122, US224 & US428 rawusb pcm */
	SNDRV_HWDEP_IFACE_PCXHR,	/* Digigram PCXHR */
	SNDRV_HWDEP_IFACE_SB_RC,	/* SB Extigy/Audigy2NX remote control */
	SNDRV_HWDEP_IFACE_HDA,		/* HD-audio */
	SNDRV_HWDEP_IFACE_USB_STREAM,	/* direct access to usb stream */
	SNDRV_HWDEP_IFACE_FW_DICE,	/* TC DICE FireWire device */
	SNDRV_HWDEP_IFACE_FW_FIREWORKS,	/* Echo Audio Fireworks based device */
	SNDRV_HWDEP_IFACE_FW_BEBOB,	/* BridgeCo BeBoB based device */
	SNDRV_HWDEP_IFACE_FW_OXFW,	/* Oxford OXFW970/971 based device */
	SNDRV_HWDEP_IFACE_FW_DIGI00X,	/* Digidesign Digi 002/003 family */
	SNDRV_HWDEP_IFACE_FW_TASCAM,	/* TASCAM FireWire series */
	SNDRV_HWDEP_IFACE_LINE6,	/* Line6 USB processors */
	SNDRV_HWDEP_IFACE_FW_MOTU,	/* MOTU FireWire series */
	SNDRV_HWDEP_IFACE_FW_FIREFACE,	/* RME Fireface series */

	/* Don't forget to change the following: */
	SNDRV_HWDEP_IFACE_LAST = SNDRV_HWDEP_IFACE_FW_FIREFACE
};

struct snd_hwdep_info {
	unsigned int device;		/* WR: device number */
	int card;			/* R: card number */
	unsigned char id[64];		/* ID (user selectable) */
	unsigned char name[80];		/* hwdep name */
	int iface;			/* hwdep interface */
	unsigned char reserved[64];	/* reserved for future */
};

/* generic DSP loader */
struct snd_hwdep_dsp_status {
	unsigned int version;		/* R: driver-specific version */
	unsigned char id[32];		/* R: driver-specific ID string */
	unsigned int num_dsps;		/* R: number of DSP images to transfer */
	unsigned int dsp_loaded;	/* R: bit flags indicating the loaded DSPs */
	unsigned int chip_ready;	/* R: 1 = initialization finished */
	unsigned char reserved[16];	/* reserved for future use */
};

struct snd_hwdep_dsp_image {
	unsigned int index;		/* W: DSP index */
	unsigned char name[64];		/* W: ID (e.g. file name) */
	unsigned char *image;	/* W: binary image */
	size_t length;			/* W: size of image in bytes */
	unsigned long driver_data;	/* W: driver-specific data */
};

#define SNDRV_HWDEP_IOCTL_PVERSION	_IOR ('H', 0x00, int)
#define SNDRV_HWDEP_IOCTL_INFO		_IOR ('H', 0x01, struct snd_hwdep_info)
#define SNDRV_HWDEP_IOCTL_DSP_STATUS	_IOR('H', 0x02, struct snd_hwdep_dsp_status)
#define SNDRV_HWDEP_IOCTL_DSP_LOAD	_IOW('H', 0x03, struct snd_hwdep_dsp_image)

/*****************************************************************************
 *                                                                           *
 *             Digital Audio (PCM) interface - /dev/snd/pcm??                *
 *                                                                           *
 *****************************************************************************/

#define SNDRV_PCM_VERSION		SNDRV_PROTOCOL_VERSION(2, 0, 15)

typedef unsigned long snd_pcm_uframes_t;
typedef signed long snd_pcm_sframes_t;

enum {
	SNDRV_PCM_CLASS_GENERIC = 0,	/* standard mono or stereo device */
	SNDRV_PCM_CLASS_MULTI,		/* multichannel device */
	SNDRV_PCM_CLASS_MODEM,		/* software modem class */
	SNDRV_PCM_CLASS_DIGITIZER,	/* digitizer class */
	/* Don't forget to change the following: */
	SNDRV_PCM_CLASS_LAST = SNDRV_PCM_CLASS_DIGITIZER,
};

enum {
	SNDRV_PCM_SUBCLASS_GENERIC_MIX = 0, /* mono or stereo subdevices are mixed together */
	SNDRV_PCM_SUBCLASS_MULTI_MIX,	/* multichannel subdevices are mixed together */
	/* Don't forget to change the following: */
	SNDRV_PCM_SUBCLASS_LAST = SNDRV_PCM_SUBCLASS_MULTI_MIX,
};

enum {
	SNDRV_PCM_STREAM_PLAYBACK = 0,
	SNDRV_PCM_STREAM_CAPTURE,
	SNDRV_PCM_STREAM_LAST = SNDRV_PCM_STREAM_CAPTURE,
};

#if defined(__QNX__)
#define	SNDRV_PCM_ACCESS_MMAP_INTERLEAVED     (0) /* interleaved mmap */
#define	SNDRV_PCM_ACCESS_MMAP_NONINTERLEAVED  (1) /* noninterleaved mmap */
#define	SNDRV_PCM_ACCESS_MMAP_COMPLEX         (2) /* complex mmap */
#define	SNDRV_PCM_ACCESS_RW_INTERLEAVED       (3) /* readi/writei */
#define	SNDRV_PCM_ACCESS_RW_NONINTERLEAVED    (4) /* readn/writen */
#else
typedef int __bitwise snd_pcm_access_t;
#define	SNDRV_PCM_ACCESS_MMAP_INTERLEAVED	((snd_pcm_access_t) 0) /* interleaved mmap */
#define	SNDRV_PCM_ACCESS_MMAP_NONINTERLEAVED	((snd_pcm_access_t) 1) /* noninterleaved mmap */
#define	SNDRV_PCM_ACCESS_MMAP_COMPLEX		((snd_pcm_access_t) 2) /* complex mmap */
#define	SNDRV_PCM_ACCESS_RW_INTERLEAVED		((snd_pcm_access_t) 3) /* readi/writei */
#define	SNDRV_PCM_ACCESS_RW_NONINTERLEAVED	((snd_pcm_access_t) 4) /* readn/writen */
#endif
#define	SNDRV_PCM_ACCESS_LAST		SNDRV_PCM_ACCESS_RW_NONINTERLEAVED

#if defined(__QNX__)
#define	SNDRV_PCM_FORMAT_S8          (0)
#define	SNDRV_PCM_FORMAT_U8          (1)
#define	SNDRV_PCM_FORMAT_S16_LE      (2)
#define	SNDRV_PCM_FORMAT_S16_BE      (3)
#define	SNDRV_PCM_FORMAT_U16_LE      (4)
#define	SNDRV_PCM_FORMAT_U16_BE      (5)
#define	SNDRV_PCM_FORMAT_S24_LE      (6) /* low three bytes */
#define	SNDRV_PCM_FORMAT_S24_BE      (7) /* low three bytes */
#define	SNDRV_PCM_FORMAT_U24_LE      (8) /* low three bytes */
#define	SNDRV_PCM_FORMAT_U24_BE      (9) /* low three bytes */
#define	SNDRV_PCM_FORMAT_S32_LE     (10)
#define	SNDRV_PCM_FORMAT_S32_BE     (11)
#define	SNDRV_PCM_FORMAT_U32_LE     (12)
#define	SNDRV_PCM_FORMAT_U32_BE     (13)
#define	SNDRV_PCM_FORMAT_FLOAT_LE   (14) /* 4-byte float, IEEE-754 32-bit, range -1.0 to 1.0 */
#define	SNDRV_PCM_FORMAT_FLOAT_BE   (15) /* 4-byte float, IEEE-754 32-bit, range -1.0 to 1.0 */
#define	SNDRV_PCM_FORMAT_FLOAT64_LE (16) /* 8-byte float, IEEE-754 64-bit, range -1.0 to 1.0 */
#define	SNDRV_PCM_FORMAT_FLOAT64_BE (17) /* 8-byte float, IEEE-754 64-bit, range -1.0 to 1.0 */
#define	SNDRV_PCM_FORMAT_IEC958_SUBFRAME_LE (18) /* IEC-958 subframe, Little Endian */
#define	SNDRV_PCM_FORMAT_IEC958_SUBFRAME_BE (19) /* IEC-958 subframe, Big Endian */
#define	SNDRV_PCM_FORMAT_MU_LAW     (20)
#define	SNDRV_PCM_FORMAT_A_LAW      (21)
#define	SNDRV_PCM_FORMAT_IMA_ADPCM  (22)
#define	SNDRV_PCM_FORMAT_MPEG       (23)
#define	SNDRV_PCM_FORMAT_GSM        (24)
#define	SNDRV_PCM_FORMAT_S20_LE     (25) /* in four bytes, LSB justified */
#define	SNDRV_PCM_FORMAT_S20_BE     (26) /* in four bytes, LSB justified */
#define	SNDRV_PCM_FORMAT_U20_LE     (27) /* in four bytes, LSB justified */
#define	SNDRV_PCM_FORMAT_U20_BE     (28) /* in four bytes, LSB justified */
/* gap in the numbering for a future standard linear format */
#define	SNDRV_PCM_FORMAT_SPECIAL    (31)
#define	SNDRV_PCM_FORMAT_S24_3LE    (32)	/* in three bytes */
#define	SNDRV_PCM_FORMAT_S24_3BE    (33)	/* in three bytes */
#define	SNDRV_PCM_FORMAT_U24_3LE    (34)	/* in three bytes */
#define	SNDRV_PCM_FORMAT_U24_3BE    (35)	/* in three bytes */
#define	SNDRV_PCM_FORMAT_S20_3LE    (36)	/* in three bytes */
#define	SNDRV_PCM_FORMAT_S20_3BE    (37)	/* in three bytes */
#define	SNDRV_PCM_FORMAT_U20_3LE    (38)	/* in three bytes */
#define	SNDRV_PCM_FORMAT_U20_3BE    (39)	/* in three bytes */
#define	SNDRV_PCM_FORMAT_S18_3LE    (40)	/* in three bytes */
#define	SNDRV_PCM_FORMAT_S18_3BE    (41)	/* in three bytes */
#define	SNDRV_PCM_FORMAT_U18_3LE    (42)	/* in three bytes */
#define	SNDRV_PCM_FORMAT_U18_3BE    (43)	/* in three bytes */
#define	SNDRV_PCM_FORMAT_G723_24    (44) /* 8 samples in 3 bytes */
#define	SNDRV_PCM_FORMAT_G723_24_1B (45) /* 1 sample in 1 byte */
#define	SNDRV_PCM_FORMAT_G723_40    (46) /* 8 Samples in 5 bytes */
#define	SNDRV_PCM_FORMAT_G723_40_1B (47) /* 1 sample in 1 byte */
#define	SNDRV_PCM_FORMAT_DSD_U8     (48) /* DSD, 1-byte samples DSD (x8) */
#define	SNDRV_PCM_FORMAT_DSD_U16_LE (49) /* DSD, 2-byte samples DSD (x16), little endian */
#define	SNDRV_PCM_FORMAT_DSD_U32_LE (50) /* DSD, 4-byte samples DSD (x32), little endian */
#define	SNDRV_PCM_FORMAT_DSD_U16_BE (51) /* DSD, 2-byte samples DSD (x16), big endian */
#define	SNDRV_PCM_FORMAT_DSD_U32_BE (52) /* DSD, 4-byte samples DSD (x32), big endian */
#else
typedef int __bitwise snd_pcm_format_t;
#define	SNDRV_PCM_FORMAT_S8	((snd_pcm_format_t) 0)
#define	SNDRV_PCM_FORMAT_U8	((snd_pcm_format_t) 1)
#define	SNDRV_PCM_FORMAT_S16_LE	((snd_pcm_format_t) 2)
#define	SNDRV_PCM_FORMAT_S16_BE	((snd_pcm_format_t) 3)
#define	SNDRV_PCM_FORMAT_U16_LE	((snd_pcm_format_t) 4)
#define	SNDRV_PCM_FORMAT_U16_BE	((snd_pcm_format_t) 5)
#define	SNDRV_PCM_FORMAT_S24_LE	((snd_pcm_format_t) 6) /* low three bytes */
#define	SNDRV_PCM_FORMAT_S24_BE	((snd_pcm_format_t) 7) /* low three bytes */
#define	SNDRV_PCM_FORMAT_U24_LE	((snd_pcm_format_t) 8) /* low three bytes */
#define	SNDRV_PCM_FORMAT_U24_BE	((snd_pcm_format_t) 9) /* low three bytes */
#define	SNDRV_PCM_FORMAT_S32_LE	((snd_pcm_format_t) 10)
#define	SNDRV_PCM_FORMAT_S32_BE	((snd_pcm_format_t) 11)
#define	SNDRV_PCM_FORMAT_U32_LE	((snd_pcm_format_t) 12)
#define	SNDRV_PCM_FORMAT_U32_BE	((snd_pcm_format_t) 13)
#define	SNDRV_PCM_FORMAT_FLOAT_LE	((snd_pcm_format_t) 14) /* 4-byte float, IEEE-754 32-bit, range -1.0 to 1.0 */
#define	SNDRV_PCM_FORMAT_FLOAT_BE	((snd_pcm_format_t) 15) /* 4-byte float, IEEE-754 32-bit, range -1.0 to 1.0 */
#define	SNDRV_PCM_FORMAT_FLOAT64_LE	((snd_pcm_format_t) 16) /* 8-byte float, IEEE-754 64-bit, range -1.0 to 1.0 */
#define	SNDRV_PCM_FORMAT_FLOAT64_BE	((snd_pcm_format_t) 17) /* 8-byte float, IEEE-754 64-bit, range -1.0 to 1.0 */
#define	SNDRV_PCM_FORMAT_IEC958_SUBFRAME_LE ((snd_pcm_format_t) 18) /* IEC-958 subframe, Little Endian */
#define	SNDRV_PCM_FORMAT_IEC958_SUBFRAME_BE ((snd_pcm_format_t) 19) /* IEC-958 subframe, Big Endian */
#define	SNDRV_PCM_FORMAT_MU_LAW		((snd_pcm_format_t) 20)
#define	SNDRV_PCM_FORMAT_A_LAW		((snd_pcm_format_t) 21)
#define	SNDRV_PCM_FORMAT_IMA_ADPCM	((snd_pcm_format_t) 22)
#define	SNDRV_PCM_FORMAT_MPEG		((snd_pcm_format_t) 23)
#define	SNDRV_PCM_FORMAT_GSM		((snd_pcm_format_t) 24)
#define	SNDRV_PCM_FORMAT_S20_LE	((snd_pcm_format_t) 25) /* in four bytes, LSB justified */
#define	SNDRV_PCM_FORMAT_S20_BE	((snd_pcm_format_t) 26) /* in four bytes, LSB justified */
#define	SNDRV_PCM_FORMAT_U20_LE	((snd_pcm_format_t) 27) /* in four bytes, LSB justified */
#define	SNDRV_PCM_FORMAT_U20_BE	((snd_pcm_format_t) 28) /* in four bytes, LSB justified */
/* gap in the numbering for a future standard linear format */
#define	SNDRV_PCM_FORMAT_SPECIAL	((snd_pcm_format_t) 31)
#define	SNDRV_PCM_FORMAT_S24_3LE	((snd_pcm_format_t) 32)	/* in three bytes */
#define	SNDRV_PCM_FORMAT_S24_3BE	((snd_pcm_format_t) 33)	/* in three bytes */
#define	SNDRV_PCM_FORMAT_U24_3LE	((snd_pcm_format_t) 34)	/* in three bytes */
#define	SNDRV_PCM_FORMAT_U24_3BE	((snd_pcm_format_t) 35)	/* in three bytes */
#define	SNDRV_PCM_FORMAT_S20_3LE	((snd_pcm_format_t) 36)	/* in three bytes */
#define	SNDRV_PCM_FORMAT_S20_3BE	((snd_pcm_format_t) 37)	/* in three bytes */
#define	SNDRV_PCM_FORMAT_U20_3LE	((snd_pcm_format_t) 38)	/* in three bytes */
#define	SNDRV_PCM_FORMAT_U20_3BE	((snd_pcm_format_t) 39)	/* in three bytes */
#define	SNDRV_PCM_FORMAT_S18_3LE	((snd_pcm_format_t) 40)	/* in three bytes */
#define	SNDRV_PCM_FORMAT_S18_3BE	((snd_pcm_format_t) 41)	/* in three bytes */
#define	SNDRV_PCM_FORMAT_U18_3LE	((snd_pcm_format_t) 42)	/* in three bytes */
#define	SNDRV_PCM_FORMAT_U18_3BE	((snd_pcm_format_t) 43)	/* in three bytes */
#define	SNDRV_PCM_FORMAT_G723_24	((snd_pcm_format_t) 44) /* 8 samples in 3 bytes */
#define	SNDRV_PCM_FORMAT_G723_24_1B	((snd_pcm_format_t) 45) /* 1 sample in 1 byte */
#define	SNDRV_PCM_FORMAT_G723_40	((snd_pcm_format_t) 46) /* 8 Samples in 5 bytes */
#define	SNDRV_PCM_FORMAT_G723_40_1B	((snd_pcm_format_t) 47) /* 1 sample in 1 byte */
#define	SNDRV_PCM_FORMAT_DSD_U8		((snd_pcm_format_t) 48) /* DSD, 1-byte samples DSD (x8) */
#define	SNDRV_PCM_FORMAT_DSD_U16_LE	((snd_pcm_format_t) 49) /* DSD, 2-byte samples DSD (x16), little endian */
#define	SNDRV_PCM_FORMAT_DSD_U32_LE	((snd_pcm_format_t) 50) /* DSD, 4-byte samples DSD (x32), little endian */
#define	SNDRV_PCM_FORMAT_DSD_U16_BE	((snd_pcm_format_t) 51) /* DSD, 2-byte samples DSD (x16), big endian */
#define	SNDRV_PCM_FORMAT_DSD_U32_BE	((snd_pcm_format_t) 52) /* DSD, 4-byte samples DSD (x32), big endian */
#endif
#define	SNDRV_PCM_FORMAT_LAST		SNDRV_PCM_FORMAT_DSD_U32_BE
#define	SNDRV_PCM_FORMAT_FIRST		SNDRV_PCM_FORMAT_S8

#ifdef SNDRV_LITTLE_ENDIAN
#define	SNDRV_PCM_FORMAT_S16		SNDRV_PCM_FORMAT_S16_LE
#define	SNDRV_PCM_FORMAT_U16		SNDRV_PCM_FORMAT_U16_LE
#define	SNDRV_PCM_FORMAT_S24		SNDRV_PCM_FORMAT_S24_LE
#define	SNDRV_PCM_FORMAT_U24		SNDRV_PCM_FORMAT_U24_LE
#define	SNDRV_PCM_FORMAT_S32		SNDRV_PCM_FORMAT_S32_LE
#define	SNDRV_PCM_FORMAT_U32		SNDRV_PCM_FORMAT_U32_LE
#define	SNDRV_PCM_FORMAT_FLOAT		SNDRV_PCM_FORMAT_FLOAT_LE
#define	SNDRV_PCM_FORMAT_FLOAT64	SNDRV_PCM_FORMAT_FLOAT64_LE
#define	SNDRV_PCM_FORMAT_IEC958_SUBFRAME SNDRV_PCM_FORMAT_IEC958_SUBFRAME_LE
#define	SNDRV_PCM_FORMAT_S20		SNDRV_PCM_FORMAT_S20_LE
#define	SNDRV_PCM_FORMAT_U20		SNDRV_PCM_FORMAT_U20_LE
#endif
#ifdef SNDRV_BIG_ENDIAN
#define	SNDRV_PCM_FORMAT_S16		SNDRV_PCM_FORMAT_S16_BE
#define	SNDRV_PCM_FORMAT_U16		SNDRV_PCM_FORMAT_U16_BE
#define	SNDRV_PCM_FORMAT_S24		SNDRV_PCM_FORMAT_S24_BE
#define	SNDRV_PCM_FORMAT_U24		SNDRV_PCM_FORMAT_U24_BE
#define	SNDRV_PCM_FORMAT_S32		SNDRV_PCM_FORMAT_S32_BE
#define	SNDRV_PCM_FORMAT_U32		SNDRV_PCM_FORMAT_U32_BE
#define	SNDRV_PCM_FORMAT_FLOAT		SNDRV_PCM_FORMAT_FLOAT_BE
#define	SNDRV_PCM_FORMAT_FLOAT64	SNDRV_PCM_FORMAT_FLOAT64_BE
#define	SNDRV_PCM_FORMAT_IEC958_SUBFRAME SNDRV_PCM_FORMAT_IEC958_SUBFRAME_BE
#define	SNDRV_PCM_FORMAT_S20		SNDRV_PCM_FORMAT_S20_BE
#define	SNDRV_PCM_FORMAT_U20		SNDRV_PCM_FORMAT_U20_BE
#endif

#if defined(__QNX__)
#define	SNDRV_PCM_SUBFORMAT_STD		(0)
#else
typedef int __bitwise snd_pcm_subformat_t;
#define	SNDRV_PCM_SUBFORMAT_STD		((snd_pcm_subformat_t) 0)
#endif
#define	SNDRV_PCM_SUBFORMAT_LAST	SNDRV_PCM_SUBFORMAT_STD

#define SNDRV_PCM_INFO_MMAP                        (1UL<<0)   /* hardware supports mmap */
#define SNDRV_PCM_INFO_MMAP_VALID                  (1UL<<1)   /* period data are valid during transfer */
#define SNDRV_PCM_INFO_DOUBLE                      (1UL<<2)   /* Double buffering needed for PCM start/stop */
#define SNDRV_PCM_INFO_BATCH                       (1UL<<4)   /* double buffering */
#define SNDRV_PCM_INFO_SYNC_APPLPTR                (1UL<<5)   /* need the explicit sync of appl_ptr update */
#define SNDRV_PCM_INFO_INTERLEAVED                 (1UL<<8)   /* channels are interleaved */
#define SNDRV_PCM_INFO_NONINTERLEAVED              (1UL<<9)   /* channels are not interleaved */
#define SNDRV_PCM_INFO_COMPLEX                     (1UL<<10)  /* complex frame organization (mmap only) */
#define SNDRV_PCM_INFO_BLOCK_TRANSFER              (1UL<<16)  /* hardware transfer block of samples */
#define SNDRV_PCM_INFO_OVERRANGE                   (1UL<<17)  /* hardware supports ADC (capture) overrange detection */
#define SNDRV_PCM_INFO_RESUME                      (1UL<<18)  /* hardware supports stream resume after suspend */
#define SNDRV_PCM_INFO_PAUSE                       (1UL<<19)  /* pause ioctl is supported */
#define SNDRV_PCM_INFO_HALF_DUPLEX                 (1UL<<20)  /* only half duplex */
#define SNDRV_PCM_INFO_JOINT_DUPLEX                (1UL<<21)  /* playback and capture stream are somewhat correlated */
#define SNDRV_PCM_INFO_SYNC_START                  (1UL<<22)  /* pcm support some kind of sync go */
#define SNDRV_PCM_INFO_NO_PERIOD_WAKEUP            (1UL<<23)  /* period wakeup can be disabled */
#define SNDRV_PCM_INFO_HAS_WALL_CLOCK              (1UL<<24)  /* (Deprecated)has audio wall clock for audio/system time sync */
#define SNDRV_PCM_INFO_HAS_LINK_ATIME              (1UL<<24)  /* report hardware link audio time, reset on startup */
#define SNDRV_PCM_INFO_HAS_LINK_ABSOLUTE_ATIME     (1UL<<25)  /* report absolute hardware link audio time, not reset on startup */
#define SNDRV_PCM_INFO_HAS_LINK_ESTIMATED_ATIME    (1UL<<26)  /* report estimated link audio time */
#define SNDRV_PCM_INFO_HAS_LINK_SYNCHRONIZED_ATIME (1UL<<27)  /* report synchronized audio/system time */

#define SNDRV_PCM_INFO_DRAIN_TRIGGER               (1UL<<30)  /* internal kernel flag - trigger in drain */
#define SNDRV_PCM_INFO_FIFO_IN_FRAMES              (1UL<<31)  /* internal kernel flag - FIFO size is in frames */

#if defined(__QNX__)
/* QNX SNDRV_PCM_INFO_* Extensions
 * NOTE: Start from the MSB and work backwards to avoid conflicts with standard ALSA definitions
 */
#define SNDRV_PCM_INFO_PCM_MIXER                   (1UL<<63)       /* PCM Mixer device                                     */
#define SNDRV_PCM_INFO_PCM_SPLITTER                (1UL<<62)       /* PCM SPLITTER device                                  */
#define SNDRV_PCM_INFO_ROUTING                     (1UL<<61)       /* channel may be redirected to a different transducer  */
#define SNDRV_PCM_INFO_AFM_PCM                     (1UL<<60)       /* PCM device created by an AFM                         */
#define SNDRV_PCM_INFO_LOGGING                     (1UL<<59)       /* PCM Logging is enabled on the channel                */
#define SNDRV_PCM_INFO_LOW_LATENCY                 (1UL<<58)       /* PCM Low Latency device                               */
#define SNDRV_PCM_INFO_SECURE                      (1UL<<57)
#define SNDRV_PCM_INFO_RESTRICTED                  (1UL<<56)
#define SNDRV_PCM_INFO_HW_POSITION                 (1UL<<55)       /* Hardware sub-period positional information supported */
#endif

#if (__BITS_PER_LONG == 32 && defined(__USE_TIME_BITS64)) || defined(__KERNEL__) || defined(__QNX__)
#define __SND_STRUCT_TIME64
#endif

#if defined(__QNX__)
#define	SNDRV_PCM_STATE_OPEN            (0) /* stream is open */
#define	SNDRV_PCM_STATE_SETUP           (1) /* stream has a setup */
#define	SNDRV_PCM_STATE_PREPARED        (2) /* stream is ready to start */
#define	SNDRV_PCM_STATE_RUNNING         (3) /* stream is running */
#define	SNDRV_PCM_STATE_XRUN            (4) /* stream reached an xrun */
#define	SNDRV_PCM_STATE_DRAINING        (5) /* stream is draining */
#define	SNDRV_PCM_STATE_PAUSED          (6) /* stream is paused */
#define	SNDRV_PCM_STATE_SUSPENDED       (7) /* hardware is suspended */
#define	SNDRV_PCM_STATE_DISCONNECTED    (8) /* hardware is disconnected */
#define	SNDRV_PCM_STATE_ERROR           (9)	/* hardware error */
#define	SNDRV_PCM_STATE_CHANGE          (10) /* hardware device capability change */
#define	SNDRV_PCM_STATE_LAST            (SNDRV_PCM_STATE_CHANGE)
#else
typedef int __bitwise snd_pcm_state_t;
#define	SNDRV_PCM_STATE_OPEN		((snd_pcm_state_t) 0) /* stream is open */
#define	SNDRV_PCM_STATE_SETUP		((snd_pcm_state_t) 1) /* stream has a setup */
#define	SNDRV_PCM_STATE_PREPARED	((snd_pcm_state_t) 2) /* stream is ready to start */
#define	SNDRV_PCM_STATE_RUNNING		((snd_pcm_state_t) 3) /* stream is running */
#define	SNDRV_PCM_STATE_XRUN		((snd_pcm_state_t) 4) /* stream reached an xrun */
#define	SNDRV_PCM_STATE_DRAINING	((snd_pcm_state_t) 5) /* stream is draining */
#define	SNDRV_PCM_STATE_PAUSED		((snd_pcm_state_t) 6) /* stream is paused */
#define	SNDRV_PCM_STATE_SUSPENDED	((snd_pcm_state_t) 7) /* hardware is suspended */
#define	SNDRV_PCM_STATE_DISCONNECTED	((snd_pcm_state_t) 8) /* hardware is disconnected */
#define	SNDRV_PCM_STATE_LAST		SNDRV_PCM_STATE_DISCONNECTED
#endif

enum {
	SNDRV_PCM_MMAP_OFFSET_DATA = 0x00000000,
	SNDRV_PCM_MMAP_OFFSET_STATUS_OLD = 0x80000000,
	SNDRV_PCM_MMAP_OFFSET_CONTROL_OLD = 0x81000000,
	SNDRV_PCM_MMAP_OFFSET_STATUS_NEW = 0x82000000,
	SNDRV_PCM_MMAP_OFFSET_CONTROL_NEW = 0x83000000,
#ifdef __SND_STRUCT_TIME64
	SNDRV_PCM_MMAP_OFFSET_STATUS = SNDRV_PCM_MMAP_OFFSET_STATUS_NEW,
	SNDRV_PCM_MMAP_OFFSET_CONTROL = SNDRV_PCM_MMAP_OFFSET_CONTROL_NEW,
#else
	SNDRV_PCM_MMAP_OFFSET_STATUS = SNDRV_PCM_MMAP_OFFSET_STATUS_OLD,
	SNDRV_PCM_MMAP_OFFSET_CONTROL = SNDRV_PCM_MMAP_OFFSET_CONTROL_OLD,
#endif
};

union snd_pcm_sync_id {
	unsigned char id[16];
	unsigned short id16[8];
	unsigned int id32[4];
};

struct snd_pcm_info {
	unsigned int device;		/* RO/WR (control): device number */
	unsigned int subdevice;		/* RO/WR (control): subdevice number */
	int stream;			/* RO/WR (control): stream direction */
	int card;			/* R: card number */
	unsigned char id[64];		/* ID (user selectable) */
	unsigned char name[80];		/* name of this device */
	unsigned char subname[32];	/* subdevice name */
	int dev_class;			/* SNDRV_PCM_CLASS_* */
	int dev_subclass;		/* SNDRV_PCM_SUBCLASS_* */
	unsigned int subdevices_count;
	unsigned int subdevices_avail;
	union snd_pcm_sync_id sync;	/* hardware synchronization ID */
	unsigned char reserved[64];	/* reserved for future... */
};

typedef int snd_pcm_hw_param_t;
#define	SNDRV_PCM_HW_PARAM_ACCESS	0	/* Access type */
#define	SNDRV_PCM_HW_PARAM_FORMAT	1	/* Format */
#define	SNDRV_PCM_HW_PARAM_SUBFORMAT	2	/* Subformat */
#define	SNDRV_PCM_HW_PARAM_FIRST_MASK	SNDRV_PCM_HW_PARAM_ACCESS
#define	SNDRV_PCM_HW_PARAM_LAST_MASK	SNDRV_PCM_HW_PARAM_SUBFORMAT

#define	SNDRV_PCM_HW_PARAM_SAMPLE_BITS	8	/* Bits per sample */
#define	SNDRV_PCM_HW_PARAM_FRAME_BITS	9	/* Bits per frame */
#define	SNDRV_PCM_HW_PARAM_CHANNELS	10	/* Channels */
#define	SNDRV_PCM_HW_PARAM_RATE		11	/* Approx rate */
#define	SNDRV_PCM_HW_PARAM_PERIOD_TIME	12	/* Approx distance between
						 * interrupts in us
						 */
#define	SNDRV_PCM_HW_PARAM_PERIOD_SIZE	13	/* Approx frames between
						 * interrupts
						 */
#define	SNDRV_PCM_HW_PARAM_PERIOD_BYTES	14	/* Approx bytes between
						 * interrupts
						 */
#define	SNDRV_PCM_HW_PARAM_PERIODS	15	/* Approx interrupts per
						 * buffer
						 */
#define	SNDRV_PCM_HW_PARAM_BUFFER_TIME	16	/* Approx duration of buffer
						 * in us
						 */
#define	SNDRV_PCM_HW_PARAM_BUFFER_SIZE	17	/* Size of buffer in frames */
#define	SNDRV_PCM_HW_PARAM_BUFFER_BYTES	18	/* Size of buffer in bytes */
#define	SNDRV_PCM_HW_PARAM_TICK_TIME	19	/* Approx tick duration in us */
#define	SNDRV_PCM_HW_PARAM_FIRST_INTERVAL	SNDRV_PCM_HW_PARAM_SAMPLE_BITS
#define	SNDRV_PCM_HW_PARAM_LAST_INTERVAL	SNDRV_PCM_HW_PARAM_TICK_TIME

#define SNDRV_PCM_HW_PARAMS_NORESAMPLE	(1<<0)	/* avoid rate resampling */
#define SNDRV_PCM_HW_PARAMS_EXPORT_BUFFER	(1<<1)	/* export buffer */
#define SNDRV_PCM_HW_PARAMS_NO_PERIOD_WAKEUP	(1<<2)	/* disable period wakeups */

struct snd_interval {
	unsigned int min, max;
	unsigned int openmin:1,
		     openmax:1,
		     integer:1,
		     empty:1;
};

#define SNDRV_MASK_MAX	256

struct snd_mask {
	__u32 bits[(SNDRV_MASK_MAX+31)/32];
};

#if defined(__QNX__)
#define MAX_RATE_LIST    8  /* Array length for KNOT rate list */
#endif

struct snd_pcm_hw_params {
	unsigned int flags;
	struct snd_mask masks[SNDRV_PCM_HW_PARAM_LAST_MASK -
			       SNDRV_PCM_HW_PARAM_FIRST_MASK + 1];
	struct snd_mask mres[5];	/* reserved masks */
	struct snd_interval intervals[SNDRV_PCM_HW_PARAM_LAST_INTERVAL -
				        SNDRV_PCM_HW_PARAM_FIRST_INTERVAL + 1];
	struct snd_interval ires[9];	/* reserved intervals */
	unsigned int rmask;		/* W: requested masks */
	unsigned int cmask;		/* R: changed masks */
#if defined(__QNX__)
	uint64_t     info;                      /* R: Info flags for returned setup */
	uint32_t     chmap_channels_mask;       /* R: Supported channels mask from HW channel maps, bit location represents the number of channels */
	uint32_t     rates;                     /* R: Supported rates mask from HW rates */
	uint32_t     rate_list_len;             /* R: The rate list length for KNOT rates */
	uint32_t     rate_list[MAX_RATE_LIST];  /* R: Rate list if KNOT rates are set */
	uint32_t     subdevice;                 /* R: Acquired subdevice              */
#else
	uint32_t     info;		/* R: Info flags for returned setup */
#endif
	unsigned int msbits;		/* R: used most significant bits */
	unsigned int rate_num;		/* R: rate numerator */
	unsigned int rate_den;		/* R: rate denominator */
	snd_pcm_uframes_t fifo_size;	/* R: chip FIFO size in frames */
#if defined(__QNX__)
	unsigned char reserved[12];	/* reserved for future */
#else
	unsigned char reserved[64];	/* reserved for future */
#endif
};

enum {
	SNDRV_PCM_TSTAMP_NONE = 0,
	SNDRV_PCM_TSTAMP_ENABLE,
	SNDRV_PCM_TSTAMP_LAST = SNDRV_PCM_TSTAMP_ENABLE,
};

struct snd_pcm_sw_params {
	int tstamp_mode;			/* timestamp mode */
	unsigned int period_step;
	unsigned int sleep_min;			/* min ticks to sleep */
	snd_pcm_uframes_t avail_min;		/* min avail frames for wakeup */
	snd_pcm_uframes_t xfer_align;		/* obsolete: xfer size need to be a multiple */
	snd_pcm_uframes_t start_threshold;	/* min hw_avail frames for automatic start */
	snd_pcm_uframes_t stop_threshold;	/* min avail frames for automatic stop */
	snd_pcm_uframes_t silence_threshold;	/* min distance from noise for silence filling */
	snd_pcm_uframes_t silence_size;		/* silence block size */
	snd_pcm_uframes_t boundary;		/* pointers wrap point */
	unsigned int proto;			/* protocol version */
	unsigned int tstamp_type;		/* timestamp type (req. proto >= 2.0.12) */
#if defined(__QNX__)
	char sound_type[32];			/* Sound management stream type    */
	unsigned char reserved[24];		/* reserved for future */
#else
	unsigned char reserved[56];		/* reserved for future */
#endif
};

struct snd_pcm_channel_info {
	unsigned int channel;
	__kernel_off_t offset;		/* mmap offset */
	unsigned int first;		/* offset to first sample in bits */
	unsigned int step;		/* samples distance in bits */
};

enum {
	/*
	 *  first definition for backwards compatibility only,
	 *  maps to wallclock/link time for HDAudio playback and DEFAULT/DMA time for everything else
	 */
	SNDRV_PCM_AUDIO_TSTAMP_TYPE_COMPAT = 0,

	/* timestamp definitions */
	SNDRV_PCM_AUDIO_TSTAMP_TYPE_DEFAULT = 1,           /* DMA time, reported as per hw_ptr */
	SNDRV_PCM_AUDIO_TSTAMP_TYPE_LINK = 2,	           /* link time reported by sample or wallclock counter, reset on startup */
	SNDRV_PCM_AUDIO_TSTAMP_TYPE_LINK_ABSOLUTE = 3,	   /* link time reported by sample or wallclock counter, not reset on startup */
	SNDRV_PCM_AUDIO_TSTAMP_TYPE_LINK_ESTIMATED = 4,    /* link time estimated indirectly */
	SNDRV_PCM_AUDIO_TSTAMP_TYPE_LINK_SYNCHRONIZED = 5, /* link time synchronized with system time */
	SNDRV_PCM_AUDIO_TSTAMP_TYPE_LAST = SNDRV_PCM_AUDIO_TSTAMP_TYPE_LINK_SYNCHRONIZED
};

/* explicit padding avoids incompatibility between i386 and x86-64 */
typedef struct { unsigned char pad[sizeof(time_t) - sizeof(int)]; } __time_pad;

struct snd_pcm_status {
#if defined(__QNX__)
	int state;                       /* stream state */
#else
	snd_pcm_state_t state;           /* stream state */
#endif
	__time_pad pad1;                 /* align to timespec */
	struct timespec trigger_tstamp;  /* time when stream was started/stopped/paused */
	struct timespec tstamp;          /* reference timestamp */
	snd_pcm_uframes_t appl_ptr;      /* appl ptr */
	snd_pcm_uframes_t hw_ptr;        /* hw ptr */
	snd_pcm_sframes_t delay;         /* current delay in frames */
	snd_pcm_uframes_t avail;         /* number of frames available */
#if defined(__QNX__)
	snd_pcm_uframes_t avail_min;     /* min frames needed before a 'start' can be issued */
#endif
	snd_pcm_uframes_t avail_max;     /* max frames available on hw since last status */
	snd_pcm_uframes_t overrange;     /* count of ADC (capture) overrange detections from last status */
#if defined(__QNX__)
	int suspended_state;             /* suspended stream state */
#else
	snd_pcm_state_t suspended_state; /* suspended stream state */
#endif
	__u32 audio_tstamp_data;         /* needed for 64-bit alignment, used for configs/report to/from userspace */
	struct timespec audio_tstamp;    /* sample counter, wall clock, PHC or on-demand sync'ed */
	struct timespec driver_tstamp;   /* useful in case reference system tstamp is reported with delay */
	__u32 audio_tstamp_accuracy;     /* in ns units, only valid if indicated in audio_tstamp_data */
#if defined(__QNX__)
	uint32_t      cm_state;          /* Concurrency management state, SND_PCM_CM_STATE_* (asound_qnx.h) */
	unsigned char reserved[48-2*sizeof(struct timespec)]; /* must be filled with zero */
#else
	unsigned char reserved[52-2*sizeof(struct timespec)]; /* must be filled with zero */
#endif
};

/*
 * For mmap operations, we need the 64-bit layout, both for compat mode,
 * and for y2038 compatibility. For 64-bit applications, the two definitions
 * are identical, so we keep the traditional version.
 */
#ifdef __SND_STRUCT_TIME64
#define __snd_pcm_mmap_status64		snd_pcm_mmap_status
#define __snd_pcm_mmap_control64	snd_pcm_mmap_control
#define __snd_pcm_sync_ptr64		snd_pcm_sync_ptr
#define __snd_timespec64		timespec
struct __snd_timespec {
	__s32 tv_sec;
	__s32 tv_nsec;
};
#else
#define __snd_pcm_mmap_status		snd_pcm_mmap_status
#define __snd_pcm_mmap_control		snd_pcm_mmap_control
#define __snd_pcm_sync_ptr		snd_pcm_sync_ptr
#define __snd_timespec			timespec
struct __snd_timespec64 {
	__s64 tv_sec;
	__s64 tv_nsec;
};

#endif

struct __snd_pcm_mmap_status {
#if defined(__QNX__)
	int state;                  /* RO: state - SNDRV_PCM_STATE_XXXX */
#else
	snd_pcm_state_t state;      /* RO: state - SNDRV_PCM_STATE_XXXX */
#endif
	int pad1;                   /* Needed for 64 bit alignment */
	snd_pcm_uframes_t hw_ptr;	/* RO: hw ptr (0...boundary-1) */
	struct __snd_timespec tstamp; /* Timestamp */
#if defined(__QNX__)
	int suspended_state;             /* RO: suspended stream state */
#else
	snd_pcm_state_t suspended_state; /* RO: suspended stream state */
#endif
	struct __snd_timespec audio_tstamp; /* from sample counter or wall clock */
};

struct __snd_pcm_mmap_control {
	snd_pcm_uframes_t appl_ptr;	/* RW: appl ptr (0...boundary-1) */
	snd_pcm_uframes_t avail_min;	/* RW: min available frames for wakeup */
};

#define SNDRV_PCM_SYNC_PTR_HWSYNC	(1<<0)	/* execute hwsync */
#define SNDRV_PCM_SYNC_PTR_APPL		(1<<1)	/* get appl_ptr from driver (r/w op) */
#define SNDRV_PCM_SYNC_PTR_AVAIL_MIN	(1<<2)	/* get avail_min from driver */

struct __snd_pcm_sync_ptr {
	unsigned int flags;
	union {
		struct __snd_pcm_mmap_status status;
		unsigned char reserved[64];
	} s;
	union {
		struct __snd_pcm_mmap_control control;
		unsigned char reserved[64];
	} c;
};

#if defined(__BYTE_ORDER) ? __BYTE_ORDER == __BIG_ENDIAN : defined(__BIG_ENDIAN)
typedef char __pad_before_uframe[sizeof(__u64) - sizeof(snd_pcm_uframes_t)];
typedef char __pad_after_uframe[0];
#endif

#if defined(__BYTE_ORDER) ? __BYTE_ORDER == __LITTLE_ENDIAN : defined(__LITTLE_ENDIAN)
typedef char __pad_before_uframe[0];
typedef char __pad_after_uframe[sizeof(__u64) - sizeof(snd_pcm_uframes_t)];
#endif

struct __snd_pcm_mmap_status64 {
#if defined(__QNX__)
	int state;                  /* RO: state - SNDRV_PCM_STATE_XXXX */
#else
	snd_pcm_state_t state;      /* RO: state - SNDRV_PCM_STATE_XXXX */
#endif
	__u32 pad1;                 /* Needed for 64 bit alignment */
	__pad_before_uframe __pad1;
	snd_pcm_uframes_t hw_ptr;   /* RO: hw ptr (0...boundary-1) */
	__pad_after_uframe __pad2;
	struct __snd_timespec64 tstamp; /* Timestamp */
#if defined(__QNX__)
	int suspended_state;            /* RO: suspended stream state */
#else
	snd_pcm_state_t suspended_state;/* RO: suspended stream state */
#endif
	__u32 pad3;                     /* Needed for 64 bit alignment */
	struct __snd_timespec64 audio_tstamp; /* sample counter or wall clock */
};

struct __snd_pcm_mmap_control64 {
	__pad_before_uframe __pad1;
	snd_pcm_uframes_t appl_ptr;	 /* RW: appl ptr (0...boundary-1) */
	__pad_before_uframe __pad2;

	__pad_before_uframe __pad3;
	snd_pcm_uframes_t  avail_min;	 /* RW: min available frames for wakeup */
	__pad_after_uframe __pad4;
};

struct __snd_pcm_sync_ptr64 {
	__u32 flags;
	__u32 pad1;
	union {
		struct __snd_pcm_mmap_status64 status;
		unsigned char reserved[64];
	} s;
	union {
		struct __snd_pcm_mmap_control64 control;
		unsigned char reserved[64];
	} c;
};

#if defined(__QNX__)
typedef struct snd_pcm_mmap_status snd_pcm_mmap_status_t;
typedef struct snd_pcm_mmap_control snd_pcm_mmap_control_t;
typedef struct snd_pcm_shm_state_handles {
	shm_handle_t status_handle;
	shm_handle_t control_handle;
} snd_pcm_shm_state_handles_t;

typedef struct {
	volatile snd_pcm_uframes_t *appl_ptr;
	volatile snd_pcm_uframes_t *hw_ptr;
	int state;                  /* RO: state - SNDRV_PCM_STATE_XXXX */
} snd_pcm_mmap_frame_ptrs_t;
#endif

struct snd_xferi {
	snd_pcm_sframes_t result;
	void *buf;
	snd_pcm_uframes_t frames;
};

struct snd_xfern {
	snd_pcm_sframes_t result;
	void * *bufs;
	snd_pcm_uframes_t frames;
};

enum {
	SNDRV_PCM_TSTAMP_TYPE_GETTIMEOFDAY = 0,	/* gettimeofday equivalent */
	SNDRV_PCM_TSTAMP_TYPE_MONOTONIC,	/* posix_clock_monotonic equivalent */
	SNDRV_PCM_TSTAMP_TYPE_MONOTONIC_RAW,    /* monotonic_raw (no NTP) */
	SNDRV_PCM_TSTAMP_TYPE_LAST = SNDRV_PCM_TSTAMP_TYPE_MONOTONIC_RAW,
};

/* channel positions */
enum {
	SNDRV_CHMAP_UNKNOWN = 0,
	SNDRV_CHMAP_NA,		/* N/A, silent */
	SNDRV_CHMAP_MONO,	/* mono stream */
	/* this follows the alsa-lib mixer channel value + 3 */
	SNDRV_CHMAP_FL,		/* front left */
	SNDRV_CHMAP_FR,		/* front right */
	SNDRV_CHMAP_RL,		/* rear left */
	SNDRV_CHMAP_RR,		/* rear right */
	SNDRV_CHMAP_FC,		/* front center */
	SNDRV_CHMAP_LFE,	/* LFE */
	SNDRV_CHMAP_SL,		/* side left */
	SNDRV_CHMAP_SR,		/* side right */
	SNDRV_CHMAP_RC,		/* rear center */
	/* new definitions */
	SNDRV_CHMAP_FLC,	/* front left center */
	SNDRV_CHMAP_FRC,	/* front right center */
	SNDRV_CHMAP_RLC,	/* rear left center */
	SNDRV_CHMAP_RRC,	/* rear right center */
	SNDRV_CHMAP_FLW,	/* front left wide */
	SNDRV_CHMAP_FRW,	/* front right wide */
	SNDRV_CHMAP_FLH,	/* front left high */
	SNDRV_CHMAP_FCH,	/* front center high */
	SNDRV_CHMAP_FRH,	/* front right high */
	SNDRV_CHMAP_TC,		/* top center */
	SNDRV_CHMAP_TFL,	/* top front left */
	SNDRV_CHMAP_TFR,	/* top front right */
	SNDRV_CHMAP_TFC,	/* top front center */
	SNDRV_CHMAP_TRL,	/* top rear left */
	SNDRV_CHMAP_TRR,	/* top rear right */
	SNDRV_CHMAP_TRC,	/* top rear center */
	/* new definitions for UAC2 */
	SNDRV_CHMAP_TFLC,	/* top front left center */
	SNDRV_CHMAP_TFRC,	/* top front right center */
	SNDRV_CHMAP_TSL,	/* top side left */
	SNDRV_CHMAP_TSR,	/* top side right */
	SNDRV_CHMAP_LLFE,	/* left LFE */
	SNDRV_CHMAP_RLFE,	/* right LFE */
	SNDRV_CHMAP_BC,		/* bottom center */
	SNDRV_CHMAP_BLC,	/* bottom left center */
	SNDRV_CHMAP_BRC,	/* bottom right center */
	SNDRV_CHMAP_LAST = SNDRV_CHMAP_BRC,
};

#define SNDRV_CHMAP_POSITION_MASK       0xffff
#define SNDRV_CHMAP_PHASE_INVERSE       (0x01 << 16)
#define SNDRV_CHMAP_DRIVER_SPEC         (0x02 << 16)

#define SNDRV_PCM_IOCTL_PVERSION        _IOR('A', 0x00, int)
#define SNDRV_PCM_IOCTL_INFO            _IOR('A', 0x01, struct snd_pcm_info)
#define SNDRV_PCM_IOCTL_TSTAMP          _IOW('A', 0x02, int)
#define SNDRV_PCM_IOCTL_TTSTAMP         _IOW('A', 0x03, int)
#define SNDRV_PCM_IOCTL_USER_PVERSION   _IOW('A', 0x04, int)
#define SNDRV_PCM_IOCTL_HW_REFINE       _IOWR('A', 0x10, struct snd_pcm_hw_params)
#define SNDRV_PCM_IOCTL_HW_PARAMS       _IOWR('A', 0x11, struct snd_pcm_hw_params)
#define SNDRV_PCM_IOCTL_HW_FREE         _IO('A', 0x12)
#define SNDRV_PCM_IOCTL_SW_PARAMS       _IOWR('A', 0x13, struct snd_pcm_sw_params)
#define SNDRV_PCM_IOCTL_GET_SW_PARAMS   _IOR('A', 0x13, struct snd_pcm_sw_params)
#define SNDRV_PCM_IOCTL_STATUS          _IOR('A', 0x20, struct snd_pcm_status)
#define SNDRV_PCM_IOCTL_DELAY           _IOR('A', 0x21, snd_pcm_sframes_t)
#define SNDRV_PCM_IOCTL_HWSYNC          _IO('A', 0x22)
#define __SNDRV_PCM_IOCTL_SYNC_PTR      _IOWR('A', 0x23, struct __snd_pcm_sync_ptr)
#define __SNDRV_PCM_IOCTL_SYNC_PTR64    _IOWR('A', 0x23, struct __snd_pcm_sync_ptr64)
#define SNDRV_PCM_IOCTL_SYNC_PTR        _IOWR('A', 0x23, struct snd_pcm_sync_ptr)
#define SNDRV_PCM_IOCTL_STATUS_EXT      _IOWR('A', 0x24, struct snd_pcm_status)
#define SNDRV_PCM_IOCTL_CHANNEL_INFO    _IOR('A', 0x32, struct snd_pcm_channel_info)
#define SNDRV_PCM_IOCTL_PREPARE         _IO('A', 0x40)
#define SNDRV_PCM_IOCTL_RESET           _IO('A', 0x41)
#define SNDRV_PCM_IOCTL_START           _IO('A', 0x42)
#define SNDRV_PCM_IOCTL_DROP            _IO('A', 0x43)
#define SNDRV_PCM_IOCTL_DRAIN           _IO('A', 0x44)
#define SNDRV_PCM_IOCTL_PAUSE           _IOW('A', 0x45, int)
#define SNDRV_PCM_IOCTL_REWIND          _IOW('A', 0x46, snd_pcm_uframes_t)
#define SNDRV_PCM_IOCTL_RESUME          _IO('A', 0x47)
#define SNDRV_PCM_IOCTL_XRUN            _IO('A', 0x48)
#define SNDRV_PCM_IOCTL_FORWARD         _IOW('A', 0x49, snd_pcm_uframes_t)
#define SNDRV_PCM_IOCTL_WRITEI_FRAMES   _IOW('A', 0x50, struct snd_xferi)
#define SNDRV_PCM_IOCTL_READI_FRAMES    _IOR('A', 0x51, struct snd_xferi)
#define SNDRV_PCM_IOCTL_WRITEN_FRAMES   _IOW('A', 0x52, struct snd_xfern)
#define SNDRV_PCM_IOCTL_READN_FRAMES    _IOR('A', 0x53, struct snd_xfern)
#if defined(__QNX__)
#define SNDRV_PCM_IOCTL_LINK            _IOW ('A', 0x60, snd_pcm_link_info_t)
#else
#define SNDRV_PCM_IOCTL_LINK            _IOW('A', 0x60, int)
#endif

#define SNDRV_PCM_IOCTL_UNLINK          _IO('A', 0x61)

#if defined(__QNX__)
#define     SNDRV_PCM_IOCTL_MMAP_INFO                  _IOWR('A', 0x8E, snd_pcm_mmap_info_t)
#define     SNDRV_PCM_IOCTL_MMAP_STATUS_CONTROL        _IOR ('A', 0x8F, snd_pcm_shm_state_handles_t)
#define     SNDRV_PCM_IOCTL_LINK_TRANSITION            _IO  ('A', 0x90)
#define     SNDRV_PCM_IOCTL_LINK_MODE                  _IOW ('A', 0x91, int)
#define     SNDRV_PCM_IOCTL_CM_ACTIVATE                _IOW ('A', 0x92, bool)
#define     SNDRV_PCM_IOCTL_SET_OUTPUT_CLASS           _IOW ('A', 0x93, uint32_t)
#define     SNDRV_PCM_IOCTL_READ_EVENT                 _IOR ('A', 0x94, snd_pcm_event_t)
#define     SNDRV_PCM_IOCTL_GET_FILTER                 _IOR ('A', 0x95, snd_event_filter_t)
#define     SNDRV_PCM_IOCTL_SET_FILTER                 _IOW ('A', 0x96, snd_event_filter_t)
#define     SNDRV_PCM_DCMD_GET_AP_DATA                 __DIOTF ('A', 0x97, snd_pcm_ap_param_t)
#define     SNDRV_PCM_DCMD_SET_AP_DATA                 __DIOTF ('A', 0x98, snd_pcm_ap_param_t)
#define     SNDRV_PCM_DCMD_LOAD_AP_DATASET             __DIOTF ('A', 0x99, int)
#define     SNDRV_PCM_DCMD_BEGIN_TRANSACTION           __DIOTF ('A', 0x9C, snd_pcm_transaction_t)
#define     SNDRV_PCM_DCMD_COMMIT_TRANSACTION          __DIOTF ('A', 0x9D, snd_pcm_transaction_t)
#endif


/*****************************************************************************
 *                                                                           *
 *                            MIDI v1.0 interface                            *
 *                                                                           *
 *****************************************************************************/

/*
 *  Raw MIDI section - /dev/snd/midi??
 */

#define SNDRV_RAWMIDI_VERSION		SNDRV_PROTOCOL_VERSION(2, 0, 2)

enum {
	SNDRV_RAWMIDI_STREAM_OUTPUT = 0,
	SNDRV_RAWMIDI_STREAM_INPUT,
	SNDRV_RAWMIDI_STREAM_LAST = SNDRV_RAWMIDI_STREAM_INPUT,
};

#define SNDRV_RAWMIDI_INFO_OUTPUT		0x00000001
#define SNDRV_RAWMIDI_INFO_INPUT		0x00000002
#define SNDRV_RAWMIDI_INFO_DUPLEX		0x00000004

struct snd_rawmidi_info {
	unsigned int device;		/* RO/WR (control): device number */
	unsigned int subdevice;		/* RO/WR (control): subdevice number */
	int stream;			/* WR: stream */
	int card;			/* R: card number */
	unsigned int flags;		/* SNDRV_RAWMIDI_INFO_XXXX */
	unsigned char id[64];		/* ID (user selectable) */
	unsigned char name[80];		/* name of device */
	unsigned char subname[32];	/* name of active or selected subdevice */
	unsigned int subdevices_count;
	unsigned int subdevices_avail;
	unsigned char reserved[64];	/* reserved for future use */
};

#define SNDRV_RAWMIDI_MODE_FRAMING_MASK		(7<<0)
#define SNDRV_RAWMIDI_MODE_FRAMING_SHIFT	0
#define SNDRV_RAWMIDI_MODE_FRAMING_NONE		(0<<0)
#define SNDRV_RAWMIDI_MODE_FRAMING_TSTAMP	(1<<0)
#define SNDRV_RAWMIDI_MODE_CLOCK_MASK		(7<<3)
#define SNDRV_RAWMIDI_MODE_CLOCK_SHIFT		3
#define SNDRV_RAWMIDI_MODE_CLOCK_NONE		(0<<3)
#define SNDRV_RAWMIDI_MODE_CLOCK_REALTIME	(1<<3)
#define SNDRV_RAWMIDI_MODE_CLOCK_MONOTONIC	(2<<3)
#define SNDRV_RAWMIDI_MODE_CLOCK_MONOTONIC_RAW	(3<<3)

#define SNDRV_RAWMIDI_FRAMING_DATA_LENGTH 16

struct snd_rawmidi_framing_tstamp {
	/* For now, frame_type is always 0. Midi 2.0 is expected to add new
	 * types here. Applications are expected to skip unknown frame types.
	 */
	__u8 frame_type;
	__u8 length; /* number of valid bytes in data field */
	__u8 reserved[2];
	__u32 tv_nsec;		/* nanoseconds */
	__u64 tv_sec;		/* seconds */
	__u8 data[SNDRV_RAWMIDI_FRAMING_DATA_LENGTH];
} __packed;

struct snd_rawmidi_params {
	int stream;
	size_t buffer_size;		/* queue size in bytes */
	size_t avail_min;		/* minimum avail bytes for wakeup */
	unsigned int no_active_sensing: 1; /* do not send active sensing byte in close() */
	unsigned int mode;		/* For input data only, frame incoming data */
	unsigned char reserved[12];	/* reserved for future use */
};

struct snd_rawmidi_status {
	int stream;
	__time_pad pad1;
	struct timespec tstamp;		/* Timestamp */
	size_t avail;			/* available bytes */
	size_t xruns;			/* count of overruns since last status (in bytes) */
	unsigned char reserved[16];	/* reserved for future use */
};

#define SNDRV_RAWMIDI_IOCTL_PVERSION	_IOR('W', 0x00, int)
#define SNDRV_RAWMIDI_IOCTL_INFO	_IOR('W', 0x01, struct snd_rawmidi_info)
#define SNDRV_RAWMIDI_IOCTL_USER_PVERSION _IOW('W', 0x02, int)
#define SNDRV_RAWMIDI_IOCTL_PARAMS	_IOWR('W', 0x10, struct snd_rawmidi_params)
#define SNDRV_RAWMIDI_IOCTL_STATUS	_IOWR('W', 0x20, struct snd_rawmidi_status)
#define SNDRV_RAWMIDI_IOCTL_DROP	_IOW('W', 0x30, int)
#define SNDRV_RAWMIDI_IOCTL_DRAIN	_IOW('W', 0x31, int)

/*
 *  Timer section - /dev/snd/timer
 */

#define SNDRV_TIMER_VERSION		SNDRV_PROTOCOL_VERSION(2, 0, 7)

enum {
	SNDRV_TIMER_CLASS_NONE = -1,
	SNDRV_TIMER_CLASS_SLAVE = 0,
	SNDRV_TIMER_CLASS_GLOBAL,
	SNDRV_TIMER_CLASS_CARD,
	SNDRV_TIMER_CLASS_PCM,
	SNDRV_TIMER_CLASS_LAST = SNDRV_TIMER_CLASS_PCM,
};

/* slave timer classes */
enum {
	SNDRV_TIMER_SCLASS_NONE = 0,
	SNDRV_TIMER_SCLASS_APPLICATION,
	SNDRV_TIMER_SCLASS_SEQUENCER,		/* alias */
	SNDRV_TIMER_SCLASS_OSS_SEQUENCER,	/* alias */
	SNDRV_TIMER_SCLASS_LAST = SNDRV_TIMER_SCLASS_OSS_SEQUENCER,
};

/* global timers (device member) */
#define SNDRV_TIMER_GLOBAL_SYSTEM	0
#define SNDRV_TIMER_GLOBAL_RTC		1	/* unused */
#define SNDRV_TIMER_GLOBAL_HPET		2
#define SNDRV_TIMER_GLOBAL_HRTIMER	3

/* info flags */
#define SNDRV_TIMER_FLG_SLAVE		(1<<0)	/* cannot be controlled */

struct snd_timer_id {
	int dev_class;
	int dev_sclass;
	int card;
	int device;
	int subdevice;
};

struct snd_timer_ginfo {
	struct snd_timer_id tid;	/* requested timer ID */
	unsigned int flags;		/* timer flags - SNDRV_TIMER_FLG_* */
	int card;			/* card number */
	unsigned char id[64];		/* timer identification */
	unsigned char name[80];		/* timer name */
	unsigned long reserved0;	/* reserved for future use */
	unsigned long resolution;	/* average period resolution in ns */
	unsigned long resolution_min;	/* minimal period resolution in ns */
	unsigned long resolution_max;	/* maximal period resolution in ns */
	unsigned int clients;		/* active timer clients */
	unsigned char reserved[32];
};

struct snd_timer_gparams {
	struct snd_timer_id tid;	/* requested timer ID */
	unsigned long period_num;	/* requested precise period duration (in seconds) - numerator */
	unsigned long period_den;	/* requested precise period duration (in seconds) - denominator */
	unsigned char reserved[32];
};

struct snd_timer_gstatus {
	struct snd_timer_id tid;	/* requested timer ID */
	unsigned long resolution;	/* current period resolution in ns */
	unsigned long resolution_num;	/* precise current period resolution (in seconds) - numerator */
	unsigned long resolution_den;	/* precise current period resolution (in seconds) - denominator */
	unsigned char reserved[32];
};

struct snd_timer_select {
	struct snd_timer_id id;	/* bind to timer ID */
	unsigned char reserved[32];	/* reserved */
};

struct snd_timer_info {
	unsigned int flags;		/* timer flags - SNDRV_TIMER_FLG_* */
	int card;			/* card number */
	unsigned char id[64];		/* timer identificator */
	unsigned char name[80];		/* timer name */
	unsigned long reserved0;	/* reserved for future use */
	unsigned long resolution;	/* average period resolution in ns */
	unsigned char reserved[64];	/* reserved */
};

#define SNDRV_TIMER_PSFLG_AUTO		(1<<0)	/* auto start, otherwise one-shot */
#define SNDRV_TIMER_PSFLG_EXCLUSIVE	(1<<1)	/* exclusive use, precise start/stop/pause/continue */
#define SNDRV_TIMER_PSFLG_EARLY_EVENT	(1<<2)	/* write early event to the poll queue */

struct snd_timer_params {
	unsigned int flags;		/* flags - SNDRV_TIMER_PSFLG_* */
	unsigned int ticks;		/* requested resolution in ticks */
	unsigned int queue_size;	/* total size of queue (32-1024) */
	unsigned int reserved0;		/* reserved, was: failure locations */
	unsigned int filter;		/* event filter (bitmask of SNDRV_TIMER_EVENT_*) */
	unsigned char reserved[60];	/* reserved */
};

struct snd_timer_status {
	struct timespec tstamp;		/* Timestamp - last update */
	unsigned int resolution;	/* current period resolution in ns */
	unsigned int lost;		/* counter of master tick lost */
	unsigned int overrun;		/* count of read queue overruns */
	unsigned int queue;		/* used queue size */
	unsigned char reserved[64];	/* reserved */
};

#define SNDRV_TIMER_IOCTL_PVERSION	_IOR('T', 0x00, int)
#define SNDRV_TIMER_IOCTL_NEXT_DEVICE	_IOWR('T', 0x01, struct snd_timer_id)
#define SNDRV_TIMER_IOCTL_TREAD_OLD	_IOW('T', 0x02, int)
#define SNDRV_TIMER_IOCTL_GINFO		_IOWR('T', 0x03, struct snd_timer_ginfo)
#define SNDRV_TIMER_IOCTL_GPARAMS	_IOW('T', 0x04, struct snd_timer_gparams)
#define SNDRV_TIMER_IOCTL_GSTATUS	_IOWR('T', 0x05, struct snd_timer_gstatus)
#define SNDRV_TIMER_IOCTL_SELECT	_IOW('T', 0x10, struct snd_timer_select)
#define SNDRV_TIMER_IOCTL_INFO		_IOR('T', 0x11, struct snd_timer_info)
#define SNDRV_TIMER_IOCTL_PARAMS	_IOW('T', 0x12, struct snd_timer_params)
#define SNDRV_TIMER_IOCTL_STATUS	_IOR('T', 0x14, struct snd_timer_status)
/* The following four ioctls are changed since 1.0.9 due to confliction */
#define SNDRV_TIMER_IOCTL_START		_IO('T', 0xa0)
#define SNDRV_TIMER_IOCTL_STOP		_IO('T', 0xa1)
#define SNDRV_TIMER_IOCTL_CONTINUE	_IO('T', 0xa2)
#define SNDRV_TIMER_IOCTL_PAUSE		_IO('T', 0xa3)
#define SNDRV_TIMER_IOCTL_TREAD64	_IOW('T', 0xa4, int)

#if __BITS_PER_LONG == 64
#define SNDRV_TIMER_IOCTL_TREAD SNDRV_TIMER_IOCTL_TREAD_OLD
#else
#define SNDRV_TIMER_IOCTL_TREAD ((sizeof(__kernel_long_t) >= sizeof(time_t)) ? \
				 SNDRV_TIMER_IOCTL_TREAD_OLD : \
				 SNDRV_TIMER_IOCTL_TREAD64)
#endif

struct snd_timer_read {
	unsigned int resolution;
	unsigned int ticks;
};

enum {
	SNDRV_TIMER_EVENT_RESOLUTION = 0,	/* val = resolution in ns */
	SNDRV_TIMER_EVENT_TICK,			/* val = ticks */
	SNDRV_TIMER_EVENT_START,		/* val = resolution in ns */
	SNDRV_TIMER_EVENT_STOP,			/* val = 0 */
	SNDRV_TIMER_EVENT_CONTINUE,		/* val = resolution in ns */
	SNDRV_TIMER_EVENT_PAUSE,		/* val = 0 */
	SNDRV_TIMER_EVENT_EARLY,		/* val = 0, early event */
	SNDRV_TIMER_EVENT_SUSPEND,		/* val = 0 */
	SNDRV_TIMER_EVENT_RESUME,		/* val = resolution in ns */
	/* master timer events for slave timer instances */
	SNDRV_TIMER_EVENT_MSTART = SNDRV_TIMER_EVENT_START + 10,
	SNDRV_TIMER_EVENT_MSTOP = SNDRV_TIMER_EVENT_STOP + 10,
	SNDRV_TIMER_EVENT_MCONTINUE = SNDRV_TIMER_EVENT_CONTINUE + 10,
	SNDRV_TIMER_EVENT_MPAUSE = SNDRV_TIMER_EVENT_PAUSE + 10,
	SNDRV_TIMER_EVENT_MSUSPEND = SNDRV_TIMER_EVENT_SUSPEND + 10,
	SNDRV_TIMER_EVENT_MRESUME = SNDRV_TIMER_EVENT_RESUME + 10,
};

struct snd_timer_tread {
	int event;
	__time_pad pad1;
	struct timespec tstamp;
	unsigned int val;
	__time_pad pad2;
};

/****************************************************************************
 *                                                                          *
 *        Section for driver control interface - /dev/snd/control?          *
 *                                                                          *
 ****************************************************************************/

#define SNDRV_CTL_VERSION		SNDRV_PROTOCOL_VERSION(2, 0, 8)

struct snd_ctl_card_info {
	int card;			/* card number */
	int pad;			/* reserved for future (was type) */
	unsigned char id[16];		/* ID of card (user selectable) */
	unsigned char driver[16];	/* Driver name */
	unsigned char name[32];		/* Short name of soundcard */
	unsigned char longname[80];	/* name + info text about soundcard */
	unsigned char reserved_[16];	/* reserved for future (was ID of mixer) */
	unsigned char mixername[80];	/* visual mixer identification */
	unsigned char components[128];	/* card components / fine identification, delimited with one space (AC97 etc..) */
};

#if defined(__QNX__)
#define	SNDRV_CTL_ELEM_TYPE_NONE        (0U) /* invalid */
#define	SNDRV_CTL_ELEM_TYPE_BOOLEAN     (1U) /* boolean type */
#define	SNDRV_CTL_ELEM_TYPE_INTEGER     (2U) /* integer type */
#define	SNDRV_CTL_ELEM_TYPE_ENUMERATED  (3U) /* enumerated type */
#define	SNDRV_CTL_ELEM_TYPE_BYTES       (4U) /* byte array */
#define	SNDRV_CTL_ELEM_TYPE_IEC958      (5U) /* IEC958 (S/PDIF) setup */
#define	SNDRV_CTL_ELEM_TYPE_INTEGER64   (6U) /* 64-bit integer type */
#else
typedef int __bitwise snd_ctl_elem_type_t;
#define	SNDRV_CTL_ELEM_TYPE_NONE	((snd_ctl_elem_type_t) 0) /* invalid */
#define	SNDRV_CTL_ELEM_TYPE_BOOLEAN	((snd_ctl_elem_type_t) 1) /* boolean type */
#define	SNDRV_CTL_ELEM_TYPE_INTEGER	((snd_ctl_elem_type_t) 2) /* integer type */
#define	SNDRV_CTL_ELEM_TYPE_ENUMERATED	((snd_ctl_elem_type_t) 3) /* enumerated type */
#define	SNDRV_CTL_ELEM_TYPE_BYTES	((snd_ctl_elem_type_t) 4) /* byte array */
#define	SNDRV_CTL_ELEM_TYPE_IEC958	((snd_ctl_elem_type_t) 5) /* IEC958 (S/PDIF) setup */
#define	SNDRV_CTL_ELEM_TYPE_INTEGER64	((snd_ctl_elem_type_t) 6) /* 64-bit integer type */
#endif
#define	SNDRV_CTL_ELEM_TYPE_LAST	SNDRV_CTL_ELEM_TYPE_INTEGER64

#if defined(__QNX__)
#define	SNDRV_CTL_ELEM_IFACE_CARD       (0U) /* global control */
#define	SNDRV_CTL_ELEM_IFACE_HWDEP      (1U) /* hardware dependent device */
#define	SNDRV_CTL_ELEM_IFACE_MIXER      (2U) /* virtual mixer device */
#define	SNDRV_CTL_ELEM_IFACE_PCM        (3U) /* PCM device */
#define	SNDRV_CTL_ELEM_IFACE_RAWMIDI    (4U) /* RawMidi device */
#define	SNDRV_CTL_ELEM_IFACE_TIMER      (5U) /* timer device */
#define	SNDRV_CTL_ELEM_IFACE_SEQUENCER	(6U) /* sequencer client */
#else
typedef int __bitwise snd_ctl_elem_iface_t;
#define	SNDRV_CTL_ELEM_IFACE_CARD	((snd_ctl_elem_iface_t) 0) /* global control */
#define	SNDRV_CTL_ELEM_IFACE_HWDEP	((snd_ctl_elem_iface_t) 1) /* hardware dependent device */
#define	SNDRV_CTL_ELEM_IFACE_MIXER	((snd_ctl_elem_iface_t) 2) /* virtual mixer device */
#define	SNDRV_CTL_ELEM_IFACE_PCM	((snd_ctl_elem_iface_t) 3) /* PCM device */
#define	SNDRV_CTL_ELEM_IFACE_RAWMIDI	((snd_ctl_elem_iface_t) 4) /* RawMidi device */
#define	SNDRV_CTL_ELEM_IFACE_TIMER	((snd_ctl_elem_iface_t) 5) /* timer device */
#define	SNDRV_CTL_ELEM_IFACE_SEQUENCER	((snd_ctl_elem_iface_t) 6) /* sequencer client */
#endif
#define	SNDRV_CTL_ELEM_IFACE_LAST	SNDRV_CTL_ELEM_IFACE_SEQUENCER

#define SNDRV_CTL_ELEM_ACCESS_READ		(1<<0)
#define SNDRV_CTL_ELEM_ACCESS_WRITE		(1<<1)
#define SNDRV_CTL_ELEM_ACCESS_READWRITE		(SNDRV_CTL_ELEM_ACCESS_READ|SNDRV_CTL_ELEM_ACCESS_WRITE)
#define SNDRV_CTL_ELEM_ACCESS_VOLATILE		(1<<2)	/* control value may be changed without a notification */
// (1 << 3) is unused.
#define SNDRV_CTL_ELEM_ACCESS_TLV_READ		(1<<4)	/* TLV read is possible */
#define SNDRV_CTL_ELEM_ACCESS_TLV_WRITE		(1<<5)	/* TLV write is possible */
#define SNDRV_CTL_ELEM_ACCESS_TLV_READWRITE	(SNDRV_CTL_ELEM_ACCESS_TLV_READ|SNDRV_CTL_ELEM_ACCESS_TLV_WRITE)
#define SNDRV_CTL_ELEM_ACCESS_TLV_COMMAND	(1<<6)	/* TLV command is possible */
#define SNDRV_CTL_ELEM_ACCESS_INACTIVE		(1<<8)	/* control does actually nothing, but may be updated */
#define SNDRV_CTL_ELEM_ACCESS_LOCK		(1<<9)	/* write lock */
#define SNDRV_CTL_ELEM_ACCESS_OWNER		(1<<10)	/* write lock owner */
#define SNDRV_CTL_ELEM_ACCESS_TLV_CALLBACK	(1<<28)	/* kernel use a TLV callback */
#define SNDRV_CTL_ELEM_ACCESS_USER		(1<<29) /* user space element */
/* bits 30 and 31 are obsoleted (for indirect access) */

/* for further details see the ACPI and PCI power management specification */
#define SNDRV_CTL_POWER_D0		0x0000	/* full On */
#define SNDRV_CTL_POWER_D1		0x0100	/* partial On */
#define SNDRV_CTL_POWER_D2		0x0200	/* partial On */
#define SNDRV_CTL_POWER_D3		0x0300	/* Off */
#define SNDRV_CTL_POWER_D3hot		(SNDRV_CTL_POWER_D3|0x0000)	/* Off, with power */
#define SNDRV_CTL_POWER_D3cold		(SNDRV_CTL_POWER_D3|0x0001)	/* Off, without power */

#if defined(__QNX__)
#define SNDRV_CTL_ELEM_ID_NAME_MAXLEN	60
#else
#define SNDRV_CTL_ELEM_ID_NAME_MAXLEN	44
#endif

struct snd_ctl_elem_id {
	unsigned int numid;     /* numeric identifier, zero = invalid */
#if defined(__QNX__)
	unsigned int iface;         /* interface identifier */
#else
	snd_ctl_elem_iface_t iface; /* interface identifier */
#endif
	unsigned int device;        /* device/client number */
	unsigned int subdevice;     /* subdevice (substream) number */
	unsigned char name[SNDRV_CTL_ELEM_ID_NAME_MAXLEN]; /* ASCII name of item */
	unsigned int index;         /* index of item */
};

struct snd_ctl_elem_list {
	unsigned int offset;		/* W: first element ID to get */
	unsigned int space;		/* W: count of element IDs to get */
	unsigned int used;		/* R: count of element IDs set */
	unsigned int count;		/* R: count of all elements */
	struct snd_ctl_elem_id *pids; /* R: IDs */
#if defined(__QNX__)
	unsigned char reserved[48];  /* Updated in QNX for 64bit alignment */
#else
	unsigned char reserved[50];
#endif
};

struct snd_ctl_elem_info {
	struct snd_ctl_elem_id id;  /* W: element ID */
#if defined(__QNX__)
	unsigned int type;          /* R: value type - SNDRV_CTL_ELEM_TYPE_* */
#else
	snd_ctl_elem_type_t type;   /* R: value type - SNDRV_CTL_ELEM_TYPE_* */
#endif
	unsigned int access;        /* R: value access (bitmask) - SNDRV_CTL_ELEM_ACCESS_* */
	unsigned int count;         /* count of values */
	__kernel_pid_t owner;       /* owner's PID of this control */
	union {
		struct {
			long min;           /* R: minimum value */
			long max;           /* R: maximum value */
			long step;          /* R: step (0 variable) */
		} integer;
		struct {
			long long min;      /* R: minimum value */
			long long max;      /* R: maximum value */
			long long step;     /* R: step (0 variable) */
		} integer64;
		struct {
			unsigned int items; /* R: number of items */
			unsigned int item;  /* W: item number */
			char name[64];      /* R: value name */
			__u64 names_ptr;    /* W: names list (ELEM_ADD only) */
			unsigned int names_length;
		} enumerated;
		unsigned char reserved[128];
	} value;
	unsigned char reserved[64];
};

struct snd_ctl_elem_value {
	struct snd_ctl_elem_id id;	/* W: element ID */
	unsigned int indirect: 1;	/* W: indirect access - obsoleted */
	union {
		union {
			long value[128];
			long *value_ptr;	/* obsoleted */
		} integer;
		union {
			long long value[64];
			long long *value_ptr;	/* obsoleted */
		} integer64;
		union {
			unsigned int item[128];
			unsigned int *item_ptr;	/* obsoleted */
		} enumerated;
		union {
			unsigned char data[512];
			unsigned char *data_ptr;	/* obsoleted */
		} bytes;
		struct snd_aes_iec958 iec958;
	} value;		/* RO */
	unsigned char reserved[128];
};

struct snd_ctl_tlv {
	unsigned int numid;	/* control element numeric identification */
	unsigned int length;	/* in bytes aligned to 4 */
	unsigned int tlv[0];	/* first TLV */
};

#define SNDRV_CTL_IOCTL_PVERSION	_IOR('U', 0x00, int)
#define SNDRV_CTL_IOCTL_CARD_INFO	_IOR('U', 0x01, struct snd_ctl_card_info)
#define SNDRV_CTL_IOCTL_ELEM_LIST	_IOWR('U', 0x10, struct snd_ctl_elem_list)
#define SNDRV_CTL_IOCTL_ELEM_INFO	_IOWR('U', 0x11, struct snd_ctl_elem_info)
#define SNDRV_CTL_IOCTL_ELEM_READ	_IOWR('U', 0x12, struct snd_ctl_elem_value)
#define SNDRV_CTL_IOCTL_ELEM_WRITE	_IOWR('U', 0x13, struct snd_ctl_elem_value)
#define SNDRV_CTL_IOCTL_ELEM_LOCK	_IOW('U', 0x14, struct snd_ctl_elem_id)
#define SNDRV_CTL_IOCTL_ELEM_UNLOCK	_IOW('U', 0x15, struct snd_ctl_elem_id)
#define SNDRV_CTL_IOCTL_SUBSCRIBE_EVENTS _IOWR('U', 0x16, int)
#define SNDRV_CTL_IOCTL_ELEM_ADD	_IOWR('U', 0x17, struct snd_ctl_elem_info)
#define SNDRV_CTL_IOCTL_ELEM_REPLACE	_IOWR('U', 0x18, struct snd_ctl_elem_info)
#define SNDRV_CTL_IOCTL_ELEM_REMOVE	_IOWR('U', 0x19, struct snd_ctl_elem_id)
#define SNDRV_CTL_IOCTL_TLV_READ	_IOWR('U', 0x1a, struct snd_ctl_tlv)
#define SNDRV_CTL_IOCTL_TLV_WRITE	_IOWR('U', 0x1b, struct snd_ctl_tlv)
#define SNDRV_CTL_IOCTL_TLV_COMMAND	_IOWR('U', 0x1c, struct snd_ctl_tlv)
#if defined(__QNX__)
/* Requires read/write to write in the starting device number and read back the next device number */
#define SNDRV_CTL_IOCTL_HWDEP_NEXT_DEVICE _IOWR('U', 0x20, int)
#else
#define SNDRV_CTL_IOCTL_HWDEP_NEXT_DEVICE _IOR('U', 0x20, int)
#endif
#define SNDRV_CTL_IOCTL_HWDEP_INFO	_IOR('U', 0x21, struct snd_hwdep_info)
#define SNDRV_CTL_IOCTL_PCM_NEXT_DEVICE	_IOWR('U', 0x30, int)
#define SNDRV_CTL_IOCTL_PCM_INFO	_IOWR('U', 0x31, struct snd_pcm_info)
#define SNDRV_CTL_IOCTL_PCM_PREFER_SUBDEVICE _IOW('U', 0x32, int)
#define SNDRV_CTL_IOCTL_RAWMIDI_NEXT_DEVICE _IOWR('U', 0x40, int)
#define SNDRV_CTL_IOCTL_RAWMIDI_INFO	_IOWR('U', 0x41, struct snd_rawmidi_info)
#define SNDRV_CTL_IOCTL_RAWMIDI_PREFER_SUBDEVICE _IOW('U', 0x42, int)
#define SNDRV_CTL_IOCTL_POWER		_IOWR('U', 0xd0, int)
#define SNDRV_CTL_IOCTL_POWER_STATE	_IOR('U', 0xd1, int)


#if defined(__QNX__)
#define     SNDRV_CTL_DCMD_CM_STATUS_READ         __DIOTF ('C', 0x90, char)
#define     SNDRV_CTL_IOCTL_GET_FILTER            _IOR ('C', 0x91, snd_event_filter_t)
#define     SNDRV_CTL_IOCTL_SET_FILTER            _IOW ('C', 0x92, snd_event_filter_t)
#endif

/*
 *  Read interface.
 */

enum sndrv_ctl_event_type {
	SNDRV_CTL_EVENT_ELEM = 0,
#if defined (__QNX__)
	/* Must match SND_CTL_EVENT_* definitions in alsa/control.h */
	SNDRV_CTL_EVENT_CM   = 1,
	SNDRV_CTL_EVENT_AFM  = 2,
	SNDRV_CTL_EVENT_LAST = SNDRV_CTL_EVENT_AFM,
#else
	SNDRV_CTL_EVENT_LAST = SNDRV_CTL_EVENT_ELEM,
#endif
};

#define SNDRV_CTL_EVENT_MASK_VALUE	(1<<0)	/* element value was changed */
#define SNDRV_CTL_EVENT_MASK_INFO	(1<<1)	/* element info was changed */
#define SNDRV_CTL_EVENT_MASK_ADD	(1<<2)	/* element was added */
#define SNDRV_CTL_EVENT_MASK_TLV	(1<<3)	/* element TLV tree was changed */
#define SNDRV_CTL_EVENT_MASK_REMOVE	(~0U)	/* element was removed */

#if defined(__QNX__)
typedef struct snd_ctrl_afm_event
{
    uint64_t timestamp_ms;  /* timestamp of event; number of milliseconds since the AFM started processing */
    uint32_t data;          /* event specific data (e.g. SND_CTL_READ_AFM_STATE gives the new AFM state) */
    uint16_t channel;       /* channel associated with the event */
    uint16_t devno;         /* afm device number associated with the event */
    uint8_t reserved[64];   /* must be filled with zero */
} snd_ctrl_afm_event_t;
#endif

struct snd_ctl_event {
	int type;	/* event type - SNDRV_CTL_EVENT_* */
	union {
        struct {
            unsigned int mask;
            struct snd_ctl_elem_id id;
        } elem;
#if defined(__QNX__)
        struct {
            int cmd;                         /* SND_CTL_READ_AFM_*                          */
            snd_ctrl_afm_event_t value;
        } afm;                               /* QNX Extension - Acoustic Functional Module   */
        struct {
            int cmd;                         /* SND_CTL_READ_CM_*                            */
            char output_id[64];              /* Sound concurrency management output ID/name  */
        } cm;                                /* QNX Extension - Concurrency Management       */
        unsigned char data8[84];
#else
        unsigned char data8[60];
#endif
    } data;
};

/*
 *  Control names
 */

#define SNDRV_CTL_NAME_NONE				""
#define SNDRV_CTL_NAME_PLAYBACK				"Playback "
#define SNDRV_CTL_NAME_CAPTURE				"Capture "

#define SNDRV_CTL_NAME_IEC958_NONE			""
#define SNDRV_CTL_NAME_IEC958_SWITCH			"Switch"
#define SNDRV_CTL_NAME_IEC958_VOLUME			"Volume"
#define SNDRV_CTL_NAME_IEC958_DEFAULT			"Default"
#define SNDRV_CTL_NAME_IEC958_MASK			"Mask"
#define SNDRV_CTL_NAME_IEC958_CON_MASK			"Con Mask"
#define SNDRV_CTL_NAME_IEC958_PRO_MASK			"Pro Mask"
#define SNDRV_CTL_NAME_IEC958_PCM_STREAM		"PCM Stream"
#define SNDRV_CTL_NAME_IEC958(expl,direction,what)	"IEC958 " expl SNDRV_CTL_NAME_##direction SNDRV_CTL_NAME_IEC958_##what

#if defined(__QNX__)
typedef enum _snd_pcm_rates_bit {
	SND_PCM_RATEBIT_OFFS_UNKNOWN = -1,
	SND_PCM_RATEBIT_OFFS_8000 = 0,
	SND_PCM_RATEBIT_OFFS_11025,
	SND_PCM_RATEBIT_OFFS_16000,
	SND_PCM_RATEBIT_OFFS_22050,
	SND_PCM_RATEBIT_OFFS_24000,
	SND_PCM_RATEBIT_OFFS_32000,
	SND_PCM_RATEBIT_OFFS_44100,
	SND_PCM_RATEBIT_OFFS_48000,
	SND_PCM_RATEBIT_OFFS_64000,
	SND_PCM_RATEBIT_OFFS_88200,
	SND_PCM_RATEBIT_OFFS_96000,
	SND_PCM_RATEBIT_OFFS_176400,
	SND_PCM_RATEBIT_OFFS_192000,
	SND_PCM_RATEBIT_OFFS_CONTINUOUS = 30,
	SND_PCM_RATEBIT_OFFS_KNOT = 31,
	SND_PCM_RATEBIT_OFFS_LAST = SND_PCM_RATEBIT_OFFS_KNOT,
} snd_pcm_rates_bit_t;

/* PCM sample rate bit masks */
#define	SND_PCM_RATEBIT_8000                 (1U << SND_PCM_RATEBIT_OFFS_8000)
#define	SND_PCM_RATEBIT_11025                (1U << SND_PCM_RATEBIT_OFFS_11025)
#define	SND_PCM_RATEBIT_16000                (1U << SND_PCM_RATEBIT_OFFS_16000)
#define	SND_PCM_RATEBIT_22050                (1U << SND_PCM_RATEBIT_OFFS_22050)
#define	SND_PCM_RATEBIT_24000                (1U << SND_PCM_RATEBIT_OFFS_24000)
#define	SND_PCM_RATEBIT_32000                (1U << SND_PCM_RATEBIT_OFFS_32000)
#define	SND_PCM_RATEBIT_44100                (1U << SND_PCM_RATEBIT_OFFS_44100)
#define	SND_PCM_RATEBIT_48000                (1U << SND_PCM_RATEBIT_OFFS_48000)
#define	SND_PCM_RATEBIT_64000                (1U << SND_PCM_RATEBIT_OFFS_64000)
#define	SND_PCM_RATEBIT_88200                (1U << SND_PCM_RATEBIT_OFFS_88200)
#define	SND_PCM_RATEBIT_96000                (1U << SND_PCM_RATEBIT_OFFS_96000)
#define	SND_PCM_RATEBIT_176400               (1U << SND_PCM_RATEBIT_OFFS_176400)
#define	SND_PCM_RATEBIT_192000               (1U << SND_PCM_RATEBIT_OFFS_192000)
#define	SND_PCM_RATEBIT_CONTINUOUS           (1U << SND_PCM_RATEBIT_OFFS_CONTINUOUS)
#define	SND_PCM_RATEBIT_KNOT                 (1U << SND_PCM_RATEBIT_OFFS_KNOT)

#endif

#endif /* __SOUND_ASOUND_H */
