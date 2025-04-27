#ifndef CSD2_MEDIA_FORMAT_H
#define CSD2_MEDIA_FORMAT_H

/*
  @file csd2_media_format.h
  @author
  @date
  @brief define media format configuration payload for raw PCM and compress 
format.
 */

/*************************************************************************
  Copyright (c) 2019-2020 by Qualcomm Technologies, Inc. and/or its
  subsidiaries. All rights reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
**************************************************************************/

/*=========================================================================
                      edit history for module
  this section contains comments describing changes made to this module.
  notice that changes are listed in reverse chronological order.
  when				who				what, where, why
  -----------     --------		------------------------------------------
  06/16/2020        lkathy      Edited for Agile release (Rev. AA)
  11/30/2019        congt       Initial version
=========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

#include "mmdefs.h"


/** @ingroup csd2_format_macros
  Maximum number of channels supported. */
#define CSD2_MAX_CHANNELS_NUMBER 32

/** @addtogroup csd2_format_datatypes
@{ */

/**
  Audio channel map enumeration.
 */
typedef enum {
  CSD2_CHMAP_CHANNEL_FL = 1,      /**< Front left channel. */
  CSD2_CHMAP_CHANNEL_FR = 2,      /**< Front right channel. */
  CSD2_CHMAP_CHANNEL_C = 3,       /**< Front center channel. */
  CSD2_CHMAP_CHANNEL_LS = 4,      /**< Left surround channel. */
  CSD2_CHMAP_CHANNEL_RS = 5,      /**< Right surround channel. */
  CSD2_CHMAP_CHANNEL_LFE = 6,     /**< Low frequency effect channel. */
  CSD2_CHMAP_CHANNEL_CS = 7,     /**< Center surround channel. */
  CSD2_CHMAP_CHANNEL_LB = 8,      /**< Rear left channel. */
  CSD2_CHMAP_CHANNEL_RB = 9,      /**< Rear right channel. */
  CSD2_CHMAP_CHANNEL_TS = 10,     /**< Top surround channel. */
  CSD2_CHMAP_CHANNEL_TFC = 11,    /**< Top front center channel, or center vertical
                                       height channel.*/
  CSD2_CHMAP_CHANNEL_MS = 12,     /**< Mono surround channel. */
  CSD2_CHMAP_CHANNEL_FLC = 13,    /**< Front left of center channel. */
  CSD2_CHMAP_CHANNEL_FRC = 14,    /**< Front right of center channel. */
  CSD2_CHMAP_CHANNEL_RLC = 15,    /**< Rear left of center channel. */
  CSD2_CHMAP_CHANNEL_RRC = 16,    /**< Rear right of center channel. */
  CSD2_CHMAP_CHANNEL_LFE2 = 17,   /**< Secondary low frequency effect channel. */
  CSD2_CHMAP_CHANNEL_SL = 18,     /**< Side left channel. */
  CSD2_CHMAP_CHANNEL_SR = 19,     /**< Side right channel. */
  CSD2_CHMAP_CHANNEL_TFL = 20,    /**< Top front left channel, or left vertical height
                                       channel */
  CSD2_CHMAP_CHANNEL_TFR = 21,    /**< Top front right channel, or right vertical height
                                       channel. */
  CSD2_CHMAP_CHANNEL_TC = 22,     /**< Top center channel. */
  CSD2_CHMAP_CHANNEL_TBL = 23,    /**< Top back left channel. */
  CSD2_CHMAP_CHANNEL_TBR = 24,    /**< Top back right channel. */
  CSD2_CHMAP_CHANNEL_TSL = 25,    /**< Top side left channel. */
  CSD2_CHMAP_CHANNEL_TSR = 26,    /**< Top side right channel. */
  CSD2_CHMAP_CHANNEL_TBC = 27,    /**< Top back center channel. */
  CSD2_CHMAP_CHANNEL_BFC = 28,    /**< Bottom front center channel. */
  CSD2_CHMAP_CHANNEL_BFL = 29,    /**< Bottom front left channel. */
  CSD2_CHMAP_CHANNEL_BFR = 30,    /**< Bottom front right channel. */
  CSD2_CHMAP_CHANNEL_LW = 31,     /**< Left wide channel. */
  CSD2_CHMAP_CHANNEL_RW = 32,     /**< Right wide channel. */
  CSD2_CHMAP_CHANNEL_LSD = 33,    /**< Left side direct channel. */
  CSD2_CHMAP_CHANNEL_RSD = 34,    /**< Right side direct channel. */
  CSD2_CHMAP_CUSTOM_1 = 48,       /**< Custom channel mapping 1. */
  CSD2_CHMAP_CUSTOM_2 = 49,       /**< */
  CSD2_CHMAP_CUSTOM_3 = 50,       /**< */
  CSD2_CHMAP_CUSTOM_4 = 51,       /**< */
  CSD2_CHMAP_CUSTOM_5 = 52,       /**< */
  CSD2_CHMAP_CUSTOM_6 = 53,       /**< */
  CSD2_CHMAP_CUSTOM_7 = 54,       /**< */
  CSD2_CHMAP_CUSTOM_8 = 55,       /**< */
  CSD2_CHMAP_CUSTOM_9 = 56,       /**< */
  CSD2_CHMAP_CUSTOM_10= 57,       /**< */
  CSD2_CHMAP_CUSTOM_11 = 59,      /**< */
  CSD2_CHMAP_CUSTOM_12= 60,       /**< */
  CSD2_CHMAP_CUSTOM_13= 61,       /**< */
  CSD2_CHMAP_CUSTOM_14= 62,       /**< */
  CSD2_CHMAP_CUSTOM_15= 63,       /**< */
  CSD2_CHMAP_MAXIMUM,
} csd2_channel_map;

