// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 03.01.2001 09:32:39 
//
// @doc
// @module StatFuncTreeDlg.h | Declaration of the <c CStatFuncTreeDlg> class

#if !defined(_STATFUNCTREEDLG_H__74755346_0864_4562_BB2C_9518D304CF81__INCLUDED_)
#define _STATFUNCTREEDLG_H__74755346_0864_4562_BB2C_9518D304CF81__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "StatFuncTreeCtrl.h"
#include "PopupTreeDlg.h"

class CStatFuncTreeDlg : 
	public CPopupTreeDlg<CStatFuncTreeDlg> 
{
public:
	CStatFuncTreeDlg(CPopupTree *pPopupTree, LPCSTR pcPreSelect) :
		CPopupTreeDlg<CStatFuncTreeDlg>(pPopupTree)
	{
		if (NULL != pcPreSelect)
			SetSelectedItem(pcPreSelect);
	}

	enum { IDD = IDD_POPUPTREEDLG };

	BEGIN_MSG_MAP_EX(CStatFuncTreeDlg)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_SIZE(OnSize)
		REFLECT_NOTIFICATIONS()
		MESSAGE_HANDLER_EX(WM_ITEMSELECTED, OnOK)
		CHAIN_MSG_MAP(CPopupTreeDlg<CStatFuncTreeDlg>)
	END_MSG_MAP()

	LRESULT OnInitDialog(HWND wParam, LPARAM lParam)
	{
		if (!CPopupTreeDlg<CStatFuncTreeDlg>::OnInitDialog(wParam, lParam))
			return FALSE;

		m_treeStatFuncs.SubclassWindow(GetDlgItem(IDC_POPUPTREE));
		m_treeStatFuncs.Init (GetSelectedItem());
		return TRUE;
	}

	void OnSize (UINT uiFlags, CSize szNewSize)
	{
		m_treeStatFuncs.SetWindowPos (NULL, 0, 0, szNewSize.cx, szNewSize.cy, SWP_NOZORDER);
	}
	LRESULT OnOK(UINT uiMsg, WPARAM wParam, LPARAM lParam)
	{
	CString strSelected, strFullSelected;

		if (m_treeStatFuncs.CountSelectedItems() > 0) 
			m_treeStatFuncs.GetSelectedStatFunc(strSelected, &strFullSelected);

		SetSelectedItem(strSelected);
		return CPopupTreeDlg<CStatFuncTreeDlg>::OnOK(uiMsg, wParam, lParam);
	}

	HRESULT GetSelectedObject (IUnknown **ppIUnk)
	{
		return m_treeStatFuncs.GetSelectObject(ppIUnk);
	}
	static HRESULT GetStatFunc (LPCSTR pcStatFunc, IGenericStatistics **ppIStatFunc)
	{
		return CStatFuncTreeCtrl::GetStatFunc(pcStatFunc, ppIStatFunc);
	}

private:
	CStatFuncTreeCtrl m_treeStatFuncs;
};

#endif // !defined(_STATFUNCTREEDLG_H__74755346_0864_4562_BB2C_9518D304CF81__INCLUDED_)
