/*
   LTNET.H - internet module header file
   Copyright (c) 1991-2000 LEAD Technologies, Inc.
   All Rights Reserved.
*/

#ifndef _LTNET_H_
#define _LTNET_H_

#include "ltkrn.h"

#define _HEADER_ENTRY_
#include "ltpck.h"   

#ifndef WIN32
#include <compobj.h>
#endif

#if !defined(_WINSOCKAPI_) && !defined(_WINSOCK2API_)
/*
 * From winsock2.h: The new type to be used in all
 * instances which refer to sockets.
 */
typedef L_UINT           SOCKET;
#endif

#include "ltfil.h"

/************************************************************************************
 *                                                                                  *
 *                  Internet Messages                                               *
 *                                                                                  *
 ************************************************************************************/

#define INET_CONNECT          0  /* connected to remote computer                    */
#define INET_DATA_READY       1  /* data ready to be read                           */
#define INET_CLOSE            2  /* connection has been terminated                  */
#define INET_CONNECT_REQUEST  3  /* remote computer is requesting a connections     */
#define INET_DATA_SENT        4  /* data has been completely send to remote         */
#define INET_DATA_SENDING     5  /* lets user know that queued data has been sent   */
#define INET_DATA_START       6  /* about to start receiving data                   */
#define INET_DATA_RECEIVING   7  /* receiving data from a remote connection         */
#define INET_IMAGE_RECEIVED   8  /* an image has been received                      */
#define INET_MMEDIA_RECEIVED  9  /* a multimedia object has been received           */
#define INET_SOUND_RECEIVED   10 /* sound data has been received                    */
#define INET_USER1_RECEIVED   11 /* user data has been received                     */
#define INET_USER2_RECEIVED   12 /* user data has been received                     */
#define INET_USER3_RECEIVED   13 /* user data has been received                     */
#define INET_USER4_RECEIVED   14 /* user data has been received                     */
#define INET_COMMAND_RECEIVED 15 /* a command has been received                     */
#define INET_RESPONSE_RECEIVED 16 /* a response has been received                   */
#define INET_DETACH           17 /* handle has been detached from windows socket    */

/************************************************************************************
 *                                                                                  *
 *                  Internet Data types                                             *
 *                                                                                  *
 ************************************************************************************/

typedef enum {
   IDATA_IMAGE  = 0,  /* image data           */
   IDATA_MMEDIA = 1,  /* multimedia object    */
   IDATA_SOUND  = 2,  /* multimedia object    */
   IDATA_USER1  = 3,  /* user data            */
   IDATA_USER2  = 4,  /* user data            */
   IDATA_USER3  = 5,  /* user data            */
   IDATA_USER4  = 6,  /* user data            */
   IDATA_COMMAND = 7, /* command data         */
   IDATA_RESPONSE = 8,/* response data        */
   IDATA_LAST,        /* first invalid value  */
}IDATATYPE, *pIDATATYPE;

/************************************************************************************
 *                                                                                  *
 *                  Internet Address Types                                          *
 *                                                                                  *
 ************************************************************************************/

#define  HOST_NAME_DESCRP  0
#define  HOST_NAME_IP      1

/************************************************************************************
 *                                                                                  *
 *                        Predefined Queue sizes                                    *
 *                                                                                  *
 ************************************************************************************/

#define  QUEUE_NO_DATA     0xFFFFFFFF     /* Queue has only data required for auto processing */

/************************************************************************************
 *                                                                                  *
 *                  Command types                                                   *
 *                                                                                  *
 ************************************************************************************/
typedef enum {
   /* predefined commands */
   CMD_LOAD       = 0,  /* load a file */
   CMD_SAVE       = 1,  /* save a file */
   CMD_CREATE_WIN = 2,  /* create a window   */
   CMD_SIZE_WIN   = 3,  /* size a new window */
   CMD_CLOSE_WIN  = 4,  /* close a window */
   CMD_SHOW_WIN   = 5,  /* show/hide the window */
   CMD_SET_RECT   = 6,  /* set bitmap display rectangles */
   CMD_SEND_ANN   = 7,  /* send annotation to remote  */
   CMD_ATTACH_BITMAP = 8, /* attach a bitmap to a window */
   CMD_FREE_BITMAP = 9, /* free bitmap */
   CMD_GET_MAGGLASS_DATA = 10, /* get MagGlass needed data*/
      /* Registered user commands. Users are encouraged to register their commands with LEAD. 
         The registered commands will go in the 10000.19999 interval. 
         Registering commands will help avoid conflicts when 
         two different applications talk to each other.  */
   CMD_USER_REG   = 10000, /* start of registered user command values   */
      /* Custom user commands. These commands will be known only by the 
         application that sent them. */
   CMD_USER_CUSTOM = 20000,   /* start of custom user command values */
} CMDTYPE, *pCMDTYPE;

