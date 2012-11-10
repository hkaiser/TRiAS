// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 17.03.2002 13:34:15 
//
// @doc
// @module MapArcInfo.cpp | Definition of the <c CMapGeoPunktDLK> class

#include "stdafx.h"

#include <fstream.h>
#include <ospace/file/path.h>

#include "resource.h"
#include "MMGeoPunktDLK.h"
#include "../MapCtrlImpl.h"
#include "MapGeoPunktDLK.h"

/////////////////////////////////////////////////////////////////////////////
// CMapGeoPunktDLK

HRESULT CMapGeoPunktDLK::FinalConstruct() 
{
	_ASSERTE(!!m_pCS && !!m_pGCS && !!m_pPCS);
	if (!m_pCS || !m_pGCS || !m_pPCS)
		return E_FAIL;

	m_pCS->put_CoordSystemType(tcsCS_Projected);

	m_pGCS->put_GeodeticDatum(tcsGD_DeutscheHauptdreiecksnetz);
	m_pGCS->put_PrimeMeridian(tcsPM_Greenwich);
	m_pGCS->put_UnitOfAngle(tcsUOA_Second);

CComQIPtr<ITRiASCSDatumTransformation, &IID_ITRiASCSDatumTransformation> m_pDT;

	m_pCS->get_DatumTransformation(&m_pDT);
	m_pDT->put_TransformationAlgorithm(tcsDTA_PositionVector7ParamTransformation);
	m_pDT->put_GeodeticDatum(tcsGD_DeutscheHauptdreiecksnetz);

	m_pPCS->put_ProjectionAlgorithm(tcsPA_TransverseMercator);
	m_pPCS->put_ProjectionParameter(tcsPP_GaussKrueger_ZoneWidth, 3);
	m_pPCS->put_ProjectionParameter(tcsPP_GaussKrueger_FalseNorthing, 0.0);
	m_pPCS->put_ProjectionParameter(tcsPP_GaussKrueger_LatitudeOfNaturalOrigin, 0.0);
	m_pPCS->put_ProjectionParameter(tcsPP_GaussKrueger_ScaleFactorAtNaturalOrigin, 1.0);

	return S_OK;
}

void CMapGeoPunktDLK::FinalRelease() 
{
}

STDMETHODIMP CMapGeoPunktDLK::GetAltFileFilter(BSTR* pbstrFilter) 
{
	CHECKINPOINTER(pbstrFilter);

CComBSTR S;

	VERIFY(S.LoadString (_Module.GetResourceInstance(), IDS_DISPLAYFILTER_DLK));
	*pbstrFilter = S.Detach();
	return S_OK;
}

STDMETHODIMP CMapGeoPunktDLK::GetDisplayName(BSTR *pbstrDisplay) 
{
	CHECKINPOINTER(pbstrDisplay);

CComBSTR S;

	VERIFY(S.LoadString (_Module.GetResourceInstance(), IDS_DISPLAYNAME_DLK));
	*pbstrDisplay = S.Detach();
	return S_OK;
}

STDMETHODIMP CMapGeoPunktDLK::CheckAltFile(BSTR bstrFileName, long *pValid) 
{
	CHECKINPOINTER(pValid);
	*pValid = FALSE;

HRESULT hr = E_FAIL;

	m_DiffPoints.clear();
	for ( long j = 0; j < 4; j++) {
	GCP gcp;
	
		gcp.m_ptGeoCoord.X = 0.0;
		gcp.m_ptGeoCoord.Y = 0.0;
		m_DiffPoints.push_back( gcp );
	}

	USES_CONVERSION;

os_path path = OLE2A(bstrFileName);

	path.extension("tfw");
	if ((DWORD)(-1) != GetFileAttributes((LPCSTR)path)) {
		try {
		ifstream i ((LPCTSTR)path);
		double p0x, p0y, a11, a12, a21, a22;

			for(;;) {
				i >> a11; if (!i.good()) break;
				i >> a12; if (!i.good()) break;
				i >> a21; if (!i.good()) break;
				i >> a22; if (!i.good()) break;
				i >> p0x; if (!i.good()) break;
				i >> p0y; if (!i.good()) break;

				_ASSERTE(m_listOfGCP.size() == 4);

			double dGeoX = m_listOfGCP[1].m_ptPictPoint.X * a11;
			double dGeoY = m_listOfGCP[1].m_ptPictPoint.Y * a22;

				m_listOfGCP[0].m_ptGeoCoord = GEOPOINT(p0x        , p0y + dGeoY, 0);
				m_listOfGCP[1].m_ptGeoCoord = GEOPOINT(p0x + dGeoX, p0y + dGeoY, 0);
				m_listOfGCP[2].m_ptGeoCoord = GEOPOINT(p0x + dGeoX, p0y        , 0);
				m_listOfGCP[3].m_ptGeoCoord = GEOPOINT(p0x        , p0y        , 0);

				*pValid = TRUE;
				hr = S_OK;
				break;
			}
		} 
		catch(...) {
			hr = E_UNEXPECTED;
		}
	}

	if (*pValid) 
		return hr;

// das Ganze nochmal mit den *.x Dateien versuchen
	path.extension("x");
	if ((DWORD)(-1) != GetFileAttributes((LPCSTR)path)) {
		try {
		ifstream i ((LPCTSTR)path);
		double dXMin, dYMin, dXMax, dYMax;

			for (;;) {
				i >> dXMin; if (!i.good()) break;
				i >> dYMin; if (!i.good()) break;
				i >> dXMax; if (!i.good()) break;
				i >> dYMax; if (!i.good()) break;

				m_listOfGCP[0].m_ptGeoCoord = GEOPOINT(dXMin, dYMin, 0);
				m_listOfGCP[1].m_ptGeoCoord = GEOPOINT(dXMax, dYMin, 0);
				m_listOfGCP[2].m_ptGeoCoord = GEOPOINT(dXMax, dYMax, 0);
				m_listOfGCP[3].m_ptGeoCoord = GEOPOINT(dXMin, dYMax, 0);

				*pValid = TRUE;
				hr = S_OK;
			}
		}
		catch (...) {
			hr = E_UNEXPECTED;
		}
	}
	return hr;
}

