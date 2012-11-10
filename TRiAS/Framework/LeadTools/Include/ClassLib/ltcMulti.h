/*----------------------------------------------------------------------------+
| LEADTOOLS for Windows -                                                     |
| Copyright (c) 1991-2000 LEAD Technologies, Inc.                             |
| All Rights Reserved.                                                        |
|-----------------------------------------------------------------------------|
| PROJECT   : LEAD wrappers                                                   |
| FILE NAME : ltcMulti.h                                                      |
| DESC      :                                                                 |
+----------------------------------------------------------------------------*/

#ifndef  _LEAD_MULTIMEDIA_H_
#define  _LEAD_MULTIMEDIA_H_

typedef struct struct_MMITEM
{
  pMEDIAHANDLE  pMediaHandle;
  LMultimedia  *pThis;
} MMITEM, L_FAR * pMMITEM;

/*----------------------------------------------------------------------------+
| CLASSES DECLARATION                                                         |
+----------------------------------------------------------------------------*/
class LMultimedia;
/*----------------------------------------------------------------------------+
| Class     : LMultimedia                                                     |
| Desc      :                                                                 |
| Return    :                                                                 | 
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+
| Date      : September 1998                                                  |
+----------------------------------------------------------------------------*/
class LWRP_EXPORT LMultimedia : public LBase
{
   LEAD_DECLAREOBJECT(LMultimedia);

   public:
      L_VOID *m_extLMultimedia;

   private:
      static   L_BOOL   m_bMMWinRegisterd;
      static   L_UINT   m_uInstancesCount;
      HWND              m_hMMWin;
      static   LDictionary m_mmDictionary;
      MMITEM            m_mmItem;

   protected:
      MEDIAHANDLE       m_MMedia;
      
   private:
      static  L_INT  EXT_CALLBACK EnumCompressorsCS (L_CHAR L_FAR *pszName,L_VOID L_FAR * pUserData);
      
