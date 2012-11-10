// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 07.12.2000 22:24:00 
//
// @doc
// @module ConnectedCtf.cpp | Connected CTF for maintenance of coordinate system configuration

#include "StdAfx.h"

#include "triastlb.h"
#include "ConnectedCtf.h"

#if defined(_DEBUG)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // defined(_DEBUG)

///////////////////////////////////////////////////////////////////////////////
// Initialisierung
HRESULT CConnectedCtf::FinalConstruct(void)
{
char cbBuffer[_MAX_PATH];

	if (NULL != DEX_GetActiveProject(cbBuffer)) {
	// wenn Projekt bereits geˆffnet ist, dann laden
		if (!LoadCTF())
			return E_OUTOFMEMORY;
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Am TRiAS-ConnectionPoint ankoppeln

HRESULT CConnectedCtf::SetXtsnSite (ITriasXtensionSite *pSite)
{
	try {
		if (NULL != pSite) {
			m_Cont = pSite;		// throws HRESULT
			THROW_FAILED_HRESULT(AtlAdvise (m_Cont, (ITRiASNotificationSink *)this, __uuidof(ITRiASNotificationSink), &m_dwCookie));
		} else
			DisConnectFromServer();

	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}
	return S_OK;
}

HRESULT CConnectedCtf::DisConnectFromServer (void)
{
HRESULT hr = S_OK;

	if (NULL != (IUnknown *)m_Cont && 0 != m_dwCookie) {
	WUnknown Unk (this);	// uns festhalten

		hr = AtlUnadvise (m_Cont, __uuidof(ITRiASNotificationSink), m_dwCookie);
		if (SUCCEEDED(hr)) {
			m_dwCookie = 0L;
			m_Cont.Assign (NULL);	// Release()
		}
	}
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
// *** ITRiASNotificationSink specific functions ***
STDMETHODIMP CConnectedCtf::ServerEvent (SERVEREVT se)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState())

	switch (se) {
	case SERVEREVT_ServerToClose:	// das letzte vom Tage
		DisConnectFromServer();
		break;
	}
	return S_OK;
}

STDMETHODIMP CConnectedCtf::ProjectEvent (long hPr, PROJECTEVT pe, VARIANT)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState())
	switch (pe) {
	case PROJECTEVT_ProjectOpened:
	case PROJECTEVT_ReReadHeader:
		LoadCTF();
		break;

	case PROJECTEVT_ProjectClosed:		// wirklich erst, wenn alles vorbei ist
		ReleaseCTF();
		break;
	}
	return S_OK;
}

STDMETHODIMP CConnectedCtf::GeoViewEvent (long hPr, GEOVIEWEVT ve, VARIANT)
{
	return S_OK;
}

STDMETHODIMP CConnectedCtf::GeoClassEvent (long hPr, GEOCLASSEVT ce, long ulIdent)
{
	return S_OK;
}

STDMETHODIMP CConnectedCtf::GeoObjectEvent (long hPr, GEOOBJECTEVT oe, long lONr)
{
	return S_OK;
}

STDMETHODIMP CConnectedCtf::GeoFeatureEvent (long hPr, GEOFEATUREEVT fe, long ulMCode)
{
	return S_OK;
}

STDMETHODIMP CConnectedCtf::GeoRelationEvent (long hPr, GEORELATIONEVT re, long ulRCode)
{
	return S_OK;
}

STDMETHODIMP CConnectedCtf::ObjectWindowEvent (OBJWNDEVT oe, long hORWnd)
{
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// CTF specifics
bool CConnectedCtf::EnsureLoaded(void)
{
	if (NULL != m_pCTF)
		return true;
	return LoadCTF();
}

bool CConnectedCtf::LoadCTF (void)
{
	if (NULL != m_pCTF) {
		if (!m_pCTF -> Reload (true))
			return true;	// muﬂ nicht neu geladen laden

		ReleaseCTF();
	}

// wirklich neuladen
char cbBuffer[_MAX_PATH];

	if (NULL == DEX_GetActiveProject(cbBuffer))
		return false;

	ATLTRY(m_pCTF = new CCoordTransX);
	return (NULL != m_pCTF) ? true : false;
}

void CConnectedCtf::ReleaseCTF (void)
{
	DELETE_OBJ(m_pCTF);
}

