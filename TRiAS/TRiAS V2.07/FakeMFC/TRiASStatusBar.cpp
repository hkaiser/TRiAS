// TRiASStatusBar.cpp : implementation file
//

#include "fakemfcp.hxx"
#include "fakemfc.h"
#include <xtensnn.h>

#include <itoolbar.h>
#include <dtoolbar.h>
#include <toolguid.h>
#include <dirisole.h>

#include "Wrapper.h"		// SmartInterfaces
#include "mainfrm.h"
#include "fakemfc.hxx"

#include "TRiASCmdUI.h"
#include "TRiASStatusBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTRiASStatusBar

CTRiASStatusBar::CTRiASStatusBar(ITRiASStatusBar *pIBar)
{
	m_pMainFrm = (CMainFrame *)AfxGetMainWnd();
	m_pIBar = pIBar;		// kein AddRef()!, fully contained
	m_dwFlags = 0L;
}

CTRiASStatusBar::~CTRiASStatusBar()
{
	if (m_pDockSite != NULL) {
		m_pDockSite->RemoveControlBar(this);
		m_pDockSite = NULL;
	} 
	m_pMainFrm = NULL;		// wird nicht mehr gebraucht
	m_pIBar = NULL;
}


BEGIN_MESSAGE_MAP(CTRiASStatusBar, CStatusBar)
	//{{AFX_MSG_MAP(CTRiASStatusBar)
	ON_WM_NCDESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////////////////
// sonstige Funktionalität
HRESULT CTRiASStatusBar::InitNew (void)
{
	AFX_MANAGE_STATE(AfxGetModuleState());
    ASSERT_VALID(this);
	ASSERT_VALID(m_pMainFrm);

	if (!Create (m_pMainFrm, WS_CHILD|CBRS_BOTTOM, AFX_IDW_STATUS_BAR))
		return ResultFromScode (E_FAIL);

	m_pMainFrm -> AddNewBar (m_pIBar);		// jetzt hier, damit alle von außen das geleiche tun können
	m_pMainFrm -> ShowControlBar (this, false, false);

return NOERROR;
}

HRESULT CTRiASStatusBar::RemoveBar (void)
{
	AFX_MANAGE_STATE(AfxGetModuleState());
    ASSERT_VALID(this);
	ASSERT_VALID(m_pMainFrm);

	return m_pMainFrm -> RemoveBar (m_pIBar);		// deletes this object !
}

///////////////////////////////////////////////////////////////////////////////
// 
HRESULT CTRiASStatusBar::GetBarStyleEx (LPSTR pName, ULONG ulLen, ULONG *pulWritten, 
									  DWORD *pdwStyle, DWORD *pdwStyleEx)
{
	AFX_MANAGE_STATE(AfxGetModuleState());
    ASSERT_VALID(this);
    ASSERT(::IsWindow(m_hWnd));

bool fOK = false;

	if (NULL != pdwStyle) {
	// Style abfragen
		*pdwStyle = GetBarStyle();
		if (GetStyle() & WS_VISIBLE)
			*pdwStyle |= WS_VISIBLE;
		else
			*pdwStyle &= ~WS_VISIBLE;

		fOK = true;
	}

	if (NULL != pdwStyleEx)
		*pdwStyleEx = m_dwFlags;

	if (NULL != pName) {
	// Caption abfragen
	int iLen = GetWindowText (pName, ulLen);

		if (pulWritten) *pulWritten = iLen;
		fOK = true;
	}

return fOK ? NOERROR : ResultFromScode(S_FALSE);
}

HRESULT CTRiASStatusBar::SetBarStyleEx (LPCSTR pcName, DWORD dwStyle, DWORD dwStyleEx, bool fDelay)
{
	AFX_MANAGE_STATE(AfxGetModuleState());
    ASSERT_VALID(this);
    ASSERT(::IsWindow(m_hWnd));

// Style ändern
	SetBarStyle (dwStyle);

// Sichtbar/unsichtbar
	m_pMainFrm -> ShowControlBar (this, WS_VISIBLE & dwStyle ? true : false, fDelay);

// sonstige Flags
	m_dwFlags = dwStyleEx;

// Caption neu setzen
	if (NULL != pcName)		
		SetWindowText (pcName);

return NOERROR;
}

