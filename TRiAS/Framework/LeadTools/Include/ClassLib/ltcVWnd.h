/*----------------------------------------------------------------------------+
| LEADTOOLS for Windows -                                                     |
| Copyright (c) 1991-2000 LEAD Technologies, Inc.                             |
| All Rights Reserved.                                                        |
|-----------------------------------------------------------------------------|
| PROJECT   : LEAD wrappers                                                   |
| FILE NAME : ltcVWnd.h                                                       |
| DESC      :                                                                 |
+----------------------------------------------------------------------------*/

#ifndef  _LEAD_VECTORWINDOW_H_
#define  _LEAD_VECTORWINDOW_H_
/*----------------------------------------------------------------------------+
| CLASSES DECLARATION                                                         |
+----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------+
| Class     : LVectorWindow                                                   |
| Desc      :                                                                 |
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+
| Date      : September  1998                                                 |
+----------------------------------------------------------------------------*/
class LWRP_EXPORT LVectorWindow :public LVectorBase
{
   LEAD_DECLAREOBJECT(LVectorWindow);
   LEAD_DECLARE_CLASS_MAP();

   private :
      static  L_BOOL    m_bVectorWindowRegistered;
      static  L_INT     m_nVectorWindowInstanceCount;
      static  HCURSOR   m_hHandCursor;
      static  HCURSOR   Reserved1;
      static  HCURSOR   m_hRotateCursorXY;
      static  HCURSOR   m_hRotateCursorZ;
      static  HCURSOR   m_hSelectCursor;

      //For default m_bAutoScroll value
      //static L_BOOL     m_bStaticAutoScroll;


      L_INT             m_nHScrollPos;
      L_INT             m_nHorzMaxPos;
      L_INT             m_nVScrollPos;
      L_INT             m_nVertMaxPos;
      L_BOOL            m_bAutoPaint;

      L_BOOL            m_bMouseCaptured;
      RECT              m_ClientRect;
      HCURSOR           m_hCursor;

      WNDPROC           m_pWindowFun;

      L_BOOL            m_KeyBoardEnable;
      //L_INT             m_nKeyMode;
      L_INT             NotUsed1;
      RECT              m_rcDst;
      L_BOOL            m_bAdjustingScrollBars;
      L_BOOL            m_bSelecting;
      RECT              m_rectCapture;
      L_COLOR           m_BackColor;

      //For TOOL_VECTOR_SELECT
      L_BOOL            m_bSelect;
      L_BOOL            m_bUseRect;
      RECT              m_SelectRect;
      L_BOOL            m_bNeedPaint;
      L_BOOL            m_bObjectSelected;
      L_BOOL            m_bSelectedOnly;

      //For TOOL_VECTOR_PAN
      L_BOOL            m_bOkToPan;
      POINT             m_StartPoint;  //for panning and rotating
      L_BOOL            m_bPanning;

      //For Zooming
      VECTORPOINT       m_ZoomPoint;

      //For Rotating    
      L_INT            m_Rotating;
      VECTORPOINT      m_StartRotateAngle;
      L_INT            m_nOldDrawMode; //VECTOR_DRAW_NORMAL

      /*
      Moved this to LVectorBase

      //For LVKRN event callback
      pVECTOREVENTPROC m_OldEventProc;
      L_VOID          *m_pOldEventUserData;  
      
        */






   protected:
      HWND              m_hWnd;
      L_BOOL            m_bCreateAsControl;
      L_UINT            m_uToolType; 
      L_BOOL            m_bAutoScroll;
      VECTORPOINT       m_ScaleFactor;
      L_UINT            m_ZoomPercent;
      L_BOOL            m_bDragAcceptFiles;
   
   private :
      static LRESULT EXT_CALLBACK  VectorWindowProcCS(HWND hWnd, UINT uMsg,
                                                 WPARAM wParam,LPARAM lParam);