/* types of parameters */
typedef enum {
   PARAM_INT32,/* signed integer */
   PARAM_UINT32,
   PARAM_CHAR,
   PARAM_UCHAR,
   PARAM_STRING,
   PARAM_LONG,
   PARAM_UINT16,
   PARAM_INT16,
   PARAM_USTRING,
} PARMTYPE, L_FAR*pPARMTYPE;

/* command formats */
#define  CMD_LOAD_FORMAT               "%s%d%d%ud"
#define  CMD_SAVE_FORMAT               "%s%ud%d%d%d%ud"
#define  CMD_CREATE_WIN_FORMAT         "%s%s%ud%d%d%d%d%ud"
#define  CMD_SIZE_WIN_FORMAT           "%ud%d%d%d%d"
#define  CMD_CLOSE_WIN_FORMAT          "%ud"
#define  CMD_SHOW_WIN_FORMAT           "%ud%d"
#define  CMD_SET_RECT_FORMAT           "%ud%d%d%d%d%d"
#define  CMD_ATTACH_BITMAP_FORMAT      "%ud%ud"
#define  CMD_FREE_BITMAP_FORMAT        "%ud"
#define  CMD_ADD_ANN_FORMAT            "%ud%ud"
#define  CMD_GET_MAGGLASS_DATA_FORMAT  "%ud%ud%bs%d%d"

#define  RSP_LOAD_FORMAT               "%ud"
#define  RSP_SAVE_FORMAT               "%d%s%d%d%d%ud"
#define  RSP_CREATE_WIN_FORMAT         "%ud"
#define  RSP_ADD_ANN_FORMAT            "%ud"
#define  RSP_GET_MAGGLASS_DATA_FORMAT  "%ud%bs%ud%bs%d%d"

#define  INET_WINDOW_NONE        0xFFFFFFFF

/****** TYPEDEFS/defines **********/
typedef L_UINT       L_COMP;     // handle to a connected computer
typedef HGLOBAL      HINET, *pHINET;
typedef HGLOBAL      HINETPACK, *pHINETPACK;

typedef enum tagRECTTYPE
{
   RECT_SRC,      /* source            */
   RECT_SRCCLIP,  /* source clip       */
   RECT_SRCALL,   /* source and source clip */
   RECT_DST,      /* destination       */ 
   RECT_DSTCLIP,  /* destination clip  */
   RECT_DSTALL,   /* destination and destination clip */
} RECTTYPE;

typedef enum tagANNCMD
{
   CMD_ANN_ADD,
   CMD_ANN_DELETE,
   CMD_ANN_MOVE,
   CMD_ANN_CHANGE,
} ANNCMD;

typedef struct tagPARAMETER
{
   PARMTYPE uType;
   L_UINT32 uLength; // used only if uType is PARAM_STRING
   union
   {
      L_CHAR L_FAR *pValue;
      L_UCHAR L_FAR *puValue;
      L_CHAR   cValue;
      L_UCHAR  ucValue;
      L_INT16  sValue;
      L_UINT16 usValue;
      L_INT32  iValue;
      L_UINT32 uiValue;
   };
} PARAMETER, L_FAR *pPARAMETER;

typedef struct tagCOMMAND
{
   CMDTYPE  uCmd;
   L_UINT32 ulNumParams;
   pPARAMETER  pParams;
   L_UINT32 ulLength;      /* length of pData */
   L_CHAR L_FAR *pData;
} INETCMD, L_FAR *pINETCMD;

typedef struct tagRESPONSE
{
   L_UINT32 ulNumParams;
   pPARAMETER pParams;
   L_UINT uLength;      /* length of pData */
   L_CHAR L_FAR *pData;
} INETRSP, L_FAR *pINETRSP;

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

// ltsnd.h contains the structures for the non-PCM wave formats
#include "ltsnd.h"

// useful macro to find out the size of the WAVEFORMATDATA structure
#define SIZEOF_WAVEFORMATDATA(pwfx)   (sizeof(WAVEFORMATDATA) + ((CAP_WAVE_FORMAT_PCM==(pwfx)->wFormatTag)?0:(pwfx)->cbSize))

/************************************************************************************
 *                                                                                  *
 *                  Callback Functions                                              *
 *                                                                                  *
 ************************************************************************************/

