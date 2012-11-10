/*----------------------------------------------------------------------------+
| LEADTOOLS for Windows -                                                     |
| Copyright (c) 1991-2000 LEAD Technologies, Inc.                             |
| All Rights Reserved.                                                        |
|-----------------------------------------------------------------------------|
| PROJECT   : LEAD wrappers                                                   |
| FILE NAME : ltcBWnd.h                                                       |
| DESC      :                                                                 |
+----------------------------------------------------------------------------*/

#ifndef  _LEAD_BITMAPWINDOW_H_
#define  _LEAD_BITMAPWINDOW_H_
/*----------------------------------------------------------------------------+
| CLASSES DECLARATION                                                         |
+----------------------------------------------------------------------------*/
#include "ltcShape.h"

#define  FLOAT_RGN_TRANS_NONE          0
#define  FLOAT_RGN_TRANS_FROM_WINDOW   1
#define  FLOAT_RGN_TRANS_USE_XFORM     2

typedef struct tagMAGGLASSDATA
{
   L_INT             nWidth;
   L_INT             nHeight;
   L_INT             nZoom;
   COLORREF          clrPen;
   COLORREF          clrBack;
   L_BOOL            bEllipse;
   L_INT             nBorderSize;
   L_BOOL            b3D;
   HCURSOR           hCursor;
   L_UINT32          uPaintFlags;
   COLORREF L_FAR*   pMask;
   L_UINT            uMaskCount;
   L_INT             nCrosshair;
   L_BOOL            bIgnoreRgn;
   L_BOOL            bCenter;
}MAGGLASSDATA, L_FAR *pMAGGLASSDATA;

/*----------------------------------------------------------------------------+
| Class     : LBitmapWindow                                                   |
| Desc      :                                                                 |
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+
| Date      : September  1998                                                 |
+----------------------------------------------------------------------------*/
class LWRP_EXPORT LBitmapWindow :public LBitmap
{
	friend class LAnnotationWindow;

   LEAD_DECLAREOBJECT(LBitmapWindow);
   LEAD_DECLARE_CLASS_MAP();

   public:
      L_VOID *m_extLBitmapWindow;

   private :
      static  L_BOOL    m_bBitmapWindowRegisterd;
      static  L_INT     m_nBitmapWindowInstanceCount;
      static  HCURSOR   m_hHandCursor;
      static  HCURSOR   m_hZoomToRectCursor;
      static  HCURSOR   m_hZoomInMouseCursor;

      LShape*           m_pShape;
      L_INT             m_nHScrollPos;
      L_INT             m_nHorzMaxPos;
      L_INT             m_nVScrollPos;
      L_INT             m_nVertMaxPos;
      L_BOOL            m_bAutoPaint;
//      L_BOOL            m_bPicturize;
      HANDLE            m_hPaintThread;
      L_BOOL            m_bDrawAll;

      DWORD             m_dwPaintID; 
      L_BOOL            m_bTransparentColor;


      L_BOOL            m_bMouseCaptured;
      L_BOOL            m_bPaintWhileLoad; 
      L_BOOL            m_bFloaterAsMain;
      RECT              m_ClientRect;
      L_BOOL            m_bNotUsed2;
      L_FLOAT           m_fCurrentZoom;
      HCURSOR           m_hCursor;
      L_BOOL            m_polygonStart;
      L_BOOL            m_CurveStart;
      L_BOOL            m_BezierStart;
      L_UINT            m_uRgnFrameTimer;
      L_UINT            uRgnFramType;
      L_BOOL            m_bFloaterOnWork;
      L_BOOL            m_bBusy;

      L_BOOL            m_bAutoFloaterToRgn;
      L_BOOL            m_bAutoRgnToFloater;
      L_BOOL            m_bCreatingFloater;
      L_BOOL            m_bFloater;
      L_BOOL            m_bFloaterMove;
      LBitmap           m_LBitmapFloater;
      BITMAPHANDLE      m_NotUsed3;
      POINT             m_ptStartPos;
      POINT             m_ptStartFloater;
      WNDPROC           m_pPanFun;
      WNDPROC           m_pWindowFun;
      RECT              m_NotUsed4;

      L_BOOL            m_KeyBoardEnable;
      LBuffer           m_LBuffer;
      L_INT             m_nNotUsed5;
      L_INT             m_nStopPaint;
      L_BOOL            m_bOperationCanceld;

