// @doc
// @module SimpleStatistics.h | Declaration of the <c CSimpleStatistics> class

#if !defined(_SIMPLESTATISTICS_H__0CB3A69B_E5CE_11D2_9BD9_586A20524153__INCLUDED_)
#define _SIMPLESTATISTICS_H__0CB3A69B_E5CE_11D2_9BD9_586A20524153__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <float.h>
#include <ospace/std/set>

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSimpleStatistics
class ATL_NO_VTABLE CSimpleStatistics : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CSimpleStatistics, &CLSID_TRiASSimpleStatistics>,
	public CErrSupport<CSimpleStatistics, &IID_ITRiASSimpleStatistics>,
	public IDispatchImpl<ITRiASSimpleStatistics, &IID_ITRiASSimpleStatistics, 
		&LIBID_TRiASStatistics,
		TYPELIB_STATIST_MAJOR_VERSION, TYPELIB_STATIST_MINOR_VERSION>
{
public:
	CSimpleStatistics() :
		m_lCount(0L), m_lCountNotNull(0L),
		m_dSum(0.0), m_dSqrSum(0.0), m_dMin(DBL_MAX), m_dMax(-DBL_MAX)
	{
	}

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CSimpleStatistics)
	DECLARE_REGISTRY_RESOURCEID(IDR_SIMPLESTATISTICS)

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CSimpleStatistics)
		COM_INTERFACE_ENTRY(ITRiASSimpleStatistics)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ISimpleStatistics
public:
	STDMETHOD(get_Count)(/*[out, retval]*/ ULONG *pVal);
	STDMETHOD(get_Sum)(/*[out, retval]*/ double *pVal);
	STDMETHOD(get_CountNotNull)(/*[out, retval]*/ ULONG *pVal);
	STDMETHOD(get_ArithmeticAverage)(/*[out, retval]*/ double *pVal);
	STDMETHOD(get_GeometricAverage)(/*[out, retval]*/ double *pVal);
	STDMETHOD(get_Median)(/*[out, retval]*/ double *pVal);
	STDMETHOD(get_MaxValue)(/*[out, retval]*/ double *pVal);
	STDMETHOD(get_MinValue)(/*[out, retval]*/ double *pVal);
	STDMETHOD(get_Range)(/*[out, retval]*/ double *pVal);
	STDMETHOD(get_StandardDeviation)(/*[out, retval]*/ double *pVal);
	STDMETHOD(get_Variance)(/*[out, retval]*/ double *pVal);

	STDMETHOD(Reset)();
	STDMETHOD(AddValue)(/*[in]*/ double Value, /*[in, optional]*/ VARIANT vData);
	STDMETHOD(RemoveValue)(/*[in]*/ double Value);

	STDMETHOD(RangesByEqualCount)(/*[in]*/ ULONG NumberOfRanges, /*[in, out]*/ SAFEARRAY **pMinBounds, /*[in, out]*/ SAFEARRAY **pMaxBounds, /*[in, out]*/ SAFEARRAY **ppCounts, /*[in, out, optional]*/ SAFEARRAY **ppData);
	STDMETHOD(RangesByEqualRange)(/*[in]*/ ULONG NumberOfRanges, /*[in]*/ double StartValue, /*[in]*/ double EndValue, /*[in, out]*/ SAFEARRAY **pMinBounds, /*[in, out]*/ SAFEARRAY **pMaxBounds, /*[in, out]*/ SAFEARRAY **ppCounts, /*[in, out, optional]*/ SAFEARRAY **ppData);
	STDMETHOD(RangesByStandardDeviation)(/*[in]*/ ULONG NumberOfRanges, /*[in, out]*/ SAFEARRAY **pMinBounds, /*[in, out]*/ SAFEARRAY **pMaxBounds, /*[in, out]*/ SAFEARRAY **ppCounts, /*[in, out, optional]*/ SAFEARRAY **ppData);

private:
// OriginalWerte
	ULONG m_lCount;
	ULONG m_lCountNotNull;

	typedef multiset<double, less<double> > CValueSet;
	CValueSet m_Values;

// diverse berechnete Werte
	double m_dSum;		// Summe aller Werte
	double m_dSqrSum;	// Summe der Quadrate aller Werte
	double m_dMin;		// kleinster aller Werte
	double m_dMax;		// größter aller Werte
};

#endif // !defined(_SIMPLESTATISTICS_H__0CB3A69B_E5CE_11D2_9BD9_586A20524153__INCLUDED_)
