// $Header: $
// Copyright© 1999-2003 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 07.02.2003 11:34:29 
//
// @doc
// @module TRiASOptionsPropPage.h | Declaration of the <c COptionsPropPage> class

#if !defined(_TRIASOPTIONSPROPPAGE_H__1EB7DED5_16FF_4D1B_AE45_F23C20B8B468__INCLUDED_)
#define _TRIASOPTIONSPROPPAGE_H__1EB7DED5_16FF_4D1B_AE45_F23C20B8B468__INCLUDED_

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
class COptionsPropPage : 
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
	COptionsPropPage() : m_pDlg(NULL) {}
	~COptionsPropPage() { DestroyDlg(); }        

////////////////////////////////////////////////////////////////////////////
// ITriasPropSheetExt
	STDMETHOD(AddPages)(LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam)
	{
	HPROPSHEETPAGE hPSP = NULL;

		try {
			if (NULL == m_pDlg) 
				_com_issue_error(E_UNEXPECTED);
		
		// Page erzeugen
			hPSP = m_pDlg->CreatePage(); 
			if (NULL == hPSP) _com_issue_error(E_HANDLE);	
		
		// Page hinzufügen
			if (!(*lpfnAddPage) (hPSP, lParam)) 
				_com_issue_error(E_FAIL);
		
		} catch (_com_error &e) {
			DestroyDlg(); 
			if (hPSP) 
				DestroyPropertySheetPage(hPSP);
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
		if (!DEX_TestActiveProject()) 
			return E_UNEXPECTED;
		DestroyDlg();

	extern char g_pDLLName[_MAX_PATH];
	ResourceFile RF (g_pDLLName);

		ATLTRY(m_pDlg = new T(RF));		// Page neu anlegen		
		if (NULL == m_pDlg)
			return E_OUTOFMEMORY;
		return S_OK;
	}
};

#endif // !defined(_TRIASOPTIONSPROPPAGE_H__1EB7DED5_16FF_4D1B_AE45_F23C20B8B468__INCLUDED_)
