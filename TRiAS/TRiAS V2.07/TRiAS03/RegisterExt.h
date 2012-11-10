// RegisterExt.h : Declaration of the CRegisterExt

#ifndef __REGISTEREXT_H_
#define __REGISTEREXT_H_

#include "trias03.h"       // main symbols

#include <ospace/file/path.h>

EXTERN_C const CLSID CLSID_RegisterExt;
EXTERN_C const CLSID IID_IRegisterTRiASExtension;

#if !defined(__ATL_20_USED__)
#define ATL_NO_VTABLE 
#endif // __ATL_20_USED__

/////////////////////////////////////////////////////////////////////////////
// CRegisterExt
class ATL_NO_VTABLE CRegisterExt : 
	public CComObjectRoot,
	public CComCoClass<CRegisterExt, &CLSID_RegisterExt>,
	public IRegisterTRiASExtension
{
public:
	CRegisterExt()
	{
	}

	DECLARE_STATIC_REGISTRY_RESOURCEID(IDR_REGISTEREXT_RGS)

	BEGIN_COM_MAP(CRegisterExt)
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

bool FindExtNameFromDLLName (/*[in]*/string strDLLPath, 
	/*[out]*/string &rStrExtName, /*[out]*/string &rStrProgID);
bool CompareDLLName (/*[in]*/string strProgID, /*[in]*/string strDLLPath, 
	/*[out]*/string &rStrLongName);
bool ServerFromProgID (/*[in]*/LPCSTR pcProgID, /*[in, out]*/string &rStr);

#endif //__REGISTEREXT_H_
