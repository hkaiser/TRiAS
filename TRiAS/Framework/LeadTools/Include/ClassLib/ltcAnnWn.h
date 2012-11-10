/*----------------------------------------------------------------------------+
| LEADTOOLS for Windows -                                                     |
| Copyright (c) 1991-2000 LEAD Technologies, Inc.                             |
| All Rights Reserved.                                                        |
|-----------------------------------------------------------------------------|
| PROJECT   : LEAD wrappers                                                   |
| FILE NAME : ltcAnnWn.h                                                      |
| DESC      :                                                                 |
+----------------------------------------------------------------------------*/

#ifndef  _LEAD_BITMAPANNWINDOW_H_
#define  _LEAD_BITMAPANNWINDOW_H_

#ifndef AnnLoadMemory
#define AnnLoadMemory z000AnnLoadMemory
#endif

/*----------------------------------------------------------------------------+
| CLASSES DECLARATION                                                         |
+----------------------------------------------------------------------------*/
//#include "ltcBWnd.h"

/*----------------------------------------------------------------------------+
| Class     : LAnnotationWindow                                               |
| Desc      :                                                                 |
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+
| Date      : September 1998                                                  |
+----------------------------------------------------------------------------*/
class LWRP_EXPORT LAnnotationWindow : public LBitmapWindow
{
   LEAD_DECLAREOBJECT(LAnnotationWindow);
   LEAD_DECLARE_CLASS_MAP();

   public:
      L_VOID *m_extLAnnotationWindow;

   private:
      LAnnAutomation             m_Automation;
      LAnnContainer              m_Container;
      static LAnnToolBar         m_ToolBar;
      static L_INT               m_nRefCount;
      L_BOOL                     m_bEntered;

   private:
      L_VOID            OnAnnotationEvent(L_UINT uAnnEvent,L_UINT32 lParam);
      L_INT             InitAnnAutomation(HWND hWnd);

   protected:
      virtual L_INT     StartChanging(L_UINT nChangeType,L_UINT nChangeCategory);
      virtual L_VOID    EndChanging(L_UINT nChangeType,L_UINT nChangeCategory,L_INT nRetCode);
      virtual LRESULT   MsgProcCallBack(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
      virtual L_VOID    OnAnnEvent(L_UINT uAnnEvent,L_UINT32 lParam);
      virtual L_VOID    OnDraw(HDC hdc,RECT& Rect);
      virtual L_VOID    OnZoom(L_UINT uZoomPercent);
      virtual L_VOID    PanWndCallBack(L_UINT uFlag,LPRECT prcPan);
      
   public : 
      LAnnotationWindow();
      LAnnotationWindow(
                        HWND hWndParent,L_INT nID=0,
                        DWORD dwStyle=WS_VISIBLE|L_BS_CENTER|L_BS_PROCESSKEYBOARD,
                        L_INT x=0,L_INT y=0,
                        L_INT nCx=200,L_INT nCy=200
                      );
      virtual ~LAnnotationWindow();

      virtual L_INT     CopyFromClipboard(HWND hWnd);
      virtual L_INT     CopyToClipboard(HWND hWnd,L_UINT uFlags=COPY2CB_ANNOBJECTS|COPY2CB_EMPTY|COPY2CB_DIB|COPY2CB_DDB|COPY2CB_PALETTE);

      L_BOOL            HandlePalette(UINT uMsg,WPARAM wParam,LPARAM lParam);
      LAnnAutomation&   GetAutomationObject();
      LAnnContainer&    GetContainerObject();
      LAnnToolBar&      GetToolBar();

      HWND              CreateWnd(
                                    HWND hWndParent,
                                    L_INT nID=0,
                                    DWORD dwStyle=WS_VISIBLE|L_BS_CENTER|L_BS_PROCESSKEYBOARD,
                                    L_INT x=0,L_INT y=0,
                                    L_INT nCX=200,L_INT nCY=200
                                 );
      L_INT             SetWndHandle(HWND hWnd);

      virtual L_INT     AnnPrint(HDC hDC,L_INT x=0,L_INT y=0,L_UINT width=0,L_UINT height=0);
      virtual L_INT     AnnLoad(L_CHAR L_FAR* pszFile,pLOADFILEOPTION pLoadFileOption=NULL);
      virtual L_INT     AnnLoadMemory(L_UCHAR L_FAR *phGlobalAnn, L_UINT32 uMemSize);

      virtual L_INT     AnnSave(L_CHAR L_FAR* pszFile, L_INT nFormat=ANNFMT_NATIVE,L_BOOL bSelected=FALSE);
      virtual L_VOID    SetToolType(L_UINT uToolType);
};

#endif //_LEAD_BITMAPANNWINDOW_H_
/*================================================================= EOF =====*/
