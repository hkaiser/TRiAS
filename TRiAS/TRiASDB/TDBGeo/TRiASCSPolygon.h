///////////////////////////////////////////////////////////////////////////
// @doc
// @module TRiASCSPolygon.h | Declaration of the <c CTRiASCSPolygonGeometry>
// class

#if !defined(_TRIASCSPOLYGON_H__CF648168_9E24_11D1_BA1C_080036D63803__INCLUDED_)
#define _TRIASCSPOLYGON_H__CF648168_9E24_11D1_BA1C_080036D63803__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "TRiASCSPolyline.h"

/////////////////////////////////////////////////////////////////////////////
// CTRiASCSPolygonGeometry
class ATL_NO_VTABLE CTRiASCSPolygonGeometry :
	public CComCoClass<CTRiASCSPolygonGeometry, &CLSID_TRiASCSPolygonGeometry>,
	public IDispatchImpl<_DGMPolygonGeometry, &IID__DGMPolygonGeometry, TLB_TDBGEO_SIGNAT>,
	public CTRiASCSPolylineBase
{
public:
	CTRiASCSPolygonGeometry()
	{
	}
	~CTRiASCSPolygonGeometry()
	{
	}

	DECLARE_ONE_SIZE_PRIVATE_HEAP()
	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASCSPOLYGONGEOMETRY)

	DECLARE_PROTECT_FINAL_CONSTRUCT()
	DECLARE_GET_CONTROLLING_UNKNOWN()
	void FinalRelease()
	{
		m_TearOff.Release();
	}
	typedef CTRiASCSTearOff2<CTRiASCSPolygonGeometry> tearoff_t;
	CComPtr<IUnknown> m_TearOff;

	_COMX_PERF_OBJECTCOUNT_IMPL(CTRiASCSPolygonGeometry)
	BEGIN_COM_MAP(CTRiASCSPolygonGeometry)
		COM_INTERFACE_ENTRY(_DGMPolygonGeometry)
		COM_INTERFACE_ENTRY(_DGMPolylineGeometry)
		COM_INTERFACE_ENTRY(_DGMGeometry)
		COM_INTERFACE_ENTRY2(IDispatch, ITRiASCSGeometryProperties)
		COM_INTERFACE_ENTRY_CACHED_TEAR_OFF(_ATL_IIDOF(ITRiASTransformGeometry), tearoff_t, m_TearOff.p)
		COM_INTERFACE_ENTRY_CACHED_TEAR_OFF(_ATL_IIDOF(IPersistMemoryGDO), tearoff_t, m_TearOff.p)
		COM_INTERFACE_ENTRY_CACHED_TEAR_OFF(_ATL_IIDOF(IPersistMemory), tearoff_t, m_TearOff.p)
		COM_INTERFACE_ENTRY_CACHED_TEAR_OFF(_ATL_IIDOF(IPersistStreamInit), tearoff_t, m_TearOff.p)
		COM_INTERFACE_ENTRY_CACHED_TEAR_OFF(_ATL_IIDOF(IPersistStream), tearoff_t, m_TearOff.p)
		COM_INTERFACE_ENTRY_CACHED_TEAR_OFF(_ATL_IIDOF(IPersist), tearoff_t, m_TearOff.p)
		COM_INTERFACE_ENTRY_CACHED_TEAR_OFF(_ATL_IIDOF(IPersistMemoryWks), tearoff_t, m_TearOff.p)
		COM_INTERFACE_ENTRY_CHAIN(CTRiASCSPolylineBase)
	END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IPersist
	HRESULT GetClassID(CLSID * pClassID)
	{
		CHECKINPOINTER(pClassID);
		*pClassID = CLSID_TRiASCSPolygonGeometry;
		return S_OK;
	}

// ITRiASCSGeometryProperties
	STDMETHOD(get_Type)(/*[out, retval]*/ GEOMETRYTYPE * pval);
//	STDMETHOD(get_Envelope)(/*[out, retval]*/_DGMRectangleGeometry ** Rect);
	STDMETHOD(get_InitString) (/*[out, retval]*/ BSTR *pbstrMkName);
	STDMETHOD(put_InitString) (/*[in]*/ BSTR bstrMkName);

// _DGMGeometry
	STDMETHOD(get_Type)(BSTR * typeName);

// ITRiASCloneGeometry
	STDMETHODIMP Clone(/*[out, retval]*/ IDispatch * * ppIClonedObj);

// IPersistMemoryWks
	HRESULT GetSizeMaxWkb(ULONG *pulSize);
	HRESULT LoadWkb(LPVOID pMem, ULONG cbSize);
	HRESULT SaveWkb(LPVOID pMem, BOOL fClearDirty, ULONG cbSize);
	HRESULT LoadWkt(BSTR WKT);
	HRESULT SaveWkt(BSTR *WKT, BOOL fClearDirty);

// ITRiASCSPolygonGeometry
public:
// Properties
	STDMETHOD(get_Points)(_DGMPoints * * returnValue)
		{ return CTRiASCSPolylineBase::get_Points(returnValue); }
};

#endif //_TRIASCSPOLYGON_H__CF648168_9E24_11D1_BA1C_080036D63803__INCLUDED_
