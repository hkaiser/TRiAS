// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 22.12.2000 16:48:00 
//
// @doc
// @module PropPageExt.h | Declaration of the <c CPropPageExt> class

#if !defined(_PROPPAGEEXT_H__2DCB0D35_154C_438F_BE46_124772B17170__INCLUDED_)
#define _PROPPAGEEXT_H__2DCB0D35_154C_438F_BE46_124772B17170__INCLUDED_

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
template <class T>
class CPropPageExt : 
	public ITriasPropSheetExt,
	public ITriasExtInit
{
protected:
	T *m_pDlg;
	void DestroyDlg(void) 
	{
		if (m_pDlg) { delete m_pDlg; m_pDlg = NULL; }
	}

public:
	CPropPageExt() : m_pDlg(NULL) {}
	~CPropPageExt() { DestroyDlg(); }        

////////////////////////////////////////////////////////////////////////////
// ITriasPropSheetExt
	STDMETHOD(AddPages)(LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam)
	{
	HPROPSHEETPAGE hPSP = NULL;

//		AFX_MANAGE_STATE(AfxGetAppModuleState()); 		
		try {
			if (NULL == m_pDlg) _com_issue_error(E_UNEXPECTED);
		
		// Page erzeugen
			hPSP = CreatePropertySheetPage ((PROPSHEETPAGE *)&m_pDlg->m_psp); 
			if (NULL == hPSP) _com_issue_error(E_HANDLE);	
		
		// Page hinzufügen
			if (!(*lpfnAddPage) (hPSP, lParam)) 
				_com_issue_error(E_FAIL);
		
		} catch (_com_error &e) {
			DestroyDlg(); 
			if (hPSP) DestroyPropertySheetPage(hPSP);
			return _COM_ERROR(e);
		}
		return S_OK;
	}
	STDMETHOD(ReplacePage)(UINT uPageID, LPFNADDPROPSHEETPAGE lpfnReplacePage, LPARAM lParam)
	{
		return E_NOTIMPL;
	}

////////////////////////////////////////////////////////////////////////////
// ITriasExtInit
	STDMETHOD(Initialize)(LPCITEMIDLIST pidlFolder, LPDATAOBJECT lpdobj, HKEY hkeyProgID)
	{
//		AFX_MANAGE_STATE(AfxGetAppModuleState()); 

		if (!g_pTE -> isLoaded() || !DEX_TestActiveProject()) 
			return E_UNEXPECTED;
		DestroyDlg();

		ATLTRY(m_pDlg = new T);		// Page neu anlegen		
		if (NULL == m_pDlg)
			return E_OUTOFMEMORY;
		return S_OK;
	}
};

#endif // !defined(_PROPPAGEEXT_H__2DCB0D35_154C_438F_BE46_124772B17170__INCLUDED_)
