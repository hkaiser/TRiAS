// Verwaltung von Objektrelationen --------------------------------------------
// File: FAKEMFCX.CXX

#include "fakemfcp.hxx"
#include "fakemfc.h"		// ResourceKonstanten
#include "Strings.h"
#include <xtensnn.h>

#include <ospace/file/path.h>
#include <ScopeVar.h>

#include <initguid.h>		// nur im einem Module notwendig
#include <toolguid.h>
#include <SrChoice.h>
#include <oleguid.h>
#define _TriasTLB_H_
#include <dirisole.h>
#include <xtsnguid.h>
#include <bscrguid.h>		// BSCRIPT.EXT
#include <TrCatIds.h>
#include <objgguid.h>

#include <registrx.hxx>
#include <Esnecil.h>
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

#include "InPlaceFrame.h"	// #AD19991220		OleInPlace-Aktivierung

// weitere benötigte Guid's
const IID IID_ITRiASNotificationSink = {0x0796385A,0x3123,0x101C,{0xBB,0x62,0x00,0xAA,0x00,0x18,0x49,0x7C}};
const IID IID_ITRiASSysNotificationSink = {0x0796386E,0x3123,0x101C,{0xBB,0x62,0x00,0xAA,0x00,0x18,0x49,0x7C}};
const CLSID CLSID_GeoDocument = {0x937EEB40,0x2234,0x101B,{0xAA,0xE1,0xE7,0xE7,0xE7,0xE7,0xE7,0xE7}};
const CLSID CLSID_CatSimpleCache = {0xEA68A685,0x5166,0x4E55,{0x90,0x62,0x0B,0x13,0x06,0x81,0x33,0x93}};

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#if _TRiAS_VER < 0x0400
///////////////////////////////////////////////////////////////////////////////
// Version 4 emulieren
DWORD g_dwVer4 = 0;
#endif // _TRiAS_VER < 0x0400
#if _TRiAS_VER < 0x0510
DWORD g_dwVer51 = 0;
#endif // _TRiAS_VER < 0x0510

///////////////////////////////////////////////////////////////////////////////
// Smartinterfaces
DefineSmartInterface(Storage);
DefineSmartInterface(TRiASProjectEvents);
DefineSmartInterface(TRiASProject);
DefineSmartInterface(CatInformation);
DefineSmartInterface(EnumGUID);
DefineSmartInterface(EnumString);

///////////////////////////////////////////////////////////////////////////////
// ComponentCategory
extern const CATID CATID_TRiASDBEngine;

///////////////////////////////////////////////////////////////////////////////
#define HELPPOPUPMENU_POSITION_STARTUP	1
#define HELPPOPUPMENU_POSITION			HELP_MENU_POS

#define VIEWPOPUPMENU_POSITION			VIEW_MENU_POS
#define FULLSCREEN_POSITION				3

#define EXTRAPOPUPMENU_POSITION			EXTRA_MENU_POS
#define TOOLBARSDLG_POSITION			4

#define PROJECTPOPUPMENU_POSITION		PROJECT_MENU_POS
#define NEWPROJECT_POSITION				0
#define OPENPROJECT_POSITION			1
#define HANDLEDATASOURCES_POSITION		8
#define HANDLECONNECTFILTERS_POSITION	9
#define PRINTPREVIEW_POSITION			12

///////////////////////////////////////////////////////////////////////////////
// gecachete GUIDs der DBEngines
CFakeMFCExtension::CEnumGuids CFakeMFCExtension::s_DBEngineGUIDs;

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
BOOL GetExtensionCLSID (CLSID &rClsID)	// Liefert CLSID
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
BOOL UpdateRegistry (BOOL fRegister)	// RegDB aktualisieren (initialisieren/löschen)
{
	if (fRegister) {	// RegDB initialisieren
	// Erweiterung selbst registrieren
		if (!ExtOleRegisterExtensionClass (g_hInstance,
				CLSID_FakeMFCExtension, 
				TEXT("TRiAS.FakeMFC.1"), IDS_LONGCLASSNAME,
				FAKEMFC_MAJORVERSION, FAKEMFC_MINORVERSION,
				EFPreLoad|EFPriorityLoad8|EFAggregate|EFRegisterToolBitmap|EFDragDropTarget))
			return false;
	
	// SummaryInfo-PropertySheets registrieren
		if (!RegisterHandler (CLSID_TRiASDocSummaryInfo, 
				TEXT("TRiASEx.SummaryInfo.1"), IDS_LONGCLASSNAMEEX, 
				CLSID_GeoDocument, TEXT("TRiAS.Document.2")))
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
				CLSID_GeoDocument, TEXT("TRiAS.Document.2")))
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
CFakeMFCExtension::CFakeMFCExtension (void)
		           : CTriasExtension()
{
	m_dwTOTD = TOTD_ForceNoTips;
	m_pSummInfo = NULL;
	m_fDirty = false;
	m_pBarCont = NULL;

	m_pDocTempl = NULL;
	m_pViewWnd = NULL;

	m_dwCookie = 0L;
	m_ulOpenSem = 0L;

	m_cbDexProcs = NULL;
	m_iDexProcsNum = 0;
	m_i1stDexProc = 0;

	m_pPopupMenu = NULL;
	m_pConnectFilterMenu = NULL;

	m_bRunEmbedded = false;

	s_DBEngineGUIDs.InitGuids();

#if defined(_USE_DRAG_N_DROP)
	m_fHasExts = false;
#endif // defined(_USE_DRAG_N_DROP)

	m_pManageConnections = NULL;
}

