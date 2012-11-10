// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 07/27/1998 06:01:55 PM
//
// @doc
// @module TRiASCSOrientedPointGeometry.h | Declaration of the <c CTRiASCSOrientedPointGeometry>
// class

#if !defined(_TRIASCSORIENTEDPOINTGEOMETRY_H__1369BDE6_2567_11D2_9EA2_006008447800__INCLUDED_)
#define _TRIASCSORIENTEDPOINTGEOMETRY_H__1369BDE6_2567_11D2_9EA2_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "TRiASCSTearOff.h"

/////////////////////////////////////////////////////////////////////////////
// CTRiASCSOrientedPointGeometry
class ATL_NO_VTABLE CTRiASCSOrientedPointGeometry :
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CTRiASCSOrientedPointGeometry, &CLSID_TRiASCSOrientedPointGeometry>,
	public CErrSupport<CTRiASCSOrientedPointGeometry, &IID__DGMOrientedPointGeometry>,
	public IDispatchImpl<_DGMOrientedPointGeometry, &IID__DGMOrientedPointGeometry, TLB_TDBGEO_SIGNAT>,
	public IDispatchImpl<ITRiASCSGeometryProperties, &IID_ITRiASCSGeometryProperties, TLB_TDBGEO_SIGNAT>
{
public:
	CTRiASCSOrientedPointGeometry()
	{
		m_fIsDirty = false;
		m_fIsInitialized = false;
		m_fIsOwnerOrig = false;
		m_ptOrigin = NULL;
		m_fIsOwnerOrientation = false;
		m_vecOrientation = NULL;
	}
	~CTRiASCSOrientedPointGeometry()
	{
		ReleaseOrigin();
		ReleaseOrientation();
	}

	DECLARE_ONE_SIZE_PRIVATE_HEAP();
	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASCSORIENTEDPOINTGEOMETRY)

	DECLARE_PROTECT_FINAL_CONSTRUCT()
	DECLARE_GET_CONTROLLING_UNKNOWN()
	void FinalRelease()
	{
		m_TearOff.Release();
	}
	typedef CTRiASCSTearOff2<CTRiASCSOrientedPointGeometry> tearoff_t;
	CComPtr<IUnknown> m_TearOff;

	BEGIN_COM_MAP(CTRiASCSOrientedPointGeometry)
		COM_INTERFACE_ENTRY(_DGMOrientedPointGeometry)
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
		 * pClassID = CLSID_TRiASCSOrientedPointGeometry;
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

// ITRiASCloneGeometry
	STDMETHODIMP Clone(/*[out, retval]*/ IDispatch * * ppIClonedObj);

// _DGMGeometry
	STDMETHOD(get_Type)(BSTR * typeName);

// _DGMPointGeometry
	STDMETHOD(get_Origin)(_DGMPoint * * returnValue);
	STDMETHOD(putref_Origin)(_DGMPoint * newValue);

// _DGMOrientedPointGeometry
public:
// Properties
	STDMETHOD(get_Orientation)(_DGMVector * * returnValue);
	STDMETHOD(putref_Orientation)(_DGMVector * newValue);

//ITRiASTransformGeometry
	HRESULT Transform(/* [in]*/ struct CSID csGUID, /*[in]*/ ITRiASCSTransform * pCSTransform);
	HRESULT TransformInverse(/*[in]*/ struct CSID csGUID, /*[in]*/ ITRiASCSTransform * pCSTransform);

// Methods
protected:
	void ReleaseOrigin()
	{
		if (m_fIsOwnerOrig)
		{
				ASSERT(NULL != m_ptOrigin);
			m_ptOrigin -> Release();
		}
		m_ptOrigin = NULL;
		m_fIsOwnerOrig = false;
	}
	void PutOrigin(_DGMPoint * newVal, bool owner)
	{
		ReleaseOrigin();
		m_ptOrigin = newVal;
		if (NULL != m_ptOrigin)
		{
			m_fIsOwnerOrig = owner;
			// JG990201
			if (m_fIsOwnerOrig)
				m_ptOrigin -> AddRef();
		}
	}

	void ReleaseOrientation()
	{
		if (m_fIsOwnerOrientation)
		{
				ASSERT(NULL != m_vecOrientation);
			m_vecOrientation -> Release();
		}
		m_vecOrientation = NULL;
		m_fIsOwnerOrientation = false;
	}
	void PutOrientation(_DGMVector * newVal, bool owner)
	{
		ReleaseOrientation();
		m_vecOrientation = newVal;
		if (NULL != m_vecOrientation)
		{
			m_fIsOwnerOrientation = owner;
			// JG990201
			if (m_fIsOwnerOrientation)
				m_vecOrientation -> AddRef();
		}
	}

protected:
	bool m_fIsDirty;
	bool m_fIsInitialized;

private:
	bool m_fIsOwnerOrig;
	bool m_fIsOwnerOrientation;

	_DGMPoint *m_ptOrigin;
	_DGMVector *m_vecOrientation;
};

#endif // !defined(_TRIASCSORIENTEDPOINTGEOMETRY_H__1369BDE6_2567_11D2_9EA2_006008447800__INCLUDED_)