/**
  Supported media formats.
 */
typedef enum {
  CSD2_MEDIA_FORMAT_PCM,          /**< */
  CSD2_MEDIA_FORMAT_AAC,          /**< */
  CSD2_MEDIA_FORMAT_MP3,          /**< */
} csd2_audio_fmt_t;
/** @} *//* end_addtogroup csd2_format_datatypes */

/** @addtogroup csd2_format_macros
@{ */

/** 16 bits per sample word size. */
#define CSD2_BITS_PER_SAMPLE_16        16

/** 24 bits per sample word size. */
#define CSD2_BITS_PER_SAMPLE_24        24

/** 32 bits per sample word size. */
#define CSD2_BITS_PER_SAMPLE_32        32

/** Channel number value is 1. */
#define CSD2_CHANNELS_1                 1

/** Channel number value is 2. */
#define CSD2_CHANNELS_2                 2

/** Channel number value is 3. */
#define CSD2_CHANNELS_3                 3

/** Channel number value is 4. */
#define CSD2_CHANNELS_4                 4

/** Channel number value is 6. */
#define CSD2_CHANNELS_5_1               6

/** Channel number values is 8. */
#define CSD2_CHANNELS_8                 8

/** Channel number values is 16. */
#define CSD2_CHANNELS_16                16

/** Channel number values is 32. */
#define CSD2_CHANNELS_32                32

/* Bytes per sample. */
/** 2 bytes per sample. */
#define CSD2_BYTES_PER_SAMPLE_TWO        2

/** 3 bytes per sample. */
#define CSD2_BYTES_PER_SAMPLE_THREE      3

/** 4 bytes per sample. */
#define CSD2_BYTES_PER_SAMPLE_FOUR       4


/** Bit width is 16 (actual width of the sample in a word). */
#define CSD2_BIT_WIDTH_16                16

/** Bit width is 24 (actual width of the sample in a word). */
#define CSD2_BIT_WIDTH_24                24

/** Bit width is 32 (actual width of the sample in a word). */
#define CSD2_BIT_WIDTH_32                32


/** Alignment value is 1. */
#define CSD2_PCM_LSB_ALIGNED             1

/** Alignment value is 2. */
#define CSD2_PCM_MSB_ALIGNED             2


 /** Q factor is 15. */
#define CSD2_PCM_Q_FACTOR_15             15

 /** Q factor is 23. */
#define CSD2_PCM_Q_FACTOR_23             23

 /** Q factor is 27. */
#define CSD2_PCM_Q_FACTOR_27             27

 /** Q factor is 31. */
#define CSD2_PCM_Q_FACTOR_31             31

/** Shift factor between Q31 and Q28 conversion for 32-bit P.
  @hideinitializer
 */
#define CSD2_PCM_QFORMAT_SHIFT_FACTOR     (CSD2_PCM_Q_FACTOR_31 - CSD2_PCM_Q_FACTOR_27)

/** Sample rate is 8 kHz. */
#define CSD2_SAMPLE_RATE_8K               8000

/** Sample rate is 11.025 kHz. */
#define CSD2_SAMPLE_RATE_11_025K          11025

/** Sample rate is 12 kHz. */
#define CSD2_SAMPLE_RATE_12K              12000

/** Sample rate is 16 kHz. */
#define CSD2_SAMPLE_RATE_16K              16000