// Destruktor -----------------------------------------------------------------
CFakeMFCExtension::~CFakeMFCExtension (void) 
{
	ASSERT(NULL == m_pManageConnections);
	ASSERT(NULL == m_pViewWnd);
	ASSERT(NULL == m_cbDexProcs);

	DELETE_OBJ(m_pConnectFilterMenu);
	DELETE_OBJ(m_pPopupMenu);
	DELETE_OBJ(m_pSummInfo);
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
STDMETHODIMP_(BOOL) CFakeMFCExtension::InitExtension (short iMode)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	if (!CTriasExtension::InitExtension (iMode) || !InitJumpTable())
		return false;

// unseren aktuellen Namen besorgen
	{
	CCurrentUser regCfg (KEY_READ, g_cbRegConfig);
	DWORD dwSize = _MAX_PATH;

		if (!regCfg.GetSubSZ (g_cbTRiASName, g_cbTRiAS, dwSize))
			strcpy (g_cbTRiAS, g_cbCopyrightName);		// default

#if _TRiAS_VER < 0x0400
		g_dwVer4 = 0;
		regCfg.GetDWORD (TEXT("FakeTRiAS4"), g_dwVer4);
#endif // _TRiAS_VER < 0x0400
#if _TRiAS_VER < 0x0510
		g_dwVer51 = 0;
		regCfg.GetDWORD (TEXT("FakeTRiAS51"), g_dwVer51);
#endif // _TRiAS_VER < 0x0510
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
	RegisterNotification (DEX_N_PROJECTTOCLOSE);
	RegisterNotification (DEX_ISCLOSEDPROJECT);
	RegisterNotification (DEX_SERVERCLOSED);
	RegisterNotification (DEX_HEADERREREAD);

// WindowsNotifikationen anfordern
	RegisterNotification (__DexCmd, FALSE);		// alle DEX_... bei uns vorbeischicken

	InstallMenuItem (IDM_SHOWTIPOFTHEDAY, CG_IDS_TIPOFTHEDAYMENU, 
					 IMIStartUpMenu, HELPPOPUPMENU_POSITION_STARTUP, -1);
	InstallMenuItem (IDM_SHOWTIPOFTHEDAY, CG_IDS_TIPOFTHEDAYMENU, 
					 IMINormalMenu, HELPPOPUPMENU_POSITION, -1);

	if (g_dwHookFlags & TRIASMODE_SubClassTRiAS) {
	// sämtliche projektbezogenen und andere Menupunkte umleiten
		InstallMenuItems();

		if (g_dwHookFlags & TRIASMODE_SubClassTRiASView) {
		// Standard initialization
			RegisterNotification (DEX_N_VIEWCREATED);
			RegisterNotification (DEX_N_VIEWDELETED);
			RegisterNotification (DEX_PAINTTOPLAYER);
		
		// Register the application's document templates.  Document templates
		//  serve as the connection between documents, frame windows and views.
			AfxGetApp()->AddDocTemplate(NULL);		// nicht statischen DocMgr verwenden
			m_pDocTempl = new CTRiASDocTemplate(
				IDR_MAINFRAME, 
				RUNTIME_CLASS(CTRiASDoc),		// Document Class
				NULL,							// Frame Class
				RUNTIME_CLASS(CTRiASView));		// View Class

		// #AD991026: Zunächst nur der Server
//			pDocTemplate->SetContainerInfo(IDR_CNTR_INPLACE);

		// #AD991026: zunächst nur 'embedded', nicht 'in Place'
//			m_pDocTempl ->SetServerInfo(
//				IDR_MAINFRAME, IDR_MAINFRAME,
//				RUNTIME_CLASS(CInPlaceFrame));
//			AfxGetApp()->AddDocTemplate(m_pDocTempl);

			m_pDocTempl->SetServerInfo(IDR_MAINFRAME);
			AfxGetApp()->AddDocTemplate(m_pDocTempl);

		// Connect the COleTemplateServer to the document template.
		//  The COleTemplateServer creates new documents on behalf
		//  of requesting OLE containers by using information
		//  specified in the document template.
//			ASSERT( FALSE );	// Debug Break #AD000125
			m_server.ConnectTemplate(CLSID_GeoDocument, m_pDocTempl, TRUE);
			// Note: SDI applications register server objects only if /Embedding
			//   or /Automation is present on the command line.

		// #AD991026: command line auswerten
		// Parse command line for standard shell commands, DDE, file open
		CCommandLineInfo cmdInfo;

			AfxGetApp()->ParseCommandLine(cmdInfo);

			// Check to see if launched as OLE server
			if (cmdInfo.m_bRunEmbedded && !cmdInfo.m_bRunAutomated) {
			// Register all OLE server (factories) as running.  This enables the
			//  OLE libraries to create objects from other applications.
			// Das Registrieren erfolgt in OLE2AUTO.CXX in Auswertung der Notifikation
			// DEX_HANDLEEMBEDDING !
				DEX_ChangeMRUMode(false);		// MRU abschalten!

				m_bRunEmbedded = true;
				InstallEmbeddedMenu();
			}
		} 

#if defined(_SEC_SUBCLASS_ORWND)
	// Recherchefenster subclass'n
		RegisterNotification (DEX_CREATEOBJEKTINFO);
		RegisterNotification (DEX_OBJWNDCLOSED);
#endif // _SEC_SUBCLASS_ORWND

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

// DBEngines instantiieren und starten
	return StartDBEngines();
}

///////////////////////////////////////////////////////////////////////////////
// MenuItems verwalten
void CFakeMFCExtension::InstallMenuItems (void)
{
// sonstiges ...
//	InstallMenuItem (IDM_SHOWTOOLBARSDLG, IDS_TOOLBARSDLG, 
//				 IMINormalMenu, EXTRAPOPUPMENU_POSITION, TOOLBARSDLG_POSITION);
	InstallMenuItem (IDM_SWITCHFULLSCREENMODE, IDS_SWITCHFULLSCREENMODE, 
				 IMINormalMenu, VIEWPOPUPMENU_POSITION, FULLSCREEN_POSITION);

// ToolBars >
	InstallToolbarMenu();

// Projekt Neu ... - alte Einträge raus, neue rein
	InstallMenuItem (IDM_CREATENEWPROJECT, IDS_CREATENEWPROJECT, 
				 IMIStartUpMenu, PROJECTPOPUPMENU_POSITION, NEWPROJECT_POSITION);
	InstallMenuItem (IDM_CREATENEWPROJECT, IDS_CREATENEWPROJECT, 
				 IMINormalMenu, PROJECTPOPUPMENU_POSITION, NEWPROJECT_POSITION);
	RemoveMenuItem (IDM_NEWDB, IMINormalMenu|IMIOrigMenuItem, PROJECTPOPUPMENU_POSITION);
	RemoveMenuItem (IDM_NEWDB, IMIStartUpMenu|IMIOrigMenuItem, PROJECTPOPUPMENU_POSITION);

// Projekt öffnen - alte Einträge raus, neue rein
	InstallMenuItem (IDM_OPENPROJECT, IDS_OPENPROJECT, 
				 IMIStartUpMenu, PROJECTPOPUPMENU_POSITION, OPENPROJECT_POSITION);
	InstallMenuItem (IDM_OPENPROJECT, IDS_OPENPROJECT, 
				 IMINormalMenu, PROJECTPOPUPMENU_POSITION, OPENPROJECT_POSITION);
	RemoveMenuItem (IDM_OPEN, IMINormalMenu|IMIOrigMenuItem, PROJECTPOPUPMENU_POSITION);
	RemoveMenuItem (IDM_OPEN, IMIStartUpMenu|IMIOrigMenuItem, PROJECTPOPUPMENU_POSITION);

#if defined(_USE_PRINT_PREVIEW)
// Druckvorschau
#if _TRiAS_VER < 0x0400
	if (0 != g_dwVer4) 
#endif // _TRiAS_VER < 0x0400
	{
#if _TRiAS_VER < 0x0510
		if (0 == g_dwVer51) {
		// ManageConnectFilters steht über diesem Eintrag
			InstallMenuItem (IDM_PRINTPREVIEW, IDS_PRINTPREVIEW_MENU, 
						 IMINormalMenu, PROJECTPOPUPMENU_POSITION, PRINTPREVIEW_POSITION-1);
		}
		else 
#endif // _TRiAS_VER < 0x0510
		{
			InstallMenuItem (IDM_PRINTPREVIEW, IDS_PRINTPREVIEW_MENU, 
						 IMINormalMenu, PROJECTPOPUPMENU_POSITION, PRINTPREVIEW_POSITION);
		}
		RemoveMenuItem (IDM_PRINTPREVIEW_ORG, IMINormalMenu|IMIOrigMenuItem, PROJECTPOPUPMENU_POSITION);
	}
#endif // defined(_USE_PRINT_PREVIEW)

// Datenquellen verwalten ...
	InstallMenuItem (IDM_MANAGEDATASOURCESDEL, 0, 
				 IMINormalMenu, PROJECTPOPUPMENU_POSITION, HANDLEDATASOURCES_POSITION);
	InstallMenuItem (IDM_MANAGEDATASOURCES, IDS_MANAGEDATASOURCES, 
				 IMINormalMenu, PROJECTPOPUPMENU_POSITION, HANDLEDATASOURCES_POSITION);

#if _TRiAS_VER < 0x0510
	if (0 != g_dwVer51) 
#endif // _TRiAS_VER < 0x0510
	{
		InstallConnectFilterMenu();
	}
}

void CFakeMFCExtension::InstallEmbeddedMenu (void)
{
// Projekt Neu ... gibt es im Embedded-Mode nicht
	RemoveMenuItem (IDM_CREATENEWPROJECT, IMINormalMenu, NEWPROJECT_POSITION);
	RemoveMenuItem (IDM_CREATENEWPROJECT, IMIStartUpMenu, NEWPROJECT_POSITION);

// Projekt öffnen ... gibt es im Embedded-Mode ebenfalls nicht
	RemoveMenuItem (IDM_OPENPROJECT, IMINormalMenu, NEWPROJECT_POSITION);
	RemoveMenuItem (IDM_OPENPROJECT, IMIStartUpMenu, NEWPROJECT_POSITION);

// Projekt schließen ... ersetzen durch Dokument aktualisieren
	InstallMenuItem (IDM_UPDATECLIENT, IDS_UPDATECLIENT, 
				 IMINormalMenu, PROJECTPOPUPMENU_POSITION, NEWPROJECT_POSITION);
	RemoveMenuItem (IDM_CLOSE, IMINormalMenu|IMIOrigMenuItem, PROJECTPOPUPMENU_POSITION);

// Projekt speichern, Speichern als... gibt es hier nicht
	RemoveMenuItem (IDM_SAVEDB, IMINormalMenu|IMIOrigMenuItem, PROJECTPOPUPMENU_POSITION);
	RemoveMenuItem (IDM_SAVEAS, IMINormalMenu|IMIOrigMenuItem, PROJECTPOPUPMENU_POSITION);
	// Kopie speichern unter.. kann auch im Embedded-Mode nützlich sein!
//	RemoveMenuItem (IDM_SAVECOPYAS, IMINormalMenu|IMIOrigMenuItem, PROJECTPOPUPMENU_POSITION);

// Beenden ... ersetzen durch 'Schließen und zurück zu xx'
	InstallMenuItem (IDM_RETURN, IDS_RETURN, IMINormalMenu, PROJECTPOPUPMENU_POSITION);
	RemoveMenuItem (IDM_EXIT, IMINormalMenu|IMIOrigMenuItem, PROJECTPOPUPMENU_POSITION);

// zu guter Letzt die überzähligen Separatoren
	RemoveMenuItem (-1, IMINormalMenu|IMIOrigMenuItem, PROJECTPOPUPMENU_POSITION, 12);
	RemoveMenuItem (-1, IMINormalMenu|IMIOrigMenuItem, PROJECTPOPUPMENU_POSITION, 1);
}

void CFakeMFCExtension::RemoveMenuItems (void)
{
#if _TRiAS_VER < 0x0510
	if (0 != g_dwVer51) 
#endif // _TRiAS_VER < 0x0510
	{
		RemoveConnectFilterMenu();
	}
#if defined(_USE_PRINT_PREVIEW)
// Druckvorschau
#if _TRiAS_VER < 0x0400
	if (0 != g_dwVer4) 
#endif // _TRiAS_VER < 0x0400
	{
		RemoveMenuItem (IDM_PRINTPREVIEW, IMINormalMenu, PROJECTPOPUPMENU_POSITION);
	}
#endif // defined(_USE_PRINT_PREVIEW)

// Datenquellen verwalten ...
	RemoveMenuItem (IDM_MANAGEDATASOURCESDEL, IMINormalMenu, PROJECTPOPUPMENU_POSITION);
	RemoveMenuItem (IDM_MANAGEDATASOURCES, IMINormalMenu, PROJECTPOPUPMENU_POSITION);

// Toolbars >
	RemoveToolbarMenu();

// sonstige zusätzliche Menupunkte
//	RemoveMenuItem (IDM_SHOWTOOLBARSDLG, IMINormalMenu, EXTRAPOPUPMENU_POSITION);
	RemoveMenuItem (IDM_SWITCHFULLSCREENMODE, IMINormalMenu, VIEWPOPUPMENU_POSITION);

// Projektverwaltung
	if (!m_bRunEmbedded) {
		RemoveMenuItem (IDM_CREATENEWPROJECT, IMINormalMenu, PROJECTPOPUPMENU_POSITION);
		RemoveMenuItem (IDM_CREATENEWPROJECT, IMIStartUpMenu, PROJECTPOPUPMENU_POSITION);
		RemoveMenuItem (IDM_OPENPROJECT, IMINormalMenu, PROJECTPOPUPMENU_POSITION);
		RemoveMenuItem (IDM_OPENPROJECT, IMIStartUpMenu, PROJECTPOPUPMENU_POSITION);
	}
	else {
		RemoveMenuItem (IDM_RETURN, IMINormalMenu, PROJECTPOPUPMENU_POSITION);
		RemoveMenuItem (IDM_UPDATECLIENT, IMINormalMenu, PROJECTPOPUPMENU_POSITION);
	}
}

BOOL CFakeMFCExtension::InstallToolbarMenu()
{
// erst Separator einfügen
	InstallMenuItem((UINT)-1, 0, IMINormalMenu, VIEWPOPUPMENU_POSITION, FULLSCREEN_POSITION);

// PopupMenu einbauen
	if (NULL == m_pPopupMenu) {
		ATLTRY(m_pPopupMenu = new CMenu());
		if (NULL == m_pPopupMenu || !m_pPopupMenu -> LoadMenu (CG_IDR_POPUP_TRIASTOOL_BARMENU))
			return FALSE;
	}

INSTALLMENUITEMEX imi;

	INITSTRUCT(imi, INSTALLMENUITEMEX);
	imi.hDex = hDex();
	imi.iMenuID = -1;
	imi.iFlag = IMINormalMenu;
	imi.iMenuNum = VIEWPOPUPMENU_POSITION;
	imi.iMenuPos = FULLSCREEN_POSITION;

// PopUpMenu und MenuText holen
char cbBuffer[64];

	imi.hMenu = GetSubMenu (m_pPopupMenu -> m_hMenu, 0);
	ASSERT(NULL != imi.hMenu);
	GetMenuString (m_pPopupMenu -> m_hMenu, 0, cbBuffer, sizeof(cbBuffer), MF_BYPOSITION);

	imi.pMenuText = cbBuffer;
	return (NULL != DEX_InstallMenuItem (imi)) ? TRUE : FALSE;
}

void CFakeMFCExtension::RemoveToolbarMenu()
{
REMOVEMENUITEMEX rmi;

	INITSTRUCT(rmi, REMOVEMENUITEMEX);
	rmi.hDex = hDex();
	rmi.iMenuID = -1;
	rmi.iMenuNum = VIEWPOPUPMENU_POSITION;
	rmi.iFlag = IMINormalMenu;
	rmi.iMenuPos = FULLSCREEN_POSITION;
	DEX_RemoveMenuItem (rmi);

	RemoveMenuItem ((UINT)-1, IMINormalMenu, VIEWPOPUPMENU_POSITION, FULLSCREEN_POSITION);
}

BOOL CFakeMFCExtension::InstallConnectFilterMenu()
{
// PopupMenu einbauen
	if (NULL == m_pConnectFilterMenu) {
		ATLTRY(m_pConnectFilterMenu = new CMenu());
		if (NULL == m_pConnectFilterMenu || 
			!m_pConnectFilterMenu -> LoadMenu (IDR_POPUP_TRIASTOOL_CONNECTFILTERMENU))
		{
			return FALSE;
		}
	}

INSTALLMENUITEMEX imi;

	INITSTRUCT(imi, INSTALLMENUITEMEX);
	imi.hDex = hDex();
	imi.iMenuID = -1;
	imi.iFlag = IMINormalMenu;
	imi.iMenuNum = PROJECTPOPUPMENU_POSITION;
	imi.iMenuPos = HANDLECONNECTFILTERS_POSITION;

// PopUpMenu und MenuText holen
char cbBuffer[64];

	imi.hMenu = GetSubMenu (m_pConnectFilterMenu -> m_hMenu, 0);
	ASSERT(NULL != imi.hMenu);
	GetMenuString (m_pConnectFilterMenu -> m_hMenu, 0, cbBuffer, 
		sizeof(cbBuffer), MF_BYPOSITION);

	imi.pMenuText = cbBuffer;
	return (NULL != DEX_InstallMenuItem (imi)) ? TRUE : FALSE;
}

void CFakeMFCExtension::RemoveConnectFilterMenu()
{
REMOVEMENUITEMEX rmi;

	INITSTRUCT(rmi, REMOVEMENUITEMEX);
	rmi.hDex = hDex();
	rmi.iMenuID = -1;
	rmi.iMenuNum = PROJECTPOPUPMENU_POSITION;
	rmi.iFlag = IMINormalMenu;
	rmi.iMenuPos = HANDLECONNECTFILTERS_POSITION;
	DEX_RemoveMenuItem (rmi);
}

///////////////////////////////////////////////////////////////////////////////
// DBEngines starten und anhalten
bool CFakeMFCExtension::StartDBEngines (void)
{
	try {
	// DBEngines über CATID enumerieren
		THROW_FAILED_HRESULT(s_DBEngineGUIDs.InitGuids());

//	WEnumGUID EnumGuids;		// Enumerator der RegisterTRiASExtension-Objekte
//	WCatInformation CatInfo (CLSID_StdComponentCategoriesMgr);	// throws hr
//	GUID guidImpl[1]; 
//
//		guidImpl[0] = CATID_TRiASDBEngine;
//		THROW_FAILED_HRESULT(CatInfo -> EnumClassesOfCategories (1, guidImpl, 0, NULL, EnumGuids.ppi()));

	GUID guid;
	STARTMODE rgStartMode = STARTMODE_Normal;
	
		if (DEX_QueryMode() & QMSysAdmin)
			rgStartMode = (STARTMODE)(STARTMODE_SysAdmin|STARTMODE_CompatibleWithStb);

	CCurrentUser regCfg (g_cbRegConfig);
	DWORD dwBackup = 0;

		if (regCfg.GetDWORD(g_cbBackupDatafiles, dwBackup) && 0 != dwBackup)
			rgStartMode = (STARTMODE)(rgStartMode | STARTMODE_BackupDatafile);

		_ASSERTE(s_DBEngineGUIDs.IsValid());
		for (s_DBEngineGUIDs.Reset(); S_OK == s_DBEngineGUIDs.Next (1, &guid, NULL); /**/)
		{
		WTRiASDBEngine DBEng;
		WUnknown Dummy;
		HRESULT hr = DBEng.CreateInstance(guid);

			if (FAILED(hr)) {
				if (CLASS_E_NOTLICENSED == hr)
					s_DBEngineGUIDs.RemoveActiveItem();
				continue;	// registriert, aber nicht instantiierbar (nicht lizensiert o.ä.)
			}

			if (SUCCEEDED(DBEng -> QueryInterface (IID_ITRiASMainDBEngine, Dummy.ppv())))
			{
			// TRiAS bei dieser GeoDBEngine registrieren
				ASSERT(0 == m_dwCookie);	// nur eine DBEngine darf eine MainDBEngine sein
				THROW_FAILED_HRESULT(AtlAdvise (DBEng, m_pXtnSite, IID_ITRiASProjectEvents, &m_dwCookie));
#if defined(_SEC_USE_TABWND)
				THROW_FAILED_HRESULT(((CMainFrame *)MWind()) -> ConnectProject (DBEng));
#endif // defined(_SEC_USE_TABWND)
			}

			if (SUCCEEDED(DBEng -> Start(rgStartMode))) {	// starten und ...
			// ...zur Liste hinzufügen
				try {
				DWORD dwCookie = 0;

					AtlAdvise (DBEng, m_pXtnSite, IID_ITRiASDBEngineEvents, &dwCookie);		// darf fehlschlagen
					m_DBEngs.push_back (CTRiASDBEngines::value_type(DBEng, dwCookie));
				} catch (...) {
					DBEng -> Stop();		// Engine anhalten
					if (Dummy.IsValid()) {
						AtlUnadvise (DBEng, IID_ITRiASProjectEvents, m_dwCookie);
						m_dwCookie = 0;
					}
					_com_issue_error(E_OUTOFMEMORY);
				}
			}
		}

	} catch (_com_error &e) {
		ASSERT(FALSE);	
		VMessageBox (MWind(), FakeTRiASName(IDS_DBENGINITFAILURE_CAP, g_cbTRiAS).c_str(), 
			MB_OK|MB_ICONSTOP, IDS_DBENGINITFAILURE, _COM_ERROR(e), g_cbTRiAS);
		return FALSE;
	}

// Nutzer von Mißständen informieren
	ASSERT(0 != m_dwCookie);		// einer muß MainDBEngine sein
	if (0 == m_dwCookie) {
		VMessageBox (MWind(), FakeTRiASName(IDS_BADREGISTRATION_CAP, g_cbTRiAS).c_str(), 
			MB_OK|MB_ICONSTOP, IDS_BADREGISTRATION, g_cbTRiAS);
		return FALSE;
	}
	return TRUE;
}

bool CFakeMFCExtension::StopDBEngines (void)
{
	try {
	// DataServerRegEntries freigeben
		m_Entries.Assign(NULL);

	// TRiAS bei der GeoDBEngine abmelden
		ASSERT(0 != m_dwCookie);

		for (CTRiASDBEngines::iterator it = m_DBEngs.begin(); it != m_DBEngs.end(); ++it)
		{
		WUnknown Dummy;

			if (SUCCEEDED((*it).first -> QueryInterface (IID_ITRiASMainDBEngine, Dummy.ppv())))
			{
				ASSERT(0 != m_dwCookie);	// nur einer darf MainDBEngine sein
				THROW_FAILED_HRESULT(AtlUnadvise ((*it).first, IID_ITRiASProjectEvents, m_dwCookie));
				m_dwCookie = 0L;
#if defined(_SEC_USE_TABWND)
				THROW_FAILED_HRESULT(((CMainFrame *)MWind()) -> DisconnectProject (*it));
#endif // defined(_SEC_USE_TABWND)
			}
			if (0 != (*it).second)
				AtlUnadvise((*it).first, IID_ITRiASDBEngineEvents, (*it).second);
			THROW_FAILED_HRESULT((*it).first -> Stop());
		}

	} catch (_com_error &) {
		ASSERT(FALSE);
		return false;
	}

	ASSERT(0 == m_dwCookie);		// einer muß MainDBEngine sein
	m_DBEngs.clear();				// alles freigeben
	return true;	 
}

// Diese Funktion wird gerufen bevor die Erweiterung freigegeben wird.
// An dieser Stelle kann (und soll) der gesamte von der Erweiterung angeforderte
// Speicher freigegeben, und sonstige Aufräumarbeiten durchgeführt werden.
// Die Semantik hat sich nicht geändert.
STDMETHODIMP_(BOOL) CFakeMFCExtension::UnLoadExtension (void)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	StopDBEngines();	// TRiAS wieder abmelden

	if (g_dwHookFlags & TRIASMODE_SubClassTRiAS) {
	CMainFrame *pFrame = (CMainFrame *)MWind();

		ASSERT(NULL != pFrame);

	// CControlBars wieder freigeben
		if (FAILED(pFrame -> FreeToolBars()))
			ASSERT(false);
		if (FAILED(pFrame -> FreeStatusBar()))
			ASSERT(false);

	// Container der ToolBars entlassen
		if (m_pBarCont) {
			m_pBarCont -> Release();
			m_pBarCont = NULL;
		}

		CTRiASView::m_ptToolTest.Assign(NULL);

#if defined(_SEC_SUBCLASS_ORWND)
	// Recherchefenster subclass'n
		UnRegisterNotification (DEX_CREATEOBJEKTINFO);
		UnRegisterNotification (DEX_OBJWNDCLOSED);
#endif // _SEC_SUBCLASS_ORWND
	}

//	UnRegisterNotification (DEX_INITIALIZEDSERVER);
//	UnRegisterNotification (DEX_N_EXTENSIONSLOADED);
//	UnRegisterNotification (DEX_N_TIPOFTHEDAY);
	UnRegisterNotification (DEX_N_SAVESAMESTORAGE);
	UnRegisterNotification (DEX_N_SAVEOTHERSTORAGE);
	UnRegisterNotification (DEX_PROJECTOPEN);
	UnRegisterNotification (DEX_N_PROJECTPRINTED);
	UnRegisterNotification (DEX_ISCLOSEDPROJECT);
	UnRegisterNotification (DEX_N_PROJECTTOCLOSE);
	UnRegisterNotification (DEX_PROJECTCLOSE);
	UnRegisterNotification (DEX_SERVERCLOSED);
	UnRegisterNotification (DEX_HEADERREREAD);
	if (g_dwHookFlags & TRIASMODE_SubClassTRiASView) {
		UnRegisterNotification (DEX_N_VIEWDELETED);
		UnRegisterNotification (DEX_N_VIEWCREATED);
		UnRegisterNotification (DEX_PAINTTOPLAYER);
	}

// WindowsNotifikationen abmelden
	UnRegisterNotification (__DexCmd, FALSE);		// alle DEX_... bei uns vorbeischicken

	RemoveMenuItem (IDM_SHOWTIPOFTHEDAY, IMINormalMenu, HELPPOPUPMENU_POSITION);
	RemoveMenuItem (IDM_SHOWTIPOFTHEDAY, IMIStartUpMenu, HELPPOPUPMENU_POSITION_STARTUP);
	
	if (g_dwHookFlags & TRIASMODE_SubClassTRiAS) 
		RemoveMenuItems();

	FreeJumpTable();
	return CTriasExtension::UnLoadExtension();
}

///////////////////////////////////////////////////////////////////////////////
// Handler für notifications
STDMETHODIMP_(LRESULT) CFakeMFCExtension::Notification (WPARAM wParam, LPARAM lParam)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());

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

	case DEX_PROJECTCLOSE:			// Projekt soll geschlossen werden 
		OnClosingProject();
		break;

	case DEX_N_PROJECTTOCLOSE:		// Projekt wird geschlossen werden
		OnProjectToClose();
		break;

	case DEX_ISCLOSEDPROJECT:
		CoFreeUnusedLibraries();	// alles freigeben
		break;

	case DEX_N_VIEWCREATED:		// ViewFenster erzeugt
		if (g_dwHookFlags & TRIASMODE_SubClassTRiASView) 
			OnViewCreated ((HWND)lParam);
		break;

	case DEX_N_VIEWDELETED:		// ViewFenster zerlegt
		if (g_dwHookFlags & TRIASMODE_SubClassTRiASView) 
			OnViewDeleted ((HWND)lParam);
		break;

	case DEX_PAINTTOPLAYER:
		{
		HDC *phDCs = reinterpret_cast<HDC *>(lParam);
		CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
		CTRiASView *pView = (CTRiASView *)pFrame->GetActiveView();

			ASSERT_KINDOF(CTRiASView, pView);
			pView -> PaintTopLayer(phDCs[0], phDCs[1]);
		}
		break;

