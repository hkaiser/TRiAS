//////////////////////////////////////////////////////////////////////
// @doc
// @module ManageParamDlg.h | Definition of the CManageParamDlg class

#if !defined(_MANAGEPARAMDLG_H__95F58F38_DF2C_11D1_8606_00600875138A__INCLUDED_)
#define _MANAGEPARAMDLG_H__95F58F38_DF2C_11D1_8606_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <ixtnext.hxx>
#include "default.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TriasPropSheetExt);		// WTriasPropSheetExt

/////////////////////////////////////////////////////////////////////////////
// CManageParamDlg

class CManageParamDlg : 
	public ITriasPropSheetExt, 
	public ITriasExtInit,
	public IObjectWithSiteImpl<CManageParamDlg>,
	public CComObjectRoot,
	public CComCoClass<CManageParamDlg, &CLSID_ManageCoordParam>
{
public:
	CManageParamDlg() 
	{
	}

	BEGIN_COM_MAP(CManageParamDlg)
		COM_INTERFACE_ENTRY_IMPL(IObjectWithSite)
		COM_INTERFACE_ENTRY_EX(ITriasPropSheetExt)
		COM_INTERFACE_ENTRY_EX(ITriasExtInit)
	END_COM_MAP()
	DECLARE_NOT_AGGREGATABLE(CManageParamDlg) 

	DECLARE_REGISTRY_RESOURCEID(IDR_MANAGECOORDPARAM)

// ITriasPropSheetExt
public:
	STDMETHOD(AddPages)(THIS_ LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam);
	STDMETHOD(ReplacePage)(THIS_ UINT uPageID, LPFNADDPROPSHEETPAGE lpfnReplacePage, LPARAM lParam);

/////////////////////////////////////////////////////////////////////////////
// ITriasExtInit methods 
	STDMETHOD(Initialize)(THIS_ LPCITEMIDLIST pidl, LPDATAOBJECT lpdobj, HKEY hkeyProgID);

protected:
	HRESULT EnsureConnectedCTF();

private:
	WTriasPropSheetExt m_PSE;
};

#endif // !defined(_MANAGEPARAMDLG_H__95F58F38_DF2C_11D1_8606_00600875138A__INCLUDED_)
