// @doc
// @module TRiASCSPoint.h | Definition of the CTRiASCSPoint class
//

#if !defined(_TRIASCSPOINT_H__0BDC3C1F_503F_11D1_96F0_00A024D6F582__INCLUDED_)
#define _TRIASCSPOINT_H__0BDC3C1F_503F_11D1_96F0_00A024D6F582__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "TRiASCSTearOff.h"

/////////////////////////////////////////////////////////////////////////////
// CTRiASCSPoint

class ATL_NO_VTABLE CTRiASCSPoint :
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CTRiASCSPoint, &CLSID_TRiASCSPoint>,
	public CErrSupport<CTRiASCSPoint, &IID__DGMPoint>,
	public IDispatchImpl<_DGMPoint, &IID__DGMPoint, TLB_TDBGEO_SIGNAT>,
	public IDispatchImpl<ITRiASCloneGeometry, &IID_ITRiASCloneGeometry, TLB_TDBGEO_SIGNAT>
{
public:
	CTRiASCSPoint()
	{
		m_p.X = m_p.Y = m_p.Z = 0;
		m_fIsDirty = false;
		m_fIsInitialized = false;
	}
	~CTRiASCSPoint()
	{
	}

	DECLARE_ONE_SIZE_PRIVATE_HEAP()
	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASCSPOINT)

	DECLARE_PROTECT_FINAL_CONSTRUCT()
	DECLARE_GET_CONTROLLING_UNKNOWN()
	void FinalRelease()
	{
		m_TearOff.Release();
	}
	typedef CTRiASCSTearOff2<CTRiASCSPoint> tearoff_t;
	CComPtr<IUnknown> m_TearOff;

	_COMX_PERF_OBJECTCOUNT_IMPL(CTRiASCSPoint)
	BEGIN_COM_MAP(CTRiASCSPoint)
		COM_INTERFACE_ENTRY(_DGMPoint)
		COM_INTERFACE_ENTRY2(IDispatch, _DGMPoint)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY(ITRiASCloneGeometry)
		COM_INTERFACE_ENTRY_CACHED_TEAR_OFF(_ATL_IIDOF(ITRiASTransformGeometry), tearoff_t, m_TearOff.p)
		COM_INTERFACE_ENTRY_CACHED_TEAR_OFF(_ATL_IIDOF(IPersistMemoryGDO), tearoff_t, m_TearOff.p)
		COM_INTERFACE_ENTRY_CACHED_TEAR_OFF(_ATL_IIDOF(IPersistMemory), tearoff_t, m_TearOff.p)
		COM_INTERFACE_ENTRY_CACHED_TEAR_OFF(_ATL_IIDOF(IPersistStreamInit), tearoff_t, m_TearOff.p)
		COM_INTERFACE_ENTRY_CACHED_TEAR_OFF(_ATL_IIDOF(IPersistStream), tearoff_t, m_TearOff.p)
		COM_INTERFACE_ENTRY_CACHED_TEAR_OFF(_ATL_IIDOF(IPersist), tearoff_t, m_TearOff.p)
		COM_INTERFACE_ENTRY_CACHED_TEAR_OFF(_ATL_IIDOF(IPersistMemoryWks), tearoff_t, m_TearOff.p)
	END_COM_MAP()

// IPersist
	HRESULT GetClassID (CLSID * pClassID)
	{
		CHECKINPOINTER(pClassID);
		*pClassID = CLSID_TRiASCSPoint;
		return S_OK;
	}

// IPersistStream
	HRESULT IsDirty ();
	HRESULT Load (LPSTREAM pStm);
	HRESULT Save (LPSTREAM pStm, BOOL fClearDirty);
	HRESULT GetSizeMax (ULARGE_INTEGER * pcbSize);

// IPersistStreamInit
	HRESULT InitNew ();

// IPersistMemory
	HRESULT Load (void * pvMem, ULONG cbSize);
	HRESULT Save (void * pvMem, BOOL fClearDirty, ULONG cbSize);
	HRESULT GetSizeMax (ULONG * pcbSize);

// IPersistMemoryGDO
	HRESULT LoadGDO (VOID * pMem, ULONG cbSize)
	{
		return Load(pMem, cbSize);
	}
	HRESULT SaveGDO (VOID * pMem, BOOL fClearDirty, ULONG cbSize)
	{
		return Save(pMem, fClearDirty, cbSize);
	}

// IPersistMemoryWks
	HRESULT GetSizeMaxWkb(ULONG *pulSize);
	HRESULT LoadWkb(LPVOID pMem, ULONG cbSize);
	HRESULT SaveWkb(LPVOID pMem, BOOL fClearDirty, ULONG cbSize);
	HRESULT LoadWkt(BSTR WKT);
	HRESULT SaveWkt(BSTR *WKT, BOOL fClearDirty);

