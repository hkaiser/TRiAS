// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 14.09.2000 08:52:33
//
// @doc
// @module DeleteObjectPropertyDlg.h | Declaration of the <c CDeleteObjectPropertyDlg> class

#if !defined(_DELETEOBJECTPROPERTYDLG_H__B9F627AB_EB0F_40EC_96B6_C696D079FBE6__INCLUDED_)
#define _DELETEOBJECTPROPERTYDLG_H__B9F627AB_EB0F_40EC_96B6_C696D079FBE6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <SelObjProp.h>

#include "TRiAS03.h"       // main symbols
#include "Strings.h"

/////////////////////////////////////////////////////////////////////////////
// CDeleteObjectPropertyDlg dialog

class CDeleteObjectPropertyDlg : 
	public CPropertyPage
{
// Construction
public:
	CDeleteObjectPropertyDlg(ResID resID, LPCSTR pcCaption);
	~CDeleteObjectPropertyDlg();

// Dialog Data
	enum { IDD = IDD_DELETEOBJECTPROPERTY_OPTIONS };

// Overrides
public:
	void WindowInit (Event);

	int OnSetActive (NotifyEvt);
	void OnCancel (NotifyEvt);
	int OnWizNext (NotifyEvt);
	BOOL OnWizFinish (NotifyEvt);
	void OnSelChanged (NotifyEvt);
	void OnItemExpanded (NotifyEvt);

	BOOL FInit();

public:
	void SetFlags (DWORD dwFlags) { m_dwFlags = dwFlags; }

	void SetInitialObjProps (list<os_string> &rLstStrs) { m_lstObjProps = rLstStrs; }
	const list<os_string> & GetSelectedObjProps() const { return m_lstObjProps; }
	IObjectProps *GetObjectProps() { return m_pObjProps -> GetObjectProps(); }

	static CDeleteObjectPropertyDlg *CreateInstance (ResID resID, LPCSTR pcCaption);

	HPROPSHEETPAGE CreatePage (void) { return CPropertyPage::CreatePage(); }

// Implementation
protected:
	BOOL AdjustSheetButtons();
	BOOL GetDisableNextPage();
	HRESULT DoUpdate();

	HRESULT GetObjectProperty (IObjectProperty **ppIObjProp);

private:
	DWORD m_dwFlags;
	CSelObjPropTree *m_pObjProps;
	list<os_string> m_lstObjProps;
	FixedText m_ftDesc;
};

// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_DELETEOBJECTPROPERTYDLG_H__B9F627AB_EB0F_40EC_96B6_C696D079FBE6__INCLUDED_)
