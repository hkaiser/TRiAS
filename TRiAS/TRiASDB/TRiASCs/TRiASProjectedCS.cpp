// TRiASProjectedCS.cpp : Implementation of CTRiASProjectedCS

#include "stdafx.h"
#include "TRiASCsImpl.h"
#include "LibCTF/LibCTFImpl.h"
#include "TRiASProjectedCS.h"

#include "McKinney/OleType.h"

#include "EPSGMgr.h"

#if defined(_DEBUG)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

HRESULT CTRiASProjectedCS::FinalConstruct() 
{
	return InternalInitialize();
}

void CTRiASProjectedCS::FinalRelease()
{
	if(m_pTransform)
		delete m_pTransform;
	m_pTransform = NULL;
}

/////////////////////////////////////////////////////////////////////////////
// CTRiASProjectedCS

HRESULT CTRiASProjectedCS::SetParameters() 
{
	_ASSERTE (m_pTransform && tcsPA_Undefined != m_algorithm); 
	switch (m_algorithm) {
	case tcsPA_GaussKrueger:
	case tcsPA_TransverseMercator:
	case tcsPA_CylindricEquirectangular:
	case tcsPA_LambertConicConformal2SP:
	case tcsPA_AffineTransformation:
	case tcsPA_CassiniSoldner:
		ERROR_RCT_NOTOK(m_pTransform->SetParameters (tcsPP_SizeOfParameterSet, m_parOfProjection) , PCS_E_INAVLIDPARAMETER); 
		break;

	default :
		MAKE_ERROR (PCS_E_INAVLIDPROJECTIONALGORITHM); 
	}
	return S_OK;
}

STDMETHODIMP CTRiASProjectedCS::get_UnitOfLength(TRIASCSUNITOFLENGTH * pVal) 
{
	CHECKOUTPOINTER (pVal); 
	*pVal = m_UOL;
	return S_OK;
}

STDMETHODIMP CTRiASProjectedCS::put_UnitOfLength(TRIASCSUNITOFLENGTH newVal) 
{
	ERROR_EXPR_TRUE (!_EM.Decode (tcsCType_UOL, newVal) , PCS_E_INAVLIDUNITOFLENGTH); 
	CSTRACE1 (_T("    @@@ CTRiASProjectedCS::put_UnitOfLength: %s\n"), _EM.Decode(tcsCType_UOL,newVal)); 
	m_UOL = newVal;
	return S_OK;
}

STDMETHODIMP CTRiASProjectedCS::get_ProjectionAlgorithm(TRIASCSPROJECTIONALGORITHM * pVal) 
{
	CHECKOUTPOINTER (pVal); 
	*pVal = m_algorithm;
	return S_OK;
}

