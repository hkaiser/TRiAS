///////////////////////////////////////////////////////////////////////////
// @doc
// @module TRiASCSTextPointGeometry.h | Declaration of the <c CTRiASCSTextPointGeometry>
// class

#if !defined(_TRIASCSTEXTPOINTGEOMETRY_H__0F5171D5_AF43_11D1_A06E_0060975566B4__INCLUDED_)
#define _TRIASCSTEXTPOINTGEOMETRY_H__0F5171D5_AF43_11D1_A06E_0060975566B4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "TRiASCSTearOff.h"
#include "TRiASCSPoint.h"
#include "TRiASCSVector.h"

/////////////////////////////////////////////////////////////////////////////
// CTRiASCSTextPointGeometry
class ATL_NO_VTABLE CTRiASCSTextPointGeometry :
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CTRiASCSTextPointGeometry, & CLSID_TRiASCSTextPointGeometry>,
	public CErrSupport<CTRiASCSTextPointGeometry, & IID__DGMTextPointGeometry>,
	public IDispatchImpl<_DGMTextPointGeometry, & IID__DGMTextPointGeometry, TLB_TDBGEO_SIGNAT>,
	public IDispatchImpl<ITRiASCSGeometryProperties, & IID_ITRiASCSGeometryProperties, TLB_TDBGEO_SIGNAT>
{
	typedef CComCoClass<CTRiASCSTextPointGeometry, & IID__DGMTextPointGeometry> base_t;

	// Format-Konstanten:
	//	gmfRichText		0
	//	gmfUnformatted	1

	// Alignment-Konstanten:
	//	gmaCenterCenter	0	Der Ursprungspunkt befindet sich in der Mitte
	//						des Rich-Texts.
	//	gmaCenterLeft	1	Der Rich-Text ist vertikal und links vom
	//						Ursprungspunkt zentriert.
	//	gmaCenterRight	2	Der Rich-Text ist vertikal und rechts vom
	//						Ursprungspunkt zentriert.
	//	gmaTopCenter	4	Der Rich-Text ist horizontal und oberhalb des
	//						Ursprungspunkts zentriert.
	//	gmaTopLeft		5	Der Rich-Text befindet sich links oberhalb des
	//						Ursprungspunkts.
	//	gmaTopRight		6	Der Rich-Text befindet sich rechts oberhalb des
	//						Ursprungspunkts.
	//	gmaBottomCenter	8	Der Rich-Text ist horizontal und unterhalb des
	//						Ursprungspunkts zentriert.
	//	gmaBottomLeft	9	Der Rich-Text befindet sich links unterhalb des
	//						Ursprungspunkts.
	//	gmaBottomRight	10	Der Rich-Text befindet sich rechts unterhalb des
	//						Ursprungspunkts.
public:
	CTRiASCSTextPointGeometry()
	{
		m_fIsDirty = false;
		m_fIsInitialized = false;
		m_fIsOwnerNormal = false;

		m_dRotation = 0.0;
		m_lAlignment = 0L;		// gmaCenterCenter
		m_iFormat = 1;			// gmfUnformatted

		m_vecNormal = NULL;

		memset (&m_ptOrig, 0, sizeof(CSCOORD));
	}
	~CTRiASCSTextPointGeometry()
	{
		ReleaseNormal();
	}

	DECLARE_ONE_SIZE_PRIVATE_HEAP();
	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASCSTEXTPOINTGEOMETRY)

	DECLARE_PROTECT_FINAL_CONSTRUCT()
	DECLARE_GET_CONTROLLING_UNKNOWN()
	void FinalRelease()
	{
		m_TearOff.Release();
	}
	typedef CTRiASCSTearOff2<CTRiASCSTextPointGeometry> tearoff_t;
	CComPtr<IUnknown> m_TearOff;

	_COMX_PERF_OBJECTCOUNT_IMPL(CTRiASCSTextPointGeometry)
	BEGIN_COM_MAP(CTRiASCSTextPointGeometry)
		COM_INTERFACE_ENTRY(_DGMTextPointGeometry)
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
		 * pClassID = CLSID_TRiASCSTextPointGeometry;
		return S_OK;
	}

// IPersistStream
	HRESULT IsDirty();
	HRESULT Load(LPSTREAM pStm);
	HRESULT Save(LPSTREAM pStm, BOOL fClearDirty);
	HRESULT GetSizeMax(ULARGE_INTEGER * pcbSize);

// IPersistStreamInit
	HRESULT InitNew();

	HRESULT DoLoad(void * pvMem, ULONG cbSize, bool bLoadGDO);
	HRESULT DoSave(void * pvMem, BOOL fClearDirty, ULONG cbSize, bool bSaveGDO);

// IPersistMemory
	HRESULT Load(void * pvMem, ULONG cbSize);
	HRESULT Save(void * pvMem, BOOL fClearDirty, ULONG cbSize);
	HRESULT GetSizeMax(ULONG * pcbSize);

// IPersistMemoryGDO
	HRESULT LoadGDO(VOID * pMem, ULONG cbSize);
	HRESULT SaveGDO(VOID * pMem, BOOL fClearDirty, ULONG cbSize);

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
	STDMETHOD(get_Origin)(_DGMPoint * * returnValue);
	STDMETHOD(putref_Origin)(_DGMPoint * returnValue);

// _DGMTextPointGeometry
public:
// Properties
	STDMETHOD(get_Rotation)(double * returnValue);
	STDMETHOD(put_Rotation)(double returnValue);
	STDMETHOD(get_Alignment)(long * returnValue);
	STDMETHOD(put_Alignment)(long returnValue);
	STDMETHOD(get_RichText)(BSTR * text);
	STDMETHOD(put_RichText)(BSTR text);
	STDMETHOD(get_text)(BSTR * text);
	STDMETHOD(put_text)(BSTR text);
	STDMETHOD(get_Format)(short * returnValue);

	STDMETHOD(get_Normal)(_DGMVector * * returnValue);
	STDMETHOD(putref_Normal)(_DGMVector * returnValue);

// ITRiASTransformGeometry
	HRESULT Transform(/* [in]*/ struct CSID csGUID, /*[in]*/ ITRiASCSTransform * pCSTransform);
	HRESULT TransformInverse(/*[in]*/ struct CSID csGUID, /*[in]*/ ITRiASCSTransform * pCSTransform);

// ITRiASCloneGeometry
	STDMETHOD(Clone)(/*[out, retval]*/ IDispatch * * ppIClonedObj);

// Methods
protected:
	void ReleaseNormal()
	{
		if (m_fIsOwnerNormal)
		{
				ASSERT(NULL != m_vecNormal);
			m_vecNormal -> Release();
		}
		m_vecNormal = NULL;
		m_fIsOwnerNormal = false;
	}
	void PutNormal(_DGMVector * newVal, bool owner)
	{
		ReleaseNormal();
		m_vecNormal = newVal;
		if (NULL != m_vecNormal)
		{
			m_fIsOwnerNormal = owner;
			// JG990201 AddRef, wenn's unseres ist
			if (m_fIsOwnerNormal)
				m_vecNormal -> AddRef();
		}
	}

protected:
	bool m_fIsDirty;
	bool m_fIsInitialized;

	double m_dRotation;
	long m_lAlignment;
	CComBSTR m_bstrText;
	int m_iFormat;

	CSCOORD m_ptOrig;

private:
	bool m_fIsOwnerNormal;
	_DGMVector * m_vecNormal;
};

#endif // !defined(_TRIASCSTEXTPOINTGEOMETRY_H__0F5171D5_AF43_11D1_A06E_0060975566B4__INCLUDED_)
