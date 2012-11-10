// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 17.03.2002 13:35:23 
//
// @doc
// @module MapReferenced.cpp | Definition of the <c CMapReferenced> class

// MapReferenced.cpp : Implementation of CMapReferenced
#include "stdafx.h"

#include "resource.h"
#include "MMRefer.h"
#include "../MapCtrlImpl.h"
#include "MapReferenced.h"

/////////////////////////////////////////////////////////////////////////////
// CMapReferenced

HRESULT CMapReferenced::FinalConstruct() {
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

void CMapReferenced::FinalRelease() {
}

STDMETHODIMP CMapReferenced::GetDisplayName(/*[out]*/ BSTR* strDisplay) {
	if(!strDisplay)
		return E_POINTER;
//	*strDisplay = ::SysAllocString( L"Rasterkarte mit Referenzinformationen\\Karte mit bekannten Eckpunkten" );

CComBSTR S;

	VERIFY(S.LoadString (_Module.GetResourceInstance(), IDS_DISPLAYNAME_REF));
	*strDisplay = S.Detach();
	return S_OK;
}

STDMETHODIMP CMapReferenced::NeedFixPoints(/*[in,out]*/ long* pNeedPoints ) 
{
	if( !pNeedPoints )
		return E_POINTER;
	*pNeedPoints = TRUE;
	return S_OK;
}
