// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 07.10.1999 14:27:12 
//
// @doc
// @module TRiASGeographicCS.h | Declaration of the <c CTRiASGeographicCS> class

#if !defined(_TRIASGEOGRAPHICCS_H__BE4F3868_626C_4A01_B91D_58677DE7E751__INCLUDED_)
#define _TRIASGEOGRAPHICCS_H__BE4F3868_626C_4A01_B91D_58677DE7E751__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

/////////////////////////////////////////////////////////////////////////////
// CTRiASCS_GCS

const long GCS_VERSION_MINOR_MASK = 0xff;
const long GCS_VERSION_100 = 0x0100L;
const long GCS_VERSION_101 = 0x0101L;
const long LASTKNOWN_GCS_VERSION = GCS_VERSION_101;

class ATL_NO_VTABLE CTRiASGeographicCS : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CTRiASGeographicCS, &CLSID_TRiASCSGCS>,
	public CErrSupport<CTRiASGeographicCS, &IID_ITRiASCSGCS>,
	public CPersistStreamInitImpl<CTRiASGeographicCS, &CLSID_TRiASCSGCS>,
	public IDispatchImpl<ITRiASCSGCS, &IID_ITRiASCSGCS, &LIBID_TRIASCS>,
	public IDispatchImpl<ITRiASCSUIHelper, &IID_ITRiASCSUIHelper, &LIBID_TRIASCS>,
	public ITRiASCSValidate,
	public ITRiASCSTransformInfo
{
private:
	TRIASCSUNITOFANGLE m_UOA;
	TRIASCSGEODETICDATUM m_GD;
	TRIASCSELLIPSOID m_EL;
	TRIASCSPRIMEMERIDIAN m_PM;
	double m_HA;
	double m_HB;
	double m_f;
	long m_lPrec;
	bool m_bDirty;

	HRESULT	PutEllipsoid (TRIASCSELLIPSOID e); 
	HRESULT	InternalInitialize() 
	{
		put_GeodeticDatum (tcsGD_WorldGeodeticSystem1984); 
		put_PrimeMeridian (tcsPM_Greenwich); 
		put_UnitOfAngle (tcsUOA_Radian); 
		m_bDirty = false;
		return S_OK;
	}

public:
	CTRiASGeographicCS() {}

	HRESULT FinalConstruct();
	void FinalRelease();

//	_ATLX_DEBUG_ADDREF_RELEASE_IMPL(CTRiASProjectedCS)
	
	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CTRiASGeographicCS)
	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASGEOGRAPHICCS)
	DECLARE_AGGREGATABLE(CTRiASGeographicCS)

	BEGIN_COM_MAP(CTRiASGeographicCS)
		COM_INTERFACE_ENTRY(ITRiASCSGCS)
		COM_INTERFACE_ENTRY2(IDispatch, ITRiASCSGCS)
		COM_INTERFACE_ENTRY(ITRiASCSValidate)
		COM_INTERFACE_ENTRY(ITRiASCSTransformInfo)
		COM_INTERFACE_ENTRY_CHAIN(CPersistStreamInitImpl_t)
		COM_INTERFACE_ENTRY_CHAIN(CErrSupport_t)
		COM_INTERFACE_ENTRY(ITRiASCSUIHelper)
	END_COM_MAP()

// ITRiASCS_GCS
public:
	STDMETHOD(get_Ellipsoid)(/*[out, retval]*/ TRIASCSELLIPSOID *pVal);
	STDMETHOD(put_Ellipsoid)(/*[in]*/ TRIASCSELLIPSOID newVal);
	STDMETHOD(get_SemiMinorAxis)(/*[out, retval]*/ double *pVal);
	STDMETHOD(get_Flattening)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_Flattening)(/*[in]*/ double newVal);
	STDMETHOD(get_SemiMajorAxis)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_SemiMajorAxis)(/*[in]*/ double newVal);
	STDMETHOD(get_PrimeMeridian)(/*[out, retval]*/ TRIASCSPRIMEMERIDIAN *pVal);
	STDMETHOD(put_PrimeMeridian)(/*[in]*/ TRIASCSPRIMEMERIDIAN newVal);
	STDMETHOD(get_GeodeticDatum)(/*[out, retval]*/ TRIASCSGEODETICDATUM *pVal);
	STDMETHOD(put_GeodeticDatum)(/*[in]*/ TRIASCSGEODETICDATUM newVal);
	STDMETHOD(get_UnitOfAngle)(/*[out, retval]*/ TRIASCSUNITOFANGLE *pVal);
	STDMETHOD(put_UnitOfAngle)(/*[in]*/ TRIASCSUNITOFANGLE newVal);

// ITRiASCSTransformInfo
	STDMETHOD(CanTransform)(/*[in]*/ LONG typeOfTransformation);

// ITRiASCSValidate
	STDMETHOD(RecomputeTransformation)(/*[in,defaultvalue(NULL)]*/ ITRiASCSGCS *pGCS);
	STDMETHOD(IsValid) ();

// ITRiASCSUIHelper
	STDMETHOD(get_InputMask) (/*[in]*/ COORDELEMENT rgElement, /*[out, retval]*/ BSTR *UIMask);
	STDMETHOD(get_Precision) (/*[out, retval]*/ long *pPrec);
	STDMETHOD(put_Precision) (/*[in]*/ long lPrec);
	STDMETHOD(Format) (/*[in]*/ COORDELEMENT rgElement, /*[in]*/ double dValue, /*[out, retval]*/ BSTR *pbstrFormattedElement);
	STDMETHOD(Convert) (/*[in]*/ COORDELEMENT rgElement, /*[in]*/ BSTR bstrFormatted, /*[out, retval]*/ double *pdValue);

// CPersistStreamInit
	HRESULT	OnInitNew ();
	HRESULT LoadData (LPSTREAM pStm, DWORD dwVersion); 
	HRESULT SaveData (LPSTREAM pStm, BOOL bClearDirty); 
	ULONG GetDataSize();

	DWORD GetSignature() { char *s = "CSGS"; return *((DWORD *)s); }
	DWORD GetVersion() { return LASTKNOWN_GCS_VERSION; }
};

#endif // !defined(_TRIASGEOGRAPHICCS_H__BE4F3868_626C_4A01_B91D_58677DE7E751__INCLUDED_)
