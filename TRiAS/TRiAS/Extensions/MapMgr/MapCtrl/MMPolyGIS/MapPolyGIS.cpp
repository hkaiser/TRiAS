// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 16.03.2002 23:52:18 
//
// @doc
// @module MapPolyGIS.cpp | Definition of the <c CMapPolyGIS> class

#include "stdafx.h"

#include <ospace/file/path.h>
#include <pgr.h>
#include <fstream.h>
#include <io.h>

#include "resource.h"
#include "MMPolyGIS.h"
#include "../MapCtrlImpl.h"
#include "MapPolyGIS.h"

/////////////////////////////////////////////////////////////////////////////
// CMapPolyGIS

HRESULT CMapPolyGIS::FinalConstruct() 
{
	m_pPCS.Release();
	m_pGCS.Release();
	m_pCS.Release();
	return S_OK;
}

void CMapPolyGIS::FinalRelease() 
{
}

STDMETHODIMP CMapPolyGIS::GetImageFileFilter (BSTR* pFilter) 
{
	CHECKINPOINTER(pFilter);

CComBSTR strT("");		// no file filter (directory based)

	*pFilter = strT.Detach();
	return S_OK;
}

STDMETHODIMP CMapPolyGIS::GetAltFileFilter(BSTR *pbstrFilter) 
{
	CHECKINPOINTER(pbstrFilter);

CComBSTR S;

	VERIFY(S.LoadString (_Module.GetResourceInstance(), IDS_DISPLAYFILTER_PGIS));
	*pbstrFilter = S.Detach();
	return S_OK;
}

STDMETHODIMP CMapPolyGIS::GetDisplayName(BSTR *pbstrDisplay) 
{
	CHECKINPOINTER(pbstrDisplay);

CComBSTR S;

	VERIFY(S.LoadString (_Module.GetResourceInstance(), IDS_DISPLAYNAME_PGIS));
	*pbstrDisplay = S.Detach();
	return S_OK;
}

STDMETHODIMP CMapPolyGIS::CheckPictureFile (ITopoPict *pServer, long* pValid) 
{
// Seitenverschiebungen der Rasterkarte ausnullen
	m_DiffPoints.clear();
	for (long j = 0; j < 4; j++) {
	GCP	gcp;

		gcp.m_ptGeoCoord.X = 0.0;
		gcp.m_ptGeoCoord.Y = 0.0;
		m_DiffPoints.push_back(gcp);
	}

// GCP's vom Bild geben lassen
SAFEARRAY *pCoords = NULL;
CComPtr<IUnknown> pICS;
HRESULT hr = pServer->GetGeoCodedPoints(&pCoords, &pICS);

	if (FAILED(hr)) return hr;

	m_listOfGCP.clear();

MC::ArrayDouble	geoPoints(pCoords);
GCP	gcp;
long coord, nCoords = geoPoints.Elements() / 6, geoIdx;

	_ASSERTE(nCoords >= 4);
	for (coord = 0, geoIdx = 0; coord < nCoords; ++coord) {
		gcp.m_ptGeoCoord.X = geoPoints[geoIdx++];
		gcp.m_ptGeoCoord.Y = geoPoints[geoIdx++];
		gcp.m_ptGeoCoord.Z = geoPoints[geoIdx++];
		gcp.m_ptPictPoint.X = geoPoints[geoIdx++];
		gcp.m_ptPictPoint.Y = geoPoints[geoIdx++];
		gcp.m_ptPictPoint.Z = geoPoints[geoIdx++];
		m_listOfGCP.push_back(gcp);
	}

	if (pICS != NULL) {
		m_pPCS.Release();
		m_pGCS.Release();
		m_pCS.Release();

		m_pCS = pICS;
		_ASSERTE(m_pCS != NULL);
		m_pCS->get_GeographicCS(&m_pGCS);
		m_pCS->get_ProjectedCS(&m_pPCS);
	}
	return S_OK;
}

STDMETHODIMP CMapPolyGIS::CheckAltFile(BSTR bstrFileName, long *pValid) 
{
	CHECKINPOINTER(pValid);
	*pValid = TRUE;
	return S_OK;
}

