// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 17.03.2002 13:34:15 
//
// @doc
// @module MapArcInfo.cpp | Definition of the <c CMapArcInfo> class

#include "stdafx.h"

#include <fstream.h>
#include <ospace/file/path.h>

#include "resource.h"
#include "MMArcInf.h"
#include "../MapCtrlImpl.h"
#include "MapArcInfo.h"


/////////////////////////////////////////////////////////////////////////////
// CMapArcInfo

HRESULT CMapArcInfo::FinalConstruct() 
{
	m_pPCS.Release();
	m_pGCS.Release();
	m_pCS.Release();
	return S_OK;
}

void CMapArcInfo::FinalRelease() 
{
}

STDMETHODIMP CMapArcInfo::GetAltFileFilter(BSTR* pFilter) {
	USES_CONVERSION;
	if(!pFilter)
		return E_POINTER;

//	*pFilter = ::SysAllocString(L"Arc Info Beschreibung (*.tfw)|*.tfw||");

CComBSTR S;

	VERIFY(S.LoadString (_Module.GetResourceInstance(), IDS_DISPLAYFILTER_ARC));
	*pFilter = S.Detach();
	return S_OK;
}

STDMETHODIMP CMapArcInfo::GetDisplayName(BSTR * strDisplay) 
{
	if(!strDisplay)
		return E_POINTER;

CComBSTR S;

	VERIFY(S.LoadString (_Module.GetResourceInstance(), IDS_DISPLAYNAME_ARC));
	*strDisplay = S.Detach();
	return S_OK;
}

STDMETHODIMP CMapArcInfo::CheckAltFile(BSTR bstrFileName, long* pValid) 
{
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

os_path path = OLE2A(bstrFileName);

	path.extension("tfw");
	try {
		ifstream i ((LPCTSTR)path);
		double	p0x, p0y, a11, a12, a21, a22;
		for(;;) {
			i >> a11; if( !i.good() ) break;
			i >> a12; if( !i.good() ) break;
			i >> a21; if( !i.good() ) break;
			i >> a22; if( !i.good() ) break;
			i >> p0x; if( !i.good() ) break;
			i >> p0y; if( !i.good() ) break;
			_ASSERTE( m_listOfGCP.size() == 4 );
			double	dGeoX = m_listOfGCP[1].m_ptPictPoint.X * a11;
			double	dGeoY = m_listOfGCP[1].m_ptPictPoint.Y * a22;
			m_listOfGCP[0].m_ptGeoCoord = GEOPOINT( p0x        , p0y + dGeoY, 0 );
			m_listOfGCP[1].m_ptGeoCoord = GEOPOINT( p0x + dGeoX, p0y + dGeoY, 0 );
			m_listOfGCP[2].m_ptGeoCoord = GEOPOINT( p0x + dGeoX, p0y        , 0 );
			m_listOfGCP[3].m_ptGeoCoord = GEOPOINT( p0x        , p0y        , 0 );
			*pValid = TRUE;
			hr = S_OK;
			break;
		}
	} catch(...) {
		hr = E_UNEXPECTED;
	}
	return hr;

}

//////////////////////////////////////////////////////////////////////////////////////
//
STDMETHODIMP CMapArcInfo::GetAltFileTyp(BSTR* pTyp) {
	USES_CONVERSION;
	if(!pTyp)
		return E_POINTER;

	*pTyp = ::SysAllocString(L"tfw");

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////////////
//
STDMETHODIMP CMapArcInfo::HaveMultiMap(long* pHaveMultiMap) {
	CHECKINPOINTER(pHaveMultiMap);
	*pHaveMultiMap = TRUE;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// #HK020318
STDMETHODIMP CMapArcInfo::BitmapIndex (long *plIndex)
{
	CHECKINPOINTER(plIndex);
	*plIndex = IMG_ARCINFO_TFW;		// Arc/Info Icon
	return S_OK;
}

STDMETHODIMP CMapArcInfo::GetDescription(BSTR *prgFlags)
{
	CHECKINPOINTER(prgFlags);

CComBSTR bstrDesc;

	VERIFY(bstrDesc.LoadString(_Module.GetResourceInstance(), IDS_DESCRIPTION));
	*prgFlags = bstrDesc.Detach();
	return S_OK;
}

