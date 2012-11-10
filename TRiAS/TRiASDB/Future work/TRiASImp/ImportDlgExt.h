///////////////////////////////////////////////////////////////////////////
// @doc 
// @module ImportDlgExt.h | Description goes here

#if !defined(_IMPORTDLGEXT_H__3F5197F3_A3D3_11D1_A054_0060975566B4__INCLUDED_)
#define _IMPORTDLGEXT_H__3F5197F3_A3D3_11D1_A054_0060975566B4__INCLUDED_

//#if _MSC_VER >= 1000
//#pragma once
//#endif // _MSC_VER >= 1000

#include "resource.h"       // main symbols
#include "Strings.h"
#include "PropSheetExt.h"
#include "DlgImportOpt.h"

/////////////////////////////////////////////////////////////////////////////
// CImportDlgExt
class ATL_NO_VTABLE CImportDlgExt : 
	public CTRiASPropSheetExt<CDlgImportOpt>,
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CImportDlgExt, &CLSID_ImportDlgExt>,
	public IDispatchImpl<IGetImportExtension, &IID_IGetImportExtension, &LIBID_TRiASDB>
{
public:
	CImportDlgExt()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_IMPORTDLGEXT)

BEGIN_COM_MAP(CImportDlgExt)
	COM_INTERFACE_ENTRY(IGetImportExtension)
	COM_INTERFACE_ENTRY2(IUnknown, ITRiASOpenWizardPropExt)
	COM_INTERFACE_ENTRY_CHAIN(CTRiASPropSheetExt<CDlgImportOpt>)
END_COM_MAP()

// IGetImportExtension
public:
	STDMETHOD(get_GetImportExt)(IUnknown**pImpExt)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState())

		try {
			if (NULL == m_pDlg) _com_issue_error(E_OUTOFMEMORY);

			THROW_FAILED_HRESULT(m_pDlg -> GetImportExt(pImpExt));

		} catch (_com_error &e) {

			return _COM_ERROR(e);
		}
		return S_OK;
	}
};

#endif // !defined(_IMPORTDLGEXT_H__3F5197F3_A3D3_11D1_A054_0060975566B4__INCLUDED_)
