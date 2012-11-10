/*
   LTVID.H - video module header file
   Copyright (c) 1991-2000 LEAD Technologies, Inc.
   All Rights Reserved.
*/

#ifndef _LTVID_H_
#define _LTVID_H_

#include "ltkrn.h"

#define _HEADER_ENTRY_
#include "ltpck.h"   

#ifndef WIN32
#include <compobj.h>
#endif


/*      wave formats                                                            */
#ifndef FILE_WAV_1M08
#define FILE_WAV_1M08       0x00000001       /* 11.025 kHz, Mono,   8-bit  */
#define FILE_WAV_1S08       0x00000002       /* 11.025 kHz, Stereo, 8-bit  */
#define FILE_WAV_1M16       0x00000004       /* 11.025 kHz, Mono,   16-bit */
#define FILE_WAV_1S16       0x00000008       /* 11.025 kHz, Stereo, 16-bit */
#define FILE_WAV_2M08       0x00000010       /* 22.05  kHz, Mono,   8-bit  */
#define FILE_WAV_2S08       0x00000020       /* 22.05  kHz, Stereo, 8-bit  */
#define FILE_WAV_2M16       0x00000040       /* 22.05  kHz, Mono,   16-bit */
#define FILE_WAV_2S16       0x00000080       /* 22.05  kHz, Stereo, 16-bit */
#define FILE_WAV_4M08       0x00000100       /* 44.1   kHz, Mono,   8-bit  */
#define FILE_WAV_4S08       0x00000200       /* 44.1   kHz, Stereo, 8-bit  */
#define FILE_WAV_4M16       0x00000400       /* 44.1   kHz, Mono,   16-bit */
#define FILE_WAV_4S16       0x00000800       /* 44.1   kHz, Stereo, 16-bit */
#define FILE_WAV_OTHER      0xFFFFFFFF       /* non-PCM format */
#endif

#define L_MEDIA             L_VOID L_FAR *


/************************************************************************************
 *                                                                                  *
 *                            Compressor Enumerators                                *
 *                                                                                  *
 ************************************************************************************/

#define COMP_VIDEO          0
#define COMP_AUDIO          1

/************************************************************************************
 *                                                                                  *
 *                            Seeking Formats                                       *
 *                                                                                  *
 ************************************************************************************/

#define MM_TIME_FRAME       0
#define MM_TIME_TIME        1

/************************************************************************************
 *                                                                                  *
 *                            Recording Devices                                     *
 *                                                                                  *
 ************************************************************************************/

#define RECORD_MIC          0
#define RECORD_CD           1
#define RECORD_LINE         2

/************************************************************************************
 *                                                                                  *
 *                            Event Notification Codes                              *
 *                                                                                  *
 ************************************************************************************/

#define L_EVENT_DONE                0
#define L_EVENT_ERROR               1
#define L_EVENT_PALETTE             2
#define L_EVENT_USERABORT           3
#define L_EVENT_SIZE_CHANGE         4
#define L_EVENT_EXIT_FULLSCREEN     5
#define L_EVENT_PLAY                6
#define L_EVENT_STOP                7
#define L_EVENT_PAUSE               8
#define L_EVENT_RESUME              9

/************************************************************************************
 *                                                                                  *
 *                            Open Modes                                            *
 *                                                                                  *
 ************************************************************************************/

#define L_OPEN_READ                 0
#define L_OPEN_EDIT                 1

/************************************************************************************
 *                                                                                  *
 *                            EDIT Flags                                            *
 *                                                                                  *
 ************************************************************************************/

#define MM_EDIT_VIDEO               0x0001
#define MM_EDIT_AUDIO               0x0002

/************************************************************************************
 *                                                                                  *
 *                            Stream Types Flags                                    *
 *                                                                                  *
 ************************************************************************************/

#define STREAM_VIDEO                0x0001
#define STREAM_AUDIO                0x0002
#define STREAM_UNKNOWN              0x0003

/************************************************************************************
 *                                                                                  *
 *                            Option Types                                          *
 *                                                                                  *
 ************************************************************************************/

