/*
 * Copyright (c) 2019, 2023 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

typedef enum {
	PLATFORM_LA = 1, 	/**< @h2xmle_name {LA} */
	PLATFORM_LE = 2,	/**< @h2xmle_name {LE} */
}platforms;
/**
  	@h2xml_platforms{PLATFORM_LA,PLATFORM_LE}
*/

enum AllKeyIds{
	STREAMRX     = 0xA1000000,    /**< @h2xmle_name{StreamRX} */
	DEVICERX     = 0xA2000000,    /**< @h2xmle_name{DeviceRX} */
	DEVICETX     = 0xA3000000,    /**< @h2xmle_name{DeviceTX} */
	VOLUME       = 0xA4000000,    /**< @h2xmle_name{Volume} */
	SAMPLINGRATE = 0xA5000000,    /**< @h2xmle_name{SamplingRate} */
	BITWIDTH     = 0xA6000000,    /**< @h2xmle_name{BitWidth} */
	PAUSE        = 0xA7000000,    /**< @h2xmle_name{Pause} */
	MUTE         = 0xA8000000,    /**< @h2xmle_name{Mute} */
	CHANNELS     = 0xA9000000,    /**< @h2xmle_name{Channels} */
	FLUENCE      = 0xAA000000,    /**< @h2xmle_name{Fluence} */
	INSTANCE     = 0xAB000000,    /**< @h2xmle_name{Instance} */
	DEVICEPP_RX  = 0xAC000000,    /**< @h2xmle_name{DevicePP_Rx} */
	DEVICEPP_TX  = 0xAD000000,    /**< @h2xmle_name{DevicePP_Tx} */
	MEDIA_FMT_ID = 0xAE000000,    /**< @h2xmle_name{MediaFmtID} */
	STREAMPP_RX  = 0xAF000000,    /**< @h2xmle_name{StreamPP_RX} */
	STREAMPP_TX  = 0xB0000000,    /**< @h2xmle_name{StreamPP_TX} */
	STREAMTX     = 0xB1000000,    /**< @h2xmle_name{StreamTX} */
	EQUALIZER    = 0xB2000000,    /**< @h2xmle_name{Equalizer} */
	PEQ          = 0xD7000000,    /**< @h2xmle_name{PEQ} */
	SYNTH        = 0xD8000000,    /**< @h2xmle_name{SYNTH} */
	BMT          = 0xD9000000,    /**< @h2xmle_name{BMT} */
	FNB          = 0xDA000000,    /**< @h2xmle_name{FNB} */
	SUMX         = 0xDB000000,    /**< @h2xmle_name{SUMX} */
	AVC          = 0xDC000000,    /**< @h2xmle_name{AVC} */

	VMID         = 0xFF000000,    /**< @h2xmle_name{VMID} */
};

/**
	@h2xmlk_key {STREAMRX}
	@h2xmlk_description {Type of Rx Stream}
*/
enum Key_StreamRX {
	PCM_DEEP_BUFFER                 = 0xA1000001,    /**< @h2xmle_name {PCM_Deep_Buffer}*/
	PCM_RX_LOOPBACK                 = 0xA1000003,    /**< @h2xmle_name {PCM_Rx_Loopback}*/
	VOIP_RX_PLAYBACK                = 0xA1000005,    /**< @h2xmle_name {Voip_Rx}*/
	COMPRESSED_OFFLOAD_PLAYBACK     = 0xA100000A,    /**< @h2xmle_name {Compress_Offload_Playback}*/
	HFP_RX_PLAYBACK                 = 0xA100000C,    /**< @h2xmle_name {HFP_Rx_Playback}*/
	HFP_TX_PLAYBACK                 = 0xA100000D,    /**< @h2xmle_name {HFP_Tx_Playback}*/
	PCM_LL_PLAYBACK                 = 0xA100000E,    /**< @h2xmle_name {PCM_LL_Playback}*/
	PCM_OFFLOAD_PLAYBACK            = 0xA100000F,    /**< @h2xmle_name {PCM_Offload}*/
	PCM_MDF_PLAYBACK                = 0xA100F011,    /**< @h2xmle_name {PCM_MDF_Playback}*/
	BUS00_MEDIA                     = 0xA100F015,    /**< @h2xmle_name {BUS00_Media}*/
	BUS01_SYS_NOTIFICATION          = 0xA100F016,    /**< @h2xmle_name {BUS01_Sys_Notification}*/
	BUS02_NAV_GUIDANCE              = 0xA100F017,    /**< @h2xmle_name {BUS02_Nav_Guidance}*/
	BUS03_PHONE                     = 0xA100F018,    /**< @h2xmle_name {BUS03_Phone}*/
	BUS08_FRONT_PASSENGER           = 0xA100F019,    /**< @h2xmle_name {BUS08_Front_Passenger}*/
	BUS16_REAR_SEAT                 = 0xA100F01A,    /**< @h2xmle_name {BUS16_Rear_Seat}*/
};

