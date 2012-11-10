// @doc
// @module TRiASCSPoints.h | Definition of the CTRiASCSPoints class
//

#if !defined(_TRIASCSPOINTS_H__0BDC3C22_503F_11D1_96F0_00A024D6F582__INCLUDED_)
#define _TRIASCSPOINTS_H__0BDC3C22_503F_11D1_96F0_00A024D6F582__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "TRiASCSTearOff.h"
#include "TRiASCSPoint.h"
#include "coordfield.h"

/////////////////////////////////////////////////////////////////////////////
// CTRiASCSPoints

class ATL_NO_VTABLE CTRiASCSPoints :
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CTRiASCSPoints, &CLSID_TRiASCSPoints>,
	public CErrSupport<CTRiASCSPoints, &IID_ITRiASSimplePoints>,
	public ITRiASCSMBRAccess,
	public IDispatchImpl<ITRiASSimplePoints, &IID_ITRiASSimplePoints, TLB_TDBGEO_SIGNAT>,
	public IDispatchImpl<ITRiASCloneGeometry, &IID_ITRiASCloneGeometry, TLB_TDBGEO_SIGNAT>
{
public:
	CTRiASCSPoints()
	{
		m_fIsDirty = false;
		m_fIsInitialized = false;
	}

	DECLARE_ONE_SIZE_PRIVATE_HEAP();
	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASCSPOINTS)

	DECLARE_PROTECT_FINAL_CONSTRUCT()
	DECLARE_GET_CONTROLLING_UNKNOWN()
	void FinalRelease()
	{
		m_TearOff.Release();
	}
	typedef CTRiASCSTearOff2<CTRiASCSPoints> tearoff_t;
	CComPtr<IUnknown> m_TearOff;

	_COMX_PERF_OBJECTCOUNT_IMPL(CTRiASCSPoints)
	BEGIN_COM_MAP(CTRiASCSPoints)
		COM_INTERFACE_ENTRY(ITRiASSimplePoints)
		COM_INTERFACE_ENTRY2(_DGMPoints, ITRiASSimplePoints)
		COM_INTERFACE_ENTRY2(IDispatch, _DGMPoints)
		COM_INTERFACE_ENTRY_CACHED_TEAR_OFF(_ATL_IIDOF(ITRiASTransformGeometry), tearoff_t, m_TearOff.p)
		COM_INTERFACE_ENTRY_CACHED_TEAR_OFF(_ATL_IIDOF(IPersistMemoryGDO), tearoff_t, m_TearOff.p)
		COM_INTERFACE_ENTRY_CACHED_TEAR_OFF(_ATL_IIDOF(IPersistMemory), tearoff_t, m_TearOff.p)
		COM_INTERFACE_ENTRY_CACHED_TEAR_OFF(_ATL_IIDOF(IPersistStreamInit), tearoff_t, m_TearOff.p)
		COM_INTERFACE_ENTRY_CACHED_TEAR_OFF(_ATL_IIDOF(IPersistStream), tearoff_t, m_TearOff.p)
		COM_INTERFACE_ENTRY_CACHED_TEAR_OFF(_ATL_IIDOF(IPersist), tearoff_t, m_TearOff.p)
		COM_INTERFACE_ENTRY_CACHED_TEAR_OFF(_ATL_IIDOF(IPersistMemoryWks), tearoff_t, m_TearOff.p)
		COM_INTERFACE_ENTRY(ITRiASCloneGeometry)
		COM_INTERFACE_ENTRY(ITRiASCSMBRAccess)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

// ISupportsErrorInfo
//	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IPersist
	HRESULT GetClassID(CLSID * pClassID)
	{
		CHECKINPOINTER(pClassID);
		 * pClassID = CLSID_TRiASCSPoints;
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

// _DGMPoints
public:
	STDMETHOD(get_Count)(/*[out, retval]*/ long * pVal);
	STDMETHOD(get_NewEnum)(/*[out, retval]*/ IUnknown * * ppIEnum);

	STDMETHOD(Item)(/*[in]*/ VARIANT Index, /*[out, retval]*/ _DGMPoint * * Point);
	STDMETHOD(Add)(/*[in]*/ _DGMPoint * Point, /*[in, optional]*/ VARIANT Index);
	STDMETHOD(Remove)(/*[in]*/ VARIANT Index);
	STDMETHOD(GetPoint)(/*[in]*/ long Index, /*[out]*/ double * Point);
	STDMETHOD(SetPoint)(/*[in]*/ long Index, /*[in]*/ double * Point);

// ITRiASSimplePoints
	STDMETHOD(GetPoints)(/*[in]*/ ULONG Index, /*[in]*/ ULONG nCoords, /*[in, out, size_is(3*nCoords)]*/ double *Points);

// ITRiASCSMBRAccess
	STDMETHOD(get_Envelope)(/* [retval][out] */ ITRiASSimpleRectangle * * Rect);

// ITRiASTransformGeometry
	HRESULT Transform(/* [in]*/ struct CSID csGUID, /*[in]*/ ITRiASCSTransform * pCSTransform);
	HRESULT TransformInverse(/*[in]*/ struct CSID csGUID, /*[in]*/ ITRiASCSTransform * pCSTransform);

// ITRiASCloneGeometry
	STDMETHODIMP Clone(/*[out, retval]*/ IDispatch * * ppIClonedObj);

protected:
	bool m_fIsDirty;
	bool m_fIsInitialized;

	CCoordField	clCoords;

private:
// Hilfsfunktionen
	HRESULT CreateRect(CSCOORD & org, CSCOORD & sec, ITRiASSimpleRectangle * * pRect);
};

#endif // !defined(_TRIASCSPOINTS_H__0BDC3C22_503F_11D1_96F0_00A024D6F582__INCLUDED_)