#define MM_DLG_CONFIGURE            0x0001
#define MM_DLG_ABOUT                0x0002

/************************************************************************************
 *                                                                                  *
 *                            Structure Definitions                                 *
 *                                                                                  *
 ************************************************************************************/

typedef struct tagEDITINFO
{
    L_INT           nFstVid;
    L_INT           nFstAud;
    L_INT           nVidActive;
    L_INT           nAudActive;
    L_INT           nFstTxt;
    L_INT           nFrameRate;
    L_INT32         lClipStart;
    L_INT32         lClipEnd;
    L_INT           nFrameCurrent;
    L_INT           nRate;
    L_INT           nTimeFormat;
    L_INT           nStreams;
    L_INT           nState;
    HWND            hwndPlay;
    HWND            hwndMessage;
    HANDLE          hSignal;
    L_UINT32        lID;
    L_MEDIA L_FAR   *pStreams;
} EDITINFO, L_FAR *pEDITINFO;

typedef struct tagMEDIAHANDLE
{
    L_MEDIA         pGraph;
    L_MEDIA         pMedia;
    L_MEDIA         pWindow;
    L_MEDIA         pReader;
    L_MEDIA         pStream;
    L_INT           nWidth;
    L_INT           nHeight;
    L_INT           nOpenMode;
    L_INT32         lLength;
    struct struct_media_flags
    {
        L_BITFIELD Allocated:1;     /* Is the media allocated? */
        L_BITFIELD TempFile:1;      /* Do we have a temp file  */
        L_BITFIELD Reserved1:1;
        L_BITFIELD Reserved2:1;
        L_BITFIELD Reserved3:1;
        L_BITFIELD Reserved4:1;
        L_BITFIELD Reserved5:1;
        L_BITFIELD Reserved6:1;
        L_BITFIELD Reserved7:1;
        L_BITFIELD Reserved8:1;
        L_BITFIELD Reserved9:1;
        L_BITFIELD Reserved10:1;
        L_BITFIELD Reserved11:1;
        L_BITFIELD Reserved12:1;
        L_BITFIELD Reserved13:1;
        L_BITFIELD Reserved14:1;
        L_BITFIELD Dummy:16;
    } Flags;
    L_VOID L_FAR    *pReserved;
    EDITINFO        ei;
} MEDIAHANDLE, L_FAR * pMEDIAHANDLE;

typedef struct tagCOMPRESSIONOPTS
{
    L_INT32         lKeyFrameRate;
    L_INT           nQuality;
    L_INT32         lDataRate;
    L_INT           nAudFormat;

	  // MPEG Specific Options

    L_BOOL	Constrained;
    L_BOOL	FieldPic;
    L_INT	FrameRate;
    L_INT	FramesGOP;
    L_INT	PelAspectRatio;
    L_INT	ProfileID;
    L_INT	LevelID;
    L_INT	ChromaFormat;
    L_INT	VideoFormat;
    L_INT	IntraDcPrec;
    L_INT32	BitRate;	
    L_CHAR	UserInfo[255];		// user defined data to be put in mpeg stream
} COMPRESSIONOPTS, L_FAR * pCOMPRESSIONOPTS;


typedef struct tagMMFILEINFO
{
    L_INT   nFileType;
    L_INT   nWidth;
    L_INT   nHeight;
    L_INT   nStreams;
    L_INT   nAudFormat;     /* audio format of file                 */
    L_INT   nFrames;        /* number of frames in file             */
    L_INT32 lLength;        /* length of data in file               */
} MMFILEINFO, L_FAR *pMMFILEINFO;


/*

    MPEG constants

*/

/* scalable_mode */
#define SC_NONE									0
#define SC_DP									1
#define SC_SPAT									2
#define SC_SNR									3
#define SC_TEMP									4

/* picture coding type */
#define I_TYPE									1
#define P_TYPE									2
#define B_TYPE									3
#define D_TYPE									4

/* picture structure */
#define TOP_FIELD								1
#define BOTTOM_FIELD							2
#define FRAME_PICTURE							3

