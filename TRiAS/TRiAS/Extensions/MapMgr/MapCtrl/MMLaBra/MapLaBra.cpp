// MapLaBra.cpp : Implementierung von CMMLaBraApp und DLL-Registrierung.

#include "stdafx.h"

#include "resource.h"
#include "MMLaBra.h"
#include "../MapCtrlImpl.h"
#include "MapLaBra.h"

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

// CMapLaBra

HRESULT CMapLaBra::FinalConstruct() {
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

void CMapLaBra::FinalRelease() 
{
}

STDMETHODIMP CMapLaBra::GetAltFileFilter(BSTR* pFilter) {
	USES_CONVERSION;
	if(!pFilter)
		return E_POINTER;
//	*pFilter = ::SysAllocString(L"Arc Info ASC-Datei (*.asc)|*.asc||");

CComBSTR S;

	VERIFY(S.LoadString (_Module.GetResourceInstance(), IDS_DISPLAYFILTER_BRB));
	*pFilter = S.Detach();
	return S_OK;
}

STDMETHODIMP CMapLaBra::GetDisplayName(BSTR * strDisplay) {
	if(!strDisplay)
		return E_POINTER;

CComBSTR S;

	VERIFY(S.LoadString (_Module.GetResourceInstance(), IDS_DISPLAYNAME_BRB));
	*strDisplay = S.Detach();
	return S_OK;
}

#include <fstream.h>

#include <ospace\string\tokenize.h>
#include <ospace\string\regexp.h>

STDMETHODIMP CMapLaBra::CheckAltFile(BSTR strFileName, long* pValid) {
	if( !pValid )
		return E_POINTER;
	HRESULT hr = E_FAIL;
	*pValid = FALSE;
	USES_CONVERSION;

// KK010201
// Prüfung, ob richtige Doc-Datei!

	CComBSTR	STyp;
	GetAltFileTyp( &STyp ); 
	CString	strFilter( STyp );

	CString	S (strFileName);
	int pos = S.Find('.');

	if ( -1 != pos) 
		S = S.Right(3);
	else
		return hr;

	if ( 0 != strcmp((LPCSTR)strFilter,(LPCSTR)S))
		return hr;


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
	short iRef;
	short iNum;
		
	double	px[6], py[6];
	double	bx[6], by[6];
	double xref,yref,lref,bref;

	try {

		char *pLine = new char[_MAX_PATH];                       // 1 Zeile

		iNumber = 2;
		iRef = 0;
		iNum = 0;

		wsprintf (&p[0],pF,iNumber);

		while (fgets (pLine, MAX_PATH-1,pActFile ))     

		{

			{
			os_string pattern(p);
			os_regexp rx(pattern);
			os_substring range = rx.search(pLine);

			if (!range.empty()) {

				int irc = 0;

				if ( iNumber < 5 ) {
					irc = sscanf ( pLine,"%d%lf%lf", &iNum,&xref,&yref);
					if ( 3 != irc || iNum != iNumber)
						irc = 0;
				} else {
					irc = sscanf ( pLine,"%d%lf%lf%lf%lf", &iNum,&lref,&bref,&xref,&yref);
					if ( 5 != irc || iNum != iNumber)
						irc = 0;
				}

				if ( irc ) {

					bx[iRef] = xref;
					by[iRef] = yref;
					iRef++;

					if ( 2 == iNumber ) { 
						iNumber = 4;
					} else {
						iNumber++;
					}
	
					wsprintf (&p[0],pF,iNumber);
				}

			}

			}
				if ( 6 < iRef)
					break;
		}

		
		for ( long ii = 0 ; ii < 6; ii++) {
			px[ii] = bx[5-ii];
			py[ii] = by[5-ii];
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
STDMETHODIMP CMapLaBra::GetAltFileTyp(BSTR* pTyp) {
	USES_CONVERSION;
	if(!pTyp)
		return E_POINTER;

	*pTyp = ::SysAllocString(L"asc");

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CMapLaBra::HaveMultiMap(long* pHaveMultiMap) {
	CHECKINPOINTER(pHaveMultiMap);
// KK001129 Nur für Günther - Magdeburg
	*pHaveMultiMap = TRUE;
//	*pHaveMultiMap = FALSE;
	return S_OK;
}
//

