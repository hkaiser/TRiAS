/*----------------------------------------------------------------------------+
| LEADTOOLS for Windows -                                                     |
| Copyright (c) 1990, 1998 by LEAD Technologies, Inc.                         |
| All Rights Reserved.                                                        |
|-----------------------------------------------------------------------------|
| PROJECT   :                                                                 |
| FILE NAME : LRasterPaintWindow.h                                            |
| DESC      :                                                                 |
+----------------------------------------------------------------------------*/
#ifndef  _LEAD_LRASTERPAINTWINDOW_H_
#define  _LEAD_LRASTERPAINTWINDOW_H_
/*----------------------------------------------------------------------------+
| INCLUDES                                                                    |
+----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------+
| CLASSES DECLARATION                                                         |
+----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------+
| Class     : LRasterPaintWindow                                              |
| Desc      :                                                                 |
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+
| Date      : March  2000                                                     |
+----------------------------------------------------------------------------*/

class LWRP_EXPORT LRasterPaintWindow :public LBase  //LBitmapBase
{
   private:
      static  L_BOOL                m_bRasterWindowRegisterd;
      static  L_INT                 m_nRasterWindowInstanceCount;
      WNDPROC                       m_pWindowFun;
      
      static pAUTOMATIONHANDLE      m_pAutomation;
      static LToolbar               m_LToolbar;
      pCONTAINERHANDLE              m_pContainer;

      PAINTBRUSH                    m_Paintbrush;
      PAINTSHAPE                    m_PaintShape; 
      PAINTREGION                   m_PaintRegion; 
      PAINTFILL                     m_PaintFill;
      PAINTTEXT                     m_PaintText;

      LBitmapBase                   m_LBitmapBase;
      L_DOUBLE                      m_dStretchFactor; 
      L_INT                         m_nHScroll;
      L_INT                         m_nVScroll;

   protected:
      HWND            m_hWnd;
      L_BOOL          m_bCreateAsControl;
      virtual LRESULT MsgProcCallBack(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);

   private:
      static LRESULT EXT_CALLBACK  RasterWindowProcCS(HWND hWnd, UINT uMsg,WPARAM wParam,LPARAM lParam);

      LRESULT        RasterWindowProcCallBack(HWND hWnd,UINT uMsg, WPARAM wParam,LPARAM lParam);
      L_VOID         InitializeClass();
      L_INT          RegisterRasterPntWndClass();
      L_BOOL         UnRegisterRasterWndClass();
      L_INT          FreeContainer();
      L_VOID         InitStruct();
      L_INT          PrepareContainer(L_VOID L_FAR *pModeData);
      L_VOID         InializeScroll(L_INT nWidth,L_INT nHeight);
      L_VOID         OnSize(L_INT nWidth ,L_INT nHeight);
      L_VOID         OnVScroll(L_UINT uCode,L_INT nPos);
      L_VOID         OnHScroll(L_UINT uCode,L_INT nPos);
      L_VOID         OnPaint();
      L_VOID         FillBkGrnd(HDC hdc = NULL);
      L_INT          SetOffset(L_INT nXOffset = 0, L_INT nYOffset = 0, L_INT nZOffset = 0);
      L_INT          GetScalar(pVECTORPOINT pvptScalarNum, pVECTORPOINT pvptScalarDen);

   public:
      LRasterPaintWindow();
      ~LRasterPaintWindow();

      L_INT                SetWndHandle(HWND hWnd);
      L_INT                SetBitmap(LBitmapBase * pLBitmap);
      LBitmapBase*         GetBitmap();

      L_BOOL               HandlePalette(UINT uMsg,WPARAM  wParam,LPARAM lParam);
      L_VOID               Repaint(LPRECT pRect=NULL, L_BOOL bDrawBK = TRUE);

      // Container Functions.
      L_VOID               SetPaintBrush(PAINTBRUSH* pPaintbrush);
      PAINTBRUSH*          GetPaintBrush();

      L_VOID               SetPaintShape(PAINTSHAPE*  pPaintShape);
      PAINTSHAPE*          GetPaintShape();

      L_VOID               SetPaintRegion(PAINTREGION* pPaintRegion);
      PAINTREGION*         GetPaintRegion();

      L_VOID               SetPaintFill(PAINTFILL* pPaintFill);
      PAINTFILL*           GetPaintFill();

      L_VOID               SetPaintText(PAINTTEXT* pPaintText);
      PAINTTEXT*           GetPaintText();

      // Automation Functions.
      static L_INT         SetToolbar(LToolbar *pLToolbar);
      static LToolbar*     GetToolbar();
      static L_INT         Free();
      static L_INT         Initialize();
      L_BOOL               IsValid();

      L_INT                Undo();
      L_INT                Redo();
      L_BOOL               CanUndo();
      L_BOOL               CanRedo();
      L_INT                Cut();
      L_INT                Copy();
      L_INT                Paste();
      L_INT                Delete();
      L_INT                Print();
      L_INT                SelectNone();
      L_INT                SelectAll();

      // ToolBar Functions.
      static L_INT         CreateToolbar(LToolbar* pLToolbar, HWND hWndParent, L_CHAR * lpCaption);
      static L_INT         FreeToolbar(LToolbar* pLToolbar);
      static L_INT         ShowToolbar(L_BOOL bShow);
      static L_INT         SetToolbarPosition(LPPOINT lpptPos, L_UINT32 dwFlags = TOOLBAR_POSITION_TOP | TOOLBAR_POSITION_LEFT);
};

#endif //_LEAD_LRASTERPAINTWINDOW_H_
/*================================================================= EOF =====*/
