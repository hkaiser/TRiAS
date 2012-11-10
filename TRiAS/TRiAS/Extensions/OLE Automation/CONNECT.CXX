// ConnectionKlasse selbst (Node in der Liste aller Connections ---------------
// File: CONNECT.CXX

#include "precomp.hxx"

#include <eb.h>		// für CBScriptConnection

#include "oleguid.h"
#include "connect.hxx"

#if defined(_DEBUG) && defined(WIN32)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

///////////////////////////////////////////////////////////////////////////////
// Klasse, die von App registriert wird, um Notifikationen zu empfangen 
CAppConnection *CAppConnection::CreateInstance (CTriasApp *pApp)
{
CAppConnection *pPnt = new CAppConnection (pApp);

	if (pPnt == NULL || !pPnt -> FInit()) {
		DELETE_OBJ (pPnt);
		return NULL;
	}
	pPnt -> AddRef();
	
return pPnt;
}

bool CAppConnection::FInit (void)
{
	return true;
}

CAppConnection::CAppConnection (CTriasApp *pApp)
{
	CONSTRUCT_TRACE(CAppConnection);

	m_pApp = pApp;
//	ADDREF(m_pApp);		// muß App am leben halten
	
	m_dwRefCnt = 0;
}

CAppConnection::~CAppConnection (void)
{
	DESTRUCT_TRACE(CAppConnection);
	
//	RELEASE(m_pApp);
}

// *** IUnknown members -------------------------------------------------------
STDMETHODIMP CAppConnection::QueryInterface (REFIID riid, LPVOID *ppv)
{
	*ppv=NULL;
	if (riid == IID_IUnknown || riid == IID_INotificationSink2)
		*ppv = (LPVOID)this;

	if (*ppv != NULL) {
		((LPUNKNOWN)*ppv) -> AddRef();
		return NOERROR;
	}

return ResultFromScode (E_NOINTERFACE);
}

STDMETHODIMP_(ULONG) CAppConnection::AddRef (void)
{
	ADDREF_TRACE(CAppConnection, m_dwRefCnt);
	++m_dwRefCnt;

return m_dwRefCnt;
}

STDMETHODIMP_(ULONG) CAppConnection::Release (void)
{
	RELEASE_TRACE(CAppConnection, m_dwRefCnt);

	if (--m_dwRefCnt != 0L)
		return m_dwRefCnt;

	delete this;
	return 0;
}


// *** INotificationSink2 members ---------------------------------------------
// ein CGeoDoc interessieren nur einzelne Notifications
STDMETHODIMP_(ULONG) CAppConnection::ServerEvent (SERVEREVT) 
{ 
	return false; 
}

STDMETHODIMP_(ULONG) CAppConnection:: ProjectEvent (PROJECTEVT pe, LPCTSTR pProj)
{
// wenn Projekt geschlossen wurde, dann Dokument freigeben
	switch (pe) {
	case PROJECTEVT_ProjectClosed:
		m_pApp -> FInvDoc(pProj);	// gibt Doc möglicherweise frei!
		break;

	case PROJECTEVT_ProjectOpened:
		if (NULL == m_pApp -> FFindDoc (pProj))
			m_pApp -> FGetDocDisp (pProj);
		break;
	}
		
return false;
}

STDMETHODIMP_(ULONG) CAppConnection::GeoViewEvent (GEOVIEWEVT ve, LPCTSTR pView)
{
	return false;		// Notification immer weiterleiten
}

STDMETHODIMP_(ULONG) CAppConnection::GeoClassEvent (GEOCLASSEVT ce, ULONG ulIdent)
{
	return false;		// Notification immer weiterleiten
}

STDMETHODIMP_(ULONG) CAppConnection:: GeoObjectEvent (GEOOBJECTEVT oe, LONG lONr)
{
	return false;		// Notification immer weiterleiten
}

STDMETHODIMP_(ULONG) CAppConnection::GeoFeatureEvent (GEOFEATUREEVT fe, ULONG ulMCode)
{
	return false;
}

STDMETHODIMP_(ULONG) CAppConnection::GeoRelationEvent (GEORELATIONEVT re, ULONG ulRCode)
{
	return false;
}

STDMETHODIMP_(ULONG) CAppConnection::ObjectWindowEvent (OBJWNDEVT oe, HWND hORWnd)
{
	return false;
}

STDMETHODIMP_(ULONG) CAppConnection::MenuInitEvent (HMENU hMenu, LPARAM lParam, HWND hWnd)
{
	return false;
}

STDMETHODIMP_(ULONG) CAppConnection::MenuSelectEvent (UINT uiMenuID, HMENU hMenu, HWND hWnd)
{
	return false;
}

STDMETHODIMP_(ULONG) CAppConnection::MenuCommandEvent (WPARAM wParam, HWND hWnd)
{
	return false;
}


// Klasse, die von Document registriert wird, um Notifikationen zu empfangen --
CDocumentConnection *CDocumentConnection::CreateInstance (CGeoDoc *pDoc)
{
CDocumentConnection *pPnt = new CDocumentConnection (pDoc);

	if (pPnt == NULL || !pPnt -> FInit()) {
		DELETE_OBJ (pPnt);
		return NULL;
	}
	pPnt -> AddRef();
	
return pPnt;
}

