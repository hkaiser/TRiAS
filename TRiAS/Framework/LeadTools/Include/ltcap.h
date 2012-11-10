/*[]=====================================================================[]*/
/*[]     LEADTOOLS CAPTURE DLL - Video Capture Support                   []*/
/*[]                                                                     []*/
/*[]     Copyright (c) 1991-2000 LEAD Technologies, Inc.                 []*/
/*[]     All Rights Reserved.                                            []*/
/*[]=====================================================================[]*/

/*
 * $HISTORY: $
 */

#ifndef _LTCAP_H_
#define _LTCAP_H_

#include "ltkrn.h"

#define _HEADER_ENTRY_
#include "ltpck.h"   

#ifndef WIN32
#include <compobj.h>
#endif

/************************************************************************************
 *                                                                                  *
 *                            CAPTURE FLAGS                                         *
 *                                                                                  *
 ************************************************************************************/

#define CAP_DLG_VIDCOMP       0x003  /* video compression dialog                  */
#define CAP_DLG_VIDDISPLAY    0x005  /* video display dialog                      */
#define CAP_DLG_VIDFORMAT     0x006  /* video format dialog                       */
#define CAP_DLG_VIDSOURCE     0x007  /* video source dialog                       */

#define CAP_HAS_OVERLAY       0x009  /* does capture device suport overlay        */
#define CAP_AUD_SUPPORT       0x011  /* does the driver support audio             */


/* flags used by L_CapStartFeedSound */
#define CAP_FEED_SAVEDATA     0x00000001  /* save the audio data to a file        */
#define CAP_FEED_PLAYDATA     0x00000002  /* play the audio data to the sound card*/
#define CAP_FEED_SAVEONERROR  0x00000004  /* save data even when there is an error playing data */

#define CAP_DEVICE_MAPPER     ((L_UINT)-1)/* use any suitable device                   */

#define CAP_FEED_EMPTY     0  /* the sound queue is empty. call L_CapFeedSound with more data */
#define CAP_FEED_CLOSED    1  /* the sound device has been closed */


/* Flags used  by L_CapChooseAudFormat */
#define CAP_CHOOSE_INIT       0x00000040   /* The wave format structure has been initialized */
#define CAP_CHOOSE_INPUT      0x00800000   /* Enumerate the formats compatible for input */
#define CAP_CHOOSE_OUTPUT     0x01000000   /* Enumerate the formats compatible for output */

/* values for L_CapGetMetrics */
#define CAP_METRIC_MAX_SIZE_FORMAT  50

/************************************************************************************
 *                                                                                  *
 *                            WAVE FORMATS                                          *
 *                                                                                  *
 ************************************************************************************/

#ifndef FILE_WAV_1M08
#define FILE_WAV_1M08         0x00000001       /* 11.025 kHz, Mono,   8-bit  */
#define FILE_WAV_1S08         0x00000002       /* 11.025 kHz, Stereo, 8-bit  */
#define FILE_WAV_1M16         0x00000004       /* 11.025 kHz, Mono,   16-bit */
#define FILE_WAV_1S16         0x00000008       /* 11.025 kHz, Stereo, 16-bit */
#define FILE_WAV_2M08         0x00000010       /* 22.05  kHz, Mono,   8-bit  */
#define FILE_WAV_2S08         0x00000020       /* 22.05  kHz, Stereo, 8-bit  */
#define FILE_WAV_2M16         0x00000040       /* 22.05  kHz, Mono,   16-bit */
#define FILE_WAV_2S16         0x00000080       /* 22.05  kHz, Stereo, 16-bit */
#define FILE_WAV_4M08         0x00000100       /* 44.1   kHz, Mono,   8-bit  */
#define FILE_WAV_4S08         0x00000200       /* 44.1   kHz, Stereo, 8-bit  */
#define FILE_WAV_4M16         0x00000400       /* 44.1   kHz, Mono,   16-bit */
#define FILE_WAV_4S16         0x00000800       /* 44.1   kHz, Stereo, 16-bit */
#define FILE_WAV_OTHER        0xFFFFFFFF       /* non-PCM format */
#endif