/**
	@h2xmlk_key {STREAMTX}
	@h2xmlk_description {Type of Tx Stream}
*/
enum Key_StreamTX {
	PCM_RECORD      = 0xB1000001,    /**< @h2xmle_name {PCM_Record}*/
	PCM_TX_LOOPBACK = 0xB1000002,    /**< @h2xmle_name {PCM_Tx_Loopback}*/
	VOICE_UI        = 0xB1000003,    /**< @h2xmle_name {Voice_UI}*/
	VOIP_TX_RECORD  = 0xB1000004,    /**< @h2xmle_name {Voip_Tx}*/	
	HFP_RX_CAPTURE  = 0xB1000005,    /**< @h2xmle_name {HFP_Rx_Capture}*/
	HFP_TX_CAPTURE  = 0xB1000006,    /**< @h2xmle_name {HFP_Tx_Capture}*/
};

/**
	@h2xmlk_key {INSTANCE}
	@h2xmlk_description {Stream Instance Id}
*/
enum Key_Instance {
	INSTANCE_1 = 1, /**< @h2xmle_name {Instance_1}*/
	INSTANCE_2 = 2, /**< @h2xmle_name {Instance_2}*/
	INSTANCE_3 = 3, /**< @h2xmle_name {Instance_3}*/
	INSTANCE_4 = 4, /**< @h2xmle_name {Instance_4}*/
	INSTANCE_5 = 5, /**< @h2xmle_name {Instance_5}*/
	INSTANCE_6 = 6, /**< @h2xmle_name {Instance_6}*/
	INSTANCE_7 = 7, /**< @h2xmle_name {Instance_7}*/
	INSTANCE_8 = 8, /**< @h2xmle_name {Instance_8}*/
	INSTANCE_9 = 9, /**< @h2xmle_name {Instance_9}*/
	INSTANCE_10 = 10, /**< @h2xmle_name {Instance_10}*/
};

/**
	@h2xmlk_key {VMID}
	@h2xmlk_description {Stream VM Id}
*/
enum Key_VMID {
	PVM = 0,      /**< @h2xmle_name {PVM}*/
	LA_GVM_1 = 1, /**< @h2xmle_name {LA_GVM_1}*/
	LA_GVM_2 = 2, /**< @h2xmle_name {LA_GVM_2}*/
	LV_GVM_1 = 3, /**< @h2xmle_name {LV_GVM_1}*/
};

/**
	@h2xmlk_key {DEVICERX}
	@h2xmlk_description {Rx Device}
*/
enum Key_DeviceRX {
	SPEAKER         = 0xA2000001, /**< @h2xmle_name {Speaker}*/
	HEADPHONES      = 0xA2000002, /**< @h2xmle_name {Headphones}*/
	BT_RX           = 0xA2000003, /**< @h2xmle_name {BT_Rx}*/
	HANDSET         = 0xA2000004, /**< @h2xmle_name {Handset}*/
	USB_RX          = 0xA2000005, /**< @h2xmle_name {USB_Rx}*/
	HDMI_RX         = 0xA2000006, /**< @h2xmle_name {HDMI_Rx}*/
	SEC_CLK         = 0xA2000007, /**< @h2xmle_name {SEC_CLK}*/
	TERT_CLK        = 0xA2000008, /**< @h2xmle_name {TERT_CLK}*/
	QUAT_CLK        = 0xA2000009, /**< @h2xmle_name {QUAT_CLK}*/
	QUIN_CLK        = 0xA200000a, /**< @h2xmle_name {QUIN_CLK}*/
	MEDIA_SPKR      = 0xA200000b, /**< @h2xmle_name {Media_Speaker}*/
	NAVI_SPKR       = 0xA200000c, /**< @h2xmle_name {Navi_Speaker}*/
	A2B_SPKR        = 0xA200000d, /**< @h2xmle_name {A2B_Speaker}*/
	A2B2_SPKR       = 0xA200000e, /**< @h2xmle_name {A2B2_Speaker}*/
	PRI_CLK         = 0xA200000f, /**< @h2xmle_name {PRI_CLK}*/
	SEN_SINK        = 0xA2000010, /**< @h2xmle_name {SEN_SINK}*/
	SEP_SINK        = 0xA2000011, /**< @h2xmle_name {SEP_SINK}*/
	HS_IF0_SINK     = 0xA2000012, /**< @h2xmle_name {HS_IF0_SINK}*/
	HS_IF1_SINK     = 0xA2000013, /**< @h2xmle_name {HS_IF1_SINK}*/
	HS_IF2_SINK     = 0xA2000014, /**< @h2xmle_name {HS_IF2_SINK}*/
	HS_IF3_SINK     = 0xA2000015, /**< @h2xmle_name {HS_IF3_SINK}*/
	HS_IF4_SINK     = 0xA2000016, /**< @h2xmle_name {HS_IF4_SINK}*/
};