STDMETHODIMP CTRiASProjectedCS::put_ProjectionAlgorithm(TRIASCSPROJECTIONALGORITHM newVal) 
{
	CSTRACE1 (_T("    @@@ CTRiASProjectedCS::put_ProjectionAlgorithm: %s\n"), _EM.Decode(tcsCType_PA,newVal)); 
	COM_TRY {
	CTransform *pNewTransform = NULL;

		switch (newVal) {
		case tcsPA_GaussKrueger:
		case tcsPA_TransverseMercator:
			 pNewTransform = new CTPCSGaussKrueger();
			 break;

		case tcsPA_CylindricEquirectangular:
			pNewTransform = new CTPCSCylindricEquirectangular();
			break;

		case tcsPA_AffineTransformation:
			pNewTransform = new CTPCSGeneric();
			break;

		case tcsPA_LambertConicConformal2SP:
			pNewTransform = new CTPCSLambertConicConformal2P();
			break;

		case tcsPA_CassiniSoldner:
			pNewTransform = new CTPCSCassiniSoldner();
			break;

		default:
			MAKE_ERROR (PCS_E_INAVLIDPROJECTIONALGORITHM); 
		}

		if (NULL != pNewTransform) {
			if (m_pTransform) {
				delete m_pTransform;
				m_pTransform = NULL;
			}

			memset (m_parOfProjection, PADCHAR, sizeof (m_parOfProjection));  
			m_pTransform = pNewTransform;
			m_pTransform -> GetDefaults (tcsPP_SizeOfParameterSet, m_parOfProjection); 
			m_algorithm = newVal;
		} 
		else {
			MAKE_ERROR (E_OUTOFMEMORY); 
		}
		
	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASProjectedCS::get_ProjectionParameters(VARIANT * pVal) 
{
	CHECKOUTPOINTER (pVal); 
	COM_TRY {
	MC::Dim	dim (tcsPP_SizeOfParameterSet); 
	MC::ArrayDouble	parArr (dim); 
	double	*p = &parArr[0];

		memcpy (p, m_parOfProjection, sizeof(m_parOfProjection)); 
		::VariantInit (pVal); 
		V_VT(pVal) = VT_R8 | VT_ARRAY;
		V_ARRAY(pVal) = parArr.Detach();
	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASProjectedCS::put_ProjectionParameters(VARIANT newVal) 
{
	COM_TRY {
		ERROR_EXPR_FALSE (V_ISARRAY(&newVal) && V_R8(&newVal), E_INVALIDARG); 

	SAFEARRAY *pArray = V_ISBYREF(&newVal) ? *newVal.pparray : newVal.parray;

		ERROR_EXPR_FALSE (NULL != pArray, E_INVALIDARG); 

	MC::ArrayDouble	parArr;

		ERROR_EXPR_FALSE (parArr.Attach (pArray) , E_INVALIDARG); 

	double	*pDbl = &parArr[0];

		memcpy (m_parOfProjection, pDbl, sizeof(m_parOfProjection)); 
		RETURN_FAILED_HRESULT (SetParameters()); 

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASProjectedCS::get_ProjectionParameter(TRIASCSPROJECTIONPARAMETER par, double * pVal) 
{
	CHECKOUTPOINTER (pVal); 
	ERROR_EXPR_FALSE (TCS_PARAMETER_INRANGE(par), TCS_E_INVALIDPARAMETERINDEX); 
	*pVal = m_parOfProjection[par];
	return S_OK;
}

STDMETHODIMP CTRiASProjectedCS::put_ProjectionParameter(TRIASCSPROJECTIONPARAMETER par, double newVal) 
{
	ERROR_EXPR_FALSE (TCS_PARAMETER_INRANGE(par), TCS_E_INVALIDPARAMETERINDEX); 
	ERROR_EXPR_TRUE (NULL == m_pTransform && tcsPA_Undefined != m_algorithm, PCS_E_INAVLIDPROJECTIONALGORITHM); 
	m_parOfProjection[par] = newVal;
	CSTRACE2 (_T("    @@@ CTRiASProjectedCS::put_ProjectionParameter: %d %lf\n"), par, newVal); 
	RETURN_FAILED_HRESULT (SetParameters()); 
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// ITRiASCSValidate

STDMETHODIMP CTRiASProjectedCS::IsValid () 
{
	RETURN_EXPR_TRUE (tcsPA_Undefined == m_algorithm, PCS_E_INAVLIDPROJECTIONALGORITHM); 
	RETURN_EXPR_FALSE (S_OK == m_pTransform->IsValid(), PCS_E_INAVLIDTRANSFORMATION);  
	return S_OK;
}

STDMETHODIMP CTRiASProjectedCS::RecomputeTransformation(/*[in,defaultvalue(NULL)]*/ ITRiASCSGCS *pGCS) 
{
	CHECKINPOINTER (pGCS); 
	COM_TRY {
	// allgemeines Modell
	double	ha, f;

		pGCS->get_SemiMajorAxis (&ha); 
		pGCS->get_Flattening (&f); 
		ERROR_RCT_NOTOK (m_pTransform->SetModel (ha, f) , PCS_E_INAVLIDPARAMETER); 

	// Skalierung Winkeleinheit
	TRIASCSUNITOFANGLE	uoa;

		pGCS->get_UnitOfAngle (&uoa); 

	LPCPARAMETERSET	p = _EM.GetParameters (tcsCType_UOA, uoa); 
	double scaleUOA = p->p[1] / p->p[0];

	// Skalierung Längeneinheit
		p = _EM.GetParameters (tcsCType_UOL, m_UOL); 
		ERROR_EXPR_TRUE (NULL == p, PCS_E_INAVLIDUNITOFLENGTH); 

	double scaleUOL = p->p[1] / p->p[0];

		ERROR_RCT_NOTOK (m_pTransform->SetScale (scaleUOL, scaleUOL, scaleUOA, scaleUOA) , PCS_E_INAVLIDPARAMETER); 
		ERROR_EXPR_FALSE (S_OK == m_pTransform->IsValid(), PCS_E_INAVLIDTRANSFORMATION);  
	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// ITRiASCSTransformInfo (um in Propertypages nur das anzuzeigen, was wir können)

STDMETHODIMP CTRiASProjectedCS::CanTransform(LONG typeOfTransformation) 
{
	switch (typeOfTransformation) {
	case tcsPA_GaussKrueger:
	case tcsPA_TransverseMercator:
	case tcsPA_CylindricEquirectangular:
	case tcsPA_AffineTransformation:
	case tcsPA_LambertConicConformal2SP:
	case tcsPA_CassiniSoldner:
		return S_OK;

	default:
		break;
	}
	return S_FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// ITRiASCSTransform

STDMETHODIMP CTRiASProjectedCS::Transform(/*[in]*/ long nCoords, /*[in,out,size_is(nCoords)]*/ CSCOORD* pCoords) 
{
	CHECKINPOINTER (pCoords); 
	ERROR_EXPR_TRUE (tcsPA_Undefined == m_algorithm, PCS_E_INAVLIDPROJECTIONALGORITHM); 
	_ASSERTE (m_pTransform); 
	CSTRACE4 (_T("    @@@ CTRiASProjectedCS::Transform: %d %lf %lf %lf\n"), nCoords, pCoords->X, pCoords->Y, pCoords->Z); 
	ERROR_RCT_NOTOK (m_pTransform->Transform (nCoords, (LPTCSDBLCOORD) pCoords) , PCS_E_TRANSFORMATIONFAILED) 
	CSTRACE4 (_T("    @@@ CTRiASProjectedCS::Transform: %d %lf %lf %lf\n"), nCoords, pCoords->X, pCoords->Y, pCoords->Z); 
	return S_OK;
}

STDMETHODIMP CTRiASProjectedCS::TransformInverse(/*[in]*/ long nCoords, /*[in,out,size_is(nCoords)]*/ CSCOORD* pCoords) 
{
	CHECKINPOINTER (pCoords); 
	ERROR_EXPR_TRUE (tcsPA_Undefined == m_algorithm, PCS_E_INAVLIDPROJECTIONALGORITHM); 
	_ASSERTE (m_pTransform); 
	CSTRACE4 (_T("    @@@ CTRiASProjectedCS::TransformInverse: %d %lf %lf %lf\n"), nCoords, pCoords->X, pCoords->Y, pCoords->Z); 
	ERROR_RCT_NOTOK (m_pTransform->TransformInverse (nCoords, (LPTCSDBLCOORD) pCoords) , PCS_E_TRANSFORMATIONFAILED) 
	CSTRACE4 (_T("    @@@ CTRiASProjectedCS::TransformInverse: %d %lf %lf %lf\n"), nCoords, pCoords->X, pCoords->Y, pCoords->Z); 
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// CPersistStreamInitImpl

HRESULT CTRiASProjectedCS::LoadData(IStream * pStream, DWORD dwVersion) 
{
	CHECKINPOINTER (pStream); 
	COM_TRY {
	// Version testen
		if ((dwVersion & ~PCS_VERSION_MINOR_MASK) > LASTKNOWN_PCS_VERSION)
			return CS_W_NEWEROBJECT;

	DWORD nParam = 0;

		LoadItem (pStream, m_algorithm); 
		THROW_FAILED_HRESULT(put_ProjectionAlgorithm(m_algorithm));

		LoadItem (pStream, m_UOL); 
		LoadItem (pStream, nParam); 
		ERROR_EXPR_FALSE (tcsPP_SizeOfParameterSet == nParam, E_FAIL); 
		LoadItem (pStream, m_parOfProjection); 

		THROW_FAILED_HRESULT(SetParameters());		// unterliegendes Koordinatensystem initialisieren

#if defined(_USE_OGC_COMPATIBILITY)
	// neuere Systeme speichern Ogc Beschreibungen mit weg
		if (dwVersion >= PCS_VERSION_101) {
			LoadItemInd<CComBSTR>(pStream, m_pTransform, CTransform::put_Name);
			LoadItemInd<CComBSTR>(pStream, m_pTransform, CTransform::put_Authority);
			LoadItemInd<long>(pStream, m_pTransform, CTransform::put_Code);
			LoadItemInd<CComBSTR>(pStream, m_pTransform, CTransform::put_Alias);
			LoadItemInd<CComBSTR>(pStream, m_pTransform, CTransform::put_Abbreviation);
			LoadItemInd<CComBSTR>(pStream, m_pTransform, CTransform::put_Remarks);
		}
#endif // defined(_USE_OGC_COMPATIBILITY)

	} COM_CATCH;
	return S_OK;
}

HRESULT CTRiASProjectedCS::SaveData(IStream *pStream, BOOL bClearDirty) 
{
	CHECKINPOINTER (pStream); 
	COM_TRY {
	DWORD nParam = tcsPP_SizeOfParameterSet; 

		SaveItem (pStream, m_algorithm); 
		SaveItem (pStream, m_UOL); 
		SaveItem (pStream, nParam); 
		SaveItem (pStream, m_parOfProjection); 

#if defined(_USE_OGC_COMPATIBILITY)
	// neuere Systeme speichern Ogc Beschreibungen mit weg
		SaveItemInd<CComBSTR>(pStream, m_pTransform, CTransform::get_Name);
		SaveItemInd<CComBSTR>(pStream, m_pTransform, CTransform::get_Authority);
		SaveItemInd<long>(pStream, m_pTransform, CTransform::get_Code);
		SaveItemInd<CComBSTR>(pStream, m_pTransform, CTransform::get_Alias);
		SaveItemInd<CComBSTR>(pStream, m_pTransform, CTransform::get_Abbreviation);
		SaveItemInd<CComBSTR>(pStream, m_pTransform, CTransform::get_Remarks);
#endif // defined(_USE_OGC_COMPATIBILITY)

	} COM_CATCH;
	return S_OK;
}

ULONG CTRiASProjectedCS::GetDataSize () 
{
	return sizeof(m_algorithm) + sizeof(m_UOL) + sizeof(DWORD) + sizeof(m_parOfProjection);
}

HRESULT CTRiASProjectedCS::OnInitNew() 
{
	COM_TRY {
		InternalInitialize();
		m_bDirty = false;
	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// ITRiASCSUIHelper

// Implementation of get_InputMask
STDMETHODIMP CTRiASProjectedCS::get_InputMask(COORDELEMENT rgElement, BSTR *pbstrUIMask)
{
	ATLTRACE(_T("CTRiASProjectedCS::get_InputMask\n"));
	CHECKOUTPOINTER(pbstrUIMask);

	ERROR_EXPR_TRUE (tcsPA_Undefined == m_algorithm, PCS_E_INAVLIDPROJECTIONALGORITHM); 
	_ASSERTE (m_pTransform); 

	return m_pTransform -> get_InputMask(rgElement, pbstrUIMask);
}

// Implementation of get_Precision
STDMETHODIMP CTRiASProjectedCS::get_Precision(long *plPrec)
{
	ATLTRACE(_T("CTRiASProjectedCS::get_Precision\n"));
	CHECKOUTPOINTER(plPrec);

	ERROR_EXPR_TRUE (tcsPA_Undefined == m_algorithm, PCS_E_INAVLIDPROJECTIONALGORITHM); 
	_ASSERTE (m_pTransform); 

	return m_pTransform -> get_Precision(plPrec);
}

// Implementation of put_Precision
STDMETHODIMP CTRiASProjectedCS::put_Precision(long lPrec)
{
	ATLTRACE(_T("CTRiASProjectedCS::put_Precision\n"));

	ERROR_EXPR_TRUE (tcsPA_Undefined == m_algorithm, PCS_E_INAVLIDPROJECTIONALGORITHM); 
	_ASSERTE (m_pTransform); 

	return m_pTransform -> put_Precision(lPrec);
}

// Implementation of Format
STDMETHODIMP CTRiASProjectedCS::Format(COORDELEMENT rgElement, double dValue, BSTR *pbstrFormattedElement)
{
	ATLTRACE(_T("CTRiASProjectedCS::Format\n"));
	CHECKOUTPOINTER(pbstrFormattedElement);

	ERROR_EXPR_TRUE (tcsPA_Undefined == m_algorithm, PCS_E_INAVLIDPROJECTIONALGORITHM); 
	_ASSERTE (m_pTransform); 

	return m_pTransform -> Format(rgElement, dValue, pbstrFormattedElement);
}

// Implementation of Convert
STDMETHODIMP CTRiASProjectedCS::Convert(COORDELEMENT rgElement, BSTR bstrFormatted, double *pValue)
{
	ATLTRACE(_T("CTRiASProjectedCS::Convert\n"));
	CHECKOUTPOINTER(pValue);

	ERROR_EXPR_TRUE (tcsPA_Undefined == m_algorithm, PCS_E_INAVLIDPROJECTIONALGORITHM); 
	_ASSERTE (m_pTransform); 

	return m_pTransform -> Convert(rgElement, bstrFormatted, pValue);
}


#if defined(_USE_OGC_COMPATIBILITY)
// Implementation of get_Name
STDMETHODIMP CTRiASProjectedCS::get_Name(BSTR *pbstrName)
{
	return E_NOTIMPL;
}

// Implementation of put_Name
STDMETHODIMP CTRiASProjectedCS::put_Name(BSTR bstrName)
{
	return E_NOTIMPL;
}

// Implementation of get_Authority
STDMETHODIMP CTRiASProjectedCS::get_Authority(BSTR *pbstrAuth)
{
	return E_NOTIMPL;
}

// Implementation of put_Authority
STDMETHODIMP CTRiASProjectedCS::put_Authority(BSTR bstrAuth)
{
	return E_NOTIMPL;
}

// Implementation of get_Code
STDMETHODIMP CTRiASProjectedCS::get_Code(long *plCode)
{
	return E_NOTIMPL;
}

// Implementation of put_Code
STDMETHODIMP CTRiASProjectedCS::put_Code(long lCode)
{
	return E_NOTIMPL;
}

// Implementation of get_Alias
STDMETHODIMP CTRiASProjectedCS::get_Alias(BSTR *pbstrAlias)
{
	return E_NOTIMPL;
}

// Implementation of put_Alias
STDMETHODIMP CTRiASProjectedCS::put_Alias(BSTR bstrAlias)
{
	return E_NOTIMPL;
}

// Implementation of get_Abbreviation
STDMETHODIMP CTRiASProjectedCS::get_Abbreviation(BSTR *pbstrAbbrev)
{
	return E_NOTIMPL;
}

// Implementation of put_Abbreviation
STDMETHODIMP CTRiASProjectedCS::put_Abbreviation(BSTR bstrAbbrev)
{
	return E_NOTIMPL;
}

// Implementation of get_Remarks
STDMETHODIMP CTRiASProjectedCS::get_Remarks(BSTR *pbstrRemarks)
{
	return E_NOTIMPL;
}

// Implementation of put_Remarks
STDMETHODIMP CTRiASProjectedCS::put_Remarks(BSTR bstrRemarks)
{
	return E_NOTIMPL;
}

// Implementation of get_WellKnownText
STDMETHODIMP CTRiASProjectedCS::get_WellKnownText(BSTR *pbstrWkt)
{
	return E_NOTIMPL;
}
#endif // defined(_USE_OGC_COMPATIBILITY)

