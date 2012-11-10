// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 08.01.2001 11:02:27 
//
// @doc
// @module StatistValue.h | Declaration of several statistics classes

#if !defined(_STATISTVALUE_H__4704B0B9_A51E_406A_82C6_30667028389C__INCLUDED_)
#define _STATISTVALUE_H__4704B0B9_A51E_406A_82C6_30667028389C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"       // main symbols
#include "StatFuncName.h"

/////////////////////////////////////////////////////////////////////////////
// CStatistValue(s)
class ATL_NO_VTABLE CStatistValue : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public ISupportErrorInfo,
	public IDispatchImpl<IGenericStatistics, &IID_IGenericStatistics, &LIBID_TRiASStatistics>
{
public:
	CStatistValue()
	{
	}

	DECLARE_PROTECT_FINAL_CONSTRUCT()
	BEGIN_COM_MAP(CStatistValue)
		COM_INTERFACE_ENTRY(IGenericStatistics)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

	HRESULT FinalConstruct()
	{
	HRESULT hr = m_CumPts.LocalCreateInstance(CLSID_TRiASSimpleStatistics);

		if (SUCCEEDED(hr))
			hr = CComObjectRootEx<_ThreadModel>::FinalConstruct();
		return hr;
	}
	void FinalRelease()
	{
		m_CumPts.Assign(NULL);
	}

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IGenericStatistics
public:
	STDMETHOD(AddValue)(double Value, VARIANT Data);
	STDMETHOD(RemoveValue)(double Value);
	STDMETHOD(Reset)();

protected:
	WTRiASSimpleStatistics m_CumPts;	// hier wird die eigentliche Arbeit gemacht
};

// diverse inline Funktionen
#include "StatistValueImpl.cpp"

///////////////////////////////////////////////////////////////////////////////
// Definition einer konkreten statistischen Kenngröße
template<class T, const CLSID *pclsid>
class CStatistValueT : 
	public CStatistValue,
	public CComCoClass<T, pclsid>
{ 
public: 
// Registry
	static HRESULT WINAPI UpdateRegistry(BOOL bRegister)
	{
		static _ATL_REGMAP_ENTRY regEntryMap[] = 
		{
			{ L"VALUENAME", T::RegValueName() },
			{ L"CLASSNAME", T::RegClassName() },
			{ L"GUID", T::RegGuidAsString() },
			{ NULL, NULL },		// EndeKennung
		};
		return _Module.UpdateRegistryFromResource(IDR_STATISTVALUE, bRegister, regEntryMap);
	}
};

///////////////////////////////////////////////////////////////////////////////
// Makro zur Definition einer konkreten statistischen Kenngröße
extern OLECHAR s_cbGuid[37];
extern OLECHAR s_cbStatName[128];

namespace {
	inline 
	CComBSTR GetStatFuncName (BSTR bstrFullName)
	{
		USES_CONVERSION;

	CStatFuncName FuncName(OLE2A(bstrFullName));

		return CComBSTR(FuncName.GetName().c_str());
	}
}

