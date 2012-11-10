// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 07.10.1999 11:31:25 
//
// @doc
// @module TRiASCoordTransform.h | Declaration of the <c CTRiASCoordTransform> class

#if !defined(_TRIASCOORDTRANSFORM_H__4C94758F_D85C_417F_9696_3806F1CE1E5A__INCLUDED_)
#define _TRIASCOORDTRANSFORM_H__4C94758F_D85C_417F_9696_3806F1CE1E5A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <Atl/Ciethis.h>

#include "libctf/libctf.h"

inline void CopyCSGUID(GUID &g, CSID const& cg)  
{
	_ASSERTE(sizeof(g)==sizeof(cg));
	memcpy (&g, &cg, sizeof(g));
}

typedef struct _G {
	union { GUID	g; CSID	c; };
	_G(GUID _g) { g = _g; }
	_G(CSID _c) { c = _c; }
} _G;

class ATL_NO_VTABLE CTRiASCoordTransform : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CTRiASCoordTransform, &CLSID_TRiASCSTransform>,
	public CErrSupport<CTRiASCoordTransform, &IID_ITRiASCSTransform>,
	public IDispatchImpl<ITRiASCSTransform, &IID_ITRiASCSTransform, &LIBID_TRIASCS>,
	public IDispatchImpl<ITRiASCSEvents, &IID_ITRiASCSEvents, &LIBID_TRIASCS>,
	public ITRiASRawCoordTransform
{
private:
///////////////////////////////////////////////////////////////////////
// Wenn (m_bDTransIntern == true), wird Datumstransformation nur im Eingangssystem 
// durchgeführt. Die Koeffizienten des Ausgangssystems werden in das Eingangssystem
// eingerechnet
	BOOL m_bDTransIntern;
	LPDispatchMap m_mapOfCS;
	WTRiASCS m_pOutputCS;
	DWORD m_cookOutput;

	CSCOORD m_goodEnv[2];
	WTRiASCS m_WGS84;
	_G m_guidWGS84;

	HRESULT	RecomputeTransformation(WTRiASCS &pd);
	HRESULT CheckDatum (WTRiASCS& csIn, WTRiASCS& csOut); 
	HRESULT	RecomputePath (WTRiASCS& csIn, WTRiASCS& csOut, bool bTransformDatum); 
	HRESULT	RemoveOutput();
	HRESULT	RemoveInput (LPDispatchMap::iterator &i); 

public:
	CTRiASCoordTransform() :
		m_bDTransIntern(TRUE), m_cookOutput(0),	m_guidWGS84(IID_NULL)
	{
		memset (m_goodEnv, 0, sizeof(m_goodEnv)); 
	}
	~CTRiASCoordTransform() 
	{
	}

	HRESULT FinalConstruct();
	void FinalRelease();

//	_ATLX_DEBUG_ADDREF_RELEASE_IMPL(CTRiASCoordTransform)

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CTRiASCoordTransform)
	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASCOORDTRANSFORM)

	BEGIN_COM_MAP(CTRiASCoordTransform)
		COM_INTERFACE_ENTRY(ITRiASCSTransform)
		COM_INTERFACE_ENTRY(ITRiASCSTransform0)
		COM_INTERFACE_ENTRY2(IDispatch,ITRiASCSTransform)
		COM_INTERFACE_ENTRY(ITRiASCSEvents)
		COM_INTERFACE_ENTRY(ITRiASRawCoordTransform)
		COM_INTERFACE_ENTRY_THIS()
	END_COM_MAP()

// ITRiASCoordTransform0
public:
	STDMETHOD(RecomputeTransformations)();
	STDMETHOD(putref_OutputCS)(/* [in] */ ITRiASCS *pVal);
	STDMETHOD(get_OutputCS)(/* [retval][out] */ ITRiASCS **pVal);
	STDMETHOD(AddInputCS)(/* [in] */ ITRiASCS *pCS);
	STDMETHOD(RemoveInputCS)(/*[in]*/ BSTR strGUID);

	STDMETHOD(get_IsValid)(/*[in]*/ BSTR GUID, /*[out, retval]*/ VARIANT_BOOL *pVal); 
	STDMETHOD(Transform)(/* [in] */ BSTR GUID, /* [in] */ VARIANT InPoints, /* [retval][out] */ VARIANT *OutPoints);
	STDMETHOD(TransformInverse) (/* [in] */ BSTR GUID, /* [in] */ VARIANT InPoints, /* [retval][out] */ VARIANT *OutPoints);
	STDMETHOD(ShutDown)();
	STDMETHOD(GetGoodEnvelope)(/*[in,out]*/ double *lowerLeftX, /*[in,out]*/ double *lowerLeftY, /*[in,out]*/ double *upperRightX, /*[in,out]*/ double *upperRightY); 
	STDMETHOD(SetGoodEnvelope)(/*[in]*/ double lowerLeftX, /*[in]*/ double lowerLeftY, /*[in]*/ double upperRightX, /*[in]*/ double upperRightY); 

// ITRiASCoordTransform
	STDMETHOD(get_Count)(/*[out, retval]*/ long* pCount); 
	STDMETHOD(get_Item)(/*[in]*/ VARIANT vGUID, /*[out, retval]*/ VARIANT* pvTRiASCS); 
	STDMETHOD(get__NewEnum)(/*[out,retval] */ IUnknown** ppEnum); 
	STDMETHOD(Add)(/*[in]*/ VARIANT vCS); 
	STDMETHOD(Remove)(/*[in]*/ VARIANT vCS); 

// ITRiASRawCoordTransform
	STDMETHOD(Transform) (/*[in]*/ CSID CoordSysGUID, /*[in]*/ long nCoords, /*[in,size_is(nCoords)]*/ CSCOORD* pInPoints, /*[in,out,size_is(3*nCoords)]*/ CSCOORD* pOutPoints); 
	STDMETHOD(TransformInverse) (/*[in]*/ CSID CoordSysGUID, /*[in]*/ long nCoords, /*[in,size_is(nCoords)]*/ CSCOORD* pInPoints, /*[in,out,size_is(nCoords)]*/ CSCOORD* pOutPoints); 

// ITRiASCSEvents
	STDMETHOD(ChangingCS)(/*[in]*/ ITRiASCS* pCS, /*[in,out]*/ VARIANT_BOOL *canChange);
	STDMETHOD(CSToChange)(/*[in]*/ ITRiASCS* pCS); 
	STDMETHOD(CSChanged)(/*in]*/ ITRiASCS* pCS); 

// für gute Freunde ...
	HRESULT Transform (REFGUID inCS, long nCoords, CSCOORD *pData); 
	HRESULT TransformInverse (REFGUID inCS, long nCoords, CSCOORD *pData); 
};

#endif // !defined(_TRIASCOORDTRANSFORM_H__4C94758F_D85C_417F_9696_3806F1CE1E5A__INCLUDED_)