#if defined(_SEC_SUBCLASS_ORWND)
	case DEX_CREATEOBJEKTINFO:		// ORFenster erzeugt
		if (g_dwHookFlags & TRIASMODE_SubClassTRiAS) 
			OnORWndCreated ((HWND)lParam);
		break;

	case DEX_OBJWNDCLOSED:			// ORFenster zerlegt
		if (g_dwHookFlags & TRIASMODE_SubClassTRiAS) 
			OnORWndDeleted ((HWND)lParam);
		break;
#endif // _SEC_SUBCLASS_ORWND

	case DEX_HEADERREREAD:
		OnReReadHeader();
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

bool ConnectFiltersExist();		// testet Existenz mindestens eines Filters

STDMETHODIMP_(BOOL) CFakeMFCExtension::MenuInit (HMENU hMenu, LPARAM lParam, HWND hWnd)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());

CMenu *pMenu = CMenu::FromHandle (hMenu);
CMainFrame *pFrame = (CMainFrame *)MWind();

	ASSERT(NULL != pFrame);
	ASSERT(NULL != pMenu);

	if (FindMenuItem (pMenu, IDM_SWITCHFULLSCREENMODE)) {
	UINT uiFlags = MF_BYCOMMAND | (pFrame->IsFullScreen() ? MF_CHECKED : MF_UNCHECKED);

		pMenu -> CheckMenuItem (IDM_SWITCHFULLSCREENMODE+MenuOffset(), uiFlags);
		return true;
	
	} 
	else if (NULL != m_pPopupMenu && 
		hMenu == GetSubMenu (m_pPopupMenu -> m_hMenu, 0)) 
	{
	// alle ToolbarItems herausnehmen
	int iCnt = pMenu -> GetMenuItemCount() -2;	// die letzten 2 Einträge drinlassen

		for (int i = 0; i < iCnt; i++)
			pMenu -> RemoveMenu(0, MF_BYPOSITION);

	// neue ToolbarItems einfügen
		return pFrame -> InitToolbarMenu (pMenu);
	}
	else if (NULL != m_pConnectFilterMenu && 
		hMenu == GetSubMenu (m_pConnectFilterMenu -> m_hMenu, 0)) 
	{
		if (!ConnectFiltersExist()) {
			pMenu -> CheckMenuItem(IDM_SHOWCONNECTFILTERS+MenuOffset(), 
				MF_BYCOMMAND|MF_UNCHECKED);
			pMenu -> EnableMenuItem(IDM_SHOWCONNECTFILTERS+MenuOffset(),
				MF_BYCOMMAND|MF_GRAYED);
		}
		else {
		BOOL fShownFilters = FALSE;

			DEX_ConnectionFiltersShown(fShownFilters);
			pMenu -> EnableMenuItem(IDM_SHOWCONNECTFILTERS+MenuOffset(), 
				MF_BYCOMMAND|MF_ENABLED);
			pMenu -> CheckMenuItem(IDM_SHOWCONNECTFILTERS+MenuOffset(), 
				MF_BYCOMMAND| (fShownFilters ? MF_CHECKED : MF_UNCHECKED));
		}
		return true;
	}
	return false;
}

