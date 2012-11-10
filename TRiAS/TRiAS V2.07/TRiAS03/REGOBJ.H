// RegObj.h : Declaration of the CRegObject

#include "trias03.h"       // main symbols

#define INITGUID
#include <olectl.h>

/////////////////////////////////////////////////////////////////////////////
// register

#if defined(__ATL_20_USED__)
#include "static\\statreg.h"

EXTERN_C const IID IID_ITRiASRegistryHelper;
EXTERN_C const CLSID CLSID_TRiASRegistryHelper;
#endif 

class CTRiASRegObject : public CRegObject,
	public CComDualImpl<ITRiASRegistryHelper, &IID_ITRiASRegistryHelper, &LIBID_TRiASHelperLib,
			TYPELIB_HELPER_VERSION_MAJOR, TYPELIB_HELPER_VERSION_MINOR>,
	public ISupportErrorInfo,
	public CComObjectRoot,
	public CComCoClass<CTRiASRegObject, &CLSID_TRiASRegistryHelper>
{
public:
	CTRiASRegObject() {}
	~CTRiASRegObject(){ClearReplacements();}

BEGIN_COM_MAP(CTRiASRegObject)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ITRiASRegistryHelper)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

DECLARE_NOT_AGGREGATABLE(CTRiASRegObject)

DECLARE_STATIC_REGISTRY_RESOURCEID(IDR_REGISTRYHELPER);

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ITRiASRegistryHelper
public:
	STDMETHOD(AddReplacement)(BSTR key, BSTR item);
	STDMETHOD(ClearReplacements)();
	STDMETHOD(ResourceRegister)(BSTR resFileName, VARIANT ID, VARIANT type);
	STDMETHOD(ResourceUnregister)(BSTR resFileName, VARIANT ID, VARIANT type);
	STDMETHOD(FileRegister)(BSTR fileName);
	STDMETHOD(FileUnregister)(BSTR fileName);
	STDMETHOD(StringRegister)(BSTR data);
	STDMETHOD(StringUnregister)(BSTR data);
	STDMETHOD(AddKey)(BSTR keyName);
	STDMETHOD(DeleteKey)(BSTR keyName);
	STDMETHOD(AddKeyValue)(BSTR keyName, BSTR valueName, VARIANT value);
	STDMETHOD(GetKeyValue)(BSTR keyName, BSTR valueName, VARIANT* value);
	STDMETHOD(SetKeyValue)(BSTR keyName, BSTR valueName, VARIANT value);

protected:

	void ReportToIError(CRegException& re);
};