/*
   WAVE form wFormatTag IDs. Values used in as wFormatTag in WAVEFORMATDATA

   This list might be updated by Microsoft as manufacturers come up with new formats.

   This list was extracted from MMREG.H included with Visual C++ 4.2
*/
#define  CAP_WAVE_FORMAT_UNKNOWN    0x0000  /*  Microsoft Corporation  */
#define  CAP_WAVE_FORMAT_PCM        0x0001  /*  Microsoft Corporation  */
#define  CAP_WAVE_FORMAT_ADPCM      0x0002  /*  Microsoft Corporation  */
#define  CAP_WAVE_FORMAT_IBM_CVSD   0x0005  /*  IBM Corporation  */
#define  CAP_WAVE_FORMAT_ALAW       0x0006  /*  Microsoft Corporation  */
#define  CAP_WAVE_FORMAT_MULAW      0x0007  /*  Microsoft Corporation  */
#define  CAP_WAVE_FORMAT_OKI_ADPCM  0x0010  /*  OKI  */
#define  CAP_WAVE_FORMAT_DVI_ADPCM  0x0011  /*  Intel Corporation  */
#define  CAP_WAVE_FORMAT_IMA_ADPCM  (CAP_WAVE_FORMAT_DVI_ADPCM) /*  Intel Corporation  */
#define  CAP_WAVE_FORMAT_MEDIASPACE_ADPCM   0x0012  /*  Videologic  */
#define  CAP_WAVE_FORMAT_SIERRA_ADPCM       0x0013  /*  Sierra Semiconductor Corp  */
#define  CAP_WAVE_FORMAT_G723_ADPCM 0x0014  /*  Antex Electronics Corporation  */
#define  CAP_WAVE_FORMAT_DIGISTD    0x0015  /*  DSP Solutions, Inc.  */
#define  CAP_WAVE_FORMAT_DIGIFIX    0x0016  /*  DSP Solutions, Inc.  */
#define  CAP_WAVE_FORMAT_DIALOGIC_OKI_ADPCM 0x0017  /*  Dialogic Corporation  */
#define  CAP_WAVE_FORMAT_YAMAHA_ADPCM       0x0020  /*  Yamaha Corporation of America  */
#define  CAP_WAVE_FORMAT_SONARC     0x0021  /*  Speech Compression  */
#define  CAP_WAVE_FORMAT_DSPGROUP_TRUESPEECH        0x0022  /*  DSP Group, Inc  */
#define  CAP_WAVE_FORMAT_ECHOSC1    0x0023  /*  Echo Speech Corporation  */
#define  CAP_WAVE_FORMAT_AUDIOFILE_AF36     0x0024  /*    */
#define  CAP_WAVE_FORMAT_APTX       0x0025  /*  Audio Processing Technology  */
#define  CAP_WAVE_FORMAT_AUDIOFILE_AF10     0x0026  /*    */
#define  CAP_WAVE_FORMAT_DOLBY_AC2  0x0030  /*  Dolby Laboratories  */
#define  CAP_WAVE_FORMAT_GSM610     0x0031  /*  Microsoft Corporation  */
#define  CAP_WAVE_FORMAT_ANTEX_ADPCME       0x0033  /*  Antex Electronics Corporation  */
#define  CAP_WAVE_FORMAT_CONTROL_RES_VQLPC  0x0034  /*  Control Resources Limited  */
#define  CAP_WAVE_FORMAT_DIGIREAL   0x0035  /*  DSP Solutions, Inc.  */
#define  CAP_WAVE_FORMAT_DIGIADPCM  0x0036  /*  DSP Solutions, Inc.  */
#define  CAP_WAVE_FORMAT_CONTROL_RES_CR10   0x0037  /*  Control Resources Limited  */
#define  CAP_WAVE_FORMAT_NMS_VBXADPCM       0x0038  /*  Natural MicroSystems  */
#define  CAP_WAVE_FORMAT_CS_IMAADPCM 0x0039 /* Crystal Semiconductor IMA ADPCM */
#define  CAP_WAVE_FORMAT_G721_ADPCM 0x0040  /*  Antex Electronics Corporation  */
#define  CAP_WAVE_FORMAT_MPEG       0x0050  /*  Microsoft Corporation  */
#define  CAP_WAVE_FORMAT_CREATIVE_ADPCM     0x0200  /*  Creative Labs, Inc  */
#define  CAP_WAVE_FORMAT_CREATIVE_FASTSPEECH8       0x0202  /*  Creative Labs, Inc  */
#define  CAP_WAVE_FORMAT_CREATIVE_FASTSPEECH10      0x0203  /*  Creative Labs, Inc  */
#define  CAP_WAVE_FORMAT_FM_TOWNS_SND       0x0300  /*  Fujitsu Corp.  */
#define  CAP_WAVE_FORMAT_OLIGSM     0x1000  /*  Ing C. Olivetti & C., S.p.A.  */
#define  CAP_WAVE_FORMAT_OLIADPCM   0x1001  /*  Ing C. Olivetti & C., S.p.A.  */
#define  CAP_WAVE_FORMAT_OLICELP    0x1002  /*  Ing C. Olivetti & C., S.p.A.  */
#define  CAP_WAVE_FORMAT_OLISBC     0x1003  /*  Ing C. Olivetti & C., S.p.A.  */
#define  CAP_WAVE_FORMAT_OLIOPR     0x1004  /*  Ing C. Olivetti & C., S.p.A.  */


