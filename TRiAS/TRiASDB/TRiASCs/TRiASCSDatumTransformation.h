// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 07.10.1999 11:08:21 
//
// @doc
// @module TRiASCSDatumTransformation.h | Declaration of the <c CTRiASCSDatumTransformation> class

#if !defined(_TRIASCSDATUMTRANSFORMATION_H__1BA04933_6864_4F89_A81A_388DC7C32105__INCLUDED_)
#define _TRIASCSDATUMTRANSFORMATION_H__1BA04933_6864_4F89_A81A_388DC7C32105__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "libctf/libctf.h"

/////////////////////////////////////////////////////////////////////////////
// CTRiASCSDatumTransformation

const long DTT_VERSION = 0x0100L;
const long LASTKNOWN_DTT_VERSION = DTT_VERSION;

class ATL_NO_VTABLE CTRiASCSDatumTransformation : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CTRiASCSDatumTransformation, &CLSID_TRiASCSDatumTransformation>,
	public CErrSupport<CTRiASCSDatumTransformation, &IID_ITRiASCSDatumTransformation>,
	public CPersistStreamInitImpl<CTRiASCSDatumTransformation, &CLSID_TRiASCSDatumTransformation>,
	public IDispatchImpl<ITRiASCSDatumTransformation, &IID_ITRiASCSDatumTransformation, &LIBID_TRIASCS>,
	public ITRiASCSTransformData,
	public ITRiASCSTransformInfo,
	public ITRiASCSValidateDatum
{
private:
	bool m_bDirty;
	TRIASCSDTRANSALGORITHM m_DT;
	TRIASCSGEODETICDATUM m_GD;
	double m_TP[tcsPP_SizeOfParameterSet];
	double m_scale[16];
	CTransform *m_pDTransform;
	
	HRESULT	InternalInitialize() 
	{
		memset (m_TP, PADCHAR, sizeof(m_TP));
		memset (m_scale, PADCHAR, sizeof(m_scale));
		m_scale[0] = m_scale[5] = m_scale[10] = 1;
		put_GeodeticDatum (tcsGD_WorldGeodeticSystem1984);
		put_TransformationAlgorithm (tcsDTA_PositionVector7ParamTransformation);
		put_Parameter (tcsDTP_GeocentricTranslations_XAxisTranslation, 0) ;
		put_Parameter (tcsDTP_GeocentricTranslations_YAxisTranslation, 0);
		put_Parameter (tcsDTP_GeocentricTranslations_ZAxisTranslation, 0);
		m_bDirty = false;
		return S_OK;
	}

public:
	CTRiASCSDatumTransformation() 
		: m_pDTransform(NULL)
	{
	}
	~CTRiASCSDatumTransformation() {}
	
	HRESULT FinalConstruct();
	void FinalRelease();

//	_ATLX_DEBUG_ADDREF_RELEASE_IMPL(CTRiASCSDatumTransformation)

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CTRiASCSDatumTransformation)
	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASCSDATUMTRANSFORMATION)
	DECLARE_AGGREGATABLE(CTRiASCSDatumTransformation)

	BEGIN_COM_MAP(CTRiASCSDatumTransformation)
		COM_INTERFACE_ENTRY(ITRiASCSTransformData)	// meist gebrauchtes Interface
		COM_INTERFACE_ENTRY(ITRiASCSDatumTransformation)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ITRiASCSValidate)
		COM_INTERFACE_ENTRY(ITRiASCSValidateDatum)
		COM_INTERFACE_ENTRY(ITRiASCSTransformInfo)
		COM_INTERFACE_ENTRY_CHAIN(CPersistStreamInitImpl_t)
		COM_INTERFACE_ENTRY_CHAIN(CErrSupport_t)
	END_COM_MAP()

public:
// ITRiASCSDatumTransformation
	STDMETHOD(get_GeodeticDatum)(/*[out, retval]*/ TRIASCSGEODETICDATUM *pVal);
	STDMETHOD(put_GeodeticDatum)(/*[in]*/ TRIASCSGEODETICDATUM newVal);
	STDMETHOD(get_Parameter)(/*[in]*/ TRIASCSDTRANSPARAMETER par, /*[out, retval]*/ double *pVal);
	STDMETHOD(put_Parameter)(/*[in]*/ TRIASCSDTRANSPARAMETER par, /*[in]*/ double newVal);
	STDMETHOD(get_Parameters)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_Parameters)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_TransformationAlgorithm)(/*[out, retval]*/ TRIASCSDTRANSALGORITHM *pVal);
	STDMETHOD(put_TransformationAlgorithm)(/*[in]*/ TRIASCSDTRANSALGORITHM newVal);

// ITRiASCSValidate
	STDMETHOD(IsValid)( );
	STDMETHOD(RecomputeTransformation)(/*[in,defaultvalue(NULL)]*/ ITRiASCSGCS *pGCS);

// ITRiASCSValidateDatum
	STDMETHOD(RecomputeDatumTransformation)(/*[in]*/ ITRiASCSGCS *pSrcGCS, /*[in]*/ ITRiASCSGCS *pDstGCS, /*[in]*/ ITRiASCSDatumTransformation *pDstDTrans );

// ITRiASCSTransformData
	STDMETHOD(Transform)(/*[in]*/ long nCoords, /*[in,out,size_is(nCoords)]*/ CSCOORD* pCoords );
	STDMETHOD(TransformInverse)(/*[in]*/ long nCoords, /*[in,out,size_is(nCoords)]*/ CSCOORD* pCoords );

// ITRiASCSTransformInfo
	STDMETHOD(CanTransform)(/*[in]*/ LONG typeOfTransformation);

// CPersistStreamInit
	HRESULT	OnInitNew( );
	HRESULT LoadData( LPSTREAM pStm, DWORD dwVersion );
	HRESULT SaveData( LPSTREAM pStm, BOOL bClearDirty );
	DWORD	GetDataSize( );

	DWORD	GetSignature( ) { char *s = "CSDT"; return *((DWORD*)s); }
	DWORD	GetVersion( ) { return LASTKNOWN_DTT_VERSION; }

protected:
	HRESULT InitParametersFromDatum();
};

#endif // !defined(_TRIASCSDATUMTRANSFORMATION_H__1BA04933_6864_4F89_A81A_388DC7C32105__INCLUDED_)
