// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 11.10.2002 21:24:52 
//
// @doc
// @module PropSheetExt2.h | Declaration of the <c CPropSheetExt> class

#if !defined(_PROPSHEETEXT2_H__6F448F87_974A_479E_BC1B_85AAAB9F57BE__INCLUDED_)
#define _PROPSHEETEXT2_H__6F448F87_974A_479E_BC1B_85AAAB9F57BE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <shlobj.h>
#include <ixtnext.hxx>

///////////////////////////////////////////////////////////////////////////
// Template zum Einhängen von PropertyPages

template <typename DlgT1, typename DlgT2>
class CTRiASPropSheetExt2 : 
	public ITriasPropSheetExt,
	public ITRiASOpenWizardPropExt
{
protected:
	DlgT1 *m_pDlg1;
	DlgT2 *m_pDlg2;

	void DestroyDlgs(void) 
	{
		if (m_pDlg1) delete m_pDlg1; m_pDlg1 = NULL; 
		if (m_pDlg2) delete m_pDlg2; m_pDlg2 = NULL; 
	}

public:
// Konstruktor
	CTRiASPropSheetExt2() : m_pDlg1(NULL), m_pDlg2(NULL) {}
	~CTRiASPropSheetExt2() { DestroyDlgs(); }

	BEGIN_COM_MAP(CTRiASPropSheetExt2)
		COM_INTERFACE_ENTRY(ITRiASOpenWizardPropExt)
		COM_INTERFACE_ENTRY(ITriasPropSheetExt)
	END_COM_MAP()

////////////////////////////////////////////////////////////////////////////
// ITriasPropSheetExt
	STDMETHOD(AddPages)(LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam)
	{
	HPROPSHEETPAGE hPSP1 = NULL;
	HPROPSHEETPAGE hPSP2 = NULL;

		try {
			if (NULL == m_pDlg1 || NULL == m_pDlg2) 
				_com_issue_error(E_UNEXPECTED);
		
		// Pages kreieren
		PROPSHEETPAGE psp;

			memcpy(&psp, &m_pDlg1->m_psp, sizeof(PROPSHEETPAGE));
			hPSP1 = ::CreatePropertySheetPage (&psp); 
			if (NULL == hPSP1) _com_issue_error(E_HANDLE);	
		
		// Page hinzufügen
			if (!(*lpfnAddPage) (hPSP1, lParam)) 
				_com_issue_error(E_FAIL);
		
			memcpy(&psp, &m_pDlg2->m_psp, sizeof(PROPSHEETPAGE));
			hPSP2 = ::CreatePropertySheetPage (&psp); 
			if (NULL == hPSP2) _com_issue_error(E_HANDLE);	
		
		// Page hinzufügen
			if (!(*lpfnAddPage) (hPSP2, lParam)) 
				_com_issue_error(E_FAIL);
		
		} catch (_com_error &e) {
			DestroyDlgs(); 
			if (hPSP1) ::DestroyPropertySheetPage(hPSP1);
			if (hPSP2) ::DestroyPropertySheetPage(hPSP2);
			return _COM_ERROR(e);
		}
		return S_OK;
	}

	STDMETHOD(ReplacePage)(UINT uPageID, LPFNADDPROPSHEETPAGE lpfnReplacePage, LPARAM lParam)
	{
		ATLTRACENOTIMPL("CTRiASPropSheetExt2<T>::ReplacePage");
	}

////////////////////////////////////////////////////////////////////////////
// ITRiASOpenWizardPropExt
// Die Implementation in diesem Template setzt vorraus, daß der zu instantiierende
// Dialog die folgenden Funktionen implementiert hat:

	STDMETHOD(InitForOpenDialog)(BSTR bstrProgID, BSTR bstrCaption, 
		VARIANT_BOOL fCreate, IComposeStringPairs *pIPairs)
	{
		USES_CONVERSION;

		DestroyDlgs(); 
		COM_TRY {
			m_pDlg1 = new DlgT1(OLE2A(bstrCaption));	// Page 1 neu anlegen
			m_pDlg2 = new DlgT2(OLE2A(bstrCaption));	// Page 2 neu anlegen

			THROW_FAILED_HRESULT(m_pDlg1 -> SetProgID(OLE2A(bstrProgID)));
			THROW_FAILED_HRESULT(m_pDlg1 -> SetPairs(pIPairs));

			THROW_FAILED_HRESULT(m_pDlg2 -> SetProgID(OLE2A(bstrProgID)));
			THROW_FAILED_HRESULT(m_pDlg2 -> SetPairs(pIPairs));

		} COM_CATCH_OP(DestroyDlgs());

	// wenn der Speichermode nicht stimmt, dann normal wieder raus
		if (FAILED(m_pDlg1 -> SetCreateMode(fCreate)) || 
			FAILED(m_pDlg2 -> SetCreateMode(fCreate))) 
		{
			DestroyDlgs();
			return E_FAIL;
		}
		return S_OK;
	}
};

#endif // !defined(_PROPSHEETEXT2_H__6F448F87_974A_479E_BC1B_85AAAB9F57BE__INCLUDED_)