/************************************************************************************
 *                                                                                  *
 *                            STRUCTURE DEFINITIONS                                 *
 *                                                                                  *
 ************************************************************************************/

typedef struct tagCAPTUREOPTIONS
{
    L_BOOL          bHitOkToCapture;     /* user has to hit ok to capture    */
    L_UINT          wPercentDrop;        /* % of drop frames allowed         */
    L_BOOL          bCaptureAudio;       /* true to capture audio            */
    L_UINT          wVKeyToAbort;        /* key code to stop capture         */
    L_BOOL          bEnableTimeLimit;    /* true to enable a capture limit   */
    L_UINT          wTimeLimit;          /* time limit to capture            */
    L_FLOAT         fFramesPerSecond;    /* frames per second to capture     */ 
    L_BOOL          bSynchVidToAud;      /* true to sync video to audio      */
    L_BOOL          bAbortLeftMouse;     /* abort capture with left click    */
    L_BOOL          bAbortRightMouse;    /* abort capture with right click   */
} CAPTUREOPTIONS, L_FAR * pCAPTUREOPTIONS;

typedef struct tagCAPSTATUSINFO
{
    L_UINT          iWidth;             /* image width                      */
    L_UINT          iHeight;            /* image height                     */
    L_UINT32        NumFrames;          /* #frames processed                */
    L_UINT32        FramesDropped;      /* #frames dropped during capture   */
    L_UINT32        WaveSamples;        /* #waveform audio samples          */
    L_UINT32        ElapsedTime;        /* time elapsed from start of cap.  */
    HPALETTE        hPalette;           /* handle of current palette        */
} CAPSTATUSINFO, L_FAR * pCAPSTATUSINFO;

typedef struct videoData {
    L_CHAR L_FAR* lpData;                 /* pointer to locked data buffer */
    L_UINT32      dwBufferLength;         /* Length of data buffer */
    L_UINT32      dwBytesUsed;            /* Bytes actually used */
    L_UINT32      dwTimeCaptured;         /* Milliseconds from start of stream */
    L_UINT32      dwUser;                 /* for client's use */
    L_UINT32      dwFlags;                /* assorted flags (see defines) */
    L_UINT32      dwReserved[4];          /* reserved for driver */
} VIDEODATA,L_FAR * LPVIDEODATA;                                 

typedef struct waveData {
    L_CHAR L_FAR* lpData;                 /* pointer to locked data buffer */
    L_UINT32      dwBufferLength;         /* length of data buffer */
    L_UINT32      dwBytesRecorded;        /* used for input only */
    L_UINT32      dwUser;                 /* for client's use */
    L_UINT32      dwFlags;                /* assorted flags (see defines) */
    L_UINT32      dwLoops;                /* loop control counter */
    struct waveData L_FAR *lpNext;     /* reserved for driver */
    L_UINT32      reserved;               /* reserved for driver */
} WAVEDATA,L_FAR * LPWAVEDATA;

typedef struct waveFormatData
{
    L_UINT16    wFormatTag;         /* format type */
    L_UINT16    nChannels;          /* number of channels (i.e. mono, stereo...) */
    L_UINT32    nSamplesPerSec;     /* sample rate */
    L_UINT32    nAvgBytesPerSec;    /* for buffer estimation */
    L_UINT16    nBlockAlign;        /* block size of data */
    L_UINT16    wBitsPerSample;     /* number of bits per sample of mono data */
    L_UINT16    cbSize;             /* the count in bytes of the size of */
				    /* extra information (after cbSize) */
} WAVEFORMATDATA, FAR *LPWAVEFORMATDATA;

