// Verwaltung von Objektrelationen --------------------------------------------
// File: FAKEMFCX.CXX

#include "fakemfcp.hxx"
#include "fakemfc.h"		// ResourceKonstanten
#include "Strings.h"
#include <xtensnn.h>

#include <toolguid.h>
#include <SrChoice.h>
#include <oleguid.h>

#include <initguid.h>		// nur im einem Module notwendig
#define _TriasTLB_H_
#include <dirisole.h>
#include <xtsnguid.h>
#include <bscrguid.h>		// BSCRIPT.EXT
#include <TrCatIds.h>
#include <objgguid.h>

#include <registrx.hxx>
#include <itoolbar.h>

#include "Wrapper.h"		// SmartInterfaces
#include "fmfcguid.h"
#include "version.h"

#include "ThisDll.h"
#include "fakemfc.hxx"		// die Erweiterung selbst
#include "tipdlg.h"
#include "summinfo.h"
#include "mainfrm.h"
#include "Strings.h"
#include "WelcomeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// Smartinterfaces
DefineSmartInterface(Storage);

///////////////////////////////////////////////////////////////////////////////
#define HELPPOPUPMENU_POSITION_STARTUP	1
#define HELPPOPUPMENU_POSITION			6

#define VIEWPOPUPMENU_POSITION			4
#define FULLSCREEN_POSITION				11

#define EXTRAPOPUPMENU_POSITION			5
#define TOOLBARSDLG_POSITION			4

#define PROJECTPOPUPMENU_POSITION		0
#define NEWPROJECT_POSITION				0

//
// Die folgende Funktion muß vom Nutzer bereitgestellt werden und lediglich
// ein Objekt vom konkreten ErweiterungTyp anlegen. Diese Funktion ist notwendig,
// da keine virtuellen Konstruktoren erlaubt sind.
//
CTriasExtension *NewExtension (void)		// NEU: ohne Parameter
{
	return new CFakeMFCExtension();
}

//
// NEU: Die folgende Funktion muß ebenfalls vom Nutzer bereitgestellt werden. 
// Sie liefert den (für jede Erweiterung neu zu generierenden) CLSID 
// dieser Erweiterung.
// Bitte beachten: JEDE Erweiterung muß ihren eigenen ClassID haben. Dieser ID
// kann mit dem Tool GENGUID.EXE generiert werden. 
//
bool GetExtensionCLSID (CLSID &rClsID)	// Liefert CLSID
{
	memcpy (&rClsID, &CLSID_FakeMFCExtension, sizeof (GUID));
	return true;
}

//
// NEU: Die Funktion UpdateRegistry muß definiert werden, wenn die Erweiterung 
// sich selbst in der RegDB registrieren soll (empfohlen!!).
// Der ProgID (hier 'TRiAS.Features.1') ist eine ZeichenKette, die die Erweiterung
// in der RegDB repräsentiert. Das Format sollte beibehalten werden. Die '... .1'
// steht für die VersionsNummer.
// Der KlassenName (hier die Stringresource hinter IDS_LONGCLASSNAME) ist eine 
// normal-lesbare Zeichenkette, die lokalisiert wird (deshalb in der Resource) und
// die Bezeichnung der Erweiterung definiert.
//
bool UpdateRegistry (bool fRegister)	// RegDB aktualisieren (initialisieren/löschen)
{
	if (fRegister) {	// RegDB initialisieren
	// Erweiterung selbst registrieren
		if (!ExtOleRegisterExtensionClass (g_hInstance,
				CLSID_FakeMFCExtension, 
				TEXT("TRiAS.FakeMFC.1"), IDS_LONGCLASSNAME,
				FAKEMFC_MAJORVERSION, FAKEMFC_MINORVERSION,
				EFPreLoad|EFPriorityLoad8|EFAggregate|EFRegisterToolBitmap))
			return false;
	
	// SummaryInfo-PropertySheets registrieren
		if (!RegisterHandler (CLSID_TRiASDocSummaryInfo, 
				TEXT("TRiASEx.SummaryInfo.1"), IDS_LONGCLASSNAMEEX, 
				CLSID_DirisProject, TEXT("TRiAS.Document.2")))
			return false;
	
	// TipsOfTheDay anfangs anzeigen
	CCurrentUser regTip (g_cbRegSection, true);
	DWORD dwVal = true;

		if (!regTip.SetDWORD (g_cbIntStartup, dwVal)) 
			return false;

	} else {
	// RegDB säubern
		if (!ExtOleUnregisterClass (CLSID_FakeMFCExtension, 
				TEXT("TRiAS.FakeMFC.1")))
			return false;
		if (!UnRegisterHandler (
				CLSID_TRiASDocSummaryInfo, TEXT("TRiASEx.SummaryInfo.1"), 
				CLSID_DirisProject, TEXT("TRiAS.Document.2")))
			return false;
	}

// in jedem Fall LastLayout, NormalLayout und FullScreenLayout löschen
	{
	CRegKey regLayout;

		regLayout.Attach (AfxGetApp()->GetAppRegistryKey());
		regLayout.RecurseDeleteKey (g_cbLayoutRoot);
		regLayout.RecurseDeleteKey (g_cbLayoutRootFS);
		regLayout.RecurseDeleteKey (g_cbLayoutRootOld);
	}

return true;	// alles ok
}


