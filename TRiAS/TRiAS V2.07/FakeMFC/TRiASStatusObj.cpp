// TRiASStatusObj.cpp : Implementation of CTRiASStatusBarObj

#include "fakemfcp.hxx"
#include <xtensnn.h>

#include <itoolbar.h>
#include <dtoolbar.h>
#include <toolguid.h>
#include <dirisole.h>

#include "Wrapper.h"		// SmartInterfaces

#include "mainfrm.h"
#include "TRiASStatusBar.h"
#include "TRiASStatusObj.h"
#include "TRiASCmdUI.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// zusätzlich benötigte SmartInterfaces
DefineSmartInterface(TRiASBarInstallControl);
DefineSmartInterface(EnumConnections);

///////////////////////////////////////////////////////////////////////////////
// Basisklassen fertig initialisieren
HRESULT CTRiASStatusBarObj::FinalConstruct (void)
{
	return S_OK;
}

CTRiASStatusBarObj::~CTRiASStatusBarObj(void)
{ 
	DELETE(m_pStatusBar);				// jetzt Toolbar verabschieden
}

/////////////////////////////////////////////////////////////////////////////
// *** ITRiASBar specific functions ***
STDMETHODIMP CTRiASStatusBarObj::GetBarStyle (
	LPSTR pName, ULONG ulLen, ULONG *pulWritten/*=NULL*/, 
	DWORD *pdwStyle/*=NULL*/, DWORD *pdwStyleEx/*=NULL*/)
{
	ASSERT(NULL != m_pStatusBar);
	return m_pStatusBar -> GetBarStyleEx (pName, ulLen, pulWritten, pdwStyle, pdwStyleEx);
}

STDMETHODIMP CTRiASStatusBarObj::SetBarStyle (LPCSTR pcName, DWORD dwStyle, DWORD dwStyleEx, bool fDelay)
{
	ASSERT(NULL != m_pStatusBar);
	return m_pStatusBar -> SetBarStyleEx (pcName, dwStyle, dwStyleEx, fDelay);
}

STDMETHODIMP CTRiASStatusBarObj::FloatBar (POINT pt, DWORD dwStyle)
{
	ASSERT(NULL != m_pStatusBar);
	return E_NOTIMPL;
}

STDMETHODIMP CTRiASStatusBarObj::DockBar (UINT uiWhere, LPCRECT pcRc/*=NULL*/)
{
	ASSERT(NULL != m_pStatusBar);
	return E_NOTIMPL;
}

STDMETHODIMP CTRiASStatusBarObj::IsFloating (void)
{
	ASSERT(NULL != m_pStatusBar);
	return S_FALSE;
}

STDMETHODIMP CTRiASStatusBarObj::GetBarID (UINT *puiID)
{
	ASSERT(NULL != m_pStatusBar);
	return m_pStatusBar -> GetBarID (puiID);
}

STDMETHODIMP CTRiASStatusBarObj::GetBarHandle (HWND *phWnd)
{
	ASSERT(NULL != m_pStatusBar);
	return m_pStatusBar -> GetBarHandle (phWnd);
}

STDMETHODIMP CTRiASStatusBarObj::OnCmdMsg (UINT uiID, int nCode, void *pExtra1, void *pExtra2)
{
	ASSERT(NULL != m_pStatusBar);
	return m_pStatusBar -> OnCmdMessage (uiID, nCode, pExtra1, (AFX_CMDHANDLERINFO *)pExtra2);
}


STDMETHODIMP CTRiASStatusBarObj::DeleteItem (int iIndex)
{
	ASSERT(NULL != m_pStatusBar);

HRESULT hr = NOERROR;
UINT uiID = 0;

	try {
	UINT uiStyle = m_pStatusBar -> GetPaneStyle (iIndex);

		uiID = m_pStatusBar -> GetItemID (iIndex);

	// nachfragen, ob wirklich gelöscht werden soll
		hr = OnRequestDeleteItem (uiID, DWORD(uiStyle));
		if (S_OK != hr) _com_issue_error(hr);

	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}

// nur entfernen, wenn kein Fehler und keiner was dagegen hat
	hr = m_pStatusBar -> DeleteItem (iIndex);
	OnDeletedItem (uiID);

return hr;
}

STDMETHODIMP CTRiASStatusBarObj::CommandToIndex (UINT uiID, int *piIndex)
{
	ASSERT(NULL != m_pStatusBar);
	return m_pStatusBar -> CommandToIndex (uiID, piIndex);
}

STDMETHODIMP CTRiASStatusBarObj::GetItemRect (int iIndex, LPRECT pRc)
{
	ASSERT(NULL != m_pStatusBar);
	return m_pStatusBar -> GetItemRect (iIndex, pRc);
}

///////////////////////////////////////////////////////////////////////////////
// *** ITRiASStatusBar specific functions ***
STDMETHODIMP CTRiASStatusBarObj::SetSimple (BOOL fSimple)
{
	ASSERT(NULL != m_pStatusBar);
	return E_NOTIMPL;
}

