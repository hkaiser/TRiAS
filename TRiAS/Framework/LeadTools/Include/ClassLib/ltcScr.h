/*----------------------------------------------------------------------------+
| LEADTOOLS for Windows -                                                     |
| Copyright (c) 1991-2000 LEAD Technologies, Inc.                             |
| All Rights Reserved.                                                        |
|-----------------------------------------------------------------------------|
| PROJECT   : LEAD wrappers                                                   |
| FILE NAME : ltcbase.h                                                       |
| DESC      :                                                                 |
+----------------------------------------------------------------------------*/

#ifndef  _LEAD_SCREEN_CAPTURE_H_
#define  _LEAD_SCREEN_CAPTURE_H_

/*----------------------------------------------------------------------------+
| CLASSES DECLARATION                                                         |
+----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------+
| Class     : LScreenCapture                                                  |
| Desc      :                                                                 |
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+
| Date      : September 1998                                                  |
+----------------------------------------------------------------------------*/
class LWRP_EXPORT LScreenCapture : public LBase
{
   LEAD_DECLAREOBJECT(LScreenCapture);

   public:
      L_VOID *m_extLScreenCapture;
      
   protected:  
      LEADCAPTUREINFO         m_CaptureInfo; 
      LEADCAPTUREOPTION       m_CaptureOptions;
      LEADCAPTUREAREAOPTION   m_CaptureAreaOption; 
      LEADCAPTUREOBJECTOPTION m_CaptureObjectOptions;

      LBitmapBase L_FAR*      m_pBitmap;      

   private:  
      L_VOID InitializeClass();
      static L_INT EXT_CALLBACK ScreenCaptureCS(pBITMAPHANDLE pBitmap,
                                    pLEADCAPTUREINFO pCaptureInfo,
                                    L_VOID L_FAR * pUserData);

      static L_INT EXT_CALLBACK CaptureHotKeyCS(L_INT nHotKey,L_UINT uHotKeyModifiers,
                                    L_VOID L_FAR * pUserData);

   protected:
      virtual L_INT  ScreenCaptureCallBack();
      virtual L_INT  CaptureHotKeyCallBack(L_INT nHotKey,L_UINT uHotKeyModifiers);

   public:
      LScreenCapture();
      LScreenCapture(LBitmapBase L_FAR* pLBitmap);
      LScreenCapture(LScreenCapture L_FAR* pScreenCapture);
      virtual ~LScreenCapture();

      virtual L_VOID    SetBitmap(LBitmapBase L_FAR* pLBitmap);
      virtual L_BOOL    IsValid();

      virtual L_INT     SetCaptureOptions(pLEADCAPTUREOPTION pCaptureOptions);
      virtual L_INT     GetCaptureOptions(pLEADCAPTUREOPTION pCaptureOptions);

      virtual L_INT     SetCaptureAreaOptions(pLEADCAPTUREAREAOPTION pCaptureAreaOption);
      virtual L_INT     GetCaptureAreaOptions(pLEADCAPTUREAREAOPTION pCaptureAreaOption);

      virtual L_INT     SetCaptureObjectOptions(pLEADCAPTUREOBJECTOPTION   pCaptureObjectOptions);
      virtual L_INT     GetCaptureObjectOptions(pLEADCAPTUREOBJECTOPTION   pCaptureObjectOptions);

      virtual L_INT     SetDefaultCaptureOptions(L_VOID);
      virtual L_INT     SetDefaultAreaOptions(L_VOID);
      virtual L_INT     SetDefaultObjectOptions(L_VOID);

      virtual L_INT     CaptureWallpaper(L_VOID);
      virtual L_INT     CaptureFullScreen(L_VOID);
      virtual L_INT     CaptureMenuUnderCursor(L_VOID);
      virtual L_INT     CaptureWindowUnderCursor(L_VOID);
      virtual L_INT     CaptureMouseCursor(COLORREF crFill=RGB(255,255,255));

      virtual L_INT     CaptureWindow(HWND hWnd,WINDOWCAPTURETYPE wctCaptureType);
      virtual L_INT     CaptureActiveClient(L_VOID);
      virtual L_INT     CaptureActiveWindow(L_VOID);

      virtual L_INT     CaptureArea(L_VOID); 
      virtual L_INT     CaptureAreaOptionDlg(HWND hParentWnd);

      virtual L_INT     CaptureSelectedObject(L_VOID);
      virtual L_INT     CaptureObjectOptionDlg(HWND hParentWnd);

      virtual L_INT     SetCaptureOptionDlg(HWND hParentWnd);

      virtual L_INT     CaptureFromEXE(
                                       L_CHAR L_FAR* pszFileName,
                                       L_INT nResType,
                                       L_CHAR L_FAR* pResID,
                                       L_BOOL bCaptureByIndex,
                                       COLORREF clrBackGnd=RGB(0,0,0)
                                      );

      virtual L_INT     CaptureFromEXEDlg(
                                          L_CHAR L_FAR* pszFileName,
                                          COLORREF L_FAR* pTransparentColor,
                                          L_INT nResType, 
                                          L_INT nDialogType=LTCAPDLG_TREEVIEW
                                         );

      virtual L_INT     CaptureGetResCount(
                                             L_CHAR L_FAR* pszFileName, 
                                             L_INT nResType, 
                                             L_INT32 L_FAR* pnCount
                                          );

      static  L_BOOL    IsCaptureActive();
      static  L_INT     StopCapture(L_VOID);
};


#endif //_LEAD_SCREEN_CAPTURE_H_
/*================================================================= EOF =====*/