// NEU: Die Funktion void DeleteExtension (CTriasExtension *pTE) muß nicht mehr
// zur Verfügung gestellt werden. Die Destruktoren sind 'virtual', so daß auch so
// alles sauber aufgeräumt werden kann.

// Konstruktor der ExtensionKlasse --------------------------------------------
// Die nutzerdefinierte Erweiterung muß von der Klasse 'CTriasExtension'
// abgeleitet sein, welche wiederum als einzige Parameter die ResID's der
// im Hauptfenster und ORFenster einzuhängeneden Menu's übergeben bekommt.
CFakeMFCExtension :: CFakeMFCExtension (void)
		           : CTriasExtension()
{
	m_dwTOTD = TOTD_ForceNoTips;
	m_pSummInfo = NULL;
	m_fDirty = false;
	m_pBarCont = NULL;

	m_pDocTempl = NULL;
	m_pViewWnd = NULL;
}

// Destruktor -----------------------------------------------------------------
CFakeMFCExtension :: ~CFakeMFCExtension (void) 
{
	ASSERT(NULL == m_pViewWnd);

	DELETE(m_pSummInfo);
	if (m_pBarCont) m_pBarCont  -> Release();
}

STDMETHODIMP CFakeMFCExtension::QueryInterface (REFIID riid, LPVOID *ppvObj)
{
// erst den BarContainer befragen
	if (NULL != m_pBarCont && SUCCEEDED(m_pBarCont -> QueryInterface (riid, ppvObj)))
		return S_OK;

// dann die BasisKlasse
	return CTriasExtension::QueryInterface (riid, ppvObj);
}

