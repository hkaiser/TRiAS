// RegisterEbs.h : Declaration of the CRegisterEbs

#ifndef __REGISTEREBS_H_
#define __REGISTEREBS_H_

#include <TRiASHelper.h>

/////////////////////////////////////////////////////////////////////////////
// CRegisterEbs
class /*ATL_NO_VTABLE*/ CRegisterEbs : 
	public CComObjectRoot,
	public CComCoClass<CRegisterEbs, &CLSID_RegisterEbs>,
	public IRegisterTRiASExtension
{
public:
	CRegisterEbs()
	{
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_REGISTEREBS)

	BEGIN_COM_MAP(CRegisterEbs)
		COM_INTERFACE_ENTRY(IRegisterTRiASExtension)
	END_COM_MAP()

// IRegisterTRiASExtension
public:
	STDMETHOD(RegisterTRiASExtension)(/*[in]*/BSTR bstrTarget, /*[in, out]*/BSTR *pbstrName, /*[in, out]*/BSTR *pbstrID, /*[in, out]*/EXTENSIONFLAGS *prgFlags);
	STDMETHOD(RegisterProjectExtension)(/*[in]*/long hPr, /*[in]*/BSTR bstrName, /*[in]*/BSTR bstrID, /*[in]*/BSTR bstrTarget);
	STDMETHOD(UnRegisterTRiASExtension)(/*[in]*/ BSTR bstrName, /*[in]*/BSTR bstrID, /*[in]*/long hPr);

protected:
	HRESULT GetActiveProjectIni (long hPr, os_path &path);
};

#endif //__REGISTEREBS_H_