STDMETHODIMP_(BOOL) CFakeMFCExtension::MenuSelect (UINT uiMenuID, HMENU hMenu, HWND hWnd)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());

	if (NULL != hWnd) return false;		// nicht für uns

// StatusZeile anpassen
	if (!(g_dwHookFlags & TRIASMODE_SubClassTRiAS)) return false;

UINT uiID = 0;

	switch (uiMenuID) {
	case IDM_SHOWTIPOFTHEDAY:
		uiID = CG_IDS_TIPOFTHEDAY;
		break;

//	case IDM_SHOWTOOLBARSDLG:
//		uiID = IDM_SHOWTOOLBARSDLG_STATUS;
//		break;

	case IDM_SWITCHFULLSCREENMODE:
		uiID = IDS_SWITCHFULLSCREENMODE_STATUS;
		break;

	case IDM_CREATENEWPROJECT:
		uiID = ID_STANDARD_NEWPRJ;
		break;

	case IDM_OPENPROJECT:
		uiID = ID_STANDARD_OPEN;
		break;

	case IDM_MANAGEDATASOURCES:
		uiID = ID_STANDARD_DATASOURCES;
		break;

	case IDM_MANAGECONNECTFILTERS:
		uiID = ID_CONNECTFILTERS_MANAGE;
		break;

	case IDM_CREATECONNECTFILTER:
		uiID = ID_CONNECTFILTERS_CREATE;
		break;

	case IDM_SHOWCONNECTFILTERS:
		uiID = ID_CONNECTFILTERS_TOGGLESHOW;
		break;

	case IDM_TOOLBARSDLG:
		uiID = ID_TOOLBARS;
		break;

	case IDM_CUSTOMIZEDLG:
		uiID = ID_STANDARD_CUSTOMIZE2;
		break;

#if defined(_USE_PRINT_PREVIEW)
	case IDM_PRINTPREVIEW:
		uiID = ID_STANDARD_PRINTPREVIEW;
		break;
#endif // defined(_USE_PRINT_PREVIEW)

	default:
		return false;
	}