// ltsnd.h contains the structures for the non-PCM wave formats
#include "ltsnd.h"

// useful macro to find out the size of the WAVEFORMATDATA structure
#define SIZEOF_WAVEFORMATDATA(pwfx)   (sizeof(WAVEFORMATDATA) + ((CAP_WAVE_FORMAT_PCM==(pwfx)->wFormatTag)?0:(pwfx)->cbSize))

#define MIXERLINE_ENUM_AUX       0x0001
#define MIXERLINE_ENUM_WAVE_IN   0x0002
#define MIXERLINE_ENUM_WAVE_OUT  0x0004
#define MIXERLINE_ENUM_MIDI_IN   0x0008
#define MIXERLINE_ENUM_MIDI_OUT  0x0010
#define MIXERLINE_ENUM_ALL       0x0FFF

enum
{
   MIXERLINE_DST_UNDEFINED, 
   MIXERLINE_DST_DIGITAL,   
   MIXERLINE_DST_LINE,      
   MIXERLINE_DST_MONITOR,   
   MIXERLINE_DST_SPEAKERS,  
   MIXERLINE_DST_HEADPHONES,
   MIXERLINE_DST_TELEPHONE, 
   MIXERLINE_DST_WAVEIN,    
   MIXERLINE_DST_VOICEIN,   
};

enum
{
   MIXERLINE_SRC_UNDEFINED, 
   MIXERLINE_SRC_DIGITAL,   
   MIXERLINE_SRC_LINE,      
   MIXERLINE_SRC_MICROPHONE,
   MIXERLINE_SRC_SYNTHESIZER,
   MIXERLINE_SRC_COMPACTDISC,
   MIXERLINE_SRC_TELEPHONE, 
   MIXERLINE_SRC_PCSPEAKER, 
   MIXERLINE_SRC_WAVEOUT,   
   MIXERLINE_SRC_AUXILIARY, 
   MIXERLINE_SRC_ANALOG,    
};

enum
{
   MIXERLINE_TARGET_UNDEFINED,
   MIXERLINE_TARGET_WAVEOUT,  
   MIXERLINE_TARGET_WAVEIN,   
   MIXERLINE_TARGET_MIDIOUT,  
   MIXERLINE_TARGET_MIDIIN,   
   MIXERLINE_TARGET_AUX,      
};

typedef struct _MIXERLINEINFO
{
   L_CHAR   szDeviceName[32];
   L_UINT32 nDeviceID;

   L_CHAR   szDstName[64];
   L_UINT32 nDstType;
   L_UINT32 nDstID;
   L_CHAR   szDstTargetName[32];
   L_UINT32 nDstTargetType;
   L_UINT32 nDstTargetID;

   L_CHAR   szSrcName[64];
   L_UINT32 nSrcType;
   L_UINT32 nSrcID;
   L_CHAR   szSrcTargetName[32];
   L_UINT32 nSrcTargetType;
   L_UINT32 nSrcTargetID;
} MIXERLINEINFO, far *pMIXERLINEINFO;


/************************************************************************************
 *                                                                                  *
 *                            Callback Declarations                                 *
 *                                                                                  *
 ************************************************************************************/

typedef L_INT (pEXT_CALLBACK CAPVIDCALLBACK) (LPVIDEODATA pVidData,
                                              L_VOID L_FAR *pUserData);

typedef L_INT (pEXT_CALLBACK CAPAUDCALLBACK) (LPWAVEDATA pAudData,
                                              L_VOID L_FAR *pUserData);

typedef L_INT (pEXT_CALLBACK ENUMDRIVERCALLBACK) (L_INT iIndex,
                                                  L_CHAR L_FAR *szName,
                                                  L_CHAR L_FAR *szVersion,
                                                              L_VOID L_FAR *pUserData);

typedef L_INT (pEXT_CALLBACK CAPSTATCALLBACK) (L_CHAR L_FAR *lpszString,
                                               L_VOID L_FAR *pUserData);

typedef L_INT (pEXT_CALLBACK FEEDSOUNDCALLBACK) (HGLOBAL hSound,
                                                 L_UINT  uMsg,
                                                 L_VOID L_FAR *pUserData);


typedef L_VOID (pEXT_CALLBACK ENUMMIXERLINESCALLBACK) (pMIXERLINEINFO pInfo, 
                                                       L_VOID L_FAR *pUserData);
                                                 
