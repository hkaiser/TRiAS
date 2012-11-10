///////////////////////////////////////////////////////////////////////////
// StringPairs.h : Declaration of the CStringPairs

#if !defined(_STRINGPAIR_H__C21AAF99_2DE5_11d1_969A_00A024D6F582__INCLUDED_)
#define _STRINGPAIR_H__C21AAF99_2DE5_11d1_969A_00A024D6F582__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <ospace/std/map>

#include "resource.h"       // main symbols

DefineSmartInterface(ParseRegularExpression);	// WParseRegularExpression

/////////////////////////////////////////////////////////////////////////////
// CStringPairs

#if _MSC_VER < 1100
class CComBSTREx :
	public CComBSTR
{
public:
	CComBSTREx * operator &() { return this; }
	CComBSTREx () {}
	CComBSTREx (const CComBSTR &rhs) : CComBSTR(rhs) {}
};
#else
typedef CComBSTR CComBSTREx;
#endif // _MSC_VER < 1100

typedef map<CComBSTR, CComBSTREx, less<CComBSTR> > CStringPairList;
typedef CComEnum<IEnumString, &IID_IEnumString, LPOLESTR, _Copy<LPOLESTR> > CEnumString;

inline bool operator< (const CComBSTR &r1, const CComBSTR &r2) 
{ 
	return wcscmp (r1, r2) < 0; 
}

/////////////////////////////////////////////////////////////////////////////
//
class ATL_NO_VTABLE CStringPairs : 
#if defined(__ATL_20_USED__)
	public CComObjectRootEx<CComObjectThreadModel>,
	public IDispatchImpl<IParseStringPairs2, &IID_IParseStringPairs, &LIBID_TRiASSupport,
		TYPELIB_TRIASSUPPORT_VERSION_MAJOR, TYPELIB_TRIASSUPPORT_VERSION_MINOR>,
	public IDispatchImpl<IComposeStringPairs, &IID_IComposeStringPairs, &LIBID_TRiASSupport,
		TYPELIB_TRIASSUPPORT_VERSION_MAJOR, TYPELIB_TRIASSUPPORT_VERSION_MINOR>,
	public IDispatchImpl<ITRiASPropertyBag, &IID_ITRiASPropertyBag, &LIBID_TRiASSupport,
		TYPELIB_TRIASSUPPORT_VERSION_MAJOR, TYPELIB_TRIASSUPPORT_VERSION_MINOR>,
#else
	public CComObjectRoot,
	public CComDualImpl<IParseStringPairs, &IID_IParseStringPairs, 
			&LIBID_TRiASSupport>,
	public CComDualImpl<IComposeStringPairs, &IID_IComposeStringPairs, 
			&LIBID_TRiASSupport>,
#endif
	public CComCoClass<CStringPairs, &CLSID_ParseStringPairs>,
	public IPropertyBag,
	public ISupportErrorInfo
{
public:
	CStringPairs() :
		m_l1st(-1), m_l2nd(-1), 
		m_fIsParsed(false), m_fHasPattern(false), m_fHasDataSet(false)
	{
	}

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CStringPairs)
	DECLARE_REGISTRY_RESOURCEID(IDR_STRINGPAIR)
	DECLARE_GET_CONTROLLING_UNKNOWN()
	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CStringPairs)
		COM_INTERFACE_ENTRY2(IParseStringPairs, IParseStringPairs2)
		COM_INTERFACE_ENTRY(IParseStringPairs2)
		COM_INTERFACE_ENTRY(IComposeStringPairs)
		COM_INTERFACE_ENTRY(ITRiASPropertyBag)
		COM_INTERFACE_ENTRY(IPropertyBag)
		COM_INTERFACE_ENTRY2(IDispatch, IParseStringPairs)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

	HRESULT FinalConstruct (void);
	void FinalRelease();

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IParseStringPairs
public:
	STDMETHOD(get_Value)(/*[in]*/ BSTR Key, /*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_Pattern)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Pattern)(/*[in]*/ BSTR newVal);

	STDMETHOD(Parse)(/*[in]*/ BSTR ToParse, /*[out, retval]*/ long *plPairs);
	STDMETHOD(GetKeyStrings) (/*[out, retval]*/ IUnknown **Keys);
	STDMETHOD(InitObject) (/*[in]*/ IUnknown *Obj, /*[in, optional]*/ VARIANT ErrorLog);

// IComposeStringPairs
	STDMETHOD(get_ComposedData)(/*[in]*/ BSTR Pattern, /*[out, retval]*/  BSTR *pVal);
	STDMETHOD(SetValue)(/*[in]*/ BSTR Key, /*[in]*/ BSTR Val, /*[in, optional, defaultvalue(VARIANT_FALSE)]*/ VARIANT_BOOL fCreate);

// IParseStringPairs2
	STDMETHOD(DeletePair)(/*[in]*/ BSTR Key);

// IPropertyBag
	STDMETHOD(Read)(/*[in]*/ LPCOLESTR pszPropName, /*[in, out]*/ VARIANT *pVar, /*[in]*/ IErrorLog *pErrorLog);
	STDMETHOD(Write)(/*[in]*/ LPCOLESTR pszPropName, /*[in]*/ VARIANT *pVar);

// ITRiASPropertyBag
	STDMETHODIMP ReadProperty(BSTR bstrDataName, VARIANT vDefaultValue, VARIANT *pvData);
	STDMETHODIMP WriteProperty(BSTR bstrDataName, VARIANT vData, VARIANT vDefaultValue);

protected:
	HRESULT GenRegExpr (os_string &rStr);
	HRESULT GenOutputFormat (LPCSTR pcPattern, BSTR bstrFirst, BSTR bstrSecond, BSTR *pbstr);

private:
	os_string m_strPattern;
	long m_l1st;
	long m_l2nd;
	CStringPairList m_Pairs;
	bool m_fHasPattern;
	bool m_fIsParsed;
	bool m_fHasDataSet;
	WParseRegularExpression m_RegExpr;
};

#endif // !defined(_STRINGPAIR_H__C21AAF99_2DE5_11d1_969A_00A024D6F582__INCLUDED_)
