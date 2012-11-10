///////////////////////////////////////////////////////////////////////////
// @doc
// @module TRiASCSBoundaryGeometry.h | Declaration of the <c CTRiASCSBoundaryGeometry>
// class

#if !defined(__TRIASCSBOUNDARYGEOMETRY_H__CF648168_9E24_11D1_BA1C_080036D63803__INCLUDED_)
#define __TRIASCSBOUNDARYGEOMETRY_H__CF648168_9E24_11D1_BA1C_080036D63803__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "TRiASCSTearOff.h"
#include "TRiASCSPoint.h"
#include "TRiASCSGeometryCollection.h"

/////////////////////////////////////////////////////////////////////////////
// CTRiASCSBoundaryGeometry
class ATL_NO_VTABLE CTRiASCSBoundaryGeometry :
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CTRiASCSBoundaryGeometry, &CLSID_TRiASCSBoundaryGeometry>,
	public CErrSupport<CTRiASCSBoundaryGeometry, &IID__DGMBoundaryGeometry>,
	public IDispatchImpl<_DGMBoundaryGeometry, &IID__DGMBoundaryGeometry, TLB_TDBGEO_SIGNAT>,
	public IDispatchImpl<ITRiASCSGeometryProperties, &IID_ITRiASCSGeometryProperties, TLB_TDBGEO_SIGNAT>
{
public:
	CTRiASCSBoundaryGeometry()
	{
		m_fIsDirty = false;
		m_fIsInitialized = false;
		m_fIsOwner = false;
		m_pExterior = NULL;
	}
	~CTRiASCSBoundaryGeometry()
	{
		ReleaseExterior();
	}

	DECLARE_ONE_SIZE_PRIVATE_HEAP();
	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASCSBOUNDARYGEOMETRY)

	DECLARE_PROTECT_FINAL_CONSTRUCT()
	DECLARE_GET_CONTROLLING_UNKNOWN()
	void FinalRelease()
	{
		m_TearOff.Release();
	}
	typedef CTRiASCSTearOff2<CTRiASCSBoundaryGeometry> tearoff_t;
	CComPtr<IUnknown> m_TearOff;

	_COMX_PERF_OBJECTCOUNT_IMPL(CTRiASCSBoundaryGeometry)
	BEGIN_COM_MAP(CTRiASCSBoundaryGeometry)
		COM_INTERFACE_ENTRY(_DGMBoundaryGeometry)
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
		 * pClassID = CLSID_TRiASCSBoundaryGeometry;
		return S_OK;
	}

// IPersistStream
	HRESULT IsDirty();
	HRESULT Load(LPSTREAM pStm);
	HRESULT Save(LPSTREAM pStm , BOOL fClearDirty);
	HRESULT GetSizeMax(ULARGE_INTEGER * pcbSize);

// IPersistStreamInit
	HRESULT InitNew();

// IPersistMemory
	HRESULT Load(void * pvMem , ULONG cbSize);
	HRESULT Save(void * pvMem , BOOL fClearDirty , ULONG cbSize);
	HRESULT GetSizeMax(ULONG * pcbSize);

// IPersistMemoryGDO
	HRESULT LoadGDO(VOID * pMem , ULONG cbSize);
	HRESULT SaveGDO(VOID * pMem , BOOL fClearDirty , ULONG cbSize);

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

// _DGMBoundaryGeometry
public:
	STDMETHOD(get_Type)(/*[out, retval]*/ LONG * pVal);
	STDMETHOD(get_Exterior)(IDispatch * * returnValue);
	STDMETHOD(get_Holes)(_DGMGeometryCollection * * returnValue);
	STDMETHOD(putref_Exterior)(IDispatch * returnValue);

// ITRiASTransformGeometry
	HRESULT Transform(/*[in]*/ struct CSID csGUID , /*[in]*/ ITRiASCSTransform * pCSTransform);
	HRESULT TransformInverse(/*[in]*/ struct CSID csGUID , /*[in]*/ ITRiASCSTransform * pCSTransform);

// ITRiASCloneGeometry
	STDMETHODIMP Clone(/*[out, retval]*/ IDispatch * * ppIClonedObj);

protected:
	HRESULT ReleaseExterior()
	{
		if (m_fIsOwner)
		{
				ASSERT(NULL != m_pExterior);
			m_pExterior -> Release();
			m_pExterior = NULL;
		}
		m_fIsOwner = false;
		return S_OK;
	}
	HRESULT PutExterior(IDispatch * newVal , bool owner)
	{
		ReleaseExterior();
		m_pExterior = newVal;
		if (NULL != m_pExterior)
		{
			m_fIsOwner = owner;
			// JG990201
			if (m_fIsOwner)
				m_pExterior -> AddRef();
		}

		return S_OK;
	}

protected:
	bool m_fIsDirty;
	bool m_fIsInitialized;
	W_DGMGeometryCollection m_pHoles;

private:
	bool m_fIsOwner;
	IDispatch * m_pExterior;
};

#endif //__TRIASCSBOUNDARYGEOMETRY_H__CF648168_9E24_11D1_BA1C_080036D63803__INCLUDED_
