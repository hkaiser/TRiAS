// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 05.09.2001 19:39:13 
//
// @doc
// @module ProjectValuesView.h | Declaration of the <c CProjectValuesView> class

#if !defined(_PROJECTVALUESVIEW_H__B6697DBC_83D5_4FD1_AF60_86630CFFD9A8__INCLUDED_)
#define _PROJECTVALUESVIEW_H__B6697DBC_83D5_4FD1_AF60_86630CFFD9A8__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "HourglassFX.h"
#include "TreeListView.h"

///////////////////////////////////////////////////////////////////////////////
// CProjectValuesView Class
template<class T>
class CProjectValuesView : 
	public CTreeListViewImpl<CProjectValuesView, CHourglassFX<T> >
{
public:
	typedef CTreeListViewImpl<CProjectValuesView, CHourglassFX<T> > base_t;

// Construction
	CProjectValuesView() : 
		base_t(WS_CHILD|WS_VISIBLE|HDS_HORZ), m_fInitialized(false) 
	{
	}
	~CProjectValuesView() {}

	DECLARE_WND_CLASS(_T("ProjectValuesView"))

	BEGIN_MSG_MAP_EX(CProjectValuesView)
		MSG_WM_SIZE(OnSize)
		CHAIN_MSG_MAP(base_t)
	ALT_MSG_MAP(1) // Tree
		MSG_WM_GETDLGCODE(OnGetDlgCode)
		MSG_WM_KEYDOWN(OnKeyDown)
		MESSAGE_HANDLER(WM_NCDESTROY, base_t::OnTreeNcDestroy)
		MESSAGE_HANDLER(WM_LBUTTONDOWN, base_t::OnTreeFixButtonHit)
		MESSAGE_HANDLER(WM_LBUTTONDBLCLK, base_t::OnTreeFixButtonHit)
		MESSAGE_HANDLER(WM_ERASEBKGND, base_t::OnTreeEraseBkGnd)
		MESSAGE_HANDLER(TVM_INSERTITEM, base_t::OnTreeItemInsert)
		MESSAGE_HANDLER(TVM_SETBKCOLOR, base_t::OnTreeSetColor)
		MESSAGE_HANDLER(TVM_SETTEXTCOLOR, base_t::OnTreeSetColor)
		MESSAGE_HANDLER(TVM_SETITEM, base_t::OnTreeSetItem)
		MESSAGE_HANDLER(TVMX_GETSUBITEM, base_t::OnTreeGetSubItem)
		MESSAGE_HANDLER(TVMX_SETSUBITEM, base_t::OnTreeSetSubItem)
		MESSAGE_HANDLER(TVM_GETITEMRECT, base_t::OnTreeGetItemRect)
	ALT_MSG_MAP(2) // Header
		MESSAGE_HANDLER(HDM_INSERTITEM, base_t::OnHeaderItemInsert)
		MESSAGE_HANDLER(HDM_DELETEITEM, base_t::OnHeaderItemDelete)
	END_MSG_MAP()

// Message handlers
	void OnSize (UINT uiParam, CSize szSize)
	{
		if (!m_fInitialized)
			return;		// do nothing while not initialized

	CRect rcTree, rcList;

		m_ctrlHeader.GetItemRect(0, &rcTree);	
		m_ctrlHeader.GetItemRect(1, &rcList);	

	HDITEM hdiTree, hdiList;
	long lWidth = MulDiv(rcTree.Width()+rcList.Width(), 110, 100);

		memset(&hdiTree, 0, sizeof(HDITEM));
		hdiTree.mask = HDI_WIDTH;
		hdiTree.cxy = MulDiv(szSize.cx, rcTree.Width(), lWidth);
		m_ctrlHeader.SetItem(0, &hdiTree);

		memset(&hdiList, 0, sizeof(HDITEM));
		hdiList.mask = HDI_WIDTH;
		hdiList.cxy = MulDiv(szSize.cx, rcList.Width(), lWidth);
		m_ctrlHeader.SetItem(1, &hdiList);

		UpdateLayout();
	}

	LRESULT OnGetDlgCode(MSG *pMsg)
	{
	LRESULT lRet = DefWindowProc(WM_GETDLGCODE, 0, (LPARAM)pMsg);

		if (NULL != pMsg && WM_KEYDOWN == pMsg->message && VK_TAB == pMsg->wParam) 
			lRet |= DLGC_WANTMESSAGE;
		return  lRet;
	}

	void OnKeyDown(TCHAR cChar, UINT iuRepeatCnt, UINT uiFlags)
	{
		if (VK_TAB == cChar) {
		HWND hDlgWnd = GetParent();	// übergeordnetes Dialogfenster
		HWND hAxWnd = ::GetParent(hDlgWnd);	// übergeordnetes AxWindow
		HWND hParentWnd = ::GetParent(hAxWnd);	// PageWindow im DockingKontext

			_ASSERTE(NULL != hDlgWnd && NULL != hAxWnd && NULL != hParentWnd);

		// selbst das nächste Control suchen
		HWND hCtrl = ::GetNextDlgTabItem(hParentWnd, hAxWnd, FALSE);

			_ASSERTE(NULL != hCtrl && ::IsWindow(hCtrl));
			::SetFocus (hCtrl);		// Focus selbst weiterreichen
			return;
		}
		SetMsgHandled(FALSE);
	}

// Operations
	bool Init()
	{
	// Tree control initialisieren (Spalten, Größen voreinstellen)
	CRect rcCanvas;
	HDITEM hdiColumn;

		GetWindowRect(&rcCanvas);
		memset(&hdiColumn, 0, sizeof(HDITEM));
		hdiColumn.mask = HDI_FORMAT | HDI_TEXT | HDI_WIDTH;
		hdiColumn.fmt = HDF_LEFT;
		hdiColumn.cxy = (3*rcCanvas.Width())/4;

	CString strName, strValue;

		strName.LoadString(IDS_STATISTVALUEHDRNAME);
		_ASSERTE(strName.GetLength() > 0);
		hdiColumn.pszText = (LPSTR)(LPCSTR)strName;
		m_ctrlHeader.InsertItem(0, &hdiColumn);

		hdiColumn.cxy = rcCanvas.Width() - hdiColumn.cxy - rcCanvas.Width()/20;
		strValue.LoadString(IDS_STATISTVALUEHDRVALUE);
		_ASSERTE(strValue.GetLength() > 0);
		hdiColumn.pszText = (LPSTR)(LPCSTR)strValue;
		m_ctrlHeader.InsertItem(1, &hdiColumn);

	// Imagelist laden und im Tree setzen
	CBitmap bmpIcons;
	CBitmap bmpMask;

		if (!bmpIcons.LoadBitmap(IDB_STATVALUES) || !bmpMask.LoadBitmap(IDB_STATVALUES_MASK)) {
			ATLTRACE("Could not load bitmaps for CProjectValuesView\r\n");
			return false;
		} 
		else if (!m_ItemBmps.Create(16, 16, ILC_COLOR8|ILC_MASK, 20, 0) ||
				-1 == m_ItemBmps.Add(bmpIcons, bmpMask)) 
		{
			ATLTRACE("Could not create imagelist for CProjectValuesView\r\n");
			return false;
		} 
		_ASSERTE(NULL != HIMAGELIST(m_ItemBmps));
		m_ItemBmps.SetOverlayImage(IMG_PUBLISH, OVL_PUBLISH);	// Publish ist Overlay 1

	// Wurzel füllen
		m_ctrlTree.SetImageList(m_ItemBmps, TVSIL_NORMAL);		// Imagelist an TreeControl dranhängen
		m_ctrlTree.PopulateRoot();

		m_fInitialized = true;
		return true;
	}

// Implementation
	InsertItem();

protected:
// Attributes

// Operations

private:
	bool m_fInitialized;
	CImageList m_ItemBmps;
};

#endif // !defined(_PROJECTVALUESVIEW_H__B6697DBC_83D5_4FD1_AF60_86630CFFD9A8__INCLUDED_)