/**
	@h2xmlk_key {DEVICETX}
	@h2xmlk_description {Tx Device}
*/
enum Key_DeviceTX {
	SPEAKER_MIC     = 0xA3000001, /**< @h2xmle_name {Speaker_Mic}*/
	BT_TX           = 0xA3000002, /**< @h2xmle_name {BT_Tx}*/
	HEADPHONE_MIC   = 0xA3000003, /**< @h2xmle_name {Headphone_Mic}*/
	HANDSETMIC      = 0xA3000004, /**< @h2xmle_name {Handset_Mic}*/
	USB_TX          = 0xA3000005, /**< @h2xmle_name {USB_Tx}*/
	RECORD_MIC      = 0xA3000007, /**< @h2xmle_name {Record_Mic}*/
	A2B_MIC         = 0xA3000008, /**< @h2xmle_name {A2B_Mic}*/
	A2B2_MIC        = 0xA3000009, /**< @h2xmle_name {A2B2_Mic}*/
	FM_TX           = 0xA300000a, /**< @h2xmle_name {FM_TX}*/
	SEN_SOURCE      = 0XA300000b, /**< @h2xmle_name {SEN_SOURCE}*/
	SEP_SOURCE      = 0XA300000c, /**< @h2xmle_name {SEP_SOURCE}*/
	HS_IF0_SOURCE   = 0XA300000d, /**< @h2xmle_name {HS_IF0_SOURCE}*/
	HS_IF1_SOURCE   = 0XA300000e, /**< @h2xmle_name {HS_IF1_SOURCE}*/
	HS_IF2_SOURCE   = 0XA300000f, /**< @h2xmle_name {HS_IF2_SOURCE}*/
};

/**
	@h2xmlk_key {DEVICEPP_RX}
	@h2xmlk_description {Rx Device Post/Pre Processing Chain}
*/
enum Key_DevicePP_RX {
	DEVICEPP_RX_DEFAULT                   = 0xAC000001, /**< @h2xmle_name {DevicePP_Rx_Default} @h2xmlk_description {Default PP}*/
	DEVICEPP_RX_AUDIO_MBDRC               = 0xAC000002, /**< @h2xmle_name {Audio_MBDRC} @h2xmlk_description {Audio Rx MBDRC PP }*/
	DEVICEPP_RX_VOIP_MBDRC                = 0xAC000003, /**< @h2xmle_name {Voip_MBDRC} @h2xmlk_description {Voip Rx MBDRC}*/
	DEVICEPP_RX_HFPSINK                   = 0xAC000004, /**< @h2xmle_name {HFP_Sink} @h2xmlk_description {HFP Sink}*/
	DEVICEPP_RX_BUS00_MEDIA               = 0xAC000006, /**< @h2xmle_name {BUS00_Media} @h2xmlk_description {Audio Rx BUS Media and BUS Sys Notification PP }*/
	DEVICEPP_RX_BUS02_NAV_GUIDANCE        = 0xAC000007, /**< @h2xmle_name {BUS02_Nav_Guidance} @h2xmlk_description {Audio Rx BUS Nav Guidance PP }*/
	DEVICEPP_RX_BUS03_PHONE               = 0xAC000008, /**< @h2xmle_name {BUS03_Phone} @h2xmlk_description {Audio Rx BUS Phone PP }*/
	DEVICEPP_RX_BUS08_FRONT_PASSENGER     = 0xAC000009, /**< @h2xmle_name {BUS08_Front_Passenger} @h2xmlk_description {Audio Rx BUS Front Passenger PP }*/
	DEVICEPP_RX_BUS16_REAR_SEAT           = 0xAC00000A, /**< @h2xmle_name {BUS16_Rear_Seat} @h2xmlk_description {Audio Rx BUS Rear Seat PP }*/
	DEVICEPP_RX_UPMIX                     = 0xAC00000E, /**< @h2xmle_name {DevicePP_Rx_Upmix} @h2xmlk_description {Default PP}*/
	AUDIO_CAPI_LOAD                       = 0xAC0FF001, /**< @h2xmle_name {Audio_Capi_Load} @h2xmlk_description {For AUDIO_LOAD test}*/
	AUDIO_GPIO                            = 0xAC0FF002, /**< @h2xmle_name {Audio_GPIO} @h2xmlk_description {For AUDIO_GPIO test}*/
	AUDIO_IRQ_COMM                        = 0xAC0FF003, /**< @h2xmle_name {AUDIO_IRQ_COMM} @h2xmlk_description {For AUDIO_IRQ_COMM test}*/
};
/**
	@h2xmlk_key {DEVICEPP_TX}
	@h2xmlk_description {Tx Device Post/Pre Processing Chain}
*/
enum Key_DevicePP_TX {
    DEVICEPP_TX_VOICE_UI_FLUENCE_FFECNS = 0xAD000001, /**< @h2xmle_name {Voice_UI_Fluence_FFECNS} @h2xmlk_description {Used in Voice UI use-cases}*/
	DEVICEPP_TX_AUDIO_FLUENCE_SMECNS    = 0xAD000002, /**< @h2xmle_name {Audio_Fluence_SMECNS} @h2xmlk_description {Single Mic ECNS }*/
	DEVICEPP_TX_AUDIO_FLUENCE_ENDFIRE   = 0xAD000003, /**< @h2xmle_name {Audio_Fluence_Endfire} @h2xmlk_description {EndFire_ECNS - Typically used for dual mic capture scenarios}*/
	DEVICEPP_TX_AUDIO_FLUENCE_PRO       = 0xAD000004, /**< @h2xmle_name {Audio_Fluence_Pro} @h2xmlk_description {Audio Multi MIC scenarios ; at least 3 or more Micss}*/
	DEVICEPP_TX_VOIP_FLUENCE_PRO        = 0xAD000005, /**< @h2xmle_name {Voip_Fluence_Pro} @h2xmlk_description {Voip Multi MIC scenarios ; at least 3 or more Micss}*/
	DEVICEPP_TX_HFP_SINK_FLUENCE_SMECNS = 0xAD000006, /**< @h2xmle_name {HFP_Sink_Fluence_SMECNS} @h2xmlk_description {HFP Sink Single Mic ECNS }*/
	DEVICEPP_TX_VOIP_FLUENCE_SMECNS     = 0xAD000007, /**< @h2xmle_name {Voip_Fluence_SMECNS} @h2xmlk_description {Voip SMECNS scenarios ;1 mic}*/
};

