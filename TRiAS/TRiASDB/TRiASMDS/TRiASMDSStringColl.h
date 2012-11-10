// TRiASMDSStringColl.h : Declaration of the CTRiASMDSStringColl

#ifndef __TRIASMDSSTRINGCOLL_H_
#define __TRIASMDSSTRINGCOLL_H_

/////////////////////////////////////////////////////////////////////////////
// CTRiASMDSStringColl

class ATL_NO_VTABLE CTRiASMDSStringColl : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CTRiASMDSStringColl, &CLSID_TRiASMDSStringColl>,
	public CErrSupport<CTRiASMDSStringColl, &IID_ITRiASMDSStringColl>,
	public IDispatchImpl<ITRiASMDSStringColl, &IID_ITRiASMDSStringColl, TLB_TRiASMDS_SIGNAT>
{
private:
	WEnumBSTR m_enumOfStrings;

public:
	CTRiASMDSStringColl()
	{
	}

	HRESULT FinalConstruct();
	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASMDSSTRINGCOLL)

	BEGIN_COM_MAP(CTRiASMDSStringColl)
		COM_INTERFACE_ENTRY(ITRiASMDSStringColl)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

// ITRiASMDSStringColl
public:
	STDMETHOD(Add)(BSTR strNewVal);
	STDMETHOD(_NewEnum)(/*[out,retval]*/ IUnknown** pStrings);
};

#endif //__TRIASMDSSTRINGCOLL_H_
