// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 17.03.2002 13:35:37 
//
// @doc
// @module MapSALayer.cpp | Definition of the <c CMapSALayer> class

// MapSALayer.cpp : Implementierung von CMMSALayerApp und DLL-Registrierung.

#include "stdafx.h"

#include "resource.h"
#include "MMSALayer.h"
#include "../MapCtrlImpl.h"
#include "MapSALayer.h"

// globale Variablen
#include <float.h>		  	// für DBL_MAX

double XMin = DBL_MAX;		 	
double YMin = DBL_MAX;			//EXTMIN/EXTMAX
double XMax = DBL_MIN;
double YMax = DBL_MIN;
// KK001108
// Inline-Funktionen
inline
void SetXCon (double X) { if (X < XMin) XMin = X; if (X > XMax) XMax = X; }
inline
void SetYCon (double Y) { if (Y < YMin) YMin = Y; if (Y > YMax) YMax = Y; }


/////////////////////////////////////////////////////////////////////////////

// CMapSALayer

HRESULT CMapSALayer::FinalConstruct() {
//	_ASSERTE( !!m_pCS && !!m_pGCS && !!m_pPCS );
//	if( !m_pCS || !m_pGCS || !m_pPCS )
//		return E_FAIL;
//	m_pCS->put_CoordSystemType( tcsCS_Projected );
//	m_pGCS->put_GeodeticDatum( tcsGD_DeutscheHauptdreiecksnetz );
//	m_pPCS->put_ProjectionAlgorithm( tcsPA_GaussKrueger );
//    m_pPCS->put_ProjectionParameter( tcsPP_GaussKrueger_FalseEasting, 4500000 );
//    m_pPCS->put_ProjectionParameter( tcsPP_GaussKrueger_FalseNorthing, 0 );
//    m_pPCS->put_ProjectionParameter( tcsPP_GaussKrueger_LatitudeOfNaturalOrigin, 0 );
//    m_pPCS->put_ProjectionParameter( tcsPP_GaussKrueger_LongitudeOfNaturalOrigin, 12 );
//    m_pPCS->put_ProjectionParameter( tcsPP_GaussKrueger_ScaleFactorAtNaturalOrigin, 1 );
	m_pPCS.Release();
	m_pGCS.Release();
	m_pCS.Release();
	return S_OK;
}

void CMapSALayer::FinalRelease() 
{
}

STDMETHODIMP CMapSALayer::GetAltFileFilter(BSTR* pFilter) {
	USES_CONVERSION;
	if(!pFilter)
		return E_POINTER;

CComBSTR S;
	
	VERIFY(S.LoadString (_Module.GetResourceInstance(), IDS_DISPLAYFILTER_SAL));
	*pFilter = S.Detach();
	return S_OK;
}

STDMETHODIMP CMapSALayer::GetDisplayName(BSTR * strDisplay) {
	if(!strDisplay)
		return E_POINTER;

CComBSTR S;

	VERIFY(S.LoadString (_Module.GetResourceInstance(), IDS_DISPLAYNAME_SAL));
	*strDisplay = S.Detach();
	return S_OK;
}

#include <fstream.h>

#include <ospace\string\tokenize.h>
#include <ospace\string\regexp.h>

STDMETHODIMP CMapSALayer::CheckAltFile(BSTR strFileName, long* pValid) {
	if( !pValid )
		return E_POINTER;
	HRESULT hr = E_FAIL;
	*pValid = FALSE;
	USES_CONVERSION;

// KK001109
// Seitenverschiebungen der Rasterkarte
// Ausnullen
	m_DiffPoints.clear();
	GCP	gcp;
	for ( long j = 0; j < 4; j++) {
		gcp.m_ptGeoCoord.X = 0.0;
		gcp.m_ptGeoCoord.Y = 0.0;
		m_DiffPoints.push_back( gcp );
	}


	FILE *pActFile;

	if ((pActFile = fopen (W2A(strFileName), "rt")) == NULL)
		return E_FAIL;  

//	char *pF = "^[:blank:]*%d[:blank:]*";
	char *pF = "[:blank:]*%d[:blank:]*";
	char p[30];

	short iNumber;
		
	double	px[6], py[6];

	try {

		char *pLine = new char[_MAX_PATH];                       // 1 Zeile
		iNumber = 1;
		wsprintf (&p[0],pF,iNumber);

		while (fgets (pLine, MAX_PATH-1,pActFile ))     

		{

			os_string pattern(p);
			os_regexp rx(pattern);
			os_substring range = rx.search(pLine);

			if (!range.empty()) {
				int irc = sscanf ( pLine,"%d%lf%lf", &iNumber,&px[iNumber-1],&py[iNumber-1]);
				iNumber++;
				wsprintf (&p[0],pF,iNumber);
			}

			if ( 6 < iNumber)
				break;

		}

// Container richten
		XMin = DBL_MAX;		 	
		YMin = DBL_MAX;
		XMax = DBL_MIN;
		YMax = DBL_MIN;


		for ( long i = 0 ; i < 4; i++) {
			SetXCon(px[i]);
			SetYCon(py[i]);
		}

		_ASSERTE( m_listOfGCP.size() == 4 );
		m_listOfGCP[0].m_ptGeoCoord = GEOPOINT( XMin, YMin, 0 );
		m_listOfGCP[1].m_ptGeoCoord = GEOPOINT( XMax, YMin, 0 );
		m_listOfGCP[2].m_ptGeoCoord = GEOPOINT( XMax, YMax, 0 );
		m_listOfGCP[3].m_ptGeoCoord = GEOPOINT( XMin, YMax, 0 );

	// Karten/Koordinaten hinbiegen
		double	dGeoX = m_listOfGCP[1].m_ptPictPoint.X;
		double	dGeoY = m_listOfGCP[1].m_ptPictPoint.Y;
		dGeoX = dGeoX/(px[5]-px[4]);
		dGeoY = dGeoY/(py[5]-py[4]);

		m_DiffPoints[0].m_ptGeoCoord = GEOPOINT( (XMin-px[4]) * dGeoX, (YMin-py[4]) * dGeoY, 0);
		m_DiffPoints[1].m_ptGeoCoord = GEOPOINT( (px[5]-XMax) * dGeoX, (YMin-py[4]) * dGeoY, 0);
		m_DiffPoints[2].m_ptGeoCoord = GEOPOINT( (px[5]-XMax) * dGeoX, (py[5]-YMax) * dGeoY, 0);
		m_DiffPoints[3].m_ptGeoCoord = GEOPOINT( (XMin-px[4]) * dGeoX, (py[5]-YMax) * dGeoY, 0);

		*pValid = TRUE;
		hr = S_OK;
		
		fclose (pActFile);
				
	} catch(...) {
			hr = E_UNEXPECTED;
	}
	return hr;


}
//////////////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CMapSALayer::GetAltFileTyp(BSTR* pTyp) {
	USES_CONVERSION;
	if(!pTyp)
		return E_POINTER;

	*pTyp = ::SysAllocString(L"doc");

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CMapSALayer::HaveMultiMap(long* pHaveMultiMap) {
	CHECKINPOINTER(pHaveMultiMap);
// KK001129 Nur für Günther - Magdeburg
	*pHaveMultiMap = TRUE;
//	*pHaveMultiMap = FALSE;
	return S_OK;
}
//

