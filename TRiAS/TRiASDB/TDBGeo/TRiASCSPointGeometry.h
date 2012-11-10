///////////////////////////////////////////////////////////////////////////
// @doc
// @module TRiASCSPointGeometry.h | Declaration of the <c CTRiASCSPointGeometry>
// class

#if !defined(_TRIASCSPOINTGEOMETRY_H__CF648168_9E24_11D1_BA1C_080036D63803__INCLUDED_)
#define _TRIASCSPOINTGEOMETRY_H__CF648168_9E24_11D1_BA1C_080036D63803__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "TRiASCSPoint.h"

/////////////////////////////////////////////////////////////////////////////
// CTRiASCSPointGeometry
class ATL_NO_VTABLE CTRiASCSPointGeometry :
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CTRiASCSPointGeometry, &CLSID_TRiASCSPointGeometry>,
	public CErrSupport<CTRiASCSPointGeometry, &IID_ITRiASSimplePoint>,
	public IDispatchImpl<ITRiASSimplePoint, &IID_ITRiASSimplePoint, TLB_TDBGEO_SIGNAT>,
	public IDispatchImpl<ITRiASCSGeometryProperties, &IID_ITRiASCSGeometryProperties, TLB_TDBGEO_SIGNAT>
{
public:
	CTRiASCSPointGeometry()
	{
		m_fIsDirty = false;
		m_fIsInitialized = false;
		memset (&m_ptOrig, 0, sizeof(CSCOORD));
	}
	~CTRiASCSPointGeometry()
	{
	}

	DECLARE_ONE_SIZE_PRIVATE_HEAP();
	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASCSPOINTGEOMETRY)

	DECLARE_PROTECT_FINAL_CONSTRUCT()
	DECLARE_GET_CONTROLLING_UNKNOWN()
	void FinalRelease()
	{
		m_TearOff.Release();
	}
	typedef CTRiASCSTearOff2<CTRiASCSPointGeometry> tearoff_t;
	CComPtr<IUnknown> m_TearOff;

	_COMX_PERF_OBJECTCOUNT_IMPL(CTRiASCSPointGeometry)
	BEGIN_COM_MAP(CTRiASCSPointGeometry)
		COM_INTERFACE_ENTRY(ITRiASSimplePoint)
		COM_INTERFACE_ENTRY(_DGMPointGeometry)
		COM_INTERFACE_ENTRY(_DGMGeometry)
		COM_INTERFACE_ENTRY2(IDispatch, ITRiASCSGeometryProperties)
		COM_INTERFACE_ENTRY(ITRiASCSGeometryProperties)
		COM_INTERFACE_ENTRY(ITRiASCloneGeometry)
		COM_INTERFACE_ENTRY_CACHED_TEAR_OFF(_ATL_IIDOF(ITRiASTransformGeometry), tearoff_t, m_TearOff.p)
		COM_INTERFACE_ENTRY_CACHED_TEAR_OFF(_ATL_IIDOF(IPersistMemoryGDO), tearoff_t, m_TearOff.p)
		COM_INTERFACE_ENTRY_CACHED_TEAR_OFF(_ATL_IIDOF(IPersistMemory), tearoff_t, m_TearOff.p)
		COM_INTERFACE_ENTRY_CACHED_TEAR_OFF(_ATL_IIDOF(IPersistStreamInit), tearoff_t, m_TearOff.p)
		COM_INTERFACE_ENTRY_CACHED_TEAR_OFF(_ATL_IIDOF(IPersistStream), tearoff_t, m_TearOff.p)
		COM_INTERFACE_ENTRY_CACHED_TEAR_OFF(_ATL_IIDOF(IPersist), tearoff_t, m_TearOff.p)
		COM_INTERFACE_ENTRY_CACHED_TEAR_OFF(_ATL_IIDOF(IPersistMemoryWks), tearoff_t, m_TearOff.p)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IPersist
	HRESULT GetClassID(CLSID * pClassID)
	{
		CHECKINPOINTER(pClassID);
		*pClassID = CLSID_TRiASCSPointGeometry;
		return S_OK;
	}

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

// IPersistMemoryWks
	HRESULT GetSizeMaxWkb(ULONG *pulSize);
	HRESULT LoadWkb(LPVOID pMem, ULONG cbSize);
	HRESULT SaveWkb(LPVOID pMem, BOOL fClearDirty, ULONG cbSize);
	HRESULT LoadWkt(BSTR WKT);
	HRESULT SaveWkt(BSTR *WKT, BOOL fClearDirty);

// ITRiASCSGeometryProperties
	STDMETHOD(get_Type)(/*[out, retval]*/ GEOMETRYTYPE * pval);
	STDMETHOD(get_Envelope)(/*[out, retval]*/ITRiASSimpleRectangle * * Rect);
	STDMETHOD(get_InitString) (/*[out, retval]*/ BSTR *pbstrMkName);
	STDMETHOD(put_InitString) (/*[in]*/ BSTR bstrMkName);

// _DGMGeometry
	STDMETHOD(get_Type)(BSTR * typeName);

// _DGMPointGeometry
public:
// Properties
	STDMETHOD(get_Origin)(_DGMPoint * * returnValue);
	STDMETHOD(putref_Origin)(_DGMPoint * returnValue);

// ITRiASSimplePoint
	STDMETHOD(GetPoint)(double *pVals);
	STDMETHOD(SetPoint)(double *pVals);
	STDMETHODIMP get_X(double *pVal);
	STDMETHODIMP put_X(double newVal);
	STDMETHODIMP get_Y(double *pVal);
	STDMETHODIMP put_Y(double newVal);
	STDMETHODIMP get_Z(double *pVal);
	STDMETHODIMP put_Z(double newVal);

// ITRiASTransformGeometry
	HRESULT Transform(/* [in]*/ struct CSID csGUID, /*[in]*/ ITRiASCSTransform * pCSTransform);
	HRESULT TransformInverse(/*[in]*/ struct CSID csGUID, /*[in]*/ ITRiASCSTransform * pCSTransform);

// ITRiASCloneGeometry
	STDMETHODIMP Clone(/*[out, retval]*/ IDispatch * * ppIClonedObj);

protected:
	bool m_fIsDirty;
	bool m_fIsInitialized;

	CSCOORD m_ptOrig;
};

#endif //_TRIASCSPOINTGEOMETRY_H__CF648168_9E24_11D1_BA1C_080036D63803__INCLUDED_