      //MagGlass
      L_BOOL            m_bMagGlass;
      L_INT             m_nMagGlassWidth;
      L_INT             m_nMagGlassHeight;
      L_INT             m_nMagGlassZoom;
      COLORREF          m_clrMagGlassPen;
      COLORREF          m_clrMagGlassBack;
      L_BOOL            m_bMagGlassEllipse;
      L_INT             m_nMagGlassBorderSize;
      L_BOOL            m_bMagGlass3D;
      HCURSOR           m_hMagGlassCursor;
      L_UINT32          m_uMagGlassPaintFlags;
      COLORREF L_FAR*   m_pMagGlassMask;
      L_UINT            m_uMagGlassMaskCount;
      L_INT             m_nMagGlassCrosshair;
      L_BOOL            m_bMagGlassIgnoreRgn;
      L_BOOL            m_bMagGlassCenter;
      CURVE             m_Curve;

   protected:

      HWND              m_hWnd;
      L_BOOL            m_bCreateAsControl;
      L_BOOL            m_bEndThread;
      L_UINT            m_uRegionType;
      L_UINT            m_uToolType; 
      L_BOOL            m_bCenterOnZoom;  
      L_BOOL            m_bAutoScroll;
      L_INT             m_nHLineStep;  
      L_INT             m_nVLineStep;  
      L_INT             m_nHPageStep;  
      L_INT             m_nVPageStep;  
      L_UINT            m_uMaxEfxPasses;
      L_UINT            m_uMaxTrnPasses;
      L_UINT            m_uEfxPass;
      L_UINT            m_uTransitionEffect;
      L_UINT            m_uTransition;
      L_BOOL            m_bEnableDrawGradient;
      L_BOOL            m_bEnableDrawPattern;
      L_BOOL            m_bEnablePaintTransition;
      L_BOOL            m_bEnablePaintEffect; 
      HWND              m_hPanWnd;
      L_UINT            m_uZoomMode;
      L_FLOAT           m_fZoomFactor;
      L_UINT            m_uRgnFrameType;
      L_INT             m_uGradientStyle;
      L_UINT            m_uEffect;
      L_INT             m_uPatternStyle;
      L_BOOL            m_bUpdatePan;
      L_UINT32          m_uROP3;
      L_BOOL            m_bDragAcceptFiles;  
      L_BOOL            m_bPaintSizeUseDPI;
      L_UINT32          m_uDisplayPanFlags;
      COLORREF          m_crPanPen;
      L_CHAR            m_szPanTitle[255];
   
   private :

      static LRESULT EXT_CALLBACK  BitmapWindowProcCS(HWND hWnd, UINT uMsg,
                                                 WPARAM wParam,LPARAM lParam);
      static L_VOID    EXT_CALLBACK PanWindowCS(HWND hPanWnd,HWND hParentWnd,L_UINT uFlag, 
                                    LPRECT lprcPan, L_VOID L_FAR* pUserData);

      LRESULT           BitmapWindowProcCallBack(HWND hWnd,UINT uMsg,
                                                 WPARAM wParam,LPARAM lParam);
      L_VOID            PanWindowCB(L_UINT uFlag,LPRECT prcPan);

      static LRESULT    CALLBACK  PanSubClass(HWND hWnd, UINT uMsg,
                                              WPARAM wParam,LPARAM lParam);

      static L_INT      EXT_CALLBACK PaintWhileLoadCallBack(pFILEINFO pFileInfo,pBITMAPHANDLE pBitmap,
                                               L_UCHAR L_FAR *pBuffer,L_UINT uFlags,
                                               L_INT nRow,L_INT nLines,L_VOID L_FAR * pData);
      static DWORD WINAPI PaintThreadCS(LPVOID pThis);

