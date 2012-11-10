// MainFrm.cpp : implementation of the CMainFrame class
//

#include "fakemfcp.hxx"
#define __AFXCONV_H__
#include <afxpriv.h>		// CDockState et.al.
#include <ScopeVar.h>

#include "fakemfc.h"		// ResourceKonstanten
#include "Strings.h"

#include <itoolbar.h>
#include <toolguid.h>
#include <dirisole.h>

#include "Wrapper.h"		// SmartInterfaces
#include "fakemfc.hxx"		// die Erweiterung selbst

#include "MainFrm.h"
#include "MainUIOwner.h"
#include "AuxUIOwner.h"

#include "ToolBarsDlg.h"

#if defined(_USE_SEC_CLASSES)
#include <sbardock.h>
#include "TRiASBarObj.h"
#include "TRiASToolBar.h"
#include "ToolBarManager.h"
#include "ViewComboBoxSec.h"
#include "ZoomComboBoxSec.h"
#include "CoordStaticsSec.h"
#else
#include "ZoomComboBox.h"
#include "ViewComboBox.h"
#include "CoordStatics.h"
#endif // _USE_SEC_CLASSES

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const int WM_SECTOOLBARWNDNOTIFY = RegisterWindowMessage(_T("WM_SECTOOLBARWNDNOTIFY"));

/////////////////////////////////////////////////////////////////////////////
// lokale Funktionen
TBBUTTON *CopyButtons (const TBBUTTON *pBttns, int iCnt);

/////////////////////////////////////////////////////////////////////////////
// zusätzlich benötigte Interfaces
DefineSmartInterface(PersistStreamInit);

///////////////////////////////////////////////////////////////////////////////
// DefineSmartInterface(TRiASToolBar) - (WTRiASToolBar)
// typedef __Interface<ITRiASToolBar, &IID_IEnumTRiASBar> WTRiASToolBar;

// Enumerator aller installierten ToolBars - (NEnumWTRiASToolBar)
DefineEnumerator2(WTRiASToolBar, IID_IEnumITRiASBar);
// typedef __Enumerator<WTRiASToolBar, &IID_IEnumITRiASBar, list<WTRiASToolBar> > NEnumWTRiASToolBar;

// SmartInterface für diesen Enumerator - (WEnumWTRiASToolBar)
DefineSmartEnumerator(WTRiASToolBar); //, IID_IEnumITRiASBar);
// typedef __Interface<IEnum<WTRiASToolBar>, &IID_IEnumITRiASBar> WEnumWTRiASToolBar;

///////////////////////////////////////////////////////////////////////////////
// OutputIterator, der den o.g. Enumerator füllt - (OutEnumWTRiASToolBar)
DefineEnumOutputIterator(WTRiASToolBar); //, IID_IEnumITRiASBar);
// typedef oenum_iterator<WTRiASToolBar, &IID_IEnumITRiASBar> OutEnumWTRiASToolBar;

/////////////////////////////////////////////////////////////////////////////
// Helperfunktion
HACCEL LoadCopyAndCorrectAccelerators (UINT uiID)
{
HACCEL hAccel = LoadAccelerators (g_hInstance, MAKEINTRESOURCE(uiID));

	ASSERT(NULL != hAccel);

int iCnt = CopyAcceleratorTable (hAccel, NULL, 0);

	ASSERT(0 < iCnt);

	TRY {
	ACCEL *pAccels = new ACCEL[iCnt];
	UINT uiOffset = g_pTE -> MenuOffset();

		iCnt = CopyAcceleratorTable (hAccel, pAccels, iCnt);
		for (int i = 0; i < iCnt; i++)
			pAccels[i].cmd += uiOffset;

	// mit LoadAccelerators geladene Accels müssen nicht freigegeben werden
		hAccel = CreateAcceleratorTable (pAccels, iCnt);
		delete pAccels;

	} CATCH(CMemoryException, e) {
		hAccel = NULL;
	} END_CATCH;

return hAccel;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, SECToplevelFrame)

BEGIN_MESSAGE_MAP(CMainFrame, SECToplevelFrame)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_INITMENUPOPUP()
	ON_WM_CLOSE()
	ON_WM_QUERYENDSESSION()
	ON_WM_ENDSESSION()
	ON_WM_KEYUP()
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_TOOLBARS, OnToolbars)
	ON_COMMAND(ID_TOOLBAR_CUSTOMIZE, OnToolbarCustomize)
	ON_UPDATE_COMMAND_UI(ID_TOOLBAR_CUSTOMIZE, OnUpdateToolbarCustomize)
	ON_UPDATE_COMMAND_UI(ID_TOOLBARS, OnUpdateToolbars)
	ON_WM_MENUSELECT()
	ON_WM_NCLBUTTONDOWN()
	ON_WM_GETMINMAXINFO()
	ON_MESSAGE_VOID(WM_IDLEUPDATECMDUI, OnIdleUpdateCmdUI)
	ON_WM_SIZE()
	ON_REGISTERED_MESSAGE(WM_SECTOOLBARWNDNOTIFY, OnToolBarWndNotify)
	ON_WM_NCDESTROY()
	ON_WM_ENABLE()
	//}}AFX_MSG_MAP
//	ON_COMMAND(ID_EDIT_SCALING, OnEditScaling)
//	ON_COMMAND(ID_SELECT_ACTVIEW, OnSelectActview)
	ON_COMMAND_RANGE(FIRST_TOOLBAR_ID, FIRST_TOOLBAR_ID+100, OnCommandToolBarPopup)
	ON_UPDATE_COMMAND_UI_RANGE(FIRST_TOOLBAR_ID, FIRST_TOOLBAR_ID+100, OnUpdateToolBarPopup)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
// die üblichen Initialisierungen
	m_bAutoMenuEnable = false;	
	m_uiBarID = AFX_IDW_TOOLBAR+5;

	m_pITRiASExt = NULL;
	m_dwCookie = 0L;
	m_fShowToolTips = false;
	m_bBlownUpMode = false;

// Accels aus Resource laden und MenuOffset addieren
	m_hAccelEsc = LoadCopyAndCorrectAccelerators (IDR_MAINFRAME_ESC);
	m_hAccelMisc = LoadCopyAndCorrectAccelerators (IDR_MAINFRAME_MISC);

#if defined(_USE_SEC_CLASSES)
// ToolBarManager generieren
	 ATLTRY(m_pControlBarManager = new CTRiASToolBarManager(this));
#endif // _USE_SEC_CLASSES
}

CMainFrame::~CMainFrame()
{
// OnDestroy wird nicht mehr gerufen, da an dieser Stelle, die Messages schon 
// nicht mehr hier ankommen. Daher müssen alle notwendigen aufräumaktionen direkt 
// ausgeführt werden.
	DestroyDockBars();

	if (m_pITRiASExt) { 
		m_pITRiASExt -> Release();	// hoffentlich letztes 'Release()'
		m_pITRiASExt = NULL;
	}

// die AccelTable ist nicht aus der Resource geladen, sondern selbst erzeugt,
// also müssen wird diese auch wieder selbst zerlegen
	if (m_hAccelEsc) DestroyAcceleratorTable (m_hAccelEsc);
	if (m_hAccelMisc) DestroyAcceleratorTable (m_hAccelMisc);

#if defined(_USE_SEC_CLASSES)
// ToolBarManager generieren
	DELETE(m_pControlBarManager);
#endif // _USE_SEC_CLASSES
}

void CMainFrame::SetDepUnk (IUnknown *pIUnk)
{
IUnknown *poldIUnk = m_pITRiASExt;

	m_pITRiASExt = pIUnk;
	if (m_pITRiASExt)	// die Erweiterung bis zum bitteren Ende festhalten
		m_pITRiASExt -> AddRef();
	if (poldIUnk) 
		poldIUnk -> Release();
}

// liefert einen Enumerator aller bisher intallierten TRiASBars -------------
HRESULT CMainFrame::GetEnumTRiASToolBars (IEnumITRiASBar **ppIEnum, LONG *plCount)
{
	TRY {
	// Enumerator anlegen
	WEnumWTRiASToolBar NewEnum (new NEnumWTRiASToolBar());

	// InterfacePointer umkopieren
		{
		OutEnumWTRiASToolBar out_iter (NewEnum);
		TRiASBars Bars (m_mapBars);

			copy (Bars.begin(), Bars.end(), out_iter);
		}

		if (NULL != plCount)		// evtl. Anzahl liefern
			*plCount = NewEnum -> Count();

		NewEnum -> Release();			// wird mit RefCnt 1 generiert
		*ppIEnum = (IEnumITRiASBar *)NewEnum.detach();

		return NOERROR;
	
	} CATCH(CMemoryException, e) {
		return E_OUTOFMEMORY;
	} END_CATCH
}

BEGIN_INTERFACE_MAP(CMainFrame, SECToplevelFrame)
	INTERFACE_PART(CMainFrame, IID_ITRiASBarNotifySink, TRiASBarNotifySink)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	SECToplevelFrame::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	SECToplevelFrame::Dump(dc);
}

#endif //_DEBUG

///////////////////////////////////////////////////////////////////////////////
// Liefert den nächsten verfügbaren ID für eine neu zu erzeugende ControlBar --
class CLockCS {
private:
	CCriticalSection &m_rCS;

public: 
		CLockCS (CCriticalSection &rCS) : m_rCS (rCS) { m_rCS.Lock(); }
		~CLockCS (void) { m_rCS.Unlock(); }
};

UINT CMainFrame::GetNextBarID (void)
{
CLockCS sync (m_Sync);

	return m_uiBarID++;
}

// Neue Toolbar erzeugt, diese jetzt im Enumerator speichern ------------------
HRESULT CMainFrame::AddNewBar (ITRiASBar *pIBar)
{
// zur Liste unserer Bars hinzufügen
CLockCS sync (m_Sync);
UINT uiID = 0;
HRESULT hr = pIBar -> GetBarID (&uiID);

	if (FAILED(hr)) return hr;

	TRY {
	pair<TRiASBarsMap::iterator, bool> p = m_mapBars.insert (uiID, WTRiASToolBar(pIBar));

		return p.second ? S_OK : E_FAIL;

	} CATCH(CMemoryException, e) {
		return E_OUTOFMEMORY;
	} END_CATCH
}

// existierende Toolbar aus der Liste unserer Bars entfernen ----------------
HRESULT CMainFrame::RemoveBar (ITRiASBar *pIBar)
{
CLockCS sync (m_Sync);
UINT uiID = 0;
HRESULT hr = pIBar -> GetBarID (&uiID);

	if (FAILED(hr)) return hr;
	
	if (m_mapBars.find (uiID) == m_mapBars.end()) 
		return S_FALSE;		// bereits entfernt

	pIBar -> AddRef();

	if (FIRST_TOOLBAR_ID == uiID)
		DisconnectMainToolBar (pIBar);			// evtl. MainToolbar abkoppeln

	m_mapBars.erase(uiID);		
	
// Bar sofort unsichtbar machen
DWORD dwStyle = 0L;
DWORD dwStyleEx = 0L;

	pIBar -> GetBarStyle (NULL, 0L, NULL, &dwStyle, &dwStyleEx);
	pIBar -> SetBarStyle (NULL, dwStyle & ~WS_VISIBLE, dwStyleEx, false);

	pIBar -> Release();		// letztes (hoffentlich) Release
	return S_OK;
}