/**
	@h2xmlk_key {STREAMPP_RX}
	@h2xmlk_description {Rx Stream Post/Pre Processing Chain}
*/
enum Key_StreamPP_RX {
	STREAMPP_RX_DEFAULT         = 0xAF000001, /**< @h2xmle_name {StreamPP_Rx_Default} @h2xmlk_description {Default PP Playback}*/
};

/**
	@h2xmlk_key {STREAMPP_TX}
	@h2xmlk_description {Tx Stream Post/Pre Processing Chain}
*/
enum Key_StreamPP_TX {
	STREAMPP_TX_DEFAULT = 0xB0000001, /**< @h2xmle_name {StreamPP_Tx_Default} @h2xmlk_description {Default PP Capture}*/
};

/**
	@h2xmlk_key {VOLUME}
	@h2xmlk_description {Volume}
*/
enum Key_Volume {
	LEVEL_0 = 0, /**< @h2xmle_name {Level_0}*/
	LEVEL_1 = 1, /**< @h2xmle_name {Level_1}*/
	LEVEL_2 = 2, /**< @h2xmle_name {Level_2}*/
	LEVEL_3 = 3, /**< @h2xmle_name {Level_3}*/
	LEVEL_4 = 4, /**< @h2xmle_name {Level_4}*/
	LEVEL_5 = 5, /**< @h2xmle_name {Level_5}*/
	LEVEL_6 = 6, /**< @h2xmle_name {Level_6}*/
	LEVEL_7 = 7, /**< @h2xmle_name {Level_7}*/
	LEVEL_8 = 8, /**< @h2xmle_name {Level_8}*/
	LEVEL_9 = 9, /**< @h2xmle_name {Level_9}*/
	LEVEL_10 = 10, /**< @h2xmle_name {Level_10}*/
	LEVEL_11 = 11, /**< @h2xmle_name {Level_11}*/
	LEVEL_12 = 12, /**< @h2xmle_name {Level_12}*/
	LEVEL_13 = 13, /**< @h2xmle_name {Level_13}*/
	LEVEL_14 = 14, /**< @h2xmle_name {Level_14}*/
	LEVEL_15 = 15, /**< @h2xmle_name {Level_15}*/
};
/**
	@h2xmlk_key {SAMPLINGRATE}
	@h2xmlk_sampleRate
	@h2xmlk_description {Sampling Rate}
*/
enum Key_SamplingRate {
	SAMPLINGRATE_8K = 8000,   /**< @h2xmle_sampleRate{8000} @h2xmle_name {SR_8K}*/
	SAMPLINGRATE_16K = 16000, /**< @h2xmle_sampleRate{16000} @h2xmle_name {SR_16K}*/
	SAMPLINGRATE_24K = 24000, /**< @h2xmle_sampleRate{24000} @h2xmle_name {SR_24K}*/
	SAMPLINGRATE_32K = 32000, /**< @h2xmle_sampleRate{44100} @h2xmle_name {SR_32K}*/
	SAMPLINGRATE_44K = 44100, /**< @h2xmle_sampleRate{44100} @h2xmle_name {SR_44.1K}*/
	SAMPLINGRATE_48K = 48000, /**< @h2xmle_sampleRate{48000} @h2xmle_name {SR_48K}*/
	SAMPLINGRATE_96K = 96000, /**< @h2xmle_sampleRate{96000} @h2xmle_name {SR_96K}*/
	SAMPLINGRATE_192K = 192000, /**< @h2xmle_sampleRate{192000} @h2xmle_name {SR_192K}*/
	SAMPLINGRATE_384K = 384000, /**< @h2xmle_sampleRate{384000} @h2xmle_name {SR_384K}*/
};
/**
	@h2xmlk_key {BITWIDTH}
	@h2xmlk_description {Bit Width}
*/
enum Key_BitWidth {
	BITWIDTH_16 = 16, /**< @h2xmle_name {BW_16}*/
	BITWIDTH_24 = 24, /**< @h2xmle_name {BW_24}*/
	BITWIDTH_32 = 32, /**< @h2xmle_name {BW_32}*/
};
/**
	@h2xmlk_key {PAUSE}
	@h2xmlk_description {Pause}
*/
enum Key_Pause {
	PAUSE_OFF = 0, /**< @h2xmle_name {Off}*/
	PAUSE_ON = 1, /**< @h2xmle_name {On}*/
};
/**
	@h2xmlk_key {MUTE}
	@h2xmlk_description {Mute}
*/
enum Key_Mute {
	MUTE_OFF = 0, /**< @h2xmle_name {Off}*/
	MUTE_ON = 1, /**< @h2xmle_name {On}*/
};
enum Key_Bmt
{
    BMT_OFF = 0, /**< @h2xmle_name {Off}*/
    BMT_ON = 1,  /**< @h2xmle_name {On}*/
};
enum Key_Fnb
{
    FNB_OFF = 0, /**< @h2xmle_name {Off}*/
    FNB_ON = 1,  /**< @h2xmle_name {On}*/
};
enum Key_Sumx
{
    SUMX_OFF = 0, /**< @h2xmle_name {Off}*/
    SUMX_ON = 1,  /**< @h2xmle_name {On}*/
};
enum Key_Avc
{
    AVC_OFF = 0, /**< @h2xmle_name {Off}*/
    AVC_ON = 1,  /**< @h2xmle_name {On}*/
};
enum Key_Peq
{
    PEQ_OFF = 0, /**< @h2xmle_name {Off}*/
    PEQ_ON = 1,  /**< @h2xmle_name {On}*/
};
enum Key_Synth
{
    SYNTH_OFF = 0, /**< @h2xmle_name {Off}*/
    SYNTH_ON = 1,  /**< @h2xmle_name {On}*/
};
/**
	@h2xmlk_key {CHANNELS}
	@h2xmlk_description {Channels}
*/
enum Key_Channels {
	CHANNELS_1 = 1,   /**< @h2xmle_name {CHS_1}*/
	CHANNELS_2 = 2,   /**< @h2xmle_name {CHS_2}*/
	CHANNELS_3 = 3,   /**< @h2xmle_name {CHS_3}*/
	CHANNELS_4 = 4,   /**< @h2xmle_name {CHS_4}*/
	CHANNELS_5_1 = 6, /**< @h2xmle_name {CHS_6}*/
	CHANNELS_8 = 8,	  /**< @h2xmle_name {CHS_8}*/
	CHANNELS_16 = 16, /**< @h2xmle_name {CHS_16}*/
	CHANNELS_32 = 32, /**< @h2xmle_name {CHS_32}*/
};
/**
	@h2xmlk_key {FLUENCE}
	@h2xmlk_description {Fluence}
*/
enum Key_Fluence {
	FLUENCE_OFF = 0, /**< @h2xmle_name {Off}*/
	FLUENCE_ON = 1, /**< @h2xmle_name {On}*/
};

