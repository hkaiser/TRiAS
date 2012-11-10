// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 02.05.2004 19:36:09
//
// @doc
// @module SelectCoordSysActionDlg.h | Declaration of the <c CSelectCoordSysActionDlg> class

#if !defined(__SELECTCOORDSYSACTIONDLG_H_)
#define __SELECTCOORDSYSACTIONDLG_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "CoordSystemTree.h"

/////////////////////////////////////////////////////////////////////////////
// CSelectCoordSysActionDlg dialog

class CSelectCoordSysActionDlg : 
	public CPropertyPage
{
// Construction
public:
	CSelectCoordSysActionDlg(ResID uiId, LPCSTR pcCaption);
	~CSelectCoordSysActionDlg();

	void SetDescription (HTREEITEM hItem = NULL);

// Dialog Data
	FixedText	m_ftDescription;
	CCoordSystemTree m_tvCoordSystems;
	os_string m_strTcfName;			// der Name des Koordinatensystemes

protected:
// EventHandler
	void WindowInit (Event);

	int OnWizFinish (NotifyEvt);
	int OnWizNext (NotifyEvt);
	int OnSetActive (NotifyEvt);

	void OnDblClick (NotifyEvt);
	void OnDeleteItem (NotifyEvt);
	void OnSelChanged (NotifyEvt);
	void OnItemExpanded (NotifyEvt);

public:
	void SetFlags (DWORD dwFlags) { m_dwFlags = dwFlags; }
	static CSelectCoordSysActionDlg *CreateInstance (UINT uiDlg, 
		LPCSTR pcCaption, ResourceFile &rRF);

	HRESULT GetSelectedCS(ITRiASCS **ppICS)
	{
		if (NULL != ppICS) {
		CComPtr<ITRiASCS> CS(m_CS);

			*ppICS = CS.Detach();
			return S_OK;
		}
		return E_POINTER;
	}

	void SetNextPageId(UINT uiNextPage)
	{
		m_uiNextPage = uiNextPage;
	}

// Implementation
protected:
	void AdjustSheetButtons(HTREEITEM hItem);
	BOOL GetDisableNextPage(HTREEITEM hItem);
	bool PrepareResult();

private:
	DWORD m_dwFlags;
	BOOL m_fNotEmpty;
	CComQIPtr<ITRiASCS, &IID_ITRiASCS> m_CS;
	UINT m_uiNextPage;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(__SELECTCOORDSYSACTIONDLG_H_)