HRESULT CMainFrame::RemapBarID (ITRiASBar *pIBar, UINT uiOldID, UINT uiNewID)
{
CLockCS sync (m_Sync);

	if (m_mapBars.find (uiOldID) == m_mapBars.end()) 
		return S_FALSE;		// nicht wiedergefunden

WTRiASBar Bar (pIBar);		// festhalten

	m_mapBars.erase(uiOldID);	// rausnehmen

// wieder reinbauen (mit neuem ID)
	TRY {
	pair<TRiASBarsMap::iterator, bool> p = m_mapBars.insert (uiNewID, WTRiASToolBar(pIBar));

		return p.second ? S_OK : E_FAIL;

	} CATCH(CMemoryException, e) {
		return E_OUTOFMEMORY;
	} END_CATCH
}

// neu erzeugen und initialisieren einer Toolbar ------------------------------
HRESULT CMainFrame::CreateToolBar (ITRiASToolBar **ppITools, UINT *puiID)
{
	*ppITools = NULL;

#if !defined(_USE_SEC_CLASSES)
	puiID;	/* unused */
	try {
	WTRiASToolBar Tools;
	HRESULT hr = CoCreateInstance (CLSID_TRiASToolBar, NULL, 
				CLSCTX_INPROC_SERVER, IID_ITRiASToolBar, Tools.ppv());

		if (FAILED(hr)) _com_issue_error(hr);

		{	// initialisieren
		WPersistStreamInit IInit = Tools;	// throws HRESULT

			hr = IInit -> InitNew();
			if (FAILED(hr)) _com_issue_error(hr);
		}

	// zur Liste unserer Bars hinzufügen
//		hr = AddNewBar (Tools);		// macht Toolbar jetzt selbst
//		if (FAILED(hr)) _com_issue_error(hr);

		*ppITools = Tools.detach();

	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}

	return NOERROR;
#else
	ASSERT(m_pControlBarManager != NULL);
	ASSERT_KINDOF(CTRiASToolBarManager, m_pControlBarManager);

CTRiASToolBarManager* pMgr = (CTRiASToolBarManager*)m_pControlBarManager;
UINT uiID = GetNextBarID();

	if (NULL != puiID)
		*puiID = uiID;

CString strDefCap;

	strDefCap.Format (IDS_DEFAULTTOOLBARCAPTION, uiID-(AFX_IDW_TOOLBAR+4));
	return pMgr -> CreateToolBar (uiID, strDefCap, ppITools);
#endif // _USE_SEC_CLASSES
}

#if defined(_USE_SEC_CLASSES)
void CMainFrame::DefineDefaultToolBar (
		UINT nID, LPCTSTR lpszTitle, const TBBUTTON *pBttns, UINT nBtnCount, 
		DWORD dwAlignment, UINT nDockBarID, UINT nDockNextToID,	BOOL bDocked, BOOL bVisible)
{
	ASSERT(m_pControlBarManager != NULL);
	ASSERT_KINDOF(CTRiASToolBarManager, m_pControlBarManager);

CTRiASToolBarManager* pMgr = (CTRiASToolBarManager*)m_pControlBarManager;

	pMgr -> DefineDefaultToolBar (
		nID, lpszTitle, pBttns, nBtnCount, dwAlignment, 
		nDockBarID, nDockNextToID, bDocked, bVisible);
}

HRESULT CMainFrame::CreateToolBar (LPCSTR pcCaption, ITRiASToolBar **ppITools)
{
	ASSERT(m_pControlBarManager != NULL);
	ASSERT_KINDOF(CTRiASToolBarManager, m_pControlBarManager);

CTRiASToolBarManager* pMgr = (CTRiASToolBarManager*)m_pControlBarManager;
UINT uiID = GetNextBarID();

	return pMgr -> CreateToolBar (uiID, pcCaption, ppITools);
}
#endif // _USE_SEC_CLASSES

HRESULT CMainFrame::InitToolBar (ITRiASToolBar *pITools, 
	LPCSTR pcCaption, DWORD dwStyle, HINSTANCE hInst, UINT uiID, int iCnt, 
	const TBBUTTON *pBttns, int iBttnCnt, ITRiASUIOwner *pIOwner)
{
	ASSERT(NULL != pITools);

HRESULT hr = S_OK;

#if defined(_USE_SEC_CLASSES)
	ASSERT(m_pControlBarManager != NULL);
	ASSERT_KINDOF(CTRiASToolBarManager, m_pControlBarManager);

CTRiASToolBarManager* pMgr = (CTRiASToolBarManager*)m_pControlBarManager;
DWORD dwStyleOld = 0L;
DWORD dwStyleExOld = 0L;
DWORD dwExStyle = TRIASTOOLBAR_PREDEFINED | pMgr -> GetDefaultBarStyleEx();

	pITools -> GetBarStyle (NULL, 0, NULL, &dwStyleOld, &dwStyleExOld);
	pITools -> SetBarStyle (pcCaption, dwStyle, dwStyleExOld | dwExStyle, true);
#else
	hr = pITools -> SetBarStyle (pcCaption, dwStyle, TRIASTOOLBAR_PREDEFINED, true);
	if (FAILED(hr)) return hr;
#endif // _USE_SEC_CLASSES

int iOffset = 0;

	hr = pITools -> AddBitmap (hInst, uiID, iCnt, &iOffset);
	if (FAILED(hr)) return hr;

	if (iBttnCnt > 0) {
		ASSERT(NULL != pBttns);

	TBBUTTON *pBtnCopy = CopyButtons (pBttns, iBttnCnt);

		if (NULL != pBtnCopy) {
		TBBUTTON *pCurr = pBtnCopy;

			for (int i = 0; i < iBttnCnt; i++, pCurr++)
				pCurr -> iBitmap += iOffset;

			hr = pITools -> AddButtons (pBtnCopy, iBttnCnt, pIOwner);
			DELETE (pBtnCopy);
		} else
			return E_OUTOFMEMORY;
	}

	return NOERROR;	
}

///////////////////////////////////////////////////////////////////////////////
// ToolBars erzeugen

TBBUTTON *CopyButtons (const TBBUTTON *pBttns, int iCnt)
{
	TRY {
	TBBUTTON *pBtnCopy = new TBBUTTON [iCnt];

		for (int i = 0; i < iCnt; i++) 
			pBtnCopy[i] = pBttns[i];

		return pBtnCopy;

	} CATCH (CMemoryException, e) {
		return NULL;
	} END_CATCH
}

///////////////////////////////////////////////////////////////////////////////
// Toolbar 'Werkzeuge' erzeugen -----------------------------------------------
const int NOSTRING = 0;
const TBBUTTON buttonsMain[] =
{	// same order as in the bitmap 'toolbar.bmp'
	{ 0, ID_TOOL_SELECT, 0, TBSTYLE_CHECKGROUP, 0L, NOSTRING, },
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, NOSTRING, },
	{ 1, ID_TOOL_ZOOM, 0, TBSTYLE_CHECKGROUP, 0L, NOSTRING, },
	{ 2, ID_TOOL_SEARCH, 0, TBSTYLE_CHECKGROUP, 0L, NOSTRING, },
	{ 3, ID_TOOL_DISTANCE, 0, TBSTYLE_CHECKGROUP, 0L, NOSTRING, },
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, NOSTRING, },
	{ 4, ID_TOOL_TEXT, 0, TBSTYLE_CHECKGROUP, 0L, NOSTRING, },
};
#define NUMBUTTONS_MAIN (sizeof(buttonsMain)/sizeof(buttonsMain[0]))

HRESULT CMainFrame::CreateMainToolBar (ITRiASToolBar **ppIToolBar)
{
	if (NULL != ppIToolBar)
		*ppIToolBar = NULL;

UINT uiID = 0L;
WTRiASToolBar Tools;
HRESULT hr = CreateToolBar (Tools.ppi(), &uiID);
WTRiASUIOwner UIOwner;

	if (SUCCEEDED(hr)) {
		TRY {
		CComObject<CMainUIOwner> *pOwner = NULL;		// _ATL_11
		
			hr = CComObject<CMainUIOwner>::CreateInstance(&pOwner);
			if (FAILED(hr)) AfxThrowMemoryException();

			UIOwner = (ITRiASUIOwner *)pOwner;					// RefCnt ist jetzt 1
			hr = pOwner -> SetXtsnSite (g_pTE -> m_pXtnSite);	// init Connection

		} CATCH (CMemoryException, e) {
			hr = E_OUTOFMEMORY;
		} END_CATCH
	}
	if (FAILED(hr)) return hr;

CString strCap;

	VERIFY(strCap.LoadString (IDS_MAINTOOLCAPTION));

DWORD dwFlags = CBRS_ALIGN_LEFT|CBRS_SIZE_DYNAMIC|CBRS_TOOLTIPS|
				CBRS_BORDER_ANY|CBRS_FLYBY|WS_VISIBLE;

	if (IsWin40()) dwFlags |= CBRS_BORDER_3D;
	hr = InitToolBar (Tools, strCap, dwFlags,
					  g_hInstance, IDR_MAINFRAME, 5, 
					  buttonsMain, NUMBUTTONS_MAIN, UIOwner);

	if (SUCCEEDED(hr)) {
		Tools -> DockBar (AFX_IDW_DOCKBAR_LEFT, NULL);	// Fehler nicht fatal
		hr = ConnectMainToolBar (Tools);	// Verbindung zu dieser Toolbar halten
	}
	if (FAILED(hr)) {
		RemoveBar (Tools);
		return hr;
	}

#if defined(_USE_SEC_CLASSES)
	DefineDefaultToolBar (uiID, strCap, buttonsMain, NUMBUTTONS_MAIN, 
						  CBRS_ALIGN_LEFT, AFX_IDW_DOCKBAR_LEFT, 0, TRUE, TRUE);
#endif // _USE_SEC_CLASSES

// fertige ToolBar liefern
	if (NULL != ppIToolBar)
		*ppIToolBar = Tools.detach();

	return hr;
}

