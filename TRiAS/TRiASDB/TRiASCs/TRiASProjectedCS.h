// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 07.10.1999 14:27:02 
//
// @doc
// @module TRiASProjectedCS.h | Declaration of the <c CTRiASProjectedCS> class

#if !defined(_TRIASPROJECTEDCS_H__5A1FC394_6D2F_48AC_A89B_D838DDED52C1__INCLUDED_)
#define _TRIASPROJECTEDCS_H__5A1FC394_6D2F_48AC_A89B_D838DDED52C1__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "libctf/libctf.h"

/////////////////////////////////////////////////////////////////////////////
// CTRiASCS_PCS

#define	TCSPA_PARAMETER_INRANGE(idx) ((idx) >= 0 && (idx) < tcsPP_SizeOfParameterSet)

// persisted versions
const long PCS_VERSION_100 = 0x0100L;
const long PCS_VERSION_101 = 0x0101L;
const long PCS_VERSION_MINOR_MASK = 0xff;

#if defined(_USE_OGC_COMPATIBILITY)
const long LASTKNOWN_PCS_VERSION = PCS_VERSION_101;
#else
const long LASTKNOWN_PCS_VERSION = PCS_VERSION_100;
#endif // defined(_USE_OGC_COMPATIBILITY)

///////////////////////////////////////////////////////////////////////////////
// 
class ATL_NO_VTABLE CTRiASProjectedCS : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CTRiASProjectedCS, &CLSID_TRiASCSPCS>,
	public CErrSupport<CTRiASProjectedCS, &IID_ITRiASCSPCS>,
	public CPersistStreamInitImpl<CTRiASProjectedCS, &CLSID_TRiASCSPCS>,
	public IDispatchImpl<ITRiASCSPCS, &IID_ITRiASCSPCS, &LIBID_TRIASCS>,
	public IDispatchImpl<ITRiASCSUIHelper, &IID_ITRiASCSUIHelper, &LIBID_TRIASCS>,
	public ITRiASCSTransformData,
	public ITRiASCSTransformInfo,
#if defined(_USE_OGC_COMPATIBILITY)
	public ISpatialReference,
#endif // defined(_USE_OGC_COMPATIBILITY)
	public ITRiASCSValidate
{
private:
	bool m_bDirty;
	TRIASCSPROJECTIONALGORITHM m_algorithm;
	TRIASCSUNITOFLENGTH m_UOL;
	CTransform *m_pTransform;
	double m_parOfProjection[tcsPP_SizeOfParameterSet];

	HRESULT SetParameters();
	HRESULT InternalInitialize() 
	{
		put_ProjectionAlgorithm (tcsPA_CylindricEquirectangular); 
		put_UnitOfLength (tcsUOL_Metre); 
		memset (m_parOfProjection, PADCHAR, sizeof(m_parOfProjection)); 
		put_ProjectionParameter (tcsPP_CylindricEquirectangular_FalseEasting, 0); 
		put_ProjectionParameter (tcsPP_CylindricEquirectangular_FalseNorthing, 0); 
		put_ProjectionParameter (tcsPP_CylindricEquirectangular_LatitudeOfNaturalOrigin, 0); 
		put_ProjectionParameter (tcsPP_CylindricEquirectangular_LongitudeOfNaturalOrigin, 0); 
		return S_OK;
	}

public:
	CTRiASProjectedCS() 
		: m_pTransform(NULL), m_bDirty(false), m_algorithm (tcsPA_Undefined), m_UOL (tcsUOL_Undefined) 
	{
		memset (m_parOfProjection, PADCHAR, sizeof(m_parOfProjection)); 
	}
	~CTRiASProjectedCS() 
	{
		_ASSERTE(NULL == m_pTransform);
	}

	HRESULT FinalConstruct();
	void FinalRelease();

//	_ATLX_DEBUG_ADDREF_RELEASE_IMPL(CTRiASProjectedCS)

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CTRiASProjectedCS)
	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASPROJECTEDCS)
	DECLARE_AGGREGATABLE(CTRiASProjectedCS)
	DECLARE_GET_CONTROLLING_UNKNOWN()

	BEGIN_COM_MAP(CTRiASProjectedCS)
		COM_INTERFACE_ENTRY(ITRiASCSTransformData)	// meist gebrauchtes Interface
		COM_INTERFACE_ENTRY(ITRiASCSPCS)
		COM_INTERFACE_ENTRY2(IDispatch, ITRiASCSPCS)
		COM_INTERFACE_ENTRY(ITRiASCSValidate)
		COM_INTERFACE_ENTRY(ITRiASCSTransformInfo)
		COM_INTERFACE_ENTRY_CHAIN(CPersistStreamInitImpl_t)
		COM_INTERFACE_ENTRY_CHAIN(CErrSupport_t)
		COM_INTERFACE_ENTRY(ITRiASCSUIHelper)