CMainFrame *pFrame = (CMainFrame *)MWind();

	ASSERT(NULL != pFrame);
	pFrame -> SendMessage (WM_SETMESSAGESTRING, uiID);
	return true;
}

STDMETHODIMP_(BOOL) CFakeMFCExtension::MenuCommand (WPARAM wParam, HWND hWnd)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	switch (wParam) {
	case IDM_SHOWTIPOFTHEDAY:
		ShowTipOfTheDay();
		return true;

	case IDM_UPDATECLIENT:
	// Als Notification herum schicken! Wird dann von OLE2Auto behandelt
		DEXN_OleUpdateClient();
		return true;

	case IDM_RETURN:
	// Als Notification herum schicken! Wird dann von OLE2Auto behandelt
		DEXN_OleReturnToClient();
		return true;
	}

// Accels only
	if (g_dwHookFlags & TRIASMODE_SubClassTRiAS) {
	CMainFrame *pFrame = (CMainFrame *)MWind();

		ASSERT(NULL != pFrame);
		switch (wParam) {
//		case IDM_SHOWTOOLBARSDLG:
//			pFrame -> ShowToolBarDlg();		// Dialog anzeigen und auswerten
//			break;
		
		case IDM_SWITCHFULLSCREENMODE:
			pFrame -> OnViewFullScreen();
			break;

		case ID_EDIT_SCALING:
			pFrame -> OnEditScaling();
			break;

		case ID_SELECT_ACTVIEW: 
			pFrame -> OnSelectActview();
			break;

		// Projekt- und Connection- Verwaltung
		case IDM_MANAGEDATASOURCES:
			pFrame -> OnManageConnections();
			break;

		case IDM_MANAGECONNECTFILTERS:
			pFrame -> OnManageConnectFilters();
			break;

		case IDM_CREATECONNECTFILTER:
			pFrame -> OnCreateConnectFilter();
			break;

		case IDM_SHOWCONNECTFILTERS:
			pFrame -> OnShowConnectFilters();
			break;

		case IDM_CREATENEWPROJECT:
			ShowNewprojectCommand();
			break;

		case IDM_OPENPROJECT:
	#if defined(_USE_LEGACY_CODE)
			if (::GetKeyState (VK_CONTROL) < 0)	// Schlupfloch lassen 
				return ForwardMsgToTRiAS (MWind() -> GetSafeHwnd(), WM_COMMAND, IDM_OPEN);
	#endif // _USE_LEGACY_CODE
			ShowOpenprojectCommand();
			break;

		case IDM_OPENOLDPROJECT1:
		case IDM_OPENOLDPROJECT2:
		case IDM_OPENOLDPROJECT3:
		case IDM_OPENOLDPROJECT4:
	#if defined(_USE_LEGACY_CODE)
			if (::GetKeyState (VK_CONTROL) < 0)	// Schlupfloch lassen 
				return ForwardMsgToTRiAS (MWind() -> GetSafeHwnd(), WM_COMMAND, 8000 + wParam -1);
	#endif // _USE_LEGACY_CODE
			OpenLastMRUProject (wParam);
			break;

//		case IDM_TOOLBARSDLG:
//			pFrame -> OnToolbars();
//			return true;

		case IDM_CUSTOMIZEDLG:
			pFrame -> OnToolbarCustomize();
			return true;

#if defined(_USE_PRINT_PREVIEW)
		case IDM_PRINTPREVIEW:
			pFrame -> OnPrintPreview();
			return true;
#endif // defined(_USE_PRINT_PREVIEW)
			
		default:
			return pFrame -> OnToolbarCommand (wParam);
		}
		return true;
	}
	return false;	// keine Menubearbeitung
}

///////////////////////////////////////////////////////////////////////////////
// Hilfsroutinen zur Eventbehandlung
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
	m_pSummInfo -> SetAppname (FakeTRiASName (szApp, g_cbTRiAS).c_str());

char cbBuffer[_MAX_PATH+1];
ULONG ulLen = sizeof(cbBuffer);

	if (::GetUserName (cbBuffer, &ulLen)) 
		m_pSummInfo -> SetAuthor (cbBuffer);

	return NOERROR;
}

