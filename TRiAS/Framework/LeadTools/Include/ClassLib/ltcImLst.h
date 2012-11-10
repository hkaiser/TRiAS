/*----------------------------------------------------------------------------+
| LEADTOOLS for Windows -                                                     |
| Copyright (c) 1991-2000 LEAD Technologies, Inc.                             |
| All Rights Reserved.                                                        |
|-----------------------------------------------------------------------------|
| PROJECT   : LEAD wrappers                                                   |
| FILE NAME : ltcimlst.h                                                      |
| DESC      : header file for LEAD Image List Control class LImageListControl |
+----------------------------------------------------------------------------*/

#ifndef  _LEAD_IMAGELIST_H_
#define  _LEAD_IMAGELIST_H_

/*----------------------------------------------------------------------------+
| CLASS DECLARATION                                                           |
+----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------+
| Class     : LImageListControl                                               |
| Desc      :                                                                 |
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+
| Date      : May 1999                                                        |
+----------------------------------------------------------------------------*/
class LWRP_EXPORT LImageListControl :public LBase
{
   LEAD_DECLAREOBJECT(LImageListControl);

   public:
      L_VOID *m_extLImageListControl;

   private:
      static LRESULT EXT_CALLBACK  ImageListProcCS(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
      static LRESULT EXT_CALLBACK  ParentWndProcCS(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam);

   protected:  
      // data members
      WNDPROC m_pfnSuperClassProc;

   public:
      // data members
      HWND    m_hWnd;

      // constructors
      LImageListControl();
      LImageListControl(HWND hWndParent, L_INT nID,
                        DWORD dwStyle=WS_CHILD|WS_VISIBLE|WS_BORDER|WS_TABSTOP,
                        L_INT x=0, L_INT y=0, L_INT nCx=200, L_INT nCy=200,
                        COLORREF cbBackground=RGB(128,128,128));
      // destructors
      ~LImageListControl();

      // member functions
      HWND CreateControl(HWND hWndParent, L_INT nID=0,
                         DWORD dwStyle=WS_CHILD|WS_VISIBLE|WS_BORDER|WS_TABSTOP,
                         L_INT x=0, L_INT y=0, L_INT nCx=200, L_INT nCy=200,
                         COLORREF crBackground = RGB(128,128,128));

      L_INT GetSelectionOptions(pLILSELOPTION pSelOptions);
      L_INT SetSelectionOptions(pLILSELOPTION pSelOptions);
      
      L_INT GetItemOptions(pLILITEMOPTION pItemOptions);
      L_INT SetItemOptions(pLILITEMOPTION pItemOptions);

      L_INT GetBackColor(COLORREF L_FAR* pcrBack);
      L_INT SetBackColor(COLORREF crBack);

      L_INT GetBorderColor(COLORREF L_FAR* pcrBorder);
      L_INT SetBorderColor(COLORREF crBorder);

      L_INT GetScrollStyle(L_VOID);
      L_INT SetScrollStyle(L_INT nScrollStyle=SCROLLSTYLE_VERTICAL);

      L_BOOL EnableKeyboard(L_BOOL bEnable=TRUE);

      L_INT Insert(pLILITEM pItem, L_INT nIndex=-1);
      L_INT Update(pLILITEM pItem, L_INT nIndex);

      L_INT GetItem(pLILITEM pItem, L_INT nIndex);

      L_INT Remove(L_INT nIndex);

      L_INT Clear(L_VOID);

      L_INT EnsureVisible(L_INT nIndex);

      L_INT GetItemCount(L_VOID);

      L_INT GetRowCount(L_VOID);
      L_INT GetColumnCount(L_VOID);

      L_INT Sort(L_BOOL bAscending=TRUE);

      L_INT ScrollItems(L_INT nCount=1);

      L_INT SelectAll(L_BOOL bFlag=TRUE);

      L_INT GetSelectCount(L_VOID);
      L_INT GetSelectedItems(pLILITEM pItems=NULL);

      L_INT HitTest(POINT L_FAR* pPoint);

      L_INT SetDisplayFlags(L_UINT32 uFlags);

      L_INT SetSelectionBitmap(COLORREF crTransparent, LBitmapBase *pBitmap);

      L_INT GetViewSize();

      L_INT GetFirstVisible();

      // overridables
      virtual LRESULT MsgProcCallBack(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
      virtual L_VOID ItemSelected(L_INT nCtlID, pLILITEMSEL pItemSel);
      virtual L_INT DrawItem(pLILDRAWITEM pDrawItem);
};

#endif //_LEAD_IMAGELIST_H_
/*================================================================= EOF =====*/
