// CTDSThroughECEF.cpp: implementation of the CTDSThroughECEF class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LibCTFImpl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

HRESULT CTDSThroughECEF::IsValid( ) 
{
	return CTransform::IsValid();
}

HRESULT CTDSThroughECEF::SetModelParameters2(double ha, double f) 
{
	m_DstSys.m_HA	= ha;
	m_DstSys.m_f	= f;
	m_DstSys.m_HB	= HB(ha, f);
	m_DstSys.m_e2	= E2(f);
	m_DstSys.m_e12	= E12(f);
	m_DstSys.m_e22	= E22(ha, HB(ha, f));
	return S_OK;
}

HRESULT CTDSThroughECEF::SetParameters( long nParams, double *pParam ) 
{
	_ASSERTE(tcsPP_SizeOfParameterSet == nParams);
	m_dx = pParam[tcsDTP_GeocentricTranslations_XAxisTranslation];
	m_dy = pParam[tcsDTP_GeocentricTranslations_YAxisTranslation];
	m_dz = pParam[tcsDTP_GeocentricTranslations_ZAxisTranslation];
	return S_OK;
}

HRESULT CTDSThroughECEF::GetDefaults(long nParams, double *pParam) 
{
	_ASSERTE(tcsPP_SizeOfParameterSet == nParams);
	pParam[tcsDTP_GeocentricTranslations_XAxisTranslation] = m_dx;
	pParam[tcsDTP_GeocentricTranslations_YAxisTranslation] = m_dy;
	pParam[tcsDTP_GeocentricTranslations_ZAxisTranslation] = m_dz;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// TransformInverse
//		aus dem eigenen geodätischem Datum zu WGS84, d.h. WBS84-Offsets
//		addieren

HRESULT CTDSThroughECEF::TransformInverse(long nCoords, LPTCSDBLCOORD pData) 
{
bool fNeedsShift = (0 != m_dx || 0 != m_dy || 0 != m_dz) ? true : false;

	for(int i = 0; i < nCoords; i++, pData++) {
		pData->c1 /= m_scaleXOut;
		pData->c2 /= m_scaleYOut;
		if (fNeedsShift) {
			LLH2XYZ(m_MeSelf, pData);
			pData->c1 += m_dx;
			pData->c2 += m_dy;
			pData->h += m_dz;
			XYZ2LLH(m_DstSys, pData);
		}
		pData->c1 *= m_scaleXIn;
		pData->c2 *= m_scaleYIn;
	}
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Transform
//		aus WGS84 zum eigenen geodätischem Datum, d.h. WBS84-Offsets
//		subtrahieren
HRESULT CTDSThroughECEF::Transform(long nCoords, LPTCSDBLCOORD pData) 
{
bool fNeedsShift = (0 != m_dx || 0 != m_dy || 0 != m_dz) ? true : false;

	for(int i = 0; i < nCoords; i++, pData++) {
		pData->c1 /= m_scaleXIn;
		pData->c2 /= m_scaleYIn;
		if (fNeedsShift) {
			LLH2XYZ(m_DstSys, pData);
			pData->c1 -= m_dx;
			pData->c2 -= m_dy;
			pData->h -= m_dz;
			XYZ2LLH(m_MeSelf, pData);
		}
		pData->c1 *= m_scaleXOut;
		pData->c2 *= m_scaleYOut;
	}
	return S_OK;
}