/**
@h2xmlk_key {MEDIA_FMT_ID}
@h2xmlk_description {MediaFmtID}
*/
enum Key_MediaFmtID {
	MEDIA_FMT_ID_PCM = 0xAE000001,     /**< @h2xmle_name {PCM} @h2xmlk_description {PCM Media format}*/
	MEDIA_FMT_ID_AAC = 0xAE000002,     /**< @h2xmle_name {AAC} @h2xmlk_description {AAC Media format}*/
	MEDIA_FMT_ID_ALAC = 0xAE000003,    /**< @h2xmle_name {ALAC} @h2xmlk_description {ALAC Media format}*/
	MEDIA_FMT_ID_APE = 0xAE000004,     /**< @h2xmle_name {APE} @h2xmlk_description {APE Media format}*/
	MEDIA_FMT_ID_WMAPRO = 0xAE000005,  /**< @h2xmle_name {WMAPRO} @h2xmlk_description {WMAPRO Media format}*/
	MEDIA_FMT_ID_WMASTD = 0xAE000006,  /**< @h2xmle_name {WMASTD} @h2xmlk_description {WMASTD Media format}*/
	MEDIA_FMT_ID_FLAC = 0xAE000007,    /**< @h2xmle_name {FLAC} @h2xmlk_description {FLAC Media format}*/
	MEDIA_FMT_ID_VORBIS = 0xAE000008,  /**< @h2xmle_name {VORBIS} @h2xmlk_description {VORBIS Media format}*/
	MEDIA_FMT_ID_MP3 = 0xAE000009,     /**< @h2xmle_name {MP3} @h2xmlk_description {MP3 Media format}*/
	MEDIA_FMT_ID_AMRWBPLUS = 0xAE00000A,  /**< @h2xmle_name {AMRWBPLUS} @h2xmlk_description {AMRWBPLUS Media format}*/
};


