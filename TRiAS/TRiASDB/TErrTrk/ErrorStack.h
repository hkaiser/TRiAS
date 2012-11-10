// ErrorStack.h : Declaration of the CErrorStack

#ifndef __ERRORSTACK_H_
#define __ERRORSTACK_H_

/////////////////////////////////////////////////////////////////////////////
// CErrorStack
class ATL_NO_VTABLE CErrorStack : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CErrorStack, &CLSID_ErrorStack>,
	public IDispatchImpl<IErrorStack, &IID_IErrorStack, &LIBID_TERRTRKLib>
{
	WEnumWErrorItem	m_Enum;
public:
	CErrorStack() {
	}
	HRESULT	FinalConstruct();
	HRESULT	FinalRelease();

	DECLARE_REGISTRY_RESOURCEID(IDR_ERRORSTACK)
	DECLARE_NOT_AGGREGATABLE(CErrorStack)
	DECLARE_CLASSFACTORY_SINGLETON(CErrorStack)

	BEGIN_COM_MAP(CErrorStack)
		COM_INTERFACE_ENTRY(IErrorStack)
		COM_INTERFACE_ENTRY(IDispatch)
	END_COM_MAP()

// IErrorStack
public:
	STDMETHOD(_newEnum)(/*[out,retval]*/ IUnknown **ppIEnum);
	STDMETHOD(Clear)();
	STDMETHOD(get_Count)(ULONG* pItems);
	STDMETHOD(Push)(IUnknown *pIError);
};

#endif //__ERRORSTACK_H_