// barstat.cpp: AFX_STATUSPANE
typedef struct tagPANEINFO {
	UINT    uiID;		// IDC of indicator: 0 => normal text area
	int     uiWidth;	// width of string area in pixels
						//   on both sides there is a 3 pixel gap and
						//   a one pixel border, making a pane 6 pixels wider
	UINT    uiStyle;	// style flags (SBPS_*)
	UINT    nFlags;		// state flags (SBPF_*)
	CString strText;	// text in the pane
} PANEINFO;

HRESULT CTRiASStatusBar::DeleteItem (int iIndex)
{
	AFX_MANAGE_STATE(AfxGetModuleState());
    ASSERT_VALID(this);
    ASSERT(::IsWindow(m_hWnd));

// das erste Pane darf nicht entfernt werden
	if (0 == iIndex) return E_INVALIDARG;

PANEINFO *pPanes = NULL;

	try {
		if (iIndex >= m_nCount) return E_INVALIDARG;

		pPanes = new PANEINFO[m_nCount];

	// zusammenschieben der Panes
		for (int i = m_nCount-1; i >= 0; i--) {
			if (i > iIndex) {
				GetPaneInfo (i, pPanes[i-1].uiID, pPanes[i-1].uiStyle, pPanes[i-1].uiWidth);
				GetPaneText (i, pPanes[i-1].strText);
			}
			if (i < iIndex) {
				GetPaneInfo (i, pPanes[i].uiID, pPanes[i].uiStyle, pPanes[i].uiWidth);
				GetPaneText (i, pPanes[i].strText);
			}
		}

	// setzen der neuen PaneInfo
	// first allocate array for panes and copy initial data
		if (!AllocElements(m_nCount-1, sizeof(PANEINFO)))
			return FALSE;
	
	// m_nCount ist jetzt eins kleiner
		for (int j = 0; j < m_nCount; j++) {
			SetPaneInfo (j, pPanes[j].uiID, pPanes[j].uiStyle, pPanes[j].uiWidth);
			SetPaneText (j, pPanes[j].strText);
		}

	// neu zeichnen
		UpdateAllPanes(TRUE, FALSE);

		DELETE(pPanes);

	} catch(...) {
		DELETE(pPanes);
		return E_OUTOFMEMORY;
	}

return NOERROR;
}

HRESULT CTRiASStatusBar::CommandToIndex (UINT uiID, int *piIndex)
{
	AFX_MANAGE_STATE(AfxGetModuleState());
    ASSERT_VALID(this);
    ASSERT(::IsWindow(m_hWnd));
	ASSERT(NULL != piIndex);

	*piIndex = CStatusBar::CommandToIndex (uiID);
	return NOERROR;
}

HRESULT CTRiASStatusBar::GetItemRect (int iIndex, LPRECT pRc)
{
	AFX_MANAGE_STATE(AfxGetModuleState());
    ASSERT_VALID(this);
    ASSERT(::IsWindow(m_hWnd));
	ASSERT(NULL != pRc);

	if (NULL == pRc) return E_POINTER;

	CStatusBar::GetItemRect (iIndex, pRc);
	return NOERROR;
}

HRESULT CTRiASStatusBar::GetBarID (UINT *puiID)
{
	AFX_MANAGE_STATE(AfxGetModuleState());
    ASSERT_VALID(this);
    ASSERT(::IsWindow(m_hWnd));

	if (NULL == puiID) return E_POINTER;

	*puiID = AFX_IDW_STATUS_BAR;
	return NOERROR;
}