/** Sample rate is 22.05 kHz. */
#define CSD2_SAMPLE_RATE_22_05K           22050

/** Sample rate is 24 kHz. */
#define CSD2_SAMPLE_RATE_24K              24000

/** Sample rate is 32 kHz. */
#define CSD2_SAMPLE_RATE_32K              32000

/** Sample rate is 44.1 kHz. */
#define CSD2_SAMPLE_RATE_44_1K            44100

/** Sample rate is 48 kHz. */
#define CSD2_SAMPLE_RATE_48K              48000

/** Sample rate is 88.2 kHz. */
#define CSD2_SAMPLE_RATE_88_2K            88200

/** Sample rate is 96 kHz. */
#define CSD2_SAMPLE_RATE_96K              96000

/** Sample rate is 176.4 kHz.*/
#define CSD2_SAMPLE_RATE_176_4K           176400

/** Sample rate is 192 kHz. */
#define CSD2_SAMPLE_RATE_192K             192000

/** Sample rate is 352.8 kHz. */
#define CSD2_SAMPLE_RATE_352_8K           352800

/** Sample rate is 384 kHz. */
#define CSD2_SAMPLE_RATE_384K             384000


/** Little Endianness value. */
#define CSD2_PCM_LITTLE_ENDIAN                 1

/** Big Endianness value. */
#define CSD2_PCM_BIG_ENDIAN                    2

/* Interleaving values */
/** Interleaved pulse code modulation (PCM). */
#define CSD2_PCM_INTERLEAVED                           1

/**
  Packed deinterleaved PCM.

  A buffer of maximum size M with C channels and
  N/C actual bytes per channel is deinterleaved-packed if (M - N) is zero. */
#define CSD2_PCM_DEINTERLEAVED_PACKED                  2

/**
  Unpacked deinterleaved PCM.

  A buffer of maximum size M with C channels and N/C actual bytes per channel
  is deinterleaved-unpacked if (M - N) is not zero.

  Alternatively, each channel has its own buffers with an actual length less
  than the maximum length.
 */
#define CSD2_PCM_DEINTERLEAVED_UNPACKED                3

/* Data formats */
/** Data format is a fixed point. */
#define CSD2_DATA_FORMAT_FIXED_POINT                   1

/** Data format is IEC61937 packetized stream.

  Data has properties such as sample rate, number of channels
  bit-width like PCM, etc. */
#define CSD2_DATA_FORMAT_IEC61937_PACKETIZED           2

/** Data format is IEC60958 packetized stream.

  Data has properties such as sample rate, number of channels, bit-width
  like PCM, etc. */
#define CSD2_DATA_FORMAT_IEC60958_PACKETIZED           3

/** Data format is direct stream digital (DSD) over PCM stream.

  Data has properties such as sample rate, number of channels, bit-width
  like PCM, etc. */
#define CSD2_DATA_FORMAT_DSD_OVER_PCM                  4

/** Data format is generic compressed stream.

  Data has properties such as sample rate, number of channels, bit-width like
  PCM, etc.*/
#define CSD2_DATA_FORMAT_GENERIC_COMPRESSED            5

/** Data format is raw compressed stream.

  Data does not have properties such as sample rate, number of channels, and
  bit-width like PCM. */
#define CSD2_DATA_FORMAT_RAW_COMPRESSED                6

/** Compressed bitstreams packetized like PCM using a Qualcomm
    Technologies, Inc. (QTI) designed packetizer. */
#define CSD2_DATA_FORMAT_COMPR_OVER_PCM_PACKETIZED     7
/** @} *//* end_addtogroup csd2_format_macros */

/** @addtogroup csd2_format_datatypes
@{ */

/**
  Input media format block definition.
 */
struct csd2_media_fmt_input_pcm {
    uint32_t sample_rate;
    /**< Number of samples per second.

         @values
         - Default: 0
         - Range: 0-384000 Hz
         - Policy: Basic */

    uint16_t bit_width;
    /**< Bit width of each sample.

         @values
         - Default: 0
         - Range list: INVALID_VALUE = 0, 16, 24, 32
         - Policy: Basic */

    uint16_t num_channels;
    /**< Number of channels.

         @values
         - Default: 0
         - Range: 0-32
         - Policy: Basic */

     uint8_t channel_mapping[CSD2_MAX_CHANNELS_NUMBER];
     /**< Channel mapping array of variable size. Size of this array depends
          on the number of channels.

          For example, channel[i] mapping describes channel i. Each element i
          of the array describes channel i inside the buffer where i is less
          than #num_channels. An unused channel is set to 0.

          @values
          - Variable array size: (num_channels*4 + 3) / 4
          - Default: 0
          - Policy: Basic @newpagetable*/
};