      LRESULT           VectorWindowProcCallBack(HWND hWnd,UINT uMsg,
                                                 WPARAM wParam,LPARAM lParam);

      L_VOID            InitializeClass();
      L_VOID            NotifyParent(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
      L_INT             RegisterVectorWndClass();
      L_BOOL            UnRegisterVectorWndClass(); 

      L_VOID            onPaint();
      L_VOID            OnVScroll(HWND pScrollBar, UINT nSBCode, UINT nPos);
      L_VOID            OnHScroll(HWND pScrollBar, UINT nSBCode, UINT nPos);

      L_VOID            OnSize(UINT state, int cx, int cy);
      L_VOID            OnKeyDown(L_UINT vertKey,L_INT  nRepeat,L_UINT uFlags);
      L_INT             OnDropFile(HDROP hDrop);
      L_VOID            AdjustScrollBars();

      L_VOID            SetCurrentCursor();
      L_INT             VectorSetViewPort();

      L_VOID            StartToolSelect(UINT nFlags, L_BOOL bSelectFlag, POINT point);
      L_VOID            ContinueToolSelect(UINT nFlags, POINT point);
      L_VOID            EndToolSelect(UINT nFlags, L_BOOL bSelectFlag, POINT point);
      L_VOID            DrawCaptureRect();

      L_INT             ResetView(L_UINT uFlags = VECTOR_RESET_ALL);



      /* 
      Moved this to LVectorBase

      static L_INT      EXT_CALLBACK  VectorEventProcCS(
                           pVECTORHANDLE pVector, 
                           L_UINT uEvent, 
                           L_UINT nStatus,
                           L_INT  nRet,
                           L_VOID *pReserved, 
                           L_VOID *pUserData );
      
      L_INT             VectorEventProcCallBack(
                           pVECTORHANDLE pVector, 
                           L_UINT uEvent, 
                           L_UINT nStatus,
                           L_INT  nRet,
                           L_VOID *pReserved, 
                           L_VOID *pUserData );

  */
      
      L_VOID            VectorToolRotateZYX(LPARAM lParam);
      L_VOID            VectorToolRotateXYZ(LPARAM lParam);




   protected: 
      virtual LRESULT   MsgProcCallBack(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
      virtual L_BOOL    OnFileDropped(L_CHAR L_FAR* pszFile,L_UINT uFileNumber,L_UINT uFilesCount);
      virtual L_VOID    OnDraw(HDC hdc,RECT& Rect);
      virtual L_VOID    OnZoom(L_INT ZoomPercent);
      virtual L_VOID    OnScale(VECTORPOINT ScaleFactor);

      virtual L_INT     StartChanging(L_UINT nChangeType,L_UINT nChangeCategory);
      virtual L_VOID    EndChanging(L_UINT nChangeType,L_UINT nChangeCategory,L_INT nRetCode);
      virtual L_INT     EnumObjectsCallBack(pVECTORHANDLE pVector, pVECTOROBJECT pObject);

      //BJ: solve the scolling problem in the ClassLib demo.
      virtual L_INT  VectorEventProcCallBack(
                           pVECTORHANDLE pVector, 
                           L_UINT uLevel, 
                           pVECTOREVENT pEvent, 
                           L_VOID L_FAR *pUserData 
                           );



   public :
      LVectorWindow();
      LVectorWindow(    HWND hWndParent,
                        L_INT  nID,
                        DWORD  dwStyle=WS_VISIBLE|L_BS_CENTER|L_BS_PROCESSKEYBOARD,
                        L_INT  x=0,
                        L_INT  y=0,
                        L_INT  nCx=200,
                        L_INT  nCy=200);

      virtual           ~LVectorWindow();

      L_INT             SetWndHandle(HWND hWnd);
      L_BOOL            EnableAlwaysEndNotification(L_BOOL bEnable);
      L_BOOL            EnableChangeNotification(L_BOOL bEnable);

      L_BOOL            IsKeyBoardEnabled();
      L_BOOL            EnableKeyBoard(L_BOOL bEnable);

      L_BOOL            IsAutoPaintEnabled();
      L_BOOL            EnableAutoPaint(L_BOOL bEnable);
   
      HWND              CreateWnd(  HWND hWndParent,
                                    L_INT  nID=0,
                                    DWORD  dwStyle=WS_VISIBLE|L_BS_PROCESSKEYBOARD,
                                    L_INT  x=0,
                                    L_INT  y=0,
                                    L_INT  nCx=200,
                                    L_INT  nCy=200);

      L_BOOL            EnableFileName(L_BOOL bEnableFileName);

      L_VOID            Repaint(LPRECT pRect=NULL);      
      POINT             ScrollBy(L_INT dx, L_INT dy);
      POINT             ScrollTo(L_INT x, L_INT y);
      L_BOOL            HandlePalette(UINT uMsg,WPARAM  wParam,LPARAM lParam);   

      HWND              GetVectorWnd();
      L_BOOL            EnableAutoScroll(L_BOOL bAutoScroll);   
      L_BOOL            IsAutoScrollEnabled();         
      L_BOOL            EnableDragAcceptFiles(L_BOOL  bDragAcceptFiles);
      L_BOOL            IsDragAcceptFilesEnabled();

      L_UINT            GetToolType();
      L_INT             SetToolType(L_UINT uToolType);

      L_VOID            ZoomIn();
      L_VOID            ZoomOut();

      L_VOID            ScaleIn();
      L_VOID            ScaleOut();

      L_INT             FitToParent(L_BOOL bFlag=TRUE);
      L_INT             Move(RECT& rect,L_BOOL bFlag=TRUE);
      L_INT             GetVectorVisibleRect(LPRECT pRect);
      L_INT             GetVectorRect(LPRECT pRect);

      L_VOID            SetScaleFactor(pVECTORPOINT pScaleFactor);
      VECTORPOINT       GetScaleFactor();

      L_VOID            SetZoomPercent(L_UINT ZoomPercent);
      L_UINT            GetZoomPercent();

      virtual L_INT     Load( L_CHAR L_FAR * pszFile, 
                              L_INT nEngine = VECTOR_ENGINE_GDI, 
                              L_UINT32 dwFlags = VECTOR_ENGINE_DOUBLEBUFFER,
                              pLOADFILEOPTION pLoadOption=NULL,
                              pFILEINFO pFileInfo = NULL);

      virtual L_INT     Load( 
                              L_INT nEngine = VECTOR_ENGINE_GDI, 
                              L_UINT32 dwFlags = VECTOR_ENGINE_DOUBLEBUFFER,
                              pLOADFILEOPTION pLoadOption=NULL,
                              pFILEINFO pFileInfo = NULL);

      virtual L_INT     CreateNew( L_INT nEngine    = VECTOR_ENGINE_GDI, 
                                   L_UINT32 dwFlags = VECTOR_ENGINE_DOUBLEBUFFER
                                 );

      L_INT             SelectAllObjects( L_BOOL bSelect,RECT L_FAR *pRect);

      L_BOOL            SetSelectedOnly( L_BOOL bSelectedOnly);
      L_BOOL            GetSelectedOnly();
      L_INT             SetPan(const POINT L_FAR *pPan);

      L_BOOL            IsControl();

      L_INT             SetBackgroundColor(L_COLOR color=0);
      L_INT             GetBackgroundColor(L_COLOR L_FAR *pColor);

      L_INT             SetEngine(L_INT nEngine = VECTOR_ENGINE_GDI, L_UINT32 dwFlags = VECTOR_ENGINE_DOUBLEBUFFER);

      L_INT             Reset(L_UINT uFlags = VECTOR_RESET_ALL);

};

#endif //_LEAD_VECTORWINDOW_H_
/*================================================================= EOF =====*/
