// TRiASMDSKey.h: Definition of the CTRiASMDSKey class
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRIASMDSKEY_H__0F4DBAD6_B5D2_11D2_98E3_0060085FC1CE__INCLUDED_)
#define AFX_TRIASMDSKEY_H__0F4DBAD6_B5D2_11D2_98E3_0060085FC1CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTRiASMDSKey

class CTRiASMDSKey : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CTRiASMDSKey, &CLSID_TRiASMDSKey>,
	public CErrSupport<CTRiASMDSKey, &IID_ITRiASMDSKey>,
	public IDispatchImpl<ITRiASMDSKey, &IID_ITRiASMDSKey, TLB_TRiASMDS_SIGNAT>,
	public os_regexp
{
private:
	os_regexp	m_rexOKS_0;
	os_regexp	m_rexOKS_1;
	os_regexp	m_rexOKS_2;
	os_regexp	m_rexOKS_3;

public:
	CTRiASMDSKey();

	DECLARE_NOT_AGGREGATABLE(CTRiASMDSKey) 
	DECLARE_REGISTRY_RESOURCEID(IDR_TRiASMDSKey)

	BEGIN_COM_MAP(CTRiASMDSKey)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ITRiASMDSKey)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

// ITRiASMDSKey
public:
	STDMETHOD(FormatOKS)(
		/*[in]*/ VARIANT vOKS,
		/*[in,optional,defaultvalue(NULL)]*/ BSTR strShortname,
		/*[out,retval]*/ BSTR* strFormattedOKS
	);
	STDMETHOD(SplitOKS)(
		/*[in]*/ BSTR strPossibleOKS,
		/*[in,optional,defaultvalue(NULL)]*/ BSTR* pbstrAppendix,
		/*[out,retval]*/ BSTR* strOKS
	);
};

#endif // !defined(AFX_TRIASMDSKEY_H__0F4DBAD6_B5D2_11D2_98E3_0060085FC1CE__INCLUDED_)