//////////////////////////////////////////////////////////////////////////////////////
//
STDMETHODIMP CMapGeoPunktDLK::GetAltFileTyp(BSTR* pbstrTyp) 
{
	USES_CONVERSION;
	CHECKINPOINTER(pbstrTyp);

	*pbstrTyp = ::SysAllocString(L"tfw");
	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////////////
//
STDMETHODIMP CMapGeoPunktDLK::HaveMultiMap(long* pHaveMultiMap) 
{
	CHECKINPOINTER(pHaveMultiMap);
	*pHaveMultiMap = TRUE;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// #HK020318
STDMETHODIMP CMapGeoPunktDLK::BitmapIndex (long *plIndex)
{
	CHECKINPOINTER(plIndex);
	*plIndex = IMG_GEOPUNKT_DLK;		// GeoPunkt Icon
	return S_OK;
}


STDMETHODIMP CMapGeoPunktDLK::GetDescription(BSTR *prgFlags)
{
	CHECKINPOINTER(prgFlags);

CComBSTR bstrDesc;

	VERIFY(bstrDesc.LoadString(_Module.GetResourceInstance(), IDS_DESCRIPTION));
	*prgFlags = bstrDesc.Detach();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Korrektur des Namens, der am TRiAS-Objekt geschrieben werden soll
// Für DLK wird am Objekt geschrieben:
//		LetztesUnterVerzeichnis@@BildName
STDMETHODIMP CMapGeoPunktDLK::CorrectName (BSTR bstrDestDir, BSTR bstrName, BSTR *pbstrToWrite)
{
	CHECKINPOINTER(pbstrToWrite);
	*pbstrToWrite = NULL;

	CHECKINPOINTER(bstrDestDir);
	CHECKINPOINTER(bstrName);

	USES_CONVERSION;

// String erzeugen, der am Objekt gespeichert werden soll
os_path path = OLE2A(bstrDestDir);
CString strT;

	if (path.levels() > 1)
		strT = path[path.levels()-1].c_str();
	if (-1 != strT.Find(' '))
		strT = "\"" + strT + "\"";

	strT += "@@@";
	if (::SysStringLen(bstrName) > 0)
		strT += bstrName;
	else
		return E_UNEXPECTED;

	*pbstrToWrite = strT.AllocSysString();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Korrektur des Verzeichnisses, welches zum Bild-Suchpfad hinzugefügt werden soll
// Für DLK wird vom gegebenen Verzeichnis das letzte Unterverzeichnis
// abgeschnitten, da am Bild der Rest gespeichert ist (s. CorrectName)
//STDMETHODIMP CMapGeoPunktDLK::CorrectDirectory (BSTR bstrDestDir, BSTR *pbstrToWrite)
//{
//	CHECKINPOINTER(pbstrToWrite);
//	*pbstrToWrite = NULL;
//	CHECKINPOINTER(pbstrToWrite);
//
//	USES_CONVERSION;
//
//os_path path = OLE2A(bstrDestDir);
//
//	if (path.levels() > 1)
//		path.cd("..");		// go one level up
//
//CComBSTR bstrT (os_string(path).c_str());
//
//	*pbstrToWrite = bstrT.Detach();
//	return S_OK;
//}

STDMETHODIMP CMapGeoPunktDLK::NeedsCoordSystem (VARIANT_BOOL *pfNeedsCoordSys)
{
	CHECKINPOINTER(pfNeedsCoordSys);
	*pfNeedsCoordSys = VARIANT_TRUE;
	return S_OK;
}