#if defined(_USE_OGC_COMPATIBILITY)
		COM_INTERFACE_ENTRY(ISpatialReference)
#endif // defined(_USE_OGC_COMPATIBILITY)
	END_COM_MAP()

public:
// ITRiASCS_PCS
	STDMETHOD(get_ProjectionParameter)(TRIASCSPROJECTIONPARAMETER par, /*[out, retval]*/ double *pVal);
	STDMETHOD(put_ProjectionParameter)(TRIASCSPROJECTIONPARAMETER par, /*[in]*/ double newVal);
	STDMETHOD(get_ProjectionParameters)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_ProjectionParameters)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_ProjectionAlgorithm)(/*[out, retval]*/ TRIASCSPROJECTIONALGORITHM *pVal);
	STDMETHOD(put_ProjectionAlgorithm)(/*[in]*/ TRIASCSPROJECTIONALGORITHM newVal);
	STDMETHOD(get_UnitOfLength)(/*[out, retval]*/ TRIASCSUNITOFLENGTH *pVal);
	STDMETHOD(put_UnitOfLength)(/*[in]*/ TRIASCSUNITOFLENGTH newVal);

// ITRiASTransformData
	STDMETHOD(Transform)(/*[in]*/ long nCoords, /*[in,out,size_is(nCoords)]*/ CSCOORD* pCoords); 
	STDMETHOD(TransformInverse)(/*[in]*/ long nCoords, /*[in,out,size_is(nCoords)]*/ CSCOORD* pCoords); 

// ITRiASCSValidate
	STDMETHOD(IsValid) ();
	STDMETHOD(RecomputeTransformation)(/*[in,defaultvalue(NULL)]*/ ITRiASCSGCS *pGCS);

// ITRiASCSTransformInfo
	STDMETHOD(CanTransform)(/*[in]*/ LONG typeOfTransformation); 

// ITRiASCSUIHelper
	STDMETHOD(get_InputMask) (/*[in]*/ COORDELEMENT rgElement, /*[out, retval]*/ BSTR *UIMask);
	STDMETHOD(get_Precision) (/*[out, retval]*/ long *pPrec);
	STDMETHOD(put_Precision) (/*[in]*/ long lPrec);
	STDMETHOD(Format) (/*[in]*/ COORDELEMENT rgElement, /*[in]*/ double dValue, /*[out, retval]*/ BSTR *pbstrFormattedElement);
	STDMETHOD(Convert) (/*[in]*/ COORDELEMENT rgElement, /*[in]*/ BSTR bstrFormatted, /*[out, retval]*/ double *pdValue);

#if defined(_USE_OGC_COMPATIBILITY)
// ISpatialReference
	STDMETHODIMP get_Name(BSTR *pbstrName);
	STDMETHODIMP put_Name(BSTR bstrName);
	STDMETHODIMP get_Authority(BSTR *pbstrAuth);
	STDMETHODIMP put_Authority(BSTR bstrAuth);
	STDMETHODIMP get_Code(long *plCode);
	STDMETHODIMP put_Code(long lCode);
	STDMETHODIMP get_Alias(BSTR *pbstrAlias);
	STDMETHODIMP put_Alias(BSTR bstrAlias);
	STDMETHODIMP get_Abbreviation(BSTR *pbstrAbbrev);
	STDMETHODIMP put_Abbreviation(BSTR bstrAbbrev);
	STDMETHODIMP get_Remarks(BSTR *pbstrRemarks);
	STDMETHODIMP put_Remarks(BSTR bstrRemarks);
	STDMETHODIMP get_WellKnownText(BSTR *pbstrWkt);
#endif // defined(_USE_OGC_COMPATIBILITY)

// CPersistStreamInitImpl
	HRESULT	OnInitNew ();
	HRESULT LoadData (LPSTREAM pStm, DWORD dwVersion); 
	HRESULT SaveData (LPSTREAM pStm, BOOL bClearDirty); 
	ULONG	GetDataSize ();

	DWORD GetSignature () { const char *s = "CSPS"; return *((DWORD *)s); }
	DWORD GetVersion () { return LASTKNOWN_PCS_VERSION; }
};

#endif // !defined(_TRIASPROJECTEDCS_H__5A1FC394_6D2F_48AC_A89B_D838DDED52C1__INCLUDED_)
