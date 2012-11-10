// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 09.12.2002 09:16:47 
//
// @doc
// @module SaveObjectCollectionDlg.h | Declaration of the <c CSaveObjectCollectionDlg> class

#if !defined(_SAVEOBJECTCOLLECTIONDLG_H__7DFAFEEA_DAAD_4F9A_ABA7_FB8ECCA4EE54__INCLUDED_)
#define _SAVEOBJECTCOLLECTIONDLG_H__7DFAFEEA_DAAD_4F9A_ABA7_FB8ECCA4EE54__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "trias03.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSaveObjectCollectionDlg dialog

typedef struct tagSAVEOBJCOLLDATA {
	bool m_fSaveInProject;
	os_string m_strSaveAs;
} SAVEOBJCOLLDATA;

inline
void TidySaveData(SAVEOBJCOLLDATA &rData) 
{
	rData.m_fSaveInProject = false;
	rData.m_strSaveAs.empty();
}

class CSaveObjectCollectionDlg : 
	public CPropertyPage
{
// Construction
public:
	CSaveObjectCollectionDlg(ResID uiResID, LPCSTR pcCaption);
	~CSaveObjectCollectionDlg();

// Dialog Data
	enum { IDD = IDD_SAVEOBJECTCOLLECTION_OPTIONS };

// Overrides
public:
	BOOL OnSetActive();

	HPROPSHEETPAGE CreatePage() { return CPropertyPage::CreatePage(); }

public:
	void SetFlags (DWORD dwFlags) { m_dwFlags = dwFlags; }
	SAVEOBJCOLLDATA GetData () { return m_CfgData; }
	void SetData(SAVEOBJCOLLDATA const &rData) { m_CfgData = rData; }

	static CSaveObjectCollectionDlg *CreateInstance (LPCSTR pcCaption);

// Implementation
protected:
	void AdjustSheetButtons();
	BOOL GetDisableNextPage();
	BOOL PrepareResult();

	BOOL FInit();

private:
	DWORD m_dwFlags;
	SAVEOBJCOLLDATA m_CfgData;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_SAVEOBJECTCOLLECTIONDLG_H__7DFAFEEA_DAAD_4F9A_ABA7_FB8ECCA4EE54__INCLUDED_)