// Diese Funktion wird einmalig nach der erfolgreichen Installation der 
// Erweiterung durch TRIAS gerufen. Hier sollten alle notwendigen 
// Initialisierungen erfolgen. Die Semantik hat sich nicht geändert.
STDMETHODIMP_(bool) CFakeMFCExtension :: InitExtension (short iMode)
{
	if (!CTriasExtension :: InitExtension (iMode))
		return false;

// unseren aktuellen Namen besorgen
	{
	CCurrentUser regCfg (g_cbRegConfig);
	DWORD dwSize = _MAX_PATH;

		if (!regCfg.GetSubSZ (g_cbTRiASName, g_cbTRiAS, dwSize))
			strcpy (g_cbTRiAS, g_cbCopyrightName);		// default
	}		

// Notifikationen anfordern
	RegisterNotification (DEX_INITIALIZEDSERVER);
//	RegisterNotification (DEX_N_EXTENSIONSLOADED);
	RegisterNotification (DEX_N_UIREADY);
	RegisterNotification (DEX_N_TIPOFTHEDAY);
	RegisterNotification (DEX_N_SAVESAMESTORAGE);
	RegisterNotification (DEX_N_SAVEOTHERSTORAGE);
	RegisterNotification (DEX_PROJECTOPEN);
	RegisterNotification (DEX_N_PROJECTPRINTED);
	RegisterNotification (DEX_PROJECTCLOSE);
	RegisterNotification (DEX_SERVERCLOSED);

	InstallMenuItem (IDM_SHOWTIPOFTHEDAY, CG_IDS_TIPOFTHEDAYMENU, 
					 IMIStartUpMenu, HELPPOPUPMENU_POSITION_STARTUP, -1);
	InstallMenuItem (IDM_SHOWTIPOFTHEDAY, CG_IDS_TIPOFTHEDAYMENU, 
					 IMINormalMenu, HELPPOPUPMENU_POSITION, -1);
	if (g_dwHookFlags & SUBCLASSTRIAS) {
		InstallMenuItem (IDM_SHOWTOOLBARSDLG, IDS_TOOLBARSDLG, 
					 IMINormalMenu, EXTRAPOPUPMENU_POSITION, TOOLBARSDLG_POSITION);
		InstallMenuItem (IDM_SWITCHFULLSCREENMODE, IDS_SWITCHFULLSCREENMODE, 
					 IMINormalMenu, VIEWPOPUPMENU_POSITION, FULLSCREEN_POSITION);

	// Projekt Neu ... - alte Einträge raus, neue rein
		InstallMenuItem (IDM_CREATENEWPROJECT, IDS_CREATENEWPROJECT, 
					 IMIStartUpMenu, PROJECTPOPUPMENU_POSITION, NEWPROJECT_POSITION);
		InstallMenuItem (IDM_CREATENEWPROJECT, IDS_CREATENEWPROJECT, 
					 IMINormalMenu, PROJECTPOPUPMENU_POSITION, NEWPROJECT_POSITION);
		RemoveMenuItem (IDM_NEWDB, IMINormalMenu|IMIOrigMenuItem, NEWPROJECT_POSITION);
		RemoveMenuItem (IDM_NEWDB, IMIStartUpMenu|IMIOrigMenuItem, NEWPROJECT_POSITION);

		if (g_dwHookFlags & SUBCLASSTRIASVIEW) {
		// Standard initialization
			RegisterNotification (DEX_N_VIEWCREATED);
			RegisterNotification (DEX_N_VIEWDELETED);
		
		// Register the application's document templates.  Document templates
		//  serve as the connection between documents, frame windows and views.
			AfxGetApp()->AddDocTemplate(NULL);		// nicht statischen DocMgr verwenden
			m_pDocTempl = new CTRiASDocTemplate(
				IDR_MAINFRAME, 
				RUNTIME_CLASS(CTRiASDoc),		// Document Class
				NULL,							// Frame Class
				RUNTIME_CLASS(CTRiASView));		// View Class

	/*	pDocTemplate->SetContainerInfo(IDR_CNTR_INPLACE);
		pDocTemplate->SetServerInfo(
			IDR_SRVR_EMBEDDED, IDR_SRVR_INPLACE,
			RUNTIME_CLASS(CInPlaceFrame));
	*/		AfxGetApp()->AddDocTemplate(m_pDocTempl);

		// Connect the COleTemplateServer to the document template.
		//  The COleTemplateServer creates new documents on behalf
		//  of requesting OLE containers by using information
		//  specified in the document template.
		//		m_server.ConnectTemplate(clsid, pDocTemplate, TRUE);
				// Note: SDI applications register server objects only if /Embedding
				//   or /Automation is present on the command line.
		} 

	// MainToolbar erzeugen
	CMainFrame *pFrame = (CMainFrame *)MWind();

		ASSERT(NULL != pFrame);

	// BarContainer erzeugen und initialisieren
		if (FAILED(CComObject<CTRiASBarCont>::CreateInstance(&m_pBarCont)))
			return false;
		if (NULL == m_pBarCont) return false;

		m_pBarCont -> AddRef();		// wird mit RefCnt == 0 angelegt
		m_pBarCont -> SetFrame (pFrame);

		pFrame -> InstallToolBars();		// Fehler nicht fatal
		pFrame -> InstallStatusBar();
	}

return true;
}