typedef L_INT (pEXT_CALLBACK INETCALLBACK)
(
   L_COMP hComputer,
   L_INT nMessage,
   L_INT nError,
   L_CHAR L_FAR *pBuffer,
   L_UINT32 lSize,
   L_VOID L_FAR *pUserData
);

typedef L_VOID (pEXT_CALLBACK INETRESPONSECALLBACK)
(
   L_COMP      hComputer,
   CMDTYPE     uCommand,
   L_UINT      uCommandID,
   L_INT       nError,
   L_INT       nStatus,
   L_UINT      uParams, 
   pPARAMETER  pParams, 
   L_UINT      uExtra, 
   L_CHAR L_FAR*pExtra,
   L_VOID L_FAR*pUserData
);

typedef L_VOID (pEXT_CALLBACK INETCOMMANDCALLBACK)
(
   L_COMP      hComputer,   
   CMDTYPE     uCommand,
   L_UINT      uCommandID,
   L_INT       nError,
   L_UINT      uParams, 
   pPARAMETER  pParams, 
   L_UINT      uExtra,
   L_CHAR L_FAR*pExtra,
   L_VOID L_FAR*pUserData
);

/************************************************************************************
 *                                                                                  *
 *                  Internet Functions                                              *
 *                                                                                  *
 ************************************************************************************/

L_INT EXT_FUNCTION L_InetConnect(L_CHAR L_FAR *pszAddress,
                                 L_INT nPort,
                                 L_COMP L_FAR *phComputer,
                                 INETCALLBACK pfnCallback,
                                 L_VOID L_FAR *pUserData);

L_INT EXT_FUNCTION L_InetServerInit(L_INT nPort,
                                    L_COMP L_FAR *phComputer,
                                    INETCALLBACK pfnCallback,
                                    L_VOID L_FAR *pUserData);

L_INT EXT_FUNCTION L_InetClose(L_COMP hComputer, L_BOOL bGraceful);

L_INT EXT_FUNCTION L_InetSendData(L_COMP hComputer, 
                                  L_CHAR L_FAR *pBuffer, 
                                  L_UINT32 L_FAR *pulBufferLength,
                                  IDATATYPE uDataType);

L_INT EXT_FUNCTION L_InetSendMMData(L_COMP hComputer, 
                                    L_CHAR L_FAR *pBuffer, 
                                    L_UINT32 L_FAR*pulBufferLength);

L_INT EXT_FUNCTION L_InetReadData(L_COMP hComputer, 
                                  L_CHAR L_FAR *pBuffer, 
                                  L_UINT32 L_FAR *pulBufferLength);


L_INT EXT_FUNCTION L_InetGetHostName(L_COMP hHost,
                                     L_CHAR L_FAR *pszName,
                                     L_INT nType,
                                     L_UINT32 L_FAR *pulBufferLength);

L_INT EXT_FUNCTION L_InetAcceptConnect(L_COMP hHost, 
                                       L_COMP L_FAR *phRemote,
                                       INETCALLBACK pfnCallback,
                                       L_VOID L_FAR *pUserData);

L_INT EXT_FUNCTION L_InetSendBitmap(L_COMP hComputer, 
                                    pBITMAPHANDLE pBitmap,
                                    L_INT nFormat, 
                                    L_INT nBitsPerPixel, 
                                    L_INT nQFactor,
                                    L_UINT32 L_FAR*pulImageLength);

L_INT EXT_FUNCTION L_InetAutoProcess(L_COMP hComputer,
                                     L_BOOL bProcess);

L_INT EXT_FUNCTION L_InetSendRawData(L_COMP hComputer, 
                                     L_CHAR L_FAR *pBuffer,
                                     L_UINT32 L_FAR *pulBufferLength);

L_INT EXT_FUNCTION L_InetGetQueueSize(L_COMP hComputer, 
                                      L_UINT32 L_FAR *pulLength);

L_INT EXT_FUNCTION L_InetClearQueue(L_COMP hComputer);

L_INT EXT_FUNCTION L_InetStartUp(void);

L_INT EXT_FUNCTION L_InetShutDown(void);

L_INT EXT_FUNCTION L_InetSendSound(L_COMP hComputer, 
                                   LPWAVEFORMATDATA pWaveFormatData, 
                                   LPWAVEDATA pWaveData, 
                                   L_UINT32 L_FAR *pdwDataSize);

L_INT EXT_FUNCTION L_InetAttachToSocket(L_COMP L_FAR *phComputer,
                                       SOCKET hSocket,
                                       INETCALLBACK pfnCallback,
                                       L_VOID L_FAR *pUserData);

