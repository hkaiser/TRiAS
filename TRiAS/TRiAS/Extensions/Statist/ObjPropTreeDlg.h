// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 03.01.2001 09:32:39 
//
// @doc
// @module ObjPropTreeDlg.h | Declaration of the <c CObjPropTreeDlg> class

#if !defined(_OBJPROPTREEDLG_H__4A86C5BA_FF42_4372_81B2_1F4C232EB645__INCLUDED_)
#define _OBJPROPTREEDLG_H__4A86C5BA_FF42_4372_81B2_1F4C232EB645__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "ObjPropTreeCtrl.h"
#include "PopupTreeDlg.h"

class CObjPropTreeDlg : 
	public CPopupTreeDlg<CObjPropTreeDlg>
{
public:
	CObjPropTreeDlg(CPopupTree *pPopupTree, LPCSTR pcPreSelect) :
		CPopupTreeDlg<CObjPropTreeDlg>(pPopupTree)
	{
		if (NULL != pcPreSelect) {
			m_rStrs.push_back(pcPreSelect);
			SetSelectedItem(pcPreSelect);
		}
	}

	enum { IDD = IDD_POPUPTREEDLG };

	BEGIN_MSG_MAP_EX(CObjPropTreeDlg)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_SIZE(OnSize)
		REFLECT_NOTIFICATIONS()
		MESSAGE_HANDLER_EX(WM_ITEMSELECTED, OnOK)
		CHAIN_MSG_MAP(CPopupTreeDlg<CObjPropTreeDlg>)
	END_MSG_MAP()

	static HRESULT GetObjectProps (IObjectProps **ppIProps)
	{
	WObjectProps Props;
	BOOL fMustReInit = DEX_GetObjectProps (Props.ppi());

		if (Props.IsValid()) {
		// evtl. alle ObjProps installieren
			if (fMustReInit) {
				Props -> OnNewReferenceObject (-1L);	// alles bisherige löschen
				if (FAILED(Props -> OnNewReferenceObject (0L))) 
					return FALSE;
				DEX_SetMustInitOPFs(FALSE);
			}
			*ppIProps = Props.detach();
			return S_OK;
		}
		return E_FAIL;
	}

	LRESULT OnInitDialog(HWND wParam, LPARAM lParam)
	{
		if (!CPopupTreeDlg<CObjPropTreeDlg>::OnInitDialog(wParam, lParam))
			return FALSE;

	// Liste der Objekteigenschaften initialisieren
	WObjectProps Props;

		GetObjectProps (Props.ppi());

		m_treeObjProps.SubclassWindow(GetDlgItem(IDC_POPUPTREE));
		m_treeObjProps.Init (Props, m_rStrs);
		return TRUE;
	}

	void OnSize (UINT uiFlags, CSize szNewSize)
	{
		m_treeObjProps.SetWindowPos (NULL, 0, 0, szNewSize.cx, szNewSize.cy, SWP_NOZORDER);
	}
	LRESULT OnOK(UINT uiMsg, WPARAM wParam, LPARAM lParam)
	{
	CString strSelected, strSelectedFull;

		if (m_treeObjProps.CountSelectedItems() > 0)
			m_treeObjProps.GetSelectedObjProp(strSelected, &strSelectedFull);

		SetSelectedItem(strSelected);
		return CPopupTreeDlg<CObjPropTreeDlg>::OnOK(uiMsg, wParam, lParam);
	}

	HRESULT GetSelectedObject (IUnknown **ppIUnk)
	{
		return m_treeObjProps.GetSelectObject(ppIUnk);
	}
	static HRESULT GetObjectProp (LPCSTR pcObjProp, IObjectProperty **ppIObjProp)
	{
	WObjectProps Props;

		GetObjectProps(Props.ppi());
		return CObjPropTreeCtrl::GetObjectProp(pcObjProp, Props, ppIObjProp);
	}

private:
	CObjPropTreeCtrl m_treeObjProps;
	list<os_string> m_rStrs;
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_OBJPROPTREEDLG_H__4A86C5BA_FF42_4372_81B2_1F4C232EB645__INCLUDED_)