// Diese Funktion wird gerufen bevor die Erweiterung freigegeben wird.
// An dieser Stelle kann (und soll) der gesamte von der Erweiterung angeforderte
// Speicher freigegeben, und sonstige Aufräumarbeiten durchgeführt werden.
// Die Semantik hat sich nicht geändert.
STDMETHODIMP_(bool) CFakeMFCExtension :: UnLoadExtension (void)
{
	if (g_dwHookFlags & SUBCLASSTRIAS) {
	CMainFrame *pFrame = (CMainFrame *)MWind();

		ASSERT(NULL != pFrame);

	// CControlBars wieder freigeben
		if (FAILED(pFrame -> FreeToolBars()))
			ASSERT(false);
		if (FAILED(pFrame -> FreeStatusBar()))
			ASSERT(false);

	// COntainer der ToolBars entlassen
		if (m_pBarCont) {
			m_pBarCont -> Release();
			m_pBarCont = NULL;
		}
	}

//	UnRegisterNotification (DEX_INITIALIZEDSERVER);
//	UnRegisterNotification (DEX_N_EXTENSIONSLOADED);
//	UnRegisterNotification (DEX_N_TIPOFTHEDAY);
	UnRegisterNotification (DEX_N_SAVESAMESTORAGE);
	UnRegisterNotification (DEX_N_SAVEOTHERSTORAGE);
	UnRegisterNotification (DEX_PROJECTOPEN);
	UnRegisterNotification (DEX_N_PROJECTPRINTED);
	UnRegisterNotification (DEX_PROJECTCLOSE);
	UnRegisterNotification (DEX_SERVERCLOSED);
	if (g_dwHookFlags & SUBCLASSTRIASVIEW) {
		UnRegisterNotification (DEX_N_VIEWDELETED);
		UnRegisterNotification (DEX_N_VIEWCREATED);
	}

	RemoveMenuItem (IDM_SHOWTIPOFTHEDAY, IMINormalMenu, HELPPOPUPMENU_POSITION);
	RemoveMenuItem (IDM_SHOWTIPOFTHEDAY, IMIStartUpMenu, HELPPOPUPMENU_POSITION_STARTUP);
	
	if (g_dwHookFlags & SUBCLASSTRIAS) {
		RemoveMenuItem (IDM_SHOWTOOLBARSDLG, IMINormalMenu, EXTRAPOPUPMENU_POSITION);
		RemoveMenuItem (IDM_SWITCHFULLSCREENMODE, IMINormalMenu, VIEWPOPUPMENU_POSITION);
		RemoveMenuItem (IDM_CREATENEWPROJECT, IMINormalMenu, NEWPROJECT_POSITION);
		RemoveMenuItem (IDM_CREATENEWPROJECT, IMIStartUpMenu, NEWPROJECT_POSITION);
	}

return CTriasExtension :: UnLoadExtension();
}

///////////////////////////////////////////////////////////////////////////////
// Handler für notifications
STDMETHODIMP_(LRESULT) CFakeMFCExtension :: Notification (WPARAM wParam, LPARAM lParam)
{
	switch (wParam) {
	case DEX_INITIALIZEDSERVER:
		OnInitializedServer();
		break;

	case DEX_N_UIREADY:
		OnExtensionsLoaded();
		break;

	case DEX_SERVERCLOSED:
		OnServerClosed();
		break;

	case DEX_N_TIPOFTHEDAY:
		return OnQueryTipOfTheDay(lParam);

	case DEX_PROJECTOPEN:
		OnOpenDocument();
		break;

	case DEX_N_SAVESAMESTORAGE:
		OnSaveDocument ((IStorage *)lParam, true);
		break;

	case DEX_N_SAVEOTHERSTORAGE:
		OnSaveDocument ((IStorage *)lParam, false);
		break;

	case DEX_N_PROJECTPRINTED:
		OnProjectPrinted();
		break;

	case DEX_PROJECTCLOSE:		// Projekt wird geschlossen
		OnClosingProject();
		break;

	case DEX_N_VIEWCREATED:		// ViewFenster erzeugt
		if (g_dwHookFlags & SUBCLASSTRIASVIEW) 
			OnViewCreated ((HWND)lParam);
		break;

	case DEX_N_VIEWDELETED:		// ViewFenster zerlegt
		if (g_dwHookFlags & SUBCLASSTRIASVIEW) 
			OnViewDeleted ((HWND)lParam);
		break;
	}

	return CTriasExtension::Notification (wParam, lParam);
}

// AFXPRIV.H:
#define WM_SETMESSAGESTRING 0x0362  // wParam = nIDS (or 0),
									// lParam = lpszOther (or NULL)