/**
	@h2xmlk_key {EQUALIZER}
	@h2xmlk_description {Equalizer}
*/
enum Key_Equalizer {
	EQUALIZER_OFF = 0, /**< @h2xmle_name {Off}*/
	EQUALIZER_ON = 1, /**< @h2xmle_name {On}*/
};

/**
	@h2xmlk_gkeys
	@h2xmlk_description {Graph Keys}
*/
enum Graph_Keys {
	gk_StreamRX = STREAMRX,
	gk_DeviceRX = DEVICERX,
	gk_DeviceTX = DEVICETX,
	gk_DevicePP_RX = DEVICEPP_RX,
	gk_DevicePP_TX = DEVICEPP_TX,
	gk_Instance = INSTANCE,
	gk_StreamPP_RX = STREAMPP_RX,
	gk_StreamPP_TX = STREAMPP_TX,
	gk_StreamTX = STREAMTX,
	gk_VMID = VMID,
};
/**
	@h2xmlk_ckeys
	@h2xmlk_description {Calibration Keys}
*/
enum Cal_Keys {
	ck_volume = VOLUME,
	ck_samplingrate = SAMPLINGRATE,
};

#define DEVICE_HW_ENDPOINT_RX        0xC0000004
/**
	@h2xmlk_modTag {"device_hw_ep_rx",DEVICE_HW_ENDPOINT_RX}
	@h2xmlk_description {Hw EP Rx}
*/
enum HW_ENDPOINT_RX_Keys {
	tk1_hweprx = CHANNELS,
};
#define DEVICE_HW_ENDPOINT_TX        0xC0000005
/**
	@h2xmlk_modTag {"device_hw_ep_tx",DEVICE_HW_ENDPOINT_TX}
	@h2xmlk_description {Hw EP Tx}
*/
enum HW_ENDPOINT_TX_Keys {
	tk1_hweptx = CHANNELS,
};

#define     DEVICE_MUX_DEMUX        0xC000001A
/**
	@h2xmlk_modTag {"device_mux_demux",DEVICE_MUX_DEMUX}
	@h2xmlk_description {Device Mux_Demux}
*/
enum DEVICE_MUX_DEMUX_Keys {
	tk1_devmux = CHANNELS,
};

#define TAG_PAUSE       0xC0000006
/**
	@h2xmlk_modTag {"stream_pause", TAG_PAUSE}
	@h2xmlk_description {Stream Pause}
*/
enum TAG_PAUSE_Keys {
	tk1_Pause = PAUSE,
};
#define TAG_MUTE        0xC0000007
/**
	@h2xmlk_modTag {"stream_mute", TAG_MUTE}
	@h2xmlk_description {Stream Mute}
*/
enum TAG_MUTE_Keys {
	tk1_Mute = MUTE,
};

#define TAG_FLUENCE  0xC000000A
/**
	@h2xmlk_modTag {"device_fluence", TAG_FLUENCE}
	@h2xmlk_description {Fluence On/Off}
*/
enum TAG_FLUENCE_Keys {
	tk1_Fluence = FLUENCE,
};

#define TAG_STREAM_VOLUME  0xC000000D
/**
	@h2xmlk_modTag {"stream_volume", TAG_STREAM_VOLUME}
	@h2xmlk_description {Stream Volume}
*/
enum TAG_STREAM_VOLUME_Keys {
	tk1_Volume = VOLUME,
};

#define TAG_DEVICE_PP_MFC  0xC0000011
/**
	@h2xmlk_modTag {"device_pp_mfc", TAG_DEVICE_PP_MFC}
	@h2xmlk_description {Device PP MFC}
*/
enum TAG_DEVICE_PP_MFC_Keys {
	tk1_device_pp_mfc = SAMPLINGRATE,
	tk2_device_pp_mfc = BITWIDTH,
	tk3_device_pp_mfc = CHANNELS,
};

#define TAG_STREAM_PLACEHOLDER_DECODER  0xC0000012
/**
@h2xmlk_modTag {"stream_placeholder_decoder", TAG_STREAM_PLACEHOLDER_DECODER}
@h2xmlk_description {Placeholder Decoder}
*/
enum TAG_STREAM_PLACEHOLDER_DECODER_Keys {
	tk1_MediaFmtID = MEDIA_FMT_ID,
};

#define STREAM_EQUALIZER  0xC0000014
/**
@h2xmlk_modTag {"stream_equalizer", STREAM_EQUALIZER}
@h2xmlk_description {Equalizer On/Off}
*/
enum TAG_EQUALIZER_Keys {
	tk1_Equalizer = EQUALIZER,
};

