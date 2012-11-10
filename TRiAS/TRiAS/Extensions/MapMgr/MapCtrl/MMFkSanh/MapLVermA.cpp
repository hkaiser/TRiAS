// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 17.03.2002 13:34:30 
//
// @doc
// @module MapLVermA.cpp | Definition of the <c CMapLVermA> class

// CMapLVermA.cpp : Implementation of CCMapLVermA

#include "stdafx.h"

#include "resource.h"
#include "MMFkSanh.h"
#include "../MapCtrlImpl.h"
#include "MapLVermA.h"

/////////////////////////////////////////////////////////////////////////////
// CCMapLVermA

HRESULT CMapLVermA::FinalConstruct() {
//	_ASSERTE( !!m_pCS && !!m_pGCS && !!m_pPCS );
//	if( !m_pCS || !m_pGCS || !m_pPCS )
//		return E_FAIL;
//	m_pCS->put_CoordSystemType( tcsCS_Projected );
//	m_pGCS->put_GeodeticDatum( tcsGD_Pulkovo1942 );
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

void CMapLVermA::FinalRelease() 
{
}

STDMETHODIMP CMapLVermA::GetDisplayName(/*[out]*/ BSTR* strDisplay) 
{
	if(!strDisplay)
		return E_POINTER;
//	*strDisplay = ::SysAllocString( L"Rasterkarte mit Referenzinformationen\\Flurkarte des LVermA Sachsen Anhalt" );

CComBSTR S;

	VERIFY(S.LoadString (_Module.GetResourceInstance(), IDS_DISPLAYNAME_FK));
	*strDisplay = S.Detach();
	return S_OK;
}

namespace MOSS {
bool Parse( LPCTSTR lpszString, CoordMap &M, GCPList &L );
}

STDMETHODIMP CMapLVermA::CheckPictureFile(ITopoPict* pServer, long* pValid) {
	if( !pServer || !pValid )
		return E_POINTER;

	if( S_OK != ITopoMapImpl::CheckPictureFile(pServer, pValid) )
		return E_FAIL;
	CComVariant	v;
	USES_CONVERSION;
	pServer->GetTagValue( 270, &v );

	if( VT_BSTR != v.vt )
		return E_FAIL;

	HRESULT	hr = E_FAIL;
	try {
		CoordMap	M;
		GCPList		L;
		LPCTSTR	lpszData = W2A(v.bstrVal);
		if( MOSS::Parse( lpszData, M, L ) ) {
			CoordMap::iterator min = M.find(_T("min"));
			CoordMap::iterator max = M.find(_T("max"));
			// GCP's: LinksUnten, RechtsUnten, RechtsOben, LinksOben
			m_listOfGCP[0].m_ptGeoCoord = GEOPOINT( (*min).second.X, (*min).second.Y, 0 );
			m_listOfGCP[1].m_ptGeoCoord = GEOPOINT( (*max).second.X, (*min).second.Y, 0 );
			m_listOfGCP[2].m_ptGeoCoord = GEOPOINT( (*max).second.X, (*max).second.Y, 0 );
			m_listOfGCP[3].m_ptGeoCoord = GEOPOINT( (*min).second.X, (*max).second.Y, 0 );
			// danach die restlichen
			GCPList::iterator g;
			for( g = L.begin(); g != L.end(); g++ ) {
				m_listOfGCP.push_back( *g );
			}
			hr = S_OK;
		}
	} catch(...) {
		hr = E_UNEXPECTED;
	}
	return hr;
}
