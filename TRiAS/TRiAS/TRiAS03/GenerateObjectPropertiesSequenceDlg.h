// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 11.10.2000 17:38:25
//
// @doc
// @module CGenerateObjectPropertiesSequenceDlg.h | Declaration of the <c CCGenerateObjectPropertiesSequenceDlg> class

#if !defined(_CGENERATEOBJECTPROPERTIESSEQUENCEDLG_H__6B9FAEB2_AE46_46C5_8EC5_2CC2368B6409__INCLUDED_)
#define _CGENERATEOBJECTPROPERTIESSEQUENCEDLG_H__6B9FAEB2_AE46_46C5_8EC5_2CC2368B6409__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <Bmpbtn.hxx>

#include "TRiAS03.h"       // main symbols
#include "SelObjpropList.h"

/////////////////////////////////////////////////////////////////////////////
// CCGenerateObjectPropertiesSequenceDlg dialog
class CGenerateObjectProperties;

class CGenerateObjectPropertiesSequenceDlg : 
	public CPropertyPage
{
// Construction
public:
	CGenerateObjectPropertiesSequenceDlg(CGenerateObjectProperties *pParent, ResID uiResID, LPCSTR pcCaption);
	~CGenerateObjectPropertiesSequenceDlg();

	BOOL FInit (void);
	HRESULT PrepareResult (void);
	HPROPSHEETPAGE CreatePage (void) { return CPropertyPage::CreatePage(); }

// Dialog Data
	enum { IDD = IDD_GENERATEOBJECTPROPERTIES_SEQUENCE };

// Overrides
	void WindowInit (Event e);
	int OnSetActive (NotifyEvt e);
	int OnWizNext (NotifyEvt e);
	int OnWizFinish (NotifyEvt e);

	void ButtonClick (ControlEvt e);

public:
	void SetFlags (DWORD dwFlags) { m_dwFlags = dwFlags; }
	static CGenerateObjectPropertiesSequenceDlg *CreateInstance (CGenerateObjectProperties *pParent, LPCSTR pcCaption);

	list<os_string> GetObjProps() { return m_lstObjProps; }

// Implementation
protected:
	void AdjustSheetButtons();
	BOOL GetDisableNextPage();

	bool FillListWithProps();

private:
	DWORD m_dwFlags;
	CGenerateObjectProperties *m_pParent;
	list<os_string> m_lstObjProps;
	
	CSelObjPropList m_lstProps;
	CBmpButton m_pbUp;
	CBmpButton m_pbDown;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_CGENERATEOBJECTPROPERTIESSEQUENCEDLG_H__6B9FAEB2_AE46_46C5_8EC5_2CC2368B6409__INCLUDED_)