/**
  PCM output format block definition.
 */
struct csd2_pcm_output_config {
    uint32_t sample_rate;
    /**< Sampling rate of audio stream.

         @values
         - Default: 0
         - Range: 0-384000 Hz
         - Policy: Basic */

    uint16_t bit_width;
    /**< Bit width of each sample.

         @values
         - Default: 0
         - Range list: INVALID_VALUE = 0, 16, 24, 32
         - Policy: Basic */

    uint16_t num_channels;
    /**< Number of channels.

         @values
         - Default: 0
         - Range: 0-32
         - Policy: Basic */

    uint8_t channel_mapping[CSD2_MAX_CHANNELS_NUMBER];
    /**< Channel mapping array of variable size. Size of this array depends
         on the number of channels.

         For example, channel[i] mapping describes channel i. Each element i
         of the array describes channel i inside the buffer where i is less
         than #num_channels. An unused channel is set to 0.

         @values
         - Variable array size: (num_channels*4 + 3) / 4
         - Default: 0
         - Policy: Basic @newpagetable*/
};
/** @} *//* end_addtogroup csd2_format_datatypes */

/** @addtogroup csd2_format_macros
@{ */

/* AAC data formats */
/**
  Enumeration for the audio data transport stream in advanced audio
  coding (AAC) format.
 */
#define CSD2_AAC_FORMAT_FLAG_ADTS 0

/** Enumeration for the low overhead audio stream AAC format. */
#define CSD2_AAC_FORMAT_FLAG_LOAS 1

/** Enumeration for the audio data interchange format AAC format. */
#define CSD2_AAC_FORMAT_FLAG_ADIF 2

/** Enumeration for the raw AAC format. */
#define CSD2_AAC_FORMAT_FLAG_RAW 3

/** Enumeration for the low overhead audio transport multiplex AAC format. */
#define CSD2_AAC_FORMAT_FLAG_LATM 4

/** Enumeration for the AAC low complexity (LC) audio object type (AOT):
    - When used for aac_fmt_flag in payload_media_fmt_aac_t, this parameter
      specifies that the AOT in the AAC stream is LC.
    - When used for enc_mode in payload_enc_cfg_aac_t, this parameter specifies
      that the Encoding mode to use is LC. */
#define CSD2_AAC_AOT_LC 2

/** Enumeration for the AAC spectral band replication AOT:
    - When used for aac_fmt_flag in payload_media_fmt_aac_t, this parameter
      specifies that the AOT in the AAC stream is a spectral bandwidth
      replication (SBR).
    - When used for enc_mode in payload_enc_cfg_aac_t, this parameter specifies
      that the Encoding mode to use is AAC+. */
#define CSD2_AAC_AOT_SBR 5

/** Enumeration for the AAC parametric stereo (PS) AOT:
    - When used for aac_fmt_flag in payload_media_fmt_aac_t, this parameter
      specifies that the AOT in the AAC stream is PS.
    - When used for enc_mode in payload_enc_cfg_aac_t, this parameter specifies
      that the Encoding mode to use is efficiency AAC+. */
#define CSD2_AAC_AOT_PS 29

/** Enumeration for the bit-slice arithmetic coding (BSAC) AOT:
    - When used for aac_fmt_flag in payload_media_fmt_aac_t, this parameter
      specifies that the AOT in the AAC stream is BSAC.
    - This parameter must not be used for enc_mode in
      payload_enc_cfg_aac_t. BSAC is not supported. */
#define CSD2_AAC_AOT_BSAC 22
/** @} *//* end_addtogroup csd2_format_macros */

/** @addtogroup csd2_format_datatypes
@{ */

/**
  Output AAC media format configuration.
 */
struct csd2_media_fmt_enc_output_aac
{
    uint16_t enc_mode;
    /**< AAC Encoding mode.

         @values
         - Default: CSD2_AAC_AOT_LC
         - Range list
           - CSD2_AAC_AOT_LC = 2
           - CSD2_AAC_AOT_SBR = 5
           - CSD2_AAC_AOT_PS = 29
         - Policy: Basic */

    uint16_t aac_fmt_flag;
    /**< AAC format flag.

         @values
         - Default: CSD2_AAC_FORMAT_FLAG_ADTS
         - Range list
           - CSD2_AAC_FORMAT_FLAG_ADTS = 0
           - CSD2_AAC_FORMAT_FLAG_LOAS = 1
           - CSD2_AAC_FORMAT_FLAG_RAW = 3
           - CSD2_AAC_FORMAT_FLAG_LATM = 4
         - Policy: Basic @newpagetable*/
};