#define PER_STREAM_PER_DEVICE_MFC  0xC0000019
/**
	@h2xmlk_modTag {"pspd_mfc", PER_STREAM_PER_DEVICE_MFC}
	@h2xmlk_description {Per Stream Per Device MFC}
*/
enum TAG_PER_STREAM_PER_DEVICE_MFC_Keys {
	tk1_pspd_mfc = SAMPLINGRATE,
	tk2_pspd_mfc = BITWIDTH,
	tk3_pspd_mfc = CHANNELS,
};

#define STREAM_BMT 0xC0000020
/**
@h2xmlk_modTag {"stream_bmt", STREAM_BMT}
@h2xmlk_description {BMT On/Off}TAG_STREAM_VOLUME
*/
enum TAG_BMT_Keys
{
    tk1_Bmt = BMT,
};
#define STREAM_FNB 0xC0000021
/**
@h2xmlk_modTag {"stream_fnb", STREAM_FNB}
@h2xmlk_description {FNB On/Off}
*/
enum TAG_FNB_Keys
{
    tk1_Fnb = FNB,
};
#define STREAM_SUMX 0xC0000022
/**
@h2xmlk_modTag {"stream_sumx", STREAM_SUMX}
@h2xmlk_description {SUMX On/Off}
*/
enum TAG_SUMX_Keys
{
    tk1_Sumx = SUMX,
};

#define STREAM_AVC 0xC0000024
/**
@h2xmlk_modTag {"stream_avc", STREAM_AVC}
@h2xmlk_description {Avc On/Off}
*/
enum TAG_AVC_Keys
{
    tk1_AVC = AVC,
};

#define STREAM_PEQ 0xC0000025
/**
@h2xmlk_modTag {"stream_peq", STREAM_PEQ}
@h2xmlk_description {PEQ On/Off}
*/
enum TAG_PEQ_Keys
{
	tk1_PEQ = PEQ,
};

#define STREAM_SYNTH 0xC0000026
/**
@h2xmlk_modTag {"stream_synth", STREAM_SYNTH}
@h2xmlk_description {Synth On/Off}
*/
enum TAG_SYNTH_Keys
{
	tk1_SYNTH = SYNTH,
};

/**
	@h2xmlk_modTagList
*/
enum TAGS_DEFINITIONS {
	SHMEM_ENDPOINT              = 0xC0000001, /**< @h2xmle_name {"sh_ep"} */
	STREAM_INPUT_MEDIA_FORMAT   = 0xC0000002, /**< @h2xmle_name {"stream_input_media_format" } */
	STREAM_OUTPUT_MEDIA_FORMAT  = 0xC0000003, /**< @h2xmle_name {"stream_output_media_format" } */
	DEVICE_SVA                  = 0xC0000008, /**< @h2xmle_name {"device_sva"} */
	DEVICE_ADAM                 = 0xC0000009, /**< @h2xmle_name {"device_adam"} */
	STREAM_MFC                  = 0xC000000B, /**< @h2xmle_name {"stream_mfc"} */
	DEVICE_MFC                  = 0xC000000C, /**< @h2xmle_name {"device_mfc"} */
	STREAM_PCM_DECODER          = 0xC000000E, /**< @h2xmle_name {"stream_pcm_decoder"} */
	STREAM_PCM_ENCODER          = 0xC000000F, /**< @h2xmle_name {"stream_pcm_encoder"} */
	STREAM_PCM_CONVERTER        = 0xC0000010, /**< @h2xmle_name {"stream_pcm_converter"} */
	STREAM_SPR                  = 0xC0000013, /**< @h2xmle_name {"stream_spr"} */
	STREAM_VIRTUALIZER          = 0xC0000015, /**< @h2xmle_name {"stream_virtualizer"} */
	STREAM_REVERB               = 0xC0000016, /**< @h2xmle_name {"stream_reverb"} */
	STREAM_PBE                  = 0xC0000017, /**< @h2xmle_name {"stream_pbe"} */
	STREAM_BASSBOOST            = 0xC0000018, /**< @h2xmle_name {"stream_bassboost"} */
	DATA_LOGGING_152E 			= 0xc00000F0,  /**< @h2xmle_name {"data_logging_152e"} */
	DATA_LOGGING_152F 			= 0xc00000F1,  /**< @h2xmle_name {"data_logging_152f"} */
	DATA_LOGGING_1530 			= 0xc00000F2,  /**< @h2xmle_name {"data_logging_1530"} */
	DATA_LOGGING_1531 			= 0xc00000F3,  /**< @h2xmle_name {"data_logging_1531"} */
	DATA_LOGGING_1532 			= 0xc00000F4,  /**< @h2xmle_name {"data_logging_1536"} */
	DATA_LOGGING_1533 			= 0xc00000F5,  /**< @h2xmle_name {"data_logging_1586"} */
	DATA_LOGGING_1536 			= 0xc00000F6,  /**< @h2xmle_name {"data_logging_19AF"} */
	DATA_LOGGING_1586 			= 0xc00000F7,  /**< @h2xmle_name {"data_logging_19B0"} */
	DATA_LOGGING_19AF 			= 0xc00000F8,  /**< @h2xmle_name {"data_logging_19B1"} */
	DATA_LOGGING_19B0			= 0xc00000F9,  /**< @h2xmle_name {"data_logging_1532"} */
	DATA_LOGGING_19B1			= 0xc00000FA,  /**< @h2xmle_name {"data_logging_1533"} */
	TEST_AUDIO_IRQ_COM                      = 0xC00FF001, /**< @h2xmle_name {"test_audio_irq_com"} */
	TEST_SHARED_MEM_TAG                     = 0xC00FF019, /**< @h2xmle_name {"test_shared_mem_tag"} */
	
	
};
typedef enum TAGS_DEFINITIONS TAGS_DEFINITIONS;

