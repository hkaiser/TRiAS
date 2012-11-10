// @doc
// @module ExtendedDataConversion.h | Declaration of the <c CExtendedDataConversion> class

#ifndef __EXTENDEDDATACONVERSION_H_
#define __EXTENDEDDATACONVERSION_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CExtendedDataConversion
class ATL_NO_VTABLE CExtendedDataConversion : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CExtendedDataConversion, &CLSID_AlkBerlin>,
	public ISupportErrorInfo,
	public IDispatchImpl<IExtendedDataConversion, &IID_IExtendedDataConversion, &LIBID_ALKBERLINLib>
{
public:
	CExtendedDataConversion()
	{
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_EXTENDEDDATACONVERSION)

	BEGIN_COM_MAP(CExtendedDataConversion)
		COM_INTERFACE_ENTRY(IExtendedDataConversion)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

	HRESULT InitConfigData();

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IExtendedDataConversion
public:
	STDMETHOD(put_ConfigFile)(/*[in]*/ BSTR newVal);
	STDMETHOD(PostOutputTrailer)(/*[out, retval]*/ BSTR *pbstrTrailer);
	STDMETHOD(PreOutputTrailer)(/*[in, out]*/ BSTR *pbstrTrailer, /*[out, retval]*/ VARIANT_BOOL *pfOutput);
	STDMETHOD(PostOutputAttribute)(/*[in]*/ LONG lMCode, /*[out, retval]*/ BSTR *pbstrOutput);
	STDMETHOD(PreOutputAttribute)(/*[in, out]*/ LONG *plMCode, /*[in, out]*/ BSTR *pbstrAttribute, /*[out, retval]*/ VARIANT_BOOL *pfOutput);
	STDMETHOD(PostOutputObjectStart)(/*[in]*/ LONG lCnt, /*[out, retval]*/ BSTR *pbstrStart);
	STDMETHOD(PreOutputObjectStart)(/*[in]*/ LONG lCnt, /*[in]*/ SAFEARRAY *psaParams, /*[in, out]*/ BSTR *pbstrStart, /*[out, retval]*/ VARIANT_BOOL *pfOutput);
	STDMETHOD(PostOutputHeader)(/*[out, retval]*/ BSTR *pbstrHeader);
	STDMETHOD(PreOutputHeader)(/*[in]*/ SAFEARRAY *psaParams, /*[in, out]*/ BSTR *pbstrHeader, VARIANT_BOOL *pfOutput);

private:
	class CRulesList :
		public list<os_string>
	{
	public:
		HRESULT InsertRules (LPCSTR pcSection, LPCSTR pcINI);
		HRESULT EvalRules (BSTR *pbstrOut);
	};
	CRulesList m_PostObjectStartRules;
	CRulesList m_PostOutputHeaderRules;

	CComBSTR m_bstrCfg;
};

#endif //__EXTENDEDDATACONVERSION_H_