STDMETHODIMP CTRiASStatusBarObj::GetPanes (int iCnt, int *piWitdhs/*=NULL*/, int *piRetrieved)
{
	ASSERT(NULL != m_pStatusBar);
	return E_NOTIMPL;
}

STDMETHODIMP CTRiASStatusBarObj::SetPanes (const int *piWitdhs, int iCnt)
{
	ASSERT(NULL != m_pStatusBar);
	return E_NOTIMPL;
}

STDMETHODIMP CTRiASStatusBarObj::GetPaneInfo (int iIndex, UINT *puiID/*=NULL*/, int *piWidth/*=NULL*/)
{
	ASSERT(NULL != m_pStatusBar);
	return E_NOTIMPL;
}

STDMETHODIMP CTRiASStatusBarObj::AddPanes (const int *piWidths, int iCnt, ITRiASUIOwner *pIOwner)
{
	ASSERT(NULL != m_pStatusBar);
	return E_NOTIMPL;
}

STDMETHODIMP CTRiASStatusBarObj::InsertPane (THIS_ int iIndex, int iWidth, ITRiASUIOwner *pIOwner)
{
	ASSERT(NULL != m_pStatusBar);
	return E_NOTIMPL;
}

STDMETHODIMP CTRiASStatusBarObj::SetPaneInfo (int iIndex, UINT uiID, int iWidth)
{
	ASSERT(NULL != m_pStatusBar);
	return E_NOTIMPL;
}

STDMETHODIMP CTRiASStatusBarObj::GetPaneText (int iIndex, LPSTR pText, ULONG ulLen, DWORD *pdwStyle/*=NULL*/)
{
	ASSERT(NULL != m_pStatusBar);
	return E_NOTIMPL;
}

STDMETHODIMP CTRiASStatusBarObj::SetPaneText (int iIndex, LPCSTR pcText, DWORD dwStyle, BOOL fUpdate)
{
	ASSERT(NULL != m_pStatusBar);
	return E_NOTIMPL;
}

///////////////////////////////////////////////////////////////////////////////
// *** IPersist methods
STDMETHODIMP CTRiASStatusBarObj::GetClassID (CLSID *pClassID)
{
	if (NULL == pClassID) return E_POINTER;

	*pClassID = CLSID_TRiASStatusBar;
	return NOERROR;
}

// *** IPersistStreamInit functions
STDMETHODIMP CTRiASStatusBarObj::IsDirty (void)
{
	return E_NOTIMPL;
}

STDMETHODIMP CTRiASStatusBarObj::Load (LPSTREAM pStrm)
{
	return E_NOTIMPL;
}

STDMETHODIMP CTRiASStatusBarObj::Save (LPSTREAM pStrm, BOOL fClearDirty)
{
	return E_NOTIMPL;
}

STDMETHODIMP CTRiASStatusBarObj::GetSizeMax (ULARGE_INTEGER * pcbSize)
{
	return E_NOTIMPL;
}

STDMETHODIMP CTRiASStatusBarObj::InitNew (void)
{
	ASSERT(NULL == m_pStatusBar);

	TRY { 
		m_pStatusBar = new CTRiASStatusBar((ITRiASStatusBar *)this);
	} CATCH (CMemoryException, e) {
		return E_OUTOFMEMORY;
	} END_CATCH

	return m_pStatusBar -> InitNew();
}

///////////////////////////////////////////////////////////////////////////////
// Connections bedienen
HRESULT CTRiASStatusBarObj::OnRequestDeleteItem (UINT uiCtrlID, DWORD dwStyle) 
{
// Enumerator besorgen
WEnumConnections Conns;
HRESULT hr = m_cpTRiASBarNotifySink.EnumConnections (Conns.ppi());

	if (FAILED(hr)) return hr;

// alle registrierten Connections abarbeiten
	try {
	CONNECTDATA cd;

		for (Conns -> Reset(); 
			 S_OK == Conns -> Next (1, &cd, NULL); /**/) 
		{
		WTRiASBarNotifySink Sink(cd.pUnk);		// throws HRESULT

			cd.pUnk -> Release();		// Connection freigeben
			hr = Sink -> OnRequestDeleteItem (this, uiCtrlID, dwStyle);
			if (S_OK != hr)
				return hr;		// nicht zulassen
		}
	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}

return NOERROR;
}

HRESULT CTRiASStatusBarObj::OnDeletedItem (UINT uiCtrlID) 
{
// Enumerator besorgen
WEnumConnections Conns;
HRESULT hr = m_cpTRiASBarNotifySink.EnumConnections (Conns.ppi());

	if (FAILED(hr)) return hr;

// alle registrierten Connections abarbeiten
	try {
	CONNECTDATA cd;

		for (Conns -> Reset(); 
			 S_OK == Conns -> Next (1, &cd, NULL); /**/) 
		{
		WTRiASBarNotifySink Sink = cd.pUnk;		// throws HRESULT

			cd.pUnk -> Release();		// Connection freigeben
			Sink -> OnDeletedItem (this, uiCtrlID);
		// evtl. Fehler ignorieren
		}
	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}

return NOERROR;
}