HRESULT CFakeMFCExtension::OnOpenDocument (void)
{
	TRACE( "CFakeMFCExtension::OnOpenDocument\r\n" );

WStorage IStg;

	if (!DEX_GetProjectStorage(*IStg.ppv())) 
	{
		TRACE( "CFakeMFCExtension::OnOpenDocument  DEX_GetProjectStorage failed\r\n" );
		return E_FAIL;
	}

// summary Info laufend halten
	m_fDirty = false;
	DELETE_OBJ(m_pSummInfo);

	m_pSummInfo = new CSummInfo;
	if (NULL == m_pSummInfo)
		return ResultFromScode (E_OUTOFMEMORY);

HRESULT hr = m_pSummInfo -> ReadFromStorage (IStg);

	if (FAILED(hr) && STG_E_FILENOTFOUND == GetScode(hr))
		hr = OnCreateNewDocument (IStg);
	else if (SUCCEEDED(hr))
		m_pSummInfo -> StartEditTimeCount();

#if defined(_USE_DOCKEDTABWINDOW)
// DockingTabWIndow das Ereignis mitteilen
CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();

	_ASSERTE(NULL != pFrame);
	pFrame -> OnOpenDocument();
#endif // defined(_USE_DOCKEDTABWINDOW)
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

		pSummInfo -> SetAppname (FakeTRiASName (szApp, g_cbTRiAS).c_str());

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
		
		DEX_SetDirtyGeoDB (true);
		m_fDirty = false;
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

HRESULT CFakeMFCExtension::OnReReadHeader()
{
// HeaderEntry abfragen
GEODBHDRENTRY DBEntry;
char cbBuffer[_MAX_PATH+1];
CString rsCaption(g_cbCaption);

	INITSTRUCT (DBEntry, GEODBHDRENTRY);
	strcpy (DBEntry.hdrKey, rsCaption);
	DBEntry.lphdrText = cbBuffer;
	DBEntry.hdrTextLen = _MAX_PATH;

#if defined(DEX_ReadHeaderEntry)
	if (DEX_ReadHeaderEntry (HACTPROJECT, DBEntry) != 0)
		return S_FALSE; // kein Caption gegeben
#else
	if (DEX_ReadGeoDBHdrEntry(DBEntry) != 0)
		return S_FALSE; // kein Caption gegeben
#endif // DEX_ReadHeaderEntry

	m_pSummInfo -> SetTitle(DBEntry.lphdrText);
	m_fDirty = true;
	return S_OK;
}

HRESULT CFakeMFCExtension::OnClosingProject (void)
{
	if (m_fDirty) {
		DEX_SetDirtyGeoDB (true);
		m_fDirty = false;
		return NOERROR;
	}
	return S_FALSE;
}

HRESULT CFakeMFCExtension::OnProjectToClose (void)
{
#if defined(_USE_DOCKEDTABWINDOW)
// DockingTabWnd informieren
CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();

	_ASSERTE(NULL != pFrame);
	pFrame -> OnClosingDocument();
#endif // defined(_USE_DOCKEDTABWINDOW)
	return S_OK;
}

bool CFakeMFCExtension::OnInitializedServer (void)
{
	UnRegisterNotification (DEX_INITIALIZEDSERVER);

#if _TRiAS_VER >= 0x0510
	if (!m_esnecil.IsValid() || 
		(!m_esnecil.IsDemoCopy() && !m_esnecil.VerifyLevel(CKILEVEL_ANALYSE))
	   )
	{
	// inform user :-)
	CString strTitle;
	CString strLicText;

		VERIFY(strTitle.LoadString(IDS_LICENSE_WARNING));
		VERIFY(strLicText.LoadString(IDS_NEWLICENSE_SCHEME));
		ATLTRY(strTitle = FakeTRiASName (strTitle, g_cbTRiAS).c_str());

	VERIFYLICENSEEX VL;

		INITSTRUCT(VL, VERIFYLICENSEEX);
		VL.pcLicText = strLicText;
		VL.iMode = VERIFYMODE_ShowDialogSync;
		DEX_ShowLicenseDenyDialog(VL);
	}
	else
#endif // _TRiAS_VER >= 0x0510
	{
		ShowTipAtStartup();
		if (!DEXN_ShowProjectWizard(m_dwTOTD) && !(TOTD_ForceNoWizard & m_dwTOTD))
			ShowProjectWizard();
	}
	return true;
}

bool CFakeMFCExtension::OnExtensionsLoaded (void)
{
	if (g_dwHookFlags & TRIASMODE_SubClassTRiAS) {
	CMainFrame *pFrame = (CMainFrame *)MWind();

		ASSERT(NULL != pFrame);
		try {
#if defined(_USE_WIN32S_CODE)
			pFrame -> LoadToolbarState (IsWin32s() ? g_cbLayoutRoot : g_cbLayout);
#else
			pFrame -> LoadToolbarState (g_cbLayout);
#endif // defined(_USE_WIN32S_CODE)
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
	if (g_dwHookFlags & TRIASMODE_SubClassTRiAS) {
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
	CCurrentUser regTip (KEY_READ, g_cbRegSection);
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
	CCurrentUser regOWiz (KEY_READ, g_cbMRUFiles);
	DWORD dwData = 0;

		if (regOWiz.GetDWORD (g_cbHideOpenWizard, dwData) && 0 != dwData) {
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
CMainFrame *pFrame = (CMainFrame *)MWind();

	ASSERT(NULL != pFrame);
	m_pViewWnd = m_pDocTempl -> SubclassView (pFrame, hViewWnd);
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
	CMainFrame *pFrame = (CMainFrame *)MWind();

		ASSERT(NULL != pFrame);
		pFrame -> SetActiveView (NULL, FALSE);
#if defined(_SEC_USE_TABWND)
		pFrame -> OnDeleteSubclassedView (hViewWnd);
#endif // defined(_SEC_USE_TABWND)

	// jetzt Fenster wieder abmelden
	HWND hWndOld = m_pViewWnd -> UnsubclassWindow();

		ASSERT(hWndOld == hViewWnd);

		m_pViewWnd -> m_hWnd = NULL;
		DELETE_OBJ(m_pViewWnd);
	}
	return true;
}

#if defined(_SEC_SUBCLASS_ORWND)
bool CFakeMFCExtension::OnORWndCreated (HWND hORWnd)
{
// ORWndObjekt anlegen
	if (g_dwHookFlags & TRIASMODE_SubClassTRiAS) {
	CWnd *pWnd = NULL;

		ATLTRY(pWnd = new CWnd());
		if (NULL == pWnd) return false;

	HWND hWndOld = pWnd -> Detach();

		if (NULL != hWndOld && ::IsWindow (hWndOld))
			::DestroyWindow (hWndOld);
		if (!pWnd -> SubclassWindow (hORWnd))
			return false;

	CMainFrame *pFrame = (CMainFrame *)MWind();

		ASSERT(NULL != pFrame);
		pFrame -> CreateDockableORWnd (pWnd);		
	}
	return true;
}

bool CFakeMFCExtension::OnORWndDeleted (HWND hORWnd)
{
CWnd *pWnd = CWnd::FromHandlePermanent(hORWnd);

	if (NULL != pWnd && ::IsWindow(pWnd -> m_hWnd)) {
	HWND hWndOld = NULL;

		if (g_dwHookFlags & TRIASMODE_SubClassTRiAS) {
			hWndOld = pWnd -> UnsubclassWindow();
			ASSERT(hWndOld == hORWnd);

		CMainFrame *pFrame = (CMainFrame *)MWind();

			ASSERT(NULL != pFrame);
			pFrame -> FreeDockableORWnd (pWnd);
		}
	}
	return true;
}
#endif // _SEC_SUBCLASS_ORWND

///////////////////////////////////////////////////////////////////////////////
// Open existing project
bool CFakeMFCExtension::ShowOpenprojectCommand (void)
{
// Das Caption richtig einstellen
CString strTitle;
CString strDocName;

	VERIFY(strTitle.LoadString (IDS_FILEOPENCAPTION));
	ATLTRY(strTitle = FakeTRiASName (strTitle, g_cbTRiAS).c_str());

// jetzt (endlich) den Dialog anzeigen
DWORD dwFlags = OFN_OVERWRITEPROMPT|OFN_FILEMUSTEXIST;
BOOL fReadOnly = TRUE;
CString strFile;
int iFilter = 0;

	dwFlags |= IsWin40() ? OFN_EXPLORER : OFN_LONGNAMES;
	if (!DoPromptFileName (strFile, strTitle, dwFlags, TRUE, fReadOnly, m_pDocTempl, &iFilter))
		return false;

// Dateiname wurde erfolgreich eingegeben, Projekt eröffnen
HRESULT hr = S_OK; 

	try {
		if (3 == iFilter || 0 == iFilter) {
		os_path path = os_string(strFile);

			if (!stricmp (path.extension().c_str(), g_cbRis+1)) 
				iFilter = 2;	// die gewünschte Datei hat die Dateiendung *.ris
			else 
				iFilter = 1;	// alle anderen als Workspace öffnen
		}

		switch (iFilter) {
		default:	// error ?
			ASSERT(0 <= iFilter && iFilter < 4);
			break;

		case 0:		// custom filter
		case 1:		// *.riw
		case 3:		// *.*: entweder *.riw oder *.ris
			{
			CAniWaitCursor Wait(ANICURSOR_LOAD);

				THROW_FAILED_HRESULT(hr = OpenExistingProject (strFile, fReadOnly));
			}
			break;

		case 2:		// *.ris
			{
			CAniWaitCursor Wait(ANICURSOR_LOAD);

				THROW_FAILED_HRESULT(hr = CreateNewProjectOpenAndConvertDatasource (strFile, fReadOnly));
			}
			break;
		}

	// Projekt neu zeichnen
		if (S_OK == hr && NULL != m_pViewWnd)
			m_pViewWnd -> InvalidateRect(NULL);

	} catch (_com_error &) {
		return false;
	}
	return (S_OK == hr) ? true : false;
}

HRESULT CFakeMFCExtension::OpenExistingProjectOrDatasource (LPCSTR pcName, bool fRO)
{
// Projekt eröffnen
os_path path = os_string(pcName);

	if (!stricmp (path.extension().c_str(), g_cbRis+1)) {
	// TRiAS-Datenquelle öffnen und implizit konvertieren
		return CreateNewProjectOpenAndConvertDatasource (pcName, fRO);
	} 
    else {
	// ansonsten versuchen, als TRiAS Workspace eröffnen
		return OpenExistingProject (pcName, fRO);
	} 
}

///////////////////////////////////////////////////////////////////////////////
// Open last MRU projects
bool CFakeMFCExtension::OpenLastMRUProject (UINT uiMenuID)
{
#if defined(_BLOCK_CLOSING_DURING_OPENING)
CScopeVar<LONG> fOpening (m_ulOpenSem, 1L);

	if (!fOpening) {
	// nicht ein 2. mal Öffnen
		ASSERT(FALSE);
		return TRUE;
	}
#endif // defined(_BLOCK_CLOSING_DURING_OPENING)

// MRU-Eintrag von TRiAS besorgen
char cbBuffer[_MAX_PATH +1];
GETMRUITEM MRU;

	INITSTRUCT(MRU, GETMRUITEM);
	MRU.uiMenuID = uiMenuID+MenuOffset();
	MRU.pName = cbBuffer;
	MRU.iLen = sizeof(cbBuffer);
	MRU.fStartup = TRUE;

HRESULT hr = S_OK;

	if (DEX_GetMRUItem (MRU)) {
	// Projekt eröffnen
	CAniWaitCursor Wait(ANICURSOR_LOAD);

		if (SUCCEEDED(hr = OpenExistingProjectOrDatasource (cbBuffer, FALSE/*MRU.fRO*/))) {		// #HK000718: jetzt immer !RO öffnen
		// Projekt neu zeichnen
			if (NULL != m_pViewWnd)
				m_pViewWnd -> InvalidateRect(NULL);
			return true;
		}
	}

	if (E_ABORT != hr) {
	// ansonsten MenuEinträge verwerfen
	DELMRUITEM DELMRU;

		INITSTRUCT(DELMRU, DELMRUITEM);
		DELMRU.uiMenuID = uiMenuID+MenuOffset();
		DELMRU.fStartup = TRUE;
		DEX_RemoveMRUItem (DELMRU);

		DELMRU.fStartup = FALSE;
		DEX_RemoveMRUItem (DELMRU);
	}
	return false;
}

static void AppendFilterSuffix(CString& filter, OPENFILENAME& ofn,
	CDocTemplate* pTemplate, CString* pstrDefaultExt)
{
	ASSERT_VALID(pTemplate);
	ASSERT_KINDOF(CDocTemplate, pTemplate);

	CString strFilterExt, strFilterName;
	if (pTemplate->GetDocString(strFilterExt, CDocTemplate::filterExt) &&
	 !strFilterExt.IsEmpty() &&
	 pTemplate->GetDocString(strFilterName, CDocTemplate::filterName) &&
	 !strFilterName.IsEmpty())
	{
		// a file based document template - add to filter list
		ASSERT(strFilterExt[0] == '.');
		if (pstrDefaultExt != NULL)
		{
			// set the default extension
			*pstrDefaultExt = ((LPCTSTR)strFilterExt) + 1;  // skip the '.'
			ofn.lpstrDefExt = (LPTSTR)(LPCTSTR)(*pstrDefaultExt);
			ofn.nFilterIndex = ofn.nMaxCustFilter + 1;  // 1 based number
		}

		// add to filter
		filter += strFilterName;
		ASSERT(!filter.IsEmpty());  // must have a file type name
		filter += (TCHAR)'\0';  // next string please
		filter += (TCHAR)'*';
		filter += strFilterExt;
		filter += (TCHAR)'\0';  // next string please
		ofn.nMaxCustFilter++;
	}
}

BOOL CFakeMFCExtension::DoPromptFileName (
	CString &strFile, CString title, DWORD dwFlags, BOOL fOpenDlg, 
	BOOL &rfReadOnly, CDocTemplate* pTemplate, int *piFilter)
{
CFileDialog dlgFile(fOpenDlg);

	dlgFile.m_ofn.Flags |= dwFlags;
	if (rfReadOnly)
		dlgFile.m_ofn.Flags &= ~OFN_HIDEREADONLY;

#if defined(OFN_ENABLESIZING)
	if (IsWin41() || (IsWinNT() && IsWin50())) {		// Win98 oder WinNT50
		dlgFile.m_ofn.Flags |= OFN_ENABLESIZING;
#if defined(OFN_DONTADDTORECENT)
		dlgFile.m_ofn.Flags |= OFN_DONTADDTORECENT;
#endif // defined(OFN_DONTADDTORECENT)
	}
#endif // OFN_ENABLESIZING

CString strFilter;
CString strDefault;

	if (pTemplate != NULL) {
		ASSERT_VALID(pTemplate);
		AppendFilterSuffix(strFilter, dlgFile.m_ofn, pTemplate, &strDefault);
	} else {
	// do for all doc template
	CDocManager *pDocMgr = AfxGetApp() -> m_pDocManager;

		if (NULL != pDocMgr) {
		POSITION pos = pDocMgr->GetFirstDocTemplatePosition();
		BOOL bFirst = TRUE;

			while (NULL != pos) {
			CDocTemplate *pTemplate = pDocMgr->GetNextDocTemplate(pos);

				AppendFilterSuffix(strFilter, dlgFile.m_ofn, pTemplate,
					bFirst ? &strDefault : NULL);
				bFirst = FALSE;
			}
		}
	}

// %TODO%: enumerate all registered Database-Servers supporting
// <i ITRiASAccessDatabase>- Interface
// append the "*.ris" TRiAS Database filter
CString risFilter;
	
	VERIFY(risFilter.LoadString(IDS_RISFILTER));
	ATLTRY(risFilter = FakeTRiASName (risFilter, g_cbTRiAS).c_str());

	strFilter += risFilter;
	strFilter += (TCHAR)'\0';   // next string please
	strFilter += _T("*");
	strFilter += g_cbRis;
	strFilter += '\0';
	dlgFile.m_ofn.nMaxCustFilter++;

// append the "*.*" all files filter
CString allFilter;

	VERIFY(allFilter.LoadString(AFX_IDS_ALLFILTER));
	strFilter += allFilter;
	strFilter += (TCHAR)'\0';   // next string please

	strFilter += _T("*.*");
	strFilter += (TCHAR)'\0';   // last string

	dlgFile.m_ofn.nMaxCustFilter++;
	dlgFile.m_ofn.lpstrFilter = strFilter;
	dlgFile.m_ofn.lpstrTitle = title;

	dlgFile.m_ofn.lpstrFile = strFile.GetBuffer(_MAX_PATH);

// evtl. Startverzeichnis setzen
CRegKey key;
CRegKey keyDirs;
CRegKey keyMRU;
char cbBuffer[_MAX_PATH+1];

	dlgFile.m_ofn.lpstrInitialDir = NULL;
	if (ERROR_SUCCESS == key.Open(HKEY_CURRENT_USER, TEXT("Software"), KEY_READ) &&
		ERROR_SUCCESS == key.Open(key, REG_COMPANY_KEY, KEY_READ) &&
		ERROR_SUCCESS == key.Open(key, REG_PRODUCT_KEY, KEY_READ))
	{
	DWORD dwLen = sizeof(cbBuffer);

		if (ERROR_SUCCESS == keyDirs.Open(key, g_cbDirectories)) {
			if (ERROR_SUCCESS == keyDirs.QueryValue(cbBuffer, g_cbLastOpenDir, &dwLen))
				dlgFile.m_ofn.lpstrInitialDir = cbBuffer;
			else {
				dwLen = sizeof(cbBuffer);
				if (ERROR_SUCCESS == keyDirs.QueryValue (cbBuffer, g_cbDefaultDir, &dwLen))
					dlgFile.m_ofn.lpstrInitialDir = cbBuffer;
			}
		}
		
	// letzter Dateityp
	DWORD dwFilter = 0;

		if (ERROR_SUCCESS == keyMRU.Open(key, g_cbOpenMRU))
			keyMRU.QueryValue (dwFilter, g_cbLastFilter);
		dlgFile.m_ofn.nFilterIndex = dwFilter;
	}

BOOL bResult = dlgFile.DoModal() == IDOK ? TRUE : FALSE;

	rfReadOnly = (dlgFile.m_ofn.Flags & OFN_READONLY) ? TRUE : FALSE;
	if (NULL != piFilter)
		*piFilter = dlgFile.m_ofn.nFilterIndex;

	strFile.ReleaseBuffer();

	if (bResult) {
		if (NULL != keyDirs.m_hKey) {
		// evtl. letztes Verzeichnis wegschreiben
		os_path path = os_string(strFile);
		os_string str = path.drive() + path.drive_separator() + path.directory();

			keyDirs.SetValue (os_string(str).c_str(), g_cbLastOpenDir);
		}
		if (NULL != keyMRU.m_hKey)
			keyMRU.SetValue ((DWORD)dlgFile.m_ofn.nFilterIndex, g_cbLastFilter);
	}
	return bResult;
}

///////////////////////////////////////////////////////////////////////////////
// DBEngine Guids in cache speichern
HRESULT CFakeMFCExtension::
CEnumGuids::InitGuids (bool fForce)
{
	if (!m_fIsInitialized || fForce) {
		Clear();					// alles bisherige vergessen
		m_fIsInitialized = false;
		
	// neu füllen
		COM_TRY {
		WEnumGUID EnumGuids;		// Enumerator der DBEngine-Objekte
		WCatInformation CatInfo (CLSID_CatSimpleCache);	// throws hr
		GUID guid, guidImpl[1]; 

			guidImpl[0] = CATID_TRiASDBEngine;
			THROW_FAILED_HRESULT(CatInfo -> EnumClassesOfCategories (1, guidImpl, 0, NULL, EnumGuids.ppi()));

		// alle Guids umkopieren
			for (EnumGuids -> Reset(); S_OK == EnumGuids -> Next (1, &guid, NULL); /**/)
				THROW_FAILED_HRESULT(AddItem (guid));

		} COM_CATCH;
		m_fIsInitialized = true;
	} 
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// DropTarget für CF_DROP
#if defined(_USE_DRAG_N_DROP)
// *** ITRiASDropTarget
STDMETHODIMP CFakeMFCExtension::DragEnter (
	DRAGDROPTYPE rgType, HWND hWnd, IDataObject *pDataObj, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect)
{
#if _TRiAS_VER < 0x0400
	if (0 == g_dwVer4)	
		return S_FALSE;		// man darf ja vorher nicht alles verraten
#endif // _TRiAS_VER < 0x0400

	if (FAILED(EnsureFileExtensionList()))
		return S_FALSE;

// alten DataSource löschen
	m_DataObject.Assign(NULL);

	if (rgType != DRAGDROPTYPE_VIEWWINDOW && rgType != DRAGDROPTYPE_FRAMEWINDOW)
		return S_FALSE;

// Testen, ob wird diese Daten verstehen, bzw. obs mit der linken Maustaste passiert
	if ((grfKeyState & MK_RBUTTON) || !QueryPasteFromData (pDataObj)) 
		return S_FALSE;

// ok, Daten sind verständlich
	if (NULL == pdwEffect)
		return E_POINTER;
		
	*pdwEffect |= DROPEFFECT_MOVE;		// kein besonderer Cursor
	*pdwEffect &= ~DROPEFFECT_COPY;		// andere waren ggf. schon da

	m_DataObject = pDataObj;
	return S_OK;
}

STDMETHODIMP CFakeMFCExtension::DragOver (
	DRAGDROPTYPE rgType, HWND hWnd, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect)
{
#if _TRiAS_VER < 0x0400
	if (0 == g_dwVer4)
		return S_FALSE;		// man darf ja vorher nicht alles verraten
#endif // _TRiAS_VER < 0x0400

	if (rgType != DRAGDROPTYPE_VIEWWINDOW && rgType != DRAGDROPTYPE_FRAMEWINDOW)
		return S_FALSE; 

	if (!m_DataObject.IsValid())
		return S_FALSE;

// Testen, ob wird diese Daten verstehen, bzw. obs mit der linken Maustaste passiert
	if ((grfKeyState & MK_RBUTTON) || !QueryPasteFromData (m_DataObject)) 
		return S_FALSE;

// ok, Daten sind verständlich
	if (NULL == pdwEffect)
		return E_POINTER;
		
	*pdwEffect |= DROPEFFECT_MOVE;		// kein besonderer Cursor
	*pdwEffect &= ~DROPEFFECT_COPY;		// andere waren ggf. schon da

	return S_OK;
}

STDMETHODIMP CFakeMFCExtension::DragLeave (DRAGDROPTYPE rgType, HWND hWnd)
{
#if _TRiAS_VER < 0x0400
	if (0 == g_dwVer4)
		return S_FALSE;		// man darf ja vorher nicht alles verraten
#endif // _TRiAS_VER < 0x0400

	if (rgType != DRAGDROPTYPE_VIEWWINDOW && rgType != DRAGDROPTYPE_FRAMEWINDOW)
		return S_FALSE; 

	if (!m_DataObject.IsValid())
		return S_FALSE;

	m_DataObject.Assign(NULL);
	return S_OK;
}

STDMETHODIMP CFakeMFCExtension::Drop (
	DRAGDROPTYPE rgType, HWND hWnd, IDataObject *pDataObj, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect)
{
#if _TRiAS_VER < 0x0400
	if (0 == g_dwVer4)
		return S_FALSE;		// man darf ja vorher nicht alles verraten
#endif // _TRiAS_VER < 0x0400

	if (rgType != DRAGDROPTYPE_VIEWWINDOW && rgType != DRAGDROPTYPE_FRAMEWINDOW)
		return S_FALSE; 

	if (!m_DataObject.IsValid())
		return S_FALSE;

BOOL fResult = PasteFromData(m_DataObject);

	if (NULL == pdwEffect)
		return E_POINTER;
		
	*pdwEffect |= DROPEFFECT_MOVE;		// kein besonderer Cursor
	*pdwEffect &= ~DROPEFFECT_COPY;		// andere waren ggf. schon da

	m_DataObject.Assign(NULL);
	return fResult ? S_OK : E_UNEXPECTED;
}

///////////////////////////////////////////////////////////////////////////////
// Einlesen der Liste der gültigen Dateierweiterungen der verschiedenen
// registrierten Datenserver
HRESULT CFakeMFCExtension::EnsureFileExtensionList()
{
	if (!m_fHasExts) {
	// gecachte GUID's verwenden
	GUID guid;

		m_lstExts.clear();

		_ASSERTE(s_DBEngineGUIDs.IsValid());
		for (s_DBEngineGUIDs.Reset(); S_OK == s_DBEngineGUIDs.Next (1, &guid, NULL); /**/)
		{
			if (CLASS_E_NOTLICENSED == InitFileExtensionList(guid))
				s_DBEngineGUIDs.RemoveActiveItem();
		}
		m_fHasExts = true;
	}
	return (m_lstExts.size() > 0) ? S_OK : S_FALSE;
}

HRESULT CFakeMFCExtension::InitFileExtensionList (REFGUID rGuid)
{
LPOLESTR poleStr = NULL;

	USES_CONVERSION;
	COM_TRY {
	// DBEngine instantiieren und nach EnumString fragen
	WTRiASDBEngine DBEng;
	WUnknown Unk;
	HRESULT hr = DBEng.CreateInstance(rGuid);

		if (SUCCEEDED(hr))
			hr = DBEng -> EnumDataBaseTypes (Unk.ppi());
		if (FAILED(hr))
			return hr;	// registriert, aber nicht instantiierbar, oder allg. Fehler

	// jetzt eigentliche Dataserver einfügen
	WEnumString EnumStr(Unk);

		for (EnumStr -> Reset(); S_OK == EnumStr -> Next (1, &poleStr, NULL); /**/)
		{
		CConnectParams Item;
		DWORD dwDummy = 0;
		HRESULT hr = ReadDataServerParams (dwDummy, &Item, OLE2A(poleStr));

			CoTaskMemFree (poleStr);
			poleStr = NULL;

		// nur dateibasierte Datenquelle untersuchen
			if (!Item.m_fNameIsFile)
				continue;

		// '.' in Dateiendung wegschneiden
			m_lstExts.insert(CExtensions::value_type(os_string((LPCSTR)Item.m_strDefExt +1), Item));
		}

	} COM_CATCH_OP(CoTaskMemFree (poleStr));
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Testen, ob die D&D Daten was für uns sind
BOOL CFakeMFCExtension::QueryPasteFromData(IDataObject *pIDO)
{
	_ASSERTE(NULL != pIDO);
	
static FORMATETC fmtEtc = { CF_HDROP, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };

	if (FAILED(pIDO -> QueryGetData(&fmtEtc)))
		return FALSE;

STGMEDIUM stgmed;
BOOL fResult = FALSE;

	ZeroMemory(&stgmed, sizeof(stgmed));
	if (SUCCEEDED(pIDO -> GetData (&fmtEtc, &stgmed))) {
	HDROP hDrop = (HDROP)GlobalLock(stgmed.hGlobal);

		if (NULL != hDrop) {
		UINT nFiles = DragQueryFile(hDrop, (UINT)-1, NULL, 0);

			for (UINT nNames = 0; nNames < nFiles; nNames++) {
			// genau eine Datei untersuchen
			TCHAR szFileName[_MAX_PATH + 1];
			
				ZeroMemory(szFileName, _MAX_PATH + 1);
				DragQueryFile (hDrop, nNames, (LPTSTR)szFileName, _MAX_PATH + 1);

			// Dateiendung herausarbeiten und nachsehen, ob's was bekanntes ist
			os_path path (szFileName);
			CExtensions::iterator it = m_lstExts.find(path.extension());

				if (it != m_lstExts.end() || (0 == stricmp(path.extension().c_str(), g_cbRiw +1))) {
					fResult = TRUE;		// was bekanntes gefunden
					break;
				}
			}
			GlobalUnlock(hDrop);
		}
		ReleaseStgMedium(&stgmed);
	}
	return fResult;
}

///////////////////////////////////////////////////////////////////////////////
// Daten nun wirklich verarbeiten
BOOL CFakeMFCExtension::PasteFromData(IDataObject *pIDO)
{
	_ASSERTE(NULL != pIDO);
	
static FORMATETC fmtEtc = { CF_HDROP, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };

	if (FAILED(pIDO -> QueryGetData(&fmtEtc)))
		return FALSE;

// einmal durchgehen und nachsehen, was zu tun ist
os_path pathPrj;
list<os_path> Files;
STGMEDIUM stgmed;

	ZeroMemory(&stgmed, sizeof(stgmed));
	if (SUCCEEDED(pIDO -> GetData (&fmtEtc, &stgmed))) {
	HDROP hDrop = (HDROP)GlobalLock(stgmed.hGlobal);

		if (NULL != hDrop) {
		UINT nFiles = DragQueryFile(hDrop, (UINT)-1, NULL, 0);

			for (UINT nNames = 0; nNames < nFiles; nNames++) {
			// genau eine Datei untersuchen
			TCHAR szFileName[_MAX_PATH + 1];
			
				ZeroMemory(szFileName, _MAX_PATH + 1);
				DragQueryFile (hDrop, nNames, (LPTSTR)szFileName, _MAX_PATH + 1);

			// Dateiendung herausarbeiten und nachsehen, ob's was bekanntes ist
			os_path path (szFileName);
			CExtensions::iterator it = m_lstExts.find(path.extension());

				if (it != m_lstExts.end()) 
					Files.push_back(path);
				else if (0 == stricmp (path.extension().c_str(), g_cbRiw +1)) 
					pathPrj = path;
			}
			GlobalUnlock(hDrop);
		}
		ReleaseStgMedium(&stgmed);
	}

// jetzt tun, was zu tun ist
CMainFrame *pFrame = (CMainFrame *)MWind();

	ASSERT(NULL != pFrame);
	if (!pFrame -> ManageConnectionsIsOpen() && os_string(pathPrj).size() > 0) {
	// riw wurde gefunden, also selbige als Grundlage öffnen (nur wenn 
	// 'Datenquellen verwalten' nicht geöffnet ist
	WTRiASProject Prj;

		{
		CAniWaitCursor Wait(ANICURSOR_LOAD);

			if (FAILED(OpenExistingProject(pathPrj, FALSE, Prj.ppi())))
				return FALSE;
		}

	// alle übergebenen Datenquellen ins Projekt einbauen
		for (list<os_path>::iterator it = Files.begin(); it != Files.end(); ++it) {
		// BeschreibungsInfo dieses Datenquellentypes finden
		CAniWaitCursor Wait(ANICURSOR_LOAD);
		CExtensions::iterator itext = m_lstExts.find((*it).extension());
 
			if (itext == m_lstExts.end()) {
				_ASSERTE(itext != m_lstExts.end());
				continue;		// snh
			}

		// Datenquelle mit Standardparametern zu Projekt hinzufügen
		HRESULT hr = OpenDataSource (Prj, LPCSTR(*it), &(*itext).second);

			if (FAILED(hr)) {
			// Fehlermeldung ausgeben
				VMessageBox (MWind(), FakeTRiASName(IDS_PROJECTERROR_CAP, g_cbTRiAS).c_str(), 
					MB_OK|MB_ICONEXCLAMATION, IDS_COULDNOTOPENDATASOURCE, LPCSTR(*it), hr);
			}
		}
	}
	else {
	// nur Datenquellen gegeben
	WTRiASProject Prj;
	list<os_path>::iterator it = Files.begin();
	HRESULT hr = E_FAIL;

		if (!DEX_GetActiveProjectPtr(*Prj.ppi())) {
		// noch kein aktuelles Projekt: erste Datenquelle konvertieren
		CAniWaitCursor Wait(ANICURSOR_LOAD);

			do {
			// BeschreibungsInfo dieses Datenquellentypes finden
			CExtensions::iterator itext = m_lstExts.find((*it).extension());

				_ASSERTE(itext != m_lstExts.end());
				if (itext != m_lstExts.end()) 
					hr = CreateNewProjectOpenAndConvertDatasource(LPCSTR(*it), FALSE, &(*itext).second, Prj.ppi());
					
				++it;	// nächste Datenquelle
			} while (FAILED(hr) && it != Files.end());
		}

	// verbliebenden Datenquellen zu nun geöffneten Projekt hinzufügen
		_ASSERTE(Prj.IsValid());
		
		for (/**/; it != Files.end(); ++it) {
		// BeschreibungsInfo dieses Datenquellentypes finden
		CAniWaitCursor Wait(ANICURSOR_LOAD);
		CExtensions::iterator itext = m_lstExts.find((*it).extension());
 
			if (itext == m_lstExts.end()) {
				_ASSERTE(itext != m_lstExts.end());
				continue;		// snh
			}

		// Datenquelle mit Standardparametern zu Projekt hinzufügen
		HRESULT hr = OpenDataSource (Prj, LPCSTR(*it), &(*itext).second);

			if (FAILED(hr)) {
			// Fehlermeldung ausgeben
				VMessageBox (MWind(), FakeTRiASName(IDS_PROJECTERROR_CAP, g_cbTRiAS).c_str(), 
					MB_OK|MB_ICONEXCLAMATION, IDS_COULDNOTOPENDATASOURCE, LPCSTR(*it), hr);
			}
		}
	}

// in evtl. angezeigtem Fenster die neuen Datenquellen einblenden
	if (pFrame -> ManageConnectionsIsOpen())
		pFrame -> RefreshConnections();

	return TRUE;
}
#endif // defined(_USE_DRAG_N_DROP)

