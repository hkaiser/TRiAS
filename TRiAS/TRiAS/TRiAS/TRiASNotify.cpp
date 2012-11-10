// TRiASNotify.cpp - Implementation des ConnectionPoints für 
// ITRiASNotificationSink

#include "triaspre.hxx"

#include <dirisole.h>
#include "extmain3.hxx"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// benötigte Interfaces
DefineSmartInterface(EnumConnections);
DefineSmartInterface(TRiASNotificationSink);
DefineSmartInterface(TRiASSysNotificationSink);

///////////////////////////////////////////////////////////////////////////////
// ITRiASNotificationSink bedienen

// ServerEvent
HRESULT ExtensionList::ServerEvent (SERVEREVT se)
{
	TX_ASSERT(NULL != m_ppCP[0]);

// Enumerator besorgen
WEnumConnections Conns;
HRESULT hr = m_ppCP[0] -> EnumConnections (Conns.ppi());

	if (FAILED(hr)) return hr;

// alle registrierten Connections abarbeiten
	try {
	CONNECTDATA cd;

		for (Conns -> Reset(); 
			 S_OK == Conns -> Next (1, &cd, NULL); /**/) 
		{
		WTRiASNotificationSink Sink = cd.pUnk;		// throws HRESULT

			cd.pUnk -> Release();				// Connection freigeben
			cd.pUnk = NULL;

			if (S_OK != (hr = Sink -> ServerEvent (se)))
				return hr;
		}
	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}

return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// ProjectEvent
HRESULT ExtensionList::ProjectEvent (PROJECTEVT pe, LPCTSTR pcPrj) 
{
	TX_ASSERT(NULL != m_ppCP[0]);

// Enumerator besorgen
WEnumConnections Conns;
HRESULT hr = m_ppCP[0] -> EnumConnections (Conns.ppi());

	if (FAILED(hr)) return hr;

// alle registrierten Connections abarbeiten
	try {
	CONNECTDATA cd;

		for (Conns -> Reset(); 
			 S_OK == Conns -> Next (1, &cd, NULL); /**/) 
		{
		WTRiASNotificationSink Sink = cd.pUnk;		// throws HRESULT

			cd.pUnk -> Release();				// Connection freigeben
			cd.pUnk = NULL;

			if (S_OK != (hr = Sink -> ProjectEvent (pe, pcPrj)))
				return hr;
		}
	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}

return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// GeoViewEvent
HRESULT ExtensionList::GeoViewEvent (GEOVIEWEVT ve, void *pData) 
{
	TX_ASSERT(NULL != m_ppCP[0]);

// Enumerator besorgen
WEnumConnections Conns;
HRESULT hr = m_ppCP[0] -> EnumConnections (Conns.ppi());

	if (FAILED(hr)) return hr;

// alle registrierten Connections abarbeiten
	try {
	CONNECTDATA cd;

		for (Conns -> Reset(); 
			 S_OK == Conns -> Next (1, &cd, NULL); /**/) 
		{
		WTRiASNotificationSink Sink = cd.pUnk;		// throws HRESULT

			cd.pUnk -> Release();				// Connection freigeben
			cd.pUnk = NULL;

			if (S_OK != (hr = Sink -> GeoViewEvent (ve, pData)))
				return hr;
		}
	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}

return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// GeoClassEvent
HRESULT ExtensionList::GeoClassEvent (GEOCLASSEVT ce, ULONG ulIdent) 
{
	TX_ASSERT(NULL != m_ppCP[0]);

// Enumerator besorgen
WEnumConnections Conns;
HRESULT hr = m_ppCP[0] -> EnumConnections (Conns.ppi());

	if (FAILED(hr)) return hr;

// alle registrierten Connections abarbeiten
	try {
	CONNECTDATA cd;

		for (Conns -> Reset(); 
			 S_OK == Conns -> Next (1, &cd, NULL); /**/) 
		{
		WTRiASNotificationSink Sink = cd.pUnk;		// throws HRESULT

			cd.pUnk -> Release();				// Connection freigeben
			cd.pUnk = NULL;

			if (S_OK != (hr = Sink -> GeoClassEvent (ce, ulIdent)))
				return hr;
		}
	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}

return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// GeoObjectEvent
HRESULT ExtensionList::GeoObjectEvent (GEOOBJECTEVT oe, LONG lONr) 
{
	TX_ASSERT(NULL != m_ppCP[0]);

// Enumerator besorgen
WEnumConnections Conns;
HRESULT hr = m_ppCP[0] -> EnumConnections (Conns.ppi());

	if (FAILED(hr)) return hr;

// alle registrierten Connections abarbeiten
	try {
	CONNECTDATA cd;

		for (Conns -> Reset(); 
			 S_OK == Conns -> Next (1, &cd, NULL); /**/) 
		{
		WTRiASNotificationSink Sink = cd.pUnk;		// throws HRESULT

			cd.pUnk -> Release();				// Connection freigeben
			cd.pUnk = NULL;

			if (S_OK != (hr = Sink -> GeoObjectEvent (oe, lONr)))
				return hr;
		}
	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}

return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// GeoFeatureEvent
HRESULT ExtensionList::GeoFeatureEvent (GEOFEATUREEVT fe, ULONG ulMCode) 
{
	TX_ASSERT(NULL != m_ppCP[0]);

// Enumerator besorgen
WEnumConnections Conns;
HRESULT hr = m_ppCP[0] -> EnumConnections (Conns.ppi());

	if (FAILED(hr)) return hr;

// alle registrierten Connections abarbeiten
	try {
	CONNECTDATA cd;

		for (Conns -> Reset(); 
			 S_OK == Conns -> Next (1, &cd, NULL); /**/) 
		{
		WTRiASNotificationSink Sink = cd.pUnk;		// throws HRESULT

			cd.pUnk -> Release();				// Connection freigeben
			cd.pUnk = NULL;

			if (S_OK != (hr = Sink -> GeoFeatureEvent (fe, ulMCode)))
				return hr;
		}
	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}

return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// GeoRelationEvent
HRESULT ExtensionList::GeoRelationEvent (GEORELATIONEVT re, ULONG ulRCode) 
{
	TX_ASSERT(NULL != m_ppCP[0]);

// Enumerator besorgen
WEnumConnections Conns;
HRESULT hr = m_ppCP[0] -> EnumConnections (Conns.ppi());

	if (FAILED(hr)) return hr;

// alle registrierten Connections abarbeiten
	try {
	CONNECTDATA cd;

		for (Conns -> Reset(); 
			 S_OK == Conns -> Next (1, &cd, NULL); /**/) 
		{
		WTRiASNotificationSink Sink = cd.pUnk;		// throws HRESULT

			cd.pUnk -> Release();				// Connection freigeben
			cd.pUnk = NULL;

			if (S_OK != (hr = Sink -> GeoRelationEvent (re, ulRCode)))
				return hr;
		}
	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}

return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// ITRiASSysNotificationSink bedienen

///////////////////////////////////////////////////////////////////////////////
// WindowsMessage
HRESULT ExtensionList::WindowsMessage (HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
	TX_ASSERT(NULL != m_ppCP[1]);

// Enumerator besorgen
WEnumConnections Conns;
HRESULT hr = m_ppCP[1] -> EnumConnections (Conns.ppi());

	if (FAILED(hr)) return hr;

// alle registrierten Connections abarbeiten
	try {
	CONNECTDATA cd;

		for (Conns -> Reset(); 
			 S_OK == Conns -> Next (1, &cd, NULL); /**/) 
		{
		WTRiASSysNotificationSink Sink = cd.pUnk;		// throws HRESULT

			cd.pUnk -> Release();				// Connection freigeben
			cd.pUnk = NULL;

			if (S_OK != (hr = Sink -> WindowsMessage (hWnd, uiMsg, wParam, lParam)))
				return hr;
		}
	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}

return NOERROR;
}

