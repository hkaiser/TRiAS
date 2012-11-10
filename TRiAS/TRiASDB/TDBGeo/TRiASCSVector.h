// $Header: /TRiAS/TRiASDB/TDBGeo/TRiASCSVector.h 1	 15.06.98 21:26 Hartmut Kaiser $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 06/11/1998 11:27:15 PM
//
// @doc
// @module TRiASCSVector.h | Description here

#if !defined(_TRIASCSVECTOR_H__BC145189_013F_11D2_864C_00600875138A__INCLUDED_)
#define _TRIASCSVECTOR_H__BC145189_013F_11D2_864C_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "TRiASCSTearOff.h"

/////////////////////////////////////////////////////////////////////////////
// CTRiASCSVector
class ATL_NO_VTABLE CTRiASCSVector :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CTRiASCSVector, &CLSID_TRiASCSVector>,
	public CErrSupport<CTRiASCSVector, &IID__DGMVector>,
	public IDispatchImpl<ITRiASCloneGeometry, &IID_ITRiASCloneGeometry, TLB_TDBGEO_SIGNAT>,
	public IDispatchImpl<_DGMVector, & IID__DGMVector, TLB_TDBGEO_SIGNAT>
{
public:
	CTRiASCSVector() :
		m_fIsDirty(false), m_fIsInitialized(false),
		m_dX(0.0), m_dY(0.0), m_dZ(1.0)
	{
	}
	~CTRiASCSVector()
	{
	}

//	DECLARE_ONE_SIZE_PRIVATE_HEAP()
	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASCSVECTOR)

	DECLARE_PROTECT_FINAL_CONSTRUCT()
	DECLARE_GET_CONTROLLING_UNKNOWN()
	void FinalRelease()
	{
		m_TearOff.Release();
	}
	typedef CTRiASCSTearOff2<CTRiASCSVector> tearoff_t;
	CComPtr<IUnknown> m_TearOff;

	_COMX_PERF_OBJECTCOUNT_IMPL(CTRiASCSVector)
	BEGIN_COM_MAP(CTRiASCSVector)
		COM_INTERFACE_ENTRY(_DGMVector)
		COM_INTERFACE_ENTRY2(IDispatch, _DGMVector)
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
		 * pClassID = CLSID_TRiASCSVector;
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

// ITRiASTransformGeometry
	HRESULT Transform (/* [in]*/ struct CSID csGUID, /*[in]*/ ITRiASCSTransform * pCSTransform)
	{
		return E_NOTIMPL;
	}
	HRESULT TransformInverse (/*[in]*/ struct CSID csGUID, /*[in]*/ ITRiASCSTransform * pCSTransform)
	{
		return E_NOTIMPL;
	}

// _DGMVector
public:
	STDMETHOD(get_I)(/*[out, retval]*/ double * pVal);
	STDMETHOD(put_I)(/*[in]*/ double newVal);
	STDMETHOD(get_J)(/*[out, retval]*/ double * pVal);
	STDMETHOD(put_J)(/*[in]*/ double newVal);
	STDMETHOD(get_K)(/*[out, retval]*/ double * pVal);
	STDMETHOD(put_K)(/*[in]*/ double newVal);
	STDMETHOD(GetVector)(/*[out]*/ double * Coords);
	STDMETHOD(SetVector)(/*[in]*/ double * Coords);

// ITRiASCSVector
	STDMETHOD(GetVector)(/*[out]*/ double * X, /*[out]*/ double * Y, /*[out]*/ double * Z);
	STDMETHOD(SetVector)(/*[in]*/ double X, /*[in]*/ double Y, /*[in]*/ double Z);

// ITRiASCloneGeometry
	STDMETHOD(Clone)(/*[out, retval]*/ IDispatch * * ppIClonedObj);

protected:
	bool m_fIsDirty;
	bool m_fIsInitialized;

	double m_dX;
	double m_dY;
	double m_dZ;
};

#endif // !defined(_TRIASCSVECTOR_H__BC145189_013F_11D2_864C_00600875138A__INCLUDED_)