// ITRiASTransformGeometry
	HRESULT Transform (/* [in]*/ struct CSID csGUID, /*[in]*/ ITRiASCSTransform * pCSTransform);
	HRESULT TransformInverse (/*[in]*/ struct CSID csGUID, /*[in]*/ ITRiASCSTransform * pCSTransform);

// ITRiASCloneGeometry
	STDMETHODIMP Clone(/*[out, retval]*/ IDispatch **ppIClonedObj);

// _DGMPoint
public:
	STDMETHOD(get_X)(/*[out, retval]*/ double * pVal);
	STDMETHOD(put_X)(/*[in]*/ double newVal);
	STDMETHOD(get_Y)(/*[out, retval]*/ double * pVal);
	STDMETHOD(put_Y)(/*[in]*/ double newVal);
	STDMETHOD(get_Z)(/*[out, retval]*/ double * pVal);
	STDMETHOD(put_Z)(/*[in]*/ double newVal);
	STDMETHOD(GetPoint)(/*[out]*/ double * Coords);
	STDMETHOD(SetPoint)(/*[in]*/ double * Coords);

// ITRiASCSPoint
	HRESULT GetPoint (/*[out]*/ double * X, /*[out]*/ double * Y, /*[out]*/ double * Z);
	HRESULT SetPoint (/*[in]*/ double X, /*[in]*/ double Y, /*[in]*/ double Z);

protected:
	bool m_fIsDirty;
	bool m_fIsInitialized;

private:
	CSCOORD	m_p;
};

/////////////////////////////////////////////////////////////////////////////
// CTRiASCSPointInTarget
class ATL_NO_VTABLE CTRiASCSPointInTarget :
	public CErrSupport<CTRiASCSPointInTarget, &IID__DGMPoint>,
	public CComObjectRootEx<CComObjectThreadModel>,
	public IDispatchImpl<_DGMPoint, &IID__DGMPoint, TLB_TDBGEO_SIGNAT>
{
public:
	CTRiASCSPointInTarget ()
	{
		m_fIsDirty = false;
		m_fIsInitialized = false;
	}
	~CTRiASCSPointInTarget ()
	{
	}

	static CLSID GetObjectCLSID() { return CLSID_TRiASCSPoint; }

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

// _DGMPoint
public:
	STDMETHOD(get_X)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_X)(/*[in]*/ double newVal);
	STDMETHOD(get_Y)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_Y)(/*[in]*/ double newVal);
	STDMETHOD(get_Z)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_Z)(/*[in]*/ double newVal);
	STDMETHOD(GetPoint)(/*[out]*/ double * Coords);
	STDMETHOD(SetPoint)(/*[in]*/ double * Coords);

// ITRiASCSPoint
	HRESULT GetPoint (/*[out]*/ double *X, /*[out]*/ double *Y, /*[out]*/ double *Z);
	HRESULT SetPoint (/*[in]*/ double X, /*[in]*/ double Y, /*[in]*/ double Z);

// ITRiASTransformGeometry
	HRESULT Transform(/* [in]*/ struct CSID csGUID, /*[in]*/ ITRiASCSTransform * pCSTransform);
	HRESULT TransformInverse(/*[in]*/ struct CSID csGUID, /*[in]*/ ITRiASCSTransform * pCSTransform);

protected:
	virtual HRESULT GetData (double *val) = 0;	// Daten aus der zugehörigen Collection holen
	virtual HRESULT SetData (double *val) = 0;	// Daten in die Collection schreiben

protected:
	bool m_fIsDirty;
	bool m_fIsInitialized;
};

/////////////////////////////////////////////////////////////////////////////
// CTRiASCSPointInCol

EXTERN_C const CLSID CLSID_TRiASCSPointInCol;
class DECLSPEC_UUID("CF8A8FF0-3DAF-11d2-8C72-006097A8F384") TRiASCSPointInCol;