/************************************************************************************
 *                                                                                  *
 *                            CAPTURE FUNCTIONS                                     *
 *                                                                                  *
 ************************************************************************************/

HWND EXT_FUNCTION L_CapCreateWin(L_CHAR L_FAR *szTitle,
                                 L_UINT32 uStyle,
                                 L_INT nXpos,
                                 L_INT nYpos,
                                 L_INT nWidth,
                                 L_INT nHeight,
                                 HWND hwndParent);

L_INT EXT_FUNCTION L_CapConnect(HWND hwndCap,
                                L_INT nDriver);

L_INT EXT_FUNCTION L_CapDisconnect(HWND hwndCap);

L_INT EXT_FUNCTION L_CapSetWorkFile(HWND hwndCap,
                                    L_CHAR L_FAR *pszCapFile,
                                    L_UINT32 uSize);

L_INT EXT_FUNCTION L_CapCopyFileAs(HWND hwndCap,
                                   L_CHAR L_FAR *pszFilename);

L_INT EXT_FUNCTION L_CapSaveFrame(HWND hwndCap,
                                  L_CHAR L_FAR *pszCapFile,
                                  L_INT nFormat,
                                  L_INT nBitsPerPixel,
                                  L_INT nQFactor,
                                  L_BOOL bMultipage);

L_INT EXT_FUNCTION L_CapSetOverlay(HWND hwndCap, 
                                   L_BOOL bOverlay);

L_INT EXT_FUNCTION L_CapSetVidOffset(HWND hwndCap,
                                     L_INT nXpos, 
                                     L_INT nYpos);

L_INT EXT_FUNCTION L_CapCopyToClipboard(HWND hwndCap);

L_INT EXT_FUNCTION L_CapSetOptions(HWND hwndCap,
                                   pCAPTUREOPTIONS pOptions);

L_INT EXT_FUNCTION L_CapGetOptions(HWND hwndCap,
                                   pCAPTUREOPTIONS pOptions);

L_INT EXT_FUNCTION L_CapGetStatus(HWND hwndCap,
                                  pCAPSTATUSINFO pCapInfo);

L_INT EXT_FUNCTION L_CapSetPreview(HWND hwndCap,
                                   L_BOOL bPreview,
                                   L_FLOAT uRate,
                                   L_BOOL bStretch);

L_INT EXT_FUNCTION L_CapStopCapture(HWND hwndCap);

L_INT EXT_FUNCTION L_CapDisplayDlg(HWND hwndCap,
                                   L_UINT uType);

L_INT EXT_FUNCTION L_CapSetVidFormat(HWND hwndCap,
                                     BITMAPINFO L_FAR *pInfo,
                                     L_UINT uSize);

L_INT EXT_FUNCTION L_CapGetVidFormat(HWND hwndCap,
                                     BITMAPINFO L_FAR *pInfo,
                                     L_UINT L_FAR *puSize);

L_INT EXT_FUNCTION L_CapSetAudFormat(HWND hwndCap,
                                     LPWAVEFORMATDATA pWaveFormat,
                                     L_UINT uSize);

L_INT EXT_FUNCTION L_CapGetAudFormat(HWND hwndCap,
                                     LPWAVEFORMATDATA pWaveFormat,
                                     L_UINT L_FAR *puSize);

L_INT EXT_FUNCTION L_CapStartCapture(HWND hwndCap);

L_INT EXT_FUNCTION L_CapEnumDrivers(ENUMDRIVERCALLBACK pfnCallback,
                                    L_VOID L_FAR *pUserData);

L_BOOL EXT_FUNCTION L_CapIsOptionAvailable(HWND hwndCap,
                                           L_UINT uOption);

L_INT EXT_FUNCTION L_CapStartSingleFrame(HWND hwndCap);

L_INT EXT_FUNCTION L_CapSingleFrame(HWND hwndCap);

L_INT EXT_FUNCTION L_CapStopSingleFrame(HWND hwndCap);

L_INT EXT_FUNCTION L_CapGetFrame(HWND hwndCap);

L_INT EXT_FUNCTION L_CapSetStatusCB(HWND hwndCap,
                                    CAPSTATCALLBACK pfnCallback,
                                    L_VOID L_FAR *pUserData);

L_INT EXT_FUNCTION L_CapSetMMCallbacks(HWND hwndCap,
                                       CAPVIDCALLBACK pVidCB,
                                       L_VOID L_FAR *pVidData,
                                       CAPAUDCALLBACK pAudCB,
                                       L_VOID L_FAR *pAudData);

