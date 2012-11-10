// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 28.02.2002 18:28:44 
//
// @doc
// @module TRiASCSDatumTransformation.cpp | Definition of the <c CTRiASCSDatumTransformation> class

#include "stdafx.h"

#include "McKinney/OleType.h"
#include "LibCTF/LibCTFImpl.h"

#include "TRiASCsImpl.h"
#include "TRiASCSDatumTransformation.h"

#include "EPSGMgr.h"

#if defined(_DEBUG)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

HRESULT	CTRiASCSDatumTransformation::FinalConstruct() 
{
	return InternalInitialize();
}

void CTRiASCSDatumTransformation::FinalRelease() {}

/////////////////////////////////////////////////////////////////////////////
// CTRiASCSDatumTransformation

STDMETHODIMP CTRiASCSDatumTransformation::get_TransformationAlgorithm(TRIASCSDTRANSALGORITHM * pVal) 
{
	CHECKOUTPOINTER (pVal); 
	*pVal = m_DT;
	return S_OK;
}

STDMETHODIMP CTRiASCSDatumTransformation::put_TransformationAlgorithm (TRIASCSDTRANSALGORITHM newVal) 
{
	CSTRACE1 (_T("    @@@ CTRiASCSDatumTransformation::put_TransformationAlgorithm: %s\n"), _EM.Decode(tcsCType_DT,newVal)); 

HRESULT	hr = E_FAIL;

	COM_TRY {
	CTransform *pTransform = NULL;

		switch (newVal)  {
		case tcsDTA_GeocentricTranslations:
			THROW_FAILED_HRESULT(InitParametersFromDatum());
			pTransform = new CTDSThroughECEF();
			break;

		case tcsDTA_PositionVector7ParamTransformation:
			THROW_FAILED_HRESULT(InitParametersFromDatum());
			pTransform = new CTDSThrough7ParameterPositionVector();
			break;

		case tcsDTA_CoordinateFrame7ParamTransformation:
			THROW_FAILED_HRESULT(InitParametersFromDatum());
			pTransform = new CTDSThrough7ParameterCoordFrameRot();
			break;

		default :
			MAKE_ERROR (DTT_E_INAVLIDDATUMTRANSFORMATION); 
		}
		if (m_pDTransform) 
			delete m_pDTransform;

		m_pDTransform = pTransform;
		m_DT = newVal;

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Parameter für geozentrische Translation initialisieren
HRESULT CTRiASCSDatumTransformation::InitParametersFromDatum()
{
	if (tcsGD_Undefined == m_GD)
		MAKE_ERROR(GCS_E_INVALIDGEODETICDATUM);

LPCPARAMETERSET p = _EM.GetParameters(tcsCType_DT, m_GD);

	_ASSERTE (NULL != p); 			// Datum muß bekannt sein
	if (NULL == p)
		MAKE_ERROR(GCS_E_INVALIDGEODETICDATUM);

//	m_TP[tcsDTP_GeocentricTranslations_XAxisTranslation] = p->p[0];
//	m_TP[tcsDTP_GeocentricTranslations_YAxisTranslation] = p->p[1];
//	m_TP[tcsDTP_GeocentricTranslations_ZAxisTranslation] = p->p[2];
	memcpy (m_TP, &p->p[0], sizeof(m_TP)); 
	return S_OK;
}

STDMETHODIMP CTRiASCSDatumTransformation::get_Parameter(TRIASCSDTRANSPARAMETER par, double *pVal) 
{
	CHECKOUTPOINTER (pVal); 
	ERROR_EXPR_FALSE (TCS_PARAMETER_INRANGE(par), TCS_E_INVALIDPARAMETERINDEX) 
	*pVal = m_TP[par];
	return S_OK;
}

STDMETHODIMP CTRiASCSDatumTransformation::put_Parameter(TRIASCSDTRANSPARAMETER par, double newVal) 
{
	ERROR_EXPR_FALSE (TCS_PARAMETER_INRANGE(par), TCS_E_INVALIDPARAMETERINDEX) 
	CSTRACE2 (_T("    @@@ CTRiASCSDatumTransformation::put_Parameter: %d %lf\n"), par, newVal); 
	m_TP[par] = newVal;
	return S_OK;
}

STDMETHODIMP CTRiASCSDatumTransformation::get_Parameters(VARIANT * pVal) 
{
	CHECKOUTPOINTER(pVal);
	COM_TRY {
		MC::Dim	dim (tcsPP_SizeOfParameterSet); 
		MC::ArrayDouble	parArr (dim); 
		double	*p = &parArr[0];
		memcpy (p, m_TP, sizeof(m_TP)); 
		::VariantInit (pVal); 
		V_VT(pVal) = VT_R8 | VT_ARRAY;
		V_ARRAY(pVal) = parArr.Detach();
	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASCSDatumTransformation::put_Parameters(VARIANT newVal) 
{
	COM_TRY {
		ERROR_EXPR_FALSE (V_ISARRAY(&newVal) && V_R8(&newVal), E_INVALIDARG); 
		SAFEARRAY FAR *pArray = NULL;
		if (V_ISBYREF (&newVal) )  {
			pArray = *newVal.pparray;
		} else {
			pArray = newVal.parray;
		}
		ERROR_EXPR_FALSE (NULL != pArray, E_INVALIDARG); 
		MC::ArrayDouble	parArr;
		ERROR_EXPR_FALSE (parArr.Attach (pArray) , E_INVALIDARG); 
		double	*pDbl = &parArr[0];
		memcpy (m_TP, pDbl, sizeof(m_TP)); 
	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASCSDatumTransformation::get_GeodeticDatum(TRIASCSGEODETICDATUM * pVal) 
{
	CHECKOUTPOINTER (pVal); 
	*pVal = m_GD;
	return S_OK;
}

STDMETHODIMP CTRiASCSDatumTransformation::put_GeodeticDatum(TRIASCSGEODETICDATUM newVal) 
{
	ERROR_EXPR_TRUE (!_EM.Decode (tcsCType_GD, newVal) , GCS_E_INVALIDGEODETICDATUM); 
	CSTRACE1 (_T("    @@@ CTRiASCSDatumTransformation::put_GeodeticDatum: %s\n"), _EM.Decode(tcsCType_GD, newVal)); 
	m_GD = newVal;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// ITRiASCSValidate

STDMETHODIMP CTRiASCSDatumTransformation::IsValid () 
{
	ERROR_EXPR_TRUE (tcsDTA_Undefined == m_DT, DTT_E_INAVLIDDATUMTRANSFORMATION); 
	return S_OK;
}

STDMETHODIMP CTRiASCSDatumTransformation::RecomputeTransformation (ITRiASCSGCS *pGCS) 
{
	CHECKINPOINTER (pGCS); 
	ERROR_EXPR_TRUE (NULL == m_pDTransform, DTT_E_INAVLIDDATUMTRANSFORMATION); 

	COM_TRY {
	double ha, f;
	TRIASCSUNITOFANGLE uoa;

		pGCS->get_SemiMajorAxis (&ha); 
		pGCS->get_Flattening (&f); 
		pGCS->get_UnitOfAngle (&uoa); 
	
	LPCPARAMETERSET	p = _EM.GetParameters (tcsCType_UOA, uoa); 
	
		_ASSERTE (NULL != p); 			// p1 muß bereits im GCS korrekt sein!
	
	double scale = p->p[1] / p->p[0];
	
		ERROR_RCT_NOTOK (m_pDTransform -> SetScale (scale, scale) , DTT_E_INAVLIDPARAMETER); 
		ERROR_RCT_NOTOK (m_pDTransform -> SetModel (ha, f) , DTT_E_INAVLIDPARAMETER); 
		ERROR_RCT_NOTOK (m_pDTransform -> SetParameters (tcsPP_SizeOfParameterSet, m_TP) , DTT_E_INAVLIDPARAMETER); 
	
	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// -	Transformationsparameter des Zieltransformators werden gleich in den
//		Quelltransformator eingerechnet
// -	wenn dieses Verfahren angewendet wird, darf auch nur einmal das Datum
//		transformiert werden
// -	im Moment funktioniert das allerdings nur bei geozentrischer Translation (!!!!)
//		(mehr gibt's ja jetzt auch noch nicht; -))

STDMETHODIMP CTRiASCSDatumTransformation::RecomputeDatumTransformation(
	ITRiASCSGCS *pSrcGCS, ITRiASCSGCS *pDstGCS, ITRiASCSDatumTransformation *pDstDTrans) 
{
	CHECKINPOINTER(pDstDTrans);
	CHECKINPOINTER(pSrcGCS);
	CHECKINPOINTER(pDstGCS);

	COM_TRY {
		ERROR_EXPR_TRUE(tcsDTA_GeocentricTranslations != m_DT, DTT_E_INAVLIDDATUMTRANSFORMATION); 

	TRIASCSDTRANSALGORITHM dtaOut;

		pDstDTrans->get_TransformationAlgorithm (&dtaOut); 
		ERROR_EXPR_TRUE (dtaOut != m_DT, DTT_E_INCOMPATIBLEDATUMTRANSFORMATION); 

	///////////////////////////////////////////////////////////////////////////////
	// Transformationsparameter aus dem Zieltransformator
	CComVariant	vParams;

		pDstDTrans->get_Parameters (CLEARED(vParams)); 

	SAFEARRAY *pArray = NULL;

		pArray = V_ISBYREF(&vParams) ? *vParams.pparray : vParams.parray;
		ERROR_EXPR_TRUE (NULL == pArray, E_INVALIDARG); 

	MC::ArrayDouble	parArr;

		ERROR_EXPR_FALSE (parArr.Attach (pArray) , E_INVALIDARG); 

	double *pDbl = &parArr[0];
	double newTP[tcsPP_SizeOfParameterSet];

		memset (newTP, PADCHAR, sizeof(newTP)); 
		for (int i = 0; i < tcsPP_SizeOfParameterSet; i++) 
			newTP[i] = m_TP[i] - pDbl[i];

#if defined(_DEBUG)
	///////////////////////////////////////////////////////////////////////////////
	// wir prüfen mal 'n bischen...; -)
	TRIASCSGEODETICDATUM dtIn, dtOut;

		pSrcGCS->get_GeodeticDatum (&dtIn); 
		pDstGCS->get_GeodeticDatum (&dtOut); 

	///////////////////////////////////////////////////////////////////////////////
	// bei gleichem geod. Datum am Ein- und Ausgang müssen dx, dy und dz in der Summe null sein!
		if (tcsGD_UserDefined != dtIn && dtIn == dtOut) {
			_ASSERTE (0 == newTP[0] && 0 == newTP[1] && 0 == newTP[2]); 
		}

	///////////////////////////////////////////////////////////////////////////////
	// wenn nicht WGS84 muß wenigstens einer der Parameter ungleich null sein!
		if (tcsGD_UserDefined != dtIn && tcsGD_WorldGeodeticSystem1984 != dtIn) {
			_ASSERTE (0 != m_TP[0] || 0 != m_TP[1] || 0 != m_TP[2]); 
		}
		if (tcsGD_UserDefined != dtOut && tcsGD_WorldGeodeticSystem1984 != dtOut) {
			_ASSERTE (0 != pDbl[0] || 0 != pDbl[1] || 0 != pDbl[2]); 
		}
#endif // defined(_DEBUG)

	double haOut, fOut, haIn, fIn;
	TRIASCSUNITOFANGLE uoaOut, uoaIn;

		pSrcGCS->get_SemiMajorAxis (&haOut); 
		pSrcGCS->get_Flattening (&fOut); 
		pSrcGCS->get_UnitOfAngle (&uoaOut); 

		pDstGCS->get_SemiMajorAxis (&haIn); 
		pDstGCS->get_Flattening (&fIn); 
		pDstGCS->get_UnitOfAngle (&uoaIn); 

	LPCPARAMETERSET	p = _EM.GetParameters (tcsCType_UOA, uoaOut); 

		_ASSERTE (NULL != p); 			// p1 muß bereits im GCS korrekt sein!

	double scaleOut = p->p[1] / p->p[0];

		p = _EM.GetParameters (tcsCType_UOA, uoaIn); 
		_ASSERTE (NULL != p); 			// p1 muß bereits im GCS korrekt sein!
	
	double scaleIn = p->p[1] / p->p[0];

		ERROR_RCT_NOTOK (m_pDTransform->SetScale (scaleOut, scaleOut, scaleIn, scaleIn) , DTT_E_INAVLIDPARAMETER); 
		ERROR_RCT_NOTOK (m_pDTransform->SetModel (haOut, fOut, haIn, fIn) , DTT_E_INAVLIDPARAMETER); 
		ERROR_RCT_NOTOK (m_pDTransform->SetParameters (tcsPP_SizeOfParameterSet, newTP) , DTT_E_INAVLIDPARAMETER); 
	
	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// ITRiASCSTransformData

STDMETHODIMP CTRiASCSDatumTransformation::Transform(/*[in]*/ long nCoords, /*[in,out,size_is(nCoords)]*/ CSCOORD* pCoords)  {
	COM_TRY {
		ERROR_EXPR_TRUE (NULL == m_pDTransform, DTT_E_INAVLIDDATUMTRANSFORMATION); 
		CSTRACE4 (_T("    @@@ CTRiASCSDatumTransformation::Transform: %d %lf %lf %lf\n"), nCoords, pCoords->X, pCoords->Y, pCoords->Z); 
		ERROR_RCT_NOTOK (m_pDTransform->Transform (nCoords, (TCSDBLCOORD*) pCoords) , PCS_E_TRANSFORMATIONFAILED); 
		CSTRACE4 (_T("    @@@ CTRiASCSDatumTransformation::Transform: %d %lf %lf %lf\n"), nCoords, pCoords->X, pCoords->Y, pCoords->Z); 
	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASCSDatumTransformation::TransformInverse(/*[in]*/ long nCoords, /*[in,out,size_is(nCoords)]*/ CSCOORD* pCoords)  {
	COM_TRY {
		ERROR_EXPR_TRUE (NULL == m_pDTransform, DTT_E_INAVLIDDATUMTRANSFORMATION); 
		CSTRACE4 (_T("    @@@ CTRiASCSDatumTransformation::TransformInverse: %d %lf %lf %lf\n"), nCoords, pCoords->X, pCoords->Y, pCoords->Z); 
		ERROR_RCT_NOTOK (m_pDTransform->TransformInverse (nCoords, (TCSDBLCOORD*) pCoords) , PCS_E_TRANSFORMATIONFAILED); 
		CSTRACE4 (_T("    @@@ CTRiASCSDatumTransformation::TransformInverse: %d %lf %lf %lf\n"), nCoords, pCoords->X, pCoords->Y, pCoords->Z); 
	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASCSDatumTransformation::CanTransform(LONG typeOfTransformation) {
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// CPersistStreamInitImpl

HRESULT CTRiASCSDatumTransformation::LoadData(IStream * pStream, DWORD dwVersion) {
	CHECKINPOINTER (pStream); 
	COM_TRY {
	DWORD nParam = 0;
	TRIASCSDTRANSALGORITHM rgAlgo;
	TRIASCSGEODETICDATUM rgDatum;

		LoadItem (pStream, rgAlgo); 
		LoadItem (pStream, rgDatum); 
		LoadItem (pStream, nParam); 
		ERROR_EXPR_FALSE (tcsPP_SizeOfParameterSet == nParam, E_FAIL); 
		LoadItem (pStream, m_TP); 
		LoadItem (pStream, m_scale); 

		THROW_FAILED_HRESULT(put_GeodeticDatum(rgDatum));
		THROW_FAILED_HRESULT(put_TransformationAlgorithm(rgAlgo));

	} COM_CATCH;
	return S_OK;
}

HRESULT CTRiASCSDatumTransformation::SaveData(IStream *pStream, BOOL bClearDirty)  {
	CHECKINPOINTER (pStream); 
	COM_TRY {
		DWORD	nParam = tcsPP_SizeOfParameterSet;
		SaveItem (pStream, m_DT); 
		SaveItem (pStream, m_GD); 
		SaveItem (pStream, nParam); 
		SaveItem (pStream, m_TP); 
		SaveItem (pStream, m_scale); 
	} COM_CATCH;
	return S_OK;
}

DWORD CTRiASCSDatumTransformation::GetDataSize () {
	return sizeof(m_DT)
		+ sizeof(m_GD)
		+ sizeof(DWORD)					// tcsPP_SizeOfParameterSet
		+ sizeof(m_TP)
		+ sizeof(m_scale)
		;
}

HRESULT CTRiASCSDatumTransformation::OnInitNew() {
	return InternalInitialize();
}