/* chroma_format */
#define CHROMA420								1
#define CHROMA422								2
#define CHROMA444								3

// aspect ratio information

#define MPEG_ASPECT_SQUARE						1	// square pel
#define MPEG_ASPECT_4_3							2	// 4:3
#define MPEG_ASPECT_16_9						3	// 16:9
#define MPEG_ASPECT_2_1							4	// 2.11:1
#define MPEG_ASPECT_625							8	// CCIR601 625 Line
#define MPEG_ASPECT_525							9	// CCIR601 525 Line

// frame rate code

#define MPEG_FRAMERATE_23						1	// 23.976
#define MPEG_FRAMERATE_24						2	// 24
#define MPEG_FRAMERATE_25						3	// 25
#define MPEG_FRAMERATE_29						4	// 29.97
#define MPEG_FRAMERATE_30						5	// 30

// profile id

#define MPEG_PROFILE_SIMPLE						5
#define MPEG_PROFILE_MAIN						4
#define MPEG_PROFILE_SNR						3
#define MPEG_PROFILE_SPATIAL					2
#define MPEG_PROFILE_HIGH						1

// level id

#define MPEG_LEVEL_LOW							10
#define MPEG_LEVEL_MAIN							8
#define MPEG_LEVEL_HIGH14440					6
#define MPEG_LEVEL_HIGH							4

// chroma format

#define MPEG_CHROMA_420							1 // 4:2:0
#define MPEG_CHROMA_422							2 // 4:2:2
#define MPEG_CHROMA_444							3 // 4:4:4

// video format

#define MPEG_VIDEO_COMP							0
#define MPEG_VIDEO_PAL							1
#define MPEG_VIDEO_NTSC							2
#define MPEG_VIDEO_SECAM						3
#define MPEG_VIDEO_MAC							4
#define MPEG_VIDEO_UNSP							5 // unspecified

// intra dc precision

#define MPEG_INTRA_8							0 // 8 bit
#define MPEG_INTRA_9							1 // 9 bit
#define MPEG_INTRA_10							2 // 10 bit
#define MPEG_INTRA_11							3 // 11 bit

// MPEG Audio Header Definitions - Mode Values 

#define MPEG_MODE_STEREO						0
#define MPEG_MODE_JOINT_STEREO					1
#define MPEG_MODE_DUAL_CHANNEL					2
#define MPEG_MODE_MONO							3

// MPEG Audio Layer Defines		

#define MPEG_LAYER_I							1
#define MPEG_LAYER_II							2
#define MPEG_LAYER_III							3

// MPEG Audio Sampling frequency

#define MPEG_FREQ_16							0	// 16000
#define MPEG_FREQ_22							1	// 22050
#define MPEG_FREQ_24							2	// 24000
#define MPEG_FREQ_32							3	// 32000
#define MPEG_FREQ_44							4	// 44100
#define MPEG_FREQ_48							5	// 48000

// MPEG Audio encoder de-emphasis

#define MPEG_DEMP_NONE							0	// none
#define MPEG_DEMP_5015							1	// 50/15 micro seconds
#define MPEG_DEMP_J17							2	// CCITT J.17

// Predefined compressor strings for L_MMSaveFile
#define COMP_UNCOMPRESSED              "* Uncompressed *"   // uncompressed
#define COMP_UNCHANGED                 "* Unchanged *"      // unchanged

// Renderer flags. They are identical to the switches in the IDirectDrawVideo interface
#ifndef AMDDS_YUV
   #define AMDDS_NONE 0x00             // No use for DCI/DirectDraw
   #define AMDDS_DCIPS 0x01            // Use DCI primary surface
   #define AMDDS_PS 0x02               // Use DirectDraw primary
   #define AMDDS_RGBOVR 0x04           // RGB overlay surfaces
   #define AMDDS_YUVOVR 0x08           // YUV overlay surfaces
   #define AMDDS_RGBOFF 0x10           // RGB offscreen surfaces
   #define AMDDS_YUVOFF 0x20           // YUV offscreen surfaces
   #define AMDDS_RGBFLP 0x40           // RGB flipping surfaces
   #define AMDDS_YUVFLP 0x80           // YUV flipping surfaces
   #define AMDDS_ALL 0xFF              // ALL the previous flags
   #define AMDDS_DEFAULT AMDDS_ALL     // Use all available surfaces
                                 
   #define AMDDS_YUV (AMDDS_YUVOFF | AMDDS_YUVOVR | AMDDS_YUVFLP)
   #define AMDDS_RGB (AMDDS_RGBOFF | AMDDS_RGBOVR | AMDDS_RGBFLP)
   #define AMDDS_PRIMARY (AMDDS_DCIPS | AMDDS_PS)