///////////////////////////////////////////////////////////////////////////////
// Toolbar für Ansicht erzeugen -----------------------------------------------
#if !defined(_USE_SEC_CLASSES)
const TBBUTTON buttonsGeoView[] =
{
	{ 2, ID_GEOVIEW_NEW, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
	{ 3, ID_GEOVIEW_DELETE, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, NOSTRING, },
//	{ 7, ID_GEOVIEW_SELECTVIEW, TBSTATE_HIDDEN, TBSTYLE_BUTTON, 0L, NOSTRING, },
	{ 245, ID_GEOVIEW_SELECTVIEW_BOX, 0, TBSTYLE_SEP, 0L, NOSTRING, },
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, NOSTRING, },
	{ 6, ID_GEOVIEW_SELSCALE, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
	{ 0, ID_GEOVIEW_ZOOMIN, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
	{ 1, ID_GEOVIEW_ZOOMOUT, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
//	{ 9, ID_GEOVIEW_HOLDZOOM, 0, TBSTYLE_CHECK, 0L, NOSTRING, },
	{ 21, ID_GEOVIEW_SELECTZOOM_TEXT, 0, TBSTYLE_SEP, 0L, NOSTRING, },
	{ 90, ID_GEOVIEW_SELECTZOOM_BOX, 0, TBSTYLE_SEP, 0L, NOSTRING, },
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, NOSTRING, },
	{ 4, ID_GEOVIEW_NEWCONT, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
	{ 5, ID_GEOVIEW_DELCONT, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, NOSTRING, },
	{ 8, ID_GEOVIEW_REPAINT, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
};
#define NUMBUTTONS_GEOVIEW (sizeof(buttonsGeoView)/sizeof(buttonsGeoView[0]))
#define CBOXPOSITION_GEOVIEW	3
#define CBOXPOSITION_ZOOMTEXT	8
#define CBOXPOSITION_ZOOM		9

#else

const SECBtnMapEntry cbViewSpecials[] = 
{ 
	WND_BUTTON(BUTTON_CLASS(CViewComboBoxSec), ID_GEOVIEW_SELECTVIEW, ID_GEOVIEW_SELECTVIEW, 
			   0, CBS_DROPDOWNLIST|WS_VSCROLL|WS_TABSTOP, /*259*/257, 150, 250) 
	WND_BUTTON(BUTTON_CLASS(CZoomComboBoxSec), ID_GEOVIEW_SELSCALE, ID_GEOVIEW_SELSCALE, 
			   0, CBS_DROPDOWN|WS_VSCROLL|WS_TABSTOP, 111, 80, 150) 
};

const TBBUTTON buttonsGeoView[] =
{
	{ 2, ID_GEOVIEW_NEW, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
	{ 3, ID_GEOVIEW_DELETE, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, NOSTRING, },
	{ 7, ID_GEOVIEW_SELECTVIEW, 0 /*&cbViewSpecials[0]*/, TBSTYLE_BUTTON, 0L, NOSTRING, },
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, NOSTRING, },
	{ 0, ID_GEOVIEW_ZOOMIN, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
	{ 1, ID_GEOVIEW_ZOOMOUT, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, NOSTRING, },
	{ 9, ID_GEOVIEW_HOLDZOOM, 0, TBSTYLE_CHECK, 0L, NOSTRING, },
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, NOSTRING, },
	{ 6, ID_GEOVIEW_SELSCALE, 0 /*&cbViewSpecials[1]*/, TBSTYLE_BUTTON, 0L, NOSTRING, },
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, NOSTRING, },
	{ 4, ID_GEOVIEW_NEWCONT, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
	{ 5, ID_GEOVIEW_DELCONT, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, NOSTRING, },
	{ 8, ID_GEOVIEW_REPAINT, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
//	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, NOSTRING, },
	{ 10, ID_GEOVIEW_PREVENT_REPAINT, 0, TBSTYLE_CHECK, 0L, NOSTRING, },
};
#define NUMBUTTONS_GEOVIEW (sizeof(buttonsGeoView)/sizeof(buttonsGeoView[0]))
#define CBOXPOSITION_GEOVIEW	3
#define CBOXPOSITION_ZOOM		10

#endif // !_USE_SEC_CLASSES

HRESULT CMainFrame::CreateGeoViewToolBar (ITRiASUIOwner *pIUIOwner, ITRiASToolBar **ppIToolBar)
{
	if (NULL != ppIToolBar) 
		*ppIToolBar = NULL;

UINT uiID = 0L;
WTRiASToolBar Tools;
HRESULT hr = CreateToolBar (Tools.ppi(), &uiID);

	if (FAILED(hr)) return hr;

TBBUTTON *pBtnCopy = CopyButtons (buttonsGeoView, NUMBUTTONS_GEOVIEW);
CString strCap;

	if (NULL == pBtnCopy) return E_OUTOFMEMORY;

// spezielle Vorbereitung für ComboBox
	TRY {
#if !defined(_USE_SEC_CLASSES)
	CComObject<CInstViewComboBox> *pInstCB = NULL;
	
		hr = CComObject<CInstViewComboBox>::CreateInstance(&pInstCB);	// _ATL_11
		if (FAILED(hr)) AfxThrowMemoryException();

	ITRiASBarInstallControl *pICtrl = (ITRiASBarInstallControl *)pInstCB;

		pICtrl -> AddRef();		// RefCnt auf 1 setzen, wird von TBBUTTON übernommen
		pInstCB -> SetXtsnSite (g_pTE -> m_pXtnSite);
		pBtnCopy[CBOXPOSITION_GEOVIEW].dwData = reinterpret_cast<DWORD>(pICtrl);

//		pICtrl -> AddRef();
//		pBtnCopy[CBOXPOSITION_GEOVIEW+1].dwData = reinterpret_cast<DWORD>(pICtrl);
	CComObject<CInstZoomStatic> *pZoomTxt = NULL;
	
		hr = CComObject<CInstZoomStatic>::CreateInstance(&pZoomTxt);	// _ATL_11
		if (FAILED(hr)) AfxThrowMemoryException();
	
		pICtrl = (ITRiASBarInstallControl *)pZoomTxt;
		pICtrl -> AddRef();		// RefCnt auf 1 setzen, wird von TBBUTTON übernommen
		pBtnCopy[CBOXPOSITION_ZOOMTEXT].dwData = reinterpret_cast<DWORD>(pZoomTxt);

	CComObject<CInstZoomComboBox> *pZoomCB = NULL;
	
		hr = CComObject<CInstZoomComboBox>::CreateInstance(&pZoomCB);	// _ATL_11
		if (FAILED(hr)) AfxThrowMemoryException();
	
		pICtrl = (ITRiASBarInstallControl *)pZoomCB;
		pICtrl -> AddRef();		// RefCnt auf 1 setzen, wird von TBBUTTON übernommen
		pZoomCB -> SetXtsnSite (g_pTE -> m_pXtnSite);
		pBtnCopy[CBOXPOSITION_ZOOM].dwData = reinterpret_cast<DWORD>(pZoomCB);
#else
		pBtnCopy[CBOXPOSITION_GEOVIEW].dwData = reinterpret_cast<DWORD>(&cbViewSpecials[0]);
		pBtnCopy[CBOXPOSITION_ZOOM].dwData = reinterpret_cast<DWORD>(&cbViewSpecials[1]);
#endif // !_USE_SEC_CLASSES

	// jetzt wirklich erzeugen
		VERIFY(strCap.LoadString (IDS_GEOVIEWTOOLCAPTION));

	DWORD dwFlags = CBRS_ALIGN_TOP|CBRS_SIZE_DYNAMIC|CBRS_TOOLTIPS|
					CBRS_BORDER_ANY|CBRS_FLYBY|WS_VISIBLE;

		if (IsWin40()) dwFlags |= CBRS_BORDER_3D;
		hr = InitToolBar (Tools, strCap, dwFlags,
						  g_hInstance, IDR_GEOVIEW, 11, 
						  pBtnCopy, NUMBUTTONS_GEOVIEW, pIUIOwner);
		if (FAILED(hr)) {
			RemoveBar (Tools);
			_com_issue_error(hr);
		}

#if defined(_USE_SEC_CLASSES)
		DefineDefaultToolBar (uiID, strCap, buttonsGeoView, NUMBUTTONS_GEOVIEW, 
							  CBRS_ALIGN_TOP, AFX_IDW_DOCKBAR_TOP, 0, TRUE, TRUE);
#endif // _USE_SEC_CLASSES

	// fertige ToolBar liefern
		delete [] pBtnCopy;
		if (NULL != ppIToolBar) 
			*ppIToolBar = Tools.detach();

	} CATCH (CMemoryException, e) {
		delete [] pBtnCopy;
		return E_OUTOFMEMORY;
	} END_CATCH

return hr;
}

///////////////////////////////////////////////////////////////////////////////
// ToolBar für Objektklassen erzeugen -----------------------------------------
const TBBUTTON buttonsClass[] =
{
	{ 0, ID_GEOCLASS_SELECT, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
	{ 1, ID_GEOCLASS_DELETE, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
	{ 2, ID_GEOCLASS_MODIFY, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, NOSTRING, },
	{ 3, ID_GEOCLASS_VISPARAMS, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
	{ 4, ID_GEOCLASS_PRIORITY, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, NOSTRING, },
	{ 5, ID_GEOCLASS_OBJPROP, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
};
#define NUMBUTTONS_CLASS (sizeof(buttonsClass)/sizeof(buttonsClass[0]))

HRESULT CMainFrame::CreateGeoClassToolBar (ITRiASUIOwner *pIUIOwner, ITRiASToolBar **ppIToolBar)
{
	if (NULL != ppIToolBar) 
		*ppIToolBar = NULL;

UINT uiID = 0L;
WTRiASToolBar Tools;
HRESULT hr = CreateToolBar (Tools.ppi(), &uiID);

	if (FAILED(hr)) return hr;

CString strCap;

	VERIFY(strCap.LoadString (IDS_GEOCLASSTOOLCAPTION));

DWORD dwFlags = CBRS_ALIGN_TOP|CBRS_SIZE_DYNAMIC|CBRS_TOOLTIPS|
				CBRS_BORDER_ANY|CBRS_FLYBY|WS_VISIBLE;

	if (IsWin40()) dwFlags |= CBRS_BORDER_3D;
	hr = InitToolBar (Tools, strCap, dwFlags,
					  g_hInstance, IDR_GEOCLASS, 6, 
					  buttonsClass, NUMBUTTONS_CLASS, pIUIOwner);
	if (SUCCEEDED(hr)) 
		hr = Tools -> DockBar (AFX_IDW_DOCKBAR_TOP, NULL);	// Fehler nicht fatal

	if (FAILED(hr)) {
		RemoveBar (Tools);
		return hr;
	}

#if defined(_USE_SEC_CLASSES)
	DefineDefaultToolBar (uiID, strCap, buttonsClass, NUMBUTTONS_CLASS, 
						  CBRS_ALIGN_TOP, AFX_IDW_DOCKBAR_TOP, 0, TRUE, TRUE);
#endif // _USE_SEC_CLASSES

// fertige ToolBar liefern
	if (NULL != ppIToolBar) 
		*ppIToolBar = Tools.detach();

return hr;
}

///////////////////////////////////////////////////////////////////////////////
// Toolbar für Standardbefehle erzeugen ---------------------------------------
const TBBUTTON buttonsStandard[] =
{
	{ 0, ID_STANDARD_NEWPRJ, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, NOSTRING, },
	{ 2, ID_STANDARD_OPEN, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, NOSTRING, },
	{ 3, ID_STANDARD_SAVEDB, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
	{ 4, ID_STANDARD_CLOSE, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, NOSTRING, },
	{ 5, ID_STANDARD_PRINT, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, NOSTRING, },
	{ 6, ID_STANDARD_UNDO, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
	{ 7, ID_STANDARD_REDO, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, NOSTRING, },
	{ 8, ID_STANDARD_CUSTOMIZE, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, NOSTRING, },
	{ 9, ID_STANDARD_LEGENDE, 0, TBSTYLE_CHECK, 0L, NOSTRING, },
	{ 10, ID_STANDARD_OVERVIEW, 0, TBSTYLE_CHECK, 0L, NOSTRING, },
};
#define NUMBUTTONS_STANDARD (sizeof(buttonsStandard)/sizeof(buttonsStandard[0]))

HRESULT CMainFrame::CreateStandardToolBar (ITRiASUIOwner *pIUIOwner, ITRiASToolBar **ppIToolBar)
{
	if (NULL != ppIToolBar) 
		*ppIToolBar = NULL;

UINT uiID = 0L;
WTRiASToolBar Tools;
HRESULT hr = CreateToolBar (Tools.ppi(), &uiID);

	if (FAILED(hr)) return hr;

CString strCap;

	VERIFY(strCap.LoadString (IDS_STANDARDTOOLCAPTION));

DWORD dwFlags = CBRS_ALIGN_TOP|CBRS_SIZE_DYNAMIC|CBRS_TOOLTIPS|
				CBRS_BORDER_ANY|CBRS_FLYBY|WS_VISIBLE;

	if (IsWin40()) dwFlags |= CBRS_BORDER_3D;
	hr = InitToolBar (Tools, strCap, dwFlags,
					  g_hInstance, IDR_STANDARD, 11, 
					  buttonsStandard, NUMBUTTONS_STANDARD, pIUIOwner);
	if (FAILED(hr)) {
		RemoveBar (Tools);
		return hr;
	}

#if defined(_USE_SEC_CLASSES)
	DefineDefaultToolBar (uiID, strCap, buttonsStandard, NUMBUTTONS_STANDARD, 
						  CBRS_ALIGN_TOP, AFX_IDW_DOCKBAR_TOP, 0, TRUE, TRUE);
#endif // _USE_SEC_CLASSES

// fertige ToolBar liefern
	if (NULL != ppIToolBar) 
		*ppIToolBar = Tools.detach();

return hr;
}

///////////////////////////////////////////////////////////////////////////////
// ToolBar für Koordinaten erzeugen 
#if !defined(_USE_SEC_CLASSES)

const TBBUTTON buttonsCoords[] =
{
	{ 0, ID_COORDS_SELECTFORMAT, 0, TBSTYLE_BUTTON, 0L, NOSTRING },
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, NOSTRING },
	{ 148, ID_COORDS_SHOWCOORDS_STATIC, 0, TBSTYLE_SEP, 0L, NOSTRING, },
	{ 3, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, NOSTRING },
};
#else

const SECBtnMapEntry cbCoordSpecials[] = 
{ 
	WND_BUTTON(BUTTON_CLASS(CCompoundStaticSec), ID_COORDS_SHOWCOORDS_STATIC, 
			   ID_COORDS_SHOWCOORDS_STATIC, 
			   0, WS_VISIBLE|WS_DISABLED, 148, 100, 20) 
};

const TBBUTTON buttonsCoords[] =
{
	{ 0, ID_COORDS_SELECTFORMAT, 0, TBSTYLE_BUTTON, 0L, NOSTRING },
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, NOSTRING },
	{ 1, ID_COORDS_SHOWCOORDS_STATIC, 0 /*&cbCoordSpecials[0]*/, TBSTYLE_BUTTON, 0L, NOSTRING, },
};

#endif // _USE_SEC_CLASSES

#define NUMBUTTONS_COORDS (sizeof(buttonsCoords)/sizeof(buttonsCoords[0]))
#define TEXTPOSITION_COORDS		2

HRESULT CMainFrame::CreateCoordsToolBar (ITRiASUIOwner *pIUIOwner, ITRiASToolBar **ppIToolBar)
{
	if (NULL != ppIToolBar) 
		*ppIToolBar = NULL;

UINT uiID = 0;
WTRiASToolBar Tools;
HRESULT hr = CreateToolBar (Tools.ppi(), &uiID);

	if (FAILED(hr)) return hr;

TBBUTTON *pBtnCopy = CopyButtons (buttonsCoords, NUMBUTTONS_COORDS);
CString strCap;

	if (NULL == pBtnCopy) return E_OUTOFMEMORY;

	TRY {
#if !defined(_USE_SEC_CLASSES)
	CComObject<CInstCoordStatics> *pCoords = NULL; 
	
		hr = CComObject<CInstCoordStatics>::CreateInstance (&pCoords);		// _ATL_11
		if (FAILED(hr)) AfxThrowMemoryException();

	ITRiASBarInstallControl *pICtrl = (ITRiASBarInstallControl *)pCoords;

		pICtrl -> AddRef();		// RefCnt auf 1 setzen, wird von TBBUTTON übernommen
		pCoords -> SetXtsnSite (g_pTE -> m_pXtnSite);
		pBtnCopy[TEXTPOSITION_COORDS].dwData = reinterpret_cast<DWORD>(pCoords);
#else
		pBtnCopy[TEXTPOSITION_COORDS].dwData = reinterpret_cast<DWORD>(&cbCoordSpecials[0]);
#endif // _USE_SEC_CLASSES

		VERIFY(strCap.LoadString (IDS_COORDSTOOLCAPTION));

	DWORD dwFlags = CBRS_ALIGN_TOP|CBRS_SIZE_DYNAMIC|CBRS_TOOLTIPS|
					CBRS_BORDER_ANY|CBRS_FLYBY|WS_VISIBLE;

		if (IsWin40()) dwFlags |= CBRS_BORDER_3D;
		hr = InitToolBar (Tools, strCap, dwFlags,
						  g_hInstance, IDR_COORDS, 2, 
						  pBtnCopy, NUMBUTTONS_COORDS, pIUIOwner);
		if (FAILED(hr)) {
			RemoveBar (Tools);
			return hr;
		}

#if defined(_USE_SEC_CLASSES)
		DefineDefaultToolBar (uiID, strCap, pBtnCopy, NUMBUTTONS_COORDS, 
							  CBRS_ALIGN_TOP, AFX_IDW_DOCKBAR_TOP, 0, TRUE, TRUE);
#endif // _USE_SEC_CLASSES

	// fertige ToolBar liefern
		if (NULL != ppIToolBar) 
			*ppIToolBar = Tools.detach();

		delete [] pBtnCopy;

	} CATCH (CMemoryException, e) {
		delete [] pBtnCopy;
		return E_OUTOFMEMORY;
	} END_CATCH

return hr;
}

///////////////////////////////////////////////////////////////////////////////
// ToolBar für FullScreen erzeugen --------------------------------------------
const TBBUTTON buttonsFullScreen[] =
{
	{ 0, ID_FULLSCREEN_TOGGLE, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
};
#define NUMBUTTONS_FULLSCREEN (sizeof(buttonsFullScreen)/sizeof(buttonsFullScreen[0]))

void CMainFrame::GetFullScreenTBCaption (CString &rStr)
{
	VERIFY(rStr.LoadString (IDS_SWITCHFULLSCREENMODE));

// alle '&' entfernen
int iIndex = rStr.Find (_T("&"));

	while (iIndex > -1) {
		rStr = rStr.Left(iIndex) + rStr.Right(rStr.GetLength()-iIndex-1);
		iIndex = rStr.Find (_T("&"));
	}
}

HRESULT CMainFrame::CreateFullScreenToolBar (ITRiASUIOwner *pIUIOwner, ITRiASToolBar **ppIToolBar)
{
	if (NULL != ppIToolBar) 
		*ppIToolBar = NULL;

UINT uiID = 0L;
WTRiASToolBar Tools;
HRESULT hr = CreateToolBar (Tools.ppi(), &uiID);

	if (FAILED(hr)) return hr;

CString strCap;

	GetFullScreenTBCaption (strCap);

DWORD dwFlags = CBRS_ALIGN_TOP|CBRS_SIZE_DYNAMIC|CBRS_TOOLTIPS|
				CBRS_BORDER_ANY|CBRS_FLYBY|CBRS_FLOATING;

	if (IsWin40()) dwFlags |= CBRS_BORDER_3D;
	hr = InitToolBar (Tools, strCap, dwFlags,
					  g_hInstance, IDR_FULLSCREEN, 1, 
					  buttonsFullScreen, NUMBUTTONS_FULLSCREEN, pIUIOwner);
	if (FAILED(hr)) {
		RemoveBar (Tools);
		return hr;
	}

#if defined(_USE_SEC_CLASSES)
	DefineDefaultToolBar (uiID, strCap, buttonsFullScreen, NUMBUTTONS_FULLSCREEN, 
						  CBRS_ALIGN_TOP, AFX_IDW_DOCKBAR_TOP, 0, TRUE, TRUE);
#endif // _USE_SEC_CLASSES

// fertige ToolBar liefern
	if (NULL != ppIToolBar) 
		*ppIToolBar = Tools.detach();

return hr;
}

///////////////////////////////////////////////////////////////////////////////
// Installieren aller Toolbars ------------------------------------------------
HRESULT CMainFrame::InstallToolBars (void)
{
HRESULT hr = CreateMainToolBar();

	if(FAILED(hr)) return hr;

WTRiASUIOwner UIOwner;

	TRY {
	CComObject<CAuxUIOwner> *pOwner = NULL;		// _ATL_11
	
		hr = CComObject<CAuxUIOwner>::CreateInstance (&pOwner);
		if (FAILED(hr)) AfxThrowMemoryException();

		UIOwner = (ITRiASUIOwner *)pOwner;		// RefCnt ist jetzt 1
		hr = pOwner -> SetXtsnSite (g_pTE -> m_pXtnSite);	// init Connection

	} CATCH (CMemoryException, e) {
		hr = E_OUTOFMEMORY;
	} END_CATCH
	if (FAILED(hr)) return hr;

	try {
	WTRiASToolBar currTool;
	WTRiASToolBar nextTool;

		THROW_FAILED_HRESULT(CreateStandardToolBar (UIOwner, currTool.ppi()));

		THROW_FAILED_HRESULT(CreateCoordsToolBar (UIOwner, nextTool.ppi()));
		DockControlBarLeftOf (nextTool, currTool);

		currTool = nextTool;
		THROW_FAILED_HRESULT(CreateGeoClassToolBar (UIOwner, nextTool.ppi()));
		DockControlBarLeftOf (nextTool, currTool);

		THROW_FAILED_HRESULT(CreateGeoViewToolBar (UIOwner, currTool.ppi()));
		THROW_FAILED_HRESULT(CreateFullScreenToolBar (UIOwner, nextTool.ppi()));
		DockControlBarLeftOf (nextTool, currTool);
	
	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}

	return NOERROR;
}

HRESULT CMainFrame::DockControlBarLeftOf (ITRiASToolBar *pIBar, ITRiASToolBar *pILeftOf)
{
	TEST_E_POINTER("CMainFrame::DockControlBarLeftOf", pILeftOf);

// get MFC to adjust the dimensions of all docked ToolBars
// so that GetWindowRect will be accurate
CRect rect;

	RecalcLayout();

HWND hTB = NULL;
HRESULT hr = pILeftOf -> GetBarHandle (&hTB);

	ASSERT(NULL != hTB && IsWindow(hTB));

	CWnd::FromHandle(hTB) -> GetWindowRect (&rect);
	rect.OffsetRect (rect.Width()/2 +1, 0);

DWORD dwStyle = 0L;
UINT uiWhere = 0;

	hr = pILeftOf -> GetBarStyle (NULL, 0L, NULL, &dwStyle, NULL);
	if (FAILED(hr)) return hr;

	uiWhere = (dwStyle & CBRS_ALIGN_TOP) ? AFX_IDW_DOCKBAR_TOP : uiWhere;
	uiWhere = (dwStyle & CBRS_ALIGN_BOTTOM && 0 == uiWhere) ? AFX_IDW_DOCKBAR_BOTTOM : uiWhere;
	uiWhere = (dwStyle & CBRS_ALIGN_LEFT && 0 == uiWhere) ? AFX_IDW_DOCKBAR_LEFT : uiWhere;
	uiWhere = (dwStyle & CBRS_ALIGN_RIGHT && 0 == uiWhere) ? AFX_IDW_DOCKBAR_RIGHT : uiWhere;

// When we take the default parameters on rect, DockControlBar will dock
// each Toolbar on a seperate line.  By calculating a rectangle, we in effect
// are simulating a Toolbar being dragged to that location and docked.
	return pIBar -> DockBar (uiWhere, &rect);
}

// Freigeben aller installierten Toolbars -------------------------------------
HRESULT CMainFrame::FreeToolBars (void)
{
// diverses anderes wegschreiben
	AfxGetApp()->WriteProfileInt (g_cbConfig, g_cbShowToolTips, m_fShowToolTips);

#if defined(_USE_SEC_CLASSES)
	ASSERT(m_pControlBarManager != NULL);
	ASSERT_KINDOF(CTRiASToolBarManager, m_pControlBarManager);

CTRiASToolBarManager* pMgr = (CTRiASToolBarManager*)m_pControlBarManager;

	AfxGetApp()->WriteProfileInt (g_cbConfig, g_cbCoolLook, pMgr -> CoolLookEnabled());
#endif // _USE_SEC_CLASSES

// MainToolbar wiederfinden
TRiASBarsMap::iterator it = m_mapBars.find (FIRST_TOOLBAR_ID); 

	if (it != m_mapBars.end())
		DisconnectMainToolBar ((*it).second);	// Verbindung zu MainToolBar wieder lösen

// alle ToolBars freigeben
	if (0 != m_mapBars.size())
		m_mapBars.erase();		// alles löschen

return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// Zustand der Bars einlesen
HRESULT CMainFrame::LoadToolbarState (LPCSTR pcKeyName, LPCSTR pcFileName)
{
	try {
		if (NULL == pcFileName) {
			if (NULL == pcKeyName)
				FixedupLoadBarState (IsFullScreen() ? g_cbLayoutFS : g_cbLayout);
			else {
			// immer aus "NormalLayout\\pcKeyName" bzw. "FullScreenLayout\\pcKeyName" laden
//			CString strKey (IsFullScreen() ? g_cbLayoutRootFS : g_cbLayoutRoot);
//
//				strKey += g_cbDel;
//				strKey += pcKeyName;
//				FixedupLoadBarState (strKey);
				FixedupLoadBarState (pcKeyName);
			}
		} else {
		// aus .INI mit gegebenem Namen lesen
			ASSERT(NULL != pcKeyName);

		// ugly hack: globale Variablen verdrehen
		CWinApp *pApp = AfxGetApp();
		CScopeVar<LPCTSTR> RegKey (pApp -> m_pszRegistryKey, NULL);
		CScopeVar<LPCTSTR> Profile (pApp -> m_pszProfileName, pcFileName);

			FixedupLoadBarState (pcKeyName);
		}
		RecalcLayout ();

	} catch (...) {
		ASSERT(false);		// BUG in MFC
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Zustand der Bars wegschreiben 
HRESULT CMainFrame::SaveToolbarState (LPCSTR pcKeyName, LPCSTR pcFileName)
{
	if (NULL == pcFileName) {
		if (!IsWin32s()) {
			if (NULL == pcKeyName) {
			// sämtliche alten Einträge herauslöschen
			CRegKey regLayout;

				regLayout.Attach (AfxGetApp()->GetAppRegistryKey());
				regLayout.RecurseDeleteKey (IsFullScreen() ? g_cbLayoutRootFS : g_cbLayoutRoot);

			// derzeitiges Layout speichern
				FixedupSaveBarState (IsFullScreen() ? g_cbLayoutFS : g_cbLayout);
			} else {
			// immer unter "NormalLayout\\pcKeyName" bzw. "FullScreenLayout\\pcKeyName" speichern
			CString strKey (IsFullScreen() ? g_cbLayoutRootFS : g_cbLayoutRoot);

				strKey += g_cbDel;
				strKey += pcKeyName;
				FixedupSaveBarState (strKey);
			}
		} else {
			if (NULL == pcKeyName)
				FixedupSaveBarState (IsFullScreen() ? g_cbLayoutRootFS : g_cbLayoutRoot);
			else 
				FixedupSaveBarState (pcKeyName);
		}
	} else {
	// in .INI mit gegebenem Namen Speichern
		ASSERT(NULL != pcKeyName);

	// ugly hack: globale Variablen verdrehen
	CWinApp *pApp = AfxGetApp();
	CScopeVar<LPCTSTR> RegKey (pApp -> m_pszRegistryKey, NULL);
	CScopeVar<LPCTSTR> Profile (pApp -> m_pszProfileName, pcFileName);

		FixedupSaveBarState (pcKeyName);
	}

	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Statusbar verwalten

HRESULT CMainFrame::InstallStatusBar (void)
{
	return NOERROR;
}

HRESULT CMainFrame::FreeStatusBar (void)
{
	return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// Mimik für ConnectionPoint

HRESULT CMainFrame::ConnectMainToolBar (ITRiASBar *pIToolBar)
{
	ASSERT(0L == m_dwCookie);

	try {
	WConnectionPointContainer Cont (pIToolBar);		// throws HRESULT
	WConnectionPoint ConnPnt;
	HRESULT hr = Cont -> FindConnectionPoint (IID_ITRiASBarNotifySink, ConnPnt.ppi());

		if (FAILED(hr)) _com_issue_error(hr);

	WTRiASBarNotifySink Sink;
	
		hr = ExternalQueryInterface (&IID_ITRiASBarNotifySink, Sink.ppv());
		if (FAILED(hr)) _com_issue_error(hr);

		hr = ConnPnt -> Advise (Sink, &m_dwCookie);		// Verbindung herstellen
		if (FAILED(hr)) _com_issue_error(hr);

	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}

return NOERROR;
}

HRESULT CMainFrame::DisconnectMainToolBar (ITRiASBar *pIToolBar)
{
	ASSERT(0L != m_dwCookie);
	if (0L == m_dwCookie)
		return E_UNEXPECTED;

	try {
	WConnectionPointContainer Cont = pIToolBar;		// throws HRESULT
	WConnectionPoint ConnPnt;
	HRESULT hr = Cont -> FindConnectionPoint (IID_ITRiASBarNotifySink, ConnPnt.ppi());

		if (FAILED(hr)) _com_issue_error(hr);
		
		hr = ConnPnt -> Unadvise (m_dwCookie);			// Verbindung lösen
		if (FAILED(hr)) _com_issue_error(hr);

		m_dwCookie = 0L;

	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}

return NOERROR;
}

/////////////////////////////////////////////////////////////////////////////
// ITRiASBarNotifySink implementation
STDMETHODIMP_(ULONG) CMainFrame::
XTRiASBarNotifySink::AddRef (void)
{
    METHOD_PROLOGUE(CMainFrame, TRiASBarNotifySink)
    return pThis->ExternalAddRef();
}

STDMETHODIMP_(ULONG) CMainFrame::
XTRiASBarNotifySink::Release (void)
{
    METHOD_PROLOGUE(CMainFrame, TRiASBarNotifySink)
    return pThis->ExternalRelease();
}

STDMETHODIMP CMainFrame::
XTRiASBarNotifySink::QueryInterface (REFIID iid, LPVOID *ppvObj)
{
    METHOD_PROLOGUE(CMainFrame, TRiASBarNotifySink)
    return (HRESULT)pThis->ExternalQueryInterface(&iid, ppvObj);
}

STDMETHODIMP CMainFrame::
XTRiASBarNotifySink::OnRequestAddButtons (ITRiASBar *pIBar, int iIndex, const TBBUTTON *pBttn, int iCnt)
{
    METHOD_PROLOGUE(CMainFrame, TRiASBarNotifySink)
	return S_OK;		// immer zulassen
}

STDMETHODIMP CMainFrame::
XTRiASBarNotifySink::OnAddedButtons (ITRiASBar *pIBar, int iIndex, const TBBUTTON *pBttn, int iCnt)
{
    METHOD_PROLOGUE(CMainFrame, TRiASBarNotifySink)
	return E_NOTIMPL;
}

///////////////////////////////////////////////////////////////////////////////
// Feststellen, ob zu entfernender Button der aktive ist 

STDMETHODIMP CMainFrame::
XTRiASBarNotifySink::OnRequestDeleteItem (ITRiASBar *pIBar, UINT uiCtrlID, DWORD dwStyle)
{
    METHOD_PROLOGUE(CMainFrame, TRiASBarNotifySink)

UINT uiID = 0;
HRESULT hr = pIBar -> GetBarID (&uiID);

	if (FIRST_TOOLBAR_ID != uiID || dwStyle & TBSTYLE_SEP)
		return NOERROR;			// nur MainToolbar/keine Separatoren behandeln

// wenn der zu entfernende Knopf der aktive ist, dann aktives Tool rücksetzen
	if (TBSTATE_CHECKED & HIWORD(dwStyle))
		DEX_ChangeActiveTool (NUMARROW);	// 'Pfeil' einstellen

	return NOERROR;			// immer zulassen, daß Button entfernt wird
}

STDMETHODIMP CMainFrame::
XTRiASBarNotifySink::OnDeletedItem (ITRiASBar *pIBar, UINT uiCtrlID)
{
    METHOD_PROLOGUE(CMainFrame, TRiASBarNotifySink)
	return E_NOTIMPL;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::PreSubclassWindow() 
{
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return;      // fail to create
	}

// ToolbarStyles aus Registry lesen
	m_fShowToolTips = AfxGetApp() -> GetProfileInt (g_cbConfig, g_cbShowToolTips, true);

#if defined(_USE_SEC_CLASSES)
	ASSERT(m_pControlBarManager != NULL);
	ASSERT_KINDOF(CTRiASToolBarManager, m_pControlBarManager);

CTRiASToolBarManager* pMgr = (CTRiASToolBarManager*)m_pControlBarManager;
BOOL fCoolLook = AfxGetApp() -> GetProfileInt (g_cbConfig, g_cbCoolLook, false);
	
	pMgr -> EnableToolTips (m_fShowToolTips);
	pMgr -> EnableCoolLook (fCoolLook);

	EnableDocking(CBRS_ALIGN_ANY);
	if (IsWin40() && !IsWin41())	// nur unter WinNT40/Win95 !
		EnableCustomCaption (true);
#else
	EnableDocking(CBRS_ALIGN_ANY);
#endif // _USE_SEC_CLASSES

// Basisklasse rufen
	SECToplevelFrame::PreSubclassWindow();
}

void CMainFrame::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu) 
{
HMENU hMenu = pPopupMenu->m_hMenu;

	SECToplevelFrame::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);
	ForwardMsgToTRiAS (m_hWnd, WM_INITMENUPOPUP, (WPARAM)hMenu, MAKELONG(nIndex, bSysMenu));
}

void CMainFrame::OnClose() 
{
// Extension festhalten, da WM_CLOSE alle Erweiterungen freigibt
WUnknown IUnk(m_pITRiASExt);	

	if (ForwardMsgToTRiAS (m_hWnd, WM_CLOSE, 0, 0L))
		SECToplevelFrame::OnClose();
}

BOOL CMainFrame::OnQueryEndSession() 
{
	if (!SECToplevelFrame::OnQueryEndSession())
		return FALSE;
	
	return ForwardMsgToTRiAS (m_hWnd, WM_QUERYENDSESSION, 0, 0L);
}

void CMainFrame::OnEndSession(BOOL bEnding) 
{
	SECToplevelFrame::OnEndSession(bEnding);
	ForwardMsgToTRiAS (m_hWnd, WM_ENDSESSION, bEnding, 0L);
}

void CMainFrame::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	ForwardMsgToTRiAS (m_hWnd, WM_KEYUP, nChar, MAKELONG(nRepCnt, nFlags));
	SECToplevelFrame::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CMainFrame::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	ForwardMsgToTRiAS (m_hWnd, WM_KEYDOWN, nChar, MAKELONG(nRepCnt, nFlags));
	SECToplevelFrame::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CMainFrame::OnContextMenu(CWnd *pWnd, CPoint point)
{
// Menu zusammenbauen, dazu Resource laden
CMenu menu;

	VERIFY(menu.LoadMenu(CG_IDR_POPUP_TRIASTOOL_BAR));

CMenu* pPopup = menu.GetSubMenu(0);

	ASSERT(pPopup != NULL);

// und alle Toolbars hinzufügen
IEnumITRiASBar *pIEnum = NULL;
HRESULT hr = GetEnumTRiASToolBars (&pIEnum);

	if (SUCCEEDED(hr)) {
	ITRiASBar *pIBar = NULL;
	int i = 0;

		for (pIEnum -> Reset(); S_OK == pIEnum -> Next (1, &pIBar, 0); i++)
		{
		char cbName[64];
		UINT uiID = 0;

			try {
			WTRiASToolBar ToolBar = pIBar;		// throws HRESULT

				hr = ToolBar -> GetBarStyle (cbName, sizeof(cbName), NULL, NULL, NULL);
				if (SUCCEEDED(hr)) {
					ToolBar -> GetBarID (&uiID);
					pPopup -> InsertMenu (i, MF_BYPOSITION|MF_STRING, uiID, cbName);
				}
			} catch (_com_error& hr) {
				UNUSED(hr);
				ASSERT(_COM_ERROR(hr) == S_OK);
			}
			pIBar -> Release();
			pIBar = NULL;
		}
	}
	pIEnum -> Release();

// Menu anzeigen
	ActivateFrame();
	pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, point.x, point.y,	this);
}

void CMainFrame::OnMenuSelect(UINT nItemID, UINT nFlags, HMENU hSysMenu) 
{
	SECToplevelFrame::OnMenuSelect(nItemID, nFlags, hSysMenu);
	ForwardMsgToTRiAS (m_hWnd, WM_MENUSELECT, MAKELONG(nItemID, nFlags), (LPARAM)hSysMenu);
}

void CMainFrame::OnNcDestroy() 
{
	SECToplevelFrame::OnNcDestroy();
}


// Cancel abfangen, wenn nicht gerade gezeichnet wird und wir im VollBildMode sind
BOOL CMainFrame::PreTranslateMessage (MSG *pMsg) 
{
// Vollbild mit ESC abbrechen, wenn nicht gerade gezeichnet wird
	if (IsFullScreen() && !DEXI_isDrawing() && m_hAccelEsc) {
	// Translate using m_hAccel
		if (::TranslateAccelerator(m_hWnd, m_hAccelEsc, pMsg))
			return true;
	}

// sonstige hier implementierte Menubefehle
	if (m_hAccelMisc && ::TranslateAccelerator(m_hWnd, m_hAccelMisc, pMsg))
		return true;

// PopupMenu auch zeigen, wenn Dockbar drunter liegt
	if ((((pMsg->message == WM_KEYDOWN || pMsg->message == WM_SYSKEYDOWN) && // If we hit a key and
		(pMsg->wParam == VK_F10) && (GetKeyState(VK_SHIFT) & ~1)) != 0) ||	// it's Shift+F10 OR
		(pMsg->message == WM_CONTEXTMENU) || 								// Natural keyboard key
		(pMsg->message == WM_RBUTTONDOWN))									// right mouse
	{
	CWnd *pWnd = CWnd::FromHandlePermanent (pMsg->hwnd);
	CControlBar *pBar = DYNAMIC_DOWNCAST (CControlBar, pWnd);
	
//		if (NULL == pBar) // oder ist es die StatusBar
//			pBar = DYNAMIC_DOWNCAST (CStatusBar, pWnd);
		if (pBar != NULL && pBar -> IsDockBar()) {
			if (pMsg->message == WM_RBUTTONDOWN) {
			CPoint point;

				GetCursorPos (&point);
				OnContextMenu (NULL, point);
				return true;
			} else {
			CRect rect;

				pBar -> GetClientRect(rect);
				pBar -> ClientToScreen(rect);

			CPoint point = rect.TopLeft();

				point.Offset (5, 5);
				OnContextMenu (NULL, point);
				return true;
			}
		}
	}

	return SECToplevelFrame::PreTranslateMessage(pMsg);
}

///////////////////////////////////////////////////////////////////////////////
// verschicken aller Commands an alle Toolbars, ansonsten normale Behandlung
BOOL CMainFrame::OnCmdMsg (UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
// Alle Toolbars durchgehen, aber nur, wenn wirklich ein Befehl ausgelöst wurde
	for (TRiASBarsMap::iterator it = m_mapBars.begin(); 
		 it != m_mapBars.end(); it++) 
	{
		if (S_OK == (*it).second -> OnCmdMsg (nID, nCode, pExtra, pHandlerInfo))
			return true;	// ok, bearbeitet
	}

// normale Behandlung	
	return SECToplevelFrame::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

// ToolBarPopupMenu wird aktiviert --------------------------------------------
void CMainFrame::OnUpdateToolBarPopup(CCmdUI* pCmdUI) 
{
WTRiASToolBar ToolBar;
HRESULT hr = GetTRiASToolBar (pCmdUI -> m_nID, ToolBar.ppi());

	if (S_OK == hr) {	// mit Häkchen versehen, wenn sichtbar
	DWORD dwStyle = 0L;

		ToolBar -> GetBarStyle (NULL, 0, NULL, &dwStyle, NULL);
		pCmdUI -> SetCheck ((dwStyle & WS_VISIBLE) ? 1 : 0);
	}
}

// ToolBarPopupMenu wurde betätigt --------------------------------------------
void CMainFrame::OnCommandToolBarPopup(UINT nID) 
{
WTRiASToolBar ToolBar;
HRESULT hr = GetTRiASToolBar (nID, ToolBar.ppi());

	if (S_OK == hr) {		// Anzeigen/Ausblenden 
	DWORD dwStyle = 0L;
	DWORD dwStyleEx = 0L;

		ToolBar -> GetBarStyle (NULL, 0L, NULL, &dwStyle, &dwStyleEx);
		if (dwStyle & WS_VISIBLE) 
			ToolBar -> SetBarStyle (NULL, dwStyle & ~WS_VISIBLE, dwStyleEx, false);
		else
			ToolBar -> SetBarStyle (NULL, dwStyle | WS_VISIBLE, dwStyleEx, false);
	}
}

LONG CMainFrame::OnToolBarWndNotify(UINT wParam, LONG lParam)
{
#if defined(_USE_SEC_CLASSES)
HWND hWnd = HWND(lParam);
UINT nNotifyCode = HIWORD(wParam);
UINT uiID = LOWORD(wParam);

	ASSERT(::IsWindow(hWnd));

	switch(nNotifyCode)	{
	case SECWndBtn::WndInit:
		break;

	case SECComboBtn::Entered:
		return OnCmdMsg (uiID, CBN_HITRETURN, NULL, NULL);
	}
#endif // _USE_SEC_CLASSES

	return FALSE;
}

// Menupunkt, der in Vollbildmodus schaltet (bzw. zurück) ---------------------
void CMainFrame::OnViewFullScreen (void)
{
	if (m_bBlownUpMode) {
		if (!m_rNonBlownUpRect.IsRectEmpty()) {
			m_bBlownUpMode = false;
			SetWindowPos(NULL,
				m_rNonBlownUpRect.left,
				m_rNonBlownUpRect.top,
				m_rNonBlownUpRect.Width(),
				m_rNonBlownUpRect.Height(),
				SWP_NOZORDER);
			ResetToolbarsFromFullScreen();
		}
	} else {
		m_bBlownUpMode = true;
		AdjustToolbarsForFullScreen();

		GetWindowRect(&m_rNonBlownUpRect);

	int x = 0, y = 0, cx, cy;
	
		GetBlownUpPosition(&x, &y);
		GetBlownUpSize(&cx, &cy);
		SetWindowPos(NULL, x, y, cx, cy, SWP_NOZORDER);
	}
}

void CMainFrame::AdjustToolbarsForFullScreen (void)
{
// Zustand der Bars wegschreiben
	if (!IsWin32s()) {
	// sämtliche alten Einträge herauslöschen
	CRegKey regLayout;

		regLayout.Attach (AfxGetApp()->GetAppRegistryKey());
		regLayout.RecurseDeleteKey (g_cbLayoutRoot);

	// derzeitiges Layout speichern
		FixedupSaveBarState (g_cbLayout);
	} else
		FixedupSaveBarState (g_cbLayoutRoot);

// StatusBar behandeln
	AdjustStatusbarForFullScreen();

// Standard einstellen, wenn kein Layout gespeichert ist
CRegKey regL;

	regL.Attach (AfxGetApp()->GetAppRegistryKey());
	if (!regL.Open (regL, g_cbLayoutRootFS)) {
	char cbName[_MAX_PATH];
	DWORD dwStyle, dwStyleEx;
	CString strCap;

		GetFullScreenTBCaption (strCap);
		for (TRiASBarsMap::iterator it = m_mapBars.begin(); 
			 it != m_mapBars.end(); ++it)
		{
		HRESULT hr = (*it).second -> GetBarStyle (cbName, _MAX_PATH, NULL, &dwStyle, &dwStyleEx);

			if (SUCCEEDED(hr)) {
				if (strCap == cbName) {
					if (!(dwStyle & WS_VISIBLE)) {
						(*it).second -> FloatBar (CPoint (20, 20), CBRS_ALIGN_TOP);
						(*it).second -> SetBarStyle (cbName, dwStyle | WS_VISIBLE, dwStyleEx | TRIASTOOLBAR_HIDDENTAG, true);
					}
				} else if (dwStyle & WS_VISIBLE)
					(*it).second -> SetBarStyle (cbName, dwStyle & ~WS_VISIBLE, dwStyleEx | TRIASTOOLBAR_HIDDENTAG, true);
			}
		}
	} else {
	// und Zustand aus Registry für FullScreen lesen
		regL.Close();
		if (!IsWin32s()) LoadToolbarState (g_cbLayoutFS);
	}
}

void CMainFrame::ResetToolbarsFromFullScreen (void)
{
// Zustand der FullScreen-Bars wegschreiben
	if (!IsWin32s()) {
	// sämtliche alte Einträge herauslöschen
	CRegKey regLayout;

		regLayout.Attach (AfxGetApp()->GetAppRegistryKey());
		regLayout.RecurseDeleteKey (g_cbLayoutRootFS);

	// derzeitiges Layout speichern
		FixedupSaveBarState (g_cbLayoutFS);
	} 

// StatusBar behandeln
	ResetStatusbarFromFullScreen();

// und Zustand aus Registry für NormalBars lesen
	LoadToolbarState (IsWin32s() ? g_cbLayoutRoot : g_cbLayout);
}

void CMainFrame::AdjustStatusbarForFullScreen (void)
{
	ShowControlBar (&m_wndStatusBar, false, true);
}

void CMainFrame::ResetStatusbarFromFullScreen (void)
{
	ShowControlBar (&m_wndStatusBar, true, true);
}

void CMainFrame::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI)
{
	SECToplevelFrame::OnGetMinMaxInfo(lpMMI);

//	lpMMI->ptMinTrackSize=CPoint(MIN_FRAME_WIDTH, 320);

int cx, cy;

	GetBlownUpSize(&cx, &cy);
	lpMMI->ptMaxTrackSize = CPoint (cx, cy);
}

void CMainFrame::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	if (m_bBlownUpMode && !(nHitTest == HTMENU)) 
		return;

	SECToplevelFrame::OnNcLButtonDown(nHitTest, point);
}

// Anzahl der Pixel, wieweit Menu am oberen Rand sichtbar ist
#define MENU_OVERLAP	2

void CMainFrame::GetBlownUpPosition(int *px, int* py)
{   
	*px=0, *py=0;

	*px -= GetSystemMetrics(SM_CXFIXEDFRAME);
//	*px -= GetSystemMetrics(SM_CXEDGE);

	*py -= GetSystemMetrics(SM_CYFIXEDFRAME);
	*py -= GetSystemMetrics(SM_CYCAPTION);
	*py -= GetSystemMetrics(SM_CYEDGE);
//	*py -= (GetSystemMetrics(SM_CYMENU)-MENU_OVERLAP);
}

void CMainFrame::GetBlownUpSize(int *pcx, int* pcy)
{   
int x, y;

	GetBlownUpPosition(&x, &y);

	*pcx = GetSystemMetrics(SM_CXSCREEN);
	*pcy = GetSystemMetrics(SM_CYSCREEN);

	*pcx += -x*2;

	*pcy += -y;
//	*pcy -= GetSystemMetrics(SM_CYEDGE);
	*pcy += GetSystemMetrics(SM_CYFIXEDFRAME);
	*pcy -= MENU_OVERLAP-1;
}

void CMainFrame::FixedupSaveBarState (LPCTSTR lpszProfileName) const 
{
#if defined(_USE_SEC_CLASSES)
	SaveBarState (lpszProfileName);

TCHAR szSection[256];

	wsprintf (szSection, g_cbSummarySection, lpszProfileName);
	AfxGetApp()->WriteProfileInt (szSection, g_cbSECBars, 1);
#else
CDockState state;

	GetDockState (state);
	
	for (int i = 0; i < state.m_arrBarInfo.GetSize(); i++) {
	CControlBarInfo* pInfo = (CControlBarInfo*)state.m_arrBarInfo[i];
	int nSize = pInfo->m_arrBarID.GetSize(); 

		for (int j = 0; j < nSize - 1; ++j) {
			if ((DWORD)(pInfo->m_arrBarID[j]) >= (DWORD)65536)
			{
			int act = j;

				if ((DWORD)(pInfo->m_arrBarID[j+1]) == 0) // >= (DWORD)65536))
				{
					pInfo->m_arrBarID.RemoveAt (j+1);
					nSize--;
					j--;
				}

				pInfo->m_arrBarID.RemoveAt (act);
				nSize--;
				j--;
			}
		}
	}
	state.SaveState (lpszProfileName);
#endif // _USE_SEC_CLASSES
}

void CMainFrame::FixedupLoadBarState (LPCSTR pcKeyName)
{
#if defined(_USE_SEC_CLASSES)
// nur dann laden, wenn die Einträge aus der SEC-Variante stammen
TCHAR szSection[256];

	wsprintf (szSection, g_cbSummarySection, pcKeyName);
	if (AfxGetApp()->GetProfileInt (szSection, g_cbSECBars, 0))
		LoadBarState (pcKeyName);
#else
	LoadBarState (pcKeyName);
#endif // _USE_SEC_CLASSES
}

///////////////////////////////////////////////////////////////////////////////
// Parameter für Toolbars einstellen, Toolbars anzeigen/ausblenden
void CMainFrame::OnUpdateToolbars(CCmdUI* pCmdUI) 
{
	pCmdUI -> Enable(true);		// 'Symbolleisten ...' immer aktiv
}

void CMainFrame::OnToolbars() 
{
IEnumITRiASBar *pIEnum;
HRESULT hr = GetEnumTRiASToolBars (&pIEnum);

	if (SUCCEEDED(hr)) {
#if defined(_USE_SEC_CLASSES)
		ASSERT(m_pControlBarManager != NULL);
		ASSERT_KINDOF(CTRiASToolBarManager, m_pControlBarManager);

	CTRiASToolBarManager* pMgr = (CTRiASToolBarManager*)m_pControlBarManager;
	BOOL fCoolLook = pMgr -> CoolLookEnabled();
	CToolBarsDlg dlg (this, pIEnum, m_fShowToolTips, fCoolLook);

		dlg.SetManager (pMgr);
#else
	BOOL fCoolLook = FALSE;
	CToolBarsDlg dlg (this, pIEnum, m_fShowToolTips, FALSE);
#endif // _USE_SEC_CLASSES

	int iResult = dlg.DoModal();

		pIEnum -> Release();
		if (IDABORT == iResult || IDCANCEL == iResult)
			return;		// abgebrochen

		if (m_fShowToolTips != dlg.m_fShowToolTips) {
			m_fShowToolTips = dlg.m_fShowToolTips;
			DEXN_ShowToolTips(m_fShowToolTips);		// löst ServerEvent aus
#if defined(_USE_SEC_CLASSES)
			pMgr -> EnableToolTips (m_fShowToolTips);
#endif // _USE_SEC_CLASSES
		}

#if defined(_USE_SEC_CLASSES)
		if (fCoolLook != dlg.m_fCoolLook) {
			fCoolLook = dlg.m_fCoolLook;
			pMgr -> EnableCoolLook (fCoolLook);
			DEXN_EnableCoolLook(fCoolLook);			// löst ServerEvent aus
		}
#endif // _USE_SEC_CLASSES
		if (IDC_CUSTOMIZE == iResult || IDC_NEWTOOLBAR == iResult) 
		// 'Anpassen...' oder 'Neu ...' Button im Dialog wurde gewählt
			ForwardMsgToTRiAS (m_hWnd, WM_COMMAND, ID_STANDARD_CUSTOMIZE-RESID_OFFSET, 0L);
	}
}

///////////////////////////////////////////////////////////////////////////////
// Menupunkt 'Anpassen...', nur aktiv, wenn Projekt offen
void CMainFrame::OnUpdateToolbarCustomize(CCmdUI* pCmdUI) 
{
	TRY {
	CString strPrj;
	LPSTR pBuffer = strPrj.GetBuffer (_MAX_PATH);

		pCmdUI -> Enable(NULL != DEX_GetActiveProject (pBuffer));
	} CATCH (CMemoryException, e) {
		pCmdUI -> Enable (false);
	} END_CATCH
}

void CMainFrame::OnToolbarCustomize() 
{
	ForwardMsgToTRiAS (m_hWnd, WM_COMMAND, ID_STANDARD_CUSTOMIZE-RESID_OFFSET, 0L);
}

// WMIDLEUPDATECMDUI an TRiAS schicken, damit diese Message über den ConnPnt 
// verteilt werden kann
void CMainFrame::OnIdleUpdateCmdUI()
{
	SECToplevelFrame::OnIdleUpdateCmdUI();
	ForwardMsgToTRiAS (m_hWnd, WM_IDLEUPDATECMDUI, 0L, 0L);
}

void CMainFrame::OnSize(UINT nType, int cx, int cy) 
{
	SECToplevelFrame::OnSize(nType, cx, cy);
	ForwardMsgToTRiAS (m_hWnd, WM_SIZE, nType, MAKELONG(cx, cy));
}

#if defined(_USE_SEC_CLASSES)
void CMainFrame::RecalcLayout (BOOL fNotify)
{
	if (!DEX_TestActiveProject())
		InvalidateRect (NULL);
	SECToplevelFrame::RecalcLayout (fNotify);
}

void CMainFrame::ResetInvalidDockbars (CControlBar *pTargetBar)
{
	for (HWND hWndChild = ::GetTopWindow(m_hWnd); hWndChild != NULL;
		hWndChild = ::GetNextWindow(hWndChild, GW_HWNDNEXT))
	{
	SECDockBar* pBar = (SECDockBar*)CWnd::FromHandlePermanent(hWndChild);
		
		if (pBar && pBar->IsKindOf(RUNTIME_CLASS(SECDockBar))) {
			if (NULL == pTargetBar)
				pBar->m_arrInvalidBars.RemoveAll();
			else {
			// finden der Einen und rauslöschen
				for (int i = 0; i < pBar->m_arrInvalidBars.GetSize(); i++) 
				{
					if (pTargetBar == (CControlBar *)pBar->m_arrInvalidBars[i]) 
					{
						pBar->m_arrInvalidBars.RemoveAt(i);
						break;
					}	/*if*/
				}		/*for*/
			}
		}
	}
}
#endif // _USE_SEC_CLASSES

// Heraussuchen einer bestimmten ToolBar --------------------------------------
HRESULT CMainFrame::GetTRiASToolBar (UINT uiID, ITRiASToolBar **ppIToolBar)
{
// MainToolbar wiederfinden
TRiASBarsMap::iterator it = m_mapBars.find (uiID); 

	*ppIToolBar = NULL;
	if (it == m_mapBars.end())
		return S_FALSE;

	*ppIToolBar = (*it).second;
	(*ppIToolBar) -> AddRef();

return NOERROR;
}

// Heraussuchen einer bestimmten ToolBar --------------------------------------
HRESULT CMainFrame::GetTRiASToolBar (LPCSTR pcName, ITRiASToolBar **ppIToolBar)
{
// Toolbar wiederfinden
CString strName;
LPSTR pName = NULL;

	*ppIToolBar = NULL;
	TRY {
		pName = strName.GetBuffer(_MAX_PATH);
	} CATCH (CMemoryException, e) {
		return E_OUTOFMEMORY;
	} END_CATCH

	for (TRiASBarsMap::iterator it = m_mapBars.begin(); 
		 it != m_mapBars.end(); ++it)
	{
	HRESULT hr = (*it).second -> GetBarStyle (pName, _MAX_PATH, NULL, NULL, NULL);

		if (FAILED(hr)) continue;
		if (!strcmp (pcName, pName)) {	// gefunden
			*ppIToolBar = (*it).second;
			(*ppIToolBar) -> AddRef();
			return NOERROR;
		}
	}

return S_FALSE;			// nicht gefunden
}

///////////////////////////////////////////////////////////////////////////////
// alle FloatingToolbar's verstecken
HRESULT CMainFrame::HideFloatingBars (void)
{
DWORD dwStyle, dwStyleEx;
CString strName;
LPSTR pName = NULL;

	TRY {
		pName = strName.GetBuffer(_MAX_PATH);
	} CATCH (CMemoryException, e) {
		return E_OUTOFMEMORY;
	} END_CATCH

	for (TRiASBarsMap::iterator it = m_mapBars.begin(); 
		 it != m_mapBars.end(); ++it)
	{
	HRESULT hr = (*it).second -> GetBarStyle (pName, _MAX_PATH, NULL, &dwStyle, &dwStyleEx);

		if (SUCCEEDED(hr) && (dwStyle & CBRS_FLOATING) && (dwStyle & WS_VISIBLE))
			(*it).second -> SetBarStyle (pName, dwStyle & ~WS_VISIBLE, dwStyleEx, false);
	}

return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// AccelBefehle zum setzen des Focus auf ComboBox's in Toolbar
void CMainFrame::OnEditScaling() 
{
	SetFocusItem (IDS_GEOVIEWTOOLCAPTION, ID_GEOVIEW_SELECTZOOM_BOX);
}

void CMainFrame::OnSelectActview() 
{
	SetFocusItem (IDS_GEOVIEWTOOLCAPTION, ID_GEOVIEW_SELECTVIEW_BOX);
}

HRESULT CMainFrame::SetFocusItem (UINT uiName, UINT uiCmdID)
{
	TRY {
	CString strName; VERIFY(strName.LoadString (uiName));
	WTRiASToolBar TB;

		try {
			THROW_FAILED_HRESULT(GetTRiASToolBar (strName, TB.ppi()));

		HWND hWnd = NULL;

			THROW_FAILED_HRESULT(TB->GetBarHandle(&hWnd));
		
		HWND hCtrl = ::GetDlgItem (hWnd, uiCmdID);

			ASSERT(::IsWindow(hCtrl));
			if (::IsWindowEnabled(hCtrl))
				::SetFocus (hCtrl);

		} catch (_com_error& hr) {
			return _COM_ERROR(hr);
		}

	} CATCH (CMemoryException, e) {
		return E_OUTOFMEMORY;
	} END_CATCH;

	return S_OK;
}

CTRiASView *CMainFrame::CreateSubclassedView (CCreateContext* pContext, HWND hWndView)
{
	ASSERT(m_hWnd != NULL);
	ASSERT(::IsWindow(m_hWnd));
	ASSERT(pContext != NULL);
	ASSERT(pContext->m_pNewViewClass != NULL);

	// Note: can be a CWnd with PostNcDestroy self cleanup
CTRiASView* pView = (CTRiASView *)pContext->m_pNewViewClass->CreateObject();

	if (pView == NULL) {
		TRACE1("Warning: Dynamic create of view type %hs failed.\n",
			pContext->m_pNewViewClass->m_lpszClassName);
		return NULL;
	}
	ASSERT_KINDOF(CTRiASView, pView);

// ViewObjekt an TRiAS-ViewFenster anhängen
HWND hWndOld = pView -> Detach();

	if (NULL != hWndOld && ::IsWindow (hWndOld))
		::DestroyWindow (hWndOld);
	if (!pView -> SubclassWindow (hWndView)) {
		delete pView;
		return NULL;
	}

	if (!pView -> WireDocument (pContext)) {
		pView -> UnsubclassWindow();
		delete pView;
		return NULL;
	}

	return pView;
}

void CMainFrame::OnEnable(BOOL bEnable) 
{
	SECToplevelFrame::OnEnable(bEnable);

// force WM_NCACTIVATE because Windows may think it is unecessary
	if (!bEnable && !(m_nFlags & WF_STAYACTIVE))
		SendMessage(WM_NCACTIVATE, FALSE);
}

#if defined(_USE_SEC_CLASSES)
///////////////////////////////////////////////////////////////////////////////
// zusätzliche Funktionen für SECToolBars

// Bitmap zu ButtonPool hinzufügen
HRESULT CMainFrame::AddBitmap (HINSTANCE hInst, UINT uiRsc, int iBttnCnt, int *piOffset)
{
	ASSERT(m_pControlBarManager != NULL);
	ASSERT_KINDOF(CTRiASToolBarManager, m_pControlBarManager);

CTRiASToolBarManager* pMgr = (CTRiASToolBarManager*)m_pControlBarManager;

	return pMgr -> AddBitmap (hInst, uiRsc, iBttnCnt, piOffset);
}

// ButtonIDs zu ButtonPool und Toolbar hinzufügen
HRESULT CMainFrame::AddButtons (
	CTRiASToolBar *pBar, int iBttnCnt, const TBBUTTON *pcBttns,
	ITRiASUIOwner *pUIOwner)
{
	ASSERT(m_pControlBarManager != NULL);
	ASSERT_KINDOF(CTRiASToolBarManager, m_pControlBarManager);

CTRiASToolBarManager* pMgr = (CTRiASToolBarManager*)m_pControlBarManager;

	return pMgr -> AddButtons (pBar, iBttnCnt, pcBttns, pUIOwner);
}

// Button zu ButtonPool und Toolbar hinzufügen
HRESULT CMainFrame::InsertButton (
	CTRiASToolBar *pBar, int iIndex, const TBBUTTON *pcBttn,
	ITRiASUIOwner *pUIOwner)
{
	ASSERT(m_pControlBarManager != NULL);
	ASSERT_KINDOF(CTRiASToolBarManager, m_pControlBarManager);

CTRiASToolBarManager* pMgr = (CTRiASToolBarManager*)m_pControlBarManager;

	return pMgr -> InsertButton (pBar, iIndex, pcBttn, pUIOwner);
}

// ButtonUIOwner aus ButtonPool herausfischen
HRESULT CMainFrame::GetUIOwner (
	CTRiASToolBar *pBar, int iIndex, ITRiASUIOwner **ppIOwner)
{
	ASSERT(m_pControlBarManager != NULL);
	ASSERT_KINDOF(CTRiASToolBarManager, m_pControlBarManager);

CTRiASToolBarManager* pMgr = (CTRiASToolBarManager*)m_pControlBarManager;

	return pMgr -> GetUIOwner (pBar, iIndex, ppIOwner);
}

// Toolbar rücksetzen
HRESULT CMainFrame::ResetToolBar (CTRiASToolBar *pBar)
{
	ASSERT(m_pControlBarManager != NULL);
	ASSERT_KINDOF(CTRiASToolBarManager, m_pControlBarManager);

CTRiASToolBarManager* pMgr = (CTRiASToolBarManager*)m_pControlBarManager;

	return pMgr -> ResetToolBar (pBar);
}

// Button aus Toolbar entfernen
HRESULT CMainFrame::DeleteButton (CTRiASToolBar *pBar, int iIndex)
{
	ASSERT(m_pControlBarManager != NULL);
	ASSERT_KINDOF(CTRiASToolBarManager, m_pControlBarManager);

CTRiASToolBarManager* pMgr = (CTRiASToolBarManager*)m_pControlBarManager;

	return pMgr -> DeleteButton (pBar, iIndex);
}

// Button aus Toolbar entfernen
HRESULT CMainFrame::GetButton (const CTRiASToolBar *pBar, int iIndex, TBBUTTON *pBttn)
{
	ASSERT(m_pControlBarManager != NULL);
	ASSERT_KINDOF(CTRiASToolBarManager, m_pControlBarManager);

CTRiASToolBarManager* pMgr = (CTRiASToolBarManager*)m_pControlBarManager;

	return pMgr -> GetButton (pBar, iIndex, pBttn);
}

BOOL CMainFrame::CoolLookEnabled (void)
{
	ASSERT(m_pControlBarManager != NULL);
	ASSERT_KINDOF(CTRiASToolBarManager, m_pControlBarManager);

CTRiASToolBarManager* pMgr = (CTRiASToolBarManager*)m_pControlBarManager;

	return pMgr -> CoolLookEnabled();
}
#endif // _USE_SEC_CLASSES

