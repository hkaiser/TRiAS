///////////////////////////////////////////////////////////////////////////
// @doc
// @module TRiASCSLine.h | Declaration of the <c CTRiASCSLineGeometry>
// class

#if !defined(__TRIASCSLINE_H__CF648168_9E24_11D1_BA1C_080036D63803__INCLUDED_)
#define __TRIASCSLINE_H__CF648168_9E24_11D1_BA1C_080036D63803__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "TRiASCSTearOff.h"
#include "TRiASCSPoint.h"

/////////////////////////////////////////////////////////////////////////////
// CTRiASCSLineGeometry
class ATL_NO_VTABLE CTRiASCSLineGeometry :
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CTRiASCSLineGeometry, &CLSID_TRiASCSLineGeometry>,
	public CErrSupport<CTRiASCSLineGeometry, &IID__DGMLineGeometry>,
	public IDispatchImpl<ITRiASCSGeometryProperties, &IID_ITRiASCSGeometryProperties, TLB_TDBGEO_SIGNAT>,
	public IDispatchImpl<_DGMLineGeometry, &IID__DGMLineGeometry, TLB_TDBGEO_SIGNAT>
{
public:
	CTRiASCSLineGeometry()
	{
		m_fIsDirty = false;
		m_fIsInitialized = false;
		m_fIsOwnerStart = false;
		m_fIsOwnerEnd = false;
		m_ptStart = NULL;
		m_ptEnd = NULL;
	}
	 ~ CTRiASCSLineGeometry()
	{
		ReleaseStart();
		ReleaseEnd();
	}

//	DECLARE_ONE_SIZE_PRIVATE_HEAP();
	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASCSLINE)

	DECLARE_PROTECT_FINAL_CONSTRUCT()
	DECLARE_GET_CONTROLLING_UNKNOWN()
	void FinalRelease()
	{
		m_TearOff.Release();
	}
	typedef CTRiASCSTearOff2<CTRiASCSLineGeometry> tearoff_t;
	CComPtr<IUnknown> m_TearOff;

	_COMX_PERF_OBJECTCOUNT_IMPL(CTRiASCSLineGeometry)
	BEGIN_COM_MAP(CTRiASCSLineGeometry)
		COM_INTERFACE_ENTRY(_DGMLineGeometry)
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
		*pClassID = CLSID_TRiASCSLineGeometry;
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

// _DGMGeometry
	STDMETHOD(get_Type)(BSTR * typeName);

// ITRiASCSGeometryProperties
	STDMETHOD(get_Type)(/*[out, retval]*/ GEOMETRYTYPE * pval);
	STDMETHOD(get_Envelope)(/*[out, retval]*/ITRiASSimpleRectangle * * Rect);
	STDMETHOD(get_InitString) (/*[out, retval]*/ BSTR *pbstrMkName);
	STDMETHOD(put_InitString) (/*[in]*/ BSTR bstrMkName);

// ITRiASTransformGeometry
	HRESULT Transform(/* [in]*/ struct CSID csGUID, /*[in]*/ ITRiASCSTransform * pCSTransform);
	HRESULT TransformInverse(/*[in]*/ struct CSID csGUID, /*[in]*/ ITRiASCSTransform * pCSTransform);

// ITRiASCloneGeometry
	STDMETHODIMP Clone(/*[out, retval]*/ IDispatch * * ppIClonedObj);

// sonstige member
	void ReleaseStart()
	{
		if (m_fIsOwnerStart)
		{
				ASSERT(NULL != m_ptStart);
			m_ptStart -> Release();
		}
		m_ptStart = NULL;
		m_fIsOwnerStart = false;
	}
	void ReleaseEnd()
	{
		if (m_fIsOwnerEnd)
		{
				ASSERT(NULL != m_ptEnd);
			m_ptEnd -> Release();
		}
		m_ptEnd = NULL;
		m_fIsOwnerEnd = false;
	}

	void PutStart(_DGMPoint * newVal, bool owner)
	{
		ReleaseStart();
		m_ptStart = newVal;
		if (NULL != m_ptStart)
		{
			m_fIsOwnerStart = owner;

			// JG990201 wenn's unser ist
			if (m_fIsOwnerStart)
				m_ptStart -> AddRef();
		}

	}
	void PutEnd(_DGMPoint * newVal, bool owner)
	{
		ReleaseEnd();
		m_ptEnd = newVal;
		if (NULL != m_ptEnd)
		{
			m_fIsOwnerEnd = owner;
			// JG990201 wenn's unser ist
			if (m_fIsOwnerEnd)
				m_ptEnd -> AddRef();
		}

	}

// ITRiASCSLine
public:
	STDMETHOD(get_Start)(_DGMPoint * * returnValue);
	STDMETHOD(putref_Start)(_DGMPoint * returnValue);
	STDMETHOD(get_End)(_DGMPoint * * returnValue);
	STDMETHOD(putref_End)(_DGMPoint * returnValue);

protected:
	bool m_fIsDirty;
	bool m_fIsInitialized;

private:
	bool m_fIsOwnerStart;
	bool m_fIsOwnerEnd;

	_DGMPoint * m_ptStart;
	_DGMPoint * m_ptEnd;
};

#endif //__TRIASCSLINE_H__CF648168_9E24_11D1_BA1C_080036D63803__INCLUDED_
