// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 10.10.2001 17:11:30
//
// @doc
// @module CopyObjectsDlg.h | Declaration of the <c CCopyObjectsDlg> class

#if !defined(_COPYOBJECTSDLG_H__6F48C5D9_360E_4CD9_B991_603E7E007A84__INCLUDED_)
#define _COPYOBJECTSDLG_H__6F48C5D9_360E_4CD9_B991_603E7E007A84__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "TRiAS03.h"       // main symbols
#include "DatasourceIcon.h"

/////////////////////////////////////////////////////////////////////////////
// CCopyObjectsDlg dialog

class CCopyObjects;

class CCopyObjectsDlg : 
	public CPropertyPage
{
// Construction
public:
	CCopyObjectsDlg(CCopyObjects *pParent, ResID uiDlg, LPCSTR pcCaption);
	~CCopyObjectsDlg();

	BOOL FInit (void) { return TRUE; }

// Dialog Data
	enum { 
		IDD = IDD_COPYOBJECTS_OPTIONS, 
		IDDPP = IDD_COPYOBJECTS_OPTIONSPP,
	};

// Overrides
	void WindowInit (Event e);

	int OnWizNext (NotifyEvt e);
	int OnWizFinish (NotifyEvt e);
	int OnSetActive (NotifyEvt e);

public:
	void SetFlags (DWORD dwFlags) { m_dwFlags = dwFlags; }
	static CCopyObjectsDlg *CreateInstance (CCopyObjects *pParent, ResID uiDlg, LPCSTR pcCaption);

	HPROPSHEETPAGE CreatePage (void) { return CPropertyPage::CreatePage(); }

	void SetDataSource (BSTR bstrDataSource) { m_bstrDataSource = bstrDataSource; }
	BSTR GetDataSource() { return m_bstrDataSource; }

	BOOL __stdcall EnumDataSources (HPROJECT hPr, BOOL, UINT_PTR *pData);

// Implementation
protected:
// Generated message map functions
	void AdjustSheetButtons();
	BOOL GetDisableNextPage();
	HRESULT PrepareResult();

	HRESULT FillDatasources();
	bool InitDatasourceCtrl();
	void FitColumn (int iCol = 0);

private:
	DWORD m_dwFlags;
	CComBSTR m_bstrDataSource;
	CListViewCtrl m_lvDatasources;
	CImageList m_ilProjects;

	CCopyObjects *m_pParent;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_COPYOBJECTSDLG_H__6F48C5D9_360E_4CD9_B991_603E7E007A84__INCLUDED_)