L_INT EXT_FUNCTION L_CapStartFeedSound(HGLOBAL L_FAR*phSound,
                                       L_CHAR L_FAR *pszFile,
                                       L_UINT   uDeviceID,
                                       LPWAVEFORMATDATA lpWaveFormat,
                                       L_UINT   uBuffers,
                                       L_UINT   uFlags,
                                       FEEDSOUNDCALLBACK pfnCallback,
                                       L_VOID L_FAR  *pUserData);

L_INT EXT_FUNCTION L_CapStopFeedSound(HGLOBAL hSound, 
                                      L_BOOL bStopWhenReady);

L_INT EXT_FUNCTION L_CapFeedSound(HGLOBAL hSound,
                                  LPWAVEDATA lpWaveData);

L_INT EXT_FUNCTION L_CapFeedResetSound(HGLOBAL hSound);

L_INT EXT_FUNCTION L_CapPauseFeedSound(HGLOBAL hSound, L_BOOL bPause);

L_INT EXT_FUNCTION L_CapGetIDFromAud(LPWAVEFORMATDATA pWaveFormat,
                                     L_UINT L_FAR *puID);

L_INT EXT_FUNCTION L_CapGetAudFromID(LPWAVEFORMATDATA pWaveFormat,
                                     L_UINT uID);

L_INT EXT_FUNCTION L_CapOpenRecord(HGLOBAL L_FAR *phSound,
                                   L_UINT uDeviceID,
                                   LPWAVEFORMATDATA lpWaveFormat,
                                   L_UINT uBuffers,
                                   L_INT32 nBufSize,
                                   CAPAUDCALLBACK pfnCallback,
                                   L_VOID L_FAR *pUserData);
L_INT EXT_FUNCTION L_CapStartRecord(HGLOBAL hSound);
L_INT EXT_FUNCTION L_CapStopRecord(HGLOBAL hSound);
L_INT EXT_FUNCTION L_CapCloseRecord(HGLOBAL hSound);

L_INT EXT_FUNCTION L_CapGetDefaultAudFormat(LPWAVEFORMATDATA pWaveFormat,
                                            L_UINT L_FAR *puSize,
                                            L_CHAR L_FAR*pszFormatName, 
                                            L_UINT L_FAR*puFormatNameSize);

L_INT EXT_FUNCTION L_CapChooseAudFormat(HWND hwndParent,
                                        LPWAVEFORMATDATA pWaveFormat,
                                        L_UINT L_FAR *puSize,
                                        L_CHAR L_FAR*pszFormatName,
                                        L_UINT L_FAR*puFormatNameSize,
                                        L_UINT  uFlags);

L_VOID EXT_FUNCTION L_CapEnumMixerLines (L_INT nType, ENUMMIXERLINESCALLBACK pFunc, L_VOID L_FAR *pUserData);
L_INT  EXT_FUNCTION L_CapSetVolume (L_UINT32 nDeviceID, L_UINT32 nLineID, L_UINT nLeft, L_UINT nRight);
L_INT  EXT_FUNCTION L_CapGetVolume (L_UINT32 nDeviceID, L_UINT32 nLineID, L_UINT L_FAR *nLeft, L_UINT L_FAR *nRight);
L_INT  EXT_FUNCTION L_CapSetMute (L_UINT32 nDeviceID, L_UINT32 nLineID, L_UINT nFlag);
L_INT  EXT_FUNCTION L_CapGetMute (L_UINT32 nDeviceID, L_UINT32 nLineID, L_UINT L_FAR *nFlag);
L_INT  EXT_FUNCTION L_CapSetSelect (L_UINT32 nDeviceID, L_UINT32 nLineID, L_UINT nFlag);
L_INT  EXT_FUNCTION L_CapGetSelect (L_UINT32 nDeviceID, L_UINT32 nLineID, L_UINT L_FAR *nFlag);

L_INT EXT_FUNCTION L_CapGetAudioPeak(LPWAVEFORMATDATA pFormat,LPWAVEDATA lpWave,L_INT L_FAR *nPeak);

L_INT EXT_FUNCTION L_CapGetMetrics(L_UINT uMetric,
                                   L_VOID L_FAR*pMetric);

#undef _HEADER_ENTRY_
#include "ltpck.h"

#endif  /*_LTCAP_H_ */

