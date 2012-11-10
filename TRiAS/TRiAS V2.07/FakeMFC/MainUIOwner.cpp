// MainUIOwner.cpp : Implementation of ToolBarOwner for MainToolbar

#include "fakemfcp.hxx"
#include "fakemfc.h"

#include <itoolbar.h>
#include <toolguid.h>
#include <dirisole.h>

#include "Wrapper.h"		// SmartInterfaces
#include "fakemfc.hxx"

#include "MainUIOwner.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// CMainUIOwner
CMainUIOwner::CMainUIOwner(void)
{
	m_fOpenProject = false;
	m_fActiveView = false;
	m_fViewPainted = false;
}

// Am TRiAS-ConnectionPoint ankoppeln
HRESULT CMainUIOwner::SetXtsnSite (ITriasXtensionSite *pSite)
{
	try {
		m_Cont = pSite;		// throws HRESULT
		THROW_FAILED_HRESULT(AtlAdvise (m_Cont, (ITRiASNotificationSink *)this, IID_ITRiASNotificationSink, &m_dwCookie));

	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}

return NOERROR;
}

// Am TRiAS ConnectionPoint abkoppeln
HRESULT CMainUIOwner::DisConnectFromServer (void)
{
HRESULT hr = NOERROR;

	if (NULL != (IUnknown *)m_Cont && 0 != m_dwCookie) {
		hr = AtlUnadvise (m_Cont, IID_ITRiASNotificationSink, m_dwCookie);
		if (SUCCEEDED(hr)) {
			m_dwCookie = 0L;
			m_Cont.Assign (NULL);	// Release()
		}
	}
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
// Helper 
HRESULT GetTool (int uiID, int *piIndex)
{
	switch (uiID) {
	case ID_TOOL_SELECT:
		*piIndex = NUMARROW;
		return NOERROR;

	case ID_TOOL_ZOOM:
		*piIndex = NUMZOOM;
		return NOERROR;

	case ID_TOOL_SEARCH:
		*piIndex = NUMSCHERE;
		return NOERROR;

	case ID_TOOL_DISTANCE:
		*piIndex = NUMLINEAL;
		return NOERROR;

	case ID_TOOL_TEXT:
		*piIndex = NUMSCHRIFT;
		return NOERROR;
	}

	return E_FAIL;
}

/////////////////////////////////////////////////////////////////////////////
// *** ITRiASUIOwner specific functions ***

HRESULT CMainUIOwner::OnUpdateUI (ITRiASBar *pIBar, ITRiASCmdUI *pICmdUI)
{
	if (NULL == pIBar) return E_POINTER;

// Testen, ob überhaupt ein Projekt geöffnet ist
	if (!m_fOpenProject || !(m_fActiveView && m_fViewPainted)) {
		pICmdUI -> put_CheckState (0);
		pICmdUI -> put_IsEnabled (false);
		return NOERROR;
	}

// Projekt ist geöffnet, Werkzeuge abfragen
int uiID = 0;
int iIndex = -1;

	pICmdUI -> put_IsEnabled (true);
	pICmdUI -> get_CmdID (&uiID);		// ID des Buttons besorgen

HRESULT hr = GetTool (uiID, &iIndex);
	
	if (SUCCEEDED(hr)) 
		hr = pICmdUI -> put_CheckState (iIndex == DEX_GetActiveTool() ? 1 : 0);

	return hr;
}

HRESULT CMainUIOwner::OnSelect (ITRiASBar *pIBar, UINT uiID, LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten)
{
	if (NULL == pIBar || NULL == pBuffer || 0 == ulLen) 
		return E_POINTER;

	TRY {
	CString str;

		str.LoadString (uiID);

	ULONG ulToWrite = min (ulLen-1, ULONG(str.GetLength()));

		strncpy (pBuffer, str, ulToWrite);
		pBuffer[ulToWrite] = '\0';

		if (pulWritten)
			*pulWritten = ulToWrite;

	} CATCH (CMemoryException, e) {
		return E_OUTOFMEMORY;
	} END_CATCH

return NOERROR;
}

HRESULT CMainUIOwner::OnCommand (ITRiASBar *pIBar, UINT uiID, int nCode)
{
	if (NULL == pIBar) return E_POINTER;
	if (nCode != CN_COMMAND)
		return S_FALSE;

int iIndex = -1;
HRESULT hr = GetTool ((int)uiID, &iIndex);
	
	if (SUCCEEDED(hr))
		DEX_ChangeActiveTool(iIndex);

	return hr;
}

///////////////////////////////////////////////////////////////////////////////
// *** ITRiASNotificationSink specific functions ***
STDMETHODIMP CMainUIOwner::ServerEvent (SERVEREVT se)
{
	switch (se) {
	case SERVEREVT_ServerToClose:	// das letzte vom Tage
		DisConnectFromServer();		// ConnectionPoint abmelden
		break;
	}

return NOERROR;
}

STDMETHODIMP CMainUIOwner::ProjectEvent (long hPr, PROJECTEVT pe, VARIANT vProj)
{
	switch (pe) {
	case PROJECTEVT_ProjectOpened:
		m_fOpenProject = true;
		m_fViewPainted = false;
		break;

	case PROJECTEVT_ProjectToClose:
		m_fOpenProject = false;
		m_fViewPainted = false;
		break;
	}

return NOERROR;
}

STDMETHODIMP CMainUIOwner::GeoViewEvent (long hPr, GEOVIEWEVT ve, VARIANT vData)
{
	switch (ve) {
	case GEOVIEWEVT_ViewSelected:
		m_fActiveView = (VT_BSTR == vData.vt && NULL != V_BSTR(&vData)) ? true : false;
		break;

	case GEOVIEWEVT_PaintingView:
		m_fViewPainted = true;
		break;
	}
	return NOERROR;
}

STDMETHODIMP CMainUIOwner::GeoClassEvent (long hPr, GEOCLASSEVT ce, long ulIdent)
{
	return NOERROR;
}

STDMETHODIMP CMainUIOwner::GeoObjectEvent (long hPr, GEOOBJECTEVT oe, long lONr)
{
	return NOERROR;
}

STDMETHODIMP CMainUIOwner::GeoFeatureEvent (long hPr, GEOFEATUREEVT fe, long ulMCode)
{
	return NOERROR;
}

STDMETHODIMP CMainUIOwner::GeoRelationEvent (long hPr, GEORELATIONEVT re, long ulRCode)
{
	return NOERROR;
}

STDMETHODIMP CMainUIOwner::ObjectWindowEvent (OBJWNDEVT oe, long hORWnd)
{
	return NOERROR;
}