enum PP_MODULE_PARAMETERS {

    AUDIO_SUMX_ENABLE           = 0x800125e,
    AUDIO_OUTPUT_CONFIG         = 0x800125f,
    AUDIO_INPUT_CONFIG          = 0x8001260,
    AUDIO_SUMX_CUSTOM_COEFFS    = 0x8001261,
    AUDIO_SUMX_BASE_CONFIG      = 0x8001262,
    AUDIO_SUMX_EFFECT           = 0x8001263,
    AUDIO_SUMX_SUBWOOFER        = 0x8001264,
    AUDIO_SUMX_INPUT_GAINS      = 0x8001265,
    AUDIO_SUMX_TIMING           = 0x8001266,
    AUDIO_SUMX_MONO_DETECT      = 0x8001267,
    AUDIO_SUMX_ALT_CONVERSIONS  = 0x8001268,
    AUDIO_SUMX_OUTPUT_DELAYS    = 0x8001269,

    AUDIO_PEQ_ENABLE            = 0x800126a,
    AUDIO_PEQ_CONFIG            = 0x800126b,
    AUDIO_PEQ_PREGAIN           = 0x800126c,
    AUDIO_PEQ_COEFFS            = 0x800126d,
    
    AUDIO_BMT_ENABLE            = 0x800126e,
    AUDIO_BMT_BASE_CONFIG       = 0x800126f,
    AUDIO_BMT_SETTING           = 0x8001270,
    AUDIO_BMT_FILTERCONFIG      = 0x8001271,
    AUDIO_BMT_RAMPINGCONFIG     = 0x8001272,
    AUDIO_BMT_PREGAIN           = 0x8001273,
    AUDIO_BMT_COEFFS            = 0x8001274,
    
    AUDIO_FNB_ENABLE            = 0x8001275,
    AUDIO_FNB_BASE_CONFIG       = 0x8001276,
    AUDIO_FNB_SETTING           = 0x8001277,
    AUDIO_FNB_RAW_SETTING       = 0x8001278,
    AUDIO_FNB_RAMPINGCONFIG     = 0x8001279,
    AUDIO_FNB_TABLE_GAINS       = 0x800127a,
    AUDIO_FNB_TABLE_ASSIGNMENT  = 0x800127b,
    AUDIO_FNB_MIXER_ASSIGNMENT  = 0x800127c,  

    AUDIO_SYNTH_ENABLE          = 0x8001283,
    AUDIO_SYNTH_WAVE_TABLES     = 0x8001284,
    AUDIO_SYNTH_ENVELOPE_TABLES = 0x8001285,
    AUDIO_SYNTH_VOICE_CONFIG    = 0x8001286,
    AUDIO_SYNTH_INPUT_GAINS     = 0x8001287,
    AUDIO_SYNTH_GAINS           = 0x8001288,
    AUDIO_SYNTH_PATTERN         = 0x8001289,
    AUDIO_SYNTH_VARIABLES       = 0x800128a,
    AUDIO_SYNTH_TRIGGER         = 0x800128b,

    AUDIO_AVC_ENABLE            = 0x800128c,
    AUDIO_AVC_BASE_CONFIG       = 0x800128d,
    AUDIO_AVC_VOLUME_CURVE      = 0x800128e,
    AUDIO_AVC_SPEED_CURVES      = 0x800128f,
    AUDIO_AVC_SPEED_GAIN_CONFIG = 0x8001290,
    AUDIO_AVC_SPEED_RAMPING     = 0x8001291,
    AUDIO_AVC_LOUD_RAMPING      = 0x8001292,
    AUDIO_AVC_LOUD_COEFFS       = 0x8001293,    
    AUDIO_AVC_LOUD_DESIGN       = 0x8001294,    
    AUDIO_AVC_LOUD_BIQUADS      = 0x8001295,    
    AUDIO_AVC_VOLUME            = 0x8001296,
    AUDIO_AVC_SPEED             = 0x8001297,
    AUDIO_AVC_SELECT_SPEEDCURVE = 0x8001298,
    AUDIO_AVC_ENABLE_LOUDNESS   = 0x8001299,
    AUDIO_AVC_CURRENT_STATE     = 0x800129a,    
};
