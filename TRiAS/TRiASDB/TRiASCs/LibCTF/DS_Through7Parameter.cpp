// CTDSThrough7ParameterPositionVector.cpp: implementation of the CTDSThrough7ParameterPositionVector class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LibCTFImpl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

HRESULT CTDSThrough7ParameterPositionVector::IsValid( ) 
{
	return CTransform::IsValid();
}

HRESULT CTDSThrough7ParameterPositionVector::SetModelParameters2 (double ha, double f) 
{
	m_DstSys.m_HA	= ha;
	m_DstSys.m_f	= f;
	m_DstSys.m_HB	= HB(ha, f);
	m_DstSys.m_e2	= E2(f);
	m_DstSys.m_e12	= E12(f);
	m_DstSys.m_e22	= E22(ha, HB(ha, f));
	return S_OK;
}

HRESULT CTDSThrough7ParameterPositionVector::SetParameters(long nParams, double *pParam) 
{
	_ASSERTE(tcsPP_SizeOfParameterSet == nParams);
	m_dx = pParam[tcsDTP_PositionVector7ParamTransformation_XAxisTranslation];
	m_dy = pParam[tcsDTP_PositionVector7ParamTransformation_YAxisTranslation];
	m_dz = pParam[tcsDTP_PositionVector7ParamTransformation_ZAxisTranslation];
	m_rx = pParam[tcsDTP_PositionVector7ParamTransformation_XAxisRotation];
	m_ry = pParam[tcsDTP_PositionVector7ParamTransformation_YAxisRotation];
	m_rz = pParam[tcsDTP_PositionVector7ParamTransformation_ZAxisRotation];
	m_ds = pParam[tcsDTP_PositionVector7ParamTransformation_ScaleDifference];
	return S_OK;
}

HRESULT CTDSThrough7ParameterPositionVector::GetDefaults(long nParams, double *pParam) 
{
	_ASSERTE(tcsPP_SizeOfParameterSet == nParams);
	pParam[tcsDTP_GeocentricTranslations_XAxisTranslation] = m_dx;
	pParam[tcsDTP_GeocentricTranslations_YAxisTranslation] = m_dy;
	pParam[tcsDTP_GeocentricTranslations_ZAxisTranslation] = m_dz;
	pParam[tcsDTP_PositionVector7ParamTransformation_XAxisRotation] = m_rx;
	pParam[tcsDTP_PositionVector7ParamTransformation_YAxisRotation] = m_ry;
	pParam[tcsDTP_PositionVector7ParamTransformation_ZAxisRotation] = m_rz;
	pParam[tcsDTP_PositionVector7ParamTransformation_ScaleDifference] = m_ds;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// TransformInverse
//		aus dem eigenen geodätischem Datum zu WGS84, d.h. WBS84-Offsets
//		addieren

HRESULT CTDSThrough7ParameterPositionVector::TransformInverse(long nCoords, LPTCSDBLCOORD pData) 
{
bool fNeedsShift = (0 != m_dx || 0 != m_dy || 0 != m_dz) ? true : false;
bool fNeedsRotation = (0 != m_rx || 0 != m_ry || 0 != m_rz || 0 != m_ds) ? true : false;
double ds = 1. + m_ds;

	for(int i = 0; i < nCoords; i++, pData++) {
		pData->c1 /= m_scaleXOut;
		pData->c2 /= m_scaleYOut;
		if (fNeedsShift || fNeedsRotation) {
			LLH2XYZ(m_MeSelf, pData);
			if (fNeedsRotation) {
			double x = (ds * pData->c1) - (m_rz * pData->c2) + (m_ry * pData->h);
			double y = (m_rz * pData->c1) + (ds * pData->c2) - (m_rx * pData->h);
				
				pData->h = -(m_ry * pData->c1) + (m_rx * pData->c2) + (ds * pData->h);
				pData->c1 = x;
				pData->c2 = y;
			}
			if (fNeedsShift) {
				pData->c1 += m_dx;
				pData->c2 += m_dy;
				pData->h += m_dz;
			}
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
HRESULT CTDSThrough7ParameterPositionVector::Transform(long nCoords, LPTCSDBLCOORD pData) 
{
bool fNeedsShift = (0 != m_dx || 0 != m_dy || 0 != m_dz) ? true : false;
bool fNeedsRotation = (0 != m_rx || 0 != m_ry || 0 != m_rz || 0 != m_ds) ? true : false;
double ds = 1. - m_ds;

	for(int i = 0; i < nCoords; i++, pData++) {
		pData->c1 /= m_scaleXIn;
		pData->c2 /= m_scaleYIn;
		if (fNeedsShift || fNeedsRotation) {
			LLH2XYZ(m_DstSys, pData);
			if (fNeedsShift) {
				pData->c1 -= m_dx;
				pData->c2 -= m_dy;
				pData->h -= m_dz;
			}
			if (fNeedsRotation) {
			double x = (ds * pData->c1) + (m_rz * pData->c2) - (m_ry * pData->h);
			double y = -(m_rz * pData->c1) + (ds * pData->c2) + (m_rx * pData->h);
				
				pData->h = (m_ry * pData->c1) - (m_rx * pData->c2) + (ds * pData->h);
				pData->c1 = x;
				pData->c2 = y;
			}
			XYZ2LLH(m_MeSelf, pData);
		}
		pData->c1 *= m_scaleXOut;
		pData->c2 *= m_scaleYOut;
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// 
HRESULT CTDSThrough7ParameterCoordFrameRot::SetParameters(long nParams, double *pParam) 
{
	_ASSERTE(tcsPP_SizeOfParameterSet == nParams);
	m_dx = pParam[tcsDTP_PositionVector7ParamTransformation_XAxisTranslation];
	m_dy = pParam[tcsDTP_PositionVector7ParamTransformation_YAxisTranslation];
	m_dz = pParam[tcsDTP_PositionVector7ParamTransformation_ZAxisTranslation];
	m_rx = -pParam[tcsDTP_PositionVector7ParamTransformation_XAxisRotation];
	m_ry = -pParam[tcsDTP_PositionVector7ParamTransformation_YAxisRotation];
	m_rz = -pParam[tcsDTP_PositionVector7ParamTransformation_ZAxisRotation];
	m_ds = pParam[tcsDTP_PositionVector7ParamTransformation_ScaleDifference];
	return S_OK;
}

HRESULT CTDSThrough7ParameterCoordFrameRot::GetDefaults(long nParams, double *pParam) 
{
	_ASSERTE(tcsPP_SizeOfParameterSet == nParams);
	pParam[tcsDTP_GeocentricTranslations_XAxisTranslation] = m_dx;
	pParam[tcsDTP_GeocentricTranslations_YAxisTranslation] = m_dy;
	pParam[tcsDTP_GeocentricTranslations_ZAxisTranslation] = m_dz;
	pParam[tcsDTP_PositionVector7ParamTransformation_XAxisRotation] = -m_rx;
	pParam[tcsDTP_PositionVector7ParamTransformation_YAxisRotation] = -m_ry;
	pParam[tcsDTP_PositionVector7ParamTransformation_ZAxisRotation] = -m_rz;
	pParam[tcsDTP_PositionVector7ParamTransformation_ScaleDifference] = m_ds;
	return S_OK;
}

	
