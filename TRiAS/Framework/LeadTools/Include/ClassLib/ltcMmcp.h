/*----------------------------------------------------------------------------+
| LEADTOOLS for Windows -                                                     |
| Copyright (c) 1991-2000 LEAD Technologies, Inc.                             |
| All Rights Reserved.                                                        |
|-----------------------------------------------------------------------------|
| PROJECT   : LEAD wrappers                                                   |
| FILE NAME : ltcmmcp.h                                                       |
| DESC      : LMMCapture Class                                                |
+----------------------------------------------------------------------------*/

#ifndef  _LEAD_MMCAPTURE_H_
#define  _LEAD_MMCAPTURE_H_

/*----------------------------------------------------------------------------+
| CLASSES DECLARATION                                                         |
+----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------+
| Class     : LMMCapture                                                      |
| Desc      :                                                                 |
| Return    :                                                                 |
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+
| Date      : September 1998                                                  |
+----------------------------------------------------------------------------*/
class LWRP_EXPORT LMMCapture : public LBase
{
   LEAD_DECLAREOBJECT(LMMCapture);

   public:
      L_VOID *m_extLMMCapture;
      
   private:
      // Data
      HWND              m_hWndCap;
      L_BOOL            m_SetCallbacks;
   protected :  
      HGLOBAL           m_hSoundRecord;
      HGLOBAL           m_hSoundFeed;
      L_BOOL            m_bConnected;

   private:
      static  L_INT EXT_CALLBACK EnumDriverCS(L_INT iIndex, L_CHAR L_FAR *pszName, L_CHAR L_FAR *pszVersion,L_VOID L_FAR * pUserData);
      static  L_INT EXT_CALLBACK VideoDataCS(LPVIDEODATA pVidData,L_VOID L_FAR * pUserData);
      static  L_INT EXT_CALLBACK AudioDataCS(LPWAVEDATA pAudData,L_VOID L_FAR * pUserData);
      static  L_INT EXT_CALLBACK FeedSoundCS(HGLOBAL hSound,L_UINT uMsg,L_VOID L_FAR * pUserData);
      static  L_INT EXT_CALLBACK RecordCS(LPWAVEDATA pAudData,L_VOID L_FAR * pUserData);
      static  L_VOID EXT_CALLBACK EnumMixerLineCS (pMIXERLINEINFO pInfo, L_VOID L_FAR * pUserData);
      static  L_INT EXT_CALLBACK StatusCS(L_CHAR L_FAR *pszString, L_VOID L_FAR * pUserData);
      L_VOID         InitializeClass();

   protected:
      virtual L_INT EnumDriverCallBack (L_INT iIndex, L_CHAR L_FAR *pszName, L_CHAR L_FAR *pszVersion);
      virtual L_INT VideoDataCallBack (LPVIDEODATA pVidData);
      virtual L_INT AudioDataCallBack (LPWAVEDATA pAudData);
      virtual L_INT FeedSoundCallBack (L_UINT uMsg);
      virtual L_INT RecordCallBack (LPWAVEDATA pAudData);
      virtual L_VOID EnumMixerLineCallBack (pMIXERLINEINFO pInfo);
      virtual L_INT StatusCallBack(L_CHAR L_FAR *pszString);
   public:
      