HRESULT CTRiASStatusBar::GetBarHandle (HWND *phWnd)
{
	AFX_MANAGE_STATE(AfxGetModuleState());
    ASSERT_VALID(this);
    ASSERT(::IsWindow(m_hWnd));

	if (NULL == phWnd) return E_POINTER;

	*phWnd = m_hWnd;
	return (NULL != m_hWnd) ? NOERROR : ResultFromScode(E_UNEXPECTED);
}

HRESULT CTRiASStatusBar::OnCmdMessage (UINT uiID, int nCode, void *pExtra, AFX_CMDHANDLERINFO *pHandlerInfo)
{
//	if (nCode != CN_COMMAND)
//		return S_FALSE;			// nur WM_COMMAND's bearbeiten

	AFX_MANAGE_STATE(AfxGetModuleState());
    ASSERT_VALID(this);
    ASSERT(::IsWindow(m_hWnd));

// nur bearbeiten, wenn dieses Fenster angezeigt ist
	if (!(GetStyle() & WS_VISIBLE))
		return S_FALSE;		// nicht bearbeitet

// Versuchen diesen Befehl an entsprechenden Handler zu schicken
UIOwners::iterator it = m_Owners.find (uiID);

	if (it != m_Owners.end()) {
		if (NULL != (IUnknown *)(*it).second) {
			if (NULL != pHandlerInfo)
				return S_OK;		// lediglich abfragen

			if (S_OK == (*it).second -> OnCommand (m_pIBar, uiID, nCode))
				return S_OK;		// bearbeitet
		}
	}

return S_FALSE;					// nicht bearbeitet
}

///////////////////////////////////////////////////////////////////////////////
// CTRiASStatusBar message handlers

// Nutzerinterface anpassen (gray/enable/disable ...) -------------------------
void CTRiASStatusBar::OnUpdateCmdUI(CFrameWnd* pTarget, bool bDisableIfNoHndler)
{
// nur bearbeiten, wenn dieses Fenster angezeigt ist
	if (!(GetStyle() & WS_VISIBLE))	return;		// nicht bearbeitet

// jetzt geht's richtig los
CComObject<CTRiASStatusCmdUI> *pCmdUI = NULL;	// _ATL_11

	TRY {
		if (FAILED(CComObject<CTRiASStatusCmdUI>::CreateInstance(&pCmdUI)))
			AfxThrowMemoryException();

		pCmdUI -> AddRef();			// RefCnt auf 1 setzen
	} CATCH (CMemoryException, e) {
		ASSERT(NULL != pCmdUI);
	
	// update the dialog controls added to the toolbar
		UpdateDialogControls (pTarget, bDisableIfNoHndler);
		return;
	} END_CATCH

CCmdUI &state = pCmdUI -> state;

	state.m_pOther = this;			// Owner setzen
	state.m_nIndexMax = (UINT)m_nCount;
	for (state.m_nIndex = 0; state.m_nIndex < state.m_nIndexMax; state.m_nIndex++)
	{
	// send to UIOwner
		state.m_nID = GetItemID (state.m_nIndex);

	UIOwners::iterator it = m_Owners.find (state.m_nID);

		if (it == m_Owners.end())
			continue;		// Fehler: erstmal weitermachen

		if (NULL != (IUnknown *)(*it).second && 
			S_OK == ((*it).second -> OnUpdateUI (m_pIBar, pCmdUI)))
		{
			continue;
		}

	// allow the owner to process the update
		state.DoUpdate(pTarget, false);
	}

// update the dialog controls added to the toolbar
	UpdateDialogControls (pTarget, bDisableIfNoHndler);

	pCmdUI -> Release();
}

// Das letzte vom Tage: alles was wir noch halten JETZT freigeben -------------
void CTRiASStatusBar::OnNcDestroy() 
{
	CStatusBar::OnNcDestroy();
	
// AddRefLoop auflösen: ~CTRiASStatusBar wird gerufen
	ExternalAddRef();
	m_Owners.erase();		// alle UIOwner freigeben

// jetzt kann alles freigegeben werden
//	m_bAutoDelete = true;
	ExternalRelease();
}