bool CFakeMFCExtension::FindMenuItem (CMenu *pMenu, UINT uiID)
{
UINT uiCnt = pMenu -> GetMenuItemCount();

	uiID += MenuOffset();
	for (UINT uiLoop = 0; uiLoop < uiCnt; uiLoop++) {
		if (uiID == pMenu->GetMenuItemID (uiLoop))
			return true;
	}

	return false;		// nichts gefunden
}

STDMETHODIMP_(bool) CFakeMFCExtension::MenuInit (HMENU hMenu, LPARAM lParam, HWND hWnd)
{
CMenu *pMenu = CMenu::FromHandle (hMenu);

	ASSERT(NULL != pMenu);
	if (!FindMenuItem (pMenu, IDM_SWITCHFULLSCREENMODE))
		return false;		// nicht unser Menu

CMainFrame *pFrame = (CMainFrame *)MWind();

	ASSERT(NULL != pFrame);

UINT uiFlags = MF_BYCOMMAND | (pFrame->IsFullScreen() ? MF_CHECKED : MF_UNCHECKED);

	pMenu -> CheckMenuItem (IDM_SWITCHFULLSCREENMODE+MenuOffset(), uiFlags);

	return true;
}

STDMETHODIMP_(bool) CFakeMFCExtension :: MenuSelect (UINT uiMenuID, HMENU hMenu, HWND hWnd)
{
	if (NULL != hWnd) return false;		// nicht für uns

// StatusZeile anpassen
	if (!(g_dwHookFlags & SUBCLASSTRIAS)) return false;

UINT uiID = 0;

	switch (uiMenuID) {
	case IDM_SHOWTIPOFTHEDAY:
		uiID = CG_IDS_TIPOFTHEDAY;
		break;

	case IDM_SHOWTOOLBARSDLG:
		uiID = IDM_SHOWTOOLBARSDLG_STATUS;
		break;

	case IDM_SWITCHFULLSCREENMODE:
		uiID = IDS_SWITCHFULLSCREENMODE_STATUS;
		break;

	case IDM_CREATENEWPROJECT:
		uiID = ID_STANDARD_NEWPRJ;
		break;

	default:
		return false;		// auch das ist nicht für uns
	}

CMainFrame *pFrame = (CMainFrame *)MWind();

	ASSERT(NULL != pFrame);
	pFrame -> SendMessage (WM_SETMESSAGESTRING, uiID);

	return true;
}

STDMETHODIMP_(bool) CFakeMFCExtension :: MenuCommand (WPARAM wParam, HWND hWnd)
{
	switch (wParam) {
	case IDM_SHOWTIPOFTHEDAY:
		ShowTipOfTheDay();
		return true;

	case IDM_CREATENEWPROJECT:
		ShowNewprojectCommand();
		return true;
	}

// Accels only
	if (g_dwHookFlags & SUBCLASSTRIAS) {
	CMainFrame *pFrame = (CMainFrame *)MWind();

		ASSERT(NULL != pFrame);
		switch (wParam) {
		case IDM_SHOWTOOLBARSDLG:
			pFrame -> ShowToolBarDlg();		// Dialog anzeigen und auswerten
			break;
		
		case IDM_SWITCHFULLSCREENMODE:
			pFrame -> OnViewFullScreen();
			break;

		case ID_EDIT_SCALING:
			pFrame -> OnEditScaling();
			break;

		case ID_SELECT_ACTVIEW: 
			pFrame -> OnSelectActview();
			break;

		default:
			return false;
		}
		return true;
	}

	return false;	// keine Menubearbeitung
}

void CFakeMFCExtension::ShowTipAtStartup (void)
{
// CG: This function added by 'Tip of the Day' component.
	if (!(m_dwTOTD & TOTD_ForceTips))
		return;

	ShowTipOfTheDay();
}

void CFakeMFCExtension::ShowTipOfTheDay(void)
{
// CG: This function added by 'Tip of the Day' component.
CTipDlg dlg (MWind());

	dlg.DoModal();
}