      L_VOID            InitializeClass();
      L_VOID            NotifyParent(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
      L_INT             RegisterBitmapWndClass();
      L_BOOL            UnRegisterBitmapWndClass(); 

      L_VOID            onPaint();
      L_VOID            PaintFast();
      L_VOID            PaintThread();
      L_VOID            EndPaintThread();

      L_VOID            OnTimer(UINT id);
      L_VOID            OnHScroll(HWND hWndCtl, UINT nCode, int nPos);
      L_VOID            OnVScroll(HWND hWndCtl, UINT nCode, int nPos);
      L_VOID            OnSize(UINT state, int cx, int cy);
      L_VOID            OnKeyDown(L_UINT vertKey,L_INT  nRepeat,L_UINT uFlags);
      L_INT             OnDropFile(HDROP hDrop);
      L_VOID            AdjustScrollBars();

      L_VOID            StartToolDrawing(POINT* pPoint);
      L_VOID            ContinueToolDrawing (POINT* pPoint,WORD wKeys);
      L_VOID            EndToolDrawing(POINT* pPoint);
      L_VOID            EndPolygon(POINT* pPoint);

      POINT             FixRectangle(LPRECT prcDst);

      L_VOID            SetRgn(HRGN hRgn);
      L_VOID            DrawShapeOnPanWindow();
      L_VOID            ZoomFloater();
      L_VOID            CreateFloater();
      L_VOID            DestroyFloater();
      L_VOID            MoveFloater(POINT* pPoint);
      L_VOID            DrawFloater(HDC hdc,L_BOOL bDrawInPan=TRUE,L_BOOL bFrame=TRUE);
      L_BOOL            IsPtInFloaterRgn(POINT point);
      L_VOID            DrawFloaterFrame();
      L_VOID            PrepareXFormPanFloater(RGNXFORM* pRgnXForm);
      L_VOID            SaveFloater();
      L_VOID            RestoreFloater();
      L_INT             GetDPIHeight();
      L_INT             GetDPIWidth();
      L_INT             CheckWorkOnFloater(L_UINT nChangeType,L_UINT nChangeCategory);
      L_VOID            Clean();
      HRGN              GetScreenFloaterRgn();
      L_VOID            SetRgnFrameTimer();
      L_VOID            KillRgnFrameTimer();
      L_INT             CombineFloater();
      L_BOOL            SetCurrentCursor();
      L_VOID            CreateFloaterPalette();
      L_VOID            ZoomOnMouse(POINT pt,L_BOOL bZoomIn);
      L_INT             ZoomInPoint(POINT pt,L_BOOL bZoomIn);
      //Magnifying Glass
      L_INT             StartMagGlass(L_VOID);
      L_INT             StopMagGlass(L_VOID);
      L_INT             UpdateMagGlassRect(RECT L_FAR* prcDst);
      L_VOID            ResetMagGlass();

   protected: 
      virtual L_VOID    PanWndCallBack(L_UINT uFlag,LPRECT prcPan);
      virtual LRESULT   MsgProcCallBack(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
      virtual L_BOOL    OnFileDropped(L_CHAR L_FAR* pszFile,L_UINT uFileNumber,L_UINT uFilesCount);
      virtual L_VOID    OnDraw(HDC hdc,RECT& Rect);
      virtual L_VOID    OnZoom(L_UINT uZoomPercent);

      virtual L_INT     StartChanging(L_UINT nChangeType,L_UINT nChangeCategory);
      virtual L_VOID    EndChanging(L_UINT nChangeType,L_UINT nChangeCategory,L_INT nRetCode);
      virtual L_VOID    PaintNotification(L_INT nPass, L_INT uType);
      virtual L_INT     StatusCallBack(L_INT nPercentComplete);
      virtual L_BOOL    IsPaintActive();
      virtual L_INT     PicturizeCallBack(pBITMAPHANDLE pCellBitmap,L_INT x,L_INT y);




   public :
      LBitmapWindow ();
      LBitmapWindow (HWND   hWndParent,L_INT  nID,DWORD  dwStyle=WS_VISIBLE|L_BS_CENTER|L_BS_PROCESSKEYBOARD,
                     L_INT  x=0,L_INT  y=0,L_INT  nCx=200,L_INT  nCy=200);

      ~LBitmapWindow();
      
      L_INT             SetWndHandle(HWND hWnd);
      L_BOOL            EnableAlwaysEndNotification(L_BOOL bEnable);
      L_BOOL            EnableChangeNotification(L_BOOL bEnable);

      L_BOOL            IsPanWndCreated();
      L_BOOL            IsKeyBoardEnabled();
      L_BOOL            EnableKeyBoard(L_BOOL bEnable);
      L_VOID            SnapWndToImage(L_BOOL bFlag=TRUE);

      L_BOOL            IsAutoPaintEnabled();
      L_BOOL            EnableAutoPaint(L_BOOL bEnable);

      L_INT             SetGradientParameters(LPGRADDLGPARM pGradDlgParm);
      L_INT             GetGradientParameters(LPGRADDLGPARM pGradDlgParm);
      L_INT             SetTransitionParameters(LPTRANSDLGPARM pTransDlgParm);
      L_INT             GetTransitionParameters(LPTRANSDLGPARM pTransDlgParm);
   
      L_INT              SetEffectParameters(LPEFXDLGPARM  pEfxDlgParm);
      L_INT              GetEffectParameters(LPEFXDLGPARM  pEfxDlgParm);

      HWND               CreateWnd(HWND   hWndParent,L_INT  nID=0,
                                   DWORD  dwStyle=WS_VISIBLE|L_BS_CENTER|L_BS_PROCESSKEYBOARD,
                                   L_INT  x=0,L_INT  y=0,L_INT  nCx=200,L_INT  nCy=200);

      L_BOOL             EnableFileName(L_BOOL bEnableFileName);

      L_INT                ZoomToRect(RECT& ZoomRect);

      L_VOID               Repaint(LPRECT pRect=NULL);

      L_UINT               GetZoomMode();
      L_INT                SetZoomMode(L_UINT uMode,L_BOOL bDraw=TRUE);
      
      POINT                ScrollBy(L_INT dx, L_INT dy);
      POINT                ScrollTo(L_INT x, L_INT y);
   
      HWND                 GetPanWnd(L_VOID);
   
      HWND                 CreatePanWnd(L_UINT32 ulDisplayFlags,L_INT x,L_INT y,
                                        L_INT nCx,L_INT nCy,L_CHAR L_FAR* pszClassName, 
                                        HICON hIcon, HCURSOR hCursor,L_BOOL bSysMenu);

      L_INT                UpdatePanWnd(L_UINT32 ulDisplayFlags,
                                           COLORREF crPen,LPCSTR pszTitle);

      L_INT                DestroyPanWnd();

      L_BOOL               HandlePalette(UINT uMsg,WPARAM  wParam,LPARAM lParam);   

      HWND                 GetBitmapWnd();
      L_BOOL               EnablePaintWhileLoad(L_BOOL bEnable);
      L_BOOL               IsPaintWhileLoadEnabled();
      L_BOOL               EnableAutoScroll(L_BOOL bAutoScroll);   
      L_BOOL               IsAutoScrollEnabled();   
      L_VOID               SetRgnFrameType(L_UINT uRgnFrameType);
      L_UINT               GetRgnFrameType();
      L_VOID               SetPaintEffect(L_UINT   uEffect);
      L_UINT               GetPaintEffect();
      L_VOID               SetTransitionEffect(L_UINT uTransitionEffect);
      L_UINT               GetTransitionEffect();
      L_VOID               SetMaxEffectPasses(L_UINT  uMaxPasses);
      L_UINT               GetMaxEffectPasses();
      L_VOID               SetMaxTransitionPasses(L_UINT uMaxPasses);
      L_UINT               GetMaxTransitionPasses();
      L_VOID               SetTransition(L_UINT uTransition);
      L_UINT               GetTransition();
      L_VOID               SetGradientStyle(L_UINT uGradientStyle);
      L_UINT               GetGradientStyle();
      L_VOID               SetPatternStyle(L_UINT  uPatternStyle);
      L_UINT               GetPatternStyle();
      L_VOID               SetPatternForeColor(COLORREF  PatternForeColor);
      COLORREF             GetPatternForeColor();
      L_VOID               SetPatternBackColor(COLORREF  PatternBackColor);
      COLORREF             GetPatternBackColor();
      L_VOID               SetROP3(L_UINT32  uROP3);
      L_UINT32             GetROP3();

      L_BOOL               EnableCenterOnZoom(L_BOOL  bCenter);
      L_BOOL               IsCenterOnZoomEnabled();
      
      L_BOOL               EnableDragAcceptFiles(L_BOOL  bDragAcceptFiles);
      L_BOOL               IsDragAcceptFilesEnabled();
      L_BOOL               EnablePaintSizeUseDPI(L_BOOL  bPaintSizeUseDPI);
      L_BOOL               IsPaintSizeUseDPIEnabled();

      L_BOOL               EnableDrawGradient(L_BOOL bEnable);
      L_BOOL               IsDrawGradientEnabled();
      L_BOOL               EnableDrawPattern(L_BOOL bEnable);
      L_BOOL               IsDrawPatternEnabled();
      L_BOOL               EnablePaintEffect(L_BOOL bEnable);
      L_BOOL               IsPaintEffectEnabled();
      L_BOOL               EnablePaintTransition(L_BOOL bEnable);
      L_BOOL               IsPaintTransitionEnabled();

      L_UINT               GetRegionType();
      L_VOID               SetRegionType(L_UINT uRegionType);
      L_UINT               GetToolType();
      L_VOID               SetToolType(L_UINT uToolType);

      L_VOID               ZoomIn();
      L_VOID               ZoomOut();

      L_VOID               SetZoomFactor (L_FLOAT fZoomFactor=1.3f);
      L_FLOAT              GetZoomFactor (L_VOID);

      L_VOID               SetZoomPercent(L_UINT uPercent);
      L_UINT               GetZoomPercent();

      L_UINT               GetHorzLineStep();
      L_VOID               SetHorzLineStep(L_INT nHLineStep);
      L_UINT               GetVertLineStep();
      L_VOID               SetVertLineStep(L_INT nVLineStep);
      L_VOID               FitToParent(L_BOOL bFlag=TRUE);
      L_INT                Move(RECT& rect,L_BOOL bFlag=TRUE);
      L_VOID               GetBitmapVisibleRect(LPRECT pRect);

      LBitmap              *GetFloater();
      L_BOOL               SetAutoRgnToFloater(L_BOOL bAutoRgnToFloater=TRUE);
      L_BOOL               GetAutoRgnToFloater();
      
      L_BOOL               SetAutoFloaterToRgn(L_BOOL bAutoFloaterToRgn=TRUE);
      L_BOOL               GetAutoFloaterToRgn();
         

      L_VOID               CancelRgn();
      L_BOOL               HasFloater();
      HRGN                 GetFloaterRgn(L_UINT uFloatRgnType, RGNXFORM* pRgnXForm = NULL);

      L_BOOL               IsToolTypeMagGlass();

      virtual L_INT        CopyFromClipboard(HWND hWnd);
      virtual L_INT        CopyToClipboard(HWND hWnd,L_UINT uFlags=COPY2CB_EMPTY|COPY2CB_DIB|COPY2CB_DDB|COPY2CB_PALETTE|COPY2CB_FLOATER);
      
      virtual L_INT        Load( L_INT nBitsPerPixel,
                                 L_INT nOrder,
                                 L_INT nPage,
                                 pFILEINFO pFileInfo = NULL
                               );
      virtual L_INT        Load( L_INT nBitsPerPixel=0,
                                 L_INT nOrder=ORDER_BGRORGRAY,
                                 pLOADFILEOPTION pLoadFileOption = NULL,
                                 pFILEINFO pFileInfo = NULL
                               );
      virtual L_INT        Load( L_CHAR L_FAR *pszFileName,
                                 L_INT nBitsPerPixel,
                                 L_INT nOrder,
                                 L_INT nPage,
                                 pFILEINFO pFileInfo = NULL
                               );
      virtual L_INT        Load( L_CHAR L_FAR *pszFileName,
                                 L_INT nBitsPerPixel=0,
                                 L_INT nOrder=ORDER_BGRORGRAY,
                                 pLOADFILEOPTION pLoadFileOption = NULL,
                                 pFILEINFO pFileInfo = NULL
                               );

      virtual L_INT        SetDisplayMode(L_UINT32 uFlagPos,L_UINT32 uFlagSet);
      virtual L_BOOL       EnableLocalSettings(L_BOOL bEnable);
      virtual L_INT        SetPaintIntensity(L_INT nValue);
      virtual L_INT        SetPaintGamma(L_UINT uValue);
      virtual L_INT        SetPaintContrast(L_INT nValue);
      virtual L_INT        SetDefaultDithering(L_UINT uMethod);
      virtual L_INT        GetMagGlassOptions(pMAGGLASSDATA pOptions);
      virtual L_INT        SetMagGlassOptions(pMAGGLASSDATA pOptions=NULL);
      virtual L_VOID       SetRgnCurveOptions(L_UINT uFillMode, L_DOUBLE dTension, L_INT nClose);
      virtual L_VOID       GetRgnCurveOptions(L_UINT * puFillMode,
                                              L_DOUBLE * pdTension = NULL,
                                              L_INT * pnClose = NULL);
      
private:
   L_INT16 XClientToBitmap(L_INT16 x);   
   L_INT16 YClientToBitmap(L_INT16 y);
   L_INT16 XClientToBitmapInverse(L_INT16 x);
   L_INT16 YClientToBitmapInverse(L_INT16 y);
   L_VOID PixelizePoint(LPPOINTS pPoint);


};

#endif //_LEAD_BITMAPWINDOW_H _
/*================================================================= EOF =====*/