class ATL_NO_VTABLE CTRiASCSPointInCol :
	public CComCoClass<CTRiASCSPointInCol, &CLSID_TRiASCSPointInCol>,
	public CTRiASCSPointInTarget
{
public:
	CTRiASCSPointInCol() {}
	~CTRiASCSPointInCol() {}

	DECLARE_ONE_SIZE_PRIVATE_HEAP()
	DECLARE_NO_REGISTRY()

	DECLARE_PROTECT_FINAL_CONSTRUCT()
	DECLARE_GET_CONTROLLING_UNKNOWN()
	void FinalRelease()
	{
		m_TearOff.Release();
	}
	typedef CTRiASCSTearOff<CTRiASCSPointInCol> tearoff_t;
	CComPtr<IUnknown> m_TearOff;

	_COMX_PERF_OBJECTCOUNT_IMPL(CTRiASCSPointInCol)
	BEGIN_COM_MAP(CTRiASCSPointInCol)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(_DGMPoint)
		COM_INTERFACE_ENTRY_CACHED_TEAR_OFF(_ATL_IIDOF(ITRiASTransformGeometry), tearoff_t, m_TearOff.p)
		COM_INTERFACE_ENTRY_CACHED_TEAR_OFF(_ATL_IIDOF(IPersistMemoryGDO), tearoff_t, m_TearOff.p)
		COM_INTERFACE_ENTRY_CACHED_TEAR_OFF(_ATL_IIDOF(IPersistMemory), tearoff_t, m_TearOff.p)
		COM_INTERFACE_ENTRY_CACHED_TEAR_OFF(_ATL_IIDOF(IPersistStreamInit), tearoff_t, m_TearOff.p)
		COM_INTERFACE_ENTRY_CACHED_TEAR_OFF(_ATL_IIDOF(IPersistStream), tearoff_t, m_TearOff.p)
		COM_INTERFACE_ENTRY_CACHED_TEAR_OFF(_ATL_IIDOF(IPersist), tearoff_t, m_TearOff.p)
		COM_INTERFACE_ENTRY_CACHED_TEAR_OFF(_ATL_IIDOF(IPersistMemoryWks), tearoff_t, m_TearOff.p)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

// IPersist
	HRESULT GetClassID(CLSID * pClassID)
	{
		CHECKINPOINTER(pClassID);
		*pClassID = CLSID_TRiASCSPoint;
		return S_OK;
	}

// former ITRiASCSPointInCol
	HRESULT SetCollectionMember (/*[in]*/ _DGMPoints *pIPoints, /*[in]*/ long nIndex);

protected:
	HRESULT GetData (double *val);	// Daten aus der zugehörigen Collection holen
	HRESULT SetData (double *val);	// Daten in die Collection schreiben

private:
	W_DGMPoints m_wParent;
	long m_nIndex;
};

/////////////////////////////////////////////////////////////////////////////
// CTRiASCSPointInCsCoordTarget

EXTERN_C const CLSID CLSID_TRiASCSPointInCsCoordTarget;
class DECLSPEC_UUID("8AE46797-080A-42ff-B21C-A9A47F0D372A") TRiASCSPointInCsCoordTarget;

class ATL_NO_VTABLE CTRiASCSPointInCsCoordTarget :
	public CComCoClass<CTRiASCSPointInCsCoordTarget, &CLSID_TRiASCSPointInCsCoordTarget>,
	public CTRiASCSPointInTarget
{
public:
	CTRiASCSPointInCsCoordTarget () {}
	~CTRiASCSPointInCsCoordTarget () {}

	DECLARE_ONE_SIZE_PRIVATE_HEAP()
	DECLARE_NO_REGISTRY()

	DECLARE_PROTECT_FINAL_CONSTRUCT()
	DECLARE_GET_CONTROLLING_UNKNOWN()
	void FinalRelease()
	{
		m_TearOff.Release();
	}
	typedef CTRiASCSTearOff<CTRiASCSPointInCsCoordTarget> tearoff_t;
	CComPtr<IUnknown> m_TearOff;

	_COMX_PERF_OBJECTCOUNT_IMPL(CTRiASCSPointInCsCoordTarget)
	BEGIN_COM_MAP(CTRiASCSPointInCsCoordTarget)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(_DGMPoint)
		COM_INTERFACE_ENTRY_CACHED_TEAR_OFF(_ATL_IIDOF(ITRiASTransformGeometry), tearoff_t, m_TearOff.p)
		COM_INTERFACE_ENTRY_CACHED_TEAR_OFF(_ATL_IIDOF(IPersistMemoryGDO), tearoff_t, m_TearOff.p)
		COM_INTERFACE_ENTRY_CACHED_TEAR_OFF(_ATL_IIDOF(IPersistMemory), tearoff_t, m_TearOff.p)
		COM_INTERFACE_ENTRY_CACHED_TEAR_OFF(_ATL_IIDOF(IPersistStreamInit), tearoff_t, m_TearOff.p)
		COM_INTERFACE_ENTRY_CACHED_TEAR_OFF(_ATL_IIDOF(IPersistStream), tearoff_t, m_TearOff.p)
		COM_INTERFACE_ENTRY_CACHED_TEAR_OFF(_ATL_IIDOF(IPersist), tearoff_t, m_TearOff.p)
		COM_INTERFACE_ENTRY_CACHED_TEAR_OFF(_ATL_IIDOF(IPersistMemoryWks), tearoff_t, m_TearOff.p)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

// IPersist
	HRESULT GetClassID(CLSID * pClassID)
	{
		CHECKINPOINTER(pClassID);
		*pClassID = CLSID_TRiASCSPoint;
		return S_OK;
	}

// former ITRiASCSPointInCol
	HRESULT SetCollectionMember (_DGMGeometry *pIPoints, CSCOORD *pPt);

protected:
	HRESULT GetData (double *val);	// Daten aus der zugehörigen Collection holen
	HRESULT SetData (double *val);	// Daten in die Collection schreiben

private:
	W_DGMGeometry m_wParent;
	CSCOORD *m_pPt;
};

#endif // !defined(_TRIASCSPOINT_H__0BDC3C1F_503F_11D1_96F0_00A024D6F582__INCLUDED_)
