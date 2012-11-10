#include "stdafx.h"
#include "LibCTFImpl.h"

// siehe auch: "gctpc/equifor.c"
// siehe auch: "gctpc/equiinv.c"

HRESULT CTPCSCylindricEquirectangular::IsValid( ) {
	return CTransform::IsValid();
}

HRESULT CTPCSCylindricEquirectangular::SetParameters( long nParams, double *pParam ) {
	_ASSERTE( tcsPP_SizeOfParameterSet == nParams );
	m_latOrigin = pParam[tcsPP_CylindricEquirectangular_LatitudeOfNaturalOrigin];
	m_lonOrigin = pParam[tcsPP_CylindricEquirectangular_LongitudeOfNaturalOrigin];
	m_falseEasting = pParam[tcsPP_CylindricEquirectangular_FalseEasting];
	m_falseNorthing = pParam[tcsPP_CylindricEquirectangular_FalseNorthing];
	return S_OK;
}

HRESULT CTPCSCylindricEquirectangular::GetDefaults( long nParams, double *pParam ) {
	_ASSERTE( tcsPP_SizeOfParameterSet == nParams );
	pParam[tcsPP_CylindricEquirectangular_LatitudeOfNaturalOrigin] = m_latOrigin;
	pParam[tcsPP_CylindricEquirectangular_LongitudeOfNaturalOrigin] = m_lonOrigin;
	pParam[tcsPP_CylindricEquirectangular_FalseEasting] = m_falseEasting;
	pParam[tcsPP_CylindricEquirectangular_FalseNorthing] = m_falseNorthing;
	return S_OK;
}

HRESULT CTPCSCylindricEquirectangular::TransformInverse(long nCoords, LPTCSDBLCOORD pData) 
{
double Lat, Lon, R, H;
//double lonOrigin = m_lonOrigin / m_scaleXIn;
double latOrigin = m_latOrigin / m_scaleYIn;
double scale = cos(latOrigin) * m_MeSelf.m_HA;

	for (long i = 0; i < nCoords; i++, pData++) {
		R = pData->c1;
		H = pData->c2;
		R -= m_falseEasting;
		H -= m_falseNorthing;
		R /= m_scaleXOut;
		H /= m_scaleYOut;

		Lon = R / scale;
		Lat = H / m_MeSelf.m_HA;

		Lon *= m_scaleXIn;
		Lat *= m_scaleYIn;
		Lon += m_lonOrigin;
		Lat += m_latOrigin;
		pData->c1 = Lon;
		pData->c2 = Lat;
	}
	return S_OK;
}

HRESULT CTPCSCylindricEquirectangular::Transform (long nCoords, LPTCSDBLCOORD pData) 
{
double Lat, Lon, R, H;
double lonOrigin = m_lonOrigin / m_scaleXIn;
double latOrigin = m_latOrigin / m_scaleYIn;
double scale = cos(latOrigin) * m_MeSelf.m_HA;

	for (long i = 0; i < nCoords; i++, pData++) {
		Lon = pData->c1;
		Lat = pData->c2;
		Lon /= m_scaleXIn;
		Lat /= m_scaleYIn;
		Lon -= lonOrigin;
		Lat -= latOrigin;

		R = Lon * scale;
		H = Lat * m_MeSelf.m_HA;

		R *= m_scaleXOut;
		H *= m_scaleYOut;
		R += m_falseEasting;
		H += m_falseNorthing;
		pData->c1 = R;
		pData->c2 = H;
	}
	return S_OK;
}