STDMETHODIMP CMapPolyGIS::GetNameAndIdent (BSTR bstrPathName, BSTR *pbstrName, BSTR *pbstrIdent) 
{
	USES_CONVERSION;

os_path fullname = OLE2A(bstrPathName);

	*pbstrName = ::SysAllocString(A2OLE(fullname.tail().c_str()));
	*pbstrIdent = ::SysAllocString(A2OLE(fullname.tail().c_str()));
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//
STDMETHODIMP CMapPolyGIS::GetAltFileTyp(BSTR *pbstrTyp) 
{
	CHECKINPOINTER(pbstrTyp);
	*pbstrTyp = ::SysAllocString (L"pgr");
	return S_FALSE;		// hat zwar georef Dateien, diese müssen jedoch nicht selektiert werden
}

///////////////////////////////////////////////////////////////////////////////
//
STDMETHODIMP CMapPolyGIS::HaveMultiMap(long *pHaveMultiMap) 
{
	CHECKINPOINTER(pHaveMultiMap);
	*pHaveMultiMap = TRUE;		// den neuen Importweg gehen
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// #HK020318
STDMETHODIMP CMapPolyGIS::BitmapIndex (long *plIndex)
{
	CHECKINPOINTER(plIndex);
	*plIndex = IMG_POLYGIS_MAP;		// PolyGIS Icon
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Korrektur des Namens, der am TRiAS-Objekt geschrieben werden soll
// Für PolyGIS wird am Objekt geschrieben:
//		LetztesUnterVerzeichnis@raster@BildName@LevelAnzahl@CoordSys
STDMETHODIMP CMapPolyGIS::CorrectName (BSTR bstrDestDir, BSTR bstrName, BSTR *pbstrToWrite)
{
	CHECKINPOINTER(pbstrToWrite);
	*pbstrToWrite = NULL;

	CHECKINPOINTER(bstrDestDir);
	CHECKINPOINTER(bstrName);

	USES_CONVERSION;

// feststellen, wieviele Auflösungsstufen vorhanden sind
os_path leveldir = OLE2A(bstrDestDir);
char const *pcAppend = "123456789";
int iLevels = 0;

	leveldir.cd("raster");
	for (int i = 0; i < 9; ++i) {
	os_path dir = leveldir;

		dir.tail(dir.tail() + pcAppend[i]);
		if (-1 == _access((LPCTSTR)dir, 04))
			break;
		++iLevels;
	}
	if (0 == iLevels)
		return E_UNEXPECTED;	// Verzeichnisstruktur unbekannt

// String erzeugen, der am Objekt gespeichert werden soll
os_path path = OLE2A(bstrDestDir);
CString strT;

	if (path.levels() > 1)
		strT = path[path.levels()-1].c_str();
	if (-1 != strT.Find(' '))
		strT = "\"" + strT + "\"";

	strT += "@raster@1@";
	if (::SysStringLen(bstrName) > 0)
		strT += bstrName;
	else
		strT += "maps.dat";

char cbT[2] = { 
		pcAppend[iLevels]-1,
		'\0'
	};

	strT += "@";
	strT += cbT;

	if (m_bstrName.Length() > 0) {
		strT += "@";
		strT += BSTR(m_bstrName);
	}

	*pbstrToWrite = strT.AllocSysString();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Korrektur des Verzeichnisses, welches zum Bild-Suchpfad hinzugefügt werden soll
// Für PolyGIS wird vom gegebenen Verzeichnis das letzte Unterverzeichnis
// abgeschnitten, da am Bild der Rest gespeichert ist (s. CorrectName)
//STDMETHODIMP CMapPolyGIS::CorrectDirectory (BSTR bstrDestDir, BSTR *pbstrToWrite)
//{
//	CHECKINPOINTER(pbstrToWrite);
//	*pbstrToWrite = NULL;
//	CHECKINPOINTER(pbstrToWrite);
//
//	USES_CONVERSION;
//
//os_path path = OLE2A(bstrDestDir);
//
//	if (path.levels() > 0)
//		path.cd("..");		// go one level up
//
//CComBSTR bstrT (os_string(path).c_str());
//
//	*pbstrToWrite = bstrT.Detach();
//	return S_OK;
//}

STDMETHODIMP CMapPolyGIS::GetDescription(BSTR *prgFlags)
{
	CHECKINPOINTER(prgFlags);

CComBSTR bstrDesc;

	VERIFY(bstrDesc.LoadString(_Module.GetResourceInstance(), IDS_DESCRIPTION));
	*prgFlags = bstrDesc.Detach();
	return S_OK;
}

STDMETHODIMP CMapPolyGIS::CopyFlags (COPYFLAG *prgFlags)
{
	CHECKINPOINTER(prgFlags);
	*prgFlags = COPYFLAG_SourceIsDirectory;
	return S_OK;
}

STDMETHODIMP CMapPolyGIS::MakeFullName (BSTR bstrBaseDir, BSTR *pbstrFullName)
{
	CHECKINPOINTER(pbstrFullName);
	*pbstrFullName = NULL;

	USES_CONVERSION;

os_path fullname = OLE2A(bstrBaseDir);

	fullname.cd("raster1").base("maps").extension("dat");

CComBSTR bstrT ((LPCTSTR)fullname);

	*pbstrFullName = bstrT.Detach();
	return S_OK;
}

STDMETHODIMP CMapPolyGIS::NeedsCoordSystem (VARIANT_BOOL *pfNeedsCoordSys)
{
	CHECKINPOINTER(pfNeedsCoordSys);
	*pfNeedsCoordSys = VARIANT_TRUE;
	return S_OK;
}

STDMETHODIMP CMapPolyGIS::PutCoordSystem (IUnknown *pICS)
{
	CHECKINPOINTER(pICS);

HRESULT hr = E_FAIL;

	if (FAILED(hr = ITopoMapImpl::PutCoordSystem(pICS)))
		return hr;
	m_bstrName.Empty();
	return m_pCS->get_Name(&m_bstrName);
}

