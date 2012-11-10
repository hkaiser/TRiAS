///////////////////////////////////////////////////////////////////////////
// @doc 
// @module CTFExContext.h | Declaration of the CCTFExContext

#if !defined(_CTFEXCONTEXT_H__95F58F35_DF2C_11D1_8606_00600875138A__INCLUDED_)
#define _CTFEXCONTEXT_H__95F58F35_DF2C_11D1_8606_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCTFExContext
class ATL_NO_VTABLE CCTFExContext : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CCTFExContext, &CLSID_CTFExContext>,
	public ISupportErrorInfo,
	public IDispatchImpl<ICTFExContext, &IID_ICTFExContext, &LIBID_GEODCTFLib>
{
public:
	typedef CComCoClass<CCTFExContext, &CLSID_CTFExContext> base_t;

	CCTFExContext()
	{
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_CTFEXCONTEXT)

	BEGIN_COM_MAP(CCTFExContext)
		COM_INTERFACE_ENTRY(ICTFExContext)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ErrorHandling
	HRESULT Error (LPCTSTR pcText, HRESULT hr = DISP_E_EXCEPTION, REFIID riid = IID_ICTFExContext)
		{ return base_t::Error (pcText, riid, hr); }

// ICTFExContext
public:
	STDMETHOD(get_Meridian)(/*[out, retval]*/ int *pVal);
	STDMETHOD(put_Meridian)(/*[in]*/ int newVal);
	STDMETHOD(get_Description)(/*[out, retval]*/ BSTR *pVal);

protected:
	int m_iMeridian;
};

#endif // !defined(_CTFEXCONTEXT_H__95F58F35_DF2C_11D1_8606_00600875138A__INCLUDED_)
