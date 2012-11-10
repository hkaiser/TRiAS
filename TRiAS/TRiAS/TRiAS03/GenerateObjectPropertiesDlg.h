// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 11.10.2000 17:38:25
//
// @doc
// @module GenerateObjectPropertiesDlg.h | Declaration of the <c CGenerateObjectPropertiesDlg> class

#if !defined(_GENERATEOBJECTPROPERTIESDLG_H__6B9FAEB2_AE46_46C5_8EC5_2CC2368B6409__INCLUDED_)
#define _GENERATEOBJECTPROPERTIESDLG_H__6B9FAEB2_AE46_46C5_8EC5_2CC2368B6409__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <ospace/std/list>
#include <SelObjProp.h>

#include "TRiAS03.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CGenerateObjectPropertiesDlg dialog
class CGenerateObjectProperties;

class CGenerateObjectPropertiesSelectDlg : 
	public CPropertyPage
{
// Construction
public:
	CGenerateObjectPropertiesSelectDlg(CGenerateObjectProperties *pParent, ResID uiResID, LPCSTR pcCaption);
	~CGenerateObjectPropertiesSelectDlg();

	BOOL FInit (void);
	HRESULT PrepareResult (void);
	HPROPSHEETPAGE CreatePage (void) { return CPropertyPage::CreatePage(); }

// Dialog Data
	enum { IDD = IDD_GENERATEOBJECTPROPERTIES_SELECTPROPS };

// Overrides
	void WindowInit (Event e);
	int OnSetActive (NotifyEvt e);
	int OnWizNext (NotifyEvt e);
	int OnWizFinish (NotifyEvt e);
	LRESULT Dispatch (Event e);
	void OnSelChanged (NotifyEvt e);

	void OnItemExpanded (NotifyEvt e);

	BOOL OnNotify (NotifyEvt e);
	void ButtonClick (ControlEvt e);

public:
	void SetFlags (DWORD dwFlags) { m_dwFlags = dwFlags; }
	static CGenerateObjectPropertiesSelectDlg *CreateInstance (CGenerateObjectProperties *pParent, LPCSTR pcCaption);

	void SetInitialObjProps (list<os_string> &rLstStrs) { m_lstObjProps = rLstStrs; }
	const list<os_string> & GetSelectedObjProps() const { return m_lstObjProps; }

	IObjectProps *GetObjectProps() { return m_pObjProps -> GetObjectProps(); }

	bool ChangedPropList() { return m_fChangedPropList; }

// Implementation
protected:
	void AdjustSheetButtons();
	BOOL GetDisableNextPage();

	HRESULT GetObjectProperty (IObjectProperty **ppIObjProp);

private:
	DWORD m_dwFlags;
	CGenerateObjectProperties *m_pParent;
	list<os_string> m_lstObjProps;

// Controls
	CSelObjPropTree *m_pObjProps;
	FixedText m_ftDesc;
	PushButton m_pbConfig;

	bool m_fChangedPropList;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_GENERATEOBJECTPROPERTIESDLG_H__6B9FAEB2_AE46_46C5_8EC5_2CC2368B6409__INCLUDED_)
