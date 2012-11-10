#include "stdafx.h"
#include "LibCTFImpl.h"

namespace {
	HRESULT EvalKoeffs (double &rdk11, double &rdk12, double &rdk21, double &rdk22)  {
		double dDetA = rdk11 * rdk22 - rdk12 * rdk21;

		if (0.0 == dDetA)
			return S_FALSE;	// singuläre Matrix

		double temp = rdk11;

		rdk11 = rdk22/dDetA;
		rdk22 = temp/dDetA;
		rdk12 = -(rdk12/dDetA);
		rdk21 = -(rdk21/dDetA);
		return S_OK;
	}
}

HRESULT CTPCSGeneric::IsValid() 
{
HRESULT hr = CTransform::IsValid();

	return SUCCEEDED(hr) ? IsInitialized() : hr;
}

HRESULT CTPCSGeneric::SetParameters( long nParams, double *pParam ) 
{
	_ASSERTE( tcsPP_SizeOfParameterSet == nParams );
	_ASSERTE(0 == pParam[tcsPP_AffineTransformation_RotatePhi]);		// Phi derzeit nicht implementiert

// Parameter kopieren
	m_dK11 = m_dInvK11 = pParam[tcsPP_AffineTransformation_ScaleX];
	m_dK12 = m_dInvK12 = 0.0;
	m_dK21 = m_dInvK21 = 0.0;
	m_dK22 = m_dInvK22 = pParam[tcsPP_AffineTransformation_ScaleY];
	m_dOX = pParam[tcsPP_AffineTransformation_OffsetX];
	m_dOY = pParam[tcsPP_AffineTransformation_OffsetY];

// inverse TransformationsMatrix berechnen
	if ( S_OK != EvalKoeffs (m_dInvK11, m_dInvK12, m_dInvK21, m_dInvK22))
		return RCS_E_SINGULAR;

	m_fIsInitialized = true;
	return S_OK;
}

HRESULT CTPCSGeneric::GetDefaults( long nParams, double *pParam ) 
{
	_ASSERTE( tcsPP_SizeOfParameterSet == nParams );
	pParam[tcsPP_AffineTransformation_ScaleX] = m_dK11;
	pParam[tcsPP_AffineTransformation_ScaleY] = m_dK22;
	pParam[tcsPP_AffineTransformation_RotatePhi] = 0;
	pParam[tcsPP_AffineTransformation_OffsetX] = m_dOX;
	pParam[tcsPP_AffineTransformation_OffsetY] = m_dOY;

// inverse TransformationsMatrix berechnen
	if (!EvalKoeffs (m_dInvK11, m_dInvK12, m_dInvK21, m_dInvK22))
		return RCS_E_SINGULAR;

	m_fIsInitialized = true;
	return S_OK;
}

HRESULT CTPCSGeneric::Transform( long nCoords, LPTCSDBLCOORD pData ) 
{
	if (!IsInitialized())
		return S_FALSE;

	_ASSERTE(0 < nCoords);

	for (long i = 0; i < nCoords; i++, pData++) {
	double dX = m_dInvK11 * (pData -> c1 - m_dOX) + m_dInvK12 * (pData -> c2 - m_dOY);
	double dY = m_dInvK21 * (pData -> c1 - m_dOX) + m_dInvK22 * (pData -> c1 - m_dOY);

		pData -> c1 = dX;
		pData -> c2 = dY;
	}
	return S_OK;
}

HRESULT CTPCSGeneric::TransformInverse( long nCoords, LPTCSDBLCOORD pData ) 
{
	if (!IsInitialized())
		return S_FALSE;

	_ASSERTE(0 < nCoords);
	
	for (long i = 0; i < nCoords; i++, pData++) {
	double dX = (m_dK11 * pData -> c1) + (m_dK12 * pData -> c2) + m_dOX;
	double dY = (m_dK21 * pData -> c1) + (m_dK22 * pData -> c2) + m_dOY;

		pData -> c1 = dX;
		pData -> c2 = dY;
	}
	return S_OK;
}

