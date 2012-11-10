///////////////////////////////////////////////////////////////////////////
// @doc
// @module TRiASCSPolyline.h | Declaration of the <c CTRiASCSPolylineGeometry>
// class

#if !defined(_TRIASCSPOLYLINE_H__CF648168_9E24_11D1_BA1C_080036D63803__INCLUDED_)
#define _TRIASCSPOLYLINE_H__CF648168_9E24_11D1_BA1C_080036D63803__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "TRiASCSTearOff.h"
#include "TRiASCSPoints.h"

/////////////////////////////////////////////////////////////////////////////
// CTRiASCSPolylineBase
class ATL_NO_VTABLE CTRiASCSPolylineBase :
	public CComObjectRootEx<CComObjectThreadModel>,
	public CErrSupport<CTRiASCSPolylineBase, &IID__DGMPolylineGeometry>,
	public IDispatchImpl<ITRiASCSGeometryProperties, &IID_ITRiASCSGeometryProperties, TLB_TDBGEO_SIGNAT>
{
public:
	static const CLSID &GetObjectCLSID() { return CLSID_TRiASCSPolylineGeometry; }
	
	CTRiASCSPolylineBase()
	{
		m_fIsDirty = false;
		m_fIsInitialized = false;
	}
	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	BEGIN_COM_MAP(CTRiASCSPolylineBase)
		COM_INTERFACE_ENTRY(ITRiASCSGeometryProperties)
		COM_INTERFACE_ENTRY(ITRiASCloneGeometry)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

// ISupportsErrorInfo
//	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IPersist

// IPersistStream
	HRESULT IsDirty();
	HRESULT Load(LPSTREAM pStm);
	HRESULT Save(LPSTREAM pStm, BOOL fClearDirty);
	HRESULT GetSizeMax(ULARGE_INTEGER * pcbSize);

// IPersistStreamInit
	HRESULT InitNew();

// IPersistMemory
	HRESULT Load(void * pvMem, ULONG cbSize);
	HRESULT Save(void * pvMem, BOOL fClearDirty, ULONG cbSize);
	HRESULT GetSizeMax(ULONG * pcbSize);

// IPersistMemoryGDO
	HRESULT LoadGDO(VOID * pMem, ULONG cbSize)
	{
		return Load(pMem, cbSize);
	}
	HRESULT SaveGDO(VOID * pMem, BOOL fClearDirty, ULONG cbSize)
	{
		return Save(pMem, fClearDirty, cbSize);
	}

// ITRiASCSPolylineGeometry
public:
// Properties
	STDMETHOD(get_Points)(_DGMPoints * * returnValue);

// ITRiASCSGeometryProperties
	STDMETHOD(get_Type)(/*[out, retval]*/ GEOMETRYTYPE * pval);
	STDMETHOD(get_Envelope)(/*[out, retval]*/ITRiASSimpleRectangle * * Rect);

// ITRiASTransformGeometry
	HRESULT Transform(/* [in]*/ struct CSID csGUID, /*[in]*/ ITRiASCSTransform * pCSTransform);
	HRESULT TransformInverse(/*[in]*/ struct CSID csGUID, /*[in]*/ ITRiASCSTransform * pCSTransform);

protected:
	bool m_fIsDirty;
	bool m_fIsInitialized;

	W_DGMPoints m_ptPoints;
};


/////////////////////////////////////////////////////////////////////////////
// CTRiASCSPolylineGeometry
class ATL_NO_VTABLE CTRiASCSPolylineGeometry :
	public CComCoClass<CTRiASCSPolylineGeometry, &CLSID_TRiASCSPolylineGeometry>,
	public IDispatchImpl<_DGMPolylineGeometry, &IID__DGMPolylineGeometry, TLB_TDBGEO_SIGNAT>,
	public CTRiASCSPolylineBase
{
public:
	CTRiASCSPolylineGeometry()
	{
	}
	~CTRiASCSPolylineGeometry()
	{
	}

	DECLARE_ONE_SIZE_PRIVATE_HEAP();
	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASCSPOLYLINEGEOMETRY)

	DECLARE_PROTECT_FINAL_CONSTRUCT()
	DECLARE_GET_CONTROLLING_UNKNOWN()
	void FinalRelease()
	{
		m_TearOff.Release();
	}
	typedef CTRiASCSTearOff2<CTRiASCSPolylineGeometry> tearoff_t;
	CComPtr<IUnknown> m_TearOff;

	_COMX_PERF_OBJECTCOUNT_IMPL(CTRiASCSPolylineGeometry)
	BEGIN_COM_MAP(CTRiASCSPolylineGeometry)
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
		*pClassID = CLSID_TRiASCSPolylineGeometry;
		return S_OK;
	}

// _DGMGeometry
	STDMETHOD(get_Type)(BSTR * typeName);
	STDMETHOD(get_InitString) (/*[out, retval]*/ BSTR *pbstrMkName);
	STDMETHOD(put_InitString) (/*[in]*/ BSTR bstrMkName);

// ITRiASCloneGeometry
	STDMETHODIMP Clone(/*[out, retval]*/ IDispatch **ppIClonedObj);

// IPersistMemoryWks
	HRESULT GetSizeMaxWkb(ULONG *pulSize);
	HRESULT LoadWkb(LPVOID pMem, ULONG cbSize);
	HRESULT SaveWkb(LPVOID pMem, BOOL fClearDirty, ULONG cbSize);
	HRESULT LoadWkt(BSTR WKT);
	HRESULT SaveWkt(BSTR *WKT, BOOL fClearDirty);

public:
// Properties
	STDMETHOD(get_Points)(_DGMPoints * * returnValue)
		{ return CTRiASCSPolylineBase::get_Points(returnValue); }
};

#endif //_TRIASCSPOLYLINE_H__CF648168_9E24_11D1_BA1C_080036D63803__INCLUDED_