#endif

/************************************************************************************
 *                                                                                  *
 *                            Callback Declarations                                 *
 *                                                                                  *
 ************************************************************************************/

typedef L_INT (pEXT_CALLBACK VIDRENDERCALLBACK) (pBITMAPHANDLE pBitmap, 
                                                 L_UINT nFrame,
                                                 L_VOID L_FAR *pUserData);


typedef L_INT (pEXT_CALLBACK ENUMCOMPCALLBACK) (L_CHAR L_FAR *szName,
                                                L_VOID L_FAR *pUserData);

typedef L_INT (pEXT_CALLBACK ENUMDRIVERCALLBACK) (L_INT iIndex,
                                                  L_CHAR L_FAR *szName,
                                                  L_CHAR L_FAR *szVersion,
                                                  L_VOID L_FAR *pUserData);

typedef L_VOID (pEXT_CALLBACK MMEVENTCALLBACK)(pMEDIAHANDLE pMMedia,
                                               L_INT nEvent,
                                               L_VOID L_FAR *pUserData);

/************************************************************************************
 *                                                                                  *
 *                            VIDEO FUNCTIONS                                       *
 *                                                                                  *
 ************************************************************************************/

L_INT EXT_FUNCTION L_MMLoad(L_CHAR L_FAR *pszFile,
                            pMEDIAHANDLE pMMedia,
                            L_INT nOpen);

L_INT EXT_FUNCTION L_MMFree(pMEDIAHANDLE pMMedia);

L_INT EXT_FUNCTION L_MMPlay(pMEDIAHANDLE pMMedia,
                            L_CHAR L_FAR *pszCaption);

L_INT EXT_FUNCTION L_MMSetRate(pMEDIAHANDLE pMMedia, 
                               L_DOUBLE dRate);

L_INT EXT_FUNCTION L_MMGetRate(pMEDIAHANDLE pMMedia, 
                               L_DOUBLE L_FAR *pdRate);

L_INT EXT_FUNCTION L_MMStop(pMEDIAHANDLE pMMedia);

L_INT EXT_FUNCTION L_MMPause(pMEDIAHANDLE pMMedia);

L_INT EXT_FUNCTION L_MMMarkClip(pMEDIAHANDLE pMMedia,
                                L_INT32 dwStart,
                                L_INT32 dwStop);

L_INT EXT_FUNCTION L_MMSetVolume(pMEDIAHANDLE pMMedia,
                                 L_INT nVolume);

L_INT EXT_FUNCTION L_MMGetVolume(pMEDIAHANDLE pMMedia,
                                 L_INT L_FAR *pnVolume);

L_INT EXT_FUNCTION L_MMSetBalance(pMEDIAHANDLE pMMedia, 
                                  L_INT nBalance);

L_INT EXT_FUNCTION L_MMGetBalance(pMEDIAHANDLE pMMedia, 
                                  L_INT L_FAR *pnBalance);

L_INT EXT_FUNCTION L_MMSetSrcRect(pMEDIAHANDLE pMMedia,
                                  L_INT nXpos,
                                  L_INT nYpos, 
                                  L_INT nWidth,
                                  L_INT nHeight);

L_INT EXT_FUNCTION L_MMSetDstRect(pMEDIAHANDLE pMMedia,
                                  L_INT nXpos,
                                  L_INT nYpos, 
                                  L_INT nWidth,
                                  L_INT nHeight);

