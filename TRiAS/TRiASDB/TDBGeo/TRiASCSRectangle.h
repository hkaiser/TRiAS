///////////////////////////////////////////////////////////////////////////
// @doc
// @module TRiASCSRectangle.h | Declaration of the <c CTRiASCSRectangleGeometry>
// class

#if !defined(_TRIASCSRECTANGLE_H__CF648168_9E24_11D1_BA1C_080036D63803__INCLUDED_)
#define _TRIASCSRECTANGLE_H__CF648168_9E24_11D1_BA1C_080036D63803__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "TRiASCSPoint.h"

/////////////////////////////////////////////////////////////////////////////
// Pointer mit ownership verwalten
template<class T>
inline void ReleasePtr(bool &rfIsOwner, T &rPtr)
{
	if (rfIsOwner)
	{
			ASSERT(NULL != rPtr);
		rPtr -> Release();
	}
	rPtr = NULL;
	rfIsOwner = false;
}

template<class T>
inline void AssignPtr (bool &rfIsOwner, T &rPtr, T newVal, bool fNewIsOwner)
{
	ReleasePtr(rfIsOwner, rPtr);
	rPtr = newVal;
	if (NULL != rPtr)
	{
		rfIsOwner = fNewIsOwner;
		if (rfIsOwner)
			rPtr -> AddRef();
	}
}

/////////////////////////////////////////////////////////////////////////////
// CTRiASCSRectangleGeometry
class ATL_NO_VTABLE CTRiASCSRectangleGeometry :
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CTRiASCSRectangleGeometry, &CLSID_TRiASCSRectangleGeometry>,
	public CErrSupport<CTRiASCSRectangleGeometry, &IID__DGMRectangleGeometry>,
	public IDispatchImpl<ITRiASCSGeometryProperties, &IID_ITRiASCSGeometryProperties, TLB_TDBGEO_SIGNAT>,
	public IDispatchImpl<ITRiASSimpleRectangle, &IID_ITRiASSimpleRectangle, TLB_TDBGEO_SIGNAT>
{
public:
	CTRiASCSRectangleGeometry()
	{
		m_fIsDirty = false;
		m_fIsInitialized = false;
		m_fIsOwnerNormal = false;

		m_dRotation = 0.0;
		m_vecNormal = NULL;

		memset (&m_ptOrig, 0, sizeof(CSCOORD));
		memset (&m_pt2nd, 0, sizeof(CSCOORD));
	}
	~CTRiASCSRectangleGeometry()
	{
		m_fIsInitialized = false;
		ReleaseNormal();
	}

//	_ATLX_DEBUG_ADDREF_RELEASE_IMPL(CTRiASCSRectangleGeometry)
	DECLARE_ONE_SIZE_PRIVATE_HEAP();
	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASCSRECTANGLE)

	DECLARE_PROTECT_FINAL_CONSTRUCT()
	DECLARE_GET_CONTROLLING_UNKNOWN()
	void FinalRelease()
	{
		m_TearOff.Release();
	}
	typedef CTRiASCSTearOff2<CTRiASCSRectangleGeometry> tearoff_t;
	CComPtr<IUnknown> m_TearOff;

	_COMX_PERF_OBJECTCOUNT_IMPL(CTRiASCSRectangleGeometry)
	BEGIN_COM_MAP(CTRiASCSRectangleGeometry)
		COM_INTERFACE_ENTRY(ITRiASSimpleRectangle)
		COM_INTERFACE_ENTRY2(_DGMRectangleGeometry, ITRiASSimpleRectangle)
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
		*pClassID = CLSID_TRiASCSRectangleGeometry;
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
	STDMETHOD(get_Type)(/*[out, retval]*/ GEOMETRYTYPE *pval);
	STDMETHOD(get_Envelope)(/*[out, retval]*/ITRiASSimpleRectangle **Rect);
	STDMETHOD(get_InitString) (/*[out, retval]*/ BSTR *pbstrMkName);
	STDMETHOD(put_InitString) (/*[in]*/ BSTR bstrInit);

// _DGMGeometry
	STDMETHOD(get_Type)(BSTR * typeName);

// ITRiASTransformGeometry
	HRESULT Transform(/* [in]*/ struct CSID csGUID, /*[in]*/ ITRiASCSTransform * pCSTransform);
	HRESULT TransformInverse(/*[in]*/ struct CSID csGUID, /*[in]*/ ITRiASCSTransform * pCSTransform);

// ITRiASCloneGeometry
	STDMETHODIMP Clone(/*[out, retval]*/ IDispatch * * ppIClonedObj);

// ITRiASCSRectangle
public:
	STDMETHOD(get_ZMax)(/*[out, retval]*/ double * pVal);
	STDMETHOD(put_ZMax)(/*[in]*/ double newVal);
	STDMETHOD(get_YMax)(/*[out, retval]*/ double * pVal);
	STDMETHOD(put_YMax)(/*[in]*/ double newVal);
	STDMETHOD(get_XMax)(/*[out, retval]*/ double * pVal);
	STDMETHOD(put_XMax)(/*[in]*/ double newVal);
	STDMETHOD(get_ZMin)(/*[out, retval]*/ double * pVal);
	STDMETHOD(put_ZMin)(/*[in]*/ double newVal);
	STDMETHOD(get_YMin)(/*[out, retval]*/ double * pVal);
	STDMETHOD(put_YMin)(/*[in]*/ double newVal);
	STDMETHOD(get_XMin)(/*[out, retval]*/ double * pVal);
	STDMETHOD(put_XMin)(/*[in]*/ double newVal);
	STDMETHOD(GetRect)(/*[out]*/ double *pValXMin, /*[out]*/ double *pValYMin, /*[out]*/ double *pValXMax, /*[out]*/ double *pValYMax);
	STDMETHOD(SetRect)(/*[in]*/ double newValXMin, /*[in]*/ double newValYMin, /*[in]*/ double newValXMax, /*[in]*/ double newValYMax);

// Properties
	STDMETHOD(get_Width)(double * returnValue);
	STDMETHOD(put_Width)(double returnValue);
	STDMETHOD(get_Height)(double * returnValue);
	STDMETHOD(put_Height)(double returnValue);
	STDMETHOD(get_Rotation)(double * returnValue);
	STDMETHOD(put_Rotation)(double returnValue);
	STDMETHOD(get_Origin)(_DGMPoint * * returnValue);
	STDMETHOD(putref_Origin)(_DGMPoint * returnValue);
	STDMETHOD(get_Normal)(_DGMVector * * returnValue);
	STDMETHOD(putref_Normal)(_DGMVector * returnValue);

protected:
	void ReleaseNormal()
		{ ReleasePtr(m_fIsOwnerNormal, m_vecNormal); }
	void PutNormal(_DGMVector * newVal, bool owner)
		{ AssignPtr(m_fIsOwnerNormal, m_vecNormal, newVal, owner); }

protected:
	double m_dRotation;
	bool m_fIsDirty;
	bool m_fIsInitialized;

	CSCOORD m_ptOrig;
	CSCOORD m_pt2nd;

private:
	bool m_fIsOwnerNormal;
	_DGMVector * m_vecNormal;
};

#endif // !defined(_TRIASCSRECTANGLE_H__CF648168_9E24_11D1_BA1C_080036D63803__INCLUDED_)