      static  L_VOID EXT_CALLBACK EventCS (pMEDIAHANDLE  pMMedia,L_INT nEvent,
                              L_VOID L_FAR * pUserData);
      static LRESULT EXT_CALLBACK 
         MultimediaWinProcCS(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
      L_INT          RegisterMultimediaWinClass();
      L_BOOL         UnRegisterMultimediaWinClass();

   protected:
      virtual L_INT  EnumCompressorsCallBack (L_CHAR L_FAR *pszName );
      virtual L_VOID EventCallBack (L_INT nEvent);

   public:
      LMultimedia();
      LMultimedia (MEDIAHANDLE L_FAR *pMedia);
      virtual ~LMultimedia();

      L_BOOL IsAllocated() const;
      L_INT  GetWidth() const;
      L_INT  GetHeight() const;
      L_INT  GetOpenMode() const;
      L_INT  GetLength() const;
      L_VOID GetEditInfo(EDITINFO L_FAR* pEi) const;
      MEDIAHANDLE*  GetHandle();
      virtual L_INT Load (L_CHAR L_FAR *pszFile, L_INT nOpen=L_OPEN_READ);
      virtual L_INT Free (L_VOID);
      virtual L_INT Play (L_CHAR L_FAR *pszCaption=NULL);
      virtual L_INT Stop (L_VOID);
      virtual L_INT Pause (L_VOID);
      virtual L_INT MarkClip (L_INT32 dwStart=-1, L_INT32 dwStop=-1);
      virtual L_INT SetSrcRect (L_INT nXpos=0, L_INT nYpos=0, L_INT nWidth=-1, L_INT nHeight=-1);
      virtual L_INT SetSrcRect (LPRECT pRect);
      virtual L_INT SetDstRect (L_INT nXpos=0, L_INT nYpos=0, L_INT nWidth=-1, L_INT nHeight=-1);
      virtual L_INT SetDstRect (LPRECT pRect);
      virtual L_INT SetPlayExt (HWND hwndParent, L_INT nXpos, L_INT nYpos, L_INT nWidth, L_INT nHeight, L_UINT32 dwStyle);
      virtual L_INT LoadMemory (L_CHAR L_FAR *pBuffer, L_INT32 dwBufferSize);
      virtual L_INT SaveFile (
         L_CHAR L_FAR *pszFile, 
         L_INT nFormat, 
         L_CHAR L_FAR *pszVidComp   = NULL, 
         L_CHAR L_FAR *pszAudComp   = NULL, 
         L_CHAR L_FAR *pszAudFormat = NULL, 
         pCOMPRESSIONOPTS pCompOpts = NULL);

      //virtual L_INT EnumCompressors (L_INT nType, L_BOOL bShowCompatibleOnly=FALSE);

      virtual L_INT EnumVideoCompressors();
      virtual L_INT EnumAudioCompressors();
      virtual L_INT EnumAudioFormats(L_CHAR L_FAR *pszAudComp);
      
      virtual L_INT GetBitmap (pBITMAPHANDLE pBitmap, L_INT32 lPos);
      virtual L_INT GetBitmap (LBitmapBase L_FAR* pBitmap, L_INT32 lPos);
      virtual L_INT SetTimeFormat (L_INT nFormat);
      virtual L_INT GetTimeFormat (L_INT L_FAR *pnFormat);
      virtual L_INT ConvertTime (L_INT32 L_FAR *pdwTarget, L_INT nTargetFormat, L_INT32 dwSource, L_INT nSourceFormat);
      virtual L_INT Resume (L_VOID);
      virtual L_INT StartRecord (L_CHAR L_FAR *pszFile, L_INT nDevice, L_INT nFormat);
      virtual L_INT StopRecord (L_VOID);
      //virtual L_INT SetCompressionOpts (pCOMPRESSIONOPTS pCompOpts);
      //virtual L_INT GetCompressionOpts (pCOMPRESSIONOPTS pCompOpts);
      virtual L_INT GetDefaultCompressionOpts(pCOMPRESSIONOPTS pCompOpts);
      virtual L_INT ConvertFromBitmapList (L_CHAR L_FAR *pszFile, L_INT nfPerSec, L_INT nBitsPerPixel, HBITMAPLIST hList, L_CHAR L_FAR* pszComp,pCOMPRESSIONOPTS pCompOpts=NULL);
      virtual L_INT ConvertFromBitmapList (L_CHAR L_FAR *pszFile, L_INT nfPerSec, L_INT nBitsPerPixel, LBitmapList* pBitmapList, L_CHAR L_FAR* pszComp, pCOMPRESSIONOPTS pCompOpts=NULL);
              HWND  CreateWin(HWND hParentWnd, L_INT nID = 0, L_UINT uStyles = WS_VISIBLE,
                              L_INT x = 0, L_INT y = 0, L_INT nCx = 320, L_INT nCy = 200);
      virtual L_INT AdjustWin (L_INT nXpos, L_INT nYpos, L_INT nWidth, L_INT nHeight);
      virtual L_INT SetParentWin (HWND hwndOwner);
      virtual L_INT SetMessageWin (HWND hwndMessage);
      virtual L_INT GetCurrentPos (L_INT32 L_FAR *plPos);
      virtual L_INT SetCurrentPos (L_INT32 lPos);
      virtual L_INT SetWinVisible (L_BOOL bVisibility=TRUE);
      virtual L_INT ReplaceFrame (L_INT32 lFrame, pBITMAPHANDLE pBitmap);
      virtual L_INT ReplaceFrame (L_INT32 lFrame, LBitmapBase L_FAR* pBitmap);
      virtual L_INT InsertFrame (L_INT32 lFrame, pBITMAPHANDLE pBitmap);
      virtual L_INT InsertFrame (L_INT32 lFrame, LBitmapBase L_FAR* pBitmap);
      virtual L_INT DeleteFrames (L_INT32 lStart, L_INT32 lLength, L_UINT32 uFlags=MM_EDIT_VIDEO|MM_EDIT_AUDIO);
      virtual L_INT CopyFrames (L_INT32 lStart, L_INT32 lLength, L_UINT32 uFlags=MM_EDIT_VIDEO|MM_EDIT_AUDIO);
      virtual L_INT PasteFrames (L_INT32 lStart, L_INT32 lLength, L_UINT32 uFlags=MM_EDIT_VIDEO|MM_EDIT_AUDIO);
      virtual L_INT SetActive (L_INT nActive = -1);
      virtual L_INT AddStream (L_UINT uType, L_VOID  L_FAR*pFormat, L_CHAR L_FAR *pszVidComp, L_INT nFPerSec, pCOMPRESSIONOPTS pCompOpts=NULL);
      virtual L_INT GetStreamType (L_INT nStream, L_UINT  L_FAR*puType);
      virtual L_INT Create (L_VOID);
      virtual L_INT Init (L_VOID);
      virtual L_INT IsClipboardReady (L_VOID);
      virtual L_INT DeleteStream (L_INT nStream);
      virtual L_BOOL IsPlaying (L_VOID);
      virtual L_INT SetRate (L_DOUBLE dRate=1.0f);
      virtual L_DOUBLE GetRate (L_VOID);
      virtual L_INT SetVolume (L_INT nVolume=50);
      virtual L_INT GetVolume (L_VOID);
      virtual L_INT SetBalance (L_INT nBalance=0);
      virtual L_INT GetBalance (L_VOID);
      virtual L_INT EnableEventCallback(L_BOOL bEnabled = TRUE);

      static  L_INT IsOptionAvailable(L_CHAR L_FAR *pszName, L_INT nType=COMP_VIDEO, L_INT nOption=MM_DLG_CONFIGURE);
      static  L_INT DisplayDlg(HWND hWndParent, L_CHAR L_FAR *pszName, L_INT nType=COMP_VIDEO, L_INT nDlgType=MM_DLG_CONFIGURE);
};

#endif //_LEAD_MULTIMEDIA_H_

/*================================================================= EOF =====*/
