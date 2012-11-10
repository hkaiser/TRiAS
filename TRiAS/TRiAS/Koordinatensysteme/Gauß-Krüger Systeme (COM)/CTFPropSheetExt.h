///////////////////////////////////////////////////////////////////////////
// @doc 
// @module CTFPropSheetExt.h | Deklaration für CCTFPropSheetExt<>

#if !defined(_CTFPROPSHEETEXT_H__D5FB8133_DF7F_11D1_8607_00600875138A__INCLUDED_)
#define _CTFPROPSHEETEXT_H__D5FB8133_DF7F_11D1_8607_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <ixtnext.hxx>

///////////////////////////////////////////////////////////////////////////
// Template zum Einhängen von PropertyPages

template <class T, class Dlg>
class CCTFPropSheetExt : 
	public ITriasPropSheetExt
{
protected:
	Dlg *m_pDlg;
	void DestroyDlg(void) 
	{
		if (m_pDlg) {
			m_pDlg -> SetTargetCTF (NULL);
			delete m_pDlg;
			m_pDlg = NULL; 
		}
	}

public:
// Konstruktor
	CCTFPropSheetExt() { m_pDlg = NULL; }
	~CCTFPropSheetExt() { DestroyDlg(); }

////////////////////////////////////////////////////////////////////////////
// ITriasPropSheetExt
	STDMETHOD(AddPages)(LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam)
	{
		AFX_MANAGE_STATE(AfxGetAppModuleState())	// HK990128

	HPROPSHEETPAGE hPSP = NULL;

		COM_TRY {
			DestroyDlg();				// für alle Fälle

			ATLTRY(m_pDlg = new Dlg);		// Page neu anlegen
			if (NULL == m_pDlg) 
				_com_issue_error(E_UNEXPECTED);

		// die Page für das jeweilige CoordSystem Parametrisieren
			m_pDlg -> SetTargetCTF((CCoordTrans *) ((T *)this) -> m_pOwner);

		// Page kreieren
			hPSP = CreatePropertySheetPage ((PROPSHEETPAGE *)&m_pDlg->m_psp); 
			if (NULL == hPSP) _com_issue_error(E_HANDLE);	
		
		// Page hinzufügen
			if (!(*lpfnAddPage) (hPSP, lParam)) 
				_com_issue_error(E_FAIL);
		
		} COM_CATCH_OP(	
			DestroyDlg();
			if (hPSP) DestroyPropertySheetPage(hPSP);
		);
		return S_OK;
	};

	STDMETHOD(ReplacePage)(UINT uPageID, LPFNADDPROPSHEETPAGE lpfnReplacePage, LPARAM lParam)
	{
		AFX_MANAGE_STATE(AfxGetAppModuleState())	// HK990128
		ATLTRACENOTIMPL("CCTFPropSheetExt<T>::ReplacePage");
	}
};

#endif // !defined(_CTFPROPSHEETEXT_H__D5FB8133_DF7F_11D1_8607_00600875138A__INCLUDED_)