// SummaryInfo behandlen ------------------------------------------------------
HRESULT CFakeMFCExtension::OnCreateNewDocument (IStorage *pIStg)
{
	if (NULL == pIStg || NULL == m_pSummInfo) 
		return ResultFromScode (E_FAIL);

// Title, Subject, Author, Keywords default to empty string
// Comments, Template, SavedBy default to empty string
// LastSave, LastPrint, EditTime, RevNum default to 0
// NumWords, NumChars default to 0
	m_pSummInfo -> StartEditTimeCount();
	m_pSummInfo -> RecordCreateDate();
	m_pSummInfo -> SetAppname (szApp);

char cbBuffer[_MAX_PATH+1];
ULONG ulLen = sizeof(cbBuffer);

	if (::GetUserName (cbBuffer, &ulLen)) 
		m_pSummInfo -> SetAuthor (cbBuffer);

	return NOERROR;
}

HRESULT CFakeMFCExtension::OnOpenDocument (void)
{
WStorage IStg;

	if (!DEX_GetProjectStorage(*IStg.ppv())) 
		return E_FAIL;

	m_fDirty = false;
	DELETE(m_pSummInfo);

	m_pSummInfo = new CSummInfo;
	if (NULL == m_pSummInfo)
		return ResultFromScode (E_OUTOFMEMORY);

HRESULT hr = m_pSummInfo -> ReadFromStorage (IStg);

	if (FAILED(hr) && STG_E_FILENOTFOUND == GetScode(hr))
		hr = OnCreateNewDocument (IStg);
	else if (SUCCEEDED(hr))
		m_pSummInfo -> StartEditTimeCount();

	return hr;
}

HRESULT CFakeMFCExtension::OnSaveDocument (IStorage *pIStg, bool fSameAsLoad)
{
	ASSERT(NULL != m_pSummInfo);

char cbBuffer[80];
ULONG ulLen = sizeof(cbBuffer);

	if (fSameAsLoad) {
		m_pSummInfo -> RecordSaveDate();
		m_pSummInfo -> IncrRevNum();
		m_pSummInfo -> AddCountToEditTime();
		m_pSummInfo -> StartEditTimeCount();
	
		if (::GetUserName (cbBuffer, &ulLen))
			m_pSummInfo -> SetLastAuthor (cbBuffer);

	HRESULT hr = m_pSummInfo -> WriteToStorage (pIStg);

		if (SUCCEEDED(hr))
			DEX_SetDirtyGeoDB (true);	// Commit erzwingen
		return hr;
	} else {
	CSummInfo *pSummInfo = new CSummInfo;

		pSummInfo -> RecordCreateDate();
		pSummInfo -> RecordSaveDate();
		pSummInfo -> IncrRevNum();

		pSummInfo -> SetAppname (szApp);

		pSummInfo -> SetAuthor (m_pSummInfo -> GetAuthor());
		pSummInfo -> SetKeywords (m_pSummInfo -> GetKeywords());
		pSummInfo -> SetSubject (m_pSummInfo -> GetSubject());
		pSummInfo -> SetComments (m_pSummInfo -> GetComments());
		pSummInfo -> SetTemplate (m_pSummInfo -> GetTemplate());
		pSummInfo -> SetTitle (m_pSummInfo -> GetTitle());

		if (::GetUserName (cbBuffer, &ulLen)) 
			pSummInfo -> SetLastAuthor (cbBuffer);
		else 
			pSummInfo -> SetLastAuthor (m_pSummInfo -> GetLastAuthor());

		pSummInfo -> SetNumWords (m_pSummInfo -> GetNumWordsNum());
		pSummInfo -> SetNumChars (m_pSummInfo -> GetNumCharsNum());
		pSummInfo -> SetSecurity (m_pSummInfo -> GetSecurityNum());

	HRESULT hr = pSummInfo -> WriteToStorage (pIStg);

		if (SUCCEEDED(hr)) {
			delete m_pSummInfo;
			m_pSummInfo = pSummInfo;
			m_pSummInfo -> StartEditTimeCount();
		} else
			delete pSummInfo;
					
		return hr;
	}
}

HRESULT CFakeMFCExtension::OnProjectPrinted (void)
{
	if (NULL == m_pSummInfo) 
		return ResultFromScode (E_FAIL);

	m_pSummInfo -> RecordPrintDate();
	m_fDirty = true;

	return NOERROR;
}

HRESULT CFakeMFCExtension::OnClosingProject (void)
{
	if (m_fDirty) {
		DEX_SetDirtyGeoDB (true);
		m_fDirty = false;
		return NOERROR;
	}

	return ResultFromScode (S_FALSE);
}