L_INT EXT_FUNCTION L_InetDetachFromSocket(L_COMP hComputer,
                                          L_BOOL bWaitTillQueueEmpty,
                                          SOCKET L_FAR*phSocket);

L_INT EXT_FUNCTION L_InetSetCallback(L_COMP hComputer,
                                     INETCALLBACK  pfnCallback,
                                     L_VOID L_FAR* pUserData);

L_INT EXT_FUNCTION L_InetGetCallback(L_COMP hComputer,
                                     INETCALLBACK L_FAR*ppfnCallback,
                                     L_VOID L_FAR* L_FAR* ppUserData);

L_INT EXT_FUNCTION L_InetCreatePacket(pHINETPACK phPacket,
                                       L_UINT uExtra,
                                       L_VOID L_FAR*pExtra,
                                       L_CHAR L_FAR*pszFormat,
                                       ...);

L_INT EXT_FUNCTION L_InetCreatePacketFromParams(pHINETPACK phPacket,
                                       L_UINT uExtra,
                                       L_VOID L_FAR*pExtra,
                                       L_UINT uParama,
                                       pPARAMETER pParams);

L_VOID EXT_FUNCTION L_InetFreePacket(HINETPACK hPacket);


L_INT EXT_FUNCTION L_InetSendCmd(L_COMP hComputer, 
                                 CMDTYPE uCommand,
                                 L_UINT uCommandID,
                                 HINETPACK hPacket);

L_INT EXT_FUNCTION L_InetSendRsp(L_COMP hComputer, 
                                 CMDTYPE uCommand,
                                 L_UINT uCommandID,
                                 HINETPACK hPacket,
                                 L_INT nStatus);

L_INT EXT_FUNCTION L_InetSendLoadCmd(L_COMP hComputer,
                                     L_UINT uCommandID,
                                     L_CHAR L_FAR*pszFile,
                                     L_INT nBitsPerPixel,
                                     L_INT nOrder,
                                     L_UINT uFlags);

L_INT EXT_FUNCTION L_InetSendLoadRsp(L_COMP hComputer,
                                     L_UINT uCommandID,
                                     L_UINT uBitmapID,
                                     L_UINT uExtra,
                                     L_CHAR L_FAR*pExtra,
                                     L_INT nStatus);

L_INT EXT_FUNCTION L_InetSendSaveCmd(L_COMP hComputer,
                                     L_UINT uCommandID,
                                     L_CHAR L_FAR*pszFile,
                                     L_UINT uBitmapID,
                                     L_INT nFormat,
                                     L_INT nBitsPerPixel, 
                                     L_INT nQFactor,
                                     L_UINT uFlags);

L_INT EXT_FUNCTION L_InetSendSaveRsp(L_COMP hComputer,
                                      L_UINT uCommandID,
                                      L_UINT uExtra,
                                      L_CHAR L_FAR*pExtra,
                                      L_INT nStatus);

L_INT EXT_FUNCTION L_InetSendCreateWinCmd(L_COMP hComputer,
                                          L_UINT uCommandID,
                                          L_CHAR L_FAR*pszClassName,
                                          L_CHAR L_FAR*pszWindowName,
                                          L_UINT ulFlags,
                                          L_INT nLeft,
                                          L_INT nTop,
                                          L_INT nWidth, 
                                          L_INT nHeight,
                                          L_UINT uParentID);

L_INT EXT_FUNCTION L_InetSendCreateWinRsp(L_COMP hComputer,
                                          L_UINT uCommandID,
                                          L_UINT uWindowID,
                                          L_UINT uLength,
                                          L_CHAR L_FAR*pExtraInfo,
                                          L_INT nStatus);

L_INT EXT_FUNCTION L_InetSendSizeWinCmd(L_COMP hComputer,
                                        L_UINT uCommandID,
                                        L_UINT uWindowID,
                                        L_INT nLeft,
                                        L_INT nTop,
                                        L_INT nWidth,
                                        L_INT nHeight);

L_INT EXT_FUNCTION L_InetSendSizeWinRsp(L_COMP hComputer,
                                        L_UINT uCommandID,
                                        L_UINT uLength,
                                        L_CHAR L_FAR*pExtraInfo,
                                        L_INT nStatus);

L_INT EXT_FUNCTION L_InetSendShowWinCmd(L_COMP hComputer,
                                        L_UINT uCommandID,
                                        L_UINT uWindowID,
                                        L_INT nCmdShow);

