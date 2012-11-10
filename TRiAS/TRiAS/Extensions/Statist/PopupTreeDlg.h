// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 03.01.2001 09:32:39 
//
// @doc
// @module PopupTreeDlg.h | Declaration of the <c CPopupTreeDlg> class

#if !defined(_POPUPTREEDLG_H__14A67EDC_6B0A_4767_A2F3_1423AC14EDCF__INCLUDED_)
#define _POPUPTREEDLG_H__14A67EDC_6B0A_4767_A2F3_1423AC14EDCF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// Messages, die zum Parentdialoig geschickt werden
#define WM_ITEMSELECTED	(WM_USER+2345)
#define WM_CANCELDIALOG	(WM_USER+2346)

///////////////////////////////////////////////////////////////////////////////
// Basisklasse der PopupDialoge
class CPopupTreeDlgBase
{
public:
	virtual HRESULT GetSelectedObject (IUnknown **ppIUnk) = 0;
};

///////////////////////////////////////////////////////////////////////////////
// PopupDialog
class CPopupTree;

template<class T>
class CPopupTreeDlg : 
	public CDialogImpl<T>, 
	public CMessageFilter,
	public CPopupTreeDlgBase
{
public:
	CPopupTreeDlg(CPopupTree *pPopupTree) :
		m_pParent(pPopupTree)
	{
	}
	virtual BOOL PreTranslateMessage(MSG* pMsg)
	{
		return IsDialogMessage(pMsg);
	}

	BEGIN_MSG_MAP_EX(CPopupTreeDlg)
		MSG_WM_INITDIALOG(OnInitDialog)
		MESSAGE_HANDLER_EX(WM_CANCELDIALOG, OnCancelDialog)
		MESSAGE_HANDLER_EX(WM_ITEMSELECTED, OnOK)
		COMMAND_ID_HANDLER_EX(IDCANCEL, OnCancel)
	END_MSG_MAP()

	LRESULT OnInitDialog(HWND /*wParam*/, LPARAM /*lParam*/)
	{	
	// register object for message filtering 
	CMessageLoop *pLoop = _Module.GetMessageLoop();
		
		_ASSERTE(NULL != pLoop);
		pLoop -> AddMessageFilter(this);
		return TRUE;
	}

	LRESULT OnCancelDialog (UINT uiMsg, WPARAM wParam, LPARAM lParam)
	{
		m_pParent -> Fire_OnCanceledSelection();
		return DestroyDialog(IDCANCEL);
	}
	LRESULT OnOK(UINT uiMsg, WPARAM wParam, LPARAM lParam)
	{
		m_pParent -> OnItemSelected();
		return DestroyDialog(IDOK);
	}
	void OnCancel(UINT uiCode, int iCtrlid, HWND hCtrl)
	{
		m_pParent -> OnCanceledSelection();
		DestroyDialog(IDCANCEL);
	}

// Resultat abfragen
	bool HasSelectedItem() { return m_strSelected.GetLength() > 0 ? true : false; }
	bool GetSelectedItem (CString &rStr)
	{
		if (!HasSelectedItem())
			return false;

		rStr = m_strSelected;
		return true;
	}
	LPCSTR GetSelectedItem() { return m_strSelected; }
	void SetSelectedItem (LPCSTR pcSelItem)
	{
		m_strSelected = pcSelItem;
	}

// Position richten
	void AdjustPosAndSize (CWindow *pWnd, CRect rcEdit, CRect rcBttn, CRect *prcPopup)
	{
		_ASSERTE(NULL != prcPopup);

	CRect rcPopupNew;

		GetWindowRect(prcPopup);

		rcPopupNew.left = rcEdit.left;
		rcPopupNew.right = rcBttn.right;
		rcPopupNew.top = rcEdit.bottom + 1;
		rcPopupNew.bottom = rcPopupNew.top + prcPopup -> Height();

	// Fensterposition so richten, daß es nicht aus dem Bildschirm raushängt
		if (rcPopupNew.bottom >  GetSystemMetrics (SM_CYFULLSCREEN)) {
			rcPopupNew.bottom = rcEdit.top - 1;
			rcPopupNew.top = rcPopupNew.bottom - prcPopup -> Height();
		}
		*prcPopup = rcPopupNew;
	}

protected:
	BOOL DestroyDialog(int iRet)
	{
	// IsDialogMessage für dieses Fenster nicht mehr rufen
	CMessageLoop *pLoop = _Module.GetMessageLoop();
		
		_ASSERTE(NULL != pLoop);
		pLoop -> RemoveMessageFilter(this);

	// Fenster zerlegen		
		DestroyWindow();
		::PostQuitMessage(iRet);
		return TRUE;
	}

private:
	CPopupTree *m_pParent;
	CString m_strSelected;
};

#endif // !defined(_POPUPTREEDLG_H__14A67EDC_6B0A_4767_A2F3_1423AC14EDCF__INCLUDED_)