bool CFakeMFCExtension::OnInitializedServer (void)
{
	UnRegisterNotification (DEX_INITIALIZEDSERVER);
	ShowTipAtStartup();
	if (!DEXN_ShowProjectWizard(m_dwTOTD))
		ShowProjectWizard();
	return true;
}

bool CFakeMFCExtension::OnExtensionsLoaded (void)
{
	if (g_dwHookFlags & SUBCLASSTRIAS) {
	CMainFrame *pFrame = (CMainFrame *)MWind();

		ASSERT(NULL != pFrame);
		try {
			pFrame -> LoadToolbarState (IsWin32s() ? g_cbLayoutRoot : g_cbLayout);
			pFrame -> NotifyAboutToolTips();	// löst ServerEvent aus
		} catch (...) {
			;		// BUG in MFC
		}
	}
	UnRegisterNotification (DEX_N_UIREADY);
	return true;
}

bool CFakeMFCExtension::OnServerClosed (void)
{
	if (g_dwHookFlags & SUBCLASSTRIAS) {
	CMainFrame *pFrame = (CMainFrame *)MWind();

		ASSERT(NULL != pFrame);
		pFrame -> SaveToolbarState();
		pFrame -> HideFloatingBars();
	}
	return true;
}

bool CFakeMFCExtension::OnQueryTipOfTheDay (DWORD dwFlags)
{
	UnRegisterNotification (DEX_N_TIPOFTHEDAY);

bool fShowTips = false;

	if (dwFlags & TOTD_ForceNoTips) {
		m_dwTOTD = TOTD_ForceNoTips|TOTD_ForceNoWizard;
		fShowTips = false;			// TipsNotShown
	} else if (dwFlags & TOTD_ForceTips) {
		m_dwTOTD = TOTD_ForceTips;
		fShowTips = true;			// TipsToBeShown
	} else {
	CCurrentUser regTip (g_cbRegSection);
	DWORD dwVal = false;

		m_dwTOTD = TOTD_ForceNoTips;
		fShowTips = false;

		if (regTip.GetDWORD (g_cbIntStartup, dwVal) && dwVal) {
			m_dwTOTD = TOTD_ForceTips;
			fShowTips = true;	// TipsToBeShown
		}
	}

// wenn kein TOTD angezeigt werden soll, dann nach OpenWizard suchen
bool fShowWizard = false;

	{
	CCurrentUser regOWiz (g_cbMRUFiles);
	DWORD dwData = 0;

		if (regOWiz.GetDWORD (g_cbShowOpenWizard, dwData) && 0 != dwData) {
			m_dwTOTD |= TOTD_ForceNoWizard;
			fShowWizard = false;
		} else 
			fShowWizard = true;	// OWizard anzeigen
	}
	return fShowTips || fShowWizard;
}

bool CFakeMFCExtension::OnViewCreated (HWND hViewWnd)
{
	ASSERT(NULL != m_pDocTempl);

// ViewObjekt anlegen
	m_pViewWnd = m_pDocTempl -> SubclassView (hViewWnd);
	if (NULL == m_pViewWnd) 
		return false;

	return true;
}

bool CFakeMFCExtension::OnViewDeleted (HWND hViewWnd)
{
// evtl.Fehler beim Erzeugen des Projektfensters
	if (NULL == m_pViewWnd) return false;

// Projektfenster wurde geschlossen
	ASSERT(::IsWindow(m_pViewWnd -> m_hWnd));

	if (::IsWindow(m_pViewWnd -> m_hWnd)) {
	// Keine aktive View mehr (zumindest für die MFC)
		((CFrameWnd *)MWind()) -> SetActiveView (NULL, FALSE);

	// jetzt Fenster wieder abmelden
	HWND hWndOld = m_pViewWnd -> UnsubclassWindow();

		ASSERT(hWndOld == hViewWnd);

		m_pViewWnd -> m_hWnd = NULL;
		DELETE(m_pViewWnd);
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// Stuff for MFC-DLL ----------------------------------------------------------
CThisDLL MyExtensionDLL (NULL); // ==>> Titel in AFX_IDS_APP_TITLE !!