L_INT EXT_FUNCTION L_MMSetPlayExt(pMEDIAHANDLE pMMedia,
                                  HWND hwndParent,
                                  L_INT nXpos,
                                  L_INT nYpos,
                                  L_INT nWidth,
                                  L_INT nHeight,
                                  L_UINT32 dwStyle);

L_INT EXT_FUNCTION L_MMLoadMemory(L_CHAR L_FAR *pBuffer,
                                  pMEDIAHANDLE pMMedia,
                                  L_INT32 dwBufferSize);

L_INT EXT_FUNCTION L_MMSaveFile(L_CHAR L_FAR *pszFile,
                                pMEDIAHANDLE pMMedia,
                                L_INT nFormat,
                                L_CHAR L_FAR *pszVidComp,
                                L_CHAR L_FAR *pszAudComp,
                                L_CHAR L_FAR *pszAudFormat,
                                pCOMPRESSIONOPTS pCompOpts);

L_INT EXT_FUNCTION L_MMEnumAudioCompressors(pMEDIAHANDLE pMMedia,
                                          ENUMCOMPCALLBACK pCallback,
                                          L_VOID L_FAR *pUserData);

L_INT EXT_FUNCTION L_MMEnumAudioFormats(pMEDIAHANDLE pMMedia,
                                       L_CHAR L_FAR*pszAudComp,
                                       ENUMCOMPCALLBACK pCallback,
                                       L_VOID L_FAR *pUserData);

L_INT EXT_FUNCTION L_MMEnumVideoCompressors(pMEDIAHANDLE pMMedia,
                                          ENUMCOMPCALLBACK pCallback,
                                          L_VOID L_FAR *pUserData);

L_INT EXT_FUNCTION L_MMGetBitmap(pMEDIAHANDLE pMMedia,
                                 pBITMAPHANDLE pBitmap,
                                 L_INT32 lPos);

L_INT EXT_FUNCTION L_MMSetTimeFormat(pMEDIAHANDLE pMMedia,
                                     L_INT nFormat);

L_INT EXT_FUNCTION L_MMGetTimeFormat(pMEDIAHANDLE pMMedia,
                                     L_INT L_FAR *pnFormat);

L_INT EXT_FUNCTION L_MMConvertTime(pMEDIAHANDLE pMMedia,
                                   L_INT32 L_FAR *pdwTarget,
                                   L_INT nTargetFormat,
                                   L_INT32 dwSource,
                                   L_INT nSourceFormat);

L_INT EXT_FUNCTION L_MMResume(pMEDIAHANDLE pMMedia);

L_INT EXT_FUNCTION L_MMStartRecord(L_CHAR L_FAR *pszFile,
                                   pMEDIAHANDLE pMMedia,
                                   L_INT nDevice,
                                   L_INT nFormat);

L_INT EXT_FUNCTION L_MMStopRecord(L_VOID);

L_INT EXT_FUNCTION L_MMGetDefaultCompressionOpts(pCOMPRESSIONOPTS pCompOpts);

L_INT EXT_FUNCTION L_MMConvertFromBitmapList(pMEDIAHANDLE pMMedia,
                                             L_CHAR L_FAR *pszFile,
                                             L_INT nfPerSec,
                                             L_INT nBitsPerPixel,
                                             HBITMAPLIST hList,
                                             L_CHAR L_FAR *pszComp,
                                             pCOMPRESSIONOPTS pCompOpts);

L_INT EXT_FUNCTION L_MMAdjustWin(pMEDIAHANDLE pMMedia,
                                 L_INT nXpos,
                                 L_INT nYpos,
                                 L_INT nWidth,
                                 L_INT nHeight);

L_INT EXT_FUNCTION L_MMSetParentWin(pMEDIAHANDLE pMMedia,
                                    HWND hwndOwner);

L_INT EXT_FUNCTION L_MMSetMessageWin(pMEDIAHANDLE pMMedia,
                                     HWND hwndMessage);

