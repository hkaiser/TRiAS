///////////////////////////////////////////////////////////////////////////////
// Connected CTF for maintenance of coordinate system configuration
// File: ConnectedCtf.cpp

#include "fakemfcp.hxx"
#include "fakemfc.h"
#include "strings.h"

#include <itoolbar.h>
#include <toolguid.h>

#include "Wrapper.h"		// SmartInterfaces
#include "ConnectedCtf.h"

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
			THROW_FAILED_HRESULT(AtlAdvise (m_Cont, (ITRiASNotificationSink *)this, IID_ITRiASNotificationSink, &m_dwCookie));
		} else
			DisConnectFromServer();

	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}

	return NOERROR;
}

HRESULT CConnectedCtf::DisConnectFromServer (void)
{
HRESULT hr = NOERROR;

	if (NULL != (IUnknown *)m_Cont && 0 != m_dwCookie) {
	WUnknown Unk (this);	// uns festhalten

		hr = AtlUnadvise (m_Cont, IID_ITRiASNotificationSink, m_dwCookie);
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
	switch (se) {
	case SERVEREVT_ServerToClose:	// das letzte vom Tage
		DisConnectFromServer();
		break;
	}

	return NOERROR;
}

STDMETHODIMP CConnectedCtf::ProjectEvent (long hPr, PROJECTEVT pe, VARIANT)
{
	switch (pe) {
	case PROJECTEVT_ProjectOpened:
	case PROJECTEVT_ReReadHeader:
		LoadCTF();
		break;

//	case PROJECTEVT_ProjectToClose:
	case PROJECTEVT_ProjectClosed:		// wirklich erst, wenn alles vorbei ist
		ReleaseCTF();
		break;
	}

	return NOERROR;
}

STDMETHODIMP CConnectedCtf::GeoViewEvent (long hPr, GEOVIEWEVT ve, VARIANT)
{
	return NOERROR;
}

STDMETHODIMP CConnectedCtf::GeoClassEvent (long hPr, GEOCLASSEVT ce, long ulIdent)
{
	return NOERROR;
}

STDMETHODIMP CConnectedCtf::GeoObjectEvent (long hPr, GEOOBJECTEVT oe, long lONr)
{
	return NOERROR;
}

STDMETHODIMP CConnectedCtf::GeoFeatureEvent (long hPr, GEOFEATUREEVT fe, long ulMCode)
{
	return NOERROR;
}

STDMETHODIMP CConnectedCtf::GeoRelationEvent (long hPr, GEORELATIONEVT re, long ulRCode)
{
	return NOERROR;
}

STDMETHODIMP CConnectedCtf::ObjectWindowEvent (OBJWNDEVT oe, long hORWnd)
{
	return NOERROR;
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
	DELETE(m_pCTF);
}