      LMMCapture();
      LMMCapture::LMMCapture(HWND   hwndParent,
                             L_INT  nDriver           = 0,
                             L_CHAR L_FAR *szTitle    ="", 
                             L_UINT32 uStyle          =WS_CHILD|WS_VISIBLE, 
                             L_INT nXpos              =0, 
                             L_INT nYpos              =0, 
                             L_INT nWidth             =320, 
                             L_INT nHeight            =200);
      virtual ~LMMCapture();
      L_BOOL         IsValid();
      virtual L_INT  CreateWin (HWND hwndParent, L_CHAR L_FAR *szTitle="", L_UINT32 uStyle=WS_CHILD, L_INT nXpos=0, L_INT nYpos=0, L_INT nWidth=320, L_INT nHeight=200);
      virtual HWND   GetHwnd();
      HGLOBAL        GetFeedSoundHandle();
      HGLOBAL        GeRecordSoundHandle();
      virtual L_INT  DestroyWin(L_VOID);
      virtual L_INT  Connect (L_INT nDriver=0);
      virtual L_INT  Disconnect (L_VOID);
      virtual L_INT  SetWorkFile (L_CHAR L_FAR *pszCapFile, L_UINT32 uSize);
      virtual L_INT  CopyFileAs (L_CHAR L_FAR *pszFilename);
      virtual L_INT  SaveFrame(L_CHAR L_FAR *pszCapFile, L_INT nFormat, L_INT nBitsPerPixel=0, L_INT nQFactor=2, L_BOOL bMultipage=FALSE);
      virtual L_INT  SetOverlay (L_BOOL bOverlay=TRUE);
      virtual L_INT  SetVidOffset (L_INT nXpos=0, L_INT nYpos=0);
      virtual L_INT  CopyToClipboard (L_VOID);
      virtual L_INT  SetOptions (pCAPTUREOPTIONS pOptions);
      virtual L_INT  GetOptions (pCAPTUREOPTIONS pOptions);
      virtual L_INT  GetStatus  (pCAPSTATUSINFO  pCapInfo);
      virtual L_INT  SetPreview (L_BOOL bPreview=TRUE, L_FLOAT uRate=15.0f, L_BOOL bStretch=FALSE);
      virtual L_INT  StopCapture (L_VOID);
      virtual L_INT  DisplayDlg (L_UINT uType=CAP_DLG_VIDFORMAT);
      virtual L_INT  SetVidFormat (BITMAPINFO L_FAR *pInfo, L_UINT uSize = sizeof(BITMAPINFO));
      virtual L_INT  GetVidFormat (BITMAPINFO L_FAR *pInfo, L_UINT L_FAR *puSize);
      virtual L_INT  SetAudFormat (LPWAVEFORMATDATA pWaveFormat, L_UINT uSize);
      virtual L_INT  GetAudFormat (LPWAVEFORMATDATA pWaveFormat, L_UINT L_FAR *puSize);
      virtual L_INT  StartCapture (L_VOID);
      virtual L_INT  EnumDrivers ();
      virtual L_BOOL IsOptionAvailable (L_UINT uOption=CAP_DLG_VIDFORMAT);
      virtual L_INT  StartSingleFrame (L_VOID);
      virtual L_INT  SingleFrame (L_VOID);
      virtual L_INT  StopSingleFrame (L_VOID);
      virtual L_INT  GetFrame (L_VOID);
      virtual L_INT  EnableMMCallbacks (L_BOOL bEnableVidCB = TRUE, L_BOOL bEnableAudCB = TRUE);
      
      virtual L_INT  StartFeedSound (L_CHAR L_FAR *pszFile, L_UINT uDeviceID, LPWAVEFORMATDATA lpWaveFormat, L_UINT uBuffers, L_UINT uFlags);
      virtual L_INT  StopFeedSound (L_BOOL bStopWhenReady=TRUE);
      virtual L_INT  FeedSound (LPWAVEDATA lpWaveData);
      virtual L_INT  FeedResetSound (L_VOID);
      virtual L_INT  PauseFeedSound (L_BOOL bPause=TRUE);
      virtual L_INT  GetIDFromAud (LPWAVEFORMATDATA pWaveFormat, L_UINT L_FAR *puID);
      virtual L_INT  GetAudFromID (LPWAVEFORMATDATA pWaveFormat, L_UINT uID);
      virtual L_INT  OpenRecord (L_UINT uDeviceID, LPWAVEFORMATDATA lpWaveFormat, L_UINT uBuffers, L_INT32 nBufSize);
      virtual L_INT  StartRecord (L_VOID);
      virtual L_INT  StopRecord (L_VOID);
      virtual L_INT  CloseRecord (L_VOID);
      virtual L_INT  GetDefaultAudFormat (LPWAVEFORMATDATA pWaveFormat, L_UINT L_FAR *puSize, L_CHAR L_FAR*pszFormatName, L_UINT L_FAR*puFormatNameSize);
      virtual L_INT  ChooseAudFormat (HWND hwndParent, LPWAVEFORMATDATA pWaveFormat, L_UINT L_FAR *puSize, L_CHAR L_FAR*pszFormatName, L_UINT L_FAR*puFormatNameSize, L_UINT  uFlags);
      virtual L_VOID EnumMixerLines (L_INT nType);
      virtual L_INT  SetVolume (L_UINT32 nDeviceID, L_UINT32 nLineID, L_UINT nLeft, L_UINT nRight);
      virtual L_INT  GetVolume (L_UINT32 nDeviceID, L_UINT32 nLineID, L_UINT L_FAR *pnLeft, L_UINT L_FAR *pnRight);
      virtual L_INT  SetMute (L_UINT32 nDeviceID, L_UINT32 nLineID, L_UINT nFlag);
      virtual L_INT  GetMute (L_UINT32 nDeviceID, L_UINT32 nLineID, L_UINT L_FAR *pnFlag);
      virtual L_INT  SetSelect (L_UINT32 nDeviceID, L_UINT32 nLineID, L_UINT nFlag);
      virtual L_INT  GetSelect (L_UINT32 nDeviceID, L_UINT32 nLineID, L_UINT L_FAR *pnFlag);
      virtual L_INT  GetAudioPeak (LPWAVEFORMATDATA pFormat, LPWAVEDATA lpWave, L_INT L_FAR *nPeak);
      virtual L_INT  GetMetrics (L_UINT uMetric, L_VOID L_FAR*pMetric);
      virtual L_INT  EnableStatusCallback(L_BOOL bFlag = TRUE);
};

#endif //_LEAD_MMCAPTURE_H_

/*================================================================= EOF =====*/