#define STATISTVALUE_DOUBLE(x, clsid, name, idname, iddesc) \
class x : public CStatistValueT<x, &clsid> \
{ \
public: \
	static LPCOLESTR RegValueName() { return L#name; } \
	static LPCOLESTR RegClassName() {  CComBSTR bstr; bstr.LoadString(idname); _ASSERTE(bstr.Length() < _countof(s_cbStatName)); wcscpy(s_cbStatName, GetStatFuncName(bstr)); return s_cbStatName; } \
	static LPCOLESTR RegGuidAsString() { CIID Guid(clsid); wcscpy(s_cbGuid, CComBSTR(Guid)); return s_cbGuid; } \
	STDMETHOD(get_Name)(BSTR* pVal) { CComBSTR bstr; bstr.LoadString(idname); *pVal = bstr.Detach(); return S_OK; } \
	STDMETHOD(get_Description)(BSTR* pVal) { CComBSTR bstr; bstr.LoadString(idname); *pVal = bstr.Detach(); return S_OK; } \
	STDMETHOD(Calculate)(VARIANT *pvValue) { double Val = 0; RETURN_FAILED_HRESULT(m_CumPts -> get_##name(&Val)); CComVariant vValue(Val); return vValue.Detach(pvValue); } \
}

#define STATISTVALUE(x, clsid, name, type, vt, idname, iddesc) \
class x : public CStatistValueT<x, &clsid> \
{ \
public: \
	static LPCOLESTR RegValueName() { return L#name; } \
	static LPCOLESTR RegClassName() {  CComBSTR bstr; bstr.LoadString(idname); _ASSERTE(bstr.Length() < _countof(s_cbStatName)); wcscpy(s_cbStatName, GetStatFuncName(bstr)); return s_cbStatName; } \
	static LPCOLESTR RegGuidAsString() { CIID Guid(clsid); wcscpy(s_cbGuid, CComBSTR(Guid)); return s_cbGuid; } \
	STDMETHOD(get_Name)(BSTR* pVal) { CComBSTR bstr; bstr.LoadString(idname); *pVal = bstr.Detach(); return S_OK; } \
	STDMETHOD(get_Description)(BSTR* pVal) { CComBSTR bstr; bstr.LoadString(idname); *pVal = bstr.Detach(); return S_OK; } \
	STDMETHOD(Calculate)(VARIANT *pvValue) { type Val = 0; RETURN_FAILED_HRESULT(m_CumPts -> get_##name(&Val)); CComVariant vValue(Val, vt); return vValue.Detach(pvValue); } \
}

///////////////////////////////////////////////////////////////////////////////
// statistische Kenngrößen
STATISTVALUE(CStatistCount, CLSID_TRiASStatistCount, Count, ULONG, VT_I4, IDS_STATISTCOUNT_NAME, IDS_STATISTCOUNT_DESC);
STATISTVALUE(CStatistCountNotNull, CLSID_TRiASStatistCountNotNull, CountNotNull, ULONG, VT_I4, IDS_STATISTCOUNTNOTNULL_NAME, IDS_STATISTCOUNTNOTNULL_DESC);

STATISTVALUE_DOUBLE(CStatistSum, CLSID_TRiASStatistSum, Sum, IDS_STATISTSUM_NAME, IDS_STATISTSUM_DESC);
STATISTVALUE_DOUBLE(CStatistArithAverage, CLSID_TRiASStatistArithmeticAverage, ArithmeticAverage, IDS_STATISTARITHAVERAGE_NAME, IDS_STATISTARITHAVERAGE_DESC);
STATISTVALUE_DOUBLE(CStatistGeomAverage, CLSID_TRiASStatistGeometricAverage, GeometricAverage, IDS_STATISTGEOMAVERAGE_NAME, IDS_STATISTGEOMAVERAGE_DESC);
STATISTVALUE_DOUBLE(CStatistMedian, CLSID_TRiASStatistMedian, Median, IDS_STATISTMEDIAN_NAME, IDS_STATISTMEDIAN_DESC);

STATISTVALUE_DOUBLE(CStatistMinValue, CLSID_TRiASStatistMinValue, MinValue, IDS_STATISTMINVALUE_NAME, IDS_STATISTMINVALUE_DESC);
STATISTVALUE_DOUBLE(CStatistMaxValue, CLSID_TRiASStatistMaxValue, MaxValue, IDS_STATISTMAXVALUE_NAME, IDS_STATISTMAXVALUE_DESC);
STATISTVALUE_DOUBLE(CStatistRange, CLSID_TRiASStatistRange, Range, IDS_STATISTRANGE_NAME, IDS_STATISTRANGE_DESC);

STATISTVALUE_DOUBLE(CStatistStandardDeviation, CLSID_TRiASStatistStandardDeviation, StandardDeviation, IDS_STATISTDEVIATION_NAME, IDS_STATISTDEVIATION_DESC);
STATISTVALUE_DOUBLE(CStatistVariance, CLSID_TRiASStatistVariance, Variance, IDS_STATISTVARIANCE_NAME, IDS_STATISTVARIANCE_DESC);

#endif // !defined(_STATISTVALUE_H__4704B0B9_A51E_406A_82C6_30667028389C__INCLUDED_)