bool CDocumentConnection::FInit (void)
{
	return true;
}

CDocumentConnection::CDocumentConnection (CGeoDoc *pDoc)
{
	CONSTRUCT_TRACE(CDocumentConnection);

	m_dwRefCnt = 0;

	m_pDoc = pDoc;
	ADDREF_CAST(_DDocument, m_pDoc);	// muß Doc am leben halten
}

CDocumentConnection::~CDocumentConnection (void)
{
	DESTRUCT_TRACE(CDocumentConnection);
	
	RELEASE_CAST(_DDocument, m_pDoc);		// Document wieder loslassen
}

// *** IUnknown members -------------------------------------------------------
STDMETHODIMP CDocumentConnection::QueryInterface (REFIID riid, LPVOID *ppv)
{
	*ppv=NULL;
	if (riid == IID_IUnknown || riid == IID_INotificationSink2)
		*ppv = (LPVOID)this;

	if (*ppv != NULL) {
		((LPUNKNOWN)*ppv) -> AddRef();
		return NOERROR;
	}

return ResultFromScode (E_NOINTERFACE);
}

STDMETHODIMP_(ULONG) CDocumentConnection::AddRef (void)
{
	ADDREF_TRACE(CDocumentConnection, m_dwRefCnt);
	++m_dwRefCnt;

return m_dwRefCnt;
}

STDMETHODIMP_(ULONG) CDocumentConnection::Release (void)
{
	RELEASE_TRACE(CDocumentConnection, m_dwRefCnt);

	if (--m_dwRefCnt != 0L)
		return m_dwRefCnt;

	delete this;
	return 0;
}


// *** INotificationSink2 members ---------------------------------------------
// ein CGeoDoc interessieren nur einzelne Notifications
STDMETHODIMP_(ULONG) CDocumentConnection::ServerEvent (SERVEREVT) 
{ 
	return false; 
}

STDMETHODIMP_(ULONG) CDocumentConnection::ProjectEvent (PROJECTEVT pe, LPCTSTR pcName)
{
	switch (pe) {
	case PROJECTEVT_RenamingFile:
		m_pDoc -> RenamingFile();
		break;

	case PROJECTEVT_FileRenamed:
		m_pDoc -> Rename (pcName);
		break;

	case PROJECTEVT_ProjectIsNotDirty:
		m_pDoc -> ProjectSaved();
		break;

	case PROJECTEVT_ProjectIsDirty:
		break;

	default:
		break;
	}
	return false;
}

STDMETHODIMP_(ULONG) CDocumentConnection::GeoViewEvent (GEOVIEWEVT ve, LPCTSTR pView)
{
	if (ve == GEOVIEWEVT_ViewDeleted)	// Sicht wurde gelöscht
		m_pDoc -> FInvView (pView);
	return false;		// Notification immer weiterleiten
}

STDMETHODIMP_(ULONG) CDocumentConnection::GeoClassEvent (GEOCLASSEVT ce, ULONG ulIdent)
{
	if (ce == GEOCLASSEVT_ClassDeleted)	// Objektklasse wurde gelöscht
		m_pDoc -> FInvClass (ulIdent);
	return false;		// Notification immer weiterleiten
}

STDMETHODIMP_(ULONG) CDocumentConnection::GeoObjectEvent (GEOOBJECTEVT oe, LONG lONr)
{
	switch (oe) {
	case GEOOBJECTEVT_ObjectDeleted:	// Objekt wurde gelöscht
		m_pDoc -> FInvObject (lONr);
		break;

	case GEOOBJECTEVT_ObjectClassified:	// Objekt wurde umklassifiziert
		m_pDoc -> ObjectClassified (lONr);
		break;

	default:
		break;
	}
	return false;		// Notification immer weiterleiten
}

STDMETHODIMP_(ULONG) CDocumentConnection::GeoFeatureEvent (GEOFEATUREEVT fe, ULONG ulMCode)
{
	return false;
}

STDMETHODIMP_(ULONG) CDocumentConnection::GeoRelationEvent (GEORELATIONEVT re, ULONG ulRCode)
{
	return false;
}

STDMETHODIMP_(ULONG) CDocumentConnection::ObjectWindowEvent (OBJWNDEVT oe, HWND hORWnd)
{
	switch (oe) {
	case OBJWNDEVT_WindowCreated:
		m_pDoc -> FGetObjWinDisp (hORWnd);
		break;

	case OBJWNDEVT_WindowToDestroy:
		m_pDoc -> FInvObjWin (hORWnd);
		break;
	}
	return false;
}

STDMETHODIMP_(ULONG) CDocumentConnection::MenuInitEvent (HMENU hMenu, LPARAM lParam, HWND hWnd)
{
	return false;
}

STDMETHODIMP_(ULONG) CDocumentConnection::MenuSelectEvent (UINT uiMenuID, HMENU hMenu, HWND hWnd)
{
	return false;
}

STDMETHODIMP_(ULONG) CDocumentConnection::MenuCommandEvent (WPARAM wParam, HWND hWnd)
{
	return false;
}