/**
  Input AAC media format configuration.
 */
struct csd2_media_fmt_input_aac
{
    uint16_t aac_fmt_flag;
    /**< Bit stream format option.

         @values
         - Range list
           - CSD2_AAC_FORMAT_FLAG_ADTS = 0
           - CSD2_AAC_FORMAT_FLAG_LOAS = 1
           - CSD2_AAC_FORMAT_FLAG_ADIF = 2
           - CSD2_AAC_FORMAT_FLAG_RAW = 3
           - CSD2_AAC_FORMAT_FLAG_LATM = 4
         - Policy: Basic */

   uint16_t audio_obj_type;
    /**< AOT present in AAC stream.

         @values
         - Default: CSD2_AAC_AOT_LC
         - Range list
           - CSD2_AAC_AOT_LC = 2
           - CSD2_AAC_AOT_SBR = 5
           - CSD2_AAC_AOT_BSAC = 22
           - CSD2_AAC_AOT_PS = 29
         - Policy: Basic */

    uint16_t num_channels;
    /**< Number of channels present in AAC stream.

         @values
         - Range list
           - PCE = 0
           - Mono = 1
           - Stereo = 2
           - 5.1 content = 6
         - Policy: Basic */

    uint16_t total_size_of_PCE_bits;
    /**< For RAW formats and if channel_config = 0, the client can send the 
         bitstream containing program configuration elements (PCE) immediately
         following this structure (in band):
          - If this field is set to 0, it is assumed that PCE information is
            available in the audio bitstream, not the band.
          - If this field is greater than 0, PCE information follows this
            structure.

         Additional bits might be required for 32-bit alignment.

         @values
         - Range: 0...0xFFFF
         - Policy: Basic */

    uint32_t sample_rate;
    /**< Number of samples per second.

         This field must be equal to the sample rate of the AAC-LC decoder
         output:
          - For MP4 or 3GP containers, this sample rate is indicated by the
            samplingFrequencyIndex field in the AudioSpecificConfig element.
          - For Audio Data Transport Stream (ADTS) format, this sample rate
            is indicated by the samplingFrequencyIndex in the ADTS) fixed header.
          - For audio data interchange format (ADIF), this sample rate is
            indicated by the samplingFrequencyIndex in program_config_element
            (present in ADIF header).

         @values
         - Default: 0
         - Range list: INVALID_VALUE = 0, 8000, 11025, 12000, 16000, 22050,
                       24000,32000,44100, 48000, 64000, 88200, 96000
         - Policy: Basic @newpagetable*/
};

/**
  Input media format block definition.
 */
struct csd2_media_fmt_input_config {
    csd2_audio_fmt_t aud_fmt_id;
    /**< Audio format ID. */

    uint32_t fmt_blk_size;
    /**< Input media format block size. */

    uint32_t data_format;
    /**< Format block payload for each format ID. */
    union {
        struct csd2_media_fmt_input_pcm pcm;    /**< PCM media format block. */
        struct csd2_media_fmt_input_aac aac;    /**< AAC media format block. */
        }u /** Payload of input media format. */;
};

/**
  Output media format block definition.
 */
struct csd2_media_fmt_output_config {
    csd2_audio_fmt_t aud_fmt_id;
    /**< Audio format ID. */

    uint32_t fmt_blk_size;
    /**< Format block payload for each format ID. */
    union {
        struct csd2_pcm_output_config pcm;
        /**< PCM encoder output configuration is the
             same as PCM output configuration #csd2_media_fmt_enc_output_aac aac. */
    }u /** Payload of output media format. @newpagetable*/;
};

/**
  Playback stream media format block definition.
 */
struct csd2_media_fmt_rx {
    struct csd2_media_fmt_input_config fmt_cfg;
    /**< Playback stream input media format block definition. */

    struct csd2_pcm_output_config pcm_output_cfg;
    /**< Playback stream output media format block definition. */
};

/**
  Captures Stream media format block definition.
 */
struct csd2_media_fmt_tx {
    struct csd2_media_fmt_output_config fmt_cfg;
    /**< Captures Stream input media format block definition. */

    struct csd2_pcm_output_config pcm_output_cfg;
    /**< Captures Stream output media format block definition. @newpagetable*/
};
/** @} *//* end_addtogroup csd2_format_datatypes */


#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* CSD2_MEDIA_FORMAT_H */