L_INT EXT_FUNCTION L_InetSendShowWinRsp(L_COMP hComputer,
                                        L_UINT uCommandID,
                                        L_UINT uLength,
                                        L_CHAR L_FAR*pExtraInfo,
                                        L_INT nStatus);

L_INT EXT_FUNCTION L_InetSendCloseWinCmd(L_COMP hComputer,
                                         L_UINT uCommandID,
                                         L_UINT uWindowID);

L_INT EXT_FUNCTION L_InetSendCloseWinRsp(L_COMP hComputer,
                                         L_UINT uCommandID,
                                         L_UINT uLength,
                                         L_CHAR L_FAR*pExtraInfo,
                                         L_INT nStatus);

L_INT EXT_FUNCTION L_InetSendFreeBitmapCmd(L_COMP hComputer,
                                         L_UINT uCommandID,
                                         L_UINT uBitmapID);

L_INT EXT_FUNCTION L_InetSendFreeBitmapRsp(L_COMP hComputer,
                                         L_UINT uCommandID,
                                         L_UINT uLength,
                                         L_CHAR L_FAR*pExtraInfo,
                                         L_INT nStatus);

L_INT EXT_FUNCTION L_InetSendSetRectCmd(L_COMP hComputer,
                                        L_UINT uCommandID,
                                        L_UINT uWindowID,
                                        RECTTYPE nType,
                                        L_INT nLeft,
                                        L_INT nTop,
                                        L_INT nWidth,
                                        L_INT nHeight);

L_INT EXT_FUNCTION L_InetSendSetRectRsp(L_COMP hComputer,
                                        L_UINT uCommandID,
                                        L_UINT uLength,
                                        L_CHAR L_FAR*pExtraInfo,
                                        L_INT nStatus);

/*
L_INT EXT_FUNCTION L_InetSendAnnCmd(L_COMP hComputer,
                                    L_UINT uCommandID,
                                    L_UINT uWindowID,
                                    ANNCMD nCommand,
                                    pPARAMETER pParams);

L_INT EXT_FUNCTION L_InetSendAnnRsp(L_COMP hComputer,
                                    L_UINT uCommandID,
                                    L_INT nStatus);
*/

L_INT EXT_FUNCTION L_InetSetCommandCallback(L_COMP hComputer, 
                                            INETCOMMANDCALLBACK pfnCallback,
                                            L_VOID L_FAR *pUserData);

L_INT EXT_FUNCTION L_InetSetResponseCallback(L_COMP hComputer,
                                             INETRESPONSECALLBACK pfnCallback,
                                             L_VOID L_FAR *pUserData);


L_INT EXT_FUNCTION L_InetSendAttachBitmapCmd(L_COMP hComputer,
                                             L_UINT uCommandID,
                                             L_UINT uBitmapID,
                                             L_UINT uWindowID);

L_INT EXT_FUNCTION L_InetSendAttachBitmapRsp(L_COMP hComputer,
                                             L_UINT uCommandID,
                                             L_UINT uExtra,
                                             L_CHAR L_FAR *pExtra,
                                             L_INT nStatus);

L_INT EXT_FUNCTION L_InetSendGetMagGlassDataCmd(L_COMP hComputer,
                                                L_UINT uCommandID,
                                                L_UINT uBitmapID,
                                                L_UINT32 nMaskPlaneSize,
                                                L_UCHAR L_FAR *pMaskPlane,
                                                L_INT nMaskPlaneStart,
                                                L_INT nMaskPlaneEnd);

L_INT EXT_FUNCTION L_InetSendGetMagGlassDataRsp(L_COMP hComputer,
                                                L_UINT uCommandID,
                                                L_UINT32 lColorSize,
                                                COLORREF L_FAR *pColor,
                                                L_UINT32 nMaskPlaneSize,
                                                L_UCHAR L_FAR *pMaskPlane,
                                                L_INT nMaskPlaneStart,
                                                L_INT nMaskPlaneEnd,
                                                L_UINT uExtra,
                                                L_CHAR L_FAR *pExtra,
                                                L_INT nStatus);

L_INT EXT_FUNCTION L_InetGetMagGlassData(pBITMAPHANDLE pBitmap,
                                         L_UINT32 *plColorSize,
                                         COLORREF L_FAR *pColor,
                                         L_UCHAR L_FAR *pMaskPlane,
                                         L_INT nMaskPlaneStart,
                                         L_INT nMaskPlaneEnd);

#undef _HEADER_ENTRY_
#include "ltpck.h"

#endif  /*_LTNET_H_ */
