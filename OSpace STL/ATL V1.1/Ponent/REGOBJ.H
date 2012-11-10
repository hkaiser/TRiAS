// RegObj.h : Declaration of the CRegObject

#include "resource.h"       // main symbols

#define INITGUID
#include <olectlid.h>

/////////////////////////////////////////////////////////////////////////////
// register

//REVIEW -- using pointers to ID's is necessary because some compilers don't like
//references as template arguments.

class CDLLRegObject : public CRegObject,
	public CComDualImpl<IRegistrar, &IID_IRegistrar, &LIBID_REGISTERLib>,
	public ISupportErrorInfo,
	public CComObjectRoot,
	public CComCoClass<CDLLRegObject, &CLSID_Registrar>

{
public:
	CDLLRegObject() {}
	~CDLLRegObject(){ClearReplacements();}

BEGIN_COM_MAP(CDLLRegObject)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IRegistrar)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

DECLARE_NOT_AGGREGATABLE(CDLLRegObject)

//static HRESULT WINAPI UpdateRegistry(BOOL bRegister);
DECLARE_STATIC_REGISTRY_RESOURCEID(IDR_REGISTRAR);
// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IRegistrar
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