L_INT EXT_FUNCTION L_MMSetEventCallback(MMEVENTCALLBACK pCallback,
                                        L_VOID L_FAR *pUserData);

L_INT EXT_FUNCTION L_MMGetCurrentPos(pMEDIAHANDLE pMMedia, 
                                     L_INT32 L_FAR *plPos);

L_INT EXT_FUNCTION L_MMSetCurrentPos(pMEDIAHANDLE pMMedia, 
                                     L_INT32 lPos);

L_INT EXT_FUNCTION L_MMSetWinVisible(pMEDIAHANDLE pMMedia,
                                     L_BOOL bVisibility);

L_INT EXT_FUNCTION L_MMReplaceFrame(pMEDIAHANDLE pMMedia,
                                    L_INT32 lFrame,
                                    pBITMAPHANDLE pBitmap);

L_INT EXT_FUNCTION L_MMInsertFrame(pMEDIAHANDLE pMMedia,
                                   L_INT32 lFrame,
                                   pBITMAPHANDLE pBitmap);

L_INT EXT_FUNCTION L_MMDeleteFrames(pMEDIAHANDLE pMMedia,
                                    L_INT32 lStart,
                                    L_INT32 lLength,
                                    L_UINT32 uFlags);

L_INT EXT_FUNCTION L_MMCopyFrames(pMEDIAHANDLE pMMedia,
                                  L_INT32 lStart,
                                  L_INT32 lLength,
                                  L_UINT32 uFlags);

L_INT EXT_FUNCTION L_MMPasteFrames(pMEDIAHANDLE pMMedia,
                                   L_INT32 lStart,
                                   L_INT32 lLength,
                                   L_UINT32 uFlags);

L_INT EXT_FUNCTION L_MMSetActive(pMEDIAHANDLE pMMedia,
                                 L_INT nActive);

L_INT EXT_FUNCTION L_MMAddStream(pMEDIAHANDLE pMMedia,
                                 L_UINT uType,
                                 L_VOID *pFormat,
                                 L_CHAR L_FAR *pszVidComp,
                                 L_INT nFPerSec,
                                 pCOMPRESSIONOPTS pCompOpts);

L_INT EXT_FUNCTION L_MMGetStreamType(pMEDIAHANDLE pMMedia,
                                     L_INT nStream,
                                     L_UINT *puType);

L_INT EXT_FUNCTION L_MMCreate(pMEDIAHANDLE pMMedia);

L_INT EXT_FUNCTION L_MMInit(pMEDIAHANDLE pMMedia);

L_INT EXT_FUNCTION L_MMIsClipboardReady(L_VOID);

L_INT EXT_FUNCTION L_MMDeleteStream(pMEDIAHANDLE pMMedia,
                           L_INT nStream);

L_BOOL EXT_FUNCTION L_MMIsPlaying(pMEDIAHANDLE pMMedia);

L_BOOL EXT_FUNCTION L_MMIsOptionAvailable(L_CHAR L_FAR *pszName, 
                                          L_INT nType, 
                                          L_INT nOption);

L_INT EXT_FUNCTION L_MMDisplayDlg(HWND hWnd, 
                                  L_CHAR L_FAR *pszName, 
                                  L_INT nType, 
                                  L_INT nDlgType);

L_INT EXT_FUNCTION L_MMAddSoundFile(L_CHAR L_FAR *pszFile, 
                                    pMEDIAHANDLE pMMedia, 
                                    L_INT32 lSrcPos,
                                    L_INT32 lDstPos,
                                    L_INT32 lLength);

L_INT EXT_FUNCTION L_MMShowRendererProperties(pMEDIAHANDLE pMMedia, 
                                              HWND hwndParent);

L_INT EXT_FUNCTION L_MMGetRendererFlags(pMEDIAHANDLE pMMedia,
                                        L_UINT32 L_FAR*pFlags);

L_INT EXT_FUNCTION L_MMSetRendererFlags(pMEDIAHANDLE pMMedia,
                                        L_UINT32 ulFlags);

#undef _HEADER_ENTRY_
#include "ltpck.h"

#endif  /*_LTVID_H_ */

