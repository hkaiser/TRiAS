// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 09.12.2002 09:17:10 
//
// @doc
// @module LoadObjectCollectionDlg.h | Declaration of the <c CLoadObjectCollectionDlg> class

#if !defined(_LOADOBJECTCOLLECTIONDLG_H__CB7BC44A_780F_4E2B_BCB4_C34A648DF207__INCLUDED_)
#define _LOADOBJECTCOLLECTIONDLG_H__CB7BC44A_780F_4E2B_BCB4_C34A648DF207__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "trias03.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CLoadObjectCollectionDlg dialog

class CLoadObjectCollectionDlg : 
	public CPropertyPage
{
// Construction
public:
	CLoadObjectCollectionDlg(ResID uiResID, LPCSTR pcCaption);
	~CLoadObjectCollectionDlg();

// Dialog Data
	enum { IDD = IDD_LOADOBJECTCOLLECTION_OPTIONS };

// Overrides
public:
	BOOL OnSetActive();

	HPROPSHEETPAGE CreatePage() { return CPropertyPage::CreatePage(); }

public:
	void SetFlags (DWORD dwFlags) { m_dwFlags = dwFlags; }
	static CLoadObjectCollectionDlg *CreateInstance (LPCSTR pcCaption);

// Implementation
protected:
	void AdjustSheetButtons();
	BOOL GetDisableNextPage();

	BOOL FInit();

private:
	DWORD m_dwFlags;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_LOADOBJECTCOLLECTIONDLG_H__CB7BC44A_780F_4E2B_BCB4_C34A648DF207__INCLUDED_)
