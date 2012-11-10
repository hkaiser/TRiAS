// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 25.01.2000 20:42:33 
//
// @doc
// @module TRiASCSGeometryCollection.h | Declaration of the <c CTRiASCSGeometryCollection> class

#if !defined(_TRIASCSGEOMETRYCOLLECTION_H__68035FEA_2C5E_46BE_9518_0D19106FCA6D__INCLUDED_)
#define _TRIASCSGEOMETRYCOLLECTION_H__68035FEA_2C5E_46BE_9518_0D19106FCA6D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "TRiASCSTearOff.h"

// {28A55900-A2FB-11d1-A052-0060975566B4}
extern "C" const IID __declspec(selectany) IID_IEnumDispatch =
{0x28a55900, 0xa2fb, 0x11d1, {0xa0, 0x52, 0x00, 0x60, 0x97, 0x55, 0x66, 0xb4}};

// Enumerator soll AddItem/RemoveItem über Index haben (s. iterenum.h)
typedef IEnum2<WDispatch>IEnumDispatch;

///////////////////////////////////////////////////////////////////////////////
// Die folgenden typedef's verwenden die in <ospace/com/iterenum.h> definierten Templates,
// um einen Enumerator zu definieren, der neben der Standardfunktionalität (Reset, Skip, Clone etc.)
// zusätzlich die Möglichkeit bietet, schnell an einzelne Einträge heranzukommen (hier über den
// Bezeichner des ViewItems, s.a. 'bool operator< (const CComBSTR &, const CComBSTR &)' ).

// Helperklasse zur Verpackung des CLSID's als Klasse
DefineEnumIIDWrapper2(WDispatch, IID_IEnumDispatch);		// CIID_WDispatchEnum

// der eigentliche Enumerator
typedef vector<WDispatch>CEnumDispatchVector;	// unterliegender Vector
typedef __Enumerator<WDispatch, CIID_WDispatchEnum, CEnumDispatchVector,
			__EnumeratorBase2<WDispatch, CEnumDispatchVector, IEnumDispatch> >
				TEnumWDispatch;

// Wrapper für Interface, über welches der definierte Enumerator ansprechbar ist
typedef __Interface<IEnumDispatch, CIID_WDispatchEnum, CComPtr<IEnumDispatch> > WEnumWDispatch;

/////////////////////////////////////////////////////////////////////////////
// CTRiASCSGeometryCollection
class ATL_NO_VTABLE CTRiASCSGeometryCollection :
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CTRiASCSGeometryCollection, &CLSID_TRiASCSGeometryCollection>,
	public CErrSupport<CTRiASCSGeometryCollection, &IID__DGMGeometryCollection>,
	public IDispatchImpl<_DGMGeometryCollection, &IID__DGMGeometryCollection, TLB_TDBGEO_SIGNAT>,
	public IDispatchImpl<ITRiASCSGeometryProperties, &IID_ITRiASCSGeometryProperties, TLB_TDBGEO_SIGNAT>
{
public:
	CTRiASCSGeometryCollection()
	{
		m_fIsDirty = false;
		m_fIsInitialized = false;
	}

	DECLARE_ONE_SIZE_PRIVATE_HEAP();
	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASCSGEOMETRYCOLLECTION)

	DECLARE_PROTECT_FINAL_CONSTRUCT()
	DECLARE_GET_CONTROLLING_UNKNOWN()
	void FinalRelease()
	{
		m_TearOff.Release();
	}
	typedef CTRiASCSTearOff2<CTRiASCSGeometryCollection> tearoff_t;
	CComPtr<IUnknown> m_TearOff;

	_COMX_PERF_OBJECTCOUNT_IMPL(CTRiASCSGeometryCollection)
	BEGIN_COM_MAP(CTRiASCSGeometryCollection)
		COM_INTERFACE_ENTRY(_DGMGeometryCollection)
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

	HRESULT FinalConstruct()
	{
		return CreateNewEnum (m_Enum.ppi());
	}

	HRESULT CreateNewEnum (IEnum2<WDispatch>* * ppIEnum)
	{
		ATLTRY(* ppIEnum = new TEnumWDispatch());
		return (NULL == * ppIEnum) ? E_OUTOFMEMORY : S_OK;
	}
	HRESULT InitEnum (IEnum2<WDispatch>* pTarget)
	{
		return pTarget -> Clone (m_Enum.ppi());
	}

public:
/////////////////////////////////////////////////////////////////////////////
// IPersist
	HRESULT GetClassID(CLSID * pClassID)
	{
		CHECKINPOINTER(pClassID);
		*pClassID = CLSID_TRiASCSGeometryCollection;
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
	HRESULT LoadGDO(VOID * pMem, ULONG cbSize);
	HRESULT SaveGDO(VOID * pMem, BOOL fClearDirty, ULONG cbSize);

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

// _DGMGeometryCollection
	STDMETHOD(get_Count)(/*[out, retval]*/ long * pVal);
	STDMETHOD(get_NewEnum)(/*[out, retval]*/ IUnknown * * ppIEnum);

	STDMETHOD(Item)(/*[in]*/ VARIANT Index, /*[out, retval]*/ IDispatch * * Point);
	STDMETHOD(Add)(/*[in]*/ IDispatch * Point, /*[in, optional]*/ VARIANT Index);
	STDMETHOD(Remove)(/*[in]*/ VARIANT Index);

// ITRiASTransformGeometry
	HRESULT Transform(/* [in]*/ struct CSID csGUID, /*[in]*/ ITRiASCSTransform * pCSTransform);
	HRESULT TransformInverse(/*[in]*/ struct CSID csGUID, /*[in]*/ ITRiASCSTransform * pCSTransform);

// ITRiASCloneGeometry
	STDMETHODIMP Clone(/*[out, retval]*/ IDispatch * * ppIClonedObj);

protected:
	bool m_fIsDirty;
	bool m_fIsInitialized;
	WEnumWDispatch m_Enum;
};

#endif // !defined(_TRIASCSGEOMETRYCOLLECTION_H__68035FEA_2C5E_46BE_9518_0D19106FCA6D__INCLUDED_)
